/*
 * config_gw.h
 *
 *  Created on: 2014年7月4日
 *      Author: chens
 */

#ifndef CONFIG_GW_H_
#define CONFIG_GW_H_

#include <string.h>
#include <stdio.h>

#define MAX_LANE_NUM    (4)
#define MAX_FLASH_NUM   (4)
#define MAX_RADAR_NUM   (4)
#define MAX_INPUT_IO_NUM    (8)
#define MAX_COIL_GROUP  (4)
#define  MAX_CABINET_STATE (8)

#define HA_SERIA_RS485 (1) 
#define HA_SERIA_RS232 (2)

//人员查询条件标记
typedef enum {
  //通过ID查询
  QUERY_BY_ID = 0x1,

  //通过姓名查询
  QUERY_BY_NAME = 0x1 << 1,

  //通过韦根卡号查询
  QUERY_BY_WGNO = 0x1 << 2,

  //通过有效期截止时间范围查询
  QUERY_BY_EFFECT_TIME = 0x1 << 3,

  //通过有效期起始时间范围查询
  QUERY_BY_EFFECT_START_TIME = 0x1 << 4,

  /*! 保留。 */
  QUERY_BY_FLAG_RECV = 0x1 << 5,

  //通过自定义字段查询
  QUERY_BY_CUSTOMERTXT = 0x1 << 6,
  //无特征值
  QUERY_BY_NO_FEATURE = 0x1<<7,
}ConditionFlag;

// 记录查询条件标记。
enum RecordQueryFlag {
  /*! 通过抓拍时间范围查询。 */
  RECORD_QUERY_FLAG_TIME         = 0x1,

  /*! 通过比对分数范围查询。 */
  RECORD_QUERY_FLAG_SCORE        = 0x1 << 1,

  /*! 通过性别查询。 */
  RECORD_QUERY_FLAG_SEX          = 0x1 << 2,

  /*! 通过年龄范围查询。 */
  RECORD_QUERY_FLAG_AGE          = 0x1 << 3,

  /*! 通过比上的人员id查询。 */
  RECORD_QUERY_FLAG_ID           = 0x1 << 4,
  
  /*! 通过比上的人员姓名查询。 */
  RECORD_QUERY_FLAG_NAME         = 0x1 << 5,

  /*! 通过抓拍图像的人像质量范围查询。 */
  RECORD_QUERY_FLAG_QVALUE       = 0x1 << 6,

  /*! 通过记录上传状态查询。 */
  RECORD_QUERY_FLAG_UPLOAD       = 0x1 << 7,

  /*! 通过记录数据库编号查询。 */
  RECORD_QUERY_FLAG_SEQUENCE     = 0x1 << 8,

	/*! 通过平台id筛选。 */
	RECORD_QUERY_FLAG_WORKSITE		 = 0x1 << 9
};

//人员查询条件标记
typedef enum {
  //精确查询
  QUERY_EXACT = 0x0,

  //模糊查询
  QUERY_FUZZY = 0x1
}QueryMode;

/// 比对模式。

enum MatchMode {
	/*! 未初始化。*/
	MATCH_MODE_NULL        = 0,

	/*! 对应--刷脸开闸功能。 */
	MATCH_MODE_NORMAL      = 1,

	/*! 对应--刷身份证开闸功能。 */
	MATCH_MODE_IDCARD_1TO1 = 2,

	/*! 对应--刷脸+刷身份证开闸功能。 */
	MATCH_MODE_FACE_IDCARD  = 3,

	/*! 对应--刷卡开闸功能。 */
	MATCH_MODE_WGCARD      = 4,

	/*! 对应--刷脸+刷卡开闸功能。 */
	MATCH_MODE_FACE_WGCARD = 5,

	/*! 对应--过人开闸功能。 */
	MATCH_MODE_ANY_FACE    = 6,

	/*! 对应--刷脸+白名单开闸功能 或者刷卡+白名单开闸功能*/
	MATCH_MODE_NORMAL_OR_WGCARD = 7,

	 /*! 对应--刷脸或刷身份证。 */
	MATCH_MODE_NORMAL_OR_IDCARD_1TO1 = 8,

	/*! 对应--刷卡并截图 */
	MATCH_MODE_IDCARD_SNAPSHOT       = 9,

	/*! 对应--刷脸或（刷脸+刷身份证） */
	MATCH_MODE_NORMAL_OR_FACE_IDCARD = 10,

	/*! 对应--刷身份证（白名单）只需要身份证号在白名单内 */
	MATCH_MODE_IDCARD_ONLY			 = 11,

	/*! 对应--刷身份证开闸（不需要比对） */
	MATCH_MODE_IDCARD_NOT_MATCH = 12,

	/*! 对应--刷脸或者刷身份证开闸（刷身份证不需要比对） */
	MATCH_MODE_FACE_OR_IDCARD_NOMATCH = 13,

	/*! 对应--刷脸或RFID全景快照。 */
	MATCH_MODE_NORMAL_OR_SNAPSHOT    = 20,
	MATCH_MODE_PURE_TEMPERATURE_MEASUREMENT = 21,
	MATCH_MODE_FACE_OR_IDCARD_OR_PWDCARD = 22,


};

/// gpio输入方式。
enum GpioInType{   
  /*! 韦根26协议。 */
  IN_STATE_WG26  = 0,
  
  /*! 韦根34协议。 */
  IN_STATE_WG34  = 1,

  /*! 韦根36协议。 */
  IN_STATE_WG36  = 2,

  /*! 韦根44协议。 */
  IN_STATE_WG44  = 3,

  /*! 韦根66协议。 */
  IN_STATE_WG66  = 4,
  IN_STATE_WG37  = 5,
  IN_STATE_DOOR_KEY = 0x10, //开门按键
  IN_STATE_ANTI_DEMOLITION_KEY = 0x11, //防拆按键
  IN_STATE_GATE_MAGNETISM =  0x12,//门磁
  IN_STATE_DOORBELL= 0x13,//门铃	 
  /*! IO输入方式。 */
  IN_STATE_IO = 255
};
    

/// 图片形式。
typedef enum {
  /*! 未初始化数据输出模式。 */
  IMAGE_FORM_NULL    = 0,

  /*! 全景。 */
  IMAGE_FORM_OVERALL = 0x1,

  /*! 特写。 */
  IMAGE_FORM_CLOSEUP = 0x1 << 1,

  /*! 全景+特写。 */
  IMAGE_FORM_BOTH    = IMAGE_FORM_OVERALL | IMAGE_FORM_CLOSEUP
} ImageForm;

/// 输出选项。
enum OutputOption {
  /*! 选项为空。 */
  OUTPUT_OPTION_NULL      = 0,

  /*! 全景图。 */
  OUTPUT_OPTION_OVERALL   = IMAGE_FORM_OVERALL,

  /*! 特写图。 */
  OUTPUT_OPTION_CLOSEUP   = IMAGE_FORM_CLOSEUP,

  /*! 比对原型图。 */
  OUTPUT_OPTION_PROTOTYPE = 0x1 << 2,

  /*! 特征数据。 */
  OUTPUT_OPTION_FEATURE   = 0x1 << 3,

  /*! 调试图像(用于算法调试)*/
  OUTPUT_OPTION_TWIST_IMAGE = 0x1 << 4
};

/// 人脸功能选项。
enum FuncOption {
  /*! 除抓拍功能（必不可少）外的无其它功能选项。 */
  FUNC_OPTION_NULL       = 0,

  /*! 人脸比对。 */
  FUNC_OPTION_MATCH      = 0x1,

  /*! 年龄检测。 */
  FUNC_OPTION_AGE        = 0x1 << 1,

  /*! 性别检测。 */
  FUNC_OPTION_SEX        = 0x1 << 2,

  /*! 表情检测。 */
  FUNC_OPTION_EMOTION    = 0x1 << 3,

  /*! 肤色检测。 */
  FUNC_OPTION_SKIN       = 0x1 << 4,

  /*! 活体检测。 */
  FUNC_OPTION_ALIVE      = 0x1 << 5,

  /*! 安全帽检测。 */
  FUNC_OPTION_HAT        = 0x1 << 6,
  
  /*! 体温检测。 */
  FUNC_OPTION_TEMPERATURE = 0x1 << 7,

 /*! 口罩检测。 */
  FUNC_OPTION_MASK        = 0x1 << 8

};

//人员对比失败原因
enum MatchFailedReasons {
  /*NULL*/
  MATCH_FAILED_NULL                  = 0,

  /*限制人员*/
  MATCH_FAILED_NOT_WHITE             = -2,

  /*! 人员过期 */
  MATCH_FAILED_EXPIRE                = -3,

  /*! 不在调度时间 */
  MATCH_FAILED_UN_CHEDULES           = -4,

  /*! 节假日 */
  MATCH_FAILED_FESTIVAL              = -5,

  /*! 温度过高 */
  MATCH_FAILED_ABN_TEMPERATURE       = -6,

  /*! 口罩 */
  MATCH_FAILED_MASK                  = -7,

  /*! 未带安全帽 */
  MATCH_FAILED_WITHOUT_HAT           = -8,

  /*卡号未注册*/
  MATCH_FAILED_INVAILED_CARD         = -9,

  /*认证不匹配*/
  MATCH_FAILED_UMMATCHED_ID          = -10,

  /*未授权*/
  MATCH_FAILED_NOAUTH                = -11

};



/// 数据上传模式。
typedef enum {
  /*! 未初始化。 */
  UPLOAD_MODE_NULL = 0,

  /*! TCP协议上传。 */
  UPLOAD_MODE_TCP  = 1,

  /*! FTP协议上传。 */
  UPLOAD_MODE_FTP  = 2,

  /*! HTTP协议上传。 */
  UPLOAD_MODE_HTTP = 3,

  /* WebService上传*/
  UPLOAD_MODE_SERVICE=4
} UploadMode;

/// 韦根协议类型。
typedef enum {
  WG26 = 0,

  WG34 = 1,

  WG36 = 2,

  WG44 = 3,

  WG66 = 4,
  
  WG37 = 5,

  GPIO = 255
} WiegandType;

typedef enum {
  //无任何操作
  HA_SYNC_NONE = 0,
  
  //添加人员信息
  HA_FACE_ADD = 1,

  //修改人员信息
  HA_FACE_UPDATE = 2,

  //删除人员信息
  HA_FACE_DEL = 3
}FaceSyncMode;


enum PTZCTL {
 PTZ_CTRL_ZOOM_IN    =5,  /*! 变倍（放大）*/
 PTZ_CTRL_ZOOM_OUT   =6,  /*! 变倍（缩小）*/
 PTZ_CTRL_FOCUS_IN   =7, /*! 聚焦（拉近）*/
 PTZ_CTRL_FOCUS_OUT  =8 /*! 聚焦（拉远）*/
};

enum PTZMODE {
PTZ_MODE_ONCE   =1,    /*! 一次运动*/
PTZ_MODE_START  =2,   /*! 启动*/
PTZ_MODE_STOP   =3    /*! 停止*/
};


struct YunZhufenfaParam {
	/*! 心跳时间间隔。*/
	unsigned int sync_interval;

	/*! 服务器基地址。----海南采集接口*/
	char base_url[52];

	/*! appid*/
	char appid[50];

	/*! 密钥*/
	char secretKey[50];

	/*! 设备id。------海南设备编号*/
	char device_id[50];

	/*! 1入场  2进场*/
	unsigned int in_or_out;
};

struct config_size {
    unsigned short width;
    unsigned short height;
};

struct config_point
{
    unsigned short x;
    unsigned short y;
};

struct config_rect {
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
};

struct CardInfo {

	int total;

	int page_size;

	int count;
	/*! 身份证号码。 */
	char number[36];

	/*! 姓名。 */
	char name[43];

