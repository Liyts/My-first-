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
*            �������� ������� ��������� ������                     *
*        ��������� ��� �������� �� ������ C, PASCAL, BASIC         *
*                                                                  *
*    �������������� ������� � Windows :                            *
*                                                                  *
*    #include "maplib.h"                                           *
*    // �������� ����������                                        *
*    HINSTANCE libInst = ::LoadLibrary(MAPPICEXLIB);               *
*                                                                  *
*    // ����� �������                                              *
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
*    // �������� ����������                                        *
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
// �������� ��������� ������ �� ����� PCX � ���� RSW
//    Handle  - ������ ����������� ������������� �������� ���������.
//    PcxName - ��� PCX-�����;
//    RstName - ��� RST-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    compression - ���� ������ �����������
//              0 - ������ � ������ ����������� ����������� �� �����
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ������ �� ����� PCX � ���� RSW
//    Handle  - ������ ����������� ������������� �������� ���������.
//    PcxName - ��� PCX-�����;
//    RstName - ��� RST-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    compression - ���� ������ �����������
//              0 - ������ � ������ ����������� ����������� �� �����
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    compressJpegQuality - ������� ������ ����� ������ �� ��������� JPEG
//              ��������� ��������: 1 - 100
//              ������������� ��������: 60
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ������ �� ����� BMP � ���� RSW
//    BmpName - ��� BMP-�����;
//    RstName - ��� RSW-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - HWND ������� ����������� ������������� �������� ���������.
//    compression - ���� ������ �����������
//              0 - ������ � ������ ����������� ����������� �� �����
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ������ �� ����� BMP � ���� RSW
//    Handle  - ������ ����������� ������������� �������� ���������.
//    BmpName - ��� BMP-�����;
//    RstName - ��� RSW-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    compression - ���� ������ �����������
//              0 - ������ � ������ ����������� ����������� �� �����
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    compressJpegQuality - ������� ������ ����� ������ �� ��������� JPEG
//              ��������� ��������: 1 - 100
//              ������������� ��������: 60
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ������ �� ����� JPEG � ���� RSW
//    Map - ���������� ��������� ���������
//    inputname - ��� JPEG-�����;
//    rstname   - ��� RSW-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//              0 - ������ � ������ ����������� �� ���������
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    compressJpegQuality - ������� ������ ����� ������ �� ��������� JPEG
//              ��������� ��������: 1 - 100
//              ������������� ��������: 60
//    flagMessage - ���� ������ ���������
//                                       (��� ==1, ��������� ������ MessageBox;
//                                        ��� == 0, ���������� ��������� ������� WM_ERROR)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ������ �� ����� JPEG � ���� RSW
//    Handle - ������ ����������� ������������� �������� ���������.
//    Map - ���������� ��������� ���������
//    inputname - ��� JPEG-�����;
//    rstname   - ��� RSW-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//    flagMessage - ���� ������ ���������
//                                       (��� ==1, ��������� ������ MessageBox;
//                                        ��� == 0, ���������� ��������� ������� WM_ERROR)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ����� ��� ����������� ����������� � ������ RSW
// � �������� �������� ������ � ������� ����� ������������ ����� ������ ��������:
// (TIFF, GeoTIFF, IMG, JPEG, PNG, GIF, BMP)
// ��� �������� ���������� ������� ��������� ���� RSW � ������ outputName.
// � ���� RSW ������������ ��������� ������������ ������, ��� ���� ����������� �
// RSW �� �����������. �������� � �������� (*.RSW) ����� ������ ���������� � ����� �����.
// �������� ����������� ������ ������������ � ���� *.TOF, ������� ��������� � ���� �� �����.
// ��� ������� � ����������� ������������ ����� ��������� ���� outputName ����������
// ������� ������� ������� mapOpenRstUn, ��� �������� � �������� ����� �������
// ������� mapOpenRstForMapUn.
// ������� ��������� �������:
//    Handle          - ������ ����������� ������������� �������� ���������.
//    enableMessage   - ���� ������ ���������
//                             (��� ==1, ��������� ������ MessageBox;
//                              ��� == 0, ���������� ��������� ������� WM_ERROR)
//    sourceName      - ��� ��������� ����� (*.TIF, *.IMG, *.JPG, *.PNG, *.GIF, *.BMP);
//    outputName      - ��� ��������� ����� (*.RSW);
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point           - �������� ������
//
//    ���� � �������� ��������� ����� �������� ���� GeoTIFF, ��� ���� IMG �
//    �������������� ������������, �� ������� ��������� meterInElementX,
//    meterInElementY � point ����� ���� ����� 0.
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
//========================================================================
_PICIMP long int _PICAPI picexGetAccessToGraphicFileUn(HMESSAGE Handle,
                                                      int enableMessage,
                                                      const WCHAR * sourceName,
                                                      const WCHAR * outputName,
                                                      double* meterInPixelX,
                                                      double* meterInPixelY,
                                                      DOUBLEPOINT *point);

//========================================================================
// �������� ��������� ����� �� Tiff(GeoTiff) � RSW             // 24/02/12
// ����������� � RSW �� �����������, � RSW ������������ ���������, �������, ��.
//    Map - ���������� ��������� ���������
//    PcxName - ��� PCX-�����;
//    RstName - ��� RST-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point   - �������� ������
//    mapreg  - ��������� ��������

//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//    flagMessage - ���� ������ ���������
//                                       (��� ==1, ��������� ������ MessageBox;
//                                        ��� == 0, ���������� ��������� ������� WM_ERROR)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ����� �� Tiff(GeoTiff) � RSW
//    Handle - ������ ����������� ������������� �������� ���������.
//    TiffName - ��� Tiff-�����;
//    RstName - ��� Rst-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//              0 - ������ � ������ ����������� ����������� �� �����
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    flagIgnoreGeoTiff - (0/1) ���� ������������� GeoTiff �����
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ����� �� Tiff(GeoTiff) � RSW
//    Handle - ������ ����������� ������������� �������� ���������.
//    TiffName - ��� Tiff-�����;
//    RstName - ��� Rst-�����;
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//              0 - ������ � ������ ����������� ����������� �� �����
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    compressJpegQuality - ������� ������ ����� ������ �� ��������� JPEG
//              ��������� ��������: 1 - 100
//              ������������� ��������: 60
//    flagIgnoreGeoTiff - (0/1) ���� ������������� GeoTiff �����
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// ��������� ������������ ���������� ����������� ����� ��� ������
// (��� ������ ���������� ������������ ���������� ����������� �
//  ���������� ����� ������ �������� � �������� ������� RGB � CMYK)
//-----------------------------------------------------------------

typedef struct SAVEASPICTRPARM_FOR_PRINT
{
  int Length;         // ����� ��������� SAVEASPICTRPARM_FOR_PRINT
#if defined(_M_X64) || defined(BUILD_DLL64)          // 28/07/16
  int Reserve1;
#endif
  HMESSAGE Handle;    // ������������� ���� ������� (������������ ���
                      // ����������� ������������� ��������)
  HMAP HMap;          // ������������� �����
  int Regime;         // ����� ������ ������������� �������
                      // (AREA_ALL, AREA_SELECT_FRAME, ... - ��. maptype.h)
#if defined(_M_X64) || defined(BUILD_DLL64)          // 28/07/16
  int Reserve2;
#endif
  DFRAME PlaneFrame;  // �������� ��������� ������� � ������

  double DPI;         // ���������� ����������� (����� �� ����)
  double LPI;         // ����� ������� �� ���� (��� Method = 0 ������������).
                      // ����� ������� �� ����� ����� Shape

  double FactorVer;   // ������������ ���������� ����������� ��
  double FactorHor;   // ������������ � �������������� ����

  RECT Rect;          // ������� ����������� ������� ����� � ��������
                      //  (��� �������� � RGB �� �����������)          //24/04/08

  int Scale;          // ������� (�����������)

  int BitCount;       // ���������� ��� �� ������ ���������� �����������
                      // ��� ColorModel == 0:                          // 20/04/08
                      //   8,16,24,32 ��� �� ������ (RGB)
                      // ��� ColorModel == 1:
                      //   1,8 ��� �� ������ (CMYK) - ������ ����� BMP ��� PCX
                      //   32 ��� �� ������ (CMYK) - ���� ���� TIF

  int Intensity;      // ������������� ������� ��������� �������� (0-100)

  int ColorModel;     // ���� �������� ������:
                      //   0 - RGB (����������� ���� ����)
                      //   1 - CMYK BMP ��� CMYK PCX (������ 8-������
                      //       ��� 1-������ �����, ������������ ����������
                      //       �����������, � ����������� � ��������
                      //       ����� ��������� "-C","-M","-Y","-K"),
                      //       ��� CMYK TIF (���� ����)

  int Method;         // ����� ��������������� 8-������ �����������
                      // ����������� CMYK � 1-������:
                      //   0 - �� ��������� (��������� 8-������ �����������),
                      //   1 - ���������� ���������� ������� ����� Shape
                      //       � ����� DPI/LPI

  int Shape;          // ����� ����� (���������) ���������� �������
                      // (��� Method = 0 ������������):
                      //   0 - ���������� ���������� �������� �������

                      // ���� ������� ����� ������� (��� Method = 0 ������������)
  double AngleC;      //  15 ��������
  double AngleM;      //  75 ��������
  double AngleY;      //   0 ��������
  double AngleK;      //  45 ��������

  char Reserve[96];   // ������

  char Cross;         // ���� ��������� ����������� ������� (��� ColorModel > 0)
                      // (1 - ����, 0 - ���), (���� �� �����������)
  char Negative;      // ���� ���������� ����������� ����������� (��� BitCount = 1)
                      // (1 - ����, 0 - ���), (���� �� �����������)
  char Mirror;        // ���� ���������� ����������� ����������� (��� BitCount = 1)
                      // (1 - ����, 0 - ���), (���� �� �����������)
  char Turn;          // ���� �������� ����������� �� 90 �������� (��� BitCount = 1)
                      // (1 - ����, 0 - ���), (���� �� �����������)

  char FileName[260]; // ������� ��� ������������ ����� (BMP, PCX, TIF)

                      // ��� �������� 1.BMP (��� BitCount = 1) �����������
                      // ������ �����: 1-�.BMP, 1-M.BMP, 1-Y.BMP, 1-K.BMP

                      // ��� �������� 1.PCX (��� BitCount = 1) �����������
                      // ������ �����: 1-�.PCX, 1-M.PCX, 1-Y.PCX, 1-K.PCX

                      // � ��������� ������� ����������� ���� ����
}
  SAVEASPICTRPARM_FOR_PRINT;

