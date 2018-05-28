/****** MTDAPI.H ***************  Gorbunov A.V.  ****** 16/08/16 ***
******* MTDAPI.H ***************  Shabakov D.A.  ****** 16/04/13 ***
******* MTDAPI.H ***************  Belenkov O.V.  ****** 11/09/16 ***
******* MTDAPI.H ***************  Savelov A.S.   ****** 18/05/15 ***
******  MTDAPI.H ***************  Konon V.N.     ****** 30/06/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*          ОПИСАНИЕ ФУНКЦИЙ ДОСТУПА К МАТРИЦЕ ТОЧЕК (MTD)          *
*                                                                  *
********************************************************************
*                                                                  *
*                 ИМПОРТИРОВАНИЕ ФУНКЦИЙ :                         *
*                                                                  *
*                                                                  *
*    // Загрузка библиотеки                                        *
*                                                                  *
*    HINSTANCE libInst = ::LoadLibrary("gisacces.dll");            *
*                                                                  *
*    // Вызов функции                                              *
*                                                                  *
*    HMAP (WINAPI * lpfn_OpenMap)(const char*, long int);          *
*    (FARPROC)lpfn_OpenMap = GetProcAddress(libInst, "OpenMap");   *
*    HMAP hMap = (*lpfn_OpenMap)("Noginsk.map",0);                 *
*                                                                  *
*    // Выгрузка библиотеки                                        *
*                                                                  *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/

#ifndef MTDAPI_H
#define MTDAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // Описание структур интерфейса MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

#ifndef MTLAPI_H
  #include "mtlapi.h"
#endif


//  Параметры создаваемого MTD-файла
//------------------------------------------------------------------------------
#define POINTSFORELEMENT 32  // Кол-во точек на элемент
#define BLOCKSIDE 32         // Сторона блока элементов
#define BLOCKMTDFACTOR 8     // Сторона блока точек = 4 элемента (BLOCKSIDE / BLOCKMTDFACTOR)

// Блок точек = (4 * 4) = 16 эл-тов ~= POINTSFORELEMENT * 16 ~= 32 * 16 ~= 512 точек
//------------------------------------------------------------------------------


 // Точка MTD-модели

 typedef struct XYZC  // Размер структуры 32 байта
 {
   double    X;  // Координаты точки
   double    Y;
   double    Z;  // Высота точки
   long int  C;  // Код точки
   long int  Free;

   void operator = (XYZC p) { X = p.X;  Y = p.Y;  Z = p.Z; C = p.C; }
 }
   XYZC;

 // Точка MTD-модели с данными из LAS-файла            27/08/09

 typedef struct XYZCLAS             // Размер структуры 80 байт
 {
   double    X;                     // Координаты точки
   double    Y;
   double    Z;                     // Высота точки

   long int  C;                     // Код точки
   long int  ReturnNumber;          // Номер возврата

   long int  NumberOfReturns;       // Кол-во возвратов данного импульса
   long int  ScanDirectionFlag;     // Флаг направления сканирования

   long int  EdgeOfFlightLineFlag;  // Флаг "край линии полёта"
   long int  Classification;        // Классификация

   long int  ScanAngleRank;         // Ранг угла сканирования (от -90 до +90)
   long int  FileMarker;            // Маркер файла - для объединения в единый файл LAS файлов

   long int  Intensity;             // Интенсивность возврата
   long int  UserBits;              // Поле битов пользователя

   long int  Free1;                 // Резерв
   long int  Free2;

   long int  Free3;                 // Резерв
   long int  Free4;

   void operator = (XYZCLAS p)
   {
     X = p.X;  Y = p.Y;  Z = p.Z; C = p.C;
     ReturnNumber = p.ReturnNumber;
     NumberOfReturns = p.NumberOfReturns;
     ScanDirectionFlag = p.ScanDirectionFlag;
     EdgeOfFlightLineFlag = p.EdgeOfFlightLineFlag;
     Classification = p.Classification;
     ScanAngleRank = p.ScanAngleRank;
     FileMarker = p.FileMarker;
     Intensity = p.Intensity;
     UserBits = p.UserBits;
   }
 }
   XYZCLAS;




//-----------------------------------------------------------
// Структура точки (внутреннее представление в блоке файла)
// при загрузке MTD из TXT-файла (16 байт)
//-----------------------------------------------------------
typedef struct
{
  unsigned long int X;  // Координаты точки           // 12/05/11  "unsigned"
  unsigned long int Y;
  unsigned long int H;
  unsigned long int C;  // Код точки
}
  MTDXYHC;

//-----------------------------------
//  Битовые поля LAS-точки (4 байта)
//-----------------------------------
typedef struct
{
  unsigned ReturnNumber :3;           // The return number - номер возврата
  unsigned NumberOfReturns :3;       // The number of returns for that shot - кол-во возвратов данного импульса
  unsigned ScanDirectionFlag :1;     // The scan direction - флаг направления сканирования
  unsigned EdgeOfFlightLineFlag :1;  // Edge of scan flag - флаг "край линии полёта"
  unsigned Classification :8;        // Классификация
  signed   ScanAngleRank :8;         // Ранг угла сканирования (-90 to +90) - Left side
  unsigned FileMarker :8;            // Маркер файла - для объединения в единый файл LAS файлов
}
  LASINFO;

//-----------------------------------------------------------
// Структура точки (внутреннее представление в блоке файла)
// при загрузке MTD из LAS-файла (24 байта)
//-----------------------------------------------------------
typedef struct
{
  long int X;  // Координаты точки
  long int Y;
  long int H;
  long int C;  // Код точки

  LASINFO LasInfo;  // Битовые поля точки (4 байта)

  unsigned short int Intensity;  // Интенсивность возврата
  unsigned short int UserBits;   // Поле битов пользователя
}
  MTDXYHCLAS;
   

extern "C"
{
  // Открыть матричные данные
  // Возвращает идентификатор открытой матричной карты (TMapAccess*)
  // При ошибке возвращает ноль

  _MAPIMP HMAP _MAPAPI mapOpenMtd(const char * mtrname, long int mode = 0);
  _MAPIMP HMAP _MAPAPI mapOpenMtdUn(const WCHAR *mtrname, long int mode = 0);  // 28/01/14


  // Открыть матричные данные в заданном районе работ
  // (добавить в цепочку матриц)
  // Возвращает номер файла в цепочке матриц
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapOpenMtdForMap(HMAP hMap, const char * mtrname, long int mode);
  _MAPIMP long int _MAPAPI mapOpenMtdForMapUn(HMAP hMap, const WCHAR * mtrname, long int mode);  // 28/01/14



  // Создать матричную карту
  // Возвращает идентификатор открытой матричной карты (TMapAccess*)
  // Структурa BUILDMTL описанa в mtlapi.h
  // Структурa MTRPROJECTIONDATA описанa в maptype.h
  // maxPointCount - максимальное кол-во точек в блоке матрицы
  // При ошибке возвращает ноль

  _MAPIMP HMAP _MAPAPI mapCreateMtd(const char * mtrname,
                            BUILDMTL * mtrparm,
                            long int maxPointCount,
                            MTRPROJECTIONDATA * mtrprojectiondata);

  _MAPIMP HMAP _MAPAPI mapCreateMtdUn(const WCHAR * mtrname,          // 28/01/14
                            BUILDMTL * mtrparm,
                            long int maxPointCount,
                            MTRPROJECTIONDATA * mtrprojectiondata);

  // Создать матричную карту
  // Возвращает идентификатор открытой матричной карты (TMapAccess*)
  // Структурa BUILDMTL описанa в mtlapi.h
  // blockpointcount - массив количеств точек в блоках матрицы
  // Структурa MTRPROJECTIONDATA описанa в maptype.h
  // При ошибке возвращает ноль

  _MAPIMP HMAP _MAPAPI mapCreateMtdByBlockPointCount(const char * mtrname,
                                             BUILDMTL * mtrparm,
                                             int* blockpointcount,              // 18/05/15 Савелов
                                             MTRPROJECTIONDATA * mtrprojectiondata);

  _MAPIMP HMAP _MAPAPI mapCreateMtdByBlockPointCountUn(const WCHAR * mtrname,   // 28/01/14
                                             BUILDMTL * mtrparm,
                                             int* blockpointcount,              // 18/05/15 Савелов
                                             MTRPROJECTIONDATA * mtrprojectiondata);

  // Записать изменения матрицы в файл
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapSaveMtd(HMAP hMap, long int number);

  // Запросить признак редактируемости файла матрицы
  // number - номер файла в цепочке

  _MAPIMP long int _MAPAPI mapIsMtdEdit(HMAP hMap,long int number);

  // Закрыть матричные данные
  // number - номер закрываемой матрицы
  // если number == 0, закрываются все матрицы в окне

  _MAPIMP void _MAPAPI mapCloseMtd(HMAP hMap,long int number = 0);

  // Закрыть матричные данные в заданном районе работ
  // number - номер матричного файла в цепочке
  // Если number == 0, закрываются все матричные данные
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapCloseMtdForMap(HMAP hMap,
                                     long int number);

  // Запросить число открытых файлов матричных данных
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdCount(HMAP hMap);

  // Установить в качестве текущей матрицу с номером в цепочке "number"
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapActiveMtd(HMAP hMap, long int number);


  // Установить диапазон отображаемых элементов матрицы
  // number   - номер матрицы в цепочке
  // minvalue - минимальное значение отображаемого элемента
  //            в единицах матрицы
  // maxvalue - максимальное значение отображаемого элемента
  //            в единицах матрицы
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetMtdShowRange(HMAP hMap,
                                      long int number,
                                      double minvalue,
                                      double maxvalue);

  // Установить плотность точек матрицы
  // number - номер матрицы в цепочке
  // density - значение плотности точек (кол-во точек на кв.метр)
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetMtdDensity(HMAP hMap,
                                    long int number,
                                    double density);

  // Запросить плотность точек матрицы
  // number - номер матрицы в цепочке
  // Возвращает значение плотности точек (кол-во точек на кв.метр)
  // При ошибке возвращает ERRORHEIGHT

  _MAPIMP double _MAPAPI mapGetMtdDensity(HMAP hMap,    // 16/08/16
                                    long int number);

  // Вывод точки "dot" в матрицу
  // number - номер файла в цепочке
  // Структура XYZC описана в данном файле
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapPutMtdDot(HMAP hMap, long int number, XYZC* dot);

  // Вывод точки "dot" в матрицу
  // number - номер файла в цепочке
  // Структура XYZCLAS (точка MTD-модели с данными из LAS-файла)
  // описана в данном файле
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapPutMtdDotLas(HMAP hMap, long int number, XYZCLAS* dot);  // 27/08/09

  // Занесение значения абсолютной высоты в элемент матрицы,
  // соответствующий заданной точке.
  // number - номер матрицы в цепочке.
  // Координаты точки (x,y) и значение высоты (h) задаются в метрах
  // в системе координат векторной карты.
  // В случае ошибки возвращает ноль.

  _MAPIMP long int _MAPAPI mapPutMtdElementHeight(HMAP hMap,long int number,
                                          double x, double y, double h);

  // Занести код слоя в элемент матрицы, соответствующий заданной точке.
  // number - номер матрицы в цепочке.
  // Координаты точки (x,y) задаются в метрах в системе координат векторной карты.
  // code - код слоя
  // В случае ошибки возвращает 0.

  _MAPIMP long int _MAPAPI mapPutMtdElementCode(HMAP hMap, long int number,       // 10/06/08
                                        double x, double y, long int code);

  // Запросить код слоя из элемента матрицы, соответствующего заданной точке.
  // number - номер матрицы в цепочке.
  // Координаты точки (x,y) задаются в метрах в системе координат векторной карты.
  // Возвращает код слоя
  // В случае ошибки возвращает 0.

  _MAPIMP long int _MAPAPI mapGetMtdElementCode(HMAP hMap, long int number,
                                            double x, double y);

  /*********************************************************
  *                                                        *
  *           ЗАПРОС ДАННЫХ ИЗ МАТРИЦЫ ТОЧЕК               *
  *                                                        *
  *********************************************************/

  // Запросить имя файла матричных данных
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP const char * _MAPAPI mapGetMtdName(HMAP hMap,long int number);

  // Запросить имя файла матричных данных
  // hMap - идентификатор открытой основной векторной карты
  // number - номер файла в цепочке
  // name - адрес строки для размещения результата
  // size - размер строки
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdNameUn(HMAP hMap,long int number,  // 28/01/14
                                           WCHAR *name, long int size);

  // Запросить номер матрицы в цепочке по имени файла
  // name - имя файла матрицы
  // В цепочке номера матриц начинаются с 1
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdNumberByName(HMAP hMap, const char * name);
  _MAPIMP long int _MAPAPI mapGetMtdNumberByNameUn(HMAP hMap, const WCHAR * name);  // 28/01/14


  // Запросить длину файла матричных данных
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP double _MAPAPI mapGetMtdFileLength(HMAP hMap,long int number);

  // Запросить количество точек в матрице
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP unsigned long _MAPAPI mapGetMtdPointCount(HMAP hMap,long int number);

  // Запросить данные о проекции матрицы
  // hMap   - идентификатор открытой основной векторной карты
  // number - номер файла в цепочке
  // mapregister - адрес структуры, в которой будут размещены
  // данные о проекции
  // Структурa MAPREGISTEREX описанa в mapcreat.h
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdProjectionData(HMAP hMap, long int number,
                                           MAPREGISTEREX* mapregister);

  // Запросить данные о проекции матрицы
  // hMap   - идентификатор открытой основной векторной карты
  // number - номер файла в цепочке
  // mapregister, datumparam, ellipsoidparam - адреса структур, в которых будут размещены
  // Структуры MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM описаны в mapcreat.h
  // ttype  - тип локального преобразования координат (см. TRANSFORMTYPE в mapcreat.h) или 0
  // tparm - параметры локального преобразования координат (см. mapcreat.h)
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdProjectionDataPro(HMAP hMap, long int number,   // 11/09/16
                                                      MAPREGISTEREX  *mapregister,
                                                      DATUMPARAM     *datumparam,
                                                      ELLIPSOIDPARAM *ellipsoidparam,
                                                      long int * ttype,
                                                      LOCALTRANSFORM * tparm);

  _MAPIMP long int _MAPAPI mapGetMtdProjectionDataEx(HMAP hMap, long int number,
                                                   MAPREGISTEREX  *mapregister,
                                                   DATUMPARAM     *datumparam,
                                                   ELLIPSOIDPARAM *ellipsoidparam);

  // Установить данные о проекции матрицы
  // number - номер файла в цепочке
  // mapregister - адрес структуры, содержащей данные о проекции
  // Структурa MAPREGISTEREX описанa в mapcreat.h
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapSetMtdProjectionData(HMAP hMap,long int number,
                                           MAPREGISTEREX* mapregister);

  // Установить данные о проекции матрицы
  // hMap   - идентификатор открытой основной векторной карты
  // number - номер матрицы в цепочке.
  // mapregister, datumparam, ellipsoidparam - адреса структур, содержащих данные о проекции
  // Структуры MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM описаны в mapcreat.h
  // ttype  - тип локального преобразования координат (см. TRANSFORMTYPE в mapcreat.h) или 0
  // tparm - параметры локального преобразования координат (см. mapcreat.h)
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapSetMtdProjectionDataPro(HMAP hMap, long int number,       // 11/09/16
                                                    MAPREGISTEREX  *mapregister,
                                                    DATUMPARAM     *datumparam,
                                                    ELLIPSOIDPARAM *ellipsoidparam,
                                                    long int ttype,
                                                    LOCALTRANSFORM * tparm);

