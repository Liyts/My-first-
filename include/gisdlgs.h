/**** GISDLGS.H *************** Belenkov O.V. ********* 30/07/14 ***
***** GISDLGS.H *************** Panteleeva N.A. ******* 30/07/13 ***
***** GISDLGS.H *************** Kruzhkov A.E. ********* 22/06/09 ***
***** GISDLGS.H *************** Tarakanova I.R. ******* 16/10/14 ***
***** GISDLGS.H *************** Derevyagina Zh.A. ***** 24/04/12 ***
***** GISDLGS.H *************** Shishkova L.A. ******** 13/08/10 ***
***** GISDLGS.H *************** Konon V.N.     ******** 08/04/15 ***
***** GISDLGS.H *************** Gheleznykova U.V.****** 31/01/11 ***
***** GISDLGS.H *************** Alexeev S.A.  ********* 31/01/13 ***
***** GISDLGS.H *************** Shabakov D.A.  ******** 29/07/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
* ����������� ������� ��� ����� 2011 ��� ���������� �� GIS ToolKit *
*                                                                  *
*                 ������ ������ �������:                           *
*                                                                  *
*   // �������� ���������� �� ��� ����������                       *
*   HINSTANCE libInst = ::LoadLibrary("gisdlgs.dll");              *
*   // �������� ���������� �� ���������� ��� ����� 2011            *
*   HINSTANCE libInst = ::LoadLibrary("mapscena.dll");             *
*                                                                  *
*   // ����� �������                                               *
*   typedef long int (WINAPI * INSERTPOINTS)(HMAP hMap,            *
*                                            TASKPARMEX* parm,     *
*                                            HOBJ info,            *
*                                            RECT * rect);         *
*                                                                  *
*   INSERTPOINTS InsertPoints = (INSERTPOINTS)                     *
*                   GetProcAddress(libInst, "tedInsertPoints");    *
*                                                                  *
*   long int Rezult = (*InsertPoints)(hMap, parm, info, 0);        *
*                                                                  *
*   // �������� ����������                                         *
*   ::FreeLibrary(libInst);                                        *
*                                                                  *
*******************************************************************/

#ifndef GISDLGS_H
#define GISDLGS_H

#ifndef ALSAPI_H        
  #include "alsapi.h"
#endif

#if defined(_M_X64) || defined(BUILD_DLL64)       // 26/08/13
typedef __int64   HBUILDPROFIL; // ������������� ��������� �������
                                // ���������� �������

typedef __int64   HSTATOBJ;     // ������������� ��������� �������
                                // ������� �� �������

typedef __int64   HSEMANT;      // ������������� ��������� �������
                                // �������������� ���������

typedef __int64   HMCLCALC;     // ������������� ��������� �������
                                // �����������
#else
typedef long int  HBUILDPROFIL; // ������������� ��������� �������
                                // ���������� �������

typedef long int  HSTATOBJ;     // ������������� ��������� �������
                                // ������� �� �������

typedef long int  HSEMANT;      // ������������� ��������� �������
                                // �������������� ���������

typedef long int  HMCLCALC;     // ������������� ��������� �������
                                // �����������
#endif


// ��������� ��� ������ ���������� �� ���������� ��������    // 05/05/09
typedef struct SELECTOBJLIST
{
  char * Caption;           // ��������� �������
  long PluralFlag;          // 1 - ������������� �����
  long Left;                // �����
  long Top;                 // ������� ���� �������
  long Height;              // ������
  long Width;               // ������ ������� (���� ������ ������ �������� - �� �����������)
  long FirstWidth;          // ������ ������ �������,���������� �������� ������� ��-��������������
                            // (�������) ������ = 0 - ������� �� �������, ������ = -1 �����������
  long SemCount;            // ���������� ��������� �������� (�� ����� 10)
  long * SemCode;           // ��������� �� ������ ����� ��������
  long * ColWidth;          // ��������� �� ������ ����� ��������
                            // (�������) ������ = 0 - �� �������, ������ = -1 �����������
                            // ���� ColWidth == 0, ������ ������� ��������������
}
SELECTOBJLIST;

// ��������� � ������ �������� �����
typedef struct SELECTOBJINFO
{
  HMAP HMap;       // ������������� �������� �����
  HSITE HSite;     // ������������� �������� ���������������� �����
  long ListNumber; // ����� ����� (���� ����� - site 0)
  long Number;     // ����� ������� � �����
  long Flag;       // ��� ����� 0, ��� ������ 1, ���� ������ ������
  long Reserve;    // ������                            // 22/06/09
}
SELECTOBINFO;

