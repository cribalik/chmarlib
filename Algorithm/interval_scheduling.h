/*
 * interval_scheduling.h
 *
 *  Created on: Feb 12, 2014
 *      Author: christopher
 */

#ifndef INTERVAL_SCHEDULING_H_
#define INTERVAL_SCHEDULING_H_
#include <algorithm>
/* @summary: Solves the (nonweighted) interval scheduling problem. Given a set
 * of intervals, the function finds the maximum amount of intervals that do not
 * coincide, and a list of these. The intervals are assumed to be inside the given
 * interval
 * @templ-param MAXINTERVALCOUNT: The maximum size of the array of intervals (for efficiency upon repeated calls)
 * @param begin: begin iterator to the intervals
 * @param end: end iterator to the intervals
 * @param interval: the interval to schedule in the smaller intervals
 * intervals should be given as [first,second), and should be able to be accessed
 * by .first and .second
 * @param out: output iterator
 * @param sorted: flag wether or not the array of intervals is already sorted on ending time in rising order*/
template<size_t MAXINTERVALCOUNT, typename InputIterator, typename Interval, typename OutputIterator>
OutputIterator interval_scheduling(InputIterator begin, InputIterator end, Interval interval, OutputIterator out, bool sorted = false){
	typedef size_t index_t;
	static index_t indexes[MAXINTERVALCOUNT];
	auto size = end-begin;
	for (index_t i=0; i<size; ++i)
		indexes[i]=i;
	auto a = interval.first;
	index_t i=0;
	if (!sorted)
		std::sort(indexes,indexes+size,[&begin](index_t a, index_t b){
			return begin[a].second < begin[b].second;
		});
	*out++ = indexes[0];
	index_t* it = indexes;
	index_t* itend = indexes+size;
	a = begin[*it].second;
	while(it!=itend){
		while (it!=itend && begin[*it].first < a) ++it;
		if (it==itend) return out;
		*out++ = *it;
		a=begin[*it].second;
	}
	return out;
}

#endif /* INTERVAL_SCHEDULING_H_ */
