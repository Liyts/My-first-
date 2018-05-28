/******  WMSAPI.H   ***********  Belenkov     O.V. **** 30/08/14 ***
*******  WMSAPI.H   ***********  Dishlenko    S.G. **** 04/10/11 ***
*******  WMSAPI.H   ***********  Zheleznyakov V.A. **** 23/06/16 ***
*******  WMSAPI.H   ***********  Tarakanova I.R.   **** 14/02/14 ***
*******  WMSAPI.H   ***********  Konon V.N.        **** 25/01/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                  ��������� ������� � WMS-��������                *
*              ��� ���������� gisacces.dll (gisu64acces.dll)       *
*                                                                  *
*******************************************************************/

#ifndef WMSAPI_H
#define WMSAPI_H

#include "mapcreat.h"                                     // 04/10/11

extern "C"
{
  // ����������� � WMS �������
  // wmsstring - ������ ����������� � �������
  // ������� ��� ������: WMS#IP=ipname&Id1=layerID&Name1=layerName
  // ��� ipname - IP ����� �������
  // layerID - �������������� ���� �������
  // layerName - ����� ���� �������
  // ��� ������ ���������� 0

_MAPIMP HMAP _MAPAPI mapOpenWMS(const char* wmsstring);
_MAPIMP HMAP _MAPAPI mapOpenWMSUn(const WCHAR* wmsstring);

  // ����������� � WMS ������� � �������� ������ �����
  // ���������� ����� WMS-���������� � ������ ����������
  // hMap    - ������������� ��������� ���������
  // wmsstring - ������ ����������� � �������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapOpenWMSForMap(HMAP hMap, const char* wmsstring);
_MAPIMP long int _MAPAPI mapOpenWMSForMapUn(HMAP hMap, const WCHAR* wmsstring);

  // ������� ���������� �� ��� ����������� ������ � ������ �����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� ������������ ���������� � ������ ���������� (� 1)
  // freelib - ����������� ������� ����������, 1 - �� �����������, 0- �����������

_MAPIMP void _MAPAPI mapCloseWMS(HMAP hMap, long int number, long int freelib = 0);

  // ��������� ��� ���������� �� ������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� ���������� � ������ ���������� (� 1)
  // ��� ������ ���������� ������ ������

_MAPIMP const char * _MAPAPI mapGetWMSName(HMAP hMap, long int number);

  // ��������� ��� ���������� �� ������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� ���������� � ������ ���������� (� 1)
  // wname     - ����� ��� ������������ ������
  // namesize - ������ ������ � ������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapGetWMSNameUn(HMAP hMap, long int number,    // 14/02/14
                                         WCHAR *wname, int namesize);

  // ��������� ����� �������� ����������
  // hMap    - ������������� ��������� ���������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapGetWMSCount(HMAP hMap);

  // ��������� ����� ������� �������� EPSG ��� WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� ���������� � ������ ���������� (� 1)
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapGetWMSEPSGCode(HMAP hMap, long int number);

  // ��������� ������ � �������� ��� WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� ���������� � ������ ���������� (� 1)
  // mapregister - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // datum   - ��������� ��������� � ���������� ������� ������� ���������
  //           � WGS-84 (datum ����� ���� 0)
  // ellparam - ��������� ����������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapGetWMSProjectionData(HMAP hMap, int number,
                                                 MAPREGISTEREX* mapregister,
                                                 DATUMPARAM* datum,
                                                 ELLIPSOIDPARAM* ellparam);

  // ��������� ����������� �������� ������������� ������ � ������ � ������ �����
  // ��� ����������� ������ �� ����� ������������ �������� �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // frame      - ������������ �������� ����������� � ������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetWMSPlaneFrame(HMAP hMap, long int number, DFRAME *frame);

  // ��������� �������� ������� ����������� � �������� � ����������� � �������
  // �������� ��������� WMS-����������, �������� ����� EPSG (mapGetWMSEPSGCode)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // frame      - ������������ �������� ����������� � ��������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapGetWMSGeoFrame(HMAP hMap, long int number, DFRAME * frame);

  // ���������/���������� ������� ��������� ������, ����������� � WMS
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� ���������� � ������ ���������� (� 1)
  //  view = 0 - �� �����
  //  view = 1 - ������ ���������
  //  view = 2 - ����������
  //  view = 3 - ��������������
  //  view = 4 - �������
  //  view = 5 - ����������

_MAPIMP long int _MAPAPI mapGetWMSView(HMAP hMap,long int number);
_MAPIMP long int _MAPAPI mapSetWMSView(HMAP hMap,long int number,
                                       long int view);

  // ���������/���������� ������� ����������� WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // order  - 0 - ��� ��������� ������, 1 - ��� ������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapSetWMSViewOrder(HMAP hMap, long int number,
                                            long int order);
