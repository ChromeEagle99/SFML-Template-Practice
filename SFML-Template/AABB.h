#pragma once


struct AABB 
{
	//position
	float x, y;
	//size
	float width, height;
	//min position
	float min_x, min_y;
	//max position
	float max_x, max_y;
	AABB();
	AABB(float, float, float, float);
};

bool pointVsRectCheck(float, float, AABB&);
