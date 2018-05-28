/****** MTREXAPI.H ************** Gorbunov A.V. ****** 05/03/14 ****
******* MTREXAPI.H ************** Tarakanova I.R. **** 05/10/16 ****
******* MTREXAPI.H ************** Dishlenko S.G.****** 14/12/09 ****
******* MTREXAPI.H ************** Gustinovich N.A. *** 12/12/07 ****
******* MTREXAPI.H ************** Shabakov D.A.    *** 22/05/09 ****
******* MTREXAPI.H ************** Borzov A.Y.      *** 20/05/15 ****
******* MTREXAPI.H ************** Belenkov O.V.    *** 25/07/10 ****
******* MTREXAPI.H ************** Kruzhkov A.E.    *** 12/11/15 ****
******* MTREXAPI.H ************** Zheleznyakov V.A.*** 06/06/16 ****
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*          ������� ���������� (GIS\GSS)MAPMTREX.DLL                *
*                                                                  *
*******************************************************************/

#ifndef MTREXAPI_H
#define MTREXAPI_H

#include "maptype.h"                 // 17/03/07

#ifndef MAPCREAT_H
  #include "mapcreat.h"              // 18/12/07
#endif

#ifdef WIN32API                      // 17/03/07
#define HMESSAGE HWND
#else
#define HMESSAGE MSGHANDLER
#endif

#ifdef LINUXAPI                      // 04/02/14
 #define MTREXPORT _export WINAPI
#else
 #define MTREXPORT __declspec( dllexport ) WINAPI
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++  ��������������� ���������  ++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 // ���������� ��������������� ������ �������������
 // ����������� �������

 typedef struct PRIORMTRPARM
 {
   int    Length;              // ������ ������ ��������� :
                               //  sizeof (PRIORMTRPARM) = 64
   int    Free;                // ������ ���� ����

   double AbsHeightDifference; // ������ ��������� ����� - ����������
                               // �������� �������� ����� ��������
                               // ���������� � �������� ������� (�����)

   double Reserve[6];          // ������ ���� ����
 }
   PRIORMTRPARM;



// ��������� ���������� �������� ������� ������� ����������  // 28/01/09

typedef struct SPREADPARM
{
  int         Length;       // ����� ������ ��������� SPREADPARM
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int         Free;         // ������ ���� ����
#endif
  HMESSAGE    hWnd;         // ������������� ���� �������, �������� ����������
                            // ��������� 0x0581 � �������� ����������� ����� (� WPARAM),
                            // ���� ������� ������ ���� ������������� ��������, � �����
                            // ������ ��������� �������� 0x0581.
                            // ���� Handle ����� ���� - ��������� �� ����������.

  int         IterCount;    // ���������� ��������
                            // (��� ������ ��������, ��� ������ ����������� ���)
  COLORREF    Palette[256]; // ������� ����������� ������� �������
  int         PaletteCount; // ���������� ������ � �������
  int         IsIterMtq;    // ������� �������� ������ �� ������ ��������
  int         IsAllEject;   // ������� �������������� �������
                            // (���� 0, �� ���� ����������� �� ����� ��������)

  double      EjectSize;    // ����� ������� �������� � ������ �����.
  double      AbsorbHeight; // ������� ������, ����������� � ����� � ������
  double      ElemSize;     // ������ �������� ����������� ������� � ������
  double      WaveHeight;   // ������ �����

  DOUBLEPOINT Point;        // ����� �������

  char        Reserve[64];  // ������ ���� ����
}
  SPREADPARM;



// ��������� ������ ������ �������� ������� �����-��������� ���������    // 22/05/09

typedef struct WZONEPARM
{
  int      Length;        // ����� ������ ��������� WZONEPARM
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int      Free;          // ������ ���� ����
#endif
  HMESSAGE Wnd;           // ������������� ���� �������, �������� ����������
                          // ��������� 0x0581 � �������� ����������� ����� (� WPARAM),
                          // ���� ������� ������ ���� ������������� ��������, � �����
                          // ������ ��������� �������� 0x0581.
                          // ���� Handle ����� ���� - ��������� �� ����������.

  HMAP     Map;           // ������������� �������� �������� �����
  HSELECT  Select;        // ����� ��������, ��� ������� ����������� ����������
  DFRAME   Frame;         // ������� ����������

  double   ElemSize;      // ������ �������� � ������
  double   dH;            // ������ �� ������ ��� ���������� 
                          // ������������� ������� �����

  char     Reserved[64];  // ������ ���� ����
}
  WZONEPARM;


// ��������� ���������� ������� ������ (MTQ)

typedef struct DEPTHMTQPARM
{
  int    StructSize;      // ������ ������ ��������� : sizeof (DEPTHMTQPARM) = 256 ����
  int    Free;            // ������ ���� ����

  int    MatrixType;      // ��� �������� ������� �������:
                          //  1 - ������� ����� (mtw)
                          //  2 - ������� ������� (mtq)

  int    MatrixNumber;    // ����� ������� � �������

  double BeginX;          // ������������� ���������� ������
  double BeginY;          // (���-��������� ����) ������� � ������

  double Width;           // ������ ������� � ������
  double Height;          // ������ ������� � ������

  double MinValue;        // �������� �������� ������ ����������� �������,
  double MaxValue;        // ���� MinValue >= MaxValue � ������� ���������
                          // ����������� �������� ��������

  double Level;           // ���������� ������ �������������� �����������
                          // ��� ���������� ������, ��������� � �������

  double ElemSizeMeters;  // ������ ������� �������� ������� ������
                          // � ������ �� ��������� (������� �������)

  int    UserLabel;       // ������������ �����, ����������� � ����������� ��������
                          //  (���, �������������� �������)
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int    Free1;           // ������ ���� ����
#endif

  HWND   Handle;          // ������������� ���� �������, �������� ����������
                          // ��������� 0x0581 � �������� ����������� ����� (� WPARAM),
                          // ���� ������� ������ ���� ������������� ��������, � �����
                          // ������ ��������� �������� 0x0581.
                          // ���� Handle ����� ���� - ��������� �� ����������.

  HOBJ   Border;          // ������������� ���������� ������� �����, ���������������
                          // ������� ����������� ��������� ������� (���� ����� ����,
                          // �� �� ������������). ���� ������ ���������� ��� ���������
                          // �������, ������������ ���������� ����� BeginX, BeginY,
                          // Width, Height ������ ���������, �� �� ������������.

#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
#else
  int    Free2;           // ������ ���� ����
#endif

  char   Reserve[128];    // ������ ���� ����

  char   UserName[32];    // �������� ��� ������� (�������� �������������� ��������)
}
  DEPTHMTQPARM;


