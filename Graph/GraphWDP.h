/*
 * GraphWDP.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Christopher Mårtensson, Niklas Rosén
 */

#ifndef GRAPHWDP_H_
#define GRAPHWDP_H_
#include "GraphWD.h"

namespace graph {


/*** GraphWDP ***/

/* @brief: Weighted Directed graph with nonnegative edges only
 * May be faster than parent class GraphWD */
class GraphWDP : public GraphWD {
public:
	GraphWDP(uint n) : GraphWD(n) {}
	void getShortestDistance(uint u, PathVector& P);
	using GraphWD::getShortestDistance;
};




/* Updates the passed PathVector object to contain the shortest paths between s and all other nodes.
 * If no path exists, the distance is graph::inf.
 * @param: s - source node
 * @param: P - Path object to contain the result
 * @notes: Implemented using Dijkstra's algorithm */
void GraphWDP::getShortestDistance(uint s, PathVector& result){
	typedef pair<uint,int> d_pair;
	uint u,v;
	int d;
	int w;
	result.u = s;
	auto& dist = result.dist;
	auto& prev = result.prev;
	auto comp = [](pair<uint,int> a, pair<uint,int> b) {
		return a.second > b.second;
	};
	dist.assign(N,inf);
	prev.assign(N,-1);
	//Priority queues don't support updating values, so instead we have a visited array
	//and constantly add new nodes into the queue instead
	priority_queue<d_pair,vector<d_pair>,decltype(comp)> q(comp);
	vector<bool> visited(N,false);
	dist[s] = 0;
	q.push({s,dist[s]});
	while(!q.empty()){
		u = q.top().first;
		d = q.top().second;
		q.pop();
		if (visited[u]) continue;
		visited[u] = true;
		for (auto edge = begin(u); edge != end(u); ++edge){
			v = edge->first;
			w = edge->second;
			int newDist = d + w;
			// if better, replace
			if (newDist < dist[v]){
				dist[v] = newDist;
				q.push({v,newDist});
				prev[v] = u;
			}
		}
	}
}


} //namespace graph


#endif /* GRAPHWDP_H_ */
