/****** MTLAPI.H *************** Gorbunov A.V.   ****** 06/09/16 ***
******* MTLAPI.H *************** Kruzhkov A.E.   ****** 24/10/00 ***
******* MTLAPI.H *************** Shabakov D.A.   ****** 08/12/03 ***
******* MTLAPI.H *************** Belenkov O.V.   ****** 11/09/16 ***
******* MTLAPI.H *************** Derevaygina Zh.A.***** 27/02/13 ***
******* MTLAPI.H *************** Борзов А.Ю.      ***** 14/03/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*            ОПИСАНИЕ ФУНКЦИЙ ДОСТУПА К МАТРИЦЕ СЛОЕВ              *
*                                                                  *
*   СТРУКТУРЫ :                                                    *
*                                                                  *
*   ПАРАМЕТРЫ СОЗДАНИЯ МАТРИЦЫ СЛОЕВ (MTLBUILDPARM, BUILDMTL)      *
*   ОПИСАНИЕ ОТКРЫТОЙ МАТРИЦЫ СЛОЕВ (MTLDESCRIBE)                  *
*                                                                  *
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

#ifndef MTLAPI_H
#define MTLAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // Описание структур интерфейса MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h" 
#endif

//------------------------------------------------------------------
//  ПАРАМЕТРЫ СОЗДАНИЯ МАТРИЦЫ СЛОЕВ                  25/04/14
//------------------------------------------------------------------
typedef struct BUILDMTL     // РАЗМЕР СТРУКТУРЫ 160 БАЙТ
{
  unsigned
  int StructSize;     // Размер данной структуры : sizeof (BUILDMTL)
  int Free;           // Должен быть ноль

  double   BeginX;    // Прямоугольные координаты начала
  double   BeginY;    // (юго-западного угла) матрицы в метрах

  double   EndX;      // Прямоугольные координаты окончания
  double   EndY;      // (северо - восточного угла) матрицы в метрах

  double   ElemSizeMeters; // Размер стороны элементарного участка
                           // в метрах на местности

  int LayerCount;     // Количество слоев

  int LayerForm;      // Форма представления инф-ции о слоях
                      // допустимые значения :
                      //  0 - мощности слоев
                      //  1 - абсолютые высоты

  int HeightSizeBytes; // Размер высоты рельефа в байтах
                       // допустимые значения :
                       //  0 - рельеф отсутствует,
                       //  2 - высоты "short int"
                       //  4 - высоты "long int"

  int LayerSizeBytes;  // Размер мощности слоя в байтах
                       // допустимые значения :
                       //  1 - мощности "unsigned char"
                       //  2 - мощности "unsigned short int"
                       //  4 - мощности "unsigned long int"

  int HeightMeasure;  // Eдиница измерения высоты
                      // допустимые значения :
                      //  0 - метры
                      //  1 - дециметры
                      //  2 - сантиметры
                      //  3 - миллиметры

  int LayerMeasure;   // Eдиница измерения мощности слоя
                      // допустимые значения
                      // - те же,что для HeightMeasure

  int UserType;       // Произвольное число, связываемое
                      // с создаваемой матрицей

  int Scale;          // Масштаб

  int BlockSide;      // Размер стороны блока матрицы в элементах
                      // допустимые значения : 0 - 64
                      //  (если равно 0, используется значение 64)

  int CodeCount;      // Количество кодов точек          10/06/08
  int MtdPointFormat; // Формат точки MTD-модели :       04/09/09
                      //   0 - структура точки MTDXYHC (16 байт)
                      //   1 - структура точки MTDXYHCLAS (24 байта)


  char Reserve[68];   // Должны быть нули
}
  BUILDMTL;


//------------------------------------------------------------------
//  ПАРАМЕТРЫ СОЗДАНИЯ МАТРИЦЫ СЛОЕВ (устаревшая структура)
//------------------------------------------------------------------
typedef struct MTLBUILDPARM     // РАЗМЕР СТРУКТУРЫ 128 БАЙТ
{
  unsigned
  long int StructSize;     // Размер данной структуры :
                           //  sizeof (MTRLAYERBUILDPARM)

  double   BeginX;         // Прямоугольные координаты начала
  double   BeginY;         // (юго-западного угла) матрицы в метрах

  double   EndX;           // Прямоугольные координаты окончания
  double   EndY;           // (северо - восточного угла) матрицы в метрах

  double   ElemSizeMeters; // Размер стороны элементарного участка
                           // в метрах на местности

  long int LayerCount;     // Количество слоев

  long int LayerForm;      // Форма представления инф-ции о слоях
                           // допустимые значения :
                           //  0 - мощности слоев
                           //  1 - абсолютые высоты

  long int HeightSizeBytes; // Размер высоты рельефа в байтах
                            // допустимые значения :
                            //  0 - рельеф отсутствует,
                            //  2 - высоты "short int"
                            //  4 - высоты "long int"

  long int LayerSizeBytes;  // Размер мощности слоя в байтах
                            // допустимые значения :
                            //  1 - мощности "unsigned char"
                            //  2 - мощности "unsigned short int"
                            //  4 - мощности "unsigned long int"

  long int HeightMeasure;  // Eдиница измерения высоты
                           // допустимые значения :
                           //  0 - метры
                           //  1 - дециметры
                           //  2 - сантиметры
                           //  3 - миллиметры

  long int LayerMeasure;   // Eдиница измерения мощности слоя
                           // допустимые значения
                           // - те же,что для HeightMeasure

  long int UserType;       // Произвольное число, связываемое
                           // с создаваемой матрицей

  long int Scale;          // Масштаб

  char     Reserve[52];     // Должны быть нули
}
  MTLBUILDPARM;


//------------------------------------------------------------------
//  ОПИСАНИЕ ОТКРЫТОЙ МАТРИЦЫ СЛОЕВ (размер структуры 1024 байта)
//------------------------------------------------------------------
typedef struct MTLDESCRIBE
{
  char  Name[260];              // ИМЯ ФАЙЛА МАТРИЦЫ
  char  MaterialFileName[260];  // ИМЯ ФАЙЛА ОПИСАНИЯ МАТЕРИАЛОВ

  long  LayerCount;      // КОЛ-ВО СЛОЕВ
  long  MaterialCount;   // КОЛ-ВО МАТЕРИАЛОВ

  double ElementInPlane; // РАЗМЕР ЭЛЕМЕНТА В МЕТРАХ НА МЕСТНОСТИ

  DFRAME FrameMeters;    // ГАБАРИТЫ МАТРИЦЫ В ПЛАНЕ (МЕТРЫ)

  double MinHeightValue; // МИНИМАЛЬНОЕ ЗНАЧЕНИЕ ВЫСОТЫ ЭЛЕМЕНТА В МАТРИЦЕ (МЕТРЫ)
  double MaxHeightValue; // МАКСИМАЛЬНОЕ ЗНАЧЕНИЕ ВЫСОТЫ ЭЛЕМЕНТА В МАТРИЦЕ (МЕТРЫ)

  double BotLevelHeight; // ВЫСОТА ЭЛЕМЕНТА МАТРИЦЫ НИЖНЕГО УРОВНЯ (МЕТРЫ)  // 24/10/00

  long   UserType;       // ТИП ПОЛЬЗОВАТЕЛЬСКИХ ДАННЫХ
  long   View;           // ПРИЗНАК ОТОБРАЖАЕМОСТИ
  long   UserLabel;      // ПОЛЬЗОВАТЕЛЬСКИЙ ИДЕНТИФИКАТОР
  long   ReliefPresence; // ПРИЗНАК НАЛИЧИЯ РЕЛЬЕФА  17/01/01

  double MaxSummaryPower; // МАКСИМАЛЬНАЯ СУММАРНАЯ МОЩНОСТЬ
                          // СЛОЕВ  (МЕТРЫ)  // 17/05/01

  char   Reserve[408];   // РЕЗЕРВ

}
  MTLDESCRIBE;

// МОЩНОСТЬ - РАССТОЯНИЕ МЕЖДУ ВЕРХНЕЙ И НИЖНЕЙ ТОЧКАМИ,
//            ОГРАНИЧИВАЮЩИМИ ОБ'ЕМНОЕ ТЕЛО ПО ОСИ,
//            ПЕРПЕНДИКУЛЯРНОЙ ГОРИЗОНТАЛЬНОЙ ПЛОСКОСТИ
//            (БЕЗЗНАКОВОЕ ЦЕЛОЕ ЧИСЛО).

//------------------------------------------------------------------
//  ОПИСАНИЕ ОТКРЫТОЙ МАТРИЦЫ СЛОЕВ                03/04/14
//------------------------------------------------------------------
typedef struct MTLDESCRIBEUN
{
  WCHAR Name[MAX_PATH_LONG];              // ИМЯ ФАЙЛА МАТРИЦЫ
  WCHAR MaterialFileName[MAX_PATH_LONG];  // ИМЯ ФАЙЛА ОПИСАНИЯ МАТЕРИАЛОВ

  DFRAME FrameMeters;     // ГАБАРИТЫ МАТРИЦЫ В ПЛАНЕ (МЕТРЫ)

  double ElementInPlane;  // РАЗМЕР ЭЛЕМЕНТА В МЕТРАХ НА МЕСТНОСТИ

  double MinHeightValue;  // МИНИМАЛЬНОЕ ЗНАЧЕНИЕ ВЫСОТЫ ЭЛЕМЕНТА В МАТРИЦЕ (МЕТРЫ)
  double MaxHeightValue;  // МАКСИМАЛЬНОЕ ЗНАЧЕНИЕ ВЫСОТЫ ЭЛЕМЕНТА В МАТРИЦЕ (МЕТРЫ)

  double BotLevelHeight;  // ВЫСОТА ЭЛЕМЕНТА МАТРИЦЫ НИЖНЕГО УРОВНЯ (МЕТРЫ)

  double MaxSummaryPower; // МАКСИМАЛЬНАЯ СУММАРНАЯ МОЩНОСТЬ СЛОЕВ  (МЕТРЫ)

  int   LayerCount;       // КОЛ-ВО СЛОЕВ
  int   MaterialCount;    // КОЛ-ВО МАТЕРИАЛОВ

  int   UserType;         // ТИП ПОЛЬЗОВАТЕЛЬСКИХ ДАННЫХ
  int   View;             // ПРИЗНАК ОТОБРАЖАЕМОСТИ

  int   UserLabel;        // ПОЛЬЗОВАТЕЛЬСКИЙ ИДЕНТИФИКАТОР
  int   ReliefPresence;   // ПРИЗНАК НАЛИЧИЯ РЕЛЬЕФА

  char  Reserve[64];      // РЕЗЕРВ

}
  MTLDESCRIBEUN;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ ОПИСАНИЕ ФУНКЦИЙ ДОСТУПА К МАТРИЦАМ СЛОЕВ +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{

  // Открыть матричные данные
  // Возвращает идентификатор открытой матричной карты (TMapAccess*)
  // mtrname - имя открываемого файла
  // mode - режим чтения/записи (GENERIC_READ, GENERIC_WRITE или 0)
  // GENERIC_READ - все данные только на чтение
  // При ошибке возвращает ноль

_MAPIMP HMAP _MAPAPI mapOpenMtl(const char * mtrname,long int mode = 0);
_MAPIMP HMAP _MAPAPI mapOpenMtlUn(const WCHAR *mtrname, long int mode = 0);  // 28/01/14


  // Открыть матричные данные в заданном районе работ
  // (добавить в цепочку матриц)
  // Возвращает номер файла в цепочке матриц
  // hMap - идентификатор открытой основной карты
  // mtrname - имя открываемого файла
  // mode - режим чтения/записи (GENERIC_READ, GENERIC_WRITE или 0)
  // GENERIC_READ - все данные только на чтение
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapOpenMtlForMap(HMAP hMap, const char * mtrname, long int mode);
_MAPIMP long int _MAPAPI mapOpenMtlForMapUn(HMAP hMap, const WCHAR * mtrname, long int mode);  // 28/01/14


  // Закрыть матричные данные
  // hMap - идентификатор открытой основной карты
  // number - номер закрываемой матрицы в цепочке матриц
  // если number == 0, закрываются все матричные данные

_MAPIMP void _MAPAPI mapCloseMtl(HMAP hMap,long int number = 0);

  // Закрыть матричные данные в заданном районе работ
  // hMap - идентификатор открытой основной карты
  // number - номер матричного файла в цепочке
  // Если number == 0, закрываются все матричные данные
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapCloseMtlForMap(HMAP hMap,
                                     long int number);

  // Построение матрицы на заданный участок района работ
  // При ошибке возвращает ноль
  // hMap    - идентификатор исходной карты для построения матрицы,
  // mtrname - полное имя файла создаваемой матрицы,
  // ininame - полное имя файла легенды создаваемой матрицы,
  // mtrparm - параметры создаваемой матрицы,
  // Структурa BUILDMTL описанa в mtlapi.h
  // hselect - идентификатор контекста отбора объектов карты,
  // handle  - идентификатор окна диалога, которому посылаются
  // сообщения о ходе процесса :
  //  0x0378 - сообщение о проценте выполненных работ (в WPARAM),
  //  если процесс должен быть принудительно завершен, в ответ
  //  должно вернуться значение 0x0378.
  // Если handle равно нулю - сообщения не посылаются.

_MAPIMP long int _MAPAPI mapBuildMtlEx(HMAP hMap,
                                 const char * mtrname,
                                 const char * ininame,
                                 BUILDMTL * mtrparm,
                                 HSELECT  hselect,
                                 HWND     handle);

_MAPIMP long int _MAPAPI mapBuildMtlUn(HMAP hMap,       // 10/06/16
                                 const WCHAR * mtrname,
                                 const WCHAR * ininame,
                                 BUILDMTL * mtrparm,
                                 HSELECT  hselect,
                                 HWND     handle);

  // Построение матрицы на заданный участок района работ (устаревшая)
  // При ошибке возвращает ноль
  // hMap    - идентификатор исходной карты для построения матрицы,
  // mtrname - полное имя файла создаваемой матрицы,
  // ininame - полное имя файла легенды создаваемой матрицы,
  // mtrparm - параметры создаваемой матрицы,
  // Структурa MTLBUILDPARM описанa в mtlapi.h
  // hselect - идентификатор контекста отбора объектов карты,
  // handle  - идентификатор окна диалога, которому посылаются
  // сообщения о ходе процесса :
  //  0x0378 - сообщение о проценте выполненных работ (в WPARAM),
  //  если процесс должен быть принудительно завершен, в ответ
  //  должно вернуться значение 0x0378.
  // Если handle равно нулю - сообщения не посылаются.

_MAPIMP long int _MAPAPI mapBuildMtl(HMAP hMap,
                               const char * mtrname,
                               const char * ininame,
                               MTLBUILDPARM * mtrparm,
                               HSELECT  hselect,
                               HWND     handle);


  /*********************************************************
  *                                                        *
  *           ЗАПРОС ДАННЫХ ИЗ МАТРИЦЫ СЛОЕВ               *
  *                                                        *
  *********************************************************/

  // Запросить описание файла матричных данных
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // describe - адрес структуры, в которой будет размещено
  // описание матрицы
  // Структурa MTLDESCRIBE описанa в mtlapi.h
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlDescribe(HMAP hMap,long int number,
                                     MTLDESCRIBE * describe);

