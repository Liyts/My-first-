/****** PASPAPI.H ************** Беленков О.В. ******** 29/09/16 ***
******* PASPAPI.H ************** Shishkova L.A. ******* 02/12/13 ***
******* PASPAPI.H ************** Tarakanova I.R. ****** 28/09/16 ***
******* PASPAPI.H ************** Konon V.N.      ****** 10/03/11 ***
******* PASPAPI.H ************** Kruzhkov A.E.   ****** 18/04/16 ***
******* PASPAPI.H ************** Shabakov D.A.   ****** 29/07/16 ***
******* PASPAPI.H ************** Derevyagina Zh.A.***** 06/10/16 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                           FOR WINDOWS                            *
*                                                                  *
********************************************************************
*                                                                  *
*            ОПИСАНИЕ ФУНКЦИЙ РАБОТЫ С ПАСПОРТОМ КАРТЫ             *
*                                                                  *
* СТАНДАРТНЫЕ ДИАЛОГИ ГИС КАРТА 2011 ДЛЯ ПРИЛОЖЕНИЙ НА GIS ToolKit *
*                                                                  *
*                 ПРИМЕР ВЫЗОВА ДИАЛОГА:                           *
*                                                                  *
*   // Загрузка библиотеки                                         *
*   HINSTANCE libInst = ::LoadLibrary("gispasp.dll");              *
*                                                                  *
*   // Вызов функции                                               *
*   typedef long int (WINAPI * CREATEPLAN)(char * mapname,         *
*                                          int size,               *
*                                          TASKPARMEX* parm);      *
*                                                                  *
*   CREATEPLAN pcreateplan = (CREATEPLAN)                          *
*                   GetProcAddress(libInst, "paspCreatePlan");     *
*                                                                  *
*   long int rezult = (*pcreateplan)(mapname, size, parm);         *
*                                                                  *
*   // Выгрузка библиотеки                                         *
*   ::FreeLibrary(libInst);                                        *
*                                                                  *
*******************************************************************/

#if !defined(PASPAPI_H)
#define PASPAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifdef LINUXAPI                            // 08/10/15
  #define _PASPAPI
  #define _PASPIMP
#else
  #define _PASPAPI  WINAPI
  #if defined(PASP_DLL)
    #define _PASPIMP __declspec(dllexport)
  #else
    #ifdef VECTOR_DLL     // 06/10/16
      #define _PASPIMP
    #else
      #define _PASPIMP __declspec(dllimport)
  #endif
#endif
#endif

typedef struct REFERENCESYSTEM
{
  char NameSystem[512];
  char Comment[512];
  char Ident[64];
  long int CodeEpsg;
}
REFERENCESYSTEM;

typedef struct REFERENCESYSTEMUN               // 01/04/14
{
  WCHAR NameSystem[512];
  WCHAR Comment[512];
  WCHAR Ident[64];
  int CodeEpsg;
  int Reserve;
}
REFERENCESYSTEMUN;


// Сведения об организации-производителе набора данных
typedef struct ORGANIZATION
{
  char Name[256];                // Название организации
  char Phone[32];                // Телефон
  char Facsimile[32];            // Факс
  char City[32];                 // Населенный пункт
  char Adminarea[32];            // Административный район
  char Postalcode[32];           // Почтовый индекс
  char Country[32];              // Страна
  char Email[64];                // Электронная почта
  char Reserve[256];
}
ORGANIZATION;


// Сведения о сотруднике, который выполнил загрузку набора данных и ввод метаданных
typedef struct AGENT
{
  char Fio[256];                 // Фамилия  имя  отчество
  char NameOrg[256];             // Название организации 
  char Phone[32];                // Телефон
  char Facsimile[32];            // Факс
  char Email[64];                // Электронная почта
}
AGENT;

// Сведения о сотруднике, который выполнил загрузку набора данных и ввод метаданных
typedef struct AGENTEX           // 31/07/15
{
  WCHAR Fio[256];                 // Фамилия  имя  отчество
  WCHAR NameOrg[256];             // Название организации
  WCHAR Position[256];            // Должность
  WCHAR Phone[32];                // Телефон
  WCHAR Facsimile[32];            // Факс
  WCHAR Email[64];                // Электронная почта
  WCHAR Reserve[256];
}
AGENTEX;