	/*! 性别。@ref Sex 。 */
	unsigned char sex;

	/*! 民族。 */
	char national[20];

	/*! 出生日期。 */
	char birth[17];

	/*! 住址。 */
	char residence_address[103];

	/*! 签发机关。 */
	char organ_issue[43];

	/*! 有效期起始日期。 */
	char valid_date_start[17];

	/*! 有效期截止日期。 */
	char valid_date_end[17];

	/*! 身份证图片数据长度 。 */
	int img_size;

	/*! 身份证图片数据 。 */
	unsigned char* img;

	/*! 保留。 */
	char resv[15];
};

struct searchCamInfo{
	/*! 设备序列号。 */
	char devId[32];
	char devIp[16];
	unsigned int port;
	/*! 点位编号。 */
	char addr_id[32];
	/*! 点位名称。 */
	char addr_name[96];

};

struct WifiSignal {
	char ssid[36]; 				// wifi名称
	unsigned int frequency;		// 频率 2.4G或5G
    int rssi;   				// 信号强度 信号强度在[-126, 0]范围递增，频率为5G时[156, 200)递增
    char mac[20];  				// MAC地址
    char encryptMethod[256];	// 加密方式
    int speed;					// 连接速度
};

struct ImageShowPlan
{
  unsigned int x;  // 图片显示位置 x 
  unsigned int y;  // 图片显示位置 y
  unsigned int formt; // 图片类型 0:jpg 1:png
  unsigned int alive_time; // 显示时间 单位:毫秒 (0:永久显示)
  unsigned int data_size;         // 数据长度
  unsigned char* data;		// 图片数据
  char recv[32]; // 保留
};


struct LogContains {
    unsigned int temp;
    unsigned int level;
    char content[512];
	char resv[24];
};



enum log_level {
    LOG_DEBUG = 0x1, 
    LOG_INFO  = 0x1 << 1, 
    LOG_USER  = 0x1 << 2,
    LOG_WARN  = 0x1 << 3,
    LOG_ERROR = 0x1 << 4,
    LOG_FATAL = 0x1 << 5,
};

struct LogCondition {
	unsigned int page_no; //查询页面
	unsigned int page_size; //分页大小 注:最大 100
    unsigned int time_begin;  //日志开始时间  Linux时间
	unsigned int time_end; //日志结束时间
	unsigned int level; //日志等级 enum log_level 可或运算
    char resv[16];
};


/// LCD显示项
enum LcdDisplayItem {
	/*! 显示标题 */
	LCD_DISPLAY_ITEM_TITILE     = 0x1, 

	/*! 显示时间 */
	LCD_DISPLAY_ITEM_TIME       = 0x1 << 1,

	/*! 显示IP */
	LCD_DISPLAY_ITEM_IP         = 0x1 << 2,  

	/*! 显示人脸库数量 */
	LCD_DISPLAY_ITEM_PERSON_NUM = 0x1 << 3,

	/*! 相机序列号 */
	LCD_DISPLAY_ITEM_SERIAL_NUM = 0x1 << 4,

	/*! 刷卡卡号信息 */
	LCD_DISPLAY_ITEM_CARD_NUM   = 0x1 << 5,

	/*! 4G GPS信息 */
	LCD_DISPLAY_ITEM_GPSINFO   = 0x1 << 6,

	/*! 测温人数统计 */
	LCD_TIMES_OF_TEMPERATURE_MEASUREMENT = 0x1 << 7,
	LCD_DISPLAY_ITEM_HEALTH_CODE = 0x1 << 8,
	/*! 人脸框绘制 */
	LCD_DISPLAY_ITEM_FACE_RECT = 0x1 << 9,
};


enum LcdPersonDisplayItem {
  /*! 显示比对成功的人员姓名 */
  LCD_PERSON_DISPLAY_ITEM_PERSON_NAME = 0x1 << 1,
  
  /*! 显示比对成功的人员图像 */
  LCD_PERSON_DISPLAY_ITEM_PERSON_IMAGE = 0x1 << 2,
  
  /*! 显示比对成功的人员比对时间 */
  LCD_PERSON_DISPLAY_ITEM_PERSON_MATCH_TIME = 0x1 << 3,

  /*! 显示比对成功的人员自定义字段 */
  LCD_PERSON_DISPLAY_ITEM_PERSON_TEXT = 0x1 << 4
};



//------------------------------------------------------------//

/// 服务参数（8字节）。
struct ServiceParam {
  /*! 服务端口(只读 )。 */
  unsigned short port;

  /*! 最大客户端连接数，当前不生效。 */
  unsigned char max_clients;

  /*! 心跳超时时间，当前不生效。 */
  unsigned char heart_timeout;

  /*! 保留字段。 */
  unsigned char resv[4];
};

/// 分辨率。
enum PIC_SIZE_E
{
    PIC_360P = 1,      /* 640 * 360 */
    PIC_D1_PAL,    /* 720 * 576 */
    PIC_D1_NTSC,   /* 720 * 480 */
    PIC_720P      /* 1280 * 720  */
};


/// 相机容量信息。
struct MemoryInfor {
	unsigned int SDCardTotalSize; //SD卡 总容容量	单位 k
	unsigned int SDCardUsedSize;  //SD卡 已使用容量 单位 k
	unsigned int EMMCTotalSize;	  //EMMC 总容量		单位 k
	unsigned int EMMCUsedSize;    //EMMC 已使用容量 单位 k
	unsigned int UDISKTotalSize;  
	unsigned int UDISKUsedSize;   
	char resv[56]; 
};


struct SnapImageInfo {
  char wgcard[8];
  unsigned int surplus;
  unsigned int year;
  unsigned char month;
  unsigned char mday;
  unsigned char hour;
  unsigned char minute;
  unsigned char second;
  char resv[33];
};


struct SubCodParam{
  /*! 子码流 开关 0 关 !0开    默认关闭。*/
  unsigned char subcod_enable;

  /*! 子码流分辨率   enum PIC_SIZE_E*/
  unsigned char subcod_pic_size;

  /*! 保留*/
  unsigned char resv[2];

  /*! 子码流码率  单位：kbps 默认1024 恒码率时为平均码率  变码率时为最大码率 */
  unsigned int subcod_rate;

  /*! 子码流码率控制模式    0 恒码率 !0 变码率 默认0*/
  unsigned char subcod_rcMode;

  /*! 子码流输出帧率  1~30 默认 30*/
  unsigned char subcod_frame_rate;

  /*! 保留 */
  char res[16];
};




/// 相机参数(512字节)。
struct CameraParam {
  /*! 相机流名称。 */
  char stream_url[128];

  /*! 相机流端口。 */
  short stream_port;

  /*! 相机控制端口。 */
  short control_port;

  /*! 视频OSD，支持最多两行。 */
  char video_osd[2][96];

  /*! 帧率。 */
  char fps;

  /*! 饱和度。取值范围：1~255。 */
  unsigned char saturation;

  /*! 亮度。取值范围：1~100。 */
  unsigned char brightness;

  /*! 自动曝光使能开关。 */
  char enable_ae;

  /*! 最大曝光时间。单位：毫秒。取值范围：0~100。 */
  short max_exposure;

  /*! 最大增益。单位：DB。取值范围：0~40。 */
  short max_gain;

  /*! 对比度。取值范围：0~128。 */
  short contrast;

   /*! 码率。单位：kbps。 */
  unsigned short video_br;

  /*! 视频流图像宽度。 */
  unsigned short video_width;

  /*! 视频流图像高度。 */
  unsigned short video_height;

  /*! 视频流编码类型。1：H264，2：MJPEG。 */
  unsigned char video_enc_type;

  /*! 视频旋转角度 0:默认值 1：顺时针旋转90度 2：顺时针旋转180度 3：顺时针旋转270度*/
  unsigned char video_rotate;

  /*! 外接显示屏标题osd*/
  char screen_osd_title[64];
  
  /*！畸形校变使能*/
  char ldc_enable;
  char ldc_recv;

  /*! 畸变程度 -300~500*/
  int ldc_ratio;

  /*! LCD显示项开关，一个bit位对应一项开关 参见 enum LcdDisplayItem */
  unsigned int lcd_display_options;
  
  /*! 0:关闭 1:息屏模式 2:图片屏保  */
  unsigned char screensaver_enable;

  /*! 宽动态开关 0:关 1：常开 2:按时间段开关 3:自动开关 */
  unsigned char wdr_enable;

  /*! 打开宽动态  时。取值范围：0~24。 */
  unsigned char wdr_open_hour;

  /*! 打开宽动态 分。取值范围：0~59。 */
  unsigned char wdr_open_minute;

   /*! 关闭宽动态 时。 */
  unsigned char wdr_close_hour;

  /*! 关闭宽动态 分。 */
  unsigned char wdr_close_minute;

  /*! 子码流 开关 0 关 !0开    默认关闭。*/
  unsigned char subcod_enable;

  /*! 子码流分辨率   enum PIC_SIZE_E*/
  unsigned char subcod_pic_size;

  /*! 子码流码率  单位：kbps 默认1024 恒码率时为平均码率  变码率时为最大码率 */
  unsigned int subcod_rate;

  /*! 子码流码率控制模式    0 恒码率 !0 变码率 默认0*/
  unsigned char subcod_rcMode;

  /*! 子码流输出帧率  1~30 默认 30*/
  unsigned char subcod_frame_rate;

  /*! lcd镜像开关 */
  char flipEnable;

  /*! h264叠字显示开关(1<<0地点编号 1<<1时间 1<<2ip) */
  char osd_display_options;

  /*! 比对成功人员显示项开关，一个bit位对应一项开关 */
  unsigned int person_display_options;
  
/*! 定时重启开关, 0：关 !0：开 */
  unsigned char restart_enable;

  /*! 定时重启时间（小时） */
  unsigned char restart_hour;

  /*! 定时重启时间（分钟） */
  unsigned char restart_minute;
  
    /*! 视频画面输出： 0：默认值，相机自带屏幕， 1：HDMI */
  char video_output_type;

  /*! 视频画面输出大小: 0：720p60 */
  char video_output_size;

  /*! 显示屏 亮度      [0~100] 默认 50*/
  unsigned char csc_luma;    

  /*! 显示屏 对比度      [0~100] 默认 50*/
  unsigned char csc_contrast;  

  /*! 显示屏 色度      [0~100] 默认 50*/
  unsigned char csc_hue;       

  /*! 显示屏 饱和度      [0~100] 默认 50*/
  unsigned char csc_satuature; 
  
   /*! lcd显示红外热像图 */
  char show_infrared_phy;

  /*! lcd显示调试信息 */
  char show_debug_infor;

  /*! 保留 */
  char resv_corre;

  /*! 温度校正参数 */
  float temp_corre;

  float temp_rang_upper;

  float temp_rang_lower;

  unsigned char aec_time;
  unsigned char audio_boost_enable;//AudioBoost
  short forehead_x_corrent;//[-100~100] 热力图额头框位置微调
  short forehead_y_corrent;//[-100~100]

   unsigned char switchstream;//0-关闭，1-可见光流 2-红外流 3-可见光流+红外流
  /*! 保留。 */
  char resv2[45];
};


/// 服务（32字节）。
struct AppServicesParam {
  /*! 配置服务。 */
  struct ServiceParam config_service;

  /*! 查询服务。 */
  struct ServiceParam query_service;

  /*! 日志服务。 */
  struct ServiceParam log_service;

  /*! 保留。 */
  struct ServiceParam resv_service;
};

/// 设备描述信息参数（224字节）。
struct DescriptionParam {
  /*! 点位编号。 */
  char addr_id[32];

  /*! 点位名称。 */
  char addr_name[96];

  /*! 设备编号。 */
  char device_id[32];

  /*! 设备类型 */
  char device_type;
  char selfdef[31];//自定义
  /*! 保留字段。 */
  char resv[32];
};


