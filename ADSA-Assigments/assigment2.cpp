#include <iostream>

using namespace std;

long long power(long long base, int exp) {
    long long result = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }

    return result;
}

int main() {
    long long base;
    int exp;

    cout << "Enter base number: ";
    cin >> base;
    cout << "Enter exponent: ";
    cin >> exp;

    cout << "\n--- Input ---" << endl;
    cout << "Base: " << base << ", Exponent: " << exp << endl;

    long long result = power(base, exp);

    cout << "\n--- Output ---" << endl;
    cout << base << "^" << exp << " = " << result << endl;
    cout << "Time Complexity: O(log n) [where n is exponent]" << endl;

    return 0;
}