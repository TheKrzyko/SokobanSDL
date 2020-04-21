#include "Transformable.h"


Transformable::Transformable()
{
}


Transformable::~Transformable()
{
}
void Transformable::setPosition(const Vector2f pos)
{
	position = pos;
}

void Transformable::setPosition(const float x, const float y)
{
	position = Vector2f(x, y);
}

Vector2f Transformable::getPosition() const
{
	return position;
}

void Transformable::move(float x, float y)
{
	setPosition(position.x + x, position.y + y);
}

void Transformable::move(Vector2f pos)
{
	move(pos.x, pos.y);
}

void Transformable::setOrigin(const Vector2f pos)
{
	origin = pos;
}

void Transformable::setOrigin(const float x, const float y)
{
	origin = Vector2f(x, y);
}

Vector2f Transformable::getOrigin() const
{
	return origin;
}

void Transformable::setScale(const Vector2f scale)
{
	this->scale = scale;
}

void Transformable::setScale(const float x, const float y)
{
	scale = Vector2f(x, y);
}

Vector2f Transformable::getScale() const
{
	return scale;
}

void Transformable::setRotation(const double rotation)
{
	angle = rotation;
}

double Transformable::getRotation() const
{
	return angle;
}

void Transformable::rotate(double rotation)
{
	setRotation(angle + rotation);
}