/***** ADDRESS.H ***********  Korolev A.A.  ***************** 12/02/15 ****
****** ADDRESS.H ***********  Shevchenko A.A.  ************** 08/12/14 ****
****** ADDRESS.H ***********  Shabakov D.A. ***************** 15/09/16 ****
*                                                                         *
*                   Copyright (c) PANORAMA Group 1991-2016                *
*                          All Rights Reserved                            *
*                                                                         *
***************************************************************************
*                                                                         *
*                             �������� �������                            *
*                                                                         *
***************************************************************************
*                                                                         *
*                    �������������� ������� � Windows :                   *
*                                                                         *
* // �������� ����������                                                  *
* HINSTANCE libInst = ::LoadLibrary("address.dll");                       *
*                                                                         *
* // ����� �������                                                        *
* HADDRESS (WINAPI * lpfn_addressCreate)(const WCHAR * connectionstring); *
* (FARPROC)lpfn_addressCreate = GetProcAddress(libInst, "addressCreate"); *
* HADDRESS address = (*lpfn_addressCreate)("<������ ����������>");        *
*                                                                         *
* // �������� ����������                                                  *
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

#define chars_for_record 512                     // ���������� ��������, ������������ �� ���� ������ �� ��������� ��������
#define common_chars 64                          // ���������� ���������� ��������, ������������ �� ����� ������� �� ��������� ��������
#define minout (chars_for_record+common_chars)   // ����������� ���������� ��������, ��� ������� ��������� ��������� ������,
                                                 // ��� ������������� addressGetAddressByStr, addressGetAddressByHumanStr
                                                 // � addressGetAddressDlg
#define MaxINForGetAddressByHumanStr 2048        // ������������ ����� ������� ������ ��� GetAddressByHumanStr (� ��������)
#define MaxINForGetAddressByStr 32768            // ������������ ����� ������� ������ ��� GetAddressByStr (� ��������)

typedef struct TSTRUCT_ADDRESS
{
  WCHAR OKATO[32];                       // ��� �����
  WCHAR KLADR[32];                       // ��� �����
  WCHAR POSTINDEX[16];                   // �������� ������
  WCHAR REGION[256];                     // ������
  WCHAR RCODE[32];                       // ��� �������
  WCHAR DISTRICT[256];                   // �����/��������� �����
  WCHAR DTYPE[32];                       // ��� ������/���������� ������
  WCHAR CITY[256];                       // ������������ ���������� ������/���������
  WCHAR CTYPE[32];                       // ��� ���������� ������/���������
  WCHAR UDNAME[256];                     // ��������� �����
  WCHAR UDTYPE[32];                      // ��� ���������� ������
  WCHAR SVILLAGE[256];                   // ������������ ����������
  WCHAR SVTYPE[32];                      // ��� ����������
  WCHAR NP[256];                         // ��������� �����
  WCHAR NPTYPE[256];                     // ��� ���������� ������
  WCHAR STREET[256];                     // ������������ �����
  WCHAR STYPE[32];                       // ��� �����
  WCHAR HTYPE[32];                       // ��� ����
  WCHAR HOUSE[256];                      // ���
  WCHAR PTYPE[32];                       // ��� �������
  WCHAR PART[256];                       // ������
  WCHAR BLDNGTYPE[32];                   // ��� ��������
  WCHAR BUILDING[256];                   // ��������
  WCHAR FLATTYPE[32];                    // ��� ��������
  WCHAR FLAT[256];                       // ��������
  WCHAR OTHERDESC[4096];                 // ���� �������� ��������������
  WCHAR UNFORMADDR[4096];                // ����������������� �������� ������(��������������)
}
TSTRUCT_ADDRESS, *PSTRUCT_ADDRESS;

typedef WCHAR TGEOCODINGREQUEST[4096];
typedef TGEOCODINGREQUEST* PGEOCODINGREQUEST;

typedef struct TGEOCODINGRESPONSE
{
  WCHAR B[32];                               // B
  WCHAR L[32];                               // L
  WCHAR A[4096];                             // �����
}
TGEOCODINGRESPONSE, *PGEOCODINGRESPONSE;

// ������� ��������� ������ (���)
// callparam - ������������ ������ ������� ��������, ������ ������� �� ����������
// command - ������� ����������� ����������:
// CM_ADDR_DLG_SHOW  - ��� ������ �������
// CM_ADDR_DLG_CLOSE - ��� �������� �������
// CM_ADDR_DLG_MOVE  - ��� ����������� � �������� �����
// addr - ��������� ������ (��������� ������������� ������)
typedef long int (*callbackAddress)(HANDLE callparam, long int command, const WCHAR* addr);

// ������� ��������� ������ (���)
// callparam - ������������ ������ ������� ��������, ������ ������� �� ����������
// command - ������� ����������� ����������:
// CM_ADDR_DLG_SHOW  - ��� ������ �������
// CM_ADDR_DLG_CLOSE - ��� �������� ������� (B � L �������� ���������� ������� � �������� �� ������ � ������ ��������)
// CM_ADDR_DLG_MOVE  - ��� ����������� � �������� ����� (B � L �������� ��������� ����������)
// B, L - ���������� (������� � WGS 84 ���� ������� ������)
// urequest - ���������������� ������
typedef long int (*callbackAddressBL)(HANDLE callparam, long int command, double B, double L, const WCHAR* urequest);

// ������� ������������� ���������� � �������� ���������
// connectionstring - ������ ���������� � ��������
// �� ������ - ������������� ���������� � �������� ���������
// ��� ������ (� �.�. ��� ���������� ���������� � ��������) ���������� 0
// �����: ������� ������ addressCreate ������ ��������������� addressFree
_ADRIMP HADDRESS _ADRAPI addressCreate(const WCHAR * connectionstring);

// �������������� �������� ���������� � ��������
// address - ������������� ���������� � �������� ���������, �������� addressCreate()
// ��� ������ ���������� 1
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressCheckConnect(HADDRESS address);

// �������� ������ ������� �� ���������� ������� � ������� SQL Server
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// in - ������� ������ (�� ������ MaxINForGetAddressByStr ��������)
// out - �������� ������ (xml)
// outsize - ������ ������ (� ��������, �� ����� minout) ���������� ��� out
// ���������� ������ ���������� ����������� ������� ������ ������ �� (outsize-common_chars)/chars_for_record
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressGetAddressByStr(HADDRESS address, const WCHAR* in,
                                                WCHAR* out, long int outsize);

// �������� ������ ������� �� ���������� ������� � ��������� �����
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// in - ������� ������ (�� ������ MaxINForGetAddressByHumanStr ��������)
// out - �������� ������ (xml, ����� ������� �������� � ����������� ������������)
// outsize - ������ ������ (� ��������, �� ����� minout) ���������� ��� out;
// ���������� ������ ���������� ����������� ������� ������ ������ �� (outsize-common_chars)/chars_for_record
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressGetAddressByHumanStr(HADDRESS address, const WCHAR* in,
                                                     WCHAR* out, long int outsize);

// ��������� ������ ��������� ������ �� ���������� ������� � ��������� �����
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// out - �������� ������ (xml)  (������ ���������� ������ ��� out ������ ���� �� ����� minout ��������)
// count - ���������� ������� � ���������� ������
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressGetAddressDlg(HADDRESS address, WCHAR* out,
                                              long int count);

// ����������� ������ ��������� ������ �� ���������� �������  � ��������� �����
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// callparam - ������������ ��������
// callbackfunc - ��������� �� ������� ��������� ������
// count - ���������� ������� � ���������� ������
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressGetAddressDlgNoModal(HADDRESS address,
                                                     callbackAddress callbackfunc,
                                                     HANDLE callparam,
                                                     long int count);

// ����������� ������ ��������� ������ �� ���������� �������  � ��������� ����� � ������������ ������� ���������
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// callparam - ������������ ��������
// callbackfunc - ��������� �� ������� ��������� ������
// count - ���������� ������� � ���������� ������
// caption - ��������� �������
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressGetAddressDlgNoModalCaption(HADDRESS address,
                                                            callbackAddress callbackfunc,
                                                            HANDLE callparam,
                                                            long int count,
                                                            const WCHAR* caption);

// ����������� ������ ��������� ��������� ������ �� ���������� �������  � ��������� �����
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// callparam - ������������ ��������
// callbackfunc - ��������� �� ������� ��������� ������
// count - ���������� ������� � ���������� ������
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressGetAddressDlgNoModalBL(HADDRESS address,
                                                       callbackAddressBL callbackfunc,
                                                       HANDLE callparam,
                                                       long int count);

// ����������� ������ ��������� ��������� ������ �� ���������� �������  � ��������� �����
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// callparam - ������������ ��������
// callbackfunc - ��������� �� ������� ��������� ������
// count - ���������� ������� � ���������� ������
// x, y - ���������� ������ �������� ���� ������� (�����������, ���������) � ��������
// ��� ������ ������� ���������� callbackfunc � �������� CM_ADDR_DLG_SHOW
// ��� �������� ���������� callbackfunc � �������� CM_ADDR_DLG_CLOSE (B � L ��������
// ���������� ������� � �������� �� ������ � ������ ��������)
// ��� ����������� � �������� ����� ���������� callbackfunc � �������� CM_ADDR_DLG_MOVE (B � L ��������
// ������� ����������: ������� � WGS 84)
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressGetAddressDlgNoModalBLEx(HADDRESS address,
                                                         callbackAddressBL callbackfunc,
                                                         HANDLE callparam,
                                                         long int count,
                                                         long int x,
                                                         long int y);

// �������������� �������� ������� ������ ������
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressCloseDLG(HADDRESS address);

// ������ ������������ ������ �� ��
// address - ������������� ���������� � �������� ���������, ��������� addressCreate()
// st_address - ��������� �� ��������� ������
// P�������� ������ ������� (������������ ��������): 0 - ������, 1 - �������, 2 - �����
_ADRIMP long int _ADRAPI addressSelectAddressFromDB(HADDRESS address, TSTRUCT_ADDRESS* st_address);

// ������������� ������
// SearchString - ������
// ResultString ���������
// ��� ������ ���������� 0
_ADRIMP long int _ADRAPI addressGeoCode(PGEOCODINGREQUEST SearchString,
                                        PGEOCODINGRESPONSE ResultString);

// ������� ���������� � �������� ��������� � ���������� �������
// address - ������������� ���������� � �������� ���������, ��������� addressCreate
// �����: ������� ������ addressFree ������ ��������������� addressCreate
_ADRIMP void _ADRAPI addressFree(HADDRESS address);

#endif //ADDRESS_H