extern "C"
{

//========================================================================
//    ��������� PCX -> Rsw
//    map - ���������� ��������� ���������
//    handle - ������ ����������� ������������� �������� ���������.
//    pcxname - ��� PCX-�����;
//    rstname - ��� RST-�����(*.rsw);
//    scale   - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� PCX -> Rsw
//    map - ���������� ��������� ���������
//    handle - ������ ����������� ������������� �������� ���������.
//    pcxname - ��� PCX-�����;
//    rstname - ��� RST-�����(*.rsw);
//    scale   - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    Map     - ���������� ��������� ���������
//    PcxName - ��� PCX-�����;
//    RstName - ��� RST-�����;
//    scale   - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ��������� PCX-�����
//    pcxname     - ��� PCX-�����;
//    information - ��������� �� ��������� DATAINFORMATION ��� ������ ���������� PCX-�����
//    ��������� DATAINFORMATION ������� � picexprm.h
//
//    ������� LoadPxcInformation ������������� �������� ����� �������
//    ����������� PCX-����� � Rsw ��� ������������� ������� �������������
//========================================================================
_PICIMP long int _PICAPI LoadPcxInformation(const char * pcxname,
                                           DATAINFORMATION * information);

_PICIMP long int _PICAPI LoadPcxInformationUn(const WCHAR * PcxName,             // 19/06/14
                                           DATAINFORMATION * information);


//========================================================================
//    ��������� Bmp -> Rsw
//    map       - ���������� ��������� ���������
//    handle    - ������ ����������� ������������� �������� ���������;
//    bmpname   - ��� BMP-�����;
//    rstname   - ��� RST-�����(*.rsw);
//    scale     - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� Bmp -> Rsw
//    map     - ���������� ��������� ���������
//    handle  - ������ ����������� ������������� �������� ���������;
//    bmpname - ��� BMP-�����;
//    rstname - ��� RST-�����;
//    scale   - ������� ������������ ������;
//    frame   - �������� ������(� ������ �� ���������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� Bmp -> Rsw
//    map       - ���������� ��������� ���������
//    handle    - ������ ����������� ������������� �������� ���������;
//    bmpname   - ��� BMP-�����;
//    rstname   - ��� RST-�����(*.rsw);
//    scale     - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)

//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ��������� BMP-�����
//    bmpname     - ��� BMP-�����;
//    information - ��������� �� ��������� DATAINFORMATION ��� ������ ���������� BMP-�����
//    ��������� DATAINFORMATION ������� � picexprm.h
//
//    ������� LoadBmpInformation ������������� �������� ����� �������
//    ����������� BMP-����� � Rsw ��� ������������� ������� �������������
//========================================================================
_PICIMP long int _PICAPI LoadBmpInformation(const char * bmpname,
                                       DATAINFORMATION * information);

_PICIMP long int _PICAPI LoadBmpInformationUn(const WCHAR * bmpname,              // 10/02/14
                                       DATAINFORMATION * information);


//========================================================================
//    ��������� Tiff -> Rsw
//    map       - ���������� ��������� ���������
//    handle    - ������ ����������� ������������� �������� ���������.
//    tifname   - ��� TIF-�����;
//    rstname   - ��� RST-�����;
//    scale     - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� Tiff -> Rsw
//    map       - ���������� ��������� ���������
//    handle    - ������ ����������� ������������� �������� ���������.
//    tifname   - ��� TIF-�����;
//    rstname   - ��� RST-�����;
//    scale     - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� Tiff -> Rsw
//    Map     - ���������� ��������� ���������
//    PcxName - ��� PCX-�����;
//    RstName - ��� RST-�����;
//    scale   - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� Tiff -> Rsw
//    Map     - ���������� ��������� ���������
//    PcxName - ��� PCX-�����;
//    RstName - ��� RST-�����;
//    scale   - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//    flagIgnoreGeoTiff - (0/1) ���� ������������� GeoTiff �����                 // 17/11/11
//    arg1,arg2 - ��������� �� ������������
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ��������� TIFF-�����
//    tifname     - ��� TIFF-�����;
//    information -  ��������� �� ��������� DATAINFORMATION ��� ������ ���������� TIFF-�����
//    ��������� DATAINFORMATION ������� � picexprm.h
//
//    ������� LoadTifInformation ������������� �������� ����� �������
//    ����������� TIFF-����� � Rsw ��� ������������� ������� �������������
//========================================================================
_PICIMP long int _PICAPI LoadTifInformation(HMESSAGE handle, const char * TifName,
                                           DATAINFORMATION * information);

long int _PICAPI LoadTifInformationUn(HMESSAGE handle, const WCHAR * TifName, // 18/06/14
                                           DATAINFORMATION * information);

//========================================================================
//    ��������� ��������� GeoTIFF-�����
//    TifName - ��� GeoTIF-�����;
//    DataInformation - ���������, ������� ���������� ���������
//    geoTIFFinformation - ���������, ������� ���������� ���������
//    ��������� DATAINFORMATION � GEOTIFFINFORMATION ������� � picexprm.h
//
//    ������� LoadGeoTifInformation ������������� �������� ����� �������
//    ����������� TIFF-����� � Rsw ��� ������������� ������� �������������
//========================================================================
_PICIMP long int _PICAPI LoadGeoTifInformation(HMESSAGE Handle, const char * TiffName,
                                              DATAINFORMATION * information,
                                              GEOTIFFINFORMATION* geoTIFFinformation);

_PICIMP long int _PICAPI LoadGeoTifInformationUn(HMESSAGE Handle, const WCHAR * TiffName,  // 18/06/14
                                              DATAINFORMATION * information,
                                              GEOTIFFINFORMATION* geoTIFFinformation);

//========================================================================
//    ��������� ��������� �� �� ����� GeoTiff
//    Handle              - ������ ����������� ������������� �������� ���������.
//    TifName             - ��� TIF-�����;
//    geoTIFFparam        - ��������� �� ��������� GEOTIFFPARAM ��� ������
//                                                                ���������� ��
//========================================================================
_PICIMP long int _PICAPI LoadGeoTiffParameters(HMESSAGE Handle, const char * TiffName,
                                              GEOTIFFPARAM * geoTIFFparam);

_PICIMP long int _PICAPI LoadGeoTiffParametersUn(HMESSAGE Handle, const WCHAR * TiffName,  // 18/06/14
                                              GEOTIFFPARAM * geoTIFFparam);

//#ifndef LINUXAPI	// 03/02/15 Korjilov
//======================================================================== // 24/11/03
//    ��������� ��������� JPEG-�����
//    inputname   - ��� JPEG-�����;
//    information -  ��������� �� ��������� DATAINFORMATION ��� ������ ���������� JPEG-�����
//    ��������� DATAINFORMATION ������� � picexprm.h
//
//    ������� LoadJPEGInformation ������������� �������� ����� �������
//    �������������� JPEG-����� � Rsw ��� ������ ���������� � ����������� �����
//========================================================================
_PICIMP long int _PICAPI LoadJPEGInformation(const char * inputname,
                                            DATAINFORMATION * iformation);

_PICIMP long int _PICAPI LoadJPEGInformationUn(const WCHAR * inputname,
                                            DATAINFORMATION * iformation);

//========================================================================
//    map     - ���������� ��������� ���������
//    PcxName - ��� PCX-�����;
//    RstName - ��� RST-�����;
//    scale   - ������� ������������ ������
//    precision - ����������� ����������� ������������ ������(�/�)
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//    flagMessage - ���� ������ ���������
//                                       (��� ==1, ��������� ����� MessageBox;
//                                        ��� == 0, ���������� ��������� ������� WM_ERROR)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// ��������� ����������� 24-� ������� ������ RSW � ���� JPEG                    // 21/08/13
// hMap                - ������������� ��������� � �������� ������� rswName
// Handle              - ������ ����������� ������������� �������� ���������.
// rswName             - ��� ����� 24-� ������� ������ RSW
// jpegName            - ��� ����� JPEG
// compressJpegQuality - ������� ������ ����� ������ �� ��������� JPEG
//              ��������� ��������: 1 - 100
//              ������������� ��������: 60
//========================================================================
_PICIMP long int _PICAPI picexSaveRswToJpeg(HMAP hMap, HMESSAGE handle,
                                      const char * rswName, const char * jpegName,
                                      long int compressJpegQuality);

_PICIMP long int _PICAPI picexSaveRswToJpegUn(HMAP hMap, HMESSAGE handle,       // 20/06/14
                                      const WCHAR * rswName, const WCHAR * jpegName,
                                      long int compressJpegQuality);

//========================================================================
// ��������� ��������� MrSID-����� (*.jp2;*.sid;*.ntf)
// handle              - ������ ����������� ������������� �������� ���������.
// inputname           - ��� MrSID-�����
// information         - ��������� �� ��������� DATAINFORMATION ��� ������
//                                                              ���������� �����
// geoInformation      - ��������� �� ��������� GEOTIFFINFORMATION ��� ������
//                                                        ���������� �����������
//    ��������� DATAINFORMATION � GEOTIFFINFORMATION ������� � picexprm.h
//
//    ������� LoadMrSIDInformation ������������� �������� ����� �������
//    �������������� MrSIDI-����� � Rsw ��� ������ ���������� � ����������� �����
//========================================================================
_PICIMP long int _PICAPI LoadMrSIDInformation(HWND handle, const char * inputname,
                                             DATAINFORMATION * iformation,
                                             GEOTIFFINFORMATION* geoInformation);

_PICIMP long int _PICAPI LoadMrSIDInformationUn(HWND handle, const WCHAR * inputname,
                                             DATAINFORMATION * iformation,
                                             GEOTIFFINFORMATION* geoInformation);

//========================================================================
// ��������� ��������� �� �� ����� MrSID
// name - ��� ����� MrSid (*.jp2;*.sid;*.ntf)
// geoTIFFparam - ��������� �� ��������� GEOTIFFPARAM ��� ������ ���������� ��
//========================================================================
_PICIMP long int _PICAPI picexLoadGeoParametersMrSID(HMESSAGE Handle,
                                                    const char * name,
                                                    GEOTIFFPARAM * geoTIFFparam);

_PICIMP long int _PICAPI picexLoadGeoParametersMrSID_Un(HMESSAGE Handle,
                                                    const WCHAR * name,
                                                    GEOTIFFPARAM * geoTIFFparam);

//========================================================================
// �������� ��������� ������ � ���� RSW
// �������������� ����� MrSid (*.jp2;*.sid;*.ntf)
//    Map - �����,���������� ��������� ������
//    inputname - ��� ������������ �����
//    rstname   - ��� RST-�����
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������ �����������
//              0 - ������ � ������ ����������� ����������� �� �����
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    flagMessage - ���� ������ ���������
//                                       (��� ==1, ��������� ������ MessageBox;
//                                        ��� == 0, ���������� ��������� ������� WM_ERROR)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ��������� ������ � ���� RSW
// �������������� ����� MrSid (*.jp2;*.sid;*.ntf)
//    Map - �����,���������� ��������� ������
//    inputname - ��� ������������ �����
//    rstname   - ��� RST-�����
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������ �����������
//              0 - ������ � ������ ����������� ����������� �� �����
//              1 - ����� �.�. ����� �� ������ LZW
//              2 - ����� �.�. ����� �� ������ JPEG (����������� ��� 24 ������ �������)
//    compressJpegQuality - ������� ������ ����� ������ �� ��������� JPEG
//              ��������� ��������: 1 - 100
//              ������������� ��������: 60
//    flagMessage - ���� ������ ���������
//                                       (��� ==1, ��������� ������ MessageBox;
//                                        ��� == 0, ���������� ��������� ������� WM_ERROR)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ��������� ����� � ������� BMP
//    map     - ���������� ��������� ���������
//    handle  - ������ ����������� ������������� �������� ���������.
//    rstname - ��� RST-�����;
//    bmpname - ��� BMP-�����;
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstToBmpConverter(HMAP map, HMESSAGE handle,
                                              const char * rstname,
                                              const char * bmpname);

_PICIMP long int _PICAPI LoadRstToBmpConverterUn(HMAP map, HMESSAGE handle,
                                              const WCHAR * rstname,
                                              const WCHAR * bmpname);

//========================================================================
//    ��������� ��������� ����� � ������� BMP � ��������� �������� ����������� �� ����� ������
//    map     - ���������� ��������� ���������
//    handle  - ������ ����������� ������������� �������� ���������.
//    rstname - ��� RST-�����;
//    bmpname - ��� BMP-�����;
//    flagUseBorder - ���� "�������� ����������� �� �����"(0/1)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ��������� ����� � ������� BMP
//    � ��������������� �������� ������� ����������� ������ colorClear
//    ��� ������� � 1,4,8 ��� �� ������� colorClear - ������ ����� ������� ������,
//    ��� ������� � 16,24,32 ��� �� ������� colorClear - ���� COLORREF,
//
//    map     - ���������� ��������� ���������
//    handle  - ������ ����������� ������������� �������� ���������.
//    rstname - ��� RST-�����;
//    bmpname - ��� BMP-�����;
//    flagUseBorder - ���� "�������� ����������� �� �����"
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ��������� ����� � ������� PCX
//    map     - ���������� ��������� ���������
//    handle  - ������ ����������� ������������� �������� ���������.
//    rstname - ��� RST-�����;
//    pcxname - ��� PCX-�����;
//    flagUseBorder - ���� "�������� ����������� �� �����"
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ��������� ����� � ������� PCX
//    � ��������������� �������� ������� ����������� ������ colorClear
//    ��� ������� � 1,4,8 ��� �� ������� colorClear - ������ ����� ������� ������,
//    ��� ������� � 16,24,32 ��� �� ������� colorClear - ���� COLORREF,
//    map     - ���������� ��������� ���������
//    handle  - ������ ����������� ������������� �������� ���������.
//    rstname - ��� RST-�����;
//    pcxname - ��� PCX-�����;
//    flagUseBorder - ���� "�������� ����������� �� �����"
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
//========================================================================
_PICIMP long int _PICAPI SaveRstToPcxClear(HMAP map, HMESSAGE handle,
                                          const char * rstname, const char * pcxname,
                                          int flagUseBorder, long colorClear);

_PICIMP long int _PICAPI SaveRstToPcxClearUn(HMAP map, HMESSAGE handle,          // 19/06/14
                                          const WCHAR *rstname, const WCHAR *pcxname,
                                          int flagUseBorder, long colorClear);

//========================================================================
//    ��������� ��������� ����� � ������� TIFF
//    Map      - ���������� ��������� ���������
//    RstName  - ��� RST-�����;
//    TiffName - ��� TIFF-�����;
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������ (������������� �������� - 0)
//    platform - ��� ��������� (0 - INTEL, 1 - MOTOROLA)             (������������� �������� - 0)
//    imageStructure - ��������� ����������� TIFF (0 - BLOCK, 1- STRIP, 2 - NONFRAG) (������������� �������� - 1)
//    compressMethod - ���� ������ ����������� (0- �� ��������� ������, 1 - ������ PackBit) (������������� �������� - 0)
//    flagCMYK - ����� �������� ������:
//                     0 - �������� ������ RGB 24 ��� �� ������
//                     1 - �������� ������ CMYK 32 ��� �� ������
//                     ����� �������������� ������ ���  ������� 24,32 ��� �� ������.
//    Handle - ������ ����������� ������������� �������� ���������.
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
//    ��������� ��������� ����� � ������� TIFF
//    Map            - ���������� ��������� ���������
//    Handle         - ������ ����������� ������������� �������� ���������.
//    RstName        - ��� RST-�����;
//    TiffName       - ��� TIFF-�����;
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������
//                     (������������� �������� - 0).
//    platform - ��� ��������� (0 - INTEL, 1 - MOTOROLA)
//                     (������������� �������� - 0).
//    imageStructure - ��������� ����������� TIFF (0 - BLOCK, 1- STRIP, 2 - NONFRAG)
//                     (������������� �������� - 1).
//    compressMethod - ���� ������ ����������� (0- �� ��������� ������, 1 - ������ PackBit)
//                     (������������� �������� - 0).
//    flagCMYK - ����� �������� ������:
//                     0 - �������� ������ RGB 24 ��� �� ������
//                     1 - �������� ������ CMYK 32 ��� �� ������
//                     ����� �������������� ������ ���  ������� 24,32 ��� �� ������.
//    flagIntergraph - ���� ������ ������� �����������������,
//                        � ������� ������� Intergraph ���������� �������� ������
//    dframe         - �������� ����������� � ������ � ������.   // 25/10/05
//                     �������� ���������� ��� ������ ������� ����������������� (���� flagIntergraph == 1)
//    flag1 - flag6  - �� ������������. ������ ���� ����� ����.
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
//    �������� ����������� ��������� ����� �� ������������� �������, �������� � ������
//    map           - ���������� ��������� ���������
//    handle        - ������ ����������� ������������� �������� ���������.
//    rstInputName  - ��� ����� ��������� �����;
//    rstOutputName - ��� ����� ����������� ��������� �����;
//    frame         - �������� ���������� ������������� �������(� ������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    �������� ����������� ��������� ����� �� ������������� �������, �������� � ������
//    map           - ���������� ��������� ���������
//    handle        - ������ ����������� ������������� �������� ���������.
//    rstInputName  - ��� ����� ��������� �����;
//    rstOutputName - ��� ����� ����������� ��������� �����;
//    frame         - �������� ���������� ������������� �������(� ������)
//    flagUpdateRstDuplicates - ���� �������� ����������� ����� (0-���, 1-��)
//
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    �������� ����������� ������� �� ������������� �������, �������� � ������
//    map           - ���������� ��������� ���������
//    handle        - ������ ����������� ������������� �������� ���������.
//    rstInputName  - ��� ����� �������;
//    rstOutputName - ��� ����� ����������� �������;
//    frame         - �������� ���������� ������������� �������(� ������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ����������� ������� �� ������������� �������
// � ������ ����� �������� �������
//   map           - ���������� ��������� ���������
//   handle        - ������ ����������� ������������� �������� ���������
//   mtrInputName  - ��� ����� �������� �������
//   mtrOutputName - ��� ����� ����������� �������
//   frame         - �������� ���������� ������������� �������(� ������)
//   flag - ���� ����� ����� �������� �������, �������� :
//     0 - ����� �������� ������� �� �����������,
//     1 - �������� �������� �������, ����������� ��� �����, �� ������������
//         (������ ����������� ��������� ��� �����)
//     2 - �������� ��������� �������� �������, ����������� ��� �����,
//         ���������� �� fillValue (������� ��������� fillValue
//         ����������� ��������� ��� �����)
//   fillValue - �������� ��� ������� ����������� ��������� ��� �����,
//               ������������ ��� flag = 2, ������ ���� ������ -111111
//               (���� fillValue <= -111111, �� ����������� ������ �����������
//                ��������� ��� ����� ��� ��� flag = 1)
//   ������� ����������� ������������� �������� ��������� ����������
//   ���������:
//   -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//      WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//   -  (WM_ERROR) ��������� �� ������
//      LPARAM - ��������� �� ��������� ERRORINFORMATION
//      ��������� ERRORINFORMATION ������� � picexprm.h,
//      WM_PROGRESSBAR � WM_ERROR - � maptype.h
//
//   ��� ������ ���������� ����
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
//    ����������������� �������
// (���������� ������������� ��������� ��������� ������� ���������� ���������)
//
//   handle    - ������ ����������� ������������� �������� ���������;
//   map       - ���������� ��������� ���������
//   parm      - ��������� ���������� ������;
//   namein    - ��� ��������� ������ (MAX_PATH_LONG)
//   nameout   - ��� ��������� ������ (������ ���������� ������ �.�. �� ����� MAX_PATH_LONG ��������)
//   fact      - �������� ���������� �����;
//   teor      - �������� ���������� �����;
//   count     - ���������� ������� �����.
//
//   ������� ����������� ������������� �������� ��������� ���������� ���������:
//   -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//      WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����,
//==============================================================================
_PICIMP long int _PICAPI MtwTransformingBySquareMethod(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm, const char * namein, char * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);

//   sizeNameOut - ������ ���������� ������ ��� nameout � ������
_PICIMP long int _PICAPI MtwTransformingBySquareMethodUn(HMAP map,HMESSAGE handle,  // 19/06/14
                           TASKPARMEX * parm, const WCHAR * namein,
                           WCHAR * nameout, int sizeNameOut,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);

//==============================================================================
//    ��������� ������� � ���� ������� TIFF
//    handle         - ������ ����������� ������������� �������� ���������.
//    mtwName        - ��� ����� �������
//    tiffName       - ��� TIFF-�����;
//    flagborder     - ���� ������������� �����
//                     0 - �������� � ����������� ���� ��� �������� �������
//                     1 - �� �������� � ����������� ���� �������� �������
//                         ���������� � �������, ������������ ������
//    dframe         - ������������� ������� ����������� ��������� �������
//                     ��������� �.�. ����� ����
//==============================================================================
_PICIMP long int _PICAPI LoadMtwToTiffConverter(HMESSAGE handle,                 // 01/07/14
                                       char * mtwName, char * tiffName,
                                       long int flagborder, DFRAME* dframe);

_PICIMP long int _PICAPI LoadMtwToTiffConverterUn(HMESSAGE handle,               // 01/07/14
                                         const WCHAR * mtwName, const WCHAR * tiffName,
                                         long int flagborder, DFRAME* dframe);

//========================================================================      // 14/03/16
//    ��������� ������� � ������� TIFF
//    handle         - ������ ����������� ������������� �������� ���������.
//    mtwName        - ��� ����� �������
//    tiffName       - ��� TIFF-�����;
//    fileName       - ��� ����� ���������� (TFW, TAB);
//    flagborder     - ���� ������������� �����
//                     0 - �������� � ����������� ���� ��� �������� �������
//                     1 - �� �������� � ����������� ���� �������� �������
//                         ���������� � �������, ������������ ������
//    dframe         - ������������� ������� ����������� ��������� �������
//                     ��������� �.�. ����� ����
//========================================================================
_PICIMP long int _PICAPI LoadMtwToTiffConverterExUn(HMESSAGE handle,
                                         const WCHAR * mtwName,
                                         const WCHAR * tiffName,
                                         const WCHAR * fileName,
   				         long int flagborder, DFRAME* dframe);

//==============================================================================
// �������� ������ �� ������� SRTM (GeoTIFF)
//    map            - ���������� ��������� ���������
//    Handle         - ������ ����������� ������������� �������� ���������.
//    nameTiff       - ��� ��������� ����� ������� SRTM (GeoTIFF)
//    nameMtr        - ��� ����� ����������� �������
//    scale          - ������� ����������� �������
//    flagCompress   - �������� �� ������������, �.�. ����� 0.
//==============================================================================
_PICIMP long int _PICAPI LoadGeoTiffToMtr(HMAP map, HMESSAGE handle,                 // 01/07/14	// 06/02/15 Korjilov
                                 const char* nameTiff, const char* nameMtr,
                                 double scale, long int flagCompress);

_PICIMP long int _PICAPI LoadGeoTiffToMtrUn(HMAP map, HMESSAGE handle,               // 01/07/14	// 06/02/15 Korjilov
                                   const WCHAR* nameTiff, const WCHAR* nameMtr,
                                   double scale, long int flagCompress);

//#ifndef LINUXAPI								// 13/02/15 Korjilov
//================================================-========================
//    ��������� ����� � ������� BMP, Tiff, RSW  // 15/01/10
//    map        - ���������� ��������� ���������, ����������� ���������, ��������� � ��. ������;
//    handle     - ������ ������������� �������� ���������;
//    dframe     - �������� ����������� �����(� ������ �� ���������)
//    bitcount   - ���-�� ��� �� ������ ������������ ����������� (16, 24-������������� ��������, 32)
//    scale      - ������� ������������ �����������
//    resolution - ����������� ����������� ������������ �����������(�/�)
//    filename   - ��� ����� ������������ ����������� (*.bmp, *.tif);
//    handleMainWin - ������ ���� ����� ����
//    ��� ������ ������� ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ����� ��� TIFF GrayScale (8 ��� �� ������� - 256 �������� ������)   // 30/08/10
//    map        - ���������� ��������� ���������, ����������� ���������, ��������� � ��. ������;
//    handle     - ������ ������������� �������� ���������;
//    dframe     - �������� ����������� �����(� ������ �� ���������)
//    scale      - ������� ������������ �����������
//    resolution - ����������� ����������� ������������ �����������(�/�)
//    tiffName   - ��� ������������ TIFF-�����;
//    handleMainWin - ������ ���� ����� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadMapToGrayScaleTiff(HMAP map,HMESSAGE handle,
                                               DFRAME * dframe, long scale, long resolution,
                                               const char* tiffName, HMESSAGE handleMainWin);

