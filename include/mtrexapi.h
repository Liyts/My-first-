/****** MTREXAPI.H ************** Gorbunov A.V. ****** 05/03/14 ****
******* MTREXAPI.H ************** Tarakanova I.R. **** 05/10/16 ****
******* MTREXAPI.H ************** Dishlenko S.G.****** 14/12/09 ****
******* MTREXAPI.H ************** Gustinovich N.A. *** 12/12/07 ****
******* MTREXAPI.H ************** Shabakov D.A.    *** 22/05/09 ****
******* MTREXAPI.H ************** Borzov A.Y.      *** 20/05/15 ****
******* MTREXAPI.H ************** Belenkov O.V.    *** 25/07/10 ****
******* MTREXAPI.H ************** Kruzhkov A.E.    *** 12/11/15 ****
******* MTREXAPI.H ************** Zheleznyakov V.A.*** 06/06/16 ****
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*          ФУНКЦИИ БИБЛИОТЕКИ (GIS\GSS)MAPMTREX.DLL                *
*                                                                  *
*******************************************************************/

#ifndef MTREXAPI_H
#define MTREXAPI_H

#include "maptype.h"                 // 17/03/07

#ifndef MAPCREAT_H
  #include "mapcreat.h"              // 18/12/07
#endif

#ifdef WIN32API                      // 17/03/07
#define HMESSAGE HWND
#else
#define HMESSAGE MSGHANDLER
#endif

#ifdef LINUXAPI                      // 04/02/14
 #define MTREXPORT _export WINAPI
#else
 #define MTREXPORT __declspec( dllexport ) WINAPI
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++  ВСПОМОГАТЕЛЬНЫЕ СТРУКТУРЫ  ++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 // РЕЗУЛЬТАТЫ ПРЕДВАРИТЕЛЬНОЙ ОЦЕНКИ ХАРАКТЕРИСТИК
 // СОЗДАВАЕМОЙ МАТРИЦЫ

 typedef struct PRIORMTRPARM
 {
   int    Length;              // Размер данной структуры :
                               //  sizeof (PRIORMTRPARM) = 64
   int    Free;                // Должен быть ноль

   double AbsHeightDifference; // Ошибка наложения высот - абсолютная
                               // величина разности высот объектов
                               // попадающих в элементы матрицы (метры)

   double Reserve[6];          // Должны быть нули
 }
   PRIORMTRPARM;



// СТРУКТУРА ПАРАМЕТРОВ СОЗДАНИЯ МАТРИЦЫ КАЧЕСТВ РАСТЕКАНИЯ  // 28/01/09

typedef struct SPREADPARM
{
  int         Length;       // Длина записи структуры SPREADPARM
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int         Free;         // Должен быть ноль
#endif
  HMESSAGE    hWnd;         // Идентификатор окна диалога, которому посылается
                            // сообщение 0x0581 о проценте выполненных работ (в WPARAM),
                            // если процесс должен быть принудительно завершен, в ответ
                            // должно вернуться значение 0x0581.
                            // Если Handle равно нулю - сообщения не посылаются.

  int         IterCount;    // Количество итераций
                            // (чем больше итераций, тем точнее заполняются ямы)
  COLORREF    Palette[256]; // Палитра создаваемой матрицы качеств
  int         PaletteCount; // Количество цветов в палитре
  int         IsIterMtq;    // Признак создания матриц на каждой итерации
  int         IsAllEject;   // Признак одномоментного выброса
                            // (если 0, то вода подливается на кажой итерации)

  double      EjectSize;    // Объем выброса жидкости в метрах кубич.
  double      AbsorbHeight; // Толщина пленки, впитываемой в землю в метрах
  double      ElemSize;     // Размер элемента создаваемой матрицы в метрах
  double      WaveHeight;   // Высота волны

  DOUBLEPOINT Point;        // Точка выброса

  char        Reserve[64];  // Должны быть нули
}
  SPREADPARM;



// ПАРАМЕТРЫ ВЫЗОВА ЗАДАЧИ СОЗДАНИЯ МАТРИЦЫ ВОДНО-БАЛАНСНЫХ БАССЕЙНОВ    // 22/05/09

typedef struct WZONEPARM
{
  int      Length;        // Длина записи структуры WZONEPARM
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int      Free;          // Должен быть ноль
#endif
  HMESSAGE Wnd;           // Идентификатор окна диалога, которому посылается
                          // сообщение 0x0581 о проценте выполненных работ (в WPARAM),
                          // если процесс должен быть принудительно завершен, в ответ
                          // должно вернуться значение 0x0581.
                          // Если Handle равно нулю - сообщения не посылаются.

  HMAP     Map;           // Идентификатор открытой основной карты
  HSELECT  Select;        // Набор объектов, для которых выполняется построение
  DFRAME   Frame;         // Область построения

  double   ElemSize;      // Размер элемента в метрах
  double   dH;            // Допуск по высоте для устранения 
                          // шероховатости матрицы высот

  char     Reserved[64];  // Должны быть нули
}
  WZONEPARM;


// ПАРАМЕТРЫ ПОСТРОЕНИЯ МАТРИЦЫ ГЛУБИН (MTQ)

