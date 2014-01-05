#ifndef UTILITIES_LDL_INTERNAL_LDL_H
#define UTILITIES_LDL_INTERNAL_LDL_H

#include "../../NewTypes/Array.h"

/* ========================================================================== */
/* === ldl.h:  include file for the LDL package ============================= */
/* ========================================================================== */

/* LDL Copyright (c) Timothy A Davis,
 * University of Florida.  All Rights Reserved.  See README for the License.
 */

/* ========================================================================== */
/* === LDL version ========================================================== */
/* ========================================================================== */

//#define LDL_DATE "Jan 25, 2011"
//#define LDL_VERSION_CODE(main,sub) ((main) * 1000 + (sub))
//#define LDL_MAIN_VERSION 2
//#define LDL_SUB_VERSION 0
//#define LDL_SUBSUB_VERSION 3
//#define LDL_VERSION LDL_VERSION_CODE(LDL_MAIN_VERSION,LDL_SUB_VERSION)

// Adapted by Michele Moarara for the package glmmGS - December 4, 2011

namespace Utilities
{
	namespace LDL
	{
		namespace Internal
		{
			using namespace Utilities::NewTypes;

			void LDL_symbolic(int n,
					const Array<int> Ap,
					const Array<int> Ai,
					Array<int> Lp,
					Array<int> Parent,
					Array<int> Lnz,
					Array<int> Flag,
					const Array<int> P,
					Array<int> Pinv);

			int LDL_numeric(int n,
					const Array<int> Ap,
					const Array<int> Ai,
					const Array<double> Ax,
					const Array<int> Lp,
					const Array<int> Parent,
					Array<int> Lnz,
					Array<int> Li,
					Array<double> Lx,
					Array<double> D,
					Array<double> Y,
					Array<int> Pattern,
					Array<int> Flag,
					const Array<int> P,
					const Array<int> Pinv);

			void LDL_lsolve(int n,
					Array<double> X,
					const Array<int> Lp,
					const Array<int> Li,
					const Array<double> Lx);

			void LDL_dsolve(int n,
					Array<double> X,
					const Array<double> D);

			void LDL_ltsolve(int n,
					Array<double> X,
					const Array<int> Lp,
					const Array<int> Li,
					const Array<double> Lx);

			void LDL_perm(int n,
					Array<double> X,
					const Array<double> B,
					const Array<int> P);

			void LDL_permt(int n,
					Array<double> X,
					const Array<double> B,
					const Array<int> P);

			int LDL_valid_perm (int n,
					const Array<int> P,
					Array<int> Flag);

			int LDL_valid_matrix (int n,
					const Array<int> Ap,
					const Array<int> Ai);
		}
	}
}

#endif
