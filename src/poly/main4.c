#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define SIZE 20
void poly_print (const double  p [], const int  m){
    assert(m > 0);
    printf("%.0f",p [0]);
    for(int i = 1; i < m+1; i++){
         double temp=p[i];
         if(i <= (m)){
            char operation='+';
            if(p[i] < 0){
               temp=temp*(-1);
               operation='-';
            }
            if(temp==0){
               printf("%s", "");
            }else if (temp==1){
               printf(" %c ",operation);
            }else {
               printf(" %c %.0f*",operation,temp);
            }
            if(i>0 && temp!=0){
               
               printf("x");
               if(i>1){
                  printf("^%d",i);
               }
            }
         }         
    }  
    printf("\n");
}
double poly_evaluate (const double  p [], const int  m, const double  x){
   assert(m > 0);
   double polyValue=p[0];
   
   for(int i = 1; i < m+1; i++){
      
      polyValue=polyValue+p[i]*pow(x,i);
      
   }
   return polyValue;
}
int poly_add (const double  p [], int const m, const double  q [], const int  n,  double r []){
   assert(m > 0 && n > 0);
   int highestPolyDeg= (m > n) ? m : n;

   for(int i = 0; i < highestPolyDeg+1; i++){
      
      r [i]=p [i]+q [i];
      
   }
   
   return highestPolyDeg;
}

int poly_mult (const double  p [], int const m, const double  q [], const int  n,  double r []){
   assert(m > 0 && n > 0);

   
   int highestPolyDeg= m + n ;
   assert(highestPolyDeg < SIZE);
     
   for(int i = 0; i < m+1; i++){
      for(int j = 0; j < n+1; j++){
         r[i + j]=r[i + j] + p[i] * q[j];
         
      }
   }
   
   return highestPolyDeg;
}
int isPowerOfTwo(int number) {
    if (number <= 0) {
        return 0; // Nicht negativ oder null kann keine Zweierpotenz sein
    }

    return (number & (number - 1)) == 0;
}

int poly_mult_fast (const double  p [], int const m, const double  q [], const int  n,  double r []){
   assert(m > 0 && n==m);
   assert(isPowerOfTwo(m+1));

   if (m == 1) {
        int m2 = poly_mult(p,m,q,m,r);
        return m;
    }
   int highestPolyDeg= m;

   //init var
   int halfPoly=m/2;
   

   //init p and q halves 
   double pL[halfPoly],pR[halfPoly], qL[halfPoly], qR[halfPoly];
   double hL[m],hR[m], hM[m];
   double hLtemp1[halfPoly],hLtemp2[halfPoly];
   for(int i = 0; i <= halfPoly; i++){
      pL[i]=pR[i]=qL[i]=qR[i]=hLtemp1[i]=hLtemp1[i]=0;
      
   }
   //init the rest
   for(int i = 0; i <= m; i++){
      hL[i]=hR[i]=hM[i]=0;
      
   }

   for (int i = 0; i <= halfPoly; i++) {
      pL[i] = p[i];
      pR[i] = p[i + halfPoly+1];
      qL[i] = q[i];
      qR[i] = q[i + halfPoly+1];
   }
   
   highestPolyDeg+= poly_mult_fast (pL, halfPoly, qL, halfPoly, hL);
   highestPolyDeg+= poly_mult_fast (pR, halfPoly, qR, halfPoly, hR);
   
   int polytemp=poly_add (pL, halfPoly, pR, halfPoly, hLtemp1);
   polytemp=poly_add (qL, halfPoly, qR, halfPoly, hLtemp2);

   highestPolyDeg+= poly_mult_fast (hLtemp1, halfPoly, hLtemp2, halfPoly, hM);
   for (int i = 0; i <= m; i++) {
      r[i] += hL[i];
   }

   for (int i = 0; i < n; i++) {
      r[i + (m/2)+1] += hM[i] - hL[i] - hR[i];
   }
   for (int i = 0; i <= m; i++) {
      r[i + m + 1] += hR[i];
   }
   
   
   poly_print(hL,m);
   
   poly_print(r,highestPolyDeg);
   return highestPolyDeg;
   
}


int main () {
   printf ("Assignment not completely implemented yet.\n"); 
   int m=3;
   int n=3;
   //double arr[SIZE]={1, 1};
   //double arr2[SIZE]={1, 2};
   double arr[SIZE]={1, 1, 3, -4};
   double arr2[SIZE]={1, 2, -5, -3};
   /*poly_print(arr,m);
   double polyValue=poly_evaluate (arr, m, 1.5);
   printf("polyValue: %f\n",polyValue);
   double tempArr[]={0};
   int addPolyDeg=poly_add (arr, m, arr, m, tempArr);
   printf("polyValue: %d\n",addPolyDeg);
   */
   double r[SIZE];
   int mulPolyDeg=poly_mult_fast (arr, m, arr2, n, r);
   poly_print(r,mulPolyDeg);
   printf("polyValue: %d\n",mulPolyDeg);
   return EXIT_SUCCESS;
}
