/****** MTLAPI.H *************** Gorbunov A.V.   ****** 06/09/16 ***
******* MTLAPI.H *************** Kruzhkov A.E.   ****** 24/10/00 ***
******* MTLAPI.H *************** Shabakov D.A.   ****** 08/12/03 ***
******* MTLAPI.H *************** Belenkov O.V.   ****** 11/09/16 ***
******* MTLAPI.H *************** Derevaygina Zh.A.***** 27/02/13 ***
******* MTLAPI.H *************** ������ �.�.      ***** 14/03/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*            �������� ������� ������� � ������� �����              *
*                                                                  *
*   ��������� :                                                    *
*                                                                  *
*   ��������� �������� ������� ����� (MTLBUILDPARM, BUILDMTL)      *
*   �������� �������� ������� ����� (MTLDESCRIBE)                  *
*                                                                  *
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

#ifndef MTLAPI_H
#define MTLAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h" 
#endif

//------------------------------------------------------------------
//  ��������� �������� ������� �����                  25/04/14
//------------------------------------------------------------------
typedef struct BUILDMTL     // ������ ��������� 160 ����
{
  unsigned
  int StructSize;     // ������ ������ ��������� : sizeof (BUILDMTL)
  int Free;           // ������ ���� ����

  double   BeginX;    // ������������� ���������� ������
  double   BeginY;    // (���-��������� ����) ������� � ������

  double   EndX;      // ������������� ���������� ���������
  double   EndY;      // (������ - ���������� ����) ������� � ������

  double   ElemSizeMeters; // ������ ������� ������������� �������
                           // � ������ �� ���������

  int LayerCount;     // ���������� �����

  int LayerForm;      // ����� ������������� ���-��� � �����
                      // ���������� �������� :
                      //  0 - �������� �����
                      //  1 - ��������� ������

  int HeightSizeBytes; // ������ ������ ������� � ������
                       // ���������� �������� :
                       //  0 - ������ �����������,
                       //  2 - ������ "short int"
                       //  4 - ������ "long int"

  int LayerSizeBytes;  // ������ �������� ���� � ������
                       // ���������� �������� :
                       //  1 - �������� "unsigned char"
                       //  2 - �������� "unsigned short int"
                       //  4 - �������� "unsigned long int"

  int HeightMeasure;  // E������ ��������� ������
                      // ���������� �������� :
                      //  0 - �����
                      //  1 - ���������
                      //  2 - ����������
                      //  3 - ����������

  int LayerMeasure;   // E������ ��������� �������� ����
                      // ���������� ��������
                      // - �� ��,��� ��� HeightMeasure

  int UserType;       // ������������ �����, �����������
                      // � ����������� ��������

  int Scale;          // �������

  int BlockSide;      // ������ ������� ����� ������� � ���������
                      // ���������� �������� : 0 - 64
                      //  (���� ����� 0, ������������ �������� 64)

  int CodeCount;      // ���������� ����� �����          10/06/08
  int MtdPointFormat; // ������ ����� MTD-������ :       04/09/09
                      //   0 - ��������� ����� MTDXYHC (16 ����)
                      //   1 - ��������� ����� MTDXYHCLAS (24 �����)


  char Reserve[68];   // ������ ���� ����
}
  BUILDMTL;


//------------------------------------------------------------------
//  ��������� �������� ������� ����� (���������� ���������)
//------------------------------------------------------------------
typedef struct MTLBUILDPARM     // ������ ��������� 128 ����
{
  unsigned
  long int StructSize;     // ������ ������ ��������� :
                           //  sizeof (MTRLAYERBUILDPARM)

  double   BeginX;         // ������������� ���������� ������
  double   BeginY;         // (���-��������� ����) ������� � ������

  double   EndX;           // ������������� ���������� ���������
  double   EndY;           // (������ - ���������� ����) ������� � ������

  double   ElemSizeMeters; // ������ ������� ������������� �������
                           // � ������ �� ���������

  long int LayerCount;     // ���������� �����

  long int LayerForm;      // ����� ������������� ���-��� � �����
                           // ���������� �������� :
                           //  0 - �������� �����
                           //  1 - ��������� ������

  long int HeightSizeBytes; // ������ ������ ������� � ������
                            // ���������� �������� :
                            //  0 - ������ �����������,
                            //  2 - ������ "short int"
                            //  4 - ������ "long int"

  long int LayerSizeBytes;  // ������ �������� ���� � ������
                            // ���������� �������� :
                            //  1 - �������� "unsigned char"
                            //  2 - �������� "unsigned short int"
                            //  4 - �������� "unsigned long int"

  long int HeightMeasure;  // E������ ��������� ������
                           // ���������� �������� :
                           //  0 - �����
                           //  1 - ���������
                           //  2 - ����������
                           //  3 - ����������

  long int LayerMeasure;   // E������ ��������� �������� ����
                           // ���������� ��������
                           // - �� ��,��� ��� HeightMeasure

  long int UserType;       // ������������ �����, �����������
                           // � ����������� ��������

  long int Scale;          // �������

  char     Reserve[52];     // ������ ���� ����
}
  MTLBUILDPARM;


//------------------------------------------------------------------
//  �������� �������� ������� ����� (������ ��������� 1024 �����)
//------------------------------------------------------------------
typedef struct MTLDESCRIBE
{
  char  Name[260];              // ��� ����� �������
  char  MaterialFileName[260];  // ��� ����� �������� ����������

  long  LayerCount;      // ���-�� �����
  long  MaterialCount;   // ���-�� ����������

  double ElementInPlane; // ������ �������� � ������ �� ���������

  DFRAME FrameMeters;    // �������� ������� � ����� (�����)

  double MinHeightValue; // ����������� �������� ������ �������� � ������� (�����)
  double MaxHeightValue; // ������������ �������� ������ �������� � ������� (�����)

  double BotLevelHeight; // ������ �������� ������� ������� ������ (�����)  // 24/10/00

  long   UserType;       // ��� ���������������� ������
  long   View;           // ������� ��������������
  long   UserLabel;      // ���������������� �������������
  long   ReliefPresence; // ������� ������� �������  17/01/01

  double MaxSummaryPower; // ������������ ��������� ��������
                          // �����  (�����)  // 17/05/01

  char   Reserve[408];   // ������

}
  MTLDESCRIBE;

// �������� - ���������� ����� ������� � ������ �������,
//            ��������������� ��'����� ���� �� ���,
//            ���������������� �������������� ���������
//            (����������� ����� �����).

//------------------------------------------------------------------
//  �������� �������� ������� �����                03/04/14
//------------------------------------------------------------------
typedef struct MTLDESCRIBEUN
{
  WCHAR Name[MAX_PATH_LONG];              // ��� ����� �������
  WCHAR MaterialFileName[MAX_PATH_LONG];  // ��� ����� �������� ����������

  DFRAME FrameMeters;     // �������� ������� � ����� (�����)

  double ElementInPlane;  // ������ �������� � ������ �� ���������

  double MinHeightValue;  // ����������� �������� ������ �������� � ������� (�����)
  double MaxHeightValue;  // ������������ �������� ������ �������� � ������� (�����)

  double BotLevelHeight;  // ������ �������� ������� ������� ������ (�����)

  double MaxSummaryPower; // ������������ ��������� �������� �����  (�����)

  int   LayerCount;       // ���-�� �����
  int   MaterialCount;    // ���-�� ����������

  int   UserType;         // ��� ���������������� ������
  int   View;             // ������� ��������������

  int   UserLabel;        // ���������������� �������������
  int   ReliefPresence;   // ������� ������� �������

  char  Reserve[64];      // ������

}
  MTLDESCRIBEUN;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ �������� ������� ������� � �������� ����� +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{

  // ������� ��������� ������
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // mtrname - ��� ������������ �����
  // mode - ����� ������/������ (GENERIC_READ, GENERIC_WRITE ��� 0)
  // GENERIC_READ - ��� ������ ������ �� ������
  // ��� ������ ���������� ����

_MAPIMP HMAP _MAPAPI mapOpenMtl(const char * mtrname,long int mode = 0);
_MAPIMP HMAP _MAPAPI mapOpenMtlUn(const WCHAR *mtrname, long int mode = 0);  // 28/01/14


  // ������� ��������� ������ � �������� ������ �����
  // (�������� � ������� ������)
  // ���������� ����� ����� � ������� ������
  // hMap - ������������� �������� �������� �����
  // mtrname - ��� ������������ �����
  // mode - ����� ������/������ (GENERIC_READ, GENERIC_WRITE ��� 0)
  // GENERIC_READ - ��� ������ ������ �� ������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapOpenMtlForMap(HMAP hMap, const char * mtrname, long int mode);
_MAPIMP long int _MAPAPI mapOpenMtlForMapUn(HMAP hMap, const WCHAR * mtrname, long int mode);  // 28/01/14


  // ������� ��������� ������
  // hMap - ������������� �������� �������� �����
  // number - ����� ����������� ������� � ������� ������
  // ���� number == 0, ����������� ��� ��������� ������

_MAPIMP void _MAPAPI mapCloseMtl(HMAP hMap,long int number = 0);

  // ������� ��������� ������ � �������� ������ �����
  // hMap - ������������� �������� �������� �����
  // number - ����� ���������� ����� � �������
  // ���� number == 0, ����������� ��� ��������� ������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapCloseMtlForMap(HMAP hMap,
                                     long int number);

  // ���������� ������� �� �������� ������� ������ �����
  // ��� ������ ���������� ����
  // hMap    - ������������� �������� ����� ��� ���������� �������,
  // mtrname - ������ ��� ����� ����������� �������,
  // ininame - ������ ��� ����� ������� ����������� �������,
  // mtrparm - ��������� ����������� �������,
  // ��������a BUILDMTL ������a � mtlapi.h
  // hselect - ������������� ��������� ������ �������� �����,
  // handle  - ������������� ���� �������, �������� ����������
  // ��������� � ���� �������� :
  //  0x0378 - ��������� � �������� ����������� ����� (� WPARAM),
  //  ���� ������� ������ ���� ������������� ��������, � �����
  //  ������ ��������� �������� 0x0378.
  // ���� handle ����� ���� - ��������� �� ����������.

_MAPIMP long int _MAPAPI mapBuildMtlEx(HMAP hMap,
                                 const char * mtrname,
                                 const char * ininame,
                                 BUILDMTL * mtrparm,
                                 HSELECT  hselect,
                                 HWND     handle);

_MAPIMP long int _MAPAPI mapBuildMtlUn(HMAP hMap,       // 10/06/16
                                 const WCHAR * mtrname,
                                 const WCHAR * ininame,
                                 BUILDMTL * mtrparm,
                                 HSELECT  hselect,
                                 HWND     handle);

  // ���������� ������� �� �������� ������� ������ ����� (����������)
  // ��� ������ ���������� ����
  // hMap    - ������������� �������� ����� ��� ���������� �������,
  // mtrname - ������ ��� ����� ����������� �������,
  // ininame - ������ ��� ����� ������� ����������� �������,
  // mtrparm - ��������� ����������� �������,
  // ��������a MTLBUILDPARM ������a � mtlapi.h
  // hselect - ������������� ��������� ������ �������� �����,
  // handle  - ������������� ���� �������, �������� ����������
  // ��������� � ���� �������� :
  //  0x0378 - ��������� � �������� ����������� ����� (� WPARAM),
  //  ���� ������� ������ ���� ������������� ��������, � �����
  //  ������ ��������� �������� 0x0378.
  // ���� handle ����� ���� - ��������� �� ����������.

_MAPIMP long int _MAPAPI mapBuildMtl(HMAP hMap,
                               const char * mtrname,
                               const char * ininame,
                               MTLBUILDPARM * mtrparm,
                               HSELECT  hselect,
                               HWND     handle);


  /*********************************************************
  *                                                        *
  *           ������ ������ �� ������� �����               *
  *                                                        *
  *********************************************************/

  // ��������� �������� ����� ��������� ������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // describe - ����� ���������, � ������� ����� ���������
  // �������� �������
  // ��������a MTLDESCRIBE ������a � mtlapi.h
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlDescribe(HMAP hMap,long int number,
                                     MTLDESCRIBE * describe);

