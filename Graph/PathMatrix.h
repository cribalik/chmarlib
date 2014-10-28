/*
 * PathMatrix.h
 *
 *  Created on: Mar 2, 2014
 *      Author: Christopher Mårtensson, Niklas Rosén
 */

#ifndef PATHMATRIX_H_
#define PATHMATRIX_H_

#include "GraphUtil.h"

namespace graph{

/*** PathMatrix ***/

/* @brief: Class for holding the path between any pairs of nodes */
class PathMatrix {
	vector<vector<int> > dist;
	vector<vector<int> > prev;
public:
	template<typename OutIter>
	OutIter getPath(uint u, uint v, OutIter out) const;
	int getDistance(uint u, uint v) const {return dist[u][v];}
	friend class GraphWD;
};



/* @brief: Writes nodes in shortest path between u and v starting
 * from v and ending at u (inclusive)
 * @return: beyond-end iterator of output range */
template<typename OutIter>
OutIter PathMatrix::getPath(uint u, uint v, OutIter out) const {
	//no path exists or negative cycle
	if (dist[u][v] == inf || dist[u][v] == neginf) return out;
	while (v != u){
		*out = v; ++out;
		v = prev[u][v];
	}
	*out = v; ++out;
	return out;
}



} /* namespace graph */

#endif /* PATHMATRIX_H_ */