_PICIMP long int _PICAPI LoadMapToGrayScaleTiffUn(HMAP Map,HMESSAGE Handle,
                                               DFRAME * dframe, long scale, long resolution,
                                               const WCHAR* tiffName, HMESSAGE handleMainWin);

//========================================================================
//    ��������� ����� � ������� BMP
//    map        - ���������� ��������� ���������, ����������� ���������, ��������� � ��. ������;
//    handle       - ������ ����������� ������������� �������� ���������.
//    dframe       - �������� ����������� �����(� ������ �� ���������)
//    bitcount     - ���-�� ��� �� ������ ������������ �����������(16,24,32)
//    scale        - ������� ������������ �����������
//    resolution   - ����������� ����������� ������������ �����������(�/�)
//    bmpname      - ��� ����� ������������ ����������� (*.bmp);
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ��������� ����� � ������� EMF
//    map          - ���������� ��������� ���������, ����������� ���������, ��������� � ��. ������;
//    handle       - ������ ����������� ������������� �������� ���������.
//    rectmetr     - �������� ����������� �����(� ������ �� ���������)
//    bitcount = 24 - ���-�� ��� �� ������ ������������ �����������
//    scale        - ������� ������������ �����������
//    resolution   - ����������� ����������� ������������ �����������(�/�)
//    emfname      - ��� ����� ������������ ����������� (*.emf);
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// ��������� ����� � ��������� ������� CMYK � RGB (BMP, ...)
// � ����� ���������� ����� � ������
//
//  parm   - ��������� ���������� �����������
//
//  ������� ����������� ������������� �������� ��������� ����������
//  ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
// (��� ������ ��������� ������������ ����� 60 �� ����������� ������)
//========================================================================
_PICIMP long int _PICAPI LoadMapToRasterForPrint(SAVEASPICTRPARM_FOR_PRINT* parm);

