/****  VECEXAPI.H    **********  Belenkov  O.V.  *****  02/09/16 ***
*****  VECEXAPI.H    **********  Konon  V.N.     *****  07/06/13 ***
*****  VECEXAPI.H    **********  Shabakov D.A.   *****  07/08/14 ***
*****  VECEXAPI.H    **********  Derevyagina Zh.A.****  02/10/15 ***
*****  VECEXAPI.H    **********  Dishlenko S.G.  *****  17/11/15 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                     FOR  WINDOWS & LINUX                         *
*                                                                  *
********************************************************************
*                                                                  *
*                 ПРИМЕР ВЫЗОВА ДИАЛОГА:                           *
*                                                                  *
*   // Загрузка библиотеки                                         *
*   HINSTANCE libInst = ::LoadLibrary("gisvecex.dll");             *
*                                                                  *
*   // Вызов функции                                               *
*   typedef long int (WINAPI * MAPSORTING)(HMAP hMap,              *
*                                          HMESSAGE handle,        *
*                                          long int mode);         *
*                                                                  *
*   MAPSORTING mapsorting = (MAPSORTING)                           *
*                   GetProcAddress(libInst, "MapSortProcess");     *
*                                                                  *
*   long int rezult = (*mapsorting)(hMap, hWnd, mode);             *
*                                                                  *
*   // Выгрузка библиотеки                                         *
*   ::FreeLibrary(libInst);                                        *
*                                                                  *
*******************************************************************/

#if !defined(VECEXAPI_H)
#define VECEXAPI_H

#ifndef MMSTRUCT_H
  #include "mmstruct.h"
#endif

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

#ifdef WIN32API
   #define HMESSAGE HWND
#else
   #define HMESSAGE MSGHANDLER
#endif

#ifdef WIN32API      
#if defined(VECEX_DLL)
 #define _VECAPI  WINAPI
 #define _VECIMP  __declspec( dllexport )
#else
 #define _VECAPI  WINAPI
 #define _VECIMP  __declspec( dllimport )
#endif
#else
#if defined(VECEX_DLL)
 #define _VECAPI  WINAPI
 #define _VECIMP
#else
 #define _VECAPI  WINAPI
 #define _VECIMP
#endif
#endif

enum SXFFORMATFLAG
 {
   DATAMETERS       = 0,  // Метрика в метрах
   DATARADIANS      = 4,  // Метрика в радианах
   DATADEGREES      = 8,  // Метрика в градусах
 };

