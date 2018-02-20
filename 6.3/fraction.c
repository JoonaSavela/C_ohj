#include <stdlib.h>
#include "fraction.h"
#include <stdio.h>

/* Algorithm for determining greatest common divisor, needed in (d) */
/* The function returns gcd between the two parameters, u and v */
/* Taken from http://en.wikipedia.org/wiki/Binary_GCD_algorithm */
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;
 
    if (u == 0)
        return v;
 
    if (v == 0)
        return u;
 
    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }
 
    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);
 
    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);
 
    return gcd((v - u) >> 1, u);
}

Fraction* setFraction(unsigned int numerator, unsigned int denominator)
{
    Fraction *newfraction = malloc(sizeof(Fraction));
    
    newfraction->numerator = numerator;
    newfraction->denominator = denominator;

    return newfraction;
}

void freeFraction(Fraction* f)
{
    free(f);
}

unsigned int getNum(const Fraction *f)
{
    return f->numerator;
}

unsigned int getDenom(const Fraction *f)
{
    return f->denominator;
}

int compFraction(const Fraction *a, const Fraction *b)
{
    unsigned int t1 = getNum(a) * getDenom(b);
    unsigned int t2 = getDenom(a) * getNum(b);

    if (t1 == t2) {
        return 0;
    } else if (t1 > t2) {
        return 1;
    } else {
        return -1;
    }
}

Fraction *addFraction(const Fraction *a, const Fraction *b)
{
    unsigned int num1, num2;
    unsigned int denom = getDenom(a) * getDenom(b);
    
    num1 = getNum(a) * getDenom(b);
    num2 = getNum(b) * getDenom(a);

    return setFraction(num1 + num2, denom);
}

void reduceFraction(Fraction *val)
{
    unsigned int n = getNum(val);
    unsigned int d = getDenom(val);
    unsigned int g = gcd(n, d);

    while (g > 1) {
        n /= g;
        d /= g;
        val->numerator = n;
        val->denominator = d;
        g = gcd(n, d);
    }
}

void printFraction(const Fraction *val)
{
    printf("fraction: %u/%u\n", getNum(val), getDenom(val));
}



