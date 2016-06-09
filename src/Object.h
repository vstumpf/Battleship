#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Shape.h"
#include "Program.h"
#include <Eigen/Dense>
#include "MatrixStack.h"
#include "Material.h"
#include "Light.h"

#define NUMOBJS 300



class Object
{
public:
	Object(Shape * s);
	~Object();

	void draw(MatrixStack * MV, Program * prog);
	float randFloat(float l, float h);
	void setMTrans(Eigen::Vector3f t) { meshTrans = t; };
	void setMat(Material * m) { material = m; };
	void setSelected(int s) { selected = s; };
	void setMScale(float s) { meshScale = Eigen::Vector3f(s, s, s); };
	void setJScale(float s) { jointScale = Eigen::Vector3f(s, s, s); };

private:
	Shape * shape;
	Eigen::Vector3f meshScale;
	Eigen::Vector3f meshTrans;
	Eigen::Vector3f jointScale;

	float xdegree, ydegree, zdegree;
	Material * material;
	int selected;

};

