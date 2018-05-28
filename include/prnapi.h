/****** PRNAPI.H *************** Kruzhkov  A.E.  ****** 24/12/09 ***
******* PRNAPI.H *************** Dishlenko S.G.  ****** 11/04/02 ***
******* PRNAPI.H *************** Shabakov  D.A.  ****** 25/12/13 ***
******* PRNAPI.H *************** Belenkov  O.V.  ****** 30/11/06 ***
******* PRNAPI.H *************** Vitsko    D.A.  ****** 13/04/06 ***
******* PRNAPI.H *************** Gorbunov  A.V.  ****** 04/09/08 ***
******* PRNAPI.H *************** Derevyagina Zh.A.***** 16/02/16 ***
******* PRNAPI.H *************** Kruzhkova  E.A. ****** 15/05/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*       ������� ������ � �������� ������ ����������� �����         *
*                                                                  *
*                   mapprint.dll, gisforms.dll                     *
*                                                                  *
*******************************************************************/

#ifndef PRNAPI_H
#define PRNAPI_H

/*******************************************************************
  ������� ������ � �������� ������ ����� :
********************************************************************

  // ��������� �������
  HPRINTER printer = prnLoadPrinter();

  // ������� ������ ������
  // (������ ���������� ��������� ����� ������������
  //  ������������� ��� ������� ������ "������")
  ret = prnMapPrint(hmap, printer, printparm, taskparm);

  // ��� �������� ���������� ������� ������������ �������� �� ����� 0
  if (ret != 0)
  {
    // �������� ������� ��� ������ ������ "�������"
    if (printparm->Regime == MPR_SELECTFRAME)
    {
      // ������� ���������������� ������� ������ ������������� �������
      // ...
    }

    // �������� ������� ��� ������ ������ "��������"
    if (printparm->Regime == MPR_CHANGEFRAME)
    {
      // ������� ���������������� ������� ��������� ������������� �������
      // ...
    }
  }

  // ���������� �������
  prnFreePrinter(printer);

********************************************************************
  ����������� :
********************************************************************

1. ������� prnMapPrint ����� ��������� ������� ������. ��� �����
   ��������������:
   a) ��� ��������� �������� � ���������� ������ (MPR_INITPARM);
   �) ��� ������� ������ � �������������� ����������� ��� ������
      ������� (MPR_PRINTONLY) - ��� ����������� �������� ������;
   �) ��� ������� ������ �� ������� (MPR_PRINTALL, MPR_PRINT,
      MPR_SELECTFRAME, MPR_CHANGEFRAME). � ������ MPR_PRINTALL
      ������� ������ ��������������� �� ��������� ������
      �������������;
   �) ��� ��������� ��������, ���������� ������, ������ � ���������
      ������� ������. ��� ������� �� ������ "�������" � "��������"
      ������ ����������� � ����������� ���� ����������, ���� Regime
      ��������������� ������ MPR_SELECTFRAME ��� MPR_CHANGEFRAME.

2. ��� ���������� �������������� �������� printer �� ����� ������
   ���������� ��������� � ������� ������� � ��� ��������� �����������.

3. ��� ������ ����� ��� ���� ��������� printparm ����� ���� ��������,
     ����� ���� Length. ��� ���� ������ ��������� ������ ���������
     MAPPRINTPARM.
   ��� ���������� ������� printparm � ������������ ������� �������
     ��������� � ������� ��������� ������ �����������.
   ��� ����������� ����� � ���������� ������ (VT_PRINT) � ����
     � ��������������� Handle � ��������� ������������� �������
     ��������� �������� ������������ ��������� ���� ����� (�����������)
     � ������ �������� �������������. ��� Handle ������ ���� ����
     ����� �� �����������.

4. ���� Handle ������� taskparm ������ ��������� �������������
   �������� ����. ��������� TASKPARM ������� � maptype.h.
   ���� � TASKPARM ����������� ������ ��� ����� ".hlp",
   �� ���� ���� ������ ��������� ����� � ������� 5037,
   ������� ����� ���������� ��� ������� ������ "������".

*******************************************************************/

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif


#ifdef WIN32API                                // 16/02/16
#if defined(PRINT_DLL)
 #define _PRINTAPI  WINAPI
 #define _PRINTIMP  __declspec( dllexport )
#else
 #define _PRINTAPI  WINAPI
 #define _PRINTIMP  __declspec( dllimport )
