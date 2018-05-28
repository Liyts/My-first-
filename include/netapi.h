/****** NETAPI.H ************* Tarakanova I.R.  ******* 03/07/15 ***
******* NETAPI.H ************* Shabakov D.A.    ******* 31/05/13 ***
******* NETAPI.H ************* ������ �.�.      ******* 02/08/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2014              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*          ���������� ������� ������� � ���� ��������              *
*           ����� ������� ��. GRAPHAPI.H, GRAPHDLG.H               *
*             ������� ������������� �� OBJNET.DLL                  *
*                                                                  *
********************************************************************/

#ifndef NETAPI_H
#define NETAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifdef WIN32API
#if defined(_NETDLLEXP)
  #define _NETIMP __declspec(dllexport)
#else
  #define _NETIMP __declspec(dllimport)
#endif
#else
  #define _NETIMP
#endif

// ���� �������� ��� ���������� ������ ����� ��������� ����:
#define SEMNETRIB       32812  // ����� �������-����� (��� ����)
#define SEMNETKNOTFIRST 32813  // ����� �������-���� ������ ����� (��� �����)
#define SEMNETKNOTLAST  32814  // ����� �������-���� ��������� ����� (��� �����)
#define SEMNETNUMBER    32815  // ����� ����
#define SEMNETTOOBJECT  32816  // ������ �� ������ �����
#define SEMNETVDIRECT   32817  // �������� ������ (��� �����)
#define SEMNETVUNDIRECT 32818  // �������� �������� (��� �����)
#define SEMNETCOSTRIB   32819  // ��������� �����
#define SEMNETRANKRIB   32820  // ���� �����

typedef HANDLE HGRAPH;  // ������������� �����

extern "C"
{
// ���������� ����� ����� � ������� �������
// hmap - ������������� �������� ��������� �����
// parm - �������� ���������� ������
// �� ����� �������������� ������ ���� �������� ������� ��� ���������� ����
// ��� �������� ���������� ���������� ������������� ���������������� �����
// � ����������� �����
// ��� ������ ���������� 0

_NETIMP HSITE WINAPI onCreateNetDlg(HMAP hmap, TASKPARMEX *parm);

// ���������� ����� ����� � ������� ��� ��� ������ �������
// hmap - ������������� �������� ��������� �����
// parm - �������� ���������� ������ (��.maptype.h)
// namesit - ��� ��������� �����
// namersc - ������ ��� ����� �������������� road25.rsc                         // 02/08/16
// flag - ���������� ��������  "���������� ����" (0- �� �������� ������, 1 - ��������)

_NETIMP HSITE WINAPI onCreateNetDlgEx(HMAP hmap, TASKPARMEX *parm,
                              char *namesit, char *namersc, long int flag);

_NETIMP HSITE WINAPI onCreateNetDlgUn(HMAP hmap, TASKPARMEX *parm,
                              WCHAR *namesit, WCHAR *namersc, long int flag);

// ����������� ����������� ���������� ����� ����� ������ ����
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// pointbegin - ��������� ���� (������������� ������� ����� � ������)
// pointend - �������� ���� (������������� ������� ����� � ������)
// � ������� ���������� ������ "��������� ���������� ������������ ����", � �������
// ��������������� ����� ���������� (����� ��� �����,� ��������� ������ �����
// ������ ����� ��������� "��������") � ������ �� ���������� �����
// �� ��������� ������ ������� �������� �������������� ������ "������ ��������",
// � ������� ������������ �������� ������� ����� � ������������� ���� �� ������� �������
// �� ���������������� ����e ����� �������� �����,������� ���������� ����������� �������
// ����� ���������� �������� ������������ �������� mapTotalSeekObjectCount(seekapi.h)
// �������� ������������� ����������� ������� ����� ��������� ������� mapTotalSeekObject(seekapi.h)
// ����������: ����� ������� (mapObjectKey), ���� ������ ������� ����������
//            - 1, ���� ������ ������� �� ����������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathDlg(HMAP hmap, HSITE site, TASKPARMEX *parm,
                              HOBJ infobegin, HOBJ infoend);