//========================================================================
// ��������� ����� � ��������� ������� CMYK (BMP, ...)
//
//  map    - ���������� ��������� ���������, ����������� ���������, ��������� ������;
//  handle - ������ ����������� ������������� �������� ���������
//  rect   - ������� ����������� ����� (� ��������)
//  parm   - �������������� ��������� ����������� (��. pictrapi.h)
//
//  ������� ����������� ������������� �������� ��������� ����������
//  ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//========================================================================
_PICIMP long int _PICAPI LoadMapToRasterCMYK(HMAP map, HMESSAGE handle,
                                            RECT* rect,
                                            SAVEASPICTRPARM* parm);


//========================================================================
// ������� ����������� ����� � �������� � �������� �������� �� �����
// (������� ����������� ������ ��� ��������� Windows)
//    handle         - ������ ����������� ������������� �������� ���������.
//    map            - ���������� ��������� ���������, ����������� ���������,
//                     ��������� � ��. ������;
//    name           - ��� ���������
//    ��������� METAFILEBUILDPARMEX ������� � maptype.h
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ � ���������� ���������� ����
//========================================================================
_PICIMP long int _PICAPI PaintToEmfByFrame(HMESSAGE handle, HMAP hMap,
                                          const char * name,
                                          METAFILEBUILDPARMEX * parm);

_PICIMP long int _PICAPI PaintToEmfByFrameUn(HMESSAGE handle, HMAP hMap,
                                          const WCHAR * name,
                                          METAFILEBUILDPARMEX * parm);

//#endif // LINUXAPI


//========================================================================
//    �������������� ���� ��������� ����� � ��������� ������� �����������
//    handle         - ������ ����������� ������������� �������� ���������.
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ���������������� ��������� �����
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     1 - �������� ������ LZW
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������,
//                         �� �������� � �������, ������������ ������
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    �������������� ���� ��������� ����� � ��������� ������� �����������
//    handle         - ������ ����������� ������������� �������� ���������.
//    map            - ���������� ��������� ���������, ����������� ����� name
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ���������������� ��������� �����
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     1 - �������� ������ LZW
//                     2 - �������� ������ JPEG (��� 24 ������ �������)
//    jpegCompressValue - ������� ������ ����������� ������ �� ��������� JPEG   // 04/12/11
//                        ����� ��������, ���� compressnumber ��������� �������� 2
//                        (1-100, 1-������������ ������, 100-������ ��� ������ ��������),
//                         ������������� �������� 60.
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������
//     �������� �������� ��������� ������ ��� ������� ����������� ��
//     ����� ������ (����� flagborder == 1).
//    ��� ������ ���������� ����
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
//    �������������� ���� ��������� ����� � ��������� ������� ����������� �
//    ��������� ����������� ����� ������
//    handle         - ������ ����������� ������������� �������� ���������.
//    map            - ���������� ��������� ���������, ����������� ����� name
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ���������������� ��������� �����
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     1 - �������� ������ LZW
//                     2 - �������� ������ JPEG (��� 24 ������ �������)
//    jpegCompressValue - ������� ������ ����������� ������ �� ��������� JPEG
//                        ����� ��������, ���� compressnumber ��������� �������� 2
//                        (1-100, 1-������������ ������, 100-������ ��� ������ ��������),
//                         ������������� �������� 60.
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         �� �������� � �������, ������������ ������
//    flagSaveCopy   - ���� ���������� ����� ��������� ����� � ������ *.~rw
//                     0 - �� ��������� ����� ��������� �����
//                     1 - ������� ����� ��������� �����
// flag_CreateDuplicate- ���� �������� ����������� ����� ������
//                     0 - �� ��������� ����������� ����� ������
//                     1 - ��������� ����������� ����� ������
// flag              - �� ������������. ������ ���� ����� 0.
//
//     �������� �������� ��������� ������ ��� ������� ����������� ��
//     ����� ������ (����� flagborder == 1).
//    ��� ������ ���������� ����
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
//                       ���������� �������    // 04/06/13
//    �������������� ���� ��������� ����� � ��������� ������� �����������
//    handle         - ������ ����������� ������������� �������� ���������.
//    map            - ���������� ��������� ���������, ����������� ����� name
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ���������������� ��������� �����
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     1 - �������� ������ LZW
//                     2 - �������� ������ JPEG (��� 24 ������ �������)
//    jpegCompressValue - ������� ������ ����������� ������ �� ��������� JPEG
//                        ����� ��������, ���� compressnumber ��������� �������� 2
//                        (1-100, 1-������������ ������, 100-������ ��� ������ ��������),
//                         ������������� �������� 60.
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������
//     �������� �������� ��������� ������ ��� ������� ����������� ��
//     ����� ������ (����� flagborder == 1).
//    ��� ������ ���������� ����
//========================================================================
_PICIMP long int _PICAPI LoadRstOptimizationEx1(HMESSAGE handle, HMAP hMap,
                                       const char* name, const char* newname,
                                       long int compressnumber, long int jpegCompressValue,
                                       long int flagborder);

