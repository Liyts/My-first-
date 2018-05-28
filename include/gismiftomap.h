/****** GISMIFTOMAP.H *********** Shabakov D.A.   ****** 21/11/16 **
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*  � ��������� ����� ���������� ���������� ��������� ��������:     *
*                                                                  *
                                                                  *
*                                                                  *
*                                                                  *
********************************************************************
*                                                                  *
*                 �������������� ������� :                         *
*                                                                  *
*                                                                  *
*    #include "maplib.h"                                           *
*                                                                  *
*    // �������� ����������                                        *
*    HINSTANCE libInst = ::LoadLibrary(MIFMIDLIB);                 *
*                                                                  *
*    // ���������� ��������                                        *
*                                                                  *
*    // ����� �������                                              *
*                                                                  *
*    long int (WINAPI * lpfn_ImportFromMifEx)(HMAP         hmap,   *
*                                        const char * namemif,     *
*                                        const char * namersc,     *
*                                        char       * namemap,     *
*                                        char       * buildname,   *
*                                        int        * numsem,      *
*                                        HMESSAGE     handle,      *
*                                        long int     flag,        *
*                                        long int     size);       *
*                                                                  *
*    (FARPROC)lpfn_ImportFromMifEx =                               *
*              GetProcAddress(libInst, "ImportFromMifEx");         *
*                                                                  *
*    (*lpfn_RswFilterDialog)(hmap,                                 *
*                            "file.mif",                           *
*                            "classifier.rsc",                     *
*                            "filemap.sit",                        *
*                            "param.ini",                          *
*                            0, 0, 0, 0);                          *
*                                                                  *
*    // �������� ����������                                        *
*                                                                  *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/
#ifndef GISMIFTOMAP_H
#define GISMIFTOMAP_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ �������� ������� ����������� ���������� ���� ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
// ------------------------------------------------------------------
// ������ �������� ����� �� ������� MIF/MID
// hmap      - ������������� �������� �����
// namemif   - ��� ������������ ����� ���� MIF
// namersc   - ��� ����� ��������������, � ������� ����������� �����
// namemap   - ��� ����������� �����
// buildname - ��� ����� ��������
// handle    - ������������� ���� �������, �������� ���������� ��������������
//             ���������
// flag      - ������� �������� ����� (0) ��� ���������� (1);
// size      - ����� ������, �� ������� ��������� ���������� namemap ��� 0. ������ �����
//             ����� MAX_PATH
// ����������:
// 1 - ���������� ������ �������
// 0 - ��� ������
// 2 - ��� ���������� ���� ������������������ ���� (CODEOBJECT)� ����������� �����
// 3 - ��� ��������� ������� ��������� ������� �������� (�� WGS84)
// 4 - ��� ���������� ���� CODEOBJECT � ��������� ������� ��������� �������
// ------------------------------------------------------------------
long int WINAPI _export ImportFromMifEx(HMAP         hmap,
                                        const char * namemif,
                                        const char * namersc,
                                        char       * namemap,
                                        char       * buildname,
                                        int        * numsem,
                                        HMESSAGE     handle,
                                        long int     flag,
                                        long int     size);


// ------------------------------------------------------------------
// ������ �������� ����� �� ������� MIF/MID
// hmap      - ������������� �������� �����
// mifname   - ��� �������� ������������ ����� ���� MIF
// rscname   - ��� ����� ��������������, � ������� ����������� �����
// mapname   - ��� ����������� �����
// size      - ����� ������, �� ������� ��������� ���������� namemap ��� 0. ������ �����
//             ����� MAX_PATH
// buildname - ��� �������� ����� ��������
// codename  - ��� � ����� ��������� ����, ������� �������� ��� �������
// sizename  - ����� ������, �� ������� ��������� ���������� codename
// handle    - ������������� ���� �������, �������� ���������� ��������������
//             ���������
// flag      - ������� �������� ����� (0) ��� ���������� (1);

// ����������:
// 1 - ���������� ������ �������
// 0 - ��� ������
// 2 - ��� ���������� ���� ������������������ ���� (CODEOBJECT)� ����������� �����
// 3 - ��� ��������� ������� ��������� ������� �������� (�� WGS84)
// 4 - ��� ���������� ���� CODEOBJECT � ��������� ������� ��������� �������
// ------------------------------------------------------------------
long int WINAPI _export ImportFromMifName(HMAP         hmap,
                                          const char * mifname,
                                          const char * rscname,
                                          char       * mapname,
                                          long int     size,
                                          char       * buildname,
                                          long int   * numsem,
                                          char       * codename,
                                          long int     sizename,
                                          HMESSAGE     handle,
                                          long int     flag,
                                          long int code);

}

#endif


