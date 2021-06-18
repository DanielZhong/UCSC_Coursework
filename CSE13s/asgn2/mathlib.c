#include "mathlib.h"

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#define EPSILON 1e-10
static inline double Abs(double x) {
    return x < 0 ? -x : x;
}

double POW(double x, int y) {
    if (y == 0) {
        return 1; //x^0 = 1
    }
    if (y == 1) {
        return x; //x^1 = x
    }
    if (x == 0) {
        return 0; //0^y = 0
    }

    double temp;
    temp = POW(x, y >> 1); //recursion
    double res;
    res = temp * temp;

    if (y % 2 == 0) {
        return res;
    } else { //if y is even
        return res * x;
    }
} //inspired by quick power idea

//calculate the next term in taylor series based on the k formula
double next(double a, double x, int i) {
    double result = 1;
    double denominator = (2 * i) * (2 * i + 1); //calculate new denominator
    double numerator = POW(2 * i - 1, 2) * POW(x, 2); //calculate new numerator
    result *= a; // the previous term
    result *= numerator; // the new numerator
    result /= denominator; // the new denominator
    return result;
} //ideas inspired by this answer in stackoverflow @https://stackoverflow.com/questions/20161346/approximation-of-arcsin-in-c

double arcSin(double x) {
    double temp = x;
    double sum = temp; // in taylor seris, the first term equal x.
    int idx = 0;
    double l = -1 * M_PI;
    double r = M_PI;
    double m = 0.0;

    if (Abs(x) > 0.75) { //for taylor series, it will have big difference at  [-1,-3/4] and [3/4,1]
        //inverse method
        double diff = sin(m) - x; //find sin(y)= x, so sin(y) - x should be 0
        while (
            Abs(diff) > pow(EPSILON,
                M_PI)) { //since sin is -pi and pi, and arcsin is -1 and 1, so epsilon should be the power of pi
            if (diff > 0) {
                r = m;
            } else {
                l = m;
            }
            m = (r + l) / 2;
            diff = sin(m) - x;
        } //when sin(y) - x not = 0, then inside the for loop, split the whole thing to two side, find if the mid is correct sin(y)=x, if not go to left or right side to create new mid......
        sum = m;
    } else {
        //idea inspired by this answer in stackoverflow @https://stackoverflow.com/a/20162144/12995428
        idx += 1;
        temp = next(temp, x, idx);
        while (Abs(temp) > EPSILON) {
            sum += temp; //add them
            idx += 1;
            temp = next(temp, x, idx); //save the next term
        }
    }

    return sum;
}

double arcCos(double x) {
    double a = (M_PI / 2) - arcSin(x); //same as pdf formula
    return a;
}

double Sqrt(double x) {
    double y = 1.0;
    assert(x >= 0);
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}
//cited from piazza note@143

double arcTan(double x) {
    double a = arcSin(x / (Sqrt(x * x + 1))); //same as pdf formula
    return a;
}

double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}
//cited from piazza note@69

double Log(double x) {
    double a = 1.0;
    double b = Exp(a);
    while (Abs(b - x) > EPSILON) {
        a = a + (x - b) / b;
        b = Exp(a);
    }
    return a;
}
//cited from 4/9/2021 lecture ppt
