# String Zipper
# Given two strings, return a new string that interleaves their characters one at a time. If one string is longer, append the remaining characters at the end.

# Begin with the first character of the first string.

from itertools import zip_longest

def zip_strings(a, b):
   return "".join(c1 + c2 for c1, c2 in zip_longest(a, b, fillvalue=""))