_MAPIMP long int _MAPAPI mapGetWMSViewOrder(HMAP hMap, long int number);

  // ��������� ������� ������� WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetWMSBright(HMAP hMap,long int number);

  // ��������� ������������� ������� WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetWMSContrast(HMAP hMap,long int number);

  // ���������� ������� ������� WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // bright  - �������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetWMSBright(HMAP hMap, long int number,
                                          long int bright);

  // ���������� ������������� WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // contrast - ��������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetWMSContrast(HMAP hMap, long int number,
                                                       long int contrast);

  // ���������� ���������� ���� ������ WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // color  - �������� ����������� ����� � ������� RGB (�� 0 �� 0x00FFFFFF)
  // ��� ��������� IMGC_TRANSPARENT (0xFFFFFFFF) ���������� ���� �� ������������
  // ��� ������ ���������� IMGC_TRANSPARENT

_MAPIMP COLORREF _MAPAPI mapSetWMSTransparentColor(HMAP hMap, long int number,
                                                   COLORREF color);

  // ��������� ���������� ���� ������ WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // ���������� ���� � ������� RGB (�� 0 �� 0x00FFFFFF)
  // ��� �������� IMGC_TRANSPARENT (0xFFFFFFFF) ���������� ���� �� ������������
  // ��� ������ ���������� IMGC_TRANSPARENT

_MAPIMP  COLORREF _MAPAPI mapGetWMSTransparentColor(HMAP hMap, long int number);

  // ��������� �������� �������� ������ � ������� ������ ��������� ������ WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // �� ������ bottomScale ������������ ����������� �������� ������ ������� ��������� ������
  // �� ������ topScale ������������ ����������� �������� ������� ������� ��������� ������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetWMSRangeScaleVisible(HMAP hMap, long int number,
                                                     long int *bottomScale,
                                                     long int *topScale);

  // ���������� �������� �������� ������ � ������� ������ ��������� ������ WMS-����������
  // hMap    - ������������� ��������� ���������
  // number  - ���������� ����� c��������� � ������ ���������� (� 1)
  // bottomScale - ����������� �������� ������ ������� ��������� ������
  // topScale    - ����������� �������� ������� ������� ��������� ������
  //               bottomScale <= topScale, ����� ���������� 0
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetWMSRangeScaleVisible(HMAP hMap, long int number,
                                                     long int bottomScale,
                                                     long int topScale);

  

  // �������� ����������� � WMS �������
  // hMap   - ������������� ��������� ���������
  // number - ���������� ����� c��������� � ������ ���������� (� 1)
  // hdc    - �������� ���������� �����������,
  // erase  - ������� ��������������� ������� ���� �����������,
  // rect   - ������� �������������� ����������� � ��������,
  //          ������ = (rect.RT-rect.LT+1) � ������ = (rect.DN-rect.UP+1)
  // frame  - ������������� ���������� ������������ ������� � ��������
  //          � ����������� � ������� �������� ��������� WMS-����������,
  //          �������� ����� EPSG (mapGetWMSEPSGCode)
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapPaintWMS(HMAP hMap, long int number, HDC hdc, long int erase,
                                     RECT* rect, DFRAME* frame);

  // �������� ��������� WMS-����������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapChangeWMS(HMAP hMap, long int number, const char* wmsstring);
_MAPIMP long int _MAPAPI mapChangeWMSUn(HMAP hMap, long int number, const WCHAR* wmsstring);

  // ��������� - ����������� �� �������� ����������� (WMS-��������)
  // hWMS - ������������� �������
  // ���� ��� - ���������� 0

