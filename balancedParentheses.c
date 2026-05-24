// Balanced Parentheses
// Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
// determine if the input string has balanced brackets.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

// Stack-based approach: push opening brackets, pop and validate on closing ones.
// Chosen over recursion to avoid stack overflow on long expressions,
// and because manual stack management is O(n) time and O(n) space.
bool isValid(char *s) {
    char stack[MAX];
    int top = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else {
            if (top == -1) return false;

            char open = stack[top--];
            if ((c == ')' && open != '(') ||
                (c == '}' && open != '{') ||
                (c == ']' && open != '[')) {
                return false;
            }
        }
    }

    return top == -1;
}

int main() {
    printf("%d\n", isValid("()[]{}"));   // 1 (true)
    printf("%d\n", isValid("([)]"));     // 0 (false)
    printf("%d\n", isValid("{[]}"));     // 1 (true)
    return 0;
}