typedef struct DEPTHMTQPARM
{
  int    StructSize;      // Размер данной структуры : sizeof (DEPTHMTQPARM) = 256 байт
  int    Free;            // Должен быть ноль

  int    MatrixType;      // Тип исходной матрицы рельефа:
                          //  1 - матрица высот (mtw)
                          //  2 - матрица качеств (mtq)

  int    MatrixNumber;    // Номер матрицы в цепочке

  double BeginX;          // Прямоугольные координаты начала
  double BeginY;          // (юго-западного угла) матрицы в метрах

  double Width;           // Ширина матрицы в метрах
  double Height;          // Высота матрицы в метрах

  double MinValue;        // Диапазон значений глубин создаваемой матрицы,
  double MaxValue;        // если MinValue >= MaxValue в матрицу заносится
                          // фактический диапазон значений

  double Level;           // Абсолютная высота горизонтальной поверхности
                          // для вычисления глубин, заносимых в матрицу

  double ElemSizeMeters;  // Размер стороны элемента матрицы глубин
                          // в метрах на местности (дискрет матрицы)

  int    UserLabel;       // Произвольное число, связываемое с создаваемой матрицей
                          //  (тип, характеристика матрицы)
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int    Free1;           // Должен быть ноль
#endif

  HWND   Handle;          // Идентификатор окна диалога, которому посылается
                          // сообщение 0x0581 о проценте выполненных работ (в WPARAM),
                          // если процесс должен быть принудительно завершен, в ответ
                          // должно вернуться значение 0x0581.
                          // Если Handle равно нулю - сообщения не посылаются.

  HOBJ   Border;          // Идентификатор замкнутого объекта карты, ограничивающего
                          // область заполняемых элементов матрицы (если равен нулю,
                          // то не используется). Если объект расположен вне габаритов
                          // матрицы, определяемых значениями полей BeginX, BeginY,
                          // Width, Height данной структуры, то не используется.

#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
#else
  int    Free2;           // Должен быть ноль
#endif

  char   Reserve[128];    // Должны быть нули

  char   UserName[32];    // Условное имя матрицы (название характеристики качества)
}
  DEPTHMTQPARM;


// ПАРАМЕТРЫ ВЫЧИСЛЕНИЯ СТАТИСТИКИ ПО МАТРИЦЕ

typedef struct CALCMATRIXPARM
{
  int    StructSize;      // Размер данной структуры : sizeof (CALCMATRIXPARM) = 264 байт
  int    Free;            // Должен быть ноль

  int    MatrixType;      // Тип исходной матрицы:
                          //  1 - матрица высот (mtw)
                          //  2 - матрица качеств (mtq)

  int    MatrixNumber;    // Номер матрицы в цепочке

  double BeginX;          // Прямоугольные координаты начала
  double BeginY;          // (юго-западного угла) области вычислений в метрах

  double Width;           // Ширина области вычислений в метрах
  double Height;          // Высота области вычислений в метрах ( если Width равно нулю
                          // или Height равно нулю, то область вычислений определяется
                          // габаритами заданной матрицы

  double MinValue;        // Диапазон значений элементов матрицы, участвующих в вычислениях.
  double MaxValue;        // Если MinValue >= MaxValue в вычислениях участвуют все элементы

  double ElemSizeMeters;  // Дискрет вычислений в метрах
                          // (если равен нулю, то используется дискрет матрицы)

  double Level;           // Высота уровня горизонтальной плоскости (основания)
                          // для вычисления объёма (используется при CalcVolume == 1)

  HWND   Handle;          // Идентификатор окна диалога, которому посылается
                          // сообщение 0x0581 о проценте выполненных работ (в WPARAM),
                          // если процесс должен быть принудительно завершен, в ответ
                          // должно вернуться значение 0x0581.
                          // Если Handle равно нулю - сообщения не посылаются.

  HOBJ   Border;          // Идентификатор замкнутого объекта карты, ограничивающего
                          // область выбираемых для вычислений элементов матрицы
                          // (если равен нулю, то не используется). Если объект 
                          // расположен вне габаритов области вычислений, определяемых
                          // значениями полей BeginX, BeginY, Width, Height
                          // данной структуры, то не используется.

  // Типы (задачи) вычислений:
  //---------------------------------------------
  char   CalcSquare;      // Определить площадь
  char   CalcVolume;      // Определить объём
  char   CalcMinimun;     // Определить минимальное значение
  char   CalcMaximun;     // Определить максимальное значение
  char   CalcAverage;     // Определить среднеарифметическое значение
 
  char   CalcSquareWater; // Определить площадь водного зеркала 
                          // (горизонтальная плоскость с абсолютной высотой LevelWater) 
                          // и площадь мелководий - SquareShallowWater

  char   CalcVolumeLayer; // Определить объём слоя между уровнями 
                          // LayerTop (верхний) и LayerBottom (нижний)
 
  char   CalcTypeReserve; // Резерв для типов вычислений
  //---------------------------------------------


  // Результаты вычислений:
  //-----------------------------------------------------------
  double Square;          // Площадь
  double Volume;          // Объём

  double Minimun;         // Минимальное значение
  double Maximun;         // Максимальное значение
  double Average;         // Среднеарифметическое значение

  double SquareWater;     // Площадь водного зеркала уровня LevelWater

  double SquareShallowWater;  // Площадь мелководья уровня LevelWater
                              // мелководье:   2 м >= глубина >= 1 см

  double VolumeLayer;     // Объём слоя между уровнями LayerTop и LayerBottom
  //-----------------------------------------------------------

  double LevelWater;      // Высота уровня горизонтальной плоскости водного зеркала
                          //  (используется при CalcSquareWater == 1)

  double LayerTop;        // Высота верхнего уровня слоя
                          //  (используется при CalcVolumeLayer == 1)

  double LayerBottom;     // Высота нижнего уровня слоя
                          //  (используется при CalcVolumeLayer == 1)

  char   Reserve[80];     // Должны быть нули
}
  CALCMATRIXPARM;


// ПАРАМЕТРЫ ПОСТРОЕНИЯ ЗОНЫ ЗАТОПЛЕНИЯ          // 30/08/10

