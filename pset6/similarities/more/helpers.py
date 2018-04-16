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
    for i in range(len(a) + 1):
        matrix.append([i])
    for i in range(len(b) + 1):
        matrix[0][i].append(i)

    # TODO
    return [[]]
