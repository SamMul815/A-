#pragma once
#include <vector>

//================================
// ## animation ## 2016. 01. 07 ##
//================================

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//void* <--- ���̵������� == ���°� ���� ����ų �� �ֱ� ������
//� ���̵� �� ���� ���� �ִ�. ���� �������̶�� ĳ������ �ؼ� ����Ѵٴɰ�!

class animation
{
public:
	//�����ӿ� �������ٰ������Ϸ��� ����!!!
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

private:
	int _frameNum;

	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameWidth;
	int _frameHeight;

	BOOL _loop;

	float _frameUpdateSec;
	float _elapsedSec;

	DWORD _nowPlayIdx;
	BOOL _play;

	void* _obj;
	CALLBACK_FUNCTION _callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	animation();
	~animation();

	HRESULT Init(int totalW, int totalH, int frameW, int frameH);
	void Release(void);

	//default �ִϸ��̼�
	void SetDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void SetDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void SetDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//�迭�� ������ �ִϸ��̼�
	void SetPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void SetPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void SetPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//���۰� �� ��ȣ�� ������ �ִϸ��̼�(���� ���)
	void SetPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void SetPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void SetPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void SetFPS(int framePerSec);

	void FrameUpdate(float elapsedTime);

	void Start(void);
	void Stop(void);
	void Pause(void);
	void Resume(void);

	inline BOOL IsPlay(void) { return _play; }

	inline POINT GetFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	inline int GetFrameWidth(void) { return _frameWidth; }

	inline int GetFrameHeight(void) { return _frameHeight; }

	inline DWORD GetPlayIndex(void) { return _nowPlayIdx; }

	inline int GetPlayListSize(void) { return _playList.size(); }
};