typedef struct BUILDZONEFLOODPARM
{
  int         Length;       // Длина записи структуры BUILDZONEFLOODPARM
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int         Free1;        // Должен быть ноль
#endif
  HWND        Handle;       // Идентификатор окна диалога, которому посылается
                            // сообщение 0x0590 о проценте выполненных работ (в WPARAM),
                            // если процесс должен быть принудительно завершен, в ответ
                            // должно вернуться значение 0x0590.
                            // Если Handle равно нулю - сообщения не посылаются.

  DOUBLEPOINT Point1;       // Координаты первой точки, у которой указан уровень подъема воды
  DOUBLEPOINT Point2;       // Координаты второй точки, у которой указан уровень подъема воды
                            // Координаты задаются в метрах в системе координат векторной карты

  double      Height1;      // Уровень подъема воды первой точки
  double      Height2;      // Уровень подъема воды второй точки
  double      Width;        // Ширина зоны затопления
  double      ElementSize;  // Размер стороны элемента матрицы в метрах на местности

  HOBJ        Object;       // Объект (река), на котором указываются точки подъема воды

  int         Active;       // 0 - не создавать объекты зоны затопления
                            // 1 - создавать, удалив существующие
                            // 2 - создавать, не удаляя существующие
#if defined(_M_X64) || defined(BUILD_DLL64)  // 12/11/15
  int         Free2;        // Должен быть ноль
#endif
  char        Reserve[64];  // Должны быть нули
} 
  BUILDZONEFLOODPARM;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++  ФУНКЦИИ БИБЛИОТЕКИ MAPMTREX.DLL  +++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{

 // Вычисление значения абсолютной высоты (point->H) в заданной
 // точке (point->X,point->Y) по данным векторной карты.
 // Координаты точки задаются в метрах в системе координат
 // векторной карты.
 // В случае ошибки при вычислении высоты возвращает 0.

long int MTREXPORT mtrCalcAbsoluteHeight(HMAP hMap,XYHDOUBLE* point);

 // Вычисление значения абсолютной высоты в заданной
 // точке (point->X,point->Y) по данным векторной карты.
 // Координаты точки задаются в метрах в системе координат
 // векторной карты.
 // sectorcount - количество направлений для поиска окружающих высот
 //  (должно быть кратно 4, минимальное количество направлений = 4,
 //   максимальное = 256).
 // Возвращает значение высоты в метрах.
 // В случае ошибки при вычислении высоты возвращает ERRORHEIGHT.

double MTREXPORT mtrCalcAbsoluteHeightBySectors(HMAP hMap,
                                                DOUBLEPOINT* point,
                                                long int sectorcount);

 // Вычисление значения характеристики в заданной точке
 // по данным векторной карты.
 // Характеристика задается кодом семантики - semanticCode.
 // Координаты точки (point->X,point->Y) задаются в метрах в
 // системе координат векторной карты.
 // Вычисленное значение характеристики заносится в value.
 // flagSelect - флаг использования условий отбора объектов карты.
 // Если flagSelect = 0, то выполняется поиск заданной характеристики
 // по всем объектам векторной карты.
 // Если flagSelect = 1, то поиск заданной характеристики выполняется
 // только по объектам, удовлетворяющим условиям отбора (HSELECT),
 // установленным для векторной карты.
 // В случае ошибки возвращает 0

long int MTREXPORT mtrCalcCharacteristic(HMAP hMap,
                                         DOUBLEPOINT* point,
                                         long int semanticCode,
                                         long int flagSelect,
                                         double*  value);

  // Предварительная оценка характеристик матрицы, создаваемой
  // по векторной карте на заданный участок района работ.
  // В процессе оценки выполняется преобразование исходных
  // векторных данных района в растровый вид.
  // При ошибке возвращает ноль.
  // hMap    - исходная карта для построения матрицы,
  // filtername - полное имя фильтра объектов
  //   Вместе с картой может располагаться фильтр объектов -
  //   текстовый файл MTRCREA.IMH, содержащий перечень кодов
  //   объектов, используемых при построении матрицы (см. MAPAPI.DOC)
  //   Если filtername равно нулю - фильтр объектов не используется.
  // buildparm - параметры создаваемой матрицы,
  // priorparm - результаты предварительной оценки,
  // handle   - идентификатор окна диалога, которому посылаются
  // сообщения о ходе процесса :
  //   0x0581 - сообщение о проценте выполненных работ (в WPARAM),
  //   если процесс должен быть принудительно завершен, в ответ
  //   должно вернуться значение 0x0581.
  //   Если handle равно нулю - сообщения не посылаются.

long int MTREXPORT mtrTryBuild(HMAP hMap,
                               const char * filtername,
                               BUILDMTW * buildparm,
                               PRIORMTRPARM * priorparm,
                               HMESSAGE handle);


 // Вычисление значения максимального уклона и направления(азимут) максимального
 // уклона в заданной точке (point) по данным матрицы высот.
 // Координаты точки задаются в метрах в системе координат векторной карты.
 // Возвращает:
 //  incline - уклон в радианах
 //  azimuth  - азимут радианах
 // В случае ошибки при вычислении возвращает 0.

long int MTREXPORT  mtrCalcInclineInPoint(HMAP hMap,
                                          DOUBLEPOINT * point,
                                          double * incline,
                                          double * azimuth);


 // Построение растра качеств по векторной карте на заданный
 // участок района работ
 // При ошибке возвращает ноль
 // hMap    - исходная карта для построения растра,
 // rstname - полное имя создаваемого растра,
 // filtername - полное имя служебного текстового файла
 //   Вместе с картой должен располагаться фильтр объектов -
 //   служебный текстовый файл MАP2RSW.INI, содержащий перечень кодов
 //   объектов, используемых при построении растра
 // mtrparm - параметры создаваемого растра,
 // handle   - идентификатор окна диалога, которому посылаются
 // сообщения о ходе процесса :
 //   0x0581 - сообщение о проценте выполненных работ (в WPARAM),
 //   если процесс должен быть принудительно завершен, в ответ
 //   должно вернуться значение 0x0581.
 // Если handle равно нулю - сообщения не посылаются.

long int MTREXPORT mtrBuildRaster(HMAP hMap,
                                  const char * rstname,
                                  const char * filtername,
                                  BUILDMTW * rstparm,
                                  HMESSAGE handle);


 // Построение зоны затопления по набору отметок уровня воды.
 // В результате построения формируется матрица качеств, элементы
 // которой содержат глубины в зоне затопления.
 // Габариты матрицы качеств определяются координатами точек с
 // отметками уровня воды (массив pointArray) и величиной расширения
 // габаритов области (areaExtension).
 // hMap    - исходная карта для построения зоны,
 // mtqName - полное имя создаваемой матрицы качеств,
 // pointArray - адрес массива точек с отметками уровня воды
 //   Координаты точек (pointArray->X,pointArray->Y) и значения уровня
 //   (pointArray->H) задаются в метрах в системе координат векторной
 //   карты,
 // pointCount - число точек в массиве pointArray
 //   Размер в байтах массива, заданного адресом pointArray, должен
 //   быть не менее pointCount * sizeof(XYHDOUBLE), в противном случае
 //   возможны ошибки работы с памятью,
 // areaExtension - положительное число, задающее величину
 //   расширения габаритов области в метрах,
 // minDepth - положительное число, задающее минимальную глубину
 //   зоны затопления в метрах (глубины, меньшие minDepth в матрицу
 //   качеств не заносятся),
 // handle - идентификатор окна диалога, которому посылаются
 // сообщения о ходе процесса :
 //   0x0581 - сообщение о проценте выполненных работ (в WPARAM),
 //   если процесс должен быть принудительно завершен, в ответ
 //   должно вернуться значение 0x0581.
 //   Если handle равно нулю - сообщения не посылаются.

long int MTREXPORT mtrBuildFloodZone(HMAP hMap,
                                     const char * mtqName,
                                     XYHDOUBLE * pointArray,
                                     long int pointCount,
                                     double areaExtension,
                                     double minDepth,
                                     HMESSAGE handle);


 // Построение зоны затопления по объекту методом створов.
 // hMap - исходная карта, обеспеченная данными о рельефе,
 // parm - параметры построения зоны затопления.
 // mtqname - полное имя создаваемой матрицы качеств
 // sitename - имя пользовательской карты для записи объектов - зон затопления
 // В результате построения формируется матрица качеств, элементы
 // которой содержат глубины в зоне затопления.
 // В памяти создается пользовательская карта sitename с классификатором service.rsc.
 // Классификатор service.rsc должен находиться в одном каталоге с приложением или с hMap.
 // Если задано sitename и  Active > 0 (параметр Active из BUILDZONEFLOODPARM - флаг 
 // создания объектов), пользовательская карта будет записана на диск
 // hPaint - идентификатор контекста отображения для многопоточного вызова функций,
 //          создается функцией mapCreatePaintControl, освобождается - mapFreePaintControl
 // В случае ошибки возвращает 0.

long int MTREXPORT mtrFloodZoneByObject(HMAP hMap,
                                        const char * mtqname,
                                        const char * sitename,
                                        BUILDZONEFLOODPARM * parm);

long int MTREXPORT mtrFloodZoneByObjectUn(HMAP hMap,                    // 20/11/14
                                          const WCHAR * mtqname,
                                          const WCHAR * sitename,
                                          BUILDZONEFLOODPARM * parm);

long int MTREXPORT mtrFloodZoneByObjectEx(HMAP hMap,
                                          const WCHAR * mtqname,
                                          const WCHAR * sitename,
                                          BUILDZONEFLOODPARM * parm, HPAINT hPaint);

 // Построение матрицы качеств по массиву значений характеристики качества.
 // hMap - исходная карта для построения матрицы качеств,
 // mtqName - полное имя создаваемой матрицы качеств,
 // palette - адрес палитры создаваемой матрицы качеств,
 // countpalette - количество цветов в палитре,
 // pointArray - адрес массива значений характеристики качества
 //   Координаты точек (pointArray->X,pointArray->Y) задаются в метрах
 //   в системе координат векторной карты,
 // pointCount - число точек в массиве pointArray
 //   Размер в байтах массива, заданного адресом pointArray, должен
 //   быть не менее pointCount * sizeof(XYHDOUBLE), в противном случае
 //   возможны ошибки работы с памятью,
 // elemSizeMeters - размер стороны элементарного участка в метрах на местности
 //                  (дискрет матрицы)
 // minValue,maxValue - диапазон значений характеристики качества создаваемой матрицы
 //                     качеств, если minValue >= maxValue - в матрицу заносится
 //                     фактический диапазон значений из массива pointArray
 // handle - идентификатор окна диалога, которому посылаются
 //   сообщения о ходе процесса :
 //   0x0581 - сообщение о проценте выполненных работ (в WPARAM),
 //   если процесс должен быть принудительно завершен, в ответ
 //   должно вернуться значение 0x0581.
 //   Если handle равно нулю - сообщения не посылаются.

long int MTREXPORT mtrBuildMtq(HMAP hMap,
                               const char * mtqName,
                               const COLORREF* palette,
                               long int countpalette,
                               const XYHDOUBLE * pointArray,
                               long int pointCount,
                               double elemSizeMeters,
                               double minValue,
                               double maxValue,
                               HMESSAGE handle);

 // Построение матрицы поверхности (матрицы качеств или матрицы высот)
 // по данным векторной карты. Если mtrparm->FileMtw равно 1, то строится
 // матрица высот (*.mtw), иначе строится матрица качеств (*.mtq).
 // hmap - исходная карта для построения матрицы
 // mtrname - полное имя создаваемой матрицы
 // mtrparm - параметры создаваемой матрицы (структура BUILDSURFACE описана в maptype.h)
 // При ошибке возвращает 0.

long int MTREXPORT mtrBuildMatrixSurface(HMAP hmap,
                                         const char * mtrname,
                                         BUILDSURFACE * mtrparm);

long int MTREXPORT mtrBuildMatrixSurfaceUn(HMAP hmap,               // 17/02/14
                                           const WCHAR * mtrname,
                                           BUILDSURFACE * mtrparm);

 // Занесение в матрицу качеств зоны вдоль линейного объекта
 // hMap - идентификатор открытой матричной карты
 // number - номер матрицы качеств в цепочке
 // infoLine - линейный объект
 // width - ширина зоны в метрах
 // value - значение, заносимое в элементы зоны
 // regime - режим занесения значения (0 - без учёта ранее занесённого значения)
 // В случае ошибки возвращает 0

long int MTREXPORT mtrPutMtqLineZone(HMAP hMap,
                                     long int number,
                                     HOBJ infoLine,
                                     double width,
                                     double value,
                                     long int regime);

 // Занесение в матрицу качеств зоны вдоль линейного объекта
 // в границах площадного объекта
 // hMap - идентификатор открытой матричной карты
 // number - номер матрицы качеств в цепочке
 // infoLine - линейный объект
 // infoPolygon - площадной объект
 // width - ширина зоны в метрах
 // valueZone - значение, заносимое в элементы зоны
 // valuePolygon - значение, заносимое в элементы площадного объекта
 // regime - режим занесения значения (0 - без учёта ранее занесённого значения)
 // В случае ошибки возвращает 0

long int MTREXPORT mtrPutMtqLineZoneForPolygon(HMAP hMap,       // 26/06/08
                                               long int number,
                                               HOBJ infoLine,
                                               HOBJ infoPolygon,
                                               double width,
                                               double valueZone,
                                               double valuePolygon,
                                               long int regime);

 // Создание матрицы качеств растекания жидкости         // 28/01/09
 // Заполненные элементы матрицы содержат толщину слоя
 // растекшейся жидкости
 // hmap    - идентификатор открытых данных (должна быть открыта хотя бы одна матрица высот)
 // mtqname - имя создаваемой матрицы качеств растекания, если матрицы создаются на каждой итерации,
 //           то в конце имени добавляется номер итерации (для первой = MtqName_1.mtq)
 // parm    - параметры вызова
 // При ошибке возвращает ноль

long int MTREXPORT mtrLiquidSpreading(HMAP hMap, const char *mtqname, SPREADPARM *parm);
long int MTREXPORT mtrLiquidSpreadingUn(HMAP hMap, const WCHAR *mtqname, SPREADPARM *parm);  // 17/02/14

 // Вычисление площади зоны по матрице качеств
 // hMap - идентификатор открытой матричной карты
 // number - номер матрицы качеств в цепочке
 // minValue,maxValue - задают диапазон значений элементов,
 // участвующих в вычислении площади
 // если minValue > maxValue, то площадь вычисляется по всем
 // заполненым элементам матрицы
 // Вычисленное значение площади заносится в zoneSquare.
 // В случае ошибки возвращает 0

long int MTREXPORT mtrCalcMtqZoneSquare(HMAP hMap,
                                        long int number,
                                        double minValue,
                                        double maxValue,
                                        double* zoneSquare);


 // Преобразование матрицы высот (MTW) или матрицы качеств (MTQ) к заданной проекции
 //   handle  - диалог визуального сопровождения процесса обработки,
 //   namein  - имя исходной матрицы,
 //   nameout - имя выходной матрицы,
 //   mapreg  - адрес структуры с данными о заданной проекции,
 //   datum   - параметры пересчета геодезических координат с заданного эллипсоида
 //             на эллипсоид WGS-84 (может быть ноль),
 //  ellparam - параметры пользовательского эллипсоида (может быть ноль).
 //  ttype    - тип локального преобразования координат (см. TRANSFORMTYPE в mapcreat.h) или 0
 //  tparm    - параметры локального преобразования координат (см. mapcreat.h)
 //
 // Описание структур MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM - mapcreat.h
 // Диалогу визуального сопровождения процесса обработки посылаются сообщения:
 //   -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
 //      WPARAM - текущее состояние процесса в процентах (0% - 100%)
 //      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
 //
 // При ошибке возвращает ноль, код ошибки возвращается функцией
 // picexGetLastError (коды ошибок - maperr.rh)

 long int MTREXPORT
 MtwProjectionReformingPro(HMESSAGE handle,                  // 05/10/16
                          const WCHAR * namein,
                          const WCHAR * nameout,
                          MAPREGISTEREX * mapreg,
                          DATUMPARAM * datum,
                          ELLIPSOIDPARAM * ellparam,
                          long int ttype,
                          LOCALTRANSFORM * tparm);

 long int MTREXPORT
 MtwProjectionReformingEx(HMESSAGE handle,
                          const char * namein,
                          const char * nameout,
                          MAPREGISTEREX * mapreg,
                          DATUMPARAM * datum,
                          ELLIPSOIDPARAM * ellparam);

 long int MTREXPORT
 MtwProjectionReformingUn(HMESSAGE handle,                  // 18/02/14
                          const WCHAR * namein,
                          const WCHAR * nameout,
                          MAPREGISTEREX * mapreg,
                          DATUMPARAM * datum,
                          ELLIPSOIDPARAM * ellparam);

 long int MTREXPORT
 MtwProjectionReforming(HMESSAGE handle, const char * namein,
                        const char * nameout, MAPREGISTEREX * mapreg);

 // Cоздание матрицы водно-балансных бассейнов
 // Элемент матрицы качеств содержит ключ объекта, к которому относится бассейн
 // mtqname - имя создаваемой матрицы водно-балансных бассейнов
 // parm    - параметры вызова
 // При ошибке возвращает ноль

long int MTREXPORT mtrWaterZone(const char *mtqname, WZONEPARM *parm);
long int MTREXPORT mtrWaterZoneUn(const WCHAR *mtqname, WZONEPARM *parm);  // 17/02/14

 // Построение матрицы глубин (матрицы качеств mtq)
 // hmap - исходная карта для построения матрицы,
 // обеспеченная данными о рельефе дна
 // depthmtqname - полное имя создаваемой матрицы
 // depthmtqparm - параметры построения
 // palette - адрес палитры создаваемой матрицы
 //  (если равен нулю, используется палитра по умолчанию)
 // paletteCount - число цветов палитры
 // При ошибке возвращает 0.

long int MTREXPORT mtrBuildDepthMtq(HMAP hmap,
                                    const char * depthmtqname,
                                    DEPTHMTQPARM * depthmtqparm,
                                    COLORREF * palette,
                                    long int paletteCount);

long int MTREXPORT mtrBuildDepthMtqUn(HMAP hmap,                 // 17/02/14
                                      const WCHAR * depthmtqname,
                                      DEPTHMTQPARM * depthmtqparm,
                                      COLORREF * palette,
                                      long int paletteCount);

 // Вычисление статистики по матрице высот (mtw) или матрице качеств (mtq)
 // hmap - исходная карта, обеспеченная матричными данными
 // calcmatrixparm - параметры и результаты вычислений
 // При наличии данных (значений качества) для вычисления статистики в области,
 // заданной параметрами calcmatrixparm, возвращает 1.
 // При отсутствии данных (значений качества) в заданной области возвращает 0.

long int MTREXPORT mtrCalcByMatrix(HMAP hmap,                 // 12/11/09
                                   CALCMATRIXPARM * calcmatrixparm);

// Сплайн сглаживание матрицы высот
//  mtrName      - полное имя сглаживаемой матрицы
//  smoothFactor - уровень сглаживания (от 0 до 1, 0 - прямая линия,
//                 1 - кубический сплайн)
//  handle       - идентификатор окна диалога, которому посылаются
//                 сообщения о ходе процесса (процент обработки),
//                 если handle = 0, то сообщения не посылаются
//  messageId    - идентификатор сообщения с процентом обработки
// Для сглаживания матрицы запрашивается оперативная память в размере
// (RowCount*ColCount*16) байт, где RowCount - количество строк матрицы,
// ColCount - количество столбцов матрицы
// В случае ошибки возвращает 0

long int MTREXPORT mtrSmoothMtr(const char *mtrName, double smoothFactor,
                                HMESSAGE handle, long int messageId);

long int MTREXPORT mtrSmoothMtrUn(const WCHAR *mtrName, double smoothFactor,  // 17/02/14
                                  HMESSAGE handle, long int messageId);


//********************************************************************
// Кригинг // 15/06/11
//********************************************************************
// Последовательность вызова функций :

// hKriging = mapKrigingCreate(hmap, &MtrParm);

// Размер лага определяем, как максимальное расстояние между точками деленное
// на количество лагов. В этом случае будет перекрыт весь диапазон измерений.
// mapKrigingGetMinMaxDistance(hKriging, &MinDist, &MaxDist);
// double LagSize = MaxDist / LagCount;

// Вычисляем эмпирические вариограммы для лагов
// mapKrigingSetEmpiricalVariograms(hKriging, LagSize, LagCount);

// Показываем эмипирические вариограммы точками
//  for (int i = 0; i < LagCount; i++)
//    {
//      mapKrigingGetEmpiricalVariogram(Kriging, i, &Var, &Dist, &PointCount);
//      if (PointCount) Series2->AddXY(Dist, Var, IntToStr(PointCount), clGray);
//    }

// Вычисляем параметры модели
// Если параметр модели надо вычислить, то передаем в ф-цию -1
//  double Range  = -1;
//  double Sill   = -1;
//  double Nugget = -1;
//  if (! CalcRangeButton ->Down) Range  = atof(RangeEdit ->Text.c_str());
//  if (! CalcSillButton  ->Down) Sill   = atof(SillEdit  ->Text.c_str());
//  if (! CalcNuggetButton->Down) Nugget = atof(NuggetEdit->Text.c_str());
//  mapKrigingSetTeoreticalVariograms(hKriging, ModelType, &Range, &Sill, &Nugget))

//  Показываем вычисленные коэффициенты
//  RangeEdit ->Text = FloatToStr(Range);
//  SillEdit  ->Text = FloatToStr(Sill);
//  NuggetEdit->Text = FloatToStr(Nugget);

//  // Рисуем теоретическую вариограмму на графике линией
//  double LagsSize = LagSize * LagCount;
//  double Step = LagsSize / 100.;
//  for (double Dist = 0; Dist < LagsSize; Dist += Step)
//    {
//      mapKrigingGetTeoreticalVariogram(Kriging, Dist, &Var);
//      Series1->AddXY(Dist, Var / Divider, "", clGray);
//    }

// ...

//  После интерактивного подбора порога, самородка и радиуса строим матрицу
//  mapKrigingBuild(hKriging, MtrName);

// mapKrigingFree(hKriging);
//********************************************************************

// Тип модели, применяемой для вычисления теоретичекой вариограммы
#define KM_FIRST       0
#define KM_LAST        7
#define KM_SPHEROIDAL  0  // сферическая
#define KM_CIRCULAR    1  // круговая
#define KM_TETRASPHER  2  // тетрасферическая
#define KM_PENTASPHER  3  // пентасферическая
#define KM_EXPONENT    4  // экспоненциальная
#define KM_GAUSS       5  // гауссова
#define KM_RATSQUARE   6  // рациональная квадратичная
#define KM_HOLE        7  // эффекта дыры

// Создание класса кригинга
// hmap - карта по объектам которой будет строится матрица
// mtrparm - параметры построения матрицы
// ranges  - для матриц качеств диапазон значений для палитры (при 0 не устанавливается)
// В случае ошибки возвращает 0

HANDLE MTREXPORT mtrKrigingCreate(HMAP hmap, HSITE hsit, BUILDSURFACE *mtrparm, double *ranges);

// Освобождение класса кригинга
// kriging - идентификатор созданного класса кригинга

void MTREXPORT mtrKrigingFree(HANDLE kriging);

// Возвращает минимальное и максимальное расстояние между точками
// kriging - идентификатор созданного класса кригинга
// min     - возвращаемое минимальное расстояние между точками (только узловыми)
// max     - возвращаемое максимальное расстояние между точками
// В случае ошибки возвращает 0

long int MTREXPORT mtrKrigingGetMinMaxDistance(HANDLE kriging, double *min, double *max);

// Вычисляет эмпирическую вариограмму для лагов
// Лаг - диапазон расстояний между парами точек, для которых вычисляется эмпирическая вариограмма
// kriging - идентификатор созданного класса кригинга
// lagsize - размер лага в метрах (для всего диапазона LagSize = MaxDist / LagCount
// lagcount - количество лагов
// В случае ошибки возвращает 0

long int MTREXPORT mtrKrigingSetEmpiricalVariograms(HANDLE kriging, double lagsize, int lagcount);

// Возвращает параметры эмпирической вариограммы для лага
// kriging - идентификатор созданного класса кригинга
// lagnum  - номер лага, для которого возвращаются параметры
// variogram - эмпирическая вариограмма = sum(dH * dH) / 2
// dist      - центр лага по оси расстояний между парами точек = lagnum * lagsize + lagszie / 2
// pointcount - количество пар точек, попавших в диапазон лага
// В случае ошибки возвращает 0

long int MTREXPORT mtrKrigingGetEmpiricalVariogram(HANDLE kriging, int lagnum,
                                                        double *variogram, double *dist,
                                                        int *pointcount);

// Вычисляет параметры модели, применяемой для вычисления теоретичекой вариограммы
// kriging - идентификатор созданного класса кригинга
// modeltype - тип модели (см. KM_SPHEROIDAL и др.)
// range     - радиус модели (метры) - точка на оси расстояний между точками
//             после которой кривая становится горизонтальной.
//             Если = -1 - то значение вычисляется, если > 0, то устанавливается
// sill      - порог - значение, которое принимает теоретическая вариограмма в
//             точке радиуса модели, из которого вычтено значение самородка
//             Если = -1 - то значение вычисляется, если > 0, то устанавливается
// nugget    - самородок - точка в которой кривая пересекает ось вариограммы.
//             Теоретически для нулевого расстояния между точками, изменение функции
//             должно быть равно 0. Однако при бесконечно малых расстояниях разница
//             между измерениями зачастую не стремится к нулю.
//             Если = -1 - то значение вычисляется, если >= 0, то устанавливается
// В случае ошибки возвращает 0

long int MTREXPORT mtrKrigingSetTeoreticalVariograms(HANDLE kriging, int modeltype,
                                                          double *range, double *sill, double *nugget);

// Вычисляет значение теоретической вариограммы по расстоянию между двумя точками
// kriging - идентификатор созданного класса кригинга
// В случае ошибки возвращает 0

long int MTREXPORT mtrKrigingGetTeoreticalVariogram(HANDLE kriging, double dist, double *var);

// Строит матрицу
// kriging - идентификатор созданного класса кригинга
// mtrname - имя создаваемой маррицы высот или качеств
// В случае ошибки возвращает 0

long int MTREXPORT mtrKrigingBuild(HANDLE kriging, const char *mtrname);
long int MTREXPORT mtrKrigingBuildUn(HANDLE kriging, const WCHAR *mtrname);  // 03/03/14


//********************************************************************
// Кокригинг // 13/02/13
//********************************************************************

// Признак (внутри которого или между которыми) вычисляется ковариация в кокригинге
#define COVFEATUREMIN 1
#define COVFEATUREMAX 3
#define COVFEATURE1   1
#define COVFEATURE2   2
#define COVFEATURE12  3

// Создание класса кокригинга
// ranges  - для матриц качеств диапазон значений для палитры (при 0 не устанавливается)

HANDLE MTREXPORT mtrCokrigingCreate(HMAP hmap, HSITE hsit, BUILDSURFACE *mtrparm, double *ranges);

// Освобождение класса кокригинга

void MTREXPORT mtrCokrigingFree(HANDLE cokriging);

// Возвращает минимальное и максимальное расстояние между точками

long int MTREXPORT mtrCokrigingGetMinMaxDistance(HANDLE cokriging, int feature,
                                                      double *min, double *max);

// Вычисляет эмпирическую вариограмму

long int MTREXPORT mtrCokrigingSetEmpiricalCovariance(HANDLE cokriging, int feature,
                                                           double lagsize, int lagcount);

// Возвращает значение эмпирической вариограммы для лага

long int MTREXPORT mtrCokrigingGetEmpiricalCovariance(HANDLE cokriging, int feature, int lagnum,
                                                           double *variogram, double *dist, int *pointcount);

// Возвращает значение дисперсии

long int MTREXPORT mtrCokrigingGetVariance(HANDLE cokriging, int feature, double *variance);

// Возвращает количество точек, по которым считалась дисперсия
// Для признаков - количество реальных исходных точек
// Для кросс - количество точек на которых одновременно выполнялись оба измерения

long int MTREXPORT mtrCokrigingGetVariancePointCount(HANDLE cokriging, int feature, int *variancepointcount);

// Вычисляет теоретическую вариограмму

long int MTREXPORT mtrCokrigingSetTeoreticalCovariance(HANDLE cokriging, int feature, int modeltype,
                                                            double *range, double *sill, double *nugget);

// Вычисляет значение теоретической вариограммы по расстоянию между двумя точками

long int MTREXPORT mtrCokrigingGetTeoreticalCovariance(HANDLE cokriging, int feature, double dist, double *var);

// Строит матрицу

long int MTREXPORT mtrCokrigingBuild(HANDLE cokriging, const char *mtrname);
long int MTREXPORT mtrCokrigingBuildUn(HANDLE cokriging, const WCHAR *mtrname);  // 03/03/14

//********************************************************************
// Логарифмическая интерполяция
//********************************************************************

long int MTREXPORT mtrLogarithmBuild(HMAP hmap, HSITE hsit, const char *mtrname,
                                     BUILDSURFACE *mtrparm, double *ranges);

long int MTREXPORT mtrLogarithmBuildUn(HMAP hmap, HSITE hsit, const WCHAR *mtrname,  // 03/03/14
                                     BUILDSURFACE *mtrparm, double *ranges);

//********************************************************************
// Оконтуривание матриц и растров  // 28/05/13
//********************************************************************

// Класс однородных областей в матрице

typedef struct MTRCLASS
{
  double Min;            // Диапазон значений элементов матрицы, принадлежащих классу (включая Min, исключая Max)
  double Max;            // для матрицы высот      - диапазон высот
                         // для матрицы качеств    - диапазон значений
                         // для палитрового растра - диапазон индексов
                         // для RGB растра         - яркость - среднее по R,G,B
  int    Excode;         // Код создаваемого объекта
  int    Color;          // Цвет отображения полигонов
  int    SemanticNumber; // Код числовой семантики в которую записывается номер класса (если 0, то не пишется)
                         // (в семантику заносится номер класса начиная с 1)
  int    SemanticMin;    // Код числовой семантики для записи Min класса (если 0, то не пишется)
  int    SemanticMax;    // Код числовой семантики для записи Max класса (если 0, то не пишется)
  int    SemanticColor;  // Код числовой семантики для записи цвета отображения полигонов класса (если 0, то не пишется)
}
  MTRCLASS;

// Преобразование матрицы высот в вектор
// hmap       - основная карта
// hsit       - векторная карта в которую пишутся объекты
// mtrnum     - номер оконтуриваемой матрицы высот, добавленной к карте
// isfilter   - признак фильтрации точек, лежащих на одной прямой
// hselect    - содержит созданные объекты
//              если = 0, то не заполняется, ненулевое значение сильно замедляет обработку
// classes    - распознаваемые классы
// classcount - количество классов
// border     - объект, ограничивающий область преобразования матрицы в вектор
// iscuthole  - признак вырезания подобъектов
//              если = 0, то внутренний объект всегда имеет больший номер (Key), чем внешний
// handle     - идентификатор окна диалога, которому посылается cообщение 0x0581
//              в wParam - процент выполненной обработки
//              в lParam - адрес строки с названием выполняемого этапа
//              Если процесс должен быть принудительно завершен, в ответ
//              должно вернуться значение 0x0581.
//              Если Handle равно нулю - сообщения не посылаются.
// При ошибке возвращает 0

long int MTREXPORT mtrMtwToVector(HMAP hmap, HSITE hsit, long int mtrnum, long int isfilter,
                                  HSELECT hselect, MTRCLASS *classes, long int classcount, HOBJ border,
                                  long int iscuthole, HMESSAGE handle);

// Преобразование матрицы качеств в вектор
// hmap       - основная карта
// hsit       - векторная карта в которую пишутся объекты
// mtqnum     - номер исходной матрицы качеств, добавленной к карте
// isfilter   - признак фильтрации точек, лежащих на одной прямой (0..1)
// hselect    - содержит созданные объекты (если = 0, то не заполняется)
// classes    - распознаваемые классы
// classcount - количество классов
// border     - объект, ограничивающий область преобразования матрицы в вектор
// iscuthole  - признак вырезания подобъектов
//              если = 0, то внутренний объект всегда имеет больший номер (Key), чем внешний
// handle     - идентификатор окна диалога, которому посылается cообщение 0x0581
//              в wParam - процент выполненной обработки
//              в lParam - адрес строки с названием выполняемого этапа
//              Если процесс должен быть принудительно завершен, в ответ
//              должно вернуться значение 0x0581.
//              Если Handle равно нулю - сообщения не посылаются.
// При ошибке возвращает 0

long int MTREXPORT mtrMtqToVector(HMAP hmap, HSITE hsit, long int mtqnum, long int isfilter,
                                  HSELECT hselect, MTRCLASS *classes, long int classcount, HOBJ border,
                                  long int iscuthole, HMESSAGE handle);

// Преобразование растра в вектор
// hmap       - основная карта
// hsit       - векторная карта в которую пишутся объекты
// rstnum     - номер исходного растра, добавленного к карте
// isfilter   - признак фильтрации точек, лежащих на одной прямой (0..1)
// hselect    - содержит созданные объекты (если = 0, то не заполняется)
// classes    - распознаваемые классы
// classcount - количество классов
// border     - объект, ограничивающий область преобразования растра в вектор
// iscuthole  - признак вырезания подобъектов
//              если = 0, то внутренний объект всегда имеет больший номер (Key), чем внешний
// handle     - идентификатор окна диалога, которому посылается cообщение 0x0581
//              в wParam - процент выполненной обработки
//              в lParam - адрес строки с названием выполняемого этапа
//              Если процесс должен быть принудительно завершен, в ответ
//              должно вернуться значение 0x0581.
//              Если Handle равно нулю - сообщения не посылаются.
// При ошибке возвращает 0

long int MTREXPORT mtrRstToVector(HMAP hmap, HSITE hsit, long int rstnum, long int isfilter,
                                  HSELECT hselect, MTRCLASS *classes, long int classcount, HOBJ border,
                                  long int iscuthole, HMESSAGE handle);

//********************************************************************
// Построение матрицы плотности (элемент матрицы содержит количество точек,
// попавших в заданный радиус)
//********************************************************************

// Параметры вызова задачи построения матрицы плотности

typedef struct BUILDDENSITY
{
  double    Radius;       // радиус поиска точек в метрах для вычисления значения элемента
  double    ElemSize;     // размер элемента создаваемой матрицы в метрах
  COLORREF  Palette[256]; // палитра матрицы
  int       PaletteCount; // количество цветов в палитре (если = 0, то устанавливается стандартная)
  int       Reserved[63];
}
  BUILDDENSITY;

// Построение матрицы плотности
// hmap    - основная карта
// hsit    - векторная карта с объектами, по которым строится матрица плотности
// mtqname - имя создаваемой матрицы
// hselect - объекты, по которым строится матрица (если = 0, то все объекты карты)
// parm    - параметры построения
// hwnd    - окно, которому посылаются сообщения WM_PROGRESSBAR с процентом
//           обработки в WPARAM (если = 0, то сообщения не посылаются)
// При ошибке возвращает 0

long int MTREXPORT mtrBuildDensityMtq(HMAP hmap, HSITE hsit, const WCHAR *mtqname,
                                      HSELECT hselect, BUILDDENSITY *parm, HMESSAGE hwnd);

//********************************************************************
// Построение матрицы зон видимости (элемент матрицы имеет значение 1, в случае
// если с него видна хотя бы одна заданная точка, в противном случае 0)
//********************************************************************

// Параметры вызова задачи построения матрицы зон видимости

typedef struct BUILDVISIBLE
{
  double    Radius;   // предельный радиус видимости
  double    ElemSize; // размер элемента создаваемой матрицы в метрах
  COLORREF  Color;    // цвет, которым показывается элементы, с которых видны точки
  int       Reserved[63];
}
  BUILDVISIBLE;

// Построение матрицы видимости
// hmap    - основная карта
// hsit    - векторная карта с объектами, по которым строится матрица плотности
// mtqname - имя создаваемой матрицы
// hselect - объекты, по которым строится матрица (если = 0, то все объекты карты)
// parm    - параметры построения
// hwnd    - окно, которому посылаются сообщения WM_PROGRESSBAR с процентом
//           обработки в WPARAM (если = 0, то сообщения не посылаются)
// При ошибке возвращает 0

long int MTREXPORT mtrBuildVisibleMtq(HMAP hmap, HSITE hsit, const WCHAR *mtqname,
                                      HSELECT hselect, BUILDVISIBLE *parm, HMESSAGE hwnd);

} // extern "С"
#endif // MTREXAPI_H

