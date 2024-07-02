#ifndef FACE_RECO_DEF_H
#define FACE_RECO_DEF_H

#include "config_gw.h"







/// 单天最大调度时段数。
#define MAX_SCHEDULE_PER_DAY 6

/// 调度最大分类数。分类自行定义，范围：1~5。
#define MAX_SCHEDULE_KIND 5

/// 单周天数。
#define ONE_WEEK_DAYS     7

/// 调度模式。
enum ScheduleMode {
	/*! 禁用。 */
	SCHEDULE_MODE_NONE = 0,

	/*! 按天调度。 周1-周7 都按照此设置运行  */
	SCHEDULE_MODE_DAILY = 1,   

	/*! 按周调度。 周1-周7分别设置*/
	SCHEDULE_MODE_WEEKLY = 2
};

/// 时间点。
struct MinuteSchedule {
	/*! 时。取值范围：0~24。 */
	unsigned char hour;

	/*! 分。取值范围：0~59。 */
	unsigned char minute;
};

/// 时间段。
struct HourSchedule {
	/*! 起始时间。闭区间（包含该值）。 */
	MinuteSchedule start;

	/*! 结束时间。开区间（不包含该值）。 */
	MinuteSchedule end;
};


/// 按天调度。
struct DailySchedule {
	unsigned int Sector; // 一天内时间总段数 最大支持6段   设置Schedule[0]--Schedule[1].......Schedule[Sector] 内为开闸时间
	HourSchedule SchTime[6];  // 调度时间 在此时间段为开闸时间
	char recv[16]; //保留 
};

/// 分类调度。
struct KindSchedule {
	enum ScheduleMode Mode; //调度模式 
	char ScheduleName[16];  //类别名称  自定义
	unsigned short ScheduleNameCode; //类别代码  取值 [1~100] 不能重复   
	/*调度模式为 SCHEDULE_MODE_DAILY 时 只读取Schedule[0] 配置  
	为 SCHEDULE_MODE_WEEKLY 时周日 到 周六 按Schedule[0]-Schedule[5] 配置 */
	DailySchedule Schedule[7];  //调度时间 
	char recv[32]; //保留 
};

#define MAXFESTIVALITEM 15

struct FestivalItem {
	/* 节假日描述 */
	char festival_desc[32];

	/* 节假日起始时间 单位 秒  从1970/1/1 8:0:0计数 */
	unsigned int term_start;

	/* 节假日截止时间 单位 秒 从1970/1/1 8:0:0计数 */
	unsigned int term_end;
	
	char res[32];
};

struct ScheduleFestival {
	unsigned int festival_num;  //节日调度总数 < MAXFESTIVALITEM
	FestivalItem festival_item[MAXFESTIVALITEM];
};




enum HatDetectResult
{
	/*! 未检测到安全帽 */
    NO_HAT = 0, 
    /*! 蓝色安全帽 */
    HAVE_BLUE_HAT,
    /*! 橙色安全帽 */
    HAVE_ORANGE_HAT,  
    /*! 红色安全帽 */
    HAVE_RED_HAT,
    /*! 白色安全帽 */
    HAVE_WHITE_HAT,
    /*! 黄色安全帽 */
    HAVE_YELLOW_HAT
};

// 人员比对成功类型

enum MatchType {
  /*! 未知 */
  MATCH_TYPE_NULL                  = 0x0,

  /*! 刷脸比对成功 */

  MATCH_TYPE_NORMAL                = 0x1,

  /*! 人证比对成功 */

  MATCH_TYPE_IDCARD_1TO1           = 0x1 << 1,

  /*! 刷身份证比对 */

  MATCH_TYPE_IDCARD                = 0x1 << 2,

  /*! 刷卡比对成功 */

  MATCH_TYPE_WGCARD                = 0x1 << 3,

  /*! 过人开闸 */

  MATCH_TYPE_ANY_FACE              = 0x1 << 4
};

/// 人员更新项。
enum ParsonDataFlags {
  /*! 未知。*/
  DATA_FLAG_NULL                = 0x0,

  /*! 更新姓名。 */
  DATA_FLAG_NAME                = 0x1,

  /*! 更新角色。 */
  DATA_FLAG_ROLE                = 0x1 << 1,

  /*! 更新韦根卡号。 */
  DATA_FLAG_WG                  = 0x1 << 2,

  /*! 更新有效截止时间。 */
  DATA_FLAG_EFFET               = 0x1 << 3,

  /*! 更新有效起始时间。 */
  DATA_FLAG_EFFECTSTART         = 0x1 << 4,

  /*! 更新调度模式。 */
  DATA_FLAG_SCHEDULE            = 0x1 << 5,

