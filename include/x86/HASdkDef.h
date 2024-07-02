#ifndef HASDK_DEF_H
#define HASDK_DEF_H

//#include "pkg_vehicle.h"
#include "network_msg.h"
#include "config_gw.h"
#include "discover_def.h"
#include "discover_client.h"
#include "FaceRecoDef.h"

#if defined(WIN32) || defined(WIN64)

// #define HASDK_CALL __stdcall

#define HASDK_CALL __stdcall

#include <Windows.h>

#define HASDK_EXPORTS

#ifdef HASDK_EXPORTS
#define HASDK_API __declspec(dllexport)
#else
#define HASDK_API __declspec(dllimport)
#endif

#else
#define HASDK_API
#define HASDK_CALL

#define HWND  void*
#define MAX_PATH 256

#endif //WIN32

#ifdef __linux__
#include <sys/time.h>
#define HASDK_CALL
#endif

#define SDK_VERSION         "0.10.0"
#define SDK_CODE_VERSION    "64"
#define ALGORITHM_VERSION   "v0.1.0_NCNN"
#define MIN_FIRMWARE_VER    "0.6.7"

#define ERR_NONE                    0    //无错误
#define ERR_INVALID_PARAM           -1   //不合法的值
#define ERR_TIMEOUT                 -2   //响应超时
#define ERR_SEND_BUF_FULL           -3   //发送缓存已满
#define ERR_SYS_NOT_MATCH           -4   //保留
#define ERR_UNCONNECTED             -5   //相机未连接
#define ERR_SNAPSHOT_UNAVAILABLE    -6   //截图失败
#define ERR_JPEG_ENCODE_ERROR       -7   //JPEG解码失败
#define ERR_BUF_TOO_SMALL           -8   //缓存空间不足
#define ERR_CANCEL                  -9   //保留
#define ERR_UNABLE_TO_OPEN_FILE     -10  //文件打开失败
#define ERR_DEVICE_NOT_SUPPORTED    -11  //设备不支持
#define ERR_COUNT_INVALID           -12  //保留
#define REPLYCODE_ERROR_OPERATION_FAILED -13 //操作失败           
#define ERR_GET_FACE_FEATURE        -14   //未检测到人脸
#define ERR_FACE_ID_REPEAT          -15   //添加人员失败，人员id重复
#define ERR_FACE_ID_NOT_EXITS       -16   //修改人脸特征失败，未找到对应ID
#define ERR_GET_FACE_INIT           -17   //人脸提取器未初始化，请调用HA_InitFaceModel初始化
#define ERR_GET_FACE_ID             -18   //无当前记录
#define ERR_SERIAL_INDEX            -19   //错误的串口编号，目前只支持HA_SERIAL_RS485和HA_SERIAL_RS232
#define ERR_SYSTEM_REBOOT           -20   //重启系统失败
#define ERR_APP_REBOOT              -21   //重启应用程序失败
#define ERR_ENCODE_JPG              -22   //压缩图像失败
#define ERR_FACES_NUM               -23   //单个人员最大支持5张图像
#define ERR_IMAGE_DECODE            -24   //图像解码失败
#define ERR_IMAGE_SIZE              -25   //图像太大，用于提取特征的jpg图像不能超过10M，jpg 直接注册图像不超过1M 
#define ERR_IMAGE_PATH              -26   //文件不存在，请检查图片路径是否正确
#define ERR_SAVE_IMG_NUM            -27   //目前相机只支持存一张模板图像，pictureFlags必须<=1
#define ERR_PTZ_CTRL                -28   //不支持的云台控制，目前只支持5：变倍（放大） 6：变倍（缩小） 7：聚焦（拉近） 8：聚焦（拉远）
#define ERR_PTZ_CTRL_MODE           -29   //不支持的控制模式，1：一次运动 2：启动 3：停止
#define ERR_DAEMON_REQUEST          -30   //保留
#define ERR_UPPER_LIMIT             -31   //人员数量已达上限
#define ERR_PROTOCAL_VER            -32   //协议版本不匹配，请确认SDK和相机固件版本
#define ERR_REQUEST_CMD             -33   //不支持的操作请求
#define ERR_PACKET_DATA             -34   //请求数据包包含不合法字段
#define ERR_AUTH_FAILED             -35   //认证失败
#define ERR_WRITE_DATA              -36   //写入数据失败
#define ERR_READ_DATA               -37   //读取数据失败
#define ERR_TWIST_FACE              -38   //归一化图像失败
#define ERR_EXTRACT_FEATURE         -39   //提取特征失败
#define ERR_MIN_FACE                -40   //人脸尺寸太小，人脸轮廓必须大于96*96
#define ERR_QVALUE_TOO_SMALL        -41   //人像质量太差不满足注册条件
#define ERR_INVALID_SYNC_MODE       -42   //无效的同步操作
#define ERR_WG_QUERY_MODE           -43   //韦根卡号不支持模糊查询
#define ERR_SYSTEM_BUSY             -44   //操作系统繁忙
#define ERR_VERSION_MATCH           -45   //版本不匹配
#define ERR_TOO_MUCH_FACE           -46   //图像中人脸数不为1
#define ERR_FACE_INCOMPLETE         -47     //图像中人脸不完整
#define ERR_ANGLE_PITCH             -48     //人脸俯仰角太大
#define ERR_ANGLE_YAW               -49     //人脸侧偏角太大
#define ERR_ANGLE_ROLL              -50     //人脸不正
#define ERR_MOUTH_OPEN              -51     //张嘴幅度过大
#define ERR_YINYANG_FACE            -52     //光照不均匀
#define ERR_DARK_LIGHT				-53     //光照太暗
#define ERR_VISIBLE_TARGET          -54    // 未检出人脸*/
#define ERR_INFRARED_TARGET         -55    //未检出指定个数红外光目标*/
#define ERR_ABERRATION_TOO_BIG      -56     // 可见光红外光像差过大*/
#define ERR_BRIGHT_LIGHT			-57     //  光线太亮 */
#define ERR_FACE_FUZZY				-58     //  人脸模糊  */
#define ERR_REPLYCODE_FEATURE_VERSION   -60  //特征数据版本不匹配
#define ERR_LACK_TWISTIMGE              -61  //缺少归一化图像
#define ERR_FACE_EXISTED			 -62    //存在相似人脸
#define ERR_FUNC_AUTH                -70   //功能授权失败
#define ERR_FUNC_AUTHORIZED          -71   //功能已授权
#define ERR_UN_AUTH					 -72   //功能未授权
#define ERR_4GINFO					-75   //获取4G信号消息失败
#define ERR_PING_BLOCK				-76   //ping网址失败
#define ERR_WIFIUNCONNECTED			-80   //wifi未连接

