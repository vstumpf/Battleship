#include "Material.h"
#include "Eigen/dense"

Material::Material(int type) {
	switch (type) {
	case MAT_WATER:
		ka = Eigen::Vector3f(0., 0., .7);
		kd = Eigen::Vector3f(0., 0., 0.);
		ks = Eigen::Vector3f(0., 0., 0.);
		s = 1.;
		break;
	case MAT_WATER_MISS:
		ka = Eigen::Vector3f(.0, .0, .5);
		kd = Eigen::Vector3f(0., 0., 0.);
		ks = Eigen::Vector3f(0., 0., 0.);
		s = 1.;
		break;
	case MAT_SHIP:
		ka = Eigen::Vector3f(0.5, 0.5, 0.5);
		kd = Eigen::Vector3f(0., 0., 0.);
		ks = Eigen::Vector3f(0., 0., 0.);
		s = 1.;
		break;
	case MAT_SHIP_HIT:
		ka = Eigen::Vector3f(0.7, 0., 0.);
		kd = Eigen::Vector3f(0., 0., 0.);
		ks = Eigen::Vector3f(0., 0., 0.);
		s = 1.;
		break;
	case MAT_SELECT:
		ka = Eigen::Vector3f(0., 0., 0.0);
		kd = Eigen::Vector3f(0., 0., 0.);
		ks = Eigen::Vector3f(0., 0., 0.);
		s = 1.;
		break;
	default:
		ka = Eigen::Vector3f(0., 0., 0.);
		kd = Eigen::Vector3f(0., 0., 0.);
		ks = Eigen::Vector3f(0., 0., 0.);
		s = 1.;
		break;
	}
}

