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
	GraphWDP getShortestDistanceMulti(uint s);
};




/* Updates the passed PathVector object to contain the shortest paths between s and all other nodes.
 * If no path exists, the distance is graph::inf.
 * @param: s - source node
 * @param: P - Path object to contain the result
 * @notes: Implemented using UCS (Uniform Cost Search) */
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
	priority_queue<d_pair,vector<d_pair>,decltype(comp)> q(comp);
	dist[s] = 0;
	q.push({s,dist[s]});
	while(!q.empty()){
		u = q.top().first;
		d = q.top().second;
		q.pop();
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

/* Returns a graph of all shortest paths from node s to all other nodes
 * @param: s - source node
 * @param: P - Path object to contain the result
 * @notes: Implemented using UCS (Uniform Cost Search) */
GraphWDP GraphWDP::getShortestDistanceMulti(uint s) {
	typedef pair<uint,int> d_pair;
	uint u,v;
	int d,w;
	std::vector<uint> dist(N,inf);
	GraphWDP res(N);
	auto comp = [](pair<uint,int> a, pair<uint,int> b) {
		return a.second > b.second;
	};
	priority_queue<d_pair,vector<d_pair>,decltype(comp)> q(comp);
	dist[s] = 0;
	q.push({s,dist[s]});
	while(!q.empty()){
		u = q.top().first;
		d = q.top().second;
		q.pop();
		for (auto edge = begin(u); edge != end(u); ++edge){
			v = edge->first;
			w = edge->second;
			int newDist = d + w;
			// if better, replace
			if (newDist < dist[v]) {
				dist[v] = newDist;
				q.push({v,newDist});
				res.edges[v].clear();
				res.edges[v].push_back({u,w});
			} else if (newDist == dist[v]) {
				res.edges[v].push_back({u,w});
			}
		}
	}
	return res;
}


} //namespace graph


#endif /* GRAPHWDP_H_ */
