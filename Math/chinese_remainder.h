/*
 * chinese_remainder.h
 *
 *      Author: Christopher Mårtensson
 */

#ifndef CHINESE_REMAINDER_H_
#define CHINESE_REMAINDER_H_

#include "GCD.h"
#include "modular.h"

/* @summary: uses the chinese remainder theorem to calculate x mod n*m that solves the system
 *      x = a (mod n)
 *      x = b (mod n) 
 *  where n and m are relatively prime */
template<typename T>
T chinese_remainder(const T& a, const T& n, const T& b, const T& m){
	Modular<T> x(m*n);
	Modular<T> c1(m*n);
	Modular<T> c2(m*n);
	
	c1 += (std::get<1>(extGCD(m,n))+n)%n;
	c1 *= m;
	c1 *= a;

	c2 += (std::get<1>(extGCD(n,m))+m)%m;
	c2 *= n;
	c2 *= b;

	x += c1;
	x += c2;
	return x.getValue();
}

/* @summary: uses the chinese remainder theorem to calculate x mod n*m that solves the system
 *      x = a (mod n)
 *      x = b (mod n) 
 *  where n and m are not neccecarily relatively prime.
 *
 * @returns: (x,K) - if no solution exists, x is returned as 0. Otherwise, x is the solution and K is the modulo under which x is. */
template<typename T>
std::tuple<T,T> general_chinese_remainder(T a, T n, T b, T m){
	

	T common = GCD(n,m);

	if (common == 1)
		return std::make_tuple(chinese_remainder(a,n,b,m),n*m);
	
	T K = (n/common)*m;

	if (a == b) return std::make_tuple(a,K);

	//Do the variable substitution so we get positive ap
	if (a > b){
		std::swap(a,b);
		std::swap(n,m);
	}

	T ap = b-a;
	n /= common;
	m /= common;

	if (ap%common != 0)
		return std::make_tuple(0,K);
	

	T x = chinese_remainder(T(),n,(ap/common),m);

	x *= common;
	x += a;
	return std::make_tuple(x,K);
}


#endif /* CHINESE_REMAINDER_H_ */