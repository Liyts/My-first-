/****  MAPPICEX.H    **********  Shabakov D.A.   *****  14/07/16 ***
*****  MAPPICEX.H    **********  Gorbunov A.V.   *****  30/07/14 ***
*****  MAPPICEX.H    **********  Belenkov O.V.   *****  23/11/15 ***
*****  MAPPICEX.H    **********  Kruzhkov A.E.   *****  28/07/16 ***
*****  MAPPICEX.H    **********  Kruzhkova E.A.  *****  10/02/14 ***
*****  MAPPICEX.H    **********  Derevyagina Zh.A.****  02/12/14 ***
*****  MAPPICEX.H    **********  Korjilov A.     *****  13/02/15 ***
*****  MAPPICEX.H    **********  Letov V.I.      *****  26/07/16 ***
*****  MAPPICEX.H    **********  Tarakanova  I.R.*****  05/10/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                     All Rights Reserved                          *
*                                                                  *
********************************************************************
*                                                                  *
*            ОПИСАНИЕ ФУНКЦИЙ ОБРАБОТКИ ДАННЫХ                     *
*        ИНТЕРФЕЙС ДЛЯ ПРОГРАММ НА ЯЗЫКАХ C, PASCAL, BASIC         *
*                                                                  *
*    Импортирование функций в Windows :                            *
*                                                                  *
*    #include "maplib.h"                                           *
*    // Загрузка библиотеки                                        *
*    HINSTANCE libInst = ::LoadLibrary(MAPPICEXLIB);               *
*                                                                  *
*    // Вызов функции                                              *
*                                                                  *
*    long int (WINAPI * lpfn_LoadPcxToRstConverter)( HMAP map,     *
*                               HMESSAGE handle,                   *
*                               char * pcxname,                    *
*                               char * rstname,                    *
*                               double scale,                      *
*                               double precision );                *
*                                                                  *
*    (FARPROC)lpfn_LoadPcxToRstConverter =                         *
*              GetProcAddress(libInst, "LoadPcxToRstConverter");   *
*    (*lpfn_LoadPcxToRstConverter)(0, 0,                           *
*                                   "image.pcx",                   *
*                                   "image.rsw",                   *
*                                   10000, 20000);                 *
*                                                                  *
*    // Выгрузка библиотеки                                        *
*    ::FreeLibrary(libInst);                                       *
*                                                                  *
*******************************************************************/
#ifndef MAPPICEX_H
#define MAPPICEX_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

#ifndef PICEXPRM_H
  #include "picexprm.h"
#endif

#ifdef WIN32API   
   #define HMESSAGE HWND
#else
   #define HMESSAGE MSGHANDLER
#endif

#ifdef LINUXAPI                            // 08/10/15
  #define _PICAPI
  #define _PICIMP
#else
  #define _PICAPI  WINAPI
  #if defined(PICEX_DLL)
    #define _PICIMP __declspec(dllexport)
  #else
    #define _PICIMP __declspec(dllimport)
  #endif
#endif


extern "C"
{

//========================================================================
// Загрузка растровых данных из файла PCX в файл RSW
//    Handle  - диалог визуального сопровождения процесса обработки.
//    PcxName - имя PCX-файла;
//    RstName - имя RST-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    compression - флаг сжатия изображения
//              0 - сжатие к блокам изображения применяться не будет
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadPcxToRstAndCompress(HMESSAGE handle,             // 02/12/14
                               const char * pcxname,
                               const char * rstname,
                               double* meterInElementX,
                               double* meterInElementY,
                               DOUBLEPOINT *point,
                               int compression);

_PICIMP long int _PICAPI picexLoadPcxToRstAndCompressUn(HMESSAGE handle,
                               const WCHAR * pcxname,
                               const WCHAR * rstname,
                               double* meterInElementX,
                               double* meterInElementY,
                               DOUBLEPOINT *point,
                               int compression);

//========================================================================  // 04/06/13
// Загрузка растровых данных из файла PCX в файл RSW
//    Handle  - диалог визуального сопровождения процесса обработки.
//    PcxName - имя PCX-файла;
//    RstName - имя RST-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    compression - флаг сжатия изображения
//              0 - сжатие к блокам изображения применяться не будет
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    compressJpegQuality - степень сжатия блока растра по алгоритму JPEG
//              Возможные значения: 1 - 100
//              Рекомендуемое значение: 60
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadPcxToRstAndCompressJPEG(HMESSAGE handle,
                               const char * pcxname,
                               const char * rstname,
                               double* meterInElementX,
                               double* meterInElementY,
                               DOUBLEPOINT *point,
                               int compression,
                               int compressJpegQuality);

_PICIMP long int _PICAPI picexLoadPcxToRstAndCompressJPEG_Un(HMESSAGE handle,    // 19/06/14
                               const WCHAR *pcxname,
                               const WCHAR *rstname,
                               double* meterInElementX,
                               double* meterInElementY,
                               DOUBLEPOINT *point,
                               int compression,
                               int compressJpegQuality);

//========================================================================
// Загрузка растровых данных из файла BMP в файл RSW
//    BmpName - имя BMP-файла;
//    RstName - имя RSW-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - HWND диалога визуального сопровождения процесса обработки.
//    compression - флаг сжатия изображения
//              0 - сжатие к блокам изображения применяться не будет
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadBmpToRstAndCompress(HMESSAGE Handle,
                               const char * BmpName,
                               const char * RstName,
                               double* meterInElementX,
                               double* meterInElementY,
                               DOUBLEPOINT *point,
                               int compression);

_PICIMP long int _PICAPI picexLoadBmpToRstAndCompressUn(HMESSAGE Handle,
                               const WCHAR *BmpName,
                               const WCHAR *RstName,
                               double* meterInElementX,
                               double* meterInElementY,
                               DOUBLEPOINT *point,
                               int compression);

//========================================================================  // 04/06/13
// Загрузка растровых данных из файла BMP в файл RSW
//    Handle  - диалог визуального сопровождения процесса обработки.
//    BmpName - имя BMP-файла;
//    RstName - имя RSW-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    compression - флаг сжатия изображения
//              0 - сжатие к блокам изображения применяться не будет
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    compressJpegQuality - степень сжатия блока растра по алгоритму JPEG
//              Возможные значения: 1 - 100
//              Рекомендуемое значение: 60
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadBmpToRstAndCompressJPEG(HMESSAGE Handle,
                               const char * BmpName,
                               const char * RstName,
                               double* meterInElementX,
                               double* meterInElementY,
                               DOUBLEPOINT *point,
                               int compression,
                               int compressJpegQuality);

_PICIMP long int _PICAPI picexLoadBmpToRstAndCompressJPEG_Un(HMESSAGE Handle,    // 19/06/14
                               const WCHAR * BmpName,
                               const WCHAR * RstName,
                               double* meterInElementX,
                               double* meterInElementY,
                               DOUBLEPOINT *point,
                               int compression,
                               int compressJpegQuality);

//========================================================================      // 04/06/13
// Загрузка растровых данных из файла JPEG в файл RSW
//    Map - дескриптор открытого документа
//    inputname - имя JPEG-файла;
//    rstname   - имя RSW-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//              0 - сжатие к блокам изображения не применено
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    compressJpegQuality - степень сжатия блока растра по алгоритму JPEG
//              Возможные значения: 1 - 100
//              Рекомендуемое значение: 60
//    flagMessage - флаг выдачи сообщений
//                                       (при ==1, сообщение выдает MessageBox;
//                                        при == 0, посылается сообщение диалогу WM_ERROR)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadJpegToRswAndCompressJPEG(HMAP map, HMESSAGE handle,
                                                  const char * inputname,
                                                  const char * rstname,
                                                  double* meterInElementX,
                                                  double* meterInElementY,
                                                  DOUBLEPOINT *point,
                                                  int compression,
                                                  int compressJpegQuality,
                                                  int flagMessage);

_PICIMP long int _PICAPI picexLoadJpegToRswAndCompressJPEG_Un(HMAP map, HMESSAGE handle,
                                                  const WCHAR * inputname,
                                                  const WCHAR * rstname,
                                                  double* meterInElementX,
                                                  double* meterInElementY,
                                                  DOUBLEPOINT *point,
                                                  int compression,
                                                  int compressJpegQuality,
                                                  int flagMessage);

//========================================================================
// Загрузка растровых данных из файла JPEG в файл RSW
//    Handle - диалог визуального сопровождения процесса обработки.
//    Map - дескриптор открытого документа
//    inputname - имя JPEG-файла;
//    rstname   - имя RSW-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//    flagMessage - флаг выдачи сообщений
//                                       (при ==1, сообщение выдает MessageBox;
//                                        при == 0, посылается сообщение диалогу WM_ERROR)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadJpegToRswAndCompress(HMAP map, HMESSAGE handle,
                                                  const char * inputname,
                                                  const char * rstname,
                                                  double* meterInElementX,
                                                  double* meterInElementY,
                                                  DOUBLEPOINT *point,
                                                  int compression,
                                                  int flagMessage);

_PICIMP long int _PICAPI picexLoadJpegToRswAndCompressUn(HMAP map, HMESSAGE handle,
                                                  const WCHAR * inputname,
                                                  const WCHAR * rstname,
                                                  double* meterInElementX,
                                                  double* meterInElementY,
                                                  DOUBLEPOINT *point,
                                                  int compression,
                                                  int flagMessage);

//========================================================================      // 08/02/16
// Загрузка растровой карты без копирования изображения в формат RSW
// В качестве исходных данных в функцию могут передаваться имена файлов форматов:
// (TIFF, GeoTIFF, IMG, JPEG, PNG, GIF, BMP)
// При успешном выполнении функции создается файл RSW с именем outputName.
// В файл RSW записываются параметры загружаемого растра, при этом изображение в
// RSW не переносится. Исходный и выходной (*.RSW) файлы должны находиться в одной папке.
// Обзорное изображение растра записывается в файл *.TOF, который создается в этой же папке.
// Для доступа к изображению графического файла созданный файл outputName необходимо
// открыть вызовом функции mapOpenRstUn, или добавить в документ карты вызовом
// функции mapOpenRstForMapUn.
// Входные параметры функции:
//    Handle          - диалог визуального сопровождения процесса обработки.
//    enableMessage   - флаг выдачи сообщений
//                             (при ==1, сообщение выдает MessageBox;
//                              при == 0, посылается сообщение диалогу WM_ERROR)
//    sourceName      - имя исходного файла (*.TIF, *.IMG, *.JPG, *.PNG, *.GIF, *.BMP);
//    outputName      - имя выходного файла (*.RSW);
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point           - привязка растра
//
//    Если в качестве исходного файла подается файл GeoTIFF, или файл IMG с
//    геопривязанным изображением, то входные параметры meterInElementX,
//    meterInElementY и point могут быть равны 0.
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexGetAccessToGraphicFileUn(HMESSAGE Handle,
                                                      int enableMessage,
                                                      const WCHAR * sourceName,
                                                      const WCHAR * outputName,
                                                      double* meterInPixelX,
                                                      double* meterInPixelY,
                                                      DOUBLEPOINT *point);

//========================================================================
// Загрузка растровой карты из Tiff(GeoTiff) в RSW             // 24/02/12
// Изображение в RSW не переносится, в RSW записываются заголовки, палитра, УК.
//    Map - дескриптор открытого документа
//    PcxName - имя PCX-файла;
//    RstName - имя RST-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point   - привязка растра
//    mapreg  - параметры проекции

//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//    flagMessage - флаг выдачи сообщений
//                                       (при ==1, сообщение выдает MessageBox;
//                                        при == 0, посылается сообщение диалогу WM_ERROR)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadTiffAccessToRsw(HMESSAGE Handle, int enableMessage,
                                           const char * TiffName, const char * RstName,
                                           double* meterInPixelX, double* meterInPixelY,
                                           DOUBLEPOINT *point);

_PICIMP long int _PICAPI picexLoadTiffAccessToRswUn(HMESSAGE Handle, int enableMessage,   // 19/06/14
                                           const WCHAR * TiffName, const WCHAR * RstName,
                                           double* meterInPixelX, double* meterInPixelY,
                                           DOUBLEPOINT *point);

_PICIMP long int _PICAPI LoadTiffAccessToRsw(HMAP Map, HMESSAGE Handle,
                                           int enableMessage,
                                           const char * TiffName,
                                           const char * RstName,
                                           double scale, double precision,
                                           DOUBLEPOINT *point,
                                           MAPREGISTEREX* mapreg,
                                           int res, int rez1);

_PICIMP long int _PICAPI LoadTiffAccessToRswUn(HMAP Map, HMESSAGE Handle,
                                           int enableMessage,
                                           const WCHAR * TiffName,
                                           const WCHAR * RstName,
                                           double scale, double precision,
                                           DOUBLEPOINT *point,
                                           MAPREGISTEREX* mapreg,
                                           int res, int rez1);

//========================================================================
// Загрузка растровой карты из Tiff(GeoTiff) в RSW
//    Handle - диалог визуального сопровождения процесса обработки.
//    TiffName - имя Tiff-файла;
//    RstName - имя Rst-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//              0 - сжатие к блокам изображения применяться не будет
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    flagIgnoreGeoTiff - (0/1) флаг игнорирования GeoTiff тегов
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadTiffToRstAndCompressEx(HMESSAGE handle,
                               const char * TiffName,
                               const char * RstName,
                               double* meterInPixelX, double* meterInPixelY,
                               DOUBLEPOINT *point,
                               int compression,
                               int flagIgnoreGeoTiff);

_PICIMP long int _PICAPI picexLoadTiffToRstAndCompressExUn(HMESSAGE handle,
                               const WCHAR * TiffName,
                               const WCHAR * RstName,
                               double* meterInPixelX, double* meterInPixelY,
                               DOUBLEPOINT *point,
                               int compression,
                               int flagIgnoreGeoTiff);

//========================================================================      // 04/06/13
// Загрузка растровой карты из Tiff(GeoTiff) в RSW
//    Handle - диалог визуального сопровождения процесса обработки.
//    TiffName - имя Tiff-файла;
//    RstName - имя Rst-файла;
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//              0 - сжатие к блокам изображения применяться не будет
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    compressJpegQuality - степень сжатия блока растра по алгоритму JPEG
//              Возможные значения: 1 - 100
//              Рекомендуемое значение: 60
//    flagIgnoreGeoTiff - (0/1) флаг игнорирования GeoTiff тегов
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadTiffToRstAndCompressJPEG(HMESSAGE handle,
                               const char * TiffName,
                               const char * RstName,
                               double* meterInPixelX, double* meterInPixelY,
                               DOUBLEPOINT *point,
                               int compression,
                               int compressJpegQuality,
                               int flagIgnoreGeoTiff);

_PICIMP long int _PICAPI picexLoadTiffToRstAndCompressJPEG_Un(HMESSAGE handle,  // 18/06/14
                               const WCHAR * TiffName,
                               const WCHAR * RstName,
                               double* meterInPixelX, double* meterInPixelY,
                               DOUBLEPOINT *point,
                               int compression,
                               int compressJpegQuality,
                               int flagIgnoreGeoTiff);

}  // extern "C"



struct SAVEASPICTRPARM;

//-----------------------------------------------------------------
// ПАРАМЕТРЫ ФОРМИРОВАНИЯ РАСТРОВОГО ИЗОБРАЖЕНИЯ КАРТЫ ДЛЯ ПЕЧАТИ
// (для задачи послойного формирования растрового изображения с
//  вычищением полей вокруг подписей в цветовых моделях RGB и CMYK)
//-----------------------------------------------------------------

