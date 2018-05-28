/****** PASPAPI.H ************** �������� �.�. ******** 29/09/16 ***
******* PASPAPI.H ************** Shishkova L.A. ******* 02/12/13 ***
******* PASPAPI.H ************** Tarakanova I.R. ****** 28/09/16 ***
******* PASPAPI.H ************** Konon V.N.      ****** 10/03/11 ***
******* PASPAPI.H ************** Kruzhkov A.E.   ****** 18/04/16 ***
******* PASPAPI.H ************** Shabakov D.A.   ****** 29/07/16 ***
******* PASPAPI.H ************** Derevyagina Zh.A.***** 06/10/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                           FOR WINDOWS                            *
*                                                                  *
********************************************************************
*                                                                  *
*            �������� ������� ������ � ��������� �����             *
*                                                                  *
* ����������� ������� ��� ����� 2011 ��� ���������� �� GIS ToolKit *
*                                                                  *
*                 ������ ������ �������:                           *
*                                                                  *
*   // �������� ����������                                         *
*   HINSTANCE libInst = ::LoadLibrary("gispasp.dll");              *
*                                                                  *
*   // ����� �������                                               *
*   typedef long int (WINAPI * CREATEPLAN)(char * mapname,         *
*                                          int size,               *
*                                          TASKPARMEX* parm);      *
*                                                                  *
*   CREATEPLAN pcreateplan = (CREATEPLAN)                          *
*                   GetProcAddress(libInst, "paspCreatePlan");     *
*                                                                  *
*   long int rezult = (*pcreateplan)(mapname, size, parm);         *
*                                                                  *
*   // �������� ����������                                         *
*   ::FreeLibrary(libInst);                                        *
*                                                                  *
*******************************************************************/

#if !defined(PASPAPI_H)
#define PASPAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifdef LINUXAPI                            // 08/10/15
  #define _PASPAPI
  #define _PASPIMP
#else
  #define _PASPAPI  WINAPI
  #if defined(PASP_DLL)
    #define _PASPIMP __declspec(dllexport)
  #else
    #ifdef VECTOR_DLL     // 06/10/16
      #define _PASPIMP
    #else
      #define _PASPIMP __declspec(dllimport)
  #endif
#endif
#endif

typedef struct REFERENCESYSTEM
{
  char NameSystem[512];
  char Comment[512];
  char Ident[64];
  long int CodeEpsg;
}
REFERENCESYSTEM;

typedef struct REFERENCESYSTEMUN               // 01/04/14
{
  WCHAR NameSystem[512];
  WCHAR Comment[512];
  WCHAR Ident[64];
  int CodeEpsg;
  int Reserve;
}
REFERENCESYSTEMUN;


// �������� �� �����������-������������� ������ ������
typedef struct ORGANIZATION
{
  char Name[256];                // �������� �����������
  char Phone[32];                // �������
  char Facsimile[32];            // ����
  char City[32];                 // ���������� �����
  char Adminarea[32];            // ���������������� �����
  char Postalcode[32];           // �������� ������
  char Country[32];              // ������
  char Email[64];                // ����������� �����
  char Reserve[256];
}
ORGANIZATION;


// �������� � ����������, ������� �������� �������� ������ ������ � ���� ����������
typedef struct AGENT
{
  char Fio[256];                 // �������  ���  ��������
  char NameOrg[256];             // �������� ����������� 
  char Phone[32];                // �������
  char Facsimile[32];            // ����
  char Email[64];                // ����������� �����
}
AGENT;

// �������� � ����������, ������� �������� �������� ������ ������ � ���� ����������
typedef struct AGENTEX           // 31/07/15
{
  WCHAR Fio[256];                 // �������  ���  ��������
  WCHAR NameOrg[256];             // �������� �����������
  WCHAR Position[256];            // ���������
  WCHAR Phone[32];                // �������
  WCHAR Facsimile[32];            // ����
  WCHAR Email[64];                // ����������� �����
  WCHAR Reserve[256];
}
AGENTEX;

