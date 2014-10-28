/*
 * linear_equation.h
 *
 *      Author: Christopher Mårtensson
 */

#ifndef LINEAR_EQUATION_H_
#define LINEAR_EQUATION_H_


#include <cmath>
#include <utility>
#include "Matrix.h"
#include <limits>

namespace linear {

using matrix::Matrix;
using std::abs;

enum Result { SUCCESS, MULTIPLE, INCONSISTENT };


/* @summary: A linear equation solver, for solving linear equations of the form Ax = b,
 * where A is a known n*n matrix, b is a known vector of length n, and x is the vector to be found

 * @method solve: solves for x given b

 * @tparam Float: The floating point precision with which to solve the linear equation

 * @notes: Performs LUP decomposition, so solving several times for different b will be faster than gaussian elimination 
 */
template<typename Float = double>
class Solver {
	typedef int Int;
	typedef typename matrix::Matrix<Float> Matrix_t;
	typedef typename Matrix_t::iterator M_iterator;
	const Int n;
	Matrix_t A;
	Int* pi;
public:

	/* @param _n: Integer n indicating the dimensions of A and b
     * @param _A: Input iterator that iterates through the n*n elements of matrix A in row-wise order */
	template<typename InputIter>
	Solver (Int _n, InputIter _A) : n(_n), A(_n,_A), pi(new Int[_n]) {
		for (Int i = 0; i < n; ++i)
			pi[i] = i;
        //perform LUP decomposition
		LUP();
	}
	~Solver () { delete [] pi; }

	/* @summary: Solves the linear equation Ax=b for x given vector b, and writes x to the output iterator
	 * @param b: Input Random access iterator to the vector b of size n
	 * @param x: Output random access iterator for the result (the vector x) */
	 template <typename InputIter, typename OutputIter>
	 Result solve(InputIter b, OutputIter x){
	 	//forward
		for (Int i = 0; i < n; ++i){
			x[i] = b[pi[i]];
			M_iterator li = A.begin(i);
			for (Int j = 0; j < i; ++j)
				x[i] -= li[j]*x[j];
		}
		//backward
		for (Int i = n-1; i >= 0; --i){
			M_iterator ui = A.begin(i);
			for (Int j = i+1; j < n; ++j)
				x[i] -= ui[j]*x[j];
			if (ui[i] == 0 && x[i] != 0) return INCONSISTENT;
			if (ui[i] == 0) return MULTIPLE;
			x[i] /= ui[i];
		}
		return SUCCESS;
	 }

private:
    /* @summary: performs LUP decomposition on A, and uses A to hold L and U and P is represented in the pi array */
	void LUP(){
		Float aik, p;
		Int kp;
		for (Int k = 0; k < n; ++k)
		{
            
            //pivot
			p = 0;
			for (Int i = k; i < n; ++i){
				aik = abs(A(i,k));
				if (aik > p){
					p = aik;
					kp = i; 
				}
			}
			
            //Check if Matrix is singular
			if (p == 0){
				A(k,k) = 0;
				continue; 
			}
			
            //exchange rows
			std::swap(pi[k],pi[kp]);
			M_iterator Ak = A.begin(k), Akp = A.begin(kp);
			for (Int i = 0; i < n; ++i)
				std::swap(Ak[i],Akp[i]);

			//calculate Shur complement
			for (Int i = k+1; i < n; ++i){
				A(i,k) /= A(k,k);
				aik = A(i,k);
				M_iterator Ai = A.begin(i), Ak = A.begin(k);
				for(Int j = k+1; j < n; ++j)
					Ai[j] -= aik*Ak[j];
			}
		}
		
	}

};

} //namespace linear


#endif /* LINEAR_EQUATION */