#endif
#else
#if defined(PRINT_DLL)
 #define _PRINTAPI  WINAPI
 #define _PRINTIMP
#else
 #define _PRINTAPI  WINAPI
 #define _PRINTIMP
#endif
#endif

struct MAPPRINTPARM;
struct MAPPRINTPARMEX;
struct PRINTERINFO;                                     // 24/12/09

extern "C"
{

 // ��������� �������

_PRINTIMP HPRINTER _PRINTAPI prnLoadPrinter();


 // ���������� �������

_PRINTIMP void _PRINTAPI prnFreePrinter(HPRINTER printer);


 // ������ �����
 //  hmap      - ������������� �����
 //  printer   - ������������� ���������� ������
 //  printparm - ��������� ������� ������ ����� (���� Length ������
 //              ��������� ������ ���������)
 //  taskparm  - ��������� ������ (���� Handle ������ ���������
 //              ������������� �������� ����)
 //  title     - ��������� �������
 // ��� ������ ���������� 0

_PRINTIMP long int _PRINTAPI prnMapPrint(HMAP hmap, HPRINTER printer,
                                        MAPPRINTPARM* printparm,
                                        TASKPARM* taskparm);

_PRINTIMP long int _PRINTAPI prnMapPrintTitle(HMAP hmap, HPRINTER printer,
                                             MAPPRINTPARM* printparm,
                                             TASKPARM* taskparm, char* title);

_PRINTIMP long int _PRINTAPI prnMapPrintEx(HMAP hmap, HPRINTER printer,
                                          MAPPRINTPARMEX* printparm,
                                          TASKPARM* taskparm, char* title);

 // ����� ��������� ������ ����� � ��������
 //  hmap      - ������������� �����
 //  printer   - ������������� ���������� ������
 //  printparm - ��������� ������� ������ (���� Length ������
 //              ��������� ������ ���������)
 //  parm      - ��������� ������ (���� Handle ������ ���������
 //              ������������� �������� ����)
 //  title     - ��������� �������
 // ���������� �������� ����� ������������ � ���������� ..\Print
 // �������� ��������� ��������� (������ Print.mpt).
 // ������ Print.mpt �������� ���������� �� ��������� �����
 // ����� ���������, ��������� � ��������� ������.
 // ��� ������ ���������� 0

_PRINTIMP long int _PRINTAPI prnMapPrintSelect(HMAP hmap, HPRINTER printer,
                                              MAPPRINTPARMEX* printparm,
                                              TASKPARM* parm, char* title);

// ��������� ������� �������������� ���������� ������
//   printer     - ������������� ���������� ������ ����������:
//                 (HPRINTER)(MapWindow->GetPrinter()).
//                 ���� printer = 0, �� ������������� ��������������
//                 ���������� ������, �������������� � Windows �� ���������)
//   printerinfo - �������� �������������� ���������� ������
// ��� ������ ���������� 0

_PRINTIMP long int _PRINTAPI prnPrinterInfo(HPRINTER printer,
                                           PRINTERINFO* printerinfo);  // 24/12/09

} // extern "C"

//-----------------------------------------------------------------
// ��������� ������� ������ �����
//-----------------------------------------------------------------

typedef struct MAPPRINTPARM
{
  int  Length;          // ����� ��������� MAPPRINTPARM
#ifdef _M_X64                                                                   // 25/12/13
  int  MapPrintParmZero;// ������������                                         // 25/12/13
#endif
  HWND Handle;          // ������������� ���� �����
                                                           // 0x008 (8)
  int  Scale;           // ������� ������ (�����������)
  int  ScaleSave;       // ������� ������ (����������� ��� FitToPage = 1)
                                                           // 0x010 (16)
  RECT RectMetr;        // ������������� ������ � ������ (� ������)
                                                           // 0x020 (32)
  int  ShiftLTmm;       // �������� (� �����������)
  int  ShiftUPmm;       //
                                                           // 0x028 (40)
  int  FieldLTmm;       // ���� �������� (� �����������)
  int  FieldUPmm;       //
  int  FieldRTmm;       //
  int  FieldDNmm;       //
                                                           // 0x038 (56)
  int  Intensity;       // ������������� ������� ��������� (0-100)
  int  Copies;          // ���������� �����
                                                           // 0x040 (64)
  char Regime;          // ����� ������ ������ (��. MAPPRINT_REGIME)
  char Preview;         // ����� ������ ���� (��. MAPPRINT_PREVIEW)
  char TypePrint;       // ��� ������ (��. MAPPRINT_TYPE)
  char TypeOutput;      // ��� ������ (��. MAPPRINT_OUTPUT)
                                                           // 0x044 (68)
  char Orientation;     // ���������� (��. MAPPRINT_ORIENT)
  char File;            // ���� ���������� ������ (1 - ����, 0 - �������)
  char Border;          // ���� ������ ����� (1 - ����, 0 - ���)
  char FitToPage;       // ������������ � �������� ��������
                        //   (��. MAPPRINT_FITTING)
  char Black;           // ���� �����-����� ������ (1 - ����, 0 - ���)
  char Calibration;     // ���� ����� ������������� ����������
                        //   (1 - ���������, 0 - ���)
  char Mirror;          // ���� ����������� ������ (1 - ����, 0 - ���)
  char Reserve;         // ������ (������ ���� �������)
                                                           // 0x04C (76)
  char FileName[260];   // ��� ����� ������
}                                                          // 0x150 (336)
  MAPPRINTPARM;