extern "C"
{
 // Запросить паспортные данные из файлов SXF, TXF, MAP, SIT, SITX     // 12/06/15
 // по имени файла 
 // name - имя файла карты в одном из вышеперечисленных форматов
 // Структуры MAPREGISTER и LISTREGISTER описаны в mapcreat.h
 // rscname - адрес буфера для записи имени классификатора (может быть 0)
 // rsize - длина буфера в байтах
 // sheetname - адрес буфера для записи длинного имени карты (может быть 0)
 // ssize - длина буфера в байтах
 // securitycode - адрес поля для записи кода степени секретности (может быть 0)
 // ( 0 - не установлено, 1 - открытая информация (unclassified), 
 // 2 - информация с ограниченным доступом (restricted),
 // 3 - информация для служебного пользования (confidential),
 // 4 - секретная информация (secret), 5 - совершенно секретная информация (topsecret))
 // Возвращает число объектов в карте
 // При ошибке возвращает ноль
 
_VECIMP long int _VECAPI mapGetAnySxfInfoByNamePro(const WCHAR * name, MAPREGISTEREX * mapreg,
                                                  LISTREGISTER * sheet,
                                                  WCHAR * rscname, long int rsize,
                                                  WCHAR * sheetname, long int ssize,
                                                  long int * securitycode);
                                                  
_VECIMP long int _VECAPI mapGetAnySxfInfoByNameUn(const WCHAR * name, MAPREGISTEREX * mapreg,
                                                 LISTREGISTER * sheet);
_VECIMP long int _VECAPI mapGetAnySxfInfoByName(const char * name,
                                               MAPREGISTEREX * mapreg,
                                               LISTREGISTER * sheet);

 // Запросить имя классификатора (RSC) из файлов SXF, TXF, MAP (SIT)
 // В файлах SXF и TXF имя классификатора (RSC) может отсутствовать
 // rscname - адрес буфера для записи имени классификатора
 // size - длина буфера в байтах
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI GetRscNameFromAnySxfUn(const WCHAR * name, WCHAR * rscname, long int size);
_VECIMP long int _VECAPI GetRscNameFromAnySxf(const char * name, char * rscname, long int size);
_VECIMP long int _VECAPI GetRscNameFromSxfUn(const WCHAR * name, WCHAR * rscname, long int size);
_VECIMP long int _VECAPI GetRscNameFromSxf(const char * name, char * rscname, long int size);

 // Запросить имя карты из файлов SXF, TXF, MAP (SIT)
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI GetSheetNameFromAnySxfUn(const WCHAR * name,
                                                 WCHAR * sheetname, long int size);
_VECIMP long int _VECAPI GetSheetNameFromAnySxf(const char * filename, char * sheetname,
                                               long int size);

 // Запросить контрольную сумму файла SXF
 // name - имя файла SXF
 // При ошибке возвращает ноль и выдает сообщение на экран
 // Ноль - допустимое значение контрольной суммы

_VECIMP long int _VECAPI GetSxfCheckSumUn(const WCHAR * name);
_VECIMP long int _VECAPI GetSxfCheckSum(const char * name);

 // Проверить контрольную сумму файла SXF
 // name - имя файла SXF
 // При успешной проверке возвращает 1
 // При несовпадении контрольной суммы возвращает -1
 // При ошибке структуры файла возвращает -2
 // При устаревшей версии структуры файла возвращает -3
 // При ошибке доступа к данным возвращает ноль и выдает сообщение на экран (если выдача сообщений разрешена)

_VECIMP long int _VECAPI SxfCheckSumUn(const WCHAR * name);

 // Выполнить контроль структуры данных карты
 // hMap,hSite - идентификаторы карты (см.MAPAPI.H),
 // mode       - режим работы (0 - контроль, 1 - редактирование),
 // handle     - идентификатор окна диалога процесса обработки (HWND для Windows).
 //
 // Окну диалога посылаются следующие сообщения :
 //  WM_LIST   = 0x586   WParam - количество листов в районе
 //                      LParam - номер текущего листа
 //  WM_OBJECT = 0x585   WParam - процент обработанных объектов
 //  WM_ERROR  = 0x587   WParam - порядковый номер объекта или 0
 //                      LParam = 1 - ошибка в карте
 //                             = 2 - ошибка в классификаторе
 //                             = 3 - ошибка в описании объекта
 //                             = 4 - ошибка в метрике
 //                             = 5 - ошибка в семантике
 //                             = 6 - ошибка в графике
 // Возвращает количество ошибок в районе

_VECIMP long int _VECAPI mapStructControl(HMAP hMap,HSITE hSite,
                                         long int mode,HMESSAGE handle);

 // Сортировка всех карт, входящих в документ
 // hmap   - идентификатор сортируемого документа
 // handle - идентификатор окна диалога процесса обработки (HWND)
 // mode   - комбинация флагов способа обработки карты:
 //   0 - сортировать все листы,
 //   1 - только несортированные;
 //   2 - сохранять файлы отката;
 //   4 - повысить точность хранения в метрах, число знаков максимальное;
 //  16 - повысить точность хранения в метрах, формат - см  (2 знака);
 //  32 - повысить точность хранения в метрах, формат - мм  (3 знака);
 //  64 - повысить точность хранения в радианах, число знаков максимальное;
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI MapSortProcess(HMAP hmap, HMESSAGE handle, long int mode);

 // Запрос числа элементов (SXF,TXF,MAP,...) в DIR
 // В списке элементов файла DIR могуть быть растры и матрицы
 // dirname - полное имя файла DIR
 // При ошибке возвращает ноль
 
_VECIMP long int _VECAPI GetDirItemCount(const char * dirname);

_VECIMP long int _VECAPI GetDirItemCountUn(const WCHAR * dirname);               // 07/08/14

 // Запрос названия района или первой карты в списке (SXF,TXF,MAP,...) в DIR
 // dirname - полное имя файла DIR
 // name    - адрес буфера для размещения запрошенного имени
 // size    - размер буфера
 // При успешном выполнении возвращает число элементов в списке
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI GetDirAreaName(const char * dirname, char * name, long int size);

_VECIMP long int _VECAPI GetDirAreaNameUn(const WCHAR * namedir, WCHAR * name, long int size);   // 26/05/14

 // Запрос списка имен файлов данных (SXF,TXF,MAP,...) в DIR
 // dirname - полное имя файла DIR
 // items   - адрес буфера для размещения заполненной структуры NAMESARRAY
 //           (см. mmstruct.h)
 // size    - размер буфера; должен быть не меньше, чем размер струткруры
 //           для числа элементов, равного GetDirItemCount()
 //           size = sizeof(NAMESARRAY) + sizeof(LISTSNAME) * (count - 1);
 // При успешном выполнении возвращает число элементов в списке
 // При ошибке возвращает ноль
 
_VECIMP long int _VECAPI GetDirItemList(const char * dirname,
                                       NAMESARRAY * items, long int size);
_VECIMP long int _VECAPI GetDirItemListUn(const WCHAR * dirname,
                                         NAMESARRAY * items, long int size);


 // Заполнить метрику объекта координатами рамки листа карты          // 14/06/15
 // из файлов SXF, TXF, MAP, SIT, SITX
 // name - имя файла карты в одном из вышеперечисленных форматов
 // HOBJ - идентификатор объекта, созданного на той карте, где будет сохранен объект
 // Координаты будут пересчитаны из системы координат файла к системе координат выходной карты
 // Если объекта-рамки нет в наборе данных, то запишутся координаты габаритов набора данных
 // Если у исходного объекта имелись координаты, то они будут удалены 
 // Объект-рамка ищется по коду SHEETFRAMEEXCODE (91000000)
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI GetBorderMetricsFromAnySxfUn(const WCHAR * name, HOBJ hobj);
                                              

 // Сформировать обзорное изображение карты в формате PNG               // 16/06/15
 // из файлов SXF, TXF, MAP, SIT, SITX
 // Изображение строится из цетральной части карты в базовом масштабе карты
 // sxfname - имя файла карты в одном из вышеперечисленных форматов
 // imagename - имя файла PNG с обзорным изображением, если равно 0, 
 //           то к полному имени файла карты добавляется ".preview.png"
 // width   - ширина изображения (обычно 512)
 // height  - высота изображения (обычно 512)
 // rscname - имя цифрового классификатора для карт формата SXF и TXF,
 //           если равно нулю, то ищется в SXF или TXF
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI BuildPreviewImageFromAnySxfUn(const WCHAR * sxfname,
                                                      const WCHAR * imagename, 
                                                      long int width, long int height,
                                                      const WCHAR * rscname);
                                              
 //========================================================================
 //   Функции импорта, экспорта и обновления карты для форматов SXF, TXF и DIR
 //========================================================================
 //  Окну диалога посылаются следующие сообщения :
 //  WM_LIST   = 0x586   WParam - количество листов в районе
 //                      LParam - номер текущего листа
 //  WM_OBJECT = 0x585   WParam - процент обработанных объектов
 //  WM_INFOLIST = 0x584 LParam - адрес структуры INFOLIST
 // ----------------------------------------------------------------

 // Загрузить (импортировать) карту из файла SXF, TXF или DIR с
 // использованием Select с преобразованием топокарты к зоне документа
 // Файлы SXF и TXF могут хранить координаты в метрах, радианах или градусах
 // hmap    - идентификатор открытой карты (рекомендуется указывать
 //           для определения текущей зоны топокарты) или 0;
 // sxfname - имя загружаемого файла типа SXF, TXF или DIR;
 // rscname - имя файла классификатора, с которым загружается карта,
 //           имя классификатора можно запросить из SXF (TXF) функцией GetRscNameFromSxf
 //           или из карты; для файла DIR может быть 0;
 // mapname - имя создаваемой карты (обычно совпадает с именем SXF (TXF))
 //           или ноль или указатель на пустую строку (буфер размером MAX_PATH
 //           c нулевым байтом равным нулю) или указатель на папку для размещения
 //           карты. Если имя карты не задано или задана только папка, то карта
 //           создается с именем SXF (TXF) и расширением ".sit". Если namemap
 //           указывает на буфер достаточной длины (size), то в буфер записывается 
 //           имя созданной карты;
 //           Для файла DIR тип общей карты - MPT (проект данных, включающий все 
 //           открытые карты из DIR) или MAP (многолистовая карта);
 // size    - длина буфера, на который указывает переменная namemap, или 0. Обычно длина
 //           равна MAX_PATH_LONG (1024);
 // handle  - идентификатор окна диалога, которому посылаются уведомительные 
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux);
 // select  - фильтр загружаемых объектов и слоев, если необходима выборочная
 //           обработка данных;
 // frscfromsxf - значение флажка "разрешить использование
 //               имени классификатора, указанного в файле sxf"
 // typesit - тип создаваемых карт в проекте MPT при импорте DIR (1- SIT; -1- SITX)
 // password - пароль для создания защищенного хранилища карты (SITX)
 // psize    - длина пароля в байтах
 // transform - признак необходимости трансформировать загружаемую карту в систему координат hmap
 //             (если hmap и transform не равно 0)
 // Для добавления открытой карты в документ необходимо вызвать функцию
 // mapAppendData(hmap, namemap). Если mapname содержит имя карты типа MAP и
 // она содержит хотя бы один лист, то при импорте данных выполняется создание
 // нового листа в карте MAP. В этом случае функция mapAppendData не должна вызываться. 
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI ImportFromAnySxfProM(HMAP hmap, const WCHAR * namesxf,
                                            const WCHAR * namersc,  WCHAR * namemap, long int size,
                                            HMESSAGE handle, HSELECT select, long int frscfromsxf,
                                            long int typesit, const WCHAR * password, long int psize,
                                            long int transform);

