#include "comMath/VekMat.h"

void matrixProduct(double m1[3][3], double m2[3][3], double m3[3][3])
{
    int i, j, l;
    double s;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            s = 0.;
            for (l = 0; l < 3; l++)
                s += m1[i][l] * m2[l][j];
            m3[i][j] = s;
        }
    }
}

void matrixTransposition(double m1[3][3], double m2[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            m2[i][j] = m1[j][i];
}

double AbsVector(double v[3])
{
    double s;

    s = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];

    return sqrt(s);
}

void matrixVectMult(double m[3][3], double v1[3], double v2[3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        v2[i] = 0.;
        for (j = 0; j < 3; j++)
            v2[i] += m[i][j] * v1[j];
    }
}

void MatrixVectMult4(double m[3][4], double v1[4], double v2[3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        v2[i] = 0.;
        for (j = 0; j < 4; j++)
        {
            v2[i] += m[i][j] * v1[j];
        }
    }
}

void R_x(double RotAngle, double m[3][3])
{
    double S, C;
    S = sin(RotAngle);
    C = cos(RotAngle);

    m[0][0] = 1.0;
    m[0][1] = 0.0;
    m[0][2] = 0.0;
    m[1][0] = 0.0;
    m[1][1] = +C;
    m[1][2] = +S;
    m[2][0] = 0.0;
    m[2][1] = -S;
    m[2][2] = +C;

    return;
}

void R_y(double RotAngle, double m[3][3])
{
    double S, C;
    S = sin(RotAngle);
    C = cos(RotAngle);

    m[0][0] = +C;
    m[0][1] = 0.0;
    m[0][2] = -S;
    m[1][0] = 0.0;
    m[1][1] = 1.0;
    m[1][2] = 0.0;
    m[2][0] = +S;
    m[2][1] = 0.0;
    m[2][2] = +C;

    return;
}

void R_z(double RotAngle, double m[3][3])
{
    double S, C;
    S = sin(RotAngle);
    C = cos(RotAngle);

    m[0][0] = +C;
    m[0][1] = +S;
    m[0][2] = 0.0;
    m[1][0] = -S;
    m[1][1] = +C;
    m[1][2] = 0.0;
    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;

    return;
}

/**
 * Calculates the polar coordinates of a vector given in Cartesian coordinates.
 * @param Vec vector in Cartesian coordinates
 * @param phi azimuthal angle [rad]
 * @param theta polar angle [rad]
 * @param r
 */
void calcPolarAngles(double vector[3], double *phi, double *theta, double *r)
{
    double rhoSqr, rho;

    // Laenge der Projektion des Vektors in die x-y-Ebene
    rhoSqr = vector[0] * vector[0] + vector[1] * vector[1];

    // Betrag des Vektors
    *r = sqrt(rhoSqr + vector[2] * vector[2]);

    // Azimut des Vektors
    if ((vector[0] == 0.0) && (vector[1] == 0.0))
    {
        *phi = 0.0;
    }
    else
    {
        *phi = atan2(vector[1], vector[0]);
    }
    if (*phi < 0.0)
    {
        *phi += 2.0 * M_PI;
    }

    // Elevation des Vektors
    rho = sqrt(rhoSqr);
    if ((vector[2] == 0.0) && (rho == 0.0))
    {
        *theta = 0.0;
    }
    else
    {
        *theta = atan2(vector[2], rho);
    }
}

void calcCart(double phi, double theta, double r, double Vec[3])
{
    double cosEl;
    cosEl = cos(theta);

    Vec[0] = r * cos(phi) * cosEl;
    Vec[1] = r * sin(phi) * cosEl;
    Vec[2] = r * sin(theta);
}

double crossAngle(double a[3], double b[3])
{
    double sp, f1, f2;

    sp = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    f1 = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    f2 = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);

    return acos(sp / f1 / f2);
}

double crossAngle2PointLine(double aa[3], double bb[3], double u[3])
{
    double sp, f1, f2;
    double a[3],b[3];
    int i;
    
    for(i=0;i<3;i++)
    {
         a[i] = aa[i]-u[i];
         b[i] = bb[i]-u[i];
    }

    sp = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    f1 = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    f2 = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);

    return acos(sp / f1 / f2);
}

void norm(double v[3])
{
    double f;

    f = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= f;
    v[1] /= f;
    v[2] /= f;

}

void vecStatD( int n, double *vec, double *mw, double *stabw)
{
    int i;
    double sum=0.,sum2=0.;
    
    if( n<2 )
    {
       *mw=0.;
       *stabw=0.;
       return;
    }
    
    for(i=0;i<n;i++)
    {
        sum += vec[i];
        sum2 += vec[i]*vec[i];
    }
    
    *mw = sum / (double) n;
    
    *stabw = sqrt((sum2-sum*sum/(double)n)/(double)(n-1));
}


void vecKorrelD( int n, double *t, double *vec, double *a, double *b)
{
    int i;
    double st=0.,st2=0.,stvec=0.,svec=0.,delta;
    
    for(i=0;i<n;i++)
    {
        st += t[i];
        st2 += t[i]*t[i];
        svec += vec[i];
        stvec += t[i]*vec[i];
    }
    
    delta = (double)n*st2 - st*st;

    *b = ((double)n*stvec - st*svec)/delta;   
    *a = (st2*svec-st*stvec)/delta;

}