_MAPIMP long int _MAPAPI mapGetMtlDescribeUn(HMAP hMap,long int number,  // 06/09/16
                                     MTLDESCRIBEUN * describe);

  // Запросить имя файла матричных данных
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP const char * _MAPAPI mapGetMtlName(HMAP hMap,long int number);

  // Запросить имя файла матричных данных
  // hMap - идентификатор открытой основной векторной карты
  // number - номер файла в цепочке
  // name - адрес строки для размещения результата
  // size - размер строки
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlNameUn(HMAP hMap,long int number,  // 28/01/14
                                         WCHAR *name, long int size);

  // Запросить число открытых файлов матричных данных
  // hMap - идентификатор открытой основной карты
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlCount(HMAP hMap);

  // Запросить максимальное количество слоев всех матриц MTL-цепочки
  // hMap - идентификатор открытой основной карты
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMaxLayerCount(HMAP hMap);

  // Запросить количество слоев матрицы с номером number в цепочке.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetLayerCountOfMtl(HMAP hMap,long int number);

  // Запросить минимальную высоту нижнего уровня
  // hMap - идентификатор открытой основной карты
  // При ошибке возвращает ERRORHEIGHT

_MAPIMP double _MAPAPI mapGetMinBotLevelHeight(HMAP hMap);    // 24/10/00

  // Запросить максимальную суммарную мощность слоев
  // hMap - идентификатор открытой основной карты
  // При ошибке возвращает ERRORPOWER