_VECIMP long int _VECAPI ImportFromAnySxfPro(HMAP          hmap,
                                            const WCHAR * namesxf,
                                            const WCHAR * namersc,
                                            WCHAR *       namemap,
                                            long int      size,
                                            HMESSAGE      handle,
                                            HSELECT       select,
                                            long int      frscfromsxf,
                                            long int      typesit,
                                            const WCHAR * password, long int psize);

 // Загрузить (импортировать) карту из файла DIR
 // frscfromsxf - значение флажка "разрешить использование
 // имени классификатора, указанного в файле sxf"

_VECIMP long int _VECAPI ImportFromAnySxfEx(HMAP hmap,
                                         const char * sxfname,
                                         const char * rscname,
                                         char * mapname,
                                         long int size,
                                         HMESSAGE handle,
                                         HSELECT select,
                                         long int     frscfromsxf);
                                         
 // Загрузить карту из файла SXF, TXF или DIR с использованием Select
 // с преобразованием топокарты к зоне документа
 // Файлы SXF и TXF могут хранить координаты в метрах, радианах или градусах
 // namedir - имя загружаемого файла типа DIR;
 // namemap - имя создаваемой карты
 //           или ноль или указатель на пустую строку (буфер размером 1024 символа
 //           c нулевым байтом равным нулю) или указатель на папку для размещения
 //           карты. Если namemap указывает на буфер достаточной длины (size),
 //           то в буфер записывается имя созданной карты;
 //           Для файла DIR тип общей карты - MPT (проект данных, включающий все
 //           открытые карты из DIR) или MAP (многолистовая карта);
 // size    - длина буфера, на который указывает переменная namemap или 0. Обычно длина
 //           равна 2048 байт;
 // handle  - идентификатор окна диалога, которому посылаются уведомительные
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux) или 0;
 // typesit  - тип создаваемых карт в проекте MPT при импорте DIR (1- SIT; -1- SITX)
 // password - пароль доступа к данным, из которого формируется 256-битный код
 //            для шифрования данных (при утрате данные не восстанавливаются) или 0
 // psize    - длина пароля в байтах или 0
 // crscode  - указатель на строку с кодом системы координат, к которой преобразуются
 //            данные или 0. Примеры строки: "EPSG:3857", "crslist:80070050"
 //            В первом случае преобразование выполняется в систему 3857 (проекция Меркатора на шаре),
 //            во втором - к параметрам, считанным из файла crslist.xml по коду 80070050,
 //            то есть, к некоторой пользовательской системе координат, описанной в файле crslist.xml.
 // callevent - адрес функции обратного вызова для получения уведомлений о проценте загруженных данных (см. maptype.h)
 // parm      - параметр, передаваемый в функцию обратного вызова (например, адрес класса обработки сообщений)
 // logfile   - путь к файлу журнала работы программы (может быть 0)
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI ImportFromDirPro(const WCHAR* namedir, WCHAR* namemap, long int size,
                                          HMESSAGE handle, long int typesit, const WCHAR * password, long int psize,
                                          const char * crscode, EVENTSTATE callevent, void * parm,
                                          const WCHAR * logfile);

 // Обновить карту из файла SXF, TXF или DIR с использованием Select
 // с преобразованием топокарты к зоне документа
 // Файлы SXF и TXF могут хранить координаты в метрах, радианах или градусах
 // hmap    - идентификатор открытой карты (для определения текущей
 //           зоны топокарты) или 0;
 // sxfname - имя загружаемого файла типа SXF, TXF или DIR;
 // mapname - имя обновляемой карты; может быть ноль или указатель на пустую 
 //           строку, в этом случае обновляемая карта в документе ищется 
 //           по совпадению номенклатур.
 //           Если namemap указывает на буфер достаточной длины (size), 
 //           то в буфер записывается имя обновленной карты;
 //           Если карты не было в документе - она может быть создана (добавлена) 
 // size    - длина буфера, на который указывает переменная namemap или 0. Обычно длина
 //           равна MAX_PATH (256);
 // handle  - идентификатор окна диалога, которому посылаются уведомительные 
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux);
 // select  - фильтр загружаемых объектов и слоев, если необходима выборочная 
 //           обработка данных;
 // mode    - режим обновления данных:
 //           0 - поиск записей по совпадению уникального номера в карте и 
 //               исходном файле и обновление,
 //               если объект не найден, то добавление объекта;
 //           1 - добавление объектов с новыми уникальными номерами в те карты,
 //               номенклатуры которых совпадают с номенклатурой SXF (TXF),
 //               если - номенклатура не найдена, то добавляется новый лист (карта);
 //           2 - добавление объектов с новыми уникальными номерами в заданную
 //               карту без учета номенклатур
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UpdateFromAnySxf(HMAP hmap,
                                         const char * sxfname,
                                         char * mapname,
                                         long int size,
                                         HMESSAGE handle,
                                         HSELECT select,
                                         long int mode);

