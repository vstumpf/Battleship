#include "Object.h"
#include "Shape.h"
#include <memory>
#include <string>
#include <vector>
#include "Material.h"
#include "Light.h"
#include "GLSL.h"

#define PUSH() MV->pushMatrix()
#define POP() MV->popMatrix()


Object::Object(Shape * s)
{
	shape = s;
	float rscale = randFloat(.3f, 2.f);
	rscale = .07f;
	meshScale = Eigen::Vector3f(rscale, rscale, rscale);
	meshTrans = Eigen::Vector3f(0, 0, 0);
	jointScale = Eigen::Vector3f(1, 1, 1);
	xdegree = 0, ydegree = 0, zdegree = 0;
	selected = 0;
}


Object::~Object()
{
}

void Object::draw(MatrixStack * MV, Program * prog) {
	PUSH();
	MV->scale(meshScale);
	MV->translate(meshTrans);
	MV->scale(jointScale);
	MV->rotate(ydegree, Eigen::Vector3f(0, 1, 0));
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, MV->topMatrix().data());
	glUniform3f(prog->getUniform("ka"), material->getKar(), material->getKag(), material->getKab());
	glUniform3f(prog->getUniform("kd"), material->getKdr(), material->getKdg(), material->getKdb());
	glUniform3f(prog->getUniform("ks"), material->getKsr(), material->getKsg(), material->getKsb());
	glUniform1f(prog->getUniform("s"), material->getS());
	glUniform1i(prog->getUniform("selected"), selected);

	shape->draw(prog);
	POP();
}

float Object::randFloat(float l, float h)
{
	float r = rand() / (float)RAND_MAX;
	return (1.0f - r) * l + r * h;
}