typedef struct SAVEASPICTRPARM_FOR_PRINT
{
  int Length;         // Длина структуры SAVEASPICTRPARM_FOR_PRINT
#if defined(_M_X64) || defined(BUILD_DLL64)          // 28/07/16
  int Reserve1;
#endif
  HMESSAGE Handle;    // Идентификатор окна диалога (используется для
                      // визуального сопровождения процесса)
  HMAP HMap;          // Идентификатор карты
  int Regime;         // Режим выбора прямоугольной области
                      // (AREA_ALL, AREA_SELECT_FRAME, ... - см. maptype.h)
#if defined(_M_X64) || defined(BUILD_DLL64)          // 28/07/16
  int Reserve2;
#endif
  DFRAME PlaneFrame;  // Габариты выбранной области в метрах

  double DPI;         // Разрешение изображения (точек на дюйм)
  double LPI;         // Линий решетки на дюйм (при Method = 0 игнорируются).
                      // Линия состоит из точек формы Shape

  double FactorVer;   // Коэффициенты калибловки изображения по
  double FactorHor;   // вертикальной и горизонтальной осям

  RECT Rect;          // Область сохраняемой области карты в пикселах
                      //  (при выгрузке в RGB не учитывается)          //24/04/08

  int Scale;          // Масштаб (знаменатель)

  int BitCount;       // Количество бит на пиксел растрового изображения
                      // При ColorModel == 0:                          // 20/04/08
                      //   8,16,24,32 бит на пиксел (RGB)
                      // При ColorModel == 1:
                      //   1,8 бит на пиксел (CMYK) - четыре файла BMP или PCX
                      //   32 бит на пиксел (CMYK) - один файл TIF

  int Intensity;      // Интенсивность заливки площадных объектов (0-100)

  int ColorModel;     // Флаг цветовой модели:
                      //   0 - RGB (формируется один файл)
                      //   1 - CMYK BMP или CMYK PCX (четыре 8-битных
                      //       или 1-битных файла, составляющие растрового
                      //       изображения, с добавлением с базовому
                      //       имени окончаний "-C","-M","-Y","-K"),
                      //       или CMYK TIF (один файл)

  int Method;         // Метод конвертирования 8-битных полутоновых
                      // изображений CMYK в 1-битные:
                      //   0 - не выполнять (сохранить 8-битные изображения),
                      //   1 - регулярное заполнение точками формы Shape
                      //       с шагом DPI/LPI

  int Shape;          // Форма точки (штриховки) заполнения решетки
                      // (при Method = 0 игнорируется):
                      //   0 - регулярное заполнение круглыми точками

                      // Углы наклона точек решетки (при Method = 0 игнорируются)
  double AngleC;      //  15 градусов
  double AngleM;      //  75 градусов
  double AngleY;      //   0 градусов
  double AngleK;      //  45 градусов

  char Reserve[96];   // Резерв

  char Cross;         // Флаг нанесения приводочных крестов (для ColorModel > 0)
                      // (1 - есть, 0 - нет), (пока не реализовано)
  char Negative;      // Флаг сохранения негативного изображения (для BitCount = 1)
                      // (1 - есть, 0 - нет), (пока не реализовано)
  char Mirror;        // Флаг сохранения зеркального изображения (для BitCount = 1)
                      // (1 - есть, 0 - нет), (пока не реализовано)
  char Turn;          // Флаг поворота изображения на 90 градусов (для BitCount = 1)
                      // (1 - есть, 0 - нет), (пока не реализовано)

  char FileName[260]; // Базовое имя сохраняемого файла (BMP, PCX, TIF)

                      // При заданном 1.BMP (при BitCount = 1) формируются
                      // четыре файла: 1-С.BMP, 1-M.BMP, 1-Y.BMP, 1-K.BMP

                      // При заданном 1.PCX (при BitCount = 1) формируются
                      // четыре файла: 1-С.PCX, 1-M.PCX, 1-Y.PCX, 1-K.PCX

                      // В остальных случаях формируется один файл
}
  SAVEASPICTRPARM_FOR_PRINT;

extern "C"
{

//========================================================================
//    Конвертор PCX -> Rsw
//    map - дескриптор открытого документа
//    handle - диалог визуального сопровождения процесса обработки.
//    pcxname - имя PCX-файла;
//    rstname - имя RST-файла(*.rsw);
//    scale   - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadPcxToRstConverter( HMAP map, HMESSAGE handle,
                               const char * pcxname,
                               const char * rstname,
                               double scale, double precision );

_PICIMP long int _PICAPI LoadPcxToRstConverterUn( HMAP Map, HMESSAGE Handle,       // 19/06/14
                               const WCHAR * PcxName,
                               const WCHAR * RstName,
                               double scale, double precisionMet);

//========================================================================
//    Конвертор PCX -> Rsw
//    map - дескриптор открытого документа
//    handle - диалог визуального сопровождения процесса обработки.
//    pcxname - имя PCX-файла;
//    rstname - имя RST-файла(*.rsw);
//    scale   - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadPcxToRstConverterEx( HMAP map, HMESSAGE handle,
                               const char * pcxname,
                               const char * rstname,
                               double scale,
                               double precision,
                               DOUBLEPOINT *point);

_PICIMP long int _PICAPI LoadPcxToRstConverterExUn( HMAP map, HMESSAGE handle,   // 19/06/14
                               const WCHAR * pcxname,
                               const WCHAR * rstname,
                               double scale,
                               double precisionMet,
                               DOUBLEPOINT *point);

//========================================================================
//    Map     - дескриптор открытого документа
//    PcxName - имя PCX-файла;
//    RstName - имя RST-файла;
//    scale   - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadPcxToRstAndCompress( HMAP map, HMESSAGE handle,
                               const char * pcxname,
                               const char * rstname,
                               double scale,
                               double precision,
                               DOUBLEPOINT *point,
                               int compression);

_PICIMP long int _PICAPI LoadPcxToRstAndCompressUn( HMAP map, HMESSAGE handle,   // 19/06/14
                               const WCHAR * pcxname,
                               const WCHAR * rstname,
                               double scale,
                               double precisionMet,
                               DOUBLEPOINT *point,
                               int compression);

//========================================================================
//    Запросить параметры PCX-файла
//    pcxname     - имя PCX-файла;
//    information - указатель на структуру DATAINFORMATION для записи параметров PCX-файла
//    Структура DATAINFORMATION описана в picexprm.h
//
//    Функцию LoadPxcInformation рекомендуется вызывать перед началом
//    конвертации PCX-файла в Rsw для инициализации диалога сопровождения
//========================================================================
_PICIMP long int _PICAPI LoadPcxInformation(const char * pcxname,
                                           DATAINFORMATION * information);

_PICIMP long int _PICAPI LoadPcxInformationUn(const WCHAR * PcxName,             // 19/06/14
                                           DATAINFORMATION * information);


//========================================================================
//    Конвертор Bmp -> Rsw
//    map       - дескриптор открытого документа
//    handle    - диалог визуального сопровождения процесса обработки;
//    bmpname   - имя BMP-файла;
//    rstname   - имя RST-файла(*.rsw);
//    scale     - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadBmpToRstConverter( HMAP map,
                                               HMESSAGE handle,
                                               const char * bmpname,
                                               const char * rstname,
                                               double scale, double precision,
                                               DOUBLEPOINT *point = 0);

_PICIMP long int _PICAPI LoadBmpToRstConverterUn( HMAP Map,
                                               HMESSAGE Handle,
                                               const WCHAR * BmpName,
                                               const WCHAR * RstName,
                                               double scale, double precisionMet,
                                               DOUBLEPOINT *frame);

//=================================================================
//    Конвертор Bmp -> Rsw
//    map     - дескриптор открытого документа
//    handle  - диалог визуального сопровождения процесса обработки;
//    bmpname - имя BMP-файла;
//    rstname - имя RST-файла;
//    scale   - масштаб создаваемого растра;
//    frame   - габариты растра(в метрах на местности)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadBmpToRstByPlace(HMAP map, HMESSAGE handle,
                                       const char * bmpname,
                                       const char * rstname,
                                       double scale,
                                       DFRAME *frame);

_PICIMP long int _PICAPI LoadBmpToRstByPlaceUn( HMAP Map, HMESSAGE Handle,       // 19/06/14
                                        const WCHAR * BmpName,
                                        const WCHAR * RstName,
                                        double scale,
                                        DFRAME *frame);

//========================================================================
//    Конвертор Bmp -> Rsw
//    map       - дескриптор открытого документа
//    handle    - диалог визуального сопровождения процесса обработки;
//    bmpname   - имя BMP-файла;
//    rstname   - имя RST-файла(*.rsw);
//    scale     - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    compression - флаг использования сжатия при формировании RST-файла (0/1)

//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadBmpToRstAndCompress( HMAP map, HMESSAGE handle,
                               const char * bmpname,
                               const char * rstname,
                               double scale, double precision,
                               DOUBLEPOINT *point,
                               int compression);

_PICIMP long int _PICAPI LoadBmpToRstAndCompressUn( HMAP Map, HMESSAGE Handle,   // 19/06/14
                               const WCHAR * BmpName,
                               const WCHAR * RstName,
                               double scale, double precisionMet,
                               DOUBLEPOINT *point,
                               int compression);

//========================================================================
//    Запросить параметры BMP-файла
//    bmpname     - имя BMP-файла;
//    information - указатель на структуру DATAINFORMATION для записи параметров BMP-файла
//    Структура DATAINFORMATION описана в picexprm.h
//
//    Функцию LoadBmpInformation рекомендуется вызывать перед началом
//    конвертации BMP-файла в Rsw для инициализации диалога сопровождения
//========================================================================
_PICIMP long int _PICAPI LoadBmpInformation(const char * bmpname,
                                       DATAINFORMATION * information);

_PICIMP long int _PICAPI LoadBmpInformationUn(const WCHAR * bmpname,              // 10/02/14
                                       DATAINFORMATION * information);


//========================================================================
//    Конвертор Tiff -> Rsw
//    map       - дескриптор открытого документа
//    handle    - диалог визуального сопровождения процесса обработки.
//    tifname   - имя TIF-файла;
//    rstname   - имя RST-файла;
//    scale     - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadTiffToRstConverter( HMAP map, HMESSAGE handle,
                                                const char * tifname,
                                                const char * rstname,
                                                double scale, double precision );

_PICIMP long int _PICAPI LoadTiffToRstConverterUn( HMAP Map, HMESSAGE Handle,    // 18/06/14
                                                const WCHAR * tiffName,
                                                const WCHAR * rstName,
                                                double scale, double precision );

//========================================================================
//    Конвертор Tiff -> Rsw
//    map       - дескриптор открытого документа
//    handle    - диалог визуального сопровождения процесса обработки.
//    tifname   - имя TIF-файла;
//    rstname   - имя RST-файла;
//    scale     - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadTiffToRstConverterEx(HMAP map, HMESSAGE handle,
                               const char * tifname,
                               const char * rstname,
                               double scale,
                               double precision,
                               DOUBLEPOINT *point );

_PICIMP long int _PICAPI LoadTiffToRstConverterExUn( HMAP map, HMESSAGE handle,  // 18/06/14
                               const WCHAR * tifname,
                               const WCHAR * rstname,
                               double scale,
                               double precision,
                               DOUBLEPOINT *point);

//========================================================================
//    Конвертор Tiff -> Rsw
//    Map     - дескриптор открытого документа
//    PcxName - имя PCX-файла;
//    RstName - имя RST-файла;
//    scale   - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadTiffToRstAndCompress(HMAP map, HMESSAGE handle,
                                                 const char * TiffName,
                                                 const char * RstName,
                                                 double scale,
                                                 double precision,
                                                 DOUBLEPOINT *point,
                                                 int compression);

_PICIMP long int _PICAPI LoadTiffToRstAndCompressUn( HMAP map, HMESSAGE handle,
                                                 const WCHAR * TiffName,
                                                 const WCHAR * RstName,
                                                 double scale,
                                                 double precision,
                                                 DOUBLEPOINT *point,
                                                 int compression);

//========================================================================
//    Конвертор Tiff -> Rsw
//    Map     - дескриптор открытого документа
//    PcxName - имя PCX-файла;
//    RstName - имя RST-файла;
//    scale   - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//    flagIgnoreGeoTiff - (0/1) флаг игнорирования GeoTiff тегов                 // 17/11/11
//    arg1,arg2 - параметры не используются
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadTiffToRstAndCompressEx( HMAP/*map*/, HMESSAGE handle,
                               const char * TiffName,
                               const char * RstName,
                               double scale,
                               double precision,
                               DOUBLEPOINT *point,
                               int compression,
                               int flagIgnoreGeoTiff,
                               int arg1, int arg2);

_PICIMP long int _PICAPI LoadTiffToRstAndCompressExUn( HMAP/*map*/, HMESSAGE handle,   // 18/06/14
                               const WCHAR * TiffName,
                               const WCHAR * RstName,
                               double scale,
                               double precision,
                               DOUBLEPOINT *point,
                               int compression,
                               int flagIgnoreGeoTiff,
                               int arg1, int arg2);

//========================================================================
//    Запросить параметры TIFF-файла
//    tifname     - имя TIFF-файла;
//    information -  указатель на структуру DATAINFORMATION для записи параметров TIFF-файла
//    Структура DATAINFORMATION описана в picexprm.h
//
//    Функцию LoadTifInformation рекомендуется вызывать перед началом
//    конвертации TIFF-файла в Rsw для инициализации диалога сопровождения
//========================================================================
_PICIMP long int _PICAPI LoadTifInformation(HMESSAGE handle, const char * TifName,
                                           DATAINFORMATION * information);

long int _PICAPI LoadTifInformationUn(HMESSAGE handle, const WCHAR * TifName, // 18/06/14
                                           DATAINFORMATION * information);

//========================================================================
//    Запросить параметры GeoTIFF-файла
//    TifName - имя GeoTIF-файла;
//    DataInformation - структура, которую необходимо заполнить
//    geoTIFFinformation - структура, которую необходимо заполнить
//    Структуры DATAINFORMATION и GEOTIFFINFORMATION описаны в picexprm.h
//
//    Функцию LoadGeoTifInformation рекомендуется вызывать перед началом
//    конвертации TIFF-файла в Rsw для инициализации диалога сопровождения
//========================================================================
_PICIMP long int _PICAPI LoadGeoTifInformation(HMESSAGE Handle, const char * TiffName,
                                              DATAINFORMATION * information,
                                              GEOTIFFINFORMATION* geoTIFFinformation);

_PICIMP long int _PICAPI LoadGeoTifInformationUn(HMESSAGE Handle, const WCHAR * TiffName,  // 18/06/14
                                              DATAINFORMATION * information,
                                              GEOTIFFINFORMATION* geoTIFFinformation);

//========================================================================
//    Запросить параметры СК из файла GeoTiff
//    Handle              - диалог визуального сопровождения процесса обработки.
//    TifName             - имя TIF-файла;
//    geoTIFFparam        - указатель на структуру GEOTIFFPARAM для записи
//                                                                параметров СК
//========================================================================
_PICIMP long int _PICAPI LoadGeoTiffParameters(HMESSAGE Handle, const char * TiffName,
                                              GEOTIFFPARAM * geoTIFFparam);

_PICIMP long int _PICAPI LoadGeoTiffParametersUn(HMESSAGE Handle, const WCHAR * TiffName,  // 18/06/14
                                              GEOTIFFPARAM * geoTIFFparam);

//#ifndef LINUXAPI	// 03/02/15 Korjilov
//======================================================================== // 24/11/03
//    Запросить параметры JPEG-файла
//    inputname   - имя JPEG-файла;
//    information -  указатель на структуру DATAINFORMATION для записи параметров JPEG-файла
//    Структура DATAINFORMATION описана в picexprm.h
//
//    Функцию LoadJPEGInformation рекомендуется вызывать перед началом
//    преобразования JPEG-файла в Rsw для вывода информации о графическом файле
//========================================================================
_PICIMP long int _PICAPI LoadJPEGInformation(const char * inputname,
                                            DATAINFORMATION * iformation);