// ����������� ����������� ���������� ����� ����� ������ ���� ��� ������ ��������
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// pointbegin - ��������� ����(������������� ������� ����� � ������)
// pointend - �������� ����(������������� ������� ����� � ������)
// methodseek - ����� ���������� (0 - �����, 1- �����)
// speed - ������� �������� (��/�)(���� methodseek = 1 � �������� ���������
// "��������" �� �����������)
// �� ���������������� ����e ����� �������� �����,������� ���������� ����������� �������
// ����� ���������� �������� ������������ �������� mapTotalSeekObjectCount(seekapi.h)
// �������� ������������� ����������� ������� ����� ��������� ������� mapTotalSeekObject(seekapi.h)
// ����������: ����� ������� (mapObjectKey), ���� ������ ������� ����������
//            - 1, ���� ������ ������� �� ����������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPath(HMAP hmap, HSITE site, TASKPARMEX *parm,
                           HOBJ infobegin, HOBJ infoend,
                           long int methodseek, double speed);

// ����������� ����������� ���������� ����� ����� ������ ���� ��� ������ ��������
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// object - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����.
// pointbegin - ��������� ����(������������� ������� ����� � ������)
// pointend - �������� ����(������������� ������� ����� � ������)
// methodseek - ����� ���������� (0 - �����, 1- �����)
// speed - ������� �������� (��/�)(���� methodseek = 1 � �������� ���������
// "��������" �� �����������)
// ����������: -1, ���� ���� ������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathCreateObject(HMAP hmap, HSITE site,
                                       TASKPARMEX *parm, HOBJ object,
                                       HOBJ infobegin, HOBJ infoend,
                                       long int methodseek, double speed);

// ����������� ����������� ���������� ����� ����� �������
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// info - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����
// point1 - ��������� ����� � ������ �� ���������
// point2 - �������� ����� � ������ �� ���������
// ���� ������������ �� ����� �� ��������� ����� � point1 �� ����� �� ���������
// ����� � point2
// �� ����e ��������� �������� ������ - ����������� �������
// ����������: ����� ������� (mapObjectKey), ���� ������ ������� ����������
//            - 1, ���� ������ ������� �� ����������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathDlgByPoint(HMAP hmap, HSITE site, HOBJ info, TASKPARMEX *parm,
                                     DOUBLEPOINT *point1,DOUBLEPOINT *point2);

// ����������� ����������� ���������� ����� ����� �������
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// info - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����
// point1 - ��������� ����� � ������ �� ���������
// point2 - �������� ����� � ������ �� ���������
// ���� ������������ �� ����� �� ��������� ����� � point1 �� ����� �� ���������
// ����� � point2
// ����������: -1, ���� ���� ������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathByPoint(HMAP hmap, HSITE site, HOBJ info, TASKPARMEX *parm,
                                  DOUBLEPOINT *point1,DOUBLEPOINT *point2);

// ����������� ����������� ���������� ����� ����� ������� � ������ ��������������
// �������� � ����������� ����� (��������� ��������)
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// info - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����
// point1 - ��������� ����� � ������ �� ���������
// point2 - �������� ����� � ������ �� ���������
// select - �������� ������� ������ (������ ��������� �����, ������� ����������� �� ������ ���. ����)
// foneway - ���� �������������� �������� (0 - �� ���������, 1- ���������)
// ���� ������������ �� ����� �� ��������� ����� � point1 �� ����� �� ���������
// ����� � point2
// ����������: -1, ���� ���� ������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathByPointEx(HMAP hmap, HSITE site, HOBJ info, TASKPARMEX *parm,
                                    DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                                    HSELECT select, long int foneway);

