/*
 * binary_indexed_tree.h
 *
 *  Created on: Feb 12, 2014
 *      Author: christopher
 */

#ifndef BINARY_INDEXED_TREE_H_
#define BINARY_INDEXED_TREE_H_
/* @summary: An implementation of a Fenwick tree
 * @Template parameter: The type of object used in the tree
 * @constructor arg: n - the size of the data
 * @Add: Add the value t to position k
 * @Query: Get the sum of all items up to (not including) the item at position i
 */
template<typename T>
class Fenwick {
	unsigned long size;
	T* ptr;
public:
	Fenwick(unsigned long n) : size(n), ptr(new T[n+2]) {
		for (unsigned long i=0; i<=size; ++i)
			ptr[i] = T();
	}
	~Fenwick() { delete [] ptr; }
	T Query(long i){
		T r = T();
		while (i > 0){
			r+=ptr[i];
			i -= i&-i;
		}
		return r;
	}
	void Add(long i, const T& t){
		++i;
		while (i <= size){
			ptr[i] += t;
			i += i&-i;
		}
	}
};

#endif /* BINARY_INDEXED_TREE_H_ */
