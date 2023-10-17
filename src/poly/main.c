#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 10

void print_array(double const p[], size_t const arr_len) {
   printf("array = {");
   for (size_t i = 0; i < arr_len; i++) {
      printf(" %f ", p[i]);
   }
   printf("}\n");
}

void print_sign(int num) {
   if (num >= 0) {
      printf(" + ");
   } else {
      printf(" - ");
   }
}

void print_coefficient(int num) {
   if (num != 1) {
      printf("%d*", abs(num));
   }
}

void print_potency(int num) {
   if (num != 1)
   {
      printf("x^%d", num);
   } else {
      printf("x");
   }
}

void poly_print (double const p [], int const m) {
   assert(m >= 0);

   printf("%d", (int)p[0]);
   for (int i = 1; i <= m; i++) {
      if (p[i] != 0) { // only show non-zero terms
         int num = (int)p[i];
         print_sign(num);
         print_coefficient(num);
         print_potency(i);
      }
   }
   printf("\n");
}

double poly_evaluate (double const p[], int const m, double const x) {
   double sum = 0.0;
   for (int i = 0; i <= m; i++) {
      sum += p[i] * pow(x, i);
   }
   return sum;
}

int poly_add (
   double const p[], int const m,
   double const q[], int const n,
   double       r[]) {
   int max = m > n ? m : n;
   for (int i = 0; i <= max; i++) {
      r[i] = p[i] + q[i];
   }
   return max;
}

int poly_mult (
   double const p[], int const m,
   double const q[], int const n,
   double       r[]) {
   // initalize result array
   for (int i = 0; i <= m+n; i++) {
      r[i] = 0;
   }
   
   // calculate new array
   for (int i = 0; i <= m; i++) {
      for (int j = 0; j <= n; j++) {
         r[i+j] += p[i] * q[j];
      }
   }
   return m + n;
}

//int poly_mult_fast (
//   double const p[], int const m,
//   double const q[], int const n,
//   double       r[]) {
//   // assertions
//   assert(m == n);
//   int k = log2(m + 1);
//   assert(m + 1 == pow(2, k));
//
//   return m + n;
//}

int main () {
   double p1[ARR_SIZE] = {4, 3, -2, 1,};
   poly_print(p1, 3);
   double p2[ARR_SIZE] = {0, 0, 0, 0,};
   poly_print(p2, 3);
   //double p3[ARR_SIZE] = {4, 3, -2, 1,};
   //poly_print(p3, -1);

   //print_array(p1, 4);
   printf("\n");
   double y;
   y = poly_evaluate(p1, 3, 1.5);
   printf("%f\n", y);
   y = poly_evaluate(p1, 3, -3.0);
   printf("%f\n", y);
   y = poly_evaluate(p1, 3, 0.0);
   printf("%f\n", y);   
   y = poly_evaluate(p1, 0, 1.5);
   printf("%f\n", y);   

   printf("\n");
   double p4[ARR_SIZE] = {1, 1, 3, -4};
   double p5[ARR_SIZE] = {1, 2, -5, -3, 0, -2};
   double r[ARR_SIZE];
   printf("grad of polynom = %d\n", poly_add(p4, 3, p5, 5, r));
   poly_print(r, 5);
   
   printf("\n");
   printf("grad of polynom = %d\n", poly_mult(p4, 3, p5, 5, r));
   poly_print(r, poly_mult(p4, 3, p5, 5, r));


   return EXIT_SUCCESS;
}