// ���������� � ���� �����, ������������� �� ���������� ����� ��������� ��
// ���������� ���� (���������� ����� �����������)
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����, �.�. �� ����� ������ ����
// ������� ���� ���� � ������������� �����������: ����� ���� � ������ �� �����
// ����, � ����� � �����������: ����� ������� � ���������� ����� ��� �������
// �����, ������ �� ������ ����� � ����� ����
// info -  ���� ���� (������������� ������� ����� � ������)
// distance - ���������� � ������
// �� ���������������� ����� ����� �������� �����, �������������  �� ����������,
// ����� distance �� info
// ����� ���������� �������� ������������ �������� mapTotalSeekObjectCount(seekapi.h)
// �������� ������������� ������� ����� ��������� ������� mapTotalSeekObject(seekapi.h)
// ��� ������ ���������� 0

_NETIMP long int WINAPI onDistFromKnot(HMAP hmap, HSITE site, TASKPARMEX *parm,
                               HOBJ info, double distance);

// �������� ��������� ���� ���� � ��������� �����
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// info - ������������� ������� ����� � ������
// point - ���������� ����� � ������  � ������� �����
// ������ �������������:
//  - ������� ������
//    HOBJ hobj = mapCreateSiteObject(hmap,site,IDDOUBLE2,0);
//  - ������� ��������� ���� � ����� point � ���������� � hobj
//    long int ret = onGetNodeByPoint(hmap,site,hobj, point);
//  - �������� ������� ������ � �����
//    if (ret)
//        onDistFromKnot(hmap,site,parm,hobj,20);
// ��� ������ ���������� 0

_NETIMP long int WINAPI onGetNodeByPoint(HMAP hmap, HSITE site,
                                 HOBJ info, DOUBLEPOINT *point);

// �������� ��������� �������� ������ (�����) � ��������� �����
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// info - ������������� ������� ����� � ������
// point - ���������� ����� � ������  � ������� �����
// ��� ������ ���������� 0

_NETIMP long int WINAPI onGetRibByPoint(HMAP hmap, HSITE site,
                                HOBJ info, DOUBLEPOINT *point);

// ���������� ������������ ���� ����� ������� (������ ����)
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// parm - �������� ���������� ������ (��.maptype.h)
// array - ����� ������� ��������� ������� �����,
//         ������ ������� ����� count
// count - ���������� ����� ��� ���������� ������������ ����
// ������� ������������ �� ��������� � ������ ����� ����
// � ������� ���������� ������ "��������� ���������� ������������ ����", � �������
// ��������������� ����� ���������� (����� ��� �����,� ��������� ������ �����
// ������ ����� ��������� "��������") � ������ �� ���������� �����
// �� ��������� ������ ������� �������� �������������� ������ "������� ������ �����",
// � ������� ������������ ������ ����� � ��� �������, � ������� ���� ����������� �� ��� ���������,
// ������������� �������� ����� �������� ����� �����, ����� ����� ����.
// ��� ������ ���������� 0

_NETIMP long int WINAPI onMinimalPath(HMAP hmap, HSITE site, TASKPARMEX *parm,
                              DOUBLEPOINT *arraypoint, long int count);

// ���������� ������������ ���� ����� ������� (������ ����)
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// parm - �������� ���������� ������ (��.maptype.h)
// arraypoint - ����� ������� ��������� (� ������ �� ���������) ������� �����,
//              ������ ������� ����� count
// arraynumber - ����� ������� � �������� ����� (��� �����������),
//               ������ ������� ����� count
// count - ���������� ����� ��� ���������� ������������ ����
// flagoneway - ���� �������������� �������� (0 - �� ���������, 1 - ���������)
// flagreturn - ���� �������� � ������ ����� (0 - �� ������������, 1 - ������������)
// flagcalc - ����� ������� (0 - �� �����, 1- �� �������)
// ������� ������������ �� ��������� � ������ ����� ����
// � ������ arraynumber ����� �������� ������ �����, ������� ���������� ������� ������
// ���������� ����� ����� ����
// ��� ������ ���������� 0