//========================================================================  // 28/10/03
//    �������������� ���� ��������� ����� � ��������� ������� �����������
//    handle         - ������ ����������� ������������� �������� ���������.
//    hMap           - ���������� ��������� ���������, ����������� ����� name
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ���������������� ��������� �����
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     1 - �������� ������ LZW
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������
//     �������� �������� ��������� ������ ��� ������� ����������� ��
//     ����� ������ (����� flagborder == 1).
//    ��� ������ ���������� ����
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
//    �������������� ���� ��������� ����� � ��������� ������� �����������
//    handle         - ������ ����������� ������������� �������� ���������.
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ���������������� ��������� �����
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     32 - �������� ������ �������
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    �������������� ���� ��������� ����� � ��������� ������� �����������
//    handle         - ������ ����������� ������������� �������� ���������.
//    hMap           - ���������� ��������� ���������, ����������� ������� name
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ���������������� ��������� �����
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     32 - �������� ������ �������
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������
//     �������� �������� ��������� ��������� ����� ��� ������� ����������� ��
//     ����� ��������� ����� (����� flagborder == 1).
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    �������������� ���� ������� ����� � ��������� ������� ����������� �
//    ��������� ����������� ����� �����������
//    handle         - ������ ����������� ������������� �������� ���������.
//    hMap           - ���������� ��������� ���������, ����������� ����� name
//    name           - ��� ����� ������� �����
//    newname        - ��� ����� ���������������� ������� �����
//    compressnumber - ����� ��������� ������ ������
//                     0 - �� ������������ ������
//                     32 - �������� ������ �������
//    flagborder     - ���� ������������� ����� ������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         �� �������� � �������, ������������ ������
// flag_CreateDuplicate- ���� �������� ����������� �����
//                     0 - �� ��������� ����������� �����
//                     1 - ��������� ����������� �����
// flag              - �� ������������. ������ ���� ����� 0.
//
//     �������� �������� ��������� ������� ����� ��� ������� ����������� ��
//     ����� ������� ����� (����� flagborder == 1).
//    ��� ������ ���������� ����
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
//    �������������� ���� ������� �������� MTQ � ��������� ������� ����������� �
//    ��������� ����������� ����� �����������
//
//    ��������: ������ ����� ���� ��������� � �������� � �������� �������� � 4 �����
//
//    handle         - ������ ����������� ������������� �������� ���������.
//    map            - �����,���������� ��������� ������;
//    name           - ��� ����� ������� �������� MTQ
//    newname        - ��� ����� ���������������� ������� �������� MTQ
//    compressnumber - ����� ��������� ������ ������
//                     0 - �� ������������ ������
//                     32 - �������� ������ �������
//    flagborder     - ���� ������������� ����� ������� �������� MTQ
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         �� �������� � �������, ������������ ������
// flag_CreateDuplicate- ���� �������� ����������� �����
//                     0 - �� ��������� ����������� �����
//                     1 - ��������� ����������� �����
// flag              - �� ������������. ������ ���� ����� 0.
//
//     �������� �������� ��������� ������� �������� MTQ ��� ������� ����������� ��
//     ����� ������� �������� MTQ (����� flagborder == 1).
//    ��� ������ ���������� ����
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
//    �������������� ���� ������� �������� MTQ � ��������� ������� �����������
//
//    ��������: ������ ����� ���� ��������� � �������� � �������� �������� � 4 �����
//
//    map            - �����,���������� ��������� ������;
//    handle         - ������ ����������� ������������� �������� ���������.
//    name           - ��� ����� ������� ��������
//    newname        - ��� ����� ���������������� ������� ��������
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     32 - �������� ������ ������� ��������
//    flagborder     - ���� ������������� ����� ������� ��������
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������
//     �������� �������� ��������� ������� �������� ��� ������� ����������� ��
//     ����� ������� �������� (����� flagborder == 1).
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    �������������� ���� ������� �������� MTQ � ��������� ������� �����������
//
//    ��������: ������ ����� ���� ��������� � �������� � �������� �������� � 4 �����
//
//    handle         - ������ ����������� ������������� �������� ���������.
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ���������������� ��������� �����
//    compressnumber - ����� ��������� ������ ������ �����������
//                     0 - �� ������������ ������
//                     32 - �������� ������ �������
//    flagborder     - ���� ������������� ����� ��������� �����
//                     0 - �������� � ����������� ���� ��� ����� �����������
//                     1 - �� �������� � ����������� ���� ����� �����������
//                         ���������� � �������, ������������ ������
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    �������� ����������� ������� �� ������������� �������, �������� � ������
//    map           - �����, ���������� ��������� ������;
//    handle        - ������ ����������� ������������� �������� ���������.
//    rstInputName  - ��� ����� �������;
//    rstOutputName - ��� ����� ����������� �������;
//    frame         - �������� ���������� ������������� �������(� ������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
//    ������� ��������� �����
//
//    handle         - ������ ����������� ������������� �������� ���������.
//    hmap           - ������������� �������� ��������� �����
//    name           - ��� ����� ��������� �����
//    newname        - ��� ����� ��������� ����� � ���������� ������������
//    mirrortype     - ��� ���������
//                     (0- ��������� ����������� ����������� ��������� �����
//                           ����������� ������������ ��� )
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstMirror(HMESSAGE handle, HMAP map,
                                    const char* name, const char* newname,
                                    long int mirrortype);

_PICIMP long int _PICAPI LoadRstMirrorUn(HMESSAGE handle, HMAP map,                // 20/06/14
                                    const WCHAR* name, const WCHAR* newname,
                                    long int mirrortype);

//======================================================================== 
//    ��������� ����������� ����������� ����� ��������� ����� ��� ��������������� �����
//    map           - �����, ���������� ��������� ������;
//    handle        - ������ ����������� ������������� �������� ���������.
//    rstInputName  - ��� ����� ��������� �����;
//    rstOutputName - ��� ����� ����������� ��������� �����;
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
//========================================================================
_PICIMP long int _PICAPI LoadRstDuplicateAs (HMAP map, HMESSAGE handle,
                                            const char * rstInputName,
                                            const char * rstOutputName);



//========================================================================
//    ������� ������ ������ ����� NullPoint �� ���� Angle      // 17/05/05
//
//    map        - �����,���������� ��������� ������;
//    RstNumber  - ����� ��������� ������ � ������� �������
//    NameRstIn  - ��� ��������� ������;
//    NameRstOut - ��� ��������� ������;
//    NullPoint  - ���������� ����� �������� � ��������� ������;
//    Angle      - ���� �������� (� ��������);
//    handle     - ������ ����������� ������������� �������� ���������.
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
//    ������� ������ ������ ����� NullPoint �� ���� Angle        // 17/05/05
//
//    map        - �����,���������� ��������� ������;
//    RstNumber  - ����� ��������� ������ � ������� �������
//    NameRstIn  - ��� ��������� ������;
//    NameRstOut - ��� ��������� ������;
//    NullPoint  - ���������� ����� �������� � ������ �� ���������;
//    Angle      - ���� �������� (� ��������);
//    handle     - ������ ����������� ������������� �������� ���������.
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
// �������� ������ � ���������������� �� ���� ������
// ��������: �������� ��������� �������� ���� �� ����� �������� ������� �� X � �� Y
//
// �����:
// ���� ������� ������� �� X � �� Y ���������� ���� �� �����, �� � �����
// ��������������� ������  1.04 (0x0104).
// ������ ������ 1.04 ����������� � �� �������� � 11-�� ������.
//
// hMap        - �����, ���������� ��������� ������;
// rswName     - ��� ����� ������
// pointMet1   - ���������� ������ �����  � ������
// pointMet1   - ���������� ������ ����� � ������
// pointMet2   - ���������� ������ �����  � ������
// pointMet2   - ���������� ������ ����� � ������
// message     - ���� �� ������ ��������� (0\1)
// ��� ������ ���������� ����
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
// �������� ������ � ���������������� �� ���� ������
// ��������: ��������������� ���������� ������ ������� �� X � �� Y
//
// hMap        - �����, ���������� ��������� ������;
// rswName     - ��� ����� ������
// pointMet1   - ���������� ������ �����  � ������
// pointMet1   - ���������� ������ ����� � ������
// pointMet2   - ���������� ������ �����  � ������
// pointMet2   - ���������� ������ ����� � ������
// message     - ���� �� ������ ��������� (0\1)
// ��� ������ ���������� ����
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
// �������� ������ � ���������������� � ��������� �� ���� ������  // 15/09/05
// hmap          - ������������� �����, � ������� ����������� �����
// handle        - ������������� ���� ������� ��� ��������� ��������� � ���� ��������
// rswname       - ���� � ����� ������, ������� ����������������
// pointmet1     - �������� ���������� ������ ����� � ������
// pointmetnew1  - �������� ���������� ������ ����� � ������
// pointmet2     - �������� ���������� ������ ����� � ������
// pointmet2     - �������� ���������� ������ ����� � ������
// message       - ���� �� ������ ��������� (0\1) � �������� �����������������
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//       WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����
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
// �������� ������ � ���������������� � ��������� �� ���� ������          // 10/03/06
//
// hmap        - �����, ���������� ��������� ������;
// handle      - ������ ����������� ������������� �������� ���������.
// rswnamein   - ��� ��������� ����� ������
// rswNameOut  - ��� ��������� ����� ������ (������ ������ �.�. �� ����� MAX_PATH_LONG ����)
// pointmet1   - ���������� ������ �����  � ������
// pointmet1   - ���������� ������ ����� � ������
// pointmet2   - ���������� ������ �����  � ������
// pointmet2   - ���������� ������ ����� � ������
// message     - ���� �� ������ ��������� (0\1)
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//       WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����
//========================================================================
_PICIMP long int _PICAPI AttachRswWithScalingAndRotationEx(HMAP hmap, HMESSAGE handle,
                                             const char* rswnamein, char* rswnameout,
                                             DOUBLEPOINT *pointmet1, DOUBLEPOINT *pointmetnew1,
                                             DOUBLEPOINT *pointmet2, DOUBLEPOINT *pointmetnew2,
                                             int message);

// sizeNameIn  - ������ ������ rswName � ������
// sizeNameOut - ������ ������ rswNameOut � ������
_PICIMP long int _PICAPI AttachRswWithScalingAndRotationExUn(HMAP hmap, HMESSAGE handle,
                                             const WCHAR* rswName, int sizeNameIn,
                                             WCHAR* rswNameOut, int sizeNameOut,
                                             DOUBLEPOINT *pointmet1, DOUBLEPOINT *pointmetnew1,
                                             DOUBLEPOINT *pointmet2, DOUBLEPOINT *pointmetnew2,
                                             int message);

