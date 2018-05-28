/****** GRAPHAPI.H  ************ Borzov A.U.      ***** 22/12/14 ***
*                                                                  *
*              Copyright (c) PANORAMA Group 1991-2014              *
*                      All Rights Reserved                         *
*                                                                  *
********************************************************************
*                                                                  *
*           ИНТЕРФЕЙСНЫЕ ФУНКЦИИ ДОСТУПА К ГРАФУ СЕТИ              *
*              ИМПОРТИРУЮТСЯ ИЗ MAPACCES.DLL                       *
*                                                                  *
*******************************************************************/
#ifndef GraphApiH
#define GraphApiH

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

typedef HANDLE HNET;  // идентификатор графа
typedef HANDLE HPATH; // идентификатор маршрута
typedef HANDLE HDGR;  // идентификатор графа удаленности
typedef HANDLE HTSP;  // идентификатор задачи коммивояжера


#if defined(_NETDLLEXPORT)
 #ifdef LINUXAPI
  #define NETIMP
 #else
  #define NETIMP __declspec(dllexport)
 #endif
#else
 #ifdef LINUXAPI
  #define NETIMP
 #else 
  #define NETIMP __declspec(dllimport)
 #endif 
#endif

// Коды объектов карты графа
#define NODECODE       5558   // Excode узла
#define EDGECODE       5557   // Excode ребра
#define ONEWAYEDGECODE 5562   // Excode ребра одностороннего
#define PARENTLISTCODE 5555   // Excode рамки родительского листа

// Коды семантики 
#define SEMNETROADTYPE 1052   // Тип (класс) дороги

// Тип расчета кратчайшего пути, т.е. пути с минимальным суммарным весом ребер
#define SP_LENGTH        0 // по расстоянию - стоимость ребра равен длине ребра
#define SP_TIME          1 // по времени - стоимость ребра равен длине ребра, деленной на значение семантики
                           // "Скорость" (32817), "Скорость обратная" (32818)
                           // Если для ребра семантика не задана, то скорость принимается = 60 км/час
#define SP_SEMCOST       2 // по стоимости из семантики ребра "Стоимость ребра" (32819),
                           // "Стоимость ребра обратная" (32824)
                           // Если для ребра семантика не задана, то вес стоимость принимается = 1
#define SHORTPATHTYPEMIN 0
#define SHORTPATHTYPEMAX 2

// Параметры открытия карты графа
typedef struct OPENNETPARM
{
  HWND   Wnd;          // идентификатор окна, которому посылается сообщение WM_PROGRESSBAR
                       // с названием этапа и процентом обработки
                       // если 0, то сообщения не посылаются
  HMAP   ParentMap;    // документ, в котором открыты карты, по которым построен граф
                       // необходим для функции onGetPathParentEdgeSite
                       // если 0, то не используется
  char   Reserve[128];
}
  OPENNETPARM;

// Параметры построения кратчайшего маршрута
typedef struct PATHPARM
{
  DOUBLEPOINT Point1;       // координаты начала маршрута
                            // маршрут строится от ближайшей точки на узле или ребре
  DOUBLEPOINT Point2;       // координаты конца маршрута
                            // маршрут строится до ближайшей точки на узле или ребре
  HWND        Wnd;          // окно, которому посылается сообщение WM_PROGRESSBAR с процентом обработки
  int         NodeKey1;     // ключ узла, от которого строится маршрут
                            // если = 0, то маршрут строится между точками Point1-Point2
  int         NodeKey2;     // ключ узла, до которого строится маршрут
                            // если = 0, то маршрут строится между точками Point1-Point2
  int         IsWgs;        // координаты заданы не в системе координат карты графа в метрах,
                            // а явлются геодезическими координатами (широта, долгота)
                            // на эллипсоиде Wgs84 в радианах
  int         Type;         // тип расчета (SP_LENGTH, SP_SEMCOST, SP_TIME)
  int         IsUturn;      // разрешены развороты при построении маршрута
  int         UseRoadCount; // размер массива флагов разрешенных типов дорог
                            // (должен быть равен 0, если все дороги разрешены или
                            // onGetParentRoadTypeCount, если есть запрещенные)
  int        *UseRoads;     // массив флагов разрешенных типов дорог при построении маршрута
                            // (если = 0, то все дороги разрешены)
  HSELECT     UseSelect;    // разрешенные ребра (если = 0, то разрешены все ребра)
  HSELECT     BanSelect;    // запрещенные ребра (запрет имеет больший приоритет)
                            // если = 0, то нет запрещенных ребер

  char        Reserve[128];
}
  PATHPARM;