// Сведения об организации-производителе набора данных
typedef struct ORGANIZATIONEX
{
  WCHAR Name[256];                // Название организации
  WCHAR Phone[32];                // Телефон
  WCHAR Facsimile[32];            // Факс
  WCHAR City[32];                 // Населенный пункт
  WCHAR Adminarea[32];            // Административный район
  WCHAR Postalcode[32];           // Почтовый индекс
  WCHAR Country[32];              // Страна
  WCHAR Email[64];                // Электронная почта
  WCHAR Reserve[256];
}
ORGANIZATIONEX;

// Метаданные матриц и растров
typedef struct RMF_METADATA
{
  double  Totalsize;              // Общий размер данных в Kбайтах (запросить функцией mapGetDataSize(...))
  WCHAR   Ident[64];              // Идентификатор набора в формате GUID
  WCHAR   WestLongitude[32];      // Долгота Юго-Западного угла габаритов в градусах WGS-84
  WCHAR   EastLongitude[32];      // Широта Юго-Западного угла габаритов в градусах WGS-84
  WCHAR   SouthLatitude[32];      // Долгота Северо-Восточного угла габаритов в градусах WGS-84
  WCHAR   NorthLatitude[32];      // Широта Северо-Восточного угла габаритов в градусах WGS-84

  WCHAR   Scale[32];              // Число метров в одном пикселе (растры)
                                  // Число метров в одном элементе матрицы
  WCHAR   Nomenclature[256];      // Условное название матрицы
  WCHAR   Createdate[32];         // Дата создания/обновления матриц (растров) - YYYY-MM-DD
  WCHAR   Format[16];             // Идентификатор формата файлов (MTW, RSW ...)
  WCHAR   Filename[1024];         // Ссылка на основной файл данных   (noginsk.mtw)
  WCHAR   Comment[256];           // Комментарий, краткое описание
  WCHAR   Lineage[512];           // Общие сведения об исходных данных, по которым создана карта или план, и о технологии их обработки
  WCHAR   Areadate[16];           // Год состояния местности

  WCHAR   Security[128];           // Гриф секретности (справочник)
  WCHAR   Datatype[128];           // Тип данных - космический оптический снимок, аэрофотоснимок, мультиспектральный снимок (101-106)
                                   // Тип данных - регулярная матрица высот, TIN-модель, MTD-модель (облако точек) (201-203)
  // Для данных ДЗЗ

  WCHAR   SatName[64];            // Название или условное обозначение аппарата
  WCHAR   CloudState[32];         // Процент снимка, закрытый облачностью
  WCHAR   SunAngle[32];           // Азимут солнца (градусы)
  WCHAR   ScanAngle[32];          // Угол съемки (градусы)

  int     Epsgcode;               // Код EPSG системы координат карты
  WCHAR   Reserve[252];
}
  RMF_METADATA;

