/****  VECEXAPI.H    **********  Belenkov  O.V.  *****  02/09/16 ***
*****  VECEXAPI.H    **********  Konon  V.N.     *****  07/06/13 ***
*****  VECEXAPI.H    **********  Shabakov D.A.   *****  07/08/14 ***
*****  VECEXAPI.H    **********  Derevyagina Zh.A.****  02/10/15 ***
*****  VECEXAPI.H    **********  Dishlenko S.G.  *****  17/11/15 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                     FOR  WINDOWS & LINUX                         *
*                                                                  *
********************************************************************
*                                                                  *
*                 ������ ������ �������:                           *
*                                                                  *
*   // �������� ����������                                         *
*   HINSTANCE libInst = ::LoadLibrary("gisvecex.dll");             *
*                                                                  *
*   // ����� �������                                               *
*   typedef long int (WINAPI * MAPSORTING)(HMAP hMap,              *
*                                          HMESSAGE handle,        *
*                                          long int mode);         *
*                                                                  *
*   MAPSORTING mapsorting = (MAPSORTING)                           *
*                   GetProcAddress(libInst, "MapSortProcess");     *
*                                                                  *
*   long int rezult = (*mapsorting)(hMap, hWnd, mode);             *
*                                                                  *
*   // �������� ����������                                         *
*   ::FreeLibrary(libInst);                                        *
*                                                                  *
*******************************************************************/

#if !defined(VECEXAPI_H)
#define VECEXAPI_H

#ifndef MMSTRUCT_H
  #include "mmstruct.h"
#endif

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

#ifdef WIN32API
   #define HMESSAGE HWND
#else
   #define HMESSAGE MSGHANDLER
#endif

#ifdef WIN32API      
#if defined(VECEX_DLL)
 #define _VECAPI  WINAPI
 #define _VECIMP  __declspec( dllexport )
#else
 #define _VECAPI  WINAPI
 #define _VECIMP  __declspec( dllimport )
#endif
#else
#if defined(VECEX_DLL)
 #define _VECAPI  WINAPI
 #define _VECIMP
#else
 #define _VECAPI  WINAPI
 #define _VECIMP
#endif
#endif

enum SXFFORMATFLAG
 {
   DATAMETERS       = 0,  // ������� � ������
   DATARADIANS      = 4,  // ������� � ��������
   DATADEGREES      = 8,  // ������� � ��������
 };

