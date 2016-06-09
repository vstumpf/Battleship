#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_
#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Dense>

#define FRONT 0
#define BACK 1
#define MAXLIGHTS 1
#define LIGHT_TRANSFORM .3

class Light
{
public:
	Light(int);
	void setIntensity(float t) { intensity = t; };
	float getIntensity() { return intensity; };
	void setPos(Eigen::Vector3f t) { pos = t; };
	Eigen::Vector3f getPos() { return pos; };
	void setColPos(Eigen::Vector3f t) { col = t; };
	Eigen::Vector3f getCol() { return col; };
	float getX() { return pos[0]; };
	float getY() { return pos[1]; };
	float getZ() { return pos[2]; };

	void translateX(float t);
	void translateY(float t);
	void upX();
	void downX();
	void upY();
	void downY();


private:
	Eigen::Vector3f pos;
	Eigen::Vector3f col;
	float intensity;
	
};

#endif