// Параметры построения графа удаленности (список ребер, находящихся на заданном расстоянии от узла)
typedef struct DISTGRAPHPARM
{
  double  Dist;         // расстояние (время, вес) на которое можно уехать из начального узла
  HWND    Wnd;          // окно, которому посылается сообщение WM_PROGRESSBAR с процентом обработки
  int     NodeKey;      // ключ узла, от которого строится граф удаленности
  int     Type;         // тип расчета (SP_LENGTH, SP_SEMCOST, SP_TIME)
  int     IsUturn;      // разрешены развороты
  int     UseRoadCount; // размер массива флагов разрешенных типов дорог
                        // (должен быть равен 0, если все дороги разрешены или
                        // onGetParentRoadTypeCount, если есть запрещенные)
  int    *UseRoads;     // массив флагов разрешенных типов дорог при построении маршрута
                        // (если = 0, то все дороги разрешены)
  HSELECT UseSelect;    // разрешенные ребра (если = 0, то разрешены все ребра)
  HSELECT BanSelect;    // запрещенные ребра (запрет имеет больший приоритет)
                        // если = 0, то нет запрещенных ребер
  char    Reserve[128];
}
  DISTGRAPHPARM;

// Тип решения задачи коммивояжера
#define TSP_TOFIRST  0 // тур заканчивается в первом пункте (классическая постановка задачи)
#define TSP_TOLAST   1 // тур заканчивается в последнем пункте
#define TSPTYPEMIN   0
#define TSPTYPEMAX   1

// Параметры решения задачи коммивояжера (Travelling salesman problem)
typedef struct TSPPARM
{
  HWND         Wnd;          // окно, которому посылается сообщение WM_PROGRESSBAR с процентом обработки
  int          PointCount;   // количество точек, которые надо посетить
  DOUBLEPOINT *Points;       // координаты точек, которые надо посетить
  int          CalcType;     // тип решения задачи коммивояжера (TSP_TOFIRST, TSP_TOLAST)
  int          IsWgs;        // координаты заданы не в системе координат карты графа в метрах,
                             // а явлются геодезическими координатами (широта, долгота)
                             // на эллипсоиде Wgs84 в радианах
  int          Type;         // тип поиска маршрута (SP_LENGTH, SP_SEMCOST, SP_TIME)
  int          IsUturn;      // разрешены развороты
  int          UseRoadCount; // размер массива флагов разрешенных типов дорог
                             // (должен быть равен 0, если все дороги разрешены или
                             // onGetParentRoadTypeCount, если есть запрещенные)
  int         *UseRoads;     // массив флагов разрешенных типов дорог при построении маршрута
                             // (если = 0, то все дороги разрешены)
  HSELECT      UseSelect;    // разрешенные ребра (если = 0, то разрешены все ребра)
  HSELECT      BanSelect;    // запрещенные ребра (запрет имеет больший приоритет)
                             // если = 0, то нет запрещенных ребер
  char         Reserve[128];
}
  TSPPARM;

