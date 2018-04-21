from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    matrix = []
    #create base cases for matrix
    for i in range(len(a) + 1):
      if i:
        op = Operation(1)
        matrix.append([(i, op)])
      else:
        matrix.append([(i, '')])
    for i in range(1, len(b) + 1):
        op = Operation(2)
        matrix[0].append((i, op))


    #iterate over each letter in target string, compare letter to character in base string,
    #if characters dont match find the minimum of 3 neighbors (according to algorithm) and add 1, else take neighbor from top left corners value
    #create tuple and append it to matrix
    for i, char1 in enumerate(b):
      i = i + 1
      for j, char2 in enumerate(a):
        j = j + 1
        if char1 is not char2:
          to_append = min(matrix[j][i - 1][0], matrix[j - 1][i - 1][0], matrix[j - 1][i][0]) + 1
          op = Operation(2)
        else:
          to_append = matrix[j - 1][i - 1][0]
          op = Operation(3)
        matrix[j].append((to_append, op))



    # TODO
    return matrix
