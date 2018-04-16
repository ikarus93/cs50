from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    # TODO
    a, b = a.split("\n"), b.split("\n")
    return list(set([line for line in a if line in b]))


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    a, b = sent_tokenize(a, language='english'), sent_tokenize(b, language='english')
    return list(set([sentence for sentence in a if sentence in b]))



def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    def retrieve_sub(s, n):
      """Retrieves the substrings of length n from the given string"""
      subs = []
      for idx, char in enumerate(s):
        sub = char
        c = 1
        for next_char in s[idx + 1:]:
          if c >= n:
            break
          else:
            sub += next_char
            c += 1
        subs.append(sub)
      return [x for x in subs if len(x) == n]

    # TODO
    subs_A, subs_B = retrieve_sub(a, n), retrieve_sub(b, n)

    return list(set([sub for sub in subs_A if sub in subs_B]))
