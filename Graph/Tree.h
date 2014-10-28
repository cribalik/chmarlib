/*
 * Tree.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Christopher Mårtensson, Niklas Rosén
 */

#ifndef TREE_H_
#define TREE_H_

#include "GraphUtil.h"

namespace graph {


/*** Tree ***/

/* @brief: A class containing a spanning tree */
class Tree {
	vector<int> prev;
	int w;
	uint N;
public:
	int getWeight() {return w;}
	template<typename OutIter>
	void getPath(OutIter out) const;
	friend class GraphWU;
};


/* @brief: For each node i = [0,n-1), outputs a node that is connected to i in the spanning tree
 * (the root node is n-1)
 * @param: out - output iterator to which to write output */
template<typename OutIter>
void Tree::getPath(OutIter out) const {
	for (uint i = 0; i < N; ++i) {
		*out = prev[i]; ++out;
	}
}


} //namespace graph


#endif /* TREE_H_ */