_NETIMP double WINAPI onMinimalPathEx(HMAP hmap, HSITE site, TASKPARMEX *parm,
                                      DOUBLEPOINT *arraypoint, long int *arraynumber,
                                      long int count, long int flagoneway,
                                      long int flagreturn, long int flagcalc);

// �������������� ���� - �������� �����
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// info - ������������� �������, ������� ����� �������
// ���� ��� �������� ������ ����� ������ �� ������ �����
// ���� � �������������� ����� ��������� ���������, �� ���� ���������,���� ��� -
// ��������� ���������  � ��� ������ ���� ����� ��������� ���� ����
// ��� ������ ���������� 0

_NETIMP long int WINAPI onEditDeleteNode(HMAP hmap, HSITE site,TASKPARMEX *parm,
                                         HOBJ info);

// �������������� ���� - ���������� �����
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// info1 � info2 - �������������� ��������, �� ����������� ������� ����� �������� ����
// ������� �������� �  onEditDeleteNode(...)
// ��������� ��������� ���� � ������������� ���������
// ��� ������ ���������� 0

_NETIMP long int WINAPI onEditAddNode(HMAP hmap, HSITE site,TASKPARMEX *parm,
                                      HOBJ info1, HOBJ info2);

// �������������� ���� - ����������������� �����
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// ������� ��������� � ���� ������������ ������� �� ������������ �����
// info - ������������� �������(���� �� �����������)
// ���� ������ ����� ������ �� ������ �����
// ������� ������� �������������� ���� ���� � ����� ���� �������������
// ��� ������ ���������� 0

_NETIMP long int WINAPI onEditRoad(HMAP hmap, HSITE site,TASKPARMEX *parm,
                           HOBJ info);

// �������������� ���� - �������� ������� � ����������
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � ����������� �����
// info1 � info2 - �������������� �������� (�����),������ ����� ����� ���� � ���� ��������������
// � �������� info1 � info2 ������������� ������������ ���������� ������� onEditRoad(...)
// ������� ������� - ����� � ���� ��� � ������� ����� ����
// ��� ������ ���������� 0
_NETIMP long int WINAPI onEditCreateArc(HMAP hmap, HSITE site,TASKPARMEX *parm,
                                HOBJ info1,HOBJ info2);

/*********************************************************
*                                                        *
*                  ������� HGRAPH                        *
*                                                        *
*********************************************************/

// �������� ������ ������
// hmap - ������������� �������� ��������� �����
// site - ���������������� ����� � �����
// ������������� ���������������� ����� � �����  ����� ��������,
// ��������� ������� onGetGraphSiteIdent(...)
// ��� �������� ���������� ���������� ������������� ����� ����
// ��� ������ ���������� 0

_NETIMP HGRAPH WINAPI onOpenGraphEx(HMAP hmap, HSITE site);

// ������� ������ ������
// hgraph - ������������� ����� ����

_NETIMP long int WINAPI onCloseGraph(HGRAPH hgraph);

// ���������� sit � �����
// hmap - ������������� �������� ��������� �����
// ��� �������� ���������� ���������� ������������� ����������������
// ����� � ������ ���� (���� ���� � ����� ���������, ������������ �������������
// ������ ����� � �����)
// ��� ������ ���������� 0

_NETIMP HSITE WINAPI onGetGraphSiteIdent(HMAP hmap);


_NETIMP long int WINAPI onSeekPathDlgGraph(HMAP hmap, HGRAPH hgraph, TASKPARMEX *parm,
                                   HOBJ infobegin, HOBJ infoend);

// ����������� ����������� ���������� ����� ����� ������ ���� ��� ������ ��������
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// pointbegin - ��������� ����(������������� ������� ����� � ������)
// pointend - �������� ����(������������� ������� ����� � ������)
// methodseek - ����� ���������� (0 - �����, 1- �����)
// speed - ������� �������� (��/�)(���� methodseek = 1 � �������� ���������
// "��������" �� �����������)
// �� ���������������� ����e ����� �������� �����,������� ���������� ����������� �������
// ����� ���������� �������� ������������ �������� mapTotalSeekObjectCount(seekapi.h)
// �������� ������������� ����������� ������� ����� ��������� ������� mapTotalSeekObject(seekapi.h)
// ����������: ����� ������� (mapObjectKey), ���� ������ ������� ����������
//            - 1, ���� ������ ������� �� ����������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathGraph(HMAP hmap, HGRAPH hgraph, TASKPARMEX *parm,
                                HOBJ infobegin, HOBJ infoend,
                                long int methodseek, double speed);

