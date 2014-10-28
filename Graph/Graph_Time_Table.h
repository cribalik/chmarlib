/*
 * Graph_Time_Table.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Christopher Mårtensson, Niklas Rosén
 */

#ifndef GRAPH_TIME_TABLE_H_
#define GRAPH_TIME_TABLE_H_
#include "GraphUtil.h"
#include "PathVector.h"

namespace graph{


/*** Graph_Time_Table ***/

/* @brief: A Graph for the time table problem. Each edge has values
 * t0, P and d, where an edge can only be traversed during times
 * t0 + P*t and it takes time d to traverse the edge. */
class Graph_Time_Table {
public:
	struct Edge {
		uint v, t0, P, d;
	};
	typedef vector<Edge> EdgeList;
protected:
	uint N;
	vector<EdgeList> edges;
public:
	Graph_Time_Table(uint n) : N(n), edges(n) {}
	void reset(uint n);
	/* Add an edge between u and v with starting time t0, period P and traversal time d */
	void addEdge(uint u, uint v, uint t0, uint P, uint d) {edges[u].push_back({v,t0,P,d});}
	/* Begin Iterator to edges going from node u */
	EdgeList::const_iterator begin(uint u) const {return edges[u].begin();}
	/* Beyond-end Iterator to edges going from node u */
	EdgeList::const_iterator end(uint u) const {return edges[u].end();}
	void getShortestTime(uint s, PathVector& result) const;
};




/* Reset a Graph to another size to save unnecessary reallocation ;) */
void Graph_Time_Table::reset(uint n) {
	edges.resize(n);
	N = n;
	for (uint i = 0; i < n; ++i)
		edges[i].clear();
}

/* @brief: Updates the passed PathVector object to contain the shortest time needed to
 * travel between source node s and all other nodes.
 * If no path exists, the distance returned is graph::inf.
 * @param: s - source node
 * @param: result - Path object to hold the time needed to reach each node and the
 * best path */
void Graph_Time_Table::getShortestTime(uint s, PathVector& result) const {
	typedef pair<uint,int> pii;
	result.u = s;
	auto& dist = result.dist;
	auto& prev = result.prev;
	dist.assign(N,inf);
	prev.assign(N,-1);
	auto comp = [](pii a, pii b) {
		return a.second > b.second;
	};
	//Priority queue to get the node with next smallest time we can traverse edge
	//Priority queues don't support updating of values, so we use a visited array
	//and just add new nodes into the queue instead of updating.
	priority_queue<pii,vector<pii>,decltype(comp)> q(comp);
	uint u,v;
	int t,d,t0,P;
	vector<bool> visited(N,false);
	dist[s] = 0;
	q.push({s,0});
	while (!q.empty()){
		u = q.top().first;
		t = q.top().second;
		q.pop();
		if (visited[u]) continue;
		visited[u] = true;
		for (auto edge = begin(u); edge != end(u); ++edge){
			P = edge->P; t0 = edge->t0; d = edge->d; v = edge->v;
			int newT;
			if (t0 >= t)
				newT = t0; //we can travel as soon as edge opens
			else if (P != 0){
				newT = P - ((t-t0)%P); newT = t + newT - (newT/P)*P; //a strange way to calculate next occasion we can travel
			}
			else //P is 0 and t > t0, we can never travel to v
				continue;
			newT += d; //takes d time to travel
			if (newT < dist[v]){
				dist[v] = newT;
				q.push({v,newT});
				prev[v] = u;
			}
		}
	}
}



} //namespace graph

#endif /* GRAPH_TIME_TABLE_H_ */
