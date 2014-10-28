/*
 * GraphWD.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Christopher Mårtensson, Niklas Rosén
 */

#ifndef GRAPHWD_H_
#define GRAPHWD_H_

#include "GraphUtil.h"
#include "PathMatrix.h"
#include "PathVector.h"

namespace graph {

/*** GraphWD ***/

/* @brief: Weighted Directed Graph allowing positive and negative edge weights
 * @notes: If only positive edges are used, consider using GraphWDP for speed */
class GraphWD {
public:
	typedef pair<uint,int> EdgePair; // first: destination node  second: edge weight
	typedef vector<EdgePair> EdgeList;
protected:
	uint N;
	vector<EdgeList> edges;
public:
	GraphWD(uint n) : N(n), edges(n) {}
	void reset(uint n);
	/* Add edge from u to v with weight w */
	void addEdge(uint u, uint v, int w) {edges[u].push_back(EdgePair(v,w));}
	/* @return: Begin Iterator for edges going from node u */
	EdgeList::const_iterator begin(uint u) const {return edges[u].begin();}
	/* @return: Beyond-end Iterator for edges going from node u */
	EdgeList::const_iterator end(uint u) const {return edges[u].end();}
	void getShortestDistance(PathMatrix& P) const;
	void getShortestDistance(uint s, PathVector& P) const;
};




/* Reset a Graph to another size to save unnecessary reallocation ;) */
void GraphWD::reset(uint n) {
	edges.resize(n);
	N = n;
	for (uint i = 0; i < n; ++i)
		edges[i].clear();
}

/* Updates the passed PathVector object to contain the shortest paths between s and all other nodes.
 * If no path exists, the distance is graph::inf, if an infinitely short path exists, the distance is graph::neginf
 * @param: s - source node
 * @param: P - Path object to contain the result
 * @notes: Implemented using Bellman-Ford's algorithm */
void GraphWD::getShortestDistance(uint s, PathVector& P) const {
	auto& dist = P.dist;
	auto& prev = P.prev;
	P.u = s;
	dist.assign(N,inf);
	prev.assign(N,-1);
	dist[s] = 0;
	uint v;
	int w;
	bool endEarly; /* for optimization */
	//go through graph N times and update distances
	for (uint i = 0; i < N; ++i) {
		endEarly = true;
		for (uint u = 0; u < N; ++u){
			if (dist[u] == inf) continue;
			for (auto e = begin(u); e != end(u); ++e) {
				v = e->first;
				w = e->second;
				if (dist[u] + w < dist[v]) {
					endEarly = false;
					dist[v] = dist[u] + w;
					prev[v] = u;
				}
			}
		}
		if (endEarly) return; /* If no change happened, we are done */
	}
	//one more iteration to check for infinite cycles
	for (uint u = 0; u < N; ++u){
		if (dist[u] == inf) continue;
		for (auto e = begin(u); e != end(u); ++e) {
			v = e->first;
			w = e->second;
			if (dist[u] == neginf || dist[u] + w < dist[v]) {
				dist[u] = neginf;
				dist[v] = neginf;
			}
		}
	}

}

/* @brief: Updates the passed PathMatrix object to contain shortest distance between all pairs of nodes.
 * If a infinitely short path exists, the distance is graph::neginf.
 * If no path exists, the distance is graph::inf
 * @notes: Implemented using the Floyd-Warshall algorithm */
void GraphWD::getShortestDistance(PathMatrix& P) const {
	auto& dist = P.dist;
	auto& prev = P.prev;
	dist.resize(N); prev.resize(N);
	//initialize DP matrix with weights
	for (uint u = 0; u < N; ++u) {
		dist[u].assign(N,inf);
		prev[u].assign(N,-1);
		for (auto edge = begin(u); edge != end(u); ++edge){
			uint v = edge->first;
			//In case of parallel edges
			if (edge->second < dist[u][v]) {
				dist[u][v] = edge->second;
				prev[u][v] = u;
			}
		}
		//In case of positive self-loops
		if (dist[u][u] > 0){
			dist[u][u] = 0;
			prev[u][u] = -1;
		}
	}
	//DP
	for (uint k = 0; k < N; ++k) {
		for (uint i = 0; i < N; ++i) {
			if (dist[i][k] == inf) continue; //optimization
			for (uint j = 0; j < N; ++j) {
				if (dist[k][j] == inf) continue;
				//there is a path between ik and kj, now to check if there is a negative loop there
				if (dist[k][k] < 0 || dist[k][j] == neginf || dist[i][k] == neginf)
					dist[i][j] = neginf;
				else {
					//if not, check if path ik+kj is smaller than the current path
					int newDist = dist[i][k] + dist[k][j];
					if (newDist < dist[i][j]){
						dist[i][j] = newDist;
						prev[i][j] = prev[k][j];
					}
				}
			}
		}
	}
}



} //namespace graph

#endif /* GRAPHWD_H_ */
