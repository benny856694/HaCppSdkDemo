#ifndef NETWORK_MSG_H
#define NETWORK_MSG_H

/* 每个数据包头部长度，包含4字节的T(封装消息ID，系统类型，版本号等) 和4字节的L(表示后面数据长度) */
#define TL_HEADER_SIZE 8

/* 协议主、次版本号 */
#define PROTOCOL_MAJOR  1
#define PROTOCOL_MINOR  10   //次版本号最大 15

/* SystemID的定义，各个系统在发送数据包时按文档将该字段封装在包头 */
#define SYS_TYPE_EP     1
#define SYS_TYPE_GW     2
#define SYS_TYPE_GKJ    3
#define SYS_TYPE_ILLEGALPARK    4
#define SYS_TYPE_MIDDLEWARE 5
#define SYS_TYPE_FACE_CAR_GW 6
#define SYS_TYPE_PARK        7
#define SYSTEM_TYPE_FACE     12

/* MessageID的定义 */
#define MESSAGE_ID_REBOOT            0      /* 重启机器 */
#define MESSAGE_ID_RESTART           1      /* 重启进程 */
#define MESSAGE_ID_HEART_BEAT        2      /* 心跳包 */
#define MESSAGE_ID_SYNCTIME          3      /* 时间同步请求 */
#define MESSAGE_ID_REPLY             4      /* 统一应答 */
#define MESSAGE_ID_CAR               5      /* 抓拍数据包 */
#define MESSAGE_ID_GET_FIRMWARE_VER     6       /*获取相机固件版本信息*/
#define MESSAGE_ID_VERIFY           7      /* 系统认证请求 */

#define MESSAGE_ID_SERIAL_READ      8       /* 透明串口 - 读 */
#define MESSAGE_ID_SERIAL232_READ      80      /* 透明串口 - 读 */

#define MESSAGE_ID_SERIAL_WRITE      9      /* 透明串口 - 写 */

#define MESSAGE_ID_REQ_SYS_TIME         11      /*获取系统时间*/
#define MESSAGE_ID_SET_SYS_TIME         12      /*设置系统时间*/

#define MESSAGE_ID_REQ_NTP_INFO          13     /*请求NTP信息*/
#define MESSAGE_ID_SET_NTP_INFO          14     /*设置NTP信息*/

#define MESSAGE_ID_REQ_NET_INFO          15     /*请求系统网络信息*/
#define MESSAGE_ID_SET_NET_INFO          16     /*设置系统网络信息*/
#define MESSAGE_ID_REQ_DIAGNOSE          17     /*系统诊断信息*/

#define MESSAGE_ID_QR_CODE               18    /*! 二维码信息 。 */

#define MESSAGE_ID_AUDIO_PLAY_INFO     19 /*! 音频播放内容信息 。 */

#define MESSAGE_ID_JSON_MSG          50     /* json 字段消息 */


#define MESSAGE_ID_SET_LCD_UI          60     /* 显示屏UI配置 */
#define MESSAGE_ID_LCD_CONTROL         61     /* 显示屏息屏控制 */

#define MESSAGE_ID_SEARCH_CAM          20     /* 搜索服务器相机 */
#define MESSAGE_ID_MAP_CAM             21     /* 服务器映射到相机 */

#define MESSAGE_ID_REQ_AUTH          101    /* 查询授权 */
#define MESSAGE_ID_STREAM_CTRL       102    /* 视频流控制      用于开关视频流*/
#define MESSAGE_ID_LIVE_IMAGE        103    /* 实时图像 */

#define MESSAGE_ID_FACE_RECT         104    /* 实时人脸轮廓区域 */
#define MESSAGE_ID_LIVE_IMAGE1       105    /* 第二路实时图像，用于双目相机*/
#define MESSAGE_ID_PLATE_IMAGE       106    /* 子码流 */

#define MESSAGE_ID_RADAR_STATE       107    /* 交通卡口: 雷达状态 */
#define MESSAGE_ID_COIL_STATE        108    /* 交通卡口: 线圈状态 */
#define MESSAGE_ID_DMODE_STATE       109    /* 交通卡口: 双模式状态 */

#define MESSAGE_ID_GPIO_SET     110         /* GPIO控制 */
#define MESSAGE_ID_GPIO_INPUT   112         /* GPIO输入信号*/


#define MESSAGE_ID_GW_TEST_AUDIO     111    /* 测试声音播放 */
#define MESSAGE_ID_GW_GET_AUDIOLIST  113    /* 获取可用音频列表 */


