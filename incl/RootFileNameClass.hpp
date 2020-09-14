#ifndef RootFileNameClass_hpp
#define RootFileNameClass_hpp
#include <iostream>
#include "TString.h"

class RootFileNameClass
{
private:
    /* data */
public:
    RootFileNameClass(/* args */);
    ~RootFileNameClass();
    TString FileNameSet_LAB[30] = 
    {
        // 0-8
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser265nmC95_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser270nmC60_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser280nmC50_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser290nmC45_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser300nmC41_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser310nmC35_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser320nmC31_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser330nmC29_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/LAB_HV3005_laser340nmC29_T100mV_under25de.root",

        // 9-12
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/LAB_HV3002_laser375nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/LAB_HV3002_laser390nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/LAB_HV3002_laser405nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/LAB_HV3002_laser430nmC40_T100_under25deg.root",

        //13-14
        // "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200116/LAB_HV3002_laser405\(375\)nmC40_T100_roomtemp.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200116/LAB_HV3002_laser405nmC40_T100_roomtemp.root",

    };


    TString FileNameSet_SLS[40] = 
    {
        // "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119/SLS_HV3005_laser265nmC69_T100mV_under25de.root",//随便省略一个
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119/SLS_HV3005_laser265nmC70_T100mV_under25de.root",
        // "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119/SLS_HV3005_laser270nmC55_T100mV_under25de.root",//随便省略一个
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119/SLS_HV3005_laser270nmC60_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119/SLS_HV3005_laser280nmC50_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119/SLS_HV3005_laser290nmC45_T100mV_under25de.root",

        //这个文件可能有点问题 "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/SLS_HV3005_laser265nmC69_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/SLS_HV3005_laser300nmC41_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/SLS_HV3005_laser310nmC35_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/SLS_HV3005_laser320nmC31_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/SLS_HV3005_laser330nmC29_T100mV_under25de.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200119_back/SLS_HV3005_laser340nmC26_T100mV_under25de.root",

        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/SLS_HV3002_laser405(355)nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/SLS_HV3002_laser365nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/SLS_HV3002_laser375nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/SLS_HV3002_laser385nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/SLS_HV3002_laser395nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/SLS_HV3002_laser405nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200117/SLS_HV3002_laser415nmC40_T100_under25deg.root",

        // "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/SLS_HV3002_laser415nmC40_T100_under25deg.root",//随便省略一个
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/SLS_HV3002_laser425nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/SLS_HV3002_laser435nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/SLS_HV3002_laser445nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/SLS_HV3002_laser455nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/SLS_HV3002_laser465nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/SLS_HV3002_laser475nmC40_T100_under25deg.root",

    };

    TString FileNameSet_LS[50] = 
    {
        // "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118_405/LS_HV3002_laser405nmC40_T100_under25deg.root",

        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser355nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser365nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser375nmC20_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser375nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser385nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser395nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser415(405)nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser415nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser425nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser435nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser445nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser455nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser465nmC40_T100_under25deg.root",
        "/Users/dengjiawei/20200401/20200401PMTGainCalibration/20200118/LS_HV3002_laser475nmC40_T100_under25deg.root",

    };

};

RootFileNameClass::RootFileNameClass(/* args */)
{
}

RootFileNameClass::~RootFileNameClass()
{

}

#endif