/****  Jpg2Rsw.H     **********  Shabakov D.A.   *****  31/08/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2014              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                   FOR  WINDOWS95 & WINDOWS NT                    *
*                                                                  *
********************************************************************
*                                                                  *
*            �������� ������� ��������� ������                     *
*        ��������� ��� �������� �� ������ C, PASCAL, BASIC         *
*                                                                  *
*******************************************************************/
#if !defined(JPEG2RSW_H)
#define JPEG2RSW_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

extern "C"
{

//========================================================================
// ����������� ������� "�������� ��������� ����� �� ����� ������� JPG"
//    � ������������ ������ ���� ������ �
//                   ��������� �������� ������ ��� ��������� �����.
//
//    nameJpg - ��������� �� ������ � �������� MAX_PATH,
//              ���������� ��� JPEG-�����;
//    nameRsw - ��������� �� ������ � �������� MAX_PATH,
//              ���������� ��� RSW-�����; ����� �������� ��������
//              �� ��������� nameRsw ���������� ��� ����� ��������� ��������� �����
//    compression - ���� ������������� ������ ��� ������������ ��������� ����� (0/1)
//
//    ��� ������ ���������� ����
//========================================================================
long int _export WINAPI LoadJpegToRsw(const char* nameJpg, char* nameRsw,
                                      TASKPARM * parm,
                                      long int flagCompress);

long int WINAPI __export LoadJpegToRswUn(const WCHAR* nameJpg,
                                      WCHAR* nameRsw, int sizenameRsw,
                                      TASKPARM * parm,
                                      long int flagCompress);

//========================================================================
// ����������� ������� "�������� ��������� ����� �� ����� ������� JPG"
//    � ������������ ������ ���� ������ �
//                   ��������� �������� ������ ��� ��������� �����.
//
//    hMapDoc - ������������� ���� ��������� (�������������� ��������)
//    hMap    - ������������� �������� ��������� �����
//    nameJpg - ��������� �� ������ � �������� MAX_PATH,
//              ���������� ��� JPEG-�����;
//    nameRsw - ��������� �� ������ � �������� MAX_PATH,
//              ���������� ��� RSW-�����; ����� �������� ��������
//              �� ��������� nameRsw ���������� ��� ����� ��������� ��������� �����
//    point   - ��������� �� ����� �������� ������ (� ������)
//              (��������� ���-��������� ���� ������ � ������)
//              (�������������� ��������)
//    compression - ���� ������������� ������ ��� ������������ ��������� ����� (0/1)
//
//    ��� ������ ���������� ����
//========================================================================
long int WINAPI __export LoadJpegToRswByPlace(HMAPDOC hMapDoc, HMAP hMap,
                                         const char* nameJpg,
                                         char* nameRsw,
                                         TASKPARM * parm,
                                         DOUBLEPOINT * point,
                                         long int flagCompress);

long int WINAPI __export LoadJpegToRswByPlaceUn(HMAPDOC hMapDoc, HMAP hMap,
                                         const WCHAR* nameJpg,
                                         WCHAR* nameRsw,
                                         int sizenameRsw,
                                         TASKPARM * parm,
                                         DOUBLEPOINT * point,
                                         long int flagCompress);


//========================================================================
// ������ "���������� ��������� ����� � ���� ������� JPG"
//
//    hMap    - ������������� �������� �����
//    nameRsw - ��������� �� ������ � �������� MAX_PATH_LONG,
//              ���������� ��� RSW-�����
//    nameJpg - ��������� �� ������ � �������� MAX_PATH_LONG,
//              ���������� ��� JPEG-�����;
//    parm    - ��������� �� ��������� TASKPARMEX
//
//    ��� ������ ���������� ����
//========================================================================
  long int WINAPI __export SaveRswToJpeg(HMAP hMap, const char* nameRsw,
                                         const char* nameJpg,
                                         TASKPARM * parm);

  long int WINAPI __export SaveRswToJpegUn(HMAP hMap, const WCHAR* nameRsw,
                                         WCHAR* nameJpg, int sizenameJpg,
                                         TASKPARM * parm);

//========================================================================
// ������ "��������� ������������ ������ ����������� �� ������ JPEG"
// value   - ��������� �� ������������ ������
// parm    - ��������� �� ��������� TASKPARMEX
//========================================================================
long int WINAPI __export SetJpegCompress(long int* value, TASKPARMEX * parm);

}       // extern "C"


#endif  // JPEG2RSW_H



