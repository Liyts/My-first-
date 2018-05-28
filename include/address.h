/***** ADDRESS.H ***********  Korolev A.A.  ***************** 12/02/15 ****
****** ADDRESS.H ***********  Shevchenko A.A.  ************** 08/12/14 ****
****** ADDRESS.H ***********  Shabakov D.A. ***************** 15/09/16 ****
*                                                                         *
*                   Copyright (c) PANORAMA Group 1991-2016                *
*                          All Rights Reserved                            *
*                                                                         *
***************************************************************************
*                                                                         *
*                             АДРЕСНЫЙ ЛОКАТОР                            *
*                                                                         *
***************************************************************************
*                                                                         *
*                    Импортирование функций В Windows :                   *
*                                                                         *
* // Загрузка библиотеки                                                  *
* HINSTANCE libInst = ::LoadLibrary("address.dll");                       *
*                                                                         *
* // Вызов функции                                                        *
* HADDRESS (WINAPI * lpfn_addressCreate)(const WCHAR * connectionstring); *
* (FARPROC)lpfn_addressCreate = GetProcAddress(libInst, "addressCreate"); *
* HADDRESS address = (*lpfn_addressCreate)("<строка соединения>");        *
*                                                                         *
* // Выгрузка библиотеки                                                  *
* ::FreeLibrary(libInst);                                                 *
*                                                                         *
**************************************************************************/


#ifndef ADDRESS_H
#define ADDRESS_H

#define _ADRAPI WINAPI                                // 15/09/16
#ifdef COMPILE_DLL
  #define _ADRIMP  extern "C" __declspec(dllexport)
#else
  #define _ADRIMP  extern "C" __declspec(dllimport)
#endif

#define HADDRESS HANDLE
#define CM_ADDR_DLG_SHOW  2089
#define CM_ADDR_DLG_CLOSE 2090
#define CM_ADDR_DLG_MOVE  2091

#define chars_for_record 512                     // количество символов, приходящихся на одну запись из адресного локатора
#define common_chars 64                          // постоянное количество символов, приходящееся на набор записей из адресного локатора
#define minout (chars_for_record+common_chars)   // минимальное количество символов, для которых требуется выделение памяти,
                                                 // при использовании addressGetAddressByStr, addressGetAddressByHumanStr
                                                 // и addressGetAddressDlg
#define MaxINForGetAddressByHumanStr 2048        // Максимальная длина входной строки для GetAddressByHumanStr (в символах)
#define MaxINForGetAddressByStr 32768            // Максимальная длина входной строки для GetAddressByStr (в символах)

typedef struct TSTRUCT_ADDRESS
{
  WCHAR OKATO[32];                       // код ОКАТО
  WCHAR KLADR[32];                       // код КЛАДР
  WCHAR POSTINDEX[16];                   // почтовый индекс
  WCHAR REGION[256];                     // регион
  WCHAR RCODE[32];                       // код региона
  WCHAR DISTRICT[256];                   // район/городской округ
  WCHAR DTYPE[32];                       // тип района/городского округа
  WCHAR CITY[256];                       // наименование населённого пункта/поселения
  WCHAR CTYPE[32];                       // тип населённого пункта/поселения
  WCHAR UDNAME[256];                     // городской район
  WCHAR UDTYPE[32];                      // тип городского района
  WCHAR SVILLAGE[256];                   // наименование сельсовета
  WCHAR SVTYPE[32];                      // тип сельсовета
  WCHAR NP[256];                         // населённый пункт
  WCHAR NPTYPE[256];                     // тип населённого пункта
  WCHAR STREET[256];                     // наименование улицы
  WCHAR STYPE[32];                       // тип улицы
  WCHAR HTYPE[32];                       // тип дома
  WCHAR HOUSE[256];                      // дом
  WCHAR PTYPE[32];                       // тип корпуса
  WCHAR PART[256];                       // корпус
  WCHAR BLDNGTYPE[32];                   // тип строения
  WCHAR BUILDING[256];                   // строение
  WCHAR FLATTYPE[32];                    // тип квартиры
  WCHAR FLAT[256];                       // квартира
  WCHAR OTHERDESC[4096];                 // иное описание местоположения
  WCHAR UNFORMADDR[4096];                // неформализованное описание адреса(местоположения)
}
TSTRUCT_ADDRESS, *PSTRUCT_ADDRESS;

typedef WCHAR TGEOCODINGREQUEST[4096];
typedef TGEOCODINGREQUEST* PGEOCODINGREQUEST;

typedef struct TGEOCODINGRESPONSE
{
  WCHAR B[32];                               // B
  WCHAR L[32];                               // L
  WCHAR A[4096];                             // Адрес
}
TGEOCODINGRESPONSE, *PGEOCODINGRESPONSE;

// Функция обратного вызова (тип)
// callparam - передаваемый внутрь функции параметр, внутри функции не изменяется
// command - команда вызывающему приложению:
// CM_ADDR_DLG_SHOW  - при показе диалога
// CM_ADDR_DLG_CLOSE - при закрытии диалога
// CM_ADDR_DLG_MOVE  - при перемещении в заданную точку
// addr - результат поиска (выбранная пользователем запись)
typedef long int (*callbackAddress)(HANDLE callparam, long int command, const WCHAR* addr);