_MAPIMP long int _MAPAPI mapGetMtlDescribeUn(HMAP hMap,long int number,  // 06/09/16
                                     MTLDESCRIBEUN * describe);

  // ��������� ��� ����� ��������� ������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP const char * _MAPAPI mapGetMtlName(HMAP hMap,long int number);

  // ��������� ��� ����� ��������� ������
  // hMap - ������������� �������� �������� ��������� �����
  // number - ����� ����� � �������
  // name - ����� ������ ��� ���������� ����������
  // size - ������ ������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlNameUn(HMAP hMap,long int number,  // 28/01/14
                                         WCHAR *name, long int size);

  // ��������� ����� �������� ������ ��������� ������
  // hMap - ������������� �������� �������� �����
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlCount(HMAP hMap);

  // ��������� ������������ ���������� ����� ���� ������ MTL-�������
  // hMap - ������������� �������� �������� �����
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMaxLayerCount(HMAP hMap);

  // ��������� ���������� ����� ������� � ������� number � �������.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetLayerCountOfMtl(HMAP hMap,long int number);

  // ��������� ����������� ������ ������� ������
  // hMap - ������������� �������� �������� �����
  // ��� ������ ���������� ERRORHEIGHT

_MAPIMP double _MAPAPI mapGetMinBotLevelHeight(HMAP hMap);    // 24/10/00

  // ��������� ������������ ��������� �������� �����
  // hMap - ������������� �������� �������� �����
  // ��� ������ ���������� ERRORPOWER

