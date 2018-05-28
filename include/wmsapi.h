/******  WMSAPI.H   ***********  Belenkov     O.V. **** 30/08/14 ***
*******  WMSAPI.H   ***********  Dishlenko    S.G. **** 04/10/11 ***
*******  WMSAPI.H   ***********  Zheleznyakov V.A. **** 23/06/16 ***
*******  WMSAPI.H   ***********  Tarakanova I.R.   **** 14/02/14 ***
*******  WMSAPI.H   ***********  Konon V.N.        **** 25/01/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                  Интерфейс доступа к WMS-сервисам                *
*              для библиотеки gisacces.dll (gisu64acces.dll)       *
*                                                                  *
*******************************************************************/

#ifndef WMSAPI_H
#define WMSAPI_H

#include "mapcreat.h"                                     // 04/10/11

extern "C"
{
  // Подключится к WMS сервису
  // wmsstring - строка подключения к сервису
  // внешний вид строки: WMS#IP=ipname&Id1=layerID&Name1=layerName
  // где ipname - IP адрес сервиса
  // layerID - идентификаторы слоёв сервиса
  // layerName - имена слоёв сервиса
  // При ошибке возвращает 0

_MAPIMP HMAP _MAPAPI mapOpenWMS(const char* wmsstring);
_MAPIMP HMAP _MAPAPI mapOpenWMSUn(const WCHAR* wmsstring);

  // Подключится к WMS сервису в заданном районе работ
  // Возвращает номер WMS-соединения в списке соединений
  // hMap    - идентификатор открытого документа
  // wmsstring - строка подключения к сервису
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapOpenWMSForMap(HMAP hMap, const char* wmsstring);
_MAPIMP long int _MAPAPI mapOpenWMSForMapUn(HMAP hMap, const WCHAR* wmsstring);

  // Закрыть соединение по его порядковому номеру в списке подключений
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер закрываемого соединения в списке соединений (с 1)
  // freelib - освобождать ресурсы библиотеки, 1 - не освобождать, 0- освобождать

_MAPIMP void _MAPAPI mapCloseWMS(HMAP hMap, long int number, long int freelib = 0);

  // Запросить имя соединения по номеру
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер соединения в списке соединений (с 1)
  // При ошибке возвращает пустую строку

_MAPIMP const char * _MAPAPI mapGetWMSName(HMAP hMap, long int number);

  // Запросить имя соединения по номеру
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер соединения в списке соединений (с 1)
  // wname     - буфер для возвращаемой строки
  // namesize - размер буфера в БАЙТАХ
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapGetWMSNameUn(HMAP hMap, long int number,    // 14/02/14
                                         WCHAR *wname, int namesize);

  // Запросить число открытых соединений
  // hMap    - идентификатор открытого документа
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapGetWMSCount(HMAP hMap);

  // Запросить номер текущей проекции EPSG для WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер соединения в списке соединений (с 1)
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapGetWMSEPSGCode(HMAP hMap, long int number);

  // Запросить данные о проекции для WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер соединения в списке соединений (с 1)
  // mapregister - адрес структуры, в которой будут размещены
  // данные о проекции
  // datum   - параметры пересчета с эллипсоида рабочей системы координат
  //           к WGS-84 (datum может быть 0)
  // ellparam - параметры эллипсоида
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapGetWMSProjectionData(HMAP hMap, int number,
                                                 MAPREGISTEREX* mapregister,
                                                 DATUMPARAM* datum,
                                                 ELLIPSOIDPARAM* ellparam);

  // Запросить фактические габариты отображаемого растра в метрах в районе работ
  // При отображение растра по рамке возвращаются габариты рамки
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // frame      - возвращаемые габариты изображения в метрах
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapGetWMSPlaneFrame(HMAP hMap, long int number, DFRAME *frame);

  // Запросить габариты полного изображения в радианах в соотвествии с текущей
  // системой координат WMS-соединения, заданной кодом EPSG (mapGetWMSEPSGCode)
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // frame      - возвращаемые габариты изображения в радианах
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapGetWMSGeoFrame(HMAP hMap, long int number, DFRAME * frame);

  // Запросить/Установить степень видимости растра, получаемого с WMS
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер соединения в списке соединений (с 1)
  //  view = 0 - не виден
  //  view = 1 - полная видимость
  //  view = 2 - насыщенная
  //  view = 3 - полупрозрачная
  //  view = 4 - средняя
  //  view = 5 - прозрачная

_MAPIMP long int _MAPAPI mapGetWMSView(HMAP hMap,long int number);
_MAPIMP long int _MAPAPI mapSetWMSView(HMAP hMap,long int number,
                                       long int view);

  // Запросить/Установить порядок отображения WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // order  - 0 - под векторной картой, 1 - над картой
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapSetWMSViewOrder(HMAP hMap, long int number,
                                            long int order);
_MAPIMP long int _MAPAPI mapGetWMSViewOrder(HMAP hMap, long int number);

  // Запросить яркость палитры WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapGetWMSBright(HMAP hMap,long int number);

  // Запросить контрастность палитры WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapGetWMSContrast(HMAP hMap,long int number);

  // Установить яркость палитры WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // bright  - яркость
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapSetWMSBright(HMAP hMap, long int number,
                                          long int bright);

  // Установить контрастность WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // contrast - контраст
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapSetWMSContrast(HMAP hMap, long int number,
                                                       long int contrast);

  // Установить прозрачный цвет растра WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // color  - значение прозрачного цвета в формате RGB (от 0 до 0x00FFFFFF)
  // При установке IMGC_TRANSPARENT (0xFFFFFFFF) прозрачный цвет не используется
  // При ошибке возвращает IMGC_TRANSPARENT

_MAPIMP COLORREF _MAPAPI mapSetWMSTransparentColor(HMAP hMap, long int number,
                                                   COLORREF color);

  // Запросить прозрачный цвет растра WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // Возвращает цвет в формате RGB (от 0 до 0x00FFFFFF)
  // При возврате IMGC_TRANSPARENT (0xFFFFFFFF) прозрачный цвет не используется
  // При ошибке возвращает IMGC_TRANSPARENT

_MAPIMP  COLORREF _MAPAPI mapGetWMSTransparentColor(HMAP hMap, long int number);

  // Запросить значения масштаба нижней и верхней границ видимости растра WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // По адресу bottomScale записывается знаменатель масштаба нижней границы видимости растра
  // По адресу topScale записывается знаменатель масштаба верхней границы видимости растра
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapGetWMSRangeScaleVisible(HMAP hMap, long int number,
                                                     long int *bottomScale,
                                                     long int *topScale);

  // Установить значения масштаба нижней и верхней границ видимости растра WMS-соединения
  // hMap    - идентификатор открытого документа
  // number  - порядковый номер cоединения в списке соединений (с 1)
  // bottomScale - знаменатель масштаба нижней границы видимости растра
  // topScale    - знаменатель масштаба верхней границы видимости растра
  //               bottomScale <= topScale, иначе возвращает 0
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapSetWMSRangeScaleVisible(HMAP hMap, long int number,
                                                     long int bottomScale,
                                                     long int topScale);

  

  // Получить изображение с WMS сервиса
  // hMap   - идентификатор открытого документа
  // number - порядковый номер cоединения в списке соединений (с 1)
  // hdc    - контекст устройства отображения,
  // erase  - признак предварительной очистки фона изображения,
  // rect   - размеры запрашиваемого изображения в пикселах,
  //          ширина = (rect.RT-rect.LT+1) и высота = (rect.DN-rect.UP+1)
  // frame  - геодезические координаты отображаемой области в радианах
  //          в соотвествии с текущей системой координат WMS-соединения,
  //          заданной кодом EPSG (mapGetWMSEPSGCode)
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapPaintWMS(HMAP hMap, long int number, HDC hdc, long int erase,
                                     RECT* rect, DFRAME* frame);

  // Изменить параметры WMS-соединения
  // hMap       - идентификатор открытой векторной карты
  // number     - номер файла в цепочке
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapChangeWMS(HMAP hMap, long int number, const char* wmsstring);
_MAPIMP long int _MAPAPI mapChangeWMSUn(HMAP hMap, long int number, const WCHAR* wmsstring);

  // Запросить - установлена ли проекция геопорталом (WMS-сервисом)
  // hWMS - идентификатор сервиса
  // Если нет - возвращает 0

_MAPIMP long int _MAPAPI mapIsTranslateWMS(HMAP hMap);

  // Отобразить список геопорталов в виде дерева (открывается диалог в виде меню)
  // hmap        - идентификатор главного документа
  // parm      - текущие системные параметры, поле Handle должно 
  //             содержать идентификатор окна приложения, обрабатывающего
  //             поступающие сообщения. Описание структуры - см. maptype.h)
  // left, top   - координаты расположения меню (верхний левый угол в пикселях экрана)
  // При использовании функции необходимо обработать сообщения AW_OPENDOC, AW_CLOSEDOC,
  // MT_MAPWINPORT, AW_MOVEDOC, MT_SELECTOBJECT.
  // В GIS ToolKit за обработку сообщений отвечает компонент TMapWMSPopupDialog
  // Главному окну (parm->Handle) посылаются сообщения:
  //                          Главному окну (parm->Handle)
  //                          AW_OPENDOC - открыть документ в приложении
  //                          ::SendMessage(Parm->Handle, AW_OPENDOC, (WPARAM)fname, 0);
  //                          AW_CLOSEDOC - закрыть текущий документ в приложении
  //                          ::SendMessage(parm->Handle, AW_CLOSEDOC, (WPARAM)filename.c_str(), 0);
  //                          Окну карты (parm->DocHandle)
  //                          MT_MAPWINPORT - обновление карты
  //                          ::SendMessage(Parm->DocHandle, MT_MAPWINPORT, MWP_SETVIEWSCALE,0)
  //                          AW_MOVEDOC - перемещение карты в точку geopoint
  //                          ::SendMessage(Parm->DocHandle, AW_MOVEDOC,(WPARAM)&geopoint, PP_GEOWGS84);
  //                          PP_GEOWGS84 -  // КООРДИНАТЫ ТОЧЕК В ГЕОДЕЗИЧЕСКИХ КООРДИНАТАХ
  //                                         // В РАДИАНАХ В СИСТЕМЕ WGS-84
  //                          MT_SELECTOBJECT - убрать перекрестие после перемещения в заданную точку
  //                          ::SendMessage(Parm->DocHandle, MT_SELECTOBJECT,0,0);
  // Функция всегда возвращает 0


_MAPIMP HMAP _MAPAPI mapPortalMenu(HMAP hmap, TASKPARMEX *parm, int left, int top);

  // Изменить параметры соединения с сервисом/или запросить строку подключения (открывается диалог)
  // parm      - текущие системные параметры, поле Handle должно 
  //             содержать идентификатор окна приложения. Описание структуры - см. maptype.h)
  // wmsstring - строка подключения к сервису
  // size - длина буфера, отведенного под размещение строки
  // flag - признак выполняемого действия (будет отображено в заголовке диалога)
  // 0 - открыть данные, 1 - добавить данные, 2 - изменить данные
  // type - тип данных для открытия/изменения/добавления 0 - WMS, 1 - WMTS
  // При ошибке возвращает 0

_MAPIMP long int _MAPAPI mapEditWms(TASKPARMEX *parm, char* wmsstring, int size, int flag);
_MAPIMP long int _MAPAPI mapEditWmsUn(TASKPARMEX *parm, WCHAR* wmsstring, int size, int flag);

  // Запросить короткое имя строки подключения
  // wmsname - полное имя соединения
  // shortname- короткое имя соединения
  // size - размер короткого имени соединения
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapGetShortWMSName(const char* wmsname, char* shortname, int size);
_MAPIMP  long int _MAPAPI mapGetShortWMSNameUn(const WCHAR* wmsname, WCHAR* shortname, int size);


  // Установить версию запроса данных для геопортала
  // version - версия геопортала
  // в случае ошибки возвращает 0

  _MAPIMP  long int _MAPAPI mapSetPortalVersion(HMAP hMap, int number, const char* version);
  _MAPIMP  long int _MAPAPI mapSetPortalVersionUn(HMAP hMap, int number, const WCHAR* version);

  // Запросить версию запроса данных для геопортала
  // version - версия геопортала
  // в случае ошибки возвращает 0

_MAPIMP  long int _MAPAPI mapGetPortalVersion(HMAP hMap, int number, char* version);
_MAPIMP long int _MAPAPI mapGetPortalVersionUn(HMAP hMap, int number, WCHAR* version, int verssize);

  // Установить время запроса данных для геопортала
  // time - время формата(TDateTime)
  // в случае ошибки возвращает 0

_MAPIMP  long int _MAPAPI mapSetGeoportalDateTime(HMAP hMap, int number, double time);

  // Запросить время запроса данных для геопортала
  // в случае ошибки возвращает 0, иначе время в формате (TDateTime)

_MAPIMP  long int _MAPAPI mapGetGeoportalDateTime(HMAP hMap, int number, double* time);

  // Отобразить диалог настройки версии, даты/времени работы геопортала
  // При ошибке возвращает 0

_MAPIMP  long int _MAPAPI mapShowGeoportalDateTimeDialog(HMAP hMap, TASKPARMEX *parm);

  // Очистить кэш данных для всех геопорталов с сервисов WMS/WMTS для текущего документа
  
_MAPIMP  long int _MAPAPI mapClearWmsCache(HMAP hMap);

   // Изменить порядок отображения геопорталов в цепочке
   // Нумерация геопорталов в цепочке начинается с 1
   // oldNumber - номер файла в цепочке
   // newNumber - устанавливаемый номер файла в цепочке
   // При ошибке возвращает 0
  
_MAPIMP  long int _MAPAPI mapChangeOrderWmsShow(HMAP hMap, long int oldNumber, long int newNumber);

   // Запросить номер геопортала в цепочке по имени файла
   // name - имя файла геопортала
   // В цепочке номера геопорталов начинаются с 1.
   // При ошибке возвращает ноль

_MAPIMP long int _MAPAPI mapGetWmsNumberByName(HMAP hMap, const WCHAR * name);

}

#endif  // WMSAPI_H
