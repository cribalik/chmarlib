/*
 * GraphWU.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Christopher Mårtensson, Niklas Rosén
 */

#ifndef GRAPHWU_H_
#define GRAPHWU_H_
#include "GraphUtil.h"
#include "Tree.h"

namespace graph {



/*** GraphWU ***/

/* @brief: Weighted Undirected Graph allowing positive and negative edge weights */
class GraphWU {
public:
	typedef pair<uint,int> EdgePair; // first: destination node  second: edge weight
	typedef vector<EdgePair> EdgeList;
protected:
	uint N;
	vector<EdgeList> edges;
public:
	GraphWU(uint n) : N(n), edges(n) {}
	void reset(uint n);
	/* Add edge from u to v with weight w */
	void addEdge(uint u, uint v, int w) { edges[u].push_back({v,w}); edges[v].push_back({u,w}); }
	/* @return: Begin Iterator for edges going from node u */
	EdgeList::const_iterator begin(uint u) const {return edges[u].begin();}
	/* @return: Beyond-end Iterator for edges going from node u */
	EdgeList::const_iterator end(uint u) const {return edges[u].end();}
	void getMinimumSpanningTree(Tree& T) const;
};




/* Reset a Graph to another size to save unnecessary reallocation ;) */
void GraphWU::reset(uint n){
	N = n;
	edges.resize(n);
	for (uint i = 0; i < n; ++i)
		edges[i].clear();
}

/* @brief: Updates Tree object to contain a minimum spanning tree of the graph
 * @param: T - Tree object to store the tree in
 * @notes: Implemented using Prim's algorithm */
void GraphWU::getMinimumSpanningTree(Tree& T) const {
	typedef pair<uint,int> d_pair;
	T.N = N;
	uint u,v,root=N-1;
	int w;
	auto& prev = T.prev;
	prev.assign(N,-1);
	vector<int> dist(N,inf);
	auto comp = [](d_pair a, d_pair b) {
		return a.second > b.second;
	};
	//priority queue for finding nearest uncolored node
	priority_queue<d_pair,vector<d_pair>,decltype(comp)> q(comp);
	vector<bool> colored(N,false);
	dist[root]=0;
	q.push({root,dist[root]});
	while (!q.empty()){
		//pick nearest node that is uncolored
		u = q.top().first;
		q.pop();
		if (colored[u]) continue;
		colored[u] = true; //color it
		// update uncolored neighbors
		for (auto edge = begin(u); edge != end(u); ++edge){
			v = edge->first;
			w = edge->second;
			if (colored[v]) continue;
			if (w < dist[v]){
				dist[v] = w;
				prev[v] = u;
				q.push({v,w});
			}
		}
	}
	//get total weight of tree. If some weight is inf, no path was found
	int sum = 0;
	for (uint i = 0; i < N; ++i){
		if (dist[i] == inf) {T.w = inf; return;}
		sum += dist[i];
	}
	T.w = sum;
}





} //namespace graph


#endif /* GRAPHWU_H_ */