_MAPIMP long int _MAPAPI mapIsTranslateWMS(HMAP hMap);

  // ���������� ������ ����������� � ���� ������ (����������� ������ � ���� ����)
  // hmap        - ������������� �������� ���������
  // parm      - ������� ��������� ���������, ���� Handle ������ 
  //             ��������� ������������� ���� ����������, ���������������
  //             ����������� ���������. �������� ��������� - ��. maptype.h)
  // left, top   - ���������� ������������ ���� (������� ����� ���� � �������� ������)
  // ��� ������������� ������� ���������� ���������� ��������� AW_OPENDOC, AW_CLOSEDOC,
  // MT_MAPWINPORT, AW_MOVEDOC, MT_SELECTOBJECT.
  // � GIS ToolKit �� ��������� ��������� �������� ��������� TMapWMSPopupDialog
  // �������� ���� (parm->Handle) ���������� ���������:
  //                          �������� ���� (parm->Handle)
  //                          AW_OPENDOC - ������� �������� � ����������
  //                          ::SendMessage(Parm->Handle, AW_OPENDOC, (WPARAM)fname, 0);
  //                          AW_CLOSEDOC - ������� ������� �������� � ����������
  //                          ::SendMessage(parm->Handle, AW_CLOSEDOC, (WPARAM)filename.c_str(), 0);
  //                          ���� ����� (parm->DocHandle)
  //                          MT_MAPWINPORT - ���������� �����
  //                          ::SendMessage(Parm->DocHandle, MT_MAPWINPORT, MWP_SETVIEWSCALE,0)
  //                          AW_MOVEDOC - ����������� ����� � ����� geopoint
  //                          ::SendMessage(Parm->DocHandle, AW_MOVEDOC,(WPARAM)&geopoint, PP_GEOWGS84);
  //                          PP_GEOWGS84 -  // ���������� ����� � ������������� �����������
  //                                         // � �������� � ������� WGS-84
  //                          MT_SELECTOBJECT - ������ ����������� ����� ����������� � �������� �����
  //                          ::SendMessage(Parm->DocHandle, MT_SELECTOBJECT,0,0);
  // ������� ������ ���������� 0


_MAPIMP HMAP _MAPAPI mapPortalMenu(HMAP hmap, TASKPARMEX *parm, int left, int top);

  // �������� ��������� ���������� � ��������/��� ��������� ������ ����������� (����������� ������)
  // parm      - ������� ��������� ���������, ���� Handle ������ 
  //             ��������� ������������� ���� ����������. �������� ��������� - ��. maptype.h)
  // wmsstring - ������ ����������� � �������
  // size - ����� ������, ����������� ��� ���������� ������
  // flag - ������� ������������ �������� (����� ���������� � ��������� �������)
  // 0 - ������� ������, 1 - �������� ������, 2 - �������� ������
  // type - ��� ������ ��� ��������/���������/���������� 0 - WMS, 1 - WMTS
  // ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapEditWms(TASKPARMEX *parm, char* wmsstring, int size, int flag);
_MAPIMP long int _MAPAPI mapEditWmsUn(TASKPARMEX *parm, WCHAR* wmsstring, int size, int flag);

  // ��������� �������� ��� ������ �����������
  // wmsname - ������ ��� ����������
  // shortname- �������� ��� ����������
  // size - ������ ��������� ����� ����������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetShortWMSName(const char* wmsname, char* shortname, int size);
_MAPIMP  long int _MAPAPI mapGetShortWMSNameUn(const WCHAR* wmsname, WCHAR* shortname, int size);


  // ���������� ������ ������� ������ ��� ����������
  // version - ������ ����������
  // � ������ ������ ���������� 0

  _MAPIMP  long int _MAPAPI mapSetPortalVersion(HMAP hMap, int number, const char* version);
  _MAPIMP  long int _MAPAPI mapSetPortalVersionUn(HMAP hMap, int number, const WCHAR* version);

  // ��������� ������ ������� ������ ��� ����������
  // version - ������ ����������
  // � ������ ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetPortalVersion(HMAP hMap, int number, char* version);
_MAPIMP long int _MAPAPI mapGetPortalVersionUn(HMAP hMap, int number, WCHAR* version, int verssize);

  // ���������� ����� ������� ������ ��� ����������
  // time - ����� �������(TDateTime)
  // � ������ ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetGeoportalDateTime(HMAP hMap, int number, double time);

  // ��������� ����� ������� ������ ��� ����������
  // � ������ ������ ���������� 0, ����� ����� � ������� (TDateTime)

_MAPIMP  long int _MAPAPI mapGetGeoportalDateTime(HMAP hMap, int number, double* time);

  // ���������� ������ ��������� ������, ����/������� ������ ����������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapShowGeoportalDateTimeDialog(HMAP hMap, TASKPARMEX *parm);

  // �������� ��� ������ ��� ���� ����������� � �������� WMS/WMTS ��� �������� ���������
  
_MAPIMP  long int _MAPAPI mapClearWmsCache(HMAP hMap);

   // �������� ������� ����������� ����������� � �������
   // ��������� ����������� � ������� ���������� � 1
   // oldNumber - ����� ����� � �������
   // newNumber - ��������������� ����� ����� � �������
   // ��� ������ ���������� 0
  
_MAPIMP  long int _MAPAPI mapChangeOrderWmsShow(HMAP hMap, long int oldNumber, long int newNumber);

   // ��������� ����� ���������� � ������� �� ����� �����
   // name - ��� ����� ����������
   // � ������� ������ ����������� ���������� � 1.
   // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapGetWmsNumberByName(HMAP hMap, const WCHAR * name);

}

#endif  // WMSAPI_H