  /*! 更新用户自定义字段。 */
  DATA_FLAG_USERPARAM           = 0x1 << 6,

  /*! 更新归一化图片。 */
  DATA_FLAG_NORM_IMAGE          = 0x1 << 7,

  /*! 更新缩略图像。 */
  DATA_FLAG_REG_IMAGES          = 0x1 << 8,
  
};

/// SIP通话事件
enum SIPEventCall {
	 /*! 通话结束。 */
	SIP_EVENT_CALL_CLOSED	= 0,  

	 /*! 主叫开始。 */
	SIP_EVENT_CALL_RING		= 1, 

	 /*! 主叫振铃。 */
	SIP_EVENT_CALL_RINGING	= 2,  

	 /*! 主叫被拒绝。 */
	SIP_EVENT_CALL_REJECT	= 3, 

	 /*! 主叫接通。 */
	SIP_EVENT_CALL_ANSWERD	= 4, 

	 /*! 被叫。 */
	SIP_EVENT_CALL_INVITE	= 5,   

	 /*! 被叫接通。 */
	SIP_EVENT_CALL_INVITE_ANSWERD = 6     
};


struct FaceRecoInfo
{
    unsigned int sequence;  //抓拍序号，从1开始，每产生一组抓拍数据增加1。
    char camId[32];         //相机编号
    char posId[32];         //点位编号
    char posName[96];       //点位名称
    
    unsigned int tvSec;     //抓拍时间秒数，从1970年01月01日00时00分00秒至抓拍时间经过的秒数。
    unsigned int tvUsec;    //抓拍时间微秒数，tvSec的尾数
    
    short isRealtimeData;   //实时抓拍标志，0：非实时抓拍数据。非0：实时抓拍数据。
        
    short matched;          //比对结果，0：未比对。-1：比对失败。大于0的取值：比对成功时的确信度分数（100分制）。
    char matchPersonId[20]; //人员ID
    char matchPersonName[16];//人员姓名
    int matchRole;          //人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员
    
    int existImg;           //全景图，是否包含全景图像。0：不包含全景图像。非0：包含全景图像。
    char imgFormat[4];      //全景图像格式
    int imgLen;             //全景图像大小
    unsigned short faceXInImg;//人脸位于全景图像的X坐标。
    unsigned short faceYInImg;//人脸位于全景图像的y坐标
    unsigned short faceWInImg;//人脸位于全景图像宽度
    unsigned short faceHInImg;//人脸位于全景图像高度
    
    int existFaceImg;       //人脸图，特写图像标志，是否包含特写图像。0：不包含特写图像。非0：包含特写图像。
    char faceImgFormat[4];  //人脸图像封装格式。
    int faceImgLen;         //特写图像大小
    unsigned short faceXInFaceImg;//人脸位于特写图像的X坐标。
    unsigned short faceYInFaceImg;//人脸位于特写图像的y坐标。
    unsigned short faceWInFaceImg;//人脸位于特写图像的宽度
    unsigned short faceHInFaceImg;//人脸位于特写图像的高度
    
    int existVideo;         //是否包含视频。0：不包含视频。非0：包含视频。
    unsigned int videoStartSec;//视频起始时间（秒）
    unsigned int videoStartUsec;//videoStartSec尾数，微妙
    unsigned int videoEndSec;   //视频结束时间（秒）
    unsigned int videoEndUsec;  //videoEndSec尾数，微妙
    char videoFormat[4];        //视频封装格式。
    int videoLen;               //视频大小
    
