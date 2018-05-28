/****  VECTRAPI.H    **********  Belenkov  O.V.  *****  25/10/16 ***
/****  VECTRAPI.H    **********  Konon V.N.      *****  17/01/11 ***
*****  VECTRAPI.H    **********  Shabakov D.A.   *****  07/08/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
* СТАНДАРТНЫЕ ДИАЛОГИ ГИС КАРТА 2011 ДЛЯ ПРИЛОЖЕНИЙ НА GIS ToolKit *
*                                                                  *
*                 ПРИМЕР ВЫЗОВА ДИАЛОГА:                           *
*                                                                  *
*   // Загрузка библиотеки                                         *
*   HINSTANCE libInst = ::LoadLibrary("gisvectr.dll");             *
*                                                                  *
*   // Вызов функции                                               *
*   typedef long int (WINAPI * MAPSORTING)(HMAP hMap,              *
*                                          TASKPARM * parm)        *
*                                                                  *
*   MAPSORTING mapsorting = (MAPSORTING)                           *
*                   GetProcAddress(libInst, "MapSort");            *
*                                                                  *
*   long int rezult = (*mapsorting)(hMap, parm);                   *
*                                                                  *
*   // Выгрузка библиотеки                                         *
*   ::FreeLibrary(libInst);                                        *
*                                                                  *
*******************************************************************/

#if !defined(VECTRAPI_H)
#define VECTRAPI_H


#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

extern "C"
{

  // Вызвать диалог сортировки векторных карт
  // hmap - идентификатор открытых данных;
  // parm - параметры задачи, описание структуры TASKPARM в maptype.h 
  //        (поле Handle должно содержать идентификатор главного окна).
  // Вызов файла справки из Mapvectr.chm ("MAPSORTS")
  // При ошибке возвращает ноль

_MAPIMP long int WINAPI MapSort(HMAP hmap,TASKPARM * parm);


  // Вызвать диалог импорта векторных карт из формата SXF или TXF
  // lpszsource - адрес строки с именем импортируемого файла;
  // lpsztarget - адрес строки (буфера размером не менее 256 байт) для
  //              размещения имени создаваемой карты, строка может иметь
  //              начальное значение;
  // parm       - параметры задачи, описание структуры TASKPARM в maptype.h 
  //              (поле Handle должно содержать идентификатор главного окна).
  // Вызов файла справки из Mapvectr.chm ("IMPORTSXF")
  // При ошибке возвращает ноль

_MAPIMP long int WINAPI LoadSxf2Map(char* lpszsource, char* lpsztarget, TASKPARM* parm);

  // Вызвать диалог импорта векторных карт из формата DIR (списка SXF или TXF)
  // lpszsource - адрес строки с именем импортируемого файла DIR;
  // lpsztarget - адрес строки (буфера размером не менее 256 байт) для
  //              размещения имени создаваемой карты, строка может иметь
  //              начальное значение;
  // parm       - параметры задачи, описание структуры TASKPARM в maptype.h 
  //              (поле Handle должно содержать идентификатор главного окна).
  // Вызов файла справки из Mapvectr.chm ("IMPORTSXF")
  // При ошибке возвращает ноль

_MAPIMP long int WINAPI LoadDir2Map(const char* lpszsource, char* lpsztarget, TASKPARM* parm);

  // Вызвать диалог импорта векторных карт из формата DIR (списка SXF или TXF)   // 19/01/14
  // lpszsource - адрес строки с именем импортируемого файла DIR;
  // lpsztarget - адрес строки (буфера размером size) для
  //              размещения имени создаваемой карты, строка может иметь
  //              начальное значение, оно может быть изменено
  //              пользователем в диалоге, новое имя записывается вместо
  //              исходного;
  // size       - размер строки в байтах для записи имени создаваемой карты;
  // parm       - параметры задачи, описание структуры TASKPARM в maptype.h 
  //              (поле Handle должно содержать идентификатор главного окна).
  // Вызов файла справки из Mapvectr.chm ("IMPORTSXF")
  //  При ошибке возвращает ноль

_MAPIMP long int WINAPI vctLoadDir2MapUn(const WCHAR * lpszsource, WCHAR * lpsztarget, long int size, TASKPARM* parm);

  // Вызвать диалог обновления векторных карт из формата SXF, TXF или DIR
  // (списка SXF или TXF)
  // lpszsource - адрес строки с именем импортируемого файла, используемого
  //              для обновления векторной карты;
  // size - длина строки lpszsource для записи имени файла SXF, если в диалоге выбрано
  //        другое имя SXF;
  // hmap - идентификатор открытых данных;
  // parm       - параметры задачи, описание структуры TASKPARM в maptype.h 
  //              (поле Handle должно содержать идентификатор главного окна).
  // Вызов файла справки из Mapvectr.chm ("UPDATESXF")
  // При ошибке возвращает ноль

_MAPIMP long int WINAPI UpdateMapFromSxfDialog(char* lpszsource, int size, HMAP hmap, TASKPARM* parm);

_MAPIMP long int WINAPI UpdateMap2Sxf(char* lpszsource, HMAP hmap, TASKPARM* parm);


  // Сохранить векторную карту (экспорт) в формат SXF
  // hmap       - идентификатор открытых данных;
  // lpszsource - имя файла сохраняемой карты
  // lpsztarget - имя выходного файла
  // parm       - параметры задачи, описание структуры TASKPARM в maptype.h 
  //              (поле Handle должно содержать идентификатор главного окна).
  // Вызов файла справки из Mapvectr.chm ("EXPORTSXF")
  // При ошибке возвращает ноль

_MAPIMP long int WINAPI SaveMap2SxfEx(HMAP hmap, char* lpszsource, char* lpsztarget, TASKPARM* parm);

  // Сохранить векторную карту (экспорт) в формат TXF (текстовый SXF)
  // hmap       - идентификатор открытых данных;
  // lpszsource - имя файла сохраняемой карты
  // lpsztarget - имя выходного файла
  // parm       - параметры задачи, описание структуры TASKPARM в maptype.h
  //              (поле Handle должно содержать идентификатор главного окна).
  // Вызов файла справки из Mapvectr.chm ("EXPORTSXF")
  // При ошибке возвращает ноль

_MAPIMP long int WINAPI SaveMap2TxfEx(HMAP hmap, char* lpszsource, char* lpsztarget, TASKPARM* parm);


  // Сохранить одну или все векторные карты (экспорт) в формат DIR (список SXF или TXF)
  // hmap       - идентификатор открытых данных;
  // lpszsource - имя файла сохраняемой карты
  // parm       - параметры задачи, описание структуры TASKPARM в maptype.h
  //              (поле Handle должно содержать идентификатор главного окна).
  // Вызов файла справки из Mapvectr.chm ("EXPORTSXF")
  // При ошибке возвращает ноль

_MAPIMP long int WINAPI SaveMap2Dir(HMAP hmap, char* lpszsource, TASKPARM* parm);

}       // extern "C"

#endif  // VECTRAPI_H


