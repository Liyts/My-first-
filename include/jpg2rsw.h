/****  Jpg2Rsw.H     **********  Shabakov D.A.   *****  31/08/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2014              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*                   FOR  WINDOWS95 & WINDOWS NT                    *
*                                                                  *
********************************************************************
*                                                                  *
*            ОПИСАНИЕ ФУНКЦИЙ ОБРАБОТКИ ДАННЫХ                     *
*        ИНТЕРФЕЙС ДЛЯ ПРОГРАММ НА ЯЗЫКАХ C, PASCAL, BASIC         *
*                                                                  *
*******************************************************************/
#if !defined(JPEG2RSW_H)
#define JPEG2RSW_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

extern "C"
{

//========================================================================
// Активизация диалога "Загрузка растровой карты из файла формата JPG"
//    с возможностью выбора имен файлов и
//                   установки признака сжатия для растровой карты.
//
//    nameJpg - указатель на строку с размером MAX_PATH,
//              содержащую имя JPEG-файла;
//    nameRsw - указатель на строку с размером MAX_PATH,
//              содержащую имя RSW-файла; После успешной загрузки
//              по указателю nameRsw помещается имя файла созданной растровой карты
//    compression - флаг использования сжатия при формировании растровой карты (0/1)
//
//    При ошибке возвращает ноль
//========================================================================
long int _export WINAPI LoadJpegToRsw(const char* nameJpg, char* nameRsw,
                                      TASKPARM * parm,
                                      long int flagCompress);

long int WINAPI __export LoadJpegToRswUn(const WCHAR* nameJpg,
                                      WCHAR* nameRsw, int sizenameRsw,
                                      TASKPARM * parm,
                                      long int flagCompress);

//========================================================================
// Активизация диалога "Загрузка растровой карты из файла формата JPG"
//    с возможностью выбора имен файлов и
//                   установки признака сжатия для растровой карты.
//
//    hMapDoc - ИДЕНТИФИКАТОР ОКНА ДОКУМЕНТА (необязательный параметр)
//    hMap    - ИДЕНТИФИКАТОР ОТКРЫТОЙ ВЕКТОРНОЙ КАРТЫ
//    nameJpg - указатель на строку с размером MAX_PATH,
//              содержащую имя JPEG-файла;
//    nameRsw - указатель на строку с размером MAX_PATH,
//              содержащую имя RSW-файла; После успешной загрузки
//              по указателю nameRsw помещается имя файла созданной растровой карты
//    point   - указатель на точку привязки растра (в метрах)
//              (положение юго-западного угла растра в районе)
//              (необязательный параметр)
//    compression - флаг использования сжатия при формировании растровой карты (0/1)
//
//    При ошибке возвращает ноль
//========================================================================
long int WINAPI __export LoadJpegToRswByPlace(HMAPDOC hMapDoc, HMAP hMap,
                                         const char* nameJpg,
                                         char* nameRsw,
                                         TASKPARM * parm,
                                         DOUBLEPOINT * point,
                                         long int flagCompress);

long int WINAPI __export LoadJpegToRswByPlaceUn(HMAPDOC hMapDoc, HMAP hMap,
                                         const WCHAR* nameJpg,
                                         WCHAR* nameRsw,
                                         int sizenameRsw,
                                         TASKPARM * parm,
                                         DOUBLEPOINT * point,
                                         long int flagCompress);


//========================================================================
// Диалог "Сохранение растровой карты в файл формата JPG"
//
//    hMap    - ИДЕНТИФИКАТОР ОТКРЫТОЙ КАРТЫ
//    nameRsw - указатель на строку с размером MAX_PATH_LONG,
//              содержащую имя RSW-файла
//    nameJpg - указатель на строку с размером MAX_PATH_LONG,
//              содержащую имя JPEG-файла;
//    parm    - указатель на структуру TASKPARMEX
//
//    При ошибке возвращает ноль
//========================================================================
  long int WINAPI __export SaveRswToJpeg(HMAP hMap, const char* nameRsw,
                                         const char* nameJpg,
                                         TASKPARM * parm);

  long int WINAPI __export SaveRswToJpegUn(HMAP hMap, const WCHAR* nameRsw,
                                         WCHAR* nameJpg, int sizenameJpg,
                                         TASKPARM * parm);

//========================================================================
// Диалог "Установка коэффициента сжатия изображения по методу JPEG"
// value   - указатель на коэффициента сжатия
// parm    - указатель на структуру TASKPARMEX
//========================================================================
long int WINAPI __export SetJpegCompress(long int* value, TASKPARMEX * parm);

}       // extern "C"


#endif  // JPEG2RSW_H