_MAPIMP double _MAPAPI mapGetMaxSummaryPower(HMAP hMap);    // 17/05/01

  // Выбор значения абсолютной высоты в заданной точке.
  // hMap - идентификатор открытой основной карты
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.

_MAPIMP double _MAPAPI mapGetElementHeight(HMAP hMap,double x,double y);

  // Выбор значения абсолютной высоты в заданной точке из матрицы
  // с номером number в цепочке.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.

_MAPIMP double _MAPAPI mapGetElementHeightOfMtl(HMAP hMap,long int number,double x,double y);

  // Выбор значения мощности слоя в заданной точке.
  // hMap - идентификатор открытой основной карты
  // layernumber - номер слоя
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение мощности слоя в метрах.
  // В случае ошибки и в случае необеспеченности заданной
  // точки матричными данными возвращает ERRORPOWER.

_MAPIMP double _MAPAPI mapGetElementPower(HMAP hMap,double x,double y,long layernumber);

  // Выбор значения мощности слоя в заданной точке из матрицы
  // с номером number в цепочке.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение мощности слоя в метрах.
  // В случае ошибки и в случае необеспеченности заданной
  // точки матричными данными возвращает ERRORPOWER.

_MAPIMP double _MAPAPI mapGetElementPowerOfMtl(HMAP hMap,long int number,
                                         double x,double y,long layernumber);

  // Вычисление значений мощностей слоев в заданной точке
  // методом треугольников по матрице с номером number в цепочке.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // Координаты точки задаются в метрах в системе координат
  // векторной карты
  // powers - адрес массива для записи вычисленных значений
  //          мощностей (в метрах)
  // count - размер массива, должен быть не менее mapGetLayerCountOfMtl()
  // Возвращает количество заполненных элементов массива powers
  // При ошибке возвращает ноль.

