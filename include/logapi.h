/****** LOGAPI.H *************** Vitsko      O.V. ***** 23/11/05 ***
******* LOGAPI.H *************** Belenkov    O.V. ***** 27/10/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*       �������� ������ ������� � ��'���� "������ ����������"      *
*        ��������� ��� �������� �� ������ C, PASCAL, BASIC         *
*                                                                  *
*******************************************************************/

#ifndef LOGAPI_H
#define LOGAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ �������� ������� ������� � ������� ���������� +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{

 // ��������� - ������� �� ������ ����������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // 0 - �� �������, ����� - �������
 
_MAPIMP long int _MAPAPI mapGetLogAccess(HMAP hMap, HSITE hSite);


 // ���������/��������� ������� ������� ���������� (0/1)
 // ����� �������� ����� ������� ������� ���������.
 // ����������� ������������ ������ ��� ��������� ���������
 // ��������, ����� �������������� ������ �����������
 // ��������� ������ ��� ���� ������� !
 // ����� ����������� ������� ������������� ������������ �
 // ��������� ����� ������ !
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� ����� 
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogAccess(HMAP hMap, HSITE hSite,long int mode);


 // ��������� ����� ���������� � �������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogCount(HMAP hMap, HSITE hSite);


 // ��������� ���� �������� �������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // date - ���� � ������� "YYYYMMDD"
 // time - ����� � ������� "����� ������ �� 00:00:00"
 // �� ��������� ����
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogDate(HMAP hMap, HSITE hSite,
                                    long int * date, long int * time);


 // ������� ������ ����������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // type - ��� ���������� (�� 0x4000 �� 0�0FFFF - �� ���������)
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogCreateAction(HMAP hMap, HSITE hSite,
                                            long int type);


 // ������ � �������� ���������� �������� �� ��������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ��������� ACTIONRECORD ������� � maptype.h
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogPutRecord(HMAP hMap, HSITE hSite,
                                         ACTIONRECORD * record);


 // ������� ������ ����������
 // hMap   - ������������� �������� �����
 // hSite  - ������������� �������� ���������������� �����
 // number - ���� ��� ������ ������ ����������� ���������� � ������� ����������
 // ���������� ����� ����������� �������� � ���������� ��� �����   // 23/12/14
 // ���� ����� ���������� �� ����� ���� ���������� ���������� -1   
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogCommitActionEx(HMAP hMap, HSITE hSite, long int * number);  // 27/10/16
_MAPIMP long int _MAPAPI mapLogCommitAction(HMAP hMap, HSITE hSite);


 // ��������� ����� ������ ����������,�����������
 // ����� ��������� ���� � �������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // date - ���� � ������� "YYYYMMDD"
 // time - ����� � ������� "����� ������ �� 00:00:00"
 // �� ��������� ���� (�� �������� - GetSystemTime, in Coordinated Universal Time (UTC))
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogGetActionNumberByTime(HMAP hMap, HSITE hSite,
                                                     long int date,
                                                     long int time);


 // ������� ��������� �������� ��������� �� ���������� ����������
 // ������ �� �������
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ��������� ACTIONRECORD ������� � maptype.h
 // ��� ������ ���������� ����,
 // ����� - ����� ����������

_MAPIMP long int _MAPAPI mapReadLastAction(HMAP hMap, HSITE hSite,
                                           ACTIONHEAD * head);


 // ������� ��������� �������� ��������� �� ���������� ����������
 // ������ �� �������
 // flag - ������� ������ ��������� ����������:
 // LOG_ANYACTION(0) - ��� �������, LOG_MYACTION(1) - ��������� ���������
 // ���� ���������� (���������� ���������� ������ �������������)
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ��������� ACTIONRECORD ������� � maptype.h
 // ��� ������ ���������� ����,
 // ����� - ����� ����������

_MAPIMP long int _MAPAPI mapReadLastActionEx(HMAP hMap, HSITE hSite,
                                             ACTIONHEAD * head, long int flag);

 // ������� ��������� �������� ��������� ���������� "��� �����" �
 // ��������� ����� ���������� ���������� (���������� ������� "������������")
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // head  - ����� ���� ��� ������ ��������� ���������� "��� �����"
 // ��������� ACTIONRECORD ������� � maptype.h
 // actionnumber - ����� ���� ��� ������ ������ ���������� ����������,
 // flag         - ������� ������ ��������� ���������� "��� �����":
 // LOG_ANYACTION(0) - ��� �������, LOG_MYACTION(1) - ��������� ���������
 // ���� ���������� (���������� ���������� ������ �������������)
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // ��� ������ ���������� ����, ����� - ����� ����������

_MAPIMP long int _MAPAPI mapReadLastUndoActionEx(HMAP hMap, HSITE hSite,
                                                 ACTIONHEAD * head, 
                                                 long int * actionnumber, 
                                                 long int flag);

 // ������� ��������� �������� ���������� �� �������
 // number - ���������������� ����� ����������
 // (�� 1 �� Count(...)).
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ��������� ACTIONRECORD ������� � maptype.h
 // ��� ������ ���������� ����,
 // ����� - ����� �������� � ����������
_MAPIMP long int _MAPAPI mapLogReadAction(HMAP hMap, HSITE hSite,
                                          long int number, ACTIONHEAD * head);

 // ��������� �������� �� ��������
 // number - ���������������� ����� ���������� (�� 1)
 // recnumber - ����� �������� (�� 1 �� ReadAction(...))
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ��������� ACTIONRECORD ������� � maptype.h
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogGetActionRecordEx(HMAP hMap, HSITE hSite,
                                                 long int number,
                                                 long int recnumber,
                                                 ACTIONRECORD * record);

_MAPIMP long int _MAPAPI mapLogGetActionRecord(HMAP hMap, HSITE hSite,
                                               long int recnumber,
                                               ACTIONRECORD * record);

 // ��������� ���������� �������� � ����������
 // hMap   - ������������� �������� �����
 // hSite  - ������������� �������� ���������������� �����
 // number - ����� ����������
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogGetActionRecordCountEx(HMAP hMap, HSITE hSite,
                                                      long int number);

_MAPIMP long int _MAPAPI mapLogGetActionRecordCount(HMAP hMap, HSITE hSite);

 // ��������� �������� �� ������ �� ������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogIsWrite(HMAP hMap, HSITE hSite);


 // �������� ��������� ����������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // ��� ������ ���������� ����,
 // ����� - ���������� ��������������� ��������

_MAPIMP long int _MAPAPI mapLogAbolitionLastAction(HMAP hMap, HSITE hSite);

 // ������������ ��������� ���������� ����������  // 05/07/10
 // flag - ������� ������ ��������� ����������:
 // LOG_ANYACTION(0) - ��� �������, LOG_MYACTION(1) - ��������� ���������
 // ���� ���������� (���������� ���������� ������ �������������)
 // ���� ����� ������ ���������� ����������� ������ �������� ���
 // ����������� ���������� ����� ��� ������ ���� - ���������� ����
 // ��� ������ ���������� ����,
 // ����� - ���������� ��������������� ��������

_MAPIMP long int _MAPAPI mapLogRedoLastAction(HMAP hMap, HSITE hSite,
                                              long int flag);

 // �������� ��������� ����������
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // flag - ������� ������ ��������� ����������:
 // LOG_ANYACTION(0) - ��� �������, LOG_MYACTION(1) - ������������ ���������
 // ���� ���������� (���������� ���������� ������ �������������)
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // ��� ������ ���������� ����,
 // ����� - ���������� ��������������� ��������

_MAPIMP long int _MAPAPI mapLogAbolitionLastActionEx(HMAP hMap, HSITE hSite,
                                                     long int flag);


 // �������� ��������� ���������� � ���������                 // 26/07/11
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // hMap  - ������������� �������� �����
 // hSite - ���� ��� ������ �������������� �����, �� ������� ���������
 //         ������ ����������
 // flag - ������� ������ ��������� ����������:
 // LOG_ANYACTION(0) - ��� �������, LOG_MYACTION(1) - ������������ ���������
 // ���� ���������� (���������� ���������� ������ �������������)
 // ��� ������ ���������� ����,
 // ����� - ���������� ��������������� ��������

_MAPIMP long int _MAPAPI mapLogUndoAction(HMAP hMap, HSITE * hSite, long int flag);


 // ��������� ��������� ���������� � ���������,������� ����� ��������    // 31/07/11
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // hMap  - ������������� �������� �����
 // hSite  - ���� ��� ������ �������������� �����, �� ������� ���������
 //          ������ ����������
 // flag - ������� ������ ��������� ����������:
 // LOG_ANYACTION(0) - ��� �������, LOG_MYACTION(1) - ������������ ���������
 // ���� ���������� (���������� ���������� ������ �������������)
 // ��� ������ ���������� ����, ����� - ����� ����������

_MAPIMP long int _MAPAPI mapLogReadActionForUndo(HMAP hMap, HSITE * hSite, long int flag);

 // ��������� ������ ���������� (� ����������� ����)
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����

_MAPIMP void _MAPAPI mapLogFlush(HMAP hMap, HSITE hSite);


 // ��������� ������������� �������� ����������
 // ������������ � ���� Task ��������� ACTIONHEAD
 // hMap  - ������������� �������� �����
 // hSite - ������������� �������� ���������������� �����
 // ��� ������ ���������� ����

_MAPIMP long int _MAPAPI mapLogGetMyIdent(HMAP hMap, HSITE hSite);

 // ��������� ��� �������� ���������� � ������������  
 // ������������ � ���� Task ��������� ACTIONHEAD
 // ��� ������ ���������� ����

_MAPIMP const char * _MAPAPI mapLogGetMyName(HMAP hMap, HSITE hSite);
_MAPIMP const WCHAR * _MAPAPI mapLogGetMyNameUn(HMAP hMap, HSITE hSite);

 // ���������� ����������� ������ �� ���� ����������� ��������� ������
 // �������� ��� �������� �������������� ���� �� ���� �����������
 // �������� ������ �� ���� ��� �������� access �� ������ 0
 // ��� ����������� ������� ������ ���������� �� ������
 // ������������� �����
 // ���� �����-���� ����� �� ����� ���� ������� � �����������
 // ������� - ������� ������������� ������������
 // ���������� ����� �������� �������� ������������ �������

_MAPIMP long int _MAPAPI mapSetExclusiveAccess(long int access);

 // ��������� �������� �������� ������������ ������� � ����������� ��������� ������

_MAPIMP long int _MAPAPI mapGetExclusiveAccess(void);

}  // extern "C"

#endif