#define REPLYCODE_ERROR_CALL_TURN_ON_FAIL   -82    /*! 房号不存在 */
#define REPLYCODE_ERROR_CALL_TURN_OFF_FAIL  -83    /*! 通话关闭失败 */


#define ERR_UNKNOWN                 -1000 //未知错误

enum CAM_TYPE
{
    CAM_TYPE_TI8127,
    CAM_TYPE_S2
};




typedef enum       //相机连接event
{	
	DEVICEIDUNKNOWN=-1,   //没有设备编号
    UNKNOWN,              //未知错误
    CONNECTED,            //连接成功
    DISCONNECTED          //连接断开
}CONNECTSTATE;









typedef enum
{
    STREAM_FORMAT_JPEG = 1,   //jpeg视频流
    STREAM_FORMAT_H264 = 2,    //H264视频流
	STREAM_FORMAT_RGB = 3    //RGB视频帧
}STREAM_FORMAT;


typedef enum
{
    CHAR_ENCODE_GBK = 0,
    CHAR_ENCODE_UTF8
}CHAR_ENCODE;


typedef enum
{
    TRIG_TYPE_VIDEO,
    TRIG_TYPE_COIL,
    TRIG_TYPE_SOFT,
    TRIG_TYPE_RADIA
}TRIG_TYPE;


struct HA_LiveStream
{
    int w;  //视频宽
    int h;  //视频高
    STREAM_FORMAT format;   //视频格式
    int streamLen;          //视频流数据长度
    int streamBufSize;      //保留
    char* streamBuf;        //视频流数据
	unsigned int  h264_sequence; // 帧号
	unsigned char channel;  //通道号 0:主码流 4:子码流
};

struct FeeInfoRes
{
    char plate[16];           //车牌
    time_t time_in;           //入场时间
    time_t time_out;          //出场时间
    float park_fee;           //停车费用
    unsigned short fee_mode;  //收费类型
    unsigned char platecolor; //车牌颜色
    unsigned char InOut_type; //月租车还是临时车
};

