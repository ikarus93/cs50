# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A word with the maximum amount of characters allowed for our program.

## According to its man page, what does `getrusage` do?

It gets the resource usage of the program/calling process.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 members

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because they are structs so we need to refer to their memory address.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

After opening the file and saving it in a file pointer called "*file", main iterates over each character in the file, constructing words from those characters
after checking if they are either lowercase alphabetical chars or an apostrophe.
Main() is using a for loop, that ends once the end of the file is reached.
If the character is a valid char it increments the index variable, and appends the character to the word string.
If the character is a number, we need to consume the rest of the string, then reset the index to 0 to skip over any words containing numbers.
Else if the character is not a valid char or number, it must be a delimiter to mark the end of a word (full stop, comma, space character).
In that case we finish our constructed word by appending a '\0', then incrementing the total word count,
check the word for validity and printing if valid, then reseting the index.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

By using fgetc we can ensure that the word only contains valid characters. We can also easily create strings not containing special characters like fullstops etc.


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because they are constants, meaning that they are immutable in that context.