_MAPIMP double _MAPAPI mapGetMaxSummaryPower(HMAP hMap);    // 17/05/01

  // ����� �������� ���������� ������ � �������� �����.
  // hMap - ������������� �������� �������� �����
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

_MAPIMP double _MAPAPI mapGetElementHeight(HMAP hMap,double x,double y);

  // ����� �������� ���������� ������ � �������� ����� �� �������
  // � ������� number � �������.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

_MAPIMP double _MAPAPI mapGetElementHeightOfMtl(HMAP hMap,long int number,double x,double y);

  // ����� �������� �������� ���� � �������� �����.
  // hMap - ������������� �������� �������� �����
  // layernumber - ����� ����
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� �������� ���� � ������.
  // � ������ ������ � � ������ ���������������� ��������
  // ����� ���������� ������� ���������� ERRORPOWER.

_MAPIMP double _MAPAPI mapGetElementPower(HMAP hMap,double x,double y,long layernumber);

  // ����� �������� �������� ���� � �������� ����� �� �������
  // � ������� number � �������.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� �������� ���� � ������.
  // � ������ ������ � � ������ ���������������� ��������
  // ����� ���������� ������� ���������� ERRORPOWER.

_MAPIMP double _MAPAPI mapGetElementPowerOfMtl(HMAP hMap,long int number,
                                         double x,double y,long layernumber);

  // ���������� �������� ��������� ����� � �������� �����
  // ������� ������������� �� ������� � ������� number � �������.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����
  // powers - ����� ������� ��� ������ ����������� ��������
  //          ��������� (� ������)
  // count - ������ �������, ������ ���� �� ����� mapGetLayerCountOfMtl()
  // ���������� ���������� ����������� ��������� ������� powers
  // ��� ������ ���������� ����.