_VECIMP long int _VECAPI UpdateFromAnySxfUn(HMAP hmap,                           // 07/08/14
                                         const WCHAR * sxfname,
                                         WCHAR * mapname,
                                         long int size,
                                         HMESSAGE handle,
                                         HSELECT select,
                                         long int mode);

 // Загрузить карту из файла SXF, TXF или DIR с использованием Select           // 17/07/16
 // с преобразованием топокарты к зоне документа
 // Файлы SXF и TXF могут хранить координаты в метрах, радианах или градусах
 // namedir - имя загружаемого файла типа DIR;
 // namemap - имя создаваемой карты
 //           или ноль или указатель на пустую строку (буфер размером 1024 символа
 //           c нулевым байтом равным нулю) или указатель на папку для размещения
 //           карты. Если namemap указывает на буфер достаточной длины (size),
 //           то в буфер записывается имя созданной карты;
 //           Для файла DIR тип общей карты - MPT (проект данных, включающий все
 //           открытые карты из DIR) или MAP (многолистовая карта);
 // size    - длина буфера, на который указывает переменная namemap или 0. Обычно длина
 //           равна 2048 байт;
 // handle  - идентификатор окна диалога, которому посылаются уведомительные
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux) или 0;
 // callevent - адрес функции обратного вызова для получения уведомлений о проценте загруженных данных (см. maptype.h)
 // parm      - параметр, передаваемый в функцию обратного вызова (например, адрес класса обработки сообщений)
 // logfile   - путь к файлу журнала работы программы (может быть 0)
 // mode    - режим обновления данных:
 //           0 - поиск записей по совпадению уникального номера в карте и
 //               исходном файле и обновление,
 //               если объект не найден, то добавление объекта;
 //           1 - добавление объектов с новыми уникальными номерами в те карты,
 //               номенклатуры которых совпадают с номенклатурой SXF (TXF);
 //           2 - добавление объектов с новыми уникальными номерами в заданную
 //               карту без учета номенклатур;
 //           3 - замена листов или добавление новых листов (карт).
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UpdateFromDirPro(const WCHAR* namedir, WCHAR* namemap, long int size, long int mode,
                                          HMESSAGE handle, EVENTSTATE callevent, void * parm,
                                          const WCHAR * logfile);

 // Сохранить (экспортировать) карту в двоичный формат SXF
 // mapname - имя файла сохраняемой карты;
 // list    - номер листа для многолистовой карты или 1;
 // sxfname - имя создаваемого файла SXF, обычно совпадает с
 //           именем карты, но имеет расширение SXF;
 // flag    - вид хранимых координат (0 - метры, 4 - радианы
 //           для карты, поддерживающей геодезические координаты,
 //           -1 - определить по виду координат на карте);
 //           Если карты не было в документе - она может быть создана (добавлена)
 // handle  - идентификатор окна диалога, которому посылаются уведомительные
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux);
 // select  - фильтр выгружаемых объектов и слоев, если необходима выборочная
 //           обработка данных;
 // flserv  - записать служебный объект c датумом и эллипсоидом и имя классификатора
 //           (поддерживается с версии 10.7 и выше) 
 // Для топокарт, хранящих координаты в метрах, координаты всегда хранятся
 // в зоне, указанной в паспорте карты
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI ExportToSxfEx(const char * mapname, long int list,
                                    const char * sxfname, long int flag,
                                    HMESSAGE handle, HSELECT select, long int flserv);

