# -*- coding: utf-8 -*-
# Author : Arpan Mahanty
# Team : Komodo

from random import sample

# Utility function to calculate nCr i.e., C(n,r).
def nCr(n,r):
    """
        Calculates nCr value i.e., number of possible combinatons that can be formed using
        n items selecting r at a time.
    """
    num = 1
    di = 1
    r = r if r >= n-r else n-r
    for i in range(n,r,-1):
        num *= i
    for i in range(n-r,0,-1):
        di *= i
    return num//di

# Utility Class to generate random combinations from a list of items taking k at a time.
class random_combination_gen:
    def __init__(self, i, r = 2, t = 10000):
        """
            Generates random combinations from a list of elements i,
            selecting r items at once, and continues till t combinations are generated.
        """
        self.used_combinations = dict()
        self.i = i
        self.r = r
        self.t = min(t, nCr(len(self.i), self.r))
    
    def __iter__(self):
        return self
    
    def __next__(self):
        if len(self.used_combinations)==self.t:
            raise StopIteration()
        idx = None
        while True:
            idx = tuple(sorted(sample(self.i, self.r)))
            if self.used_combinations.get(idx, True):
                self.used_combinations[idx] = False
                break
        return idx
    
    def __len__(self):
        return self.t

# Driver Code
if __name__ == '__main__':
    print(sorted(sample(range(3), 4)))