    unsigned char sex;          //性别 0: 无此信息 1：男 2：女
    unsigned char age;          //年龄 0: 无此信息 其它值：年龄
    unsigned char expression;   //表情 0: 无此信息 其它值：暂未定义
    unsigned char skinColour;   //肤色 0: 无此信息 其它值：暂未定义
    unsigned char qValue;       //注册标准分数，分数越高越适合用来注册
    unsigned char sourceOfReg;   //注册来源 0：无此信息 1：注册软件注册  2：无感录入 3：云同步注册
	char attributeOfReg;  //注册人员属性 0:无此信息 1：永久有效名单 2：临时有效名单 3：永久无效名单
	unsigned char living;    //是否活体 0：无此信息 1：活体 2：非活体
	char hatColour; //安全帽颜色  enum HatDetectResult
	char FaceAngle; //人脸扭转角度 (与平面夹角)  -90~90;
	char FaceAngleFlat; // 人脸旋转角度 (在平面上的旋转角度） -90~90;
	char is_encry;  // 姓名ID 是否加密 0:未加密 1:已加密
	unsigned int math_type;		//比对类型  参见 MatchType
	unsigned int wgCardNO;		//  32位韦根卡号 
	unsigned long long  wgCardNOLong; //  46位韦根卡号 
    char GPSN[16]; //gps经度
    char GPSE[16]; //gps纬度
    unsigned int GPSNum; //gps卫星数量
	int match_failed_reson; //比对失败原因 参见 enum MatchFailedReasons
	char resv[55];				//保留
	char hasMask;			//是否佩戴口罩 0:无此信息 1:已佩戴口罩 2:未佩戴口罩
	float temperature;     // 人体温度
    unsigned char* img;         //全景图像数据
    unsigned char* faceImg;     //特写图像数据
    unsigned char* video;       //视频数据
    int feature_size;           //当前抓拍人脸的特征数据大小
    float *feature;             //当前抓拍人脸的特征数据
    int modelFaceImgLen;        //模板人脸图像长度
    char modelFaceImgFmt[4];       //模板人脸图像类型
    unsigned char *modelFaceImg;    //模板人脸图像数据
	HA_Point PointInImg[5];  //全景图人脸特征点 需打开全景图
	HA_Point PointInFaceImg[5];  //特写图人脸特征点 需打开特写图
	char dev_id[32];  //设备序列号 
	int existIDCard;  //是否存在身份证信息 

	char IDCardnumber[36];   // 身份证号码。 
	char IDCardname[43];        // 姓名。 
	unsigned char IDCardsex;  // 性别。@ref Sex 。 
	char IDCardnational[19];   // 民族。 
	char IDCardbirth[17];    // 出生日期。 
	char IDCardresidence_address[103];   // 住址。 
	char IDCardorgan_issue[43];   // 签发机关。 
	char IDCardvalid_date_start[17];   // 有效期起始日期。 
	char IDCardvalid_date_end[17];   // 有效期截止日期。 
	char userParam[68]; //用户自定义信息
	char matchPersonNameEx[64]; //用户名拓展 用户名长于15字节使用此字段 或者加密后密文
	char matchPersonIDEx[64]; //id 加密后密文
	unsigned char person_name_aes_len;  // 加密后姓名密文长度
	unsigned char person_id_aes_len;  // 加密后id密文长度
	char trip_info[512]; 
};

/*

//相机系统时间信息
struct SystemTimeEx
{
	char date[24];          //日期 2017/12/6（2017年12月6日）
	char time[24];           //时间 17:37:05
	char time_zone[24];         //时区
	char isTwelveHour;         //12小时制 0:关 1：开
	char DST;   // 夏令时
	char resc[62];
};

*/



//相机系统时间信息
struct SystemTime
{
    char time_zone;         //时区
    char date[11];          //日期 2017/12/06（2017年12月6日）
    char time[9];           //时间 17:37:05
    char resv[11];          //保留
};

struct ha_rect{
  short x;
  short y;
  short width;
  short height;
};


struct TimeZone{
	float timeZone; //  时区 -11.0~+11.0 
	char timeZoneSes[128]; // 时区描述
	char resv[64];
};


struct FaceFlags
{
    char faceID[20];    //人员ID
    char faceName[16];  //人员姓名
    int role;           //人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
    unsigned int wgCardNO;//韦根协议门禁卡号
    unsigned int effectTime;   //有效期截止时间，该人员信息在该时间内有效,从1970年1月1日0时0分0秒到截止时间的秒数（0xFFFFFFFF表示永久有效，0表示永久失效） 最大2038 年
    unsigned int effectStartTime;//有效期起始时间，该人员信息在该时间之后有效,从1970年1月1日0时0分0秒到起始时间的秒数（0表示未初始化） 最大2038 年
	short version;           //特征数据版本 用于同步注册特征数据时相机校验 未使用特征数据注册填0;
	unsigned long long  wgCardNOLong;   // 韦根门禁卡号加长 在wgCardNO长度不满足时可将wgCardNO置0使用此成员
	unsigned char ScheduleMode; ////调度模式 0:不使用调度模式  1~5 对应 Struct KindSchedule->ScheduleNameCode模式
	char resv2;
	char userParam[68];  //用户自定义文本内容，可用于相机TTS播放、LCD显示，也可作为用户平台自定义属性使用
	char faceNameEx[64];  //用户名拓展，人员姓名长于15字节时使用此字段
	char worksiteID[16]; //注册往哪个平台
	char resv[8024]; 
};

struct FaceFeature 
{
	float *feature; //特征数据
	short featureseize; //单个特征长度
	short featureNum; //特征数量
	short version; // 特征版本
	char resv[64]; // 保留
};