extern "C"
{
 // ��������� ���������� ������ �� ������ SXF, TXF, MAP, SIT, SITX     // 12/06/15
 // �� ����� ����� 
 // name - ��� ����� ����� � ����� �� ����������������� ��������
 // ��������� MAPREGISTER � LISTREGISTER ������� � mapcreat.h
 // rscname - ����� ������ ��� ������ ����� �������������� (����� ���� 0)
 // rsize - ����� ������ � ������
 // sheetname - ����� ������ ��� ������ �������� ����� ����� (����� ���� 0)
 // ssize - ����� ������ � ������
 // securitycode - ����� ���� ��� ������ ���� ������� ����������� (����� ���� 0)
 // ( 0 - �� �����������, 1 - �������� ���������� (unclassified), 
 // 2 - ���������� � ������������ �������� (restricted),
 // 3 - ���������� ��� ���������� ����������� (confidential),
 // 4 - ��������� ���������� (secret), 5 - ���������� ��������� ���������� (topsecret))
 // ���������� ����� �������� � �����
 // ��� ������ ���������� ����
 
_VECIMP long int _VECAPI mapGetAnySxfInfoByNamePro(const WCHAR * name, MAPREGISTEREX * mapreg,
                                                  LISTREGISTER * sheet,
                                                  WCHAR * rscname, long int rsize,
                                                  WCHAR * sheetname, long int ssize,
                                                  long int * securitycode);
                                                  
_VECIMP long int _VECAPI mapGetAnySxfInfoByNameUn(const WCHAR * name, MAPREGISTEREX * mapreg,
                                                 LISTREGISTER * sheet);
_VECIMP long int _VECAPI mapGetAnySxfInfoByName(const char * name,
                                               MAPREGISTEREX * mapreg,
                                               LISTREGISTER * sheet);

 // ��������� ��� �������������� (RSC) �� ������ SXF, TXF, MAP (SIT)
 // � ������ SXF � TXF ��� �������������� (RSC) ����� �������������
 // rscname - ����� ������ ��� ������ ����� ��������������
 // size - ����� ������ � ������
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI GetRscNameFromAnySxfUn(const WCHAR * name, WCHAR * rscname, long int size);
_VECIMP long int _VECAPI GetRscNameFromAnySxf(const char * name, char * rscname, long int size);
_VECIMP long int _VECAPI GetRscNameFromSxfUn(const WCHAR * name, WCHAR * rscname, long int size);
_VECIMP long int _VECAPI GetRscNameFromSxf(const char * name, char * rscname, long int size);

 // ��������� ��� ����� �� ������ SXF, TXF, MAP (SIT)
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI GetSheetNameFromAnySxfUn(const WCHAR * name,
                                                 WCHAR * sheetname, long int size);
_VECIMP long int _VECAPI GetSheetNameFromAnySxf(const char * filename, char * sheetname,
                                               long int size);

 // ��������� ����������� ����� ����� SXF
 // name - ��� ����� SXF
 // ��� ������ ���������� ���� � ������ ��������� �� �����
 // ���� - ���������� �������� ����������� �����

_VECIMP long int _VECAPI GetSxfCheckSumUn(const WCHAR * name);
_VECIMP long int _VECAPI GetSxfCheckSum(const char * name);

 // ��������� ����������� ����� ����� SXF
 // name - ��� ����� SXF
 // ��� �������� �������� ���������� 1
 // ��� ������������ ����������� ����� ���������� -1
 // ��� ������ ��������� ����� ���������� -2
 // ��� ���������� ������ ��������� ����� ���������� -3
 // ��� ������ ������� � ������ ���������� ���� � ������ ��������� �� ����� (���� ������ ��������� ���������)

_VECIMP long int _VECAPI SxfCheckSumUn(const WCHAR * name);

 // ��������� �������� ��������� ������ �����
 // hMap,hSite - �������������� ����� (��.MAPAPI.H),
 // mode       - ����� ������ (0 - ��������, 1 - ��������������),
 // handle     - ������������� ���� ������� �������� ��������� (HWND ��� Windows).
 //
 // ���� ������� ���������� ��������� ��������� :
 //  WM_LIST   = 0x586   WParam - ���������� ������ � ������
 //                      LParam - ����� �������� �����
 //  WM_OBJECT = 0x585   WParam - ������� ������������ ��������
 //  WM_ERROR  = 0x587   WParam - ���������� ����� ������� ��� 0
 //                      LParam = 1 - ������ � �����
 //                             = 2 - ������ � ��������������
 //                             = 3 - ������ � �������� �������
 //                             = 4 - ������ � �������
 //                             = 5 - ������ � ���������
 //                             = 6 - ������ � �������
 // ���������� ���������� ������ � ������

_VECIMP long int _VECAPI mapStructControl(HMAP hMap,HSITE hSite,
                                         long int mode,HMESSAGE handle);

 // ���������� ���� ����, �������� � ��������
 // hmap   - ������������� ������������ ���������
 // handle - ������������� ���� ������� �������� ��������� (HWND)
 // mode   - ���������� ������ ������� ��������� �����:
 //   0 - ����������� ��� �����,
 //   1 - ������ ���������������;
 //   2 - ��������� ����� ������;
 //   4 - �������� �������� �������� � ������, ����� ������ ������������;
 //  16 - �������� �������� �������� � ������, ������ - ��  (2 �����);
 //  32 - �������� �������� �������� � ������, ������ - ��  (3 �����);
 //  64 - �������� �������� �������� � ��������, ����� ������ ������������;
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI MapSortProcess(HMAP hmap, HMESSAGE handle, long int mode);

 // ������ ����� ��������� (SXF,TXF,MAP,...) � DIR
 // � ������ ��������� ����� DIR ������ ���� ������ � �������
 // dirname - ������ ��� ����� DIR
 // ��� ������ ���������� ����
 
_VECIMP long int _VECAPI GetDirItemCount(const char * dirname);

_VECIMP long int _VECAPI GetDirItemCountUn(const WCHAR * dirname);               // 07/08/14

 // ������ �������� ������ ��� ������ ����� � ������ (SXF,TXF,MAP,...) � DIR
 // dirname - ������ ��� ����� DIR
 // name    - ����� ������ ��� ���������� ������������ �����
 // size    - ������ ������
 // ��� �������� ���������� ���������� ����� ��������� � ������
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI GetDirAreaName(const char * dirname, char * name, long int size);

_VECIMP long int _VECAPI GetDirAreaNameUn(const WCHAR * namedir, WCHAR * name, long int size);   // 26/05/14

 // ������ ������ ���� ������ ������ (SXF,TXF,MAP,...) � DIR
 // dirname - ������ ��� ����� DIR
 // items   - ����� ������ ��� ���������� ����������� ��������� NAMESARRAY
 //           (��. mmstruct.h)
 // size    - ������ ������; ������ ���� �� ������, ��� ������ ����������
 //           ��� ����� ���������, ������� GetDirItemCount()
 //           size = sizeof(NAMESARRAY) + sizeof(LISTSNAME) * (count - 1);
 // ��� �������� ���������� ���������� ����� ��������� � ������
 // ��� ������ ���������� ����
 
_VECIMP long int _VECAPI GetDirItemList(const char * dirname,
                                       NAMESARRAY * items, long int size);
_VECIMP long int _VECAPI GetDirItemListUn(const WCHAR * dirname,
                                         NAMESARRAY * items, long int size);


 // ��������� ������� ������� ������������ ����� ����� �����          // 14/06/15
 // �� ������ SXF, TXF, MAP, SIT, SITX
 // name - ��� ����� ����� � ����� �� ����������������� ��������
 // HOBJ - ������������� �������, ���������� �� ��� �����, ��� ����� �������� ������
 // ���������� ����� ����������� �� ������� ��������� ����� � ������� ��������� �������� �����
 // ���� �������-����� ��� � ������ ������, �� ��������� ���������� ��������� ������ ������
 // ���� � ��������� ������� ������� ����������, �� ��� ����� ������� 
 // ������-����� ������ �� ���� SHEETFRAMEEXCODE (91000000)
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI GetBorderMetricsFromAnySxfUn(const WCHAR * name, HOBJ hobj);
                                              

 // ������������ �������� ����������� ����� � ������� PNG               // 16/06/15
 // �� ������ SXF, TXF, MAP, SIT, SITX
 // ����������� �������� �� ���������� ����� ����� � ������� �������� �����
 // sxfname - ��� ����� ����� � ����� �� ����������������� ��������
 // imagename - ��� ����� PNG � �������� ������������, ���� ����� 0, 
 //           �� � ������� ����� ����� ����� ����������� ".preview.png"
 // width   - ������ ����������� (������ 512)
 // height  - ������ ����������� (������ 512)
 // rscname - ��� ��������� �������������� ��� ���� ������� SXF � TXF,
 //           ���� ����� ����, �� ������ � SXF ��� TXF
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI BuildPreviewImageFromAnySxfUn(const WCHAR * sxfname,
                                                      const WCHAR * imagename, 
                                                      long int width, long int height,
                                                      const WCHAR * rscname);
                                              
 //========================================================================
 //   ������� �������, �������� � ���������� ����� ��� �������� SXF, TXF � DIR
 //========================================================================
 //  ���� ������� ���������� ��������� ��������� :
 //  WM_LIST   = 0x586   WParam - ���������� ������ � ������
 //                      LParam - ����� �������� �����
 //  WM_OBJECT = 0x585   WParam - ������� ������������ ��������
 //  WM_INFOLIST = 0x584 LParam - ����� ��������� INFOLIST
 // ----------------------------------------------------------------

 // ��������� (�������������) ����� �� ����� SXF, TXF ��� DIR �
 // �������������� Select � ��������������� ��������� � ���� ���������
 // ����� SXF � TXF ����� ������� ���������� � ������, �������� ��� ��������
 // hmap    - ������������� �������� ����� (������������� ���������
 //           ��� ����������� ������� ���� ���������) ��� 0;
 // sxfname - ��� ������������ ����� ���� SXF, TXF ��� DIR;
 // rscname - ��� ����� ��������������, � ������� ����������� �����,
 //           ��� �������������� ����� ��������� �� SXF (TXF) �������� GetRscNameFromSxf
 //           ��� �� �����; ��� ����� DIR ����� ���� 0;
 // mapname - ��� ����������� ����� (������ ��������� � ������ SXF (TXF))
 //           ��� ���� ��� ��������� �� ������ ������ (����� �������� MAX_PATH
 //           c ������� ������ ������ ����) ��� ��������� �� ����� ��� ����������
 //           �����. ���� ��� ����� �� ������ ��� ������ ������ �����, �� �����
 //           ��������� � ������ SXF (TXF) � ����������� ".sit". ���� namemap
 //           ��������� �� ����� ����������� ����� (size), �� � ����� ������������ 
 //           ��� ��������� �����;
 //           ��� ����� DIR ��� ����� ����� - MPT (������ ������, ���������� ��� 
 //           �������� ����� �� DIR) ��� MAP (������������� �����);
 // size    - ����� ������, �� ������� ��������� ���������� namemap, ��� 0. ������ �����
 //           ����� MAX_PATH_LONG (1024);
 // handle  - ������������� ���� �������, �������� ���������� �������������� 
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux);
 // select  - ������ ����������� �������� � �����, ���� ���������� ����������
 //           ��������� ������;
 // frscfromsxf - �������� ������ "��������� �������������
 //               ����� ��������������, ���������� � ����� sxf"
 // typesit - ��� ����������� ���� � ������� MPT ��� ������� DIR (1- SIT; -1- SITX)
 // password - ������ ��� �������� ����������� ��������� ����� (SITX)
 // psize    - ����� ������ � ������
 // transform - ������� ������������� ���������������� ����������� ����� � ������� ��������� hmap
 //             (���� hmap � transform �� ����� 0)
 // ��� ���������� �������� ����� � �������� ���������� ������� �������
 // mapAppendData(hmap, namemap). ���� mapname �������� ��� ����� ���� MAP �
 // ��� �������� ���� �� ���� ����, �� ��� ������� ������ ����������� ��������
 // ������ ����� � ����� MAP. � ���� ������ ������� mapAppendData �� ������ ����������. 
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI ImportFromAnySxfProM(HMAP hmap, const WCHAR * namesxf,
                                            const WCHAR * namersc,  WCHAR * namemap, long int size,
                                            HMESSAGE handle, HSELECT select, long int frscfromsxf,
                                            long int typesit, const WCHAR * password, long int psize,
                                            long int transform);

