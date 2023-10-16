#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void print_sign(int num) {
   if (num >= 0){
      printf(" + ");
   } else {
      printf(" - ");
   }
}
void print_coefficient(int num) {
   if (num != 1) {
      printf("%d", abs(num));
   }
}
void print_potency(int num) {
   if (/* condition */)
   {
      /* code */
   }
   
   printf("*x^%d", num);
}

void poly_print (double const p [], int const m) {
   assert(m >= 0);

   printf("%d", (int)p[0]);
   for (int i = 1; i < m+1; i++) {
      if (p[i] != 0) { // only show non-zero terms
         int num = (int)p[i];
         print_sign(num);
         print_coefficient(num);
         print_potency(num);
      }
   }
   
}

int main () {
   double p[10] = {4, 3, -2, 1,};
   poly_print(p, 3);

   return EXIT_SUCCESS;
}