struct FaceImage
{
    int img_seq;    //图片编号 0
    int img_fmt;    //图片格式 0：jpg 1：bgr 
    unsigned char *img; //要注册的人脸图片数据，支持主流图像格式
    int img_len;    //img的长度
    int width;      //图像宽度，jpg图像不填此项
    int height;     //图像高度，jpg图像不填此项
};

struct ErrorFaceImage
{
    int img_seq;    //注册失败的图像编号
    int err_code;   //失败的错误码
};

//人脸查询返回
struct QueryFaceFlags 
{
    char personID[20];           //人员ID
    char personName[16];         //姓名 
	short feature_count;         //当前id的特征数总量
    int featureSize;             //人脸特征数据大小
    float feature[2048]; //人脸特征数据
    int imgNum;                  //图像数目
    int imgSize;                 //图像大小
	unsigned char img[10240];    //图像数据
    int role;           //人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
    unsigned int wgCardNO;//韦根协议门禁卡号
    unsigned int effectTime;   //有效期截止时间，该人员信息在该时间内有效,从1970年1月1日0时0分0秒到截止时间的秒数（0xFFFFFFFF表示永久有效，0表示永久失效）
    unsigned int effectStartTime;//有效期起始时间，该人员信息在该时间之后有效,从1970年1月1日0时0分0秒到起始时间的秒数（0表示未初始化）	
};

//人脸查询回调返回
struct QueryFaceInfo
{
    int record_count;            //查询的角色记录总量
    int record_no;               //当前收到的记录序号
    char personID[20];           //人员ID
    char personName[16];         //姓名   
    int role;                    //人员角色 0：普通人员。 1：白名单人员。 2：黑名单人员。 -1：所有人员。
    short feature_count;         //当前id的特征数总量
    short feature_size;           //人脸特征数据长度
    float *feature;              //人脸特征数据，按顺序排列所有特征数据 featureSize*feature_count
    int imgNum;                     //模板图像数量
    int imgSize[5];                 //图像大小，imgSize[i]为第i张图片的大小
    char imgFmt[5][4];              //图像格式,imgFmt[i]为第i张图片的格式
    unsigned char *imgBuff[5];          //imgBuff[i]位第i张图片给数据首地址
    unsigned int wgCardNO;                       //韦根门禁卡号
    unsigned int  effectTime;   //有效期截止时间，该人员信息在该时间内有效,从1970年1月1日0时0分0秒到截止时间的秒数（0xFFFFFFFF表示永久有效，0表示永久失效）  
    unsigned int  effectStartTime;   //有效期起始时间，该人员信息在该时间之后有效,从1970年1月1日0时0分0秒到起始时间的秒数（0表示未初始化）
	short version;                 //非0:当前特征数据版本 0:不支持版本查询
	unsigned char ScheduleMode;  //调度模式 0:不使用调度模式  1~5 对应 Struct KindSchedule->ScheduleNameCode模式
 	char resv;
	int twistImgNum;//归一化图像数量
	short twistwidth[5];					//归一化图像宽度
    short twistheight[5];					//归一化图像高度
	int twischannel[5];                   //归一化图像通道
	char *twistimgBuff[5];          //归一化图像第i张图片给数据首地址
	unsigned long long wgCardNOLong;   // 韦根门禁卡号加长 在wgCardNO长度不满足时使用此成员
	char userParam[68];  //用户自定义文本内容，可用于相机TTS播放、LCD显示，也可作为用户平台自定义属性使用
	char faceNameEx [64]; //用户名拓展 当用户名不字段长于15字节使用此字段
	char resv1[372];
};

/// 抓拍比对纪录。
struct RecordData {
  /*! 查询的角色记录总量 */
  int record_count;            

  /*! 当前收到的记录序号 */
  int record_no;

  /*! 抓拍纪录序列号 */
  unsigned int sequence;

  /*! 抓拍时间秒数，从1970年01月01日00时00分00秒至抓拍时间经过的秒数。 */
  unsigned int tvSec;

  /*! 抓拍时间微秒数，tvSec的尾数 */
  unsigned int tvUsec;

  /*! 比对状态(分数) */
  short matched;

  /*! 性别 */
  unsigned char sex;
  
  /*! 年龄*/
  unsigned char age;

  /*! 比对上的人员id */
  char person_id[20];

  /*! 比对上的人员姓名 */
  char person_name[16];

  /*！实时人脸图像长度 */
  int face_image_len;

  /*！实时人脸图像（jpg格式） */
  unsigned char* face_image;

  /*! 人脸位于特写图像的X坐标。 */
  unsigned short faceXInFaceImg;

  /*! 人脸位于特写图像的y坐标。 */
  unsigned short faceYInFaceImg;