// ����������� ����������� ���������� ����� ����� ������ ���� ��� ������ ��������
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// object - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����.
// infobegin - ��������� ����(������������� ������� ����� � ������)
// infoend - �������� ����(������������� ������� ����� � ������)
// select - �������� ������� ������, �������������� ��������� ��������
// mapCreateSiteSelectContext(...), ��� ���������� ����������� (� select ������������
// ����, ������� ���������� ����������� ����)
// methodseek - ����� ���������� (0 - �����, 1- �����)
// speed - ������� �������� (��/�)(���� methodseek = 1 � �������� ���������
// "��������" �� �����������)
// ��� ������ ���������� 0

_NETIMP long int WINAPI onSeekPathGraphSelect(HMAP hmap, HGRAPH hgraph, HOBJ object,
                                      HOBJ infobegin, HOBJ infoend, HSELECT select,
                                      long int methodseek, double speed);

// ����������� ����������� ���������� ����� ����� ������ ���� ��� ������ ��������
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// object - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����.
// pointbegin - ��������� ����(������������� ������� ����� � ������)
// pointend - �������� ����(������������� ������� ����� � ������)
// methodseek - ����� ���������� (0 - �����, 1- �����)
// speed - ������� �������� (��/�)(���� methodseek = 1 � �������� ���������
// "��������" �� �����������)
// ����������: -1, ���� ���� ������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathCreateObjectGraph(HMAP hmap, HGRAPH hgraph, TASKPARMEX * parm,
                                            HOBJ object, HOBJ infobegin, HOBJ infoend,
                                            long int methodseek, double speed);

// ����������� ����������� ���������� ����� ����� �������
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// info - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����
// point1 - ��������� ����� � ������ �� ���������
// point2 - �������� ����� � ������ �� ���������
// ���� ������������ �� ����� �� ��������� ����� � point1 �� ����� �� ���������
// ����� � point2
// �� ����e ��������� �������� ������ - ����������� �������
// ����������: ����� ������� (mapObjectKey), ���� ������ ������� ����������
//            - 1, ���� ������ ������� �� ����������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathDlgByPointGraph(HMAP hmap, HGRAPH hgraph, HOBJ info, TASKPARMEX *parm,
                                          DOUBLEPOINT *point1, DOUBLEPOINT *point2);

// ����������� ����������� ���������� ����� ����� �������
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// info - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����
// point1 - ��������� ����� � ������ �� ���������
// point2 - �������� ����� � ������ �� ���������
// ���� ������������ �� ����� �� ��������� ����� � point1 �� ����� �� ���������
// ����� � point2
// ����������: -1, ���� ���� ������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathByPointGraph(HMAP hmap, HGRAPH hgraph, HOBJ info, TASKPARMEX * parm,
                                       DOUBLEPOINT *point1, DOUBLEPOINT *point2);

// ����������� ����������� ���������� ����� ����� �������
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// info - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����
// point1 - ��������� ����� � ������ �� ���������
// point2 - �������� ����� � ������ �� ���������
// ���� ������������ �� ����� �� ��������� ����� � point1 �� ����� �� ���������
// ����� � point2
// ��� ������ ���������� 0

_NETIMP long int WINAPI onSeekPathByPointGraphEx(HMAP hmap,HGRAPH hgraph, HOBJ info,
                                         DOUBLEPOINT *point1, DOUBLEPOINT *point2);