_MAPIMP long int _MAPAPI mapGetElementPowersTriangleOfMtl(HMAP hMap,long int number,
                                                    double x,double y,
                                                    double* powers,long int count);

  // Вычисление значения мощности слоя layernumber в заданной точке
  // методом треугольников по матрице с номером number в цепочке.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // Координаты точки задаются в метрах в системе координат
  // векторной карты
  // layernumber - номер слоя
  // Возвращает значение мощности слоя в метрах.
  // При ошибке возвращает ERRORPOWER.

_MAPIMP double _MAPAPI mapGetElementPowerTriangleOfMtl  
                   (HMAP hMap,long int number,
                    double x,double y,long int layernumber);

  // Занесение значения абсолютной высоты в элемент матрицы,
  // соответствующий заданной точке.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // Координаты точки (x,y) и значение высоты (h) задаются в метрах
  // в системе координат векторной карты.
  // В случае ошибки возвращает ноль.

_MAPIMP long int _MAPAPI mapPutElementHeight(HMAP hMap,long int number,
                                       double x, double y, double h);


  // Занесение значения мощности слоя layernumber в элемент,
  // соответствующий заданной точке.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // Координаты точки (x,y) и значение мощности (power) задаются
  // в метрах в системе координат векторной карты
  // layernumber - номер слоя
  // В случае ошибки возвращает ноль.

