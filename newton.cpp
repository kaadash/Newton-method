#include "newton.h"
#include <cmath>
#include <iostream>
#include <QDebug>
#include <string>
using namespace std;
Newton::Newton()
{
}

Interval <long double> Newton::iabs(Interval <long double> value) {
    Interval <long double> resultValue;
    if((value.a <= 0) && (value.b >= 0)) {
        resultValue.a = 0;
        if(abs(value.a) > abs(value.b)){
            resultValue.b = abs(value.a);
        }
        else {
            resultValue.b = value.b;
        }
    }
    else {
        if(abs(value.a) < abs(value.b)) {
            resultValue.b = abs(value.b);
            resultValue.a = abs(value.a);
        }
        else {
            resultValue.b = abs(value.a);
            resultValue.a = abs(value.b);
        }
    }
    return resultValue;
}

long double Newton::normalArithmetic(long double x,
                                     fxFunctionCall f,
                                     fxFunctionCall df,
                                     int mit,
                                     long double eps,
                                     long double *fatx,
                                     int *it,
                                     int *st)
{
    float dfatx,v,w,xh;

      if (mit<1) {
          *st = 1;
      }
      else {
          *st = 3;
          *it = 0;
          do {
              *it = *it + 1;

              dfatx=df(x);

              if (dfatx==0) {
                  *st = 2;
              } else {
                  xh = x;
                  w = abs(xh);
                  x = x - f(x)/dfatx;
                  qDebug() << "x: " << (double)x;
                  v = abs(x);
                  if(v < w) {
                      v = w;
                  }
                  if(v == 0) {
                      st = 0;
                  }
                  else if(abs(x - xh) / v <= eps) {
                      st = 0;
                  }
              }
          } while(*it < mit && *st == 3);

          if(*st == 0 || *st == 3) {
              *fatx = f(x);
              return x;
          }
      }
}

Interval<long double> Newton::intervalArithmetic(Interval <long double> x,
                                         ifxFunctionCall f,
                                         ifxFunctionCall df,
                                         int mit,
                                         long double eps,
                                         Interval <long double> *fatx,
                                         int *it,
                                         int *st){
    Interval <long double> dfatx,v,w,xh;

      if (mit<1) {
          *st = 1;
      }
      else {
          *st = 3;
          *it = 0;
          do {
              *it = *it + 1;
              dfatx=df(x);
              if (dfatx.a <= 0 && dfatx.b >=0) {
                  *st = 2;
              } else {
//                  previous x
                  xh = x;
//                  absolute value of previous x
                  w = iabs(xh);
//                  x1 = x0 - fx/dfx
                  x = x - f(x)/dfatx;
//                  v is equal absolute value of new x
                  v = iabs(x);
                  if(v.b <= w.a) {
//                      v is equal absolute value of old x
                      v = w;
                  }
                      /*diff is equal to substraction of new x and old x
                              divided by absolute value of old x*/

                  if(v.a <= 0 && v.b >= 0) {
                      *st = 0;
                  }
                  else {
                      Interval<long double> diff = iabs(x - xh) / v;
                      qDebug() << "diff: " << (double)diff.a << ": " << (double)diff.b;
                      if(diff.a <= eps) {
                        *st = 0;
                      }
                  }
              }
          } while(*it < mit && *st == 3);

          if(*st == 0 || *st == 3) {
              *fatx = f(x);
              return x;
          }
      }
}
