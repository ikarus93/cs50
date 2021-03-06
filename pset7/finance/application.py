import os
import re
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash


from helpers import apology, login_required, lookup, usd, update_position

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
status_codes = {"One or more Input fields were empty": 400,
                "Non positive integer provided": 400,
                "Couldn't get stock price": 404,
    "Insufficient Balance": 403,
    "Wrong Password": 401
}

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "GET":
        try:

            #retrieve logged in users open positions based on user id
            user = session["user_id"]
            open_positions = db.execute("SELECT * from open_positions WHERE user_id = :user_id", user_id = user)
            profit = 0
            current_positions = []

            if open_positions:
                #retrieve current prices for each open position then save it in dictionary
                for row in open_positions:
                    latest_price = lookup(row["symbol"])
                    if not latest_price:
                        raise Exception("Error retrieving stockprice")
                    else:
                        latest_price = latest_price["price"]
                    total = latest_price * int(row["shares"])
                    profit += total
                    position = {
                        "symbol": row["symbol"],
                        "shares": row["shares"],
                        "price": latest_price,
                        "total": usd(total)
                    }
                    current_positions.append(position)
            #retrieve current users balance
            balance = db.execute("SELECT cash from users WHERE id = :user_id", user_id = user)[0]["cash"]
            total_balance = float(balance) + profit
            #append total cash row for template
            current_positions.append(
                {
                "symbol": "CASH",
                "shares": "",
                "price": "",
                "total": balance
            })
            return render_template("index.html", positions = current_positions, total_balance = usd(total_balance))

        except Exception as e:
            if str(e) in status_codes:
                return apology(str(e), status_codes[str(e)])
            else:
                return apology(str(e))

    else:
        return apology("Wrong Method")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        try:

            sym = request.form.get("symbol")
            shares = int(request.form.get("shares"))
            if not sym or not shares:
                #If input from has empty fields
                raise Exception("One or more Input fields were empty")
            if shares <= 0:
                #if non negative value was provided
                raise Exception("Non positive integer provided.")

            #lookup stock price
            price = lookup(sym)
            if not price:
                raise Exception("Couldnt lookup stock price")
            else:
                price = price["price"]
            #retrieve current users id
            user_id = session["user_id"]

            #calculate total price of transaction and check if user has valid credit
            total_price = price * shares
            user_credit = float(db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = user_id)[0]["cash"])
            if (user_credit - total_price) < 0:
                raise Exception("Insufficient Balance")

            #update users balance and add transaction to buy history table
            new_balance = user_credit - total_price
            db.execute("UPDATE users SET cash = :new_balance WHERE id = :user_id", new_balance = new_balance, user_id = user_id)

            # check if user already has open positions for stock symbol,
            #if yes - increase amount else add new entry to open_positions table
            user_position = db.execute("SELECT id, shares FROM open_positions WHERE symbol = :symbol AND user_id = :user_id", symbol = sym, user_id = user_id)
            if user_position:
                user_position = user_position[0]
                new_total = shares + user_position["shares"]
                update_position(db, new_total, price, user_position["id"])

            else:
                db.execute("INSERT INTO open_positions(id, user_id, symbol, price, shares) VALUES (NULL, :user_id, :symbol, :price, :shares)", user_id = user_id, symbol = sym, price = price, shares = shares)
            #create transaction object for template rendering
            transaction = {
                "type": "bought",
                "symbol": sym,
                "shares": shares,
                "price": price,
                "new_balance": usd(new_balance)
            }
            db.execute("INSERT INTO transaction_history(id, user_id, symbol, price, shares, type) VALUES (NULL, :user_id, :symbol, :price, :shares, :_type)", user_id = user_id, symbol = sym, price = price, shares = shares, _type = "buy")
            return render_template("success.html", transaction = transaction)

        except Exception as e:
            if str(e) in status_codes:
                #return exception name and status code if status code for given exception is in status_code dictionary defined at beginning of file
                return apology(str(e), status_codes[str(e)])
            else:
                return apology(str(e))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        try:
            user = session["user_id"]
            transactions = db.execute("SELECT * from transaction_history WHERE user_id = :user_id", user_id = user)
            positions = []
            for row in transactions:
                temp = {
                    "type": row["type"],
                    "symbol": row["symbol"],
                    "shares": row["shares"],
                    "price": usd(row["price"]),
                    "datetime": row["timestamp"]
                }
                positions.append(temp)
            return render_template("history.html", positions = positions)
        except Exception as e:
            if str(e) in status_codes:
                return apology(str(e), status_codes[str(e)])
            else:
                return apology(str(e))
    else:

        return apology("Only accept GET requests")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/user", methods=["GET"])
@login_required
def user():
    """Renders view containing user specific menu, like links to change password, input more cash, """
    return render_template("user.html")