extern "C"
{ 
// --------------------------------------------------------------
// Диалог создания карты
// hmap     - идентификатор открытой карты
// mapname  - указатель на строку, содержащую имя карты (файла паспорта)
//            После вызова функции значение строки может измениться!
// size     - длина строки, содержащей имя карты (не меньше 260)
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик CREATE_MAP
// При ошибке возвращает ноль
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspCreateMap(HMAP hmap, char *mapname, long int size,
                                         TASKPARMEX * parm);

_PASPIMP long int _PASPAPI paspCreateMapUn(HMAP hmap,WCHAR *mapname, long int size,
                                           TASKPARMEX * parm);

// --------------------------------------------------------------
// Диалог создания карты
// hmap     - идентификатор открытой карты
// mapname  - указатель на строку, содержащую имя карты (файла паспорта)
//            После вызова функции значение строки может измениться
// size     - длина строки, содержащей имя карты
// parm     - структура параметров для диалога (см. maptype.h)
// password - пароль доступа к данным из которого формируется 256-битный код
//            для шифрования данных (при утрате данные не восстанавливаются)
// sizepassw - длина пароля в байтах !!!
// Help вызывается из mappasp.chm, топик CREATE_MAP
// При ошибке возвращает ноль
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspCreateMapPro(HMAP hmap, WCHAR *mapname, long int size,
                                            TASKPARMEX * parm,
                                            WCHAR * password, long int sizepassw);

// --------------------------------------------------------------
// Диалог создания крупномасштабного плана
// mapname  - указатель на строку, содержащую имя карты (файла паспорта)
//            После вызова функции значение строки может измениться
// size     - длина строки, содержащей имя карты
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик CREATE_PLAN
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspCreatePlan(char* mapname,long int size,
                                       TASKPARMEX* parm);

// 18/03/13
_PASPIMP long int _PASPAPI paspCreatePlanUn(WCHAR* mapname,long int size,
                                         TASKPARMEX* parm);

// --------------------------------------------------------------
// Диалог создания пользовательской карты по открытой карте
// hmap     - идентификатор открытой карты
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик CREATE_SITE
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspCreateSite(HMAP hmap, TASKPARMEX * parm);

// --------------------------------------------------------------
// Диалог просмотра и редактирования паспорта
// hmap     - идентификатор открытой карты
// hsite    - пользовательская карта
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик PASP_EDID
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspViewPasp(HMAP hmap, HSITE hsite,
                                     TASKPARMEX * parm);

// --------------------------------------------------------------
// Диалог для изменения параметров местной системы координат
// Устанавливает параметры МСК для документа (HMAP),
// которые затем могут использоваться при пересчетах координат
// в функциях mapPlaneToWorkSystemPlane, mapWorkSystemPlaneToGeo и т.п.
// hmap       - идентификатор открытой карты (документа),
// taskparmex - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик MCK_PARAM
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspSetWorkSystemParameters(HMAP hmap,
                                                    TASKPARMEX* taskparmex);


// --------------------------------------------------------------
// Отображение и установка текущих параметров проекции документа
// для отображения, печати и расчета координат
// Устанавливать общие параметры проекции можно для документа
// поддерживающего пересчет геодезических координат (mapIsGeoSupported() != 0)
// После установки общих параметров проекции изображение карты формируется
// в заданной проекции. Векторные карты, имеющие другие параметры
// проекции, трансформируются в процессе отображения.
// Все операции с координатами (mapPlaneToGeo, mapGeoToPlane,
// mapPlaneToGeoWGS84, mapAppendPointPlane, mapInsertPointPlane,
// mapUpdatePointPlane, mapAppendPointGeo и другие) выполняются
// в системе координат документа, определяемой общими параметрами проекции
// При чтении\записи координат в конкретной карте выполняется пересчет
// из системы координат документа
// hmap       - идентификатор открытой карты (документа),
// taskparmex - структура параметров для диалога (см. maptype.h)
// Новые параметры устанавливаются функцией mapSetDocProjection(...)(см. mapapi.h)
// Help вызывается из mappasp.chm, топик DOCPROJECTION
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspSetCurrentProjectionParameters(HMAP hmap,
                                                           TASKPARMEX* taskparm);


// --------------------------------------------------------------
// Установить/Отобразить параметры проекции
// hmap - идентификатор открытых данных (или 0)
// Структуры MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// описаны в mapcreat.h
// Структура TASKPARMEX описана в maptype.h
// const char* title - заголовок диалога
// Исходные значения параметров проекции заданы в
// MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// iswrite           - флаг допустимости редактирования параметров проекции
//                     (0 - не редактировать / 1 - редактировать)
// Выход: установленные MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// При изменении значений параметров возвращает 1
// При отсутствии изменений и при ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspSetProjectionParameters(HMAP hmap,           // 02/12/13
                                                    MAPREGISTEREX* mapregisterex,
                                                    DATUMPARAM*    datum,
                                                    ELLIPSOIDPARAM* spheroidparam,
                                                    TASKPARMEX* parm,
                                                    const char* title,
                                                    long int iswrite);


// --------------------------------------------------------------
// Установить/Отобразить параметры проекции
// hmap - идентификатор открытых данных (или 0)
// Структуры MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// описаны в mapcreat.h
// Структура TASKPARMEX описана в maptype.h
// title             - заголовок диалога в кодировке UNICODE
// Исходные значения параметров проекции заданы в
// MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// ttype   -  тип преобразования координат (см. TRANSFORMTYPE в mapcreat.h) или 0
// Структура LOCALTRANSFORM  описана в mapcreat.h
// iswrite           - флаг допустимости редактирования параметров проекции
//                     (0 - не редактировать / 1 - редактировать)       // 16/05/11
// Выход: установленные MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// При изменении значений параметров возвращает 1
// При отсутствии изменений и при ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspSetProjectionParametersPro(HMAP hmap,         // 28/09/16
                                                      MAPREGISTEREX* mapregisterex,
                                                      DATUMPARAM*    datum,
                                                      ELLIPSOIDPARAM* spheroidparam,
                                                      long int * ttype,
                                                      LOCALTRANSFORM * tparm,
                                                      TASKPARMEX* parm,const WCHAR * title,
                                                      long int iswrite);