_PICIMP long int _PICAPI LoadJPEGInformationUn(const WCHAR * inputname,
                                            DATAINFORMATION * iformation);

//========================================================================
//    map     - дескриптор открытого документа
//    PcxName - имя PCX-файла;
//    RstName - имя RST-файла;
//    scale   - масштаб создаваемого растра
//    precision - разрешающая способность создаваемого растра(т/м)
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//    flagMessage - флаг выдачи сообщений
//                                       (при ==1, сообщение выдаёт MessageBox;
//                                        при == 0, посылается сообщение диалогу WM_ERROR)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadJpegToRswAndCompress( HMAP map, HMESSAGE handle,
                                                  const char * inputname,
                                                  const char * rstname,
                                                  double scale,
                                                  double precisionMeters,
                                                  DOUBLEPOINT *point,
                                                  int compression,
                                                  int flagMessage);

_PICIMP long int _PICAPI LoadJpegToRswAndCompressUn( HMAP map, HMESSAGE handle,
                                                  const WCHAR * inputname,
                                                  const WCHAR * rstname,
                                                  double scale,
                                                  double precisionMeters,
                                                  DOUBLEPOINT *point,
                                                  int compression,
                                                  int flagMessage);

//========================================================================
// Сохранить изображение 24-х битного растра RSW в файл JPEG                    // 21/08/13
// hMap                - идентификатор документа с открытым растром rswName
// Handle              - диалог визуального сопровождения процесса обработки.
// rswName             - имя файла 24-х битного растра RSW
// jpegName            - имя файла JPEG
// compressJpegQuality - степень сжатия блока растра по алгоритму JPEG
//              Возможные значения: 1 - 100
//              Рекомендуемое значение: 60
//========================================================================
_PICIMP long int _PICAPI picexSaveRswToJpeg(HMAP hMap, HMESSAGE handle,
                                      const char * rswName, const char * jpegName,
                                      long int compressJpegQuality);

_PICIMP long int _PICAPI picexSaveRswToJpegUn(HMAP hMap, HMESSAGE handle,       // 20/06/14
                                      const WCHAR * rswName, const WCHAR * jpegName,
                                      long int compressJpegQuality);

//========================================================================
// Запросить параметры MrSID-файла (*.jp2;*.sid;*.ntf)
// handle              - диалог визуального сопровождения процесса обработки.
// inputname           - имя MrSID-файла
// information         - указатель на структуру DATAINFORMATION для записи
//                                                              параметров файла
// geoInformation      - указатель на структуру GEOTIFFINFORMATION для записи
//                                                        параметров изображения
//    Структуры DATAINFORMATION и GEOTIFFINFORMATION описаны в picexprm.h
//
//    Функцию LoadMrSIDInformation рекомендуется вызывать перед началом
//    преобразования MrSIDI-файла в Rsw для вывода информации о графическом файле
//========================================================================
_PICIMP long int _PICAPI LoadMrSIDInformation(HWND handle, const char * inputname,
                                             DATAINFORMATION * iformation,
                                             GEOTIFFINFORMATION* geoInformation);

_PICIMP long int _PICAPI LoadMrSIDInformationUn(HWND handle, const WCHAR * inputname,
                                             DATAINFORMATION * iformation,
                                             GEOTIFFINFORMATION* geoInformation);

//========================================================================
// Запросить параметры СК из файла MrSID
// name - имя файла MrSid (*.jp2;*.sid;*.ntf)
// geoTIFFparam - указатель на структуру GEOTIFFPARAM для записи параметров СК
//========================================================================
_PICIMP long int _PICAPI picexLoadGeoParametersMrSID(HMESSAGE Handle,
                                                    const char * name,
                                                    GEOTIFFPARAM * geoTIFFparam);

_PICIMP long int _PICAPI picexLoadGeoParametersMrSID_Un(HMESSAGE Handle,
                                                    const WCHAR * name,
                                                    GEOTIFFPARAM * geoTIFFparam);

//========================================================================
// Загрузка растровых данных в файл RSW
// обрабатываются файлы MrSid (*.jp2;*.sid;*.ntf)
//    Map - карта,содержащая векторные данные
//    inputname - имя загружаемого файла
//    rstname   - имя RST-файла
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг сжатия изображения
//              0 - сжатие к блокам изображения применяться не будет
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    flagMessage - флаг выдачи сообщений
//                                       (при ==1, сообщение выдает MessageBox;
//                                        при == 0, посылается сообщение диалогу WM_ERROR)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadMrSIDToRsw(HWND handle, TASKPARM* parm,
                                        const char * inputname, const char * rstname,
                                        double* meterInPixelX, double* meterInPixelY,
                                        DOUBLEPOINT *point,
                                        long int compression, long int flagMessage);

_PICIMP long int _PICAPI picexLoadMrSIDToRswUn(HWND handle, TASKPARM* parm,
                                        const WCHAR * inputname, const WCHAR * rstname,
                                        double* meterInPixelX, double* meterInPixelY,
                                        DOUBLEPOINT *point,
                                        long int compression, long int flagMessage);

_PICIMP long int _PICAPI LoadMrSIDToRsw(HWND handle, TASKPARM* parm,
                                        const char * inputname, const char * rstname,
                                        double scale, double precisionMeters,
                                        DOUBLEPOINT *point,
                                        long int compression, long int flagMessage);

_PICIMP long int _PICAPI LoadMrSIDToRswUn(HWND handle, TASKPARM* parm,
                                        const WCHAR * inputname, const WCHAR * rstname,
                                        double scale, double precisionMeters,
                                        DOUBLEPOINT *point,
                                        long int compression, long int flagMessage);

//========================================================================
// Загрузка растровых данных в файл RSW
// обрабатываются файлы MrSid (*.jp2;*.sid;*.ntf)
//    Map - карта,содержащая векторные данные
//    inputname - имя загружаемого файла
//    rstname   - имя RST-файла
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг сжатия изображения
//              0 - сжатие к блокам изображения применяться не будет
//              1 - блоки д.б. сжаты по методу LZW
//              2 - блоки д.б. сжаты по методу JPEG (справедливо для 24 битных растров)
//    compressJpegQuality - степень сжатия блока растра по алгоритму JPEG
//              Возможные значения: 1 - 100
//              Рекомендуемое значение: 60
//    flagMessage - флаг выдачи сообщений
//                                       (при ==1, сообщение выдает MessageBox;
//                                        при == 0, посылается сообщение диалогу WM_ERROR)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadMrSIDToRswAndCompress(HWND handle, TASKPARM* parm,
                                        const char * inputname, const char * rstname,
                                        double* meterInPixelX, double* meterInPixelY,
                                        DOUBLEPOINT *point,
                                        long int compression,
                                        long int compressJpegQuality,
                                        long int flagMessage);

_PICIMP long int _PICAPI picexLoadMrSIDToRswAndCompressUn(HWND handle, TASKPARM* parm,
                                        const WCHAR * inputname, const WCHAR * rstname,
                                        double* meterInPixelX, double* meterInPixelY,
                                        DOUBLEPOINT *point,
                                        long int compression,
                                        long int compressJpegQuality,
                                        long int flagMessage);

//#endif // LINUXAPI


//========================================================================
//    Сохранить растровую карту в формате BMP
//    map     - дескриптор открытого документа
//    handle  - диалог визуального сопровождения процесса обработки.
//    rstname - имя RST-файла;
//    bmpname - имя BMP-файла;
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstToBmpConverter(HMAP map, HMESSAGE handle,
                                              const char * rstname,
                                              const char * bmpname);

_PICIMP long int _PICAPI LoadRstToBmpConverterUn(HMAP map, HMESSAGE handle,
                                              const WCHAR * rstname,
                                              const WCHAR * bmpname);

//========================================================================
//    Сохранить растровую карту в формате BMP с возможной обрезкой изображения по рамке растра
//    map     - дескриптор открытого документа
//    handle  - диалог визуального сопровождения процесса обработки.
//    rstname - имя RST-файла;
//    bmpname - имя BMP-файла;
//    flagUseBorder - флаг "Вырезать изображение по рамке"(0/1)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstToBmpConverterEx(HMAP map, HMESSAGE handle,
                                                const char * rstname,
                                                const char * bmpname,
                                                int flagUseBorder);

_PICIMP long int _PICAPI LoadRstToBmpConverterExUn(HMAP map, HMESSAGE handle,
                                                const WCHAR * rstname,
                                                const WCHAR * bmpname,
                                                int flagUseBorder);

//========================================================================
//    Сохранить растровую карту в формате BMP
//    с предварительной очисткой области изображения цветом colorClear
//    Для растров с 1,4,8 бит на пиксель colorClear - индекс цвета палитры растра,
//    для растров с 16,24,32 бит на пиксель colorClear - цвет COLORREF,
//
//    map     - дескриптор открытого документа
//    handle  - диалог визуального сопровождения процесса обработки.
//    rstname - имя RST-файла;
//    bmpname - имя BMP-файла;
//    flagUseBorder - флаг "Вырезать изображение по рамке"
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstToBmpConverterClear(HMAP map, HMESSAGE handle,
                                                 const char * rstname,
                                                 const char * bmpname,
                                                 int flagUseBorder,
                                                 long colorClear);

_PICIMP long int _PICAPI LoadRstToBmpConverterClearUn(HMAP map, HMESSAGE handle,
                                                 const WCHAR * rstname,
                                                 const WCHAR * bmpname,
                                                 int flagUseBorder,
                                                 long colorClear);

//========================================================================
//    Сохранить растровую карту в формате PCX
//    map     - дескриптор открытого документа
//    handle  - диалог визуального сопровождения процесса обработки.
//    rstname - имя RST-файла;
//    pcxname - имя PCX-файла;
//    flagUseBorder - флаг "Вырезать изображение по рамке"
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI SaveRstToPcx(HMAP map, HMESSAGE handle,
                                     const char * rstname,
                                     const char * pcxname,
                                     int flagUseBorder);

_PICIMP long int _PICAPI SaveRstToPcxUn(HMAP map, HMESSAGE handle,               // 19/06/14
                                       const WCHAR *rstname,
                                       const WCHAR *pcxname,
                                       int flagUseBorder);

//========================================================================
//    Сохранить растровую карту в формате PCX
//    с предварительной очисткой области изображения цветом colorClear
//    Для растров с 1,4,8 бит на пиксель colorClear - индекс цвета палитры растра,
//    для растров с 16,24,32 бит на пиксель colorClear - цвет COLORREF,
//    map     - дескриптор открытого документа
//    handle  - диалог визуального сопровождения процесса обработки.
//    rstname - имя RST-файла;
//    pcxname - имя PCX-файла;
//    flagUseBorder - флаг "Вырезать изображение по рамке"
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI SaveRstToPcxClear(HMAP map, HMESSAGE handle,
                                          const char * rstname, const char * pcxname,
                                          int flagUseBorder, long colorClear);

_PICIMP long int _PICAPI SaveRstToPcxClearUn(HMAP map, HMESSAGE handle,          // 19/06/14
                                          const WCHAR *rstname, const WCHAR *pcxname,
                                          int flagUseBorder, long colorClear);

//========================================================================
//    Сохранить растровую карту в формате TIFF
//    Map      - дескриптор открытого документа
//    RstName  - имя RST-файла;
//    TiffName - имя TIFF-файла;
//    flagborder     - флаг использования рамки растровой карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой (рекомендуемое значение - 0)
//    platform - Тип платформы (0 - INTEL, 1 - MOTOROLA)             (рекомендуемое значение - 0)
//    imageStructure - Структура изображения TIFF (0 - BLOCK, 1- STRIP, 2 - NONFRAG) (рекомендуемое значение - 1)
//    compressMethod - Флаг сжатия изображения (0- не применять сжатие, 1 - сжатие PackBit) (рекомендуемое значение - 0)
//    flagCMYK - выбор цветовой модели:
//                     0 - цветовая модель RGB 24 бит на пиксел
//                     1 - цветовая модель CMYK 32 бит на пиксел
//                     Режим поддерживается только для  растров 24,32 бит на пиксел.
//    Handle - диалог визуального сопровождения процесса обработки.
//========================================================================
_PICIMP long int _PICAPI LoadRstToTiffConverter(HMAP Map, HMESSAGE Handle,
                                         const char * RstName, const char * TiffName,
                                         int flagborder,
                                         int platform, int imageStructure,
                                         int compressMethod,
                                         int flagCMYK);

_PICIMP long int _PICAPI LoadRstToTiffConverterUn(HMAP Map, HMESSAGE Handle,
                                         const WCHAR * RstName, const WCHAR * TiffName,
                                         int flagborder,
                                         int platform, int imageStructure,
                                         int compressMethod,
                                         int flagCMYK);

//======================================================================== // 25/10/05
//    Сохранить растровую карту в формате TIFF
//    Map            - дескриптор открытого документа
//    Handle         - диалог визуального сопровождения процесса обработки.
//    RstName        - имя RST-файла;
//    TiffName       - имя TIFF-файла;
//    flagborder     - флаг использования рамки растровой карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой
//                     (рекомендуемое значение - 0).
//    platform - Тип платформы (0 - INTEL, 1 - MOTOROLA)
//                     (рекомендуемое значение - 0).
//    imageStructure - Структура изображения TIFF (0 - BLOCK, 1- STRIP, 2 - NONFRAG)
//                     (рекомендуемое значение - 1).
//    compressMethod - Флаг сжатия изображения (0- не применять сжатие, 1 - сжатие PackBit)
//                     (рекомендуемое значение - 0).
//    flagCMYK - выбор цветовой модели:
//                     0 - цветовая модель RGB 24 бит на пиксел
//                     1 - цветовая модель CMYK 32 бит на пиксел
//                     Режим поддерживается только для  растров 24,32 бит на пиксел.
//    flagIntergraph - Флаг записи матрицы трансформирования,
//                        с помощью которой Intergraph определяет привязку растра
//    dframe         - Габариты изображения в районе в метрах.   // 25/10/05
//                     Параметр обязателен для записи матрицы трансформирования (если flagIntergraph == 1)
//    flag1 - flag6  - Не используются. Должны быть равны нулю.
//========================================================================
_PICIMP long int _PICAPI LoadRstToTiffConverterEx(HMAP Map, HMESSAGE Handle,
                                         const char * RstName, const char * TiffName,
                                         long int flagborder,
                                         long int platform,
                                         long int imageStructure,
                                         long int compressMethod,
                                         long int flagCMYK,
                                         long int flagIntergraph,
                                         DFRAME * dframe,
                                         long int flag1, long int flag2,
                                         long int flag3, long int flag4,
                                         long int flag5, long int flag6);

_PICIMP long int _PICAPI LoadRstToTiffConverterExUn(HMAP Map, HMESSAGE Handle,
                                         const WCHAR * RstName, const WCHAR * TiffName,
                                         long int flagborder,
                                         long int platform,
                                         long int imageStructure,
                                         long int compressMethod,
                                         long int flagCMYK,
                                         long int flagIntergraph,
                                         DFRAME * dframe,
                                         long int flag1, long int flag2,
                                         long int flag3, long int flag4,
                                         long int flag5, long int flag6);

//========================================================================  // 17/04/03
//    Вырезать изображение растровой карты по прямоугольной области, заданной в метрах
//    map           - дескриптор открытого документа
//    handle        - диалог визуального сопровождения процесса обработки.
//    rstInputName  - имя файла растровой карты;
//    rstOutputName - имя файла формируемой растровой карты;
//    frame         - габариты вырезаемой прямоугольной области(в метрах)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadCutOfRstByFrame (HMAP map, HMESSAGE handle,
                                             const char * rstInputName,
                                             const char * rstOutputName,
                                             DFRAME* frame);

