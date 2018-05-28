/****** LISTAPI.H *************** Shabakov D.A.   ****** 11/08/16 **
******* LISTAPI.H *************** Konon V.N.      ****** 04/05/00 **
******* LISTAPI.H *************** Belenkov O.V.   ****** 12/12/00 **
******* LISTAPI.H *************** Gorbunov A.V.   ****** 31/03/05 **
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*      ����� �������� "������ ������" � "���������� ��������"      *
*                                                                  *
********************************************************************
*                                                                  *
*                 �������������� ������� :                         *
*                                                                  *
*                                                                  *
*    // �������� ����������                                        *
*                                                                  *
*    HINSTANCE libInst = ::LoadLibrary("gisforms.dll");            *
*                                                                  *
*    HMAP hMap;                                                    *
*                                                                  *
*    // ���������� ��������                                        *
*    MAPLISTPARM  maplistparm;                                     *
*    TASKPARM  parm;                                               *
*                                                                  *
*    // ����� �������                                              *
*                                                                  *
* long int (WINAPI * lpfn_LoadMapListDialog)(HMAP hMap,            *  
*                                         MAPLISTPARM* maplistparm,*
*                                         TASKPARM* parm);         *
* (FARPROC)lpfn_LoadMapListDialog =                                *
*                   GetProcAddress(libInst, "LoadMapListDialog");  *
*     long int Rezult = (*lpfn_LoadMapListDialog)(hMap,            *
*                                                 &maplistparm,     *
*                                                 &parm);           *
*                                                                  *
*    // �������� ����������                                        *
*                                                                  *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/

#ifndef LISTAPI_H
#define LISTAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ �������� ������� ����������� ���������� ���� ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++


typedef struct MAPLISTPARM     // ��������� �������� ������� "������ ������"
{
  HWND    Window;              // ������������� ���� ���������
#ifdef _M_X64
  int Reserv;                  // ������������
#endif // _M_X64
  int PageNumber;              //  ����� �������� �������� ��� �������� ������� "������ ������"
                               //  0 - �������������� �������� "������ �������"
                               //  1 - �������������� �������� "������ ������"
                               //  2 - �������������� �������� "������ ��"
                               //  3 - �������������� �������� "������ TIN-�������"   // 24/10/11
                               //  4 - �������������� �������� "������ WMS"           // 24/10/11

  char SaveMtrPath[MAX_PATH];  // �����������������
  char SaveRstPath[MAX_PATH];  // �����������
  char SaveSitPath[MAX_PATH];  // ������
  char SaveTinPath[MAX_PATH];  // 31/03/05

  int RstPageNumber;           //  � �������� "������ �������" ����������
                               //  ���(���������) ������  - 0(1);
  int MtrPageNumber;           //  � �������� "������ ������" ����������
                               //  ���(���������) �������  - 0(1);
  int SitPageNumber;           //  � �������� "������ ��" ����������
                               //  ���(���������) ��  - 0(1);
  int TinPageNumber;           // 31/03/05

  int RstNumber;               //  ����� ��������� ������ � �������� "������ �������"
  int MtrNumber;               //  ����� �������� ������� � �������� "������ ������"
  int SitNumber;               //  ����� �������� �� � �������� "������ ��"
  int TinNumber;               // 31/03/05

  DOUBLEPOINT CentrePosition;  // ���������� ������ ���� � ������ � ������
}
  MAPLISTPARM;


typedef struct MAPLISTPARMUN   // ��������� �������� ������� "������ ������"
{
  HWND     Window;             // ������������� ���� ���������
#ifdef _M_X64
  int Reserv;                  // ������������
#endif // _M_X64
  int PageNumber;              //  ����� �������� �������� ��� �������� ������� "������ ������"
                               //  0 - �������������� �������� "������ �������"
                               //  1 - �������������� �������� "������ ������"
                               //  2 - �������������� �������� "������ ��"
                               //  3 - �������������� �������� "������ TIN-�������"
                               //  4 - �������������� �������� "������ WMS"

  int RstPageNumber;           //  � �������� "������ �������" ����������
                               //  ���(���������) ������  - 0(1);
  int MtrPageNumber;           //  � �������� "������ ������" ����������
                               //  ���(���������) �������  - 0(1);
  int SitPageNumber;           //  � �������� "������ ��" ����������
                               //  ���(���������) ��  - 0(1);
  int TinPageNumber;

  int RstNumber;               //  ����� ��������� ������ � �������� "������ �������"
  int MtrNumber;               //  ����� �������� ������� � �������� "������ ������"
  int SitNumber;               //  ����� �������� �� � �������� "������ ��"
  int TinNumber;               //  ����� �������� TIN � �������� "������ ������"
  int WmsNumber;               //  ����� �������� WMS � �������� "������ ������"

  int Reserv2[7];              // ������ (������ ���� �������)

  DOUBLEPOINT CentrePosition;  // ���������� ������ ���� � ������ � ������

  WCHAR SaveMtrPath[MAX_PATH_LONG];  // �����������������
  WCHAR SaveRstPath[MAX_PATH_LONG];  // �����������
  WCHAR SaveSitPath[MAX_PATH_LONG];  // ������
  WCHAR SaveTinPath[MAX_PATH_LONG];
}
  MAPLISTPARMUN;

typedef struct PALETTECNTPARM  // ��������� �������� ������� "���������� ��������"
{
  HWND     Window;                 // ������������� ���� ���������

  COLORREF ColorOfSelectObject;    // ���� ��������� ��������
  COLORREF ColorOfSelectedObjects; // ���� ���������� ��������
  COLORREF ColorOfSetObjects;      // ���� ������ ��������  
                                   //04/05/00
  int     ThickOfSelectObject;     // ������� ����� ��������� ��������
}
  PALETTECNTPARM;

extern "C"
{
 //            ������ "������ ������ ����������� �����"
 // �������� ������� "������ ������ ����������� �����" �� ����������
 // ������ �������� :
 //            �������� "������ �������",
 //            �������� "������ ������",
 //            �������� "������ ���������������� ����"
 // � �������� ������� � ������� ��� ������ � ����������, ����������
 // � ����������������� �������.
 // ��� ������ ���������� ����
 //
 // ��� ��������� ��������� ������(����������/�������� ����)
 // �� ������� "������ ������ ����������� �����" ����������
 // ���� ��������� (maplistparm->Window) ���������:
 //    -  WM_MOVEDOC(0x601) ����������� ������� ����� � �������� ������
 //               � ������ ����.
 //       WPARAM - ��������� �� �������� ����� ���� DOUBLEPOINT
 //       ���������� ����� � ������� ����������� � ��������
 //
 //    -  MT_CHANGEDATA(0x65D) ��������� �� ��������� ������� ������
 //       WPARAM,LPARAM �� ������������.                                         // 10/01/12

 long int _export WINAPI  LoadMapListDialog(HMAP hMap,
                                           MAPLISTPARM* maplistparm,
                                           TASKPARM* parm);

 long int _export WINAPI  LoadMapListDialogUn(HMAP hMap,
                                           MAPLISTPARMUN* maplistparm,
                                           TASKPARM* parm);
                                           
 // --------------------------------------------------------------
 // �������� ������� "���������� ��������" �� ��������(����������)
 // ������ �������� :
 // - �������� "���������� ��������� ��������"
 //  (��������� ����� ���� �����, ����� ���������� �������,
 //   ����� ���������� ��������,������� ����� ���������
 //   ���������� ��� ����������� �������);
 // - �������� "���������� �������� �����";
 // - �������� "���������� �������� �������";
 // - �������� "���������� �������� ������".
 //
 // ����� ��������� ���������� ������� � ��������� paletteParm
 // ����������� ������������� � ������� "���������� ��������"
 // ��������: ����� ��������� ��������, ����� ���������� ��������,
 //           ������� ����� ��������� ��������
 //
 // ��� ������ ���������� ����
 // --------------------------------------------------------------
 long int _export WINAPI  LoadPaletteControl(HMAP hMap,
                                   PALETTECNTPARM* paletteParm,
                                   TASKPARM* parm);

 // --------------------------------------------------------------
 // �������� ������� "���������� ��������" � ������������ ����������� ��������
 // ������ �������� :
 // - �������� "���������� ��������� ��������"
 //  (��������� ����� ���� �����, ����� ���������� �������,
 //   ����� ���������� ��������,������� ����� ���������
 //   ���������� ��� ����������� �������);
 // - �������� "���������� �������� �����";
 // - �������� "���������� �������� �������";
 // - �������� "���������� �������� ������".
 // ��������� PALETTECNTPARM  � TASKPARM ������� � maptype.h
 // pageNumber - ����� �������� �������� ��� �������� ������� "���������� ��������"
 //              0 - �������������� �������� "���������� ��������� ��������"
 //                   (��������� ����� ���� �����, ����� ���������� �������,
 //                   ����� ���������� ��������,������� ����� ���������
 //                   ���������� ��� ����������� �������);
 //              1 - �������������� �������� "���������� �������� �����";
 //              2 - �������������� �������� "���������� �������� �������";
 //              3 - �������������� �������� "���������� �������� ������".
 // number - ����� ��������� ����� (������, �������, ��) � ������� ��������
 //          ���� number == 0, �� �������������� �������� "���������� ��������� ��������"
 //          ���������� ���������� �����. �� ����� 0.
 //          � �������� "���������� �������� �������" �� ������������.
 // ��� ������ ���������� ����
 // -------------------------------------------------------------- // 01/07/03
 long int _export WINAPI  LoadPaletteControlEx(HMAP hMap,
                                   PALETTECNTPARM* paletteParm,
                                   TASKPARM* parm,
                                   long int pageNumber,
                                   long int number);


// -------------------------------------------------------------- // 05/12/03
// �������� ������� "������� ���������"
// ��� ������ ���������� ����
// --------------------------------------------------------------
 long int _export WINAPI  LoadDialogScaleView(HMAP hMap, HWND handle, TASKPARM * parm,
                                              long int * topScale, long int * bottomScale,
                                              char* title);

// --------------------------------------------------------------
// ������ ����������� ������������� �������� ����������� ����� �������
// �������� � ��������� ������� ����������� �������
//    hmap    - �����,���������� ��������� ������;
//    handle  - ������������� ���� ���������
//    name    - ��� ����� ������� ��������
//    parm    - ��������� �� ��������� TASKPARM
//    reDraw  - ���� ����������� ���� ��������� �� ���������� ��������
//    ��� ������ ���������� ����
// --------------------------------------------------------------
 long int _export WINAPI  LoadMtqCompressDialog(HMAP hmap, HWND handle,
                                                const char* name,
                                                TASKPARM* parm, int* reDraw);

// --------------------------------------------------------------
// ������ "��������� ����� � ���� �������� BMP, PCX"
//    hmap    - �����,���������� ��������� ������
//    name    - ��� ��������� ������
// targetName - ��� ��������� ������
//    parm    - ��������� �� ��������� TASKPARM
//    ��� ������ ���������� ����
// --------------------------------------------------------------
 long int _export WINAPI  RstSaveAsExUn(HMAP hMap, const WCHAR * name,
                                    const WCHAR * targetName,TASKPARM *parm);

// --------------------------------------------------------------
// ������ "��������� ����� � ���� ������� TIFF"
//    hmap    - �����,���������� ��������� ������
//    name    - ��� ��������� ������
// targetName - ��� ��������� ������
//    parm    - ��������� �� ��������� TASKPARM
//    ��� ������ ���������� ����
// --------------------------------------------------------------
 long int _export WINAPI  RstSaveAsTiffUn(HMAP hMap, const WCHAR * name,
                                    const WCHAR * targetName, TASKPARM *parm);

// --------------------------------------------------------------
// ������������� ������� ������
// ������ ����������� ������������� �������� ������� ������
//    hmap    -  ������������� �������� ��������� �����
//    handle  -  ������������� ���� ���������
//    name    - ��� ����� ��������� �����
//    parm    - ��������� �� ��������� TASKPARM
//    reDraw  - ���� ����������� ���� ��������� �� ���������� ��������
//    ��� ������ ���������� ����
// --------------------------------------------------------------
 long int _export WINAPI  LoadRstMirrorDialogExUn(HMAP hmap, HWND handle,
                                              const WCHAR* name, TASKPARM* parm,
                                              int * reDraw);


}

#define LEVEL_RSW         0xFFFFFFFD // ����� "�����"             // 16/12/03
#define LEVEL_RSWQUALITY  0xFFFFFFFE // ����� "������ �������"
#define LEVEL_RSWVIEW     0xFFFFFFFF // ����� "������ ���� ���������"


#endif

