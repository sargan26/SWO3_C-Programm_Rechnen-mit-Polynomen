#include <stdio.h>
#include <stdlib.h>

double* karatsubaMultiplyRecursive(const double* multiplicand, const double* multiplier, int size) {
    double* product = (double*)malloc(2 * size * sizeof(double));

    // Handle the base case where the polynomial has only one coefficient
    if (size == 1) {
        product[0] = multiplicand[0] * multiplier[0];
        return product;
    }

    int halfArraySize = size / 2;

    // Declare arrays to hold halved factors
    double* multiplicandLow = (double*)malloc(halfArraySize * sizeof(double));
    double* multiplicandHigh = (double*)malloc(halfArraySize * sizeof(double));
    double* multiplierLow = (double*)malloc(halfArraySize * sizeof(double));
    double* multiplierHigh = (double*)malloc(halfArraySize * sizeof(double));
    double* multiplicandLowHigh = (double*)malloc(halfArraySize * sizeof(double));
    double* multiplierLowHigh = (double*)malloc(halfArraySize * sizeof(double));

    // Fill in the low and high arrays
    for (int halfSizeIndex = 0; halfSizeIndex < halfArraySize; ++halfSizeIndex) {
        multiplicandLow[halfSizeIndex] = multiplicand[halfSizeIndex];
        multiplicandHigh[halfSizeIndex] = multiplicand[halfSizeIndex + halfArraySize];
        multiplicandLowHigh[halfSizeIndex] = multiplicandLow[halfSizeIndex] + multiplicandHigh[halfSizeIndex];

        multiplierLow[halfSizeIndex] = multiplier[halfSizeIndex];
        multiplierHigh[halfSizeIndex] = multiplier[halfSizeIndex + halfArraySize];
        multiplierLowHigh[halfSizeIndex] = multiplierLow[halfSizeIndex] + multiplierHigh[halfSizeIndex];
    }

    // Recursively call the method on smaller arrays and construct the low and high parts of the product
    double* productLow = karatsubaMultiplyRecursive(multiplicandLow, multiplierLow, halfArraySize);
    double* productHigh = karatsubaMultiplyRecursive(multiplicandHigh, multiplierHigh, halfArraySize);
    double* productLowHigh = karatsubaMultiplyRecursive(multiplicandLowHigh, multiplierLowHigh, halfArraySize);

    // Construct the middle portion of the product
    double* productMiddle = (double*)malloc(size * sizeof(double));
    for (int halfSizeIndex = 0; halfSizeIndex < size; ++halfSizeIndex) {
        productMiddle[halfSizeIndex] = productLowHigh[halfSizeIndex] - productLow[halfSizeIndex] - productHigh[halfSizeIndex];
    }

    // Assemble the product from the low, middle, and high parts. Start with the low and high parts of the product.
    for (int halfSizeIndex = 0, middleOffset = size / 2; halfSizeIndex < size; ++halfSizeIndex) {
        product[halfSizeIndex] += productLow[halfSizeIndex];
        product[halfSizeIndex + size] += productHigh[halfSizeIndex];
        product[halfSizeIndex + middleOffset] += productMiddle[halfSizeIndex];
    }

    // Free dynamically allocated memory for intermediate arrays
    free(multiplicandLow);
    free(multiplicandHigh);
    free(multiplierLow);
    free(multiplierHigh);
    free(multiplicandLowHigh);
    free(multiplierLowHigh);
    free(productLow);
    free(productHigh);
    free(productMiddle);

    return product;
}

int main() {
    int size = 4; // Change this to the size of your arrays

    double multiplicand[] = {1.0, 1.0, 3.0, -4.0}; // Replace with your values
    double multiplier[] = {1.0, 2.0, -5.0, -3.0}; // Replace with your values

    double* product = karatsubaMultiplyRecursive(multiplicand, multiplier, size * 2);

    printf("Result of Karatsuba multiplication:\n");
    for (int i = 0; i < 2 * size; i++) {
        printf("%lf ", product[i]);
    }
    printf("\n");

    free(product); // Free dynamically allocated memory for the result

    return 0;
}