_VECIMP long int _VECAPI ImportFromAnySxfPro(HMAP          hmap,
                                            const WCHAR * namesxf,
                                            const WCHAR * namersc,
                                            WCHAR *       namemap,
                                            long int      size,
                                            HMESSAGE      handle,
                                            HSELECT       select,
                                            long int      frscfromsxf,
                                            long int      typesit,
                                            const WCHAR * password, long int psize);

 // ��������� (�������������) ����� �� ����� DIR
 // frscfromsxf - �������� ������ "��������� �������������
 // ����� ��������������, ���������� � ����� sxf"

_VECIMP long int _VECAPI ImportFromAnySxfEx(HMAP hmap,
                                         const char * sxfname,
                                         const char * rscname,
                                         char * mapname,
                                         long int size,
                                         HMESSAGE handle,
                                         HSELECT select,
                                         long int     frscfromsxf);
                                         
 // ��������� ����� �� ����� SXF, TXF ��� DIR � �������������� Select
 // � ��������������� ��������� � ���� ���������
 // ����� SXF � TXF ����� ������� ���������� � ������, �������� ��� ��������
 // namedir - ��� ������������ ����� ���� DIR;
 // namemap - ��� ����������� �����
 //           ��� ���� ��� ��������� �� ������ ������ (����� �������� 1024 �������
 //           c ������� ������ ������ ����) ��� ��������� �� ����� ��� ����������
 //           �����. ���� namemap ��������� �� ����� ����������� ����� (size),
 //           �� � ����� ������������ ��� ��������� �����;
 //           ��� ����� DIR ��� ����� ����� - MPT (������ ������, ���������� ���
 //           �������� ����� �� DIR) ��� MAP (������������� �����);
 // size    - ����� ������, �� ������� ��������� ���������� namemap ��� 0. ������ �����
 //           ����� 2048 ����;
 // handle  - ������������� ���� �������, �������� ���������� ��������������
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux) ��� 0;
 // typesit  - ��� ����������� ���� � ������� MPT ��� ������� DIR (1- SIT; -1- SITX)
 // password - ������ ������� � ������, �� �������� ����������� 256-������ ���
 //            ��� ���������� ������ (��� ������ ������ �� �����������������) ��� 0
 // psize    - ����� ������ � ������ ��� 0
 // crscode  - ��������� �� ������ � ����� ������� ���������, � ������� �������������
 //            ������ ��� 0. ������� ������: "EPSG:3857", "crslist:80070050"
 //            � ������ ������ �������������� ����������� � ������� 3857 (�������� ��������� �� ����),
 //            �� ������ - � ����������, ��������� �� ����� crslist.xml �� ���� 80070050,
 //            �� ����, � ��������� ���������������� ������� ���������, ��������� � ����� crslist.xml.
 // callevent - ����� ������� ��������� ������ ��� ��������� ����������� � �������� ����������� ������ (��. maptype.h)
 // parm      - ��������, ������������ � ������� ��������� ������ (��������, ����� ������ ��������� ���������)
 // logfile   - ���� � ����� ������� ������ ��������� (����� ���� 0)
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI ImportFromDirPro(const WCHAR* namedir, WCHAR* namemap, long int size,
                                          HMESSAGE handle, long int typesit, const WCHAR * password, long int psize,
                                          const char * crscode, EVENTSTATE callevent, void * parm,
                                          const WCHAR * logfile);

 // �������� ����� �� ����� SXF, TXF ��� DIR � �������������� Select
 // � ��������������� ��������� � ���� ���������
 // ����� SXF � TXF ����� ������� ���������� � ������, �������� ��� ��������
 // hmap    - ������������� �������� ����� (��� ����������� �������
 //           ���� ���������) ��� 0;
 // sxfname - ��� ������������ ����� ���� SXF, TXF ��� DIR;
 // mapname - ��� ����������� �����; ����� ���� ���� ��� ��������� �� ������ 
 //           ������, � ���� ������ ����������� ����� � ��������� ������ 
 //           �� ���������� �����������.
 //           ���� namemap ��������� �� ����� ����������� ����� (size), 
 //           �� � ����� ������������ ��� ����������� �����;
 //           ���� ����� �� ���� � ��������� - ��� ����� ���� ������� (���������) 
 // size    - ����� ������, �� ������� ��������� ���������� namemap ��� 0. ������ �����
 //           ����� MAX_PATH (256);
 // handle  - ������������� ���� �������, �������� ���������� �������������� 
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux);
 // select  - ������ ����������� �������� � �����, ���� ���������� ���������� 
 //           ��������� ������;
 // mode    - ����� ���������� ������:
 //           0 - ����� ������� �� ���������� ����������� ������ � ����� � 
 //               �������� ����� � ����������,
 //               ���� ������ �� ������, �� ���������� �������;
 //           1 - ���������� �������� � ������ ����������� �������� � �� �����,
 //               ������������ ������� ��������� � ������������� SXF (TXF),
 //               ���� - ������������ �� �������, �� ����������� ����� ���� (�����);
 //           2 - ���������� �������� � ������ ����������� �������� � ��������
 //               ����� ��� ����� �����������
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UpdateFromAnySxf(HMAP hmap,
                                         const char * sxfname,
                                         char * mapname,
                                         long int size,
                                         HMESSAGE handle,
                                         HSELECT select,
                                         long int mode);

