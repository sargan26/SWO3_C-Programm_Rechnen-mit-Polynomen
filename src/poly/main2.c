#include <stdio.h>
#include <stdlib.h>

#define MAX_POLY_SIZE 100

int poly_mult_fast(const long double p[], int m, const long double q[], int n, long double r[]) {
    if (m != n || (m & (m + 1)) != 0 || m > MAX_POLY_SIZE) {
        return -1; // Fehler: Ungültige Eingabe oder Polynomgröße überschritten
    }

    int degree_r = 2 * m;

    for (int i = 0; i <= degree_r; i++) {
        r[i] = 0.0;
    }

    if (m == 0) {
        r[0] = p[0] * q[0];
    } else {
        int half_degree = m / 2;
        long double a0[MAX_POLY_SIZE + 1];
        long double a1[MAX_POLY_SIZE + 1];
        long double b0[MAX_POLY_SIZE + 1];
        long double b1[MAX_POLY_SIZE + 1];
        long double result_low[(2 * MAX_POLY_SIZE) + 1];
        long double result_high[(2 * MAX_POLY_SIZE) + 1];

        if (m > MAX_POLY_SIZE || (m + 1) > MAX_POLY_SIZE || (2 * m) > (2 * MAX_POLY_SIZE)) {
            return -1; // Fehler: Polynomgröße überschritten
        }

        for (int i = 0; i <= half_degree; i++) {
            a0[i] = p[i];
            a1[i] = p[i + half_degree + 1];
            b0[i] = q[i];
            b1[i] = q[i + half_degree + 1];
        }

        poly_mult_fast(a0, half_degree, b0, half_degree, result_low);
        poly_mult_fast(a1, half_degree, b1, half_degree, result_high);

        for (int i = 0; i <= 2 * half_degree; i++) {
            result_low[i + half_degree] += (a0[i] + a1[i]) * (b0[i] + b1[i]) - result_low[i] - result_high[i];
        }

        for (int i = 0; i <= degree_r; i++) {
            r[i] = result_low[i];
            r[i + degree_r + 1] = result_high[i];
        }
    }

    return 0; // Erfolg
}

int main() {
    int m = 3; // Grad des Polynoms P(x) und Q(x)

    long double p[MAX_POLY_SIZE + 1] = {1.0, 2.0, 3.0, 4.0}; // Koeffizienten von P(x)
    long double q[MAX_POLY_SIZE + 1] = {0.5, 0.5, 0.5, 0.5}; // Koeffizienten von Q(x)

    int degree_r = 2 * m; // Grad des Ergebnispolynoms R(x)
    long double r[(2 * MAX_POLY_SIZE) + 1]; // Ergebnispolynom

    int result = poly_mult_fast(p, m, q, m, r);

    if (result == 0) {
        printf("Ergebnis der Polynom-Multiplikation:\n");
        for (int i = 0; i <= degree_r; i++) {
            printf("%Lf ", r[i]);
        }
        printf("\n");
    } else {
        printf("Fehler: Ungültige Eingabe oder Polynomgröße überschritten\n");
    }

    return 0;
}
