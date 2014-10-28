/*
 * GraphD.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Christopher Mårtensson, Niklas Rosén
 */

#ifndef GRAPHD_H_
#define GRAPHD_H_

#include "GraphUtil.h"

namespace graph{



/*** GraphD ***/

/* @brief: Undirected Nonweighted Graph */
class GraphD {
public:
	typedef vector<uint> EdgeList;
protected:
	uint N;
	vector<EdgeList> edges;
public:
	GraphD (uint n) : N(n), edges(n) {}
	void reset(uint n);
	/* Add edge from u to v */
	void addEdge(uint u, uint v) {edges[u].push_back(v);}
	/* @return: Begin Iterator for edges going from node u */
	EdgeList::const_iterator begin(uint u) const {return edges[u].begin();}
	/* @return: Beyond-end Iterator for edges going from node u */
	EdgeList::const_iterator end(uint u) const {return edges[u].end();}
	template<typename OutIter>
	OutIter getEulerianWalk(OutIter out);
private:
	template<typename OutIter>
	void find_path(uint u, uint* stk_heads, OutIter& out) const;
};


/* Reset a Graph to another size to save unnecessary reallocation ;) */
void GraphD::reset(uint n){
	N = n;
	edges.resize(n);
	for (uint i = 0; i < n; ++i)
		edges[i].clear();
}

/* private utility function for recursion in the Heirholzer alg. */
template<typename OutIter>
void GraphD::find_path(uint u, uint* stk_heads, OutIter& out) const {
	//Heirholzer's algorithm
	while(stk_heads[u] > 0){
		--stk_heads[u];
		uint v = edges[u][stk_heads[u]];
		this->find_path(v, stk_heads, out);
	}
	*out = u; ++out;
	return;
}

/* @output: If there is an Eulerian walk, output is path from END to START,
 * if there does not exist one, output is a partial walk. It is up to the caller
 * to confirm the number of edges traversed.
 * @param: out - output iterator to which the result is written
 * @return: Beyond-end iterator to output range
 * Implemented using Hierholzer's algorithm */
template<typename OutIter>
OutIter GraphD::getEulerianWalk(OutIter out){
	vector<uint> numIn(N,0); /* check for number of edges going out */
	vector<uint> stk_heads(N); /* an array of "head indexes" to keep track of used edges without copying the entire edge list */
	for (int i = 0; i < N; ++i)
		stk_heads[i] = edges[i].size();
	int start = -1;
	int end = -1;
	//count edges going in
	for (uint u = 0; u < N; ++u)
		for (auto it = this->begin(u); it != this->end(u); ++it)
			++numIn[*it];
	for (uint u = 0; u < N; ++u){
		//too many or too few edges out
		if (edges[u].size() > numIn[u]) {
			if (start != -1) return out;
			start = u;
		}
		else if (edges[u].size() < numIn[u]){
			if (end != -1) return out;
			end = u;
		}
		else if (edges[u].size() != numIn[u])
			return out;
	}
	if( !(start==-1 && end==-1) && (start == -1 || end == -1) ) return out;
	if (start == -1) start = 0;
	//even and uneven edges fine, do algorithm
	this->find_path(start,stk_heads.data(),out);
	return out;
}



} //namespace graph


#endif /* GRAPHD_H_ */