/// 系统应用私有参数。
struct AppPrivateParam {
  /*! 各系统自行定义。 */
  char resv[512];
};

/// TCP上传参数。
struct TcpClientParam 
{
  /*! 服务器IP地址。 */
  char ip[16];

  /*! 服务器端口。 */
  int port;

  /*! 使能开关（未使用，该字段仅为兼容旧协议而加入）。 */
  char enable;

  /*! 登录验证开关。 */
  unsigned char enable_verify;

  /*! 登录验证用户名。 */
  char user_name[16];

  /*! 登录验证密码。 */
  char passwd[17];

  /*！是否开启链路加密  */
  unsigned char enable_ssl;

  /*! 保留字段。 */
  char resv[64];
};



/// HTTP上传参数。
struct HttpClientParam {
  /*! 服务器IP地址。 */
  char ip[16];

  /*! 服务器端口。 */
  unsigned short port;

  /*! 服务URL。 */
  char url[102];
};

/// 4G信号信息
struct FourthGInfo
{
    int FGModuleReady; //4G模块ready
    int SIMReady;      //SIM卡ready
    int MCC;//MobileCountryCode;
    int MCN;//MobileNetworkCode; //中国移动: 0, 2, 7 中国联通:1, 6, 9  中国电信:3, 5, 11
    char dataCap[16]; //LTE etc..
    char ICCID[32];
    char IMSI[32];

    int signalStrength;
    int connected; //网络状态

	char GPSN[16]; //gps经度
	char GPSE[16]; //gps纬度
	unsigned int GPSNum; //gps卫星数量
	unsigned int state; // 注册状态
	unsigned int LAC; // 地区区域码
	unsigned int CID; // 基站码
	char resv[208];
};


/*
LCD_TYPE_WY_800_1280 = 0, // LCD_1280_800
LCD_TYPE_WY_720_1280 = 1, // LCD_1280_720
LCD_TYPE_HY070_800_1280 = 2,
LCD_TYPE_HY080_800_1280 = 3,
LCD_TYPE_CSDT050_720_1280 = 4, //Shenzhen China Star Draon Technology Co.,Ltd 华星龙
LCD_TYPE_CSDT080_800_1280 = 5, //Shenzhen China Star Draon Technology Co.,Ltd 华星龙
LCD_TYPE_PX080_800_1280 = 6,
LCD_TYPE_XHW070_1024_600 = 7,
LCD_TYPE_SQ080_800_1280 = 8,

*/

// 相机硬件信息

struct Hardware {
  /*! 芯片信息 */
  struct Chip {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32];
  } chip;

  /*! 主板信息 */
  struct Board {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32];
  } board;
  
  /*! 镜头信信息 */
  struct Sensor {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32];    
  } sensor;

  /*! 镜头电机信息 */
  struct Motor {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32]; 
    
    /*! 类型 */
    char type[16];

  } motor;
  
  /*! 显示屏信息 */
  struct Lcd {
    /*! 生产厂商 */
    char manu[32];

    /*! 型号 */
    char model[32];
	
	/* 保留 */
	char resv[4];
  } lcd;

  struct Flash {
    char manu[32];
    char model[32];
    int size;
  } flash;

  struct FourG {
    char manu[32];
    char model[32];
    int size;
  } fourg;
  
  struct WIFI {
    char manu[32];
    char model[32];
  } wifi;

  /*! 保留 */
  char resv[640];
};



/// 服器参数
struct UpdataServerParam
{
    char enable; //远程升级开关 0:关 !0:开
    char addrtype; //服务器地址类型 0:IP 1:域名 
    unsigned short port;//升级服务器端口
    char ip[64];//升级服务器IP地址
    char URL[60]; //升级服务器URL
	char resv[128];  //保留
};

/// MQTT上传参数。
struct MqttClientParam {
	/*! 服务器IP地址。 */
	char ip[16];

	/*! 服务器端口。 */
	int port;

	/*! 用户名*/
	char username[24];

	/*! 密码*/
	char password[24];

	/*! 客户端id */
	char clientid[24];

	/*! topic自定义头 */
	char topicex[24];
	char resv[4];
};


/// 穿透外网配置
struct ExtranetParam {
  /*! 以TCP客户端方式直达外网。 */
  union {
    struct TcpClientParam client;
	struct HttpClientParam http;
	struct MqttClientParam mqtt;
  };

  unsigned char enable;

  /*! 穿透模式，0：以TCP客户端方式直达外网。1：以http comet模式直达外网*/
  char mode;

  /*! 保留。 */
  char resv[6];
};

/// 服务认证参数（48字节）
struct AuthParam 
{
  /*! 服务认证开关。 */
  unsigned char enable;

  /*! 登录验证用户名。 */
  char user_name[16];

  /*! 登录验证密码。 */
  char passwd[17];

  /*! aes加密开关。 */
  char ase_de_enable;
  
  /*! 保留字段。 */
  char resv[13];

  /*! 双重认证密码长度 */
  int len;

  /*! 双重认证密码 */
  char SdkPassword[48];

  /*! aes加密 */
  unsigned char aes_cbc_de[16];
};


struct CapacityHistory
{
	/*! 最多存储的抓拍记录条数。 */
	int maxCapacity;

	/*! 已上传的抓拍记录条数。 */
	int uploadedNum;

	/*! 未上传的抓拍记录条数。 */
	int unUploadedNum;
	
	/*! 当前存储抓拍记录条数。 */
	int totalNum;

	char resv[32];
};

struct StorageCapacity
{
	/*! 最多支持添加人员名单数。 */
	int maxCapacity;

	/*! 已注册白名单条数。 */
	int whiteListNum;

	/*! 已注册黑名单条数。 */
	int blackListNum;
	
	/*! 已注册普通成员条数。 */
	int normalListNum;

	/*! 已注册成员条数。 */
	int totalNum;

	char resv[32];

};


/// 应用程序通用参数(512字节)。
struct AppCommonParam {
  struct AppServicesParam services;  //--------|-32字节--|
  struct DescriptionParam description;  //-----|-224字节-|
  struct ExtranetParam extranet;  //-----------|-128字节--|
  struct AuthParam auth;     //---------|-48字节--|
   /*! 保留字段。 */
  char resv[12];//-------------------------|-32字节-|
};

// 平台参数。

/// 服务(16字节)。
struct PlatformServicesParam {
  /*! 配置服务参数。 */
  struct ServiceParam config_service;

  /*! 流服务配置参数。 */
  struct ServiceParam stream_service;
};

/// 临时参数（32字节），应用程序重启后将失效。
struct TemporaryParam {
  /*! 开关视频流。 */
  char enable_video;

  /*! 各系统自行定义。 */
  char resv[27];
};


/// 平台参数(640字节)。
struct PlatformParam {
  /*! 服务。 */
  struct PlatformServicesParam services;

  /*! 相机。 */
  struct CameraParam camera;

  /*! 各平台可自行定义。 */
  char resv[112];
};


/// 流参数(64字节)。
struct StreamParam {
  /*! 视频流或JPEG流@ref ImageFormat 。 */
  int video_format;

  /*! 保留。 */
  char resv[60];
};



/// 应用程序参数(1024字节)。
struct AppParam {
  /*! 各应用程序公用参数。 */
  struct AppCommonParam common;

  /*! 私有参数。 */
  struct AppPrivateParam priv;
};

/// FTP上传参数。
struct FtpClientParam 
{
  /*! 服务器IP地址。 */
  char ip[16];

  /*! 服务器端口。 */
  int port;

  /*! 登录用户名。 */
  char user[15];

  /*! 登录密码。 */
  char password[15];

  /*! 上传目录。 */
  char pattern[70];
};

/// 连接参数。
struct ClientParam {
  /*! 模式@ref UploadMode 。 */
  char mode; /*0 未初始化。 1 TCP协议上传。 2 FTP协议上传。 3 HTTP协议上传。4 WebService上传 5 mqtt上传 */

  char enable_heart; //心跳开关 目前只控制http

  /*! 保留。 */
  char resv[2];

  /*! 服务器。 */
  union {
    FtpClientParam ftp;
    TcpClientParam tcp;
    HttpClientParam http;
	HttpClientParam web_service;
	MqttClientParam mqtt;
  };
};


// 数据传输。

/// 上传参数。
struct UploaderParam {
  /*! 保留字段。 */
  char resv[4];

  /*! 客户端连接参数。 */
  struct ClientParam client;
};


/// 输出参数。大小应固定为128字节。
struct OutputerParam {
  struct UploaderParam uploader;
};


// 地理位置定义。
struct GeoLocation {
  /*! 经度。 */
  float longitude;

  /*! 纬度。 */
  float latitude;

  /*! 海拔高度。 */
  float altitude;

  /*! 坐标系统。1: WGS_84，2: GCJ_02。 */
  unsigned char coordinate;

  /*! 保留。 */
  char resv[3];
};




struct GB28281Param {
  /*！开关 0：关 !0：开 */
  char enable;

  /*！IPC报警级别 */
  char alarm_priority;
  
  /*！心跳周期 单位s*/
  short heart_cycle;
  
  /*！SIP服务器ID */
  char sip_server_id[32];

  /*！SIP服务器IP地址 */
  char sip_server_ip[16];

  /*！SIP服务器端口 */
  unsigned short sip_server_port;

  /*！IPC发送端口 */
  unsigned short ipc_port;

  /*！IPC ID */
  char ipc_id[32];

  /*！IPC发送密码 */
  char ipc_passwd[24];

  /*！IPC报警ID */
  char alarm_id[32];
  
  /*！IPC有效期 当前时间之后的秒数 */
  unsigned int ipc_term;

  char sip_server_domain[32];
  char resv[96];
};




/// 人脸应用附加参数。
struct FaceExtraParam {
  /*! 人脸库ID。 */
  char face_set_id[32];

  /*! 地理位置。 */
  struct GeoLocation location;

  /*! 人脸库md5 */
  char face_set_md5[33];

  /*! 阿里云OSS的access_key */
  char oss_key_id[32];

  /*! 阿里云OSS的access_secret */
  char oss_key_secret[32];

  /*! 阿里云OSS数据中心位置 */
  char oss_endpoint[64];

  /*! 此设备在阿里云OSS存放位置的bucket名称  */
  char oss_bucket_name[64];

  /*! 相机http服务  0：关 1：开*/
  unsigned char http_server_enable;
  short http_server_port;

  /*! 保留 1*/
  char resv1[136];

 
  /*! 非测温时间段  */
  unsigned int startDetectTempTs;
  unsigned int endDetectTempTs;

  unsigned short c_Func;           //用户定制功能（custom function）
  unsigned short c_numberOfPasses1; //规定时间内允许通行的次数
  unsigned int c_startTime;        //开始时间(每天时间点的秒数，例如：9:30:30 ---> ( c_startTime = 9*60*60+30*60+30 ))
  unsigned int c_endTime;          //结束时间(同上)

  unsigned int c_startTime1;        //开始时间(每天时间点的秒数，例如：9:30:30 ---> ( c_startTime = 9*60*60+30*60+30 ))
  unsigned int c_endTime1;          //结束时间(同上)
  unsigned int c_numberOfPasses2;

  char resv2[68];

  /*gb28181参数*/	
  GB28281Param gb28181param;

  /*! 上传域名 */
  char uploader_domain[128];

  /*! 外网穿透使用域名 */
  char extra_net_domain[128];

  /*! 保留。 */
  char resv3[1004];

};










/// 子系统参数。
struct FaceSystemConfig {
  struct TemporaryParam temp;  //------28字节
  struct PlatformParam platform;  //---640字节
  struct StreamParam stream;      //---64字节
  struct AppParam app;  //-------------1024字节
  struct OutputerParam outputer;  //---128字节
  struct FaceExtraParam extraParam; //扩展参数
};

