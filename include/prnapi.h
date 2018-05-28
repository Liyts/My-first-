/****** PRNAPI.H *************** Kruzhkov  A.E.  ****** 24/12/09 ***
******* PRNAPI.H *************** Dishlenko S.G.  ****** 11/04/02 ***
******* PRNAPI.H *************** Shabakov  D.A.  ****** 25/12/13 ***
******* PRNAPI.H *************** Belenkov  O.V.  ****** 30/11/06 ***
******* PRNAPI.H *************** Vitsko    D.A.  ****** 13/04/06 ***
******* PRNAPI.H *************** Gorbunov  A.V.  ****** 04/09/08 ***
******* PRNAPI.H *************** Derevyagina Zh.A.***** 16/02/16 ***
******* PRNAPI.H *************** Kruzhkova  E.A. ****** 15/05/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*       ФУНКЦИИ РАБОТЫ С ДИАЛОГОМ ПЕЧАТИ ЭЛЕКТРОННОЙ КАРТЫ         *
*                                                                  *
*                   mapprint.dll, gisforms.dll                     *
*                                                                  *
*******************************************************************/

#ifndef PRNAPI_H
#define PRNAPI_H

/*******************************************************************
  ПОРЯДОК РАБОТЫ С ДИАЛОГОМ ПЕЧАТИ КАРТЫ :
********************************************************************

  // Загрузить принтер
  HPRINTER printer = prnLoadPrinter();

  // Вызвать диалог печати
  // (печать выбранного фрагмента карты производится
  //  автоматически при нажатии кнопки "Печать")
  ret = prnMapPrint(hmap, printer, printparm, taskparm);

  // При успешном выполнении диалога возвращаемое значение не равно 0
  if (ret != 0)
  {
    // Закрытие диалога при помощи кнопки "Выбрать"
    if (printparm->Regime == MPR_SELECTFRAME)
    {
      // Вызвать пользовательскую функцию выбора прямоугольной области
      // ...
    }

    // Закрытие диалога при помощи кнопки "Изменить"
    if (printparm->Regime == MPR_CHANGEFRAME)
    {
      // Вызвать пользовательскую функцию изменения прямоугольной области
      // ...
    }
  }

  // Освободить принтер
  prnFreePrinter(printer);

********************************************************************
  ОСОБЕННОСТИ :
********************************************************************

1. Функция prnMapPrint имеет несколько режимов работы. Она может
   использоваться:
   a) для настройки принтера и параметров печати (MPR_INITPARM);
   б) для запуска печати с установленными параметрами без вызова
      диалога (MPR_PRINTONLY) - при организации поточной печати;
   в) для запуска печати из диалога (MPR_PRINTALL, MPR_PRINT,
      MPR_SELECTFRAME, MPR_CHANGEFRAME). В режиме MPR_PRINTALL
      область печати устанавливается по габаритам района
      принудительно;
   г) для настройки принтера, параметров печати, выбора и изменения
      области печати. При нажатии на кнопки "Выбрать" и "Изменить"
      диалог закрывается с сохранением всех параметров, поле Regime
      устанавливается равным MPR_SELECTFRAME или MPR_CHANGEFRAME.

2. При сохранении идентификатора принтера printer на время работы
   приложения выбранный в диалоге принтер и его настройки сохраняются.

3. При первом входе все поля структуры printparm могут быть нулевыми,
     кроме поля Length. Это поле должно содержать размер структуры
     MAPPRINTPARM.
   При сохранении объекта printparm и многократных вызовах диалога
     выбранные в диалоге настройки печати сохраняются.
   При отображении карты в принтерном режиме (VT_PRINT) в окне
     с идентификатором Handle и изменении интенсивности заливки
     площадных объектов производится изменение вида карты (перерисовка)
     с учетом значения интенсивности. При Handle равном нулю окно
     карты не обновляется.

4. Поле Handle объекта taskparm должно содержать идентификатор
   главного окна. Структура TASKPARM описана в maptype.h.
   Если в TASKPARM установлено полное имя файла ".hlp",
   то этот файл должен содержать топик с номером 5037,
   который будет вызываться при нажатии кнопки "Помощь".

*******************************************************************/

#ifndef MAPTYPE_H
  #include "maptype.h"   // Описание структур интерфейса MAPAPI
#endif


#ifdef WIN32API                                // 16/02/16
#if defined(PRINT_DLL)
 #define _PRINTAPI  WINAPI
 #define _PRINTIMP  __declspec( dllexport )
#else
 #define _PRINTAPI  WINAPI
 #define _PRINTIMP  __declspec( dllimport )
