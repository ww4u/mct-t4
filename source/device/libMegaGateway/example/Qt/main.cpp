<<<<<<< HEAD

#include "MegaGateway.h"
#include <stdio.h>

int main()
{
    int i;
    char buff[4096] = "";
    char mrhtList[20][64] = {""};
    char mrht[64] = "";

    mrgFindGateWay(0, buff, sizeof(buff), 1);

    char *p, *pNext;
    int count = 0;
    p = STRTOK_S(buff, ",", &pNext);
    while (p){
        strcpy(mrhtList[count++], p);
        p = STRTOK_S(NULL, ",", &pNext);
    }

    for(i=0; i<count; i++){
        printf("Find MRH-T[%d]: %s\n", i, mrhtList[i]);
    }
    if(count <= 0){
        printf("Search MRH-T is empty!!!\n");
        return -1;
    }

    strcpy(mrht, mrhtList[0]);
    int visa =  (int)mrgOpenGateWay(mrht, 800);
    printf("device open: %d\n", visa);

    char IDN[64] = "";
    mrgGateWayIDNQuery(visa, IDN);
    printf("device IDN: %s\n", IDN);


#if 0
    //! 搜索并构建机器人
    count = mrgFindDevice(visa, 800);
    printf( "device count: %d\n", count);

    int deviceList[32];
    mrgGetDeviceName(visa, deviceList);
    for(i=0; i<count; i++){
        printf("Find MRQ Device[%d]: %d\n", i, deviceList[i]);
    }
    if(count <= 0){
        printf("Search MRH-T is empty!!!\n");
        return -2;
    }

    int deviceName = deviceList[0];
    char deviceType[32] = "";
    mrgGetDeviceType(visa, deviceName, deviceType);
    printf( "device type: %s\n", deviceType );

    int channelCount = mrgGetDeviceChannelCount(visa, deviceName);
    printf( "device channel count: %d\n", channelCount );

    int robotName = 0;
    sprintf(buff,"0@%d,1@%d", deviceName, deviceName);
    mrgBuildRobot(visa, "MRX-H2", buff, &robotName );
    printf("robot name: %d\n", robotName);

    //! 测试运动
    // 回零
    float posx,posy,posz;
    mrgRobotGoHomeWithParam(visa, robotName, 100, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);

    // 走一圈
    mrgRobotRelMove(visa, robotName, -1, 0, 300, 0, 1, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);

    mrgRobotRelMove(visa, robotName, -1, 300, 0, 0, 1, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);

    mrgRobotRelMove(visa, robotName, -1, 0, -300, 0, 1, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);

    mrgRobotRelMove(visa, robotName, -1, -100, 0, 0, 0.5, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);
#endif

#if 1
    //! 测试IO
    // 打开IO模式
    mrgSetProjectMode(visa, 1);

    unsigned int IOXinStates = 0;
    //循环查询IO
    while(1){
        //GetXinState
        int ret = mrgProjectGetXinState(visa, &IOXinStates);
        if(ret < 0){
            printf("mrgGetXinState error, %d\n", ret);
            Sleep(100);
            continue;
//            return -1;
        }

        int xin1 = IOXinStates & 0x01;
        int xin2 = (IOXinStates & 0x02) >> 1;
        int xin3 = (IOXinStates & 0x04)>> 2;
        int xin4 = (IOXinStates & 0x08) >> 3;

        printf("IO Xin: \t%d,\t%d,\t%d,\t%d\n", xin1, xin2, xin3, xin4);
        if(xin1 == 1)
        {
            mrgProjectSetYout(visa, 0, 1);
            Sleep(2000);
            mrgProjectSetYout(visa, 0, 0);
        }
        else if(xin2 == 1)
        {
            mrgProjectSetYout(visa, 1, 1);
            Sleep(2000);
            mrgProjectSetYout(visa, 1, 0);
        }
        else{
            printf("Wait IO...\n");
            Sleep(100);
        }

        Sleep(100);
    }
#endif



    int ret =  mrgCloseGateWay(visa);
    printf("device close: %d %d\n", visa, ret);

    printf("Press AnyKey Continue...\n");
    getchar();
    return 0;
}
=======

#include "MegaGateway.h"
#include <stdio.h>

