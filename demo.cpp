// demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iomanip>
#include <fstream>
#include <vector>
#include <iostream>
#include <HASdk.h>
#include <chrono>   // 包含 <thread> 头文件
#include <thread>
#include <string>
using namespace std;

//连接回调
void __stdcall ConnectEventCb(struct HA_Cam* cam, const char* ip,
    unsigned short port, int event, void* usrParam)
{
    if(event == 1)
        printf("连接成功\n");
else if (event == 2)
printf("连接断开\n");
}//定义连接事件回调函数 相机因意外事件断开连接或重新连接会触发此回调


//二维码回调
void __stdcall HA_QRCodeCb(
    struct HA_Cam* cam,
    unsigned char* code,
    void* resv,
    void* usrParam
) {
    cout << "收到二维码:" <<code <<endl;
}
//保存
void __stdcall saveFile(const char* fileName, unsigned int size, const unsigned char* faceImg) {
    std::ofstream file(fileName, std::ios::binary); // 创建二进制写入模式的文件流对象
    if (file) {

        // 将图像数据写入文件
        for (size_t i = 0; i < size; ++i) {
            file << static_cast<char>(faceImg[i]);
        }

        file.close(); // 关闭文件流
        std::cout << "成功保存图像数据！" << std::endl;
    }
    else {
        std::cerr << "无法打开文件！" << std::endl;
    }
}

////抓拍记录回调
void __stdcall HA_FaceRecoCb(
    struct HA_Cam* cam,
    const struct FaceRecoInfo* faceRecoInfo,
    void* usrParam
    ) {
    std::cout << "收到抓拍..." << faceRecoInfo->matchPersonNameEx<< endl;
    unsigned char* faceImg = faceRecoInfo->faceImg;
    unsigned short faceWInFaceImg = faceRecoInfo->faceWInFaceImg;
    unsigned short faceHInFaceImg = faceRecoInfo->faceHInFaceImg;
    saveFile("d:/opt/featureTest.jpg", faceWInFaceImg*faceHInFaceImg, faceImg);

    unsigned char* modelFaceImg = faceRecoInfo->modelFaceImg;
    saveFile("d:/opt/modelTest.jpg", faceRecoInfo->modelFaceImgLen, modelFaceImg);
   
}



//GPIO输入回调
//typedef void (HASDK_CALL *HA_GpioInputCb_t)(struct HA_Cam* cam, int type, unsigned int data, void* usrParam);
void __stdcall HA_GpioInputCb(
    struct HA_Cam* cam,
    int type,
    unsigned int data,
    void* usrParam
) {
    std::cout << "收到GPIO信号：type:" <<type<<",data:" <<data<< endl;
}

//韦根输入回调
//typedef void (HASDK_CALL *HA_WGInputCb_t)(struct HA_Cam* cam, int type, unsigned long long data, void* usrParam);
void __stdcall HA_WGInputCb(
    struct HA_Cam* cam, 
    int type, 
    unsigned long long data,
    void* usrParam) {
    std::cout << "收到韦根输入信号,type:" << type << ",data:" << data << endl;//收到韦根输入信号,type:18,data:0
}

//查询人员回调
void __stdcall faceQueryCb_t(struct HA_Cam* cam, const struct QueryFaceInfo* faceQueryInfo, void* usrParam) {
    //record_no=0代表查询结束
    printf("record_count=%d record_no=%d personID=%s version=%d\n", faceQueryInfo->record_count, faceQueryInfo->record_no, faceQueryInfo->personID, faceQueryInfo->version);
}

//收到JSON回调
/**
* @brief  UI交互信息
* @param  cam相机句柄
* @param  json_str json内容
* @param  usr_param 用户参数
*/
void __stdcall HA_UIJsonTransferCb(struct HA_Cam* cam, const char* json_str, void* usrParam) {
    //{"cmd": "data download","data_type": "3","data_size":"7k"}
    //{"attributeOfReg":1,"camId":"","cmd":"ShowRecord","dev_id":"F2E786-A7321E-0000FF","faceJpg...
    printf("收到JSON->%s\n", json_str);
}



struct Person {
    string name;
};

void test01() {
    Person* p0 = new Person;
    Person* p1 = new Person[2];
    Person** p2 = new Person*[2];
}
#if false
int main() {
    system("chcp 65001");
    test01();
    return 0;
}
#endif // false



