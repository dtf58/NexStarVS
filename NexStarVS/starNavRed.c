/******************************************************************************/
/*                                                                            */
/*                          starNav.c                                         */
/*                                                                            */
/******************************************************************************/

/*============================================================================*/
/* ENVIRONMENT                                                                */
/*============================================================================*/
#include "navigation/starNavRed.h"
#include "comMath/VekMat.h"
#include "utility/timeTools.h"
#include "quatMath/Quaternions.h"

// #define ADD_PRINT 1

/*============================================================================*/
/* EXPORTED DATA                                                              */
/*============================================================================*/

/*============================================================================*/
/* LOCAL TYPES & DATA                                                         */
/*============================================================================*/
static double pn_[3][3];
static double v_earth[3];
static double BreiteAP_;

double const el_a = 6378137.;
double const el_b = 6356752.31424518;
double const el_f = 3.35281066474748e-3;
double const el_e= 8.18191908426203e-2;
double const el_es= 8.20944379496945e-2;

/*============================================================================*/
/* LOCAL SUB-PROGRAMS                                                         */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/* FUNCTION    : PrecMatrix_Equ                                               */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void PrecMatrix_Equ (double T1, double T2, double m[3][3])
{
   double dT;
   double zeta,z,theta;
   double m1[3][3],m2[3][3],m3[3][3],m4[3][3];

   dT = T2-T1;
   zeta  =  ( (2306.2181+(1.39656-0.000139*T1)*T1)+
                ((0.30188-0.000344*T1)+0.017998*dT)*dT )*dT/ARCS;
   z     =  zeta + ( (0.79280+0.000411*T1)+0.000205*dT)*dT*dT/ARCS;
   theta =  ( (2004.3109-(0.85330+0.000217*T1)*T1)-
                ((0.42665+0.000217*T1)+0.041833*dT)*dT )*dT/ARCS;

   R_z(-z,m1);
   R_y(theta,m2);
   R_z(-zeta,m3);

   matrixProduct( m1, m2, m4 );
   matrixProduct( m4, m3, m );
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : Frac                                                         */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
double Frac (double x)
{
   return x-floor(x);
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : Modulo                                                       */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
double Modulo (double x, double y)
{
   return y*Frac(x/y);
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : NutMatrix                                                    */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void NutMatrix (double T, double m[3][3])
{
   double  ls, D, F, N;
   double  eps, dpsi, deps;
   double m1[3][3],m2[3][3],m3[3][3],m4[3][3];
//   int i,j;
   ls = 2.*M_PI*Frac(0.993133+  99.997306*T);   // Mittlere Anomalie der Sonne
   D  = 2.*M_PI*Frac(0.827362+1236.853087*T);   // Laengendifferenz Sonne-Mond
   F  = 2.*M_PI*Frac(0.259089+1342.227826*T);   // Mittleres Argument der Breite
   N  = 2.*M_PI*Frac(0.347346-   5.372447*T);   // Laenge des aufsteigenden Knotens

   dpsi = ( -17.200*sin(N)   - 1.319*sin(2*(F-D+N)) - 0.227*sin(2*(F+N))
           + 0.206*sin(2*N) + 0.143*sin(ls) ) / ARCS;
   deps = ( + 9.203*cos(N)   + 0.574*cos(2*(F-D+N)) + 0.098*cos(2*(F+N))
           - 0.090*cos(2*N)                 ) / ARCS;

   eps  = 0.4090928-2.2696E-4*T;            // Mittlere Schiefe der Ekliptik

   R_x(-eps-deps,m1);
   R_z(-dpsi,m2);
   R_x(+eps,m3);

   matrixProduct( m1, m2, m4 );
   matrixProduct( m4, m3, m );
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : Equ2EclMatrix                                                */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void Equ2EclMatrix (double T, double m[3][3])
{
  double eps;
    eps = ( 23.43929111-(46.8150+(0.00059-0.001813*T)*T)*T/3600.0 ) * M_PI/180.;

  R_x(eps,m);

  return;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : Ecl2EquMatrix                                                */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void Ecl2EquMatrix (double T, double m[3][3])
{
  double m1[3][3];

  Equ2EclMatrix(T,m1);
  matrixTransposition(m1,m);

  return;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : EccAcnom                                                     */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
double EccAnom (double M, double e)
{
  int    maxit = 15;
  double eps   = 100.0*1.e-10;
  int    i=0;
  double E, f;

  // Startwert
  M = Modulo(M, 2.0*M_PI);
  if (e<0.8) E=M; else E=M_PI;

  // Iteration
  do {
    f = E - e*sin(E) - M;
    E = E - f / ( 1.0 - e*cos(E) );
    ++i;
    if (i==maxit) {
      /* cerr << " Konvergenzprobleme in EccAnom" << endl; */
      break;
    }
  }
  while (fabs(f) > eps);

  return E;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : Ellip                                                        */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void Ellip ( double GM, double M, double a, double e,
             double r[3], double v[3] )
{
  //
  // Variablen
  //
  double k, E, cosE,sinE, fac, rho;


  k  = sqrt(GM/a);

  E  = EccAnom(M,e);

  cosE = cos(E);
  sinE = sin(E);

  fac = sqrt ( (1.0-e)*(1.0+e) );

  rho = 1.0 - e*cosE;

  r[0] = a*(cosE-e);
  r[1] = a*fac*sinE;
  r[2] = 0.0;
  v[0] = -k*sinE/rho;
  v[1] = k*fac*cosE/rho;
  v[2] = 0.0;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : GaussVec                                                     */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void GaussVec (double Omega, double i, double omega, double m[3][3] )
{
   double m1[3][3],m2[3][3],m3[3][3],m4[3][3];

   R_z(-Omega,m1);
   R_x(-i,m2);
   R_z(-omega,m3);

   matrixProduct( m1, m2, m4 );
   matrixProduct( m4, m3, m );
   return;
}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : VelocityEarth                                                */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void VelocityEarth(double T, double r[3], double v[3])
{
  //
  // Konstanten
  //
  double p;        // Praezession in einem Jahrhundert [deg]

  double a=0.0, e=0.0, M0=0.0, O=0.0, i=0.0, w=0.0, n=0.0, T0=0.0;
  double  PQR[3][3];
  p = 1.3970;        // Praezession in einem Jahrhundert [deg]
  double r1[3],v1[3];

  // Bahnelemente; Ekliptik und Aequinoktium J2000
      a =  1.000000; e = 0.016709; M0 = 357.5256; n  = 35999.3720;
      O = 174.876;   i = 0.0000;   w  = 102.9400; T0 = 0.0;
  // Zustandsvektor bezogen auf Ekliptik und Aequinoktium des Datums
  Ellip ( GM_SUN, M_PI/180.*(M0+n*(T-T0)), a, e, r1, v1 );  // bezogen auf Bahnebene
  GaussVec ( M_PI/180.*(O+p*T), M_PI/180.*i, M_PI/180.*(w-O), PQR ); // Transform. -> Ekliptik

  matrixVectMult(PQR,r1,r);                                        // Ekliptikale
  matrixVectMult(PQR,v1,v);                                        // Koordinaten

}


/*----------------------------------------------------------------------------*/
/* FUNCTION    : KalkPN                                                       */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void KalkPN( double t )
{
   double m1[3][3],m2[3][3],v[3],r[3];

   NutMatrix((t-51544.5)/36525., m1);
   PrecMatrix_Equ( 0.0 , (t-51544.5)/36525., m2);
// Nicht zum Jahr2000 sondern 1991.25
//   PrecMatrix_Equ( -0.089924709103 , (t-51544.5)/36525., m2);
   matrixProduct( m1, m2, pn_);

   Ecl2EquMatrix( (t-51544.5)/36525., m1 );
   VelocityEarth((t-51544.5)/36525.,r,v);
   matrixVectMult( m1,v,v_earth);
   v_earth[0] /= C_LIGHT;
   v_earth[1] /= C_LIGHT;
   v_earth[2] /= C_LIGHT;

}

/*----------------------------------------------------------------------------*/
/* FUNCTION    : ZeigeRA_DEC                                                  */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
void ZeigeRA_DEC(char *str,double ra, double f )
{
  int h_grd;
  int min;
  double sec;
  double h;

  h = ra/M_PI*f;
  h_grd = (int) h;
  h -= (double)h_grd;
  if( h < 0. )
    h *= (-1.);
  h *=60.;
  min = (int) h;
  h -= (double) min;
  h *= 60;
  sec = h;
  fprintf(stderr,"%s %4d %2d %8.3f\n",str,h_grd,min,sec);
}


double KalkGAST( double tMJD )
{
  double Secs = 86400.0;        // Anzahl der Sekunden je Tag
  double MJD_0, UT, T_0, T, gmst;
  double tau;
  double eqeq,d,eps,l,om,dpsi;

  MJD_0 = floor ( tMJD );
  UT    = Secs*(tMJD-MJD_0);     // [s]
  T_0   = (MJD_0-51544.5)/36525.0;
  T     = (tMJD  -51544.5)/36525.0;

/*
  gmst  = 24110.54841 + 8640184.812866*T_0 + 1.0027379093*UT
          + (0.093104-6.2e-6*T_0)*T_0*T_0;      // [sec]
*/
  gmst  = 24110.54841 + 8640184.812866*T_0 + 1.00273790935*UT
          + (0.093104-6.2e-6*T)*T*T;      // [sec]

  tau = (2.*M_PI/Secs)*Modulo(gmst,Secs);   // [Rad]

  d = tMJD - 51544.5;
  eps = (23.4393-0.0000004 * d) / 180. * M_PI;
  l = (280.47 + 0.98565*d) / 180. * M_PI;
  om = (125.04 - 0.052954*d) / 180. * M_PI;
  dpsi = -0.000319 * sin(om) - 0.000024*sin(2.*l);
  eqeq = dpsi * cos(eps);
  eqeq = eqeq*M_PI/12.;

  tau += eqeq;

  return tau;
}

double KalkGAST_GMST( double tMJD, double *rgmst, double *rdgmast )
{
  double Secs = 86400.0;        // Anzahl der Sekunden je Tag
  double MJD_0, UT, T_0, T, gmst;
  double tau;
  double eqeq,d,eps,l,om,dpsi;

  MJD_0 = floor ( tMJD );
  UT    = Secs*(tMJD-MJD_0);     // [s]
  T_0   = (MJD_0-51544.5)/36525.0;
  T     = (tMJD  -51544.5)/36525.0;

/*
  gmst  = 24110.54841 + 8640184.812866*T_0 + 1.0027379093*UT
          + (0.093104-6.2e-6*T_0)*T_0*T_0;      // [sec]
*/
  gmst  = 24110.54841 + 8640184.812866*T_0 + 1.00273790935*UT
          + (0.093104-6.2e-6*T)*T*T;      // [sec]

  tau = (2.*M_PI/Secs)*Modulo(gmst,Secs);   // [Rad]
  
  *rgmst = tau;

  d = tMJD - 51544.5;
  eps = (23.4393-0.0000004 * d) / 180. * M_PI;
  l = (280.47 + 0.98565*d) / 180. * M_PI;
  om = (125.04 - 0.052954*d) / 180. * M_PI;
  dpsi = -0.000319 * sin(om) - 0.000024*sin(2.*l);
  eqeq = dpsi * cos(eps);
  eqeq = eqeq*M_PI/12.;

  tau += eqeq;
  
  *rdgmast = eqeq;

  return tau;
}



/*============================================================================*/
/* EXPORTED SUB-PROGRAMS (body)                                               */
/*============================================================================*/


/*----------------------------------------------------------------------------*/
/* FUNCTION    : KalkLokalMeridian                                            */
/* DESCRIPTION :                                                              */
/* DATA IN     :                                                              */
/* DATA OUT    :                                                              */
/*----------------------------------------------------------------------------*/
double KalkLokalMeridian( double tMJD, double ra, double lam )
{
  double tau;

  tau = KalkGAST( tMJD );

#ifdef ADD_PRINT
  ZeigeRA_DEC( "GAST ",tau, 12. );
#endif

  tau += lam;
  if( tau > M_PI )
     tau -= 2.*M_PI;
  while( tau < 0.0 )
    tau += 2.*M_PI;

#ifdef ADD_PRINT
 ZeigeRA_DEC( "l.Sternzeit",tau, 12. );
#endif

  tau -= ra;
  while( tau < 0.0 )
    tau += 2.*M_PI;
  while( tau > 2.*M_PI )
    tau -= 2.*M_PI;

#ifdef ADD_PRINT
 ZeigeRA_DEC( "Stundenwinkel",tau, 12. );
#endif

  return tau;
}

void EciLD2Hor( double de, double tau, double lat, double * height, double * azimuth )
{
    double equ[3],hor[3];
    double mat[3][3],r;

    calcCart(tau,de,1.,equ);
    R_y((M_PI/2.-lat), mat);
    matrixVectMult(mat,equ,hor);

    calcPolarAngles(hor,azimuth,height,&r);

}

void Hor2EciLD( double height, double azimuth, double lat, double * de, double * tau )
{
    double hor[3],equ[3];
    double mat[3][3],r;

    calcCart (azimuth, height, 1., hor );
    R_y(-(M_PI/2.-lat), mat);
    matrixVectMult(mat,hor,equ);

    calcPolarAngles(equ,tau,de,&r);

}

void Eci2EciLD(double vec_in[3], double time, double vec_out[3], int flagAberration )
{
     double hv1[3],hv2[3];
     double ae2;

     KalkPN( time );

     matrixVectMult( pn_, vec_in, hv1 );

     if( flagAberration )
     {
         hv2[0] = hv1[0] + v_earth[0];
         hv2[1] = hv1[1] + v_earth[1];
         hv2[2] = hv1[2] + v_earth[2];

         ae2 = AbsVector(hv2);
         vec_out[0] = hv2[0] / ae2;
         vec_out[1] = hv2[1] / ae2;
         vec_out[2] = hv2[2] / ae2;
     }
     else
     {
         vec_out[0] = hv1[0];
         vec_out[1] = hv1[1];
         vec_out[2] = hv1[2];
     }
}

void EciLD2Ecef(double vec_in[3], double time, double vec_out[3] )
{
     double mat[3][3];
     double tau;

     tau = KalkGAST( time );

     // ob -tau oder tau verwendet werden muss, ist noch unklar
     R_z(tau, mat);

     matrixVectMult( mat, vec_in, vec_out );
}

void Eci2Ecef(double vec_in[3], double time, double vec_out[3] )
{
     double hv1[3];

     Eci2EciLD( vec_in, time, hv1, 0 );
     EciLD2Ecef( hv1, time, vec_out );
}

void Ecef2EciLD(double vec_in[3], double time, double vec_out[3] )
{
     double mat[3][3];
     double tau;

     tau = KalkGAST( time );

     // ob tau oder -tau verwendet werden muss, ist noch unklar
     R_z(-tau, mat);

     matrixVectMult( mat, vec_in, vec_out );

}

void EciLD2Eci(double vec_in[3], double time, double vec_out[3], int flagAberration )
{
     double hv1[3],hv2[3],mat[3][3];
     double ae2;
     double tau;

     KalkPN( time );

     if( flagAberration )
     {
         hv2[0] = vec_in[0];
         hv2[1] = vec_in[1];
         hv2[2] = vec_in[2];
         hv1[0] = hv2[0] - v_earth[0];
         hv1[1] = hv2[1] - v_earth[1];
         hv1[2] = hv2[2] - v_earth[2];

         ae2 = AbsVector(hv1);
         hv1[0] /= ae2;
         hv1[1] /= ae2;
         hv1[2] /= ae2;
     }
     else
     {
        hv1[0] = vec_in[0];
        hv1[1] = vec_in[1];
        hv1[2] = vec_in[2];
     }

     matrixTransposition( pn_, mat );
     matrixVectMult( mat, hv1, vec_out );

}



void Ecef2Eci(double vec_in[3], double time, double vec_out[3] )
{
#if 1
     double hv1[3];
     
     Ecef2EciLD(vec_in, time, hv1 );
     EciLD2Eci( hv1, time, vec_out, 0);
     
#else  
     double hv1[3],hv2[3],mat[3][3];
     double ae2;
     double tau;

     tau = KalkGAST( time );
     KalkPN( time );

     // ob tau oder -tau verwendet werden muss, ist noch unklar
     R_z(-tau, mat);

     matrixVectMult( mat, vec_in, hv2 );

     hv1[0] = hv2[0] - v_earth[0];
     hv1[1] = hv2[1] - v_earth[1];
     hv1[2] = hv2[2] - v_earth[2];

     ae2 = AbsVector(hv1);
     hv1[0] /= ae2;
     hv1[1] /= ae2;
     hv1[2] /= ae2;

     matrixTransposition( pn_, mat );
     matrixVectMult( mat, hv1, vec_out );
#endif
}

void KalkApparent(Stern* s)
{
    double e[3],e1[3],ae2,e2[3];
    double t, alp, det;

#ifdef ADD_PRINT
    ZeigeRA_DEC("ra2000",s->raJ2000_,12.);
    ZeigeRA_DEC("de2000",s->deJ2000_,180.);
#endif

    t = (s->zeitApp_ - 51544.5)/365.25;
    alp = s->raJ2000_ + s->eigenRA_*t/3600./12.*M_PI;
    det = s->deJ2000_ + s->eigenDE_*t/3600./180.*M_PI;

#ifdef ADD_PRINT
  ZeigeRA_DEC("ra2000 e",alp,12.);
  ZeigeRA_DEC("de2000 e",det,180.);
#endif

    e[0] = cos(det)*cos(alp);
    e[1] = cos(det)*sin(alp);
    e[2] = sin(det);

    matrixVectMult(pn_, e, e1);
    e2[0] = e1[0] + v_earth[0];
    e2[1] = e1[1] + v_earth[1];
    e2[2] = e1[2] + v_earth[2];

    ae2 = AbsVector(e2);
    e2[0] /= ae2;
    e2[1] /= ae2;
    e2[2] /= ae2;

    s->ra_ = atan(e2[1]/e2[0]);
    s->de_ = atan(e2[2]/sqrt(e2[0]*e2[0]+e2[1]*e2[1]));

    if (e2[0] < 0. && e2[1] > 0.0)
    {
        s->ra_ += M_PI;
    }
    if (e2[0] > 0. && e2[1] < 0.0)
    {
        s->ra_ = 2.*M_PI + s->ra_;
    }
    if (e2[0] < 0. && e2[1] < 0.0)
    {
        s->ra_ += M_PI;
    }

#ifdef ADD_PRINT
    ZeigeRA_DEC("ra_ Scheinbar",s->ra_,12.);
    ZeigeRA_DEC("de_ Scheinbar",s->de_,180.);
#endif
}

void KalkAzimutHoehe(Stern* s)
{
#if 1
    s->hoeheC_ = asin(cos(s->de_)*cos(s->lokalMeridian_)*cos(BreiteAP_) +
                      sin(s->de_)*sin(BreiteAP_));
    if( fabs(fabs(s->hoeheC_)-M_PI/2)<1.e-13)
    {
        s->azimutC_ = 0.;
    }
    else
    {
        if (fabs((sin(s->de_)-sin(BreiteAP_)*sin(s->hoeheC_))/(cos(s->hoeheC_)*cos(BreiteAP_)))>=1.)
        {
            s->azimutC_ = 0.;
        }
        else
        {
            s->azimutC_ = acos((sin(s->de_)-sin(BreiteAP_)*sin(s->hoeheC_))/(cos(s->hoeheC_)*cos(BreiteAP_)));
            if (s->lokalMeridian_ >= 0 && s->lokalMeridian_ < M_PI)
            {
                s->azimutC_ = 2*M_PI - s->azimutC_;
            }
        }
    }
#endif
#if 0
    s->hoeheC_ = asin(cos(s->de_)*cos(s->lokalMeridian_)*cos(BreiteAP_) +
                      sin(s->de_)*sin(BreiteAP_));
    s->azimutC_ = asin(cos(s->de_)*sin(s->lokalMeridian_)/cos(s->hoeheC_));
#endif
#if 0
    s->hoeheC_ = asin(cos(s->de_)*cos(s->lokalMeridian_)*cos(BreiteAP_) +
                      sin(s->de_)*sin(BreiteAP_));
    s->azimutC_ = atan(sin(s->lokalMeridian_)/(sin(BreiteAP_)*cos(s->lokalMeridian_)-cos(BreiteAP_)*tan(s->de_)));

#endif

}

void StarApparent(Stern* s, double laenge, double breite, double timeMjd)
{

    KalkPN(timeMjd);
    BreiteAP_=breite;
    s->zeitApp_ = timeMjd;
    KalkApparent(s);
    s->zeitMess_ = s->zeitApp_;
    s->lokalMeridian_ = KalkLokalMeridian(s->zeitMess_ , s->ra_, laenge);
    KalkAzimutHoehe(s);

}



void strLosCalcD( double tMJD, double qs, double q1, double q2, double q3, double los[3] )
{
    double brf[3], m[3][3];
    double t;
    struct Quaternion Q;

    brf[0]=0.;
    brf[1]=0.;
    brf[2]=1.;

    Q.r=qs;
    Q.x=q1;
    Q.y=q2;
    Q.z=q3;

    rotateVector(brf, &Q, brf);
//    printf("BRF  LOS  :  %16.6f %16.6f %16.6f\n",brf[0],brf[1],brf[2]);

    if( tMJD < 0. )
    {
       los[0] = brf[0];
       los[1] = brf[1];
       los[2] = brf[2];
    }
    else
    {
       t = (tMJD-51238.)/36525.;
       PrecMatrix_Equ (0., t, m);
       matrixVectMult( m,brf,los);
    }

    t=sqrt(los[0]*los[0]+los[1]*los[1]+los[2]*los[2]);
    los[0] /= t;
    los[1] /= t;
    los[2] /= t;
}

void los2RaDeD( double los[3], double *ra, double *de )
{
   double phi,thet,lv[3],ent;
   int i;

   ent=AbsVector(los);
   for(i=0;i<3;i++)
     lv[i] = los[i]/ent;

   phi = atan(lv[1]/lv[0]);
   if( lv[0] < 0. )
   {
      if( lv[1] >= 0. )
      {
         phi += M_PI;
      }
      else
      {
         phi -= M_PI;
      }
   }
   if( phi < 0. )
   {
      phi += M_PI*2.;
   }
   thet = asin(lv[2]);

   *ra = phi*180./M_PI;
   *de = thet*180./M_PI;

   return;
}

void quad2RaDeRollD( double qIs, double qI1, double qI2, double qI3, double *ra, double *de, double *ro )
{
    double rightAsc=-500.;
    double decl=-500.;
    double roll=-500.;
    double h=-500.;
    double q1= qI1;
    double q2= qI2;
    double q3= qI3;
    double q0= qIs;
    double sq0 = q0*q0;
    double sq1 = q1*q1;
    double sq2 = q2*q2;
    double sq3 = q3*q3;

    h=sq0-sq1-sq2+sq3;
    if( h <-0.9999999999999999999999)
    {
       h=-1.0 ;
    }
    else if( h > 0.9999999999999999999999)
    {
      h=1.0;
    }
    decl=asin(h);


    if( (h != -1.0) && (h!=1.0))
    {
       h=atan2((q2*q3-q0*q1),(q1*q3+q0*q2));
       if( h < 0.)
       {
         h=h+2.0*M_PI;
       }
       if( (fabs(h) < 0.000001) || (fabs(h-2.0*M_PI) < 0.000001) )
       {
         rightAsc=0.0;
       }
       else
       {
          rightAsc=h;
       }
       h=atan2((q2*q3+q0*q1),(q0*q2-q1*q3));
       if( h < 0.0 )
       {
          h=h+2.0*M_PI;
       }
       if( (fabs(h) < 0.000001) || (fabs(h-2.0*M_PI) < 0.000001))
       {
         roll=0.0;
       }
       else
       {
          roll=h;
       }
    }
    else
    {
        rightAsc=0.0;

        h=atan(2.0*(q1*q2+q0*q3)/(sq0-sq1+sq2-sq3));
        if( h < 0.0)
        {
          h=h+2.0*M_PI;
        }
        if( (fabs(h) < 0.000001) || (fabs(h-2*M_PI) < 0.000001))
        {
          roll=0.0;
        }
        else
        {
           roll=h;
        }
    }

   *ra = rightAsc*180./M_PI;
   *de = decl*180./M_PI;
   *ro = roll*180./M_PI;

   return;
}


void ecef2lla(double vec[3], double *lon, double *lat, double *h)
{
    double p = sqrt(vec[0]*vec[0]+vec[1]*vec[1]);
    double thet = atan(vec[2]*el_a/(p*el_b));
    double st = sin(thet);
    double ct = cos(thet);

    *lon = atan(vec[1]/vec[0]);

    *lat = atan((vec[2]+el_es*el_es*el_b*st*st*st)/(p-el_e*el_e*el_a*ct*ct*ct));

    double slat = sin(*lat);
    double N = el_a/sqrt(1.-el_e*el_e*slat*slat);
    *h = p/cos(*lat)  - N;

}

void lla2ecef(double lon, double lat, double h, double vec[3])
{
    double slat = sin(lat);
    double N = el_a/sqrt(1.-el_e*el_e*slat*slat);
//    double he = sqrt((el_a*el_a-el_b*el_b)/el_a/el_a);
// printf("el_e : %20.16e\n",he);    
//    double N = el_a/sqrt(1.-he*he*slat*slat);
    
    double slon = sin(lon);
    double clon = cos(lon);
    double clat = cos(lat);


    vec[0] = (N+h)*clat*clon;
    vec[1] = (N+h)*clat*slon;
    vec[2] = (el_b*el_b*N/el_a/el_a+h)*slat;
}

/**
 * Computes the velocity of Earth in the mean equatorial coordinate system of J2000 for modifiedJulianDate.
 * This is the coordinate system of the J2000 star catalog.
 * @param modifiedJulianDate modified Julian date
 * @param velocity Earth's velocity, in the units of speed of light
 */
void velocityOfEarth(double modifiedJulianDate, double velocity[3])
{

    // modified Julian date of the J2000 (catalog) epoch
    Zeit zeitJ2000;
    zeitJ2000.jahr_ = 2000;
    zeitJ2000.monat_ = 1;
    zeitJ2000.tag_ = 1;
    zeitJ2000.stunde_ = 12;
    zeitJ2000.minute_ = 0;
    zeitJ2000.sekunde_ = 0.0;
    KalkMJD(&zeitJ2000);
    double modifiedJulianDateJ2000 = zeitJ2000.zeitMjd_;

    // time in Julian centuries since J2000
    double t = (modifiedJulianDate - modifiedJulianDateJ2000) / (365.25 * 100.0);

    // position and velocity in the ecliptic coordinate system of date
    double positionEcl[3];
    double velocityEcl[3];
    VelocityEarth(t, positionEcl, velocityEcl);

    // transformation to the equatorial coordinate system of date
    double transformationMatrix[3][3];
    Ecl2EquMatrix(t, transformationMatrix);
    double velocityEqu0[3];
    matrixVectMult(transformationMatrix, velocityEcl, velocityEqu0);

    // transformation to the equatorial coordinate system of J2000
    PrecMatrix_Equ(t, 0.0, transformationMatrix);
    matrixVectMult(transformationMatrix, velocityEqu0, velocity);

    // units of speed of light
    velocity[0] /= C_LIGHT;
    velocity[1] /= C_LIGHT;
    velocity[2] /= C_LIGHT;

    printf("%.17e %.17e %.17e %.17e %.17e %.17e %.17e\n", t, velocityEqu0[0], velocityEqu0[1], velocityEqu0[2], velocity[0], velocity[1], velocity[2]);

}

void velocityOfEarthSimple(double modifiedJulianDate, double velocity[3])
{
    KalkPN( modifiedJulianDate );
    velocity[0] = v_earth[0];
    velocity[1] = v_earth[1];
    velocity[2] = v_earth[2];
}