typedef struct MAPPRINTPARMEX
{
  int Length;          // ����� ��������� MAPPRINTPARM
#ifdef _M_X64                                                                   // 25/12/13
  int MapPrintZero;     // ������������                                         // 25/12/13
#endif
  HWND Handle;          // ������������� ���� �����
                                                           // 0x008 (8)
  int  Scale;           // ������� ������ (�����������)
  int  ScaleSave;       // ������� ������ (����������� ��� FitToPage = 1)
                                                           // 0x010 (16)
  RECT RectMetr;        // ������������� ������ � ������ � ������
                        // (���� ������� - ������������� �� ��������� ������).
                        // ��� �������� ��������� ��������� �������
                        // (PlaneFrame) ������������
                                                           // 0x020 (32)
  int  ShiftLTmm;       // �������� (� �����������)
  int  ShiftUPmm;       //
                                                           // 0x028 (40)
  int  FieldLTmm;       // ���� �������� (� �����������)
  int  FieldUPmm;       //
  int  FieldRTmm;       //
  int  FieldDNmm;       //
                                                           // 0x038 (56)
  int  Intensity;       // ������������� ������� ��������� (0-100)
  int  Copies;          // ���������� �����
                                                           // 0x040 (64)
  char Regime;          // ����� ������ ������ (��. MAPPRINT_REGIME)
  char Preview;         // ����� ������ ���� (��. MAPPRINT_PREVIEW)
  char TypePrint;       // ��� ������ (��. MAPPRINT_TYPE)
  char TypeOutput;      // ��� ������ (��. MAPPRINT_OUTPUT)
                                                           // 0x044 (68)
  char Orientation;     // ���������� (��. MAPPRINT_ORIENT)
  char File;            // ���� ���������� ������ (1 - ����, 0 - �������)
  char Border;          // ���� ������ ����� (1 - ����, 0 - ���)
  char FitToPage;       // ������������ � �������� ��������
                        //   (��. MAPPRINT_FITTING)
  char Black;           // ���� �����-����� ������ (1 - ����, 0 - ���)
  char Calibration;     // ���� ����� ������������� ����������
                        //   (1 - ���������, 0 - ���)
  char Mirror;          // ���� ����������� ������ (1 - ����, 0 - ���)
  char CutLine;         // ���� ������ ����� ������� (1 - ����, 0 - ���)
                        //   (��� OverlapLT, OverlapUP,
                        //    OverlapRT ��� OverlapDN > 0) // 0x04C (76)
  char FileName[260];   // ��� ����� ������
                                                           // 0x150 (336)
  int  OverlapLTmm;     // ���� ���������� ����������� ��������
  int  OverlapUPmm;     //       ������� (� �����������)
  int  OverlapRTmm;     //
  int  OverlapDNmm;     //
                                                           // 0x160 (352)
  double PageWidth;     // ������� ���������� ������� �������� �� �������
  double PageHeight;    // ����� ���������� (� �����������)
                                                           // 0x170 (368)
  double Angle;         // ���� �������� ����� (� ��������)
                                                           // 0x178 (376)
  DFRAME PlaneFrame;    // �������� ��������� ������� � ������
                        // (���� ������� - ������������� �� ��������� ������).
                        //  X1,Y1 - 1 ����� ������������� �������
                        //  X2,Y2 - 3 ����� ������������� �������
                        // ��� TurnFrame = 1, ������� 1 � 3 ����� ���������
                        // ���������� ��������������, �� ������������ �����
                                                           // 0x198 (408)
  HSITE SiteDecor;      // ���������� ���������� (������ ���� �������)
                                                           // 0x19C (412)
  int  FrameKey;        // ����� ������� �����, �� �������� ���������������
                        // �������� ������� ������ PlaneFrame
                        // (���� ����� 0 ��� ������ �����������,
                        //  �� �������� ������������)
                                                           // 0x1A0 (416)

#ifdef _M_X64                                                                   // 25/12/13
  int MapPrintAddZero;  // ������������                                         // 25/12/13
#endif
  char FrameList[32];   // ��� ����� (������������) ������� FrameKey
                                                           // 0x1C0 (448)
  int  PaperWidth;      // ������ ����� (� �����������)
  int  PaperHeight;     //
                                                           // 0x1C8 (456)
  char ReserveEx[48];   // ������ (������ ���� �������)

  unsigned
  char PageCountHor;    // ����� ������� �� �����������                         // 15/05/14
                        // (������������ ��� FitToPage = MPF_FITBYHOR)
  unsigned
  char PageCountVer;    // ����� ������� �� ���������
                        // (������������ ��� FitToPage = MPF_FITBYVER)

  char FileCount;       // ����� ����������� ������ (������������ ��� PostScript = 1)
                        //   (1 - ���� �������� ��� ������������ ����� C,M,Y,K ��� R,G,B
                        //    4 - ������ �� ������� ������ �������� ���� ��
                        //        ������������ ����� C,M,Y,K)
                                                             // 0x1FB (507)
  char ColorModel;      // �������� ������ ������ � PostScript
                        //   (0 - RGB, 1 - CMYK)
  char PostScript;      // ���� PostScript-������
  char Restore;         // ���� ������������� �������������� ����������
                        //   �� INI-����� ����� (1 - ����, 0 - ���)
  char TurnFrame;       // ���� �������� ������� ������ (1 - ����, 0 - ���)
  char Decoration;      // ���� ����������� ���������� (������ ���� �������)
}                                                          // 0x200 (512)
  MAPPRINTPARMEX;