#endif
#else
#if defined(PRINT_DLL)
 #define _PRINTAPI  WINAPI
 #define _PRINTIMP
#else
 #define _PRINTAPI  WINAPI
 #define _PRINTIMP
#endif
#endif

struct MAPPRINTPARM;
struct MAPPRINTPARMEX;
struct PRINTERINFO;                                     // 24/12/09

extern "C"
{

 // Загрузить принтер

_PRINTIMP HPRINTER _PRINTAPI prnLoadPrinter();


 // Освободить принтер

_PRINTIMP void _PRINTAPI prnFreePrinter(HPRINTER printer);


 // Печать карты
 //  hmap      - идентификатор карты
 //  printer   - идентификатор устройства печати
 //  printparm - параметры диалога печати карты (поле Length должно
 //              содержать размер структуры)
 //  taskparm  - параметры задачи (поле Handle должно содержать
 //              идентификатор главного окна)
 //  title     - заголовок диалога
 // При ошибке возвращает 0

_PRINTIMP long int _PRINTAPI prnMapPrint(HMAP hmap, HPRINTER printer,
                                        MAPPRINTPARM* printparm,
                                        TASKPARM* taskparm);

_PRINTIMP long int _PRINTAPI prnMapPrintTitle(HMAP hmap, HPRINTER printer,
                                             MAPPRINTPARM* printparm,
                                             TASKPARM* taskparm, char* title);

_PRINTIMP long int _PRINTAPI prnMapPrintEx(HMAP hmap, HPRINTER printer,
                                          MAPPRINTPARMEX* printparm,
                                          TASKPARM* taskparm, char* title);

 // Выбор фрагмента печати карты с обрезкой
 //  hmap      - идентификатор карты
 //  printer   - идентификатор устройства печати
 //  printparm - параметры диалога печати (поле Length должно
 //              содержать размер структуры)
 //  parm      - параметры задачи (поле Handle должно содержать
 //              идентификатор главного окна)
 //  title     - заголовок диалога
 // Вырезанный фрагмент карты записывается в подкаталог ..\Print
 // каталога основного документа (проект Print.mpt).
 // Проект Print.mpt содержит вырезанные по выбранной рамке
 // части векторных, растровых и матричных данных.
 // При ошибке возвращает 0

_PRINTIMP long int _PRINTAPI prnMapPrintSelect(HMAP hmap, HPRINTER printer,
                                              MAPPRINTPARMEX* printparm,
                                              TASKPARM* parm, char* title);

// Запросить текущие характеристики устройства печати
//   printer     - идентификатор устройства печати приложения:
//                 (HPRINTER)(MapWindow->GetPrinter()).
//                 Если printer = 0, то запрашиваются характеристики
//                 устройства печати, установленного в Windows по умолчанию)
//   printerinfo - содержит характеристики устройства печати
// При ошибке возвращает 0

_PRINTIMP long int _PRINTAPI prnPrinterInfo(HPRINTER printer,
                                           PRINTERINFO* printerinfo);  // 24/12/09

} // extern "C"

//-----------------------------------------------------------------
// ПАРАМЕТРЫ ДИАЛОГА ПЕЧАТИ КАРТЫ
//-----------------------------------------------------------------

typedef struct MAPPRINTPARM
{
  int  Length;          // Длина структуры MAPPRINTPARM
#ifdef _M_X64                                                                   // 25/12/13
  int  MapPrintParmZero;// Выравнивание                                         // 25/12/13
#endif
  HWND Handle;          // Идентификатор окна карты
                                                           // 0x008 (8)
  int  Scale;           // Масштаб печати (знаменатель)
  int  ScaleSave;       // Масштаб печати (сохраняется при FitToPage = 1)
                                                           // 0x010 (16)
  RECT RectMetr;        // Прямоугольник печати в районе (в метрах)
                                                           // 0x020 (32)
  int  ShiftLTmm;       // Смещение (в миллиметрах)
  int  ShiftUPmm;       //
                                                           // 0x028 (40)
  int  FieldLTmm;       // Поля страницы (в миллиметрах)
  int  FieldUPmm;       //
  int  FieldRTmm;       //
  int  FieldDNmm;       //
                                                           // 0x038 (56)
  int  Intensity;       // Интенсивность заливки площадных (0-100)
  int  Copies;          // Количество копий
                                                           // 0x040 (64)
  char Regime;          // Режим работы задачи (см. MAPPRINT_REGIME)
  char Preview;         // Режим работы окна (см. MAPPRINT_PREVIEW)
  char TypePrint;       // Тип печати (см. MAPPRINT_TYPE)
  char TypeOutput;      // Тип вывода (см. MAPPRINT_OUTPUT)
                                                           // 0x044 (68)
  char Orientation;     // Ориентация (см. MAPPRINT_ORIENT)
  char File;            // Флаг устройства вывода (1 - файл, 0 - принтер)
  char Border;          // Флаг вывода рамки (1 - есть, 0 - нет)
  char FitToPage;       // Согласование с размером страницы
                        //   (см. MAPPRINT_FITTING)
  char Black;           // Флаг черно-белой печати (1 - есть, 0 - нет)
  char Calibration;     // Флаг учета коэффициентов калибровки
                        //   (1 - учитывать, 0 - нет)
  char Mirror;          // Флаг зеркального вывода (1 - есть, 0 - нет)
  char Reserve;         // Резерв (должен быть обнулен)
                                                           // 0x04C (76)
  char FileName[260];   // Имя файла печати
}                                                          // 0x150 (336)
  MAPPRINTPARM;


