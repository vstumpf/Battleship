
#include "Light.h"

Light::Light(int type) {
	col = Eigen::Vector3f(1., 1., 1.);
	if (type == FRONT) {
		pos = Eigen::Vector3f(1., 1., 1.);
		intensity = .8;
	}
	else if (type == BACK) {
		pos = Eigen::Vector3f(-1., 1., 1.);
		intensity = .2;
	}
	else {
		pos = Eigen::Vector3f(0, 0, 0);
		intensity = 0;
	}
}
void Light::translateX(double t) {
	pos = Eigen::Vector3f(pos.x() + t, pos.y(), pos.z());
}

void Light::translateY(double t) {
	pos = Eigen::Vector3f(pos.x(), pos.y() + t, pos.z());
}

void Light::upX() {
	translateX(LIGHT_TRANSFORM);
}

void Light::downX() {
	translateX(-1 * LIGHT_TRANSFORM);
}

void Light::upY() {
	translateY(LIGHT_TRANSFORM);
}

void Light::downY() {
	translateY(-1 * LIGHT_TRANSFORM);
}