#include "AABB.h"

AABB::AABB() 
{


}

AABB::AABB(float x, float y, float width, float height) :
	x(x), y(y), width(width), height(height)
{
	//this->x = x;
	//this->y = y;
	//this->width = width;
	//this->height = height;

	this->min_x = x - (width / 2.0f);
	this->max_x = x + (width / 2.0f);

	this->min_y = y - (height / 2.0f);
	this->max_y = y + (height / 2.0f);
}

bool pointVsRectCheck(float x, float y, AABB& box)
{
	return	x >= box.min_x && x <= box.max_x &&
			y >= box.min_y && y <= box.max_y;
}