_PICIMP long int _PICAPI LoadCutOfRstByFrameUn(HMAP map, HMESSAGE handle,
                                              const WCHAR * rstInputName,
                                              const WCHAR * rstOutputName,
                                              DFRAME* frame);

//========================================================================
//    Вырезать изображение растровой карты по прямоугольной области, заданной в метрах
//    map           - дескриптор открытого документа
//    handle        - диалог визуального сопровождения процесса обработки.
//    rstInputName  - имя файла растровой карты;
//    rstOutputName - имя файла формируемой растровой карты;
//    frame         - габариты вырезаемой прямоугольной области(в метрах)
//    flagUpdateRstDuplicates - флаг создания уменьшенной копии (0-нет, 1-да)
//
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadCutOfRstByFrameEx(HMAP map, HMESSAGE handle,
                                              const char * rstInputName,
                                              const char * rstOutputName,
                                              DFRAME* frame,
                                              int flagUpdateRstDuplicates);

_PICIMP long int _PICAPI LoadCutOfRstByFrameExUn(HMAP map, HMESSAGE handle,
                                              const WCHAR * rstInputName,
                                              const WCHAR * rstOutputName,
                                              DFRAME* frame,
                                              int flagUpdateRstDuplicates);

//========================================================================  // 15/05/03
//    Вырезать изображение матрицы по прямоугольной области, заданной в метрах
//    map           - дескриптор открытого документа
//    handle        - диалог визуального сопровождения процесса обработки.
//    rstInputName  - имя файла матрицы;
//    rstOutputName - имя файла формируемой матрицы;
//    frame         - габариты вырезаемой прямоугольной области(в метрах)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadCutOfMtrByFrame (HMAP map, HMESSAGE handle,
                                             const char * mtrInputName,
                                             const char * mtrOutputName,
                                             DFRAME* frame);

_PICIMP long int _PICAPI LoadCutOfMtrByFrameUn(HMAP map, HMESSAGE handle,        // 18/06/14
                                             const WCHAR * mtrInputName,
                                             const WCHAR * mtrOutputName,
                                             DFRAME* frame);

//========================================================================
// Вырезать изображение матрицы по прямоугольной области
// с учётом рамки исходной матрицы
//   map           - дескриптор открытого документа
//   handle        - диалог визуального сопровождения процесса обработки
//   mtrInputName  - имя файла исходной матрицы
//   mtrOutputName - имя файла формируемой матрицы
//   frame         - габариты вырезаемой прямоугольной области(в метрах)
//   flag - флаг учёта рамки исходной матрицы, значения :
//     0 - рамка исходной матрицы не учитывается,
//     1 - элементы исходной матрицы, находящиеся вне рамки, не используются
//         (чистка формируемых элементов вне рамки)
//     2 - значения элементов исходной матрицы, находящихся вне рамки,
//         заменяются на fillValue (заливка значением fillValue
//         формируемых элементов вне рамки)
//   fillValue - значение для заливки формируемых элементов вне рамки,
//               используется при flag = 2, должно быть больше -111111
//               (если fillValue <= -111111, то выполняется чистка формируемых
//                элементов вне рамки как при flag = 1)
//   Диалогу визуального сопровождения процесса обработки посылаются
//   сообщения:
//   -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//      WPARAM - текущее состоние процесса в процентах (0% - 100%)
//      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//   -  (WM_ERROR) Извещение об ошибке
//      LPARAM - указатель на структуру ERRORINFORMATION
//      Структура ERRORINFORMATION описана в picexprm.h,
//      WM_PROGRESSBAR и WM_ERROR - в maptype.h
//
//   При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI LoadCutOfMtrByFrameEx(HMAP map, HMESSAGE handle,
                                              const char * mtrInputName,
                                              const char * mtrOutputName,
                                              DFRAME * frame,
                                              long int flag,
                                              double fillValue);

_PICIMP long int _PICAPI LoadCutOfMtrByFrameExUn(HMAP map, HMESSAGE handle,      // 18/06/14
                                              const WCHAR * mtrInputName,
                                              const WCHAR * mtrOutputName,
                                              DFRAME * frame,
                                              long int flag,
                                              double fillValue);

//==============================================================================
//    Трансформирование матрицы
// (вычисление коэффициентов пересчета координат методом наименьших квадратов)
//
//   handle    - диалог визуального сопровождения процесса обработки;
//   map       - дескриптор открытого документа
//   parm      - параметры прикладной задачи;
//   namein    - имя исходного растра (MAX_PATH_LONG)
//   nameout   - имя выходного растра (размер выделенной памяти д.б. не менее MAX_PATH_LONG символов)
//   fact      - исходные координаты опоры;
//   teor      - желаемые координаты опоры;
//   count     - количество опорных точек.
//
//   Диалогу визуального сопровождения процесса обработки посылаются сообщения:
//   -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//      WPARAM - текущее состояние процесса в процентах (0% - 100%)
//      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль,
//==============================================================================
_PICIMP long int _PICAPI MtwTransformingBySquareMethod(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm, const char * namein, char * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);

//   sizeNameOut - размер выделенной памяти для nameout в байтах
_PICIMP long int _PICAPI MtwTransformingBySquareMethodUn(HMAP map,HMESSAGE handle,  // 19/06/14
                           TASKPARMEX * parm, const WCHAR * namein,
                           WCHAR * nameout, int sizeNameOut,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);

//==============================================================================
//    Сохранить матрицу в файл формата TIFF
//    handle         - диалог визуального сопровождения процесса обработки.
//    mtwName        - имя файла матрицы
//    tiffName       - имя TIFF-файла;
//    flagborder     - флаг использования рамки
//                     0 - включать в формируемый файл все элементы матрицы
//                     1 - не включать в формируемый файл элементы матрицы
//                         невходящие в область, ограниченную рамкой
//    dframe         - прямоугольная область сохраняемых элементов матрицы
//                     указатель м.б. равен нулю
//==============================================================================
_PICIMP long int _PICAPI LoadMtwToTiffConverter(HMESSAGE handle,                 // 01/07/14
                                       char * mtwName, char * tiffName,
                                       long int flagborder, DFRAME* dframe);

_PICIMP long int _PICAPI LoadMtwToTiffConverterUn(HMESSAGE handle,               // 01/07/14
                                         const WCHAR * mtwName, const WCHAR * tiffName,
                                         long int flagborder, DFRAME* dframe);

//========================================================================      // 14/03/16
//    Сохранить матрицу в формате TIFF
//    handle         - диалог визуального сопровождения процесса обработки.
//    mtwName        - имя файла матрицы
//    tiffName       - имя TIFF-файла;
//    fileName       - имя файла параметров (TFW, TAB);
//    flagborder     - флаг использования рамки
//                     0 - включать в формируемый файл все элементы матрицы
//                     1 - не включать в формируемый файл элементы матрицы
//                         невходящие в область, ограниченную рамкой
//    dframe         - прямоугольная область сохраняемых элементов матрицы
//                     указатель м.б. равен нулю
//========================================================================
_PICIMP long int _PICAPI LoadMtwToTiffConverterExUn(HMESSAGE handle,
                                         const WCHAR * mtwName,
                                         const WCHAR * tiffName,
                                         const WCHAR * fileName,
   				         long int flagborder, DFRAME* dframe);

//==============================================================================
// Загрузка матриц из формата SRTM (GeoTIFF)
//    map            - дескриптор открытого документа
//    Handle         - диалог визуального сопровождения процесса обработки.
//    nameTiff       - имя исходного файла формата SRTM (GeoTIFF)
//    nameMtr        - имя файла формируемой матрицы
//    scale          - масштаб формируемой матрицы
//    flagCompress   - параметр не используется, д.б. равен 0.
//==============================================================================
_PICIMP long int _PICAPI LoadGeoTiffToMtr(HMAP map, HMESSAGE handle,                 // 01/07/14	// 06/02/15 Korjilov
                                 const char* nameTiff, const char* nameMtr,
                                 double scale, long int flagCompress);

_PICIMP long int _PICAPI LoadGeoTiffToMtrUn(HMAP map, HMESSAGE handle,               // 01/07/14	// 06/02/15 Korjilov
                                   const WCHAR* nameTiff, const WCHAR* nameMtr,
                                   double scale, long int flagCompress);

//#ifndef LINUXAPI								// 13/02/15 Korjilov
//================================================-========================
//    Сохранить карту в формате BMP, Tiff, RSW  // 15/01/10
//    map        - дескриптор открытого документа, содержащего векторные, растровые и др. данные;
//    handle     - диалог сопровождения процесса обработки;
//    dframe     - фрагмент сохраняемой карты(в метрах на местности)
//    bitcount   - кол-во бит на пиксел сохраняемого изображения (16, 24-рекомендуемое значение, 32)
//    scale      - масштаб сохраняемого изображения
//    resolution - разрешающая способность сохраняемого изображения(т/м)
//    filename   - имя файла сохраняемого изображения (*.bmp, *.tif);
//    handleMainWin - должен быть равен нулю
//    При ошибке функция возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//================================================-========================
_PICIMP long int _PICAPI LoadMapToPicture(HMAP map,HMESSAGE handle,
                                 DFRAME * dframe, long bitcount,
                                 long scale, long resolution,
                                 const char* filename,
                                 HMESSAGE handleMainWin);

_PICIMP long int _PICAPI LoadMapToPictureUn(HMAP map,HMESSAGE handle,
                                 DFRAME * dframe, long bitcount,
                                 long scale, long resolution,
                                 const WCHAR* filename,
                                 HMESSAGE handleMainWin);

//========================================================================
//    Сохранить карту как TIFF GrayScale (8 бит на пиксель - 256 градаций серого)   // 30/08/10
//    map        - дескриптор открытого документа, содержащего векторные, растровые и др. данные;
//    handle     - диалог сопровождения процесса обработки;
//    dframe     - фрагмент сохраняемой карты(в метрах на местности)
//    scale      - масштаб сохраняемого изображения
//    resolution - разрешающая способность сохраняемого изображения(т/м)
//    tiffName   - имя сохраняемого TIFF-файла;
//    handleMainWin - должен быть равен нулю
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadMapToGrayScaleTiff(HMAP map,HMESSAGE handle,
                                               DFRAME * dframe, long scale, long resolution,
                                               const char* tiffName, HMESSAGE handleMainWin);

_PICIMP long int _PICAPI LoadMapToGrayScaleTiffUn(HMAP Map,HMESSAGE Handle,
                                               DFRAME * dframe, long scale, long resolution,
                                               const WCHAR* tiffName, HMESSAGE handleMainWin);

//========================================================================
//    Сохранить карту в формате BMP
//    map        - дескриптор открытого документа, содержащего векторные, растровые и др. данные;
//    handle       - диалог визуального сопровождения процесса обработки.
//    dframe       - фрагмент сохраняемой карты(в метрах на местности)
//    bitcount     - кол-во бит на пиксел сохраняемого изображения(16,24,32)
//    scale        - масштаб сохраняемого изображения
//    resolution   - разрешающая способность сохраняемого изображения(т/д)
//    bmpname      - имя файла сохраняемого изображения (*.bmp);
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadMapToBmp(HMAP map,HMESSAGE handle,
                                    DFRAME * dframe, long bitcount,
                                    long scale, long resolution,
                                    const char* bmpname);

_PICIMP long int _PICAPI LoadMapToBmpUn(HMAP map,HMESSAGE handle,
                                    DFRAME * dframe, long bitcount,
                                    long scale, long resolution,
                                    const WCHAR* bmpname);


//========================================================================
//    Сохранить карту в формате EMF
//    map          - дескриптор открытого документа, содержащего векторные, растровые и др. данные;
//    handle       - диалог визуального сопровождения процесса обработки.
//    rectmetr     - фрагмент сохраняемой карты(в метрах на местности)
//    bitcount = 24 - кол-во бит на пиксел сохраняемого изображения
//    scale        - масштаб сохраняемого изображения
//    resolution   - разрешающая способность сохраняемого изображения(т/м)
//    emfname      - имя файла сохраняемого изображения (*.emf);
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadMapToEmf(HMAP map,HMESSAGE handle,
                                    RECT rectmetr, long bitcount,
                                    long scale, long resolution,
                                    const char* emfname);

_PICIMP long int _PICAPI LoadMapToEmfUn(HMAP map,HMESSAGE handle,
                                    RECT rectmetr, long bitcount,
                                    long scale, long resolution,
                                    const WCHAR* emfname);

//========================================================================
// Сохранить карту в растровом формате CMYK и RGB (BMP, ...)
// с целью подготовки карты к печати
//
//  parm   - параметры построения изображения
//
//  Диалогу визуального сопровождения процесса обработки посылаются
//  сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
// (При работе программы используется около 60 Мб оперативной памяти)
//========================================================================
_PICIMP long int _PICAPI LoadMapToRasterForPrint(SAVEASPICTRPARM_FOR_PRINT* parm);

//========================================================================
// Сохранить карту в растровом формате CMYK (BMP, ...)
//
//  map    - дескриптор открытого документа, содержащего векторные, растровые данные;
//  handle - диалог визуального сопровождения процесса обработки
//  rect   - область сохраняемой карты (в пикселах)
//  parm   - дополнительные параметры отображения (см. pictrapi.h)
//
//  Диалогу визуального сопровождения процесса обработки посылаются
//  сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//========================================================================
_PICIMP long int _PICAPI LoadMapToRasterCMYK(HMAP map, HMESSAGE handle,
                                            RECT* rect,
                                            SAVEASPICTRPARM* parm);


//========================================================================
// Вывести изображение карты в метафайл с обрезкой объектов по рамке
// (Функция реализована только для платформы Windows)
//    handle         - диалог визуального сопровождения процесса обработки.
//    map            - дескриптор открытого документа, содержащего векторные,
//                     растровые и др. данные;
//    name           - имя метафайла
//    Структура METAFILEBUILDPARMEX описана в maptype.h
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке в параметрах возвращает ноль
//========================================================================
_PICIMP long int _PICAPI PaintToEmfByFrame(HMESSAGE handle, HMAP hMap,
                                          const char * name,
                                          METAFILEBUILDPARMEX * parm);

_PICIMP long int _PICAPI PaintToEmfByFrameUn(HMESSAGE handle, HMAP hMap,
                                          const WCHAR * name,
                                          METAFILEBUILDPARMEX * parm);

//#endif // LINUXAPI


//========================================================================
//    Оптимизировать файл растровой карты с возможным сжатием изображения
//    handle         - диалог визуального сопровождения процесса обработки.
//    name           - имя файла растровой карты
//    newname        - имя файла оптимизированной растровой карты
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     1 - алгоритм сжатия LZW
//    flagborder     - флаг использования рамки растровой карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения,
//                         не входящие в область, ограниченную рамкой
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstOptimization(HMESSAGE handle,
                                    const char* name, const char* newname,
                                    long int compressnumber,
                                    long int flagborder);

_PICIMP long int _PICAPI LoadRstOptimizationUn(HMESSAGE handle,                  // 19/06/14
                                    const WCHAR* name, const WCHAR* newname,
                                    long int compressnumber,
                                    long int flagborder);

//========================================================================  // 04/06/13
//    Оптимизировать файл растровой карты с возможным сжатием изображения
//    handle         - диалог визуального сопровождения процесса обработки.
//    map            - дескриптор открытого документа, содержащего растр name
//    name           - имя файла растровой карты
//    newname        - имя файла оптимизированной растровой карты
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     1 - алгоритм сжатия LZW
//                     2 - алгоритм сжатия JPEG (для 24 битных растров)
//    jpegCompressValue - степень сжатия изображения растра по алгоритму JPEG   // 04/12/11
//                        имеет значение, если compressnumber присвоено значение 2
//                        (1-100, 1-максимальное сжатие, 100-сжатие без потери качества),
//                         рекомендуется значение 60.
//    flagborder     - флаг использования рамки растровой карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой
//     Добавлен пересчет габаритов растра при обрезке изображения по
//     рамке растра (когда flagborder == 1).
//    При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI LoadRstOptimizationAndCompress(HMESSAGE handle, HMAP hMap,
                                       const char* name, const char* newname,
                                       long int compressnumber, long int jpegCompressValue,
                                       long int flagborder);