// �������� �� �����������-������������� ������ ������
typedef struct ORGANIZATIONEX
{
  WCHAR Name[256];                // �������� �����������
  WCHAR Phone[32];                // �������
  WCHAR Facsimile[32];            // ����
  WCHAR City[32];                 // ���������� �����
  WCHAR Adminarea[32];            // ���������������� �����
  WCHAR Postalcode[32];           // �������� ������
  WCHAR Country[32];              // ������
  WCHAR Email[64];                // ����������� �����
  WCHAR Reserve[256];
}
ORGANIZATIONEX;

// ���������� ������ � �������
typedef struct RMF_METADATA
{
  double  Totalsize;              // ����� ������ ������ � K������ (��������� �������� mapGetDataSize(...))
  WCHAR   Ident[64];              // ������������� ������ � ������� GUID
  WCHAR   WestLongitude[32];      // ������� ���-��������� ���� ��������� � �������� WGS-84
  WCHAR   EastLongitude[32];      // ������ ���-��������� ���� ��������� � �������� WGS-84
  WCHAR   SouthLatitude[32];      // ������� ������-���������� ���� ��������� � �������� WGS-84
  WCHAR   NorthLatitude[32];      // ������ ������-���������� ���� ��������� � �������� WGS-84

  WCHAR   Scale[32];              // ����� ������ � ����� ������� (������)
                                  // ����� ������ � ����� �������� �������
  WCHAR   Nomenclature[256];      // �������� �������� �������
  WCHAR   Createdate[32];         // ���� ��������/���������� ������ (�������) - YYYY-MM-DD
  WCHAR   Format[16];             // ������������� ������� ������ (MTW, RSW ...)
  WCHAR   Filename[1024];         // ������ �� �������� ���� ������   (noginsk.mtw)
  WCHAR   Comment[256];           // �����������, ������� ��������
  WCHAR   Lineage[512];           // ����� �������� �� �������� ������, �� ������� ������� ����� ��� ����, � � ���������� �� ���������
  WCHAR   Areadate[16];           // ��� ��������� ���������

  WCHAR   Security[128];           // ���� ����������� (����������)
  WCHAR   Datatype[128];           // ��� ������ - ����������� ���������� ������, ��������������, ������������������ ������ (101-106)
                                   // ��� ������ - ���������� ������� �����, TIN-������, MTD-������ (������ �����) (201-203)
  // ��� ������ ���

  WCHAR   SatName[64];            // �������� ��� �������� ����������� ��������
  WCHAR   CloudState[32];         // ������� ������, �������� �����������
  WCHAR   SunAngle[32];           // ������ ������ (�������)
  WCHAR   ScanAngle[32];          // ���� ������ (�������)

  int     Epsgcode;               // ��� EPSG ������� ��������� �����
  WCHAR   Reserve[252];
}
  RMF_METADATA;