_VECIMP long int _VECAPI ExportToSxfUn(const WCHAR * mapname,                    // 07/08/14
                                      long int list,
                                      const WCHAR * sxfname,
                                      long int flag,
                                      HMESSAGE handle,
                                      HSELECT select,
                                      long int flserv);

 // Сохранить (экспортировать) карту в текстовый формат TXF
 // mapname - имя файла сохраняемой карты;
 // list    - номер листа для многолистовой карты или 1;
 // txfname - имя создаваемого файла TXF, обычно совпадает с
 //           именем карты, но имеет расширение SXF;
 // flag    - вид хранимых координат (0 - метры, 4 - радианы, 8 - градусы,
 //           для карты, поддерживающей геодезические координаты,
 //           -1 - определить по виду координат на карте);
 //           Если карты не было в документе - она может быть создана (добавлена)
 // precision - число знаков после запятой для координат в метрах или 0;
 //             если карта имеет паспортную точность в см (2 знака) или
 //             в мм (3 знака), то precision игнорируется;
 // isutf8    - признак записи названий файлов, имени листа карты, текстов подписей и 
 //             текстовых семантик в кодировке utf8 (если значение поля ненулевое,
 //             иначе - в кодировке ANSI)
 // handle    - идентификатор окна диалога, которому посылаются уведомительные 
 //             сообщения (HWND для Windows, CALLBACK-Функция для Linux);
 // select    - фильтр выгружаемых объектов и слоев, если необходима выборочная 
 //             обработка данных;
 // Для топокарт, хранящих координаты в метрах, координаты всегда хранятся
 // в зоне, указанной в паспорте карты
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI ExportToTxfPro(const WCHAR * mapname,        // 22/01/16
                                        long int list,
                                        const WCHAR * txfname,
                                        long int flag,
                                        long int precision,
                                        long int isutf8,
                                        HMESSAGE handle,
                                        HSELECT select);

_VECIMP long int _VECAPI ExportToTxf(const char * mapname,
                                    long int list,
                                    const char * txfname,
                                    long int flag,
                                    long int precision, 
                                    HMESSAGE handle,
                                    HSELECT select);

_VECIMP long int _VECAPI ExportToTxfUn(const WCHAR * mapname,
                                      long int list,
                                      const WCHAR * txfname,
                                      long int flag,
                                      long int precision,
                                      HMESSAGE handle,
                                      HSELECT select);

 // Сохранить (экспортировать) карту в формат DIR
 // hmap    - идентификатор открытых данных
 // dirname - имя создаваемого файла DIR, обычно совпадает с
 //           именем открытого проекта или главной карты, но имеет расширение DIR;
 // type    - тип создаваемых файлов (0 - SXF, 1 - TXF);
 // flag    - вид хранимых координат (0 - метры, 4 - радианы, 8 - градусы,
 //           для карты, поддерживающей геодезические координаты,
 //           -1 - определить по виду координат на карте);
 //           Если карты не было в документе - она может быть создана (добавлена)
 // total   - признак сохранения в DIR только главной карты (0) или всех карт
 //           документа (1);
 // precision - для файлов TXF число знаков после запятой для координат в метрах или 0;
 //           если карта имеет паспортную точность в см (2 знака) или
 //           в мм (3 знака), то precision игнорируется;
 // handle  - идентификатор окна диалога, которому посылаются уведомительные
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux);
 // select  - фильтр выгружаемых объектов и слоев, если необходима выборочная
 //           обработка данных;
 // frsc    - записать имя классификатора в файл sxf (если не равно 0)
 // utf8    - записать имена файлов и файлы TXF (если type равен 1) в кодировке UTF8
 // Для топокарт, хранящих координаты в метрах, координаты всегда хранятся
 // в зоне, указанной в паспорте карты
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI ExportToDirEx(HMAP hmap, const char * dirname,
                                    long int type, long int flag,
                                    long int total, long int precision,
                                    HMESSAGE handle, HSELECT select, long int frsc);

_VECIMP long int _VECAPI ExportToDirUn(HMAP hmap, const WCHAR * dirname,
                                      long int type, long int flag, long int total,
                                      long int precision, HMESSAGE handle,
                                      HSELECT select, long int frsc, long int isutf8);

 // Проверить корректность архива в ZIP-файле                    // 09/05/16
 // (zip-архив может выдаваться по запросу из Банка данных ЦК и ДЗЗ)
 // zipfile - путь к архиву
 // error   - код ошибки (ошибка доступа может быть и при корректном архиве)
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI CheckZipValidate(const WCHAR * zipfile, long int * error);

 // Распаковать ZIP-файл в заданную папку                        
 // zipfile - путь к архиву
 // folder  - путь к папке для распаковки архива
 // logfile - путь к текстововому файлу протоколу распаковки архива (может быть 0)
 // error   - поле для записи кода ошибки распаковки архива
 // message - признак выдачи сообщения об ошибке на экран
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UnZipToFolder(const WCHAR * zipfile, const WCHAR * folder,
                                       const WCHAR * logfile, long int * error,
                                       long int message);

 // Распаковать список файлов из ZIP-файла в заданную папку      
 // zipfile - путь к архиву
 // folder  - путь к папке для распаковки архива
 // extlist - список указателей на имена файлов, которые нужно распаковать в заданную папку
 // extcount - число указателей в списке (массиве указателей)
 // logfile - путь к текстововому файлу протоколу распаковки архива (может быть 0)
 // error   - поле для записи кода ошибки распаковки архива
 // message - признак выдачи сообщения об ошибке на экран
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UnZipToFolderEx(const WCHAR * zipfile, const WCHAR * folder,
                                         const char ** extlist, long  int extcount,
                                         const WCHAR * logfile, long int * error,
                                         long int message);

 // Распаковать заданный файл из ZIP-файла в память
 // zipfile  - путь к архиву
 // filename - имя распаковываемого файла
 // logfile - путь к текстововому файлу протоколу распаковки архива (может быть 0)
 // error   - поле для записи кода ошибки распаковки архива
 // message - признак выдачи сообщения об ошибке на экран
 // При ошибке возвращает ноль, иначе - идентификатор данных в памяти
 // Для получения данных используется функция UnZipMemoryPoint
 // После считывания данных необходимо освободить ресурсы функцией UnZipFreeMemory

