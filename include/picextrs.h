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
*            �������� ������� ��������� ������                     *
*        ��������� ��� �������� �� ������ C, PASCAL, BASIC         *
*                                                                  *
*******************************************************************/
#if !defined(PICEXTRS_H)
#define PICEXTRS_H

#ifndef MACPICEX_H
  #include "macpicex.h"
#endif

#ifndef PICEXPRM_H
  #include "picexprm.h"  // 27/06/14  ��������� ��� ������ shptomap.dll
#endif  


#define WM_RSTROTATE        0x500       // ������� ������
#define RSTTRANS_DIAL       0x501       // ����� ������� ������-� ������
#define RSTTRANS_NEWPARM    0x502       // ���������� ���������� ���.������
#define RSTTRANS_END        0x503       // ���������� ������

#ifdef WIN32API                  // 18/06/02
   #define HMESSAGE HWND
#else
   #define HMESSAGE MSGHANDLER
#endif


extern "C"
{
#if defined(_M_X64) || defined(BUILD_DLL64)       // 31/05/13
 typedef __int64   HTFCR;    // ������������� �������� �������� TIFF
#else
 typedef long int  HTFCR;    // ������������� �������� �������� TIFF
#endif

 // *********************************************************
 // ����� ������� �������� �������� TIFF:
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


 //    ��������� ����������� ������ � ����� ������� TIFF  (�����������)
 //    handle     - ������ ����������� ������������� �������� ���������.
 //    tiffname   - ��� TIFF-�����;
 //    width      - ������ ����������� � ��������
 //    height     - ������ ����������� � ��������
 //    nbits      - ������ ������� (��� �� �������)
 //    palette    - ����� ��������������� �������
 //                 ���� palette == 0, � colorcount != 0, �� �������� ����������
 //                 ������� ����� �������� Load_SetTiffPalette()
 //    colorcount - ����� ��������� � ����� �������
 //    precision  - ���������� ����������� (����� �� ����)
 //    platform - ��� ��������� (0 - INTEL, 1 - MOTOROLA)             (������������� �������� - 0)
 //    compressMethod - ���� ������ ����������� (0- �� ��������� ������, 1 - ������ PackBit) (������������� �������� - 0)
 //    flagCMYK - ����� �������� ������:
 //                     0 - �������� ������ RGB 24 ��� �� ������
 //                     1 - �������� ������ CMYK 32 ��� �� ������
 //                     ����� �������������� ������ ���  ������� 24,32 ��� �� ������.
 //    flagIntergraphTIFF - ���� ������ ������� ����������������� ��� ����������� TIFF ��� ������������� � Intergraph // 28/09/05
 //                     ����� �������������� ������ ���  ������� 1 ��� �� ������.
 //    dframe           - �������� ����������� � ������ � ������ ��� ������ ������� ����������������� ��� ����������� TIFF  // 28/09/05
 //                     ����� �������������� ������ ���  ������� 1 ��� �� ������.
 //    ���������� ������������� �������� �������� TIFF
 //    ��� ������ ���������� 0
 //    ������� ����������� ������������� �������� ��������� ����������
 //    ���������:
 //    -  (WM_ERROR) ��������� �� ������
 //       LPARAM - ��������� �� ��������� ERRORINFORMATION
 //       ��������� ERRORINFORMATION ������� � picexprm.h, WM_ERROR - � maptype.h
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

 // flagSetRegister - ���� ��������� �������� ��������� ��������� // 12/10/07
 // mapReg          - ��������� �������� // 12/10/07
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
                                          long int flagSetRegister,     // ���� ��������� �������� ��������� ���������
                                          MAPREGISTEREX *mapReg);       // ��������� ��������

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
                                          long int flagSetRegister,     // ���� ��������� �������� ��������� ���������
                                          MAPREGISTEREX *mapReg);       // ��������� ��������


 //    ��������� ����������� ������ � ����� ������� TIFF GrayScale (��������� GrayScale ��� �.�. ����.) // 09/03/07
 //    �������� ������ - GrayScale, 8 ��� �� ������
 //    tiffname - ��� TIFF-�����;
 //    width      - ������ ����������� � ��������
 //    height     - ������ ����������� � ��������
 //    nbits      - ������ ������� (��� �� �������)
 //    precision  - ���������� ����������� (����� �� ����)
 // flagSetRegister - ���� ��������� �������� ����������� � �������� ��������� ��������� // 12/10/07
 //    dframe     - �������� ����������� � ������ � ������      // 17/10/07
 //    mapReg     - ��������� �������� // 12/10/07
 //    ���������� ������������� �������� �������� TIFF
 //    ��� ������ ���������� 0
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

 //    ��������� ���������� ������� (����� �����������)
 //    ��� ������ ���������� 0
long int _MAPAPI picexGetTiffStripCount(HTFCR hTiffCreate);

 //    ��������� ���������� ����� ����������� � ������
 //    ��� ������ ���������� 0
long int _MAPAPI picexGetTiffStringCountByStrip(HTFCR hTiffCreate);

 //    �������� ����� � ������� numberStrip � ����
 //    ��� ������ ����� ���������� ������, �� ����������� ����������
 //    ��������� � ������ ������� ������-����
 //    ���� flagCompress == 1, ����� ������������ ������ �� ������ PackBit
 //    ��� ������ ���������� 0