#define ALS_NO_CHOICE_ATLAS 1  // 21/04/10
#define ALS_NO_SEND_MESSAGE 2  // 21/04/10

extern "C"
{

 // ������ "�������������� ������� �������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // info    - ������������� �������������� �������
 // rect    - �������������� ������������ ������� ��� 0
 // ����� ����� ������� �� Mapscena.chm ("ENPOINT")
 // ��� ������ ���������� ����

 long int WINAPI tedInsertPoints(HMAP hmap, TASKPARMEX *parm, HOBJ info, RECT *rect);

 // ������ "�������������� ��������� �������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // info    - ������������� �������������� �������
 // ����� ����� ������� �� Mapscena.chm ("SOKOL")
 // ��� ������ ���������� ����

 long int WINAPI tedEditSemantic(HMAP hmap, TASKPARMEX *parm, HOBJ info);

 // ������ "���������� ��������� ��������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // ����� ����� ������� �� Mapscena.chm ("ZAMSEM")
 // ��� ������ ���������� ����

 long int WINAPI tedUpdateSemantic(HMAP hmap, TASKPARMEX *parm);

 // ������ "�������������� ��������� ���� "����"
 // value   - ����� ������, ���������� ���� � ���� ��/��/����
 //           (������ �������� � � �� �� ������������ ���������)
 // size    - ������ ������
 // parm    - ��������� ���������� ��� ������� (��. maptype.h)
 // point - ���������� �������� ������ ���� �������
 // ��� ������ ���������� ����

 long int WINAPI semGetDateSemantic(char* value, long int size,
                                    TASKPARMEX *parm, POINT *point);

 // ������ "������ ����������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // ����� ����� ������� �� Mapscena.chm ("KON1")
 // ��� ������ ���������� ����

 long int WINAPI tedUndoOperation(HMAP hmap, TASKPARMEX *parm);


 // ������ "������� ����� ����"
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // name    - ��� ����� ������ ����, ������� ����������� ��� ���������
 // size - ������ ������
 // mode - ������ � ������� �������
 //        0 - ������ ������
 //        ALS_NO_CHOICE_ATLAS - ����� �������������� ���������� ������
 //                                            (����� ������ � ������� �������)
 //        ALS_NO_SEND_MESSAGE - ��������� AW_OPENDOC �������� ���� �� ����������
 // ���� mode = ALS_NO_SEND_MESSAGE, �� ����������� ����� ������� ������.
 // ��������� ���������� ������������� ������ (ALS_NO_CHOICE_ATLAS | ALS_NO_SEND_MESSAGE).
 // �������� ����� ������� Arealist.chm (TOPIC: AREALIST).      // 17/01/11
 // ��� ������ ���������� ����

 long int WINAPI tedOpenAtlas(TASKPARMEX *parm, char* name, long int size);
 long int WINAPI tedOpenAtlasEx(TASKPARMEX *parm, char* name, long int size, long int mode);
 long int WINAPI tedOpenAtlasUn(TASKPARM *parm, WCHAR * name, long int size, long int mode);  // 30/07/14


 // ������ "������� ����� ����"
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // name    - ��� ����� ������ ����, ������� ���������
 // size - ������ ������
 // mode - ������ � ������� �������
 //        0 - ������ ������
 //        ALS_NO_CHOICE_ATLAS - ����� �������������� ���������� ������
 //                                            (����� ������ � ������� �������)
 //        ALS_NO_SEND_MESSAGE - ��������� AW_OPENDOC �������� ���� �� ����������
 // ���� mode = ALS_NO_SEND_MESSAGE, �� ����������� ����� ������� ������.
 // ��������� ���������� ������������� ������ (ALS_NO_CHOICE_ATLAS | ALS_NO_SEND_MESSAGE).
 // �������� ����� ������� Arealist.chm (TOPIC: AREALIST).      // 17/01/11
 // ��� ������ ���������� ����

 long int WINAPI tedCreateAtlas(TASKPARMEX *parm, char* name, long int size, long int mode); // 30/09/11


 // ������ "������� ����� �� ������"
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // hmap    - ������������� �������� �����
 // item    - ��������� �� ������ ��������� ������, ��������� � ������� �����
 // count   - ����� ��������� � ������
 // ���������� ����� ���������� ������������� ��������
 // ���� ������� ���������� -1, �� ���������� ������� ������ "������� ����� ����"    // 12/01/11
 // �������� ����� ������� Mapscena.chm (TOPIC: AREALIST1).      // 17/01/11
 // ��� ������ ���������� ����

 long int WINAPI tedAtlasList(TASKPARMEX *parm, ALSITEM* item, long int count);
 long int WINAPI tedAtlasListEx(HMAP hmap, TASKPARMEX *parm, ALSITEM* item, long int count); // 05/04/10

 // ������ "������� � �������� ����� �� �����������"
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // place   - ������ ������������ � ������� ���������:
 // PLANEPOINT      = 1,  � ������ �� ���������
 // MAPPOINT        = 2,  � �������� �������� ����� (���������)
 // PICTUREPOINT    = 3,  � �������� �������� ������� �����������
 //                       ��������� ����������� 1942�.
 // GEORAD          = 4,  � �������� � ������������ � ���������
 // GEOGRAD         = 5,  � �������� ...
 // GEOGRADMIN      = 6,  � ��������, �������, �������� ...
 //                       ���������� ��������� WGS84
 // GEORADWGS84     = 7,  � �������� � ������������ � ���������
 // GEOGRADWGS84    = 8,  � �������� ...
 // GEOGRADMINWGS84 = 9,  � ��������, �������, �������� ...
 // PLANE42POINT    = 10, � ������ �� ��������� �� ��������� ����
 // GEORADPZ90      = 11, � �������� � ������������ � ���������
 // GEOGRADPZ90     = 12, � �������� ...
 // GEOGRADMINPZ90  = 13, � ��������, �������, �������� ...
 // point  - ���������� ������� ����� � ������ �� �����
 // ��� �������� ���������� ���������� ���������� ��������� ����� � ������
 // �� �����
 // ����� ����� ������� �� Mapscena.chm ("MOVEMENT")
 // ��� ������ ���������� ����

 long int WINAPI tedGoPoint(HMAP hmap, TASKPARMEX *parm, long int place,
                            DOUBLEPOINT * point);

 // ������ "���������� � �������� ������ �� ��������"
 // ����� ���� ��������� ��, Mtw, Rsw, Mtl, Mtq, Tin
 // hmap    - ������������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // title   - ��������� �� ����� ��������� ������� ��� 0
 // flagSit - ���� ������� ���������� ��  (0-���������/1-���������)
 // flagMtw - ���� ������� ���������� Mtw (0-���������/1-���������)
 // flagRsw - ���� ������� ���������� Rsw (0-���������/1-���������)
 // flagMtl - ���� ������� ���������� Mtl (0-���������/1-���������)
 // flagMtq - ���� ������� ���������� Mtq (0-���������/1-���������)
 // flagTin - ���� ������� ���������� Tin (0-���������/1-���������)
 // ����� ����� ������� �� Mapscena.chm ("IDN7081")
 // ��� ������ ���������� ����

 long int WINAPI tedAddDataFormDirEx(HMAP hmap, TASKPARMEX * parm, char * title,
                                     long int flagSit, long int flagMtw, long int flagRsw,
                                     long int flagMtl, long int flagMtq, long int flagTin);

// ������� ���������� ������� �������

#define MC_POLYLINE     5213 // ������������ �����
#define MC_RECT         5214 // �������������� �������������
#define MC_ROTRECT      5215 // ��������� �������������
#define MC_POLYRECT     5216 // ������������� � ������� ������
#define MC_FIXCIRCLE    5217 // ���������� �������������� �������
#define MC_VARCIRCLE    5218 // ���������� ������������� �������
#define MC_AUTO         5219 // �������
#define MC_FROMFILE     5220 // �� �����
#define MC_KEYB         5221 // � ����������
#define MC_TWOSIDE      5222 // ������� ����� (��� �� ������)
#define MC_SPLINE1      5223 // ������������ ������
#define MC_SPLINE2      5224 // ��������� ������
#define MC_RIGHTSIDE    5225 // ������� ����� (��� �����)
#define MC_THREEPOINT   5226 // ���������� �� ���� ������

typedef struct MEDRSCPARM
{
 int Regime;                  // ����� �������� ������� ����� �� ��������:
                              // �� MC_POLYLINE �� MC_THREEPOINT
                              // == -1 - ������ �������� ���������� � �������!
                              // ���� ���������� �����, �� ��������������� �����������,
                              // ����� ���������� MC_POLYLINE

 int Repeat;                  // ������������� ���������
                              // == 1 - �����������
                              // == 0 - �������������
                              // == -1 - ���������� � �������

 int FlagKey;                 // ���� ��������� ������� ��������
                              // ���� == 0, �� ����������� �������
                              // ��������������� �������������,
                              // ����� - � ������������ � ���

 int Rezerv;                  // ������

 char NameDlg[128];           // �������� �������

 char Key[32];                // ���������� ������������� ���� ������� � ��������������
}
 MEDRSCPARM;

typedef struct CHOICEOBJECTPARM
{
 HSELECT hSelect;            // ������ (������ ��������� ����������� �������)

 int MapSelect;              // ������ ��� ������ �� ������� ����
                             //  = 0  - ������ �� ���� ������ ���������
                             //  = 1  - ������ �� ����� ����� (����� �����
                             //         ��������� �� �������������� �������)

 int MapEditSelect;          // ������ ��� ������ �� ������� ���� (�� �������� ��������������)
                             //  = 0  - ������ �� ���� ������ ���������
                             //  = 1  - ������ �� ����, ���������� ��������������

}
 CHOICEOBJECTPARM;

 // �������� ������ �������  (���������� �������)
 // hmap - ������������� �������� ��������� �����
 // parm    - ��������� ������
 // hobj - ������������� �������
 // medparm - ��������� ��������
 // choiceparm - ��������� ��� ������� ������ ���� �������
 // hselect - ������ (���� hselect == 0 - ������ �� ������������)
 // ���������� ���������� ��� �������
 // ����� ����� ������� �� Mapscena.chm ("SelecOb")
 // ��� ������ ��� ������ ���������� 0

 long int WINAPI scnChoiceNewObject(HMAP hmap, TASKPARMEX *parm, HOBJ hobj,
                                    MEDRSCPARM* medparm,
                                    CHOICEOBJECTPARM *choiceparm,
                                    HSELECT select);                // 26/11/10

typedef struct OBJFROMRSC
{
 HSELECT hSelect;        // ������ (��� ��������� ������ ��������� �����������)
 int MapSelect;          // ������ ��� ������ �� ������� ����
                         //  = 0 - ������ �� ���� ������ ���������
                         //  = 1 - ������ ������������� �����
                         //  = 2 - ������ �� ����� ����� (������ ��, �� �������
                         //        ��������������� ������)
 int Regime;             // ����� �������� �� MC_POLYLINE ��  MC_THREEPOINT
                         // = -1 - �� ����������
                         // ���� ���������� �����, �� ��������������� �����������
                         // ����� ���������� MC_POLYLINE
 int Repeat;             // ����� "������ ���������"
                         // = 0 ���������, 1 �������� -1 �� ����������
                         // ����� ����� ��� ���������������� �������� ���������� ��������
                         // ����� ������ ���� �� ��������������
                         // ���� ����� ��������, ����� ����� �������� ������� �������
                         // ������� ������ ���������� ��������� � ��� ������ ��������
                         // ������ ���������� ��������� �� ����������
                         // ���� ����� ��������� - ��� ������ ������� ������������ �������
                         // �������� ������ ���������� ���������
}
  OBJFROMRSC;


 // �������� (������ ����) ������� 
 // hmap - ������������� �������� ��������� �����
 // parm    - ��������� ������ (�������� � maptype.h)
 // hobj - ������������� �������
 // objparm - ��������� ��� ������� ������ ���� �������
 // name - ��������� �������
 // ���������� ���������� ��� �������, hobj �������������
 // ��������� ����� � ���� �������
 // ��� ������ ��� ������ ���������� 0                           // 25/02/14

 long int WINAPI scnGetObjectFromRsc(HMAP hmap, TASKPARMEX *parm, HOBJ hobj,
                                     OBJFROMRSC* objparm, char *title);

 // ������ ��������� ������������ �������� ����� � ��������
 // �� ������ ������ ������� info ������ ���� ��������������� (mapRegisterDrawObject)
 // ��� �������� ��� ��������� ������ (� ����������� �� ����������� ���������� ������ �������)
 // hmap   - ������������� �������� ��������� �����
 // parm   - ��������� ����������
 // info   - ������������� �������������� �������
 // regime - ��������� �� ����������, � ������� ����� ������� ��������� ������ ��������� 
 //          ������� (MC_POLYLINE,MC_RECT,...)
 // isnew  - ������� ������ ��� �������������� �������:
 //          1 - ������ ��������� (���� ������ ������� ���������)
 //          0 - ������������� ������� �������, ��� ������ ������� ���������
 // ��� ������ ���������� 0

 long int WINAPI scnSetLineDraw(HMAP hmap, TASKPARM * parm, HOBJ info, 
                                long int *regime, long int isnew);

 // ������ ��������� ������������ �������� �������
 // �� ������ ������ ������� info ������ ���� ��������������� (mapRegisterDrawObject)
 // ��� �������
 // hmap   - ������������� �������� ��������� �����
 // parm   - ��������� ����������
 // info   - ������������� �������������� �������
 // regime - ��������� �� ����������, � ������� ����� ������� ��������� ������ 
 //          ��������� ������� (MC_POLYLINE,...)
 // isnew  - ������� ������ ��� �������������� �������:
 //            1 - ������ ��������� (���� ������ ������� ���������)
 //            0 - ������������� ������� �������, ��� ������ ������� ���������
 // ��� ������ ���������� 0

long int WINAPI scnSetLabelDraw(HMAP hmap, TASKPARM * parm, HOBJ info, 
                                long int *regime, long int isnew);

 // ������ "��������� ���� ��������"
 // param  - ��������� ������ (���� IniName ������ ���������
 //          ��� ini �����, ���� PathShell - ������� ����������)
 // ����� ����� ������� �� Mapscena.chm (���� "IDN_LICENSE")
 // ��� ������ ��� ������ ���������� 0

 long int WINAPI mapExecuteGNClient(TASKPARMEX * param);    // 31/01/11

 // ����� ������ ����� (���������, ���������, ���������) �� ������
 // hmap    - ������������� �������� ��������� �����
 // parm    - ��������� ������
 // maptype - ��� ������: FILE_MAP, FILE_RSW, FILE_MTW
 // accesstype - ��� ������� � ������:
 //              0 - ���, 1-������ ��� �����������, 2-������ � ������ ��������
 // title      - �������� ���������� ������
 // ����������: -1 ��� ������ �� ������ ��� ���������� ����, ����� - ����� �����
 // � ������ (� 0 ��� FILE_MAP � � 1 ��� FILE_RSW, FILE_MTW)

 long int WINAPI scnGetMapNumberWithTitle(HMAP hmap,TASKPARMEX *parm, int maptype,
                                       int accesstype, int current, const char *title);


 // ������� �������� ������� ��������� ���������
 // hWnd     -  ������������� ����
 // message  -  ������, ���������� ����� ��������� ��� ���������� � ���� �������
 // title    -  ��������� �������
 // flag     -  ��� ��������� (MB_OK, MB_YESNO, MB_YESNOCANCEL)
 // percent  -  �������� �������� ����������
 // second   -  �������� ����������� ������� ��������� � ���. 
 // ���������� ������������� ���� �������
 // ��� �������� ������� ����� ������� ������� scnCloseMessageBoxProcess
 // ��� ������ ���������� 0
 
 HANDLE WINAPI scnOpenMessageBoxProcess(HWND hWnd, const char * message,
                                        const char * title, long int flag,
                                        long int percent, 
                                        long int second);
 
 // ������� ���������� ����������� �������
 // hmsgproc - ������������� ���� ������� ��������� ���������
 //            (������� ��� ��������� ���������� ������� CallMessageBoxProcess)
 // ���� ������ ������ �������������, �� ���������� 0
 // � ���� ������ ����� ������� scnCloseMessageBoxProcess

 long int WINAPI scnUpdateMessageBoxProcess(HANDLE hmsgproc, long int percent, 
                                                             long int second);
                                        
 // ������� �������� �������
 // hmsgproc - ������������� ���� ������� ��������� ���������
 //            (������� ��� ��������� ���������� ������� CallMessageBoxProcess)
 // ���������� ��� ������� ������ - IDYES, IDNO, IDCANCEL.

 long int WINAPI scnCloseMessageBoxProcess(HANDLE hmsgproc);

 
 // ������� ������ ���� ��������� �� �������������� ��� ���������       // 08/08/13
 // hmap       - ������������� �������� ��������� �����
 // parm       - ��������� ������
 // sitenumber - ����� ���������������� ����� � ������� �� 1 �� ����� ����
 // code       - ��� ��������� ��� ���������
 // ���������� ��� ����������� ��������� � ����� ���������������� ����� (sitenumber).
 
 long int WINAPI scnChangeCodeSemantic(HMAP hmap, TASKPARM* parm, 
                                       long int * sitenumber, long int code);

                                       
 // ������� �������������� ��������� 
 // hmap       - ������������� �������� ��������� �����
 // parm       - ��������� ������
 // info       - ������������� �������������� �������
 // ident      - ��� ������ ��������� "�������� �������" ident = 0, 
 // ����� ident = 1
 // ��� ������ ���������� ����

 long int WINAPI semMakeSemantic(HMAP hmap, TASKPARMEX *parm, HOBJ info, long int ident);


 // ��������� �������� �� ����������� �� ����� KML                   // 24/04/12
 // hmap        - ������������� �������� ���������
 // parm        - ������� ��������� ���������
 // kmlfile     - ������ ��� ������������ �����
 // ��� ������ ���������� 0

 long int WINAPI tedLoadObjectsFromKML(HMAP hmap, TASKPARMEX *parm, HOBJ info, char * kmlfile);

                                       
 /*********************************************************
 *                                                        *
 *           ������� ������� � ���-�������                *
 *                                                        *
 *     ��� �������� ����� �� ���-������� � �������        *
 *      ������� �������� ���� ���������� ������ ����      *
 *           "ALIAS#��������_���_�����"                   *
 *  �������� ��� ����� �� �������� ����� � �������� ����� *
 *     ������ "ALIAS#" �������� �������� ������ ���       *
 *           ��������� � ���-�������                      *
 *                                                        *
 *********************************************************/

 // ������� ������ ����������� ������������ �� ��� �������
 // (���� ����� ������������ � ������ � ����������� � ��� �������)
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // ��� ������ ���������� ����

 long int WINAPI svGetUserData(TASKPARM *parm);

 // ������� ������ ����������� ������������ �� ��� ������� ��� �������� ������
 // (���� ����� ������������ � ������ � ����������� � ��� �������)
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // aliasName ����� ������ ���� "HOST#����:����#ALIAS#��������_���_�����"
 // ��� ������ ���������� ����

 long int WINAPI svGetUserDataEx(TASKPARM *parm,const char * aliasName);


 // ������� ������ ����� ���������� ���������� � ��� �������� 
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // ������������ �������� ��� ����� (��� IP) � ����� �����
 // ��� ������ ���������� ����

 long int WINAPI svGetConnectParameters(TASKPARM *parm);

 // ������� ������ ������ ��������� ������������ ������ �� ��� �������
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // name    - ����� ��� ���������� ���������� ������ ������
 //          (�������� �� ����� MAXPATH)
 // size    - ������ ����������� ������
 // ��� ���������� ������ ����� ���������� � name
 // ��� ������ ���������� ����

 long int WINAPI svOpenDataEx(TASKPARM *parm,char * name,long int size);

 // ������� ������ ������ ��������� ������������ ������ �� ��� �������
 // ��� ������
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // name    - ����� ��� ���������� ���������� ������ ������
 //          (�������� �� ����� MAXPATH)
 // size    - ������ ����������� ������
 // ��� ���������� ������ ����� ���������� � name
 // ��� ������ ���������� ����

 long int WINAPI svOpenDataAtlas(TASKPARM *parm,char * name,long int size);

 // ������� ������ ������ ��������� ������������ ������ �� ��� �������
 // ��� ������
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // hwnd - ������������� ���� ������ ��� �������� ��������� � �������� ������
 // ��� ������ ���������� ����

 long int WINAPI svOpenDataAtlasEx(TASKPARM *parm, HWND hwnd);


 // ������� ������ ������ ��� ��� ������������������ �������������   // 21/02/12
 // ��������� ������ �� ��� ������� 
 // �������� ������������� ����� ������
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // hwnd - ������������� ���� ��� �������� ���������
 // ��� ������ ������ ���� ���������� ��������� MT_CHANGEDATA
 // (0x65D, WPARAM - type : FILE_MAP, FILE_RSW, FILE_MTW...
 //         LPARAM - ��� ���������� ������ ������ (��������� �� ������������
 // ������� � ��������� ANSI)
 // ��� ������ ���������� ����

 long int WINAPI svGetServerData(TASKPARM *parm,HWND handle);


 // ������� ������ ������ ��� ��� ������������������ �������������
 // ��������� ������ ������������� ���� �� ��� �������
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // hwnd - ������������� ���� ��� �������� ���������
 // ��� ������ ������ ���� ���������� ��������� MT_CHANGEDATA
 // (0x65D, WPARAM - type : FILE_MAP, FILE_RSW, FILE_MTW...
 //         LPARAM - ��� ���������� ������ ������ (��������� �� ������������
 // ������� � ��������� ANSI)
 // filetype - ��� ����������� ������: (1 - �����, 2 - �������, 3 - ������,
 //                                    -1 - ������ ���� �����)
 // �������� ������������� ����� ������
 // ��� ������ ���������� ����

 long int WINAPI svGetServerTypeData(TASKPARM *parm,HWND handle,
                                     long int filetype);                  // 30/07/13



 // ������� ������ ������ ��������� ������������ ������ �� ��� �������
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // ��� ������ ����������� ������ �������� ���� ���������� ���������
 // AW_OPENDOC (0x655) c ������ ���������� ������ ����� (����� ���� �������
 // � mapOpenData).
 // ��� ������ ���������� ����
 
 long int WINAPI svOpenData(TASKPARM *parm);

 // ������� ������ ������ ��������� ������������ ������ �� ��� �������
 // ��� ���������� � ������� �������� �����
 // parm    - ��������� ������ (���� Handle ������ ���������
 //           ������������� �������� ����)
 // ��� ������ ����������� ������ ���������� ������� mapAppendData(hmap, ...),
 // � ���� ����� ���������� ����������� - ��������� MT_CHANGEDATA
 // (0x65D, WPARAM - type : FILE_MAP, FILE_RSW, FILE_MTW...) 
 // ������������� ���� ����� ������������� ����� ������� �������� ���� ���������
 // AW_GETCURRENTDOC (0x673, WPARAM - HWND *, LPARAM - HMAP *).
 // ��� ������ ���������� ����

 long int WINAPI svAppendData(HMAP hmap, TASKPARM *parm);

 // ������������� ������ � ��� �� ��������� MD5
 // source - �������� ������ ANSI
 // target - ������ ���������� (32 ������� � ���������� ����)
 // size   - ����� ����, ����������������� � ������ (�� ����� 33)
 // ��� ������ ���������� ���������� ����

 long int WINAPI svStringToHash(const char * source,
                                char * target, long int size);

 /*********************************************************
 *                                                        *
 *             ������� ���������� �������                 *
 *                                                        *
 *********************************************************/

 // ������� ������ ���������� �������
 // hmap - ������������� �������� ��������� �����
 // parm - �������� ���������� ������ (��.maptype.h)
 // profparm - �������� ���������� ���������� ������� (��.maptype.h)
 // ���� ��� �� ����������� � profparm ����� ����, ������������ ���� �������
 // ��������� ��� �� ����������� � �� ��������� ����� ���� ���������������
 // �������� �������� � ������
 // � �������� ������ ������� � profparm ������������ ������� ���������
 // ��� �������� ������� �������� ���� ���������� ���������      21/04/10
 // AW_CLOSEDIALOGNOTIFY (0x610 - ��.maptype.h)
 // ���������� ��������� �� ������ ���������� ������� (HBuildProfil)
 // ����� ����� ������� �� Mapscena.chm ("Proflin")
 // ��� ������ ���������� ����

 // ������ ������ ������� ���������� �������
 //HBUILDPROFIL Hbuildprofil;
 //HINSTANCE LibInst;
 //HBUILDPROFIL (WINAPI * Openprof)(HMAP hmap, TASKPARMEX * parm,
 //                             PROFBUILDPARM * profparm);
 //long int (WINAPI * Closeprof)(long int Hbuildprofil);
 //long int (WINAPI * SetCurrentValue)(long int HBuildProfil,
 //                                    DOUBLEPOINT * point);
 //(FARPROC)Openprof = mapLoadLibrary("gisdlgs.dll",&LibInst,"mclOpenBuildProf");
 //(FARPROC)Closeprof = mapGetProcAddress(LibInst,"mclCloseBuildProf");
 //(FARPROC)SetCurrentValue = mapGetProcAddress(LibInst,"mclSetCurrentValue");

 // Hbuildprofil = (*(Openprof))(hmap,parm,&profparm);
 // ....
 //(*(SetCurrentValue))(Hbuildprofil,&(profparm.Point));
 // ....
 // if (Hbuildprofil)  (*(Closeprof))(Hbuildprofil);

 HBUILDPROFIL WINAPI mclOpenBuildProf(HMAP hmap, TASKPARMEX * parm,
                                      PROFBUILDPARM *profparm);

 HBUILDPROFIL WINAPI mclOpenBuildProfEx(HMAP hmap, TASKPARMEX * parm,    //23/04/10
                                        PROFBUILDPARMEX *profparm);
 // ������� ������ ���������� �������
 // HBuildProfil - ��������� ��������� ������� ���������� �������

 long int WINAPI mclCloseBuildProf(HBUILDPROFIL HBuildProfil);

 // ���������� ������� � ������� �����
 // HBuildProfil - ��������� ��������� ������� ���������� �������
 // point - ���������� ����� � ������ �� ������� �������,
 //         �� �������� �������� �������
 // ������� ���������� ������� �������, �� ������� ��������� ������ ����� �
 // ������������� � ���� ������� ����������� �������� �� ������ �����.

 long int WINAPI mclSetCurrentValue(HBUILDPROFIL HBuildProfil,
                                    DOUBLEPOINT * point);


 /*********************************************************
 *                                                        *
 *            ������� ���������� ���� ���������           *
 *                                                        *
 *********************************************************/

 // ���������� ���� ��������� �� ������� ����� � ���� ���������� �����������
 // hmap - ������������� �������� ��������� �����
 // parm - �������� ���������� ������ (��.maptype.h)
 // namersw - ������ ��� ������
 // zonevisibility - ��������� ���������� ���� (��.maptype.h)
 // ���������� ������������ ��� ������� �������� ������� �����
 // ��������� ������������ � ���� namersw
 // ���������� ����� ������ � �������
 // ����� ����� ������� �� Mapscena.chm ("ZONVIEW")
 // ��� ������ ���������� ����

 long int WINAPI mclBuildZoneVisibility(HMAP hmap,TASKPARMEX *parm,
                                        char * namersw,
                                        TBUILDZONEVISIBILITY *zonevisibility);

 long int WINAPI mclBuildZoneVisibilityUn(HMAP hmap,TASKPARMEX *parm,
                                          WCHAR * namersw,
                                          TBUILDZONEVISIBILITY *zonevisibility);

 /*********************************************************
 *                                                        *
 *      ������ ����������� ������ � �����                 *
 *                                                        *
 *********************************************************/

 // ������ ����������� ������ � ����� ��� ���� �������� ������
 // hmap - ������������� �������� ��������� �����
 // parm - �������� ���������� ������ (��.maptype.h)
 // point - ���������� ����� � ������
 // ����� ����� ������� �� Mapscena.chm ("CAN")
 // ��� ������ ���������� ����

 long int WINAPI mclShowHeight(HMAP hmap,TASKPARMEX *parm,    // 26/05/11
                               DOUBLEPOINT * point);


 /*********************************************************
 *                                                        *
 *     ��������� ���������� ��������������� � ��������    *
 *                                                        *
 *********************************************************/

//  ������ ��������� ����������� ���������������, ����������� � ��������
// *center - ��������� �� ����� ��������, ����� ��������� ���������� ����� ����������
// *dx,*dy - ��������� �� �������� �������� (�)
// *angle  - ��������� �� �������� ���� �������� (����., ������ ������� ������� +)
// *scale  - ��������� �� �������� ������������ ���������������
// ��� ������ ���������� 0, 1 - ���������� ����������
//------------------------------------------------------------------------------

 long int WINAPI scnSetRotateOptions(HMAP map,TASKPARMEX *parm,
                                     DOUBLEPOINT *center,
                                     double *dx,double *dy,
                                     double *angle,double *scale);


 /*********************************************************
 *                                                        *
 *      ������ ����� ������ ��� ������� � �����           *
 *                                                        *
 *********************************************************/

// mapname  - ��� �����
// password - ����� ��� ���������� ������
// size     - ������ ������ � ������ ��� ������
// ��� ������ ���������� 0, 1 - ���������� ����������

 long int WINAPI scnGetMapPassword(const WCHAR * mapname, WCHAR * password, int size);


/**********************************************************
 *                                                        *
 *      ������� �������� XSD-����� �� ��������������      *
 *                                                        *
 *********************************************************/

// hrsc  - ������������� �������������� �����
// ��������� ����������� ���������� ������ - ���� ����� xsd
// ��� ������ ���������� 0

 long int WINAPI scnRscToXsd(HRSC hrsc);


 /*********************************************************
 *                                                        *
 *         ������� ���������� ���� ������ �������         *
 *                                                        *
 *********************************************************/
typedef struct BUILDZONEPARMEX                    // 18/04/14
{
  double Radius;
  int FlagDial;
  int Check;
  int Size;            // 1 - ������ � �
                       // 1000 - ������ � ��
                       // 2 - �� �� �����
  int TypeZone;        // ��� ���� ��� ��������� ��������
                       // 0 - �������
                       // 1 - ����������
                       // 2 - ������� � ����������
  int EnableType;      // 0 - Info �� �������
                       // 1 - Info �������
  int FormZone;        // ��� ���� ����
                       // 1 - ������������
                       // 0 - ���� �����
} BUILDZONEPARMEX;

 // ���������� ����
 // hmap - ������������� �������� ��������� �����
 // parm - �������� ���������� ������ (��.maptype.h)
 // zoneparm - ��������� ���������� ����
 // ��� ������ ���������� ����

 long int WINAPI mclPutRadiusZoneObject(HMAP hmap,TASKPARMEX *parm,
                                        BUILDZONEPARMEX *zoneparm);


 // ������� �� ������� ���������                          // 16/10/14
 // hmap - ������������� �������� ��������� �����
 // parm - �������� ���������� ������ (��.maptype.h)
 // info - ��������� ������
 // ��� ������ ���������� ����

 // ������� ������ "������� �� �������"
 HSTATOBJ WINAPI mclCreateStatisticObject(HMAP hmap, TASKPARMEX * parm,
                                          HOBJ info);
 // ������� ������ "������� �� �������"
 long int WINAPI mclCloseStatisticObject(HSTATOBJ hstat);

// ���������� ������� "������� �� �������"
 long int WINAPI mclChangeStatisticObject(HSTATOBJ hstat, HOBJ info);

} // extern "C"

#endif  // GISDLGS_H