extern "C"
{
  // Открытие графа сети
  // mapname - имя карты графа
  // parm    - параметры открытия графа
  // Возвращает идентификатор открытого графа
  // При ошибке возвращает 0
  NETIMP HNET WINAPI onOpenNet(WCHAR *mapname, OPENNETPARM *parm);

  // Закрытие графа сети
  // hnet - идентификатор графа сети, полученный onOpenNet
  NETIMP void WINAPI onCloseNet(HNET hnet);

  // Закрытие графа сети по имени файла карты графа
  // mapname - имя файла карты графа
  NETIMP void WINAPI onCloseNetByName(WCHAR *mapname);

  // Возвращает идентификатор открытой карты графа
  // hnet - идентификатор графа сети, полученный onOpenNet
  NETIMP HMAP WINAPI onGetHMAP(HNET hnet);

  // Возвращает документ, в котором открыты карты, по которым построен граф
  // (поле ParentMap структуры OPENNETPARM, переданной при открытии графа)
  // hnet - идентификатор графа сети, полученный onOpenNet
  NETIMP HMAP WINAPI onGetParentMap(HNET hnet);

  // Возвращает количество типов дорог, участвовавших в построении графа
  // hnet - идентификатор графа сети, полученный onOpenNet
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetParentRoadTypeCount(HNET hnet);

  // Возвращает имя типа дороги, участвовавшей в построении графа
  // hnet   - идентификатор графа сети, полученный onOpenNet
  // number - порядковый номер типа дороги (от 0)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetParentRoadTypeName(HNET hnet, long int number,
                                                 WCHAR *name, long int namesize);

  //***************************************************************
  //                    Кратчайший маршрут
  //***************************************************************

  // Поиск кратчайшего маршрута
  // hnet - идентификатор графа сети, полученный onOpenNet
  // parm - параметры определения маршрута
  // Возвращает идентификатор маршрута
  // При ошибке возвращает 0
  NETIMP HPATH WINAPI onCreatePath(HNET hnet, PATHPARM *parm);

  // Удалить маршрут
  // hpath - идентификатор маршрута, полученный onCreateRoute
  NETIMP void WINAPI onFreePath(HPATH hpath);

  // Возвращает время проезда по всему маршруту в часах
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // При ошибке возвращает 0
  NETIMP double WINAPI onGetPathTime(HPATH hpath);

  // Возвращает длину всего маршрута в метрах
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // При ошибке возвращает 0
  NETIMP double WINAPI onGetPathLength(HPATH hpath);

  // Возвращает количество ребер в маршруте
  // hpath - идентификатор маршрута, полученный onCreateRoute
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeCount(HPATH hpath);

  // Возвращает ключ ребра маршрута на карте графа
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeKey(HPATH hpath, long int number);

  // Возвращает номер объекта ребра маршрута на карте графа
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeNum(HPATH hpath, long int number);

  // Возвращает номер типа объекта из которого было нарезано ребро при создании графа
  // Для получения имени типа используйте onGetParentRoadTypeName
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // ПРИ ОШИБКЕ ВОЗВРАЩАЕТ -1
  NETIMP long int WINAPI onGetPathParentEdgeType(HPATH hpath, long int number);

  // Возвращает идентификатор карты, по объекту которой построено
  // ребро маршрута при создании карты графа
  // Для работы функции необходимо чтобы:
  // - карта графа была построена с флагом "Сохранять связь с объектами исходной карты"
  // - при открытии графа указан документ ParentMap, в котором открыты карты, по которым построен граф
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP HSITE WINAPI onGetPathParentEdgeSite(HPATH hpath, long int number);

  // Возвращает номер листа карты, по объекту которой построено ребро маршрута при создании карты графа
  // Для работы функции необходимо чтобы:
  // - карта графа была построена с флагом "Сохранять связь с объектами исходной карты"
  // - при открытии графа указан документ ParentMap, в котором открыты карты, по которым построен граф
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathParentEdgeSheetNum(HPATH hpath, long int number);

  // Возвращает ключ объекта по которому построено ребро маршрута при создании карты графа
  // Для работы функции необходимо чтобы карта графа была построена с флагом
  // "Сохранять связь с объектами исходной карты"
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathParentEdgeKey(HPATH hpath, long int number);

  // Считывает объект из которого нарезано ребро маршрута при создании карты графа
  // Для работы функции необходимо чтобы:
  // - карта графа была построена с флагом "Сохранять связь с объектами исходной карты"
  // - при открытии графа указан документ ParentMap, в котором открыты карты, по которым построен граф
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // obj    - идентификатор, в который будет считан родительский объект
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathParentEdgeObject(HPATH hpath, long int number, HOBJ obj);

  // Возвращает длину ребра маршрута по порядковому номеру ребра в маршруте в метрах
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP double WINAPI onGetPathEdgeLength(HPATH hpath, long int number);

  // Возвращает время проезда ребра маршрута по порядковому номеру ребра в маршруте в часах
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP double WINAPI onGetPathEdgeTime(HPATH hpath, long int number);

  // Возвращает координаты первой точки ребра маршрута
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // point  - возвращаемые координаты первой точки ребра маршрута
  //          Если маршрут создавался onCreatePath, onCreatePathEx, то возвращаемые координаты
  //          в системе координат карты графа
  //          Если маршрут создавался onCreatePathWgs, onCreatePathWgsEx, то возвращаемые координаты-
  //          широта, долгота в радианах на WGS84
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeFirstPoint(HPATH hpath, long int number, DOUBLEPOINT *point);

  // Возвращает координаты последней точки ребра маршрута
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // point  - возвращаемые координаты последней точки ребра маршрута
  //          Если маршрут создавался onCreatePath, onCreatePathEx, то возвращаемые координаты
  //          в системе координат карты графа
  //          Если маршрут создавался onCreatePathWgs, onCreatePathWgsEx, то возвращаемые координаты-
  //          широта, долгота в радианах на WGS84
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeLastPoint(HPATH hpath, long int number, DOUBLEPOINT *point);

  // Возвращает угол поворота на последней точке ребра маршрута
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 2, НА ПОСЛЕДНЕМ РЕБРЕ НЕТ ПОВОРОТА)
  // angle  - возвращаемый угол поворота на последней точке ребра маршрута
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeLastPointAngle(HPATH hpath, long int number, double *angle);

  // Возвращает угол поворота на первой точке ребра маршрута
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 1 до onGetPathEdgeCount - 1, НА ПЕРВОМ РЕБРЕ НЕТ ПОВОРОТА)
  // angle  - возвращаемый угол поворота на первой точке ребра маршрута
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeFirstPointAngle(HPATH hpath, long int number, double *angle);

  // Возвращает дирекционный угол первого отрезка ребра маршрута
  // (угол на первой точке между направлением на север и на вторую точку против часовой стрелки)
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // dir    - возвращаемый дирекционный угол
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeFirstSegmentDir(HPATH hpath, long int number, double *dir);

  // Возвращает дирекционный угол последнего отрезка ребра маршрута
  // (угол на последней точке между направлением на север и на предпоследнюю точку против часовой стрелки)
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathEdgeCount - 1)
  // dir    - возвращаемый дирекционный угол
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathEdgeLastSegmentDir(HPATH hpath, long int number, double *dir);

  // Возвращает количество узлов в маршруте (= количество ПОЛНЫХ ребер + 1)
  // hpath - идентификатор маршрута, полученный onCreateRoute
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathNodeCount(HPATH hpath);

  // Возвращает ключ узла маршрута на карте графа
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathNodeCount - 1)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathNodeKey(HPATH hpath, long int number);

  // Возвращает номер объекта узла маршрута на карте графа
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер ребра в маршруте (от 0 до onGetPathNodeCount - 1)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathNodeNum(HPATH hpath, long int number);

  // Записывает в объект метрику маршрута
  // hpath - идентификатор маршрута, полученный onCreateRoute
  // obj   - объект, в который записывается метрика маршрута
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathObject(HPATH hpath, HOBJ obj);

  // Записывает в объект метрику маршрута
  // hpath   - идентификатор маршрута, полученный onCreateRoute
  // obj     - объект, в который записывается метрика маршрута
  // subject - номер подобъекта, в который записывается метрика маршрута
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathSubject(HPATH hpath, HOBJ obj, long int subject);

  // Возвращает количество точек в маршруте
  // hpath - идентификатор маршрута, полученный onCreateRoute
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathPointCount(HPATH hpath);

  // Возвращает координаты точки маршрута по порядковому номеру в маршруте
  // hpath  - идентификатор маршрута, полученный onCreateRoute
  // number - номер точки в маршруте (от 0 до onGetPathPointCount - 1)
  // point  - возвращаемые координтаы точки маршрута
  //          Если маршрут создавался onCreatePath, onCreatePathEx, то возвращаемые координаты
  //          в системе координат карты графа
  //          Если маршрут создавался onCreatePathWgs, onCreatePathWgsEx, то возвращаемые координаты-
  //          широта, долгота в радианах на WGS84
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetPathPoint(HPATH hpath, long int number, DOUBLEPOINT *point);

  //***************************************************************
  //                    Граф удаленности
  //***************************************************************

  // Создание графа удаленности
  // hnet - идентификатор графа сети
  // parm - параметры построения графа удаленности
  // Возвращает идентификатор графа удаленности
  // При ошибке возвращает 0
  NETIMP HDGR WINAPI onCreateDistGraph(HNET hnet, DISTGRAPHPARM *parm);

  // Удаление графа удаленности
  // hdgr - идентификатор графа удаленности
  NETIMP void WINAPI onFreeDistGraph(HDGR hdgr);

  // Возвращает количество ребер в графе удаленности
  // hdgr - идентификатор графа удаленности
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetDistGraphEdgeCount(HDGR hdgr);

  // Возвращает ключ ребра графа удаленности на карте графа
  // hdgr   - идентификатор графа удаленности
  // number - номер ребра в графе удаленности (от 0 до onGetDistGraphEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetDistGraphEdgeKey(HDGR hdgr, long int number);

  // Возвращает номер объекта ребра графа удаленности на карте графа
  // hdgr   - идентификатор графа удаленности
  // number - номер ребра в графе удаленности (от 0 до onGetDistGraphEdgeCount - 1)
  // При ошибке возвращает 0
  NETIMP long int WINAPI onGetDistGraphEdgeNum(HDGR hdgr, long int number);

  //***************************************************************
  //                    Задача коммивояжера
  //  (поиск оптимального маршрута с посещением нескольких точек)
  //***************************************************************

  // Создание тура проходящего через несколько точек (задача коммивояжера)
  // hnet - идентификатор графа сети
  // parm - параметры построения графа удаленности
  // Возвращает идентификатор задачи коммивояжера
  // При ошибке возвращает 0
  NETIMP HTSP WINAPI onCreateTSP(HNET hnet, TSPPARM *parm);

  // Удаление задачи коммивояжера
  // htsp - идентификатор задачи коммивояжера
  NETIMP void WINAPI onFreeTSP(HTSP htsp);

  // Возвращает количество маршрутов в туре
  // htsp - идентификатор задачи коммивояжера
  NETIMP long int WINAPI onGetTSPPathCount(HTSP htsp);

  // Возвращает маршрут между парой пунктов в туре
  // Освобождать HPATH не надо, это делается автоматически в onFreeTSP
  // htsp    - идентификатор задачи коммивояжера
  // pathnum - номер маршрута в туре (от 0)
  // При ошибке возвращает 0
  NETIMP HPATH WINAPI onGetTSPPath(HTSP htsp, long int pathnum);

  // Возвращает номер пункта в начале маршрута (от 0)
  // htsp    - идентификатор задачи коммивояжера
  // pathnum - номер маршрута в туре (от 0)
  // При ошибке возвращает -1
  NETIMP long int WINAPI onGetTSPPathFirstPoint(HTSP htsp, long int pathnum);

  // Возвращает номер пункта в конце маршрута
  // htsp    - идентификатор задачи коммивояжера
  // pathnum - номер маршрута в туре (от 0)
  // При ошибке возвращает -1
  NETIMP long int WINAPI onGetTSPPathLastPoint(HTSP htsp, long int pathnum);


}

#endif
