/****** MTDAPI.H ***************  Gorbunov A.V.  ****** 16/08/16 ***
******* MTDAPI.H ***************  Shabakov D.A.  ****** 16/04/13 ***
******* MTDAPI.H ***************  Belenkov O.V.  ****** 11/09/16 ***
******* MTDAPI.H ***************  Savelov A.S.   ****** 18/05/15 ***
******  MTDAPI.H ***************  Konon V.N.     ****** 30/06/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*          �������� ������� ������� � ������� ����� (MTD)          *
*                                                                  *
********************************************************************
*                                                                  *
*                 �������������� ������� :                         *
*                                                                  *
*                                                                  *
*    // �������� ����������                                        *
*                                                                  *
*    HINSTANCE libInst = ::LoadLibrary("gisacces.dll");            *
*                                                                  *
*    // ����� �������                                              *
*                                                                  *
*    HMAP (WINAPI * lpfn_OpenMap)(const char*, long int);          *
*    (FARPROC)lpfn_OpenMap = GetProcAddress(libInst, "OpenMap");   *
*    HMAP hMap = (*lpfn_OpenMap)("Noginsk.map",0);                 *
*                                                                  *
*    // �������� ����������                                        *
*                                                                  *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/

#ifndef MTDAPI_H
#define MTDAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

#ifndef MTLAPI_H
  #include "mtlapi.h"
#endif


//  ��������� ������������ MTD-�����
//------------------------------------------------------------------------------
#define POINTSFORELEMENT 32  // ���-�� ����� �� �������
#define BLOCKSIDE 32         // ������� ����� ���������
#define BLOCKMTDFACTOR 8     // ������� ����� ����� = 4 �������� (BLOCKSIDE / BLOCKMTDFACTOR)

// ���� ����� = (4 * 4) = 16 ��-��� ~= POINTSFORELEMENT * 16 ~= 32 * 16 ~= 512 �����
//------------------------------------------------------------------------------


 // ����� MTD-������

 typedef struct XYZC  // ������ ��������� 32 �����
 {
   double    X;  // ���������� �����
   double    Y;
   double    Z;  // ������ �����
   long int  C;  // ��� �����
   long int  Free;

   void operator = (XYZC p) { X = p.X;  Y = p.Y;  Z = p.Z; C = p.C; }
 }
   XYZC;

 // ����� MTD-������ � ������� �� LAS-�����            27/08/09

 typedef struct XYZCLAS             // ������ ��������� 80 ����
 {
   double    X;                     // ���������� �����
   double    Y;
   double    Z;                     // ������ �����

   long int  C;                     // ��� �����
   long int  ReturnNumber;          // ����� ��������

   long int  NumberOfReturns;       // ���-�� ��������� ������� ��������
   long int  ScanDirectionFlag;     // ���� ����������� ������������

   long int  EdgeOfFlightLineFlag;  // ���� "���� ����� �����"
   long int  Classification;        // �������������

   long int  ScanAngleRank;         // ���� ���� ������������ (�� -90 �� +90)
   long int  FileMarker;            // ������ ����� - ��� ����������� � ������ ���� LAS ������

   long int  Intensity;             // ������������� ��������
   long int  UserBits;              // ���� ����� ������������

   long int  Free1;                 // ������
   long int  Free2;

   long int  Free3;                 // ������
   long int  Free4;

   void operator = (XYZCLAS p)
   {
     X = p.X;  Y = p.Y;  Z = p.Z; C = p.C;
     ReturnNumber = p.ReturnNumber;
     NumberOfReturns = p.NumberOfReturns;
     ScanDirectionFlag = p.ScanDirectionFlag;
     EdgeOfFlightLineFlag = p.EdgeOfFlightLineFlag;
     Classification = p.Classification;
     ScanAngleRank = p.ScanAngleRank;
     FileMarker = p.FileMarker;
     Intensity = p.Intensity;
     UserBits = p.UserBits;
   }
 }
   XYZCLAS;




//-----------------------------------------------------------
// ��������� ����� (���������� ������������� � ����� �����)
// ��� �������� MTD �� TXT-����� (16 ����)
//-----------------------------------------------------------
typedef struct
{
  unsigned long int X;  // ���������� �����           // 12/05/11  "unsigned"
  unsigned long int Y;
  unsigned long int H;
  unsigned long int C;  // ��� �����
}
  MTDXYHC;

//-----------------------------------
//  ������� ���� LAS-����� (4 �����)
//-----------------------------------
typedef struct
{
  unsigned ReturnNumber :3;           // The return number - ����� ��������
  unsigned NumberOfReturns :3;       // The number of returns for that shot - ���-�� ��������� ������� ��������
  unsigned ScanDirectionFlag :1;     // The scan direction - ���� ����������� ������������
  unsigned EdgeOfFlightLineFlag :1;  // Edge of scan flag - ���� "���� ����� �����"
  unsigned Classification :8;        // �������������
  signed   ScanAngleRank :8;         // ���� ���� ������������ (-90 to +90) - Left side
  unsigned FileMarker :8;            // ������ ����� - ��� ����������� � ������ ���� LAS ������
}
  LASINFO;

//-----------------------------------------------------------
// ��������� ����� (���������� ������������� � ����� �����)
// ��� �������� MTD �� LAS-����� (24 �����)
//-----------------------------------------------------------
typedef struct
{
  long int X;  // ���������� �����
  long int Y;
  long int H;
  long int C;  // ��� �����

  LASINFO LasInfo;  // ������� ���� ����� (4 �����)

  unsigned short int Intensity;  // ������������� ��������
  unsigned short int UserBits;   // ���� ����� ������������
}
  MTDXYHCLAS;
   

extern "C"
{
  // ������� ��������� ������
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // ��� ������ ���������� ����

  _MAPIMP HMAP _MAPAPI mapOpenMtd(const char * mtrname, long int mode = 0);
  _MAPIMP HMAP _MAPAPI mapOpenMtdUn(const WCHAR *mtrname, long int mode = 0);  // 28/01/14


  // ������� ��������� ������ � �������� ������ �����
  // (�������� � ������� ������)
  // ���������� ����� ����� � ������� ������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapOpenMtdForMap(HMAP hMap, const char * mtrname, long int mode);
  _MAPIMP long int _MAPAPI mapOpenMtdForMapUn(HMAP hMap, const WCHAR * mtrname, long int mode);  // 28/01/14



  // ������� ��������� �����
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // ��������a BUILDMTL ������a � mtlapi.h
  // ��������a MTRPROJECTIONDATA ������a � maptype.h
  // maxPointCount - ������������ ���-�� ����� � ����� �������
  // ��� ������ ���������� ����

  _MAPIMP HMAP _MAPAPI mapCreateMtd(const char * mtrname,
                            BUILDMTL * mtrparm,
                            long int maxPointCount,
                            MTRPROJECTIONDATA * mtrprojectiondata);

  _MAPIMP HMAP _MAPAPI mapCreateMtdUn(const WCHAR * mtrname,          // 28/01/14
                            BUILDMTL * mtrparm,
                            long int maxPointCount,
                            MTRPROJECTIONDATA * mtrprojectiondata);

  // ������� ��������� �����
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // ��������a BUILDMTL ������a � mtlapi.h
  // blockpointcount - ������ ��������� ����� � ������ �������
  // ��������a MTRPROJECTIONDATA ������a � maptype.h
  // ��� ������ ���������� ����

  _MAPIMP HMAP _MAPAPI mapCreateMtdByBlockPointCount(const char * mtrname,
                                             BUILDMTL * mtrparm,
                                             int* blockpointcount,              // 18/05/15 �������
                                             MTRPROJECTIONDATA * mtrprojectiondata);

  _MAPIMP HMAP _MAPAPI mapCreateMtdByBlockPointCountUn(const WCHAR * mtrname,   // 28/01/14
                                             BUILDMTL * mtrparm,
                                             int* blockpointcount,              // 18/05/15 �������
                                             MTRPROJECTIONDATA * mtrprojectiondata);

  // �������� ��������� ������� � ����
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapSaveMtd(HMAP hMap, long int number);

  // ��������� ������� ��������������� ����� �������
  // number - ����� ����� � �������

  _MAPIMP long int _MAPAPI mapIsMtdEdit(HMAP hMap,long int number);

  // ������� ��������� ������
  // number - ����� ����������� �������
  // ���� number == 0, ����������� ��� ������� � ����

  _MAPIMP void _MAPAPI mapCloseMtd(HMAP hMap,long int number = 0);

  // ������� ��������� ������ � �������� ������ �����
  // number - ����� ���������� ����� � �������
  // ���� number == 0, ����������� ��� ��������� ������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapCloseMtdForMap(HMAP hMap,
                                     long int number);

  // ��������� ����� �������� ������ ��������� ������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdCount(HMAP hMap);

  // ���������� � �������� ������� ������� � ������� � ������� "number"
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapActiveMtd(HMAP hMap, long int number);


  // ���������� �������� ������������ ��������� �������
  // number   - ����� ������� � �������
  // minvalue - ����������� �������� ������������� ��������
  //            � �������� �������
  // maxvalue - ������������ �������� ������������� ��������
  //            � �������� �������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetMtdShowRange(HMAP hMap,
                                      long int number,
                                      double minvalue,
                                      double maxvalue);

  // ���������� ��������� ����� �������
  // number - ����� ������� � �������
  // density - �������� ��������� ����� (���-�� ����� �� ��.����)
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetMtdDensity(HMAP hMap,
                                    long int number,
                                    double density);

  // ��������� ��������� ����� �������
  // number - ����� ������� � �������
  // ���������� �������� ��������� ����� (���-�� ����� �� ��.����)
  // ��� ������ ���������� ERRORHEIGHT

  _MAPIMP double _MAPAPI mapGetMtdDensity(HMAP hMap,    // 16/08/16
                                    long int number);

  // ����� ����� "dot" � �������
  // number - ����� ����� � �������
  // ��������� XYZC ������� � ������ �����
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapPutMtdDot(HMAP hMap, long int number, XYZC* dot);

  // ����� ����� "dot" � �������
  // number - ����� ����� � �������
  // ��������� XYZCLAS (����� MTD-������ � ������� �� LAS-�����)
  // ������� � ������ �����
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapPutMtdDotLas(HMAP hMap, long int number, XYZCLAS* dot);  // 27/08/09

  // ��������� �������� ���������� ������ � ������� �������,
  // ��������������� �������� �����.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) � �������� ������ (h) �������� � ������
  // � ������� ��������� ��������� �����.
  // � ������ ������ ���������� ����.

  _MAPIMP long int _MAPAPI mapPutMtdElementHeight(HMAP hMap,long int number,
                                          double x, double y, double h);

  // ������� ��� ���� � ������� �������, ��������������� �������� �����.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ��������� ��������� �����.
  // code - ��� ����
  // � ������ ������ ���������� 0.

  _MAPIMP long int _MAPAPI mapPutMtdElementCode(HMAP hMap, long int number,       // 10/06/08
                                        double x, double y, long int code);

  // ��������� ��� ���� �� �������� �������, ���������������� �������� �����.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ��������� ��������� �����.
  // ���������� ��� ����
  // � ������ ������ ���������� 0.

  _MAPIMP long int _MAPAPI mapGetMtdElementCode(HMAP hMap, long int number,
                                            double x, double y);

  /*********************************************************
  *                                                        *
  *           ������ ������ �� ������� �����               *
  *                                                        *
  *********************************************************/

  // ��������� ��� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP const char * _MAPAPI mapGetMtdName(HMAP hMap,long int number);

  // ��������� ��� ����� ��������� ������
  // hMap - ������������� �������� �������� ��������� �����
  // number - ����� ����� � �������
  // name - ����� ������ ��� ���������� ����������
  // size - ������ ������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdNameUn(HMAP hMap,long int number,  // 28/01/14
                                           WCHAR *name, long int size);

  // ��������� ����� ������� � ������� �� ����� �����
  // name - ��� ����� �������
  // � ������� ������ ������ ���������� � 1
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdNumberByName(HMAP hMap, const char * name);
  _MAPIMP long int _MAPAPI mapGetMtdNumberByNameUn(HMAP hMap, const WCHAR * name);  // 28/01/14


  // ��������� ����� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP double _MAPAPI mapGetMtdFileLength(HMAP hMap,long int number);

  // ��������� ���������� ����� � �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP unsigned long _MAPAPI mapGetMtdPointCount(HMAP hMap,long int number);

  // ��������� ������ � �������� �������
  // hMap   - ������������� �������� �������� ��������� �����
  // number - ����� ����� � �������
  // mapregister - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��������a MAPREGISTEREX ������a � mapcreat.h
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdProjectionData(HMAP hMap, long int number,
                                           MAPREGISTEREX* mapregister);

  // ��������� ������ � �������� �������
  // hMap   - ������������� �������� �������� ��������� �����
  // number - ����� ����� � �������
  // mapregister, datumparam, ellipsoidparam - ������ ��������, � ������� ����� ���������
  // ��������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM ������� � mapcreat.h
  // ttype  - ��� ���������� �������������� ��������� (��. TRANSFORMTYPE � mapcreat.h) ��� 0
  // tparm - ��������� ���������� �������������� ��������� (��. mapcreat.h)
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdProjectionDataPro(HMAP hMap, long int number,   // 11/09/16
                                                      MAPREGISTEREX  *mapregister,
                                                      DATUMPARAM     *datumparam,
                                                      ELLIPSOIDPARAM *ellipsoidparam,
                                                      long int * ttype,
                                                      LOCALTRANSFORM * tparm);

  _MAPIMP long int _MAPAPI mapGetMtdProjectionDataEx(HMAP hMap, long int number,
                                                   MAPREGISTEREX  *mapregister,
                                                   DATUMPARAM     *datumparam,
                                                   ELLIPSOIDPARAM *ellipsoidparam);

  // ���������� ������ � �������� �������
  // number - ����� ����� � �������
  // mapregister - ����� ���������, ���������� ������ � ��������
  // ��������a MAPREGISTEREX ������a � mapcreat.h
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapSetMtdProjectionData(HMAP hMap,long int number,
                                           MAPREGISTEREX* mapregister);

  // ���������� ������ � �������� �������
  // hMap   - ������������� �������� �������� ��������� �����
  // number - ����� ������� � �������.
  // mapregister, datumparam, ellipsoidparam - ������ ��������, ���������� ������ � ��������
  // ��������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM ������� � mapcreat.h
  // ttype  - ��� ���������� �������������� ��������� (��. TRANSFORMTYPE � mapcreat.h) ��� 0
  // tparm - ��������� ���������� �������������� ��������� (��. mapcreat.h)
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapSetMtdProjectionDataPro(HMAP hMap, long int number,       // 11/09/16
                                                    MAPREGISTEREX  *mapregister,
                                                    DATUMPARAM     *datumparam,
                                                    ELLIPSOIDPARAM *ellipsoidparam,
                                                    long int ttype,
                                                    LOCALTRANSFORM * tparm);