#define MESSAGE_ID_SET_AUDIO_PLAY    114    /*! 音频播放设置 */
#define MESSAGE_ID_GET_AUDIO_PLAY    115    /*! 获取音频播放设置 */

#define MESSAGE_ID_SET_ALARM        116     /* 设置ALARM开关 */

#define MESSAGE_ID_BACKUP_USER_DEFAULT     117  /*备份当前参数设置成用户默认参数*/
#define MESSAGE_ID_RESTORE_USER_DEFAULT    118  /*恢复用户默认参数*/

#define MESSAGE_ID_RESTORE_MANNUF_DEFAULT 119   /*恢复出厂设置*/

#define MESSAGE_ID_CUSTOMER_GET_SN 120          /*提供给客户用户的SN*/

#define MESSAGE_ID_QUERY_DISK           123  /* 查询硬盘信息 */
#define MESSAGE_ID_FORMAT_DISK         124  /* 格式化硬盘 */

#define MESSAGE_ID_PLAY_AUDIO 125    /* 播放音频*/

#define MESSAGE_ID_PLAY_TTSAUDIO_STREAM 126  /*  文字转语音播放。 */

#define MESSAGE_ID_FORMAT_EMMC          128    /*! 格式化EMMC空间 */

#define MESSAGE_ID_SIMPLE_CARINFO 126       /*精简版车辆数据包*/

#define MESSAGE_ID_GET_SIMPLE_WLIST 127     /*获取精简版本白名单*/
#define MESSAGE_ID_SET_SIMPLE_WLIST 128     /*设置精简版本白名单*/

#define MESSAGE_ID_GET_REGINFO 129          /*获取注册信息*/

#define MESSAGE_ID_PASSTHROUGH_WRITE	130  /*SDK 透明传输 写 */
#define MESSAGE_ID_PASSTHROUGH_READ  	131  /*SDK 透明传输 读*/
#define MESSAGE_ID_USERLOG_WRITE        132   /*用日志 写 */
#define MESSAGE_ID_USERLOG_READ         133  /*用户日志 读 */
#define MESSAGE_ID_QUERY_DB_RECORD 134      /*查询数据库记录，分布查询*/

#define MESSAGE_ID_CAR_PARK_VZ 135             /*兼容臻识linux SDK包*/

#define MESSAGE_ID_QUERY_DB_RECORD_BY_ID 136  /*根据主键id查询数据库记录*/

#define MESSAGE_ID_GET_NET_AUTH 143        /*请求用户的用户名密码*/
#define MESSAGE_ID_RESET_USER_INFO 144        /*修改用户的用户名密码*/

#define MESSAGE_ID_TEMPERATURE_CORRECT 150       /* 开始温度校准 */

#define MESSAGE_ID_REQ_CONFIG        201    /* 查询应用程序配置信息(配置文件) */
#define MESSAGE_ID_SET_CONFIG        202    /* 设置应用程序配置信息 */
#define MESSAGE_ID_RESET_CONFIG      203    /* 重置应用程序配置信息 */

#define MESSAGE_ID_REQ_CAM_PARAM     204    /* 查询相机参数 */
#define MESSAGE_ID_SET_CAM_PARAM     205    /* 设置相机参数 */
#define MESSAGE_ID_RESET_CAM_PARAM   206    /* 重置相机参数 */

#define MESSAGE_ID_REQ_TEMP_CONFIG   207    /* 查询临时缓存的配置(无配置文件) */
#define MESSAGE_ID_SET_TEMP_CONFIG   208    /* 设置临时缓存的配置 */
#define MESSAGE_ID_RESET_TEMP_CONFIG 209    /* 重置临时缓存的配置 */

#define MESSAGE_ID_GET_SCHEDULEMODE_CONFIG   211    /*  获取调度时间的配置 */
#define MESSAGE_ID_SET_SCHEDULEMODE_CONFIG   212    /* 设置调度时间的配置 */

#define MESSAGE_ID_GET_SCHEDFESTIVAL  213    /*  获取节假日配置 */
#define MESSAGE_ID_SET_SCHEDFESTIVAL  214    /* 设置节假日配置 */

#define MESSAGE_ID_SNAPSHOT          210    /*! 快照/截图。 */


#define MESSAGE_ID_BATCH_REG_FACE          230    /*! 批量注册测试 */

#define MESSAGE_ID_SOFT_TRIGG               211    /* 软触发 */
#define MESSAGE_ID_SEND_UP_OFFLINE_DATA     216 /*上传脱机收费数据*/
#define MESSAGE_ID_QUERY_FACE_RECORD        217     /* 查询历史数据 */
#define MESSAGE_ID_CAPACITY_HISTORY          218    /*! 抓拍记录容量。 */
#define MESSAGE_ID_DELETE_FACE_RECORD        219     /*删除所有的脱机收费数据*/