// ����������� ����������� ���������� ����� ����� ������� � ������ ��������������
// �������� � ����������� ����� (��������� ��������)
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// info - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����
// point1 - ��������� ����� � ������ �� ���������
// point2 - �������� ����� � ������ �� ���������
// select - �������� ������� ������ (������ ��������� �����, ������� ����������� �� ������ ���. ����)
// ������������� �������� ����������� ������
// ���� ������������ �� ����� �� ��������� ����� � point1 �� ����� �� ���������
// ����� � point2
// ����������: -1, ���� ���� ������
//              0, ��� ������

_NETIMP long int WINAPI onSeekPathByPointExGraph(HMAP hmap, HGRAPH hgraph, HOBJ info,
                                         TASKPARMEX *parm, DOUBLEPOINT *point1,
                                         DOUBLEPOINT *point2, HSELECT select);

// �������� ���������� ��� ��������
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// infobegin - ��������� ����(������������� ������� ����� � ������)
// infoend - �������� ����(������������� ������� ����� � ������)
// ����������: ���������� ��� �������� �� infobegin �� infoend

_NETIMP long int WINAPI onGetCountRib(HMAP hmap, HGRAPH hgraph,
                                      HOBJ infobegin, HOBJ infoend);

// �������� ������ ������� ��� �������� �� infobegin �� infoend
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// infobegin - ��������� ����(������������� ������� ����� � ������)
// infoend - �������� ����(������������� ������� ����� � ������)
// arrayrib - ����� ������� ��� ������� ���,  ������ ������� ����� count
// count - ���������� ���, �.�. �������� �������� onGetCountRib(...)
// ��� ������ ���������� 0

_NETIMP long int WINAPI onGetArrayRib(HMAP hmap, HGRAPH hgraph,
                                      HOBJ infobegin, HOBJ infoend,
                                      long int *arrayrib, long int count);

// ���������� � ���� �����, ������������� �� ���������� ����� ��������� ��
// ���������� ���� (���������� ����� �����������)
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// info -  ���� ���� (������������� ������� ����� � ������)
// distance - ���������� � ������
// �� ���������������� ����� ����� �������� �����, �������������  �� ����������,
// ����� distance �� info
// ����� ���������� �������� ������������ �������� mapTotalSeekObjectCount(seekapi.h)
// �������� ������������� ������� ����� ��������� ������� mapTotalSeekObject(seekapi.h)
// ��� ������ ���������� 0

_NETIMP long int WINAPI onDistFromKnotGraph(HMAP hmap, HGRAPH hgraph, TASKPARMEX *parm,
                                    HOBJ info, double distance);

// ���������� � ���� �����, ������������� �� ���������� ����� ��������� ��
// ���������� ���� (���������� ����� �����������)
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// select - �������� ������� ������, �������������� ��������� ��������
// mapCreateSiteSelectContext(...), ��� ���������� ����������� (� select ������������
// ����, ������� ���������� ���� �����������)
// info -  ���� ���� (������������� ������� ����� � ������)
// distance - ���������� � ������
// ��� ������ ���������� 0

_NETIMP long int WINAPI onDistFromKnotGraphEx(HMAP hmap, HGRAPH hgraph, HSELECT select,
                                      HOBJ info, double distance);

// ���������� ������������ ���� ����� ������� (������ ����)
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// parm - �������� ���������� ������ (��.maptype.h)
// array - ����� ������� ��������� ������� �����,
//         ������ ������� ����� count
// count - ���������� ����� ��� ���������� ������������ ����
// ������� ������������ �� ��������� � ������ ����� ����
// � ������� ���������� ������ "��������� ���������� ������������ ����", � �������
// ��������������� ����� ���������� (����� ��� �����,� ��������� ������ �����
// ������ ����� ��������� "��������") � ������ �� ���������� �����
// �� ��������� ������ ������� �������� �������������� ������ "������� ������ �����",
// � ������� ������������ ������ ����� � ��� �������, � ������� ���� ����������� �� ��� ���������,
// ������������� �������� ����� �������� ����� �����, ����� ����� ����.
// ��� ������ ���������� 0