// Функция обратного вызова (тип)
// callparam - передаваемый внутрь функции параметр, внутри функции не изменяется
// command - команда вызывающему приложению:
// CM_ADDR_DLG_SHOW  - при показе диалога
// CM_ADDR_DLG_CLOSE - при закрытии диалога (B и L содержат координаты диалога в пикселах на экране в момент закрытия)
// CM_ADDR_DLG_MOVE  - при перемещении в заданную точку (B и L содержат найденные координаты)
// B, L - координаты (градусы в WGS 84 либо пиксели экрана)
// urequest - пользовательский запрос
typedef long int (*callbackAddressBL)(HANDLE callparam, long int command, double B, double L, const WCHAR* urequest);

// Создать идентификатор соединения с адресным локатором
// connectionstring - строка соединения с сервером
// На выходе - идентификатор соединения с адресным локатором
// При ошибке (в т.ч. при отсутствии соединения с сервером) возвращает 0
// Важно: каждому вызову addressCreate должен соответствовать addressFree
_ADRIMP HADDRESS _ADRAPI addressCreate(const WCHAR * connectionstring);

// Принудительная проверка соединения с сервером
// address - идентификатор соединения с адресным локатором, созданый addressCreate()
// При успехе возвращает 1
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressCheckConnect(HADDRESS address);

// Получить список адресов по поисковому запросу в нотации SQL Server
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// in - входная строка (не больше MaxINForGetAddressByStr символов)
// out - выходная строка (xml)
// outsize - размер памяти (в символах, не менее minout) выделенной под out
// выделенная память заполнится количеством записей равным целому от (outsize-common_chars)/chars_for_record
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressGetAddressByStr(HADDRESS address, const WCHAR* in,
                                                WCHAR* out, long int outsize);

// Получить список адресов по поисковому запросу в свободной форме
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// in - входная строка (не больше MaxINForGetAddressByHumanStr символов)
// out - выходная строка (xml, схема описана отдельно в руководстве программиста)
// outsize - размер памяти (в символах, не менее minout) выделенной под out;
// выделенная память заполнится количеством записей равным целому от (outsize-common_chars)/chars_for_record
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressGetAddressByHumanStr(HADDRESS address, const WCHAR* in,
                                                     WCHAR* out, long int outsize);

// Модальный диалог получения адреса по поисковому запросу в свободной форме
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// out - выходная строка (xml)  (размер выделяемой памяти под out должен быть не менее minout символов)
// count - количество записей в выпадающем списке
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressGetAddressDlg(HADDRESS address, WCHAR* out,
                                              long int count);

// Немодальный диалог получения адреса по поисковому запросу  в свободной форме
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// callparam - возвращаемый параметр
// callbackfunc - указатель на функцию обратного вызова
// count - количество записей в выпадающем списке
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressGetAddressDlgNoModal(HADDRESS address,
                                                     callbackAddress callbackfunc,
                                                     HANDLE callparam,
                                                     long int count);

// Немодальный диалог получения адреса по поисковому запросу  в свободной форме с возможностью указать заголовок
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// callparam - возвращаемый параметр
// callbackfunc - указатель на функцию обратного вызова
// count - количество записей в выпадающем списке
// caption - заголовок диалога
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressGetAddressDlgNoModalCaption(HADDRESS address,
                                                            callbackAddress callbackfunc,
                                                            HANDLE callparam,
                                                            long int count,
                                                            const WCHAR* caption);

// Немодальный диалог получения координат адреса по поисковому запросу  в свободной форме
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// callparam - возвращаемый параметр
// callbackfunc - указатель на функцию обратного вызова
// count - количество записей в выпадающем списке
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressGetAddressDlgNoModalBL(HADDRESS address,
                                                       callbackAddressBL callbackfunc,
                                                       HANDLE callparam,
                                                       long int count);

// Немодальный диалог получения координат адреса по поисковому запросу  в свободной форме
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// callparam - возвращаемый параметр
// callbackfunc - указатель на функцию обратного вызова
// count - количество записей в выпадающем списке
// x, y - координаты левого верхнего угла диалога (горизонталь, вертикаль) в пикселях
// При показе диалога вызывается callbackfunc с командой CM_ADDR_DLG_SHOW
// При закрытии вызывается callbackfunc с командой CM_ADDR_DLG_CLOSE (B и L содержат
// координаты диалога в пикселах на экране в момент закрытия)
// При перемещении в заданную точку вызывается callbackfunc с командой CM_ADDR_DLG_MOVE (B и L содержат
// искомые координаты: градусы в WGS 84)
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressGetAddressDlgNoModalBLEx(HADDRESS address,
                                                         callbackAddressBL callbackfunc,
                                                         HANDLE callparam,
                                                         long int count,
                                                         long int x,
                                                         long int y);

// Принудительное закрытие диалога поиска адреса
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressCloseDLG(HADDRESS address);

// Диалог формирования адреса из БД
// address - идентификатор соединения с адресным локатором, созданный addressCreate()
// st_address - указатель на структуру адреса
// Pезультат работы диалога (возвращаемое значение): 0 - ошибка, 1 - выбрать, 2 - выход
_ADRIMP long int _ADRAPI addressSelectAddressFromDB(HADDRESS address, TSTRUCT_ADDRESS* st_address);

// Геокодировать строку
// SearchString - запрос
// ResultString результат
// При ошибке возвращает 0
_ADRIMP long int _ADRAPI addressGeoCode(PGEOCODINGREQUEST SearchString,
                                        PGEOCODINGRESPONSE ResultString);

// Закрыть соединение с адресным локатором и освободить ресурсы
// address - идентификатор соединения с адресным локатором, созданный addressCreate
// Важно: каждому вызову addressFree должен соответствовать addressCreate
_ADRIMP void _ADRAPI addressFree(HADDRESS address);

#endif //ADDRESS_H
