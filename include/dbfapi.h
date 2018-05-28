/****** DBFAPI.CPP ************* Belenkov O.V.   ****** 28/01/15 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2015              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*             ОПИСАНИЕ ИНТЕРФЕЙСА ДОСТУПА К ФАЙЛУ DBF              *
*                                                                  *
*******************************************************************/

#ifndef DBFAPI_H
#define DBFAPI_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

typedef HANDLE HDBFC;

extern "C"
{

// Открыть таблицу 
// table - имя таблицы (полный путь к файлу DBF)
// mode  - режим открытия 
//  0 : открыть на чтение/запись, 
//      если не выйдет - только чтение;
//  1 : только чтение (рекомендуется!);
//  2 : только чтение/запись.
// При ошибке возвращает ноль, иначе - идентификатор открытой
// таблицы базы данных. Открытая таблица обязательно должна быть
// закрыта в конце работы вызовом функции dbCloseTable

_MAPIMP HDBFC _MAPAPI dbOpenTable(const char * table, long int mode);
_MAPIMP HDBFC _MAPAPI dbOpenTableUn(const WCHAR * table, long int mode = 1);

// Закрыть таблицу
// hdbf  - идентификатор открытой таблицы

_MAPIMP void _MAPAPI dbCloseTable(HDBFC hdbf);

// Cчитать данные в виде integer по имени поля
// hdbf     - идентификатор открытой таблицы
// name     - имя поля
// value    - значение поля
// При ошибке возвращает ноль

_MAPIMP long int _MAPAPI dbGetValueAsInt(HDBFC hdbf, const char * name, long int * value);
_MAPIMP long int _MAPAPI dbGetValueAsIntUn(HDBFC hdbf, const WCHAR * name, long int * value);

// Cчитать данные в виде double по имени поля
// hdbf     - идентификатор открытой таблицы
// name     - имя поля
// value    - значение поля
// При ошибке возвращает ноль

_MAPIMP long int _MAPAPI dbGetValueAsDouble(HDBFC hdbf, const char * name, double * value);
_MAPIMP long int _MAPAPI dbGetValueAsDoubleUn(HDBFC hdbf, const WCHAR * name, double * value);

// Считать данные в виде символьной строки в кодировке ANSI по имени поля 
// hdbf     - идентификатор открытой таблицы
// name     - имя поля
// value    - значение поля
// size     - длина строки
// При ошибке возвращает ноль

_MAPIMP long int _MAPAPI dbGetValueAsChar(HDBFC hdbf, const char * name, char * value, int size);

// Считать данные в виде символьной строки в кодировке UTF-16 по имени поля 
// hdbf     - идентификатор открытой таблицы
// name     - имя поля
// value    - значение поля
// size     - длина строки
// При ошибке возвращает ноль

_MAPIMP long int _MAPAPI dbGetValueAsCharUn(HDBFC hdbf, const WCHAR * name, WCHAR * value, int size);

// Получить количество полей в записи
// hdbf     - идентификатор открытой таблицы
// При ошибке возвращает ноль 

_MAPIMP long int _MAPAPI dbGetFieldCount(HDBFC hdbf);

// Получить количество записей
// hdbf     - идентификатор открытой таблицы
// При ошибке возвращает ноль 

_MAPIMP long int _MAPAPI dbGetRecordCount(HDBFC hdbf);

// Запросить название и тип поля
// hdbf     - идентификатор открытой таблицы
// number   - номер поля в таблице c 1
// name     - имя поля
// size     - длина строки
// Возвращает тип поля: 'N'- числовое, 'C'- символьное... (см. DBFFIELDTYPE)
// При ошибке возвращает ноль 

_MAPIMP long int _MAPAPI dbGetNameAndTypeByNumber(HDBFC hdbf, int number, char * name, int size);
_MAPIMP long int _MAPAPI dbGetNameAndTypeByNumberUn(HDBFC hdbf, int number, WCHAR * name, int size);

// Запросить число знаков после запятой для поля типа DBFFIXED = 'N'
// hdbf     - идентификатор открытой таблицы
// number   - номер поля в таблице c 1
// При ошибке возвращает ноль 

_MAPIMP long int _MAPAPI dbGetPresicionByNumber(HDBFC hdbf, int number);

// Перейти на первую запись таблицы
// hdbf     - идентификатор открытой таблицы
// При ошибке возвращает ноль 

_MAPIMP long int _MAPAPI dbGotoFirst(HDBFC hdbf);

// Перейти на следующую запись таблицы
// hdbf     - идентификатор открытой таблицы
// При ошибке возвращает ноль 

_MAPIMP long int _MAPAPI dbGotoNext(HDBFC hdbf);

// Запись значения в текущую запись по имени поля
// hdbf    - идентификатор открытой таблицы
// name    - имя поля,
// value   - значение
// При ошибке возвращает ноль

_MAPIMP long int _MAPAPI dbPutValue(HDBFC hdbf, const char* name, const char* value);
_MAPIMP long int _MAPAPI dbPutValueUn(HDBFC hdbf, const WCHAR* name, const WCHAR* value);

// Сохранить все изменения в файл (переоткрыть таблицу)
// hdbf     - идентификатор открытой таблицы
// При ошибке возвращает ноль

_MAPIMP long int _MAPAPI dbReopenTable(HDBFC hdbf);

} // extern "C"

#endif // DBFAPI_H