
#ifndef PCH_H
#define PCH_H


#include <windows.h>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <assert.h>
#include <algorithm>

using std::vector;
using std::queue;


#include "criticalsection.h"
#include "semaphore.h"
#include "task.h"
//#include "wqsemphore.h"


template <class Seq>
inline void rotatepopvector(Seq &seq, const unsigned int idx)
{
	if ((seq.size() - 1) > idx)
		std::rotate(seq.begin() + idx, seq.begin() + idx + 1, seq.end());
	seq.pop_back();
}


#endif //PCH_H
