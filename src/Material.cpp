#include "Material.h"
#include "Eigen/dense"

Material::Material(int type) {
	if (type == BLUE) {
		ka = Eigen::Vector3f(.2, .2, .2);
		kd = Eigen::Vector3f(0., .2, 1);
		ks = Eigen::Vector3f(.1, .9, .1);
		s = 100.;
	}
	else if (type == GRAY) {
		ka = Eigen::Vector3f(0., 0., 0.);
		kd = Eigen::Vector3f(0.5, .5, .8);
		ks = Eigen::Vector3f(0., 0., 0.);
		s = 25.;
	}
	else if (type == PINK) {
		ka = Eigen::Vector3f(0.2f, 0.2f, 0.2f);
		kd = Eigen::Vector3f(0.8f, 0.7f, 0.7f);
		ks = Eigen::Vector3f(1.0f, 0.9f, 0.8f);
		s = 200.;
	}
	else {
		ka = Eigen::Vector3f(0., 0., 0.);
		kd = Eigen::Vector3f(0., 0., 0.);
		ks = Eigen::Vector3f(0., 0., 0.);
		s = 0;
	}
}