//==============================================================================
//    ����������������� ������                                       // 08/02/07
// (���������� ������������� ��������� ��������� ������� ���������� ���������)
//
//   handle    - ������ ����������� ������������� �������� ���������;
//   map       - �����,���������� ��������� ������;
//   parm      - ��������� ���������� ������;
//   namein    - ��� ��������� ������ (MAX_PATH_LONG)
//   nameout   - ��� ��������� ������ (������ ���������� ������ �.�. �� ����� MAX_PATH_LONG ��������)
//   fact      - �������� ���������� �����;
//   teor      - �������� ���������� �����;
//   count     - ���������� ������� ����� (�� ������ 4-�).
//
//   ������� ����������� ������������� �������� ��������� ���������� ���������:
//   -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//      WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����,
//==============================================================================
_PICIMP long int _PICAPI RswTransformingBySquareMethod(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm, const char * namein, char * nameout,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);

//   sizeNameOut - ������ ���������� ������ ��� nameout � ������
_PICIMP long int _PICAPI RswTransformingBySquareMethodUn(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm,
                           const WCHAR * namein,
                           WCHAR * nameout, int sizeNameOut,
                           long int count,DOUBLEPOINT * fact,DOUBLEPOINT * teor);


//==============================================================================
//   ����������������� ������ �� ����� ����� �����                            // 06/06/11
//
//   handle    - ������ ����������� ������������� �������� ���������;
//   map       - �����,���������� ��������� ������;
//   parm      - ��������� ���������� ������;
//   namein    - ��� ��������� ������;
//   nameout   - ��� ��������� ������;
//   fact      - �������� ���������� �����;
//   teor      - �������� ���������� �����;
//   count     - ���������� ������� ����� (�� ������ 4-�).
//
//   ������� ����������� ������������� �������� ��������� ���������� ���������:
//   -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//      WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����,
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
//   ����������������� ������ �� ����� ����� �����     // 21/06/11
//   (���������� �����������������)
//   handle    - ������ ����������� ������������� �������� ���������;
//   map       - �����,���������� ��������� ������;
//   parm      - ��������� ���������� ������;
//   namein    - ��� ��������� ������;
//   nameout   - ��� ��������� ������;
//   fact      - �������� ���������� �����;
//   teor      - �������� ���������� �����;
//   count     - ���������� ������� ����� (�� ������ 4-�).
//   flagBorder- 0 - ���������� ����� ������ �� ������������� ����������� (�������� - �� ����� ��������������� �����)
//               1 - ���������� ����� ������ �� ������������� ��������� ��������� ������
//               ���� �������� ����� ������������ �� �����, flagBorder ������������.
//               ����� ���������������� � ��������������� � �������� �����.
//   colorTransparent  - ��������� �� �������������� ����
//               (���� colorTransparent != 0, �� � �������� ����� ���� ������������ ���� �� colorTransparent.
//                ����������� ����� colorTransparent �����������)
//
//   ������� ����������� ������������� �������� ��������� ���������� ���������:
//   -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//      WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����,
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
//   ����������������� ������ �� ����� ����� �����     // 29/04/13
//   (���������� �����������������)
//   handle    - ������ ����������� ������������� �������� ���������;
//   map       - �����,���������� ��������� ������;
//   parm      - ��������� ���������� ������;
//   namein    - ��� ��������� ������;
//   nameout   - ��� ��������� ������;
//   fact      - �������� ���������� �����;
//   teor      - �������� ���������� �����;
//   count     - ���������� ������� ����� (�� ������ 4-�).
//   colorTransparent  - ��������� �� �������������� ����
//                       (���� colorTransparent != 0, �� � �������� ����� ����
//                        ������������ ���� �� colorTransparent.
//                        ����������� ����� colorTransparent �����������)
//   flagCutting    - ���� ������� ����������� ��������� ������ �� ����� ������.
//                    �������� ����� ����������� �� �������� ��� ������������� ����� � ����� (��. flagBorder)
//   flagDuplicate  - ���� �������� ����������� ����� ����������� ��������� ������ (0/1)
//   flagBorderNew  - 0 - �� ������������� ����� ��������� ������
//                    1 - ���������� ����� ��������� ������ �� ������������� �����������
//                        (�������� - �� ������� <����� ��������������� ����� �����>) /
//                    2 - ���������� ����� ��������� ������ �� ����� ��������� �����.
//                        ���� � �������� ������ ����� �� �����������, �� ����� �����������
//                        ����� ������ �� ������������� ��������� ��������� ������
//                    3 - ���������� ����� ��������� ������ �� ������������� ��������� ��������� ������
//
//   ������� ����������� ������������� �������� ��������� ���������� ���������:
//   -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//      WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����,
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
// �������������� ������ � �������� ��������                           // 11/05/06
//
//   handle  - ������ ����������� ������������� �������� ���������.
//   namein  - ��� ��������� ������;
//   nameout - ��� ��������� ������;
//   mapreg  - ����� ��������� � ������� � �������� ��������
//             (�������� ��������� MAPREGISTEREX �� � mapcreate.h);
//
//   ������� ����������� ������������� �������� ��������� ���������� ���������:
//   -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//      WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����,
// ��� ������ ������������ �������� picexGetLastError() (���� ������ ��. maperr.rh)
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
// �������������� ������ � �������� ��������
//
//   handle  - ������ ����������� ������������� �������� ���������.
//   namein  - ��� ��������� ������;
//   nameout - ��� ��������� ������;
//   mapreg  - ����� ��������� � ������� � �������� ��������
//             (�������� ��������� MAPREGISTEREX �� � mapcreate.h);
//   datum   - ��������� ��������� ������������� ��������� � ��������� ����������
//             �� ��������� WGS-84 (����� ���� ����),
//   ellparam - ��������� ����������������� ���������� (����� ���� ����).
//   ttype    - ��� ���������� �������������� ��������� (��. TRANSFORMTYPE � mapcreat.h) ��� 0
//   tparm    - ��������� ���������� �������������� ��������� (��. mapcreat.h)
//   ������� ����������� ������������� �������� ��������� ���������� ���������:
//   -  (WM_PROGRESSBAR) ��������� �� ��������� ��������� ��������
//      WPARAM - ������� ��������� �������� � ��������� (0% - 100%)
//      ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
// ��� ������ ���������� ����,
// ��� ������ ������������ �������� picexGetLastError() (���� ������ ��. maperr.rh)
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
// ���������� ��� ��������� ������ (���� ������ ��. maperr.rh)     // 16/05/06
// � ������ ���������� ������ ���������� ����
//================================================================================
_PICIMP long int _PICAPI picexGetLastError();


//================================================================================
// ������� GIF-���� � ����������� � ������
//   palette    - ��������� �� �������
//   colorcount - ����� ������ ������� (�� 2 �� 256)
//   width      - ������ ����������� (�� 1 �� 65535)
//   height     - ������ ����������� (�� 1 �� 65535)
//   in         - ��������� �� ������� ������
//   sizein     - ������ ������� ������ (� ������)
//   out        - ��������� �� �������� �����
//   sizeout    - ������ ��������� ������ (� ������)
//                (����������� ������ = sizein + 1000)
// ���������� ������ ������, ����������� GIF-���� (� ������)
// ��� ������ ���������� 0
//================================================================================
// ������� ������ ������ ��������� 8-������ ����������� � ����������
// ������������� ����� (������-����) ��� ������ ������������ � ������.
// � �������� ������� ������ ����� ���� ������������ �����������
// �����, ���������� ��� ������ ������� mapPaintToImage (mapapi.h)
//================================================================================
_PICIMP long int _PICAPI picexCreateGif(RGBQUAD* palette, int colorcount,
                                       int width, int height,
                                       unsigned char* in, int sizein,
                                       unsigned char* out, int sizeout);

//================================================================================
// ������� GIF-���� � ����������� �� �����
//   name       - ��� GIF-�����
//   palette    - ��������� �� �������
//   colorcount - ����� ������ ������� (�� 2 �� 256)
//   width      - ������ ����������� (�� 1 �� 65535)
//   height     - ������ ����������� (�� 1 �� 65535)
//   in         - ��������� �� ������� ������
//   sizein     - ������ ������� ������ (� ������)
// ���������� ������ GIF-����� (� ������)
// ��� ������ ���������� 0
//================================================================================
// ������� ������ ������ ��������� 8-������ ����������� � ����������
// ������������� ����� (������-����) ��� ������ ������������ � ������.
// � �������� ������� ������ ����� ���� ������������ �����������
// �����, ���������� ��� ������ ������� mapPaintToImage (mapapi.h)
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
// �������� ����������� � ������� RGBA(��� �������� OpenGL) �� BMP-�����
//          c �������� (������ � ������ �� ����� 512 � ������ ������� 2)
//    ����: nameBmp - ��� ��������� Bmp-�����;
//            image - ����� ������� ������ ����������� �����������;
//             size - ������ ���� ������� � ������;
//      reth � retv - ������ � ������ ����������� �����������;
//        sizeimage - ����������� ������ �������� ������ �������, �����������
//                    ��� ������ ����������� �����������.
//    ������������ ��������:
//         0 - � ������ ������ (��� ��� �������� ������ ��� �����������
//             ����������� ��. sizeimage);
//         1 - � ������ ��������� ��������� �����������.
//========================================================================
_PICIMP long int _PICAPI LoadBmpToImage32WithCut(const char* bmpname,
                             const char* image, long int size,
                             long int &reth,long int &retw, long int &sizeimage);

_PICIMP long int _PICAPI LoadBmpToImage32WithCutUn(const WCHAR* bmpname,        // 03/02/14
                             const char* image, long int size,
                             long int &reth,long int &retw, long int &sizeimage);

//========================================================================
// �������� ����������� �� ������ � BMP-����
//    ����: nameBmp - ��� ����������� Bmp-�����;
//            image - ����� ������� � ������������ ��� ������;
//   width � height - ������ � ������ �����������;
//      elementsize - ������ �������� ����������� (� �����).
//    ������������ ��������:
//         0 - � ������ ������;
//         1 - � ������ ��������� ��������� Bmp-����� �����������.
//========================================================================
_PICIMP long int _PICAPI LoadImageToBmp(const char* bmpname, const char* image,
                                       long width, long height, long elementsize);

_PICIMP long int _PICAPI LoadImageToBmpUn(const WCHAR* bmpname, const char* image,    // 03/02/14
                                         long width, long height, long elementsize);


