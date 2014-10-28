/*
 * primesieve.h
 *
 *      Author: Christopher Mårtensson
 *
 *	Classes: PrimeSieve - Computes the primality of all numbers up to a given number n in O(n*loglog(n)) and answers queries in O(1).
 *
 *	Function: isPrime - Determines wether a number is prime in O(n^(1/2)) time
 *
 */

#ifndef PRIME_H_
#define PRIME_H_

#include <cstring>
#include <cstdio>
#include <cmath>

/* @summary: A prime sieve that takes a number n in the constructor and answers queries about whether a
        number i is prime for 0 < i <= n, in constant time */
class PrimeSieve {
	typedef unsigned int size_t;
	bool* sieve;
	size_t num;
public:
    /* param _n: The maximum number for which primes will be calculated, see n in the class description */
	PrimeSieve (size_t n) {
		size_t len = (n+1)/2;
		num = len;
		sieve = new bool[len];
		memset(sieve, 0, len*sizeof(bool));
		sieve[0] = true;
		size_t lim = (sqrt(n)/2) + 1;
		for (size_t i = 1; i <= lim; ++i)
		{
			if (!sieve[i]){
				size_t step = (i<<1) + 1;
				for (size_t j = (i<<1)*(i+1); j < len; j += step){
					num -= 1 ^ sieve[j];
					sieve[j] = 1;
				}
			}
#ifdef DEBUG
			for (size_t k = 1; k < len; ++k)
				printf("%i ",sieve[k]);
			putchar('\n');
#endif
		}
	}
	~PrimeSieve () {delete [] sieve;}
    /* @summary: returns the maximum number for which primes are calculated */
	size_t getNum () { return num; }
    /* @summary: returns true if i is prime, false if not */
	bool isPrime(size_t i){
		
		if (i == 2)
			return true;
		else if (i&1) //check if uneven
			return !sieve[i>>1];
		else
			return false;
	}

};


/* determines wether a number is prime in O(n^(1/2)) time */
template<typename T>
bool isPrime (const T& t) {
	if (t == 2) return true;
	if (t%2 == 0) return false;
	for (int i = 3; i <= sqrt(t); i+=2)
		if (t%i == 0) return false;
	return true;
}


/* returns exponent of prime p in the prime factorization of n! */
template <typename T>
T legendre (const T& n, const T& p) {
	T r= 0;
	for (T pt = p; pt <= n; pt *= p)
		r+=n/pt;
	return r;
}

#endif