_PASPIMP long int _PASPAPI paspSetProjectionParametersUn(HMAP hmap,         // 02/12/13
                                                      MAPREGISTEREX* mapregisterex,
                                                      DATUMPARAM*    datum,
                                                      ELLIPSOIDPARAM* spheroidparam,
                                                      TASKPARMEX* parm,const WCHAR * title,
                                                      long int iswrite);

// --------------------------------------------------------------
// Чтение XML-файла
// hmap - идентификатор открытых данных (при создании карты - hmap = 0)
// Структура REFERENCESYSTEMUN описана в paspapi.h
// Структуры MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM  описаны в mapcreat.h
// ttype   -  тип преобразования координат (см. TRANSFORMTYPE в mapcreat.h) или 0
// Структура LOCALTRANSFORM  описана в mapcreat.h
// Структура TASKPARMEX описана в maptype.h
// regime  -  режимы работы с паспортом (создание, редактирование)
// Help вызывается из mappasp.chm, топик PARAMETERSXML
// При ошибке возвращает ноль
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspReadFileXMLPro(HMAP hmap,                     // 21/09/16
                                       REFERENCESYSTEMUN * referencesystem,
                                       MAPREGISTEREX* mapregisterex,
                                       DATUMPARAM*    datum,
                                       ELLIPSOIDPARAM* ellipsoidparam,
                                       long int * ttype,
                                       LOCALTRANSFORM * tparm,
                                       TASKPARMEX* parm, long int regime);


_PASPIMP long int _PASPAPI paspReadFileXML(HMAP hmap,
                                        MAPREGISTEREX* mapregisterex,
                                        DATUMPARAM*    datum,
                                        ELLIPSOIDPARAM* spheroidparam,
                                        TASKPARMEX* parm, long int regime);

_PASPIMP long int _PASPAPI paspReadFileXMLEx(HMAP hmap,
                                        REFERENCESYSTEM * referencesystem,
                                        MAPREGISTEREX* mapregisterex,
                                        DATUMPARAM*    datum,
                                        ELLIPSOIDPARAM* spheroidparam,
                                        TASKPARMEX* parm, long int regime);

_PASPIMP long int _PASPAPI paspReadFileXMLUn(HMAP hmap,
                                        REFERENCESYSTEMUN * referencesystem,
                                        MAPREGISTEREX* mapregisterex,
                                        DATUMPARAM*    datum,
                                        ELLIPSOIDPARAM* spheroidparam,
                                        TASKPARMEX* parm, long int regime);


// --------------------------------------------------------------
// Чтение параметров из базы данных EPSG                         // 28/03/11
// hmap - идентификатор открытых данных (при создании карты - hmap = 0)
// Структуры MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// описаны в mapcreat.h
// Структура TASKPARMEX описана в maptype.h
// в epsgcode возвращается код EPSG
// Файлы базы данных EPSG.CSG, EPSG.CSP, EPSG.CSU должны находиться 
// в каталоге приложения 
// При ошибке возвращает ноль
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspReadEPSG(HMAP hmap,
                                     MAPREGISTEREX* mapregisterex,
                                     DATUMPARAM*    datum,
                                     ELLIPSOIDPARAM* ellipsoidparam,
                                     TASKPARMEX* parm,
                                     long int *epsgcode);

// --------------------------------------------------------------
// Чтение параметров из базы данных EPSG                         // 26/12/12
// hmap - идентификатор открытых данных (при создании карты - hmap = 0)
// Структуры MAPREGISTEREX, DATUMPARAM, ELLIPSOIDPARAM
// описаны в mapcreat.h
// Структура TASKPARMEX описана в maptype.h
// в epsgcode возвращается код EPSG
// Файлы базы данных EPSG.CSG, EPSG.CSP, EPSG.CSU должны находиться
// в каталоге приложения
// namesystem - строка длиной не менее 64 символов для размещения
// названия системы координат (идентификатора)
// size  - длина строки
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspReadEPSGEx(HMAP hmap,
                                       MAPREGISTEREX* mapregisterex,
                                       DATUMPARAM*    datum,
                                       ELLIPSOIDPARAM* ellipsoidparam,
                                       TASKPARMEX* parm,
                                       long int *epsgcode,
                                       char * namesystem,
                                       long int size);