extern "C"
{ 
// --------------------------------------------------------------
// ������ �������� �����
// hmap     - ������������� �������� �����
// mapname  - ��������� �� ������, ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������!
// size     - ����� ������, ���������� ��� ����� (�� ������ 260)
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� CREATE_MAP
// ��� ������ ���������� ����
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspCreateMap(HMAP hmap, char *mapname, long int size,
                                         TASKPARMEX * parm);

_PASPIMP long int _PASPAPI paspCreateMapUn(HMAP hmap,WCHAR *mapname, long int size,
                                           TASKPARMEX * parm);

// --------------------------------------------------------------
// ������ �������� �����
// hmap     - ������������� �������� �����
// mapname  - ��������� �� ������, ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// size     - ����� ������, ���������� ��� �����
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// password - ������ ������� � ������ �� �������� ����������� 256-������ ���
//            ��� ���������� ������ (��� ������ ������ �� �����������������)
// sizepassw - ����� ������ � ������ !!!
// Help ���������� �� mappasp.chm, ����� CREATE_MAP
// ��� ������ ���������� ����
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspCreateMapPro(HMAP hmap, WCHAR *mapname, long int size,
                                            TASKPARMEX * parm,
                                            WCHAR * password, long int sizepassw);

// --------------------------------------------------------------
// ������ �������� ����������������� �����
// mapname  - ��������� �� ������, ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// size     - ����� ������, ���������� ��� �����
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� CREATE_PLAN
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspCreatePlan(char* mapname,long int size,
                                       TASKPARMEX* parm);

// 18/03/13
_PASPIMP long int _PASPAPI paspCreatePlanUn(WCHAR* mapname,long int size,
                                         TASKPARMEX* parm);

// --------------------------------------------------------------
// ������ �������� ���������������� ����� �� �������� �����
// hmap     - ������������� �������� �����
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� CREATE_SITE
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspCreateSite(HMAP hmap, TASKPARMEX * parm);

// --------------------------------------------------------------
// ������ ��������� � �������������� ��������
// hmap     - ������������� �������� �����
// hsite    - ���������������� �����
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� PASP_EDID
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspViewPasp(HMAP hmap, HSITE hsite,
                                     TASKPARMEX * parm);

// --------------------------------------------------------------
// ������ ��� ��������� ���������� ������� ������� ���������
// ������������� ��������� ��� ��� ��������� (HMAP),
// ������� ����� ����� �������������� ��� ���������� ���������
// � �������� mapPlaneToWorkSystemPlane, mapWorkSystemPlaneToGeo � �.�.
// hmap       - ������������� �������� ����� (���������),
// taskparmex - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� MCK_PARAM
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspSetWorkSystemParameters(HMAP hmap,
                                                    TASKPARMEX* taskparmex);


// --------------------------------------------------------------
// ����������� � ��������� ������� ���������� �������� ���������
// ��� �����������, ������ � ������� ���������
// ������������� ����� ��������� �������� ����� ��� ���������
// ��������������� �������� ������������� ��������� (mapIsGeoSupported() != 0)
// ����� ��������� ����� ���������� �������� ����������� ����� �����������
// � �������� ��������. ��������� �����, ������� ������ ���������
// ��������, ���������������� � �������� �����������.
// ��� �������� � ������������ (mapPlaneToGeo, mapGeoToPlane,
// mapPlaneToGeoWGS84, mapAppendPointPlane, mapInsertPointPlane,
// mapUpdatePointPlane, mapAppendPointGeo � ������) �����������
// � ������� ��������� ���������, ������������ ������ ����������� ��������
// ��� ������\������ ��������� � ���������� ����� ����������� ��������
// �� ������� ��������� ���������
// hmap       - ������������� �������� ����� (���������),
// taskparmex - ��������� ���������� ��� ������� (��. maptype.h)
// ����� ��������� ��������������� �������� mapSetDocProjection(...)(��. mapapi.h)
// Help ���������� �� mappasp.chm, ����� DOCPROJECTION
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspSetCurrentProjectionParameters(HMAP hmap,
                                                           TASKPARMEX* taskparm);


// --------------------------------------------------------------
// ����������/���������� ��������� ��������
// hmap - ������������� �������� ������ (��� 0)
// ��������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// ������� � mapcreat.h
// ��������� TASKPARMEX ������� � maptype.h
// const char* title - ��������� �������
// �������� �������� ���������� �������� ������ �
// MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// iswrite           - ���� ������������ �������������� ���������� ��������
//                     (0 - �� ������������� / 1 - �������������)
// �����: ������������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// ��� ��������� �������� ���������� ���������� 1
// ��� ���������� ��������� � ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspSetProjectionParameters(HMAP hmap,           // 02/12/13
                                                    MAPREGISTEREX* mapregisterex,
                                                    DATUMPARAM*    datum,
                                                    ELLIPSOIDPARAM* spheroidparam,
                                                    TASKPARMEX* parm,
                                                    const char* title,
                                                    long int iswrite);


