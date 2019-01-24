#pragma once
template<typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase(void){};
	~singletonBase(void){};

public:
	static T* GetSingleton(void);
	void ReleaseSingleton(void);

};

//�̱��� �ʱ�ȭ
template <typename T>
T* singletonBase<T>::singleton = 0;

template <typename T>
T* singletonBase<T>::GetSingleton(void)
{
	if (!singleton) singleton = new T;

	return singleton;
}

//�̱��� �޸� ����
template <typename T>
void singletonBase<T>::ReleaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}