// ��������� ���������� ���������� �� �������

typedef struct CALCMATRIXPARM
{
  int    StructSize;      // ������ ������ ��������� : sizeof (CALCMATRIXPARM) = 264 ����
  int    Free;            // ������ ���� ����

  int    MatrixType;      // ��� �������� �������:
                          //  1 - ������� ����� (mtw)
                          //  2 - ������� ������� (mtq)

  int    MatrixNumber;    // ����� ������� � �������

  double BeginX;          // ������������� ���������� ������
  double BeginY;          // (���-��������� ����) ������� ���������� � ������

  double Width;           // ������ ������� ���������� � ������
  double Height;          // ������ ������� ���������� � ������ ( ���� Width ����� ����
                          // ��� Height ����� ����, �� ������� ���������� ������������
                          // ���������� �������� �������

  double MinValue;        // �������� �������� ��������� �������, ����������� � �����������.
  double MaxValue;        // ���� MinValue >= MaxValue � ����������� ��������� ��� ��������

  double ElemSizeMeters;  // ������� ���������� � ������
                          // (���� ����� ����, �� ������������ ������� �������)

  double Level;           // ������ ������ �������������� ��������� (���������)
                          // ��� ���������� ������ (������������ ��� CalcVolume == 1)

  HWND   Handle;          // ������������� ���� �������, �������� ����������
                          // ��������� 0x0581 � �������� ����������� ����� (� WPARAM),
                          // ���� ������� ������ ���� ������������� ��������, � �����
                          // ������ ��������� �������� 0x0581.
                          // ���� Handle ����� ���� - ��������� �� ����������.

  HOBJ   Border;          // ������������� ���������� ������� �����, ���������������
                          // ������� ���������� ��� ���������� ��������� �������
                          // (���� ����� ����, �� �� ������������). ���� ������ 
                          // ���������� ��� ��������� ������� ����������, ������������
                          // ���������� ����� BeginX, BeginY, Width, Height
                          // ������ ���������, �� �� ������������.

  // ���� (������) ����������:
  //---------------------------------------------
  char   CalcSquare;      // ���������� �������
  char   CalcVolume;      // ���������� �����
  char   CalcMinimun;     // ���������� ����������� ��������
  char   CalcMaximun;     // ���������� ������������ ��������
  char   CalcAverage;     // ���������� �������������������� ��������
 
  char   CalcSquareWater; // ���������� ������� ������� ������� 
                          // (�������������� ��������� � ���������� ������� LevelWater) 
                          // � ������� ���������� - SquareShallowWater

  char   CalcVolumeLayer; // ���������� ����� ���� ����� �������� 
                          // LayerTop (�������) � LayerBottom (������)
 
  char   CalcTypeReserve; // ������ ��� ����� ����������
  //---------------------------------------------


  // ���������� ����������:
  //-----------------------------------------------------------
  double Square;          // �������
  double Volume;          // �����

  double Minimun;         // ����������� ��������
  double Maximun;         // ������������ ��������
  double Average;         // �������������������� ��������

  double SquareWater;     // ������� ������� ������� ������ LevelWater

  double SquareShallowWater;  // ������� ���������� ������ LevelWater
                              // ����������:   2 � >= ������� >= 1 ��

  double VolumeLayer;     // ����� ���� ����� �������� LayerTop � LayerBottom
  //-----------------------------------------------------------

  double LevelWater;      // ������ ������ �������������� ��������� ������� �������
                          //  (������������ ��� CalcSquareWater == 1)

  double LayerTop;        // ������ �������� ������ ����
                          //  (������������ ��� CalcVolumeLayer == 1)

  double LayerBottom;     // ������ ������� ������ ����
                          //  (������������ ��� CalcVolumeLayer == 1)

  char   Reserve[80];     // ������ ���� ����
}
  CALCMATRIXPARM;


// ��������� ���������� ���� ����������          // 30/08/10