// --------------------------------------------------------------
// ����������/���������� ��������� ��������
// hmap - ������������� �������� ������ (��� 0)
// ��������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// ������� � mapcreat.h
// ��������� TASKPARMEX ������� � maptype.h
// title             - ��������� ������� � ��������� UNICODE
// �������� �������� ���������� �������� ������ �
// MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// ttype   -  ��� �������������� ��������� (��. TRANSFORMTYPE � mapcreat.h) ��� 0
// ��������� LOCALTRANSFORM  ������� � mapcreat.h
// iswrite           - ���� ������������ �������������� ���������� ��������
//                     (0 - �� ������������� / 1 - �������������)       // 16/05/11
// �����: ������������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// ��� ��������� �������� ���������� ���������� 1
// ��� ���������� ��������� � ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspSetProjectionParametersPro(HMAP hmap,         // 28/09/16
                                                      MAPREGISTEREX* mapregisterex,
                                                      DATUMPARAM*    datum,
                                                      ELLIPSOIDPARAM* spheroidparam,
                                                      long int * ttype,
                                                      LOCALTRANSFORM * tparm,
                                                      TASKPARMEX* parm,const WCHAR * title,
                                                      long int iswrite);

_PASPIMP long int _PASPAPI paspSetProjectionParametersUn(HMAP hmap,         // 02/12/13
                                                      MAPREGISTEREX* mapregisterex,
                                                      DATUMPARAM*    datum,
                                                      ELLIPSOIDPARAM* spheroidparam,
                                                      TASKPARMEX* parm,const WCHAR * title,
                                                      long int iswrite);

// --------------------------------------------------------------
// ������ XML-�����
// hmap - ������������� �������� ������ (��� �������� ����� - hmap = 0)
// ��������� REFERENCESYSTEMUN ������� � paspapi.h
// ��������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM  ������� � mapcreat.h
// ttype   -  ��� �������������� ��������� (��. TRANSFORMTYPE � mapcreat.h) ��� 0
// ��������� LOCALTRANSFORM  ������� � mapcreat.h
// ��������� TASKPARMEX ������� � maptype.h
// regime  -  ������ ������ � ��������� (��������, ��������������)
// Help ���������� �� mappasp.chm, ����� PARAMETERSXML
// ��� ������ ���������� ����
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspReadFileXMLPro(HMAP hmap,                     // 21/09/16
                                       REFERENCESYSTEMUN * referencesystem,
                                       MAPREGISTEREX* mapregisterex,
                                       DATUMPARAM*    datum,
                                       ELLIPSOIDPARAM* ellipsoidparam,
                                       long int * ttype,
                                       LOCALTRANSFORM * tparm,
                                       TASKPARMEX* parm, long int regime);


_PASPIMP long int _PASPAPI paspReadFileXML(HMAP hmap,
                                        MAPREGISTEREX* mapregisterex,
                                        DATUMPARAM*    datum,
                                        ELLIPSOIDPARAM* spheroidparam,
                                        TASKPARMEX* parm, long int regime);

_PASPIMP long int _PASPAPI paspReadFileXMLEx(HMAP hmap,
                                        REFERENCESYSTEM * referencesystem,
                                        MAPREGISTEREX* mapregisterex,
                                        DATUMPARAM*    datum,
                                        ELLIPSOIDPARAM* spheroidparam,
                                        TASKPARMEX* parm, long int regime);

_PASPIMP long int _PASPAPI paspReadFileXMLUn(HMAP hmap,
                                        REFERENCESYSTEMUN * referencesystem,
                                        MAPREGISTEREX* mapregisterex,
                                        DATUMPARAM*    datum,
                                        ELLIPSOIDPARAM* spheroidparam,
                                        TASKPARMEX* parm, long int regime);


// --------------------------------------------------------------
// ������ ���������� �� ���� ������ EPSG                         // 28/03/11
// hmap - ������������� �������� ������ (��� �������� ����� - hmap = 0)
// ��������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// ������� � mapcreat.h
// ��������� TASKPARMEX ������� � maptype.h
// � epsgcode ������������ ��� EPSG
// ����� ���� ������ EPSG.CSG, EPSG.CSP, EPSG.CSU ������ ���������� 
// � �������� ���������� 
// ��� ������ ���������� ����
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspReadEPSG(HMAP hmap,
                                     MAPREGISTEREX* mapregisterex,
                                     DATUMPARAM*    datum,
                                     ELLIPSOIDPARAM* ellipsoidparam,
                                     TASKPARMEX* parm,
                                     long int *epsgcode);

