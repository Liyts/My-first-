/****** MAPWEB.H *************** Belenkov O.V. ******** 12/11/07 ***
******* MAPWEB.H *************** Kruzhkov A.E. ******** 22/04/10 ***
******* MAPWEB.H *************** Nefedyeva O.A.******** 14/02/12 ***
******* MAPWEB.H *************** Savelov A.S.  ******** 11/07/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*       �������� ������ ������� � ��'���� "����������� �����"      *
*        ��������� ��� �������� �� ������ C, PASCAL, BASIC         *
*                                                                  *
********************************************************************
*                                                                  *
*     �������������� ������� � Windows :                           *
*                                                                  *
*    // �������� ����������                                        *
*    HINSTANCE libInst = ::LoadLibrary("gisacweb.dll");            *
*                                                                  *
*    // ����� �������                                              *
*    HMAP (WINAPI * lpfn_OpenMap)(const char*, long int);          *
*    (FARPROC)lpfn_OpenMap = GetProcAddress(libInst, "OpenMap");   *
*    HMAP hMap = (*lpfn_OpenMap)("Noginsk.map",0);                 *
*                                                                  *
*    // �������� ����������                                        *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/

/******************************************************************
********************  ������� ��������� ***************************
*******************************************************************

    X� X�
  ^
  | (0,0) (������ ���������� "Picture")
  +---------------------------------------------------> X�
  |                                                 ^
  |        (���������� ���� "Client")               |
  |   (0,0)                      X�                 |
  |     ----------------------->                    |
  |     |               |                           |
  |     |        x..... x  ���� ������������        |
  |     |        ....A. |                           |
  |     |        ...+.. |                           |
  |     |        ...... |                         ��������
  |     ---------x------x                    ������ ("Region")
  |     |          ^                                |
  |     |          |                                |
  |     |         ������� �������� ������           |
  |     V                  ("Draw")                 |
  |       Y�                                        |
  |                                                 V
  +----------------------------------------------------> Y� Y�
  |
  |  0,0 (������ ������ "Map" � ���������
  |       � "��������")
  |
  V        ���������� �.A � ������ X�,Y�; � ����������� X�,Y�
    Y�

******************************************************************/

#ifndef MAPWEB_H
#define MAPWEB_H

#ifndef MAPVERSN_H
 #include "mapversn.h"
#endif

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ �������� ������� ������� � ����������� ����� ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
#ifdef GISWEB
 // ��������� ������ ������

