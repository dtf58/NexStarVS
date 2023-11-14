#pragma once

typedef struct TimeOwn_ {
	int year_;
	int month_;
	int day_;
	int hour_;
	int minute_;
	double second_;
	double timeMjd_;
} TimeOwn;

class AstroCalc
{
public:
	AstroCalc();
	~AstroCalc();

	void azAlt2RaDec(double azimuth, double altitude, double lon, double lat, int diffUtm, bool summerTime, double& ra, double& dec);

private:
	void hor2EciLd(double azimuth, double altitude, double latitude, double& de, double& tau);
	void calcCart(double phi, double theta, double r, double V[3]);
	void Rot_x(double rot, double mat[3][3]);
	void Rot_y(double rot, double mat[3][3]);
	void Rot_z(double rot, double mat[3][3]);
	void matrixVecMult(double mat[3][3], double vIn[3], double vOut[3]);
	void calcPolarAngles(double vec[3], double& phi, double& theta, double& r);
	void CalcMjd(TimeOwn & t);
	double CalcGast(double timeMjd);
	double Modulo(double x, double y);

};