///// 坐标点定义。
//struct Point {
//  int x;
//  int y;
//};

/// 坐标点定义。
struct HA_Point {
  int x;
  int y;
};

struct SRect
{
  short x;
  short y;
  short widht;
  short height;
};


/// 语音拼接内容标记
enum SpeechSplicesFlag {
  /*! 无。*/
  SPEECH_SPLICE_FLAG_NONE = 0,

  /*! 拼接姓名。*/
  SPEECH_SPLICE_FLAG_NAME = 1,

  /*! 拼接角色定制内容 */
  SPEECH_SPLICE_FLAG_ROLE = 2,

 /*! 拼接人员自定义内容*/
  SPEECH_SPLICE_CUSTOMER_TEXT = 3 

};

struct FacePrivateParam {
  /*! 检测跟踪区域边数。 */
  char  roi_border_num;

  /*! 比对开关。取值为0时关闭，其它取值打开。 */
  char  enable_match;

  /*! 调试开关。 */
  char  enable_debug;
  
  /*! 深度去重复开关。1：开 0：关。 */
  char enable_dereplication;

  /*! 重复超时。超时将不再视为重复。仅在开启去重复时有效。单位：秒。取值范围：1~60。 */
  unsigned char replication_timeout;

  /*! 重复输出间隔。对于同一人员，上报人脸结果时间间隔。单位：秒。取值范围：1~120。 */
  unsigned char replication_interval;

  /*! 输出图像品质。 */
  char quality;

  /*! 名单过期自动清理功能开关。 */
  char enable_auto_clean;

  /*! 输出控制。 */
  int output_form;

  /*! 比对满分相似度值。取值范围：0.2~1.0。相似度达到该值时确信度为满分。 */
  float full_credit;

  /*! 相似度达到该值时认为比对成功（100分制）。 */
  short match_score;

  /*! 白名单GPIO输出开关（端口1）。1：开 0：关 */
  char gpio_enable_white;

  /*! 黑名单GPIO输出开关（端口2）。1：开 0：关 */
  char gpio_enable_black;

  /*! 暂未定义GPIO输出开关（端口3）。1：开 0：关 */
  char gpio_enable_resv;

  unsigned char serial_send_flag;
  unsigned char serial_databit[2];    // 数据位
  unsigned char serial_parity[2];     // 是否开始校验
  unsigned char serial_stopbit[2];    // 停止位
  int serial_baudrate[2];   // 波特率

  /*! 补光灯工作模式。1：常亮 2：自动控制 3：常闭。 */
  unsigned char light_mode;

  /*! 补光灯亮度等级(1~100)。 */
  unsigned char light_level;

  /*! 亮灯门限。画面亮度值低于该值时亮灯。亮度取值范围：1~255。 */
  unsigned char light_threshold;
  
  /*! 音量取值范围：0~100。 */
  unsigned char audio_volume;

  /*! 使用内置语音编号 */
  unsigned char audio_index;
  
  /*! 使用动态对比分数阈值，打开后将不使用配置的对比分数阈值。0：关 !0开*/
  char auto_score_enable;

  /*! 闸机控制类型：0继电器， 1韦根。 */
  unsigned char gateway_control_type;

  /*! 继电器序号。 */
  unsigned char alarm_index;

  /*! 继电器自动闭合持续时间，单位ms(500-5000)。 */
  unsigned short alarm_duration;

  /*! 韦根类型，WG26,WG34, WG36, WG44。目前只支持WG26, WG34。 */
  unsigned char wiegand_type;

  /*! 发行码，wg36 wg44需要此字段 */
  unsigned char wiegand_dcode;

  /*! 韦根门禁公共卡号。 */
  unsigned int wiegand_public_cardid;

  /*! 自动升成卡号时，韦根卡号范围，最小值。 */
  unsigned int wiegand_card_id_min;

  /*! 自动升成卡号时，韦根卡号范围，最大值。 */
  unsigned int wiegand_card_id_max;

  /*! 工作模式（@ref WorkMode ）。 */
  unsigned char work_mode;

  /*! 继电器状态，0表示常闭合 1表示常断开*/
  unsigned char gpio_state;

  /*! 无感录入（聚类）开关 */
  unsigned char cluster_enable;

  /*! 同一聚类通过的最大次数，当同一聚类通过的次数大于等于该次数时自动注册 */
  unsigned char max_pass_times;

  /*! 计算次数的时间间隔，在该时间间隔内只算通过一次 单位 秒*/
  unsigned int calc_times_interval;

  /*! 抓拍记录开关 0:关 !0:开*/
  char record_enable;

  /*! 断点续传开关，自动上传离线数据 */
  char record_resume_enable;

  /*人脸报警开关，打开后只要检测到人脸就报警开闸*/
  char face_alarm_enable;

 /*! 外接显示屏屏幕亮度 */
  char lcd_light_level;

  /*! gpio输入类型， 255就表示gpio 0表示wg26 1表示wg34*/
  int gpio_input_type;

  /*! gpio输入开关，0关，!0开*/
  char gpio_input_enable;

  /* 过滤未比对上的抓拍数据 0 不过滤 非0过滤  */
  char filter_not_match;

  /* 是否需要带安全帽 0 不需要 非0须要  */
  char must_wear_hat;

  /* 通行语音播放间隔 单位：秒  */
  char audio_interval;

  /* 韦根开闸时是否联动IO开闸 0:不联动 1:联动*/
  char ctrl_wiegand_io;
	
  /* 归一化保存图像开关 0:保存 !0:不保存 */
  char no_twist_image;

  /* 多人脸模式 0:单人脸检测 !0:多人脸检测 */
  char multipleFaceMod;

  /* 姓名隐私模式 0:关 !0:开         */
  char namePrivacy;

  /* 注册人员即将到期提醒时间 注: (有效时间 - alarm_expire) 至有效时间 内提醒  */
  unsigned int expire_alarm; 

  /*! 检测到人脸时打开所有继电器 。 */  
  char allGpioOut;

  /*! 抓拍记录保存位置 0：TF卡 1：相机EMMC  默认TF卡  重启生效*/
  char record_path;

  /*! 二维码识别 开关         0：关 1: 开 */
  char qr_code_enable;
  
  /*! 重复二维码    过滤间隔 0~255 S      默认 0*/
  unsigned char qr_code_interval;

  /*! 串口 解析 0:默认 1: 福瑞泰克 2: 韦尔讯 3: KPASS 4:铁军二维码 5:游艺云 6:六六测温 */
  unsigned char serial_parse;

  /*! 保留 */
  char resv_serial[1];

  /*! 温度单位 默认0:摄氏度 1:华氏度  */
  char temperature_unit;

  /* 热力图旋转 0:不旋转 2:旋转180度 */
  char heat_map_rorate; 

   /*! 体温限制数值。 */ 
  float temperature_limit; 
	
  /*! 体温限制开关。 0:关 1:开 */ 
  char temLimit_enable; 
  
   /* 是否需要 0 不需要 非0须要  */
  char must_wear_mask;

  /*! 高温多帧确认 */
  char high_temp_multi_confirm;

  /*! 刷身份证注册开关 0:关 1:开 */
  char id_card_register;

  /*! 比对开关拓展 */
  int enable_matchEx;

  /*! 对比模式 */
  unsigned char mache_mode;

  /*! 0:韦根输出韦根卡号  1:铁虎定制韦根输出注册人员ID 2:韦根输出注册人员ID 3:韦根输出自定制字段  */
  unsigned char wiegand_input_id;

  /*! 设置发送间隔 */
  unsigned short intervaltime;

  /*多人脸系统保留*/
  char resv_mface[16];

  /*! 检测跟踪区域坐标点。顺次连接构成检测跟踪区域。 */
  struct HA_Point roi[6];

  /*! 人脸检测最小人脸尺寸 */
  short min_face_size;

  /*! 串口配置服务开关，0：关 非0：开*/
  char serial_config_enable[2];
  
   /*! 大角度人脸过滤开关*/
  char valid_angle_enable;

  /*! 过滤人脸的最大角度，暂未使用*/
  char valid_angle;

  /*人脸质量过滤开关*/
  char valid_qvalue_enable;
  
  /*图像质量阈值*/
  char qvalue_threshold;

  /*! 人像数据同步开关 */
  char sync_enable;

  /*! 人像数据同步协议类型（暂未使用），/*0 未初始化。 1 TCP协议。 2 FTP协议。 3 HTTP协议。4 WebService*/
  char sync_mode;
  
  /*! 人像数据同步间隔时间 单位s*/
  unsigned short sync_interval;
  
  /*! 人像数据同步IP地址。 */
  char sync_ip[16];

  /*! 人像数据同步端口。 */
  unsigned short sync_port;
  
  /*! 人像数据同步URL。 */
  char sync_url[102];
  
  /*双目摄像图像差校正区域*/
  SRect bino_corret_area[3]; 

	/*! 语音拼接内容，按低字节->高字节 存拼接的内容标记 例如：char[0]=SPEECH_SPLICE_FLAG_ROLE 参见类型SpeechSplicesFlag */
  char speech_splices[4];
  
   /*! 普通人员语音播报内容（utf8编码）*/
  char normal_speech[32];
  
  /*! 白名单语音播报内容（utf8编码） */
  char white_speech[32];

  /*! 黑名单语音播报内容（utf8编码） */
  char black_speech[32];

  /*! 保存连接WIFI名称 */
  char wifi_ssid[32];
  
  char wifi_passwd[16];

  /*! 是否为围墙机 0:否 1:是 */
  unsigned char on_the_wall;

  unsigned char wifi_enable;

  /*! 双目摄像图像差校正区域4。 */
  SRect bino_corret_area4;

  /*! 是否允许同一张人脸（图片而非id）多次注册 */
  char allow_reg_same_face;

  /*! 全局网络检测开关 */
  char network_monitor_enable;

  /*! 配对相机IP。 */
  char pair_ip[16];

  /*! 是否启用配对。 */
  unsigned char enable_pair;

  /*! 配对相机开闸间隔。单位：秒。 */
  unsigned char pair_timeout;

  /*! 活体等级 1:弱等级 2:强等级 */
  unsigned char alive_level;

  /*! 是否为围墙机 0:否 1:是 */
  unsigned char resv1;
};

struct FtpInfo{
    char user_name[15];     //用户名
    char passwd[15];        //密码
    char path[70];          //路径
    char resv[2];           //空闲
};


union Upload_Infor {
	char upload_url[102];       //抓拍数据服务URL(http上传方式时有效)
	struct FtpInfo ftp_info;    //ftp上传参数信息(ftp上传时有效);
	char tcp_resv[102];         //tcp上传方式的保留字段
	char other_resv[102];       //其它上传方式保留字段
};                   //上传方式打开时，此结构可用



// 铁虎				 
struct TieHuHospitalWorksiteParam {
	/*! 上传url */
	char upload_url[128];

	/*! 进出 0:仅 1:出 */
	unsigned int in_out;

	char recv[892];
};

/// NVR对接
struct NVRWorksiteParam {
	
	/*! 抓拍上传开关 0:关 1:开 */
	unsigned char face_upload_enable;

	/*! 抓拍上传类型0:所有人上传 1:比对成功上传 2:黑名单上传 3:白名单上传 4:vip名单上传 5:陌生人上传 6:非白名单上传 */
	unsigned char face_upload_mod;

	/*! 抓拍信息内容 0x01:人脸信息 0x01 << 1:比对信息(多选)    */
	unsigned char face_upload_content;

	/*! 抓拍图片信息 0X1:特写图          0x1<<1:全景图 0x1<<2:注册图像(多选) */
	unsigned char face_upload_image;

	/*! 抓拍失败重传次数 -1:无限大 0~127:重传次数                */
	signed char upload_retransmit_times;