_MAPIMP long int _MAPAPI mapGetMapWebVersion();

  /*********************************************************
  *                                                        *
  *            ����� ����������� � ���� GIF                *
  *                                                        *
  *********************************************************/

 // ������� �������� ����������� ����� � ���� GIF
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // ��������� �������� �����, �������� ���������� rect.
 // ������ ��������� �� ����� ���� ������ ���������� ������ �� �������
 // ����������� ���������
 //  hmap      - ������������� �������� ������,
 //  rect      - ���������� ��������� ����� (Draw) � ����������� (Picture),
 //              ������ � ������ ����������� �� ������ ��������� �������
 //              ������ ����������� mapGetScreenWidth(),mapGetScreenHeight()
 //  gifname   - ��� ������������ ����� GIF (8 ��� �� ������)
 //  index     - ����� ����������� ����� � ������� ����� (�� 0 �� 255)
 //                0 - ���������� ���� ����
 //               -1 - ���������� ���� �����������
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapToGIF(HMAP hmap, RECT * rect,           // 22/04/10
                                          const char * gifname, long int index);

 // ������� �������� ����������� ����� � ���� GIF
 // � ������� �������� � ������� �������� �
 // �������� �� ����� �������, ��������������� �������� �������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hMap    - ������������� �������� ������
 // rect    - ���������� ��������� ����� (Draw) � ����������� (Picture)
 // select  - ������� ������ ��������, ���� ����� 0, �� �����������
 //           ������� ����������� ������\��������� (��. mapTotalPaintSelect95).
 // color   - ����, ������� ����� ���������� ������� �� �����
 // gifname - ��� ������������ ����� GIF (8 ��� �� ������)
 // index   - ����� ����������� ����� � ������� ����� (�� 0 �� 255)
 //                0 - ���������� ���� ����
 //               -1 - ���������� ���� �����������
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapAndSelectToGIF(HMAP hmap, RECT * rect,  // 22/04/10
                                                   HSELECT select, COLORREF color,
                                                   const char * gifname, long int index);

 // ���������� ������������ ������ � ���� GIF
 // � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hmap    - ������������� �������� ������,
 // rect    - ���������� ��������� ����� (Draw),
 // info    - ������������� ������� ����� � ������
 // gifname - ��� ������������ ����� GIF (8 ��� �� ������)
 // index   - ����� ����������� ����� � ������� ����� (�� 0 �� 255)
 //                0 - ���������� ���� ����
 //               -1 - ���������� ���� �����������
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintObjectToGIF(HMAP hmap, RECT * rect,        // 22/04/10
                                             HOBJ info,
                                             const char * gifname, long int index);

 // ������� �������� ����������� ����� � ���������� ������� � ���� GIF
 // � ������� �������� � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // ��������� �������� �����, �������� ���������� rect.
 // ������ ��������� �� ����� ���� ������ ���������� ������, �� �������
 // ����������� ���������
 //  hmap      - ������������� �������� ������,
 //  rect      - ���������� ��������� ����� (Draw)
 //              � ����������� (Picture),
 //  info      - ������������� ������� ����� � ������,
 //  color     - ����, ������� ����� ���������� ������� �� �����
 //  gifname   - ��� ������������ ����� GIF (8 ��� �� ������)
 //  index     - ����� ����������� ����� � ������� ����� (�� 0 �� 255)
 //                0 - ���������� ���� ����
 //               -1 - ���������� ���� �����������
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapAndObjectToGIF(HMAP hmap, RECT * rect,  // 22/04/10
                                                   HOBJ info, COLORREF color,
                                                   const char * gifname, long int index);

 // ������� �������� ����������� ����� � ����������� ������� � ���� GIF
 // � ������� �������� � ������� �������� �
 // �������� �� ����� �������, �������������� �������� �������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hMap    - ������������� �������� ������
 // rect    - ���������� ��������� ����� (Draw) � ����������� (Picture)
 // select  - ������� ������ ��������, ���� ����� 0, �� �����������
 //           ������� ����������� ������\��������� (��. mapTotalPaintSelect95).
 // color   - ����, ������� ����� ���������� ������� �� �����
 // info      - ������������� ������� ����� � ������,
 // color2    - ����, ������� ����� ���������� ������ info �� �����
 // gifname - ��� ������������ ����� GIF (8 ��� �� ������)
 // index   - ����� ����������� ����� � ������� ����� (�� 0 �� 255)
 //                0 - ���������� ���� ����
 //               -1 - ���������� ���� �����������
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapAndSelectObjectToGIF(HMAP hmap, RECT * rect,  // 14/02/12
                                                   HSELECT select, COLORREF color,
                                                   HOBJ info, COLORREF color2,
                                                   const char * gifname, long int index);
