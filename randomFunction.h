#pragma once
#include "singletonBase.h"
#include <time.h>

class randomFunction : public singletonBase < randomFunction >
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{

	}

	//intÇü ·£´ý°ª »Ì¾Æº¾¼¼!
	inline int GetInt(int num) { return rand() % num; }
	inline int GetFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

	//floatÇü ·£´ý°ª
	float GetFloat() { return (float)rand() / (float)RAND_MAX; }
	float GetFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	float GetFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

};