  /*! 人脸位于特写图像的宽度 */
  unsigned short faceWInFaceImg;

  /*! 人脸位于特写图像的高度 */
  unsigned short faceHInFaceImg;

  /*！比对上的注册人脸图像长度，未比对上时为0*/
  int reg_image_len;

  /*！比对上的注册人脸图像（jpg格式），未比对上时为NULL */
  unsigned char* reg_image;

  /*! 人像质量。 */
  unsigned char qvalue;

  /*! 纪录是否已上传 1:表示已经上传 0：表示未上传*/
  char is_upload;
  /* ! 人员角色 仅当matched>0有效  人员角色，0：普通人员。 1：白名单人员。 2：黑名单人员 -2：无此信息 */
  char role;

  /*! 是否加密 */
  unsigned char aes_enable;

  unsigned int match_type; // 比对类型 参见MatchType

  /* 用户自定义字段 */
  char customer_txt[64];

  /* 用户姓名扩展字段 */
  char person_name_ext[64];

  /* 体温*/
  float temperature;
  
  /* 比对失败原因  参见 enum MatchFailedReasons */
  int match_failed_reson;

    /*! id 加密密文 */
  char person_id_aes[64];

  /*! id 加密密文 长度 */
  unsigned char person_id_aes_len;

    /*! 姓名 加密字段长度 */
  unsigned char person_name_aes_len;

  /*! 姓名 上传状态 */
  char upload_message[128];
};

//NTP校时信息
struct NtpInfo
{
    short enable_state;         //Ntp开关状态，0是关 非0是开
    short update_cycle;         //更新周期，60~600s
    char ntp_server[16];        //NTP服务器ip地址
	char resv[12];              //保留
};

//NTP校时信息
struct NtpInfoEx
{
    short enable_state;         //Ntp开关状态，0是关 非0是开
    short update_cycle;         //更新周期，60~600s
    char ntp_server[16];        //NTP服务器ip地址
    char domain[64];            //NTP服务器域名  IP为空时使用   
	char resv[128];              //保留
};


enum UIID {
	UI_ID_TEXT_CUSTOMER			= 0,	// 用户显示文字
	UI_ID_TEXT_NUM_PERSON,				// 注册人员数量
	UI_ID_TEXT_TITLE,					// 标题
	UI_ID_TEXT_IDCARD,					// ID卡号码
	UI_ID_TEXT_DEBUG,					// 调试信息
	UI_ID_TEXT_TEMPERATURE,				// 体温
	UI_ID_TEXT_UNAUTH,                  // 未授权提示
	UI_ID_IMAGE_CUSTOMER		= 50,	// 用户显示图片
	UI_ID_IMAGE_INFRA_RED,				// 红外调试图像
	UI_ID_IMAGE_USB_QRCODE,         // usb二维码图像
	UI_ID_EVENT_PARAM			= 100,	// 相机参数被更新
	UI_ID_EVENT_CLOCK_CONFIRM,			// 打卡确认
	UI_ID_EVENT_SHOWWORKWXBIND,     // 显示企业微信绑定二维码
	UI_ID_EVENT_HIDEWORKWXBIND,      // 隐藏企业微信绑定二维码
	UI_ID_EVENT_SYSTEM_INIT_COMPLETE, // 系统启动完成
	UI_ID_EVENT_LCD_WAKE,            // 屏幕唤醒
	UI_ID_EVENT_LCD_HIDE,            // 屏幕息屏

	UI_ID_EVENT_QRCODE_SUCCESS = 120,             // 二维码对比成功
	UI_ID_EVENT_QRCODE_EXPIRED = 121,             // 二维码过期
	UI_ID_EVENT_QRCODE_EFFECT = 122,             // 二维码未生效
	UI_ID_EVENT_QRCODE_MAXTINES = 123,             // 二维码扫描次数达最大值
	UI_ID_EVENT_QRCODE_NOTEXIST = 124,             // 二维码不存在

	UI_ID_EVENT_HEALTH_CODE = 125,              // 健康码
	UI_ID_EVENT_QRCODE_READ = 126,              // 扫码成功

	UI_ID_EVENT_CARD_SUCCESS = 130,             // 卡号对比成功
	UI_ID_EVENT_CARD_EXPIRED = 131,             // 卡号已过期
	UI_ID_EVENT_CARD_EFFECT = 132,             // 卡号未生效
	UI_ID_EVENT_CARD_NOTEXIST = 133,             // 卡号不存在