struct FeeInfo
{
    char plate[16];           //车牌
    unsigned short in_year;           //入场时间
    unsigned short in_month;
    unsigned short in_day;
    unsigned short in_hour;
    unsigned short in_min;
    unsigned short in_sec;
    unsigned short out_year;         //出场时间
    unsigned short out_month;
    unsigned short out_day;
    unsigned short out_hour;
    unsigned short out_min;
    unsigned short out_sec; 
    float park_fee;           //停车费用
    unsigned short fee_mode;  //收费类型  0 [按时计费] 1[按次计费] 2[分段计费] 3[查表计费]
    unsigned char platecolor; //车牌颜色  0 蓝色 1 黑色 2 黄色 3 白色  4新能源车牌绿色
    unsigned char InOut_type; //月租车还是临时车  0[未经过处理，未知] 1[月租车，且在有效期] 2[临时车] 3[无牌车] 4[黑名单车] 7[月租车已过期]
};

struct FeeInfoEx
{
    char plate[16];   //车牌号码       
    unsigned short year_in;
    unsigned char  mon_in;
    unsigned char  day_in;
    unsigned char  hour_in;
    unsigned char  min_in;
    unsigned short sec_in;

    unsigned short year_out;
    unsigned char  mon_out;
    unsigned char  day_out;
    unsigned char  hour_out;
    unsigned char  min_out;
    unsigned short sec_out;

    float park_fee;          
    unsigned short fee_mode;  
    unsigned char platecolor; 
    unsigned char InOut_type; 
};


struct HA_AllowList
{
    char plate[16];                 //车牌号
    unsigned short plateColor;      //车牌颜色
    unsigned short year;            //记录的过期时间-年
    unsigned short month;           //月
    unsigned short day;             //日

    unsigned char hour;             //时
    unsigned char min;              //分
    unsigned char sec;              //秒
    unsigned char bEnable;          //记录是否有效标志

    unsigned short enable_year;     //记录的生效时间-年
    unsigned char enable_month;     //月
    unsigned char enable_day;       //日
    unsigned char enable_hour;      //时
    unsigned char enable_min;       //分
    unsigned char enable_sec;       //秒

    unsigned char bAlarm;           //是否触发报警（黑名单记录）   

    int resv[13];
};


struct VERSION
{
    char protocl_version[64];

    char arm_version[64];
    char arm_buildtime[64];
    char arm_code_version[64];

    char dsp_version[64];
    char dsp_buildtime[64];
    char dsp_code_version[64];

    unsigned short video_width;
    unsigned short video_height;
};

struct HaSdkVersion
{
    char sdk_version[64];       //sdk版本
    
    char protocl_version[64];   //协议类型

    char sdk_code_version[64];  //sdk源代码版本

    char min_firmware_ver[64];  //支持的最低固件版本

    char algorithm_version[64]; //sdk使用得算法版本
};

struct AudioItem 
{
    int id; //内置音频id
    char desc[64]; //音频文件名
};

struct AudioItemEx
{
    int id; //内置音频id
	char desc[64]; //音频文件名
    unsigned char enable;  // 默认播放开关 0:不播放 1:使用内置音频 2:使用TTS播放
	char tts_txt[35]; // TTS播放内容
	char resv[128];
};


struct DeviceInfor{
	char dev_id[32];  //设备序列号;
 	char ip[32];      //相机ip
	char camId[32];    //相机编号 
    char posId[32];    //点位编号
    char posName[96];  //点位名称
};

struct RegBinocularParam{
  /*相差参数个数 最大16*/
  int Num;
  /*！双目摄像头像差*/
  HA_Point pixel_diff[16];
};
struct RegImageSyncParam 
{
  /*! 人像数据同步开关 */
  char sync_enable;

  /*! 人像数据同步协议类型（保留暂未使用）*/
  char sync_mode;
  
  /*! 人像数据同步间隔时间 单位s*/
  unsigned short sync_interval;
  
  /*! 人像数据同步IP地址。 */
  char sync_ip[16];

  /*! 人像数据同步端口。 */
  unsigned short sync_port;

  /*! 人像数据同步URL。 */
  char sync_url[102];
};











/**
* @brief  连接/断开回调函数
* @param  cam相机句柄
* @param  ip相机ip
* @param  port相机端口
* @param  event事件 1 连接 2断开
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_ConnectEventCb_t)(struct HA_Cam* cam, const char* ip, unsigned short port, int event, void* usrParam);

/**
*  @brief Sever模式连接事件回调函数
*  @param  cam 相机句柄 连接失败时为空
*  @param  devInfor 相机信息
*  @param  port Sever 端口号
*  @param  event -1设备编号重复 -2设备编号缺失    1  连接 2 连接中断
*  @param  usrParam 用户自定义参数
*/
typedef void (HASDK_CALL *HA_ServerConnectCb_t)(struct HA_Cam* cam, DeviceInfor devInfor, unsigned short port, int event, void* usrParam);


