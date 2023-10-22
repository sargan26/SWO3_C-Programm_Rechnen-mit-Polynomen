#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 20

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
   assert(m >= 0);
   
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
   assert(m >= 0 && n >= 0);   

   int max = m > n ? m : n;
   for (int i = 0; i <= max; i++) {
      r[i] = p[i] + q[i];
   }
   return max;
}

int poly_sub (
   double const p[], int const m,
   double const q[], int const n,
   double       r[]) {
   assert(m >= 0 && n >= 0);   

   int max = m > n ? m : n;
   for (int i = 0; i <= max; i++) {
      r[i] = p[i] - q[i];
   }
   return max;
}

int poly_mult (
   double const p[], int const m,
   double const q[], int const n,
   double       r[]) {
   int degree = n + m;
   assert(m >= 0 && n >= 0);   
   assert(degree <= ARR_SIZE);

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
   return degree;
}

int poly_mult_fast (
   double const p[], int const m,
   double const q[], int const n,
   double       r[]) {
   // assertions
   assert(m == n);
   int k = (int)log2(m + 1);
   assert(m + 1 == pow(2, k));
   assert(n + m <= ARR_SIZE);

   if (m == 0 || m == 1)
   {
      poly_mult(p,m,q,n,r);
      return m;
   }
   int highestPolyDeg = m;

   // initalize result array
   for (int i = 0; i <= m+n; i++) {
      r[i] = 0;
   }

   //init var
   int halfPoly=m/2;

   //init p and q halves 
   double pL[ARR_SIZE],pR[ARR_SIZE], qL[ARR_SIZE], qR[ARR_SIZE];
   double hL[ARR_SIZE],hR[ARR_SIZE], hM[ARR_SIZE];
   double hLtemp1[ARR_SIZE],hLtemp2[ARR_SIZE];

   for(int i = 0; i <= halfPoly; i++) {
      pL[i] = pR[i] = qL[i] = qR[i] = hLtemp1[i] = hLtemp1[i] = 0;
   }

   //init the rest
   for(int i = 0; i <= m; i++) {
      hL[i] = hR[i] = hM[i] = 0;
   }

   for (int i = 0; i <= halfPoly; i++) {
      pL[i] = p[i];
      pR[i] = p[i + halfPoly+1];
      qL[i] = q[i];
      qR[i] = q[i + halfPoly+1];
   }
   
   highestPolyDeg+= poly_mult_fast (pL, halfPoly, qL, halfPoly, hL);
   highestPolyDeg+= poly_mult_fast (pR, halfPoly, qR, halfPoly, hR);
   
   int polytemp = poly_add (pL, halfPoly, pR, halfPoly, hLtemp1);
   polytemp = poly_add (qL, halfPoly, qR, halfPoly, hLtemp2);

   highestPolyDeg += poly_mult_fast (hLtemp1, halfPoly, hLtemp2, halfPoly, hM);
   for (int i = 0; i <= m; i++) {
      r[i] += hL[i];
   }

   for (int i = 0; i < n; i++) {
      r[i + (m/2)+1] += hM[i] - hL[i] - hR[i];
   }
   for (int i = 0; i <= m; i++) {
      r[i + m + 1] += hR[i];
   }
   
   //poly_print(hL,m);
   
   //poly_print(r, highestPolyDeg);
   return highestPolyDeg;
}

int main () {
  double r[ARR_SIZE];
  
  /* double p1[ARR_SIZE] = {4, 3, -2, 1,};
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
   double p4[ARR_SIZE] = {1, 1, 3, -4,};
   double p5[ARR_SIZE] = {1, 2, -5, -3, 0, -2,};
   
   printf("degree of polynom = %d\n", poly_add(p4, 3, p5, 5, r));
   poly_print(r, 5);
   
   printf("\n");
   printf("degree of polynom = %d\n", poly_mult(p4, 3, p5, 5, r));
   poly_print(r, poly_mult(p4, 3, p5, 5, r));

   double p6[ARR_SIZE] = {1,};
   double p7[ARR_SIZE] = {2,};
   printf("\n");
   printf("degree of polynom = %d\n", poly_mult_fast(p6, 0, p7, 0, r));
   poly_print(r, poly_mult_fast(p6, 0, p7, 0, r));

   double p8[ARR_SIZE] = {1, 1, 3, -4,};
   double p9[ARR_SIZE] = {1, 2, -5, -3,};
   printf("\n");
   printf("degree of polynom = %d\n", poly_mult_fast(p8, 3, p9, 3, r));
   poly_print(r, poly_mult_fast(p8, 3, p9, 3, r));
   */

   double p10[ARR_SIZE] = {1, 1,};
   double p11[ARR_SIZE] = {1, 2,};
   printf("\n");
   printf("degree of polynom = %d\n", poly_mult_fast(p10, 1, p11, 1, r));
   poly_print(r, poly_mult_fast(p10, 1, p11, 1, r)); 

   double p12[ARR_SIZE] = {1, 1, 3, -4,};
   double p13[ARR_SIZE] = {1, 2, -5, -3,};
   printf("\n");
   printf("degree of polynom = %d\n", poly_mult_fast(p12, 3, p13, 3, r));
   poly_print(r, poly_mult_fast(p12, 3, p13, 3, r)); 

   double p14[ARR_SIZE] = {0,};
   double p15[ARR_SIZE] = {0,};
   printf("\n");
   printf("degree of polynom = %d\n", poly_mult_fast(p14, 0, p15, 0, r));
   poly_print(r, poly_mult_fast(p14, 0, p15, 0, r)); 

   double p16[ARR_SIZE] = {1, 2, 3,};
   double p17[ARR_SIZE] = {1, 2, 3};
   printf("\n");
   printf("degree of polynom = %d\n", poly_mult_fast(p16, 2, p17, 2, r));
   poly_print(r, poly_mult_fast(p16, 2, p17, 2, r)); 

   return EXIT_SUCCESS;
}
