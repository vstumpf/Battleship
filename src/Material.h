#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Dense>

enum TILE_MAT {
	MAT_MIN = 0,
	MAT_WATER = MAT_MIN,
	MAT_WATER_MISS,
	MAT_SHIP,
	MAT_SHIP_HIT,
	MAT_SELECT,
	MAT_MAX
};

class Material
{
public:
	Material(int type);
	void setS(float t) { s = t; }
	float getS() { return s; }
	void setKs(Eigen::Vector3f t) { ks = t; }
	Eigen::Vector3f getKs() { return ks; }
	void setKd(Eigen::Vector3f t) { kd = t; }
	Eigen::Vector3f getKd() { return kd; }
	void setKa(Eigen::Vector3f t) { kd = t; }
	Eigen::Vector3f getKa() { return kd; }

	void setKsr(float t) { ks = Eigen::Vector3f(t, ks.y(), ks.z()); };
	void setKsg(float t) { ks = Eigen::Vector3f(ks.x(), t, ks.z()); };
	void setKsb(float t) { ks = Eigen::Vector3f(ks.x(), ks.y(), t); };
	void setKar(float t) { ka = Eigen::Vector3f(t, ka.y(), ka.z()); };
	void setKag(float t) { ka = Eigen::Vector3f(ka.x(), t, ka.z()); };
	void setKab(float t) { ka = Eigen::Vector3f(ka.x(), ka.y(), t); };
	void setKdr(float t) { kd = Eigen::Vector3f(t, kd.y(), kd.z()); };
	void setKdg(float t) { kd = Eigen::Vector3f(kd.x(), t, kd.z()); };
	void setKdb(float t) { kd = Eigen::Vector3f(kd.x(), kd.y(), t); };

	float getKsr() { return ks.x(); };
	float getKsg() { return ks.y(); };
	float getKsb() { return ks.z(); };
	float getKar() { return ka.x(); };
	float getKag() { return ka.y(); };
	float getKab() { return ka.z(); };
	float getKdr() { return kd.x(); };
	float getKdg() { return kd.y(); };
	float getKdb() { return kd.z(); };

private:
	float s; //shininess factor
	Eigen::Vector3f ks; //specular color
	Eigen::Vector3f kd; //diffuse color
	Eigen::Vector3f ka; //ambient color

};

#endif
