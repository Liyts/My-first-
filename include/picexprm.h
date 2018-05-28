/****** PICEXPRM.H ************* Shabakov D.A.   ****** 09/08/16 ***
******* PICEXPRM.H ************* ������ �.�.     ****** 18/09/13 ***
*                                                                  *
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2016              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*                  FOR  WINDOWS95 & WINDOWS NT                     *
*                                                                  *
********************************************************************
*                                                                  *
*      �������� ��������� ���������� ��������������� ������        *
*                                                                  *
*******************************************************************/

#ifndef PICEXPRM_H
#define PICEXPRM_H

#include "maptype.h"

#define WM_PCX2RST               0x590       // ���������  PCX � RST
#define WM_PCX2RST_PROGRESS      0x591
#define WM_PCX2RST_ERROR         0x592

#define WM_RSTCOMPRESS           0x593       // ������ ������
#define WM_RSTCOMPRESS_ERROR     0x594

// ��������� ��� �������� ���������� � ����������� ������ ������� �� ����������
typedef struct DATAINFORMATION
{
       unsigned int InputFileLength ;  // ����� ����� ������������ �����������
       int      Width           ;  // ������ �����������
       int      Height          ;  // ������ �����������
       int      BitPerPixel     ;  // ���-�� ��� �� ������
       double   Precision       ;  // ����������� ����������� ����������� (�\�)
       char PaletteType[4]      ;  // ���������� ����. ������      // 25/10/04

       int      BlockCount      ;  // ���-�� ������ � ������
       double   RswFileLength   ;  // ������������� ����� ����� *.rsw
       char CompressImage[16]   ;  // ������ �����������  // 26/01/01
}
       DATAINFORMATION;


// ��������� ��� �������� ���������� � GeoTIFF-������
typedef struct GEOTIFFINFORMATION   // 20/03/03
{
        unsigned int StructSize;  // ����� ���������
        unsigned int TypeCS;      // ��� ������������ �������

        unsigned int Spheroid;    // ���������
        unsigned int Datum;       // ������������� ����
        unsigned int PrimeMeridian;//������ ��������

        unsigned int Projection;  // ��������
        unsigned int Zone;        // ����� ����

        unsigned int Units;       // ������� ��������� ����� (�����, ������� ...)

        DFRAME FrameImage;             // �������� ����������� � ������
        double UnitsInElement_X;       // ������ �������� � �������� ��������� �� ��� X
        double UnitsInElement_Y;       // ������ �������� � �������� ��������� �� ��� Y
        double UnitsInElement_Z;       // ������ �������� � �������� ��������� �� ��� Z
        char Information[256]  ;       // ���������� � ��������, ����� ��������� � �.�.
        double PrecisionInch;          // ����������� ����������� ����������� (�\�) // 01/11/05
        double PrecisionMet;           // ����������� ����������� ����������� (�\�) // 01/11/05
        unsigned int UnitsAngular;// ������� ��������� ����� (�������, ������� ...)  // 28/03/06

        unsigned int RswWidth;    // ������ ������������ ����� (��� ������������� ������� �����������������)  // 28/05/10
        unsigned int RswHeight;   // ������ ������������ ����� (��� ������������� ������� �����������������)  // 28/05/10
#if defined(_M_X64) || defined(BUILD_DLL64)       // 05/12/13
        int     GeoTiffInformationZero;       // ������������
#endif
        char Reserv[236];
}
        GEOTIFFINFORMATION;


typedef struct TAG_SORTINT                     // 20/01/11
{
  short int   Value;     // �������� ����                                       // 2
  short int   Flag;      // ���� ������� ���� � �����                           // 2
#if defined(_M_X64) || defined(BUILD_DLL64)       // 05/12/13
        int   TagSortZero;       // ������������
#endif
} TAG_SORTINT;                                                                  //---4