_MAPIMP long int _MAPAPI mapSetMtdProjectionDataEx(HMAP hMap, long int number,
                                                   MAPREGISTEREX  *mapregister,
                                                   DATUMPARAM     *datumparam,
                                                   ELLIPSOIDPARAM *ellipsoidparam);

  // ��������� �������� ����� ��������� ������
  // number - ����� ����� � �������
  // describe - ����� ���������, � ������� ����� ���������
  // �������� �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdDescribe(HMAP hMap,long int number,
                                     MTLDESCRIBE * describe);

  _MAPIMP long int _MAPAPI mapGetMtdDescribeUn(HMAP hMap,long int number,  // 03/04/14
                                     MTLDESCRIBEUN * describe);

  // ��������� ����� ����� ������ �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdBlockRow(HMAP hMap,long int number);

  // ��������� ����� �������� ������ �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdBlockColumn(HMAP hMap,long int number);

  // ��������� ������ ����� �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdBlockSize(HMAP hMap,long int number);

  // ��������� ������������ ������ ����� ������� � ���������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdBlockSide(HMAP hMap,long int number);

  // ��������� ���� ������� �� ������ ������ � �������
  // ������ ����� � �������� � �������� ������ �����
  // ����� ���������� ���� ����� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP char * _MAPAPI mapGetMtdBlockAddress(HMAP hMap,long int number,
                                       long int row,
                                       long int column);

  // ��������� ����� ����� ��������� � �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdElementRow(HMAP hMap,long int number);

  // ��������� ����� �������� ��������� � �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdElementColumn(HMAP hMap,long int number);

  // ��������� ������� �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdScale(HMAP hMap,long int number);

  // ���������� ������� �������
  // number - ����� ����� � �������
  // scale  - ����������� ��������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapSetMtdScale(HMAP hMap,long int number,double scale);

  // ����� �������� ���������� ������ � �������� �����.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetMtdElementHeight(HMAP hMap,double x,double y);


  // ���������� �������� ���������� ������ � �������� �����
  // � �������������� ���� MTD-������� �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetMtdHeight(HMAP hMap,double x,double y);  // 26/02/14

  // ����� �������� ���������� ������ � �������� ����� �� �������
  // � ������� number � �������.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetElementHeightOfMtd(HMAP hMap,long int number,double x,double y);

  // ��������� �������� �������� ������ � ������� ������ ��������� �������
  // number - ����� ����� � �������
  // �� ������ bottomScale ������������ ����������� �������� ������ ������� ��������� �������
  // �� ������ topScale ������������ ����������� �������� ������� ������� ��������� �������
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapGetMtdRangeScaleVisible(HMAP hMap, long int number, long int *bottomScale, long int *topScale);

  // ���������� �������� �������� ������ � ������� ������ ��������� �������
  // number     - ����� ����� � �������
  // bottomScale   - ����������� �������� ������ ������� ��������� �������
  // topScale   - ����������� �������� ������� ������� ��������� �������
  //              bottomScale <= topScale, ����� ���������� 0
  // ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapSetMtdRangeScaleVisible(HMAP hMap, long int number, long int bottomScale, long int topScale);

  // ��������� �������� ����� ���� layernumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  _MAPIMP long int _MAPAPI mapSetMtdLayerColor(HMAP hMap,long int number,
                                       long int layernumber,
                                       COLORREF layercolor);

  // ��������� �������� ����� ���� ����� codenumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  _MAPIMP long int _MAPAPI mapSetMtdCodeColor(HMAP hMap,long int number,
                                      long int codenumber,
                                      COLORREF codecolor);

  // ��������� ���������� ����� ���� codenumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  _MAPIMP long int _MAPAPI mapSetMtdCodePointCount(HMAP hMap,long int number,
                                           long int codenumber,
                                           long int pointcount);

  // ��������� �������� ����� ���� ����� codenumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  _MAPIMP long int _MAPAPI mapSetMtdCodeFlag(HMAP hMap,long int number,
                                     long int codenumber,
                                     long int codeflag);

  // ��������� ����� codename ���� ����� codenumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  _MAPIMP char* _MAPAPI mapSetMtdCodeName(HMAP hMap,long int number,
                                     long int codenumber,
                                     char* codename);

  // ��������� ������ ����� MTD-������ (���������� ������������� � ����� �����)
  // number - ����� ����� � �������
  // ������������ ��������:  0 - ��������� ����� MTDXYHC (16 ����)
  //                         1 - ��������� ����� MTDXYHCLAS (24 �����)
  // ��������� ������� � ������ �����
  // ��� ������ ���������� -1

  _MAPIMP long int _MAPAPI mapGetMtdPointFormat(HMAP hMap, long int number);  // 02/04/13

  // ��������� ����� ����� ������ ����� MTD-������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdPointBlockRow(HMAP hMap, long int number);  // 02/04/13

  // ��������� ����� �������� ������ ����� MTD-������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  _MAPIMP long int _MAPAPI mapGetMtdPointBlockColumn(HMAP hMap, long int number);  // 02/04/13

  // ��������� �� MTD-������ ���� ����� ������� MTDXYHC �� ������ ������ � ������� �����
  // ������ ����� � �������� � �������� ������ �����
  // number - ����� ����� � �������
  // ���������� ����� ������� �������� ����� MTDXYHC
  // ��� ������ ���������� ����

  _MAPIMP MTDXYHC * _MAPAPI mapGetMtdPointBlockAddress(HMAP hMap, long int number,  // 02/04/13
                                               long int row,
                                               long int column);

  // ��������� �� MTD-������ ���� ����� ������� MTDXYHCLAS �� ������ ������ � ������� �����
  // ������ ����� � �������� � �������� ������ �����
  // number - ����� ����� � �������
  // ���������� ����� ������� �������� ����� MTDXYHCLAS
  // ��� ������ ���������� ����

  _MAPIMP MTDXYHCLAS * _MAPAPI mapGetMtdPointBlockLasAddress(HMAP hMap, long int number,  // 02/04/13
                                                     long int row,
                                                     long int column);



  /*********************************************************
  *                                                        *
  *        ���������� ������������ ������� �����           *
  *                                                        *
  *********************************************************/

  // ���������/���������� ������� ��������� �������
  //  number - ����� ����� � �������
  //  view = 0 - �� �����
  //  view = 1 - ������
  //  view = 2 - ����������
  //  view = 3 - ��������������
  //  view = 4 - �������
  //  view = 5 - ����������
  // ��� ������ ���������� 0
  
  _MAPIMP long int _MAPAPI mapGetMtdView(HMAP hMap,long int number);
  _MAPIMP long int _MAPAPI mapSetMtdView(HMAP hMap,long int number,
                                           long int view);

  // ���������/���������� ������� ����������� �������
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� 0
  
  _MAPIMP long int _MAPAPI mapGetMtdViewOrder(HMAP hMap, long int number);
  _MAPIMP long int _MAPAPI mapSetMtdViewOrder(HMAP hMap, long int number,long int order);

  // ����������� ������� ����������� �������(������������ �����)
  // ���������� 1 - ��� ����������� ������� �� �����
  //            0 - ��� ����������� ������� ��� ����� �����
  // ��� ������ ���������� -1

  _MAPIMP long int _MAPAPI mapCheckShowMtdByBorder(HMAP hMap,long int number);

  // �������� ����������� ����������� ������ � �������
  //   oldNumber - ����� ����� � �������
  //   newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0

  _MAPIMP long int _MAPAPI mapChangeOrderMtdShow(HMAP hMap, long int oldNumber,
                                        long int newNumber);

  // ��������� �������� ������ � ������ (�����)                                      
  //  ��� ������ ���������� 0
  
  _MAPIMP long int _MAPAPI mapGetMtdFrame(HMAP hMap, long int number, DFRAME * dframe);  

  // ������ ������������ � ������������� �������� ������ ����������� (�����)
  //  ��� ������ ���������� 0
    
  _MAPIMP long int _MAPAPI mapGetMtdHeightValue(HMAP hMap, long int number, 
                                                double * minvalue, double * maxvalue);                                       

}

#endif // MTDAPI_H