#endif  // GISWEB

  /*********************************************************
  *                                                        *
  *          ����� ����������� ����� ���� BMP              *
  *                                                        *
  *********************************************************/

 // ������� �������� ����������� ����� � ���� BMP
 // � ������� �������� � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // ��������� �������� �����, �������� ���������� rect.
 // ������ ��������� �� ����� ���� ������ ���������� ������ �� �������
 // ����������� ���������
 //  hmap      - ������������� �������� ������,
 //  rect      - ���������� ��������� ����� (Draw)
 //              � ����������� (Picture),
 //  bmpname   - ��� ������������ ����� BMP,
 //  bits      - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapToBMP(HMAP hmap, RECT * rect,
                                          const char * bmpname, long int bits);


 // ������� �������� ����������� ����� � ���� BMP
 // � ������� �������� � ������� �������� �
 // �������� �� ����� �������, �������������� �������� �������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hMap    - ������������� �������� ������
 // rect    - ���������� ��������� ����� (Draw) � ����������� (Picture)
 // select  - ������� ������ ��������, ���� ����� 0, �� �����������
 //           ������� ����������� ������\��������� (��. mapTotalPaintSelect95).
 // color   - ����, ������� ����� ���������� ������� �� �����
 // bmpname - ��� ������������ ����� BMP,
 // bits    - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapAndSelectToBMP(HMAP hMap, RECT * rect,
                                                   HSELECT select, COLORREF color,
                                                   const char * bmpname, long int bits);

 // ���������� ������������ ������ � ���� BMP
 // � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hmap    - ������������� �������� ������,
 // rect    - ���������� ��������� ����� (Draw),
 // info    - ������������� ������� ����� � ������
 // bmpname - ��� ������������ ����� BMP, 32 ���� �� ������,
 // bits    - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintObjectToBMP(HMAP hmap, RECT * rect,
                                             HOBJ info,
                                             const char * bmpname, long int bits);

 // ������� �������� ����������� ����� � ����������� ������� � ���� BMP
 // � ������� �������� � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // ��������� �������� �����, �������� ���������� rect.
 // ������ ��������� �� ����� ���� ������ ���������� ������ �� �������
 // ����������� ���������
 //  hmap      - ������������� �������� ������,
 //  rect      - ���������� ��������� ����� (Draw)
 //              � ����������� (Picture),
 //  info      - ������������� ������� ����� � ������,
 //  color     - ����, ������� ����� ���������� ������� �� �����
 //  bmpname   - ��� ������������ ����� BMP, 32 ���� �� ������,
 //  bits      - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapAndObjectToBMP(HMAP hmap, RECT * rect,
                                                   HOBJ info, COLORREF color,
                                                   const char * bmpname, long int bits);


 // ������� �������� ����������� ����� � ���� BMP ������������� �������
 // � ������� �������� � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // ��������� �������� �����, �������� ���������� rect.
 //  hmap      - ������������� �������� ������,
 //  rect      - ���������� ��������� ����� (Draw)
 //              � ����������� (Picture),
 //  bmpname   - ��� ������������ ����� BMP,
 //  bits      - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapToBigBMP(HMAP hmap, RECT * rect,
                                             const char * bmpname, long int bits);

  /*********************************************************
  *                                                        *
  *          ����� ����������� ����� ���� BITMAP           *
  *                                                        *
  *********************************************************/

 // ��������� ���������� ������� � ������� ����������� ������� BMP
 //  hmap      - ������������� �������� ������,
 //  color     - ��������� �� ������ ������ (������ ��RRGGBB - ��������� NET)
 // ���������� ����� ������� � ������� ������ (�� 256)
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetBitmapPalette(HMAP hmap, RGBQUAD * color);

 // ������� �������� ����������� ����� � �������� BITMAP
 // � ������� �������� � ������� �������� �
 // �������� �� ����� �������, �������������� �������� �������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hMap    - ������������� �������� ������
 // rect    - ���������� ��������� ����� (Draw) � ����������� (Picture)
 // select  - ������� ������ ��������, ���� ����� 0, �� �����������
 //           ������� ����������� ������\��������� (��. mapTotalPaintSelect95).
 // color   - ����, ������� ����� ���������� ������� �� �����
 // ����� ������������ ����������� ����� ������� BITMAP - mapCloseBitmap()
 // ��� ������ � ���������� ���������� ����

_MAPIMP HBITMAP _MAPAPI mapPaintMapAndSelectToBitmap(HMAP hMap, RECT * rect,
                                                     HSELECT select, COLORREF color);

 // ���������� ������������ ������ � �������� BITMAP
 // � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hmap    - ������������� �������� ������,
 // rect    - ���������� ��������� ����� (Draw),
 // info    - ������������� ������� ����� � ������
 // ����� ������������ ����������� ����� ������� BITMAP - mapCloseBitmap()
 // ��� ������ � ���������� ���������� ����

_MAPIMP HBITMAP _MAPAPI mapPaintObjectToBitmap(HMAP hmap, RECT * rect,
                                               HOBJ info);

 // ������� �������� ����������� ����� � ����������� ������� � �������� BITMAP
 // � ������� �������� � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // ��������� �������� �����, �������� ���������� rect.
 // ������ ��������� �� ����� ���� ������ ���������� ������ �� �������
 // ����������� ���������
 //  hmap      - ������������� �������� ������,
 //  rect      - ���������� ��������� ����� (Draw)
 //              � ����������� (Picture),
 //  info      - ������������� ������� ����� � ������,
 //  color     - ����, ������� ����� ���������� ������� �� �����
 // ����� ������������ ����������� ����� ������� BITMAP - mapCloseBitmap()
 // ��� ������ � ���������� ���������� ����

_MAPIMP HBITMAP _MAPAPI mapPaintMapAndObjectToBitmap(HMAP hmap, RECT * rect,
                                                     HOBJ info, COLORREF color);

}  // extern "C"

#endif  // MAPWEB_H
