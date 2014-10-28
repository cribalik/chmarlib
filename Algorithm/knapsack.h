/*
 * knapsack.h
 *
 *  Created on: Feb 9, 2014
 *      Author: Christopher Mårtensson
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_
#include <cstdio>
#include <cstring>
typedef unsigned int uint;

template<typename T>
T max(const T& a, const T& b) {
	return a > b ? a : b;
}
/* @summary: solves the knapsack problem, items' values and weights will be accessed by .value and .weight
 * @tparam Wlimit - The maximum limit of the capacity (if knapsack will be called several times, this saves reallocation)
 * @tparam Ilimit - The maximum limit of the number of items (if knapsack will be called several times, this saves reallocation)
 * @param: begin - the beginning of range of items, value and weight accessed by .value and .weight
 * @param: end - beyond-end of range of items
 * @param: out - output iterator which to write the result
 * @param: capacity - capacity of the knapsack (integer), defaults to the template parameter
 * @return: the beyond-end iterator of the output
 */
template<size_t WLimit, size_t ILimit, typename InputIterator,
		typename OutputIterator>
OutputIterator knapsack(InputIterator begin, InputIterator end, OutputIterator out,
		uint capacity = WLimit) {
	static uint mem[ILimit + 1][WLimit + 1];
	const uint W = capacity + 1;
	InputIterator item;
	uint i;
	memset(mem[0],0,W*sizeof(uint));
	// build matrix
	for (item = begin, i = 1; item != end; ++item, ++i) {
		uint vi = item->value;
		uint wi = item->weight;
		memcpy((void*)mem[i],(void*)mem[i-1],wi*sizeof(uint));
		for (uint w = wi; w < W; ++w)
			mem[i][w] = max(mem[i - 1][w], vi + mem[i - 1][w - wi]);
	}
#ifdef DEBUG
	uint j = 0;
	for(item=--begin; item!=end; ++item, ++j) {
		for (uint w=0; w<W; ++w)
			printf("%u ",mem[j][w]);
		printf("\n");
	}
#endif
	// backtrack to find solution
	uint w = W - 1;
	for (--item, --i; i>0; --item, --i) {
		uint wi = item->weight;
		if (mem[i - 1][w] != mem[i][w]) {
			*out++ = i - 1;
			w -= wi;
		}
	}
	return out;
}

#endif /* KNAPSACK_H_ */