	/*! 保留 */
	char upload_resv[3];

	/*! 抓拍信息上传地址         */
	char face_upload_url[128];

	/*! 开启注册功能 0:关 1:开         */
	unsigned char session_reg_enable;

	/*! 保留   */
	char session_reg_resv[3];

	/*! 注册信息上传地址         */
	char session_reg_url[128];

	/*! 开启心跳功能 0:关 1:开         */
	unsigned char heartbeat_enable;

	/*! 心跳间隔 单位:秒 默认60         */
	unsigned char heartbeat_interval;

	/*! 开启sign验证功能 0:关 1:开         */
	//unsigned char heartbeat_sign_enable;

	/*! 保留   */
	char heartbeat_resv[2];

	/*! 心跳上传地址 */
	char heartbeat_url[128];
	/*! 保留   */
	char resv[624];
};


// 企业微信
struct PlatformWeixin {
	/*! 当前通讯录版本号 (置-1即可)*/
	int curPermVer;

	/*! 同步间隔 */
	unsigned int sunc_interval;

	/*! 心跳间隔 */
	unsigned int heatbeat_interval;

	/*! 请求路径 */
	char wssUrl[128];

	/*! 硬件类型编号 */
	char modelId[64];
	
	/*! 初始输入秘钥 */
	char iniSecreNo[64];

	/*! 当前秘钥 置空 */
	char secreNo[64];

	/*! 固件版本 置空 */
	char firmver[32];

	/*! 保留 */
	char resv[660];
};

// 腾晖平台
struct TenghuiParam {
	/*! 投屏设备ip地址*/
	char osd_device_ip[64];

	/*! 进出状态 0:进 1:出 */
	unsigned int in_out_state;


	/*! 投屏设备端口 默认 10083*/
	unsigned short osd_device_port;

	/*! iot平台端口 默认8082 */
	unsigned short iot_port;

	/*! iot平台域名 默认iot.velocityai.cn */
	char iot_domain[64];

	/*! IOT平台用户名       */
	char iot_user_name[64];

	/*! IOT平台密码       */
	char iot_password[64];

	/*! 数据中台url */
	char middle_officeres[128];

	/*! tv投屏开关 0:关 1:开 */
	char tv_enable;

	/*! 光速IOT平台开关 0:关 1:开 */
	char iot_enable;

	/*! 数据中台开关 0:关 1:开*/
	char middle_office_enable;
};
/// 华为云
struct HuaWeiParam {


	/*! mqtt地址*/
	char base_url[128];

	/*! 设备id*/
	char device_id[128];

	/*! 设备密匙*/
	char secret[128];
};

//能龙教育
struct Platform58 {

  /*! 同步时间间隔*/
  int sync_interval;

  /*! 推送服务器地址*/
  char attendance_url[64];

  /*! Appcode*/
  char appcode[128];

  /*! Appkey*/
  char appkey[128];

  /*! 学校id*/
  char schoolid[64];

  /*! 学校编号*/
  char schoolno[64];

  /*! 方向：0未知 1进 2出*/
  char attentype[4];

  /*! 场景：1校门 2宿舍 3教学楼 4校车 5自定义*/
  char locationtype[4];

  /*! 自定义地点(场景为5时必填)*/
  char location[128];
};

// 唐山
struct Platform56 {

	// 服务器基地址
	char base_url[128];

	// 设备SN
	char sn[128];

	// 私密
	char key[128];

	// 设备名称
	char device_name[128];

	// 行政区划代码
	char devision_code[20];

	// 设备位置代码
	char device_site[20];

	// 设备负责人
	char leader[64];

	// 负责人电话
	char leader_phone[64];

	// 经纬度
	char location[128];
};


///安一
struct Platform55 {

	/*! 服务器基地址*/
	char base_url[128];

	/*! 设备SN*/
	char sn[128];

	/*! 设备名称 */
	char device_name[128];

	/*! 同步时间间隔（s）*/
	int sync_interval;
};


///赤壁市建筑工人管理平台
struct Platform53 {

	// 服务器基地址
	char base_url[128];

	// 设备SN码
	char sn[128];

	// appid
	char appid[128];

	// appsecret
	char appsecret[128];

	// 进出类型(0进1出)
	int outtype;
};


/// 邯郸
struct Platform52 {

	/*! 心跳间隔。*/
	unsigned sync_interval;

	/*! 基础地址*/
	char base_url[64];

	/*! 设备id*/
	char device_id[64];
	/*! 小区标识*/
	char identification[40];

	/*! 凭证号*/
	char pzh[40];

	/*! 门禁点编号*/
	char mjdbh[40];

	/*! 关联门禁采集设备的信息标识*/
	char gldmj_cjsbxxbs[40];

	/*! 关联门禁抓拍设备的信息标识*/
	char gldzp_cjsbxxbs[40];

	/*! 采集系统编号*/
	char UserIdentify[40];

	/*! 门禁点名称*/
	char mc[40];

	/*! 经度*/
	char lgd[40];

	/*! 纬度*/
	char lat[40];
	/*! 位置类型 0其他 1出入口 2单元楼*/
	char wzlx[8];

	/*! 行进方向 1进 2出 3进出 9其他*/
	char xjfx[8];

	/*! 楼 栋 信 息 标识*/
	char ldxxbz[40];

	/*! 单元信息标识*/
	char dyxxbz[40];

	/*! 小区信息标识*/
	char xqxxbz[40];

	/*! 登记人姓名*/
	char djr_xm[40];

	/*! 登记人联系电话*/
	char djr_lxdh[40];

	/*! 治 安 管 理 信
	息 所 属 警 务
	责任区代码*/
	char ZAGLXXSSJWZRQDM[40];

	/*! 数 据 归 属 单
	位名称*/
	char SJGSDWMC[40];

	/*! 设备类型 01测温门禁 02普通门禁*/
	char devicetype[8];


};

///河北公安智慧系统
struct Platform51 {

	// 服务器基地址
	char base_url[128];

	// ApeID(20位)
	char ape_id[32];

	// 设备名
	char device_name[128];

	// 设备Model(默认108)
	char device_model[32];

	// 公安机关代码(12位)
	char police_code[32];

	// 社区编码(20位)
	char place_code[32];

	// 手动经度
	char longitude[32];

	// 手动纬度
	char latitude[32];

};

///沃访客FACE
struct Platform50 {

	/*! 服务器基地址*/
	char base_url[128];

	/*! 设备sn码*/
	char sn[128];

	/*! 组织id*/
	char orgid[128];

	/*! 0通用，1进门，2出门*/
	unsigned int outtype;
};


///湖南住建局
struct Platform49 {

	/*! 服务器基地址*/
	char base_url[64];

	/*! 供应商编码*/
	char supplier_code[64];

	/*! 供应商token*/
	char supplier_token[64];

	/*! 设备编号*/
	char device_id[64];

	/*! 考勤通道名称*/
	char channel[64];

	/*! 设备接入token*/
	char device_token[64];

	/*! 0表示入场，1表示出场*/
	unsigned int in_or_out;
};


/// 智奇实业
struct Platform48 {
	/*! 人员同步时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址（URL）。*/
	char base_url[128];

	/*! 设备编号。*/
	char device_id[128];


};

/// 沈阳平台2
struct Platform47 {

	/*! websocket地址。*/
	char base_url[128];

	/*! 设备编号。*/
	char device_number[128];

	/*! 保留 */
	char resv[252];
};


//陕西工地
struct Platform46 {
	/*! 基础地址。*/
	char base_url[64];

	/*! appid。*/
	char appid[64];

	/*! secretkey*/
	char secret[64];

	/*! 设备编号*/
	char device_id[64];
	/*! 进出1进 0出 */
	int in_out;
};

/// 武汉平台。
struct Platform12 {

	/*! 人员同步时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! 接入编号。*/
	char appid[128];

	/*! 接入秘钥。*/
	char appsecret[128];

	/*! 保留 */
	char resv[636];
};


struct ChengDuParam
{
	/*! 人员同步时间间隔。*/
	unsigned sync_interval;

	/*! 人员同步服务器基地址（URL）。*/
	char person_base_url[128];

	/*! 人员采集基地址（URL）。*/
	char caiji_base_url[128];

	/*! 设备编号。*/
	char device_id[128];

	/*! 采集设备编号。*/
	char caiji_id[128];

	/*! 数据加密密钥。*/
	char key[128];
};

// 济南住建平台（鼎立兴）
struct JiNanParam {
	/*! 同步人员间隔(分钟)*/
	int sync_time;

	/*! 服务器地址*/
	char base_url[64];

	/*! 准入标识*/
	char ticket[64];

	/*! 进出标识 1进 2出 3通用*/
	int outtype;
};


struct Platform45_tenghui {

	/*! 心跳时间间隔。*/
	unsigned int sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! appid*/
	char appid[50];

	/*! 密钥*/
	char secretKey[50];

	/*! 设备id。*/
	char device_id[50];

	/*! 1入场  2进场*/
	unsigned int in_or_out;

	TenghuiParam teng_hui_param;
};


/// A2CJHH-FMC03Y
struct Platform44 {
	/*! 心跳时间间隔(秒)。*/
	unsigned int sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! projectCode*/
	char projectCode[50];

	/*! projectKeyId*/
	char projectKeyId[50];

	/*! projectKeySecret*/
	char projectKeySecret[50];
	/*! keyId*/
	char keyId[50];
	/*! keySecret*/
	char keySecret[50];

	/*! 设备编码 */
	char device_id[50];
	
	/*! 进出口设置，1表示出，其他表示进*/
	unsigned int in_or_out;
};
struct AliIoTParam 
{
	char productKey[128]; 
	char productSecret[128]; 
	char deviceName[128]; //设备ID
	char deviceSecret[128]; //设备密码
	char resv[512]; //保留
};
///?湖北黄冈平台?。
struct Platform43 {
	/*! 服务器基地址。*/
	char base_url[128];

	/*! appid*/
	char appid[128];
	
	/*! 密钥*/
	char appsecret[128];
	
	/*! 设备编码*/
	char device_id[128];
	
	/*! 保留 */
	char resv[508];
};

struct Platform42{
	
	/*! 服务器基地址（URL）。*/
	char base_url[128]; 
	//用户名
	char username[64];
	//密码
	char passwd[64];

	char resv[500]; //保留
};

struct Platform1{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char personSynUrl[128]; //人员同步地址
	char signUploadUrl[128]; //签到上传地址
	char resv[636]; //保留
};


///安徽平台
struct Platform41 {

	/*! 心跳时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! 设备id。*/
	char device_id[128];

	/*! 进出口设置，1表示出，其他表示进*/
	unsigned int in_or_out;

	///*! 济公平台（分发） */
	//Platform1 jigong;

	///*! 0不分发，1济公 */
	//char jigong_enable;
	/*! 保留 */
	char resv[760];
};

/// 深圳住建局。
struct Platform40 {
	
	/*! 工程id*/
	char eng_id[128];
	
	/*! 进出口设置，1表示出，其他表示进*/
	unsigned int in_or_out;

	/*! 项目名称*/
	char project_name[256];

	/*! 授权码*/
	char Auth_code[64];

	/*! 保留 */
	char resv[572];
};


/// 福建住建局(顶点) 。
struct Platform39 {

	/*! 心跳时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! appid*/
	char appid[128];

	/*! 密钥*/
	char appkey[128];

	/*! 企业密钥*/
	char company_key[128];

	/*! 设备id。*/
	char device_id[96];

	TenghuiParam teng_hui_param;

};

/// Onet 。
struct Platform38 {
	/*! 产品ID*/
	char ProductId[128];

	/*! 产品KEY*/
	char ProductKey[128];

	/*! 设备名称*/
	char DeviceName[128];

