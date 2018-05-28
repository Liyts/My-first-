/****** DBFAPI.CPP ************* Belenkov O.V.   ****** 28/01/15 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2015              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*             �������� ���������� ������� � ����� DBF              *
*                                                                  *
*******************************************************************/

#ifndef DBFAPI_H
#define DBFAPI_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

typedef HANDLE HDBFC;

extern "C"
{

// ������� ������� 
// table - ��� ������� (������ ���� � ����� DBF)
// mode  - ����� �������� 
//  0 : ������� �� ������/������, 
//      ���� �� ������ - ������ ������;
//  1 : ������ ������ (�������������!);
//  2 : ������ ������/������.
// ��� ������ ���������� ����, ����� - ������������� ��������
// ������� ���� ������. �������� ������� ����������� ������ ����
// ������� � ����� ������ ������� ������� dbCloseTable

_MAPIMP HDBFC _MAPAPI dbOpenTable(const char * table, long int mode);
_MAPIMP HDBFC _MAPAPI dbOpenTableUn(const WCHAR * table, long int mode = 1);

// ������� �������
// hdbf  - ������������� �������� �������

_MAPIMP void _MAPAPI dbCloseTable(HDBFC hdbf);

// C������ ������ � ���� integer �� ����� ����
// hdbf     - ������������� �������� �������
// name     - ��� ����
// value    - �������� ����
// ��� ������ ���������� ����

_MAPIMP long int _MAPAPI dbGetValueAsInt(HDBFC hdbf, const char * name, long int * value);
_MAPIMP long int _MAPAPI dbGetValueAsIntUn(HDBFC hdbf, const WCHAR * name, long int * value);

// C������ ������ � ���� double �� ����� ����
// hdbf     - ������������� �������� �������
// name     - ��� ����
// value    - �������� ����
// ��� ������ ���������� ����

_MAPIMP long int _MAPAPI dbGetValueAsDouble(HDBFC hdbf, const char * name, double * value);
_MAPIMP long int _MAPAPI dbGetValueAsDoubleUn(HDBFC hdbf, const WCHAR * name, double * value);

// ������� ������ � ���� ���������� ������ � ��������� ANSI �� ����� ���� 
// hdbf     - ������������� �������� �������
// name     - ��� ����
// value    - �������� ����
// size     - ����� ������
// ��� ������ ���������� ����

_MAPIMP long int _MAPAPI dbGetValueAsChar(HDBFC hdbf, const char * name, char * value, int size);

// ������� ������ � ���� ���������� ������ � ��������� UTF-16 �� ����� ���� 
// hdbf     - ������������� �������� �������
// name     - ��� ����
// value    - �������� ����
// size     - ����� ������
// ��� ������ ���������� ����

_MAPIMP long int _MAPAPI dbGetValueAsCharUn(HDBFC hdbf, const WCHAR * name, WCHAR * value, int size);

// �������� ���������� ����� � ������
// hdbf     - ������������� �������� �������
// ��� ������ ���������� ���� 

_MAPIMP long int _MAPAPI dbGetFieldCount(HDBFC hdbf);

// �������� ���������� �������
// hdbf     - ������������� �������� �������
// ��� ������ ���������� ���� 

_MAPIMP long int _MAPAPI dbGetRecordCount(HDBFC hdbf);

// ��������� �������� � ��� ����
// hdbf     - ������������� �������� �������
// number   - ����� ���� � ������� c 1
// name     - ��� ����
// size     - ����� ������
// ���������� ��� ����: 'N'- ��������, 'C'- ����������... (��. DBFFIELDTYPE)
// ��� ������ ���������� ���� 

_MAPIMP long int _MAPAPI dbGetNameAndTypeByNumber(HDBFC hdbf, int number, char * name, int size);
_MAPIMP long int _MAPAPI dbGetNameAndTypeByNumberUn(HDBFC hdbf, int number, WCHAR * name, int size);

// ��������� ����� ������ ����� ������� ��� ���� ���� DBFFIXED = 'N'
// hdbf     - ������������� �������� �������
// number   - ����� ���� � ������� c 1
// ��� ������ ���������� ���� 

_MAPIMP long int _MAPAPI dbGetPresicionByNumber(HDBFC hdbf, int number);

// ������� �� ������ ������ �������
// hdbf     - ������������� �������� �������
// ��� ������ ���������� ���� 

_MAPIMP long int _MAPAPI dbGotoFirst(HDBFC hdbf);

// ������� �� ��������� ������ �������
// hdbf     - ������������� �������� �������
// ��� ������ ���������� ���� 

_MAPIMP long int _MAPAPI dbGotoNext(HDBFC hdbf);

// ������ �������� � ������� ������ �� ����� ����
// hdbf    - ������������� �������� �������
// name    - ��� ����,
// value   - ��������
// ��� ������ ���������� ����

_MAPIMP long int _MAPAPI dbPutValue(HDBFC hdbf, const char* name, const char* value);
_MAPIMP long int _MAPAPI dbPutValueUn(HDBFC hdbf, const WCHAR* name, const WCHAR* value);

// ��������� ��� ��������� � ���� (����������� �������)
// hdbf     - ������������� �������� �������
// ��� ������ ���������� ����

_MAPIMP long int _MAPAPI dbReopenTable(HDBFC hdbf);

} // extern "C"

#endif // DBFAPI_H