//-----------------------------------------------------------------
// �������� ����� ��������� ������� ������ �����
//-----------------------------------------------------------------

enum MAPPRINT_REGIME         // ����� ������ ������ "������ �����"
{
  MPR_PRINTONLY       = -2,  // ������ ������ ����� ��� ������ �������

  MPR_INITPARM        = -1,  // �������� ������� ������ ��� ���������
                             //  �������� � ���������� ������ (������
                             //  "�������" � "��������" ���������)

  MPR_PRINTALL        =  0,  // �������� ������� ��� ��������� ��������,
                             //  ���������� ������ � ������� ������ �����
                             //  � �������������� ���������� ������� ��
                             //  ��������� ������ (RectMetr - ������������)

  // ��� ����� ������������ ��� �������� ������� ��������� �������� 
  // ���������� ������ � ������� ������ ����� � ��������������
  // ���������� ������� �� RectMetr
  MPR_PRINT           =  1,  // ������
  MPR_SELECTFRAME     =  2,  // ����� ������������� ����� 
  MPR_CHANGEFRAME     =  3,  // ��������� � ����������� ������������� �����
  MPR_MOVEFRAME       =  4,  // ������ ����������� ������������� �����
  MPR_SELECTBYOBJECT  =  5,  // ����� ������� � ��������� ������������� �����
                             // �� ��������� �������

  MPR_SELECTTURNFRAME = 10,  // ���� ������ ����������� ���������

  // ��������, ����������� ����� Regime ��� ������� �� ������:
  // "������"     - MPR_PRINT;
  // "�������"    - MPR_SELECTFRAME ��� MPR_SELECTTURNFRAME;
  // "��������"   - MPR_CHANGEFRAME ��� 
  //                MPR_MOVEFRAME (��� FitToPage = MPF_ACCORDTOPAGE);
  // "�� �������" - MPR_SELECTBYOBJECT.
  // ����� ������, ��������� ��� ����������� ������� ������ �����
  // ������� ������ �������� �� ������� �������� ���� Regime.
};

enum MAPPRINT_PREVIEW   // ����� ������ ���� ���������. ���������
{
  MPV_SCHEME      = 0,  // ���������� ������� �� ���� �����
  MPV_MAP         = 1,  // ���������� ������� �� ���� �����
  MPV_INFO        = 2,  // ���������� �� ���������� ������
};

