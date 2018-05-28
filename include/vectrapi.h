/****  VECTRAPI.H    **********  Belenkov  O.V.  *****  25/10/16 ***
/****  VECTRAPI.H    **********  Konon V.N.      *****  17/01/11 ***
*****  VECTRAPI.H    **********  Shabakov D.A.   *****  07/08/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
* ����������� ������� ��� ����� 2011 ��� ���������� �� GIS ToolKit *
*                                                                  *
*                 ������ ������ �������:                           *
*                                                                  *
*   // �������� ����������                                         *
*   HINSTANCE libInst = ::LoadLibrary("gisvectr.dll");             *
*                                                                  *
*   // ����� �������                                               *
*   typedef long int (WINAPI * MAPSORTING)(HMAP hMap,              *
*                                          TASKPARM * parm)        *
*                                                                  *
*   MAPSORTING mapsorting = (MAPSORTING)                           *
*                   GetProcAddress(libInst, "MapSort");            *
*                                                                  *
*   long int rezult = (*mapsorting)(hMap, parm);                   *
*                                                                  *
*   // �������� ����������                                         *
*   ::FreeLibrary(libInst);                                        *
*                                                                  *
*******************************************************************/

#if !defined(VECTRAPI_H)
#define VECTRAPI_H


#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

extern "C"
{

  // ������� ������ ���������� ��������� ����
  // hmap - ������������� �������� ������;
  // parm - ��������� ������, �������� ��������� TASKPARM � maptype.h 
  //        (���� Handle ������ ��������� ������������� �������� ����).
  // ����� ����� ������� �� Mapvectr.chm ("MAPSORTS")
  // ��� ������ ���������� ����

_MAPIMP long int WINAPI MapSort(HMAP hmap,TASKPARM * parm);


  // ������� ������ ������� ��������� ���� �� ������� SXF ��� TXF
  // lpszsource - ����� ������ � ������ �������������� �����;
  // lpsztarget - ����� ������ (������ �������� �� ����� 256 ����) ���
  //              ���������� ����� ����������� �����, ������ ����� �����
  //              ��������� ��������;
  // parm       - ��������� ������, �������� ��������� TASKPARM � maptype.h 
  //              (���� Handle ������ ��������� ������������� �������� ����).
  // ����� ����� ������� �� Mapvectr.chm ("IMPORTSXF")
  // ��� ������ ���������� ����

_MAPIMP long int WINAPI LoadSxf2Map(char* lpszsource, char* lpsztarget, TASKPARM* parm);

  // ������� ������ ������� ��������� ���� �� ������� DIR (������ SXF ��� TXF)
  // lpszsource - ����� ������ � ������ �������������� ����� DIR;
  // lpsztarget - ����� ������ (������ �������� �� ����� 256 ����) ���
  //              ���������� ����� ����������� �����, ������ ����� �����
  //              ��������� ��������;
  // parm       - ��������� ������, �������� ��������� TASKPARM � maptype.h 
  //              (���� Handle ������ ��������� ������������� �������� ����).
  // ����� ����� ������� �� Mapvectr.chm ("IMPORTSXF")
  // ��� ������ ���������� ����

_MAPIMP long int WINAPI LoadDir2Map(const char* lpszsource, char* lpsztarget, TASKPARM* parm);

  // ������� ������ ������� ��������� ���� �� ������� DIR (������ SXF ��� TXF)   // 19/01/14
  // lpszsource - ����� ������ � ������ �������������� ����� DIR;
  // lpsztarget - ����� ������ (������ �������� size) ���
  //              ���������� ����� ����������� �����, ������ ����� �����
  //              ��������� ��������, ��� ����� ���� ��������
  //              ������������� � �������, ����� ��� ������������ ������
  //              ���������;
  // size       - ������ ������ � ������ ��� ������ ����� ����������� �����;
  // parm       - ��������� ������, �������� ��������� TASKPARM � maptype.h 
  //              (���� Handle ������ ��������� ������������� �������� ����).
  // ����� ����� ������� �� Mapvectr.chm ("IMPORTSXF")
  //  ��� ������ ���������� ����

_MAPIMP long int WINAPI vctLoadDir2MapUn(const WCHAR * lpszsource, WCHAR * lpsztarget, long int size, TASKPARM* parm);

  // ������� ������ ���������� ��������� ���� �� ������� SXF, TXF ��� DIR
  // (������ SXF ��� TXF)
  // lpszsource - ����� ������ � ������ �������������� �����, �������������
  //              ��� ���������� ��������� �����;
  // size - ����� ������ lpszsource ��� ������ ����� ����� SXF, ���� � ������� �������
  //        ������ ��� SXF;
  // hmap - ������������� �������� ������;
  // parm       - ��������� ������, �������� ��������� TASKPARM � maptype.h 
  //              (���� Handle ������ ��������� ������������� �������� ����).
  // ����� ����� ������� �� Mapvectr.chm ("UPDATESXF")
  // ��� ������ ���������� ����

_MAPIMP long int WINAPI UpdateMapFromSxfDialog(char* lpszsource, int size, HMAP hmap, TASKPARM* parm);

_MAPIMP long int WINAPI UpdateMap2Sxf(char* lpszsource, HMAP hmap, TASKPARM* parm);


  // ��������� ��������� ����� (�������) � ������ SXF
  // hmap       - ������������� �������� ������;
  // lpszsource - ��� ����� ����������� �����
  // lpsztarget - ��� ��������� �����
  // parm       - ��������� ������, �������� ��������� TASKPARM � maptype.h 
  //              (���� Handle ������ ��������� ������������� �������� ����).
  // ����� ����� ������� �� Mapvectr.chm ("EXPORTSXF")
  // ��� ������ ���������� ����

_MAPIMP long int WINAPI SaveMap2SxfEx(HMAP hmap, char* lpszsource, char* lpsztarget, TASKPARM* parm);

  // ��������� ��������� ����� (�������) � ������ TXF (��������� SXF)
  // hmap       - ������������� �������� ������;
  // lpszsource - ��� ����� ����������� �����
  // lpsztarget - ��� ��������� �����
  // parm       - ��������� ������, �������� ��������� TASKPARM � maptype.h
  //              (���� Handle ������ ��������� ������������� �������� ����).
  // ����� ����� ������� �� Mapvectr.chm ("EXPORTSXF")
  // ��� ������ ���������� ����

_MAPIMP long int WINAPI SaveMap2TxfEx(HMAP hmap, char* lpszsource, char* lpsztarget, TASKPARM* parm);


  // ��������� ���� ��� ��� ��������� ����� (�������) � ������ DIR (������ SXF ��� TXF)
  // hmap       - ������������� �������� ������;
  // lpszsource - ��� ����� ����������� �����
  // parm       - ��������� ������, �������� ��������� TASKPARM � maptype.h
  //              (���� Handle ������ ��������� ������������� �������� ����).
  // ����� ����� ������� �� Mapvectr.chm ("EXPORTSXF")
  // ��� ������ ���������� ����

_MAPIMP long int WINAPI SaveMap2Dir(HMAP hmap, char* lpszsource, TASKPARM* parm);

}       // extern "C"

#endif  // VECTRAPI_H


