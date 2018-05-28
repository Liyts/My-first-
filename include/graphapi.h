/****** GRAPHAPI.H  ************ Borzov A.U.      ***** 22/12/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2014              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*           ������������ ������� ������� � ����� ����              *
*              ������������� �� MAPACCES.DLL                       *
*                                                                  *
*******************************************************************/
#ifndef GraphApiH
#define GraphApiH

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

typedef HANDLE HNET;  // ������������� �����
typedef HANDLE HPATH; // ������������� ��������
typedef HANDLE HDGR;  // ������������� ����� �����������
typedef HANDLE HTSP;  // ������������� ������ ������������


#if defined(_NETDLLEXPORT)
 #ifdef LINUXAPI
  #define NETIMP
 #else
  #define NETIMP __declspec(dllexport)
 #endif
#else
 #ifdef LINUXAPI
  #define NETIMP
 #else 
  #define NETIMP __declspec(dllimport)
 #endif 
#endif

// ���� �������� ����� �����
#define NODECODE       5558   // Excode ����
#define EDGECODE       5557   // Excode �����
#define ONEWAYEDGECODE 5562   // Excode ����� ��������������
#define PARENTLISTCODE 5555   // Excode ����� ������������� �����

// ���� ��������� 
#define SEMNETROADTYPE 1052   // ��� (�����) ������

// ��� ������� ����������� ����, �.�. ���� � ����������� ��������� ����� �����
#define SP_LENGTH        0 // �� ���������� - ��������� ����� ����� ����� �����
#define SP_TIME          1 // �� ������� - ��������� ����� ����� ����� �����, �������� �� �������� ���������
                           // "��������" (32817), "�������� ��������" (32818)
                           // ���� ��� ����� ��������� �� ������, �� �������� ����������� = 60 ��/���
#define SP_SEMCOST       2 // �� ��������� �� ��������� ����� "��������� �����" (32819),
                           // "��������� ����� ��������" (32824)
                           // ���� ��� ����� ��������� �� ������, �� ��� ��������� ����������� = 1
#define SHORTPATHTYPEMIN 0
#define SHORTPATHTYPEMAX 2

// ��������� �������� ����� �����
typedef struct OPENNETPARM
{
  HWND   Wnd;          // ������������� ����, �������� ���������� ��������� WM_PROGRESSBAR
                       // � ��������� ����� � ��������� ���������
                       // ���� 0, �� ��������� �� ����������
  HMAP   ParentMap;    // ��������, � ������� ������� �����, �� ������� �������� ����
                       // ��������� ��� ������� onGetPathParentEdgeSite
                       // ���� 0, �� �� ������������
  char   Reserve[128];
}
  OPENNETPARM;

// ��������� ���������� ����������� ��������
typedef struct PATHPARM
{
  DOUBLEPOINT Point1;       // ���������� ������ ��������
                            // ������� �������� �� ��������� ����� �� ���� ��� �����
  DOUBLEPOINT Point2;       // ���������� ����� ��������
                            // ������� �������� �� ��������� ����� �� ���� ��� �����
  HWND        Wnd;          // ����, �������� ���������� ��������� WM_PROGRESSBAR � ��������� ���������
  int         NodeKey1;     // ���� ����, �� �������� �������� �������
                            // ���� = 0, �� ������� �������� ����� ������� Point1-Point2
  int         NodeKey2;     // ���� ����, �� �������� �������� �������
                            // ���� = 0, �� ������� �������� ����� ������� Point1-Point2
  int         IsWgs;        // ���������� ������ �� � ������� ��������� ����� ����� � ������,
                            // � ������� �������������� ������������ (������, �������)
                            // �� ���������� Wgs84 � ��������
  int         Type;         // ��� ������� (SP_LENGTH, SP_SEMCOST, SP_TIME)
  int         IsUturn;      // ��������� ��������� ��� ���������� ��������
  int         UseRoadCount; // ������ ������� ������ ����������� ����� �����
                            // (������ ���� ����� 0, ���� ��� ������ ��������� ���
                            // onGetParentRoadTypeCount, ���� ���� �����������)
  int        *UseRoads;     // ������ ������ ����������� ����� ����� ��� ���������� ��������
                            // (���� = 0, �� ��� ������ ���������)
  HSELECT     UseSelect;    // ����������� ����� (���� = 0, �� ��������� ��� �����)
  HSELECT     BanSelect;    // ����������� ����� (������ ����� ������� ���������)
                            // ���� = 0, �� ��� ����������� �����

  char        Reserve[128];
}
  PATHPARM;