_VECIMP HANDLE _VECAPI UnZipFileToMemory(const WCHAR * zipfile, const WCHAR * filename,
                                         const WCHAR * logfile, long int * error,
                                         long int message);

 // Запросить адрес и размер буфера распакованного файла по идентификатору буфера
 // При ошибке возвращает ноль

_VECIMP const char * _VECAPI UnZipMemoryPoint(HANDLE hmemory, long int * size);

 // Освободить буфер распакованного файла по идентификатору буфера

_VECIMP void _VECAPI UnZipFreeMemory(HANDLE hmemory);

 // Запросить статистику по содержанию ZIP-архива (исходный размер, размер в zip,
 // процент сжатия, дата и время создания файла, имя файла)
 // zipfile - путь к архиву 
 // logfile - путь к текстововому файлу протоколу для записи статистики
 // error   - поле для записи кода ошибки распаковки архива 
 // message - признак выдачи сообщения об ошибке на экран 
 // При ошибке возвращает ноль 

_VECIMP long int _VECAPI UnZipInfo(const WCHAR * zipfile, const WCHAR * logfile, 
                                   long int * error, long int message);

 // Запросить список файлов в ZIP-архиве
 // zipfile - путь к архиву
 
// error   - поле для записи кода ошибки распаковки архива
 // message - признак выдачи сообщения об ошибке на экран
 // При ошибке возвращает ноль, иначе - идентификатор данных в памяти
 // Для получения данных используется функция UnZipMemoryPoint
 // После считывания данных необходимо освободить ресурсы функцией UnZipFreeMemory

_VECIMP HANDLE _VECAPI UnZipFileList(const WCHAR * zipfile,
                                     long int * error, long int message);

 // Запросить наличие файлов заданного типа в ZIP-архиве
 // zipfile - путь к архиву
 // extend  - строка со списком расширений (окончаний) файлов, разделенных пробелом
 //           например: "sxf,txf,rsc,.meta.xml,.geojson,gml"
 //           Окончания файлов могут быть в любом регистре, длина строки до 2048 байт
 // amounts - список счетчиков файлов с заданным расширением в zip-архиве
 // count   - число счетчиков и число расширений в списке
 // error   - поле для записи кода ошибки распаковки архива
 // message - признак выдачи сообщения об ошибке на экран
 // При ошибке возвращает ноль, иначе - число обработанных расширений

_VECIMP long int _VECAPI UnZipFileCount(const WCHAR * zipfile, const char * extend,
                                        long int * amounts, long int count,
                                        long int * error, long int message);


 // ================================================================
 //
 //                      УСТАРЕВШИЕ ФУНКЦИИ                         // 03/05/10
 //
 //              Реализованы через вызов новых функций
 // ================================================================

 // Загрузить карту из файла SXF
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadSxfToMap(char * namesxf,
                                     char * namemap,
                                     char * namersc,
                                     HMESSAGE handle);

 // Загрузить карту из файла SXF с использованием Select
 // При ошибке возвращает ноль
 