_PICIMP long int _PICAPI LoadRstOptimizationAndCompressUn(HMESSAGE handle, HMAP hMap,
                                       const WCHAR* name, const WCHAR* newname,
                                       long int compressnumber, long int jpegCompressValue,
                                       long int flagborder);

//========================================================================
//    Оптимизировать файл растровой карты с возможным сжатием изображения и
//    созданием уменьшенной копии растра
//    handle         - диалог визуального сопровождения процесса обработки.
//    map            - дескриптор открытого документа, содержащего растр name
//    name           - имя файла растровой карты
//    newname        - имя файла оптимизированной растровой карты
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     1 - алгоритм сжатия LZW
//                     2 - алгоритм сжатия JPEG (для 24 битных растров)
//    jpegCompressValue - степень сжатия изображения растра по алгоритму JPEG
//                        имеет значение, если compressnumber присвоено значение 2
//                        (1-100, 1-максимальное сжатие, 100-сжатие без потери качества),
//                         рекомендуется значение 60.
//    flagborder     - флаг использования рамки растровой карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         не входящие в область, ограниченную рамкой
//    flagSaveCopy   - флаг сохранения копии исходного файла с именем *.~rw
//                     0 - не создавать копию исходного файла
//                     1 - создать копию исходного файла
// flag_CreateDuplicate- флаг создания уменьшенной копии растра
//                     0 - не создавать уменьшенную копию растра
//                     1 - создавать уменьшенную копию растра
// flag              - не используется. Должен быть равен 0.
//
//     Добавлен пересчет габаритов растра при обрезке изображения по
//     рамке растра (когда flagborder == 1).
//    При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI LoadRstOptimizationWithSurveyImage(HMESSAGE handle,
                                   HMAP hMap, const char* name, const char* newname,
                                   long int compressnumber, long int jpegCompressValue,
                                   long int flagborder, long int flagSaveCopy,
                                   long int flag_CreateDuplicate, long int flag);

_PICIMP long int _PICAPI LoadRstOptimizationWithSurveyImageUn(HMESSAGE handle,   // 19/06/14
                                   HMAP hMap, const WCHAR* name, const WCHAR* newname,
                                   long int compressnumber, long int jpegCompressValue,
                                   long int flagborder, long int flagSaveCopy,
                                   long int flag_CreateDuplicate, long int flag);

//========================================================================
//                       УСТАРЕВШАЯ ФУНКЦИЯ    // 04/06/13
//    Оптимизировать файл растровой карты с возможным сжатием изображения
//    handle         - диалог визуального сопровождения процесса обработки.
//    map            - дескриптор открытого документа, содержащего растр name
//    name           - имя файла растровой карты
//    newname        - имя файла оптимизированной растровой карты
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     1 - алгоритм сжатия LZW
//                     2 - алгоритм сжатия JPEG (для 24 битных растров)
//    jpegCompressValue - степень сжатия изображения растра по алгоритму JPEG
//                        имеет значение, если compressnumber присвоено значение 2
//                        (1-100, 1-максимальное сжатие, 100-сжатие без потери качества),
//                         рекомендуется значение 60.
//    flagborder     - флаг использования рамки растровой карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой
//     Добавлен пересчет габаритов растра при обрезке изображения по
//     рамке растра (когда flagborder == 1).
//    При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI LoadRstOptimizationEx1(HMESSAGE handle, HMAP hMap,
                                       const char* name, const char* newname,
                                       long int compressnumber, long int jpegCompressValue,
                                       long int flagborder);

//========================================================================  // 28/10/03
//    Оптимизировать файл растровой карты с возможным сжатием изображения
//    handle         - диалог визуального сопровождения процесса обработки.
//    hMap           - дескриптор открытого документа, содержащего растр name
//    name           - имя файла растровой карты
//    newname        - имя файла оптимизированной растровой карты
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     1 - алгоритм сжатия LZW
//    flagborder     - флаг использования рамки растровой карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой
//     Добавлен пересчет габаритов растра при обрезке изображения по
//     рамке растра (когда flagborder == 1).
//    При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI LoadRstOptimizationEx(HMESSAGE handle, HMAP hMap,
                                              const char* name, const char* newname,
                                              long int compressnumber,
                                              long int flagborder);

_PICIMP long int _PICAPI LoadRstOptimizationExUn(HMESSAGE handle, HMAP hMap,
                                              const WCHAR* name, const WCHAR* newname,
                                              long int compressnumber,
                                              long int flagborder);

//========================================================================
//    Оптимизировать файл матричной карты с возможным сжатием изображения
//    handle         - диалог визуального сопровождения процесса обработки.
//    name           - имя файла матричной карты
//    newname        - имя файла оптимизированной матричной карты
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     32 - алгоритм сжатия матрицы
//    flagborder     - флаг использования рамки матричной карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadMtrOptimization(HMESSAGE handle,
                                    const char* name, const char* newname,
                                    long int compressnumber,
                                    long int flagborder);

_PICIMP long int _PICAPI LoadMtrOptimizationUn(HMESSAGE handle,                  // 19/06/14
                                    const WCHAR* name, const WCHAR* newname,
                                    long int compressnumber,
                                    long int flagborder);


//========================================================================  // 29/10/03
//    Оптимизировать файл матричной карты с возможным сжатием изображения
//    handle         - диалог визуального сопровождения процесса обработки.
//    hMap           - дескриптор открытого документа, содержащего матрицу name
//    name           - имя файла матричной карты
//    newname        - имя файла оптимизированной матричной карты
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     32 - алгоритм сжатия матрицы
//    flagborder     - флаг использования рамки матричной карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой
//     Добавлен пересчет габаритов матричной карты при обрезке изображения по
//     рамке матричной карты (когда flagborder == 1).
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadMtrOptimizationEx(HMESSAGE handle, HMAP hMap,
                                    const char* name, const char* newname,
                                    long int compressnumber,
                                    long int flagborder);

_PICIMP long int _PICAPI LoadMtrOptimizationExUn(HMESSAGE handle, HMAP hMap,
                                    const WCHAR* name, const WCHAR* newname,
                                    long int compressnumber,
                                    long int flagborder);

//========================================================================      // 19/03/12
//    Оптимизировать файл матрицы высот с возможным сжатием изображения и
//    созданием уменьшенной копии изображения
//    handle         - диалог визуального сопровождения процесса обработки.
//    hMap           - дескриптор открытого документа, содержащего растр name
//    name           - имя файла матрицы высот
//    newname        - имя файла оптимизированной матрицы высот
//    compressnumber - номер алгоритма сжатия блоков
//                     0 - не использовать сжатие
//                     32 - алгоритм сжатия матрицы
//    flagborder     - флаг использования рамки матрицы высот
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         не входящие в область, ограниченную рамкой
// flag_CreateDuplicate- флаг создания уменьшенной копии
//                     0 - не создавать уменьшенную копию
//                     1 - создавать уменьшенную копию
// flag              - не используется. Должен быть равен 0.
//
//     Добавлен пересчет габаритов матрицы высот при обрезке изображения по
//     рамке матрицы высот (когда flagborder == 1).
//    При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI LoadMtrOptimizationWithSurveyImage(HMESSAGE handle, HMAP hMap,
                                   const char* name, const char* newname,
                                   long int compressnumber,
                                   long int flagborder,
                                   long int flag_CreateDuplicate, long int flag);

_PICIMP long int _PICAPI LoadMtrOptimizationWithSurveyImageUn(HMESSAGE handle, HMAP hMap,  // 19/06/14
                                   const WCHAR* name, const WCHAR* newname,
                                   long int compressnumber,
                                   long int flagborder,
                                   long int flag_CreateDuplicate, long int flag);

#ifndef HIDEMTQ          // 18/01/12
//========================================================================      // 26/03/12
//    Оптимизировать файл матрицы качества MTQ с возможным сжатием изображения и
//    созданием уменьшенной копии изображения
//
//    ВНИМАНИЕ: сжатие может быть применено к матрицам с размером элемента в 4 байта
//
//    handle         - диалог визуального сопровождения процесса обработки.
//    map            - карта,содержащая векторные данные;
//    name           - имя файла матрицы качества MTQ
//    newname        - имя файла оптимизированной матрицы качества MTQ
//    compressnumber - номер алгоритма сжатия блоков
//                     0 - не использовать сжатие
//                     32 - алгоритм сжатия матрицы
//    flagborder     - флаг использования рамки матрицы качества MTQ
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         не входящие в область, ограниченную рамкой
// flag_CreateDuplicate- флаг создания уменьшенной копии
//                     0 - не создавать уменьшенную копию
//                     1 - создавать уменьшенную копию
// flag              - не используется. Должен быть равен 0.
//
//     Добавлен пересчет габаритов матрицы качества MTQ при обрезке изображения по
//     рамке матрицы качества MTQ (когда flagborder == 1).
//    При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI LoadMtqOptimizationWithSurveyImage(HMESSAGE handle, HMAP hMap,
                                   const char* name, const char* newname,
                                   long int compressnumber,
                                   long int flagborder,
                                   long int flag_CreateDuplicate, long int flag);

_PICIMP long int _PICAPI LoadMtqOptimizationWithSurveyImageUn(HMESSAGE handle, HMAP hMap,
                                   const WCHAR* name, const WCHAR* newname,
                                   long int compressnumber,
                                   long int flagborder,
                                   long int flag_CreateDuplicate, long int flag);

//========================================================================  // 18/01/12
//    Оптимизировать файл матрицы качества MTQ с возможным сжатием изображения
//
//    ВНИМАНИЕ: сжатие может быть применено к матрицам с размером элемента в 4 байта
//
//    map            - карта,содержащая векторные данные;
//    handle         - диалог визуального сопровождения процесса обработки.
//    name           - имя файла матрицы качества
//    newname        - имя файла оптимизированной матрицы качества
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     32 - алгоритм сжатия матрицы качества
//    flagborder     - флаг использования рамки матрицы качества
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой
//     Добавлен пересчет габаритов матрицы качества при обрезке изображения по
//     рамке матрицы качества (когда flagborder == 1).
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================    // 18/01/12
_PICIMP long int _PICAPI LoadMtqOptimizationEx(HMESSAGE handle, HMAP hMap,
                                    const char* name, const char* newname,
                                    long int compressnumber,
                                    long int flagborder);

_PICIMP long int _PICAPI LoadMtqOptimizationExUn(HMESSAGE handle, HMAP hMap,
                                    const WCHAR* name, const WCHAR* newname,
                                    long int compressnumber,
                                    long int flagborder);

//========================================================================
//    Оптимизировать файл матрицы качества MTQ с возможным сжатием изображения
//
//    ВНИМАНИЕ: сжатие может быть применено к матрицам с размером элемента в 4 байта
//
//    handle         - диалог визуального сопровождения процесса обработки.
//    name           - имя файла матричной карты
//    newname        - имя файла оптимизированной матричной карты
//    compressnumber - номер алгоритма сжатия блоков изображения
//                     0 - не использовать сжатие
//                     32 - алгоритм сжатия матрицы
//    flagborder     - флаг использования рамки матричной карты
//                     0 - включать в формируемый файл все блоки изображения
//                     1 - не включать в формируемый файл блоки изображения
//                         невходящие в область, ограниченную рамкой
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadMtqOptimization(HMESSAGE handle,
                                    const char* name, const char* newname,
                                    long int compressnumber,
                                    long int flagborder);

_PICIMP long int _PICAPI LoadMtqOptimizationUn(HMESSAGE handle,       // 19/06/14
                                    const WCHAR* name, const WCHAR* newname,
                                    long int compressnumber,
                                    long int flagborder);

//========================================================================  // 18/01/12
//    Вырезать изображение матрицы по прямоугольной области, заданной в метрах
//    map           - карта, содержащая векторные данные;
//    handle        - диалог визуального сопровождения процесса обработки.
//    rstInputName  - имя файла матрицы;
//    rstOutputName - имя файла формируемой матрицы;
//    frame         - габариты вырезаемой прямоугольной области(в метрах)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadCutOfMtqByFrame (HMAP map, HMESSAGE handle,
                                             const char * mtqInputName,
                                             const char * mtqOutputName,
                                             DFRAME* frame);

_PICIMP long int _PICAPI LoadCutOfMtqByFrameUn(HMAP map, HMESSAGE handle,
                                             const WCHAR * mtqInputName,
                                             const WCHAR * mtqOutputName,
                                             DFRAME* frame);

#endif // HIDEMTQ          // 18/01/12


//========================================================================
//    Поворот растровой карты
//
//    handle         - диалог визуального сопровождения процесса обработки.
//    hmap           - идентификатор открытой векторной карты
//    name           - имя файла растровой карты
//    newname        - имя файла растровой карты с зеркальным изображением
//    mirrortype     - тип обработки
//                     (0- Получение зеркального изображения растровой карты
//                           относитльно вертикальной оси )
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstMirror(HMESSAGE handle, HMAP map,
                                    const char* name, const char* newname,
                                    long int mirrortype);

_PICIMP long int _PICAPI LoadRstMirrorUn(HMESSAGE handle, HMAP map,                // 20/06/14
                                    const WCHAR* name, const WCHAR* newname,
                                    long int mirrortype);

//======================================================================== 
//    Сохранить изображение уменьшенной копии растровой карты как самостоятельный растр
//    map           - карта, содержащая векторные данные;
//    handle        - диалог визуального сопровождения процесса обработки.
//    rstInputName  - имя файла растровой карты;
//    rstOutputName - имя файла формируемой растровой карты;
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstDuplicateAs (HMAP map, HMESSAGE handle,
                                            const char * rstInputName,
                                            const char * rstOutputName);



//========================================================================
//    Поворот растра вокруг точки NullPoint на угол Angle      // 17/05/05
//
//    map        - карта,содержащая векторные данные;
//    RstNumber  - номер исходного растра в цепочке растров
//    NameRstIn  - имя исходного растра;
//    NameRstOut - имя выходного растра;
//    NullPoint  - координаты точки поворота в элементах растра;
//    Angle      - угол поворота (в радианах);
//    handle     - диалог визуального сопровождения процесса обработки.
//========================================================================
_PICIMP long int _PICAPI RstRotating(HMAP map, long int RstNumber,
                                    const char * NameRstIn, const char * NameRstOut,
                                    DOUBLEPOINT NullPoint, double Angle,
                                    HMESSAGE handle);

_PICIMP long int _PICAPI RstRotatingUn(HMAP Map, long int RstNumber,
                                    const WCHAR * NameRstIn, const WCHAR * NameRstOut,
                                    DOUBLEPOINT NullPoint, double Angle,
                                    HMESSAGE Handle);

//========================================================================
//    Поворот растра вокруг точки NullPoint на угол Angle        // 17/05/05
//
//    map        - карта,содержащая векторные данные;
//    RstNumber  - номер исходного растра в цепочке растров
//    NameRstIn  - имя исходного растра;
//    NameRstOut - имя выходного растра;
//    NullPoint  - координаты точки поворота в метрах на местности;
//    Angle      - угол поворота (в радианах);
//    handle     - диалог визуального сопровождения процесса обработки.
//========================================================================
_PICIMP long int _PICAPI RstPlaneRotating(HMAP map, long int RstNumber,
                                     const char * NameRstIn, const char * NameRstOut,
                                     DOUBLEPOINT NullPoint, double Angle,
                                     HMESSAGE handle);

