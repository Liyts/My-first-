/****  SHPTOMAP.H *************  Belenkov O.V. *******  18/04/13 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2013              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                   FOR  WINDOWS2000 & WINDOWS XP                  *
*                                                                  *
********************************************************************
*                                                                  *
*                  ������ ���� �� ������� SHP                      *
*                       (GISSHPTOMAP.DLL)                          *
*                                                                  *
*******************************************************************/

#if !defined(SHPTOMAP_H)
#define SHPTOMAP_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

extern "C"
{

// ----------------------------------------------------------------------------
//   ������ �� ShapeFile ������ ������
//   handle  - ���� ����������� ������������� �������� ���������
//   mapname - ��� ����� (������ ����) ����������� �����
//             ���� ��� �� ������� - ������������ �� ����� ������� SHP � ������
//             ���� ����� � ��������� (��� ��������������) ������ �� ����������
//                 - ����� �������
//             ���� ����� ��� ���������� � clear = 1 - ����������� ����������
//             (��������������� �������� ������ ��������)
//   clear   - 0/1 �������������� ������� ������������ �����?
//   rscname - ��� ����� (������ ����) �������������� (����� = 0, ���� �����
//             ��� ����������), ������ ����, ���� ����� ��� ���
//   shiname - ��� ����� ��������(������ ����) 0 - ��� ������ ������,
//             �������������� ���������� "��������"
//   scale   - ����������� �������� ����������� ����� (����� = 0, ���� �����
//             ��� ����������)
//   shppath - ���� � ����� � ������� ������
//   charset - ������� ��������� ������� DBF (0 - ANSI,1 - UTF-8, 2-OEM,
//                                     -1 - ����������, ���. �������������)
//   sort    - ��������� �������� ���������� ����� (0,1)
//   clear   - ��������� ��������������� ������� ����� (0,1)
//   �������:  1 - ���������� ����������, 0 - �������� �� ���������, -1 - ��������� � ��������
//   ������, ���������� ����� �������� (��� �������� �����) ������� � LOG �����
// ----------------------------------------------------------------------------
long int WINAPI ShpLoadFolder(HMESSAGE handle, const char *mapname, const char *rscname,
                              const char *shiname, long int scale, const char *shppath,
                              long int charset, long int sort, long int clear = 0);


// ----------------------------------------------------------------------------
//   ������ �� ShapeFile ������ ������ � �������������� ���������� "onlyconfig"
//
//   handle  - ���� ����������� ������������� �������� ���������
//   mapname - ��� ����� (������ ����) ����������� �����
//             ���� ��� �� ������� - ������������ �� ����� ������� SHP � ������
//             ���� ����� � ��������� (��� ��������������) ������ �� ����������
//                 - ����� �������
//             ���� ����� ��� ���������� � clear = 1 - ����������� ����������
//             (��������������� �������� ������ ��������)
//   clear   - 0/1 �������������� ������� ������������ �����?
//   rscname - ��� ����� (������ ����) �������������� (����� = 0, ���� �����
//             ��� ����������), ������ ����, ���� ����� ��� ���
//   shiname - ��� ����� ��������(������ ����) 0 - ��� ������ ������,
//             �������������� ���������� "��������"
//   scale   - ����������� �������� ����������� ����� (����� = 0, ���� �����
//             ��� ����������)
//   shppath - ���� � ����� � ������� ������
//   charset - ������� ��������� ������� DBF (0 - ANSI,1 - UTF-8, 2-OEM,
//                                     -1 - ����������, ���. �������������)
//   sort    - ��������� �������� ���������� ����� (0,1)
//   clear   - ��������� ��������������� ������� ����� (0,1)
//   onlyconfig - ��������� ������ ����������� ���� (0,1)
//
//   �������:  1 - ���������� ����������, 0 - �������� �� ���������, -1 - ��������� � ��������
//   ������, ���������� ����� �������� (��� �������� �����) ������� � LOG �����
// ----------------------------------------------------------------------------
long int WINAPI ShpLoadFolderEx(HMESSAGE handle, const char *mapname,
                                const char *rscname, const char *shiname,
                                long int scale, const char *shppath,
                                long int charset,long int sort,long int clear,int onlyconfig);

// ----------------------------------------------------------------------------
//   ������ �� OSM ShapeFile ������ ������ �� ��������� ���������
//
//   handle  - ���� ����������� ������������� �������� ���������
//   mapname - ��� ����� (������ ����) ����������� �����
//             ���� ��� �� ������� - ������������ �� ����� ������� SHP � ������
//             ���� ����� � ��������� (��� ��������������) ������ �� ����������
//                 - ����� �������
//             ���� ����� ��� ���������� � clear = 1 - ����������� ����������
//             (��������������� �������� ������ ��������)
//   rscname - ��� ����� (������ ����) �������������� (����� = 0, ���� �����
//             ��� ����������), ������ ����, ���� ����� ��� ���
//   shiname - ��� ����� ��������(������ ����) 0 - ��� ������ ������,
//             �������������� ���������� "��������"
//   scale   - ����������� �������� ����������� ����� (����� = 0, ���� �����
//             ��� ����������)
//   shppath - ���� � ����� � ������� ������
//   charset - ������� ��������� ������� DBF (0 - ANSI,1 - UTF-8, 2-OEM,
//                                     -1 - ����������, ���. �������������)
//   sort    - ��������� �������� ���������� ����� (0,1)
//
//   �������:  1 - ���������� ����������, 0 - �������� �� ���������, -1 - ��������� � ��������
//   ������, ���������� ����� �������� (��� �������� �����) ������� � LOG �����
// ----------------------------------------------------------------------------
long int WINAPI OSMShpLoadFolderEx(HMESSAGE handle, const char *mapname, const char *rscname,
                                   const char *shiname, long int scale,
                                   const char *shppath, long int charset, long int sort);


}       // extern "C"

#endif  