// 18/03/13
_PASPIMP long int _PASPAPI paspReadEPSGExUn(HMAP hmap,
                                         MAPREGISTEREX* mapregisterex,
                                         DATUMPARAM*    datum,
                                         ELLIPSOIDPARAM* ellipsoidparam,
                                         TASKPARMEX* parm,
                                         long int *epsgcode,
                                         WCHAR * namesystem,
                                         long int size);


// --------------------------------------------------------------
// Создание и редактирование файла метаданных в формате XML              // 15/11/12
// filename - имя файла метаданных (0, если формировать для всех листов и всех карт)
// hmap - идентификатор открытых данных
// Структура TASKPARMEX описана в maptype.h
// regime - режимы работы с файлом метаданных (0 - создание,1- редактирование)
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspWriteXMLMD(char *filename,HMAP hmap,
                                          TASKPARMEX* parm, long int regime);

_PASPIMP long int _PASPAPI paspWriteXMLMDUn(WCHAR *filename,HMAP hmap,
                                            TASKPARMEX* parm, long int regime);
// --------------------------------------------------------------
// Просмотр и редактирование файла метаданных
// filename - имя файла метаданных
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI paspEditXMLMD(char *filename,TASKPARMEX * parm);

_PASPIMP long int _PASPAPI paspEditXMLMDUn(WCHAR *filename,TASKPARMEX * parm);


// 15/01/13
// --------------------------------------------------------------
// Создание xml файла метаданных для одного листа (без вызова диалога)
// filename - имя файла метаданных
// Структуры MAPREGISTEREX, LISTREGISTER  описаны в mapcreat.h
// Структуры ORGAHIZATION, AGENT  описаны в paspapi.h
// rscname - имя файла классификатора (без пути)
// comment - комментарий, содержит краткое описание набора данных (до 256 символов)
// lineage - общие сведения об исходных данных и технологии их обработки (до 512 символов)
// security - гриф секретности:  1 - открытая информация
//                               2 - информация с ограниченным доступом
//                               3 - информация для служебного пользования
//                               4 - секретная информация
//                               5 - совершенно секретная информация
// codeepsg - код EPSG
// Обязательные для заполнения параметры: filename, mapreg, listreg
// При ошибке возвращает ноль
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspSaveMetaData(char *filename,
                                         MAPREGISTEREX * mapreg,
                                         LISTREGISTER * listreg,
                                         ORGANIZATION * organization,
                                         AGENT * agent,
                                         char * rscname,
                                         char * comment,
                                         char * lineage,
                                         long int security,
                                         long int codeepsg);

// 18/03/13                                         
_PASPIMP long int _PASPAPI paspSaveMetaDataUn(WCHAR *filename,
                                           MAPREGISTEREX * mapreg,
                                           LISTREGISTER * listreg,
                                           ORGANIZATION * organization,
                                           AGENT * agent,
                                           WCHAR * rscname,
                                           WCHAR * comment,
                                           WCHAR * lineage,
                                           long int security,
                                           long int codeepsg);

// 31/07/15
// --------------------------------------------------------------
// Создание и редактирование файла метаданных матриц и растров в формате XML
// filename - имя файла метаданных (или 0)
// hmap - идентификатор открытых данных
// Структура TASKPARMEX описана в maptype.h
// datatype тип файла (растры, матрицы)
// (см. maptype.h : FILE_RSW, FILE_MTW)
// При ошибке возвращает ноль
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspMetaDataMtwRsw(WCHAR *filename,
                                           HMAP hmap,
                                           TASKPARMEX * parm,
                                           long int datatype,
                                           long int chainnumber);

