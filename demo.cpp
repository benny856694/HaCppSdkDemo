#include <iomanip>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <HASdk.h>
#include <filesystem>
#include "demo.h"
using namespace std;


bool ReadAllBytes(const string& fullPath, byte* &pBuffer, int& length)
{
    std::ifstream is(fullPath, std::ifstream::binary);
    if (!is.is_open())
    {
        return false;
    }

    // 2. Get length of file
    is.seekg(0, is.end);
    length = is.tellg();
    is.seekg(0, is.beg);
    // 3. Create buffer
    pBuffer = new byte[length];
    // 4. Read data as a block
    is.read(reinterpret_cast<char*>(pBuffer), length);
    
    return !is.fail();
}

bool WriteBytesToFile(const std::string& filename, const byte* data, size_t len) {
    // Open the file in binary write mode
    std::ofstream file(filename, std::ios::binary);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // Write the data to the file
    file.write((const char*)data, len);

    // Check for errors during writing
    if (file.fail()) {
        std::cerr << "Error writing to file: " << filename << std::endl;
        return false;
    }

    return true; // Success
}

// Connection callback
void HASDK_CALL ConnectEventCb(struct HA_Cam* cam, const char* ip,
    unsigned short port, int event, void* usrParam)
{
    if (event == 1)
        printf("Connection successful\n");
    else if (event == 2)
        printf("Connection disconnected\n");
}
// Defines a connection event callback function that will be triggered when the camera is disconnected or reconnected due to unexpected events

// QR code callback
void HASDK_CALL HA_QRCodeCb(
    struct HA_Cam* cam,
    unsigned char* code,
    void* resv,
    void* usrParam
) {
    cout << "Received QR code: " << code << endl;
}

// Capture record callback
void HASDK_CALL HA_FaceRecoCb(
    struct HA_Cam* cam,
    const struct FaceRecoInfo* info,
    void* usrParam
    ) 
{
    cout << endl << endl;
    cout << "Received capture data..." << endl;
    if (info->matched > 0)
    {
        cout << "successful match" << endl;
        cout << "person id:" << info->matchPersonId << endl;
        cout << "person name:" << info->matchPersonName << endl;
        cout << "person nameEx:" << info->matchPersonNameEx << endl;
        if (info->existFaceImg)
        {
            static int i = 0;
            cout << "Face image" << endl;
            cout << "\timage length: " << info->faceImgLen << endl;
            cout << "\tface img data ptr: " << std::hex << reinterpret_cast<int>(info->faceImg) << std::dec << endl;
            cout << "\tface position: x="
                << info->faceXInFaceImg
                << ",y=" << info->faceYInFaceImg
                << ",w=" << info->faceWInFaceImg
                << ",h=" << info->faceHInFaceImg
                << endl;
            std::stringstream faceImageName;
            faceImageName << "FaceImg" << i++ 
                << "(" 
                << info->faceXInFaceImg << ","
                << info->faceYInFaceImg << ","
                << info->faceWInFaceImg << ","
                << info->faceHInFaceImg << ","
                << ")"
                << ".jpg";
            WriteBytesToFile(faceImageName.str(), info->faceImg, info->faceImgLen);
        }

        if (info->existImg)
        {
            static int i = 0;
            cout << "Full image" << endl;
            cout << "\timage length: " << info->imgLen << endl;
            cout << "\timg data ptr: " << std::hex << reinterpret_cast<int>(info->img) << std::dec << endl;
            cout << "\tface position: x="
                << info->faceXInImg
                << ",y=" << info->faceYInImg
                << ",w=" << info->faceWInImg
                << ",h=" << info->faceHInImg
                << endl;
            std::stringstream faceImageName;
            faceImageName << "FullImg" << i++
                << "("
                << info->faceXInImg << ","
                << info->faceYInImg << ","
                << info->faceWInImg << ","
                << info->faceHInImg << ","
                << ")"
                << ".jpg";
            WriteBytesToFile(faceImageName.str(), info->img, info->imgLen);
        }
       
    }
    else
    {
        cout << "failed match" << endl;
    }
}

// Wiegand input callback, type=18 represents door sensor signal
// typedef void (HASDK_CALL *HA_WGInputCb_t)(struct HA_Cam* cam, int type, unsigned long long data, void* usrParam);
void HASDK_CALL HA_WGInputCb(
    struct HA_Cam* cam,
    int type,
    unsigned long long data,
    void* usrParam) {
    std::cout << "Received Wiegand input signal, type: " << type << ", data: " << data << endl; // Received Wiegand input signal, type: 18, data: 0
}