#define MESSAGE_ID_REQ_RECORD_SWIPE 220    /*! 浏览刷卡抓拍记录。 */

#define MESSAGE_ID_QUERY_FAIL_MESSAGE     221 /*! 浏览注册失败信息*/

#define MESSAGE_ID_LOG               300    /* 日志信息 */

#define MESSAGE_ID_DEBUG_IMAGE          301      //调试图像信息
#define MESSAGE_ID_FACE_DEL_PROGRESS    302      //删除进度
#define MESSAGE_ID_RE_REGISTER_PROGRESS 303      //重注册进度
#define MESSAGE_ID_DEBUG_INFRARED_IMAGE 304      //红外调试图像

#define  MESSAGE_ID_GET_IMAGE_FEATURE  310 // 获取图片特征值

#define MESSAGE_ID_UIfRONT				350      // UI文字
#define MESSAGE_ID_UIWIFI				351      // UIwifi
#define MESSAGE_ID_UIFACE				352      // UI抓拍
#define MESSAGE_ID_UIRECT				353      // UI人脸框
#define MESSAGE_ID_UIIMAGE				354      // UI图片
#define MESSAGE_ID_UIREFRESH		    360      // UI唤醒 
#define MESSAGE_ID_UIEVENT				361      // UI事件
#define MESSAGE_ID_PAUSEMATCH		    362      // 暂停比对
#define MESSAGE_ID_UI_PROCESS_START		363      // QT界面程序启动完成
#define MESSAGE_ID_UI_QTEVENT			364      // QT界面反馈事件

#define MESSAGE_ID_UI_JSON_TRANSFER		365      // UIjson交互事件

#define MESSAGE_ID_FACE_OUTPUT_ONOFF 399    /*! 私有外网穿透抓拍数据上传开关。 */
#define MESSAGE_ID_QUREY_ALL_ID      400    /*查询所以注册ID*/ 
#define MESSAGE_ID_QUREY_FACE        401    /* 查询人像比对数据*/
#define MESSAGE_ID_REG_FACE          402    /* 添加人像比对数据*/
#define MESSAGE_ID_MODIFY_FACE       403    /* 修改人像比对数据*/
#define MESSAGE_ID_DELETE_FACE       404    /* 删除人像比对数据*/

#define MESSAGE_ID_ALARM_RECORD      406    /* 开闸纪录*/
#define MESSAGE_ID_ALARM_REQUEST     407    /* 开闸请求*/
#define MESSAGE_ID_REQ_PLATFORM_ACCESS     408    /* 获取平台接入配置*/
#define MESSAGE_ID_SET_PLATFORM_ACCESS     409    /* 设置平台接入配置*/
#define MESSAGE_ID_QUREY_UPDATASERVER_PARAM     410    /* 查询远程升级服务器参数*/
#define MESSAGE_ID_SET__UPDATASERVER_PARAM     411    /* 设置远程升级服务器参数*/
#define MESSAGE_ID_PLATFORM_ACCESS_SYN     412    /* 平台接入同步*/
#define MESSAGE_ID_STORAGE_CAPACITY      413   /* 查询人脸库容量*/
#define MESSAGE_ID_SET_RELAYSERVER_PARAM     420  	/*! 设置转接服务器地址参数。 */

#define MESSAGE_ID_GET_HAEDWAREINFO          430   /*! 获取硬件信息 。 */
#define MESSAGE_ID_SET_HAEDWAREINFO          431    /*! 设置支持硬件信息 。 */

#define MESSAGE_ID_REEXTRACT				444      /*! 手动重注册 */


#define MESSAGE_ID_GET_IDCARDS		460   /*! 查询采集到的身份证信息 */
#define MESSAGE_ID_ADD_IDCARDS		461  /*! 添加采集到的身份证信息 */

#define MESSAGE_ID_REQ_SYS_STORAGE   500    /* 系统存储信息状况 */
#define MESSAGE_ID_SET_SYS_STORAGE   501    /* 修改系统存储信息 */

#define MESSAGE_ID_REQ_SYS_NETWORK   502    /* 系统网络相关信息 */
#define MESSAGE_ID_SET_SYS_NETWORK   503    /* 修改系统网络相关信息 */

#define MESSAGE_ID_REQ_TIME          504    /* 获取系统时间，设置时间以MESSAGE_ID_SYNCTIME */

