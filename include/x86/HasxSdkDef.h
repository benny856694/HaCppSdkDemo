//#pragma once
#ifndef HASX_SDK_DEF_H
#define HASX_SDK_DEF_H

// 配置项

struct CamCtrlLED
{
    int seq;
    int lightType;
    int hz;
    int trigType;
    int phase;
    int pulseWidth;

    int rev[32];
};


struct CamCtrlAutoCtrl
{
    int standard;
    int maxShut;
    int minShut;
    int maxGain;
    int gainLevel[4];

    int agcSelect[6]; //16*12 第一比特对应一个区域，31-0顺序排列

    int rev[32];
};

struct CamCtrlMannualCtrl
{
	int manualShut;
	int mannuGainLevel;
	int mannualGainValue;
	int mannualR;
	int mannualGr;
	int mannualGb;
	int mannualB;
	int mannualRoft;
	int mannualGroft;
	int mannualGboft;
	int mannualBoft;
	int rev[32];
};

struct CamCtrlImageEnhance
{
    int imgSaturability; //饱和度
    int imgContrast; //对比度
    int imgSharpen; //锐化
    int imgNoise; //降噪
    int imgGamma;
    int imgGammaEnable;
    int rev[31];
};
struct CamCtrlTrigIO
{
    int trigType; //0-不触发， 1-上升沿触发， 2-下降沿触发， 3-上升，下降都触发
    int trigNum;  //最大为3
    int trigInter[2]; //ms
    int flashEable;  //是否闪光
    int flashIndex;  //闪哪个灯

    int rev[8];
};


struct CamCtrlExtSync
{
    int enable;
    int phase;
    int filter;
};

struct CamCtrl
{
    int enableAutoExp;
    int enableAutoAwb;
    struct CamCtrlAutoCtrl autoCtrl;
    struct CamCtrlMannualCtrl manualCtrl;
    struct CamCtrlImageEnhance imgEnhance;
    struct CamCtrlLED led[5];
    struct CamCtrlTrigIO trigIO[8];
    struct CamCtrlExtSync extSync;

    int jpegQ;
    int h264W;
    int h264H;
    int h264Bitrate;

    int ip;
    int netmask;
    int gateway;

    int systime; //unix time

	unsigned short trig_shut;
	unsigned short trig_gain;

    int sensorType; // 0 CCD, 1 CMOS

	int rev[126];
};

struct DayTime
{
    unsigned char startHour;
    unsigned char startMinute;
    unsigned char endHour;
    unsigned char endMinute;
};
#endif