// 07/10/15
// --------------------------------------------------------------
// Создание файла метаданных матриц и растров в формате XML
// filename - имя файла метаданных
// Структуры RMF_METADATA, ORGANIZATIONEX, AGENTEX описаны в paspapi.h
// datatype тип файла (растры, матрицы)
// (см. maptype.h : FILE_RSW, FILE_MTW)
// При ошибке возвращает ноль
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspSaveMetaDataRmf(WCHAR *filename,
                                            RMF_METADATA * metadata,
                                            ORGANIZATIONEX * organization,
                                            AGENTEX * agent,
                                            long int datatype);

// --------------------------------------------------------------
// Запросить метаданные для матриц и растров
// filename - имя файла метаданных
// Структуры RMF_METADATA, ORGANIZATIONEX, AGENTEX описаны в paspapi.h
// Структуры ORGANIZATIONEX, AGENTEX  необязательны для заполнения
// datatype тип файла (растры, матрицы)
// (см. maptype.h : FILE_RSW, FILE_MTW)
// При ошибке возвращает ноль
// --------------------------------------------------------------
_PASPIMP long int _PASPAPI paspGetMetaDataRmf(WCHAR *filename,
                                           HMAP hmap,
                                           TASKPARMEX * parm,
                                           RMF_METADATA * metadata,
                                           ORGANIZATIONEX * organization,
                                           AGENTEX * agent,
                                           long int datatype); 

                                           
// ================================================================
//
//                      УСТАРЕВШИЕ ФУНКЦИИ                         // 01/06/10
//
//              Реализованы через вызов новых функций
// ================================================================


// --------------------------------------------------------------
// Редактирование паспорта
// hmap     - идентификатор открытой карты,
// mapname  - указатель на строку длиной 260 символов,
//            содержащую имя карты (файла паспорта)
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик PASP_EDID
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspEdit(HMAP hmap, char *mapname, TASKPARM * parm);

// --------------------------------------------------------------
// Просмотр паспорта карты
// hmap     - идентификатор открытой карты,
// taskparm - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик PASP_EDID
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI mapPaspShow(HMAP hmap,TASKPARMEX* taskparm);    // 13/01/10

// --------------------------------------------------------------
// Создание плана
// mapname  - указатель на строку длиной 260 символов,
//            содержащую имя карты (файла паспорта)
//            После вызова функции значение строки может измениться
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик CREATE_PLAN
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspPlan(char *mapname, TASKPARM * parm);


// --------------------------------------------------------------
// Создание обстановки и добавление пользовательской карты
// в документ с запросом имени файла
// hmap     - идентификатор открытой карты,
// mapname  - указатель на строку длиной 260 символов,
//            содержащую имя карты (файла паспорта)
//            После вызова функции значение строки может измениться
// path     - директория в которой будет предложено создать файл
//            (пользователь может выбрать другую)
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик CREATE_MAP
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspSitDoc(HMAP hmap, char *mapname, char * path,
                                     TASKPARM * parm);

// --------------------------------------------------------------
// Создание обстановки и добавление пользовательской карты
// в документ без запроса имени файла
// hmap     - идентификатор открытой карты,
// mapname  - указатель на строку длиной 260 символов,
//            содержащую имя карты (файла паспорта)
//            После вызова функции значение строки может измениться
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик CREATE_MAP
// При ошибке возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspSitDocByName(HMAP hmap, char *mapname,  // 18/04/16
                                            TASKPARM * parm);

_PASPIMP long int _PASPAPI MapPaspSitDocByNameUn(HMAP hmap, WCHAR *mapname,  // 18/04/16
                                            TASKPARM * parm);
// --------------------------------------------------------------
// Создание пользовательской карты
// mapname  - указатель на строку длиной 260 символов,
//            содержащую имя карты (файла паспорта)
//            После вызова функции значение строки может измениться
// rscname  - имя файла классификатора (Rsc)
// areaname - имя района
// parm     - структура параметров для диалога (см. maptype.h)
// Help вызывается из mappasp.chm, топик CREATE_MAP
// При ошибке или отказе от ввода возвращает ноль
// --------------------------------------------------------------

_PASPIMP long int _PASPAPI MapPaspSitCreate(char * mapname, char *rscname,
                                        char * areaname, TASKPARM * parm);

_PASPIMP long int _PASPAPI MapPaspSitCreateUn(WCHAR *mapname, WCHAR *rscname,      // 01/04/14
                                           WCHAR *areaname, TASKPARM * parm);

}

#endif

