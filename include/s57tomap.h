/****  S57TOMAP.H *************  Belenkov O.V. *******  06/09/16 ***
*****  S57TOMAP.H ************* Gheleznykov A.V. ****** 20/10/05 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                         FOR MS WINDOWS                           *
*                                                                  *
********************************************************************
*                                                                  *
*            ������ ���� �� ������� S57 �������� 3                 *
*                 (giss57.dll, gisu64s57.dll)                      *
*                                                                  *
*******************************************************************/

#if !defined(S57TOMAP_H)
#define S57TOMAP_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

extern "C"
{

// ��������� ����� �� ������� S57 
// source - ���� � ����� ������� S57 (*.000 ��� *.CAT)
// target - ���� � ������������ ����� (MAP ��� SIT) (������ 260 ��������),
//          ����� ���� �������� � ������� �������� 
// parm   - ��������������� ���������
// ��� ������ ��������� ��������� ������������� s57navy.rsc
// ��� ����������� ���� ����� ���������� ����������� ������ s57navy.iml

__declspec(dllimport)long int WINAPI LoadS57ToMap(const char * source,
                                                  char       * target,
                                                  TASKPARM   * parm);


// ��������� ����� �� ������� S57 � ��������� �������������� �����
// source - ���� � ����� ������� S57 (*.000 ��� *.CAT)
// target - ���� � ������������ ����� (MAP ��� SIT) (������ 260 ��������),
//          ����� ���� �������� � ������� �������� 
// rscname - ���� � ������������� �������������� �����,
//          ����� ���� �������� � ������� �������� 
// parm   - ��������������� ���������
// ��� ������ ��������� ��������� ������������� s57navy.rsc
// ��� ����������� ���� ����� ���������� ����������� ������ s57navy.iml

__declspec(dllimport)long int WINAPI LoadS57ToMapForRsc(const char * source,
                                                        char       * target,
                                                        char       * rscname,
                                                        TASKPARM   * parm);

// ������ �� S57 � ������ MAP ��� ������ �������
// handle  - ������������� ������������� ���� ��� ��������� ��������� � ���� �������� ��� 0
// names57 - ������ ��� ����� ������� S57
// namemap - ������ ��� ����������� �����
// namersc - ������ ��� ����� �������������� (������ S57NAVY.RSC)
// nameregion - �������� �������� ����������� ����� ("���� ��������" � �.�.)
// safelystate - ���� �������� ������ ��� ������������ (���������� ������� ����������� ������� ������)
// ��� ������ � ���������� ���������� ����

__declspec(dllimport) long int WINAPI LoadS57_2_Map(HMESSAGE handle,const char* names57,
                                                    const char* namemap,const char* namersc,
                                                    const char* nameregion,long safelystate)


}       // extern "C"

#endif  


