#include "pch.h"
#include "AstroCalc.h"
#include <ctime>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <numbers>


AstroCalc::AstroCalc()
{
    refrAngle[0] = 0.;
    refrAngle[1] = 1.;
    refrAngle[2] = 2.;
    refrAngle[3] = 5.;
    refrAngle[4] = 10.;
    refrAngle[5] = 20.;
    refrVal[0] = 34. / 60.;
    refrVal[1] = 25. / 60. + 36. / 3600.;
    refrVal[2] = 19. / 60. +  7. / 3600.;
    refrVal[3] = 10. / 60. + 15. / 3600.;
    refrVal[4] =  5. / 60. + 31. / 3600.;
    refrVal[5] = refraction(20.);

}

AstroCalc::~AstroCalc()
{

}

void AstroCalc::azAlt2RaDec(double azimuth, double altitude, double lon, double lat, int diffUtm, bool summerTime, double& ra, double& dec, double& sidloc, double& tau)
{
    struct tm zeit;
    __time64_t sec;

    _time64(&sec);
    _localtime64_s(&zeit, &sec);

    TimeOwn timeNow;

    timeNow.year_ = zeit.tm_year - 100 + 2000;
    timeNow.day_ = zeit.tm_mday;
    timeNow.month_ = zeit.tm_mon+1;
    timeNow.hour_ = zeit.tm_hour;
    timeNow.minute_ = zeit.tm_min;
    timeNow.second_ = zeit.tm_sec;

    CalcMjd(timeNow);

    double timeMjdUTC = timeNow.timeMjd_ - ((double)diffUtm / 24. );
    if (summerTime)
    {
        timeMjdUTC -= 1. / 24.;
    }
    double tauGreenwich = CalcGast(timeMjdUTC);

    sidloc = (tauGreenwich + lon * DEG2RAD);

    azAlt2DeTau(azimuth * DEG2RAD, altitude * DEG2RAD, lat * DEG2RAD, dec, tau);

    ra = sidloc-tau;
    if (ra > 2 * PI)
    {
        ra -= 2 * PI;
    }
    if (ra < 0.)
    {
        ra += 2 * PI;
    }

    ra *= RAD2DEG;
    dec *= RAD2DEG;
}

void AstroCalc::strOnlyNumbers(char* str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (!((str[i] >= 48 && str[i] <= 57) || str[i] == '.'))
        {
            str[i] = ' ';
        }
    }

}

void AstroCalc::timeOwnInit(char* timeStamp, TimeOwn& t)
{
    strOnlyNumbers(timeStamp);

    int year, month, day, hour, minute;
    double second;
    sscanf_s(timeStamp, "%d %d %d %d %d %le", &year, &month, &day, &hour, &minute, &second);

    t.year_ = year;
    t.day_ = day;
    t.month_ = month;
    t.hour_ = hour;
    t.minute_ = minute;
    t.second_ = second;
    CalcMjd(t);
}

void AstroCalc::direction2AzAlt(char* direction, double& azimuth, double& altitude)
{
    strOnlyNumbers(direction);
    
    int azD, azM, altD, altM;
    double azS, altS;

    sscanf_s(direction, "%d %d %le %d %d %le", &azD, &azM, &azS, &altD, &altM, &altS);

    azimuth = (double)azD + (double)azM / 60. + azS / 3600.;
    altitude = (double)altD + (double)altM / 60. + altS / 3600.;

}

void AstroCalc::calcRaDec(char * timeStamp, char * direction, double lon, double lat, int diffUtm, bool summerTime, double& ra, double& dec, double& sidloc, double& tau)
{
    TimeOwn timeTest;

    timeOwnInit(timeStamp, timeTest);

    double timeMjdUTC = timeTest.timeMjd_ - ((double)diffUtm / 24.);
    if (summerTime)
    {
        timeMjdUTC -= 1. / 24.;
    }
    double tauGreenwich = CalcGast(timeMjdUTC);

    sidloc = (tauGreenwich + lon * DEG2RAD);

    double azimuth, altitude;
    direction2AzAlt(direction, azimuth, altitude);

    azAlt2DeTau(azimuth * DEG2RAD, altitude * DEG2RAD, lat * DEG2RAD, dec, tau);

    ra = sidloc - tau;
    if (ra > 2 * PI)
    {
        ra -= 2 * PI;
    }
    if (ra < 0.)
    {
        ra += 2 * PI;
    }

    ra *= RAD2DEG;
    dec *= RAD2DEG;
}

void AstroCalc::azAlt2DeTau(double azimuth, double altitude, double latitude, double& de, double& tau)
{
    double hor[3], equ[3];
    double mat[3][3], r;

    calcCart(azimuth, altitude, 1., hor);
    Rot_y((PI / 2. - latitude), mat);
    matrixVecMult(mat, hor, equ);

    calcPolarAngles(equ, tau, de, r);

    if (tau < PI)
    {
        tau += PI;
    }
    else
    {
        tau -= PI;
    }

}

void AstroCalc::azAlt2DeTau(double azimuth, double altitude, double latitude, double& de, double& tau, double& tau1, double& tau2)
{
    double sinDec = cos(altitude) * cos(azimuth) * cos(latitude) + sin(altitude) * sin(latitude);
    de = asin(sinDec);
    double cosDec = cos(de);

    double sinTau = cos(altitude) * sin(azimuth) / cosDec;
    tau = asin(sinTau);

    double cosTau = ((cos(altitude) * cos(azimuth) * sin(latitude)) + (sin(altitude) * cos(latitude))) / cosDec;
    tau1 = acos(cosTau);

    cosTau = (sin(altitude) - (sin(de) * sin(latitude))) / cosDec / cos(latitude);
    tau2 = acos(cosTau);

}