// ��������� ���������� ����� ����������� (������ �����, ����������� �� �������� ���������� �� ����)
typedef struct DISTGRAPHPARM
{
  double  Dist;         // ���������� (�����, ���) �� ������� ����� ������ �� ���������� ����
  HWND    Wnd;          // ����, �������� ���������� ��������� WM_PROGRESSBAR � ��������� ���������
  int     NodeKey;      // ���� ����, �� �������� �������� ���� �����������
  int     Type;         // ��� ������� (SP_LENGTH, SP_SEMCOST, SP_TIME)
  int     IsUturn;      // ��������� ���������
  int     UseRoadCount; // ������ ������� ������ ����������� ����� �����
                        // (������ ���� ����� 0, ���� ��� ������ ��������� ���
                        // onGetParentRoadTypeCount, ���� ���� �����������)
  int    *UseRoads;     // ������ ������ ����������� ����� ����� ��� ���������� ��������
                        // (���� = 0, �� ��� ������ ���������)
  HSELECT UseSelect;    // ����������� ����� (���� = 0, �� ��������� ��� �����)
  HSELECT BanSelect;    // ����������� ����� (������ ����� ������� ���������)
                        // ���� = 0, �� ��� ����������� �����
  char    Reserve[128];
}
  DISTGRAPHPARM;

// ��� ������� ������ ������������
#define TSP_TOFIRST  0 // ��� ������������� � ������ ������ (������������ ���������� ������)
#define TSP_TOLAST   1 // ��� ������������� � ��������� ������
#define TSPTYPEMIN   0
#define TSPTYPEMAX   1

// ��������� ������� ������ ������������ (Travelling salesman problem)
typedef struct TSPPARM
{
  HWND         Wnd;          // ����, �������� ���������� ��������� WM_PROGRESSBAR � ��������� ���������
  int          PointCount;   // ���������� �����, ������� ���� ��������
  DOUBLEPOINT *Points;       // ���������� �����, ������� ���� ��������
  int          CalcType;     // ��� ������� ������ ������������ (TSP_TOFIRST, TSP_TOLAST)
  int          IsWgs;        // ���������� ������ �� � ������� ��������� ����� ����� � ������,
                             // � ������� �������������� ������������ (������, �������)
                             // �� ���������� Wgs84 � ��������
  int          Type;         // ��� ������ �������� (SP_LENGTH, SP_SEMCOST, SP_TIME)
  int          IsUturn;      // ��������� ���������
  int          UseRoadCount; // ������ ������� ������ ����������� ����� �����
                             // (������ ���� ����� 0, ���� ��� ������ ��������� ���
                             // onGetParentRoadTypeCount, ���� ���� �����������)
  int         *UseRoads;     // ������ ������ ����������� ����� ����� ��� ���������� ��������
                             // (���� = 0, �� ��� ������ ���������)
  HSELECT      UseSelect;    // ����������� ����� (���� = 0, �� ��������� ��� �����)
  HSELECT      BanSelect;    // ����������� ����� (������ ����� ������� ���������)
                             // ���� = 0, �� ��� ����������� �����
  char         Reserve[128];
}
  TSPPARM;