/**
*  @brief wifi连接事件回调函数
*  @param  cam 相机句柄 连接失败时为空
*  @param  state 连接状态 0:连接成功 1:连接已断开 2:wifi不存在 3:密码错误 4:连接被拒绝
*  @param  ssid wifi名称 state == 1时存在 其他为NULL
*  @param  ip 相机无线网卡ip state == 1时存在 其他为NULL
*  @param  usrParam 用户自定义参数
*/
typedef void (HASDK_CALL *HA_WifiConnectCb_t)(struct HA_Cam* cam, int state, char* ssid, char* ip, void* usrParam);

/**
*  @brief  二维码接收回调函数
*  @param  code 二维码字符串
*  @param  resv 保留 NULL
*  @param  usrParam 用户自定义参数
*/
typedef void (HASDK_CALL *HA_QRCodeCb_t)(struct HA_Cam* cam, unsigned char* code, void* resv, void* usrParam);

/**
*  @brief  SDK透明传输接收回调
*  @param  cam相机句柄
*  @param  data 接收到的数据
*  @param  dataSize 数据长度
*  @param  resv 保留 NULL
*  @param  usrParam 用户自定义参数
*/
typedef void (HASDK_CALL *HA_PassThroughReadCb_t)(struct HA_Cam* cam, char* data, unsigned int dataSize, void* resv, void* usrParam);

/**
* @brief  实时流数据接收回调函数 
* @param  cam相机句柄
* @param  ip相机ip
* @param  HA_LiveStream 视频数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_LiveStreamCb_t)(struct HA_Cam* cam, const char* ip, const struct HA_LiveStream* stream, int usrParam);

//废弃
typedef void (HASDK_CALL *HA_DataReadCb_t)(struct HA_Cam* cam, const char* ip, unsigned short port, int dataType, const char* data, unsigned int dataLen, int usrParam);

/**
* 废弃
*/
typedef void (HASDK_CALL *HA_DecodeImageCb_t)(struct HA_Cam* cam, unsigned char* rgb, int width, int height, int usrParam);

/**
* @brief  实时视频帧回调函数拓展 
* @param  cam相机句柄
* @param  rgb 相机rgb数据
* @param  width rgb图像宽
* @param  height rgb图像高
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_DecodeImageExCb_t)(struct HA_Cam* cam, const struct HA_LiveStream* stream, void* usrParam);

/**
* @brief  相机录音回调函数
* @param  cam相机句柄
* @param  audio_data 音频数据 pcm数据
* @param  data_szie 数据长度
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_AudioRecordCb_t)(struct HA_Cam* cam,const char* audio_data, unsigned int data_szie, void* usrParam);


/**
* @brief  相机录音回调函数
* @param  cam相机句柄
* @param  percentage 校正进度百分比 0~100
* @param  delay_time 校正值 percentage 为100时有效 percentage为100时delay_time 任为-1 校正失败
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_AESAdjustCb_t)(struct HA_Cam* cam, unsigned int percentage, int delay_time, void* usrParam);

/**
* @brief  读取透明串口回调函数 
* @param  cam相机句柄
* @param  index 1:485 2:232
* @param  data 读取到的数据
* @param  size 数据长度
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_ReadTSerialCb_t)(struct HA_Cam* cam, int index, const unsigned char* data, int size, int usrParam);
/**
* 预留
*/
typedef void (HASDK_CALL *HA_ReadGpioCb_t)(struct HA_Cam* cam, int port, int inout, int state, int errNum, char *resv);