_VECIMP long int _VECAPI LoadSxfToMapSelect(char * namesxf,
                                           char * namemap,
                                           char * namersc,
                                           HMESSAGE handle,
                                           HSELECT select);

 // Загрузить карту из файла SXF с использованием Select 
 // и изменением имени карты
 // Параметры name и namehdr - не обрабатываются
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadSxfToMapSelectName(char * namesxf,
                                               char * namemap,
                                               char * namersc,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char * namehdr);

 // Загрузить карту из файла TXF
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadTxtToMap(char * nametxt,
                                     char * namemap,
                                     char * namersc,
                                     HMESSAGE handle);

 // Загрузить карту из файла TXF с испльзованием Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadTxtToMapSelect(char * nametxt,
                                           char * namemap,
                                           char * namersc,
                                           HMESSAGE handle,
                                           HSELECT select);


 // Загрузить карту из файла TXF с испльзованием Select и изменением имени
 // Параметры name и namehdr - не обрабатываются
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadTxtToMapSelectName(char * nametxt,
                                               char * namemap,
                                               char * namersc,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char * namehdr);

 // Загрузить карту по списку DIR
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadDirToMap(char* namedir,
                                     char* namemap,
                                     HMESSAGE handle);

 // Загрузить карту по списку DIR с использованием  Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadDirToMapSelect(char* namedir,
                                           char* namemap,
                                           HMESSAGE handle,
                                           HSELECT select);

 // Загрузить карту по списку DIR с использованием  Select и 
 // изменением имени района и имени файла ресурсов
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadDirToMapSelectName(char* namedir,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char* namersc);

 // Загрузить карту по данным из другого района
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadMapToMap(HMAP  map,
                                     char * namemap,
                                     HMESSAGE handle);

 // Загрузить карту по данным другого района с использованием  Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI LoadMapToMapSelect(HMAP map,
                                           char* namemap,
                                           HMESSAGE handle,
                                           HSELECT select);

 // Обновить карту из файла SXF
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UpdateMapFromSxf(char* namesxf,
                                         char* namemap,
                                         HMESSAGE handle);

 // Обновить карту из файла SXF с использованием Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UpdateMapFromSxfSelect(char* namesxf,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // Обновить карту по данным другого района с использованием  Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UpdateMapToMapSelect(HMAP map,
                                             const char* namemap,
                                             HMESSAGE handle,
                                             HSELECT select);

 // Добавить в карту данные из файла SXF с использованием Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI AppendMapFromSxfSelect(char* namesxf,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // Обновить карту из файла TXF
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UpdateMapFromTxt(char* nametxt,
                                         char* namemap,
                                         HMESSAGE handle);

 // Обновить карту из файла TXF с использованием Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UpdateMapFromTxtSelect(char* nametxt,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // Добавить в карту данные из файла TXF с использованием Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI AppendMapFromTxtSelect(char* namesxf,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // Обновить карту из файла DIR с использованием Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI UpdateMapFromDirSelect(char* namedir,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // Добавить в карту данные из файла DIR с использованием Select
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI AppendMapFromDirSelect(char* namedir,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

 // Запросить паспортные данные векторной карты
 // по имени файла SXF
 // Структуры MAPREGISTER и LISTREGISTER описаны в mapcreat.h
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI mapGetSxfInfoByName(const char * name,
                                            MAPREGISTER * map,
                                            LISTREGISTER * sheet);

_VECIMP long int _VECAPI mapGetSxfInfoByNameEx(const char * name,
                                              MAPREGISTEREX * map,
                                              LISTREGISTER * sheet);

 // Загрузить (импортировать) карту из файла SXF, TXF или DIR с
 // использованием Select с преобразованием топокарты к зоне документа
 // Файлы SXF и TXF могут хранить координаты в метрах, радианах или градусах
 // hmap    - идентификатор открытой карты (рекомендуется указывать
 //           для определения текущей зоны топокарты) или 0;
 // sxfname - имя загружаемого файла типа SXF, TXF или DIR;
 // rscname - имя файла классификатора, с которым загружается карта,
 //           имя классификатора можно запросить из SXF (TXF) функцией GetRscNameFromSxf
 //           или из карты; для файла DIR может быть 0;
 // mapname - имя создаваемой карты (обычно совпадает с именем SXF (TXF))
 //           или ноль или указатель на пустую строку (буфер размером MAX_PATH
 //           c нулевым байтом равным нулю) или указатель на папку для размещения
 //           карты. Если имя карты не задано или задана только папка, то карта
 //           создается с именем SXF (TXF) и расширением ".sit". Если namemap
 //           указывает на буфер достаточной длины (size), то в буфер записывается 
 //           имя созданной карты;
 //           Для файла DIR тип общей карты - MPT (проект данных, включающий все 
 //           открытые карты из DIR) или MAP (многолистовая карта);
 // size    - длина буфера, на который указывает переменная namemap, или 0. Обычно длина
 //           равна MAX_PATH_LONG (1024);
 // handle  - идентификатор окна диалога, которому посылаются уведомительные 
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux);
 // select  - фильтр загружаемых объектов и слоев, если необходима выборочная
 //           обработка данных;
 // Для добавления открытой карты в документ необходимо вызвать функцию
 // mapAppendData(hmap, namemap). Если mapname содержит имя карты типа MAP и
 // она содержит хотя бы один лист, то при импорте данных выполняется создание
 // нового листа в карте MAP. В этом случае функция mapAppendData не должна вызываться. 
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI ImportFromAnySxf(HMAP hmap,
                                         const char * sxfname,
                                         const char * rscname,
                                         char * mapname,
                                         long int size,
                                         HMESSAGE handle,
                                         HSELECT select);

//========================================================================
//   Функции сохранения карты
//========================================================================
//  Идентификатору посылаются следующие сообщения :
//  WM_LIST   = 0x586   WParam - количество листов в районе
//                      LParam - номер текущего листа
//  WM_OBJECT = 0x585   WParam - процент обработанных объектов

 // Сохранить (экспортировать) карту в двоичный формат SXF 
 // mapname - имя файла сохраняемой карты;
 // list    - номер листа для многолистовой карты или 1;
 // sxfname - имя создаваемого файла SXF, обычно совпадает с
 //           именем карты, но имеет расширение SXF;
 // flag    - вид хранимых координат (0 - метры, 4 - радианы
 //           для карты, поддерживающей геодезические координаты,
 //           -1 - определить по виду координат на карте);
 //           Если карты не было в документе - она может быть создана (добавлена) 
 // handle  - идентификатор окна диалога, которому посылаются уведомительные 
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux);
 // select  - фильтр выгружаемых объектов и слоев, если необходима выборочная 
 //           обработка данных;
 // Для топокарт, хранящих координаты в метрах, координаты всегда хранятся
 // в зоне, указанной в паспорте карты
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI ExportToSxf(const char * mapname,
                                    long int list,
                                    const char * sxfname,
                                    long int flag,
                                    HMESSAGE handle,
                                    HSELECT select);

 // Сохранить (экспортировать) карту в формат DIR
 // hmap    - идентификатор открытых данных
 // dirname - имя создаваемого файла DIR, обычно совпадает с
 //           именем открытого проекта или главной карты, но имеет расширение DIR;
 // type    - тип создаваемых файлов (0 - SXF, 1 - TXF);
 // flag    - вид хранимых координат (0 - метры, 4 - радианы, 8 - градусы,
 //           для карты, поддерживающей геодезические координаты,
 //           -1 - определить по виду координат на карте);
 //           Если карты не было в документе - она может быть создана (добавлена)
 // total   - признак сохранения в DIR только главной карты (0) или всех карт
 //           документа (1);
 // precision - для файлов TXF число знаков после запятой для координат в метрах или 0;
 //           если карта имеет паспортную точность в см (2 знака) или
 //           в мм (3 знака), то precision игнорируется;
 // handle  - идентификатор окна диалога, которому посылаются уведомительные
 //           сообщения (HWND для Windows, CALLBACK-Функция для Linux);
 // select  - фильтр выгружаемых объектов и слоев, если необходима выборочная
 //           обработка данных;
 // Для топокарт, хранящих координаты в метрах, координаты всегда хранятся
 // в зоне, указанной в паспорте карты
 // При ошибке возвращает ноль