extern "C"
{
  // �������� ����� ����
  // mapname - ��� ����� �����
  // parm    - ��������� �������� �����
  // ���������� ������������� ��������� �����
  // ��� ������ ���������� 0
  NETIMP HNET WINAPI onOpenNet(WCHAR *mapname, OPENNETPARM *parm);

  // �������� ����� ����
  // hnet - ������������� ����� ����, ���������� onOpenNet
  NETIMP void WINAPI onCloseNet(HNET hnet);

  // �������� ����� ���� �� ����� ����� ����� �����
  // mapname - ��� ����� ����� �����
  NETIMP void WINAPI onCloseNetByName(WCHAR *mapname);

  // ���������� ������������� �������� ����� �����
  // hnet - ������������� ����� ����, ���������� onOpenNet
  NETIMP HMAP WINAPI onGetHMAP(HNET hnet);

  // ���������� ��������, � ������� ������� �����, �� ������� �������� ����
  // (���� ParentMap ��������� OPENNETPARM, ���������� ��� �������� �����)
  // hnet - ������������� ����� ����, ���������� onOpenNet
  NETIMP HMAP WINAPI onGetParentMap(HNET hnet);

  // ���������� ���������� ����� �����, ������������� � ���������� �����
  // hnet - ������������� ����� ����, ���������� onOpenNet
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetParentRoadTypeCount(HNET hnet);

  // ���������� ��� ���� ������, ������������� � ���������� �����
  // hnet   - ������������� ����� ����, ���������� onOpenNet
  // number - ���������� ����� ���� ������ (�� 0)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetParentRoadTypeName(HNET hnet, long int number,
                                                 WCHAR *name, long int namesize);

  //***************************************************************
  //                    ���������� �������
  //***************************************************************

  // ����� ����������� ��������
  // hnet - ������������� ����� ����, ���������� onOpenNet
  // parm - ��������� ����������� ��������
  // ���������� ������������� ��������
  // ��� ������ ���������� 0
  NETIMP HPATH WINAPI onCreatePath(HNET hnet, PATHPARM *parm);

  // ������� �������
  // hpath - ������������� ��������, ���������� onCreateRoute
  NETIMP void WINAPI onFreePath(HPATH hpath);

  // ���������� ����� ������� �� ����� �������� � �����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // ��� ������ ���������� 0
  NETIMP double WINAPI onGetPathTime(HPATH hpath);

  // ���������� ����� ����� �������� � ������
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // ��� ������ ���������� 0
  NETIMP double WINAPI onGetPathLength(HPATH hpath);

  // ���������� ���������� ����� � ��������
  // hpath - ������������� ��������, ���������� onCreateRoute
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeCount(HPATH hpath);

  // ���������� ���� ����� �������� �� ����� �����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeKey(HPATH hpath, long int number);

  // ���������� ����� ������� ����� �������� �� ����� �����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeNum(HPATH hpath, long int number);

  // ���������� ����� ���� ������� �� �������� ���� �������� ����� ��� �������� �����
  // ��� ��������� ����� ���� ����������� onGetParentRoadTypeName
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // ��� ������ ���������� -1
  NETIMP long int WINAPI onGetPathParentEdgeType(HPATH hpath, long int number);

  // ���������� ������������� �����, �� ������� ������� ���������
  // ����� �������� ��� �������� ����� �����
  // ��� ������ ������� ���������� �����:
  // - ����� ����� ���� ��������� � ������ "��������� ����� � ��������� �������� �����"
  // - ��� �������� ����� ������ �������� ParentMap, � ������� ������� �����, �� ������� �������� ����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP HSITE WINAPI onGetPathParentEdgeSite(HPATH hpath, long int number);

  // ���������� ����� ����� �����, �� ������� ������� ��������� ����� �������� ��� �������� ����� �����
  // ��� ������ ������� ���������� �����:
  // - ����� ����� ���� ��������� � ������ "��������� ����� � ��������� �������� �����"
  // - ��� �������� ����� ������ �������� ParentMap, � ������� ������� �����, �� ������� �������� ����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathParentEdgeSheetNum(HPATH hpath, long int number);

  // ���������� ���� ������� �� �������� ��������� ����� �������� ��� �������� ����� �����
  // ��� ������ ������� ���������� ����� ����� ����� ���� ��������� � ������
  // "��������� ����� � ��������� �������� �����"
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathParentEdgeKey(HPATH hpath, long int number);

  // ��������� ������ �� �������� �������� ����� �������� ��� �������� ����� �����
  // ��� ������ ������� ���������� �����:
  // - ����� ����� ���� ��������� � ������ "��������� ����� � ��������� �������� �����"
  // - ��� �������� ����� ������ �������� ParentMap, � ������� ������� �����, �� ������� �������� ����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // obj    - �������������, � ������� ����� ������ ������������ ������
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathParentEdgeObject(HPATH hpath, long int number, HOBJ obj);

  // ���������� ����� ����� �������� �� ����������� ������ ����� � �������� � ������
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP double WINAPI onGetPathEdgeLength(HPATH hpath, long int number);

  // ���������� ����� ������� ����� �������� �� ����������� ������ ����� � �������� � �����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP double WINAPI onGetPathEdgeTime(HPATH hpath, long int number);

  // ���������� ���������� ������ ����� ����� ��������
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // point  - ������������ ���������� ������ ����� ����� ��������
  //          ���� ������� ���������� onCreatePath, onCreatePathEx, �� ������������ ����������
  //          � ������� ��������� ����� �����
  //          ���� ������� ���������� onCreatePathWgs, onCreatePathWgsEx, �� ������������ ����������-
  //          ������, ������� � �������� �� WGS84
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeFirstPoint(HPATH hpath, long int number, DOUBLEPOINT *point);

  // ���������� ���������� ��������� ����� ����� ��������
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // point  - ������������ ���������� ��������� ����� ����� ��������
  //          ���� ������� ���������� onCreatePath, onCreatePathEx, �� ������������ ����������
  //          � ������� ��������� ����� �����
  //          ���� ������� ���������� onCreatePathWgs, onCreatePathWgsEx, �� ������������ ����������-
  //          ������, ������� � �������� �� WGS84
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeLastPoint(HPATH hpath, long int number, DOUBLEPOINT *point);

  // ���������� ���� �������� �� ��������� ����� ����� ��������
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 2, �� ��������� ����� ��� ��������)
  // angle  - ������������ ���� �������� �� ��������� ����� ����� ��������
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeLastPointAngle(HPATH hpath, long int number, double *angle);

  // ���������� ���� �������� �� ������ ����� ����� ��������
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 1 �� onGetPathEdgeCount - 1, �� ������ ����� ��� ��������)
  // angle  - ������������ ���� �������� �� ������ ����� ����� ��������
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeFirstPointAngle(HPATH hpath, long int number, double *angle);

  // ���������� ������������ ���� ������� ������� ����� ��������
  // (���� �� ������ ����� ����� ������������ �� ����� � �� ������ ����� ������ ������� �������)
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // dir    - ������������ ������������ ����
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeFirstSegmentDir(HPATH hpath, long int number, double *dir);

  // ���������� ������������ ���� ���������� ������� ����� ��������
  // (���� �� ��������� ����� ����� ������������ �� ����� � �� ������������� ����� ������ ������� �������)
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathEdgeCount - 1)
  // dir    - ������������ ������������ ����
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathEdgeLastSegmentDir(HPATH hpath, long int number, double *dir);

  // ���������� ���������� ����� � �������� (= ���������� ������ ����� + 1)
  // hpath - ������������� ��������, ���������� onCreateRoute
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathNodeCount(HPATH hpath);

  // ���������� ���� ���� �������� �� ����� �����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathNodeCount - 1)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathNodeKey(HPATH hpath, long int number);

  // ���������� ����� ������� ���� �������� �� ����� �����
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathNodeCount - 1)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathNodeNum(HPATH hpath, long int number);

  // ���������� � ������ ������� ��������
  // hpath - ������������� ��������, ���������� onCreateRoute
  // obj   - ������, � ������� ������������ ������� ��������
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathObject(HPATH hpath, HOBJ obj);

  // ���������� � ������ ������� ��������
  // hpath   - ������������� ��������, ���������� onCreateRoute
  // obj     - ������, � ������� ������������ ������� ��������
  // subject - ����� ����������, � ������� ������������ ������� ��������
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathSubject(HPATH hpath, HOBJ obj, long int subject);

  // ���������� ���������� ����� � ��������
  // hpath - ������������� ��������, ���������� onCreateRoute
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathPointCount(HPATH hpath);

  // ���������� ���������� ����� �������� �� ����������� ������ � ��������
  // hpath  - ������������� ��������, ���������� onCreateRoute
  // number - ����� ����� � �������� (�� 0 �� onGetPathPointCount - 1)
  // point  - ������������ ���������� ����� ��������
  //          ���� ������� ���������� onCreatePath, onCreatePathEx, �� ������������ ����������
  //          � ������� ��������� ����� �����
  //          ���� ������� ���������� onCreatePathWgs, onCreatePathWgsEx, �� ������������ ����������-
  //          ������, ������� � �������� �� WGS84
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetPathPoint(HPATH hpath, long int number, DOUBLEPOINT *point);

  //***************************************************************
  //                    ���� �����������
  //***************************************************************

  // �������� ����� �����������
  // hnet - ������������� ����� ����
  // parm - ��������� ���������� ����� �����������
  // ���������� ������������� ����� �����������
  // ��� ������ ���������� 0
  NETIMP HDGR WINAPI onCreateDistGraph(HNET hnet, DISTGRAPHPARM *parm);

  // �������� ����� �����������
  // hdgr - ������������� ����� �����������
  NETIMP void WINAPI onFreeDistGraph(HDGR hdgr);

  // ���������� ���������� ����� � ����� �����������
  // hdgr - ������������� ����� �����������
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetDistGraphEdgeCount(HDGR hdgr);

  // ���������� ���� ����� ����� ����������� �� ����� �����
  // hdgr   - ������������� ����� �����������
  // number - ����� ����� � ����� ����������� (�� 0 �� onGetDistGraphEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetDistGraphEdgeKey(HDGR hdgr, long int number);

  // ���������� ����� ������� ����� ����� ����������� �� ����� �����
  // hdgr   - ������������� ����� �����������
  // number - ����� ����� � ����� ����������� (�� 0 �� onGetDistGraphEdgeCount - 1)
  // ��� ������ ���������� 0
  NETIMP long int WINAPI onGetDistGraphEdgeNum(HDGR hdgr, long int number);

  //***************************************************************
  //                    ������ ������������
  //  (����� ������������ �������� � ���������� ���������� �����)
  //***************************************************************

  // �������� ���� ����������� ����� ��������� ����� (������ ������������)
  // hnet - ������������� ����� ����
  // parm - ��������� ���������� ����� �����������
  // ���������� ������������� ������ ������������
  // ��� ������ ���������� 0
  NETIMP HTSP WINAPI onCreateTSP(HNET hnet, TSPPARM *parm);

  // �������� ������ ������������
  // htsp - ������������� ������ ������������
  NETIMP void WINAPI onFreeTSP(HTSP htsp);

  // ���������� ���������� ��������� � ����
  // htsp - ������������� ������ ������������
  NETIMP long int WINAPI onGetTSPPathCount(HTSP htsp);

  // ���������� ������� ����� ����� ������� � ����
  // ����������� HPATH �� ����, ��� �������� ������������� � onFreeTSP
  // htsp    - ������������� ������ ������������
  // pathnum - ����� �������� � ���� (�� 0)
  // ��� ������ ���������� 0
  NETIMP HPATH WINAPI onGetTSPPath(HTSP htsp, long int pathnum);

  // ���������� ����� ������ � ������ �������� (�� 0)
  // htsp    - ������������� ������ ������������
  // pathnum - ����� �������� � ���� (�� 0)
  // ��� ������ ���������� -1
  NETIMP long int WINAPI onGetTSPPathFirstPoint(HTSP htsp, long int pathnum);

  // ���������� ����� ������ � ����� ��������
  // htsp    - ������������� ������ ������������
  // pathnum - ����� �������� � ���� (�� 0)
  // ��� ������ ���������� -1
  NETIMP long int WINAPI onGetTSPPathLastPoint(HTSP htsp, long int pathnum);


}

#endif