// Query personnel callback
void HASDK_CALL faceQueryCb_t(struct HA_Cam* cam, const struct QueryFaceInfo* faceQueryInfo, void* usrParam) {
    // record_no=0 means the query is finished
    printf("record_count=%d record_no=%d personID=%s version=%d\n", faceQueryInfo->record_count, faceQueryInfo->record_no, faceQueryInfo->personID, faceQueryInfo->version);
}

// JSON callback
void HASDK_CALL HA_UIJsonTransferCb(struct HA_Cam* cam, const char* json_str, void* usrParam) {
    // {"cmd": "data download", "data_type": "3", "data_size": "7k"}
    // {"attributeOfReg": 1, "camId": "", "cmd": "ShowRecord", "dev_id": "F2E786-A7321E-0000FF", "faceJpg...
    printf("Received JSON -> %s\n", json_str);
}

void RegisterFace(HA_Cam* cam)
{
    FaceFlags faceID = { 0 }; // Register personnel information
    FaceImage face; // Face image information
    face.img_fmt = 1; // JPG format
    face.height = 0;
    face.width = 0;
    face.img_seq = 0;

    // 1. Open picture file
    byte* pBuffer = nullptr;
    int len = 0;
    bool suc = ReadAllBytes("d:\\sample.jpg", pBuffer, len);
    if (!suc)
    {
        cout << "read file error, fail to register face image" << endl;
        return;
    }
    face.img_len = len;
    face.img = (byte*)pBuffer;

    faceID.effectTime = 0xFFFFFFFF; // Authorization end time (permanently valid)
    faceID.effectStartTime = 0; // Authorization start time
    faceID.role = 1; // Personnel role
    strcpy_s(faceID.faceID, "a builtiful girl"); // Registered personnel ID (must be unique)
    strncpy_s(faceID.faceNameEx, "Abdurahmonov Shodmonxodja Eshmatxodja ogli", sizeof(faceID.faceNameEx)); // Registered personnel name
    strcpy_s(faceID.userParam, "Custom 123");
    strcpy_s(faceID.worksiteID, ""); // Specify platform ID, pass empty string
    faceID.ScheduleMode = 0;
    int a = HA_AddFacesByJpg(cam, &faceID, &face, 1);
    std::cout << "Face registration return: " << a << endl;
    delete[] pBuffer;
}


void ExtractFaceImage(const string& fullImagePath)
{
    int feature_size = 256 * 1024;
    byte* feature_image = new byte[feature_size];
    int imgLen = 0;
    byte* pBuffer = nullptr;
    int faceJpgLen = 128 * 1024;
    byte* faceImgJpg = new byte[faceJpgLen];
    bool suc = ReadAllBytes(fullImagePath, pBuffer, imgLen);
    if (!suc)
    {
        cout << "can't read file" << endl;
        return;
    }
    int ret = HA_GetJpgFeatureImageNew(pBuffer, faceJpgLen, feature_image, &feature_size, faceImgJpg, &faceJpgLen, NULL);
    delete[] feature_image;
    delete[] faceImgJpg;
    delete[] pBuffer;
}


int main(int argc, char* argv[])
{
    if (argc < 1)
    {
        cout << "you must input an ip of the device" << endl;
        return 0;
    }

    cout << "device ip: " << argv[1] << endl;
#ifdef WINDOWS
    system("chcp 65001");
#endif
    HA_Init(); // SDK initialization, only need to initialize once during the whole program runtime
    HA_InitFaceModel("d:\\model"); // Face extractor initialization, the model folder is in the SDK zip package
    HA_SetNotifyConnected(1); // Enable connection event callback function
    HA_RegConnectEventCb(ConnectEventCb, 0); // Register global connection event callback function

    const char* p_ip = argv[1]; // Camera IP address
    int port = 9527; // Port fixed at 9527
    int erroNum = 0; /* Error code: Note that in older camera versions, the error code may allow connection success. It is recommended to use HA_Connected to check the camera connection status */
    HA_Cam* cam = HA_Connect(p_ip, port, NULL, NULL, &erroNum); // Connect to camera

    if (HA_Connected(cam)) { // Check camera connection status
        printf("Camera connected successfully\n");
        HA_RegFaceRecoCb(cam, HA_FaceRecoCb, 0); // Capture callback
        HA_RegQRCodeCb(cam, HA_QRCodeCb, 0); // QR code callback
        HA_RegWGInputCb(cam, HA_WGInputCb, 0); // Wiegand callback
        //HA_UIJsonTransferCb(cam, HA_UIJsonTransferCb, 0); // JSON callback
    }
    else {
        printf("Camera connection failed\n");
    }

    // Additional SDK interface calls
    // Register face with original image
#if true
    RegisterFace(cam);
#endif

    // Face image verification
#if false
    // 1. Open picture file
    std::wstring filePath = L"D:\\cat.jpg";
    std::ifstream is(filePath, std::ifstream::binary);
    // 2. Get length of file
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);
    // 3. Create buffer
    char* buffer = new char[length];
    std::cout << "Reading " << length << " bits... \n";
    // 4. Read data as a block
    is.read(buffer, length);
    if (is)
        std::cout << "Picture read successfully." << endl;
    else
        std::cout << "Error: only " << is.gcount() << " could be read";
    is.close();
    int code = HA_FaceJpgLegal((const unsigned char*)buffer, length);
    std::cout << "Verification result: " << code << endl;
    delete[] buffer;
