#ifndef NEWTON_H
#define NEWTON_H
#include "Interval.h"
using namespace interval_arithmetic;
typedef long double (* fxFunctionCall)(long double args);
typedef Interval<long double> (* ifxFunctionCall)(Interval<long double> args);
class Newton
{
public:
    Newton();
    float test(float x, fxFunctionCall f, fxFunctionCall df);
    long double normalArithmetic(long double x, fxFunctionCall f, fxFunctionCall df,
                           int mit,
                           long double eps,
                           long double *fatx,
                           int *it,
                           int *st);
    Interval<long double> intervalArithmetic(Interval <long double> x,
                                             ifxFunctionCall f,
                                             ifxFunctionCall df,
                                             int mit,
                                             Interval <long double> eps,
                                             Interval <long double> *fatx,
                                             int *it,
                                             int *st);
};

#endif // NEWTON_H