#define MESSAGE_ID_CUSTOMER_READ_AUTHCODE 506   /*读取客户保存的验证码*/
#define MESSAGE_ID_CUSTOMER_WRITE_AUTHCODE 507  /*保存客户的验证码*/
#define MESSAGE_ID_GET_BINOCULARCAMERAA_AJUSTPARAM 508    /*获取双目摄像头校差*/
#define MESSAGE_ID_GET_BINOCULARCAMERAA_AJUSTREPLY 509 /* 获取双目摄像头相差消息*/
#define MESSAGE_ID_HASX_REQ_CAM_PARAM 500 
#define MESSAGE_ID_HASX_SET_CAM_PARAM 501
#define MESSAGE_ID_HASX_RESET_CAM_PARAM 502
#define MESSAGE_ID_HASX_REQ_CAM_PARAM_ONE 503
#define MESSAGE_ID_HASX_SET_CAM_PARAM_ONE 504
#define MESSAGE_ID_HASX_LIVE_IMAGE 505
#define MESSAGE_ID_CAPABILITIES_ACCREDIT 510  /* 系统功能授权 */
#define MESSAGE_ID_STATE_ACCREDIT 511  /* 系统功能授权 */
#define MESSAGE_ID_QUERY_NET4G_INFO      540   /*! 查询4G  状态信息 */
#define MESSAGE_ID_PING_CONDITION        541  /*! 测试网络地址是否连通 */
#define MESSAGE_ID_SEARCH_WIFI        561   /*! 搜索wifi */
#define MESSAGE_ID_CONNECT_WIFI        562  /*! 连接wifi */
#define MESSAGE_ID_WIFI_STATUS         563  /*! 查看wifi连接状态 */
#define MESSAGE_ID_SNAPSHOT_FACE          580    /*! 抓拍注册人脸。 */

#define MESSAGE_ID_CALL_SWITCH       600    /*! 通话开关 */
#define MESSAGE_ID_CALL_CAMERA_RECORD  601  /*! 录音数据 */
#define MESSAGE_ID_PLAY_AUDIO_STREAM 602    /* 播放音频流*/



#define MESSAGE_ID_REG_SIP_CALL		604     /*! sip拨号/挂断 */
#define MESSAGE_ID_REG_SIP_SERVER   605    /*! sip注册*/
#define MESSAGE_ID_SIP_CALL_EVENT   606   /*! sip通话事件 */
#define MESSAGE_ID_SIP_KEY_EVENT    607	  /*! sip按键事件 */
#define	MESSAGE_ID_UI_SIP_ANSWER	608      // sip被叫应答

#define MESSAGE_ID_AES_ADJUST		620 /*! 回音消除自动校正 */
#define MESSAGE_ID_AES_PROGRESS		621 /*! 回音消除自动校正进度  */


#define MESSAGE_ID_REQ_APP_PARAM    804     /*查询应用参数信息*/
#define MESSAGE_ID_SET_APP_PARAM    805     /*设置应用参数信息*/


#define MESSAGE_ID_LOAD_CONFIG_FILE  807    /*! 导出配置参数文件。 */

  
#define MESSAGE_ID_IMPORT_CONFIG_FILE 808  /*! 导入配置参数文件。 */

#define MESSAGE_ID_TEMPERATURE 809			/*! 测温参数设置和获取 */
#define MESSAGE_ID_MASK 810					/*! 口罩检测参数设置和获取 */

#define MESSAGE_ID_UPDATE            900    /* 升级 */


#define MESSAGE_ID_REQ_SYS_INFO      1000   /* 查询对端系统信息，常用于获取对端基本信息以初始化本端某些元素（如界面） */

#define MESSAGE_ID_MAX               1023   /*最大消息ID*/

/* 以下是统一应答码的定义 */
#define REPLYCODE_OK        (0)             /* 已成功处理消息 */
#define REPLYCODE_PROTOCOL_UNMATCH  (1)     /* 所接收消息与本地协议不匹配 */
#define REPLYCODE_MESSAGEID_ERROR   (2)     /* 无法识别的消息ID */
#define REPLYCODE_ERROR_VALUE       (3)     /* 消息内容中存在错误的值 */


#define DATA_TYPE_FACE_CAR_FACE 0
#define DATA_TYPE_FACE_CAR_CAR 1


typedef enum
{
    FORMAT_ID_JPEG = 1,
    FORMAT_ID_H264 = 2,
    FORMAT_ID_AVI  = 3, 
    FORMAT_ID_GRAY_8 = 4        /* 8bit灰度图 */
}FORMAT_ID;





#endif //


