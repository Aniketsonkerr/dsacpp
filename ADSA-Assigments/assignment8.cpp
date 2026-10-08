#include <iostream>
#include <cmath>
#include <string>

void masterTheoremSolver(double a, double b, double k) {
    if (a < 1 || b <= 1) {
        std::cout << "Master Theorem does not apply (Invalid a or b values).\n";
        return;
    }

    double log_b_a = std::log2(a) / std::log2(b);
    double epsilon = 1e-9; // Precision threshold to handle floating-point comparison

    std::cout << "Recurrence: T(n) = " << a << "T(n/" << b << ") + n^" << k << "\n";
    std::cout << "n^(log_b a) = n^" << log_b_a << "\n";

    if (std::abs(log_b_a - k) < epsilon) {
        // Case 2: n^(log_b a) == n^k
        std::cout << "Applies: Case 2 (f(n) = Theta(n^(log_b a)))\n";
        std::cout << "Resulting Complexity: Theta(n^" << k << " * log n)\n";
    } else if (log_b_a > k + epsilon) {
        // Case 1: n^(log_b a) > n^k
        std::cout << "Applies: Case 1 (f(n) = O(n^(log_b a - epsilon)))\n";
        std::cout << "Resulting Complexity: Theta(n^" << log_b_a << ")\n";
    } else {
        // Case 3: n^(log_b a) < n^k
        std::cout << "Applies: Case 3 (f(n) = Omega(n^(log_b a + epsilon)))\n";
        std::cout << "Resulting Complexity: Theta(n^" << k << ")\n";
    }
    std::cout << "--------------------------------------------------\n";
}

int main() {
    std::cout << "=== MASTER THEOREM AUTOMATED SOLVER ===\n\n";
    masterTheoremSolver(2, 2, 1); // T(n) = 2T(n/2) + n
    masterTheoremSolver(4, 2, 1); // T(n) = 4T(n/2) + n
    masterTheoremSolver(4, 2, 2); // T(n) = 4T(n/2) + n^2
    masterTheoremSolver(4, 2, 3); // T(n) = 4T(n/2) + n^3
    masterTheoremSolver(1, 2, 0); // T(n) = T(n/2) + 1
    return 0;
}