int main()
{
    int i;
    char buff[4096] = "";
    char mrhtList[20][64] = {""};
    char mrht[64] = "";

    mrgFindGateWay(0, buff, sizeof(buff), 1);

    char *p, *pNext;
    int count = 0;
    p = STRTOK_S(buff, ",", &pNext);
    while (p){
        strcpy(mrhtList[count++], p);
        p = STRTOK_S(NULL, ",", &pNext);
    }

    for(i=0; i<count; i++){
        printf("Find MRH-T[%d]: %s\n", i, mrhtList[i]);
    }
    if(count <= 0){
        printf("Search MRH-T is empty!!!\n");
        return -1;
    }

    strcpy(mrht, mrhtList[0]);
    int visa =  (int)mrgOpenGateWay(mrht, 800);
    printf("device open: %d\n", visa);

    char IDN[64] = "";
    mrgGateWayIDNQuery(visa, IDN);
    printf("device IDN: %s\n", IDN);


#if 0
    //! 搜索并构建机器人
    count = mrgFindDevice(visa, 800);
    printf( "device count: %d\n", count);

    int deviceList[32];
    mrgGetDeviceName(visa, deviceList);
    for(i=0; i<count; i++){
        printf("Find MRQ Device[%d]: %d\n", i, deviceList[i]);
    }
    if(count <= 0){
        printf("Search MRH-T is empty!!!\n");
        return -2;
    }

    int deviceName = deviceList[0];
    char deviceType[32] = "";
    mrgGetDeviceType(visa, deviceName, deviceType);
    printf( "device type: %s\n", deviceType );

    int channelCount = mrgGetDeviceChannelCount(visa, deviceName);
    printf( "device channel count: %d\n", channelCount );

    int robotName = 0;
    sprintf(buff,"0@%d,1@%d", deviceName, deviceName);
    mrgBuildRobot(visa, "MRX-H2", buff, &robotName );
    printf("robot name: %d\n", robotName);

    //! 测试运动
    // 回零
    float posx,posy,posz;
    mrgRobotGoHomeWithParam(visa, robotName, 100, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);

    // 走一圈
    mrgRobotRelMove(visa, robotName, -1, 0, 300, 0, 1, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);

    mrgRobotRelMove(visa, robotName, -1, 300, 0, 0, 1, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);

    mrgRobotRelMove(visa, robotName, -1, 0, -300, 0, 1, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);

    mrgRobotRelMove(visa, robotName, -1, -100, 0, 0, 0.5, 0);
    mrgGetRobotCurrentPosition(visa, robotName, &posx, &posy, &posz);
    printf("Current Pos:\t%f,\t%f,\t%f\n", posx, posy, posz);
#endif

#if 1
    //! 测试IO
    // 打开IO模式
    mrgSetProjectMode(visa, 1);

    unsigned int IOXinStates = 0;
    //循环查询IO
    while(1){
        //GetXinState
        int ret = mrgProjectGetXinState(visa, &IOXinStates);
        if(ret < 0){
            printf("mrgGetXinState error, %d\n", ret);
            Sleep(100);
            continue;
//            return -1;
        }

        int xin1 = IOXinStates & 0x01;
        int xin2 = (IOXinStates & 0x02) >> 1;
        int xin3 = (IOXinStates & 0x04)>> 2;
        int xin4 = (IOXinStates & 0x08) >> 3;

        printf("IO Xin: \t%d,\t%d,\t%d,\t%d\n", xin1, xin2, xin3, xin4);
        if(xin1 == 1)
        {
            mrgProjectSetYout(visa, 0, 1);
            Sleep(2000);
            mrgProjectSetYout(visa, 0, 0);
        }
        else if(xin2 == 1)
        {
            mrgProjectSetYout(visa, 1, 1);
            Sleep(2000);
            mrgProjectSetYout(visa, 1, 0);
        }
        else{
            printf("Wait IO...\n");
            Sleep(100);
        }

        Sleep(100);
    }
#endif



    int ret =  mrgCloseGateWay(visa);
    printf("device close: %d %d\n", visa, ret);

    printf("Press AnyKey Continue...\n");
    getchar();
    return 0;
}
>>>>>>> a22e98e36b22281ea732cdc8940c7580a9981c01