_VECIMP long int _VECAPI UpdateFromAnySxfUn(HMAP hmap,                           // 07/08/14
                                         const WCHAR * sxfname,
                                         WCHAR * mapname,
                                         long int size,
                                         HMESSAGE handle,
                                         HSELECT select,
                                         long int mode);

 // ��������� ����� �� ����� SXF, TXF ��� DIR � �������������� Select           // 17/07/16
 // � ��������������� ��������� � ���� ���������
 // ����� SXF � TXF ����� ������� ���������� � ������, �������� ��� ��������
 // namedir - ��� ������������ ����� ���� DIR;
 // namemap - ��� ����������� �����
 //           ��� ���� ��� ��������� �� ������ ������ (����� �������� 1024 �������
 //           c ������� ������ ������ ����) ��� ��������� �� ����� ��� ����������
 //           �����. ���� namemap ��������� �� ����� ����������� ����� (size),
 //           �� � ����� ������������ ��� ��������� �����;
 //           ��� ����� DIR ��� ����� ����� - MPT (������ ������, ���������� ���
 //           �������� ����� �� DIR) ��� MAP (������������� �����);
 // size    - ����� ������, �� ������� ��������� ���������� namemap ��� 0. ������ �����
 //           ����� 2048 ����;
 // handle  - ������������� ���� �������, �������� ���������� ��������������
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux) ��� 0;
 // callevent - ����� ������� ��������� ������ ��� ��������� ����������� � �������� ����������� ������ (��. maptype.h)
 // parm      - ��������, ������������ � ������� ��������� ������ (��������, ����� ������ ��������� ���������)
 // logfile   - ���� � ����� ������� ������ ��������� (����� ���� 0)
 // mode    - ����� ���������� ������:
 //           0 - ����� ������� �� ���������� ����������� ������ � ����� �
 //               �������� ����� � ����������,
 //               ���� ������ �� ������, �� ���������� �������;
 //           1 - ���������� �������� � ������ ����������� �������� � �� �����,
 //               ������������ ������� ��������� � ������������� SXF (TXF);
 //           2 - ���������� �������� � ������ ����������� �������� � ��������
 //               ����� ��� ����� �����������;
 //           3 - ������ ������ ��� ���������� ����� ������ (����).
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UpdateFromDirPro(const WCHAR* namedir, WCHAR* namemap, long int size, long int mode,
                                          HMESSAGE handle, EVENTSTATE callevent, void * parm,
                                          const WCHAR * logfile);

 // ��������� (��������������) ����� � �������� ������ SXF
 // mapname - ��� ����� ����������� �����;
 // list    - ����� ����� ��� ������������� ����� ��� 1;
 // sxfname - ��� ������������ ����� SXF, ������ ��������� �
 //           ������ �����, �� ����� ���������� SXF;
 // flag    - ��� �������� ��������� (0 - �����, 4 - �������
 //           ��� �����, �������������� ������������� ����������,
 //           -1 - ���������� �� ���� ��������� �� �����);
 //           ���� ����� �� ���� � ��������� - ��� ����� ���� ������� (���������)
 // handle  - ������������� ���� �������, �������� ���������� ��������������
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux);
 // select  - ������ ����������� �������� � �����, ���� ���������� ����������
 //           ��������� ������;
 // flserv  - �������� ��������� ������ c ������� � ����������� � ��� ��������������
 //           (�������������� � ������ 10.7 � ����) 
 // ��� ��������, �������� ���������� � ������, ���������� ������ ��������
 // � ����, ��������� � �������� �����
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI ExportToSxfEx(const char * mapname, long int list,
                                    const char * sxfname, long int flag,
                                    HMESSAGE handle, HSELECT select, long int flserv);