_MAPIMP long int _MAPAPI mapGetElementPowersTriangleOfMtl(HMAP hMap,long int number,
                                                    double x,double y,
                                                    double* powers,long int count);

  // ���������� �������� �������� ���� layernumber � �������� �����
  // ������� ������������� �� ������� � ������� number � �������.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����
  // layernumber - ����� ����
  // ���������� �������� �������� ���� � ������.
  // ��� ������ ���������� ERRORPOWER.

_MAPIMP double _MAPAPI mapGetElementPowerTriangleOfMtl  
                   (HMAP hMap,long int number,
                    double x,double y,long int layernumber);

  // ��������� �������� ���������� ������ � ������� �������,
  // ��������������� �������� �����.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ���������� ����� (x,y) � �������� ������ (h) �������� � ������
  // � ������� ��������� ��������� �����.
  // � ������ ������ ���������� ����.

_MAPIMP long int _MAPAPI mapPutElementHeight(HMAP hMap,long int number,
                                       double x, double y, double h);


  // ��������� �������� �������� ���� layernumber � �������,
  // ��������������� �������� �����.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ���������� ����� (x,y) � �������� �������� (power) ��������
  // � ������ � ������� ��������� ��������� �����
  // layernumber - ����� ����
  // � ������ ������ ���������� ����.

_MAPIMP long int _MAPAPI mapPutElementPower(HMAP hMap,long int number,
                                      double x,double y,double power,
                                      long int layernumber);

  // ��������� ����� � ������� ��� �������, �������������
  // � �������� �����
  // hMap - ������������� �������� �������� �����
  // number - ���������� �����, ��������� ������� � �����
  // (1 - ������ � ������ �����, 2 - ������ ...)
  // � ������ ������ ���������� ����.

_MAPIMP long int _MAPAPI mapGetMtlNumberInPoint(HMAP hMap,double x, double y,
                                          long int number);

  // ��������� ����� � ������� ��������� �������� �������
  // � ������������� (������ 1) ��������� ���������.
  // hMap - ������������� �������� �������� �����
  // � ������ ������ ���������� ����.