void AstroCalc::calcCart(double phi, double theta, double r, double Vec[3])
{
    double cosEl;
    cosEl = cos(theta);

    Vec[0] = r * cos(phi) * cosEl;
    Vec[1] = r * sin(phi) * cosEl;
    Vec[2] = r * sin(theta);
}

void AstroCalc::Rot_x(double rot, double mat[3][3])
{
    double S, C;
    S = sin(rot);
    C = cos(rot);

    mat[0][0] = 1.0;    mat[0][1] = 0.0;    mat[0][2] = 0.0;
    mat[1][0] = 0.0;    mat[1][1] = +C;     mat[1][2] = +S;
    mat[2][0] = 0.0;    mat[2][1] = -S;     mat[2][2] = +C;

    return;
}

void AstroCalc::Rot_y(double rot, double mat[3][3])
{
    double S, C;
    S = sin(rot);
    C = cos(rot);

    mat[0][0] = +C;    mat[0][1] = 0.0;    mat[0][2] = -S;
    mat[1][0] = 0.0;   mat[1][1] = 1.0;    mat[1][2] = 0.0;
    mat[2][0] = +S;    mat[2][1] = 0.0;    mat[2][2] = +C;

    return;
}

void AstroCalc::Rot_z(double rot, double mat[3][3])
{
    double S, C;
    S = sin(rot);
    C = cos(rot);

    mat[0][0] = +C;    mat[0][1] = +S;    mat[0][2] = 0.0;
    mat[1][0] = -S;    mat[1][1] = +C;    mat[1][2] = 0.0;
    mat[2][0] = 0.0;   mat[2][1] = 0.0;   mat[2][2] = 1.0;

    return;
}

void AstroCalc::matrixVecMult(double mat[3][3], double vIn[3], double vOut[3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        vOut[i] = 0.;
        for (j = 0; j < 3; j++)
            vOut[i] += mat[i][j] * vIn[j];
    }
}

void AstroCalc::calcPolarAngles(double vec[3], double & phi, double & theta, double & r)
{
    double rhoH2, rho;

    rhoH2 = vec[0] * vec[0] + vec[1] * vec[1];

    r = sqrt(rhoH2 + vec[2] * vec[2]);

    if ((vec[0] == 0.0) && (vec[1] == 0.0))
    {
        phi = 0.0;
    }
    else
    {
        phi = atan2(vec[1], vec[0]);
    }
    if (phi < 0.0)
    {
        phi += 2.0 * PI;
    }

    rho = sqrt(rhoH2);
    if ((vec[2] == 0.0) && (rho == 0.0))
    {
        theta = 0.0;
    }
    else
    {
        theta = atan2(vec[2], rho);
    }
}

void AstroCalc::CalcMjd(TimeOwn& t)
{
    int month, year, b, Mjd0;
    if (t.month_ <= 2)
    {
        month = t.month_ + 12;
        year = t.year_ - 1;
    }
    else
    {
        month = t.month_;
        year = t.year_;
    }
    if ((10000L * year + 100L * month + t.day_) <= 15821004L)
        b = -2 + ((year + 4716) / 4) - 1179;
    else
        b = (int)(year / 400) - (int)(year / 100) + (int)(year / 4);
    Mjd0 = 365L * year - 679004L + b + (int)(30.6001 * (month + 1)) + t.day_;
    t.timeMjd_ = ((double)t.hour_ + (double)t.minute_ / 60. + t.second_ / 3600.) / 24.;
    t.timeMjd_ += (double)Mjd0;
}

double AstroCalc::CalcGast(double timeMjd)
{
    double Secs = 86400.0;
    double MJD_0, UT, T_0, T, gmst;
    double tau;
    double eqeq, d, eps, l, om, dpsi;

    MJD_0 = floor(timeMjd);
    UT = Secs * (timeMjd - MJD_0);
    T_0 = (MJD_0 - 51544.5) / 36525.0;
    T = (timeMjd - 51544.5) / 36525.0;

    gmst = 24110.54841 + 8640184.812866 * T_0 + 1.00273790935 * UT
        + (0.093104 - 6.2e-6 * T) * T * T; 

    tau = (2. * PI / Secs) * Modulo(gmst, Secs);

    d = timeMjd - 51544.5;
    eps = (23.4393 - 0.0000004 * d) / 180. * PI;
    l = (280.47 + 0.98565 * d) / 180. * PI;
    om = (125.04 - 0.052954 * d) / 180. * PI;
    dpsi = -0.000319 * sin(om) - 0.000024 * sin(2. * l);
    eqeq = dpsi * cos(eps);
    eqeq = eqeq * PI / 12.;

    tau += eqeq;

    return tau;
}

double AstroCalc::Modulo(double x, double y)
{
    double help = x / y;
    return y * (help-floor(help));
}

double AstroCalc::refraction(double angle)
{
    double refr = 34. / 60.;
    if (angle > 0.)
    {
        if (angle >= 20.)
        {
            double tana = tan((90. - angle) * DEG2RAD);
            refr = (tana / 60. - (0.06 / 3600. * tana * tana * tana));
        }
        else
        {
            int i = 0;
            for (i = 0; i < 5; ++i)
            {
                if ((angle > refrAngle[i]) && (angle <= refrAngle[i + 1]))
                {
                    break;
                }
            }
            refr = linInterPol(angle, refrAngle[i], refrAngle[i + 1], refrVal[i], refrVal[i + 1]);
        }

    }

    return refr;
}

double AstroCalc::linInterPol(double x, double x0, double x1, double f0, double f1)
{
    return (f0 + (f1 - f0) / (x1 - x0) * (x - x0));
}