//==============================================================================
// ���������� ���������� ����� ���������������� �� ����� JPEG
// ����������
// map     - �����,���������� ��������� ������
// handle  - ������ ����������� ������������� �������� ���������.
// parm    - ��������� ���������� ������
// namein  - ��� ����� JPEG
// b,l     - ���������� ����� ���������������� (����������� ��������)
// height  - ������ ����� ���������������� (����������� ��������)
// mapreg  - ����� ��������� � ������� � �������� �������� (����������� ��������)
//           (�������� ��������� MAPREGISTEREX �� � mapcreate.h)
// ellipsoid - ��������� ���������� (����������� ��������)
// datum   - ��������� ��������� ������������� ��������� � ��������� ����������
//           �� ��������� WGS-84, ��� ��������� ����� ���������������� (����������� ��������)
// ����������: 1 - � ������ ��������� ����������� ��������� ����� ����������������
//            -1 - ��������� ����� namein �� ����������� ������� JPEG
//            -2 - � ����� namein ����������� ������ APP1, ��������������� ��� �������� ����������
//            -3 - � ����� namein ������ ������ APP1, �� ���������� ����� ���������������� �� ����������
//
// ��� ������ ���������� ����
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
// ���������� ��������� ����� JPEG � ������ EXIF
// map     - �����,���������� ��������� ������
// handle  - ������ ����������� ������������� �������� ���������.
// parm    - ��������� ���������� ������
// namein  - ��� ����� JPEG
// exifParam-��������� �� ��������� EXIFPARAM (��������� ����������� ��������)
// ����������: 1 - � ������ ��������� ����������� ��������� ����� ����������������
//            -1 - ��������� ����� namein �� ����������� ������� JPEG
//            -2 - � ����� namein ����������� ������ APP1, ��������������� ��� �������� ����������
//            -3 - � ����� namein ������ ������ APP1, �� ���������� ����� ���������������� �� ����������
//
// ��� ������ ���������� ����
//==============================================================================
_PICIMP long int _PICAPI LoadJpegExifParameters(HMAP map,HMESSAGE handle,
                           TASKPARMEX * parm, const char * namein,
                           EXIFPARAM* exifParam);

_PICIMP long int _PICAPI LoadJpegExifParametersUn(HMAP map,HMESSAGE handle,      // 18/09/14
                           TASKPARMEX * parm, const WCHAR * namein,
                           EXIFPARAM* exifParam);

//========================================================================  06/05/12
// ��������� ���������� ����������� �� ������ �������� TIFF(GeoTIFF), BMP, PCX, JPEG
// name - ��� ����� (*.tif;*.bmp;*.pcx;*.jpg)
// precisionByWidth  - ��������� �� ���������� �� ����������� (����������� ��������)
// precisionByHeight - ��������� �� ���������� �� ��������� (����������� ��������)
// �������� ���������� ��������� � �������� ��������� precisionByWidth �
//                     precisionByHeight � ������ �� ����
// flagMessage       - ���� ������ ��������� MessageBox ����������
// ������� ���������� ��������� ��������:
//   1 - ���������� ����������� ���������� � �������� � �������� ��������� precisionByWidth � precisionByHeight
//  -1 - ���������� ����������� � ����� ���������� �� �������
// ��� ������ ���������� 0
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
// ��������� ��������� ������ (�������) - ���������� ��������� �����������,
// ������� �������, ��� EPSG
// fileName        - ��� ����� (RSW, MTW, MTL, MTQ, BMP, TIFF, IMG, PNG, GIF)
// points          - ��������� �� ������ �� 4-� ����� (����������� ��������
//                   ������������ ��������� ����������� � �������� WGS-84)
// countPoint      - ���������� ��������� �������, ������������ �� ������ points
//                   (�������� ������ ���� ����� 4)
// meterInElementX - ��������� ��� ������ �������� ������� �������� �� X
//                   ��� ����������� ������ � �������� ����������� �����, ��� �
//                   ����� �������� ���������� ����������� ������� ��������� ����
// meterInElementY - ��������� ��� ������ �������� ������� �������� �� Y
//                   ��� ����������� ������ � �������� ����������� �����, ��� �
//                   ����� �������� ���������� ����������� ������� ��������� ����
// codeEPSG        - ��������� ��� ������ �������� ���� EPSG
//
//    ��� ������ ���������� ����
//========================================================================
_PICIMP long int _PICAPI picexGetImageInfoByNameUn(const WCHAR * fileName,
                               DOUBLEPOINT* points, long int countPoint,
                               double* meterInElementX, double* meterInElementY,
                               long int * codeEPSG);

//========================================================================
// ��������� ������ � �������� ������ (�������)
// fileName        - ��� ����� (RSW, MTW, MTL, MTQ, BMP, TIFF, IMG, PNG, GIF)
// mapregister - ����� ��������� MAPREGISTEREX.
// ��������a MAPREGISTEREX ������a � mapcreat.h
// ellipsoidparam - ����� ���������, � ������� ����� ���������
// ��������� ����������
// ��������a ELLIPSOIDPARAM ������a � mapcreat.h
// datumparam - ����� ���������, � ������� ����� ���������
// ������������ ����������������� ������������� ���������
// ��������a DATUMPARAM ������a � mapcreat.h
//
//    ��� ������ ���������� ����
//========================================================================
_PICIMP long int _PICAPI picexGetImageProjectionDataByNameUn(const WCHAR * fileName,
                                                 MAPREGISTEREX* mapregister,
                                                 ELLIPSOIDPARAM *ellipsoidparam,
                                                 DATUMPARAM *datumparam);

//========================================================================
// ������� ������� �������� ����������� ������(RSW, TIFF, JPEG, IMG, PNG, GIF, BMP, PCX)
// � �������(MTW, MTL, MTQ)  � ���������� ��� � ���� �������� (RSW, TIFF, JPEG, BMP, PNG).
// ������� ��������� ����������� - 24 ��� �� �������.
// handle - ������ ����������� ������������� �������� ���������
// inputFileName   - ��� �������� �����
// outputFileName  - ��� ��������� ����� ��������� �����������
// width � height  - ������� ��������� �����������
// messageEnable   - ���� ������ ��������� MessageBox ����������
// ��� ������ ���������� ����
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
// ������ ��������� ������ � ���� RSW
// handle - ������ ����������� ������������� �������� ���������
// srcname        - ��� �������� ����� (TIF, IMG, PNG, GIF, JPG, BMP, PCX)
// rstname        - ��� ��������� ����� (*.rsw)
// retcode        - ��� ��������
// ��������� ������� ���������� ��������:
//   1. ���������� ��������������� ����� ������ TIF, IMG
//   2. ���� �������� world.file
//   3. ���� �������� TAB (MapInfo)
// ������� ���� ���� �������� ����� � �������� ������ srcname,
// ��������� �� ���������� ���� ������.
// ��� ������ ���������� ����
//========================================================================
_PICIMP long int _PICAPI picexLoadRasterToRswUn(HMESSAGE handle,
                                                const WCHAR* srcname,
                                                const WCHAR* rstname,
                                                long int * retcode);

//========================================================================
// ��������� ��� ����� �������� �� ����������� ����� ������������ �����
// ������������ ��� ����� ���������� � ����������� �� ������� ������������ �����
// � ���� ����� ��������
// type              - ��� ����� ��������
// �������� ��������� type:
//        1 - ���� �������� world file
//        2 - TAB (MapInfo)
//        3 - MAP (OziExplorer)
//        4 - INI            - ���������� ������
//        5 - tpf (FOTOPLAN) - ���������� ������
//        6 - pln (TALKA)    - ���������� ������
// graphicName       - ��� ������������ �����
// locationFilesName - ��������� ��� ���������� ��������������� ����� ����� ��������
// size              - ������ ������ � ������ ������ locationFilesName (�� ����� MAX_PATH_LONG)
//========================================================================
_PICIMP long int _PICAPI picexMakeLocationFileName(long int type,
                                                const WCHAR *graphicName,
                                                WCHAR *locationFilesName, int size);

//========================================================================
// ��������� ���������� � ����������� �����
//========================================================================
_PICIMP long int _PICAPI picexGetFileInformationUn(const WCHAR* inputName,
                                                DATAINFORMATION* information);

//========================================================================
// ������ � ������ ����� �������� World File
// inputName  - ��� ������������ �����
// rstIniName - ��� ����� �������� World File
//
// locationPoint   - �������� ������
// meterInElementX - ������ �������� �� X
// meterInElementY - ������ �������� �� Y
//
// rasterPoint - ����� ������, ����� �������, ������ �������, ������ ������
// countPoint  - 4

// rasterPointTr - LT,RT,RB,LB;  ������ �����������, ���� flagTransformation == 1
// countPointTr  - 4,
// flagTransformation - ���� ����������������� �� ����������� rasterPointTr
//
// flagWorldFile_CoordinateInGradus - ���� ������ ��������� � ��������
// retCode - ��� ������� ������
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
// ������ � ������ ����� ��������� *.tab (MapInfo)
// inputName         - ��� ������������ �����
// rstIniName        - ��� ����� �������� *.tab
// mapreg            - ��������� ������� ��������� � ��������
// datum             - ��������� ��������� � ���������� ������� ������� ���������
//                     � WGS-84
// ellipsoid         - ��������� ����������������� ���������� ��� �������
//                     ������� ���������
// flagMapRegisterEx - ���� ���������� ���������� �������� �� ����� TAB
// locationPoint     - �������� ������
// meterInElementX   - ������ �������� �� X
// meterInElementY   - ������ �������� �� Y
//
// rasterPoint - ����� ������, ����� �������, ������ �������, ������ ������
// countPoint  - 4
//
// rasterPointTr - LT,RT,RB,LB;  ������ �����������, ���� flagTransformation == 1
// countPointTr  - 4,
// flagTransformation - ���� ����������������� �� ����������� rasterPointTr
//
// retCode - ��� ������� ������
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
//  ���������� ���������� ����� �� ������������� �������� �����
//  double A_coeff = 0;   // ������� ������ �� ��� X; ������ ������� �� ��� X (�������� � 1 ������� ������ - 20 ������)
//  double B_coeff = 0;   // ������� ������ �� ��� Y; ������������� ������ ������� �� ��� Y
//  double C_coeff = 0;   // ��������� �������� (������ ����� ����)
//  double D_coeff = 0;   // ��������� �������� (������ ����� ����)
//  double E_coeff = 0;   // ��������� ������; X,Y ���������� ������ �������� ������ �������
//  double F_coeff = 0;   // ��������� ������; X,Y ���������� ������ �������� ������ �������
// x1 = Ax + �y + E
// y1 = Dx + By + F
// x,y - �������� �������� ���������� ������ (x - �������, y - ���).
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
// ���������� �� �� ������ �������� ������� MapInfo �� ����� TAB
// stringIn      - ������ c ������� �������� ������� MapInfo �� ����� TAB (������� �������� )
//                 CoordSys Earth Projection 8, 104, "m", 21, 0, 0.9996, 500000, 0
//                 ������ �������� ������ �� ����� TAB - 8, 104, 7, 21, 0, 0.9996, 500000, 0
// stringOut     - ������, ��� ���������� �������� �������� (�������� �������� )
// sizeStringOut - ������ ������ stringOut � ������
// mapregOut     - ��������� ��� ���������� ����������� �������� (�������� �������� )
// ellipsoidOut  - ��������� ��� ���������� ����������� ����������
// datumOut      - ��������� ��� ���������� �������������� ����������������� ������������� ���������
// codeEPSG      - ��� EPSG
// retCode       - ��� ��������
//                           1 - �������� ��������� ���������
//                           0 - �������� ��������� �� ���������
// ��� ������ ������� ���������� 0
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
// ������ ������ � Gdal
//========================================================================
_PICIMP long int _PICAPI picexInitGdal();

