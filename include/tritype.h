/******* TRITYPE.H ************* Demidenko A.G. ******  01/09/00 ***
******** TRITYPE.H ************* Belenkov O.V.  ******  19/01/01 ***
******** TRITYPE.H ************* Gorbunov A.V.  ******  12/01/12 ***
******** TRITYPE.H ************* Shabakov D.A.  ******  31/05/13 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2013              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*               ОПИСАНИЕ БАЗОВЫХ ТИПОВ ПЕРЕМЕННЫХ                  *
*                                                                  *
*******************************************************************/

#ifndef TRIANGLETYPE_H
#define TRIANGLETYPE_H

// Определяется экспорт/импорт классов и функций
#if defined(_DELONE_DLL)
  #define _DELONECLASS _export
#else
  #define _DELONECLASS _import
#endif

// Сообщение о проценте выполненных работ
#define IDC_PERCENT_DELONE     0x3000

#define TR_ONLY           0
#define TR_THICKEN        1
#define TR_FACTORIZATION  2

// МАКСМАЛЬНЫЙ РАЗМЕР МАССИВА ВЕРШИН
// #define VERTEXCOUNT     50000  // 29/12/05
// #define VERTEXCOUNT     100000  // 26/12/08
#define VERTEXCOUNT     1000000    // 12/01/12

// МАКСМАЛЬНЫЙ РАЗМЕР МАССИВА ТРЕУГОЛЬНИКОВ
// #define TRIANGLECOUNT  150000  // 29/12/05
// #define TRIANGLECOUNT  300000  // 26/12/08
#define TRIANGLECOUNT  3000000  // 12/01/12


// ИДЕНТИФИКАТОР ПОСТРОЕННОЙ ТРИАНГУЛЯЦИИ
// (Указатель на TConstTriangle)

#if defined(_M_X64) || defined(BUILD_DLL64)       // 31/05/13
typedef __int64  HTRIANG;
#else
typedef long int HTRIANG;
#endif


// СТРУКТУРА МАССИВА ТРЕУГОЛЬНИКОВ   (56 байт)

typedef struct
{
  long int A;         // Номера вершин треугольника
  long int B;
  long int C;

  long int EdgeAB;    // Номера рёбер треугольника
  long int EdgeBC;
  long int EdgeCA;

  long int NearAB;    // Номера соседних треугольников
  long int NearBC;
  long int NearCA;

  long int ParentAB;  // Принадлежность стороны базовой триангуляции (1-да, 0-нет)
  long int ParentBC;
  long int ParentCA;

  long int Cancel;    // Флаг удаления
  long int Reserve;
}
  TRIANGLE;


// СТРУКТУРА МАССИВА РЕБЕР   (32 байтa)

typedef struct
{
  long int A;       // Номера вершин ребра
  long int B;

  long int LTri;    // Номер левого треугольника
  long int RTri;    // Номер правого треугольника

  long int Live;    // Флаг - "живое" ребро (не все соседние рёбра найдены)
  long int Cancel;  // Флаг удаления

  long int Flag;    // Флаг :
                    //  0 - ребро не входит в состав
                    //      структурной линии,
                    //  1 - ребро входит в состав структурной
                    //      линии гладкого перегиба,
                    //  2 - ребро входит в состав структурной
                    //      линии негладкого перегиба,
                    //  3 - ребро входит в состав структурной
                    //      линии разрыва,
                    //  4 - ребро входит в состав границы
                    //      полигона построения триангуляции.
  long int Reserve;
}
  EDGE;


// СТРУКТУРА МАССИВА ВЕРШИН   (32 байтa)    

typedef struct
{
  double X;
  double Y;
  double H;

  long int Cancel;  // Флаг удаления
  long int Flag;    // Флаг : 0 - обычная вершина (точечный объект)
                    //        1 - вершина принадлежит структурной линии
                    //        2 - вершина принадлежит контуру площади заполнения
}
  VERTEX;

#endif  // TRIANGLETYPE_H