typedef struct MAPPRINTPARMEX
{
  int Length;          // Длина структуры MAPPRINTPARM
#ifdef _M_X64                                                                   // 25/12/13
  int MapPrintZero;     // Выравнивание                                         // 25/12/13
#endif
  HWND Handle;          // Идентификатор окна карты
                                                           // 0x008 (8)
  int  Scale;           // Масштаб печати (знаменатель)
  int  ScaleSave;       // Масштаб печати (сохраняется при FitToPage = 1)
                                                           // 0x010 (16)
  RECT RectMetr;        // Прямоугольник печати в районе в метрах
                        // (Если обнулен - расчитывается по габаритам района).
                        // При заданных габаритах выбранной области
                        // (PlaneFrame) игнорируется
                                                           // 0x020 (32)
  int  ShiftLTmm;       // Смещение (в миллиметрах)
  int  ShiftUPmm;       //
                                                           // 0x028 (40)
  int  FieldLTmm;       // Поля страницы (в миллиметрах)
  int  FieldUPmm;       //
  int  FieldRTmm;       //
  int  FieldDNmm;       //
                                                           // 0x038 (56)
  int  Intensity;       // Интенсивность заливки площадных (0-100)
  int  Copies;          // Количество копий
                                                           // 0x040 (64)
  char Regime;          // Режим работы задачи (см. MAPPRINT_REGIME)
  char Preview;         // Режим работы окна (см. MAPPRINT_PREVIEW)
  char TypePrint;       // Тип печати (см. MAPPRINT_TYPE)
  char TypeOutput;      // Тип вывода (см. MAPPRINT_OUTPUT)
                                                           // 0x044 (68)
  char Orientation;     // Ориентация (см. MAPPRINT_ORIENT)
  char File;            // Флаг устройства вывода (1 - файл, 0 - принтер)
  char Border;          // Флаг вывода рамки (1 - есть, 0 - нет)
  char FitToPage;       // Согласование с размером страницы
                        //   (см. MAPPRINT_FITTING)
  char Black;           // Флаг черно-белой печати (1 - есть, 0 - нет)
  char Calibration;     // Флаг учета коэффициентов калибровки
                        //   (1 - учитывать, 0 - нет)
  char Mirror;          // Флаг зеркального вывода (1 - есть, 0 - нет)
  char CutLine;         // Флаг вывода линий обрезки (1 - есть, 0 - нет)
                        //   (при OverlapLT, OverlapUP,
                        //    OverlapRT или OverlapDN > 0) // 0x04C (76)
  char FileName[260];   // Имя файла печати
                                                           // 0x150 (336)
  int  OverlapLTmm;     // Поля перекрытия изображения соседних
  int  OverlapUPmm;     //       страниц (в миллиметрах)
  int  OverlapRTmm;     //
  int  OverlapDNmm;     //
                                                           // 0x160 (352)
  double PageWidth;     // Размеры печатаемой области страницы за вычетом
  double PageHeight;    // полей перекрытия (в миллиметрах)
                                                           // 0x170 (368)
  double Angle;         // Угол поворота карты (в радианах)
                                                           // 0x178 (376)
  DFRAME PlaneFrame;    // Габариты выбранной области в метрах
                        // (Если обнулен - расчитывается по габаритам района).
                        //  X1,Y1 - 1 точка прямоугольной области
                        //  X2,Y2 - 3 точка прямоугольной области
                        // При TurnFrame = 1, считать 1 и 3 точки вершинами
                        // наклонного прямоугольника, на неповернутой карте
                                                           // 0x198 (408)
  HSITE SiteDecor;      // Зарамочное оформление (должен быть обнулен)
                                                           // 0x19C (412)
  int  FrameKey;        // Номер объекта карты, по которому устанавливается
                        // габариты области печати PlaneFrame
                        // (Если равен 0 или объект отсутствует,
                        //  то параметр игнорируется)
                                                           // 0x1A0 (416)

#ifdef _M_X64                                                                   // 25/12/13
  int MapPrintAddZero;  // Выравнивание                                         // 25/12/13
#endif
  char FrameList[32];   // Имя листа (номенклатура) объекта FrameKey
                                                           // 0x1C0 (448)
  int  PaperWidth;      // Размер листа (в миллиметрах)
  int  PaperHeight;     //
                                                           // 0x1C8 (456)
  char ReserveEx[48];   // Резерв (должен быть обнулен)

  unsigned
  char PageCountHor;    // Число страниц по горизонтали                         // 15/05/14
                        // (используется при FitToPage = MPF_FITBYHOR)
  unsigned
  char PageCountVer;    // Число страниц по вертикали
                        // (используется при FitToPage = MPF_FITBYVER)

  char FileCount;       // Число формируемых файлов (используется при PostScript = 1)
                        //   (1 - файл содержит все составляющие цвета C,M,Y,K или R,G,B
                        //    4 - каждый из четырех файлов содержит одну из
                        //        составляющих цвета C,M,Y,K)
                                                             // 0x1FB (507)
  char ColorModel;      // Цветовая модель вывода в PostScript
                        //   (0 - RGB, 1 - CMYK)
  char PostScript;      // Флаг PostScript-вывода
  char Restore;         // Флаг необходимости восстановления параметров
                        //   из INI-файла карты (1 - есть, 0 - нет)
  char TurnFrame;       // Флаг поворота области выбора (1 - есть, 0 - нет)
  char Decoration;      // Флаг зарамочного оформления (должен быть обнулен)
}                                                          // 0x200 (512)
  MAPPRINTPARMEX;