typedef struct BUILDZONEFLOODPARM
{
  int         Length;       // ����� ������ ��������� BUILDZONEFLOODPARM
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int         Free1;        // ������ ���� ����
#endif
  HWND        Handle;       // ������������� ���� �������, �������� ����������
                            // ��������� 0x0590 � �������� ����������� ����� (� WPARAM),
                            // ���� ������� ������ ���� ������������� ��������, � �����
                            // ������ ��������� �������� 0x0590.
                            // ���� Handle ����� ���� - ��������� �� ����������.

  DOUBLEPOINT Point1;       // ���������� ������ �����, � ������� ������ ������� ������� ����
  DOUBLEPOINT Point2;       // ���������� ������ �����, � ������� ������ ������� ������� ����
                            // ���������� �������� � ������ � ������� ��������� ��������� �����

  double      Height1;      // ������� ������� ���� ������ �����
  double      Height2;      // ������� ������� ���� ������ �����
  double      Width;        // ������ ���� ����������
  double      ElementSize;  // ������ ������� �������� ������� � ������ �� ���������

  HOBJ        Object;       // ������ (����), �� ������� ����������� ����� ������� ����

  int         Active;       // 0 - �� ��������� ������� ���� ����������
                            // 1 - ���������, ������ ������������
                            // 2 - ���������, �� ������ ������������
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int         Free2;        // ������ ���� ����
#endif
  char        Reserve[64];  // ������ ���� ����
} 
  BUILDZONEFLOODPARM;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++  ������� ���������� MAPMTREX.DLL  +++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{

 // ���������� �������� ���������� ������ (point->H) � ��������
 // ����� (point->X,point->Y) �� ������ ��������� �����.
 // ���������� ����� �������� � ������ � ������� ���������
 // ��������� �����.
 // � ������ ������ ��� ���������� ������ ���������� 0.

long int MTREXPORT mtrCalcAbsoluteHeight(HMAP hMap,XYHDOUBLE* point);

 // ���������� �������� ���������� ������ � ��������
 // ����� (point->X,point->Y) �� ������ ��������� �����.
 // ���������� ����� �������� � ������ � ������� ���������
 // ��������� �����.
 // sectorcount - ���������� ����������� ��� ������ ���������� �����
 //  (������ ���� ������ 4, ����������� ���������� ����������� = 4,
 //   ������������ = 256).
 // ���������� �������� ������ � ������.
 // � ������ ������ ��� ���������� ������ ���������� ERRORHEIGHT.

double MTREXPORT mtrCalcAbsoluteHeightBySectors(HMAP hMap,
                                                DOUBLEPOINT* point,
                                                long int sectorcount);

 // ���������� �������� �������������� � �������� �����
 // �� ������ ��������� �����.
 // �������������� �������� ����� ��������� - semanticCode.
 // ���������� ����� (point->X,point->Y) �������� � ������ �
 // ������� ��������� ��������� �����.
 // ����������� �������� �������������� ��������� � value.
 // flagSelect - ���� ������������� ������� ������ �������� �����.
 // ���� flagSelect = 0, �� ����������� ����� �������� ��������������
 // �� ���� �������� ��������� �����.
 // ���� flagSelect = 1, �� ����� �������� �������������� �����������
 // ������ �� ��������, ��������������� �������� ������ (HSELECT),
 // ������������� ��� ��������� �����.
 // � ������ ������ ���������� 0

long int MTREXPORT mtrCalcCharacteristic(HMAP hMap,
                                         DOUBLEPOINT* point,
                                         long int semanticCode,
                                         long int flagSelect,
                                         double*  value);

  // ��������������� ������ ������������� �������, �����������
  // �� ��������� ����� �� �������� ������� ������ �����.
  // � �������� ������ ����������� �������������� ��������
  // ��������� ������ ������ � ��������� ���.
  // ��� ������ ���������� ����.
  // hMap    - �������� ����� ��� ���������� �������,
  // filtername - ������ ��� ������� ��������
  //   ������ � ������ ����� ������������� ������ �������� -
  //   ��������� ���� MTRCREA.IMH, ���������� �������� �����
  //   ��������, ������������ ��� ���������� ������� (��. MAPAPI.DOC)
  //   ���� filtername ����� ���� - ������ �������� �� ������������.
  // buildparm - ��������� ����������� �������,
  // priorparm - ���������� ��������������� ������,
  // handle   - ������������� ���� �������, �������� ����������
  // ��������� � ���� �������� :
  //   0x0581 - ��������� � �������� ����������� ����� (� WPARAM),
  //   ���� ������� ������ ���� ������������� ��������, � �����
  //   ������ ��������� �������� 0x0581.
  //   ���� handle ����� ���� - ��������� �� ����������.

long int MTREXPORT mtrTryBuild(HMAP hMap,
                               const char * filtername,
                               BUILDMTW * buildparm,
                               PRIORMTRPARM * priorparm,
                               HMESSAGE handle);


 // ���������� �������� ������������� ������ � �����������(������) �������������
 // ������ � �������� ����� (point) �� ������ ������� �����.
 // ���������� ����� �������� � ������ � ������� ��������� ��������� �����.
 // ����������:
 //  incline - ����� � ��������
 //  azimuth  - ������ ��������
 // � ������ ������ ��� ���������� ���������� 0.

long int MTREXPORT  mtrCalcInclineInPoint(HMAP hMap,
                                          DOUBLEPOINT * point,
                                          double * incline,
                                          double * azimuth);


 // ���������� ������ ������� �� ��������� ����� �� ��������
 // ������� ������ �����
 // ��� ������ ���������� ����
 // hMap    - �������� ����� ��� ���������� ������,
 // rstname - ������ ��� ������������ ������,
 // filtername - ������ ��� ���������� ���������� �����
 //   ������ � ������ ������ ������������� ������ �������� -
 //   ��������� ��������� ���� M�P2RSW.INI, ���������� �������� �����
 //   ��������, ������������ ��� ���������� ������
 // mtrparm - ��������� ������������ ������,
 // handle   - ������������� ���� �������, �������� ����������
 // ��������� � ���� �������� :
 //   0x0581 - ��������� � �������� ����������� ����� (� WPARAM),
 //   ���� ������� ������ ���� ������������� ��������, � �����
 //   ������ ��������� �������� 0x0581.
 // ���� handle ����� ���� - ��������� �� ����������.

long int MTREXPORT mtrBuildRaster(HMAP hMap,
                                  const char * rstname,
                                  const char * filtername,
                                  BUILDMTW * rstparm,
                                  HMESSAGE handle);


 // ���������� ���� ���������� �� ������ ������� ������ ����.
 // � ���������� ���������� ����������� ������� �������, ��������
 // ������� �������� ������� � ���� ����������.
 // �������� ������� ������� ������������ ������������ ����� �
 // ��������� ������ ���� (������ pointArray) � ��������� ����������
 // ��������� ������� (areaExtension).
 // hMap    - �������� ����� ��� ���������� ����,
 // mtqName - ������ ��� ����������� ������� �������,
 // pointArray - ����� ������� ����� � ��������� ������ ����
 //   ���������� ����� (pointArray->X,pointArray->Y) � �������� ������
 //   (pointArray->H) �������� � ������ � ������� ��������� ���������
 //   �����,
 // pointCount - ����� ����� � ������� pointArray
 //   ������ � ������ �������, ��������� ������� pointArray, ������
 //   ���� �� ����� pointCount * sizeof(XYHDOUBLE), � ��������� ������
 //   �������� ������ ������ � �������,
 // areaExtension - ������������� �����, �������� ��������
 //   ���������� ��������� ������� � ������,
 // minDepth - ������������� �����, �������� ����������� �������
 //   ���� ���������� � ������ (�������, ������� minDepth � �������
 //   ������� �� ���������),
 // handle - ������������� ���� �������, �������� ����������
 // ��������� � ���� �������� :
 //   0x0581 - ��������� � �������� ����������� ����� (� WPARAM),
 //   ���� ������� ������ ���� ������������� ��������, � �����
 //   ������ ��������� �������� 0x0581.
 //   ���� handle ����� ���� - ��������� �� ����������.

long int MTREXPORT mtrBuildFloodZone(HMAP hMap,
                                     const char * mtqName,
                                     XYHDOUBLE * pointArray,
                                     long int pointCount,
                                     double areaExtension,
                                     double minDepth,
                                     HMESSAGE handle);


 // ���������� ���� ���������� �� ������� ������� �������.
 // hMap - �������� �����, ������������ ������� � �������,
 // parm - ��������� ���������� ���� ����������.
 // mtqname - ������ ��� ����������� ������� �������
 // sitename - ��� ���������������� ����� ��� ������ �������� - ��� ����������
 // � ���������� ���������� ����������� ������� �������, ��������
 // ������� �������� ������� � ���� ����������.
 // � ������ ��������� ���������������� ����� sitename � ��������������� service.rsc.
 // ������������� service.rsc ������ ���������� � ����� �������� � ����������� ��� � hMap.
 // ���� ������ sitename �  Active > 0 (�������� Active �� BUILDZONEFLOODPARM - ���� 
 // �������� ��������), ���������������� ����� ����� �������� �� ����
 // hPaint - ������������� ��������� ����������� ��� �������������� ������ �������,
 //          ��������� �������� mapCreatePaintControl, ������������� - mapFreePaintControl
 // � ������ ������ ���������� 0.

long int MTREXPORT mtrFloodZoneByObject(HMAP hMap,
                                        const char * mtqname,
                                        const char * sitename,
                                        BUILDZONEFLOODPARM * parm);

long int MTREXPORT mtrFloodZoneByObjectUn(HMAP hMap,                    // 20/11/14
                                          const WCHAR * mtqname,
                                          const WCHAR * sitename,
                                          BUILDZONEFLOODPARM * parm);

long int MTREXPORT mtrFloodZoneByObjectEx(HMAP hMap,
                                          const WCHAR * mtqname,
                                          const WCHAR * sitename,
                                          BUILDZONEFLOODPARM * parm, HPAINT hPaint);

 // ���������� ������� ������� �� ������� �������� �������������� ��������.
 // hMap - �������� ����� ��� ���������� ������� �������,
 // mtqName - ������ ��� ����������� ������� �������,
 // palette - ����� ������� ����������� ������� �������,
 // countpalette - ���������� ������ � �������,
 // pointArray - ����� ������� �������� �������������� ��������
 //   ���������� ����� (pointArray->X,pointArray->Y) �������� � ������
 //   � ������� ��������� ��������� �����,
 // pointCount - ����� ����� � ������� pointArray
 //   ������ � ������ �������, ��������� ������� pointArray, ������
 //   ���� �� ����� pointCount * sizeof(XYHDOUBLE), � ��������� ������
 //   �������� ������ ������ � �������,
 // elemSizeMeters - ������ ������� ������������� ������� � ������ �� ���������
 //                  (������� �������)
 // minValue,maxValue - �������� �������� �������������� �������� ����������� �������
 //                     �������, ���� minValue >= maxValue - � ������� ���������
 //                     ����������� �������� �������� �� ������� pointArray
 // handle - ������������� ���� �������, �������� ����������
 //   ��������� � ���� �������� :
 //   0x0581 - ��������� � �������� ����������� ����� (� WPARAM),
 //   ���� ������� ������ ���� ������������� ��������, � �����
 //   ������ ��������� �������� 0x0581.
 //   ���� handle ����� ���� - ��������� �� ����������.

long int MTREXPORT mtrBuildMtq(HMAP hMap,
                               const char * mtqName,
                               const COLORREF* palette,
                               long int countpalette,
                               const XYHDOUBLE * pointArray,
                               long int pointCount,
                               double elemSizeMeters,
                               double minValue,
                               double maxValue,
                               HMESSAGE handle);

 // ���������� ������� ����������� (������� ������� ��� ������� �����)
 // �� ������ ��������� �����. ���� mtrparm->FileMtw ����� 1, �� ��������
 // ������� ����� (*.mtw), ����� �������� ������� ������� (*.mtq).
 // hmap - �������� ����� ��� ���������� �������
 // mtrname - ������ ��� ����������� �������
 // mtrparm - ��������� ����������� ������� (��������� BUILDSURFACE ������� � maptype.h)
 // ��� ������ ���������� 0.

long int MTREXPORT mtrBuildMatrixSurface(HMAP hmap,
                                         const char * mtrname,
                                         BUILDSURFACE * mtrparm);

long int MTREXPORT mtrBuildMatrixSurfaceUn(HMAP hmap,               // 17/02/14
                                           const WCHAR * mtrname,
                                           BUILDSURFACE * mtrparm);

 // ��������� � ������� ������� ���� ����� ��������� �������
 // hMap - ������������� �������� ��������� �����
 // number - ����� ������� ������� � �������
 // infoLine - �������� ������
 // width - ������ ���� � ������
 // value - ��������, ��������� � �������� ����
 // regime - ����� ��������� �������� (0 - ��� ����� ����� ���������� ��������)
 // � ������ ������ ���������� 0

long int MTREXPORT mtrPutMtqLineZone(HMAP hMap,
                                     long int number,
                                     HOBJ infoLine,
                                     double width,
                                     double value,
                                     long int regime);

 // ��������� � ������� ������� ���� ����� ��������� �������
 // � �������� ���������� �������
 // hMap - ������������� �������� ��������� �����
 // number - ����� ������� ������� � �������
 // infoLine - �������� ������
 // infoPolygon - ��������� ������
 // width - ������ ���� � ������
 // valueZone - ��������, ��������� � �������� ����
 // valuePolygon - ��������, ��������� � �������� ���������� �������
 // regime - ����� ��������� �������� (0 - ��� ����� ����� ���������� ��������)
 // � ������ ������ ���������� 0

long int MTREXPORT mtrPutMtqLineZoneForPolygon(HMAP hMap,       // 26/06/08
                                               long int number,
                                               HOBJ infoLine,
                                               HOBJ infoPolygon,
                                               double width,
                                               double valueZone,
                                               double valuePolygon,
                                               long int regime);

 // �������� ������� ������� ���������� ��������         // 28/01/09
 // ����������� �������� ������� �������� ������� ����
 // ����������� ��������
 // hmap    - ������������� �������� ������ (������ ���� ������� ���� �� ���� ������� �����)
 // mtqname - ��� ����������� ������� ������� ����������, ���� ������� ��������� �� ������ ��������,
 //           �� � ����� ����� ����������� ����� �������� (��� ������ = MtqName_1.mtq)
 // parm    - ��������� ������
 // ��� ������ ���������� ����

long int MTREXPORT mtrLiquidSpreading(HMAP hMap, const char *mtqname, SPREADPARM *parm);
long int MTREXPORT mtrLiquidSpreadingUn(HMAP hMap, const WCHAR *mtqname, SPREADPARM *parm);  // 17/02/14

 // ���������� ������� ���� �� ������� �������
 // hMap - ������������� �������� ��������� �����
 // number - ����� ������� ������� � �������
 // minValue,maxValue - ������ �������� �������� ���������,
 // ����������� � ���������� �������
 // ���� minValue > maxValue, �� ������� ����������� �� ����
 // ���������� ��������� �������
 // ����������� �������� ������� ��������� � zoneSquare.
 // � ������ ������ ���������� 0

long int MTREXPORT mtrCalcMtqZoneSquare(HMAP hMap,
                                        long int number,
                                        double minValue,
                                        double maxValue,
                                        double* zoneSquare);


 // �������������� ������� ����� (MTW) ��� ������� ������� (MTQ) � �������� ��������
 //   handle  - ������ ����������� ������������� �������� ���������,
 //   namein  - ��� �������� �������,
 //   nameout - ��� �������� �������,
 //   mapreg  - ����� ��������� � ������� � �������� ��������,
 //   datum   - ��������� ��������� ������������� ��������� � ��������� ����������
 //             �� ��������� WGS-84 (����� ���� ����),
 //  ellparam - ��������� ����������������� ���������� (����� ���� ����).
 //  ttype    - ��� ���������� �������������� ��������� (��. TRANSFORMTYPE � mapcreat.h) ��� 0
 //  tparm    - ��������� ���������� �������������� ��������� (��. mapcreat.h)
 //
 // �������� �������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM - mapcreat.h
 // ������� ����������� ������������� �������� ��������� ���������� ���������:
 //   -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
 //      WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
 //      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
 //
 // ��� ������ ���������� ����, ��� ������ ������������ ��������
 // picexGetLastError (���� ������ - maperr.rh)

 long int MTREXPORT
 MtwProjectionReformingPro(HMESSAGE handle,                  // 05/10/16
                          const WCHAR * namein,
                          const WCHAR * nameout,
                          MAPREGISTEREX * mapreg,
                          DATUMPARAM * datum,
                          ELLIPSOIDPARAM * ellparam,
                          long int ttype,
                          LOCALTRANSFORM * tparm);

 long int MTREXPORT
 MtwProjectionReformingEx(HMESSAGE handle,
                          const char * namein,
                          const char * nameout,
                          MAPREGISTEREX * mapreg,
                          DATUMPARAM * datum,
                          ELLIPSOIDPARAM * ellparam);

 long int MTREXPORT
 MtwProjectionReformingUn(HMESSAGE handle,                  // 18/02/14
                          const WCHAR * namein,
                          const WCHAR * nameout,
                          MAPREGISTEREX * mapreg,
                          DATUMPARAM * datum,
                          ELLIPSOIDPARAM * ellparam);

 long int MTREXPORT
 MtwProjectionReforming(HMESSAGE handle, const char * namein,
                        const char * nameout, MAPREGISTEREX * mapreg);

 // C������� ������� �����-��������� ���������
 // ������� ������� ������� �������� ���� �������, � �������� ��������� �������
 // mtqname - ��� ����������� ������� �����-��������� ���������
 // parm    - ��������� ������
 // ��� ������ ���������� ����

long int MTREXPORT mtrWaterZone(const char *mtqname, WZONEPARM *parm);
long int MTREXPORT mtrWaterZoneUn(const WCHAR *mtqname, WZONEPARM *parm);  // 17/02/14

 // ���������� ������� ������ (������� ������� mtq)
 // hmap - �������� ����� ��� ���������� �������,
 // ������������ ������� � ������� ���
 // depthmtqname - ������ ��� ����������� �������
 // depthmtqparm - ��������� ����������
 // palette - ����� ������� ����������� �������
 //  (���� ����� ����, ������������ ������� �� ���������)
 // paletteCount - ����� ������ �������
 // ��� ������ ���������� 0.

long int MTREXPORT mtrBuildDepthMtq(HMAP hmap,
                                    const char * depthmtqname,
                                    DEPTHMTQPARM * depthmtqparm,
                                    COLORREF * palette,
                                    long int paletteCount);

long int MTREXPORT mtrBuildDepthMtqUn(HMAP hmap,                 // 17/02/14
                                      const WCHAR * depthmtqname,
                                      DEPTHMTQPARM * depthmtqparm,
                                      COLORREF * palette,
                                      long int paletteCount);

 // ���������� ���������� �� ������� ����� (mtw) ��� ������� ������� (mtq)
 // hmap - �������� �����, ������������ ���������� �������
 // calcmatrixparm - ��������� � ���������� ����������
 // ��� ������� ������ (�������� ��������) ��� ���������� ���������� � �������,
 // �������� ����������� calcmatrixparm, ���������� 1.
 // ��� ���������� ������ (�������� ��������) � �������� ������� ���������� 0.

long int MTREXPORT mtrCalcByMatrix(HMAP hmap,                 // 12/11/09
                                   CALCMATRIXPARM * calcmatrixparm);

// ������ ����������� ������� �����
//  mtrName      - ������ ��� ������������ �������
//  smoothFactor - ������� ����������� (�� 0 �� 1, 0 - ������ �����,
//                 1 - ���������� ������)
//  handle       - ������������� ���� �������, �������� ����������
//                 ��������� � ���� �������� (������� ���������),
//                 ���� handle = 0, �� ��������� �� ����������
//  messageId    - ������������� ��������� � ��������� ���������
// ��� ����������� ������� ������������� ����������� ������ � �������
// (RowCount*ColCount*16) ����, ��� RowCount - ���������� ����� �������,
// ColCount - ���������� �������� �������
// � ������ ������ ���������� 0

long int MTREXPORT mtrSmoothMtr(const char *mtrName, double smoothFactor,
                                HMESSAGE handle, long int messageId);

long int MTREXPORT mtrSmoothMtrUn(const WCHAR *mtrName, double smoothFactor,  // 17/02/14
                                  HMESSAGE handle, long int messageId);


//********************************************************************
// ������� // 15/06/11
//********************************************************************
// ������������������ ������ ������� :

// hKriging = mapKrigingCreate(hmap, &MtrParm);

// ������ ���� ����������, ��� ������������ ���������� ����� ������� ��������
// �� ���������� �����. � ���� ������ ����� �������� ���� �������� ���������.
// mapKrigingGetMinMaxDistance(hKriging, &MinDist, &MaxDist);
// double LagSize = MaxDist / LagCount;

// ��������� ������������ ����������� ��� �����
// mapKrigingSetEmpiricalVariograms(hKriging, LagSize, LagCount);

// ���������� ������������� ����������� �������
//  for (int i = 0; i < LagCount; i++)
//    {
//      mapKrigingGetEmpiricalVariogram(Kriging, i, &Var, &Dist, &PointCount);
//      if (PointCount) Series2->AddXY(Dist, Var, IntToStr(PointCount), clGray);
//    }

// ��������� ��������� ������
// ���� �������� ������ ���� ���������, �� �������� � �-��� -1
//  double Range  = -1;
//  double Sill   = -1;
//  double Nugget = -1;
//  if (! CalcRangeButton ->Down) Range  = atof(RangeEdit ->Text.c_str());
//  if (! CalcSillButton  ->Down) Sill   = atof(SillEdit  ->Text.c_str());
//  if (! CalcNuggetButton->Down) Nugget = atof(NuggetEdit->Text.c_str());
//  mapKrigingSetTeoreticalVariograms(hKriging, ModelType, &Range, &Sill, &Nugget))

//  ���������� ����������� ������������
//  RangeEdit ->Text = FloatToStr(Range);
//  SillEdit  ->Text = FloatToStr(Sill);
//  NuggetEdit->Text = FloatToStr(Nugget);

//  // ������ ������������� ����������� �� ������� ������
//  double LagsSize = LagSize * LagCount;
//  double Step = LagsSize / 100.;
//  for (double Dist = 0; Dist < LagsSize; Dist += Step)
//    {
//      mapKrigingGetTeoreticalVariogram(Kriging, Dist, &Var);
//      Series1->AddXY(Dist, Var / Divider, "", clGray);
//    }

// ...

//  ����� �������������� ������� ������, ��������� � ������� ������ �������
//  mapKrigingBuild(hKriging, MtrName);

// mapKrigingFree(hKriging);
//********************************************************************

// ��� ������, ����������� ��� ���������� ������������ �����������
#define KM_FIRST       0
#define KM_LAST        7
#define KM_SPHEROIDAL  0  // �����������
#define KM_CIRCULAR    1  // ��������
#define KM_TETRASPHER  2  // ����������������
#define KM_PENTASPHER  3  // ����������������
#define KM_EXPONENT    4  // ����������������
#define KM_GAUSS       5  // ��������
#define KM_RATSQUARE   6  // ������������ ������������
#define KM_HOLE        7  // ������� ����

// �������� ������ ��������
// hmap - ����� �� �������� ������� ����� �������� �������
// mtrparm - ��������� ���������� �������
// ranges  - ��� ������ ������� �������� �������� ��� ������� (��� 0 �� ���������������)
// � ������ ������ ���������� 0

HANDLE MTREXPORT mtrKrigingCreate(HMAP hmap, HSITE hsit, BUILDSURFACE *mtrparm, double *ranges);

// ������������ ������ ��������
// kriging - ������������� ���������� ������ ��������

void MTREXPORT mtrKrigingFree(HANDLE kriging);

// ���������� ����������� � ������������ ���������� ����� �������
// kriging - ������������� ���������� ������ ��������
// min     - ������������ ����������� ���������� ����� ������� (������ ��������)
// max     - ������������ ������������ ���������� ����� �������
// � ������ ������ ���������� 0

long int MTREXPORT mtrKrigingGetMinMaxDistance(HANDLE kriging, double *min, double *max);

// ��������� ������������ ����������� ��� �����
// ��� - �������� ���������� ����� ������ �����, ��� ������� ����������� ������������ �����������
// kriging - ������������� ���������� ������ ��������
// lagsize - ������ ���� � ������ (��� ����� ��������� LagSize = MaxDist / LagCount
// lagcount - ���������� �����
// � ������ ������ ���������� 0

long int MTREXPORT mtrKrigingSetEmpiricalVariograms(HANDLE kriging, double lagsize, int lagcount);

// ���������� ��������� ������������ ����������� ��� ����
// kriging - ������������� ���������� ������ ��������
// lagnum  - ����� ����, ��� �������� ������������ ���������
// variogram - ������������ ����������� = sum(dH * dH) / 2
// dist      - ����� ���� �� ��� ���������� ����� ������ ����� = lagnum * lagsize + lagszie / 2
// pointcount - ���������� ��� �����, �������� � �������� ����
// � ������ ������ ���������� 0

long int MTREXPORT mtrKrigingGetEmpiricalVariogram(HANDLE kriging, int lagnum,
                                                        double *variogram, double *dist,
                                                        int *pointcount);

// ��������� ��������� ������, ����������� ��� ���������� ������������ �����������
// kriging - ������������� ���������� ������ ��������
// modeltype - ��� ������ (��. KM_SPHEROIDAL � ��.)
// range     - ������ ������ (�����) - ����� �� ��� ���������� ����� �������
//             ����� ������� ������ ���������� ��������������.
//             ���� = -1 - �� �������� �����������, ���� > 0, �� ���������������
// sill      - ����� - ��������, ������� ��������� ������������� ����������� �
//             ����� ������� ������, �� �������� ������� �������� ���������
//             ���� = -1 - �� �������� �����������, ���� > 0, �� ���������������
// nugget    - ��������� - ����� � ������� ������ ���������� ��� �����������.
//             ������������ ��� �������� ���������� ����� �������, ��������� �������
//             ������ ���� ����� 0. ������ ��� ���������� ����� ����������� �������
//             ����� ����������� �������� �� ��������� � ����.
//             ���� = -1 - �� �������� �����������, ���� >= 0, �� ���������������
// � ������ ������ ���������� 0

long int MTREXPORT mtrKrigingSetTeoreticalVariograms(HANDLE kriging, int modeltype,
                                                          double *range, double *sill, double *nugget);

// ��������� �������� ������������� ����������� �� ���������� ����� ����� �������
// kriging - ������������� ���������� ������ ��������
// � ������ ������ ���������� 0

long int MTREXPORT mtrKrigingGetTeoreticalVariogram(HANDLE kriging, double dist, double *var);

// ������ �������
// kriging - ������������� ���������� ������ ��������
// mtrname - ��� ����������� ������� ����� ��� �������
// � ������ ������ ���������� 0

long int MTREXPORT mtrKrigingBuild(HANDLE kriging, const char *mtrname);
long int MTREXPORT mtrKrigingBuildUn(HANDLE kriging, const WCHAR *mtrname);  // 03/03/14


//********************************************************************
// ��������� // 13/02/13
//********************************************************************

// ������� (������ �������� ��� ����� ��������) ����������� ���������� � ����������
#define COVFEATUREMIN 1
#define COVFEATUREMAX 3
#define COVFEATURE1   1
#define COVFEATURE2   2
#define COVFEATURE12  3

// �������� ������ ����������
// ranges  - ��� ������ ������� �������� �������� ��� ������� (��� 0 �� ���������������)

HANDLE MTREXPORT mtrCokrigingCreate(HMAP hmap, HSITE hsit, BUILDSURFACE *mtrparm, double *ranges);

// ������������ ������ ����������

void MTREXPORT mtrCokrigingFree(HANDLE cokriging);

// ���������� ����������� � ������������ ���������� ����� �������

long int MTREXPORT mtrCokrigingGetMinMaxDistance(HANDLE cokriging, int feature,
                                                      double *min, double *max);

// ��������� ������������ �����������

long int MTREXPORT mtrCokrigingSetEmpiricalCovariance(HANDLE cokriging, int feature,
                                                           double lagsize, int lagcount);

// ���������� �������� ������������ ����������� ��� ����

long int MTREXPORT mtrCokrigingGetEmpiricalCovariance(HANDLE cokriging, int feature, int lagnum,
                                                           double *variogram, double *dist, int *pointcount);

// ���������� �������� ���������

long int MTREXPORT mtrCokrigingGetVariance(HANDLE cokriging, int feature, double *variance);

// ���������� ���������� �����, �� ������� ��������� ���������
// ��� ��������� - ���������� �������� �������� �����
// ��� ����� - ���������� ����� �� ������� ������������ ����������� ��� ���������

long int MTREXPORT mtrCokrigingGetVariancePointCount(HANDLE cokriging, int feature, int *variancepointcount);

// ��������� ������������� �����������

long int MTREXPORT mtrCokrigingSetTeoreticalCovariance(HANDLE cokriging, int feature, int modeltype,
                                                            double *range, double *sill, double *nugget);

// ��������� �������� ������������� ����������� �� ���������� ����� ����� �������

long int MTREXPORT mtrCokrigingGetTeoreticalCovariance(HANDLE cokriging, int feature, double dist, double *var);

// ������ �������

long int MTREXPORT mtrCokrigingBuild(HANDLE cokriging, const char *mtrname);
long int MTREXPORT mtrCokrigingBuildUn(HANDLE cokriging, const WCHAR *mtrname);  // 03/03/14

//********************************************************************
// ��������������� ������������
//********************************************************************

long int MTREXPORT mtrLogarithmBuild(HMAP hmap, HSITE hsit, const char *mtrname,
                                     BUILDSURFACE *mtrparm, double *ranges);

long int MTREXPORT mtrLogarithmBuildUn(HMAP hmap, HSITE hsit, const WCHAR *mtrname,  // 03/03/14
                                     BUILDSURFACE *mtrparm, double *ranges);

//********************************************************************
// ������������� ������ � �������  // 28/05/13
//********************************************************************

// ����� ���������� �������� � �������

typedef struct MTRCLASS
{
  double Min;            // �������� �������� ��������� �������, ������������� ������ (������� Min, �������� Max)
  double Max;            // ��� ������� �����      - �������� �����
                         // ��� ������� �������    - �������� ��������
                         // ��� ����������� ������ - �������� ��������
                         // ��� RGB ������         - ������� - ������� �� R,G,B
  int    Excode;         // ��� ������������ �������
  int    Color;          // ���� ����������� ���������
  int    SemanticNumber; // ��� �������� ��������� � ������� ������������ ����� ������ (���� 0, �� �� �������)
                         // (� ��������� ��������� ����� ������ ������� � 1)
  int    SemanticMin;    // ��� �������� ��������� ��� ������ Min ������ (���� 0, �� �� �������)
  int    SemanticMax;    // ��� �������� ��������� ��� ������ Max ������ (���� 0, �� �� �������)
  int    SemanticColor;  // ��� �������� ��������� ��� ������ ����� ����������� ��������� ������ (���� 0, �� �� �������)
}
  MTRCLASS;

// �������������� ������� ����� � ������
// hmap       - �������� �����
// hsit       - ��������� ����� � ������� ������� �������
// mtrnum     - ����� �������������� ������� �����, ����������� � �����
// isfilter   - ������� ���������� �����, ������� �� ����� ������
// hselect    - �������� ��������� �������
//              ���� = 0, �� �� �����������, ��������� �������� ������ ��������� ���������
// classes    - �������������� ������
// classcount - ���������� �������
// border     - ������, �������������� ������� �������������� ������� � ������
// iscuthole  - ������� ��������� �����������
//              ���� = 0, �� ���������� ������ ������ ����� ������� ����� (Key), ��� �������
// handle     - ������������� ���� �������, �������� ���������� c�������� 0x0581
//              � wParam - ������� ����������� ���������
//              � lParam - ����� ������ � ��������� ������������ �����
//              ���� ������� ������ ���� ������������� ��������, � �����
//              ������ ��������� �������� 0x0581.
//              ���� Handle ����� ���� - ��������� �� ����������.
// ��� ������ ���������� 0

long int MTREXPORT mtrMtwToVector(HMAP hmap, HSITE hsit, long int mtrnum, long int isfilter,
                                  HSELECT hselect, MTRCLASS *classes, long int classcount, HOBJ border,
                                  long int iscuthole, HMESSAGE handle);

// �������������� ������� ������� � ������
// hmap       - �������� �����
// hsit       - ��������� ����� � ������� ������� �������
// mtqnum     - ����� �������� ������� �������, ����������� � �����
// isfilter   - ������� ���������� �����, ������� �� ����� ������ (0..1)
// hselect    - �������� ��������� ������� (���� = 0, �� �� �����������)
// classes    - �������������� ������
// classcount - ���������� �������
// border     - ������, �������������� ������� �������������� ������� � ������
// iscuthole  - ������� ��������� �����������
//              ���� = 0, �� ���������� ������ ������ ����� ������� ����� (Key), ��� �������
// handle     - ������������� ���� �������, �������� ���������� c�������� 0x0581
//              � wParam - ������� ����������� ���������
//              � lParam - ����� ������ � ��������� ������������ �����
//              ���� ������� ������ ���� ������������� ��������, � �����
//              ������ ��������� �������� 0x0581.
//              ���� Handle ����� ���� - ��������� �� ����������.
// ��� ������ ���������� 0

long int MTREXPORT mtrMtqToVector(HMAP hmap, HSITE hsit, long int mtqnum, long int isfilter,
                                  HSELECT hselect, MTRCLASS *classes, long int classcount, HOBJ border,
                                  long int iscuthole, HMESSAGE handle);

// �������������� ������ � ������
// hmap       - �������� �����
// hsit       - ��������� ����� � ������� ������� �������
// rstnum     - ����� ��������� ������, ������������ � �����
// isfilter   - ������� ���������� �����, ������� �� ����� ������ (0..1)
// hselect    - �������� ��������� ������� (���� = 0, �� �� �����������)
// classes    - �������������� ������
// classcount - ���������� �������
// border     - ������, �������������� ������� �������������� ������ � ������
// iscuthole  - ������� ��������� �����������
//              ���� = 0, �� ���������� ������ ������ ����� ������� ����� (Key), ��� �������
// handle     - ������������� ���� �������, �������� ���������� c�������� 0x0581
//              � wParam - ������� ����������� ���������
//              � lParam - ����� ������ � ��������� ������������ �����
//              ���� ������� ������ ���� ������������� ��������, � �����
//              ������ ��������� �������� 0x0581.
//              ���� Handle ����� ���� - ��������� �� ����������.
// ��� ������ ���������� 0

long int MTREXPORT mtrRstToVector(HMAP hmap, HSITE hsit, long int rstnum, long int isfilter,
                                  HSELECT hselect, MTRCLASS *classes, long int classcount, HOBJ border,
                                  long int iscuthole, HMESSAGE handle);

//********************************************************************
// ���������� ������� ��������� (������� ������� �������� ���������� �����,
// �������� � �������� ������)
//********************************************************************

// ��������� ������ ������ ���������� ������� ���������

typedef struct BUILDDENSITY
{
  double    Radius;       // ������ ������ ����� � ������ ��� ���������� �������� ��������
  double    ElemSize;     // ������ �������� ����������� ������� � ������
  COLORREF  Palette[256]; // ������� �������
  int       PaletteCount; // ���������� ������ � ������� (���� = 0, �� ��������������� �����������)
  int       Reserved[63];
}
  BUILDDENSITY;

// ���������� ������� ���������
// hmap    - �������� �����
// hsit    - ��������� ����� � ���������, �� ������� �������� ������� ���������
// mtqname - ��� ����������� �������
// hselect - �������, �� ������� �������� ������� (���� = 0, �� ��� ������� �����)
// parm    - ��������� ����������
// hwnd    - ����, �������� ���������� ��������� WM_PROGRESSBAR � ���������
//           ��������� � WPARAM (���� = 0, �� ��������� �� ����������)
// ��� ������ ���������� 0

long int MTREXPORT mtrBuildDensityMtq(HMAP hmap, HSITE hsit, const WCHAR *mtqname,
                                      HSELECT hselect, BUILDDENSITY *parm, HMESSAGE hwnd);

//********************************************************************
// ���������� ������� ��� ��������� (������� ������� ����� �������� 1, � ������
// ���� � ���� ����� ���� �� ���� �������� �����, � ��������� ������ 0)
//********************************************************************

// ��������� ������ ������ ���������� ������� ��� ���������

typedef struct BUILDVISIBLE
{
  double    Radius;   // ���������� ������ ���������
  double    ElemSize; // ������ �������� ����������� ������� � ������
  COLORREF  Color;    // ����, ������� ������������ ��������, � ������� ����� �����
  int       Reserved[63];
}
  BUILDVISIBLE;

// ���������� ������� ���������
// hmap    - �������� �����
// hsit    - ��������� ����� � ���������, �� ������� �������� ������� ���������
// mtqname - ��� ����������� �������
// hselect - �������, �� ������� �������� ������� (���� = 0, �� ��� ������� �����)
// parm    - ��������� ����������
// hwnd    - ����, �������� ���������� ��������� WM_PROGRESSBAR � ���������
//           ��������� � WPARAM (���� = 0, �� ��������� �� ����������)
// ��� ������ ���������� 0

long int MTREXPORT mtrBuildVisibleMtq(HMAP hmap, HSITE hsit, const WCHAR *mtqname,
                                      HSELECT hselect, BUILDVISIBLE *parm, HMESSAGE hwnd);

} // extern "�"
#endif // MTREXAPI_H