// --------------------------------------------------------------
// ������ ���������� �� ���� ������ EPSG                         // 26/12/12
// hmap - ������������� �������� ������ (��� �������� ����� - hmap = 0)
// ��������� MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// ������� � mapcreat.h
// ��������� TASKPARMEX ������� � maptype.h
// � epsgcode ������������ ��� EPSG
// ����� ���� ������ EPSG.CSG, EPSG.CSP, EPSG.CSU ������ ����������
// � �������� ����������
// namesystem - ������ ������ �� ����� 64 �������� ��� ����������
// �������� ������� ��������� (��������������)
// size  - ����� ������
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspReadEPSGEx(HMAP hmap,
                                       MAPREGISTEREX* mapregisterex,
                                       DATUMPARAM*    datum,
                                       ELLIPSOIDPARAM* ellipsoidparam,
                                       TASKPARMEX* parm,
                                       long int *epsgcode,
                                       char * namesystem,
                                       long int size);

// 18/03/13
_PASPIMP long int _PASPAPI paspReadEPSGExUn(HMAP hmap,
                                         MAPREGISTEREX* mapregisterex,
                                         DATUMPARAM*    datum,
                                         ELLIPSOIDPARAM* ellipsoidparam,
                                         TASKPARMEX* parm,
                                         long int *epsgcode,
                                         WCHAR * namesystem,
                                         long int size);


// --------------------------------------------------------------
// �������� � �������������� ����� ���������� � ������� XML              // 15/11/12
// filename - ��� ����� ���������� (0, ���� ����������� ��� ���� ������ � ���� ����)
// hmap - ������������� �������� ������
// ��������� TASKPARMEX ������� � maptype.h
// regime - ������ ������ � ������ ���������� (0 - ��������,1- ��������������)
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspWriteXMLMD(char *filename,HMAP hmap,
                                          TASKPARMEX* parm, long int regime);

_PASPIMP long int _PASPAPI paspWriteXMLMDUn(WCHAR *filename,HMAP hmap,
                                            TASKPARMEX* parm, long int regime);
// --------------------------------------------------------------
// �������� � �������������� ����� ����������
// filename - ��� ����� ����������
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspEditXMLMD(char *filename,TASKPARMEX * parm);

_PASPIMP long int _PASPAPI paspEditXMLMDUn(WCHAR *filename,TASKPARMEX * parm);


// 15/01/13
// --------------------------------------------------------------
// �������� xml ����� ���������� ��� ������ ����� (��� ������ �������)
// filename - ��� ����� ����������
// ��������� MAPREGISTEREX, LISTREGISTER  ������� � mapcreat.h
// ��������� ORGAHIZATION, AGENT  ������� � paspapi.h
// rscname - ��� ����� �������������� (��� ����)
// comment - �����������, �������� ������� �������� ������ ������ (�� 256 ��������)
// lineage - ����� �������� �� �������� ������ � ���������� �� ��������� (�� 512 ��������)
// security - ���� �����������:  1 - �������� ����������
//                               2 - ���������� � ������������ ��������
//                               3 - ���������� ��� ���������� �����������
//                               4 - ��������� ����������
//                               5 - ���������� ��������� ����������
// codeepsg - ��� EPSG
// ������������ ��� ���������� ���������: filename, mapreg, listreg
// ��� ������ ���������� ����
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspSaveMetaData(char *filename,
                                         MAPREGISTEREX * mapreg,
                                         LISTREGISTER * listreg,
                                         ORGANIZATION * organization,
                                         AGENT * agent,
                                         char * rscname,
                                         char * comment,
                                         char * lineage,
                                         long int security,
                                         long int codeepsg);

// 18/03/13                                         
_PASPIMP long int _PASPAPI paspSaveMetaDataUn(WCHAR *filename,
                                           MAPREGISTEREX * mapreg,
                                           LISTREGISTER * listreg,
                                           ORGANIZATION * organization,
                                           AGENT * agent,
                                           WCHAR * rscname,
                                           WCHAR * comment,
                                           WCHAR * lineage,
                                           long int security,
                                           long int codeepsg);

