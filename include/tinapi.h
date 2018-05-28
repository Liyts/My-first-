/****** TINAPI.H *************** Gorbunov A.V. ******** 03/04/14 ***
******* TINAPI.H *************** Shabakov D.A. ******** 21/07/16 ***
******* TINAPI.H *************** Dishlenko S.G.******** 31/03/15 ***
******* TINAPI.H *************** Konon V.N.    ******** 30/06/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                          TIN-������                              *
*                                                                  *
*  ��������� ��������                      (TINBUILD)              *
*  �������� �������� TIN-������            (TINDESCRIBE)           *
*  ��������� ������ ������� ������         (TINVERTEX)             *
*  ��������� ������ ������� �������������  (TINTRIANGLE)           *
*  �������� ������� ������� � TIN-������                           *
*                                                                  *
********************************************************************
*                                                                  *
*    �������������� ������� � Windows :                            *
*                                                                  *
*    // �������� ����������                                        *
*    HINSTANCE libInst = ::LoadLibrary("gisacces.dll");            *
*                                                                  *
*    // ����� �������                                              *
*    HMAP (WINAPI * lpfn_OpenTin)(const char*, long int);          *
*    (FARPROC)lpfn_OpenTin = GetProcAddress(libInst, "OpenTin");   *
*    HMAP hMap = (*lpfn_OpenTin)("Noginsk.tin",0);                 *
*                                                                  *
*    // �������� ����������                                        *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/

#ifndef TINAPI_H
#define TINAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

//------------------------------------------------------------------
//  ��������� �������� TIN-������
//------------------------------------------------------------------
typedef struct TINBUILD     // ������ ��������� 320 ����
{
  int  Length;              // ������ ������ ���������: sizeof(TINBUILD)              // 31/03/15

  int  UserLabel;           // ���������������� ������������� -
                            // ������������ �����, �����������
                            // � ����������� �������

  int  ModelType;           // ��� ������
                            //  ��������: 1 - ������ ������� ���������
                            //            2 - ������ ������

  int  Method;              // ����� ���������� ������
                            //  ��������: 1 - � ��������������
                            //                ������������ ������

  DFRAME    FrameMeters;    // �������� ������ � ����� (�����)

  MAPREGISTEREX
      ModelRegister;  // ���������� ������ ������
                      // ��������a MAPREGISTEREX ������a � MAPCREAT.H
                      // ��� �������� TIN-������ ������������
                      // �������� ��������� ����� :
                      //  Name - �������� ��� ������,
                      //  Scale - ����������� ��������,
                      //  EllipsoideKind - ��� ���������� (��������
                      //    � ������������ � ELLIPSOIDKIND, ���� MAPCREAT.H),
                      //  HeightSystem - ������� ����� (��������
                      //    � ������������ � HEIGHTSYSTEM, ���� MAPCREAT.H),
                      //  MaterialProjection - �������� ��������� ���������
                      //    (�������� � ������������ � MAPPROJECTION, ���� MAPCREAT.H),
                      //  CoordinateSystem - ������� ��������� (��������
                      //    � ������������ � COORDINATESYSTEM, ���� MAPCREAT.H),
                      //  MapType - ���������� ��� ����� (��������
                      //    � ������������ � MAPTYPE, ���� MAPCREAT.H),
                      //  FirstMainParallel - ������ ������� ���������,
                      //  SecondMainParallel - ������ ������� ���������,
                      //  AxisMeridian - ������ ��������,
                      //  MainPointParallel - ��������� ������� �����.

  HOBJ Border;        // ������������� ���������� ������� �����,
                      // �� �������� ��������������� ����� �����������
                      // TIN-������ (���� ������ ���������� ��� ���������
                      // ������, ������������ ���������� ���� FrameMeters
                      // ������ ���������, �� ����� �� ���������������)

  char      Reserve[60];    // ������ ���� ����
#ifdef _M_X64
  char      Free[4];        // ������������  // 21/07/16
#endif // _M_X64
}
  TINBUILD;

//------------------------------------------------------------------
//  �������� �������� TIN-������
//------------------------------------------------------------------
typedef struct TINDESCRIBE   // ������ ��������� 1024 �����
{
  char    Name[260];         // ��� ����� ������

  int   Length;              // ����� �����
  int   UserLabel;           // ���������������� �������������
  int   ModelType;           // ��� ������
  int   Method;              // ����� ���������� ������
  int   VertexCount;         // ���������� ������
  int   TriangleCount;       // ���������� �������������
  int   View;                // ������� ��������������

  DFRAME  FrameMeters;       // �������� ������ � ����� (�����)

  double  MinHeightValue;    // ����������� �������� ������ ����������� (�����)
  double  MaxHeightValue;    // ������������ �������� ������ ����������� (�����)

  MAPREGISTEREX
      ModelRegister;  // ���������� ������ ������
                      // ��������a MAPREGISTEREX ������a � MAPCREAT.H
                      // �������� TIN-������ �������� ��������
                      // ��������� ����� :
                      //  Name - �������� ��� ������,
                      //  Scale - ����������� ��������,
                      //  EllipsoideKind - ��� ����������,
                      //  HeightSystem - ������� �����,
                      //  MaterialProjection - �������� ��������� ���������,
                      //  CoordinateSystem - ������� ���������,
                      //  MapType - ���������� ��� �����,
                      //  FirstMainParallel - ������ ������� ���������,
                      //  SecondMainParallel - ������ ������� ���������,
                      //  AxisMeridian - ������ ��������,
                      //  MainPointParallel - ��������� ������� �����.

  double  ModelSquare;       // ������� ������ (��.�����)

  char    Reserve[472];      // ������

}
  TINDESCRIBE;

typedef struct TINDESCRIBEUN   // 03/04/14
{
  WCHAR   Name[MAX_PATH_LONG]; // ��� ����� ������

  DFRAME  FrameMeters;         // �������� ������ � ����� (�����)

  MAPREGISTEREX
      ModelRegister;  // ���������� ������ ������
                      // ��������a MAPREGISTEREX ������a � MAPCREAT.H
                      // �������� TIN-������ �������� ��������
                      // ��������� ����� :
                      //  Name - �������� ��� ������,
                      //  Scale - ����������� ��������,
                      //  EllipsoideKind - ��� ����������,
                      //  HeightSystem - ������� �����,
                      //  MaterialProjection - �������� ��������� ���������,
                      //  CoordinateSystem - ������� ���������,
                      //  MapType - ���������� ��� �����,
                      //  FirstMainParallel - ������ ������� ���������,
                      //  SecondMainParallel - ������ ������� ���������,
                      //  AxisMeridian - ������ ��������,
                      //  MainPointParallel - ��������� ������� �����.

  double  MinHeightValue;   // ����������� �������� ������ ����������� (�����)
  double  MaxHeightValue;   // ������������ �������� ������ ����������� (�����)
  double  ModelSquare;      // ������� ������ (��.�����)

  int    Length;            // ����� �����
  int    UserLabel;         // ���������������� �������������
  int    ModelType;         // ��� ������
  int    Method;            // ����� ���������� ������
  int    VertexCount;       // ���������� ������
  int    TriangleCount;     // ���������� �������������
  int    View;              // ������� ��������������
#ifdef _M_X64
  int    Free;              // ������������  // 21/07/16
#endif // _M_X64

  char    Reserve[128];     // ������

}
  TINDESCRIBEUN;

//------------------------------------------------------------------
// ��������� ������ ������� TIN-������
//------------------------------------------------------------------
typedef struct TINVERTEXFLAG   // ������ ��������� 8 ����
{
  char   Cancel;         // ���� ��������
  char   PolygonBorder;  // ���� �������������� ���������
                         // ����� �������� ������������
  char   StructLine;     // ���� �������������� ����������� �����
  char   FaultLine;      // ���� �������������� ����� �������
  char   FillingSquare;  // ���� �������������� ������� �������
                         // ����������
  char   Reserve[3];
}
  TINVERTEXFLAG;

//------------------------------------------------------------------
// ��������� ������ ������� ������ TIN-������
//------------------------------------------------------------------
typedef struct TINVERTEX     // ������ ��������� 40 ����
{
  double X;                  // ���������� ������� � �������������
  double Y;                  // ������� � �������� �������� (�����)
  double H;
                             // ��� ������, �������� � ������ ����� �������
  int    UpperVertexNumber;  // ����� ������� �������� ������
  int    UnderVertexNumber;  // ����� ������� ������� ������

  TINVERTEXFLAG Flag;        // ����� �������
}
  TINVERTEX;

//------------------------------------------------------------------
// ��������� ������ ������������ TIN-������
//------------------------------------------------------------------
typedef struct TINTRIANGLEFLAG   // ������ ��������� 16 ����
{
  char Cancel;           // ���� ��������

  char Location;         // ���� ��������� ������������ � ����
                         // (0 - ���������� ����������� ����,
                         //  1 - ������� ����������� ����)

  char FillingSquare;    // ���� �������������� ������� ������������
                         // ������� ����������

  char AB;               // ���� ����� "AB"
  char BC;               // ���� ����� "BC"
  char CA;               // ���� ����� "CA"
                         // (0 - ����� �� ������ � ������
                         //      ����������� �����,
                         //  1 - ����� ������ � ������ �����������
                         //      ����� �������� ��������,
                         //  2 - ����� ������ � ������ �����������
                         //      ����� ���������� ��������,
                         //  3 - ����� ������ � ������ �����������
                         //      ����� �������,
                         //  4 - ����� ������ � ������ �������
                         //      �������� ���������� ������������)
  char Reserve[10];

}
  TINTRIANGLEFLAG;
  
//------------------------------------------------------------------
// ��������� ������ ������� ������������� TIN-������
//------------------------------------------------------------------
typedef struct TINTRIANGLE  // ������ ��������� 40 ����
{
  int A;     // ����� ������� "A" � ������� ������
  int B;     // ����� ������� "B" � ������� ������
  int C;     // ����� ������� "C" � ������� ������

  int AB;    // ����� ��������� ������������ �� ����� "AB"
             // � ������� �������������
  int BC;    // ����� ��������� ������������ �� ����� "BC"
             // � ������� �������������
  int CA;    // ����� ��������� ������������ �� ����� "CA"
             // � ������� �������������
             // (���� ��������� ������������ ���, ����� ����� -1)

  TINTRIANGLEFLAG Flag;  // ����� ������������
}
  TINTRIANGLE;


  
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ �������� ������� ������� � TIN-������ +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
  // ��������� ����� �������� TIN-������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinCount(HMAP hMap);

  // ������� TIN-������
  // ���������� ������������� �������� ������ (TMapAccess*)
  // ��� ������ ���������� 0

  _MAPIMP HMAP _MAPAPI mapOpenTin(const char * tinname, long int mode);
  _MAPIMP HMAP _MAPAPI mapOpenTinUn(const WCHAR *tinname, long int mode = 0);  // 28/01/14

  // ������� TIN-������ � �������� ������ ����� (�������� � �������)
  // ���������� ����� ����� � �������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapOpenTinForMap(HMAP hMap, const char * tinname, long int mode);
  _MAPIMP long int _MAPAPI mapOpenTinForMapUn(HMAP hMap, const WCHAR * tinname, long int mode);  // 28/01/14


  // ������� TIN-������
  // number - ����� ����������� ������
  // ���� number == 0, ����������� ��� ������ � ����

  _MAPIMP void _MAPAPI mapCloseTin(HMAP hMap, long int number);

  // ������� TIN-������ � �������� ������ �����
  // number - ����� ����� ������ � �������
  // ���� number == 0, ����������� ��� ������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapCloseTinForMap(HMAP hMap, long int number);

  // ������� TIN-������
  // ���������� ������������� �������� ������ (TMapAccess*)
  // ��������a TINBUILD ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP HMAP _MAPAPI mapCreateTin(const char * name, const TINBUILD * parm);
  _MAPIMP HMAP _MAPAPI mapCreateTinUn(const WCHAR * name, const TINBUILD * parm);  // 28/01/14

  // ������� ���� TIN-������
  // hMap -  ������������� �������� ��������� �����
  // tinname - ������ ��� ����� ������
  // parm - ��������� �������� ������
  // ��������a TINBUILD ������a � TINAPI.H
  // ����������  ����� ����� � ������� TIN-�������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapCreateAndAppendTin(HMAP hMap, const char * tinname, const TINBUILD * parm);
  _MAPIMP long int _MAPAPI mapCreateAndAppendTinUn(HMAP hMap, const WCHAR * tinname, const TINBUILD * parm);  // 28/01/14

  // �������� ��������� TIN-������ � ����
  // number - ����� ����� � �������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSaveTin(HMAP hMap, long int number);

  // ��������� �������� ����� TIN-������
  // number - ����� ����� � �������
  // describe - ����� ���������, � ������� ����� ���������
  //            �������� TIN-������
  // ��������a TINDESCRIBE ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinDescribe(HMAP hMap, long int number,  // 10/04/13
                                     TINDESCRIBE * describe);

  _MAPIMP long int _MAPAPI mapGetTinDescribeUn(HMAP hMap, long int number,  // 03/04/14
                                     TINDESCRIBEUN * describe);

	// ��������� ��� ����� TIN-������
	// number - ����� ����� � �������
	// ��� ������ ���������� ����

	_MAPIMP const char * _MAPAPI mapGetTinName(HMAP hMap,long int number);  // 28/01/14

  // ��������� ��� ����� TIN-������
  // hMap - ������������� �������� �������� ��������� �����
  // number - ����� ����� � �������
  // name - ����� ������ ��� ���������� ����������
  // size - ������ ������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetTinNameUn(HMAP hMap,long int number,  // 28/01/14
                                           WCHAR *name, long int size);

  // ��������� ����� TIN-������ � ������� �� ����� ����� 
  // name - ��� ����� TIN-������
  // � ������� ������ TIN-������� ���������� � 1
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetTinNumberByName(HMAP hMap, const char * name);
  _MAPIMP long int _MAPAPI mapGetTinNumberByNameUn(HMAP hMap, const WCHAR * name);  // 28/01/14

  // ��������� ���������� ������ TIN-������
  // number - ����� TIN-����� � �������
  // data - ����� ���������, � ������� ����� ��������� ����������
  // ������ TIN-������
  // ��������a MAPREGISTEREX ������a � MAPCREAT.H
  // ���������� ������ TIN-������ �������� �������� ��������� ����� :
  //  Name - �������� ��� ������,
  //  Scale - ����������� ��������,
  //  EllipsoideKind - ��� ����������,
  //  HeightSystem - ������� �����,
  //  MaterialProjection - �������� ��������� ���������,
  //  CoordinateSystem - ������� ���������,
  //  MapType - ���������� ��� �����,
  //  FirstMainParallel - ������ ������� ���������,
  //  SecondMainParallel - ������ ������� ���������,
  //  AxisMeridian - ������ ��������,
  //  MainPointParallel - ��������� ������� �����.
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinRegister(HMAP hMap, long int number,
                                     MAPREGISTEREX* data);

  // ������ ������� � ������ ������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // ��������a TINVERTEX ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapPutTinVertex(HMAP hMap, long int number,
                                   const TINVERTEX * vertex, long int index);

  // ������ ������� �� ������� ������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // ��������a TINVERTEX ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinVertex(HMAP hMap, long int number,
                                   TINVERTEX* vertex, long int index);

  // ����� �������� ������ ����������� TIN-������ � �������� �����
  // ������ ����������� ������������� �� TIN-������ � �������
  // ������� ����� � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� TIN-������ ���������� ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetSurfaceHeight(HMAP hMap, double x, double y);

  // ����� �������� ������ ����������� TIN-������ � �������� �����
  // �� ����� � ������� number � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� TIN-������ ���������� ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetTinSurfaceHeight(HMAP hMap, long int number,
                                        double x, double y);

  // ��������� ������ ������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // flag - ����� ���������, ���������� ��������������� ��������
  //        ������ �������
  // ��������a TINVERTEXFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinVertexFlags(HMAP hMap, long int number,
                                        long int index, const TINVERTEXFLAG* flag);

  // ������ ������ ������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // flag - ����� ���������, ���������� �������� ������ �������
  // ��������a TINVERTEXFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinVertexFlags(HMAP hMap, long int number,
                                        long int index, TINVERTEXFLAG* flag);


  // ��������� ������ ������������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // flag - ����� ���������, ���������� ��������������� ��������
  //        ������ ������������
  // ��������a TINTRIANGLEFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinTriangleFlags(HMAP hMap, long int number,
                                          long int index, const TINTRIANGLEFLAG* flag);

  // ������ ������ ������������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // flag - ����� ���������, ���������� �������� ������ ������������
  // ��������a TINTRIANGLEFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinTriangleFlags(HMAP hMap, long int number,
                                          long int index, TINTRIANGLEFLAG* flag);

  // ������ ������������ �� ������� ������������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // ��������a TINTRIANGLE ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinTriangle(HMAP hMap, long int number,
                                     TINTRIANGLE* triangle, long int index);

  // ������ ������������ � ������ ������������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // ��������a TINTRIANGLE ������a � TINAPI.H
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapPutTinTriangle(HMAP hMap, long int number,
                                     const TINTRIANGLE* triangle, long int index);



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  �������� ������� ��������� ���������� TIN-������  +++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // ���������� ���������� ������ TIN-������
  // number - ����� TIN-����� � �������
  // data - ����� ���������, ���������� ���������� ������ TIN-������
  // ��������a MAPREGISTEREX ������a � MAPCREAT.H
  // ���������� ������ TIN-������ �������� �������� ��������� ����� :
  //  Name - �������� ��� ������,
  //  Scale - ����������� ��������,
  //  EllipsoideKind - ��� ���������� (��������
  //    � ������������ � ELLIPSOIDKIND, ���� MAPCREAT.H),
  //  HeightSystem - ������� ����� (��������
  //    � ������������ � HEIGHTSYSTEM, ���� MAPCREAT.H),
  //  MaterialProjection - �������� ��������� ���������
  //    (�������� � ������������ � MAPPROJECTION, ���� MAPCREAT.H),
  //  CoordinateSystem - ������� ��������� (��������
  //    � ������������ � COORDINATESYSTEM, ���� MAPCREAT.H),
  //  MapType - ���������� ��� ����� (��������
  //    � ������������ � MAPTYPE, ���� MAPCREAT.H),
  //  FirstMainParallel - ������ ������� ���������,
  //  SecondMainParallel - ������ ������� ���������,
  //  AxisMeridian - ������ ��������,
  //  MainPointParallel - ��������� ������� �����.
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinRegister(HMAP hMap, long int number,
                                     const MAPREGISTEREX* data);

  // ���������� ���������������� ������������� TIN-������
  // userLabel - ������������� ������
  // number  - ����� TIN-����� � �������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinUserLabel(HMAP hMap, long int number,
                                      long int userLabel);

  // ���������� ��� TIN-������
  // number - ����� TIN-����� � �������
  // type - ��� ������
  //   (�������� � ������������ � TINBUILD, ���� TINAPI.H)
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinModelType(HMAP hMap, long int number,
                                      long int type);

  // ���������� ����� ���������� TIN-������
  // number  - ����� TIN-����� � �������
  // method - ����� ����������  ������
  //   (�������� � ������������ � TINBUILD, ���� TINAPI.H)
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinMethod(HMAP hMap, long int number,
                                   long int method);
                                      
  // ���������� �������� TIN-������ � ������
  // frame - �������� ������ � ������ (�����)
  // ��������a DFRAME ������a � MAPTYPE.H
  // number  - ����� TIN-����� � �������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinFrameMeters(HMAP hMap, long int number,
                                        const DFRAME* frame);

  // ���������� �������� �������� ������ ����������� TIN-������
  // number  - ����� TIN-����� � �������
  // minimum - ����������� �������� ������ ����������� (�����)
  // maximum - ������������ �������� ������ ����������� (�����)
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinHeightDiapason(HMAP hMap, long int number,
                                           double minimum,
                                           double maximum);

  // ���������� ������� �������������� TIN-������
  // number - ����� TIN-����� � �������
  // view - ������� ��������������
  //   (0 - ������ �� ������������, 1 - ������ ������������)
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinView(HMAP hMap, long int number,
                                 long int view);
                                 
  // ��������� ������� �������������� TIN-������
  // number - ����� TIN-����� � �������
  // ���������� ������� ��������������
  // (0 - ������ �� ������������, 1 - ������ ������������)
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapCheckTinView(HMAP hMap, long int number); 
                                                               
  // ���������� �������� �������� ������ � �������
  // ������ ��������� TIN-������
  // number - ����� TIN-����� � �������
  // bottomScale - ����������� �������� ������ ������� ���������
  // topScale - ����������� �������� ������� ������� ���������
  // ���� �� ����������� ������� bottomScale <= topScale, ���������� 0
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetTinRangeScaleVisible(HMAP hMap, long int number,
                                              long int bottomScale,
                                              long int topScale);

  // ��������� �������� �������� ������ � �������
  // ������ ��������� TIN-������
  // number - ����� TIN-����� � �������
  // �� ������ bottomScale ������������ ����������� ��������
  // ������ ������� ���������
  // �� ������ topScale ������������ ����������� ��������
  // ������� ������� ���������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinRangeScaleVisible(HMAP hMap, long int number,
                                              long int *bottomScale,
                                              long int *topScale);


  // ���������� ������� �����������
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� -1
  _MAPIMP long int _MAPAPI mapSetTinViewOrder(HMAP hMap, long int number, long int order);

  // ���������������� �����������
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� -1
  _MAPIMP long int _MAPAPI mapGetTinViewOrder(HMAP hMap, long int number);

  // ��������� �������� ������ � ������ (�����)
  // number - ����� ����� � �������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinFrame(HMAP hMap, long int number, DFRAME * dframe);

  // ��������� ����� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����
  _MAPIMP long int _MAPAPI mapGetTinFileLength(HMAP hMap, long int number);

  // ��������� ���������� ������ � Tin-������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����
  _MAPIMP long int _MAPAPI mapGetTinVertexCount(HMAP hMap, long int number);


  // ��������� ���������� ������������� � Tin-������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����
  _MAPIMP long int _MAPAPI mapGetTinTriangleCount(HMAP hMap, long int number);

  // ��������� ������� Tin-������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetTinScale(HMAP hMap, long int number);

  // ��������� ��� TIN-������
  // number - ����� TIN-����� � �������  
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinModelType(HMAP hMap, long int number);

  // ��������� ����������� � ������������ �������� ������ ����������� (�����)
  // number - ����� TIN-����� � �������  
  // ��� ������ ���������� 0
  
  _MAPIMP long int _MAPAPI mapGetTinHeightValue(HMAP hMap, long int number, 
                                          double * minvalue, double * maxvalue);
                                        
  // ��������� ����� ���������� TIN-������
  // number  - ����� TIN-����� � �������  
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetTinMethod(HMAP hMap, long int number);
                                                                         
  // ��������� ������ � �����
  // number  - ����� TIN-����� � �������  
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapIsTinEdit(HMAP hMap, long int number);  

  // �������� ����������� ����������� �������
  // oldNumber - ����� ����� � �������
  // newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0
  _MAPIMP long int _MAPAPI mapChangeOrderTinShow(HMAP hMap, long int oldNumber, long int newNumber);

}

#endif // TINAPI_H

