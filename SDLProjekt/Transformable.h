#pragma once
#include "Vector2.h"

class Transformable
{
protected:
	Vector2f position = Vector2f(0, 0);
	//Value between 0 and 1
	Vector2f origin = Vector2f(0.5, 0.5);
	Vector2f scale = Vector2f(1, 1);
	double angle = 0.0;
public:

	void setPosition(Vector2f pos);
	void setPosition(float x, float y);
	Vector2f getPosition() const;
	void move(float x, float y);
	void move(Vector2f pos);

	void setOrigin(Vector2f pos);
	void setOrigin(float x, float y);
	Vector2f getOrigin() const;

	void setScale(Vector2f scale);
	void setScale(float x, float y);
	Vector2f getScale() const;

	void setRotation(double rotation);
	double getRotation() const;
	void rotate(double rotation);

	Transformable();
	~Transformable();
};

