/*
 * modular.h
 *
 *  Created on: Apr 6, 2014
 *      Author: Christopher Mårtensson
 *
 *	Classes:
 *		Modular - A number type that defines arithmetic operations under moduli
 *
 */

#ifndef MODULAR_H_
#define MODULAR_H_
//#ifndef DEBUG
//#define DEBUG
//#endif


#include <utility>
#include <tuple>
#ifdef DEBUG
#include <cstdio>
#include <assert.h>
#endif

/* @summary: A class that holds a number (i) of type T where all arithmetic operations 
 *      (op) with i and another number (j) are defined as i op j (mod n) where n is given 
 *      as a parameter in the constructor */
template<typename T>
class Modular {
    typedef std::tuple<T,T,T> ttt;
	T n, val;
public:
    /* @param _n: same as n in the class description
     * @param value: same as i in the class description*/ 
	explicit Modular (const T& _n, const T& value = T()) : n(_n), val(value) {}
	Modular (const Modular& m) : n(m.n), val(m.val) {}
	T getValue(){return val;}
	void setValue(T t){val = t;}
	Modular& operator=(const Modular& m) {val = m.val; n = m.n; return *this;}
	Modular& operator=(const T& t) {val = t; return *this;}
	Modular& operator+=(const T& t);
	Modular& operator-=(const T& t);
	Modular& operator*=(const T& t);
	Modular& operator/=(const T& t);
	Modular& pow(const T& t);
	Modular operator+(const T& t);
	Modular operator-(const T& t);
	Modular operator*(const T& t);
	Modular operator/(const T& t);
	Modular& operator+=(const Modular& m){ *this+=m.val; return *this;}
	Modular& operator-=(const Modular& m){ *this-=m.val; return *this;}
	Modular& operator*=(const Modular& m){ *this*=m.val; return *this;}
	Modular& operator/=(const Modular& m){ *this/=m.val; return *this;}
	Modular operator+(const Modular& t){ Modular tmp(*this); tmp += t.val; return tmp;}
	Modular operator-(const Modular& t){ Modular tmp(*this); tmp -= t.val; return tmp;}
	Modular operator*(const Modular& t){ Modular tmp(*this); tmp *= t.val; return tmp;}
	Modular operator/(const Modular& t){ Modular tmp(*this); tmp /= t.val; return tmp;}
	bool operator==(const T& m);
	bool operator!=(const T& m);
	//operator T() {return val;}
private:
	ttt extGCD(T a, T b);
	T modMult(T a, T b);
};

template<typename T>
Modular<T>& Modular<T>::operator+=(const T& t){
		val = (val+t)%n;
		return *this;
}

template<typename T>
Modular<T>& Modular<T>::operator-=(const T& t) {
	val = (n+val-t)%n;
	return *this;
}
template<typename T>
Modular<T>& Modular<T>::operator*=(const T& t) {
	val = modMult(val,t);
	return *this;
}

template<typename T>
Modular<T>& Modular<T>::operator/=(const T& t) {
	T d,x,y;
	std::tie(d,x,y) = extGCD(t,n);
	if (d != 1)
		val = -1;
	else
		val = modMult(val,(x+n)%n);
	return *this;
}

template<typename T>
Modular<T>& Modular<T>::pow(const T& t){
	T e = t;
	T r = 1;
	while (e){
		if (e&1) {r = modMult(r,val);}
		e >>= 1;
		val = modMult(val,val);
	}
	val = r;
	return *this;
}

template<typename T>
Modular<T> Modular<T>::operator+(const T& t){
	Modular<T> tmp(*this);
	tmp+=t;
	return tmp;
}

template<typename T>
Modular<T> Modular<T>::operator-(const T& t){
	Modular tmp(*this);
	tmp-=t;
	return tmp;
}

template<typename T>
Modular<T> Modular<T>::operator*(const T& t){
	Modular tmp(*this);
	tmp*=t;
	return tmp;
}

template<typename T>
Modular<T> Modular<T>::operator/(const T& t){
	Modular tmp(*this);
	tmp/=t;
	return tmp;
}

template<typename T>
auto Modular<T>::extGCD(T a, T b) -> Modular<T>::ttt {
	if (b == 0)
		return ttt(a,1,0);
	else {
		T d,x,y;
		std::tie(d,x,y) = extGCD(b,(a+b)%b);
		return std::make_tuple(d,y,x-(a/b)*y);
	}
}

template<typename T>
T Modular<T>::modMult(T a, T b){
	T r = T();
	while (b != 0){
		if (b&1)
			r = (r+a)%n;
		a = (a<<1)%n;
		b >>= 1;
	}
	return r;
}

template<typename T>
bool Modular<T>::operator==(const T& m){
	return val == m;
}

template<typename T>
bool Modular<T>::operator!=(const T& m){
	return !(*this == m);
}


#ifdef DEBUG
    // Test function to test functionality of the Modular class
	static void test(){
		Modular<int> a(13,10);
		a += 10;
		assert(a == 7);
		a /= 9;
		assert(a == 8);
		a -= 8;
		assert(a == 0);
		a -= 9;
		assert(a == 4);
		a += 5;
		assert(a == 9);
		a *= 3;
		printf("%i\n",a.getValue());
		assert(a.getValue() == 1);
		Modular<int> c(a);
		assert(c == 1);
		printf("a: %i c: %i\n",int(a),int(c));
		assert((c+=12) == 0);
		assert(c == 0);
		assert(a == 1);
		printf("a-c: %i\n",int(a-c));
		assert(a-c == 1);
		assert(c+4 == 4);
		c+=4;
		assert(c == 4);
		assert(c-4-5+2 == 10);
		Modular<int> b(1000,1);
		b /= 999;
		assert(b.getValue() == 999);
		b.setValue(1);
		b /= 998;
		assert(b.getValue() == -1);
	}

#endif

#endif /* MODULAR_H_ */