	UI_ID_EVENT_IDCARD_READ_SUCCESS = 134,             // 读取到身份证
	UI_ID_EVENT_IDCARD_MISMATCH = 135,             // 人证比对失败
	UI_ID_EVENT_UN_AUTH_PERSION = 136,             // 访客未注册
	UI_ID_EVENT_TEMPERATURE_ABNORMAL = 137,        // 体温异常

	UI_ID_EVENT_REMOTEOPENDOOR = 140,             // 远程开门，门已开
	UI_ID_EVENT_TEMPERATURE = 150,                // 体温
	UI_ID_EVENT_TEMPERATURE_TIME_OUT = 151,//测温超时
	UI_ID_EVENT_NO_MASK              =152,       // 未佩戴口罩

	UI_ID_EVENT_SIP_RINGING = 200,  // sip主叫振铃
	UI_ID_EVENT_SIP_ANSWERD,         // sip主叫接通
	UI_ID_EVENT_SIP_REJECT,          // sip主叫被拒绝
	UI_ID_EVENT_SIP_INVITE,          // sip被叫
	UI_ID_EVENT_SIP_INVITE_ANSWERD,  // sip被叫接通
	UI_ID_EVENT_SIP_INVITE_CLOSED,    // sip通话结束 
	UI_ID_EVENT_SIP_INVITE_NONE,    // sip注册未注册
	UI_ID_EVENT_SIP_INVITE_ING,    // sip注册中
	UI_ID_EVENT_SIP_INVITE_DONE,    // sip注册成功
	UI_ID_EVENT_SET_ROOMID_SPLICE,    // 房号拼接方式修改
	UI_ID_EVENT_SIP_INVITE_CLOSED_UNRING,    // sip 呼叫失败
	UI_ID_EVENT_SIP_INVITE_CLOSED_UNANSWER,    // sip 无人接听
	/***********************2000以上为界面反馈消息********************************/
	UI_ID_QT_EVENT_TEMP_ENABLE_CONFIRM = 2100 // 是否打开测温询问  

};


struct UIText
{
	char str[128]; // 文字内容
	unsigned short x;// 文字位置 x 
	unsigned short y;// 文字位置 y
	unsigned int fontSize; // 文字字体大小 
	unsigned int fontColor; // 文字颜色 0XFF00FFFF
	unsigned int BGColor; // 背景颜色  0:无背景颜色
	unsigned int aliveTime; // 显示时间ms 0:永久
	unsigned char bold; //加粗
	unsigned char uiId; // 文字来源 enum UIID
	char recv[30];
};

struct UIImage 
{
	unsigned char* image; // 图片数据
	unsigned int imageSize; // 图片数据大小
	unsigned short x; // 图片位置 x :0XFFFF 不指定
	unsigned short y; // 图片位置 y :0XFFFF 不指定
	unsigned short w; // 图片大小 w :0XFFFF 不缩放
	unsigned short h; // 图片大小 h :0XFFFF 不缩放
	unsigned int aliveTime; // 图片存在时间  单位 ms  0X0 永久显示
	unsigned char format; // 图片格式 0:jpg 1:png 2:RGB数据 3：ARGB数据
	unsigned char uiId; // 图片来源 enum UIID
	char recv[126]; // 图片额外数据
};


struct UIWifi
{
	char ssid[36];            // WIFI名称
	unsigned int frequency;   // WIFI频率
	int signal;               // 信号强度, 与rssi一致
	char bssid[20];           // 路由器MAC地址
	char flags[256];          // wifi加密方式
	int linkspeed;            // 连接速度
	char wifiMod;             // wifi模式  0:HA_WIFI_MODE_NONE 1: HA_WIFI_MODE_AP 2:HA_WIFI_MODE_STA
	char recv[127];
};

enum HEALTHWORKSITE{
	UNKNOWN_WORKSIT,
	HEALTH_WORKSITE_TIANFUTONG,
	HEALTH_WORKSITE_YUKANGMA,
	HEALTH_WORKSITE_GUOKANGDEYANG,
	HEALTH_WORKSITE_DEYANG,
	HEALTH_WORKSITE_BEIJING,
	HEALTH_WORKSITE_SUISHEN,
	HEALTH_WORKSITE_GUOKANGDEYANG2,
	HEALTH_WORKSITE_JIXIANGYUN,
	HEALTH_WORKSITE_TIANFUTONG2,
	HEALTH_WORKSITE_GUIZHOU,
	HEALTH_WORKSITE_TIANFUTONG3,
	HEALTH_WORKSITE_TIANFUTONG4,
	HEALTH_WORKSITE_SUKANGCODE,
	HEALTH_WORKSITE_GUOKANGDEYANG3,
};