//========================================================================
// ��������� ������ � Gdal
//========================================================================
_PICIMP long int _PICAPI picexCloseGdal();

//========================================================================
//    ��������� ��������� �� �� ����� ���������� GDAL
//    name - ��� ����� (*.img;*.png;*.gif...)
//    geoTIFFparam - ��������� ����������� ���������
//========================================================================
_PICIMP long int _PICAPI picexLoadGdalGeoParametersUn(HMESSAGE handle,
                                                  const WCHAR  * name,
                                                  GEOTIFFPARAM * geoTIFFparam);

//========================================================================
// ��������� ��������� ���������� ����������� ����������� ���������� GDAL
// fileName     - ��� ����� ����������� �������� (IMG, PNG, GIF)
// information -  ��������� �� ��������� DATAINFORMATION
//                ��� ������ ���������� ������������ �����
// ��������� DATAINFORMATION ������� � picexprm.h
//
// ������� ������������� �������� ����� �������
// ����������� ������������ ����� � Rsw ��� ������������� ������� �������������
// ��� ������ ���������� 0
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
// ��������� ��������� MAPREGISTEREX, ELLIPSOIDPARAM, DATUMPARAM, GEOTIFFPARAM �� ������
// ������������������ ���������� ����������� ���������� GDAL
// flagGeoSupported - ��������� ������ ������� TTranslate.SetProjection �� ��������
//                    ������������� ���������� ��������
// flag_CoordInDegre- ���������� �������� � �������� ? (0-�����, 1-�������)
// ��� ������ ���������� 0
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
// �������� ��������� ������ ����������� ���������� GDAL
// �������������� ����� ����������� �������� (IMG, PNG, GIF)
//    Map - �����,���������� ��������� ������
//    inputname - ��� ������������ �����
//    rstname   - ��� RST-�����
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point     - ����� �������� ������ (� ������)
//                (��������� ���-��������� ���� ������ � ������)
//    Handle - ������ ����������� ������������� �������� ���������.
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//    flagMessage - ���� ������ ���������
//                          (��� ==1, ��������� ������ MessageBox;
//                           ��� == 0, ���������� ��������� ������� WM_ERROR)
//    flagWorkLog - ���� ������� �������
//                          (��� ==1, ����������� ������� �������
//                           ��� == 0, �� ����������� ������� �������)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ���������� ��������� ������ ����������� ���������� GDAL � ���������� RSW
// �������������� ����� ����������� �������� (TIFF, IMG, PNG, GIF)
// GDAL ��������� ����� ����� ��� �������������, 8 ��� �� �����
//    handle      - ���������� ������� ����������� ������������� �������� ���������.
//    parm        - ��������� �� ��������� TASKPARM
//    inputname   - ��� ������������ ����������� �����
//    rstname     - ��� ����������� ����� RSW
//    meterInElementX - ������ � ������ �������� �� X
//    meterInElementY - ������ � ������ �������� �� Y
//    point       - ����� �������� ������ (� ������)
//                  (��������� ���-��������� ���� ������ � ������)
//    palette     - ������� ������
//    paletteCount- ���������� ������ � ������� (��� ����������� ����� RSW �.�. 2)
//    compression - ���� ������������� ������ ��� ������������ RST-����� (0/1)
//                  0 - ������ � ������ ����������� ����������� �� �����
//                  1 - ����� �.�. ����� �� ������ LZW
//                  ����� JPEG ����������
//    flagMessage - ���� ������ ���������
//                  (��� ==1, ��������� ������ MessageBox;
//                   ��� == 0, ���������� ��������� ������� WM_ERROR)
//    flagWorkLog - ���� ������� �������
//                  (��� ==1, ����������� ������� �������
//                   ��� == 0, �� ����������� ������� �������)
//    flagIgnoreGeoTiff - (0/1)
//                  (0 - �������� � �� ��������������� � �������� �����
//                   1 - �������� � �� �� ��������������� � �������� �����)
//    ��� ������ ���������� ����
//
//    ������� ����������� ������������� �������� ��������� ����������
//    ���������:
//    -  (WM_PROGRESSBAR) ��������� �� ��������� �������� ��������
//       WPARAM - ������� �������� �������� � ��������� (0% - 100%)
//       ���� �������-������ ���������� WM_PROGRESSBAR, �� ������� �����������.
//
//    -  (WM_ERROR) ��������� �� ������
//       LPARAM - ��������� �� ��������� ERRORINFORMATION
//       ��������� ERRORINFORMATION ������� � picexprm.h,
//       WM_PROGRESSBAR � WM_ERROR - � maptype.h
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
// �������� ����������� � ������� RGBA(��� �������� OpenGL) �� PNG-�����
//          c �������� (������ � ������ ������ ���� �������� 2)
//    ����: namePng - ��� ��������� PNG-�����
//            image - ����� ������� ������ ����������� �����������;
//             size - ������ ���� ������� � ������;
//      reth � retv - ������ � ������ ����������� �����������;
//        sizeimage - ����������� ������ �������� ������ �������, �����������
//                    ��� ������ ����������� �����������;
//    ������������ ��������:
//         0 - � ������ ������ (��� ��� �������� ������ ��� �����������
//             ����������� ��. sizeimage);
//         1 - � ������ ��������� ��������� �����������.
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
// ������� ������� ���� RSW (������ 24 �/�) �� �����������
// �������� ������������ �����
// ������� ������� ��� ����������� ���������������� ���� "PreView" ��������� "���� ������ ��"
// �������� � ��������� �������� ����������� � �������� �����.
// ������� ����������� ��������� �����(������ � ������) ���������� �������
// � ���������� width � height
// �� ���� ������� ����� ���������� ����� ��������� ��������:
//    BMP (*.bmp), TIFF (*.tif), JPEG (*.jpg), Jpeg2000 (*.jp2), MrSID (*.sid),
//    NITF (*.ntf), Imagine (*.img), PNG (*.png), GIF (*.gif)
//
// �������� ������ �������:
// ������� �������� ������� "�������" �������� ����������� ���������� GDAL �
// �������������� � ���������� (width, height) ����������� ��������.
// ���� � �������� ����� ��� ���������� �������� �����������, �� GDAL ����� ��
// ��������� ������� "�������" �������� �����������. � ����� ������, �����������
// ��������� �������� ����������� �� ��������� ����� (�������� ������� -
// ����������� width, height) � ����������� � ���� RSW.
// "�������" �������� ����������� ��������� ���������� GDAL � ���� *.ovr.
//
// �������� ������� ���������� �������:
// handle - ������ ����������� ������������� �������� ���������
// inputFileName   - ��� �������� �����
// outputFileName  - ��� ��������� ����� (*.rsw)
// width           - ������ � �������� ����������� ��������� �����
// height          - ������ � �������� ����������� ��������� �����
// messageEnable   - ���� ����� ��������� MessageBox
// ����������: 1 - � ������ ��������� �������� ��������� �����
// ��� ������ ���������� ����
//========================================================================
_PICIMP long int _PICAPI picexPaintImageDataToRswUn(HMESSAGE handle,
                                            const WCHAR * inputname,
                                            const WCHAR * rstname,
                                            long int width, long int height,
                                            long int flagMessage);

//========================================================================
// ���������� ����� � JPEG
// ������� ��������� ���������� ����� filenameSource � JPEG-���� filenameOutput
// handle         - ������ ����������� ������������� ��������
// filenameSource - ��� ��������� ����� (BMP, TIFF)
// filenameOutput - ��� ��������� ����� JPEG
// quality        - ����������� �������� �����������, ������� �� ������ JPEG
//========================================================================
_PICIMP long int _PICAPI picexCreateCopyJpegUn(HMESSAGE handle,
                                            const WCHAR *filenameSource,
                                            const WCHAR *filenameOutput,
                                            int quality);

//-----------------------------------------------------------------------------
// ���������� ����� � PNG
// ������� ��������� ���������� ����� filenameSource � PNG-���� filenameOutput
// handle         - ������ ����������� ������������� ��������
// filenameSource - ��� ��������� ����� (BMP, TIFF)
// filenameOutput - ��� ��������� ����� PNG
//-----------------------------------------------------------------------------
_PICIMP long int _PICAPI picexCreateCopyPngUn(HMESSAGE handle,
                                            const WCHAR *filenameSource,
                                            const WCHAR *filenameOutput);

//========================================================================
// ��������� ����������� 24-� ������� ������ RSW � ���� PNG                     
// Handle              - ������ ����������� ������������� �������� ���������.
// rswName             - ��� ����� 24-� ������� ������ RSW
// pngName             - ��� ����� PNG
//========================================================================
_PICIMP long int _PICAPI picexSaveRswToPngUn(HMESSAGE handle,
                                             const WCHAR* rswName,
                                             const WCHAR* pngName);                                                           

//-----------------------------------------------------------------------------
// ������� "�������� ������ �� ������� IMG"
// hmap         - ���������� ��������� ���������
// handle       - ������ ����������� ������������� ��������
// inputnameW   - ��� ��������� ����� IMG
// outputnameW  - ��� ��������� ����� MTW
// scale        - ����������� �������� ����������� �������
// flagCompress - ���� ������ ������ ������� �����
//-----------------------------------------------------------------------------
_PICIMP long int _PICAPI picexLoadIMGToMtwUn(HMAP hmap, HMESSAGE handle,
                                            const WCHAR* inputnameW,
                                            const WCHAR* outputnameW,
                                            double scale, long int flagCompress);


}       // extern "C"


#endif  // MAPPICEX_H