_PICIMP long int _PICAPI RstPlaneRotatingUn(HMAP map, long int RstNumber,
                                     const WCHAR * NameRstIn, const WCHAR * NameRstOut,
                                     DOUBLEPOINT NullPoint, double Angle,
                                     HMESSAGE handle);

//========================================================================
// Привязка растра с масштабированием по двум точкам
// Внимание: Возможна устанавка отличных друг от друга размеров пикселя по X и по Y
//
// ВАЖНО:
// Если размеры пикселя по X и по Y отличаются друг от друга, то в растр
// устанавливается версия  1.04 (0x0104).
// Растры версии 1.04 открываются в ПО начинаяя с 11-ой версии.
//
// hMap        - карта, содержащая векторные данные;
// rswName     - имя файла растра
// pointMet1   - Координаты первой точки  в метрах
// pointMet1   - Координаты первой точки в метрах
// pointMet2   - Координаты второй точки  в метрах
// pointMet2   - Координаты второй точки в метрах
// message     - флаг на выдачу сообщений (0\1)
// При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI AttachRswWithScaling(HMAP hMap, const char* rswName,
                                             DOUBLEPOINT *pointMet1, DOUBLEPOINT *pointMetNew1,
                                             DOUBLEPOINT *pointMet2, DOUBLEPOINT *pointMetNew2,
                                             int message);

_PICIMP long int _PICAPI AttachRswWithScalingUn(HMAP hMap, const WCHAR * rswName,
                                             DOUBLEPOINT *pointMet1, DOUBLEPOINT *pointMetNew1,
                                             DOUBLEPOINT *pointMet2, DOUBLEPOINT *pointMetNew2,
                                             int message);


//========================================================================
// Привязка растра с масштабированием по двум точкам
// Внимание: Устанавливается одинаковый размер пикселя по X и по Y
//
// hMap        - карта, содержащая векторные данные;
// rswName     - имя файла растра
// pointMet1   - Координаты первой точки  в метрах
// pointMet1   - Координаты первой точки в метрах
// pointMet2   - Координаты второй точки  в метрах
// pointMet2   - Координаты второй точки в метрах
// message     - флаг на выдачу сообщений (0\1)
// При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI AttachRswWithScalingEx(HMAP hMap, const char* rswName,
                                             DOUBLEPOINT *pointMet1, DOUBLEPOINT *pointMetNew1,
                                             DOUBLEPOINT *pointMet2, DOUBLEPOINT *pointMetNew2,
                                             int message);

_PICIMP long int _PICAPI AttachRswWithScalingExUn(HMAP hMap, const WCHAR* rswName,
                                             DOUBLEPOINT *pointMet1, DOUBLEPOINT *pointMetNew1,
                                             DOUBLEPOINT *pointMet2, DOUBLEPOINT *pointMetNew2,
                                             int message);

//========================================================================
// Привязка растра с масштабированием и поворотом по двум точкам  // 15/09/05
// hmap          - идентификатор карты, к которой добавляется растр
// handle        - идентификатор окна диалога для обработки сообщений о ходе процесса
// rswname       - путь к файлу растра, который трансформируется
// pointmet1     - исходные координаты первой точки в метрах
// pointmetnew1  - желаемые координаты первой точки в метрах
// pointmet2     - исходные координаты второй точки в метрах
// pointmet2     - желаемые координаты второй точки в метрах
// message       - флаг на выдачу сообщений (0\1) в процессе трансформирования
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//       WPARAM - текущее состояние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI AttachRswWithScalingAndRotation(HMAP hmap, HMESSAGE handle, const char* rswname, // 21/09/05
                                             DOUBLEPOINT *pointmet1, DOUBLEPOINT *pointmetnew1,
                                             DOUBLEPOINT *pointmet2, DOUBLEPOINT *pointmetnew2,
                                             int message);

_PICIMP long int _PICAPI AttachRswWithScalingAndRotationUn(HMAP hmap, HMESSAGE handle, const WCHAR * rswname,
                                             DOUBLEPOINT *pointmet1, DOUBLEPOINT *pointmetnew1,
                                             DOUBLEPOINT *pointmet2, DOUBLEPOINT *pointmetnew2,
                                             int message);

//========================================================================
// Привязка растра с масштабированием и поворотом по двум точкам          // 10/03/06
//
// hmap        - карта, содержащая векторные данные;
// handle      - диалог визуального сопровождения процесса обработки.
// rswnamein   - имя исходного файла растра
// rswNameOut  - имя выходного файла растра (размер строки д.б. не менее MAX_PATH_LONG байт)
// pointmet1   - Координаты первой точки  в метрах
// pointmet1   - Координаты первой точки в метрах
// pointmet2   - Координаты второй точки  в метрах
// pointmet2   - Координаты второй точки в метрах
// message     - флаг на выдачу сообщений (0\1)
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//       WPARAM - текущее состояние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI AttachRswWithScalingAndRotationEx(HMAP hmap, HMESSAGE handle,
                                             const char* rswnamein, char* rswnameout,
                                             DOUBLEPOINT *pointmet1, DOUBLEPOINT *pointmetnew1,
                                             DOUBLEPOINT *pointmet2, DOUBLEPOINT *pointmetnew2,
                                             int message);

// sizeNameIn  - размер строки rswName в байтах
// sizeNameOut - размер строки rswNameOut в байтах
_PICIMP long int _PICAPI AttachRswWithScalingAndRotationExUn(HMAP hmap, HMESSAGE handle,
                                             const WCHAR* rswName, int sizeNameIn,
                                             WCHAR* rswNameOut, int sizeNameOut,
                                             DOUBLEPOINT *pointmet1, DOUBLEPOINT *pointmetnew1,
                                             DOUBLEPOINT *pointmet2, DOUBLEPOINT *pointmetnew2,
                                             int message);

//==============================================================================
//    Трансформирование растра                                       // 08/02/07
// (вычисление коэффициентов пересчета координат методом наименьших квадратов)
//
//   handle    - диалог визуального сопровождения процесса обработки;
//   map       - карта,содержащая векторные данные;
//   parm      - параметры прикладной задачи;
//   namein    - имя исходного растра (MAX_PATH_LONG)
//   nameout   - имя выходного растра (размер выделенной памяти д.б. не менее MAX_PATH_LONG символов)
//   fact      - исходные координаты опоры;
//   teor      - желаемые координаты опоры;
//   count     - количество опорных точек (не меньше 4-х).
//
//   Диалогу визуального сопровождения процесса обработки посылаются сообщения:
//   -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//      WPARAM - текущее состояние процесса в процентах (0% - 100%)
//      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль,
//==============================================================================
_PICIMP long int _PICAPI RswTransformingBySquareMethod(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm, const char * namein, char * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);

//   sizeNameOut - размер выделенной памяти для nameout в байтах
_PICIMP long int _PICAPI RswTransformingBySquareMethodUn(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm,
                           const WCHAR * namein,
                           WCHAR * nameout, int sizeNameOut,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);


//==============================================================================
//   Трансформирование растра по рамке листа карты                            // 06/06/11
//
//   handle    - диалог визуального сопровождения процесса обработки;
//   map       - карта,содержащая векторные данные;
//   parm      - параметры прикладной задачи;
//   namein    - имя исходного растра;
//   nameout   - имя выходного растра;
//   fact      - исходные координаты опоры;
//   teor      - желаемые координаты опоры;
//   count     - количество опорных точек (не меньше 4-х).
//
//   Диалогу визуального сопровождения процесса обработки посылаются сообщения:
//   -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//      WPARAM - текущее состояние процесса в процентах (0% - 100%)
//      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль,
//==============================================================================
_PICIMP long int _PICAPI RswTransformingByBorderMethod(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm,
                           const char * namein, const char * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);

_PICIMP long int _PICAPI RswTransformingByBorderMethodUn(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm,
                           const WCHAR * namein, const WCHAR * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);

//==============================================================================
//   Трансформирование растра по рамке листа карты     // 21/06/11
//   (нелинейное трансформирование)
//   handle    - диалог визуального сопровождения процесса обработки;
//   map       - карта,содержащая векторные данные;
//   parm      - параметры прикладной задачи;
//   namein    - имя исходного растра;
//   nameout   - имя выходного растра;
//   fact      - исходные координаты опоры;
//   teor      - желаемые координаты опоры;
//   count     - количество опорных точек (не меньше 4-х).
//   flagBorder- 0 - Установить рамку растра по теоретическим координатам (например - по рамке номенклатурного листа)
//               1 - Установить рамку растра по пересчитанным габаритам исходного растра
//               Если исходный растр отображается по рамке, flagBorder игнорируется.
//               Рамка перессчитывается и устанавливается в выходной растр.
//   colorTransparent  - указатель на неотображаемый цвет
//               (если colorTransparent != 0, то в качестве цвета фона используется цвет из colorTransparent.
//                Отображение цвета colorTransparent отключается)
//
//   Диалогу визуального сопровождения процесса обработки посылаются сообщения:
//   -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//      WPARAM - текущее состояние процесса в процентах (0% - 100%)
//      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль,
//==============================================================================
_PICIMP long int _PICAPI RswTransformingByBorderMethodEx(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm,
                           const char * namein, const char * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor,
                           long int flagBorder, COLORREF * colorTransparent);

_PICIMP long int _PICAPI RswTransformingByBorderMethodExUn(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm,
                           const WCHAR * namein, const WCHAR * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor,
                           long int flagBorder, COLORREF * colorTransparent);

//==============================================================================
//   Трансформирование растра по рамке листа карты     // 29/04/13
//   (нелинейное трансформирование)
//   handle    - диалог визуального сопровождения процесса обработки;
//   map       - карта,содержащая векторные данные;
//   parm      - параметры прикладной задачи;
//   namein    - имя исходного растра;
//   nameout   - имя выходного растра;
//   fact      - исходные координаты опоры;
//   teor      - желаемые координаты опоры;
//   count     - количество опорных точек (не меньше 4-х).
//   colorTransparent  - указатель на неотображаемый цвет
//                       (если colorTransparent != 0, то в качестве цвета фона
//                        используется цвет из colorTransparent.
//                        Отображение цвета colorTransparent отключается)
//   flagCutting    - флаг обрезки изображения выходного растра по рамке растра.
//                    Значение флага принимается во внимание при установленной рамке в растр (см. flagBorder)
//   flagDuplicate  - флаг создания уменьшенной копии изображения выходного растра (0/1)
//   flagBorderNew  - 0 - Не устанавливать рамку выходного растра
//                    1 - Установить рамку выходного растра по теоретическим координатам
//                        (например - по объекту <Рамка номенклатурного листа карты>) /
//                    2 - Установить рамку выходного растра по рамке исходного раста.
//                        Если в исходном растре рамка не установлена, то будет установлена
//                        рамка растра по пересчитанным габаритам исходного растра
//                    3 - Установить рамку выходного растра по пересчитанным габаритам исходного растра
//
//   Диалогу визуального сопровождения процесса обработки посылаются сообщения:
//   -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//      WPARAM - текущее состояние процесса в процентах (0% - 100%)
//      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль,
//==============================================================================
_PICIMP long int _PICAPI RswTransformingWithBorderSetting(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm,
                           const char * namein, const char * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor,
                           COLORREF * colorTransparent,
                           long int flagCutting, long int flagDuplicate,
                           long int flagBorderNew);

_PICIMP long int _PICAPI RswTransformingWithBorderSettingUn(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm,
                           const WCHAR * namein, const WCHAR * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor,
                           COLORREF * colorTransparent,
                           long int flagCutting, long int flagDuplicate,
                           long int flagBorderNew);

//================================================================================
// Преобразование растра к заданной проекции                           // 11/05/06
//
//   handle  - диалог визуального сопровождения процесса обработки.
//   namein  - имя исходного растра;
//   nameout - имя выходного растра;
//   mapreg  - адрес структуры с данными о заданной проекции
//             (описание структуры MAPREGISTEREX см в mapcreate.h);
//
//   Диалогу визуального сопровождения процесса обработки посылаются сообщения:
//   -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//      WPARAM - текущее состояние процесса в процентах (0% - 100%)
//      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль,
// код ошибки возвращается функцией picexGetLastError() (коды ошибок см. maperr.rh)
//================================================================================
_PICIMP long int _PICAPI RswProjectionReforming(HMESSAGE handle,
                                               const char * namein,
                                               const char * nameout,
                                               MAPREGISTEREX * mapreg);

_PICIMP long int _PICAPI RswProjectionReformingUn(HMESSAGE handle,
                                               const WCHAR * namein,
                                               const WCHAR * nameout,
                                               MAPREGISTEREX * mapreg);

//================================================================================
// Преобразование растра к заданной проекции
//
//   handle  - диалог визуального сопровождения процесса обработки.
//   namein  - имя исходного растра;
//   nameout - имя выходного растра;
//   mapreg  - адрес структуры с данными о заданной проекции
//             (описание структуры MAPREGISTEREX см в mapcreate.h);
//   datum   - параметры пересчета геодезических координат с заданного эллипсоида
//             на эллипсоид WGS-84 (может быть ноль),
//   ellparam - параметры пользовательского эллипсоида (может быть ноль).
//   ttype    - тип локального преобразования координат (см. TRANSFORMTYPE в mapcreat.h) или 0
//   tparm    - параметры локального преобразования координат (см. mapcreat.h)
//   Диалогу визуального сопровождения процесса обработки посылаются сообщения:
//   -  (WM_PROGRESSBAR) Извещение об изменении состояния процесса
//      WPARAM - текущее состояние процесса в процентах (0% - 100%)
//      Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
// При ошибке возвращает ноль,
// код ошибки возвращается функцией picexGetLastError() (коды ошибок см. maperr.rh)
//================================================================================
_PICIMP long int _PICAPI RswProjectionReformingEx(HMESSAGE handle, const char * namein,
                                                 const char * nameout, MAPREGISTEREX * mapreg,
                                                 DATUMPARAM * datum,
                                                 ELLIPSOIDPARAM* ellparam);

_PICIMP long int _PICAPI RswProjectionReformingExUn(HMESSAGE handle, const WCHAR * namein,   // 19/06/14
                                                 const WCHAR * nameout, MAPREGISTEREX * mapreg,
                                                 DATUMPARAM * datum,
                                                 ELLIPSOIDPARAM* ellparam);

_PICIMP long int _PICAPI RswProjectionReformingPro(HMESSAGE handle, const WCHAR * namein,     // 05/10/16
                                                   const WCHAR * nameout, MAPREGISTEREX * mapreg,
                                                   DATUMPARAM * datum,
                                                   ELLIPSOIDPARAM* ellparam,
                                                   long int ttype,
                                                   LOCALTRANSFORM * tparm);

//================================================================================
// Возвращает код последней ошибки (коды ошибок см. maperr.rh)     // 16/05/06
// В случае отсутствия ошибки возвращает ноль
//================================================================================
_PICIMP long int _PICAPI picexGetLastError();


//================================================================================
// Создать GIF-файл с размещением в памяти
//   palette    - указатель на палитру
//   colorcount - число цветов палитры (от 2 до 256)
//   width      - ширина изображения (от 1 до 65535)
//   height     - высота изображения (от 1 до 65535)
//   in         - указатель на входные данные
//   sizein     - размер входных данных (в байтах)
//   out        - указатель на выходной буфер
//   sizeout    - размер выходного буфера (в байтах)
//                (минимальный размер = sizein + 1000)
// Возвращает размер буфера, содержащего GIF-файл (в байтах)
// При ошибке возвращает 0
//================================================================================
// Входные данные должны содержать 8-битное изображение с нормальным
// расположением строк (сверху-вниз) без байтов выравнивания в строке.
// В качестве входных данных может быть использовано изображение
// карты, полученное при помощи функции mapPaintToImage (mapapi.h)
//================================================================================
_PICIMP long int _PICAPI picexCreateGif(RGBQUAD* palette, int colorcount,
                                       int width, int height,
                                       unsigned char* in, int sizein,
                                       unsigned char* out, int sizeout);