_VECIMP long int _VECAPI ExportToSxfUn(const WCHAR * mapname,                    // 07/08/14
                                      long int list,
                                      const WCHAR * sxfname,
                                      long int flag,
                                      HMESSAGE handle,
                                      HSELECT select,
                                      long int flserv);

 // ��������� (��������������) ����� � ��������� ������ TXF
 // mapname - ��� ����� ����������� �����;
 // list    - ����� ����� ��� ������������� ����� ��� 1;
 // txfname - ��� ������������ ����� TXF, ������ ��������� �
 //           ������ �����, �� ����� ���������� SXF;
 // flag    - ��� �������� ��������� (0 - �����, 4 - �������, 8 - �������,
 //           ��� �����, �������������� ������������� ����������,
 //           -1 - ���������� �� ���� ��������� �� �����);
 //           ���� ����� �� ���� � ��������� - ��� ����� ���� ������� (���������)
 // precision - ����� ������ ����� ������� ��� ��������� � ������ ��� 0;
 //             ���� ����� ����� ���������� �������� � �� (2 �����) ���
 //             � �� (3 �����), �� precision ������������;
 // isutf8    - ������� ������ �������� ������, ����� ����� �����, ������� �������� � 
 //             ��������� �������� � ��������� utf8 (���� �������� ���� ���������,
 //             ����� - � ��������� ANSI)
 // handle    - ������������� ���� �������, �������� ���������� �������������� 
 //             ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux);
 // select    - ������ ����������� �������� � �����, ���� ���������� ���������� 
 //             ��������� ������;
 // ��� ��������, �������� ���������� � ������, ���������� ������ ��������
 // � ����, ��������� � �������� �����
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI ExportToTxfPro(const WCHAR * mapname,        // 22/01/16
                                        long int list,
                                        const WCHAR * txfname,
                                        long int flag,
                                        long int precision,
                                        long int isutf8,
                                        HMESSAGE handle,
                                        HSELECT select);

_VECIMP long int _VECAPI ExportToTxf(const char * mapname,
                                    long int list,
                                    const char * txfname,
                                    long int flag,
                                    long int precision, 
                                    HMESSAGE handle,
                                    HSELECT select);

_VECIMP long int _VECAPI ExportToTxfUn(const WCHAR * mapname,
                                      long int list,
                                      const WCHAR * txfname,
                                      long int flag,
                                      long int precision,
                                      HMESSAGE handle,
                                      HSELECT select);

 // ��������� (��������������) ����� � ������ DIR
 // hmap    - ������������� �������� ������
 // dirname - ��� ������������ ����� DIR, ������ ��������� �
 //           ������ ��������� ������� ��� ������� �����, �� ����� ���������� DIR;
 // type    - ��� ����������� ������ (0 - SXF, 1 - TXF);
 // flag    - ��� �������� ��������� (0 - �����, 4 - �������, 8 - �������,
 //           ��� �����, �������������� ������������� ����������,
 //           -1 - ���������� �� ���� ��������� �� �����);
 //           ���� ����� �� ���� � ��������� - ��� ����� ���� ������� (���������)
 // total   - ������� ���������� � DIR ������ ������� ����� (0) ��� ���� ����
 //           ��������� (1);
 // precision - ��� ������ TXF ����� ������ ����� ������� ��� ��������� � ������ ��� 0;
 //           ���� ����� ����� ���������� �������� � �� (2 �����) ���
 //           � �� (3 �����), �� precision ������������;
 // handle  - ������������� ���� �������, �������� ���������� ��������������
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux);
 // select  - ������ ����������� �������� � �����, ���� ���������� ����������
 //           ��������� ������;
 // frsc    - �������� ��� �������������� � ���� sxf (���� �� ����� 0)
 // utf8    - �������� ����� ������ � ����� TXF (���� type ����� 1) � ��������� UTF8
 // ��� ��������, �������� ���������� � ������, ���������� ������ ��������
 // � ����, ��������� � �������� �����
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI ExportToDirEx(HMAP hmap, const char * dirname,
                                    long int type, long int flag,
                                    long int total, long int precision,
                                    HMESSAGE handle, HSELECT select, long int frsc);

_VECIMP long int _VECAPI ExportToDirUn(HMAP hmap, const WCHAR * dirname,
                                      long int type, long int flag, long int total,
                                      long int precision, HMESSAGE handle,
                                      HSELECT select, long int frsc, long int isutf8);

 // ��������� ������������ ������ � ZIP-�����                    // 09/05/16
 // (zip-����� ����� ���������� �� ������� �� ����� ������ �� � ���)
 // zipfile - ���� � ������
 // error   - ��� ������ (������ ������� ����� ���� � ��� ���������� ������)
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI CheckZipValidate(const WCHAR * zipfile, long int * error);

 // ����������� ZIP-���� � �������� �����                        
 // zipfile - ���� � ������
 // folder  - ���� � ����� ��� ���������� ������
 // logfile - ���� � ������������ ����� ��������� ���������� ������ (����� ���� 0)
 // error   - ���� ��� ������ ���� ������ ���������� ������
 // message - ������� ������ ��������� �� ������ �� �����
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UnZipToFolder(const WCHAR * zipfile, const WCHAR * folder,
                                       const WCHAR * logfile, long int * error,
                                       long int message);

 // ����������� ������ ������ �� ZIP-����� � �������� �����      
 // zipfile - ���� � ������
 // folder  - ���� � ����� ��� ���������� ������
 // extlist - ������ ���������� �� ����� ������, ������� ����� ����������� � �������� �����
 // extcount - ����� ���������� � ������ (������� ����������)
 // logfile - ���� � ������������ ����� ��������� ���������� ������ (����� ���� 0)
 // error   - ���� ��� ������ ���� ������ ���������� ������
 // message - ������� ������ ��������� �� ������ �� �����
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UnZipToFolderEx(const WCHAR * zipfile, const WCHAR * folder,
                                         const char ** extlist, long  int extcount,
                                         const WCHAR * logfile, long int * error,
                                         long int message);

 // ����������� �������� ���� �� ZIP-����� � ������
 // zipfile  - ���� � ������
 // filename - ��� ���������������� �����
 // logfile - ���� � ������������ ����� ��������� ���������� ������ (����� ���� 0)
 // error   - ���� ��� ������ ���� ������ ���������� ������
 // message - ������� ������ ��������� �� ������ �� �����
 // ��� ������ ���������� ����, ����� - ������������� ������ � ������
 // ��� ��������� ������ ������������ ������� UnZipMemoryPoint
 // ����� ���������� ������ ���������� ���������� ������� �������� UnZipFreeMemory