_MAPIMP long int _MAPAPI mapPutElementPower(HMAP hMap,long int number,
                                      double x,double y,double power,
                                      long int layernumber);

  // Запросить номер в цепочке для матрицы, расположенной
  // в заданной точке
  // hMap - идентификатор открытой основной карты
  // number - порядковый номер, найденной матрицы в точке
  // (1 - первая в данной точке, 2 - вторая ...)
  // В случае ошибки возвращает ноль.

_MAPIMP long int _MAPAPI mapGetMtlNumberInPoint(HMAP hMap,double x, double y,
                                          long int number);

  // Запросить номер в цепочке последней открытой матрицы
  // с установленным (равным 1) признаком видимости.
  // hMap - идентификатор открытой основной карты
  // В случае ошибки возвращает ноль.

_MAPIMP long int _MAPAPI mapGetMtlNumberLastVisible(HMAP hMap);

  // Запросить размер полного блока матрицы в байтах
  // hMap - идентификатор открытой основной карты
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlBlockSize(HMAP hMap,long int number);

  // Запросить вертикальный размер блока матрицы в элементах
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlBlockSide(HMAP hMap,long int number);  // 28/11/07

  // Запросить адрес блока матрицы по номеру строки и столбца
  // Блоки последнего ряда могут иметь усеченный размер
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При запросе следующего блока может вернуть прежний адрес
  // Возвращает адрес считанного блока
  // При ошибке возвращает ноль

_MAPIMP char *  _MAPAPI mapGetMtlBlockAddress(HMAP hMap,long int number,
                                                  long int row,
                                                  long int column);

  // Запросить число строк блоков матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlBlockRow(HMAP hMap,long int number);

  // Запросить число столбцов блоков матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlBlockColumn(HMAP hMap,long int number);

  // Запросить число строк элементов в матрице
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlElementRow(HMAP hMap,long int number);

  // Запросить число столбцов элементов в матрице
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlElementColumn(HMAP hMap,long int number);

  // Выбор массива значений абсолютных высот, соответствующих
  // логическим элементам, лежащим на заданном отрезке.
  // hMap - идентификатор открытой основной карты
  // Координаты точек, задающих начало и конец отрезка
  // (FirstPoint,SecondPoint) задаются в метрах в системе
  // координат векторной карты.
  // Размер массива высот, заданного адресом HeightArray,
  // должен соответствовать запрашиваемому количеству высот
  // (HeightCount), в противном случае возможны ошибки работы
  // с памятью.
  // В случае необеспеченности логического элемента матричными
  // данными его значение равно ERRORHEIGHT (-111111.0 м)
  // В случае ошибки при выборе высот возвращает ноль.

_MAPIMP long int _MAPAPI mapGetHeightArrayFromMtl(HMAP   hMap,
                                            double*   HeightArray,
                                            long int  HeightCount,
                                            const DOUBLEPOINT*  FirstPoint,  // 12/02/09 const
                                            const DOUBLEPOINT*  SecondPoint);


  // Выбор значения цвета слоя layernumber
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // В случае ошибки возвращает ноль.

_MAPIMP COLORREF _MAPAPI mapGetLayerColor(HMAP hMap,long int number,long int layernumber);

  // Выбор короткого имени (ключ семантики) слоя layernumber.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // В случае ошибки возвращает ноль.

_MAPIMP char* _MAPAPI mapGetLayerShortName(HMAP hMap,long int number,long int layernumber);

  // Выбор имени (название семантики) слоя layernumber.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // В случае ошибки возвращает ноль.

_MAPIMP char* _MAPAPI mapGetLayerLongName(HMAP hMap,long int number,long int layernumber);

  // Выбор максимальной мощности слоя layernumber в метрах.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // В случае ошибки возвращает ноль.

_MAPIMP long int _MAPAPI mapGetMaxLayerHeight(HMAP hMap,long int number,long int layernumber);

  // Установка максимальной мощности слоя layernumber в метрах.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // В случае ошибки возвращает ноль.

_MAPIMP long int _MAPAPI mapSetMaxLayerHeight(HMAP hMap,long int number,long int layernumber,long int maxlayerheight);

  // Установка значения цвета слоя layernumber.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // В случае ошибки возвращает ноль.

_MAPIMP long int _MAPAPI mapSetLayerColor(HMAP hMap,long int number,
                                    long int layernumber,
                                    COLORREF layercolor);

  // Установка короткого имени (ключ семантики) слоя layernumber.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // layername - короткое имя (ключ семантики)
  // В случае ошибки возвращает ноль.

