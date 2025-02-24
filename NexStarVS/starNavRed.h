/******************************************************************************/
/*                                                                            */
/*                                starNavRed.h                                */
/*                                                                            */
/******************************************************************************/

#ifndef STARNAVRED_H
#define STARNAVRED_H

/*============================================================================*/
/* ENVIRONMENT                                                                */
/*============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//#include "quadMath.h"
//#include "Quaternions.h"

/*============================================================================*/
/* DEFINES                                                                      */
/*============================================================================*/
#define ARCS  (3600.0*180.0/M_PI)
#define KGAUSS  0.01720209895
#define GM_SUN  (KGAUSS*KGAUSS)
#define C_LIGHT 173.14
#define STERN_NAME_LEN  32
#define ASTRO_O 10
#define ASTRO_DIM (ASTRO_O*2+1)
#define ASTRO_PI2 (M_PI*2.)
#define ASTRO_RAD (M_PI/180.)
#define ERD_RAD 6378137.

#define RAD2DEG(a) (a/M_PI*180.)
#define DEG2RAD(a) (a*M_PI/180.)

typedef struct Stern_
{
    char nameInternat_[32];
    char nameDeutsch_[32];
    int hdNummer_;
    double raJ2000_;
    double deJ2000_;
    double eigenRA_;
    double eigenDE_;
    double ra_;
    double de_;
    double zeitApp_;
    double zeitMess_;
    double lokalMeridian_;
    double hoeheC_;
    double hoeheMess_;
    double azimutC_;
} Stern;


double KalkGAST( double tMJD );
double KalkGAST_GMST( double tMJD, double *rgmst, double *rdgmast );
double KalkLokalMeridian( double tMJD, double ra, double lam );
void Hor2EciLD( double height, double azimuth, double lat, double * de, double * tau );
void EciLD2Hor( double de, double tau, double lat, double * height, double * azimuth );
void Ecef2Eci(double vec_in[3], double time, double vec_out[3] );
void Eci2Ecef(double vec_in[3], double time, double vec_out[3] );
void Eci2EciLD(double vec_in[3], double time, double vec_out[3], int flagAberration );
void EciLD2Ecef(double vec_in[3], double time, double vec_out[3] );
void Ecef2EciLD(double vec_in[3], double time, double vec_out[3] );
void EciLD2Eci(double vec_in[3], double time, double vec_out[3], int flagAberration );
void StarApparent(Stern* s, double laenge, double breite, double timeMjd);

void los2RaDeD( double los[3], double *ra, double *de );
void strLosCalcD( double tMJD, double qs, double q1, double q2, double q3, double los[3] );
void quad2RaDeRollD( double qIs, double qI1, double qI2, double qI3, double *ra, double *de, double *ro );

void ecef2lla(double vec[3], double *lon, double *lat, double *h);
void lla2ecef(double lon, double lat, double h, double vec[3]);

void velocityOfEarth(double modifiedJulianDate, double velocity[3]);
void velocityOfEarthSimple(double modifiedJulianDate, double velocity[3]);

#endif