@app.route("/addcash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "GET":
        return render_template("addcash.html", initial_render = True)
    elif request.method == "POST":
        try:
            card_number = request.form.get("card")
            try:
                credit_to_add = float(request.form.get("amount"))
            except:
                return apology("Please provide a numeric value")
            current_balance = db.execute("SELECT cash from users WHERE id = :user_id", user_id = session["user_id"])[0]["cash"]
            current_balance = float(current_balance)
            db.execute("UPDATE users SET cash = :new_balance WHERE id = :user_id", new_balance = credit_to_add + current_balance, user_id = session["user_id"])
            return render_template("addcash.html", initial_render = False, success = True, balance = usd(credit_to_add + current_balance))
        except Exception as e:
            if str(e) in status_codes:
                return apology(str(e), status_codes[str(e)])
            else:
                return apology(str(e))
    else:
        return apology("Wrong Method")

@app.route("/changepw", methods=["GET", "POST"])
@login_required
def change_pw():
    """Changes user password """
    if request.method == "GET":
        return render_template("change_pw.html", change_occured = False, success = False)
    elif request.method == "POST":
        try:
            user = session["user_id"]
            new_password = request.form.get("new-password")
            real_password = db.execute("SELECT hash from users WHERE id = :user_id", user_id = user)[0]["hash"]

            #verify user is user by cross comparing his put in password
            if not check_password_hash(real_password, request.form.get("password")):
                return render_template("change_pw.html", change_occured = True, success = False)

            new_password = generate_password_hash(new_password)
            db.execute("UPDATE users SET hash = :new_pw WHERE id = :user_id", new_pw = new_password, user_id = user)
            print("still here")
            return render_template("change_pw.html", change_occured = True, success = True)
        except Exception as e:
            if str(e) in status_codes:
                return apology(str(e), status_codes[str(e)])
            else:
                return apology(str(e))
    else:
        return apology("Invalid method used")

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    try:
        if request.method == "GET":
            return render_template("quote.html")
        if request.method == "POST":
            sym = request.form.get("symbol")
            if not sym:
                raise Exception("No stock symbol provided")
            result = lookup(sym)
            if not result:
                raise Exception("Couldn't get stock price")
            return render_template("quoted.html", price = usd(result["price"]), symbol = result["symbol"])
    except Exception as e:
        if str(e) in status_codes:
            return apology(str(e), status_codes[str(e)])
        else:
            return apology(str(e))




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    elif request.method == "POST":
        user = request.form.get("username")
        pw = request.form.get("password")

        if not re.search('\d.*[A-Za-z]|[A-Za-z].*\d', pw):
            return apology("Password must contain at least one letter and one number")
        if not user or not pw:
            return apology("Username or Password field empty")

        #check if username is already in db
        user_exists = db.execute("SELECT * from users WHERE username = :username", username = user)
        if user_exists:
            return apology("Username already exists")
        #if password field or password confirmation is empty or doesnt match
        if not pw or not request.form.get("confirmation") or pw != request.form.get("confirmation"):
            return apology("Password field empty or Passwords don't match")

        #hash pw and extract user_id as length from table, then create session with it
        hashed_pw = generate_password_hash(pw)
        user_id = len(db.execute("SELECT * from users"))
        session["user_id"] = user_id
        try:
            #insert new user into db
            db.execute("INSERT into users (id, username, hash) VALUES (:user_id, :username, :pw)", user_id = user_id, username = user, pw = hashed_pw)
        except:
            return apology("Database Error", 500)

        return redirect("/buy")
    else:
        return apology("Method not supported")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")

    elif request.method == "POST":
        try:
            symbol = request.form.get("symbol")
            shares = int(request.form.get("shares"))
            user = session["user_id"]
            #shares a user currently holds

            position = db.execute("SELECT id, shares from open_positions WHERE user_id = :user_id AND symbol = :symbol", user_id = user, symbol = symbol)[0]
            if not position:
                raise Exception("You don't own any shares from this stock")

            user_holds = int(position["shares"])
            difference = user_holds - shares
            if difference < 0:
                raise Exception("Insufficient shares owned")
            elif difference == 0:
                db.execute("DELETE from open_positions WHERE id = :position_id", position_id = position["id"])
            else:
                db.execute("UPDATE open_positions SET shares = :difference WHERE id = :position_id", difference = difference, position_id = position["id"])


            price = int(lookup(symbol)["price"])
            profit = price * shares

            #select users balance, reformat deleting dollar sign and commas
            user_balance = db.execute("SELECT cash from users WHERE id = :user_id", user_id = user)[0]["cash"]
            new_balance = float(user_balance) + profit
            db.execute("UPDATE users SET cash = :new_balance WHERE id = :user_id", new_balance = new_balance, user_id = user)
            transaction = {
                "type": "sold",
                "shares": shares,
                "symbol": symbol,
                "price":  price
            }
            db.execute("INSERT INTO transaction_history(id, user_id, symbol, price, shares, type) VALUES (NULL, :user_id, :symbol, :price, :shares, :_type)", user_id = user, symbol = symbol, price = price, shares = shares, _type = "sell")
            return render_template("success.html", transaction = transaction)
        except Exception as e:
            if str(e) in status_codes:
                return apology(str(e), status_codes[str(e)])
            else:
                return apology(str(e))
    else:
        return apology("Wrong method")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