	/*! 设备密钥*/
	char DeviceSecret[128];

	char resv[512]; //保留
};


// 多度平台
struct Platform37 {
	/*! 服务器基地址 */
	char base_url[128];
	/*! 设备安装位置 */
	char postion[128];
	/*! 通道号。*/
	int channel;
};

/// 上海电力系统 。
struct Platform36 {
	
	/*! 心跳时间间隔。*/
	unsigned int sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];
	
	/*! 设备id。*/
	char device_id[128];
	
	/*! 人脸识别门禁绑定的门房ID。*/
	int porterId;
	
	/*! 保留 */
	char resv[740];
};

// 佛山南海实名制
struct Platform35 {
	/*! 服务器基地址。*/
	char base_url[96];
	// appid
	char appid[96];
	//appsecret
	char appsecret[96];
	// 项目唯一码
	char onlycode[96];
	// 设备编码
	char device_number[48];

	/*进出门，1表示进，其他表示出*/
	int in_or_out;

	///施工单位的散列值
	char companyonlycode[48];

	TenghuiParam teng_hui_param;
};


// 会基
struct Platform34 {
	/*! 同步间隔。*/
	unsigned sync_interval;
	/*! 省份.城市。*/
	char city[128];
	// 接口安全校验秘钥
	char key[128];
	// 设备唯一识别码
	char device_number[128];

	char resv[636];
};


// 中山实名制
struct Platform33 {
	/*! 服务器基地址。*/
	char base_url[52];
	/*! 设备端端口*/
	char device_port[16];
	// 接口安全校验秘钥
	char token[80];
	// 设备唯一识别码
	char device_key[80];
	// 项目唯一标识码
	char project_num[80];
	/*进出门，1表示进，其他表示出*/
	int in_or_out;

	TenghuiParam teng_hui_param;
	/* 1云筑 0不上传 */
	char shanwei_enable;
	union {
		YunZhufenfaParam yunzhu;
	};
};




// 海南实名制
struct Platform32 {
	/*! 同步间隔。*/
	unsigned sync_interval;
	/*! 服务器基地址。*/
	char base_url[52];
	// 设备加密key
	char key[52];
	// 设备编号
	char device_code[52];
	// 腾辉考勤上传地址
	char tenghui_url[52];

	// 腾晖tcp ip
	char tenghui_ip[24];

	// 腾晖tcp 端口
	unsigned int tenghui_port;
	
	// 腾晖厂商编码
	char tenghui_code[40];

	// 腾晖设备编号
	char tenghui_devicecode[24];

	// 海南采集地址
	char cjurl[52];
	
	TenghuiParam teng_hui_param;
	/* 1云筑 0不上传 */
	char shanwei_enable;
	union {
		YunZhufenfaParam yunzhu;
	};
	/*! 海南采集编号*/
	char cjsn[24];
};



/// 阿里边缘网关
struct Platform31 {

	/*! 心跳时间间隔。*/
	unsigned sync_interval;

	/*! 服务器连接地址。*/
	char base_url_connect[128];

	/*! 服务器报活地址。*/
	char base_url_keepalive[128];

	/*! 服务器人脸识别地址。*/
	char base_url_recognize[128];

	/*! 服务器人脸获取底库地址。*/
	char base_url_photo[128];

	/*! 设备编号。*/
	char device_code[128];

	/*! 保留 */
	char resv[380];
};


/// 南方电网。
struct Platform30 {

	/*! 人员获取时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! 读取安全密钥里的序列号。*/
	char appkey[128];

	/*! 闸机供应商名称。*/
	char supplier[128];

	/*! 项目编码。*/
	char bid_no[128];

	/*! 设备类型。*/
	char device_type[128];

	/*! 进出场类型,1进2出*/
	int in_or_out;

	/*! 保留 */
	char resv[379];
};





// 中移动行业开发平台参数
struct Platform29 {
	// 产品编号
	char productId[32];
	// 设备接入码
	char productKey[32];
	// IMEI
	char imei[32];
	// 手动纬度
	char latitude[16];
	// 手动经度
	char longitude[16];

	char resv[896];
};

/// 福建地铁平台 。
struct Platform28 {

	/*! 服务器基地址。*/
	char base_url[128];

	/*! 考勤上传地址。*/
	char base_url_attance[128];

	/*! sn。*/
	char device_no[128];

	/*! 保留 */
	char resv[768];
};


/// linkface2.0 。
struct Platform27 {
	char productKey[128];
	char productSecret[128];
	char deviceName[128]; //设备ID
	char deviceSecret[128]; //设备密码
	char resv[512]; //保留
};


/// 呼呼智慧工地平台 。
struct Platform26 {

	/*! 心跳时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! applyId。*/
	char applyId[128];

	/*! sn。*/
	char device_no[128];

	//*0进1出,其他就没无此字段//
	int in_or_out;

	/*! 保留 */
	char resv[632];
};


/// 中铁建工智慧管控云平台 。
struct Platform25 {

	/*! 心跳时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! x_api_key。*/
	char x_api_key[128];

	/*! 闸机名称。*/
	char gate_name[128];

	//*0进1出//
	int in_or_out;

	/*! 保留 */
	char resv[764];
};


/// 喜鹊云社区平台。
struct Platform24 {

	/*! 服务器基地址。*/
	char base_url[128];

	/*! 设备id。*/
	char device_number[128];

	/*! 秘钥*/
	char secret_key[128];

	/*! 保留 */
	char resv[640];
};



/// 宁图平台。
struct Platform23 {

	/*! 心跳时间间隔。*/
	unsigned sync_interval;

	/*! 服务器ip地址。*/
	char server_ip[32];

	/*! 服务器控制tcp端口。*/
	unsigned short tcp_port;

	/*! 服务器心跳udp端口。*/
	unsigned short udp_port;

	/*! 设备编码。*/
	char device_code[128];

	/*! 接入秘钥。*/
	char key[128];

	/*! 保留 */
	char resv[728];
};

/// 烽火平台。
struct Platform22 {

	/*! 人脸同步时间间隔。*/
	unsigned sync_interval;

	/*! 服务器地址。*/
	char base_url[128];

	/*! 设备编号。*/
	char device_numer[128];

	//*进出，1进2出//
	int in_or_out;

	/*! 保留 */
	char resv[760];
};

/// 信禾巴士平台。
struct Platform21 {

	/*! 服务器地址。*/
	char base_url[128];

	/*! 检票站场*/
	char check_station[128];

	/*! 检票站点*/
	char check_address[128];

	/*! 闸机工号*/
	char check_oper[128];

	/*! 检票口号*/
	char check_no[128];

	/*! 保留 */
	char resv[384];
};



/// 黑龙江住建局住建局。
struct Platform20 {

	/*! 人脸同步时间间隔。*/
	unsigned sync_interval;

	/*! 服务器地址。*/
	char base_url[128];

	/*! appkey。*/
	char appkey[128];

	/*! appsecret。*/
	char appsecret[128];

	/*! 项目工程施工许可证编号*/
	char numer[32];

	/*!苏中考勤上传地址 */
	char base_url_suzhong[128];

	/*! 设备编码。*/
	char device_no[64];

	/*! 项目编号*/
	char project_code[128];
	/*! 标识*/
	char action[128];

	/*! 标识2*/
	char project_code_id[128];

	/*！0进1出*/
	int in_or_out;

	/*! 保留 */
	char resv[24];
};


/// 云启平台。
struct Platform19 {

	/*! 人脸同步时间间隔。*/
	unsigned sync_interval;

	/*! 服务器地址。*/
	char base_url[128];

	/*! 密钥。*/
	char privatekey[128];

	/*! 保留 */
	char resv[760];
};

/// 辽宁盘锦住建局。
struct Platform18 {

	/*! 人脸同步时间间隔。*/
	unsigned sync_interval;

	/*! 服务器地址。*/
	char base_url[128];

	/*!苏中考勤上传地址 */
	char base_url_suzhong[128];

	/*! 设备编码。*/
	char device_no[128];

	/*! 项目编号*/
	char project_code[128];
	/*! 标识*/
	char action[128];

	/*! 标识2*/
	char project_code_id[128];

	/*！0进1出*/
	int in_or_out;

	/*! 保留 */
	char resv[248];
};


/// 山西住建局。
struct Platform17 {

	/*! 心跳时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! token。*/
	char token[128];

	/*! appsecret。*/
	char key[128];

	/*! 服务器类型*/
	int type;

	/*! 保留 */
	char resv[363];
};


/// 数字雄安建设管理平台。
struct Platform16 {

	/*! 人员同步时间间隔。*/
	unsigned sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! appkey。*/
	char appkey[128];

	/*! appsecret。*/
	char appsecret[128];

	/* 人员类型 */
	char person_ytpe[100];
	/*! 1分发云筑*/
	char fenfa_enable;

	union {
	YunZhufenfaParam yunzhu;
	};

};

 /// 黄石汇聚平台。
struct Platform15 {
	/*! 服务器基地址。*/
	char base_url[128];

	/*! 用户*/
	char user_name[128];

	/*! 秘钥*/
	char secret_key[128];

	/*!设备位置 */
	char device_location[128];

	/*! 设备名称。*/
	char device_name[128];

	/*! 设备编号*/
	char device_no[128];

	/*! 小区编号*/
	char village_no[128];

	/*! 出入方向*/
	int in_out;

	/*! 进出门类型*/
	int in_out_type;

	/*! 保留 */
	char resv[120];
};


/// 沈阳住建局平台。
struct Platform14 {

  /*! 服务器基地址。*/
  char base_url[128];

  /*!苏中考勤上传地址 */
  char base_url_suzhong[128];

  /*! 设备编号。*/
  char device_number[128];

  /*! 项目编号*/
  char project_code[128];
  /*! 标识*/
  char action[128];

  /*! 标识2*/
  char project_code_id[128];

  /*！0进1出*/
  int in_or_out;

  /*! 保留 */
  char resv[252];
};


/// 山东省农民工工资支付平台。
struct Platform13 {

  /*! 服务器基地址。*/
  char base_url[128];

  /*! 接入编号。*/
  char appid[128];

  /*! 接入秘钥。*/
  char appsecret[128];

  char md5_key[64];

  TenghuiParam teng_hui_param;
};


/// 广联达平台。
struct Platform11 {

  /*! iot服务器基地址。*/
  char iot_base_url[128];

  /*! 硬件服务器基地址。*/
  char device_base_url[128];

  /*! 接入编号。*/
  char appid[128];

  /*! 接入秘钥。*/
  char sign[128];

  /*工程id*/
  char project_id[128];

  /*设备编号*/
  char device_number[128];

  /*进出门类型0表示出，其他表示进*/
  int in_or_out;
  /*! 保留 */
  char resv[252];
};



/// 广东平台。
struct Platform10 {

  /*! 人员同步时间间隔。*/
  unsigned sync_interval;

  /*! 服务器基地址。*/
  char base_url[128];

  /*! 接入编号。*/
  char number[128];

  /*! 接入秘钥。*/
  char key[128];

  /*! 人员获取URL*/
  char employee[128];

  /*! 上报人员获取URL*/
  char messsage[128];

  /*! 考勤上传*/
  char attendance[128];

  /*! 考试签到上传*/
  char examination[128];

  /*! 保留 */
  char resv[149];
};



struct ShanWeiParam {
	/*汕尾市用工实名基地址*/
	char shanwei_baseurl[48];

	/*项目编号*/
	char project_id[48];

	/* 授权账号*/
	char api_key[32];

	/* 授权密钥*/
	char api_secret[36];

	/*设备供应商编码*/
	char supplier_id[48];

	/*!统一社会信用代码*/
	char credit_code[32];

	/*设备序列号*/
	char client_id[32];

	/*设备密钥*/
	char client_secret[48];

};