// 31/07/15
// --------------------------------------------------------------
// �������� � �������������� ����� ���������� ������ � ������� � ������� XML
// filename - ��� ����� ���������� (��� 0)
// hmap - ������������� �������� ������
// ��������� TASKPARMEX ������� � maptype.h
// datatype ��� ����� (������, �������)
// (��. maptype.h : FILE_RSW, FILE_MTW)
// ��� ������ ���������� ����
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspMetaDataMtwRsw(WCHAR *filename,
                                           HMAP hmap,
                                           TASKPARMEX * parm,
                                           long int datatype,
                                           long int chainnumber);

// 07/10/15
// --------------------------------------------------------------
// �������� ����� ���������� ������ � ������� � ������� XML
// filename - ��� ����� ����������
// ��������� RMF_METADATA, ORGANIZATIONEX, AGENTEX ������� � paspapi.h
// datatype ��� ����� (������, �������)
// (��. maptype.h : FILE_RSW, FILE_MTW)
// ��� ������ ���������� ����
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspSaveMetaDataRmf(WCHAR *filename,
                                            RMF_METADATA * metadata,
                                            ORGANIZATIONEX * organization,
                                            AGENTEX * agent,
                                            long int datatype);

// --------------------------------------------------------------
// ��������� ���������� ��� ������ � �������
// filename - ��� ����� ����������
// ��������� RMF_METADATA, ORGANIZATIONEX, AGENTEX ������� � paspapi.h
// ��������� ORGANIZATIONEX, AGENTEX  ������������� ��� ����������
// datatype ��� ����� (������, �������)
// (��. maptype.h : FILE_RSW, FILE_MTW)
// ��� ������ ���������� ����
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspGetMetaDataRmf(WCHAR *filename,
                                           HMAP hmap,
                                           TASKPARMEX * parm,
                                           RMF_METADATA * metadata,
                                           ORGANIZATIONEX * organization,
                                           AGENTEX * agent,
                                           long int datatype); 

                                           
// ================================================================
//
//                      ���������� �������                         // 01/06/10
//
//              ����������� ����� ����� ����� �������
// ================================================================


// --------------------------------------------------------------
// �������������� ��������
// hmap     - ������������� �������� �����,
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� PASP_EDID
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspEdit(HMAP hmap, char *mapname, TASKPARM * parm);

// --------------------------------------------------------------
// �������� �������� �����
// hmap     - ������������� �������� �����,
// taskparm - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� PASP_EDID
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI mapPaspShow(HMAP hmap,TASKPARMEX* taskparm);    // 13/01/10

// --------------------------------------------------------------
// �������� �����
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� CREATE_PLAN
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspPlan(char *mapname, TASKPARM * parm);


// --------------------------------------------------------------
// �������� ���������� � ���������� ���������������� �����
// � �������� � �������� ����� �����
// hmap     - ������������� �������� �����,
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// path     - ���������� � ������� ����� ���������� ������� ����
//            (������������ ����� ������� ������)
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� CREATE_MAP
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspSitDoc(HMAP hmap, char *mapname, char * path,
                                     TASKPARM * parm);

// --------------------------------------------------------------
// �������� ���������� � ���������� ���������������� �����
// � �������� ��� ������� ����� �����
// hmap     - ������������� �������� �����,
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� CREATE_MAP
// ��� ������ ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspSitDocByName(HMAP hmap, char *mapname,  // 18/04/16
                                            TASKPARM * parm);

_PASPIMP long int _PASPAPI MapPaspSitDocByNameUn(HMAP hmap, WCHAR *mapname,  // 18/04/16
                                            TASKPARM * parm);
// --------------------------------------------------------------
// �������� ���������������� �����
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// rscname  - ��� ����� �������������� (Rsc)
// areaname - ��� ������
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// Help ���������� �� mappasp.chm, ����� CREATE_MAP
// ��� ������ ��� ������ �� ����� ���������� ����
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspSitCreate(char * mapname, char *rscname,
                                        char * areaname, TASKPARM * parm);

_PASPIMP long int _PASPAPI MapPaspSitCreateUn(WCHAR *mapname, WCHAR *rscname,      // 01/04/14
                                           WCHAR *areaname, TASKPARM * parm);

}

#endif

