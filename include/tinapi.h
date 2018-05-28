/****** TINAPI.H *************** Gorbunov A.V. ******** 03/04/14 ***
******* TINAPI.H *************** Shabakov D.A. ******** 21/07/16 ***
******* TINAPI.H *************** Dishlenko S.G.******** 31/03/15 ***
******* TINAPI.H *************** Konon V.N.    ******** 30/06/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                          TIN-МОДЕЛЬ                              *
*                                                                  *
*  ПАРАМЕТРЫ СОЗДАНИЯ                      (TINBUILD)              *
*  ОПИСАНИЕ ОТКРЫТОЙ TIN-МОДЕЛИ            (TINDESCRIBE)           *
*  СТРУКТУРА ЗАПИСИ МАССИВА ВЕРШИН         (TINVERTEX)             *
*  СТРУКТУРА ЗАПИСИ МАССИВА ТРЕУГОЛЬНИКОВ  (TINTRIANGLE)           *
*  ОПИСАНИЕ ФУНКЦИЙ ДОСТУПА К TIN-МОДЕЛИ                           *
*                                                                  *
********************************************************************
*                                                                  *
*    Импортирование функций в Windows :                            *
*                                                                  *
*    // Загрузка библиотеки                                        *
*    HINSTANCE libInst = ::LoadLibrary("gisacces.dll");            *
*                                                                  *
*    // Вызов функции                                              *
*    HMAP (WINAPI * lpfn_OpenTin)(const char*, long int);          *
*    (FARPROC)lpfn_OpenTin = GetProcAddress(libInst, "OpenTin");   *
*    HMAP hMap = (*lpfn_OpenTin)("Noginsk.tin",0);                 *
*                                                                  *
*    // Выгрузка библиотеки                                        *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/

#ifndef TINAPI_H
#define TINAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // Описание структур интерфейса MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

//------------------------------------------------------------------
//  ПАРАМЕТРЫ СОЗДАНИЯ TIN-МОДЕЛИ
//------------------------------------------------------------------
typedef struct TINBUILD     // Размер структуры 320 байт
{
  int  Length;              // Размер данной структуры: sizeof(TINBUILD)              // 31/03/15

  int  UserLabel;           // Пользовательский идентификатор -
                            // произвольное число, связываемое
                            // с создаваемой моделью

  int  ModelType;           // Тип модели
                            //  Значения: 1 - модель рельефа местности
                            //            2 - модель глубин

  int  Method;              // Метод построения модели
                            //  Значения: 1 - с использованием
                            //                триангуляции Делоне

  DFRAME    FrameMeters;    // Габариты модели в плане (метры)

  MAPREGISTEREX
      ModelRegister;  // Паспортные данные модели
                      // Структурa MAPREGISTEREX описанa в MAPCREAT.H
                      // Для создания TIN-модели используются
                      // значения следующих полей :
                      //  Name - условное имя модели,
                      //  Scale - знаменатель масштаба,
                      //  EllipsoideKind - вид эллипсоида (задавать
                      //    в соответствии с ELLIPSOIDKIND, файл MAPCREAT.H),
                      //  HeightSystem - система высот (задавать
                      //    в соответствии с HEIGHTSYSTEM, файл MAPCREAT.H),
                      //  MaterialProjection - проекция исходного материала
                      //    (задавать в соответствии с MAPPROJECTION, файл MAPCREAT.H),
                      //  CoordinateSystem - система координат (задавать
                      //    в соответствии с COORDINATESYSTEM, файл MAPCREAT.H),
                      //  MapType - обобщенный тип карты (задавать
                      //    в соответствии с MAPTYPE, файл MAPCREAT.H),
                      //  FirstMainParallel - первая главная параллель,
                      //  SecondMainParallel - вторая главная параллель,
                      //  AxisMeridian - осевой меридиан,
                      //  MainPointParallel - параллель главной точки.

  HOBJ Border;        // Идентификатор замкнутого объекта карты,
                      // по которому устанавливается рамка создаваемой
                      // TIN-модели (если объект расположен вне габаритов
                      // модели, определяемых значениями поля FrameMeters
                      // данной структуры, то рамка не устанавливается)

  char      Reserve[60];    // Должны быть нули
#ifdef _M_X64
  char      Free[4];        // Выравнивание  // 21/07/16
#endif // _M_X64
}
  TINBUILD;

//------------------------------------------------------------------
//  ОПИСАНИЕ ОТКРЫТОЙ TIN-МОДЕЛИ
//------------------------------------------------------------------
typedef struct TINDESCRIBE   // Размер структуры 1024 байта
{
  char    Name[260];         // Имя файла модели

  int   Length;              // Длина файла
  int   UserLabel;           // Пользовательский идентификатор
  int   ModelType;           // Тип модели
  int   Method;              // Метод построения модели
  int   VertexCount;         // Количество вершин
  int   TriangleCount;       // Количество треугольников
  int   View;                // Признак отображаемости

  DFRAME  FrameMeters;       // Габариты модели в плане (метры)

  double  MinHeightValue;    // Минимальное значение высоты поверхности (метры)
  double  MaxHeightValue;    // Максимальное значение высоты поверхности (метры)

  MAPREGISTEREX
      ModelRegister;  // Паспортные данные модели
                      // Структурa MAPREGISTEREX описанa в MAPCREAT.H
                      // Описание TIN-модели включает значения
                      // следующих полей :
                      //  Name - условное имя модели,
                      //  Scale - знаменатель масштаба,
                      //  EllipsoideKind - вид эллипсоида,
                      //  HeightSystem - система высот,
                      //  MaterialProjection - проекция исходного материала,
                      //  CoordinateSystem - система координат,
                      //  MapType - обобщенный тип карты,
                      //  FirstMainParallel - первая главная параллель,
                      //  SecondMainParallel - вторая главная параллель,
                      //  AxisMeridian - осевой меридиан,
                      //  MainPointParallel - параллель главной точки.

  double  ModelSquare;       // Площадь модели (кв.метры)

  char    Reserve[472];      // Резерв

}
  TINDESCRIBE;

typedef struct TINDESCRIBEUN   // 03/04/14
{
  WCHAR   Name[MAX_PATH_LONG]; // Имя файла модели

  DFRAME  FrameMeters;         // Габариты модели в плане (метры)

  MAPREGISTEREX
      ModelRegister;  // Паспортные данные модели
                      // Структурa MAPREGISTEREX описанa в MAPCREAT.H
                      // Описание TIN-модели включает значения
                      // следующих полей :
                      //  Name - условное имя модели,
                      //  Scale - знаменатель масштаба,
                      //  EllipsoideKind - вид эллипсоида,
                      //  HeightSystem - система высот,
                      //  MaterialProjection - проекция исходного материала,
                      //  CoordinateSystem - система координат,
                      //  MapType - обобщенный тип карты,
                      //  FirstMainParallel - первая главная параллель,
                      //  SecondMainParallel - вторая главная параллель,
                      //  AxisMeridian - осевой меридиан,
                      //  MainPointParallel - параллель главной точки.

  double  MinHeightValue;   // Минимальное значение высоты поверхности (метры)
  double  MaxHeightValue;   // Максимальное значение высоты поверхности (метры)
  double  ModelSquare;      // Площадь модели (кв.метры)

  int    Length;            // Длина файла
  int    UserLabel;         // Пользовательский идентификатор
  int    ModelType;         // Тип модели
  int    Method;            // Метод построения модели
  int    VertexCount;       // Количество вершин
  int    TriangleCount;     // Количество треугольников
  int    View;              // Признак отображаемости
#ifdef _M_X64
  int    Free;              // Выравнивание  // 21/07/16
#endif // _M_X64

  char    Reserve[128];     // Резерв

}
  TINDESCRIBEUN;

//------------------------------------------------------------------
// СТРУКТУРА ФЛАГОВ ВЕРШИНЫ TIN-МОДЕЛИ
//------------------------------------------------------------------
typedef struct TINVERTEXFLAG   // Размер структуры 8 байт
{
  char   Cancel;         // Флаг удаления
  char   PolygonBorder;  // Флаг принадлежности граничной
                         // линии полигона триангуляции
  char   StructLine;     // Флаг принадлежности структурной линии
  char   FaultLine;      // Флаг принадлежности линии разрыва
  char   FillingSquare;  // Флаг принадлежности контуру площади
                         // заполнения
  char   Reserve[3];
}
  TINVERTEXFLAG;

//------------------------------------------------------------------
// СТРУКТУРА ЗАПИСИ МАССИВА ВЕРШИН TIN-МОДЕЛИ
//------------------------------------------------------------------
typedef struct TINVERTEX     // Размер структуры 40 байт
{
  double X;                  // Координаты вершины в прямоугольной
  double Y;                  // системе в заданной проекции (метры)
  double H;
                             // Для вершин, входящих в состав линий разрыва
  int    UpperVertexNumber;  // Номер вершины верхнего уровня
  int    UnderVertexNumber;  // Номер вершины нижнего уровня

  TINVERTEXFLAG Flag;        // Флаги вершины
}
  TINVERTEX;

//------------------------------------------------------------------
// СТРУКТУРА ФЛАГОВ ТРЕУГОЛЬНИКА TIN-МОДЕЛИ
//------------------------------------------------------------------
typedef struct TINTRIANGLEFLAG   // Размер структуры 16 байт
{
  char Cancel;           // Флаг удаления

  char Location;         // Флаг положения треугольника в сети
                         // (0 - внутренний треугольник сети,
                         //  1 - внешний треугольник сети)

  char FillingSquare;    // Флаг принадлежности данного треугольника
                         // площади заполнения

  char AB;               // Флаг ребра "AB"
  char BC;               // Флаг ребра "BC"
  char CA;               // Флаг ребра "CA"
                         // (0 - ребро не входит в состав
                         //      структурной линии,
                         //  1 - ребро входит в состав структурной
                         //      линии гладкого перегиба,
                         //  2 - ребро входит в состав структурной
                         //      линии негладкого перегиба,
                         //  3 - ребро входит в состав структурной
                         //      линии разрыва,
                         //  4 - ребро входит в состав границы
                         //      полигона построения триангуляции)
  char Reserve[10];

}
  TINTRIANGLEFLAG;
  
//------------------------------------------------------------------
// СТРУКТУРА ЗАПИСИ МАССИВА ТРЕУГОЛЬНИКОВ TIN-МОДЕЛИ
//------------------------------------------------------------------
typedef struct TINTRIANGLE  // Размер структуры 40 байт
{
  int A;     // Номер вершины "A" в массиве вершин
  int B;     // Номер вершины "B" в массиве вершин
  int C;     // Номер вершины "C" в массиве вершин

  int AB;    // Номер соседнего треугольника по ребру "AB"
             // в массиве треугольников
  int BC;    // Номер соседнего треугольника по ребру "BC"
             // в массиве треугольников
  int CA;    // Номер соседнего треугольника по ребру "CA"
             // в массиве треугольников
             // (если соседнего треугольника нет, номер равен -1)

  TINTRIANGLEFLAG Flag;  // Флаги треугольника
}
  TINTRIANGLE;


  
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ОПИСАНИЕ ФУНКЦИЙ ДОСТУПА К TIN-МОДЕЛИ +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
  // Запросить число открытых TIN-файлов
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinCount(HMAP hMap);

  // Открыть TIN-модель
  // Возвращает идентификатор открытой модели (TMapAccess*)
  // При ошибке возвращает 0

  _MAPIMP HMAP _MAPAPI mapOpenTin(const char * tinname, long int mode);
  _MAPIMP HMAP _MAPAPI mapOpenTinUn(const WCHAR *tinname, long int mode = 0);  // 28/01/14

  // Открыть TIN-модель в заданном районе работ (добавить в цепочку)
  // Возвращает номер файла в цепочке
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapOpenTinForMap(HMAP hMap, const char * tinname, long int mode);
  _MAPIMP long int _MAPAPI mapOpenTinForMapUn(HMAP hMap, const WCHAR * tinname, long int mode);  // 28/01/14


  // Закрыть TIN-модель
  // number - номер закрываемой модели
  // если number == 0, закрываются все модели в окне

  _MAPIMP void _MAPAPI mapCloseTin(HMAP hMap, long int number);

  // Закрыть TIN-модель в заданном районе работ
  // number - номер файла модели в цепочке
  // Если number == 0, закрываются все модели
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapCloseTinForMap(HMAP hMap, long int number);

  // Создать TIN-модель
  // Возвращает идентификатор открытой модели (TMapAccess*)
  // Структурa TINBUILD описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP HMAP _MAPAPI mapCreateTin(const char * name, const TINBUILD * parm);
  _MAPIMP HMAP _MAPAPI mapCreateTinUn(const WCHAR * name, const TINBUILD * parm);  // 28/01/14

  // Создать файл TIN-модели
  // hMap -  идентификатор открытой векторной карты
  // tinname - полное имя файла модели
  // parm - параметры создания модели
  // Структурa TINBUILD описанa в TINAPI.H
  // Возвращает  номер файла в цепочке TIN-моделей
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapCreateAndAppendTin(HMAP hMap, const char * tinname, const TINBUILD * parm);
  _MAPIMP long int _MAPAPI mapCreateAndAppendTinUn(HMAP hMap, const WCHAR * tinname, const TINBUILD * parm);  // 28/01/14

  // Записать изменения TIN-модели в файл
  // number - номер файла в цепочке
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSaveTin(HMAP hMap, long int number);

  // Запросить описание файла TIN-модели
  // number - номер файла в цепочке
  // describe - адрес структуры, в которой будет размещено
  //            описание TIN-модели
  // Структурa TINDESCRIBE описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinDescribe(HMAP hMap, long int number,  // 10/04/13
                                     TINDESCRIBE * describe);

  _MAPIMP long int _MAPAPI mapGetTinDescribeUn(HMAP hMap, long int number,  // 03/04/14
                                     TINDESCRIBEUN * describe);

	// Запросить имя файла TIN-модели
	// number - номер файла в цепочке
	// При ошибке возвращает ноль

	_MAPIMP const char * _MAPAPI mapGetTinName(HMAP hMap,long int number);  // 28/01/14

  // Запросить имя файла TIN-модели
  // hMap - идентификатор открытой основной векторной карты
  // number - номер файла в цепочке
  // name - адрес строки для размещения результата
  // size - размер строки
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetTinNameUn(HMAP hMap,long int number,  // 28/01/14
                                           WCHAR *name, long int size);

  // Запросить номер TIN-модели в цепочке по имени файла 
  // name - имя файла TIN-модели
  // В цепочке номера TIN-моделей начинаются с 1
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetTinNumberByName(HMAP hMap, const char * name);
  _MAPIMP long int _MAPAPI mapGetTinNumberByNameUn(HMAP hMap, const WCHAR * name);  // 28/01/14

  // Запросить паспортные данные TIN-модели
  // number - номер TIN-файла в цепочке
  // data - адрес структуры, в которой будут размещены паспортные
  // данные TIN-модели
  // Структурa MAPREGISTEREX описанa в MAPCREAT.H
  // Паспортные данные TIN-модели включают значения следующих полей :
  //  Name - условное имя модели,
  //  Scale - знаменатель масштаба,
  //  EllipsoideKind - вид эллипсоида,
  //  HeightSystem - система высот,
  //  MaterialProjection - проекция исходного материала,
  //  CoordinateSystem - система координат,
  //  MapType - обобщенный тип карты,
  //  FirstMainParallel - первая главная параллель,
  //  SecondMainParallel - вторая главная параллель,
  //  AxisMeridian - осевой меридиан,
  //  MainPointParallel - параллель главной точки.
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinRegister(HMAP hMap, long int number,
                                     MAPREGISTEREX* data);

  // Запись вершины в массив вершин TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве вершин
  // Структурa TINVERTEX описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapPutTinVertex(HMAP hMap, long int number,
                                   const TINVERTEX * vertex, long int index);

  // Запрос вершины из массива вершин TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве вершин
  // Структурa TINVERTEX описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinVertex(HMAP hMap, long int number,
                                   TINVERTEX* vertex, long int index);

  // Выбор значения высоты поверхности TIN-модели в заданной точке
  // Высота поверхности запрашивается из TIN-модели с меньшим
  // номером файла в цепочке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки данными TIN-модели возвращает ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetSurfaceHeight(HMAP hMap, double x, double y);

  // Выбор значения высоты поверхности TIN-модели в заданной точке
  // из файла с номером number в цепочке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки данными TIN-модели возвращает ERRORHEIGHT.

  _MAPIMP double _MAPAPI mapGetTinSurfaceHeight(HMAP hMap, long int number,
                                        double x, double y);

  // Установка флагов вершины TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве вершин
  // flag - адрес структуры, содержащей устанавливаемые значения
  //        флагов вершины
  // Структурa TINVERTEXFLAG описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinVertexFlags(HMAP hMap, long int number,
                                        long int index, const TINVERTEXFLAG* flag);

  // Запрос флагов вершины TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве вершин
  // flag - адрес структуры, содержащей значения флагов вершины
  // Структурa TINVERTEXFLAG описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinVertexFlags(HMAP hMap, long int number,
                                        long int index, TINVERTEXFLAG* flag);


  // Установка флагов треугольника TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве треугольников
  // flag - адрес структуры, содержащей устанавливаемые значения
  //        флагов треугольника
  // Структурa TINTRIANGLEFLAG описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinTriangleFlags(HMAP hMap, long int number,
                                          long int index, const TINTRIANGLEFLAG* flag);

  // Запрос флагов треугольника TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве треугольников
  // flag - адрес структуры, содержащей значения флагов треугольника
  // Структурa TINTRIANGLEFLAG описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinTriangleFlags(HMAP hMap, long int number,
                                          long int index, TINTRIANGLEFLAG* flag);

  // Запрос треугольника из массива треугольников TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве треугольников
  // Структурa TINTRIANGLE описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinTriangle(HMAP hMap, long int number,
                                     TINTRIANGLE* triangle, long int index);

  // Запись треугольника в массив треугольников TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве треугольников
  // Структурa TINTRIANGLE описанa в TINAPI.H
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapPutTinTriangle(HMAP hMap, long int number,
                                     const TINTRIANGLE* triangle, long int index);



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ОПИСАНИЕ ФУНКЦИЙ УСТАНОВКИ ПАРАМЕТРОВ TIN-МОДЕЛИ  +++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // Установить паспортные данные TIN-модели
  // number - номер TIN-файла в цепочке
  // data - адрес структуры, содержащей паспортные данные TIN-модели
  // Структурa MAPREGISTEREX описанa в MAPCREAT.H
  // Паспортные данные TIN-модели включают значения следующих полей :
  //  Name - условное имя модели,
  //  Scale - знаменатель масштаба,
  //  EllipsoideKind - вид эллипсоида (задавать
  //    в соответствии с ELLIPSOIDKIND, файл MAPCREAT.H),
  //  HeightSystem - система высот (задавать
  //    в соответствии с HEIGHTSYSTEM, файл MAPCREAT.H),
  //  MaterialProjection - проекция исходного материала
  //    (задавать в соответствии с MAPPROJECTION, файл MAPCREAT.H),
  //  CoordinateSystem - система координат (задавать
  //    в соответствии с COORDINATESYSTEM, файл MAPCREAT.H),
  //  MapType - обобщенный тип карты (задавать
  //    в соответствии с MAPTYPE, файл MAPCREAT.H),
  //  FirstMainParallel - первая главная параллель,
  //  SecondMainParallel - вторая главная параллель,
  //  AxisMeridian - осевой меридиан,
  //  MainPointParallel - параллель главной точки.
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinRegister(HMAP hMap, long int number,
                                     const MAPREGISTEREX* data);

  // Установить пользовательский идентификатор TIN-модели
  // userLabel - идентификатор модели
  // number  - номер TIN-файла в цепочке
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinUserLabel(HMAP hMap, long int number,
                                      long int userLabel);

  // Установить тип TIN-модели
  // number - номер TIN-файла в цепочке
  // type - тип модели
  //   (задавать в соответствии с TINBUILD, файл TINAPI.H)
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinModelType(HMAP hMap, long int number,
                                      long int type);

  // Установить метод построения TIN-модели
  // number  - номер TIN-файла в цепочке
  // method - метод построения  модели
  //   (задавать в соответствии с TINBUILD, файл TINAPI.H)
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinMethod(HMAP hMap, long int number,
                                   long int method);
                                      
  // Установить габариты TIN-модели в районе
  // frame - габариты модели в районе (метры)
  // Структурa DFRAME описанa в MAPTYPE.H
  // number  - номер TIN-файла в цепочке
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinFrameMeters(HMAP hMap, long int number,
                                        const DFRAME* frame);

  // Установить диапазон значений высоты поверхности TIN-модели
  // number  - номер TIN-файла в цепочке
  // minimum - минимальное значение высоты поверхности (метры)
  // maximum - максимальное значение высоты поверхности (метры)
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinHeightDiapason(HMAP hMap, long int number,
                                           double minimum,
                                           double maximum);

  // Установить признак отображаемости TIN-модели
  // number - номер TIN-файла в цепочке
  // view - признак отображаемости
  //   (0 - модель не отображается, 1 - модель отображается)
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinView(HMAP hMap, long int number,
                                 long int view);
                                 
  // Запросить признак отображаемости TIN-модели
  // number - номер TIN-файла в цепочке
  // Возвращает признак отображаемости
  // (0 - модель не отображается, 1 - модель отображается)
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapCheckTinView(HMAP hMap, long int number); 
                                                               
  // Установить значения масштаба нижней и верхней
  // границ видимости TIN-модели
  // number - номер TIN-файла в цепочке
  // bottomScale - знаменатель масштаба нижней границы видимости
  // topScale - знаменатель масштаба верхней границы видимости
  // Если не выполняется условие bottomScale <= topScale, возвращает 0
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapSetTinRangeScaleVisible(HMAP hMap, long int number,
                                              long int bottomScale,
                                              long int topScale);

  // Запросить значения масштаба нижней и верхней
  // границ видимости TIN-модели
  // number - номер TIN-файла в цепочке
  // По адресу bottomScale записывается знаменатель масштаба
  // нижней границы видимости
  // По адресу topScale записывается знаменатель масштаба
  // верхней границы видимости
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinRangeScaleVisible(HMAP hMap, long int number,
                                              long int *bottomScale,
                                              long int *topScale);


  // Установить порядок отображения
  //  (0 - под картой, 1 - над картой)
  // При ошибке возвращает -1
  _MAPIMP long int _MAPAPI mapSetTinViewOrder(HMAP hMap, long int number, long int order);

  // Запроситьпорядок отображения
  //  (0 - под картой, 1 - над картой)
  // При ошибке возвращает -1
  _MAPIMP long int _MAPAPI mapGetTinViewOrder(HMAP hMap, long int number);

  // Запросить габариты модели в районе (метры)
  // number - номер файла в цепочке
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinFrame(HMAP hMap, long int number, DFRAME * dframe);

  // Запросить длину файла матричных данных
  // number - номер файла в цепочке
  // При ошибке возвращает ноль
  _MAPIMP long int _MAPAPI mapGetTinFileLength(HMAP hMap, long int number);

  // Запросить количество вершин в Tin-модели
  // number - номер файла в цепочке
  // При ошибке возвращает ноль
  _MAPIMP long int _MAPAPI mapGetTinVertexCount(HMAP hMap, long int number);


  // Запросить количество треугольников в Tin-модели
  // number - номер файла в цепочке
  // При ошибке возвращает ноль
  _MAPIMP long int _MAPAPI mapGetTinTriangleCount(HMAP hMap, long int number);

  // Запросить масштаб Tin-модели
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  _MAPIMP long int _MAPAPI mapGetTinScale(HMAP hMap, long int number);

  // Запросить тип TIN-модели
  // number - номер TIN-файла в цепочке  
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinModelType(HMAP hMap, long int number);

  // Запросить минимальное и максимальное значения высоты поверхности (метры)
  // number - номер TIN-файла в цепочке  
  // При ошибке возвращает 0
  
  _MAPIMP long int _MAPAPI mapGetTinHeightValue(HMAP hMap, long int number, 
                                          double * minvalue, double * maxvalue);
                                        
  // Запросить метод построения TIN-модели
  // number  - номер TIN-файла в цепочке  
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapGetTinMethod(HMAP hMap, long int number);
                                                                         
  // Запросить доступ к файлу
  // number  - номер TIN-файла в цепочке  
  // При ошибке возвращает 0

  _MAPIMP long int _MAPAPI mapIsTinEdit(HMAP hMap, long int number);  

  // Поменять очередность отображения моделей
  // oldNumber - номер файла в цепочке
  // newNumber - устанавливаемый номер файла в цепочке
  //  При ошибке возвращает 0
  _MAPIMP long int _MAPAPI mapChangeOrderTinShow(HMAP hMap, long int oldNumber, long int newNumber);

}

#endif // TINAPI_H

