/******  TRIANAPI.H  **********  Demidenko A.G. ******  10/12/2010 *
*******  TRIANAPI.H  **********  Shishkova L.A. ******  12/05/2003 *
*******  TRIANAPI.H  **********  Tarakanova I.R.******  27/06/2005 *
*******  TRIANAPI.H  **********  Gorbunov A.V.  ******  13/01/2012 *
*******  TRIANAPI.H  **********  Borzov A.U.    ******  14/09/2010 *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*                ������� ���������� GISMATH.DLL                    *
*                                                                  *
*******************************************************************/

#include "mapsyst.h"
#include "maptype.h"
#include "tritype.h"   //12/05/03

#ifndef TRIANAPI_H
#define TRIANAPI_H

extern "C"
{

// ������� ��������� ���������� ������������ ������ �� ������� �����.
// ������� ���������: points - ��������� �� ������ �����, ��� ����������
// ������������, � ������� �� ������ ���� ������������� �����;
// count- ���������� ����� �� ������� �������;
// frame - ��������� �� ������, ��������� �������������� ������ ����� 
// ������������, ��� �������� ������������ � ��������� �������
// ����� ������� ������ CreateDeloneTtiangle ������ ���� �����
// DeleteDeloneTtiangle
// ����� ����� ����� (����� � �������� �������) ������ ���� ������ ����,
// ����� ����������� ���������� ����� ������������ (�������� �������������)
// ���������� ��������� �� ����������� ������������

// ������ ������� �������� ������������
// �� ��������� ����������� �������� �����
HTRIANG
CreateDeloneTriangle(HWND parent,
                    XYDOUBLE* points,
                    unsigned long count,
                    HOBJ frame=0);

// �������� ������� ������������ � ��������������� ����������� �����
HTRIANG
CreateDeloneTriangleSort(HWND parent,
                    XYDOUBLE* Points,
                    unsigned long count,
                    HOBJ frame=0);

// ������ ������� �������� ������������.
// �� ���������� ����������� �������� �����
HTRIANG
CreateDeloneTriangleXYH(HWND parent,
                     XYHDOUBLE* points,
                     unsigned long count,
                     HOBJ frame=0);

// �������� ������� ������������ � ������ ����� �����
// � � ��������������� ����������� �����
HTRIANG
CreateDeloneTriangleXYHSort(HWND parent,
                     XYHDOUBLE* Points,
                     unsigned long count,
                     HOBJ frame=0);

// ���������� ������������ (������� ������������� � ������� ����)
// �� ������� ���������� �����
// parent - ������������� ���� �������, �������� ����������
// ��������� � ���� �������� :
//   0x3000 - ��������� � �������� ����������� ����� (� WPARAM),
//   ���� ������� ������ ���� ������������� ��������, � �����
//   ������ ��������� �������� 0x3000.
// ���� parent = 0 - ��������� �� ����������.
// points - ������ �������� ����� (��������� VERTEX ������� � tritype.h)
//   ������ ������� �������� ����� �� ������ ������������� �� ��������� �������������
//   ����������� ������������ (�� �������� ������������ - DeleteDeloneTriangle)
// count - ���������� ����� � �������� �������
// indexEdge - ���� ���������� ���������� ���� �����������
// ������������ (0 - �� ���������, 1 - ���������).
// ���� indexEdge = 0, �� ���������� ������������ �����������
// �������, �� ������ ���� �� �������� ������ �� ������������ - ����
// LTri,RTri ��������� EDGE (��������� EDGE ������� � tritype.h)
// frame - ������������� ���������� ������� �����, ���������������
// ������������. ���������� ��������� �� ����������� ������������
// (HTRIANG ������ � tritype.h)
// � ������ ������ ���������� 0
HTRIANG
BuildDeloneTriangulation(HWND parent,
                         VERTEX* points,
                         unsigned long count,
                         long int indexEdge = 1,
                         HOBJ frame = 0);


// ���������� ������������ (������� ����)
// �� ������� ���������� �����
// parent - ������������� ���� �������, �������� ����������
// ��������� � ���� �������� :
//   0x3000 - ��������� � �������� ����������� ����� (� WPARAM),
//   ���� ������� ������ ���� ������������� ��������, � �����
//   ������ ��������� �������� 0x3000.
// ���� parent = 0 - ��������� �� ����������.
// points - ������ �������� ����� (��������� VERTEX ������� � tritype.h)
// count - ���������� ����� � �������� �������
// frame - ������������� ���������� ������� �����, ���������������
// ������������. ���������� ��������� �� ����������� ������������
// (HTRIANG ������ � tritype.h)
// � ������ ������ ���������� 0

HTRIANG
BuildDeloneEdges(HWND parent,
                 VERTEX* points,
                 unsigned long count,
                 HOBJ frame = 0);


// �������� ������� ������������
// HTRIANG htriangle - ��������� �� ����������� ������������
long int
DeleteDeloneTriangle(HTRIANG htriangle);

// �������� ����� ������������, �������� �����������  �����
// HTRIANG htriangle - ��������� �� ����������� ������������
// XYDOUBLE point - ���������� �����
// ��������� ������������� ���������� � 0.
// � ������ ������ ���������� -1.
long int
GetNumberTriangle(HTRIANG htriangle, XYDOUBLE point);

// �������� ����� ������������, �������� �����������  �����
// HTRIANG htriangle - ��������� �� ����������� ������������
//   (������������ ������ ���� ��������� �������� BuildDeloneTriangulation)
// XYDOUBLE point - ���������� �����
// ��������� ������������� ���������� � 0.
// � ������ ������ ���������� -1.
long int
GetNumberTriangleAdd(HTRIANG htriangle, XYDOUBLE point);  // 23/12/05

// �������� ���������� � ������������ �� ��� ������ � �������
// HTRIANG htriangle - ��������� �� ����������� ������������
// TRIANGLE triangle - ���������� � ������������ � ������� number
// long int number - ����� ������������ � ������� ������������
// ��������� ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int
GetTriangle(HTRIANG htriangle, TRIANGLE* triangle, long int number);

// �������� ���������� � ����� AB,BC,CA ������������ numTriangle
// HTRIANG htriangle - ��������� �� ����������� ������������
// edge - ���������� � ����� AB,BC,CA ������������ numTriangle
// (��������� EDGE ������� � tritype.h)
// � ������ ������ ���������� 0.
long int
GetTriangleEdgeAB(HTRIANG htriangle, EDGE* edge, long int numTriangle);

long int
GetTriangleEdgeBC(HTRIANG htriangle, EDGE* edge, long int numTriangle);

long int
GetTriangleEdgeCA(HTRIANG htriangle, EDGE* edge, long int numTriangle);

// �������� ���������� � ����� �� ��� ������ � �������
// HTRIANG htriangle - ��������� �� ����������� ������������
// EDGE edge - ���������� � ����� � ������� number
// long int number - ����� ������������ � ������� ������������
// ��������� ����� ���������� � 0.
// � ������ ������ ���������� 0.
long int
GetEdge(HTRIANG htriangle, EDGE* edge, long int number);


// �������� ���������� � ������� ������������ �� �� ������ � �������
// HTRIANG htriangle - ��������� �� ����������� ������������
// XYDOUBLE vertex - ���������� � ������� ������������ � ������� number
// long int number - ����� ������� ������������ � ������� �������� �����
// ��������� ������ ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int
GetVertex(HTRIANG htriangle, XYDOUBLE* vertex, long int number);

// �������� ���������� � ������� ������������ �� �� ������ � �������
// htriangle - ��������� �� ����������� ������������
// vertex - ���������� � ������� ������������ � ������� number
// (��������� VERTEX ������� � tritype.h)
// number - ����� ������� ������������ � ������� �������� �����
// ��������� ������ ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int
GetVertexXYH(HTRIANG htriangle, VERTEX* vertex, long int number);

// �������� ���������� � �������������� ������� ������������ (�������
// ����������) �� �� ������ � ������� �������� �����
// HTRIANG htriangle - ��������� �� ����������� ������������
// double heigth - �������� �������������� ������� ������������ � ������� number
// long int number - ����� ������� ������������ � ������� �������� �����
// ��������� ������ ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int
GetHeigth(HTRIANG htriangle, double* heigth, long int number);

// �������� ���������� � �������������� ������� ������������ (�������
// ����������) �� �� ������ � ������� �������� �����
// HTRIANG htriangle - ��������� �� ����������� ������������
//   (������������ ������ ���� ��������� �������� BuildDeloneTriangulation)
// double heigth - �������� �������������� ������� ������������ � ������� number
// long int number - ����� ������� ������������ � ������� �������� �����
// ��������� ������ ������������� ���������� � 0.
// � ������ ������ ���������� 0.
long int
GetHeigthAdd(HTRIANG htriangle, double* heigth, long int number);

// �������� ����� �������������.
// HTRIANG htriangle - ��������� �� ����������� ������������
// ���������� ����� ������������� � ������� ������������
// � ������ ������ ���������� 0.
long int
GetQuantTriangle(HTRIANG htriangle);

// �������� ����� ������.
// HTRIANG htriangle - ��������� �� ����������� ������������
// ���������� ����� ������ � ������� ������������
// � ������ ������ ���������� 0.
long int
GetQuantVertex(HTRIANG htriangle); 

// �������� ����� �����.
// HTRIANG htriangle - ��������� �� ����������� ������������
// ���������� ����� ����� � ������� ������������
// � ������ ������ ���������� 0.
long int
GetQuantEdges(HTRIANG htriangle);

// ��������� �������� ������������
// HTRIANG htriangle - ��������� �� ����������� ������������
// � ������ ������ ���������� 0.
long int
ThickenTriangle(HTRIANG htriangle);

// ��������� ���������� ������������
// HTRIANG htriangle - ��������� �� ����������� ������������
// � ������ ������ ���������� 0.
long int
FacrtorizationTriangle(HTRIANG htriangle);

// �������� �������� ���������� �����
// ���������� ���������� ����������� �����
long int GetControlTriangle(HTRIANG htriangle, int* control);


// ���������� � ������������ ����������� ����� (����� ��������)
// HTRIANG htriangle - ��������� �� ����������� ������������  27/06/05
// � ������ ������ ���������� 0.
long int
 AddBreakLinesInTriangle(HTRIANG htriangle,HOBJ info);

// ����������� ������������ � ������ ����������� �����    27/06/05
// HTRIANG htriangle - ��������� �� ����������� ������������
// � ������ ������ ���������� 0.
long int
 RebuildTriangle(HTRIANG htriangle,HOBJ info);

// �������� � ������ �������� ����� ����� ����������� �������� �������
// ����������� ����� info � ������ ����� ����������� ������������ htriangle
long int
 AddPointsByLine(HTRIANG htriangle, HOBJ info);

// ��������� ���� "����������� �����" ����� ������������ htriangle,
// ������� �� �������� ����������� ����� info
long int
 MarkEdgesByLine(HTRIANG htriangle, HOBJ info);

// ���������� ����������� ������������ ��� ��������� ������ ������������  //16/09/10
// � ������� �������� ����� (������� GetNumberTriangleAdd)
// HTRIANG htriangle - ��������� �� ����������� ������������
// (������������ ������ ���� ��������� �������� BuildDeloneTriangulation)
// ��� ��������� ������������ ������� ������ �������� ����������
// � ������ ������ ���������� 0.
long int IndexTriangles(HTRIANG htriangle);

// ����� ������������, ������� ������� ��������� �����
long int GetCountTriangleSummit(HTRIANG htriangle, long int summit);

// �������� ����� ������������ � ����� ������� ������������� �� ������ � ������
// number - ��������� ����� ������������ � ������� ��������� �������������
// ���������� ����� ������������ � ����� ������� �������������
long int GetNumberTriangleSummit(HTRIANG htriangle, long int number);

} // extern "C"
#endif