//================================================================================
// Создать GIF-файл с размещением на диске
//   name       - имя GIF-файла
//   palette    - указатель на палитру
//   colorcount - число цветов палитры (от 2 до 256)
//   width      - ширина изображения (от 1 до 65535)
//   height     - высота изображения (от 1 до 65535)
//   in         - указатель на входные данные
//   sizein     - размер входных данных (в байтах)
// Возвращает размер GIF-файла (в байтах)
// При ошибке возвращает 0
//================================================================================
// Входные данные должны содержать 8-битное изображение с нормальным
// расположением строк (сверху-вниз) без байтов выравнивания в строке.
// В качестве входных данных может быть использовано изображение
// карты, полученное при помощи функции mapPaintToImage (mapapi.h)
//================================================================================
_PICIMP long int _PICAPI picexCreateGifFile(const char* name,
                                       RGBQUAD* palette, int colorcount,
                                       int width, int height,
                                       unsigned char* in, int sizein);

_PICIMP long int _PICAPI picexCreateGifFileUn(const WCHAR* name,                 // 19/06/14
                                       RGBQUAD* palette, int colorcount,
                                       int width, int height,
                                       unsigned char* in, int sizein);

//========================================================================
// Загрузка изображения в формате RGBA(для текстуры OpenGL) из BMP-файла
//          c обрезкой (высота и ширина не более 512 и кратны степени 2)
//    Вход: nameBmp - имя исходного Bmp-файла;
//            image - адрес области записи получаемого изображения;
//             size - размер этой области в байтах;
//      reth и retv - высота и ширина полученного изображения;
//        sizeimage - заполняемый данной функцией размер области, необходимой
//                    для записи получаемого изображения.
//    Возвращаемое значение:
//         0 - в случае ошибки (или при нехватке памяти для получаемого
//             изображения см. sizeimage);
//         1 - в случае успешного получения изображения.
//========================================================================
_PICIMP long int _PICAPI LoadBmpToImage32WithCut(const char* bmpname,
                             const char* image, long int size,
                             long int &reth,long int &retw, long int &sizeimage);

_PICIMP long int _PICAPI LoadBmpToImage32WithCutUn(const WCHAR* bmpname,        // 03/02/14
                             const char* image, long int size,
                             long int &reth,long int &retw, long int &sizeimage);

//========================================================================
// Загрузка изображения из памяти в BMP-файл
//    Вход: nameBmp - имя получаемого Bmp-файла;
//            image - адрес области с изображением для записи;
//   width и height - ширина и высота изображения;
//      elementsize - размер элемента изображения (в битах).
//    Возвращаемое значение:
//         0 - в случае ошибки;
//         1 - в случае успешного получения Bmp-файла изображения.
//========================================================================
_PICIMP long int _PICAPI LoadImageToBmp(const char* bmpname, const char* image,
                                       long width, long height, long elementsize);

_PICIMP long int _PICAPI LoadImageToBmpUn(const WCHAR* bmpname, const char* image,    // 03/02/14
                                         long width, long height, long elementsize);


//==============================================================================
// Определить координаты точки фотографирования из файла JPEG
// Координаты
// map     - карта,содержащая векторные данные
// handle  - диалог визуального сопровождения процесса обработки.
// parm    - параметры прикладной задачи
// namein  - имя файла JPEG
// b,l     - координаты точки фотографирования (заполняется функцией)
// height  - высота точки фотографирования (заполняется функцией)
// mapreg  - адрес структуры с данными о заданной проекции (заполняется функцией)
//           (описание структуры MAPREGISTEREX см в mapcreate.h)
// ellipsoid - параметры эллипсоида (заполняется функцией)
// datum   - параметры пересчета геодезических координат с заданного эллипсоида
//           на эллипсоид WGS-84, для координат точки фотографирования (заполняется функцией)
// Возвращает: 1 - в случае успешного определения координат точки фотографирования
//            -1 - структура файла namein не соотвеотсут формату JPEG
//            -2 - в файле namein отсутствует маркер APP1, предназначенный для хранения метаданных
//            -3 - в файле namein найден маркер APP1, но координаты точки фотографирования не обнаружены
//
// При ошибке возвращает ноль
//==============================================================================
_PICIMP long int _PICAPI LoadJpegGpsPoint(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm, const char * namein,
                           SIGNDEGREE* b, SIGNDEGREE* l, double* height,
                           MAPREGISTEREX* mapreg, ELLIPSOIDPARAM *ellipsoid, DATUMPARAM *datum);

_PICIMP long int _PICAPI LoadJpegGpsPointUn(HMAP map,HMESSAGE handle,            // 18/09/14
                           TASKPARMEX * parm, const WCHAR * namein,
                           SIGNDEGREE* b, SIGNDEGREE* l, double* height,
                           MAPREGISTEREX* mapreg, ELLIPSOIDPARAM *ellipsoid, DATUMPARAM *datum);

//==============================================================================
// Определить параметры файла JPEG с тегами EXIF
// map     - карта,содержащая векторные данные
// handle  - диалог визуального сопровождения процесса обработки.
// parm    - параметры прикладной задачи
// namein  - имя файла JPEG
// exifParam-указатель на структуру EXIFPARAM (структура заполняется функцией)
// Возвращает: 1 - в случае успешного определения координат точки фотографирования
//            -1 - структура файла namein не соотвеотсут формату JPEG
//            -2 - в файле namein отсутствует маркер APP1, предназначенный для хранения метаданных
//            -3 - в файле namein найден маркер APP1, но координаты точки фотографирования не обнаружены
//
// При ошибке возвращает ноль
//==============================================================================
_PICIMP long int _PICAPI LoadJpegExifParameters(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm, const char * namein,
                           EXIFPARAM* exifParam);

_PICIMP long int _PICAPI LoadJpegExifParametersUn(HMAP map,HMESSAGE handle,      // 18/09/14
                           TASKPARMEX * parm, const WCHAR * namein,
                           EXIFPARAM* exifParam);

//========================================================================  06/05/12
// Запросить разрешение изображения из файлов форматов TIFF(GeoTIFF), BMP, PCX, JPEG
// name - имя файла (*.tif;*.bmp;*.pcx;*.jpg)
// precisionByWidth  - указатель на разрешение по горизонтали (заполняется функцией)
// precisionByHeight - указатель на разрешение по вертикали (заполняется функцией)
// значение разрешения заносится в выходные параметры precisionByWidth и
//                     precisionByHeight в точках на дюйм
// flagMessage       - флаг выдачи сообщений MessageBox программой
// Функция возвращает следующие значения:
//   1 - разрешение изображения определено и записано в выходные параметры precisionByWidth и precisionByHeight
//  -1 - разрешение изображения в файле обнаружить не удалось
// При ошибке возвращает 0
//========================================================================
_PICIMP long int _PICAPI picexGetPrecisionFromImageFile (const char * name,
                                                        double* precisionByWidth,
                                                        double* precisionByHeight,
                                                        int flagMessage);

_PICIMP long int _PICAPI picexGetPrecisionFromImageFileUn(const WCHAR * name,   
                                                        double* precisionByWidth,
                                                        double* precisionByHeight,
                                                        int flagMessage);

//========================================================================
// Запросить параметры растра (матрицы) - координаты габаритов изображения,
// размеры пикселя, код EPSG
// fileName        - имя файла (RSW, MTW, MTL, MTQ, BMP, TIFF, IMG, PNG, GIF)
// points          - указатель на массив из 4-х точек (заполняется функцией
//                   координатами габаритов изображения в радианах WGS-84)
// countPoint      - количество элементов массива, размещенного по адресу points
//                   (параметр должен быть равен 4)
// meterInElementX - указатель для записи значения размера элемента по X
//                   При обнаружении данных в исходном графическом файле, или в
//                   файле привязки растрового изображения функция заполняет поле
// meterInElementY - указатель для записи значения размера элемента по Y
//                   При обнаружении данных в исходном графическом файле, или в
//                   файле привязки растрового изображения функция заполняет поле
// codeEPSG        - указатель для записи значения кода EPSG
//
//    При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI picexGetImageInfoByNameUn(const WCHAR * fileName,
                               DOUBLEPOINT* points, long int countPoint,
                               double* meterInElementX, double* meterInElementY,
                               long int * codeEPSG);

//========================================================================
// Запросить данные о проекции растра (матрицы)
// fileName        - имя файла (RSW, MTW, MTL, MTQ, BMP, TIFF, IMG, PNG, GIF)
// mapregister - адрес структуры MAPREGISTEREX.
// Структурa MAPREGISTEREX описанa в mapcreat.h
// ellipsoidparam - адрес структуры, в которой будут размещены
// параметры эллипсоида
// Структурa ELLIPSOIDPARAM описанa в mapcreat.h
// datumparam - адрес структуры, в которой будут размещены
// коэффициенты трансформирования геодезических координат
// Структурa DATUMPARAM описанa в mapcreat.h
//
//    При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI picexGetImageProjectionDataByNameUn(const WCHAR * fileName,
                                                 MAPREGISTEREX* mapregister,
                                                 ELLIPSOIDPARAM *ellipsoidparam,
                                                 DATUMPARAM *datumparam);

//========================================================================
// Функция создает обзорное изображение растра(RSW, TIFF, JPEG, IMG, PNG, GIF, BMP, PCX)
// и матрицы(MTW, MTL, MTQ)  и записывает его в файл форматов (RSW, TIFF, JPEG, BMP, PNG).
// Глубина обзорного изображения - 24 бит на пиксель.
// handle - диалог визуального сопровождения процесса обработки
// inputFileName   - имя входного файла
// outputFileName  - имя выходного файла обзорного изображения
// width и height  - размеры обзорного изображения
// messageEnable   - флаг выдачи сообщений MessageBox программой
// При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI picexPaintDataToFile(HMESSAGE handle,
                                              const char * inputFileName,
                                              const char * outputFileName,
                                              int width, int height,
                                              int messageEnable);

_PICIMP long int _PICAPI picexPaintDataToFileUn(HMESSAGE handle,
                                              const WCHAR * inputFileName,
                                              const WCHAR * outputFileName,
                                              int width, int height,
                                              int messageEnable);

//========================================================================
// Импорт растровых данных в файл RSW
// handle - диалог визуального сопровождения процесса обработки
// srcname        - имя входного файла (TIF, IMG, PNG, GIF, JPG, BMP, PCX)
// rstname        - имя выходного файла (*.rsw)
// retcode        - код возврата
// Приоритет изъятия параметров привязки:
//   1. Содержимое соответствующих тегов файлов TIF, IMG
//   2. Файл привязки world.file
//   3. Файл привязки TAB (MapInfo)
// Функция ищет файл привязки рядом с исходным файлом srcname,
// перебирая по приоритету типы файлов.
// При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI picexLoadRasterToRswUn(HMESSAGE handle,
                                                const WCHAR* srcname,
                                                const WCHAR* rstname,
                                                long int * retcode);

//========================================================================
// Подобрать имя файла привязки по содержимому папки графического файла
// Сформировать имя файла параметров в зависимости от формата графического файла
// и типа файла привязки
// type              - тип файла привязки
// Значения параметра type:
//        1 - файл привязки world file
//        2 - TAB (MapInfo)
//        3 - MAP (OziExplorer)
//        4 - INI            - устаревший формат
//        5 - tpf (FOTOPLAN) - устаревший формат
//        6 - pln (TALKA)    - устаревший формат
// graphicName       - имя графического файла
// locationFilesName - указатель для размещения сформированного имени файла привязки
// size              - размер памяти в байтах строки locationFilesName (не менее MAX_PATH_LONG)
//========================================================================
_PICIMP long int _PICAPI picexMakeLocationFileName(long int type,
                                                const WCHAR *graphicName,
                                                WCHAR *locationFilesName, int size);

//========================================================================
// Запросить информацию о графическом файле
//========================================================================
_PICIMP long int _PICAPI picexGetFileInformationUn(const WCHAR* inputName,
                                                DATAINFORMATION* information);

//========================================================================
// Чтение и Анализ файла привязки World File
// inputName  - имя графического файла
// rstIniName - имя файла привязки World File
//
// locationPoint   - приаязка растра
// meterInElementX - размер элемента по X
// meterInElementY - размер элемента по Y
//
// rasterPoint - Левый Нижний, Левый Верхний, Правый Верхний, Правый Нижний
// countPoint  - 4

// rasterPointTr - LT,RT,RB,LB;  массив заполняется, если flagTransformation == 1
// countPointTr  - 4,
// flagTransformation - флаг трансформирования по координатам rasterPointTr
//
// flagWorldFile_CoordinateInGradus - флаг записи координат в градусах
// retCode - код возрата ошибки
//========================================================================
_PICIMP long int _PICAPI picexReadWorldFile(const WCHAR *inputName,
                                                 const WCHAR *rstIniName,
                                                 DOUBLEPOINT* locationPoint,
                                                 double* meterInElementX,
                                                 double* meterInElementY,
                                                 DOUBLEPOINT* rasterPoint,
                                                 long int countPoint,
                                                 LOCATIONPOINT* rasterPointTr,
                                                 long int countPointTr,
                                                 long int* flagTransformation,
                                                 long int* flagWorldFile_CoordinateInGradus,
                                                 long int* retCode);

//========================================================================
// Чтение и Анализ файла настройки *.tab (MapInfo)
// inputName         - имя графического файла
// rstIniName        - имя файла привязки *.tab
// mapreg            - параметры системы координат и проекции
// datum             - параметры пересчета с эллипсоида рабочей системы координат
//                     к WGS-84
// ellipsoid         - параметры пользовательского эллипсоида для рабочей
//                     системы координат
// flagMapRegisterEx - флаг заполнения параметров проекции из файла TAB
// locationPoint     - привязка растра
// meterInElementX   - размер элемента по X
// meterInElementY   - размер элемента по Y
//
// rasterPoint - Левый Нижний, Левый Верхний, Правый Верхний, Правый Нижний
// countPoint  - 4
//
// rasterPointTr - LT,RT,RB,LB;  массив заполняется, если flagTransformation == 1
// countPointTr  - 4,
// flagTransformation - флаг трансформирования по координатам rasterPointTr
//
// retCode - код возрата ошибки
//========================================================================
_PICIMP long int _PICAPI picexReadTabFile(const WCHAR *inputName,
                                          const WCHAR *rstIniName,
                                          MAPREGISTEREX* mapreg,
                                          ELLIPSOIDPARAM* ellipsoid,
                                          DATUMPARAM* datum,
                                          long int* flagMapRegisterEx,
                                          DOUBLEPOINT* locationPoint,
                                          double* meterInElementX,
                                          double* meterInElementY,
                                          DOUBLEPOINT* rasterPoint,
                                          long int countPoint,
                                          LOCATIONPOINT *rasterPointTr,
                                          long int countPointTr,
                                          long int* flagTransformation,
                                          long int* retCode);

//========================================================================
//  Определить координаты точки по коэффициентам мирового файла
//  double A_coeff = 0;   // масштаб растра по оси X; размер пиксела по оси X (например в 1 единице растра - 20 метров)
//  double B_coeff = 0;   // масштаб растра по оси Y; отрицательный размер пиксела по оси Y
//  double C_coeff = 0;   // параметры поворота (обычно равны нулю)
//  double D_coeff = 0;   // параметры поворота (обычно равны нулю)
//  double E_coeff = 0;   // параметры сдвига; X,Y координаты центра верхнего левого пиксела
//  double F_coeff = 0;   // параметры сдвига; X,Y координаты центра верхнего левого пиксела
// x1 = Ax + Сy + E
// y1 = Dx + By + F
// x,y - исходные файловые координаты растра (x - колонка, y - ряд).
// http://gis-lab.info/qa/tfw.html
//========================================================================
_PICIMP long int _PICAPI picexGetWorldCoordinate(double a_coeff,
                                                  double b_coeff,
                                                  double c_coeff,
                                                  double d_coeff,
                                                  double e_coeff,
                                                  double f_coeff,
                                                  int x,
                                                  int y,
                                                  double *xMet,
                                                  double *yMet);


