#include "newton.h"
#include <cmath>
#include <iostream>
#include <QDebug>
#include <string>
using namespace std;
Newton::Newton()
{
}
float Newton::test(float x, fxFunctionCall f, fxFunctionCall df) {
    return f(x) + df(x);
}

Interval<long double> iabs(Interval<long double> value) {

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
              qDebug() << "iterations: " << *it;
              qDebug() << "mit: " ;

              if (dfatx==0) {
                  *st = 2;
              } else {
                  xh = x;
                  w = abs(xh);
                  x = x - f(x)/dfatx;
                  qDebug() << "x: " << (float)x;
                  v = abs(x);
                  if(v < w) {
                      v = w;
                      if(v == 0) {
                          st = 0;
                      }
                      else if(abs(x - xh) / v <= eps) {
                          st = 0;
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

Interval<long double> Newton::intervalArithmetic(Interval <long double> x,
                                         ifxFunctionCall f,
                                         ifxFunctionCall df,
                                         int mit,
                                         Interval <long double> eps,
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
              qDebug() << "iterations: " << *it;
              qDebug() << "mit: " ;

              if (dfatx.a==0) {
                  *st = 2;
              } else {
                  xh = x;
                  w = abs(xh);
                  x = x - f(x)/dfatx;
                  qDebug() << "x: " << (float)x;
                  v = abs(x);
                  if(v < w) {
                      v = w;
                      if(v == 0) {
                          st = 0;
                      }
                      else if(abs(x - xh) / v <= eps) {
                          st = 0;
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
