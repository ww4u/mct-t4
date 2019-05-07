# -*- coding:utf-8 -*-

import sys
import os
pwd = os.path.abspath(os.path.dirname(__file__))
sys.path.append( pwd + "/../../lib/python")
from MegaGateway import *

if __name__ == "__main__":
    """
    
    """
    gateway = MageGateway()

################################
    mrhtList = gateway.mrgFindGateWay(0)
    print( mrhtList )

    mrht = mrhtList[0]
    visa =  gateway.mrgOpenGateWay(mrht, 800)
    print("device open:", visa)

    print( gateway.mrgGateWayIDNQuery(visa) )

    count = gateway.mrgFindDevice(visa, 800)
    print( "device count:", count )

    deviceList = gateway.mrgGetDeviceName(visa)
    print( "device list:", deviceList )

    deviceName = deviceList[0]
    deviceType = gateway.mrgGetDeviceType(visa, deviceName )
    print( "device type:", deviceType )

    channelCount = gateway.mrgGetDeviceChannelCount(visa, deviceName)
    print( "device channel count:", channelCount )

    deviceInfo = gateway.mrgGetDeviceInfo(visa, deviceName)
    print( "device info:", deviceInfo )

    deviceSoftwareVersion = gateway.mrgGetDeviceSoftVersion(visa, deviceName)
    print( "device software version:", deviceSoftwareVersion )


    firmWareHard = gateway.mrgGetFirmWareHard(visa, deviceName)
    print( "device firmWareHard:", firmWareHard )

    firmWareBoot = gateway.mrgGetFirmWareBoot(visa, deviceName)
    print( "device firmWareBoot:", firmWareBoot )


    firmWareFpga = gateway.mrgGetFirmWareFpga(visa, deviceName)
    print( "device firmWareFpga:", firmWareFpga )


    # deviceSerialNumber = gateway.mrgGetDeviceSerialNumber(visa, deviceName)
    # print( "device deviceSerialNumber:", deviceSerialNumber )

    # ret = gateway.mrgWriteDeviceSerial(visa, deviceName, "MRQM11040518C71111")
    # print("mrgWriteDeviceSerial", ret)
    
    deviceSerialNumber = gateway.mrgGetDeviceSerialNumber(visa, deviceName)
    print( "device deviceSerialNumber:", deviceSerialNumber )


    ret = gateway.mrgIdentify(visa, 1)
    print("mrgIdentify on", ret)
    time.sleep(1)
    ret = gateway.mrgIdentify(visa, 0)
    print("mrgIdentify off", ret)


    # ret = gateway.mrgModeSwitch(visa, 1)
    # print("mrgModeSwitch", ret)

    # IOXinStates = gateway.mrgGetXinState(visa)
    # print("IO Xin", IOXinStates)

    # gateway.mrgSetYoutState(visa, 1, 0)
    # gateway.mrgSetYoutState(visa, 2, 0)
    # gateway.mrgSetYoutState(visa, 1, 1)
    # gateway.mrgSetYoutState(visa, 2, 1)


################################
##  H2 示例 
    '''
    robotName = gateway.mrgBuildRobot(visa, "MRX-H2", 
                                            "0@%d,1@%d" % (deviceName, deviceName) )
    print("robot name:", robotName)

    ### 回零
    gateway.mrgRobotGoHome(visa, robotName, 0)
    print( gateway.mrgGetRobotCurrentPosition(visa, robotName) )

    ### 走一圈
    gateway.mrgRobotRelMove(visa, robotName, -1, 0, 300, 0, 1, 0)
    print( gateway.mrgGetRobotCurrentPosition(visa, robotName) )

    gateway.mrgRobotRelMove(visa, robotName, -1, 300, 0, 0, 1, 0)
    print( gateway.mrgGetRobotCurrentPosition(visa, robotName) )

    gateway.mrgRobotRelMove(visa, robotName, -1, 0, -300, 0, 1, 0)
    print( gateway.mrgGetRobotCurrentPosition(visa, robotName) )
    
    gateway.mrgRobotRelMove(visa, robotName, -1, -100, 0, 0, 0.5, 0)
    print( gateway.mrgGetRobotCurrentPosition(visa, robotName) )
    '''
################################
##  T4 示例     
    robotName = gateway.mrgBuildRobot(visa, "MRX-T4", 
                                            "0@%d,1@%d,2@%d,3@%d,4@%d" % (deviceName, deviceName,deviceName, deviceName,deviceName) )
    print("robot name:", robotName)

    ### 回零
    gateway.mrgRobotGoHome(visa, robotName, 0)
    print( gateway.mrgGetRobotCurrentPosition(visa, robotName) )

################################
    ret =  gateway.mrgCloseGateWay(visa)
    print("device close:", visa, ret)
################################