/*
 * PathVector.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Christopher Mårtensson, Niklas Rosén
 */

#ifndef PATHVECTOR_H_
#define PATHVECTOR_H_
#include "GraphUtil.h"

namespace graph {


/*** PathVector ***/

/* @brief: Class for holding the path between a source node and
 * all other nodes */
class PathVector {
	uint u; /* source node */
	vector<int> dist;
	vector<int> prev;
public:
	int getDistance(uint v) const {return dist[v];}
	template<typename OutIter>
	OutIter getPath(uint v, OutIter out) const;
	uint getSource() const {return u;}
	friend class GraphWD;
	friend class GraphWDP;
	friend class Graph_Time_Table;
};


/* @brief: Writes nodes in shortest path between source node and v to out
 * starting from v and ending at source (inclusive)
 * @return: beyond-end iterator of output range */
template<typename OutIter>
OutIter PathVector::getPath(uint v, OutIter out) const {
	//no path exists or negative cycle
	if (dist[v] == inf || dist[v] == neginf) return out;
	while (v != u){
		*out = v; ++out;
		v = prev[v];
	}
	*out = v; ++out;
	return out;
}

} //namespace graph

#endif /* PATHVECTOR_H_ */