_VECIMP HANDLE _VECAPI UnZipFileToMemory(const WCHAR * zipfile, const WCHAR * filename,
                                         const WCHAR * logfile, long int * error,
                                         long int message);

 // ��������� ����� � ������ ������ �������������� ����� �� �������������� ������
 // ��� ������ ���������� ����

_VECIMP const char * _VECAPI UnZipMemoryPoint(HANDLE hmemory, long int * size);

 // ���������� ����� �������������� ����� �� �������������� ������

_VECIMP void _VECAPI UnZipFreeMemory(HANDLE hmemory);

 // ��������� ���������� �� ���������� ZIP-������ (�������� ������, ������ � zip,
 // ������� ������, ���� � ����� �������� �����, ��� �����)
 // zipfile - ���� � ������ 
 // logfile - ���� � ������������ ����� ��������� ��� ������ ����������
 // error   - ���� ��� ������ ���� ������ ���������� ������ 
 // message - ������� ������ ��������� �� ������ �� ����� 
 // ��� ������ ���������� ���� 

_VECIMP long int _VECAPI UnZipInfo(const WCHAR * zipfile, const WCHAR * logfile, 
                                   long int * error, long int message);

 // ��������� ������ ������ � ZIP-������
 // zipfile - ���� � ������
 
// error   - ���� ��� ������ ���� ������ ���������� ������
 // message - ������� ������ ��������� �� ������ �� �����
 // ��� ������ ���������� ����, ����� - ������������� ������ � ������
 // ��� ��������� ������ ������������ ������� UnZipMemoryPoint
 // ����� ���������� ������ ���������� ���������� ������� �������� UnZipFreeMemory

_VECIMP HANDLE _VECAPI UnZipFileList(const WCHAR * zipfile,
                                     long int * error, long int message);

 // ��������� ������� ������ ��������� ���� � ZIP-������
 // zipfile - ���� � ������
 // extend  - ������ �� ������� ���������� (���������) ������, ����������� ��������
 //           ��������: "sxf,txf,rsc,.meta.xml,.geojson,gml"
 //           ��������� ������ ����� ���� � ����� ��������, ����� ������ �� 2048 ����
 // amounts - ������ ��������� ������ � �������� ����������� � zip-������
 // count   - ����� ��������� � ����� ���������� � ������
 // error   - ���� ��� ������ ���� ������ ���������� ������
 // message - ������� ������ ��������� �� ������ �� �����
 // ��� ������ ���������� ����, ����� - ����� ������������ ����������

_VECIMP long int _VECAPI UnZipFileCount(const WCHAR * zipfile, const char * extend,
                                        long int * amounts, long int count,
                                        long int * error, long int message);


 // ================================================================
 //
 //                      ���������� �������                         // 03/05/10
 //
 //              ����������� ����� ����� ����� �������
 // ================================================================

 // ��������� ����� �� ����� SXF
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadSxfToMap(char * namesxf,
                                     char * namemap,
                                     char * namersc,
                                     HMESSAGE handle);

 // ��������� ����� �� ����� SXF � �������������� Select
 // ��� ������ ���������� ����
 