_MAPIMP char* _MAPAPI mapSetLayerShortName(HMAP hMap,long int number,
                                     long int layernumber,
                                     char* layername);

  // Установка имени (название семантики) слоя layernumber.
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // layernumber - номер слоя
  // layername - название семантики
  // В случае ошибки возвращает ноль.

_MAPIMP char* _MAPAPI mapSetLayerLongName(HMAP hMap,long int number,
                                    long int layernumber,
                                    char* layername);

  // Запросить данные о проекции матричных данных
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // projectiondata - адрес структуры, в которой будут размещены
  // данные о проекции
  // Структурa MTRPROJECTIONDATA описанa в maptype.h
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlProjectionData
                     (HMAP hMap,long int number,
                      MTRPROJECTIONDATA * projectiondata);

  /*********************************************************
  *                                                        *
  *     ОПИСАНИЕ ФУНКЦИЙ ДЛЯ СОЗДАНИЯ МАТРИЦ СЛОЕВ         *
  *                                                        *
  *********************************************************/

  // Создать матричную карту
  // mtrname - полное имя файла матрицы
  // mtrparm - параметры создаваемой матрицы
  // Структурa BUILDMTL описанa в mtlapi.h
  // Возвращает идентификатор открытой матричной карты (TMapAccess*)
  // При ошибке возвращает ноль

_MAPIMP HMAP _MAPAPI mapCreateMtlEx(const char * mtrname, BUILDMTL * mtrparm);
_MAPIMP HMAP _MAPAPI mapCreateMtlUn(const WCHAR * mtrname, BUILDMTL * mtrparm);  // 28/01/14


  // Создать файл матрицы
  // hMap - идентификатор открытой основной карты
  // mtrname - полное имя файла матрицы
  // mtrparm - параметры создаваемой матрицы
  // mtrprojectiondata - параметры проекции создаваемой матрицы
  // Структурa BUILDMTL описанa в mtlapi.h
  // Структурa MTRPROJECTIONDATA описанa в maptype.h
  // Возвращает номер файла в цепочке матриц
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapCreateAndAppendMtlEx(HMAP hMap,
                                           const char * mtrname,
                                           BUILDMTL * mtrparm,
                                           MTRPROJECTIONDATA * mtrprojectiondata);

_MAPIMP long int _MAPAPI mapCreateAndAppendMtlUn(HMAP hMap,         // 28/01/14
                                           const WCHAR * mtrname,
                                           BUILDMTL * mtrparm,
                                           MTRPROJECTIONDATA * mtrprojectiondata);

  // Создать матричную карту (устаревшая)
  // mtrname - полное имя файла матрицы
  // mtrparm - параметры создаваемой матрицы
  // Возвращает идентификатор открытой матричной карты (TMapAccess*)
  // Структурa MTLBUILDPARM описанa в mtlapi.h
  // При ошибке возвращает ноль

_MAPIMP HMAP _MAPAPI mapCreateMtl(const char * mtrname,MTLBUILDPARM * mtrparm);

  // Создать файл матрицы (устаревшая)
  // hMap - идентификатор открытой основной карты
  // mtrname - полное имя файла матрицы
  // mtrparm - параметры создаваемой матрицы
  // mtrprojectiondata - параметры проекции создаваемой матрицы
  // Структурa MTLBUILDPARM описанa в mtlapi.h
  // Структурa MTRPROJECTIONDATA описанa в maptype.h
  // Возвращает  номер файла в цепочке матриц
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapCreateAndAppendMtl(HMAP hMap,
                                         const char * mtrname,
                                         MTLBUILDPARM * mtrparm,
                                         MTRPROJECTIONDATA * mtrprojectiondata);


  // Записать изменения матрицы в файл
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapSaveMtl(HMAP hMap,long int number);

  // Установить диапазон отображаемых элементов матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // minvalue - минимальное значение отображаемого элемента
  //            в единицах матрицы
  // maxvalue - максимальное значение отображаемого элемента
  //            в единицах матрицы
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapSetMtlShowRange(HMAP hMap,
                                      long int number,
                                      double minvalue,
                                      double maxvalue);

  // Установить нижний уровень слоев матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // botlevel - нижний уровень слоев в метрах
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapSetMtlBotLevel(HMAP hMap,
                                     long int number,
                                     double botlevel);

  // Установить максимальную суммарную мощность слоев матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // maxsummarypower - максимальная суммарная мощность в метрах
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapSetMtlMaxSummaryPower(HMAP hMap,
                                            long int number,
                                            double maxsummarypower);

  // Установить данные о проекции матричных данных
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // mapregister - адрес структуры, содержащей данные о проекции
  // Структуры MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM описаны в mapcreat.h
  // ttype  - тип локального преобразования координат (см. TRANSFORMTYPE в mapcreat.h) или 0
  // tparm - параметры локального преобразования координат (см. mapcreat.h)
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapSetMtlProjectionDataPro(HMAP hMap,          // 11/09/16
                                                    long int number,
                                                    MAPREGISTEREX  *mapregister,
                                                    DATUMPARAM     *datumparam,
                                                    ELLIPSOIDPARAM *ellipsoidparam,
                                                    long int ttype,
                                                    LOCALTRANSFORM * tparm);

