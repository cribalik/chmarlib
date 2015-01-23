#include <utility>

template <typename T> class xrange;
template <typename T> typename xrange<T>::iterator begin(xrange<T>& r);
template <typename T> typename xrange<T>::iterator end(xrange<T>& r);

template <typename T>
struct xrange
{
	T from, to;
	xrange(T from, T to) : from(from), to(to) {}
	xrange(T to) : from(0), to(to) {}
private:
	struct iterator {
		T val;
		iterator(T val) : val(val) {}
		iterator& operator++() {
			++val; 
			return *this;
		}
		T operator*() {
			return val;
		}
		bool operator!=(const iterator& it) {
			return val != it.val;
		}
	};
	friend xrange::iterator begin<>(xrange& r);
	friend xrange::iterator end<>(xrange& r);
};

template <typename T>
typename xrange<T>::iterator begin(xrange<T>& r) {
	return xrange<T>::iterator(r.from);
}

template <typename T>
typename xrange<T>::iterator end(xrange<T>& r) {
	return xrange<T>::iterator(r.to);
}



template <typename T> class xrevrange;
template <typename T> typename xrevrange<T>::iterator begin(xrevrange<T>& r);
template <typename T> typename xrevrange<T>::iterator end(xrevrange<T>& r);

template <typename T>
struct xrevrange
{
	T from, to;
	xrevrange(T from, T to) : from(from), to(to) {}
	xrevrange(T from) : from(from), to(0) {}
private:
	struct iterator {
		T val;
		iterator(T val) : val(val) {}
		iterator& operator++() {
			--val; 
			return *this;
		}
		T operator*() {
			return val;
		}
		bool operator!=(const iterator& it) {
			return val != it.val;
		}
		bool operator==(const iterator& it) {
			return val == it.val;
		}
	};
	friend xrevrange::iterator begin<>(xrevrange& r);
	friend xrevrange::iterator end<>(xrevrange& r);
};

template <typename T>
typename xrevrange<T>::iterator begin(xrevrange<T>& r) {
	return typename xrevrange<T>::iterator(r.from-1);
}

template <typename T>
typename xrevrange<T>::iterator end(xrevrange<T>& r) {
	return typename xrevrange<T>::iterator(r.to-1);
}



typedef xrange<int> range;
typedef xrange<std::size_t> prange;

typedef xrevrange<int> revrange;
typedef xrevrange<std::size_t> prevrange;