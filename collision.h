#pragma once

namespace TANGO_UTIL
{

	//����Ʈ ����ü
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

	//�� ����ü
	typedef struct tagCircle
	{
		float x;	//���� �߽�x��ǥ
		float y;	//���� �߽�y��ǥ
		float r;	//���� ������

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

	//�簢��
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


	//POINT�� �簢�� �ȿ� �ִ�?
	bool CheckPointInRect(const RECT& rc, const POINT& pt);
	bool CheckPointInRect(const RECT& rc, int x, int y);
	bool CheckPointInRect(const MYRECT& rc, float x, float y);
	bool CheckPointInRect(const MYRECT& rc, const MYPOINT& pt);

	//POINT�� �� �ȿ� �ִ�?
	bool CheckPointInCircle(float cX, float cY, float cR, const MYPOINT& pt);
	bool CheckPointInCircle(float cX, float cY, float cR, float x, float y);
	bool CheckPointInCircle(const MYCIRCLE& rc, float x, float y);
	bool CheckPointInCircle(const MYCIRCLE& rc, const MYPOINT& pt);

	//�簢���� �簢���� �浹�ߴ�?
	bool IsCollision(const MYRECT& rc1, const MYRECT& rc2);
	bool IsCollision(const RECT& rc1, const RECT& rc2);

	//���� ���� �浹�ߴ�?
	bool IsCollision(const MYCIRCLE& cir1, const MYCIRCLE& cir2);

	//���� �簢���� �浹�ߴ�?
	bool IsCollision(const MYCIRCLE& cir, const RECT& rc);
	bool IsCollision(const MYCIRCLE& cir, const MYRECT& rc);

	//�浹�ߴٸ� ���׼��� ��� ���ϴ�?
	bool IsCollisionReaction(const RECT& rcHold, RECT& rcMove);
	bool IsCollisionReaction(const MYRECT& mrcHold, MYRECT& mrcMove);
	bool IsCollisionReaction(const MYCIRCLE& cirHold, MYCIRCLE& cirMove);

}