_VECIMP long int _VECAPI ExportToDir(HMAP hmap,
                                    const char * dirname,
                                    long int type,
                                    long int flag,
                                    long int total,
                                    long int precision,
                                    HMESSAGE handle,
                                    HSELECT select);
                                              
// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат SXF(Windows)
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveSxfFromMap(char * namemap,
                                       int list,
                                       char * namesxf,
                                       HMESSAGE handle);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат SXF(Windows) с
// использованием  Select
//  flag = 0 - данные в метрах
//  flag = 4 - данные в радианах
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveSxfFromMapSelect(const char * namemap,
                                             long int list,
                                             const char * namesxf,
                                             HMESSAGE handle,
                                             HSELECT select,
                                             long int flag = 0,
                                             const char * nameregion = NULL);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат SXF(Windows) с
//          использованием  Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveSxfFromHMapSelect(HMAP map,
                                              long int list,
                                              const char * namesxf,
                                              HMESSAGE handle,
                                              HSELECT select,
                                              long int flag = 0,
                                              const char * nameregion = NULL);
_VECIMP long int _VECAPI SaveSxfFromHMapSelectUn(HMAP map,
                                                 long int list,
                                                 const WCHAR * namesxf,
                                                 HMESSAGE handle,
                                                 HSELECT select,
                                                 long int flag = 0,
                                                 const WCHAR * nameregion = NULL);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXT(XY)
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtFromMap(const char * namemap,
                                       long int   list,
                                       const char * nametxt,
                                       HMESSAGE handle);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(XY) с
//      использованием Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtFromMapSelect(const char * namemap,
                                             long int list,
                                             const char * nametxt,
                                             HMESSAGE handle,
                                             HSELECT select,
                                             const char * nameregion = NULL);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(XY) с
// использованием Select
// namemap - имя выгружаемой карты,
// list    - номер листа,
// nametxt - имя файла TXF,
// handle  - идентификатор окна, которому посылаются сообщения о ходе процесса
//           (WM_INFOLIST, WM_OBJECT)
// select  - идентификатор условий поиска объектов, определяющий список
//           экспортируемых в текстовый файл объектов,
// nameregion - имя района (карты),
// precision  - число знаков после запятой для прямоугольных координат
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtFromMapSelectEx(const char * namemap,
                                               long int list,
                                               const char * nametxt,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               const char * nameregion,
                                               long int precision);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(BL)
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtGeoFromMap(const char * namemap,
                                          long int list,
                                          const char * nametxt,
                                          HMESSAGE handle);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(BL) с
//      использованием Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveTxtGeoFromMapSelect(const char * namemap,
                                                long int list,
                                                const char * nametxt,
                                                HMESSAGE handle,
                                                HSELECT select,
                                                const char * nameregion = NULL);

_VECIMP long int _VECAPI SaveTxtGeoGradFromMapSelect(const char * namemap,
                                                    long int list,
                                                    const char * nametxt,
                                                    HMESSAGE handle,
                                                    HSELECT select,
                                                    const char * NameRegion = NULL);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат SXF(WINDOWS) по DIR
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirSxfFromMap(const char* namemap,
                                          const char* namedir,
                                          HMESSAGE handle);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат SXF(WINDOWS) по DIR
//   с использованием Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirSxfFromMapSelect(const char* namemap,
                                                const char* namedir,
                                                HMESSAGE handle,
                                                HSELECT select);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат SXF(WINDOWS) по DIR
//   с использованием Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirSxfIntFromMapSelect(const char* namemap,
                                                   const char* namedir,
                                                   HMESSAGE handle,
                                                   HSELECT select);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(XY) по DIR
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtFromMap(const char* namemap,
                                          const char* namedir,
                                          HMESSAGE handle);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(XY) по DIR
//   с использованием Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtFromMapSelect(const char* namemap,
                                                const char* namedir,
                                                HMESSAGE handle,
                                                HSELECT select);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(BL) по DIR
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtGeoFromMap(const char* namemap,
                                             const char* namedir,
                                             HMESSAGE handle);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(BL) по DIR
//   с использованием Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtGeoFromMapSelect(const char* namemap,
                                                   const char* namedir,
                                                   HMESSAGE handle,
                                                   HSELECT select);

// ----------------------------------------------------------------
// Выгрузка из внутреннего формата в формат TXF(BL градусы) по DIR
//   с использованием Select
// ----------------------------------------------------------------

_VECIMP long int _VECAPI SaveDirTxtGeoGradFromMapSelect(const char* namemap,
                                                       const char* namedir,
                                                       HMESSAGE handle,
                                                       HSELECT select);

//-------------------------------------------------------------------
//  Получение справочной информации о листе из SXF
// ------------------------------------------------------------------

_VECIMP long int _VECAPI GetInfoSxf(const char * namesxf,
                                   INFOSXF * infosxf);

//-------------------------------------------------------------------
//  Получение справочной информации из DIR
// ------------------------------------------------------------------

_VECIMP long int _VECAPI GetInfoDir(const char * namedir,
                                   INFODIR * infodir);

// ------------------------------------------------------------------
// Получение списка файлов SXF в DIR
// ------------------------------------------------------------------

_VECIMP long int _VECAPI GetDir(const char * namedir,
                               NAMESARRAY * sxfdir, long int length);


}       // extern "C"

#endif  // VECEXAPI_H