_MAPIMP long int _MAPAPI mapSetMtlProjectionData(HMAP hMap,
                                           long int number,
                                           MAPREGISTEREX* mapregister);

  // Запросить данные о проекции матрицы
  // hMap   - идентификатор открытой основной векторной карты
  // number - номер файла в цепочке
  // mapregister - адрес структуры, в которой будут размещены
  // данные о проекции
  // Структурa MAPREGISTEREX описанa в mapcreat.h
  // ttype  - тип локального преобразования координат (см. TRANSFORMTYPE в mapcreat.h) или 0
  // tparm - параметры локального преобразования координат (см. mapcreat.h)
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlProjectionDataPro(HMAP hMap, long int number,     // 11/09/16
                                                    MAPREGISTEREX  *mapregister,
                                                    DATUMPARAM     *datumparam,
                                                    ELLIPSOIDPARAM *ellipsoidparam,
                                                    long int * ttype,
                                                    LOCALTRANSFORM * tparm);

_MAPIMP long int _MAPAPI mapGetMtlProjectionDataEx(HMAP hMap, long int number,
                                                   MAPREGISTEREX* mapregister);

  // Запрос - поддерживается ли пересчет к геодезическим
  // координатам из плоских прямоугольных и обратно
  // hMap     - идентификатор открытой основной карты
  // number   - номер файла в цепочке
  // Если нет - возвращает ноль

_MAPIMP long int _MAPAPI mapIsMtlGeoSupported(HMAP hMap, long int number);

  // Запросить параметры эллипсоида матрицы
  // hMap   - идентификатор открытой основной векторной карты
  // number - номер файла матрицы в цепочке
  // ellipsoidparam - адрес структуры, в которой будут размещены
  // параметры эллипсоида
  // Структурa ELLIPSOIDPARAM описанa в mapcreat.h
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlEllipsoidParam(HMAP hMap, long int number,  // 16/12/10
                                                 ELLIPSOIDPARAM * ellipsoidparam);

  // Установить параметры эллипсоида матрицы
  // hMap    - идентификатор открытой основной векторной карты
  // number  - номер файла матрицы в цепочке.
  // ellipsoidparam - адрес структуры, содержащей параметры эллипсоида
  // Структурa ELLIPSOIDPARAM описанa в mapcreat.h
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapSetMtlEllipsoidParam(HMAP hMap, long int number,  // 16/12/10
                                                 const ELLIPSOIDPARAM * ellipsoidparam);

  // Запросить коэффициенты трансформирования геодезических координат матрицы
  // hMap   - идентификатор открытой основной векторной карты
  // number - номер файла матрицы в цепочке
  // datumparam - адрес структуры, в которой будут размещены
  // коэффициенты трансформирования геодезических координат
  // Структурa DATUMPARAM описанa в mapcreat.h
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlDatumParam(HMAP hMap, long int number,  // 16/12/10
                                             DATUMPARAM * datumparam);

  // Установить коэффициенты трансформирования геодезических координат матрицы
  // hMap    - идентификатор открытой основной векторной карты
  // number  - номер файла матрицы в цепочке.
  // datumparam - адрес структуры, содержащей коэффициенты трансформирования
  // геодезических координат
  // Структурa DATUMPARAM описанa в mapcreat.h
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapSetMtlDatumParam(HMAP hMap, long int number,  // 16/12/10
                                             const DATUMPARAM * datumparam);

  /*********************************************************
  *                                                        *
  *   ОПИСАНИЕ ФУНКЦИЙ ДЛЯ РАБОТЫ С РАМКОЙ МАТРИЦЫ СЛОЕВ   *
  *                                                        *
  *********************************************************/

  // Установить рамку матрицы по метрике замкнутого объекта
  // Замкнутый объект должен иметь не менее 4-х точек
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // number     - номер файла в цепочке
  // info       - замкнутый объект карты
  // После выполнения функции отображение матрицы ограничится заданной областью
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapSetMtlBorder(HMAP hMap,long int number,HOBJ info);

  // Запросить объект рамки матрицы               // 15/03/01
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlBorder(HMAP hMap,long int number,HOBJ info);

  // Удалить рамку матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // После выполнения функции отображение матрицы будет полным
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapDeleteMtlBorder(HMAP hMap,long int number);

  // Определение существования рамки матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // Если рамка матрицы существует возвращает 1, иначе возвращает 0

_MAPIMP long int _MAPAPI mapCheckExistenceMtlBorder(HMAP hMap,long int number);

  // Определение способа отображения матрицы(относительно рамки)    // 02/10/03
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // Возвращает 1 - при отображении матрицы по рамке
  //            0 - при отображении матрицы без учета рамки
  // При ошибке возвращает -1

