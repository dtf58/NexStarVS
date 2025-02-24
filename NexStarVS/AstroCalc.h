#pragma once

const double PI = 3.141592653589793238463;
const double DEG2RAD = PI / 180.;
const double RAD2DEG = 180. / PI;
const double ARCS = (3600.0 * 180.0 / PI);


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

	void azAlt2RaDec(double azimuth, double altitude, double lon, double lat, int diffUtm, bool summerTime, double& ra, double& dec, double& sidloc, double& tau);
	void calcRaDec(char* timeStamp, char* direction, double lon, double lat, int diffUtm, bool summerTime, double& ra, double& dec, double& sidloc, double& tau);
	void calcRaDec2000(double& ra, double& dec, double& ra2000, double& dec2000);
	void azAlt2DeTau(double azimuth, double altitude, double latitude, double& de, double& tau);
	void azAlt2DeTau(double azimuth, double altitude, double latitude, double& de, double& tau, double& tau1, double& tau2);
	double refraction(double angle);
	void strOnlyNumbers(char* str);
	void direction2AzAlt(char* direction, double& azimuth, double& altitude, bool hourFlag);
	void getTimeNow(TimeOwn& timeNow);
	void matrixProduct(double mat1[3][3], double mat2[3][3], double matOut[3][3]);
	void PrecMatrix_Equ(double T1, double T2, double m[3][3]);
	void NutMatrix(double T, double m[3][3]);
	double Frac(double x);
	double Modulo(double x, double y);

private:
	void calcCart(double phi, double theta, double r, double V[3]);
	void Rot_x(double rot, double mat[3][3]);
	void Rot_y(double rot, double mat[3][3]);
	void Rot_z(double rot, double mat[3][3]);
	void matrixVecMult(double mat[3][3], double vIn[3], double vOut[3]);
	void matrixTransposition(double m1[3][3], double m2[3][3]);
	void calcPolarAngles(double vec[3], double& phi, double& theta, double& r);
	void CalcMjd(TimeOwn & t);
	double CalcGast(double timeMjd);
	void timeOwnInit(char* timeStamp, TimeOwn& t);
	double linInterPol(double x, double x0, double x1, double f0, double f1);
	void KalkPN(double t);

	double refrAngle[6];
	double refrVal[6];
	double pn_[3][3];
};