_VECIMP long int _VECAPI LoadSxfToMapSelect(char * namesxf,
                                           char * namemap,
                                           char * namersc,
                                           HMESSAGE handle,
                                           HSELECT select);

 // ��������� ����� �� ����� SXF � �������������� Select 
 // � ���������� ����� �����
 // ��������� name � namehdr - �� ��������������
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadSxfToMapSelectName(char * namesxf,
                                               char * namemap,
                                               char * namersc,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char * namehdr);

 // ��������� ����� �� ����� TXF
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadTxtToMap(char * nametxt,
                                     char * namemap,
                                     char * namersc,
                                     HMESSAGE handle);

 // ��������� ����� �� ����� TXF � ������������� Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadTxtToMapSelect(char * nametxt,
                                           char * namemap,
                                           char * namersc,
                                           HMESSAGE handle,
                                           HSELECT select);


 // ��������� ����� �� ����� TXF � ������������� Select � ���������� �����
 // ��������� name � namehdr - �� ��������������
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadTxtToMapSelectName(char * nametxt,
                                               char * namemap,
                                               char * namersc,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char * namehdr);

 // ��������� ����� �� ������ DIR
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadDirToMap(char* namedir,
                                     char* namemap,
                                     HMESSAGE handle);

 // ��������� ����� �� ������ DIR � ��������������  Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadDirToMapSelect(char* namedir,
                                           char* namemap,
                                           HMESSAGE handle,
                                           HSELECT select);

 // ��������� ����� �� ������ DIR � ��������������  Select � 
 // ���������� ����� ������ � ����� ����� ��������
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadDirToMapSelectName(char* namedir,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char* namersc);

 // ��������� ����� �� ������ �� ������� ������
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadMapToMap(HMAP  map,
                                     char * namemap,
                                     HMESSAGE handle);

 // ��������� ����� �� ������ ������� ������ � ��������������  Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI LoadMapToMapSelect(HMAP map,
                                           char* namemap,
                                           HMESSAGE handle,
                                           HSELECT select);

 // �������� ����� �� ����� SXF
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UpdateMapFromSxf(char* namesxf,
                                         char* namemap,
                                         HMESSAGE handle);

 // �������� ����� �� ����� SXF � �������������� Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UpdateMapFromSxfSelect(char* namesxf,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // �������� ����� �� ������ ������� ������ � ��������������  Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UpdateMapToMapSelect(HMAP map,
                                             const char* namemap,
                                             HMESSAGE handle,
                                             HSELECT select);

 // �������� � ����� ������ �� ����� SXF � �������������� Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI AppendMapFromSxfSelect(char* namesxf,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // �������� ����� �� ����� TXF
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UpdateMapFromTxt(char* nametxt,
                                         char* namemap,
                                         HMESSAGE handle);

 // �������� ����� �� ����� TXF � �������������� Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UpdateMapFromTxtSelect(char* nametxt,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // �������� � ����� ������ �� ����� TXF � �������������� Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI AppendMapFromTxtSelect(char* namesxf,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // �������� ����� �� ����� DIR � �������������� Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI UpdateMapFromDirSelect(char* namedir,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // �������� � ����� ������ �� ����� DIR � �������������� Select
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI AppendMapFromDirSelect(char* namedir,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // ��������� ���������� ������ ��������� �����
 // �� ����� ����� SXF
 // ��������� MAPREGISTER � LISTREGISTER ������� � mapcreat.h
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI mapGetSxfInfoByName(const char * name,
                                            MAPREGISTER * map,
                                            LISTREGISTER * sheet);

_VECIMP long int _VECAPI mapGetSxfInfoByNameEx(const char * name,
                                              MAPREGISTEREX * map,
                                              LISTREGISTER * sheet);

 // ��������� (�������������) ����� �� ����� SXF, TXF ��� DIR �
 // �������������� Select � ��������������� ��������� � ���� ���������
 // ����� SXF � TXF ����� ������� ���������� � ������, �������� ��� ��������
 // hmap    - ������������� �������� ����� (������������� ���������
 //           ��� ����������� ������� ���� ���������) ��� 0;
 // sxfname - ��� ������������ ����� ���� SXF, TXF ��� DIR;
 // rscname - ��� ����� ��������������, � ������� ����������� �����,
 //           ��� �������������� ����� ��������� �� SXF (TXF) �������� GetRscNameFromSxf
 //           ��� �� �����; ��� ����� DIR ����� ���� 0;
 // mapname - ��� ����������� ����� (������ ��������� � ������ SXF (TXF))
 //           ��� ���� ��� ��������� �� ������ ������ (����� �������� MAX_PATH
 //           c ������� ������ ������ ����) ��� ��������� �� ����� ��� ����������
 //           �����. ���� ��� ����� �� ������ ��� ������ ������ �����, �� �����
 //           ��������� � ������ SXF (TXF) � ����������� ".sit". ���� namemap
 //           ��������� �� ����� ����������� ����� (size), �� � ����� ������������ 
 //           ��� ��������� �����;
 //           ��� ����� DIR ��� ����� ����� - MPT (������ ������, ���������� ��� 
 //           �������� ����� �� DIR) ��� MAP (������������� �����);
 // size    - ����� ������, �� ������� ��������� ���������� namemap, ��� 0. ������ �����
 //           ����� MAX_PATH_LONG (1024);
 // handle  - ������������� ���� �������, �������� ���������� �������������� 
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux);
 // select  - ������ ����������� �������� � �����, ���� ���������� ����������
 //           ��������� ������;
 // ��� ���������� �������� ����� � �������� ���������� ������� �������
 // mapAppendData(hmap, namemap). ���� mapname �������� ��� ����� ���� MAP �
 // ��� �������� ���� �� ���� ����, �� ��� ������� ������ ����������� ��������
 // ������ ����� � ����� MAP. � ���� ������ ������� mapAppendData �� ������ ����������. 
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI ImportFromAnySxf(HMAP hmap,
                                         const char * sxfname,
                                         const char * rscname,
                                         char * mapname,
                                         long int size,
                                         HMESSAGE handle,
                                         HSELECT select);

//========================================================================
//   ������� ���������� �����
//========================================================================
//  �������������� ���������� ��������� ��������� :
//  WM_LIST   = 0x586   WParam - ���������� ������ � ������
//                      LParam - ����� �������� �����
//  WM_OBJECT = 0x585   WParam - ������� ������������ ��������

 // ��������� (��������������) ����� � �������� ������ SXF 
 // mapname - ��� ����� ����������� �����;
 // list    - ����� ����� ��� ������������� ����� ��� 1;
 // sxfname - ��� ������������ ����� SXF, ������ ��������� �
 //           ������ �����, �� ����� ���������� SXF;
 // flag    - ��� �������� ��������� (0 - �����, 4 - �������
 //           ��� �����, �������������� ������������� ����������,
 //           -1 - ���������� �� ���� ��������� �� �����);
 //           ���� ����� �� ���� � ��������� - ��� ����� ���� ������� (���������) 
 // handle  - ������������� ���� �������, �������� ���������� �������������� 
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux);
 // select  - ������ ����������� �������� � �����, ���� ���������� ���������� 
 //           ��������� ������;
 // ��� ��������, �������� ���������� � ������, ���������� ������ ��������
 // � ����, ��������� � �������� �����
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI ExportToSxf(const char * mapname,
                                    long int list,
                                    const char * sxfname,
                                    long int flag,
                                    HMESSAGE handle,
                                    HSELECT select);

 // ��������� (��������������) ����� � ������ DIR
 // hmap    - ������������� �������� ������
 // dirname - ��� ������������ ����� DIR, ������ ��������� �
 //           ������ ��������� ������� ��� ������� �����, �� ����� ���������� DIR;
 // type    - ��� ����������� ������ (0 - SXF, 1 - TXF);
 // flag    - ��� �������� ��������� (0 - �����, 4 - �������, 8 - �������,
 //           ��� �����, �������������� ������������� ����������,
 //           -1 - ���������� �� ���� ��������� �� �����);
 //           ���� ����� �� ���� � ��������� - ��� ����� ���� ������� (���������)
 // total   - ������� ���������� � DIR ������ ������� ����� (0) ��� ���� ����
 //           ��������� (1);
 // precision - ��� ������ TXF ����� ������ ����� ������� ��� ��������� � ������ ��� 0;
 //           ���� ����� ����� ���������� �������� � �� (2 �����) ���
 //           � �� (3 �����), �� precision ������������;
 // handle  - ������������� ���� �������, �������� ���������� ��������������
 //           ��������� (HWND ��� Windows, CALLBACK-������� ��� Linux);
 // select  - ������ ����������� �������� � �����, ���� ���������� ����������
 //           ��������� ������;
 // ��� ��������, �������� ���������� � ������, ���������� ������ ��������
 // � ����, ��������� � �������� �����
 // ��� ������ ���������� ����

_VECIMP long int _VECAPI ExportToDir(HMAP hmap,
                                    const char * dirname,
                                    long int type,
                                    long int flag,
                                    long int total,
                                    long int precision,
                                    HMESSAGE handle,
                                    HSELECT select);
                                              
// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(Windows)
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveSxfFromMap(char * namemap,
                                       int list,
                                       char * namesxf,
                                       HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(Windows) �
// ��������������  Select
//  flag = 0 - ������ � ������
//  flag = 4 - ������ � ��������
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveSxfFromMapSelect(const char * namemap,
                                             long int list,
                                             const char * namesxf,
                                             HMESSAGE handle,
                                             HSELECT select,
                                             long int flag = 0,
                                             const char * nameregion = NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(Windows) �
//          ��������������  Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveSxfFromHMapSelect(HMAP map,
                                              long int list,
                                              const char * namesxf,
                                              HMESSAGE handle,
                                              HSELECT select,
                                              long int flag = 0,
                                              const char * nameregion = NULL);
_VECIMP long int _VECAPI SaveSxfFromHMapSelectUn(HMAP map,
                                                 long int list,
                                                 const WCHAR * namesxf,
                                                 HMESSAGE handle,
                                                 HSELECT select,
                                                 long int flag = 0,
                                                 const WCHAR * nameregion = NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(XY)
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtFromMap(const char * namemap,
                                       long int   list,
                                       const char * nametxt,
                                       HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(XY) �
//      �������������� Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtFromMapSelect(const char * namemap,
                                             long int list,
                                             const char * nametxt,
                                             HMESSAGE handle,
                                             HSELECT select,
                                             const char * nameregion = NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(XY) �
// �������������� Select
// namemap - ��� ����������� �����,
// list    - ����� �����,
// nametxt - ��� ����� TXF,
// handle  - ������������� ����, �������� ���������� ��������� � ���� ��������
//           (WM_INFOLIST, WM_OBJECT)
// select  - ������������� ������� ������ ��������, ������������ ������
//           �������������� � ��������� ���� ��������,
// nameregion - ��� ������ (�����),
// precision  - ����� ������ ����� ������� ��� ������������� ���������
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtFromMapSelectEx(const char * namemap,
                                               long int list,
                                               const char * nametxt,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               const char * nameregion,
                                               long int precision);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(BL)
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtGeoFromMap(const char * namemap,
                                          long int list,
                                          const char * nametxt,
                                          HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(BL) �
//      �������������� Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtGeoFromMapSelect(const char * namemap,
                                                long int list,
                                                const char * nametxt,
                                                HMESSAGE handle,
                                                HSELECT select,
                                                const char * nameregion = NULL);

_VECIMP long int _VECAPI SaveTxtGeoGradFromMapSelect(const char * namemap,
                                                    long int list,
                                                    const char * nametxt,
                                                    HMESSAGE handle,
                                                    HSELECT select,
                                                    const char * NameRegion = NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(WINDOWS) �� DIR
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirSxfFromMap(const char* namemap,
                                          const char* namedir,
                                          HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(WINDOWS) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirSxfFromMapSelect(const char* namemap,
                                                const char* namedir,
                                                HMESSAGE handle,
                                                HSELECT select);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(WINDOWS) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirSxfIntFromMapSelect(const char* namemap,
                                                   const char* namedir,
                                                   HMESSAGE handle,
                                                   HSELECT select);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(XY) �� DIR
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtFromMap(const char* namemap,
                                          const char* namedir,
                                          HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(XY) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtFromMapSelect(const char* namemap,
                                                const char* namedir,
                                                HMESSAGE handle,
                                                HSELECT select);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(BL) �� DIR
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtGeoFromMap(const char* namemap,
                                             const char* namedir,
                                             HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(BL) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtGeoFromMapSelect(const char* namemap,
                                                   const char* namedir,
                                                   HMESSAGE handle,
                                                   HSELECT select);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXF(BL �������) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtGeoGradFromMapSelect(const char* namemap,
                                                       const char* namedir,
                                                       HMESSAGE handle,
                                                       HSELECT select);

//-------------------------------------------------------------------
//  ��������� ���������� ���������� � ����� �� SXF
// ------------------------------------------------------------------

_VECIMP long int _VECAPI GetInfoSxf(const char * namesxf,
                                   INFOSXF * infosxf);

//-------------------------------------------------------------------
//  ��������� ���������� ���������� �� DIR
// ------------------------------------------------------------------

_VECIMP long int _VECAPI GetInfoDir(const char * namedir,
                                   INFODIR * infodir);

// ------------------------------------------------------------------
// ��������� ������ ������ SXF � DIR
// ------------------------------------------------------------------

_VECIMP long int _VECAPI GetDir(const char * namedir,
                               NAMESARRAY * sxfdir, long int length);


}       // extern "C"

#endif  // VECEXAPI_H