_MAPIMP long int _MAPAPI mapGetMtlNumberLastVisible(HMAP hMap);

  // ��������� ������ ������� ����� ������� � ������
  // hMap - ������������� �������� �������� �����
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlBlockSize(HMAP hMap,long int number);

  // ��������� ������������ ������ ����� ������� � ���������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlBlockSide(HMAP hMap,long int number);  // 28/11/07

  // ��������� ����� ����� ������� �� ������ ������ � �������
  // ����� ���������� ���� ����� ����� ��������� ������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������� ���������� ����� ����� ������� ������� �����
  // ���������� ����� ���������� �����
  // ��� ������ ���������� ����

_MAPIMP char *  _MAPAPI mapGetMtlBlockAddress(HMAP hMap,long int number,
                                                  long int row,
                                                  long int column);

  // ��������� ����� ����� ������ �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlBlockRow(HMAP hMap,long int number);

  // ��������� ����� �������� ������ �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlBlockColumn(HMAP hMap,long int number);

  // ��������� ����� ����� ��������� � �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlElementRow(HMAP hMap,long int number);

  // ��������� ����� �������� ��������� � �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlElementColumn(HMAP hMap,long int number);

  // ����� ������� �������� ���������� �����, ���������������
  // ���������� ���������, ������� �� �������� �������.
  // hMap - ������������� �������� �������� �����
  // ���������� �����, �������� ������ � ����� �������
  // (FirstPoint,SecondPoint) �������� � ������ � �������
  // ��������� ��������� �����.
  // ������ ������� �����, ��������� ������� HeightArray,
  // ������ ��������������� �������������� ���������� �����
  // (HeightCount), � ��������� ������ �������� ������ ������
  // � �������.
  // � ������ ���������������� ����������� �������� ����������
  // ������� ��� �������� ����� ERRORHEIGHT (-111111.0 �)
  // � ������ ������ ��� ������ ����� ���������� ����.

_MAPIMP long int _MAPAPI mapGetHeightArrayFromMtl(HMAP   hMap,
                                            double*   HeightArray,
                                            long int  HeightCount,
                                            const DOUBLEPOINT*  FirstPoint,  // 12/02/09 const
                                            const DOUBLEPOINT*  SecondPoint);


  // ����� �������� ����� ���� layernumber
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // � ������ ������ ���������� ����.

_MAPIMP COLORREF _MAPAPI mapGetLayerColor(HMAP hMap,long int number,long int layernumber);

  // ����� ��������� ����� (���� ���������) ���� layernumber.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // � ������ ������ ���������� ����.

_MAPIMP char* _MAPAPI mapGetLayerShortName(HMAP hMap,long int number,long int layernumber);

  // ����� ����� (�������� ���������) ���� layernumber.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // � ������ ������ ���������� ����.

_MAPIMP char* _MAPAPI mapGetLayerLongName(HMAP hMap,long int number,long int layernumber);

  // ����� ������������ �������� ���� layernumber � ������.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // � ������ ������ ���������� ����.

_MAPIMP long int _MAPAPI mapGetMaxLayerHeight(HMAP hMap,long int number,long int layernumber);

  // ��������� ������������ �������� ���� layernumber � ������.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // � ������ ������ ���������� ����.

_MAPIMP long int _MAPAPI mapSetMaxLayerHeight(HMAP hMap,long int number,long int layernumber,long int maxlayerheight);

  // ��������� �������� ����� ���� layernumber.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // � ������ ������ ���������� ����.

_MAPIMP long int _MAPAPI mapSetLayerColor(HMAP hMap,long int number,
                                    long int layernumber,
                                    COLORREF layercolor);

  // ��������� ��������� ����� (���� ���������) ���� layernumber.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // layername - �������� ��� (���� ���������)
  // � ������ ������ ���������� ����.

_MAPIMP char* _MAPAPI mapSetLayerShortName(HMAP hMap,long int number,
                                     long int layernumber,
                                     char* layername);

  // ��������� ����� (�������� ���������) ���� layernumber.
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // layernumber - ����� ����
  // layername - �������� ���������
  // � ������ ������ ���������� ����.

_MAPIMP char* _MAPAPI mapSetLayerLongName(HMAP hMap,long int number,
                                    long int layernumber,
                                    char* layername);

  // ��������� ������ � �������� ��������� ������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // projectiondata - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��������a MTRPROJECTIONDATA ������a � maptype.h
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlProjectionData
                     (HMAP hMap,long int number,
                      MTRPROJECTIONDATA * projectiondata);

  /*********************************************************
  *                                                        *
  *     �������� ������� ��� �������� ������ �����         *
  *                                                        *
  *********************************************************/

  // ������� ��������� �����
  // mtrname - ������ ��� ����� �������
  // mtrparm - ��������� ����������� �������
  // ��������a BUILDMTL ������a � mtlapi.h
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // ��� ������ ���������� ����

_MAPIMP HMAP _MAPAPI mapCreateMtlEx(const char * mtrname, BUILDMTL * mtrparm);
_MAPIMP HMAP _MAPAPI mapCreateMtlUn(const WCHAR * mtrname, BUILDMTL * mtrparm);  // 28/01/14


  // ������� ���� �������
  // hMap - ������������� �������� �������� �����
  // mtrname - ������ ��� ����� �������
  // mtrparm - ��������� ����������� �������
  // mtrprojectiondata - ��������� �������� ����������� �������
  // ��������a BUILDMTL ������a � mtlapi.h
  // ��������a MTRPROJECTIONDATA ������a � maptype.h
  // ���������� ����� ����� � ������� ������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapCreateAndAppendMtlEx(HMAP hMap,
                                           const char * mtrname,
                                           BUILDMTL * mtrparm,
                                           MTRPROJECTIONDATA * mtrprojectiondata);

_MAPIMP long int _MAPAPI mapCreateAndAppendMtlUn(HMAP hMap,         // 28/01/14
                                           const WCHAR * mtrname,
                                           BUILDMTL * mtrparm,
                                           MTRPROJECTIONDATA * mtrprojectiondata);

  // ������� ��������� ����� (����������)
  // mtrname - ������ ��� ����� �������
  // mtrparm - ��������� ����������� �������
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // ��������a MTLBUILDPARM ������a � mtlapi.h
  // ��� ������ ���������� ����

_MAPIMP HMAP _MAPAPI mapCreateMtl(const char * mtrname,MTLBUILDPARM * mtrparm);

  // ������� ���� ������� (����������)
  // hMap - ������������� �������� �������� �����
  // mtrname - ������ ��� ����� �������
  // mtrparm - ��������� ����������� �������
  // mtrprojectiondata - ��������� �������� ����������� �������
  // ��������a MTLBUILDPARM ������a � mtlapi.h
  // ��������a MTRPROJECTIONDATA ������a � maptype.h
  // ����������  ����� ����� � ������� ������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapCreateAndAppendMtl(HMAP hMap,
                                         const char * mtrname,
                                         MTLBUILDPARM * mtrparm,
                                         MTRPROJECTIONDATA * mtrprojectiondata);


  // �������� ��������� ������� � ����
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapSaveMtl(HMAP hMap,long int number);

  // ���������� �������� ������������ ��������� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // minvalue - ����������� �������� ������������� ��������
  //            � �������� �������
  // maxvalue - ������������ �������� ������������� ��������
  //            � �������� �������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapSetMtlShowRange(HMAP hMap,
                                      long int number,
                                      double minvalue,
                                      double maxvalue);

  // ���������� ������ ������� ����� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // botlevel - ������ ������� ����� � ������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapSetMtlBotLevel(HMAP hMap,
                                     long int number,
                                     double botlevel);

  // ���������� ������������ ��������� �������� ����� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // maxsummarypower - ������������ ��������� �������� � ������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapSetMtlMaxSummaryPower(HMAP hMap,
                                            long int number,
                                            double maxsummarypower);

  // ���������� ������ � �������� ��������� ������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // mapregister - ����� ���������, ���������� ������ � ��������
  // ��������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM ������� � mapcreat.h
  // ttype  - ��� ���������� �������������� ��������� (��. TRANSFORMTYPE � mapcreat.h) ��� 0
  // tparm - ��������� ���������� �������������� ��������� (��. mapcreat.h)
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapSetMtlProjectionDataPro(HMAP hMap,          // 11/09/16
                                                    long int number,
                                                    MAPREGISTEREX  *mapregister,
                                                    DATUMPARAM     *datumparam,
                                                    ELLIPSOIDPARAM *ellipsoidparam,
                                                    long int ttype,
                                                    LOCALTRANSFORM * tparm);