/// 江门住建局
struct JiangMenParam {
	/*! 心跳时间间隔。*/
	unsigned int sync_interval;

	/*! 服务器基地址。*/
	char base_url[128];

	/*! 项目 key*/
	char api_key[50];

	/*! 项目token*/
	char token[50];

	/*！通道名称*/
	char channel[50];

	/*!1进   0出*/
	unsigned int in_or_out;
	char appid[40];//云筑appid
	char secretkey[40];//云筑密钥

};

/// 湛江
struct ZhanJiangParam {
	/*! 服务器基地址。*/
	char base_url[128];

	/*! 设备id*/
	char device_id[56];
};

/// 福建平台。
struct Platform9 {

	/*! 人员同步时间间隔。*/
	unsigned sync_interval;

	/*! 服务器ip地址。*/
	char server_ip[32];

	/*! 服务器port。*/
	unsigned short port;

	/*! 厂商识别码。*/
	char code[52];

	/*! 设备编码。*/
	char device_code[52];

	/*! 海南采集地址。*/
	char cjurl[52];
	TenghuiParam teng_hui_param;

	/* 不上传开关 打开后不上传 */
	char unupload_enable;
	/* 1汕尾 2云筑3江门4湛江 0不上传 */
	char shanwei_enable;

	union {
		ShanWeiParam shawei; // 汕尾平台
		YunZhufenfaParam yunzhu; // 云筑平台
		struct JiangMenParam jiangmen;
		struct ZhanJiangParam zhanjiang;
	};
};

/// 杭州品茗
struct KeChuangParam {


   /*! 基础地址*/
   char base_url[128];

   /*! 设备编号。*/
  char device_id[52];

   /*! 项目编号。*/
  char projectCode[52];

   /*! 通道*/
  char deviceName[52];

  /*!进出 1入 2出*/
  char direction[52];
  
   /*!企业id*/
  char cono[52];

  /*密匙*/
  char key[52];

};

/// 广西省平台
struct GuangXiParam {

  /*! 心跳时间间隔。*/
  unsigned int sync_interval;

  /*! 服务器基地址。*/
  char base_url[128];

  /*! api key*/
  char api_key[50];

  /*! api secret*/
  char api_secret[50];

  /*! 设备编号。*/
  char device_id[50];
  /*! 1进  2出*/
  unsigned int in_or_out;

  TenghuiParam teng_hui_param;

};

// GanZhouParam
struct Platform8 {
  /*! 人员同步时间间隔。*/
    unsigned sync_interval;
    /*! 服务器基地址（URL）。*/
    char base_url[128];
    char project_code[128]; //工程编码
    char project_key[128]; //工程key
    char project_secret[128]; //工程秘钥
    char supplier_key[128]; //供应商key
    char supplier_secret[128]; //供应商秘钥
    char resv[252]; //保留
};


struct Platform7 {
 
  unsigned sync_interval;  // 人员同步时间间隔。
  char base_url[128];    // 服务器基地址（URL）。
  char key[128]; // ACS 密钥 
  char resv[764];
};



struct Platform6 {
  unsigned sync_interval; // 人员同步时间间隔
  char base_url[128]; // 服务器基地址
  char ProjectID[128]; // 项目ID
  char Key[128];
  char Picurl[256]; //图片路径
  char resv[380]; // 保留
};


struct Platform5{
	char productKey[128]; 
	char productSecret[128]; 
	char deviceName[128]; //设备ID
	char deviceSecret[128]; //设备密码
	char resv[512]; //保留
};


struct Platform4{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char messagePushUrl[128]; //消息推送地址
	char userName[64]; //消息推送用户名
	char password[64]; //消息推送密码
	char itemNumber[64]; //项目编号
	char appKey[64]; //  appKey
	char appSecret[64]; //appSecret
	char resv[444]; //保留
};

struct Platform3{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char messagePushUrl[128]; //消息推送地址
	char userName[64]; //消息推送用户名
	char password[64]; //消息推送密码
	char resv[636]; //保留
};

struct JiGongParam
{
	char jguploadurl[64];//服务器基地址
	char jgdevice[24];//设备编号
	char in_out;//进出 2进 3出
};

struct Platform2 {
	/*! 人员同步时间间隔。*/
	unsigned sync_interval;

	/*! 人员同步服务器基地址（URL）。*/
	char person_base_url[128];

	/*! 人员采集基地址（URL）。*/
	char caiji_base_url[128];

	/*! 设备编号。*/
	char device_id[128];

	/*! 采集设备编号。*/
	char caiji_id[128];

	/*! 数据加密密钥。*/
	char key[128];
	char handout;//0不分发 1济公
	struct JiGongParam jgong;//济公平台
	//char resv[380]; //保留
};

struct Platform0{
	unsigned int synInterval; //同步时间间隔
	char serverUrl[128]; //服务器基地址
	char resv[892]; //保留
};

/// 科道AIOT
struct KedaoParam {

  /*! 心跳时间间隔*/
  int heartbeat_interval;

  /*! 服务器地址*/
  char base_url[128];

  /*! 设备id*/
  char deviceid[32];

  /*! apikey*/
  char api_key[128];

  /*! apisecret*/
  char api_secret[128];

  /*! 进出状态 1进 其他出*/
  int outtype;
};

/// 横琴
struct HengQinParam{
	/*! 心跳时间间隔。*/
	unsigned int sync_interval;
	/*! 服务器基地址。*/
	char base_url[128];
	/*! 设备id*/
	char device_id[56];
	/*! 设备名称*/
	char device_name[56];
	struct TenghuiParam tenghui;
};

///金地门禁平台
struct JinDiParam {
	/*! 基础地址*/
	char base_url[128];

	/*! fid。*/
	char fid[52];

	/*! key*/
	char key[52];

	/*!sipid*/
	char sipid[52];
};

// 邦客惠
struct BangKeHuiParam {
  /*! 服务器基地址*/
  char base_url[64];

  /*! 商户号*/
  char mer_code[64];

  /*! 终端imei*/
  char imei[64];

  /*! 经度*/
  char longitude[32];
  
  /*! 纬度*/
  char latitude[32];

  /*! 进出标识 1进 2出*/
  int outtype;
};
//河南健康平台
struct HeNanParam
{
	/*! 心跳时间间隔*/
	int heartbeat_interval;
	/*! 服务器地址*/
	char base_url[128];
	/*! 设备编号*/
	char deviceid[32];
	/*! 设备名称*/
	char devicename[32];
	/*! licenseCode*/
	char licenseCode[48];
	/*! sm4密钥*/
	char sm4_secret[128];
	/*! aes密钥*/
	char aes_secret[128];
	/*mqtt地址*/
	char mqtt_url[48];
	/*mqtt用户*/
	char mqtt_ser[40];
	/*mqtt_pwd*/
	char mqtt_pwd[40];

};


// 光越
struct GuangYueParam {
  /*! 心跳间隔(分钟) */
  int heartbeat_time;

  /*! 同步人员间隔(分钟) */
  int sync_time;

  /*! 服务器地址*/
  char base_url[64];

  /*! 设备序列号*/
  char device_sn[64];

  /*! Client ID*/
  char client_id[64];

  /*! Client Secret*/
  char client_secret[64];

  /*! 进出方向 1进 2出*/
  int direction;
};

// 云南建筑工人平台平台
struct YunNanParam
{
	/*! 服务器基地址*/
	char base_url[128];


	char api_key[64];

	char api_version[64];

	char client_serial[64];

	char facephoto_mode[16];

	char api_secret[256];
	char s_serial[64];
	/*! out:出；in：进 free:自动*/
	char in_or_out[4];

	/*!通行方式 */
	unsigned int passway;
};



/// 中建云筑网 。
struct Platform45 {

	/*! 心跳时间间隔。*/
	unsigned int sync_interval;

	/*! 服务器基地址。*/
	char base_url[127];

	/*! 1普通版本 其他健康码版本 */
	unsigned char version;

	/*! appid*/
	char appid[50];

	/*! 密钥*/
	char secretKey[50];

	/*! 设备id。*/
	char device_id[50];

	/*! 1入场  2进场*/
	unsigned int in_or_out;

	/*! 0不分发 1.成都住建局 2武汉平台 3山西广联达 4济南 5湖南住建局 6智奇实业 7数字雄安建设管理平台 8山东农民工工资支付平台*/
	char choice;
	union {
		ChengDuParam chengdu;
		Platform12   wuhan;
		Platform46   shanxi;
		JiNanParam   jinan;
		Platform49   hunan;
		Platform48	 zhiqi;
		Platform16	 xiongan;
		Platform13   shandong;
	};
};



struct PlatformAccess{
	unsigned char enable; //是否开启接入功能 0:关 1:开
	char ID [67] ; //接入方ID 000002(济工网);  
	union {
		PlatformWeixin formWeixin; // 上传方式 weixing (企业微信) 。
		NVRWorksiteParam formnvr; // 上传方式 nvr (同为nvr)
		TieHuHospitalWorksiteParam tiehu; // 上传方式 threehospital (铁虎医院)
		Platform0 form0; //上传方式  000001(共用);
		Platform1 form1; //上传方式  000002(济工网); 
		Platform2 form2; //上传方式  000003(成都住建部平台); 
		Platform3 form3; //上传方式  000004(浙江工汇);
		Platform4 form4; //上传方式  000005(浙江工汇==>>成都住建部平台);
		Platform5 form5; //上传方式  000006(阿里云IOT);
		Platform6 form6; //上传方式  000007(山东聊城);
		Platform7 form7; //上传方式  000008(奥普ACS);
		Platform8 form8; //上传方式  000009(赣州劳动实名制);
		Platform9 form9; //上传方式  000010(福建平台)
		Platform10 form10; //上传方式  000011(广东平台)
		Platform11 form11; //上传方式  000012(广联达平台)
		Platform12 form12; //上传方式  000013(武汉平台)
		Platform13 form13; //上传方式  000014(山东省农民工工资支付平台)
		Platform14 form14;/// 上传方式  000015 (沈阳住建局平台) 
		Platform15 form15;/// 上传方式  000016 (黄石汇聚平台)
		Platform16 form16; // 上传方式  000017 (数字雄安建设管理平台) 
		Platform17 form17; // 上传方式  000018 (山西住建局)
		Platform18 form18; // 上传方式  000019 (辽宁盘锦住建局)
		Platform19 form19; // 上传方式  000020 (云启平台)
		Platform20 form20;  // 上传方式  000021 (黑龙江住建局住建局)					
		Platform21 form21; /// 上传方式  000022 (信禾巴士平台)
		Platform22 form22; /// 上传方式  000023 (烽火平台)
		Platform23 form23; /// 上传方式  000024 (宁图平台)
		Platform24 form24; /// 上传方式  000025 (喜鹊云社区平台)
		Platform25 form25; /// 上传方式  000026 (中铁建工智慧管控云平台)
		Platform26 form26; /// 上传方式  000027 (呼呼智慧工地平台)
		Platform27 form27; /// 上传方式  000028	(linkface2.0)
		Platform28 form28; /// 上传方式  000029	(福建地铁平台)
		Platform29 form29; /// 上传方式  000030	(中移动行业开发平台参数)
		Platform30 form30; /// 上传方式  000031	(南方电网)
		Platform31 form31; /// 上传方式  000032	(南方电网阿里边缘网关)
		Platform32 form32; /// 上传方式  000033	(海南实名制)
		Platform33 form33; /// 上传方式  000034	(中山实名制)
		Platform34 form34; /// 上传方式  000035	(会基)
		Platform35 form35; /// 上传方式  000036	(佛山南海实名制)		   
		Platform36 form36; /// 上传方式  000037 (上海电力系统) 
		Platform37 form37; /// 上传方式	 000038 (多度平台) 
		Platform38 form38; /// 上传方式	 000039 (Onet) 
		Platform39 form39; /// 上传方式	 000040 (福建住建局(顶点)) 
		Platform40 form40; /// 上传方式	 000041 (深圳住建局) 
		Platform41 form41; /// 上传方式	 000042 (安徽平台) 
		Platform42 form42; /// 上传方式	 000043 (天翼阅云) 
		Platform43 form43; /// 上传方式	 000044 (湖北黄冈) 
		Platform44 form44; /// 上传方式  000045 (A2CJHH-FMC03Y)
		Platform45 form45; /// 上传方式  000046 (中建云筑网)
		Platform46 form46; /// 上传方式  000047 (陕西工地)
		Platform47 form47; /// 上传方式  000048 (沈阳平台2)
		Platform48 form48; /// 上传方式  000049 (智奇实业)
		Platform49 form49; /// 上传方式  000050 (湖南住建局)
		AliIoTParam  aliIot;//material
		HuaWeiParam huawei;// huawei 华为云
		Platform50 form50; /// 上传方式  000051 (沃访客FACE)
		Platform51 form51; /// 上传方式  000052 (河北公安智慧系统)
		Platform52 form52; /// 上传方式  000053 (邯郸)
		Platform53 form53; /// 上传方式  000054 (赤壁市建筑工人管理平台)
		Platform23 form54; /// 上传方式  000055 (闪电face)
		Platform55 form55; /// 上传方式  000056 (安一)
		Platform56 form56; /// 上传方式  000057 (唐山)
		Platform58 form58; /// 上传方式  000059 (能龙教育)
		KeChuangParam kechuang; /// 上传方式  000058 (杭州品名)
		GuangXiParam guangxi;//上传方式  000060 (广西省平台)
    	KedaoParam kedao;  /// 上传方式  000061（科道AIOT）
		JiangMenParam jiangmen;//上传方式  000062 (江门住建局)
		struct HengQinParam hengqin;//上传方式  000063  (横琴)
		struct JinDiParam jindi;//上传方式  000064 金地门禁平台)
		BangKeHuiParam bangkehui; //上传方式  000065 (邦客惠)
		struct HeNanParam henan; //000066  (河南健康平台)
		JiNanParam jinan;//上传方式    000067 (济南住建平台)
		GuangYueParam guangyue;///上传方式  000068 (光越)
		YunNanParam yunnan;//上传方式  000069 
		char resv[1024]; //保留
	};
};