/**
* @brief  GPIO输入信号 
* @param  cam相机句柄
* @param  type GPIO的输入信号类型，255:gpio   0:WG26 1:WG34 
* @param  data 输入类型为gpio时，该值表示gpio端口号。输入类型为韦根信号时，该值为韦根协议门禁卡号
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_GpioInputCb_t)(struct HA_Cam* cam, int type, unsigned int data, void* usrParam);

/**
* @brief  WG输入信号 
* @param  cam相机句柄
* @param  type GPIO的输入信号类型 除去255:gpio   0:WG26 1:WG34 
* @param  data 输入类型为gpio时，该值表示gpio端口号。输入类型为韦根信号时，该值为韦根协议门禁卡号
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_WGInputCb_t)(struct HA_Cam* cam, int type, unsigned long long data, void* usrParam);

/**
* @brief  相机执行Ping命令结果
* @param  cam相机句柄
* @param  Infor Ping 命令打印结果 (字符串)
* @param  size Infor数据长度
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_CamPingCb_t)(struct HA_Cam* cam, char* Infor, int size, void* usrParam);

/**
* @brief  通过中转服务器搜索相机
* @param  cam相机句柄
* @param  Count 服务器当前连接相机数量
* @param  pageNum 查询此次返回相机信息数量 
* @param  searchCamInfo 相机信息
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_SearchCamCb_t)(struct HA_Cam* cam, unsigned int Count, unsigned int page_size,searchCamInfo* CamInfo , void* usrParam);

/**
* @brief  相机搜索WiFi列表回调
* @param  cam相机句柄
* @param  num wifi数量
* @param  signal wifi 信息 按照 signal[0] - signal[num - 1] 读取
* @param  usr_param 用户参数
*/

typedef void (HASDK_CALL *HA_SearchWiFiCb_t)(struct HA_Cam* cam, int num ,WifiSignal* signal, void* usrParam);

/**
* @brief  sip通话事件回调
* @param  cam相机句柄
* @param  sipEvent sip事件 参见 enum SIPEventCall
* @param  resv 保留
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_SIPCallEventCb_t)(struct HA_Cam* cam, int sipEvent, char* resv, void* userParam);

/**
* @brief  sip按键事件回调
* @param  cam相机句柄
* @param  keyId 按键 keyId 0-9 == 0-9  keyId 10 == *  keyId 11 == #
* @param  resv 保留
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_SIPKeyEventCb_t)(struct HA_Cam* cam, int keyId, char* resv, void* userParam);

/*废弃*/
typedef void (HASDK_CALL* HA_PlateInfoCb_t)(struct HA_Cam* cam, const struct pkg_vehicle* vehicle, int usrParam);

//预留
typedef void (HASDK_CALL* HA_IOStateCb_t)(struct HA_Cam* cam, int index, int state, void* usrParam);

/*废弃*/
typedef void (HASDK_CALL* HA_OfflineFeeData_t)(struct HA_Cam* cam, const struct FeeInfo* pFeeInfo,void* usrParam);

/*废弃*/
typedef void (HASDK_CALL* HA_OfflineQueriedEntryInfoCb_t)(struct HA_Cam* cam,const char* plate,struct timeval timeIn,int flag,void* usrParam);

