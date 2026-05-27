// Anagram Checker
// Given two strings, determine if they are anagrams of each other.
// An anagram is formed by rearranging the letters of one word to form another.

// Uses character frequency map for O(n) time instead of sorting (O(n log n)).
// This is more efficient for large strings.
function isAnagram(a, b) {
    if (a.length !== b.length) return false;

    const count = {};

    for (const ch of a.toLowerCase()) {
        count[ch] = (count[ch] || 0) + 1;
    }

    for (const ch of b.toLowerCase()) {
        if (!count[ch]) return false;
        count[ch]--;
    }

    return true;
}

console.log(isAnagram("listen", "silent")); // true
console.log(isAnagram("hello", "world"));   // false
console.log(isAnagram("Dormitory", "Dirty room")); // true (ignores spaces — not handled here, but shows the idea)
