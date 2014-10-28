/*
 * rational.h
 *
 *      Author: Christopher Mårtensson
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_


#include <cstdio>
#include <iostream>

/* @summary: A rational number type implemented as a fraction
        * Is always represented in the lowest possible form
        * Handles negative numbers
        * Setting 0 as the denominator and operations with other 
        Rational numbers with 0 as denominator is undefined */
template <typename T>
class Rational {
	T den;
	T num;
public:
    /* @param _num: The numerator of the fraction
     * @param _den: The denominator of the fraction */
	Rational (const T& _num, const T& _den) : num(_num), den(_den) {normalize();}
	Rational& operator=(const Rational& t){
		den = t.den;
		num = t.num;
		return *this;
	}
    bool operator==(const Rational<T>& b){return num == b.num && den == b.den;}
    bool operator!=(const Rational<T>& b){return !(*this==b);}
    bool operator<(const Rational<T>& b){Rational c = *this+b; return c.num<T();}
    bool operator<=(const Rational<T>& b){return *this<b || *this==b;}
    bool operator>(const Rational<T>& b){return !(*this<=b);}
    bool operator>=(const Rational<T>& b){return !(*this<b);}
	Rational<T>& operator+=(const Rational<T>& t) {
		T gcd = GCD(den,t.den);
		den /= gcd;
		num = num*(t.den/gcd) + t.num*den;
		den *= t.den;
		normalize();
		return *this;
	}
	Rational<T>& operator-=(const Rational<T>& t) {
		T gcd = GCD(den,t.den);
		den /= gcd;
		num = num*(t.den/gcd) - t.num*den;
		den *= t.den;
		normalize();
		return *this;
	}
	Rational<T>& operator*=(const Rational<T>& t) {
		den *= t.den;
		num *= t.num;
		normalize();
		return *this;
	}
	Rational<T>& operator/=(const Rational<T>& t) {
		den *= t.num;
		num *= t.den;
		normalize();
		return *this;
	}
	Rational operator+(const Rational& t) {
		Rational tmp(*this);
		tmp += t;
		return tmp;
	}
	Rational operator-(const Rational& t){
		Rational tmp(*this);
		tmp -= t;
		return tmp;
	}
	Rational operator*(const Rational& t){
		Rational tmp(*this);
		tmp *= t;
		return tmp;
	}
	Rational operator/(const Rational& t){
		Rational tmp(*this);
		tmp /= t;
		return tmp;
	}
    /* @summary: returns the numerator */
	T getNum(){return num;}
    /* @summary: returns the denominator */
	T getDen(){return den;}
    /* @summary: print to std output */
    void print() {std::cout << num << " / " << den;}
private:
    /* calculates the greatest common dividor between a and b */
	T GCD(T a, T b){
		T c;
		while ( a != 0 ) {
			c = a; a = b%a;  b = c;
		}
		return b;
	}
    /* normalizes the fraction using GCD */
	void normalize(){
		T frac = GCD(num,den);
		num /= frac;
		den /= frac;
		if (den<0){
			num *= -1;
			den *= -1;
		}
	}
};


#endif /* RATIONAL_H_ */