int main()
{
    system("chcp 65001");
    //SetConsoleOutputCP(CP_UTF8);
    std::cout << "start..." << endl;
    HA_Init(); //SDK 初始化 整个程序运行期间只用初始化一次
    HA_InitFaceModel("D:\\cpp\\cppsdk\\model"); //人脸提取器初始化
    HA_SetNotifyConnected(1); //启用连接事件回调函数
    HA_RegConnectEventCb(ConnectEventCb, 0); //注册全局连接事件回调函数
  
    const char* p_ip = "192.168.0.73"; //相机 IP 地址
    int port = 9527; //port 固定为 9527;
    int erroNum = 0; /*错误码注 ：在老版本相机中错误码失败也能连接成功
    建议使用 HA_Connected 判断相机连接状态*/
    //HA_Cam* cam = HA_Connect(p_ip, port, "1admin", "1admin", &erroNum); //连接相机 
    HA_Cam* cam=HA_ConnectRelayServer(p_ip, port, "1admin", "1admin", &erroNum);

    if (HA_Connected(cam)) { //判断相机连接状态
        printf("相机连接成功\n");
        HA_RegFaceRecoCb(cam, HA_FaceRecoCb,0);//抓拍回调
        HA_RegQRCodeCb(cam, HA_QRCodeCb, 0);//二维码回调
        HA_RegGpioInputCb(cam, HA_GpioInputCb, 0);//GPIO回调
        HA_RegWGInputCb(cam, HA_WGInputCb, 0);//韦根回调
        HA_UIJsonTransferCb(cam, HA_UIJsonTransferCb, 0);//收到json回调
    }
    else {
        printf("相机连接失败\n");
    }
/*************************************
SDK 其他接口调用
*************************************/

//功能授权
#if false
    const char* data = "4AB456A35614467FC8B8AAA117F105DD47E0F3F596A6E7BA";
    int len=strlen(data);
    cout << "正在授权..." << endl;
    int res = HA_FunctionAuth(cam, 8, data,len);
    cout << "授权结果：:" << res << endl;
#endif

//人脸过滤
#if false
    struct FaceSystemConfig* cfg = new FaceSystemConfig;
    HA_GetFaceSystemCfgEx(cam, cfg);
    struct FacePrivateParam* pFpp = (struct FacePrivateParam*)&cfg->app.priv;
    //printf("ma-set-timeout:%d,interval:%d*************\n",pFpp->replication_timeout,pFpp->replication_interval);
   // pFpp->min_face_size = m_scc->min_face_size;
    cout << "人脸识别距离：" << pFpp->min_face_size<< endl;
    pFpp->min_face_size = 60;
    HA_SetFaceSystemCfgEx(cam, cfg);

    
#endif

//发送httpjson
#if false
    const char* json = "{\"cmd\":\"gpio control Extend\",\"port\":1,\"ctrl_type\":\"on\",\"ctrl_mode\":\"force\",\"person_id\":\"0001\",\"voicePlay\":\"No0.pass.wav\"}";
    const char* cmd = "gpio control Extend";
    char reply[1024] = {0};
    unsigned int size = strlen(json);
    int code=HA_SendJson(cam, cmd, json, size, reply, 1024);
    cout << "返回code:" << code << endl;
    cout <<"返回结果："<< reply << endl;
#endif

//原图注册
#if false
    
    FaceFlags faceID; //注册人员信息
    FaceImage face;//人脸图片信息
    face.img_fmt = 1;//jpg格式
    face.height = 0;
    face.width = 0;
    face.img_seq = 0;

    // 1.Open picture file
    std::ifstream is("D:\\tqh.jpg", std::ifstream::binary);
    // 2.get length of file:
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);
    // 3.Create buffer
    char* buffer = new char[length];
    std::cout << "Reading " << length << " bits... \n";
    // 4.read data as a block:
    is.read(buffer, length);
    if (is)
        std::cout << "picture read successfully."<<endl;
    else
        std::cout << "error: only " << is.gcount() << " could be read";
    is.close();
    face.img_len = length;
    face.img = (unsigned char*)buffer; 
    /*face.img= new unsigned char[length];
    std::memcpy(face.img, (unsigned char*)buffer, length);*/
    faceID.effectTime = 0xFFFFFFFF; //有效时间(永久有效)
    faceID.effectStartTime = 0; //有效开始时间
    faceID.role = 1; //人员角色
   
    strcpy_s(faceID.faceID, "003"); //注册人员 ID（必须唯一）
    strcpy_s(faceID.faceName, "张三");//注册人员姓名
    strcpy_s(faceID.userParam, "自定义123");
    strcpy_s(faceID.worksiteID, "");
    faceID.ScheduleMode = 0;
    //for (int i = 0; i < 50; i++) {
        //std::string str = "000" + std::to_string(1);
        //strcpy_s(faceID.faceID, str.c_str()); //注册人员 ID（必须唯一）
        int a = HA_AddFacesByJpg(cam, &faceID, &face, 1);
        std::cout << "注册人脸返回：" << a << endl; 
    //}
    delete[] buffer;
    
    
#endif