//-----------------------------------------------------------------
// ЗНАЧЕНИЯ ПОЛЕЙ СТРУКТУРЫ ДИАЛОГА ПЕЧАТИ КАРТЫ
//-----------------------------------------------------------------

enum MAPPRINT_REGIME         // РЕЖИМ РАБОТЫ ЗАДАЧИ "ПЕЧАТЬ КАРТЫ"
{
  MPR_PRINTONLY       = -2,  // Запуск печати карты без вызова диалога

  MPR_INITPARM        = -1,  // Загрузка диалога только для настройки
                             //  принтера и параметров печати (кнопки
                             //  "Выбрать" и "Изменить" отключены)

  MPR_PRINTALL        =  0,  // Загрузка диалога для настройки принтера,
                             //  параметров печати и запуска печати карты
                             //  с инициализацией печатаемой области по
                             //  габаритам района (RectMetr - игнорируется)

  // Эти флаги используются для загрузки диалога настройки принтера 
  // параметров печати и запуска печати карты с инициализацией
  // печатаемой области из RectMetr
  MPR_PRINT           =  1,  // Печать
  MPR_SELECTFRAME     =  2,  // Выбор прямоугольной рамки 
  MPR_CHANGEFRAME     =  3,  // Изменение и перемещение прямоугольной рамки
  MPR_MOVEFRAME       =  4,  // Только перемещение прямоугольной рамки
  MPR_SELECTBYOBJECT  =  5,  // Выбор объекта и установка прямоугольной рамки
                             // по габаритам объекта

  MPR_SELECTTURNFRAME = 10,  // Флаг выбора повернутого фрагмента

  // Значения, принимаемые полем Regime при нажатии на кнопки:
  // "Печать"     - MPR_PRINT;
  // "Выбрать"    - MPR_SELECTFRAME или MPR_SELECTTURNFRAME;
  // "Изменить"   - MPR_CHANGEFRAME или 
  //                MPR_MOVEFRAME (при FitToPage = MPF_ACCORDTOPAGE);
  // "По объекту" - MPR_SELECTBYOBJECT.
  // После выбора, изменения или перемещения области печати можно
  // вызвать диалог повторно не изменяя значения поля Regime.
};

enum MAPPRINT_PREVIEW   // РЕЖИМ РАБОТЫ ОКНА ПРЕДВАРИТ. ПРОСМОТРА
{
  MPV_SCHEME      = 0,  // Печатаемая область на фоне схемы
  MPV_MAP         = 1,  // Печатаемая область на фоне карты
  MPV_INFO        = 2,  // Информация об устройстве печати
};

