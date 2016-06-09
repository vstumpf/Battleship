
#include "Light.h"

Light::Light(int type) {
	col = Eigen::Vector3f(1., 1., 1.);
	if (type == FRONT) {
		pos = Eigen::Vector3f(1., 1., 1.);
		intensity = .8f;
	}
	else if (type == BACK) {
		pos = Eigen::Vector3f(-1., 1., 1.);
		intensity = .2f;
	}
	else {
		pos = Eigen::Vector3f(0, 0, 0);
		intensity = 0;
	}
}
void Light::translateX(float t) {
	pos = Eigen::Vector3f(pos.x() + t, pos.y(), pos.z());
}

void Light::translateY(float t) {
	pos = Eigen::Vector3f(pos.x(), pos.y() + t, pos.z());
}

void Light::upX() {
	translateX((float)LIGHT_TRANSFORM);
}

void Light::downX() {
	translateX((float)(-1 * LIGHT_TRANSFORM));
}

void Light::upY() {
	translateY((float)LIGHT_TRANSFORM);
}

void Light::downY() {
	translateY((float)(-1.f * LIGHT_TRANSFORM));
}