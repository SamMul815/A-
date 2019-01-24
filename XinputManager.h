#pragma once

#include <Xinput.h>
#pragma comment(lib, "xinput9_1_0.lib")
#include "singletonBase.h"


class CXBOXController : public singletonBase<CXBOXController>
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;
public:
	CXBOXController(int playerNumber);
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);
};