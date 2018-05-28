/****  PICEXTRS.H    **********  Gustinovich N.A.*****  23/04/03 ***
*****  PICEXTRS.H    **********  Shabakov D.A.   *****  22/06/14 ***
*****  PICEXTRS.H    **********  Kruzhkov A.E.   *****  27/06/14 ***
*****  PICEXTRS.H    **********  Derevyagina Zh.A*****  02/12/14 ***
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
#if !defined(PICEXTRS_H)
#define PICEXTRS_H

#ifndef MACPICEX_H
  #include "macpicex.h"
#endif

#ifndef PICEXPRM_H
  #include "picexprm.h"  // 27/06/14  требуется для сборки shptomap.dll
#endif  


#define WM_RSTROTATE        0x500       // Поворот растра
#define RSTTRANS_DIAL       0x501       // вызов диалога трансф-я растра
#define RSTTRANS_NEWPARM    0x502       // обновление параметров вых.растра
#define RSTTRANS_END        0x503       // завершение задачи

#ifdef WIN32API                  // 18/06/02
   #define HMESSAGE HWND
#else
   #define HMESSAGE MSGHANDLER
#endif


extern "C"
{
#if defined(_M_X64) || defined(BUILD_DLL64)       // 31/05/13
 typedef __int64   HTFCR;    // ИДЕНТИФИКАТОР ПРОЦЕССА СОЗДАНИЯ TIFF
#else
 typedef long int  HTFCR;    // ИДЕНТИФИКАТОР ПРОЦЕССА СОЗДАНИЯ TIFF
#endif

 // *********************************************************
 // Схема запуска ПРОЦЕССА СОЗДАНИЯ TIFF:
 // =============
 // HTFCR hTiffCreate = picexCreateTiffFile(handle,tiffname,
 //                               width, height,
 //                               nbits,
 //                               palette, colorcount,
 //                               precision,
 //                               flagCompress,
 //                               platform,
 //                               flagCMYK};
 // if (hTiffCreate)
 //    {
 //     long int stripCount         = picexGetTiffStripCount(hTiffCreate);
 //     long int stringCountByStrip = picexGetTiffstringCountByStrip(hTiffCreate);
 //     for (int i = 0; i < stripCount, i++)
 //        {
 //         if (picexPutTiffStrip(hTiffCreate, numberStrip,
 //                              bits, sizeBits) == 0)
 //            break;
 //        }
 //     picexSaveTiffFile(hTiffCreate);
 //     picexFreeTFCRProcess(hTiffCreate);
 //    }
 // **********************************************************


 //    Сохранить графические данные в файле формата TIFF  (Конструктор)
 //    handle     - диалог визуального сопровождения процесса обработки.
 //    tiffname   - имя TIFF-файла;
 //    width      - ширина изображения в пикселях
 //    height     - высота изображения в пикселях
 //    nbits      - размер пикселя (бит на пиксель)
 //    palette    - адрес устанавливаемой палитры
 //                 если palette == 0, а colorcount != 0, то возможно установить
 //                 палитру позже функцией Load_SetTiffPalette()
 //    colorcount - число элементов в новой палитре
 //    precision  - разрешение изображения (точек на метр)
 //    platform - Тип платформы (0 - INTEL, 1 - MOTOROLA)             (рекомендуемое значение - 0)
 //    compressMethod - Флаг сжатия изображения (0- не применять сжатие, 1 - сжатие PackBit) (рекомендуемое значение - 0)
 //    flagCMYK - выбор цветовой модели:
 //                     0 - цветовая модель RGB 24 бит на пиксел
 //                     1 - цветовая модель CMYK 32 бит на пиксел
 //                     Режим поддерживается только для  растров 24,32 бит на пиксел.
 //    flagIntergraphTIFF - Флаг записи матрицы трансформирования для однобитного TIFF для использования в Intergraph // 28/09/05
 //                     Режим поддерживается только для  растров 1 бит на пиксел.
 //    dframe           - габариты изображения в районе в метрах для записи матрицы трансформирования для однобитного TIFF  // 28/09/05
 //                     Режим поддерживается только для  растров 1 бит на пиксел.
 //    Возвращает ИДЕНТИФИКАТОР ПРОЦЕССА СОЗДАНИЯ TIFF
 //    При ошибке возвращает 0
 //    Диалогу визуального сопровождения процесса обработки посылаются
 //    сообщения:
 //    -  (WM_ERROR) Извещение об ошибке
 //       LPARAM - указатель на структуру ERRORINFORMATION
 //       Структура ERRORINFORMATION описана в picexprm.h, WM_ERROR - в maptype.h
HTFCR _MAPAPI picexCreateTiffFile(HMESSAGE handle,                                        // 02/12/14
                                          const char * tiffname,
                                          long int width, long int height,
                                          long int nbits,
                                          COLORREF* palette, long int colorcount,
                                          double precision,
                                          long int compressMethod,
                                          long int platform,
                                          int flagCMYK);

HTFCR _MAPAPI picexCreateTiffFileUn(HMESSAGE handle,
                                          const WCHAR * tiffname,
                                          long int width, long int height,
                                          long int nbits,
                                          COLORREF* palette, long int colorcount,
                                          double precision,
                                          long int compressMethod,
                                          long int platform,
                                          int flagCMYK);

 // flagSetRegister - Флаг установки проекции исходного материала // 12/10/07
 // mapReg          - параметры проекции // 12/10/07
HTFCR _MAPAPI picexCreateTiffFileEx(HMESSAGE handle,
                                          const char * tiffname,
                                          long int width, long int height,
                                          long int nbits,
                                          COLORREF* palette, long int colorcount,
                                          double precision,
                                          long int compressMethod,
                                          long int platform,
                                          long int flagCMYK,
                                          long int flagIntergraphTIFF,
                                          DFRAME * dframe,
                                          long int flagSetRegister,     // Флаг установки проекции исходного материала
                                          MAPREGISTEREX *mapReg);       // параметры проекции

HTFCR _MAPAPI picexCreateTiffFileExUn(HMESSAGE handle,                  // 17/06/14
                                          const WCHAR * tiffname,
                                          long int width, long int height,
                                          long int nbits,
                                          COLORREF* palette, long int colorcount,
                                          double precision,
                                          long int compressMethod,
                                          long int platform,
                                          long int flagCMYK,
                                          long int flagIntergraphTIFF,
                                          DFRAME * dframe,
                                          long int flagSetRegister,     // Флаг установки проекции исходного материала
                                          MAPREGISTEREX *mapReg);       // параметры проекции


 //    Сохранить графические данные в файле формата TIFF GrayScale (структура GrayScale для Н.К. Добр.) // 09/03/07
 //    Цветовая модель - GrayScale, 8 бит на пиксел
 //    tiffname - имя TIFF-файла;
 //    width      - ширина изображения в пикселях
 //    height     - высота изображения в пикселях
 //    nbits      - размер пикселя (бит на пиксель)
 //    precision  - разрешение изображения (точек на метр)
 // flagSetRegister - Флаг установки привязки изображения и проекции исходного материала // 12/10/07
 //    dframe     - привязка изображения в районе в метрах      // 17/10/07
 //    mapReg     - параметры проекции // 12/10/07
 //    Возвращает ИДЕНТИФИКАТОР ПРОЦЕССА СОЗДАНИЯ TIFF
 //    При ошибке возвращает 0
HTFCR _MAPAPI picexCreateTiffGrayScale(HMESSAGE handle, const char * tiffname,
                                          long int width, long int height,
                                          long int nbits,
                                          double precision,
                                          long int flagSetRegister,
                                          DFRAME * dframe,
                                          MAPREGISTEREX *mapReg);

HTFCR _MAPAPI picexCreateTiffGrayScaleUn(HMESSAGE handle, const WCHAR * tiffname,   // 18/06/14
                                          long int width, long int height,
                                          long int nbits,
                                          double precision,
                                          long int flagSetRegister,
                                          DFRAME * dframe,
                                          MAPREGISTEREX *mapReg);

 //    Запросить количество стрипов (полос изображения)
 //    При ошибке возвращает 0
long int _MAPAPI picexGetTiffStripCount(HTFCR hTiffCreate);

 //    Запросить количество строк изображения в стрипе
 //    При ошибке возвращает 0
long int _MAPAPI picexGetTiffStringCountByStrip(HTFCR hTiffCreate);

 //    Записать стрип с номером numberStrip в файл
 //    Все стрипы имеют одинаковый размер, за исключением последнего
 //    Нумерация и запись стрипов сверху-вниз
 //    Если flagCompress == 1, стрип записывается сжатым по методу PackBit
 //    При ошибке возвращает 0
long int _MAPAPI picexPutTiffStrip(HTFCR hTiffCreate, long int numberStrip,
                                           char*bits, long int sizeBits);

 //    Записать стрип с номером numberStrip в файл   // 06/02/04
 //    Цветовая модель изображения - CMYK(flagCMYK = 1),  32 бит на пиксел (nbits = 32)
 //    Цвета хранятся последовательно(не по плоскостям).
 //    Все стрипы имеют одинаковый размер, за исключением последнего
 //    Нумерация и запись стрипов сверху-вниз
 //    Если flagCompress == 1, стрип записывается сжатым по методу PackBit
 //    numberStrip - начиная с нуля
 //    При ошибке возвращает 0
long int _MAPAPI picexPutTiffStrip_CMYK(HTFCR hTiffCreate, long int numberStrip,
                                                 char*bitsCMYK, long int sizeBitsCMYK);

 // Записать палитру в файл
 // Для изображений с 4 и 8 бит на пиксел
 //    При ошибке возвращает 0
long int _MAPAPI picexSetTiffPalette(HTFCR hTiffCreate, COLORREF* palette,
                                                             long int colorCount);

 // Записать заголовок и измененные тэги в файл
 // При ошибке возвращает 0
long int _MAPAPI picexSaveTiffFile(HTFCR hTiffCreate);


 // Освобождение памяти (Деструктор)
 // При ошибке возвращает 0
long int _MAPAPI picexFreeTFCRProcess(HTFCR hTiffCreate);

 // Определение размеров изображения с учетом рамки растра  // 10/07/03
 // rect - по адресу rect записываются габариты рамки растра в элементах растра
 // При ошибке возвращает ноль
long int _MAPAPI picexSizeImageDefinition(HMAP hMap, long int rstNumber, RECT* rect);


//---------------------------------------------------------------------------
// Вывести состав Тэгов TIFF-файла в текстовый файл *.tls
// handle   - диалог визуального сопровождения процесса обработки.
// TifName  - имя TIF-файла;
// FileName - имя файла *.tls;
//---------------------------------------------------------------------------
long int _MAPAPI picexSaveTiffTagsIntoFile(HMESSAGE Handle,
                                                  const char * TiffName,
                                                  const char * FileName);

long int _MAPAPI picexSaveTiffTagsIntoFileUn(HMESSAGE Handle,            // 18/06/14
                                                  const WCHAR * TiffName,
                                                  const WCHAR * FileName);

//---------------------------------------------------------------------------
// Вывести информацию о параметрах СК файла GeoTiff в текстовый файл
//---------------------------------------------------------------------------
// handle   - диалог визуального сопровождения процесса обработки.
// TifName  - имя TIF-файла;
// FileName - имя файла *.tls;
long int _MAPAPI picexSaveGeoTiffParamInFile(HMESSAGE Handle,
                                                    const char * TiffName,
                                                    const char * FileName);

long int _MAPAPI picexSaveGeoTiffParamInFileUn(HMESSAGE Handle,          // 18/06/14
                                                    const WCHAR * TiffName,
                                                    const WCHAR * FileName);

//---------------------------------------------------------------------------
// Заполнить структуры MAPREGISTEREX, ELLIPSOIDPARAM, DATUMPARAM по данным
// гепространственной информации из структуры GEOTIFFPARAM
// flagGeoSupported - результат работы функции TTranslate.SetProjection по прверке
// установленных параметров проекции
// При ошибке возвращает 0
//---------------------------------------------------------------------------
long int _MAPAPI picexFillMapRegisterExByStructure(GEOTIFFPARAM* geoParam,
                                                           MAPREGISTEREX *mapreg,
                                                           ELLIPSOIDPARAM *ellipsoid,
                                                           DATUMPARAM *datum,
                                                           int* flagGeoSupported);


//==============================================================================
// Создает файл RSW (TIF,BMP,JPG) (всегда 24 б/п) по изображению входного файла
// Размеры изображения выходного файла(ширина и высота) необходимо указать в параметрах width и height
// На вход функции могут подаваться файлы RSW, MTW, MTQ, MTL, TIFF
// handle - диалог визуального сопровождения процесса обработки
// inputFileName   - имя входного файла (*.rsw,*.mtw, TIF)
// outputFileName  - имя выходного файла (*.rsw)
// width           - ширина в пикселях изображения выходного файла (*.rsw)
// height          - высота в пикселях изображения выходного файла (*.rsw)
// messageEnable   - фла выдчи сообщений MessageBox
// Возвращает: 1 - в случае успешного создания выходного файла (*.rsw)
// При ошибке возвращает ноль
//==============================================================================
long int _MAPAPI PaintDataToRsw(HMESSAGE handle,
                                       const char * inputFileName,
                                       const char * outputFileName,
                                       int width, int height, int messageEnable);

long int _MAPAPI PaintDataToRswUn(HMESSAGE handle,
                                       const WCHAR * inputFileName,
                                       const WCHAR * outputFileName,
                                       int width, int height, int messageEnable);

//========================================================================
//    Сохранить несколько растров в один   
//    Map - карта,содержащая векторные данные;
//    BmpName - имя BMP-файла;
//    Handle - диалог визуального сопровождения процесса обработки.
//========================================================================
#ifdef LINUXAPI
long int _MAPAPI LoadRastersToOne(HMAP Map,HMESSAGE Handle,
                                 DFRAME * dframe, long BitCount,
                                 long Scale, long Resolution,
                                 const char* name);

long int _MAPAPI LoadRastersToOneUn(HMAP Map,HMESSAGE Handle,
                                 DFRAME * dframe, long BitCount,
                                 long Scale, long Resolution,
                                 const WCHAR* name);

#endif

}       // extern "C"


#endif  // PICEXTRS_H
