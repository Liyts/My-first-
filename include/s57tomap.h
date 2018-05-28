/****  S57TOMAP.H *************  Belenkov O.V. *******  06/09/16 ***
*****  S57TOMAP.H ************* Gheleznykov A.V. ****** 20/10/05 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                         FOR MS WINDOWS                           *
*                                                                  *
********************************************************************
*                                                                  *
*            ИМПОРТ КАРТ ИЗ ФОРМАТА S57 РЕДАКЦИИ 3                 *
*                 (giss57.dll, gisu64s57.dll)                      *
*                                                                  *
*******************************************************************/

#if !defined(S57TOMAP_H)
#define S57TOMAP_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

extern "C"
{

// Загрузить карту из формата S57 
// source - путь к файлу формата S57 (*.000 или *.CAT)
// target - путь к создаваемому файлу (MAP или SIT) (строка 260 символов),
//          может быть обновлен в диалоге загрузки 
// parm   - вспомогательные параметры
// Для работы программы требуется классификатор s57navy.rsc
// Для отображения карт нужна библиотека отображения знаков s57navy.iml

__declspec(dllimport)long int WINAPI LoadS57ToMap(const char * source,
                                                  char       * target,
                                                  TASKPARM   * parm);


// Загрузить карту из формата S57 с указанием классификатора карты
// source - путь к файлу формата S57 (*.000 или *.CAT)
// target - путь к создаваемому файлу (MAP или SIT) (строка 260 символов),
//          может быть обновлен в диалоге загрузки 
// rscname - путь к существующему классификатору карты,
//          может быть обновлен в диалоге загрузки 
// parm   - вспомогательные параметры
// Для работы программы требуется классификатор s57navy.rsc
// Для отображения карт нужна библиотека отображения знаков s57navy.iml

__declspec(dllimport)long int WINAPI LoadS57ToMapForRsc(const char * source,
                                                        char       * target,
                                                        char       * rscname,
                                                        TASKPARM   * parm);

// Импорт из S57 в формат MAP без вызова диалога
// handle  - идентификатор родительского окна для обработки сообщений о ходе процесса или 0
// names57 - полное имя файла формата S57
// namemap - полное имя создаваемой карты
// namersc - полное имя файла классификатора (обычно S57NAVY.RSC)
// nameregion - условное название создаваемой карты ("Море Лаптевых" и т.п.)
// safelystate - флаг создания границ зон безопасности (длительный процесс оверлейного анализа данных)
// При ошибке в параметрах возвращает ноль

__declspec(dllimport) long int WINAPI LoadS57_2_Map(HMESSAGE handle,const char* names57,
                                                    const char* namemap,const char* namersc,
                                                    const char* nameregion,long safelystate)


}       // extern "C"

#endif  


