#ifndef GCD_H_
#define GCD_H_


#include <tuple>

/* Returns the greatest common dividor of a and b */
template<typename T>
T GCD(T a, T b){
	T c;
	while ( a != 0 ) {
		c = a; a = b%a;  b = c;
	}
	return b;
}

/* Extended GCD
 * @returns: (gcd(a,b) , x, y) where ax + by = gcd(a,b)*/
template<typename T>
std::tuple<T,T,T> extGCD(T a, T b) {
	if (b == 0)
		return std::make_tuple(a,1,0);
	else {
		T d,x,y;
		std::tie(d,x,y) = extGCD(b,(a+b)%b);
		return std::make_tuple(d,y,x-(a/b)*y);
	}
}


#endif /* GCD_H_ */