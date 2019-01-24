#pragma once

namespace TANGO_UTIL
{

	//포인트 구조체
	typedef struct tagPoint
	{
		float x;
		float y;

		tagPoint() : x(0.0f), y(0.0f) {}

		void move(float dx, float dy)
		{
			x += dx;
			y += dy;
		}
	}MYPOINT, *LPMYPOINT;

	//원 구조체
	typedef struct tagCircle
	{
		float x;	//원의 중심x좌표
		float y;	//원의 중심y좌표
		float r;	//원의 반지름

		tagCircle() : x(0.0f), y(0.0f), r(0.0f) {}
		tagCircle(float _x, float _y, float _r) : x(_x), y(_y), r(_r) {}

		void Move(float dx, float dy)
		{
			x += dx;
			y += dy;
		}

		void Set(float centerX, float centerY, float radius)
		{
			x = centerX;
			y = centerY;
			r = radius;
		}

		void SetCenterPos(float posX, float posY)
		{
			x = posX;
			y = posY;
		}

		void Render(HDC hdc)
		{
			int x1 = FLOAT_TO_INT(x);
			int y1 = FLOAT_TO_INT(y);
			int r1 = FLOAT_TO_INT(r);

			Ellipse(hdc, x1 - r1, y1 - r1, x1 + r1, y1 + r1);
		}
	}MYCIRCLE, *LPMYCIRCLE;

	//사각형
	typedef struct tagMYRECT
	{
		float left;
		float top;
		float right;
		float bottom;

		tagMYRECT() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
		tagMYRECT(float _left, float _top, float _right, float _bottom) :
			left(_left), top(_top), right(_right), bottom(_bottom) {}

		void Move(float dx, float dy)
		{
			left += dx;
			top += dy;
			right += dx;
			bottom += dy;
		}

		void Set(float _left, float _top, float _right, float _bottom)
		{
			left = _left;
			top = _top;
			right = _right;
			bottom = _bottom;
		}

		void SetLeftTopPos(float _left, float _top)
		{
			float width = GetWidth();
			float height = GetHeight();

			left = _left;
			top = _top;
			right = _left + width;
			bottom = _top + height;
		}

		void SetCenterPos(float centerX, float centerY)
		{
			float halfW = GetWidth() * 0.5f;
			float halfH = GetHeight() * 0.5f;

			left = centerX - halfW;
			top = centerY - halfH;
			right = centerX + halfW;
			bottom = centerY + halfH;
		}

		void Render(HDC hdc)
		{
			Rectangle(hdc,
				FLOAT_TO_INT(left),
				FLOAT_TO_INT(top),
				FLOAT_TO_INT(right),
				FLOAT_TO_INT(bottom));
		}

		float GetWidth() { return right - left; }
		float GetHeight() { return bottom - top; }
	}MYRECT, *LPMYRECT;


	//POINT가 사각형 안에 있니?
	bool CheckPointInRect(const RECT& rc, const POINT& pt);
	bool CheckPointInRect(const RECT& rc, int x, int y);
	bool CheckPointInRect(const MYRECT& rc, float x, float y);
	bool CheckPointInRect(const MYRECT& rc, const MYPOINT& pt);

	//POINT가 원 안에 있니?
	bool CheckPointInCircle(float cX, float cY, float cR, const MYPOINT& pt);
	bool CheckPointInCircle(float cX, float cY, float cR, float x, float y);
	bool CheckPointInCircle(const MYCIRCLE& rc, float x, float y);
	bool CheckPointInCircle(const MYCIRCLE& rc, const MYPOINT& pt);

	//사각형이 사각형과 충돌했니?
	bool IsCollision(const MYRECT& rc1, const MYRECT& rc2);
	bool IsCollision(const RECT& rc1, const RECT& rc2);

	//원과 원이 충돌했니?
	bool IsCollision(const MYCIRCLE& cir1, const MYCIRCLE& cir2);

	//원과 사각형이 충돌했니?
	bool IsCollision(const MYCIRCLE& cir, const RECT& rc);
	bool IsCollision(const MYCIRCLE& cir, const MYRECT& rc);

	//충돌했다면 리액션은 어떻게 취하니?
	bool IsCollisionReaction(const RECT& rcHold, RECT& rcMove);
	bool IsCollisionReaction(const MYRECT& mrcHold, MYRECT& mrcMove);
	bool IsCollisionReaction(const MYCIRCLE& cirHold, MYCIRCLE& cirMove);

}