#include<iostream>

// These functions are found below.
void AllocateMemoryUnknown ();
double UnknownComp(int, int);
double prob_of_green(int, int);

// Global variables.
double **W;
int    **J;
int    r, g;
double poss_green;
double marbles, m;
double Vdont, Vstop;

#include "Functions.h"

int main() {
  m = GetInteger("Number of marbles: ");
  marbles = m+1;
  poss_green = 2*marbles;
  AllocateMemoryUnknown();
  double value = UnknownComp(0,0);
  printf ("The value of the simple game is %10.6f\n", value);
  Pause ();
}

double prob_of_green(int period, int green){
  double a = (period+green)/2;
  double num = a+1;
  double denom = period+2;
  double p = num/denom;

  return p;
}

double UnknownComp(int period, int green){
  g = (period+green)/2;
  r = (period-g);

  // Already calculated the value of this urn?
  if (J[period][g]) {
     return W[period][g];
  }
  // If not, boundary?
  else if (period == marbles-2) {
    double p = prob_of_green(period, green);
    double EV = 1*p + (-1)*(1-p);
    if(EV<0){
      W[period][g] = 0;
    }
    else{
      W[period][g] = EV;
    }
  }
    // Otherwise use recursion.
  else{
    // Expected value of playing one more time?
    double p = prob_of_green(period, green);
    Vstop = p * (1) + (1-p) * (-1);
    Vdont = p * (1 + UnknownComp (period+1, green+1)) + (1-p) * (-1 + UnknownComp (period+1, green-1));
    if(Vstop<0){Vstop=0;}
    if(Vstop>Vdont){
      W[period][g] = Vstop;
    }
    else{W[period][g]= Vdont;}
  }
  J[period][g] = 1;
  return W[period][g];
}

void AllocateMemoryUnknown () {

   int n, j;

   // Allocate space for the valuation array.
   W = (double **) calloc (marbles+1, sizeof (double *));
   for (n = 0; n <= marbles; n++) {
      W[n] = (double *) calloc (poss_green+1, sizeof (double));
    }
    J = (int **) calloc (marbles+1, sizeof (int *));
    for (n = 0; n <= marbles; n++) {
       J[n] = (int *) calloc (poss_green+1, sizeof (int));
    }
    return;
 }
