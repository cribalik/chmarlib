/*
 * KMP.h
 *
 *  Created on: Feb 12, 2014
 *      Author: christopher
 *
 */

#ifndef KMP_H_
#define KMP_H_

#include <vector>
#include <cstring>
using std::vector;
typedef long int_type;

/* @summary: Knuth-Morris-Pratt algorithm
* @templ-param PSIZE max size of pattern (to prevent reallocation for multiple calls )
* @param pb: iterator to beginning of pattern
* @param te: iterator to end of pattern
* @param tb: iterator to beginning of text
* @param te: iterator to end of text
*/
template<size_t PSIZE, typename InputIterator, typename OutputIterator>
void KMP(const InputIterator pb, const InputIterator pe, const InputIterator tb, const InputIterator te, OutputIterator out){
	static int_type T[PSIZE+1];
	const auto psize = pe-pb;
	const auto tsize = te-tb;
	memset(T,-1,(psize+1)*sizeof(int_type));

		for(int_type i = 1; i <= psize; i++)
		{
			int_type pos = T[i - 1];
			while(pos != -1 && pb[pos] != pb[i - 1]) pos = T[pos];
			T[i] = pos + 1;
		}
		int sp = 0;
		int kp = 0;
		while(sp < tsize)
		{
			while(kp != -1 && (kp == psize || pb[kp] != tb[sp])) kp = T[kp];
			kp++;
			sp++;
			if(kp == psize) *out++ = sp-psize;//matches.push_back(sp - psize);
		}
}

#endif /* KMP_H_ */