_NETIMP long int WINAPI onMinimalPathGraph(HMAP hmap, HGRAPH hgraph, TASKPARMEX *parm,
                                   DOUBLEPOINT *arraypoint, long int count);

// ���������� ������������ ���� ����� ������� (���������� ������������ �� tempsite)
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// parm - �������� ���������� ������ (��.maptype.h)
// tempsite - �� ������������ (����� ���� ����� 0)
// array - ����� ������� ��������� (� ������ �� ���������) ������� �����,
//         ������ ������� ����� count
// count - ���������� ����� ��� ���������� ������������ ����
// ������� ������������ �� ��������� � ������ ����� ����
// � ������� ���������� ������ "��������� ���������� ������������ ����", � �������
// ��������������� ����� ���������� (����� ��� �����,� ��������� ������ �����
// ������ ����� ��������� "��������") � ������ �� ���������� �����
// �� ��������� ������ ������� �������� �������������� ������ "������� ������ �����",
// � ������� ������������ ������ ����� � ��� �������, � ������� ���� ����������� �� ��� ���������,
// ������������� �������� ����� �������� ����� �����, ����� ����� ����.
// ��� ������ ���������� 0

_NETIMP long int WINAPI onMinimalPathSiteGraph(HMAP hmap,HGRAPH hgraph, TASKPARMEX *parm,
                                       HSITE tempsite, DOUBLEPOINT *arraypoint,
                                       long int count);

// ���������� ������������ ���� ����� ������� (������ ����)
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraph(...)
// parm - �������� ���������� ������ (��.maptype.h)
// arraypoint - ����� ������� ��������� (� ������)  ������� �����,
//              ������ ������� ����� count
// arraynumber - ����� ������� � �������� ����� (��� �����������),
//               ������ ������� ����� count
// count - ���������� ����� ��� ���������� ������������ ����
// ������������� �������� ����������� ������
// flagreturn - ���� �������� � ������ ����� (0 - �� ������������, 1 - ������������)
// flagcalc - ����� ������� (0 - �� �����, 1- �� �������)
// ������� ������������ �� ��������� � ������ ����� ����
// � ������ arraynumber ����� �������� ������ �����, ������� ���������� ������� ������
// ���������� ����� ����� ����
// ��� ������ ���������� 0

_NETIMP double WINAPI onMinimalPathExGraph(HMAP hmap, HGRAPH hgraph, TASKPARMEX *parm,
                                           DOUBLEPOINT *arraypoint, long int *arraynumber,
                                           long int count, long int flagreturn, long int flagcalc);

// ���������� ������������ ���� ����� ������� (������ ����)
// hmap - ������������� �������� ��������� �����
// hgraph - ������������� ����� ����, �������������� ������ ���� ������ ��������
// onOpenGraphEx(...)
// info - ������������� ������� � ������,
//        �������������� ���������� �������� mapCreateObject()
//        ��� mapCreateSiteObject(),
//        � ������� ����� �������� ��������� - ����������� ����
// arraypoint - ����� ������� ��������� (� ������)  ������� �����,
//              ������ ������� ����� count
// arraynumber - ����� ������� � �������� ����� (��� �����������),
//               ������ ������� ����� count
// count - ���������� ����� ��� ���������� ������������ ����
// ������������� �������� ����������� ������
// flagreturn - ���� �������� � ������ ����� (0 - �� ������������, 1 - ������������)
// flagcalc - ����� ������� (0 - �� �����, 1- �� �������)
// ������� ������������ �� ��������� � ������ ����� ����
// � ������ arraynumber ����� �������� ������ �����, ������� ���������� ������� ������
// ��� ������ ���������� 0

_NETIMP long int WINAPI onMinimalPathExGraphEx(HMAP hmap, HGRAPH hgraph, HOBJ info,
                                     DOUBLEPOINT *arraypoint, long int *arraynumber,
                                     long int count, long int flagreturn, long int flagcalc);

} // extern "C"


#endif  // NETAPI_H