_MAPIMP long int _MAPAPI mapCheckShowMtlByBorder(HMAP hMap,long int number);

  // Установка отображения матрицы по рамке               // 29/05/09
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // value = 1 - отобразить матрицы по рамке
  //       = 0 - отобразить матрицы без учета рамки
  //  При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapShowMtlByBorder(HMAP hMap, long int number, int value);

  // Определить координаты и порядковый номер точки рамки, которая // 02/20/03
  // входит в прямоугольник Габариты растра(матрицы) и
  // имеет наименьшее удаление от точки pointIn (координаты в метрах)
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // По адресу pointOut записываются координаты найденной точки в метрах
  // При ошибке или отсутствии рамки возвращает ноль

_MAPIMP long int _MAPAPI mapGetImmediatePointOfMtlBorder(HMAP hMap, long int number,
                                           DOUBLEPOINT* pointIn,
                                           DOUBLEPOINT* pointOut);

  // Запросить координаты Юго-Западного угла матрицы в метрах     // 29/05/09
  // hMap    - идентификатор открытой основной векторной карты
  // number  - номер файла в цепочке
  // По адресу x,y записываются координаты найденной точки в метрах
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapWhereSouthWestMtlPlane(HMAP hMap,long int number,
                                                   double * x, double * y);  

  // Запросить фактические габариты отображаемой матрицы в метрах в районе работ   // 14/05/03
  // При отображение матрицы по рамке возвращаются габариты рамки
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetActualMtlFrame(HMAP hMap,DFRAME *frame, long int number);

  // Запросить масштаб матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlScale(HMAP hMap,long int number);

  // Запросить значения масштаба нижней и верхней границ видимости матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // По адресу bottomScale записывается знаменатель масштаба нижней границы видимости матрицы
  // По адресу topScale записывается знаменатель масштаба верхней границы видимости матрицы
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlRangeScaleVisible(HMAP hMap,long int number, long int *bottomScale, 
                                                    long int *topScale);  // 08/12/03

  // Установить значения масштаба нижней и верхней границ видимости матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // bottomScale - знаменатель масштаба нижней границы видимости матрицы
  // topScale    - знаменатель масштаба верхней границы видимости матрицы
  // при невыполнении условия bottomScale <= topScale возвращает ноль
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapSetMtlRangeScaleVisible(HMAP hMap,long int number, long int bottomScale, 
                                                    long int topScale);   // 08/12/03


  // Запросить активную матрицу
  // (устанавливается приложением по своему усмотрению)
  // hMap - идентификатор открытой карты
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetActiveMtl(HMAP hMap);  // 29/05/09

  // Установить активную матрицу
  // (устанавливается приложением по своему усмотрению)
  // hMap - идентификатор открытой карты
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapSetActiveMtl(HMAP hMap, long int number);  // 29/05/09

  // Запросить флаг редактируемости матрицы                 // 18/06/09
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // При ошибке возвращает ноль

_MAPIMP  long int _MAPAPI mapGetMtlEdit(HMAP hMap,long int number);


  // Запросить размер файла             // 28/09/09
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // По адресу fileSize записывается размер файла
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlFileSize(HMAP hMap,long int number,__int64 * fileSize);

  // Запросить ширину матрицы (элементы)             // 28/09/09
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlWidthInElement(HMAP hMap,long int number);

  // Запросить высоту матрицы (элементы)             // 28/09/09
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlHeightInElement(HMAP hMap,long int number);

  // Запросить точность (метр/элем) матрицы             // 28/09/09
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlAccuracy(HMAP hMap,long int number);

  // Запросить флаг изменения привязки (метры) матрицы             // 28/09/09
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetMtlFlagLocationChanged(HMAP hMap,long int number);

  /*********************************************************
  *                                                        *
  *          УПРАВЛЕНИЕ ОТОБРАЖЕНИЕМ МАТРИЦЫ               *
  *                                                        *
  *********************************************************/

  // Запросить/Установить степень видимости матрицы
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // view = 0 - нет видимости
  // view = 1 - полная
  // view = 2 - насыщенная
  // view = 3 - полупрозрачная
  // view = 4 - средняя
  // view = 5 - прозрачная

_MAPIMP long int _MAPAPI mapGetMtlView(HMAP hMap,long int number);
_MAPIMP long int _MAPAPI mapSetMtlView(HMAP hMap,long int number,
                                           long int view);

  // Запросить/Установить порядок отображения матрицы        // 27/05/09
  // hMap - идентификатор открытой основной карты
  // number - номер матрицы в цепочке
  // order  - порядок отображения (0 - под картой, 1 - над картой)
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapSetMtlViewOrder(HMAP hMap, long int number,
                                            long int order);
_MAPIMP long int _MAPAPI mapGetMtlViewOrder(HMAP hMap, long int number);

  // Поменять очередность отображения матриц (mtl) в цепочке  // 27/02/13
  // oldNumber - номер файла в цепочке
  // newNumber - устанавливаемый номер файла в цепочке
  // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapChangeOrderMtlShow(HMAP hMap, long int oldNumber,
                                                          long int newNumber);
}

#endif // MTLAPI_H