_MAPIMP long int _MAPAPI mapSetMtdProjectionDataEx(HMAP hMap, long int number,
                                                   MAPREGISTEREX  *mapregister,
                                                   DATUMPARAM     *datumparam,
                                                   ELLIPSOIDPARAM *ellipsoidparam);

  // Запросить описание файла матричных данных
  // number - номер файла в цепочке
  // describe - адрес структуры, в которой будет размещено
  // описание матрицы
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdDescribe(HMAP hMap,long int number,
                                     MTLDESCRIBE * describe);

  _MAPIMP long int _MAPAPI mapGetMtdDescribeUn(HMAP hMap,long int number,  // 03/04/14
                                     MTLDESCRIBEUN * describe);

  // Запросить число строк блоков матрицы
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdBlockRow(HMAP hMap,long int number);

  // Запросить число столбцов блоков матрицы
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdBlockColumn(HMAP hMap,long int number);

  // Запросить размер блока матрицы
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdBlockSize(HMAP hMap,long int number);

  // Запросить вертикальный размер блока матрицы в элементах
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdBlockSide(HMAP hMap,long int number);

  // Запросить блок матрицы по номеру строки и столбца
  // Отсчет строк и столбцов с верхнего левого блока
  // Блоки последнего ряда могут иметь усеченный размер
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP char * _MAPAPI mapGetMtdBlockAddress(HMAP hMap,long int number,
                                       long int row,
                                       long int column);

  // Запросить число строк элементов в матрице
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdElementRow(HMAP hMap,long int number);

  // Запросить число столбцов элементов в матрице
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdElementColumn(HMAP hMap,long int number);

  // Запросить масштаб матрицы
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdScale(HMAP hMap,long int number);

  // Установить масштаб матрицы
  // number - номер файла в цепочке
  // scale  - знаменатель масштаба
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapSetMtdScale(HMAP hMap,long int number,double scale);

  // Выбор значения абсолютной высоты в заданной точке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetMtdElementHeight(HMAP hMap,double x,double y);


  // Вычисление значения абсолютной высоты в заданной точке
  // с использованием всех MTD-моделей цепочки.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetMtdHeight(HMAP hMap,double x,double y);  // 26/02/14

  // Выбор значения абсолютной высоты в заданной точке из матрицы
  // с номером number в цепочке.
  // number - номер матрицы в цепочке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetElementHeightOfMtd(HMAP hMap,long int number,double x,double y);

  // Запросить значения масштаба нижней и верхней границ видимости матрицы
  // number - номер файла в цепочке
  // По адресу bottomScale записывается знаменатель масштаба нижней границы видимости матрицы
  // По адресу topScale записывается знаменатель масштаба верхней границы видимости матрицы
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetMtdRangeScaleVisible(HMAP hMap, long int number, long int *bottomScale, long int *topScale);

  // Установить значения масштаба нижней и верхней границ видимости матрицы
  // number     - номер файла в цепочке
  // bottomScale   - знаменатель масштаба нижней границы видимости матрицы
  // topScale   - знаменатель масштаба верхней границы видимости матрицы
  //              bottomScale <= topScale, иначе возвращает 0
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetMtdRangeScaleVisible(HMAP hMap, long int number, long int bottomScale, long int topScale);

  // Установка значения цвета слоя layernumber.
  // number - номер матрицы в цепочке
  // В случае ошибки возвращает ноль.

  _MAPIMP long int _MAPAPI mapSetMtdLayerColor(HMAP hMap,long int number,
                                       long int layernumber,
                                       COLORREF layercolor);

  // Установка значения цвета кода точек codenumber.
  // number - номер матрицы в цепочке
  // В случае ошибки возвращает ноль.

  _MAPIMP long int _MAPAPI mapSetMtdCodeColor(HMAP hMap,long int number,
                                      long int codenumber,
                                      COLORREF codecolor);

  // Установка количества точек кода codenumber.
  // number - номер матрицы в цепочке
  // В случае ошибки возвращает ноль.

  _MAPIMP long int _MAPAPI mapSetMtdCodePointCount(HMAP hMap,long int number,
                                           long int codenumber,
                                           long int pointcount);

  // Установка значения флага кода точек codenumber.
  // number - номер матрицы в цепочке
  // В случае ошибки возвращает ноль.

  _MAPIMP long int _MAPAPI mapSetMtdCodeFlag(HMAP hMap,long int number,
                                     long int codenumber,
                                     long int codeflag);

  // Установка имени codename кода точек codenumber.
  // number - номер матрицы в цепочке
  // В случае ошибки возвращает ноль.

  _MAPIMP char* _MAPAPI mapSetMtdCodeName(HMAP hMap,long int number,
                                     long int codenumber,
                                     char* codename);

  // Запросить формат точки MTD-модели (внутреннее представление в блоке файла)
  // number - номер файла в цепочке
  // Возвращаемые значения:  0 - структура точки MTDXYHC (16 байт)
  //                         1 - структура точки MTDXYHCLAS (24 байта)
  // Структуры описаны в данном файле
  // При ошибке возвращает -1

  _MAPIMP long int _MAPAPI mapGetMtdPointFormat(HMAP hMap, long int number);  // 02/04/13

  // Запросить число строк блоков точек MTD-модели
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdPointBlockRow(HMAP hMap, long int number);  // 02/04/13

  // Запросить число столбцов блоков точек MTD-модели
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetMtdPointBlockColumn(HMAP hMap, long int number);  // 02/04/13

  // Запросить из MTD-модели блок точек формата MTDXYHC по номеру строки и столбца блока
  // Отсчет строк и столбцов с верхнего левого блока
  // number - номер файла в цепочке
  // Возвращает адрес массива структур точек MTDXYHC
  // При ошибке возвращает ноль

  _MAPIMP MTDXYHC * _MAPAPI mapGetMtdPointBlockAddress(HMAP hMap, long int number,  // 02/04/13
                                               long int row,
                                               long int column);

  // Запросить из MTD-модели блок точек формата MTDXYHCLAS по номеру строки и столбца блока
  // Отсчет строк и столбцов с верхнего левого блока
  // number - номер файла в цепочке
  // Возвращает адрес массива структур точек MTDXYHCLAS
  // При ошибке возвращает ноль

  _MAPIMP MTDXYHCLAS * _MAPAPI mapGetMtdPointBlockLasAddress(HMAP hMap, long int number,  // 02/04/13
                                                     long int row,
                                                     long int column);



  /*********************************************************
  *                                                        *
  *        УПРАВЛЕНИЕ ОТОБРАЖЕНИЕМ МАТРИЦЫ ТОЧЕК           *
  *                                                        *
  *********************************************************/

  // Запросить/Установить степень видимости матрицы
  //  number - номер файла в цепочке
  //  view = 0 - не виден
  //  view = 1 - полная
  //  view = 2 - насыщенная
  //  view = 3 - полупрозрачная
  //  view = 4 - средняя
  //  view = 5 - прозрачная
  // При ошибке возвращает 0
  
  _MAPIMP long int _MAPAPI mapGetMtdView(HMAP hMap,long int number);
  _MAPIMP long int _MAPAPI mapSetMtdView(HMAP hMap,long int number,
                                           long int view);

  // Запросить/Установить порядок отображения матрицы
  //  (0 - под картой, 1 - над картой)
  // При ошибке возвращает 0
  
  _MAPIMP long int _MAPAPI mapGetMtdViewOrder(HMAP hMap, long int number);
  _MAPIMP long int _MAPAPI mapSetMtdViewOrder(HMAP hMap, long int number,long int order);

  // Определение способа отображения матрицы(относительно рамки)
  // Возвращает 1 - при отображении матрицы по рамке
  //            0 - при отображении матрицы без учета рамки
  // При ошибке возвращает -1

  _MAPIMP long int _MAPAPI mapCheckShowMtdByBorder(HMAP hMap,long int number);

  // Поменять очередность отображения матриц в цепочке
  //   oldNumber - номер файла в цепочке
  //   newNumber - устанавливаемый номер файла в цепочке
  //  При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapChangeOrderMtdShow(HMAP hMap, long int oldNumber,
                                        long int newNumber);

  // Запросить габариты модели в районе (метры)                                      
  //  При ошибке возвращает 0
  
  _MAPIMP long int _MAPAPI mapGetMtdFrame(HMAP hMap, long int number, DFRAME * dframe);  

  // Запрос минимального и максимального значения высоты поверхности (метры)
  //  При ошибке возвращает 0
    
  _MAPIMP long int _MAPAPI mapGetMtdHeightValue(HMAP hMap, long int number, 
                                                double * minvalue, double * maxvalue);                                       

}

#endif // MTDAPI_H
