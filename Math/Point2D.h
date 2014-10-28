#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>
#include <iterator>
#include <initializer_list>
#include <cstdio>

namespace point
{

/* @summary:	A Point in 2D space, supports various operations with scalars and other points
 * @tparam:		T: The precision of point position, typically integers or floating points
 *				F: The precision for which to calculate floating point results like angles, distances, lengths etc. */
template<typename T, typename F=double>
class Point2D
{
public:
	typedef T Point_t;
	typedef F Float_t;
	T x, y;
	Point2D() : x(T()), y(T()) {}
	Point2D(const T& x, const T& y);
	Point2D(const std::initializer_list<T>& l);
	template<typename U, typename D>
	Point2D(const Point2D<U,D>& p) : x(T(p.x)), y(T(p.y)) {}
	~Point2D() {}
	Point2D& operator+=(const Point2D& p);
	Point2D& operator-=(const Point2D& p);
	Point2D& operator+=(const T& t);
	Point2D& operator-=(const T& t);
	Point2D& operator*=(const T& t);
	Point2D& operator/=(const T& t);
	Point2D operator+(const Point2D& p) const;
	Point2D operator-(const Point2D& p) const;
	Point2D operator+(const T& t) const;
	Point2D operator-(const T& t) const;
	Point2D operator*(const T& t) const;
	Point2D operator/(const T& t) const;
	bool operator==(const Point2D& p) const;
	bool operator!=(const Point2D& p) const;
	bool equals(const Point2D&p) const;
	bool equals(const Point2D&p, const F& epsilon) const;
	T dot(const Point2D& p) const;
	T cross(const Point2D& p) const;
	F dist(const Point2D& p) const;
	T distsqr(const Point2D& p) const;
	F angle(const Point2D& p) const;
	F length() const;
	F distanceToSegment(const Point2D& A,const Point2D& B) const;
};

/* Construct a Point2D with x and y values */
template<typename T, typename F>
Point2D<T,F>::Point2D(const T& x, const T& y) : x(x), y(y) {}

/* Construct a Point2D with initializer list of the form {x,y} */
template<typename T, typename F>
Point2D<T,F>::Point2D(const std::initializer_list<T>& l) {
		if(l.size() == 0) return; 
		else if (l.size() == 1) x = l.begin()[0]; 
		else {x = l.begin()[0]; y = l.begin[1];}
}

/* Vector addition */
template<typename T, typename F>
Point2D<T,F>& Point2D<T,F>::operator+=(const Point2D<T,F>& p) {
	this->x += p.x;
	this->y += p.y;
	return *this;
}

/* Vector subtraction */
template<typename T, typename F>
Point2D<T,F>& Point2D<T,F>::operator-=(const Point2D<T,F>& p) {
	this->x -= p.x;
	this->y -= p.y;
	return *this;
}

/* Addition with scalar */
template<typename T, typename F>
Point2D<T,F>& Point2D<T,F>::operator+=(const T& t) {
	this->x += t;
	this->y += t;
	return *this;
}

/* Subtraction with scalar */
template<typename T, typename F>
Point2D<T,F>& Point2D<T,F>::operator-=(const T& t) {
	this->x -= t;
	this->y -= t;
	return *this;
}

/* Multiplication with scalar */
template<typename T, typename F>
Point2D<T,F>& Point2D<T,F>::operator*=(const T& t) {
	this->x *= t;
	this->y *= t;
	return *this;
}

/* Division with scalar */
template<typename T, typename F>
Point2D<T,F>& Point2D<T,F>::operator/=(const T& t) {
	this->x /= t;
	this->y /= t;
	return *this;
}

/* Vector addition */
template<typename T, typename F>
Point2D<T,F> Point2D<T,F>::operator+(const Point2D<T,F>& p) const {
	Point2D<T,F> tmp(*this);
	tmp += p;
	return tmp;
}

/* Vector subtraction */
template<typename T, typename F>
Point2D<T,F> Point2D<T,F>::operator-(const Point2D<T,F>& p) const {
	Point2D<T,F> tmp(*this);
	tmp -= p;
	return tmp;
}

/* Addition with scalar */
template<typename T, typename F>
Point2D<T,F> Point2D<T,F>::operator+(const T& t) const {
	Point2D<T,F> tmp(*this);
	tmp += t;
	return tmp;
}

/* Subtraction with scalar */
template<typename T, typename F>
Point2D<T,F> Point2D<T,F>::operator-(const T& t) const {
	Point2D<T,F> tmp(*this);
	tmp -= t;
	return tmp;
}

/* Multiplication with scalar */
template<typename T, typename F>
Point2D<T,F> Point2D<T,F>::operator*(const T& t) const {
	Point2D<T,F> tmp(*this);
	tmp *= t;
	return tmp;
}

/* Division with scalar */
template<typename T, typename F>
Point2D<T,F> Point2D<T,F>::operator/(const T& t) const {
	Point2D<T,F> tmp(*this);
	tmp /= t;
	return tmp;
}

/* Check wether two points are equal */
template<typename T, typename F>
bool Point2D<T,F>::operator==(const Point2D<T,F>& p) const {
	return this->x == p.x && this->y == p.y;
}

/* Check wether two points are inequal */
template<typename T, typename F>
bool Point2D<T,F>::operator!=(const Point2D<T,F>& p) const {
	return !((*this) == p);
}

/* Check wether two points are equal within a distance epsilon */
template<typename T, typename F>
bool Point2D<T,F>::equals(const Point2D<T,F>&p, const F& epsilon) const {
	return this->distsqr(p) < epsilon*epsilon;
}

/* Check wether two points are equal */
template<typename T, typename F>
bool Point2D<T,F>::equals(const Point2D<T,F>&p) const {
	return (*this) == p;
}

/* Calculate dot product with given vector */
template<typename T, typename F>
T Point2D<T,F>::dot(const Point2D<T,F>& p) const {
	return this->x*p.x + this->y*p.y;
}

/* Calculate cross product with given vector */
template<typename T, typename F>
T Point2D<T,F>::cross(const Point2D<T,F>& p) const {
	return this->x*p.y - this->y*p.x;
}

/* Calculate the distance to given point */
template<typename T, typename F>
F Point2D<T,F>::dist(const Point2D<T,F>& p) const {
	T dx = p.x - this->x;
	T dy = p.y - this->y;
	F dsqr = dx*dx + dy*dy;
	return sqrt(dsqr);
}

/* Calculate the square of the distance to given point */
template<typename T, typename F>
T Point2D<T,F>::distsqr(const Point2D<T,F>& p) const {
	T dx = p.x - this->x;
	T dy = p.y - this->y;
	return dx*dx + dy*dy;
}

/* Calculate the angle to given vector */
template<typename T, typename F>
F Point2D<T,F>::angle(const Point2D<T,F>& p) const {
	F c = cross(*this,p);
	F d = dot(*this,p);
	return atan2(c,d);
}

/* Calculate length of the vector */
template<typename T, typename F>
F Point2D<T,F>::length() const {
	return sqrt(x*x + y*y);
}

/* Calculate the minimum distance from point to line segment A to B */
template<typename T, typename F>
F Point2D<T,F>::distanceToSegment(const Point2D& A,const Point2D& B) const {
	Point2D<T,F> AB(B-A);
	Point2D<T,F> Ap(*this-A);
	Point2D<T,F> Bp(*this-B);
	if (AB.dot(Ap) <= T()) {return Ap.length();}
	if (AB.dot(Bp) >= T()) {return Bp.length();}
	return abs(F(Ap.cross(AB)))/AB.length();
}

/* Calculate the dot product of two vectors */
template<typename T, typename F>
T dot(const Point2D<T,F>& p1, const Point2D<T,F>& p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

/* Calculate the cross product of two vectors */
template<typename T, typename F>
T cross(const Point2D<T,F>& p1, const Point2D<T,F>& p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

/* Calculate the distance between two points */
template<typename T, typename F>
F dist(const Point2D<T,F>& p1, const Point2D<T,F>& p2) {
	T dx = p2.x - p1.x;
	T dy = p2.y - p1.y;
	F dsqr = dx*dx + dy*dy;
	return sqrt(dsqr);
}

/* Calculate the angle between two vectors */
template<typename T, typename F>
F angle(const Point2D<T,F>& p1, const Point2D<T,F>& p2) {
	F c = cross(p1,p2);
	F d = dot(p1,p2);
	return atan2(c,d);
}

/* Calculate the square of the distance between two points */
template<typename T, typename F>
T distsqr(const Point2D<T,F>& p1, const Point2D<T,F>& p2) {
	T dx = p2.x - p1.x;
	T dy = p2.y - p1.y;
	return dx*dx + dy*dy;
}

/* Addition with scalar */
template<typename T, typename F>
Point2D<T,F> operator+(const T& t, const Point2D<T,F>& p){
	return p+t;
}

/* Negation of vector */
template<typename T, typename F>
Point2D<T,F> operator-(const Point2D<T,F>& p){
	return Point2D<T,F>(-p.x,-p.y);
}

/* Negation and addition with scalar */
template<typename T, typename F>
Point2D<T,F> operator-(const T& t, const Point2D<T,F>& p){
	return (-p)+t;
}

/* Multiplication with scalar */
template<typename T, typename F>
Point2D<T,F> operator*(const T& t, const Point2D<T,F>& p){
	return p*t;
}

/* Datatype used by the "intersection" function to return values,
 * if the intersection is a single point, the intersection field is filled,
 * otherwise if the intersection is a line segment, the segment field is filled */
template<typename T, typename F>
union Intersection
{
	Point2D<T,F> segment[2];
	Point2D<F,F> intersection;
};
/* @summary: 	Calculates wether or not two line segments intersect and the intersecting point(s)
 * @return: 	0 if lines do not intersect
 *				1 if lines intersect at one point
 *				2 if lines are parallel and intersect at multiple points
 * @param: 		A, B: endpoints of first line segment
 *				C, D: endpoints of second line segment
 *				out: an Intersection object to which the intersection point(s) will be written
 *					 if the return value is 1, the intersection field will be filled,
 *					 if the return value is 2, the segment field will be filled */
template<typename T, typename F>
int intersection(const Point2D<T,F>& A, const Point2D<T,F>& B, const Point2D<T,F>& C, const Point2D<T,F>& D, Intersection<T,F>* out){
	typedef Point2D<T,F> P;
	P AA = B-A;
	P BB = D-C;
	P CC = C-A;
	T g = BB.cross(AA);
	T ac = AA.cross(CC);
	T bc = BB.cross(CC);
	//check if segments are parallel
	if (g == T()) {
		//check if there is distance between lines
		if (ac != T() || bc != T()) return 0;
		// AB or CD may be of zero length
		if (AA.x == 0 && AA.y == 0 && BB.x == 0 && BB.y == 0) { //two points, check if equal 
			if (A == C) {out->intersection = Point2D<F,F>(A.x,A.y); return 1;}
			else return 0;
		} else if (AA.x == 0 && AA.y == 0){
		//AB is point, CD is line
			F t = BB.x == 0? -F(CC.y)/F(BB.y) : -F(CC.x)/F(BB.x);
			if (bc == 0 && 0 <= t && t <= 1) //AB is on CD
				{out->intersection = Point2D<F,F>(A.x,A.y); return 1;}
			return 0;
		} else if (BB.x == 0 && BB.y == 0){
		//CD is point, AB is line
			F t = AA.x == 0? F(CC.y)/F(AA.y) : F(CC.x)/F(AA.x);
			if (ac == 0 && 0 <= t && t <= 1) //CD is on AB
				{out->intersection = Point2D<F,F>(C.x,C.y); return 1;}
			return 0;
		}
		//segments are on a straight line
		T a,b,c,d;
		bool swapa=false, swapb=false;
		if (AA.x == T()) {
			//Vertical lines
			swapa = A.y > B.y;
			if (swapa) {a = B.y; b = A.y;}
			else {a = A.y; b = B.y;}
			swapb = C.y > D.y;
			if (swapb) {c = D.y; d = C.y;}
			else {c = C.y; d = D.y;}
		} else {
			swapa = A.x > B.x;
			if (swapa) {a = B.x; b = A.x;}
			else {a = A.x; b = B.x;}
			swapb = C.x > D.x;
			if (swapb) {c = D.x; d = C.x;}
			else {c = C.x; d = D.x;}
		}
		//a-b and c-d, c-d a-b are now ordered pairs
		if (b < c || d < a) return 0;
		Point2D<T,F> p1 = a < c ? (swapb ? D : C) : (swapa ? B : A);
		Point2D<T,F> p2 = b < d ? (swapa ? A : B) : (swapb ? C : D);
		if (p1==p2) {out->intersection = A; return 1;}
		out->segment[0] = p1;
		out->segment[1] = p2;
		return 2;
	}
	else {
		F t1 = F(bc)/F(g);
		F t2 = F(ac)/F(g);
		if (0 <= t1 && t1 <= 1 && 0 <= t2 && t2 <= 1) {
			out->intersection = Point2D<F,F>(F(A.x) + F(AA.x)*t1, F(A.y) + F(AA.y)*t1);
			return 1;
		}
		else return 0;
	}
}

/* Calculate shortest distance between a line segment and a point */
template<typename T, typename F>
F distance_point_segment(const Point2D<T,F>& A, const Point2D<T,F>& B, const Point2D<T,F>& p) {
	return p.distanceToSegment(A,B);
}

/* @summary: 	Evaluate whether a point is inside a polygon or not
 * @return: 	Returns -1 if the point is outside the polygon
 *				Returns 0 if the point is on the edge of the polygon
 *				Returns 1 if the point is inside the polygon 
 * @param:		p: The point to be evaluated
 *				begin, end: begin and end iterator to a collection of points defining the polygon, given in either clockwise or counter-clockwise order */
template<typename InputIterator, typename T, typename F>
int inside_polygon(const Point2D<T,F>& p, InputIterator begin, InputIterator end){
	static F epsilon = 0.1;
	InputIterator next = begin, prev = begin;
	++next;
	F alpha = F();
	T ux,uy,vx,vy,c,d;
	while(next != end){
		ux = prev->x-p.x;
		uy = prev->y-p.y;
		vx = next->x-p.x;
		vy = next->y-p.y;
		c = ux*vy - uy*vx;
		d = ux*vx + uy*vy;
		if (c == T() && d <= T()) return 0;
		alpha += atan2(c,d);
		++next;
		++prev;
	}
	--next;
	ux = next->x-p.x;
	uy = next->y-p.y;
	vx = begin->x-p.x;
	vy = begin->y-p.y;
	c = ux*vy - uy*vx;
	d = ux*vx + uy*vy;
	if (c == T() && d <= T()) return 0;
	alpha += atan2(c,d);
	return (abs(alpha - F()) < epsilon) ? -1 : 1;
}

/* @summary:	Evaluate the area of a polygon
 * @param:		begin, end: begin and end iterators to collection of points defining the polygon given in either clockwise or counter-clockwise order
 * 				clockwise: optional pointer to a boolean for letting the user know wether the points were given in clockwise or counter-clockwise order
 * @return:		A floating point value equal to the area of the space contained within the polygon. */
template<typename InputIterator>
typename std::iterator_traits<InputIterator>::value_type::Float_t 
	polygon_area(InputIterator begin, InputIterator end, bool* clockwise = nullptr) {
	typedef typename std::iterator_traits<InputIterator>::value_type::Float_t F;
	typedef typename std::iterator_traits<InputIterator>::value_type::Point_t T;
	T A = T();
	InputIterator prev = begin;
	InputIterator next = begin;
	++next;
	while (next!=end){
		A += next->cross(*prev);
		++prev;
		++next;
	}
	--next;
	A += begin->cross(*next);
	if (clockwise) *clockwise = A >= T();
	return A < T() ? F(-A)/F(2) : F(A)/F(2);
}

/* @summary:	Evaluate double the area of a polygon. Compared to the function polygon_area, this function will return an integer if the polygon points are given as integers
 * @param:		begin, end: begin and end iterators to collection of points defining the polygon given in either clockwise or counter-clockwise order
 * 				clockwise: optional pointer to a boolean for letting the user know wether the points were given in clockwise or counter-clockwise order
 * @return:		A value of the same precision as the given points, equal to the area of the space contained within the polygon. */
template<typename InputIterator>
typename std::iterator_traits<InputIterator>::value_type::Point_t 
	double_polygon_area(InputIterator begin, InputIterator end, bool* clockwise = nullptr) {
	typedef typename std::iterator_traits<InputIterator>::value_type::Point_t T;
	T A = T();
	InputIterator prev = begin;
	InputIterator next = begin;
	++next;
	while (next!=end){
		A += next->cross(*prev);
		++prev;
		++next;
	}
	--next;
	A += begin->cross(*next);
	if (clockwise) *clockwise = A >= T();
	return A < T() ? -A : A;
}

} /*namespace point*/

#endif /* POINT2D_H */