typedef struct TAG_DOUBLE                      // 20/01/11
{
  double      ValueDouble;// �������� ����                                      // 8      // 22/01/13
  short int   Flag;      // ���� ������� ���� � �����                           // 2
#if defined(_M_X64) || defined(BUILD_DLL64)       // 05/12/13
  short int   TagDoubleZero[3];       // ������������
#endif
} TAG_DOUBLE;                                                                   //---10


typedef struct GEOTIFFPARAM                    // 19/01/11
{
    // ������ ������ ���������
    long int    Length;                                                         // 4
#if defined(_M_X64) || defined(BUILD_DLL64)       // 05/12/13
    int         GeoTiffParamZero;       // ������������
#endif
    TAG_SORTINT GTModelTypeGeoKey;                                              // 4
    TAG_SORTINT GTRasterTypeGeoKey;                                             // 4

// Geographic CS Parameter GeoKeys
    TAG_SORTINT GeographicTypeGeoKey;                                           // 4
    TAG_SORTINT GeogGeodeticDatumGeoKey;                                        // 4
    TAG_SORTINT GeogPrimeMeridianGeoKey;                                        // 4
    TAG_SORTINT GeogLinearUnitsGeoKey;                                          // 4
    TAG_DOUBLE  GeogLinearUnitSizeGeoKey;  // Units: meters                     // 10
    TAG_SORTINT GeogAngularUnitsGeoKey;                                         // 4
    TAG_DOUBLE  GeogAngularUnitSizeGeoKey; // Units: radians                    // 10
    TAG_SORTINT GeogEllipsoidGeoKey;                                            // 4
    TAG_DOUBLE  GeogSemiMajorAxisGeoKey;   // Units: Geocentric CS Linear Units // 10
    TAG_DOUBLE  GeogSemiMinorAxisGeoKey;   // Units: Geocentric CS Linear Units // 10
    TAG_DOUBLE  GeogInvFlatteningGeoKey;   // Units: none                       // 10
    TAG_SORTINT GeogAzimuthUnitsGeoKey;                                         // 4
    TAG_DOUBLE  GeogPrimeMeridianLongGeoKey; // Units =  GeogAngularUnits       // 10

// Projected CS Parameter GeoKeys
    TAG_SORTINT ProjectedCSTypeGeoKey;                                          // 4

// Projection Definition GeoKeys
    TAG_SORTINT ProjectionGeoKey;                                               // 4
    TAG_SORTINT ProjCoordTransGeoKey;                                           // 4
    TAG_SORTINT ProjLinearUnitsGeoKey;                                          // 4
    TAG_DOUBLE  ProjLinearUnitSizeGeoKey;  // Units: meters                     // 10
    TAG_DOUBLE  ProjStdParallelGeoKey;     // Units: GeogAngularUnit            // 10
    TAG_DOUBLE  ProjStdParallel2GeoKey;    // Units: GeogAngularUnit            // 10
    TAG_DOUBLE  ProjOriginLongGeoKey;      // Units: GeogAngularUnit            // 10
    TAG_DOUBLE  ProjOriginLatGeoKey;       // Units: GeogAngularUnit            // 10
    TAG_DOUBLE  ProjFalseEastingGeoKey;    // Units: ProjLinearUnit             // 10
    TAG_DOUBLE  ProjFalseNorthingGeoKey;   // Units: ProjLinearUnit             // 10
    TAG_DOUBLE  ProjFalseOriginLongGeoKey; // Units: GeogAngularUnit            // 10
    TAG_DOUBLE  ProjFalseOriginLatGeoKey;  // Units: GeogAngularUnit            // 10
    TAG_DOUBLE  ProjFalseOriginEastingGeoKey; // Units: ProjLinearUnit          // 10
    TAG_DOUBLE  ProjFalseOriginNorthingGeoKey;// Units: ProjLinearUnit          // 10
    TAG_DOUBLE  ProjCenterLongGeoKey;      // Units: GeogAngularUnit            // 10
    TAG_DOUBLE  ProjCenterLatGeoKey;       // Units: GeogAngularUnit            // 10
    TAG_DOUBLE  ProjCenterEastingGeoKey;   // Units: ProjLinearUnit             // 10
    TAG_DOUBLE  ProjCenterNorthingGeoKey;  // Units: ProjLinearUnit             // 10
    TAG_DOUBLE  ProjScaleAtOriginGeoKey;   // Units: none                       // 10
    TAG_DOUBLE  ProjScaleAtCenterGeoKey;   // Units: none                       // 10
    TAG_DOUBLE  ProjAzimuthAngleGeoKey;    // Units: GeogAzimuthUnit            // 10
    TAG_DOUBLE  ProjStraightVertPoleLongGeoKey; // Units: GeogAngularUnit       // 10

// Vertical CS Parameter Keys
    TAG_SORTINT VerticalCSTypeGeoKey;                                           // 4
    TAG_SORTINT VerticalDatumGeoKey;                                            // 4
    TAG_SORTINT VerticalUnitsGeoKey;                                            // 4

    // TAG_MODELPIXELSCALE 33550 // ������ ����� ������ �� X,Y,Z                // 02/04/11
    // ModelPixelScaleTag = (ScaleX, ScaleY, ScaleZ)
    double ModelPixelScaleTag[3];                                               // 24
    short int Flag_ModelPixelScaleTag;      // ���� ������� ���� � �����        // 2
#if defined(_M_X64) || defined(BUILD_DLL64)       // 05/12/13
    short int GeoTiffParam1Zero[3];       // ������������
#endif
    // TAG_MODELTIEPOINT   33922 // �������� ����� ������                       // 02/04/11
    // ModelTiepointTag = (...,I,J,K, X,Y,Z...), ������ �������� (I,J,K, X,Y,Z) 6 ��������
    double ModelTiepointTag[1024];                                              // 8192
    short int Flag_ModelTiepointTag;        // ���� ������� ���� � �����        // 2
                                            // ���� ��� TAG_MODELTIEPOINT � ����� �����������, �� Flag_ModelTiepointTag = 0
                                            // ���� ��� TAG_MODELTIEPOINT � ����� ����, �� � Flag_ModelTiepointTag ������������ ���������� �������� ���� double
#if defined(_M_X64) || defined(BUILD_DLL64)       // 05/12/13
    short int GeoTiffParam2Zero[3];       // ������������
#endif
    // TAG_MODELTRANSFORMATION       33920  // ������� ����������������� ������ // 02/04/11
    // TAG_MODELTRANSFORMATION_34264 34264  // ������� ����������������� ������
    double ModelTransformationTag[16];                                          // 128
    short int Flag_ModelTransformationTag;  // ���� ������� ������� ����������������� � �����        // 2
                                            // � Flag_ModelTransformationTag ����� ������������ ��������� ��������:
                                            // 0 - ������� ����������������� � ����� �����������
                                            // 1 - ������ ModelTransformationTag �������� ������� ����������������� �� ���� 33920(TAG_MODELTRANSFORMATION)        // 16/08/13
                                            // 2 - ������ ModelTransformationTag �������� ������� ����������������� �� ���� 34264(TAG_MODELTRANSFORMATION_34264)  // 16/08/13

    /** Do we have any definition at all?  0 if no geokeys found */
    short int	Flag;  // ���� ���������� ���� �� ����� ���������               // 2
#if defined(_M_X64) || defined(BUILD_DLL64) // 05/12/13
          int GeoTiffParam3Zero;            // ������������
#endif

    // 05/03/12 �������� ����� (��������� �������� � WGS-84)7��.
    // KeyID = 2062; Type = 3/7 * DOUBLE; Values = dX, dY, dZ, Rx, Ry, Rz, dS
    double GeogTOWGS84GeoKey[7];                                                // 56       // 05/03/11
    short int Flag_GeogTOWGS84GeoKey;       // ���� ������� ���� � �����        // 2        // 05/03/11
                                            // ���� ��� GeogTOWGS84GeoKey � ����� �����������, �� Flag_GeogTOWGS84GeoKey = 0
                                            // ���� ��� GeogTOWGS84GeoKey � ����� ����, �� � Flag_GeogTOWGS84GeoKey ������������ ���������� �������� ���� double (3 ��� 7)

#if defined(_M_X64) || defined(BUILD_DLL64) // 05/12/13
    char        GeoTiffParam4Zero[6];       // ������������
#endif
    char        Reserv[8];    // 05/03/12


} GEOTIFFPARAM;


 // ��������� ��� �������� ��������� �� ������� ������� �� ����������
typedef struct ERRORINFORMATION
       {
       char * MessageR    ;  // ��������� �� ������ �� ������� �����
       char * MessageE    ;  // ��������� �� ������ �� ���������� �����
       }
           ERRORINFORMATION;

// ��� ��������� (0 - INTEL, 1 - MOTOROLA)    // 09/07/03
#define INTEL    0
#define MOTOROLA 1

// ��������� ����������� TIFF (0 - BLOCK, 1- STRIP, 2 - NONFRAG)
#define BLOCK    0
#define STRIP    1
#define NONFRAG  2


typedef struct FILENAMESETUP_PARM     
{
  int Length;          // ����� ���������

  int Mode;            // ����� ������������ �����(1-����� �� �������,
                                                 // 2-�� ������ �������
                                                 // 3-�� ����� ����� (0.L-37-01.*)
                                                 // 4-�� ���������
                                                 // 5-�� ����� ��������� ������
                                                 // 6-�� ����� ����� ��� �����, �������� (0L3701.*) 
  int BeginNumber;     // ��������� �����(����� ������������ �����: 1-����� �� �������)
  int SemanticNumber;  // ����� ���������(����� ������������ �����: 3-�� ���������)
  char Prefix[260];    // ������� ����� �����(����� ������������ �����: 1-����� �� �������
                       //                     ����� ������������ �����: 2-�� ������ �������)
  int MessageEnable;   // ���� ������ ��������� ����
  int WriteLogEnable;  // ���� ������� ������� SaveMap.log

  char        Reserv[260];
}
  FILENAMESETUP_PARM;