long int _MAPAPI picexPutTiffStrip(HTFCR hTiffCreate, long int numberStrip,
                                           char*bits, long int sizeBits);

 //    �������� ����� � ������� numberStrip � ����   // 06/02/04
 //    �������� ������ ����������� - CMYK(flagCMYK = 1),  32 ��� �� ������ (nbits = 32)
 //    ����� �������� ���������������(�� �� ����������).
 //    ��� ������ ����� ���������� ������, �� ����������� ����������
 //    ��������� � ������ ������� ������-����
 //    ���� flagCompress == 1, ����� ������������ ������ �� ������ PackBit
 //    numberStrip - ������� � ����
 //    ��� ������ ���������� 0
long int _MAPAPI picexPutTiffStrip_CMYK(HTFCR hTiffCreate, long int numberStrip,
                                                 char*bitsCMYK, long int sizeBitsCMYK);

 // �������� ������� � ����
 // ��� ����������� � 4 � 8 ��� �� ������
 //    ��� ������ ���������� 0
long int _MAPAPI picexSetTiffPalette(HTFCR hTiffCreate, COLORREF* palette,
                                                             long int colorCount);

 // �������� ��������� � ���������� ���� � ����
 // ��� ������ ���������� 0
long int _MAPAPI picexSaveTiffFile(HTFCR hTiffCreate);


 // ������������ ������ (����������)
 // ��� ������ ���������� 0
long int _MAPAPI picexFreeTFCRProcess(HTFCR hTiffCreate);

 // ����������� �������� ����������� � ������ ����� ������  // 10/07/03
 // rect - �� ������ rect ������������ �������� ����� ������ � ��������� ������
 // ��� ������ ���������� ����
long int _MAPAPI picexSizeImageDefinition(HMAP hMap, long int rstNumber, RECT* rect);


//---------------------------------------------------------------------------
// ������� ������ ����� TIFF-����� � ��������� ���� *.tls
// handle   - ������ ����������� ������������� �������� ���������.
// TifName  - ��� TIF-�����;
// FileName - ��� ����� *.tls;
//---------------------------------------------------------------------------
long int _MAPAPI picexSaveTiffTagsIntoFile(HMESSAGE Handle,
                                                  const char * TiffName,
                                                  const char * FileName);

long int _MAPAPI picexSaveTiffTagsIntoFileUn(HMESSAGE Handle,            // 18/06/14
                                                  const WCHAR * TiffName,
                                                  const WCHAR * FileName);

//---------------------------------------------------------------------------
// ������� ���������� � ���������� �� ����� GeoTiff � ��������� ����
//---------------------------------------------------------------------------
// handle   - ������ ����������� ������������� �������� ���������.
// TifName  - ��� TIF-�����;
// FileName - ��� ����� *.tls;
long int _MAPAPI picexSaveGeoTiffParamInFile(HMESSAGE Handle,
                                                    const char * TiffName,
                                                    const char * FileName);

long int _MAPAPI picexSaveGeoTiffParamInFileUn(HMESSAGE Handle,          // 18/06/14
                                                    const WCHAR * TiffName,
                                                    const WCHAR * FileName);

//---------------------------------------------------------------------------
// ��������� ��������� MAPREGISTEREX, ELLIPSOIDPARAM, DATUMPARAM �� ������
// ������������������ ���������� �� ��������� GEOTIFFPARAM
// flagGeoSupported - ��������� ������ ������� TTranslate.SetProjection �� �������
// ������������� ���������� ��������
// ��� ������ ���������� 0
//---------------------------------------------------------------------------
long int _MAPAPI picexFillMapRegisterExByStructure(GEOTIFFPARAM* geoParam,
                                                           MAPREGISTEREX *mapreg,
                                                           ELLIPSOIDPARAM *ellipsoid,
                                                           DATUMPARAM *datum,
                                                           int* flagGeoSupported);


//==============================================================================
// ������� ���� RSW (TIF,BMP,JPG) (������ 24 �/�) �� ����������� �������� �����
// ������� ����������� ��������� �����(������ � ������) ���������� ������� � ���������� width � height
// �� ���� ������� ����� ���������� ����� RSW, MTW, MTQ, MTL, TIFF
// handle - ������ ����������� ������������� �������� ���������
// inputFileName   - ��� �������� ����� (*.rsw,*.mtw, TIF)
// outputFileName  - ��� ��������� ����� (*.rsw)
// width           - ������ � �������� ����������� ��������� ����� (*.rsw)
// height          - ������ � �������� ����������� ��������� ����� (*.rsw)
// messageEnable   - ��� ����� ��������� MessageBox
// ����������: 1 - � ������ ��������� �������� ��������� ����� (*.rsw)
// ��� ������ ���������� ����
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
//    ��������� ��������� ������� � ����   
//    Map - �����,���������� ��������� ������;
//    BmpName - ��� BMP-�����;
//    Handle - ������ ����������� ������������� �������� ���������.
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