enum MAPPRINT_TYPE      // ТИП ПЕЧАТИ
{
  MPT_NORMAL      = 3,  // Нормальный
  MPT_TRANSPARENT = 4,  // Прозрачный
  MPT_CONTOUR     = 5,  // Контурный
};

enum MAPPRINT_OUTPUT    // ТИП ВЫВОДА
{
  // Используются простейшие функции WIN API (для печати)

  MPO_VECTORIAL   = 0,  // Векторный (вывод только векторных карт)
  MPO_RASTERIAL   = 1,  // Растровый (вывод карт, растров и матриц)

  // Используются макрофункции WIN API (для экспорта в PostScript-файл)

  MPO_VECTORIALEX = 4,  // Векторный специальный
};

enum MAPPRINT_ORIENT    // ОРИЕНТАЦИЯ
{
  MPN_DEFAULT     = 0,  // Взять из умалчиваемых свойств принтера
  MPN_PORTRAIT    = 1,  // Книжная
  MPN_LANDSCAPE   = 2,  // Альбомная
};

enum MAPPRINT_FITTING   // СОГЛАСОВАНИЕ
{
  MPF_SPLITTOPAGES= 0,  // Разбить постранично
  MPF_FITTOPAGE   = 1,  // Растянуть на страницу
  MPF_ACCORDTOPAGE= 2,  // По размеру страницы
  MPF_FITBYHOR    = 3,  // Растянуть по горизонтали                  // 15/05/14
                        // (на заданное количество страниц)
  MPF_FITBYVER    = 4,  // Растянуть по вертикали
};


//-----------------------------------------------------------------
// ПАРАМЕТРЫ ПЕЧАТИ КАРТЫ  для функций Print (mappaint.h, mapacces.h)
//-----------------------------------------------------------------

typedef struct PRINTPARM
{
  int  Length;          // Длина структуры PRINTPARM
  int  Scale;           // Масштаб печати (знаменатель)

  char TypePrint;       // Тип печати (см. MAPPRINT_TYPE)
  char TypeOutput;      // Тип вывода (см. MAPPRINT_OUTPUT)
  char Mirror;          // Флаг зеркального вывода (1 - есть, 0 - нет)
  char ColorModel;      // Цветовая модель вывода карты (0 - RGB, 1 - CMYK)  // 19/02/04
  char Technology;      // Технология (тип устройства)
                        //   DT_PLOTTER    = 0  -  Векторный плоттер
                        //   DT_RASDISPLAY = 1  -  Растровый дисплей
                        //   DT_RASPRINTER = 2  -  Растровый принтер
                        //   DT_METAFILE   = 5  -  Метафайл
  char Reserve[17];     // Резерв (должен быть обнулен)
  char Service;         // Служебный флаг (должен быть обнулен)             // 04/09/12
  char DontClip;        // Область обрезки                                  // 08/04/11 

  double HorPixInInch;  // Пикселов на дюйм по горизонтали
  double VerPixInInch;  // Пикселов на дюйм по вертикали
}
  PRINTPARM;


//-----------------------------------------------------------------
// СЛУЖЕБНАЯ СТРУКТУРА ПАРАМЕТРОВ для функций построения зарамочного оформления
//-----------------------------------------------------------------

typedef struct FRAMEPRINTPARAM
{
    int DeleteSite;     // Признак удаления Site после печати
    int TurnFrame;      // Тип рамки (0 - прямая, 1 - наклонная)
    DFRAME PlaneFrame;  // Габариты рамки повернутые
    DFRAME ExpandFrame; // Расширенные повернутые габариты рамки
    double Angle;       // Угол наклона рамки
    HSITE SiteDecor;    // Зарамочное оформление
    int EnableSite;     // Запрет/разрешение редактирования Sit
#ifdef _M_X64                                                                   // 25/12/13
    int FramePrintZero; // Выравнивание                                         // 25/12/13
#endif
}
  FRAMEPRINTPARAM;


//-----------------------------------------------------------------
// ХАРАКТЕРИСТИКИ УСТРОЙСТВА ПЕЧАТИ
//-----------------------------------------------------------------

typedef struct PRINTERINFO                              // 24/12/09
{
  char   DeviceName[256];    // Имя устройства печати
  char   Reserve[512];       // Резерв

  double PaperWidth;         // Текущие ширина и высота печатаемой страницы
  double PaperHeight;        // устройства печати в миллиметрах

  double PixDeviceInMeterX;  // Текущие разрешения устройства печати
  double PixDeviceInMeterY;  // по горизонтали и вертикали в точках на метр
}
  PRINTERINFO;


#endif // PRNAPI_H