// ��������� ��� �������� ���������� � ����� JPEG � ������ EXIF     // 02/05/12
typedef struct EXIFPARAM
{
  int         Length                 ; // ������ ������ ���������               // 4

  // Indicates the version of GPSInfoIFD. The version is given as 2.2.0.0. This tag is mandatory when GPSInfo tag is
  // present. Note that the GPSVersionID tag is written as a different byte than the Exif Version tag.
  char GPSVersionID[MAX_PATH]; // 0 - GPSVersionID                              // 260
  short int Flag_GPSVersionID;                                                  // 2

  // Indicates the latitude.
  SIGNDEGREE GPSLatitude;                                                       // 16
  short int Flag_GPSLatitude;                                                   // 2

  // Indicates the longitude.
  SIGNDEGREE GPSLongitude;                                                      // 16
  short int Flag_GPSLongitude;                                                  // 2

  TAG_DOUBLE GPSAltitude;   // 6 - GPSAltitude                                  // 10

  // Indicates the time as UTC (Coordinated Universal Time). TimeStamp is expressed as three RATIONAL values
  // giving the hour, minute, and second.
  TAG_DOUBLE GPSTimeStamp_Hour;   // 7 - GPSTimeStamp                           // 10
  TAG_DOUBLE GPSTimeStamp_Minute; // 7 - GPSTimeStamp                           // 10
  TAG_DOUBLE GPSTimeStamp_Second; // 7 - GPSTimeStamp                           // 10

  // Indicates the GPS satellites used for measurements. This tag can be used to describe the number of satellites,
  // their ID number, angle of elevation, azimuth, SNR and other information in ASCII notation. The format is not
  // specified. If the GPS receiver is incapable of taking measurements, value of the tag shall be set to NULL.
  char GPSSatellites[MAX_PATH]; // 8 - GPSSatellites                            // 260
  short int Flag_GPSSatellites;                                                 // 2

  // Indicates the status of the GPS receiver when the image is recorded. 'A' means measurement is in progress, and
  // 'V' means the measurement is Interoperability.
  unsigned char GPSStatus[4]; // 9 - GPSStatus                                  // 4
  short int Flag_GPSStatus;                                                     // 2

  // Indicates the GPS measurement mode. '2' means two-dimensional measurement and '3' means three-dimensional
  // measurement is in progress.
  unsigned char GPSMeasureMode[4]; // 10 - GPSMeasureMode                       // 4
  short int Flag_GPSMeasureMode;                                                // 2

  // Indicates the GPS DOP (data degree of precision). An HDOP value is written during two-dimensional measurement,
  // and PDOP during three-dimensional measurement.
  TAG_DOUBLE GPSDOP; // 11 - GPSDOP                                             // 10

  // Indicates the unit used to express the GPS receiver speed of movement. 'K' 'M' and 'N' represents kilometers per
  // hour, miles per hour, and knots.
  // 'K' = Kilometers per hour
  // 'M' = Miles per hour
  // 'N' = Knots
  unsigned char GPSSpeedRef[4]; // 12                                           // 4
  short int Flag_GPSSpeedRef;                                                   // 2

  // Indicates the speed of GPS receiver movement.
  TAG_DOUBLE GPSSpeed; // 13                                                    // 10

  // Indicates the reference for giving the direction of GPS receiver movement. 'T' denotes true direction and 'M' is
  // magnetic direction.
  // 'T' = True direction
  // 'M' = Magnetic direction
  unsigned char GPSTrackRef[4]; // 14                                           // 4
  short int Flag_GPSTrackRef;                                                   // 2

  // Indicates the direction of GPS receiver movement. The range of values is from 0.00 to 359.99.
  TAG_DOUBLE GPSTrack; // 15                                                    // 10

  // Indicates the reference for giving the direction of the image when it is captured. 'T' denotes true direction and 'M' is
  // magnetic direction.
  // 'T' = True direction
  // 'M' = Magnetic direction
  unsigned char GPSImgDirectionRef[4]; // 16                                    // 4
  short int Flag_GPSImgDirectionRef;                                            // 2

  // Indicates the direction of the image when it was captured. The range of values is from 0.00 to 359.99.
  TAG_DOUBLE GPSImgDirection; // 17                                             // 10

  // Indicates the geodetic survey data used by the GPS receiver. If the survey data is restricted to Japan, the value of
  // this tag is 'TOKYO' or 'WGS-84'. If a GPS Info tag is recorded, it is strongly recommended that this tag be recorded.

  unsigned char GPSMapDatum[MAX_PATH]; // 18                                    // 260
  short int Flag_GPSMapDatum;                                                   // 2

  // GPSDestLatitudeRef 19 13 GPS Info extension - GPSDestLatitudeRef
  // Indicates whether the latitude of the destination point is north or south latitude.

  // Indicates the latitude of the destination point. The latitude is expressed as three RATIONAL values giving the
  // degrees, minutes, and seconds, respectively. If latitude is expressed as degrees, minutes and seconds, a typical
  // format would be dd/1,mm/1,ss/1. When degrees and minutes are used and, for example, fractions of minutes are
  // given up to two decimal places, the format would be dd/1,mmmm/100,0/1.
  SIGNDEGREE GPSDestLatitude; // 20                                             // 16
  short int Flag_GPSDestLatitude;                                               // 2

  //GPSDestLongitudeRef 21 15 GPS Info extension - GPSDestLongitudeRef

  // Indicates the longitude of the destination point.
  SIGNDEGREE GPSDestLongitude; // 22                                            // 16
  short int Flag_GPSDestLongitude;                                              // 2

  // Indicates the reference used for giving the bearing to the destination point. 'T' denotes true direction and 'M' is
  // magnetic direction.
  // 'T' = True direction
  // 'M' = Magnetic direction
  unsigned char GPSDestBearingRef[4]; // 23                                     // 4
  short int Flag_GPSDestBearingRef;                                             // 2

  // Indicates the bearing to the destination point. The range of values is from 0.00 to 359.99.
  TAG_DOUBLE GPSDestBearing; // 24                                              // 10

  // Indicates the unit used to express the distance to the destination point. 'K', 'M' and 'N' represent kilometers, miles
  // and knots.
  // 'K' = Kilometers
  // 'M' = Miles
  // 'N' = Knots
  unsigned char GPSDestDistanceRef[4]; // 25                                    // 4
  short int Flag_GPSDestDistanceRef;                                            // 2

  // Indicates the distance to the destination point.
  TAG_DOUBLE GPSDestDistance; // 26                                             // 10


  // A character string recording the name of the method used for location finding. The first byte indicates the character
  // code used (Table 6�Table 7), and this is followed by the name of the method. Since the Type is not ASCII, NULL
  // termination is not necessary.
  // GPSProcessingMethod  // 27 !!!

  // A character string recording the name of the GPS area. The first byte indicates the character code used (Table 6�
  // Table 7), and this is followed by the name of the GPS area. Since the Type is not ASCII, NULL termination is not
  // necessary.
  // GPSAreaInformation  // 28 !!!

  // A character string recording date and time information relative to UTC (Coordinated Universal Time). The
  // format is "YYYY:MM:DD." The length of the string is 11 bytes including NULL.
  unsigned char GPSDateStamp[MAX_PATH];  // 29                                  // 260
  short int Flag_GPSDateStamp;                                                  // 2

  // Indicates whether differential correction is applied to the GPS receiver.
  // 0 = Measurement without differential correction
  // 1 = Differential correction applied
  TAG_SORTINT GPSDifferential;                                                  // 4

  // The image orientation viewed in terms of rows and columns.
  // 1 = The 0th row is at the visual top of the image, and the 0th column is the visual left-hand side.
  // 2 = The 0th row is at the visual top of the image, and the 0th column is the visual right-hand side.
  // 3 = The 0th row is at the visual bottom of the image, and the 0th column is the visual right-hand side.
  // 4 = The 0th row is at the visual bottom of the image, and the 0th column is the visual left-hand side.
  // 5 = The 0th row is the visual left-hand side of the image, and the 0th column is the visual top.
  // 6 = The 0th row is the visual right-hand side of the image, and the 0th column is the visual top.
  // 7 = The 0th row is the visual right-hand side of the image, and the 0th column is the visual bottom.
  // 8 = The 0th row is the visual left-hand side of the image, and the 0th column is the visual bottom.
  TAG_SORTINT Orientation; // 274                                               // 4

  // The number of pixels per ResolutionUnit in the ImageWidth direction. When the image resolution is unknown, 72
  // [dpi] is designated.
  TAG_DOUBLE XResolution; // 282                                                // 10

  // Image resolution in height  direction
  TAG_DOUBLE YResolution; // 283                                                // 10

  // The unit for measuring XResolution and YResolution. The same unit is used for both XResolution and YResolution.
  // If the image resolution in unknown, 2 (inches) is designated.
  // 2 = inches
  // 3 = centimeters
  TAG_SORTINT ResolutionUnit; // 296                                            // 4

  // The date and time of image creation. In this standard it is the date and time the file was changed. The format is
  // "YYYY:MM:DD HH:MM:SS" with time shown in 24-hour format, and the date and time separated by one blank
  // character [20.H]. When the date and time are unknown, all the character spaces except colons (":") may be filled
  // with blank characters, or else the Interoperability field may be filled with blank characters. The character string
  // length is 20 bytes including NULL for termination. When the field is left blank, it is treated as unknown.
  unsigned char DateTime[MAX_PATH];  // 306                                     // 260
  short int Flag_DateTime;                                                      // 2

  // A character string giving the title of the image. It may be a comment such as "1988 company picnic" or the like.
  // Two-byte character codes cannot be used. When a 2-byte code is necessary, the Exif Private tag UserComment is
  // to be used.
  unsigned char ImageDescription[MAX_PATH];  // 270                             // 260
  short int Flag_ImageDescription;                                              // 2

  // The manufacturer of the recording equipment. This is the manufacturer of the DSC, scanner, video digitizer or other
  // equipment that generated the image. When the field is left blank, it is treated as unknown.
  unsigned char Make[MAX_PATH];  // 271                                         // 260
  short int Flag_Make;                                                          // 2

  // The model name or model number of the equipment. This is the model name of number of the DSC, scanner, video
  // digitizer or other equipment that generated the image. When the field is left blank, it is treated as unknown.
  unsigned char Model[MAX_PATH];  // 272                                        // 260
  short int Flag_Model;                                                         // 2

  // This tag records the name and version of the software or firmware of the camera or image input device used to
  // generate the image. The detailed format is not specified, but it is recommended that the example shown below be
  // followed. When the field is left blank, it is treated as unknown.
  // Ex.) "Exif Software Version 1.00a"
  unsigned char Software[MAX_PATH];  // 305                                     // 260
  short int Flag_Software;                                                      // 2

  // This tag records the name of the camera owner, photographer or image creator. The detailed format is not specified,
  // but it is recommended that the information be written as in the example below for ease of Interoperability. When the
  // field is left blank, it is treated as unknown.
  unsigned char Artist[MAX_PATH];  // 315                                       // 260
  short int Flag_Artist;                                                        // 2

  // Copyright information. In this standard the tag is used to indicate both the photographer and editor copyrights. It is
  // the copyright notice of the person or organization claiming rights to the image. The Interoperability copyright
  // statement including date and rights should be written in this field; e.g., "Copyright, John Smith, 19xx. All rights
  // reserved." In this standard the field records both the photographer and editor copyrights, with each recorded in a
  // separate part of the statement. When there is a clear distinction between the photographer and editor copyrights,
  // these are to be written in the order of photographer followed by editor copyright, separated by NULL (in this case,
  // since the statement also ends with a NULL, there are two NULL codes) (see example 1). When only the
  // photographer copyright is given, it is terminated by one NULL code (see example 2). When only the editor
  // copyright is given, the photographer copyright part consists of one space followed by a terminating NULL code,
  // then the editor copyright is given (see example 3). When the field is left blank, it is treated as unknown.
  // Ex. 1) When both the photographer copyright and editor copyright are given.
  // Photographer copyright + NULL[00.H] + editor copyright + NULL[00.H]
  // Ex. 2) When only the photographer copyright is given.
  // Photographer copyright + NULL[00.H]
  // Ex. 3) When only the editor copyright is given.
  // Space[20.H]+ NULL[00.H] + editor copyright + NULL[00.H]
  unsigned char Copyright[MAX_PATH];  //  33432                                 // 260
  short int Flag_Copyright;                                                     // 2

                                                                                // �����: 3114

  char Reserve[66];                                                             // 66

  short int	Flag;  // ���� ���������� ���� �� ����� ���������               // 2

}
  EXIFPARAM;                                                                    // 3200



typedef struct LOCATIONPOINT   // ���������� �����                              // 02/10/12
{
  DOUBLEPOINT pointMet;  // ���������� ����� � ������
  DOUBLEPOINT pointPic;  // ���������� ����� � ��������� ������
}
  LOCATIONPOINT;

#endif  //PICEXPRM_H