struct UIFace
{
	char matchPersonId[64]; // 人员ID
	char matchPersonName[64];// 人员姓名
	char consumerText[64]; //用户自定义字段
	unsigned int tvSec;     // 抓拍时间秒数，从1970年01月01日00时00分00秒至抓拍时间经过的秒数。
	unsigned int tvUsec;    // 抓拍时间微秒数，tvSec的尾数
	unsigned int imageSize; // 注册图像数据大小 0:无注册图像
	float temperature; // 体温
	signed char matchRole; // 人员角色， -1:陌生人 0：普通人员。 1：白名单人员。 2：黑名单人员
	unsigned char living;    // 是否活体 0：无此信息 1：活体 2：非活体
	unsigned char hatColour; // 安全帽颜色  enum HatDetectResult
	unsigned char health_code;  // 0:无此信息 1:绿码 2:黄码 3:红码 4:未查询到健康码
	unsigned char* image;  // 注册图像数据
	char worksite_msg[64];//平台附带消息
	char healthcode_worksite;
	char resv[575];
};

struct SipRoomIdGroup {
	char roomId[64]; // 房号
	unsigned int sipNumCount; // sip账号组个数 最大支持3组
	char sipNum[3][128]; // sip账号组 注:拨号时将按照 sipNum[0]~sipNum[2] 优先级拨号 拨通其中一个或者全部都无法拨通则停止拨号
	char recv[64];
};

struct SipRegisterInfo {
	char sipNum[128]; //sip账号 -- 2 设备名称 
	char domain[128]; // 服务器域名 -- 2设备秘钥  --3 设备地址
	char password[128]; // 密码 -- 2 设备ID  --3 设备ID
	unsigned int port; //服务器端口
	char call_type; // 1:sip 2:webrct 3:金地
	char recv[127]; 
};


struct VORect {
	int x, y;
	int width, height;
};

struct VOAttr {
	VORect rect;
	char recv[112];
};


struct SIPCallerInfo {
	char host[64];
	char user_name[64];
};

struct RoomIdSplice {
	/*! 房号拼接符 */
	char roomid_splice_symbol[5];

	/*! 楼栋位号 + 单元号位数 + 房间号位数  sip_splice[0]~sip_splice[2]                 */
	char sip_splice[3];
};

struct BodyTemperature {
	float tempeture; // 体温
	unsigned int state; // 状态 0:超过测量范围无体温信息 1:体温正常 2:体温过高
};


struct HealthQRcode {
	char person_id[32];
	char person_name[32];

	char message[60]; // 异常 message
	unsigned char health_code;  // 0:异常 1:绿码 2:黄码 3:红码 4:未查询的健康码
	unsigned char tempeture_match; // 是否测温 0:不测温 1:测温 (仅绿码生效)
	char trip_info[512]; /*! 行程和疫苗*/
	char worksite_message[256]; /*! 核酸 */
};

struct MassageParam {
	unsigned short pos_x;
	unsigned short pos_y;
	int color;
	int font_size;
};

struct HealthCodeMassage {
	char massge[60];
	MassageParam massage_param[5];
	int massage_line_num;
};


struct UIEvent
{
	unsigned int uiId; // 事件id
	union {
		VOAttr vo_attr; // UI_ID_EVENT_LCD_WAKE
		SIPCallerInfo caller_info; // UI_ID_EVENT_SIP_INVITE
		RoomIdSplice roomid_splice; // UI_ID_EVENT_SET_ROOMID_SPLICE
		BodyTemperature temper; // UI_ID_EVENT_TEMPERATURE
		struct HealthQRcode healthCode;
		HealthCodeMassage massage;
		char recv[2048];
	};
};



struct UIFaceRect
{

	unsigned short x;
	unsigned short y;
	unsigned short w;
	unsigned short h;

	unsigned short alive;  // 0为活体，1为非活体
	unsigned short id; // 人脸框ID

	char recv[64];
};





//系统网络信息
struct SystemNetInfo
{
    char mac_addr[18];      //网卡物理地址
    char ip_addr[16];       //相机ip地址
    char netmask[16];       //子网掩码
    char gateway[16];       //默认网关
    char resv[14];          //保留
};

struct SystemNetInfoEx
{
	char mac[20];          // 网卡MAC地址
	char ip[20];           // 网卡IP地址
	char netmask[20];      // 网上子网掩码
	char gateway[20];      // 网关

	char manufacturer[16]; // 制造商名称
	char platform[32];     // 平台名称
	char system[32];       // 系统名称
	char version[64];      // 版本
	char ip_2[16];         // 网卡2IP地址
    char netmask_2[16];    // 网卡2子网掩码
    char dns[16];		       // 域名服务器地址
    char dhcp_enable;	     // DHCP开关
    char resv[64];		     // 保留
};