enum MAPPRINT_TYPE      // ��� ������
{
  MPT_NORMAL      = 3,  // ����������
  MPT_TRANSPARENT = 4,  // ����������
  MPT_CONTOUR     = 5,  // ���������
};

enum MAPPRINT_OUTPUT    // ��� ������
{
  // ������������ ���������� ������� WIN API (��� ������)

  MPO_VECTORIAL   = 0,  // ��������� (����� ������ ��������� ����)
  MPO_RASTERIAL   = 1,  // ��������� (����� ����, ������� � ������)

  // ������������ ������������ WIN API (��� �������� � PostScript-����)

  MPO_VECTORIALEX = 4,  // ��������� �����������
};

enum MAPPRINT_ORIENT    // ����������
{
  MPN_DEFAULT     = 0,  // ����� �� ������������ ������� ��������
  MPN_PORTRAIT    = 1,  // �������
  MPN_LANDSCAPE   = 2,  // ���������
};

enum MAPPRINT_FITTING   // ������������
{
  MPF_SPLITTOPAGES= 0,  // ������� �����������
  MPF_FITTOPAGE   = 1,  // ��������� �� ��������
  MPF_ACCORDTOPAGE= 2,  // �� ������� ��������
  MPF_FITBYHOR    = 3,  // ��������� �� �����������                  // 15/05/14
                        // (�� �������� ���������� �������)
  MPF_FITBYVER    = 4,  // ��������� �� ���������
};


//-----------------------------------------------------------------
// ��������� ������ �����  ��� ������� Print (mappaint.h, mapacces.h)
//-----------------------------------------------------------------

typedef struct PRINTPARM
{
  int  Length;          // ����� ��������� PRINTPARM
  int  Scale;           // ������� ������ (�����������)

  char TypePrint;       // ��� ������ (��. MAPPRINT_TYPE)
  char TypeOutput;      // ��� ������ (��. MAPPRINT_OUTPUT)
  char Mirror;          // ���� ����������� ������ (1 - ����, 0 - ���)
  char ColorModel;      // �������� ������ ������ ����� (0 - RGB, 1 - CMYK)  // 19/02/04
  char Technology;      // ���������� (��� ����������)
                        //   DT_PLOTTER    = 0  -  ��������� �������
                        //   DT_RASDISPLAY = 1  -  ��������� �������
                        //   DT_RASPRINTER = 2  -  ��������� �������
                        //   DT_METAFILE   = 5  -  ��������
  char Reserve[17];     // ������ (������ ���� �������)
  char Service;         // ��������� ���� (������ ���� �������)             // 04/09/12
  char DontClip;        // ������� �������                                  // 08/04/11 

  double HorPixInInch;  // �������� �� ���� �� �����������
  double VerPixInInch;  // �������� �� ���� �� ���������
}
  PRINTPARM;


//-----------------------------------------------------------------
// ��������� ��������� ���������� ��� ������� ���������� ����������� ����������
//-----------------------------------------------------------------

typedef struct FRAMEPRINTPARAM
{
    int DeleteSite;     // ������� �������� Site ����� ������
    int TurnFrame;      // ��� ����� (0 - ������, 1 - ���������)
    DFRAME PlaneFrame;  // �������� ����� ����������
    DFRAME ExpandFrame; // ����������� ���������� �������� �����
    double Angle;       // ���� ������� �����
    HSITE SiteDecor;    // ���������� ����������
    int EnableSite;     // ������/���������� �������������� Sit
#ifdef _M_X64                                                                   // 25/12/13
    int FramePrintZero; // ������������                                         // 25/12/13
#endif
}
  FRAMEPRINTPARAM;


//-----------------------------------------------------------------
// �������������� ���������� ������
//-----------------------------------------------------------------

typedef struct PRINTERINFO                              // 24/12/09
{
  char   DeviceName[256];    // ��� ���������� ������
  char   Reserve[512];       // ������

  double PaperWidth;         // ������� ������ � ������ ���������� ��������
  double PaperHeight;        // ���������� ������ � �����������

  double PixDeviceInMeterX;  // ������� ���������� ���������� ������
  double PixDeviceInMeterY;  // �� ����������� � ��������� � ������ �� ����
}
  PRINTERINFO;


#endif // PRNAPI_H