struct FaceAppParam
{
    char dev_no[32];            //设备编号
    char point_no[32];          //点位编号
    char point_name[96];        //点位名称
    char resv1[32];             //保留字段1
    unsigned char heart_beat_interval;//心跳时间间隔
    char extranet_enale;        //外网控制开关
    unsigned short extranet_port;//外网控制服务器端口
    char extranet_ip[16];       //外网控制服务器ip
    unsigned char verify_enable;//开启登录验证后，客户端在与服务器建立连接后将自动发送登录验证请求。注：抓拍机作为客户端。1：开启登录验证 0：关闭登录验证
    char user_name[15];         //登录验证用户名
    char passwd[16];            //登录验证密码
    unsigned char resv2[12];    //保留字段2
    unsigned short upload_mode; //数据上传方式0：关闭上传 1：TCP方式 2：FTP方式 3：HTTP方式
    unsigned short upload_port; //服务器端口
    char upload_ip[16];         //服务器IP
    Upload_Infor upload_info;   //上传方式打开时，此结构可用
    unsigned char cam_mode;     //相机工作模式。1：自动模式 2：在线模式 3：离线模式
    char resv3[17];             //保留字段3
    int match_enable;           //比对开关  
    int match_score;            //比对确信分数
    int dereplication_enable;   //重复过滤开关
    int dereplication_interval; //重复超时/输出间隔时间
    unsigned short output_mode; //图像输出形式  0:关闭图像输出 1：全景图 2：特写 4：比对模板 8:特征数据
	char autothresholdScore;    //自动阈值模式下，动态阈值(比对分数)
    char resv4[255];            //保留字段4
};


struct QueryCondition
{
    char faceID[20];        //人员ID
    char faceName[16];      //人员姓名
    unsigned int wgCardNO;  //韦根协议门禁卡号
    unsigned int timeStart; //有效期截止时间的查询起点
    unsigned int timeEnd;   //有效期截止d时间的查询终点
    unsigned int time1Start; //有效期起始时间的查询起点
    unsigned int time1End;   //有效期起始时间的查询终点
	unsigned long long  wgCardNOLong; //韦根协议门禁卡号  wgCardNO长度不满足时使用此项
	char faceNameEx [64]; //人员信息拓展人员信息长于15字节时使用此项
	char customerID[64]; // 用户自定义字段
    unsigned char resv[116];
};

/// 抓拍记录查询条件
struct RecordCondition {
  // 抓拍图像数据标记 0：不需要，非0：需要。
  char img_flag;

  // 注册图像数据标记 0：不需要，非0：需要。
  char reg_img_flag;

  // 保留 以0填充
  char resv1[2];

  // 匹配模式，0精确匹配，非0模糊匹配
  unsigned short query_mode;

  // 条件组合标记
  unsigned short condition_flag;    //RecordQueryFlag

  // 抓拍时间区间起点
  unsigned int time_start;

  // 抓拍时间区间终点
  unsigned int time_end;

  // 比对分数区间起点
  short score_start;

  // 比对分数区间终点
  short score_end;

  // 性别
  unsigned char sex;

  // 年龄区间起点
  unsigned char age_start;

  // 年龄区间终点
  unsigned char age_end;

  // 保留 以0填充
  char resv2[17];
  
  // 比对上的人员ID
  char person_id[20]; 
  
  // 比对上的人员姓名
  char person_name[16];
  
  // 人像质量区间起点
  unsigned char qvalue_start;

  // 人像质量区间终点
  unsigned char qvalue_end;

  // 是否已经上传 1:表示已经上传 0：表示未上传
  char upload_state;

  char resv4;

  // 序列号
  unsigned int suquce;

	// 比对上的人员姓名扩展
	char person_name_ext[64];

	// 平台id
	char worksite_id[16];

	char additional[512];

  // 保留 以0填充
  char resv3[176];
};

struct SnapshotImage
{
    // 快照时间戳 秒
    unsigned int  timeStamp_s;

    // 快照时间戳 毫秒
    unsigned int  timeStamp_u;

    // 快照图像长度
    int snapImageSize;

    // 快照图像
    unsigned char *snapImage;
	
	// 红外图像长度
	int infraredImageSize;

	// 红外图像大小
	unsigned char* infraredImage;
};

//开闸纪录，相机开闸后上报的开闸纪录
struct AlarmInfoRecord  
{
    char cameraID[32];      //相机编号
    char alarmTime[20];     //开闸时间     格式：2018/3/6    16:38:20
    unsigned char alarmDeviceType;//开闸设备类型，0：继电器 1：韦根设备
    char resv[3];           //保留
    char personID[20];     //人员id，报警开闸的人员id
    unsigned int alarmDeviceId;//开闸设备id，外设类型为继电器时，外设ID为GPIO端口号。外设类型为支持韦根协议的设备时，外设ID为卡号。
	unsigned long long  wgCardNOLong;   // 韦根门禁卡号加长 在alarmDeviceId长度不满足时使用此成员
};


// 音频播放信息 相机播放音频后触发
struct AudioPlayInfo
{
	char audio_type; // 播放方式 0:本地音频文件 1:tts语言播放
	union {
		struct  {
			char txt[64];
		}tts; // tts语音内容
		struct audio_info {
			int audio_id;
		}audio_info; // 本地音频文件ID
		char resv[128];
	}info;
};


//开闸请求，当相机处于在线模式时，需要开闸时会向平台发送该请求
struct AlarmRequest
{
	char cameraID[32];      //相机编号
	char personID[20];     //人员id，需要开闸的人员id
	char requestTime[20];   //请求时间     格式：2018/3/6    16:38:20 
	unsigned char alarmDeviceType;//请求的开闸设备类型，0：继电器 1：韦根设备
	unsigned char alarmDeviceState;//当前开闸设备状态，0：未启用 1：启用
	char resv[2];           //保留
	unsigned int alarmDeviceId;//开闸设备id，外设类型为继电器时，外设ID为GPIO端口号。外设类型为支持韦根协议的设备时，外设ID为卡号。
	unsigned long long  wgCardNOLong;   // 韦根门禁卡号加长 在alarmDeviceId长度不满足时使用此成员
	int type; // 请求开闸类型 0 普通请求 1:用户密码验证开闸 2: 二维码开闸
	float body_temp; //体温
	char recv[1024];
};


enum ComponentType
{
	HA_COMPONENT_TYPE_NONE = 0,               //未定义
	HA_COMPONENT_TYPE_BACKGROUND_IMAGE,		//背景图片      图像 包含图像数据
	HA_COMPONENT_TYPE_IP,						//IP显示		文字
	HA_COMPONENT_TYPE_REGISTER_NUM,			//注册人数		文字
	HA_COMPONENT_TYPE_TIME,					//时间显示		文字
	HA_COMPONENT_TYPE_TITLE,					//标题显示位置	文字
	HA_COMPONENT_TYPE_NEWS,					//资讯显示		文字
	HA_COMPONENT_TYPE_MATCH,					//比对框显示    图像 包含图像数据
	HA_COMPONENT_TYPE_MATCH_FACE,			//比对框中人脸显示  文字 相对比对框位置
	HA_COMPONENT_TYPE_MATCH_ID,			//比对框中ID显示	文字
	HA_COMPONENT_TYPE_MATCH_NAME,			//比对框姓名显示	文字
	HA_COMPONENT_TYPE_MATCH_DATE			//比对框日期显示	文字
};


struct UIComponentParam
{
	int component_type;   //  enum ComponentType
	int x, y;  //坐标 左上为坐标原点 水平 x 垂直 y
	unsigned int font_size;
	unsigned int  font_color; //文字属性
	unsigned int data_size; // 图像长度
	char resv[32]; //保留
	char *data; //图像数据
};


/// 失败信息(160字节)
struct FailMessage {
  /*! 查询的记录总量 */
  int record_count;            

  /*! 当前收到的记录序号 */
  int record_no;

  /*! 记录序号。 */
  unsigned int sequence;

  /*! 保留。 */
  char resv[4];

	unsigned int tv_sec;
	unsigned int tv_usec;

  /*! 错误信息人员id。 */
  char person_id[68];

  /*! 错误信息人员姓名。 */
  char person_name[64];

  /*! 错误原因。 */
  int failed_reason;
};

/// 失败信息查询条件标记。
enum FailMessageQueryFlag
{
  /*! 通过记录数据库编号查询。 */
  FAIL_RECORD_QUERY_FLAG_SEQUENCE = 0x1,

  /*! 通过抓拍时间范围查询。 */
  FAIL_RECORD_QUERY_FLAG_TIME = 0x1 << 1,

  /*! 通过人员id查询。 */
  FAIL_RECORD_QUERY_FLAG_ID = 0x1 << 2,

  /*! 通过人员姓名查询。 */
  FAIL_RECORD_QUERY_FLAG_NAME = 0x1 << 3
};

/// 失败信息记录查询条件(256字节)
struct FailMessageCondition {
  // 条件组合标记
  unsigned short condition_flag;

  // 1模糊查询 0精准查询
  unsigned char query_mode;

  // 保留
  char resv;

  // 数据库纪录编号
  unsigned int sequence;

  // 错误信息时间区间起点
  unsigned int time_start;

  // 错误信息时间区间终点
  unsigned int time_end;

  // 比对上的人员ID
  char person_id[68];

  // 比对上的人员姓名
  char person_name[64];

  // 保留
  char resv1[108];

};






#endif /* CONFIG_GW_H_ */
