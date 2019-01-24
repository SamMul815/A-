#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"

effectManager::effectManager()
{
}


effectManager::~effectManager()
{
}

HRESULT effectManager::Init(void)
{

	return S_OK;
}

void effectManager::Release(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//ÅäÅ»ÀÌÆåÆ® º¤ÅÍ¸¦ µ¹¾Æ¼­
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (; mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (; vArrIter != mIter->second.end(); ++vArrIter)
				{
					(*vArrIter)->Release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}
}

void effectManager::Update(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//ÅäÅ»ÀÌÆåÆ® º¤ÅÍ¸¦ µ¹¾Æ¼­
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//±× ¾È¿¡ ´ã±ä ¸ÊÀÇ ÀÌÆåÆ® °Ë»çÇØ¼­
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->Update();
			}
		}
	}
}

void effectManager::Render(HDC hdc)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//ÅäÅ»ÀÌÆåÆ® º¤ÅÍ¸¦ µ¹¾Æ¼­
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//±× ¾È¿¡ ´ã±ä ¸ÊÀÇ ÀÌÆåÆ® °Ë»çÇØ¼­
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->Render(hdc);
			}
		}
	}
}
void effectManager::Render(HDC hdc, RECT cameraRc)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//ÅäÅ»ÀÌÆåÆ® º¤ÅÍ¸¦ µ¹¾Æ¼­
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//±× ¾È¿¡ ´ã±ä ¸ÊÀÇ ÀÌÆåÆ® °Ë»çÇØ¼­
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->Render(hdc, cameraRc);
			}
		}
	}
}

void effectManager::AddEffect(wstring effectName, LPCWSTR imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer)
{
	image* img;
	arrEffects vEffectBuffer; //ÀÌÆåÆ® ¹öÆÛ
	arrEffect mArrEffect;

	if (IMAGEMANAGER->FindImage(imageName))
	{
		img = IMAGEMANAGER->FindImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->AddImage(effectName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->Init(img, effectWidth, effectHeight, fps, elapsedTime);
	}

	mArrEffect.insert(pair<wstring, arrEffects>(effectName, vEffectBuffer));

	_vTotalEffects.push_back(mArrEffect);

}

void effectManager::Play(wstring effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//ÅäÅ»ÀÌÆåÆ® º¤ÅÍ¸¦ µ¹¾Æ¼­
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//±× ¾È¿¡ ´ã±ä ¸ÊÀÇ ÀÌÆåÆ® °Ë»çÇØ¼­
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == effectName)) break;

			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				//ÀÌÆåÆ®°¡ µ¿ÀÛÇÏ°í ÀÖÀ¸¸é °Ç³Ê¶Ú´Ù
				if ((*vArrIter)->GetIsRunning()) continue;
				(*vArrIter)->StartEffect(x, y);
				return;
			}
		}
	}
}