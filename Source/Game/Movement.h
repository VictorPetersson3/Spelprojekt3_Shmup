#pragma once
class Movement
{
public:
	Movement();
	~Movement();
	void Straight(VECTOR2F& aPos, float aSpeed);
	void Wave(VECTOR2F& aPos, float aSpeed, float aMaxYValue, float aMinYValue);
	void Diagonal(VECTOR2F& aPos, float aSpeed);
	void Homing(VECTOR2F& aPos, float aSpeed);
private:

};