//系统版本信息
struct SystemVersionInfo
{
    char dev_id[32];        //设备序列号
    char protocol_ver[8];   //协议版本
    char firmware_ver[16];  //固件版本
    char code_ver[8];       //应用程序版本
    char build_time[20];    //应用编译时间
    char resv[16];          //保留
    char systemp_type[16];  //系统类型   
    char plateform[16];     //硬件平台
    char sensor_type[16];   //传感器型号
    char algorithm_ver[16]; //算法版本
    char min_sdk_ver[16];   //最低sdk版本
    unsigned int min_client_ver;//最低客户端版本
	char kernel_version[128];  //内核版本
	char lcd_type[32]; //LCD屏型号
	char algorithm_verEx[128]; //算法版本扩展
	char recv[384]; //保留
};



struct ScreenSaver
{
	unsigned char enable; //屏幕保护开关 0:关 1:息屏 2:屏保图片
	char resv[127]; 
};

struct LCDPictureList
{
	unsigned int sequence; //图片序列号
	char picture_name[64]; //图片名称
	char picture_patch[124]; //图片路径  注：由相机给出
	char resv[124];
};

struct FilePack
{
	unsigned int totalSize; //文件 总长度
	unsigned int offset; //当前文件偏移位置
	unsigned int size; // 当前数据包 data 内存大小 
	unsigned int used; //使用长度 
	char* data;  //文件数据
	char md5[35]; // 文件 md5值 最后一个包中附带此字段
	char resv[32];
};



struct FaceRect
{
    unsigned int faceId;        //人脸轮廓id
    struct ha_rect faceRect;//人脸轮廓坐标
    char resv[4];
};

struct FaceRectInfo
{
    char idShowFlag; //显示轮廓开关
    char resv[3];
    int rectNum;       //轮廓数量
    struct FaceRect faceRects[32];
};

struct FaceDelProgressInfo
{
    int delCount;   //删除的纪录总数
    int curDelNo;   //当前删除第几条纪录
    char faceId[20];//当前删除的人员ID
};

struct FaceReRegistProgressInfo
{
    int regist_count;     //重注册的人员总数
    int cur_regist_no;    //当前重注册第几条纪录
    char faceId[20];      //当前重注册的人员id
};


struct DebugImage
{
    int format;     //调试图像格式,0 rgb 1:jpg
    short width;        //调试图像宽度
    short height;       //调试图像高度
    int imageLen;       //图像数据长度
    unsigned char *imgData;//图像数据
};

struct BebugInfraredImage
{
	int lived;          // 0非活体 1 活体
	unsigned int timeStamp_s;     //时间戳 秒
    unsigned int timeStamp_u;     //时间戳 微妙
	short x_deviations;  //图像x坐标相差值
	short y_deviations;	//图像y坐标相差值
	ha_rect normalImgeRect;  //可见光图像人脸矩形
	ha_rect infraredImgeRect;	//红外光图像人脸矩形
	unsigned int viewImgeNum; //全景图数量
	DebugImage viewImge[8];  //全景图数据
	unsigned int closeupImgeNum;  //特写图数量
	DebugImage  closeupImge[8]; //特写图数据
	
};


struct BinocularAjustParam{
	unsigned int coordinatesNum; //x,y相差坐标数量 1,2字段循环
	short* x_deviations;  //图像x坐标相差值
	short* y_deviations;	//图像y坐标相差值
	unsigned int imgeNum; //用于校正的图像数量
	unsigned int* imgeFormat; //图像格式
	unsigned short* imgeWidth;  //图像宽度
	unsigned short* imgeHeight;  //图像高度
	unsigned int * imgeLen;   //图像长度
	char** imge;   //图像数据
};





struct BinocularAjustReply{
	short status;  //校准状态 是否已经计算双目像差 0：未计算 ！0已计算
	short coordinatesNum; //相差个数  3,4字段循环；
	short x_deviations[16];   //x坐标相差值 最多16个
	short y_deviations[16];  //y坐标相差值	最多16个
};
struct AllPersonID{
	int count; //注册人员数
	char** Id;  //Id[num]为一个成员id字符串的首地址
};
struct DebugImageInfo
{
    unsigned int timeStamp_s;     //时间戳 秒
    unsigned int timeStamp_u;     //时间戳 微妙
    int matched;                //比对结果，0：未比对。-1：比对失败。1：比对成功
    int matchScore;            //比对分数
    char faceId[20];            //比对上的人员id，matched等于1时有效
    int imageNum;               //调试图像数量，最大支持6张图像
    struct DebugImage debugImage[6];       //调试图像信息
};

#endif