//人脸图片校验
#if false

    // 1.Open picture file
    std::wstring filePath = L"D:\\muti3.jpg";
    std::ifstream is(filePath, std::ifstream::binary);
    // 2.get length of file:
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);
    // 3.Create buffer
    char* buffer = new char[length];
    std::cout << "Reading " << length << " bits... \n";
    // 4.read data as a block:
    is.read(buffer, length);
    if (is)
        std::cout << "picture read successfully." << endl;
    else
        std::cout << "error: only " << is.gcount() << " could be read";
    is.close();
    HA_SetFaceCheckLevel(1);
    int code=HA_FaceJpgLegal((const unsigned char*)buffer, length);
    /**
    *  @brief  通过路径提取归一化图像和人脸略缩图像
    *  @param  [IN] jpg 人脸图像路径，图像格式须为JPG
    *  @param  [OUT] twist_image 归一化图像数据 bgr格式 至少分配70K内存
    *  @param  [OUT] twist_size 归一化图像数据长度
    *  @param  [OUT] twist_width 归一化图像数宽
    *  @param  [OUT] twist_height 归一化图像高
    *  @param  [OUT] faceImgJpg 抠出的人脸略缩图像
    *  @param  [OUT] faceJpgLen 抠出的人脸略缩图像长度
    *  @return 返回值为0表示成功，返回负数表示失败，具体参考错误码
    *  const unsigned char *img_path, unsigned char *twist_image, int *twist_size, int *twist_width, int *twist_height, unsigned char *faceImgJpg, int *faceJpgLen
    */
    /*
    const unsigned char path[] = "D:\\muti.jpg";
    unsigned char* twist_image = new unsigned char[1024*80];
    int twist_size = 0;
    int twist_width = 0;
    int twist_height = 0;
    unsigned char* faceImgJpg =new unsigned char[1024];
    int faceJpgLen = 0;
    int code = HA_GetJpgPathFeatureImage(&path[0], twist_image,&twist_size,&twist_width,&twist_height,faceImgJpg,&faceJpgLen);
    */

    std::cout << "校验结果:" << code << endl;
    delete[] buffer;
#endif

//LCD图片显示
#if false
    ImageShowPlan image;
    image.x = 0;
    image.y = 50;
    image.formt = 0;
    image.alive_time = 5000;

    // 1.Open picture file
    std::ifstream is("D:\\cat.jpg", std::ifstream::binary);
    // 2.get length of file:
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);
    // 3.Create buffer
    char* buffer = new char[length];
    std::cout << "Reading " << length << " bits... \n";
    // 4.read data as a block:
    is.read(buffer, length);
    if (is)
        std::cout << "picture read successfully." << endl;
    else
        std::cout << "error: only " << is.gcount() << " could be read";
    is.close();
    image.data_size = length;
    image.data= (unsigned char*)buffer;
    int ret=HA_LCDImageDisplay(cam, &image);
    cout << "ret:" << ret << endl;
#endif

//继电器输出
#if true
    char* resv = new char[24];
    resv[0] = 1;
    //port:1代表触发白名单，2代表触发黑名单
    HA_SetGPIO(cam, 1, 2, 1,resv);
    //HA_SetGPIO(cam, 2, 2, 1, resv);
    delete[] resv;
#endif

#if false
    int res=HA_TestAudioItem(cam, 101);//0代表请通行
    if (res==0) {
        cout << "测试音频成功！" << endl;
    }
    else {
        cout << "测试音频失败！！！   " <<res <<endl;
    }

#endif

//查询人脸库
#if false
    HA_RegFaceQueryCb(cam, faceQueryCb_t, NULL);//注册回调函数
    char flags = 0;
    short mode = 1;//模糊查询
    QueryCondition condition;//查询条件
    //strcpy_s(condition.faceID, "9527");
    strcpy_s(condition.faceName, "访客");
    //flags |= QUERY_BY_ID;
    flags |= QUERY_BY_NAME;//条件为姓名查询
    int ret = HA_QueryFaceEx(cam, -1, 1, 5, 1, 100, flags, mode, &condition);
    if (ret == ERR_NONE) {
        printf("查询成功\n");
    }
    else {
        printf("查询失败 ret=%d\n", ret);
    }
#endif

#if false
    HA_TTSPlayAudio(cam, "欢迎光临");
#endif

#if false 截图
    printf("开始截图...\n");
   
    int len = 1024 * 300;
    unsigned char* jpg = new unsigned char[len];
    int jpg_size = 0;
    int ret = HA_SnapshotEx(cam, jpg, len, &jpg_size);
    printf("返回错误码：%d\n" , ret);
    //cout << "返回code:" << ret << endl;
    if (ret == 0) {
        printf("照片大小：%d KB\n", jpg_size / 1024);
        saveFile("d:/22222222.jpg", jpg_size, jpg);
    }
#endif



Sleep(60000);
HA_DeInit(); // SD 资源释放 程序结束时调用
std::cout << "销毁..." << endl;
return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
