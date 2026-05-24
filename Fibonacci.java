// Fibonacci
// Generate the nth Fibonacci number. The sequence starts with 0 and 1,
// and each subsequent number is the sum of the two preceding ones.

public class Fibonacci {

    // Iterative approach - O(n) time, O(1) space.
    // Chosen over recursion to avoid exponential time complexity (O(2^n))
    // and the risk of stack overflow for large n.
    public static int fibonacci(int n) {
        if (n <= 1) {
            return n;
        }
        int a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            int temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }

    // Recursive approach - elegant but O(2^n) time, risks stack overflow.
    // Included for comparison: demonstrates why iteration is preferred.
    public static int fibonacciRecursive(int n) {
        if (n <= 1) {
            return n;
        }
        return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
    }

    public static void main(String[] args) {
        System.out.println("=== Iterative ===");
        for (int i = 0; i <= 10; i++) {
            System.out.println("fib(" + i + ") = " + fibonacci(i));
        }

        System.out.println("=== Recursive (slow for n > 40) ===");
        for (int i = 0; i <= 10; i++) {
            System.out.println("fib(" + i + ") = " + fibonacciRecursive(i));
        }
    }
}