#endif

    // Send JSON
#if false
    const char* json = "{\"cmd\":\"gpio control Extend\",\"port\":1,\"ctrl_type\":\"on\",\"ctrl_mode\":\"force\",\"person_id\":\"0001\",\"voicePlay\":\"No0.pass.wav\"}";
    const char* cmd = "gpio control Extend";
    char reply[1024] = { 0 };
    unsigned int size = strlen(json);
    int code = HA_SendJson(cam, cmd, json, size, reply, 1024);
    cout << "Return code: " << code << endl;
    cout << "Return result: " << reply << endl;
#endif

    // Feature authorization
#if false
    const char* data = "4AB456A35614467FC8B8AAA117F105DD47E0F3F596A6E7BA";
    int len = strlen(data);
    cout << "Authorizing..." << endl;
    int res = HA_FunctionAuth(cam, 8, data, len);
    cout << "Authorization result: " << res << endl;
#endif

    // Face filtering
#if false
    struct FaceSystemConfig* cfg = new FaceSystemConfig;
    HA_GetFaceSystemCfgEx(cam, cfg);
    struct FacePrivateParam* pFpp = (struct FacePrivateParam*)&cfg->app.priv;
    cout << "Face recognition distance: " << pFpp->min_face_size << endl;
    pFpp->min_face_size = 60;
    HA_SetFaceSystemCfgEx(cam, cfg);
#endif

    // Relay output, remember to turn off relay linkage, otherwise you cannot trigger a single relay
#if false
    char* resv = new char[24];
    resv[0] = 1;
    HA_SetGPIO(cam, 1, 2, 1, resv); // This means triggering the whitelist
    delete[] resv;
#endif

    // Voice broadcast
#if false
    HA_TestAudioItem(cam, 0); // 0 means please pass, other voice see facedemo built-in audio serial number
#endif

    // TTS broadcast
#if false
    HA_TTSPlayAudio(cam, "Welcome"); // Authorization TTS is required before use
#endif

    // Query face library
#if false
    HA_RegFaceQueryCb(cam, faceQueryCb_t, NULL); // Register callback function
    char flags = 0;
    short mode = 1; // Fuzzy query
    QueryCondition condition; // Query condition
    strcpy_s(condition.faceName, "Visitor");
    flags |= QUERY_BY_NAME; // Condition is name query
    int ret = HA_QueryFaceEx(cam, -1, 1, 5, 1, 100, flags, mode, &condition);
    if (ret == ERR_NONE) {
        printf("Query successful\n");
    }
    else {
        printf("Query failed ret=%d\n", ret);
    }
#endif

    // Screenshot
#if false
    printf("Starting screenshot...\n");
    int len = 1024 * 300;
    unsigned char* jpg = new unsigned char[len];
    int jpg_size = 0;
    int ret = HA_SnapshotEx(cam, jpg, len, &jpg_size);
    printf("Return error code: %d\n", ret);
    if (ret == 0) {
        printf("Photo size: %d KB\n", jpg_size / 1024);
        saveFile("d:/22222222.jpg", jpg_size, jpg);
    }
#endif

    std::cout << "press any key to exit" << endl;
    std::cin.get(); //read any key
    HA_DeInit(); // SDK resource release, called at the end of the program
    std::cout << "Destroying..." << endl;
}