//-----------------------------------------------------------------------------
// Определить СК по набору символов формата MapInfo из файла TAB
// stringIn      - строка c набором символов формата MapInfo из файла TAB (входной параметр )
//                 CoordSys Earth Projection 8, 104, "m", 21, 0, 0.9996, 500000, 0
//                 Вторая половина строки из файла TAB - 8, 104, 7, 21, 0, 0.9996, 500000, 0
// stringOut     - строка, для размещения описания проекции (выходной параметр )
// sizeStringOut - размер строки stringOut в байтах
// mapregOut     - структура для заполнения параметрами проекции (выходной параметр )
// ellipsoidOut  - структура для заполнения параметрами эллипсоида
// datumOut      - структура для заполнения коэффициентами трансформирования геодезических координат
// codeEPSG      - код EPSG
// retCode       - код возврата
//                           1 - выходные структуры заполнены
//                           0 - выходные структуры не заполнены
// При ошибке функция возвращает 0
//-----------------------------------------------------------------------------

_PICIMP long int _PICAPI picexCheckMapInfoProjection(const char* stringIn,
                                                  char* stringOut, int sizeStringOut,
                                                  MAPREGISTEREX* mapregOut,
                                                  int* numberProjOut,
                                                  long int* retCode);

_PICIMP long int _PICAPI picexCheckMapInfoProjectionEx(const char* stringIn,
                                                  char* stringOut, long int sizeStringOut,
                                                  MAPREGISTEREX* mapregOut,
                                                  ELLIPSOIDPARAM *ellipsoidOut,
                                                  DATUMPARAM *datumOut,
                                                  long int* codeEPSG,
                                                  long int* retCode);


///////////////////////////////////////////////////////////////////////
///////////////////////    GDAL             ///////////////////////////
///////////////////////////////////////////////////////////////////////

//========================================================================
// Начать работу с Gdal
//========================================================================
_PICIMP long int _PICAPI picexInitGdal();

//========================================================================
// Закончить работу с Gdal
//========================================================================
_PICIMP long int _PICAPI picexCloseGdal();

//========================================================================
//    Запросить параметры СК из файла средствами GDAL
//    name - имя файла (*.img;*.png;*.gif...)
//    geoTIFFparam - указатель заполняемой структуры
//========================================================================
_PICIMP long int _PICAPI picexLoadGdalGeoParametersUn(HMESSAGE handle,
                                                  const WCHAR  * name,
                                                  GEOTIFFPARAM * geoTIFFparam);

//========================================================================
// запросить параметры растрового изображения посредством библиотеки GDAL
// fileName     - имя файла графических форматов (IMG, PNG, GIF)
// information -  указатель на структуру DATAINFORMATION
//                для записи параметров графического файла
// Структура DATAINFORMATION описана в picexprm.h
//
// Функцию рекомендуется вызывать перед началом
// конвертации графического файла в Rsw для инициализации диалога сопровождения
// При ошибке возвращает 0
//========================================================================
_PICIMP long int _PICAPI picexLoadGdalInformationUn(HMESSAGE handle,
                                                  const WCHAR  * fileName,
                                                  DATAINFORMATION * information,
                                                  GEOTIFFINFORMATION* geoInformation);

_PICIMP long int _PICAPI picexGetGdalFileInformationUn(HMESSAGE handle,                // 26/07/16
                                                  const WCHAR * inputname,
                                                  DATAINFORMATION * iformation,
                                                  GEOTIFFINFORMATION* geoInformation);

//========================================================================
// Заполнить структуры MAPREGISTEREX, ELLIPSOIDPARAM, DATUMPARAM, GEOTIFFPARAM по данным
// гепространственной информации посредством библиотеки GDAL
// flagGeoSupported - результат работы функции TTranslate.SetProjection по проверке
//                    установленных параметров проекции
// flag_CoordInDegre- Координаты привязки в градусах ? (0-метры, 1-градусы)
// При ошибке возвращает 0
//========================================================================
_PICIMP long int _PICAPI picexFillMapRegisterExByGdalExUn(HMESSAGE handle,
                                                  const WCHAR  * fileName,
                                                  MAPREGISTEREX *mapreg,
                                                  ELLIPSOIDPARAM *ellipsoid,
                                                  DATUMPARAM *datum,
                                                  long int* flagGeoSupported,
                                                  long int* flag_CoordInDegre,
                                                  GEOTIFFPARAM * geoTIFFparam);

_PICIMP long int _PICAPI picexFillMapRegisterExByGdalUn(HMESSAGE handle,
                                                  const WCHAR  * fileName,
                                                  MAPREGISTEREX *mapreg,
                                                  ELLIPSOIDPARAM *ellipsoid,
                                                  DATUMPARAM *datum,
                                                  long int* flagGeoSupported,
                                                  long int* flag_CoordInDegre);

//========================================================================
// Загрузка растровых данных посредством библиотеки GDAL
// обрабатываются файлы графических форматов (IMG, PNG, GIF)
//    Map - карта,содержащая векторные данные
//    inputname - имя загружаемого файла
//    rstname   - имя RST-файла
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point     - точка привязки растра (в метрах)
//                (положение юго-западного угла растра в районе)
//    Handle - диалог визуального сопровождения процесса обработки.
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//    flagMessage - флаг выдачи сообщений
//                          (при ==1, сообщение выдает MessageBox;
//                           при == 0, посылается сообщение диалогу WM_ERROR)
//    flagWorkLog - флаг ведения журнала
//                          (при ==1, выполняется ведения журнала
//                           при == 0, не выполняется ведения журнала)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadGdalFileToRswAndCompressExUn(HMESSAGE handle,
                                                 TASKPARM* parm,
                                                 const WCHAR* inputname,
                                                 const WCHAR* rstname,
                                                 double* meterInPixelX,
                                                 double* meterInPixelY,
                                                 DOUBLEPOINT *point,
                                                 long int compression,
                                                 long int compressJpegQuality,
                                                 long int flagMessage,
                                                 long int flagWorkLog,
                                                 long int flagIgnoreGeoTiff,
                                                 long int flagCreateDuplicate);

_PICIMP long int _PICAPI picexLoadGdalFileToRswUn(HMESSAGE handle, TASKPARM* parm,
                                                  const WCHAR  * inputname,
                                                  const WCHAR  * rstname,
                                                  double* meterInPixelX,
                                                  double* meterInPixelY,
                                                  DOUBLEPOINT *point,
                                                  long int compression,
                                                  long int flagMessage,
                                                  long int flagWorkLog);

_PICIMP long int _PICAPI picexLoadGdalFileToRswExUn(HMESSAGE handle, TASKPARM* parm,
                                                  const WCHAR  * inputname,
                                                  const WCHAR  * rstname,
                                                  double* meterInPixelX,
                                                  double* meterInPixelY,
                                                  DOUBLEPOINT *point,
                                                  long int compression,
                                                  long int flagMessage,
                                                  long int flagWorkLog,
                                                  long int flagIgnoreGeoTiff);

_PICIMP long int _PICAPI picexLoadGdalFileToRswAndCompressUn(HMESSAGE handle,
                                                  TASKPARM* parm,
                                                  const WCHAR* inputname,
                                                  const WCHAR* rstname,
                                                  double* meterInPixelX,
                                                  double* meterInPixelY,
                                                  DOUBLEPOINT *point,
                                                  long int compression,
                                                  long int compressJpegQuality,
                                                  long int flagMessage,
                                                  long int flagWorkLog,
                                                  long int flagIgnoreGeoTiff);

//========================================================================
// Загрузка однобитных растровых данных посредством библиотеки GDAL в однобитный RSW
// обрабатываются файлы графических форматов (TIFF, IMG, PNG, GIF)
// GDAL описывает такие файлы как одноканальные, 8 бит на канал
//    handle      - дескриптор диалога визуального сопровождения процесса обработки.
//    parm        - указатель на структуру TASKPARM
//    inputname   - имя загружаемого однобитного файла
//    rstname     - имя однобитного файла RSW
//    meterInElementX - размер в метрах элемента по X
//    meterInElementY - размер в метрах элемента по Y
//    point       - точка привязки растра (в метрах)
//                  (положение юго-западного угла растра в районе)
//    palette     - палитра растра
//    paletteCount- количество цветов в палитре (для однобитного файла RSW д.б. 2)
//    compression - флаг использования сжатия при формировании RST-файла (0/1)
//                  0 - сжатие к блокам изображения применяться не будет
//                  1 - блоки д.б. сжаты по методу LZW
//                  метод JPEG недоступен
//    flagMessage - флаг выдачи сообщений
//                  (при ==1, сообщение выдает MessageBox;
//                   при == 0, посылается сообщение диалогу WM_ERROR)
//    flagWorkLog - флаг ведения журнала
//                  (при ==1, выполняется ведения журнала
//                   при == 0, не выполняется ведения журнала)
//    flagIgnoreGeoTiff - (0/1)
//                  (0 - привязка и СК устанавливаются в выходной растр
//                   1 - привязка и СК не устанавливаются в выходной растр)
//    При ошибке возвращает ноль
//
//    Диалогу визуального сопровождения процесса обработки посылаются
//    сообщения:
//    -  (WM_PROGRESSBAR) Извещение об изменении состония процесса
//       WPARAM - текущее состоние процесса в процентах (0% - 100%)
//       Если функция-отклик возвращает WM_PROGRESSBAR, то процесс завершается.
//
//    -  (WM_ERROR) Извещение об ошибке
//       LPARAM - указатель на структуру ERRORINFORMATION
//       Структура ERRORINFORMATION описана в picexprm.h,
//       WM_PROGRESSBAR и WM_ERROR - в maptype.h
//========================================================================
_PICIMP long int _PICAPI picexLoadGdalOneBitFileToOneBitRswUn(HMESSAGE handle,
                                            const WCHAR  * inputname, const WCHAR  * rstname,
                                            double* meterInPixelX, double* meterInPixelY,
                                            DOUBLEPOINT *point,
                                            COLORREF* palette, long int paletteCount,
                                            long int compression,
                                            long int flagMessage,
                                            long int flagWorkLog,
                                            long int flagIgnoreGeoTiff);


//========================================================================
// Загрузка изображения в формате RGBA(для текстуры OpenGL) из PNG-файла
//          c обрезкой (высота и ширина должны быть степенью 2)
//    Вход: namePng - имя исходного PNG-файла
//            image - адрес области записи получаемого изображения;
//             size - размер этой области в байтах;
//      reth и retv - высота и ширина полученного изображения;
//        sizeimage - заполняемый данной функцией размер области, необходимой
//                    для записи получаемого изображения;
//    Возвращаемое значение:
//         0 - в случае ошибки (или при нехватке памяти для получаемого
//             изображения см. sizeimage);
//         1 - в случае успешного получения изображения.
//========================================================================
_PICIMP long int WINAPI LoadPngToImage32WithCut(const char* namePng,
                                            const char* image, long int size,
                                            long int *reth,long int *retw,
                                            long int *sizeimage);

_PICIMP long int WINAPI LoadPngToImage32WithCutUn(const WCHAR* namePng,
                                            const char* image, long int size,
                                            long int *reth,long int *retw,
                                            long int *sizeimage);

//========================================================================
// Функция создает файл RSW (всегда 24 б/п) по изображению
// входного графического файла
// Функция создана для обеспечения функционирования окна "PreView" программы "Банк данных ЦК"
// Привязка и параметры проекции переносятся в выходной растр.
// Размеры изображения выходного файла(ширина и высота) необходимо указать
// в параметрах width и height
// На вход функции могут подаваться файлы следующих форматов:
//    BMP (*.bmp), TIFF (*.tif), JPEG (*.jpg), Jpeg2000 (*.jp2), MrSID (*.sid),
//    NITF (*.ntf), Imagine (*.img), PNG (*.png), GIF (*.gif)
//
// Описание работы функции:
// Функция пытается создать "внешнее" обзорное изображение средствами GDAL с
// установленными в аргументах (width, height) параметрами картинки.
// Если в исходном файле уже существует обзорное изображение, то GDAL может не
// позволить создать "внешнее" обзорное изображение. В таком случае, подбирается
// ближайшее обзорное изображение из исходного файла (критерий подбора -
// параметрамы width, height) и сохраняется в файл RSW.
// "Внешнее" обзорное изображение создается средствами GDAL в файл *.ovr.
//
// Описание входных параметров функции:
// handle - диалог визуального сопровождения процесса обработки
// inputFileName   - имя входного файла
// outputFileName  - имя выходного файла (*.rsw)
// width           - ширина в пикселях изображения выходного файла
// height          - высота в пикселях изображения выходного файла
// messageEnable   - флаг выдчи сообщений MessageBox
// Возвращает: 1 - в случае успешного создания выходного файла
// При ошибке возвращает ноль
//========================================================================
_PICIMP long int _PICAPI picexPaintImageDataToRswUn(HMESSAGE handle,
                                            const WCHAR * inputname,
                                            const WCHAR * rstname,
                                            long int width, long int height,
                                            long int flagMessage);

//========================================================================
// Сохранение файла в JPEG
// Функция сохраняет содержимое файла filenameSource в JPEG-файл filenameOutput
// handle         - диалог визуального сопровождения процесса
// filenameSource - имя исходного файла (BMP, TIFF)
// filenameOutput - имя выходного файла JPEG
// quality        - коэффициент качества изображения, сжатого по методу JPEG
//========================================================================
_PICIMP long int _PICAPI picexCreateCopyJpegUn(HMESSAGE handle,
                                            const WCHAR *filenameSource,
                                            const WCHAR *filenameOutput,
                                            int quality);

//-----------------------------------------------------------------------------
// Сохранение файла в PNG
// Функция сохраняет содержимое файла filenameSource в PNG-файл filenameOutput
// handle         - диалог визуального сопровождения процесса
// filenameSource - имя исходного файла (BMP, TIFF)
// filenameOutput - имя выходного файла PNG
//-----------------------------------------------------------------------------
_PICIMP long int _PICAPI picexCreateCopyPngUn(HMESSAGE handle,
                                            const WCHAR *filenameSource,
                                            const WCHAR *filenameOutput);

//========================================================================
// Сохранить изображение 24-х битного растра RSW в файл PNG                     
// Handle              - диалог визуального сопровождения процесса обработки.
// rswName             - имя файла 24-х битного растра RSW
// pngName             - имя файла PNG
//========================================================================
_PICIMP long int _PICAPI picexSaveRswToPngUn(HMESSAGE handle,
                                             const WCHAR* rswName,
                                             const WCHAR* pngName);                                                           

//-----------------------------------------------------------------------------
// Функция "Загрузка матриц из формата IMG"
// hmap         - дескриптор открытого документа
// handle       - диалог визуального сопровождения процесса
// inputnameW   - имя исходного файла IMG
// outputnameW  - имя выходного файла MTW
// scale        - знаменатель масштаба создаваемой матрицы
// flagCompress - флаг сжатия данных матрицы высот
//-----------------------------------------------------------------------------
_PICIMP long int _PICAPI picexLoadIMGToMtwUn(HMAP hmap, HMESSAGE handle,
                                            const WCHAR* inputnameW,
                                            const WCHAR* outputnameW,
                                            double scale, long int flagCompress);


}       // extern "C"


#endif  // MAPPICEX_H