/*废弃*/
typedef void (HASDK_CALL* HA_OfflineFeeDataQueriedByPageCb_t)(struct HA_Cam* cam,int validCount,struct FeeInfoEx*pFeeInfo,int startPos,int endPos,void* usrParam);
/**
* @brief  人脸抓拍数据回调函数
* @param  cam相机句柄
* @param  faceRecoInfo 抓拍数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceRecoCb_t)(struct HA_Cam* cam,  const struct FaceRecoInfo* faceRecoInfo, void* usrParam);

/**
* @brief  人脸抓拍数据简单回调函数
* @param  cam相机句柄
* @param  faceRecoInfo 抓拍数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceSimpleRecoCb_t)(struct HA_Cam* cam, const char* id, void* usrParam);

/**
* @brief  注册人员查询回调函数
* @param  cam相机句柄
* @param  faceQueryInfo 注册人员数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceQueryCb_t)(struct HA_Cam* cam,  const struct QueryFaceInfo* faceQueryInfo, void* usrParam);

/**
* @brief  人脸轮廓坐标回调
* @param  cam相机句柄
* @param  FaceRect 人脸轮廓
* @param  rectNum  轮廓数量
* @param  showIdFlag 轮廓显示开关
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceRectCb_t)(struct HA_Cam* cam,  const struct FaceRect* faceRects, int rectNum, int showIdFlag, void* usrParam); 

/**
* @brief  调试图像回调
* @param  cam相机句柄
* @param  debugImageInfo 调试图像数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceDebugImageCb_t)(struct HA_Cam* cam, struct DebugImageInfo *debugImageInfo, void* usrParam);

/**
* @brief  红外调试图像回调
* @param  cam相机句柄
* @param  debugImageInfo 红外调试图像数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceDebugInfraredImageCb_t)(struct HA_Cam* cam, struct BebugInfraredImage *debugImageInfo, void* usrParam);

/**
* @brief  删除注册人员进度回调
* @param  cam相机句柄
* @param  delProgress 删除进度信息
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceDelProgressCb_t)(struct HA_Cam* cam, struct FaceDelProgressInfo *delProgress, void* usrParam);

/**
* @brief  快照图像回调
* @param  cam相机句柄
* @param  snapImage 快照数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_SnapshotCb_t)(struct HA_Cam* cam, struct SnapshotImage *snapImage, void* usrParam);

/**
* @brief  认证结果回调
* @param  cam相机句柄
* @param  ip 相机ip
* @param  port 相机端口
* @param  status 认证状态 0:认证成功 其他见错误码
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_VerifyStatusCb_t)(struct HA_Cam* cam, const char* ip, unsigned short port, int status, void* usrParam);

/**
* @brief  开闸信息回调，开闸纪录
* @param  cam相机句柄
* @param  alarmRecord 快照数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_AlarmRecordCb_t)(struct HA_Cam* cam, struct AlarmInfoRecord *alarmRecord, void* usrParam);

/**
* @brief  开闸请求回调
* @param  cam相机句柄
* @param  alarmRequest 开闸信息请求
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_AlarmRequestCb_t)(struct HA_Cam* cam, struct AlarmRequest *alarmRequest, void* usrParam);


/**
* @brief  音频播放内容信息回调
* @param  cam相机句柄
* @param  alarmRequest 开闸信息请求
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL *HA_AudioPlayInfoCb_t)(struct HA_Cam* cam, struct AudioPlayInfo *info, void* usrParam);

/**
* @brief  重注册进度回调
* @param  cam相机句柄
* @param  registProgress 重注册进度
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceReRegistProgressCb_t)(struct HA_Cam* cam, struct FaceReRegistProgressInfo *registProgress, void* usrParam);

/**
* @brief  双目相机校差参数查询回调函数
* @param  cam相机句柄
* @param  adjustParam 双目相机校差参数
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_BinocularAjustParamCb_t)(struct HA_Cam* cam, const struct BinocularAjustParam *adjustParam, void* usrParam);

/**
* 预留
*/
typedef void (HASDK_CALL* HA_AllPersonIdCb_t)(struct HA_Cam* cam, const struct AllPersonID *PersonId, void* usrParam);

/**
* @brief  抓拍记录查询回调函数
* @param  cam相机句柄
* @param  recordInfo 抓拍记录数据
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_FaceRecordCb_t)(struct HA_Cam* cam,  const struct RecordData* recordInfo, void* usrParam);
/*预留*/
typedef void (HASDK_CALL* HA_GetServerCamCb_t)(struct HA_Cam* cam,int port,void* usrParam);


typedef void (HASDK_CALL* HA_FailMessageCb_t)(struct HA_Cam* cam,  const struct FailMessage* recordInfo, void* usrParam);

/**
* @brief  文字信息显示回调
* @param  cam相机句柄
* @param  front 文字信息
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_UIFrontCb_t)(struct HA_Cam* cam, const struct UIText* front, void* usrParam);

/**
* @brief  wifi信息显示回调
* @param  cam相机句柄
* @param  wifi wifi信息
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_UIWifiCb_t)(struct HA_Cam* cam, const struct UIWifi* wifi, void* usrParam);

/**
* @brief  人脸信息显示回调
* @param  cam相机句柄
* @param  face 人脸信息
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_UIFaceCb_t)(struct HA_Cam* cam, const struct UIFace* face, void* usrParam);

/**
* @brief  人脸框回调
* @param  cam相机句柄
* @param  face 人脸信息
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_UIFaceRectCb_t)(struct HA_Cam* cam, const struct UIFaceRect* face, void* usrParam);


/**
* @brief  相机UI事件通知
* @param  cam相机句柄
* @param  Uievent 事件ID
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_UIEventCb_t)(struct HA_Cam* cam, const struct UIEvent* Uievent, void* usrParam);

/**
* @brief  相机图片显示
* @param  cam相机句柄
* @param  uiImage 图片信息
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_UIImageCb_t)(struct HA_Cam* cam, const struct UIImage* uiImage, void* usrParam);

/**
* @brief  UI交互信息
* @param  cam相机句柄
* @param  json_str json内容
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_UIJsonTransferCb_t)(struct HA_Cam* cam, const char* json_str, void* usrParam);

/**
* @brief  相机图片显示
* @param  cam相机句柄
* @param  uiImage 图片信息
* @param  usr_param 用户参数
*/
typedef void (HASDK_CALL* HA_UIFengHuoDataCb_t)(struct HA_Cam* cam, const struct CardInfo* card_info, void* usrParam);

#endif