_MAPIMP long int _MAPAPI mapSetMtlProjectionData(HMAP hMap,
                                           long int number,
                                           MAPREGISTEREX* mapregister);

  // ��������� ������ � �������� �������
  // hMap   - ������������� �������� �������� ��������� �����
  // number - ����� ����� � �������
  // mapregister - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��������a MAPREGISTEREX ������a � mapcreat.h
  // ttype  - ��� ���������� �������������� ��������� (��. TRANSFORMTYPE � mapcreat.h) ��� 0
  // tparm - ��������� ���������� �������������� ��������� (��. mapcreat.h)
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlProjectionDataPro(HMAP hMap, long int number,     // 11/09/16
                                                    MAPREGISTEREX  *mapregister,
                                                    DATUMPARAM     *datumparam,
                                                    ELLIPSOIDPARAM *ellipsoidparam,
                                                    long int * ttype,
                                                    LOCALTRANSFORM * tparm);

_MAPIMP long int _MAPAPI mapGetMtlProjectionDataEx(HMAP hMap, long int number,
                                                   MAPREGISTEREX* mapregister);

  // ������ - �������������� �� �������� � �������������
  // ����������� �� ������� ������������� � �������
  // hMap     - ������������� �������� �������� �����
  // number   - ����� ����� � �������
  // ���� ��� - ���������� ����

_MAPIMP long int _MAPAPI mapIsMtlGeoSupported(HMAP hMap, long int number);

  // ��������� ��������� ���������� �������
  // hMap   - ������������� �������� �������� ��������� �����
  // number - ����� ����� ������� � �������
  // ellipsoidparam - ����� ���������, � ������� ����� ���������
  // ��������� ����������
  // ��������a ELLIPSOIDPARAM ������a � mapcreat.h
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlEllipsoidParam(HMAP hMap, long int number,  // 16/12/10
                                                 ELLIPSOIDPARAM * ellipsoidparam);

  // ���������� ��������� ���������� �������
  // hMap    - ������������� �������� �������� ��������� �����
  // number  - ����� ����� ������� � �������.
  // ellipsoidparam - ����� ���������, ���������� ��������� ����������
  // ��������a ELLIPSOIDPARAM ������a � mapcreat.h
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapSetMtlEllipsoidParam(HMAP hMap, long int number,  // 16/12/10
                                                 const ELLIPSOIDPARAM * ellipsoidparam);

  // ��������� ������������ ����������������� ������������� ��������� �������
  // hMap   - ������������� �������� �������� ��������� �����
  // number - ����� ����� ������� � �������
  // datumparam - ����� ���������, � ������� ����� ���������
  // ������������ ����������������� ������������� ���������
  // ��������a DATUMPARAM ������a � mapcreat.h
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlDatumParam(HMAP hMap, long int number,  // 16/12/10
                                             DATUMPARAM * datumparam);

  // ���������� ������������ ����������������� ������������� ��������� �������
  // hMap    - ������������� �������� �������� ��������� �����
  // number  - ����� ����� ������� � �������.
  // datumparam - ����� ���������, ���������� ������������ �����������������
  // ������������� ���������
  // ��������a DATUMPARAM ������a � mapcreat.h
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapSetMtlDatumParam(HMAP hMap, long int number,  // 16/12/10
                                             const DATUMPARAM * datumparam);

  /*********************************************************
  *                                                        *
  *   �������� ������� ��� ������ � ������ ������� �����   *
  *                                                        *
  *********************************************************/

  // ���������� ����� ������� �� ������� ���������� �������
  // ��������� ������ ������ ����� �� ����� 4-� �����
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // number     - ����� ����� � �������
  // info       - ��������� ������ �����
  // ����� ���������� ������� ����������� ������� ����������� �������� ��������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapSetMtlBorder(HMAP hMap,long int number,HOBJ info);

  // ��������� ������ ����� �������               // 15/03/01
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlBorder(HMAP hMap,long int number,HOBJ info);

  // ������� ����� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ����� ���������� ������� ����������� ������� ����� ������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapDeleteMtlBorder(HMAP hMap,long int number);

  // ����������� ������������� ����� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ���� ����� ������� ���������� ���������� 1, ����� ���������� 0

_MAPIMP long int _MAPAPI mapCheckExistenceMtlBorder(HMAP hMap,long int number);

  // ����������� ������� ����������� �������(������������ �����)    // 02/10/03
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ���������� 1 - ��� ����������� ������� �� �����
  //            0 - ��� ����������� ������� ��� ����� �����
  // ��� ������ ���������� -1

_MAPIMP long int _MAPAPI mapCheckShowMtlByBorder(HMAP hMap,long int number);

  // ��������� ����������� ������� �� �����               // 29/05/09
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // value = 1 - ���������� ������� �� �����
  //       = 0 - ���������� ������� ��� ����� �����
  //  ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapShowMtlByBorder(HMAP hMap, long int number, int value);

  // ���������� ���������� � ���������� ����� ����� �����, ������� // 02/20/03
  // ������ � ������������� �������� ������(�������) �
  // ����� ���������� �������� �� ����� pointIn (���������� � ������)
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // �� ������ pointOut ������������ ���������� ��������� ����� � ������
  // ��� ������ ��� ���������� ����� ���������� ����

_MAPIMP long int _MAPAPI mapGetImmediatePointOfMtlBorder(HMAP hMap, long int number,
                                           DOUBLEPOINT* pointIn,
                                           DOUBLEPOINT* pointOut);

  // ��������� ���������� ���-��������� ���� ������� � ������     // 29/05/09
  // hMap    - ������������� �������� �������� ��������� �����
  // number  - ����� ����� � �������
  // �� ������ x,y ������������ ���������� ��������� ����� � ������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapWhereSouthWestMtlPlane(HMAP hMap,long int number,
                                                   double * x, double * y);  

  // ��������� ����������� �������� ������������ ������� � ������ � ������ �����   // 14/05/03
  // ��� ����������� ������� �� ����� ������������ �������� �����
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetActualMtlFrame(HMAP hMap,DFRAME *frame, long int number);

  // ��������� ������� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlScale(HMAP hMap,long int number);

  // ��������� �������� �������� ������ � ������� ������ ��������� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // �� ������ bottomScale ������������ ����������� �������� ������ ������� ��������� �������
  // �� ������ topScale ������������ ����������� �������� ������� ������� ��������� �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlRangeScaleVisible(HMAP hMap,long int number, long int *bottomScale, 
                                                    long int *topScale);  // 08/12/03

  // ���������� �������� �������� ������ � ������� ������ ��������� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // bottomScale - ����������� �������� ������ ������� ��������� �������
  // topScale    - ����������� �������� ������� ������� ��������� �������
  // ��� ������������ ������� bottomScale <= topScale ���������� ����
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapSetMtlRangeScaleVisible(HMAP hMap,long int number, long int bottomScale, 
                                                    long int topScale);   // 08/12/03


  // ��������� �������� �������
  // (��������������� ����������� �� ������ ����������)
  // hMap - ������������� �������� �����
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetActiveMtl(HMAP hMap);  // 29/05/09

  // ���������� �������� �������
  // (��������������� ����������� �� ������ ����������)
  // hMap - ������������� �������� �����
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapSetActiveMtl(HMAP hMap, long int number);  // 29/05/09

  // ��������� ���� ��������������� �������                 // 18/06/09
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetMtlEdit(HMAP hMap,long int number);


  // ��������� ������ �����             // 28/09/09
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // �� ������ fileSize ������������ ������ �����
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlFileSize(HMAP hMap,long int number,__int64 * fileSize);

  // ��������� ������ ������� (��������)             // 28/09/09
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlWidthInElement(HMAP hMap,long int number);

  // ��������� ������ ������� (��������)             // 28/09/09
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlHeightInElement(HMAP hMap,long int number);

  // ��������� �������� (����/����) �������             // 28/09/09
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlAccuracy(HMAP hMap,long int number);

  // ��������� ���� ��������� �������� (�����) �������             // 28/09/09
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetMtlFlagLocationChanged(HMAP hMap,long int number);

  /*********************************************************
  *                                                        *
  *          ���������� ������������ �������               *
  *                                                        *
  *********************************************************/

  // ���������/���������� ������� ��������� �������
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // view = 0 - ��� ���������
  // view = 1 - ������
  // view = 2 - ����������
  // view = 3 - ��������������
  // view = 4 - �������
  // view = 5 - ����������

_MAPIMP long int _MAPAPI mapGetMtlView(HMAP hMap,long int number);
_MAPIMP long int _MAPAPI mapSetMtlView(HMAP hMap,long int number,
                                           long int view);

  // ���������/���������� ������� ����������� �������        // 27/05/09
  // hMap - ������������� �������� �������� �����
  // number - ����� ������� � �������
  // order  - ������� ����������� (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapSetMtlViewOrder(HMAP hMap, long int number,
                                            long int order);
_MAPIMP long int _MAPAPI mapGetMtlViewOrder(HMAP hMap, long int number);

  // �������� ����������� ����������� ������ (mtl) � �������  // 27/02/13
  // oldNumber - ����� ����� � �������
  // newNumber - ��������������� ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapChangeOrderMtlShow(HMAP hMap, long int oldNumber,
                                                          long int newNumber);
}

#endif // MTLAPI_H
