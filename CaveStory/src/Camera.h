#pragma once

#include "Utils/units.h"
#include "Rectangle.h"
#include "GameObject.h"
class Camera {
public:
	Camera();
	// ����Camera����λ��
	Camera(Position2D pos);
	// ����Camera�ӽ�
	Camera(const Rectangle& rect);
	virtual ~Camera() {}
	// ����Camera�ӽ����޶��ӽ�����
	void setRestrict(Rectangle t);
	void follow(Position2D pos);
	virtual void update(units::MS deltaTime);
	void restrict(Rectangle tmpRect);// restrict��c99�ؼ���
	bool isInCamera(Rectangle) const;
	Position2D currentPos() const;
	Rectangle currentRect() const;
protected:
	Rectangle viewPort_;
	Rectangle restrict_;
	Position2D curPos_,targetPos_;// ����ʾ�������λ��
};