/****** GISMIFTOMAP.H *********** Shabakov D.A.   ****** 21/11/16 **
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*  В настоящем файле содержится объявление следующих диалогов:     *
*                                                                  *
                                                                  *
*                                                                  *
*                                                                  *
********************************************************************
*                                                                  *
*                 ИМПОРТИРОВАНИЕ ФУНКЦИЙ :                         *
*                                                                  *
*                                                                  *
*    #include "maplib.h"                                           *
*                                                                  *
*    // Загрузка библиотеки                                        *
*    HINSTANCE libInst = ::LoadLibrary(MIFMIDLIB);                 *
*                                                                  *
*    // Заполнение структур                                        *
*                                                                  *
*    // Вызов функции                                              *
*                                                                  *
*    long int (WINAPI * lpfn_ImportFromMifEx)(HMAP         hmap,   *
*                                        const char * namemif,     *
*                                        const char * namersc,     *
*                                        char       * namemap,     *
*                                        char       * buildname,   *
*                                        int        * numsem,      *
*                                        HMESSAGE     handle,      *
*                                        long int     flag,        *
*                                        long int     size);       *
*                                                                  *
*    (FARPROC)lpfn_ImportFromMifEx =                               *
*              GetProcAddress(libInst, "ImportFromMifEx");         *
*                                                                  *
*    (*lpfn_RswFilterDialog)(hmap,                                 *
*                            "file.mif",                           *
*                            "classifier.rsc",                     *
*                            "filemap.sit",                        *
*                            "param.ini",                          *
*                            0, 0, 0, 0);                          *
*                                                                  *
*    // Выгрузка библиотеки                                        *
*                                                                  *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/
#ifndef GISMIFTOMAP_H
#define GISMIFTOMAP_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // Описание структур интерфейса MAPAPI
#endif

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ ОПИСАНИЕ ФУНКЦИЙ АКТИВИЗАЦИИ ДИАЛОГОВЫХ ОКОН ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
// ------------------------------------------------------------------
// Диалог загрузки карты из формата MIF/MID
// hmap      - идентификатор открытой карты
// namemif   - имя загружаемого файла типа MIF
// namersc   - имя файла классификатора, с которым загружается карта
// namemap   - имя создаваемой карты
// buildname - имя файла настроек
// handle    - идентификатор окна диалога, которому посылаются уведомительные
//             сообщения
// flag      - признак создания карты (0) или добавления (1);
// size      - длина буфера, на который указывает переменная namemap или 0. Обычно длина
//             равна MAX_PATH
// Возвращает:
// 1 - корректный запуск диалога
// 0 - при ошибке
// 2 - при отсутствии поля классификационного кода (CODEOBJECT)в загружаемом файле
// 3 - при ошибочной системе координат метрики объектов (не WGS84)
// 4 - при отсутствии поля CODEOBJECT и ошибочной системе координат метрики
// ------------------------------------------------------------------
long int WINAPI _export ImportFromMifEx(HMAP         hmap,
                                        const char * namemif,
                                        const char * namersc,
                                        char       * namemap,
                                        char       * buildname,
                                        int        * numsem,
                                        HMESSAGE     handle,
                                        long int     flag,
                                        long int     size);


// ------------------------------------------------------------------
// Диалог загрузки карты из формата MIF/MID
// hmap      - идентификатор открытой карты
// mifname   - имя входного загружаемого файла типа MIF
// rscname   - имя файла классификатора, с которым загружается карта
// mapname   - имя создаваемой карты
// size      - длина буфера, на который указывает переменная namemap или 0. Обычно длина
//             равна MAX_PATH
// buildname - имя входного файла настроек
// codename  - имя в файле настройки поля, которое содержит код объекта
// sizename  - длина буфера, на который указывает переменная codename
// handle    - идентификатор окна диалога, которому посылаются уведомительные
//             сообщения
// flag      - признак создания карты (0) или добавления (1);

// Возвращает:
// 1 - корректный запуск диалога
// 0 - при ошибке
// 2 - при отсутствии поля классификационного кода (CODEOBJECT)в загружаемом файле
// 3 - при ошибочной системе координат метрики объектов (не WGS84)
// 4 - при отсутствии поля CODEOBJECT и ошибочной системе координат метрики
// ------------------------------------------------------------------
long int WINAPI _export ImportFromMifName(HMAP         hmap,
                                          const char * mifname,
                                          const char * rscname,
                                          char       * mapname,
                                          long int     size,
                                          char       * buildname,
                                          long int   * numsem,
                                          char       * codename,
                                          long int     sizename,
                                          HMESSAGE     handle,
                                          long int     flag,
                                          long int code);

}

#endif


