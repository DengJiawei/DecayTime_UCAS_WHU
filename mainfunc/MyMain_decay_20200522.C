#include "MyReadBinary.h"
#include "MyDataAnalysisClass.hpp"
#include "time.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TStyle.h"
#include "TSystem.h"

//2020.5.24~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* 
TString FilePath_set[] = {
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser265nmC95_T100mV_under25de/LAB_HV3005_laser265nmC95_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser270nmC60_T100mV_under25de/LAB_HV3005_laser270nmC60_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser280nmC50_T100mV_under25de/LAB_HV3005_laser280nmC50_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser290nmC45_T100mV_under25de/LAB_HV3005_laser290nmC45_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser300nmC41_T100mV_under25de/LAB_HV3005_laser300nmC41_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser310nmC35_T100mV_under25de/LAB_HV3005_laser310nmC35_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser320nmC31_T100mV_under25de/LAB_HV3005_laser320nmC31_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser330nmC29_T100mV_under25de/LAB_HV3005_laser330nmC29_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/LAB_HV3005_laser340nmC29_T100mV_under25de/LAB_HV3005_laser340nmC29_T100mV_under25de",

    "/Volumes/BackupPlus/ExperimentData/20200119/SLS_HV3005_laser265nmC69_T100mV_under25de/SLS_HV3005_laser265nmC69_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/SLS_HV3005_laser300nmC41_T100mV_under25de/SLS_HV3005_laser300nmC41_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/SLS_HV3005_laser310nmC35_T100mV_under25de/SLS_HV3005_laser310nmC35_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/SLS_HV3005_laser320nmC31_T100mV_under25de/SLS_HV3005_laser320nmC31_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/SLS_HV3005_laser330nmC29_T100mV_under25de/SLS_HV3005_laser330nmC29_T100mV_under25de",
    "/Volumes/BackupPlus/ExperimentData/20200119/SLS_HV3005_laser340nmC26_T100mV_under25de/SLS_HV3005_laser340nmC26_T100mV_under25de"  
};
*/
/* 
TString FilePath_set[] = 
{
    "/Volumes/BackupPlus/ExperimentData/20200118_405/LS_HV3002_laser405nmC40_T100_under25deg/LS_HV3002_laser405nmC40_T100_under25deg",
    
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser355nmC40_T100_under25deg/LS_HV3002_laser355nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser365nmC40_T100_under25deg/LS_HV3002_laser365nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser375nmC20_T100_under25deg/LS_HV3002_laser375nmC20_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser375nmC40_T100_under25deg/LS_HV3002_laser375nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser385nmC40_T100_under25deg/LS_HV3002_laser385nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser395nmC40_T100_under25deg/LS_HV3002_laser395nmC40_T100_under25deg",

    // 这两行名字有问题，是相似的，会覆盖掉一个
    // "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser415\(405\)nmC40_T100_under25deg/LS_HV3002_laser415nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser415nmC40_T100_under25deg/LS_HV3002_laser415nmC40_T100_under25deg",

    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser425nmC40_T100_under25deg/LS_HV3002_laser425nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser435nmC40_T100_under25deg/LS_HV3002_laser435nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser445nmC40_T100_under25deg/LS_HV3002_laser445nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser455nmC40_T100_under25deg/LS_HV3002_laser455nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser465nmC40_T100_under25deg/LS_HV3002_laser465nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/LS_HV3002_laser475nmC40_T100_under25deg/LS_HV3002_laser475nmC40_T100_under25deg",
    
    // 这行名字有问题 下面行末尾没有_
    // "/Volumes/BackupPlus/ExperimentData/20200118/SLS_HV3002_laser415nmC40_T100_under25deg/SLS_HV3002_laser415nmC40_T100_under25deg",

    "/Volumes/BackupPlus/ExperimentData/20200118/SLS_HV3002_laser425nmC40_T100_under25deg/SLS_HV3002_laser425nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/SLS_HV3002_laser435nmC40_T100_under25deg/SLS_HV3002_laser435nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/SLS_HV3002_laser445nmC40_T100_under25deg/SLS_HV3002_laser445nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/SLS_HV3002_laser455nmC40_T100_under25deg/SLS_HV3002_laser455nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/SLS_HV3002_laser465nmC40_T100_under25deg/SLS_HV3002_laser465nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200118/SLS_HV3002_laser475nmC40_T100_under25deg/SLS_HV3002_laser475nmC40_T100_under25deg",  
};
*/
/*
TString FilePath_set[] = 
{
    // "/Volumes/BackupPlus/ExperimentData/20200117/10000_LAB_HV3002_laser375nmC40_T100_under25deg/LAB_HV3002_laser375nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200117/10000_LAB_HV3002_laser390nmC40_T100_under25deg/LAB_HV3002_laser390nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200117/20000_LAB_HV3002_laser405nmC40_T100_under25deg/LAB_HV3002_laser405nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200117/20000_LAB_HV3002_laser430nmC40_T100_under25deg/LAB_HV3002_laser430nmC40_T100_under25deg",

    // "/Volumes/BackupPlus/ExperimentData/20200117/SLS_HV3002_laser365nmC40_T100_under25deg/SLS_HV3002_laser365nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200117/SLS_HV3002_laser375nmC40_T100_under25deg/SLS_HV3002_laser375nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200117/SLS_HV3002_laser385nmC40_T100_under25deg/SLS_HV3002_laser385nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200117/SLS_HV3002_laser395nmC40_T100_under25deg/SLS_HV3002_laser395nmC40_T100_under25deg",
    "/Volumes/BackupPlus/ExperimentData/20200117/SLS_HV3002_laser405(355)nmC40_T100_under25deg/SLS_HV3002_laser405nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200117/SLS_HV3002_laser405nmC40_T100_under25deg/SLS_HV3002_laser405nmC40_T100_under25deg",
    // "/Volumes/BackupPlus/ExperimentData/20200117/SLS_HV3002_laser415nmC40_T100_under25deg/SLS_HV3002_laser415nmC40_T100_under25deg",
};
*/
/* 
TString FilePath_set[] = 
{
    "/Volumes/BackupPlus/ExperimentData/20200116/10970_empty_HV3002_laser375nmC50_T100/empty_HV3002_laser375nmC50_T100",
    "/Volumes/BackupPlus/ExperimentData/20200116/14500_empty_HV3002_laser405nmC40_T100/water_HV3002_laser405nmC40_T100",
    "/Volumes/BackupPlus/ExperimentData/20200116/20000_empty_HV3002_laser405nmC50_T100/empty_HV3002_laser405nmC50_T100",
    // 这个名字有问题 "/Volumes/BackupPlus/ExperimentData/20200116/LAB_HV3002_laser405(375)nmC40_T100_roomtemp/LAB_HV3002_laser405nmC40_T100_roomtemp"
    "/Volumes/BackupPlus/ExperimentData/20200116/water_HV3002_laser405nmC40_T100/water_HV3002_laser405nmC40_T100",

    "/Volumes/BackupPlus/ExperimentData/20200115/HV2809_T40_laser430nmC17.4_Atten_apert_noglass/HV2809_T40_laser430nmC17.4_Atten_apert_noglass",
    "/Volumes/BackupPlus/ExperimentData/20200115/HV2809_T40_laser430nmC17.4_noAtten_apert_noglass/HV2809_T40_laser430nmC17.4_noAtten_apert_noglass",
    "/Volumes/BackupPlus/ExperimentData/20200115/HV2809_T40_laser430nmC17.8_Atten_apert_noglass/HV2809_T40_laser430nmC17.8_Atten_apert_noglass",
    "/Volumes/BackupPlus/ExperimentData/20200115/HV2810_T40_laser430nmC17.4_Atten_apert_glass/HV2810_T40_laser430nmC17.4_Atten_apert_glass",

};
*/
//2020.5.27~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TString FilePath_set[] = {
    "/Volumes/Seagate_Expansion_Drive/ExperimentData/20200119/SLS_HV3005_laser265nmC69_T100mV_under25de/SLS_HV3005_laser265nmC69_T100mV_under25de",
    "/Volumes/Seagate_Expansion_Drive/ExperimentData/20200119/SLS_HV3005_laser265nmC70_T100mV_under25de/SLS_HV3005_laser265nmC70_T100mV_under25de",
    "/Volumes/Seagate_Expansion_Drive/ExperimentData/20200119/SLS_HV3005_laser270nmC55_T100mV_under25de/SLS_HV3005_laser270nmC55_T100mV_under25de",
    "/Volumes/Seagate_Expansion_Drive/ExperimentData/20200119/SLS_HV3005_laser270nmC60_T100mV_under25de/SLS_HV3005_laser270nmC60_T100mV_under25de",
    "/Volumes/Seagate_Expansion_Drive/ExperimentData/20200119/SLS_HV3005_laser280nmC50_T100mV_under25de/SLS_HV3005_laser280nmC50_T100mV_under25de",
    "/Volumes/Seagate_Expansion_Drive/ExperimentData/20200119/SLS_HV3005_laser290nmC45_T100mV_under25de/SLS_HV3005_laser290nmC45_T100mV_under25de",

    "/Volumes/Seagate_Expansion_Drive/ExperimentData/20200119/water_HV3005_laser300nmC95_T100mV_under25de/water_HV3005_laser300nmC95_T100mV_under25de",
    "/Volumes/Seagate_Expansion_Drive/ExperimentData/20200119/water\(maybeisnotwater\)_HV3005_laser300nmC80_T100mV_under25de/water_HV3005_laser300nmC80_T100mV_under25de"
    };

void MyMain_decaytime_PMT_bin_ShowAsingleFile_forcheck(TString FileName_fp)
{
    gStyle->SetOptStat(111111);
    gStyle->SetOptFit(1111);

    MyDataAnalysisClass mydataanalysisclass;
 
    TString FileName = FileName_fp;
    // TString FilePath = FileName(0,FileName.Sizeof()-11); //10 = 空字符+ _00000.bin
    // TString FileCondition = FilePath(FilePath.Last('/') + 1, FilePath.Sizeof() - FilePath.Last('/') - 2);
    // TString rootname = FileCondition + TString("justOneFile.root");

    // TFile myfile(rootname, "recreate");
    // TTree tree("tree", "tree");
    // tree.Branch("signal", &mydataanalysisclass.OneSignal_DT);
    // tree.Branch("OneDecayTime", &mydataanalysisclass.OneDecayTime);
    // tree.Branch("vLaserReferTimeInOneFile", &mydataanalysisclass.vLaserReferTimeInOneFile);

    // for nano
    // tree.Branch("NanoTime", &mydataanalysisclass.NanoTime);
    // tree.Branch("NanoPeak", &mydataanalysisclass.NanoPeak);
    // tree.Branch("Nano_baselien", &mydataanalysisclass.baseline_nano);

    double V1[20000];
    double V2[20000];

    // mydataanalysisclass.SetPMTSignalThreshold(0.1);
    if (MyReadBinary_2chan(FileName) == false)
    {
        cout << "fail to open file " << FileName << endl;
        exit(EXIT_FAILURE);
    };
    for (int i = 0; i < pointNum; i++)
    {
        V1[i] = Volts1[i];
        V2[i] = Volts2[i];
    }

    //ShowBinaryInfo(namei);
    mydataanalysisclass.GetFileInfo(2, pointNum, xInc);
    mydataanalysisclass.GetDataPointer(Time, V1, V2);
    
    // mydataanalysisclass.CheckReadData_DecayTime();
    // mydataanalysisclass.WorkOnAFile_DecayTime_SignalByFindingMax();
    // mydataanalysisclass.DrawResultsForCheck();

    // mydataanalysisclass.WorkOnAFile_DecayTime();
    // mydataanalysisclass.FitSignal();
    // mydataanalysisclass.WorkOnAFile_nano();
    if (mydataanalysisclass.FileWrongProcess == 1)
    {
        cerr << "skip this file process " << mydataanalysisclass.FileOrderi << endl;
        mydataanalysisclass.FileWrongProcess = 0;
    }

    mydataanalysisclass.ShowTheReadRawDataOfAFile();
    //mydataanalysisclass.CheckResultsofOneFile();

}
    

//检查下单个文件用的
void MyMain_decaytime_PMT_bin_singleFile_forcheck(TString FileName_fp)
{
    gStyle->SetOptStat(111111);
    gStyle->SetOptFit(1111);

    MyDataAnalysisClass mydataanalysisclass;
 
    TString FileName = FileName_fp;
    TString FilePath = FileName(0,FileName.Sizeof()-11); //10 = 空字符+ _00000.bin
    TString FileCondition = FilePath(FilePath.Last('/') + 1, FilePath.Sizeof() - FilePath.Last('/') - 2);
    TString rootname = FileCondition + TString("justOneFile.root");

    TFile myfile(rootname, "recreate");
    TTree tree("tree", "tree");
    tree.Branch("signal", &mydataanalysisclass.OneSignal_DT);
    tree.Branch("OneDecayTime", &mydataanalysisclass.OneDecayTime);
    tree.Branch("vLaserReferTimeInOneFile", &mydataanalysisclass.vLaserReferTimeInOneFile);

    // for nano
    // tree.Branch("NanoTime", &mydataanalysisclass.NanoTime);
    // tree.Branch("NanoPeak", &mydataanalysisclass.NanoPeak);
    // tree.Branch("Nano_baselien", &mydataanalysisclass.baseline_nano);

    double V1[20000];
    double V2[20000];
    clock_t time1, time2, time3, time4, time5;
    time1 = clock();

    // mydataanalysisclass.SetPMTSignalThreshold(0.1);
    if (MyReadBinary_2chan(FileName) == false)
    {
        cout << "fail to open file " << FileName << endl;
        exit(EXIT_FAILURE);
    };
    time4 = clock();
    for (int i = 0; i < pointNum; i++)
    {
        V1[i] = Volts1[i];
        V2[i] = Volts2[i];
    }

    //ShowBinaryInfo(namei);
    mydataanalysisclass.GetFileInfo(2, pointNum, xInc);
    mydataanalysisclass.GetDataPointer(Time, V1, V2);
    time2 = clock();
    
    // mydataanalysisclass.CheckReadData_DecayTime();
    mydataanalysisclass.WorkOnAFile_DecayTime_SignalByFindingMax();
    // mydataanalysisclass.DrawResultsForCheck();

    // mydataanalysisclass.WorkOnAFile_DecayTime();
    // mydataanalysisclass.FitSignal();
    // mydataanalysisclass.WorkOnAFile_nano();
    if (mydataanalysisclass.FileWrongProcess == 1)
    {
        cerr << "skip this file process " << mydataanalysisclass.FileOrderi << endl;
        mydataanalysisclass.FileWrongProcess = 0;
    }

    mydataanalysisclass.ShowTheReadRawDataOfAFile();

    time3 = clock();
    cout << time2 - time1 << "      " << time3 - time2 << endl;
    cout << "read binary = " << time4 - time1 << endl;
    
    tree.Fill();
    tree.Write();
    myfile.Close();

    //mydataanalysisclass.CheckResultsofOneFile();

}


void MyMain_decaytime_PMT_bin_singleSet(TString FilePath_fp, Int_t FileQuantity_fp = 200000, Int_t FileStart_fp = 0)
{
    TString FilePath = FilePath_fp;
    Int_t FileQuantity = FileQuantity_fp;
    Int_t FileStart = FileStart_fp; //为了挑选某个文件出来分析

    MyDataAnalysisClass mydataanalysisclass;
    gStyle->SetOptStat(111111);
    gStyle->SetOptFit(1111);

    TString FileCondition = FilePath(FilePath.Last('/') + 1, FilePath.Sizeof() - FilePath.Last('/') - 2);
    TString FileLast1 = FilePath(0,FilePath.Last('/'));
    TString FileLast2 = FileLast1(0,FileLast1.Last('/'));
    TString FileDirName = FileLast2(FileLast2.Last('/')+1, FileLast2.Sizeof() - FileLast2.Last('/')-2 );
    gSystem->mkdir(FileDirName);
    gSystem->cd(FileDirName);
    TString rootname = FileCondition + TString(".root");

    TFile myfile(rootname, "recreate");
    TTree tree("tree", "tree");
    tree.Branch("signal", &mydataanalysisclass.OneSignal_DT);
    tree.Branch("OneDecayTime", &mydataanalysisclass.OneDecayTime);
    tree.Branch("vLaserReferTimeInOneFile", &mydataanalysisclass.vLaserReferTimeInOneFile);

    double V1[20000];
    double V2[20000];

    // mydataanalysisclass.SetPMTSignalThreshold(0.1);
    for (int i = FileStart; i < FileStart + FileQuantity; i++)
    {
        mydataanalysisclass.FileOrderi = i;
        cerr << mydataanalysisclass.FileOrderi << "  " ;; 
        TString namei = FilePath + Form("_%05d.bin", i);

        if (MyReadBinary_2chan(namei) == false)
        {
            cout << "fail to open file " << namei << endl;
            break;
        };

        for (int i = 0; i < pointNum; i++)
        {
            V1[i] = Volts1[i];
            V2[i] = Volts2[i];
        }

        mydataanalysisclass.GetFileInfo(2, pointNum, xInc);
        mydataanalysisclass.GetDataPointer(Time, V1, V2);


        //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // ShowBinaryInfo(namei);
        // mydataanalysisclass.CheckFileInformation(false);
        // mydataanalysisclass.ShowTheReadRawDataOfAFile();
        //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        // mydataanalysisclass.CheckReadData_DecayTime();
        // mydataanalysisclass.WorkOnAFile_DecayTime();
        if(i == FileStart)
        {
            TString FigName = TString("Fig_") + FileCondition + Form("%d",i);
            mydataanalysisclass.ShowTheReadRawDataOfAFile(true, FigName);
        }
       
        if(mydataanalysisclass.WorkOnAFile_DecayTime_SignalByFindingMax() == true)
        {
            cout << "success :WorkOnAFile_DecayTime_SignalByFindingMax() " << endl;
        } /* 
        // mydataanalysisclass.DrawResultsForCheck();
    
        // mydataanalysisclass.WorkOnAFile_DecayTime();
        // mydataanalysisclass.FitSignal();
        // mydataanalysisclass.WorkOnAFile_nano();
        if (mydataanalysisclass.FileWrongProcess == 1)
        {
            cerr << "skip this file process " << mydataanalysisclass.FileOrderi << endl;
            mydataanalysisclass.FileWrongProcess = 0;
            continue;
        }
        */

        tree.Fill();
        
    }
    tree.Write();
    myfile.Close();
    //mydataanalysisclass.CheckResultsofOneFile();

}

//跑很多文件用的
void MyMain_decaytime_PMT_bin()
{
    //如果要写到里面也可以写到里面
    // TString FilePath_set[] = {};
    // Int_t FileQuantity_set[] = {}; 不需要了，直接让FileQuantity默认很大，然后超过了就跳出好了
    TString CodePath = gSystem->pwd();
    // gSystem->cd(CodePath);
    for(TString FilePath_temp : FilePath_set)
    {
        gSystem->cd(CodePath);
        MyMain_decaytime_PMT_bin_singleSet(FilePath_temp, 100000, 0);
    }

}




TString FilePath_set_nano[] = 
{
    "/Volumes/BackupPlus/ExperimentData/20200115/Nano_laser430nmC17.4/Nano_laser430nmC17.4",
    "/Volumes/BackupPlus/ExperimentData/20200115/Nano_laser430nmC18/Nano_laser430nmC18",

};

void MyMain_decaytime_nano_bin_singleSet(TString FilePath_fp, Int_t FileQuantity_fp = 200000, Int_t FileStart_fp = 0)
{
    TString FilePath = FilePath_fp;
    Int_t FileQuantity = FileQuantity_fp;
    Int_t FileStart = FileStart_fp; //为了挑选某个文件出来分析

    MyDataAnalysisClass mydataanalysisclass;
    gStyle->SetOptStat(111111);
    gStyle->SetOptFit(1111);

    // TString FileCondition = FilePath(FilePath.Last('/') + 1, FilePath.Sizeof() - FilePath.Last('/') - 2);
    // TString rootname = FileCondition + TString(".root");
    
    TString FileCondition = FilePath(FilePath.Last('/') + 1, FilePath.Sizeof() - FilePath.Last('/') - 2);
    TString FileLast1 = FilePath(0,FilePath.Last('/'));
    TString FileLast2 = FileLast1(0,FileLast1.Last('/'));
    TString FileDirName = FileLast2(FileLast2.Last('/')+1, FileLast2.Sizeof() - FileLast2.Last('/')-2 );
    gSystem->mkdir(FileDirName);
    gSystem->cd(FileDirName);
    // TString rootname =TString("./") + FileDirName + TString("./") + FileCondition + TString(".root");
    TString rootname = FileCondition + TString(".root");


    TFile myfile(rootname, "recreate");
    TTree tree("tree", "tree");
    // tree.Branch("signal", &mydataanalysisclass.OneSignal_DT);
    // tree.Branch("OneDecayTime", &mydataanalysisclass.OneDecayTime);
    // tree.Branch("vLaserReferTimeInOneFile", &mydataanalysisclass.vLaserReferTimeInOneFile);

    // for nano
    tree.Branch("NanoTime", &mydataanalysisclass.NanoTime);
    tree.Branch("NanoPeak", &mydataanalysisclass.NanoPeak);
    tree.Branch("Nano_baselien", &mydataanalysisclass.baseline_nano);

    double V1[20000];
    double V2[20000];
    clock_t time1, time2, time3, time4, time5;

    // mydataanalysisclass.SetPMTSignalThreshold(0.1);
    for (int i = FileStart; i < FileStart + FileQuantity; i++)
    {
        mydataanalysisclass.FileOrderi = i;
        cerr << mydataanalysisclass.FileOrderi << "  " ;; 
        // time1 = clock();
        TString namei = FilePath + Form("_%05d.bin", i);

        if (MyReadBinary_2chan(namei) == false)
        {
            cout << "fail to open file " << namei << endl;
            break;
        };

        for (int i = 0; i < pointNum; i++)
        {
            V1[i] = Volts1[i];
            V2[i] = Volts2[i];
        }

        mydataanalysisclass.GetFileInfo(2, pointNum, xInc);
        mydataanalysisclass.GetDataPointer(Time, V1, V2);


        //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // ShowBinaryInfo(namei);
        // mydataanalysisclass.CheckFileInformation(false);
        // mydataanalysisclass.ShowTheReadRawDataOfAFile();
        //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        // mydataanalysisclass.CheckReadData_DecayTime();
        // mydataanalysisclass.WorkOnAFile_DecayTime();

        if(i == FileStart)
        {
            TString FigName = TString("Fig_") + FileCondition + Form("%d",i);
            mydataanalysisclass.ShowTheReadRawDataOfAFile(true, FigName);
        }
        
        // if(mydataanalysisclass.WorkOnAFile_DecayTime_SignalByFindingMax() == true)
        // {
        //     cout << "success :WorkOnAFile_DecayTime_SignalByFindingMax() " << endl;
        // }
        // mydataanalysisclass.DrawResultsForCheck();
    
        // mydataanalysisclass.WorkOnAFile_DecayTime();
        // mydataanalysisclass.FitSignal();
        mydataanalysisclass.WorkOnAFile_nano();
        if (mydataanalysisclass.FileWrongProcess == 1)
        {
            cerr << "skip this file process " << mydataanalysisclass.FileOrderi << endl;
            mydataanalysisclass.FileWrongProcess = 0;
            continue;
        }

        tree.Fill();
        
    }
    tree.Write();
    myfile.Close();
    //mydataanalysisclass.CheckResultsofOneFile();

}

void MyMain_decaytime_nano_bin()
{
    //如果要写到里面也可以写到里面
    // TString FilePath_set[] = {};
    // Int_t FileQuantity_set[] = {}; 不需要了，直接让FileQuantity默认很大，然后超过了就跳出好了
    TString CodePath = gSystem->pwd();
    for(TString FilePath_temp : FilePath_set_nano)
    {
        gSystem->cd(CodePath);
        MyMain_decaytime_nano_bin_singleSet(FilePath_temp, 100000, 0);
    }

}

// void MyMain_decaytime_PMT_csv_singleSet(TString FilePath_fp, Int_t FileQuantity_fp = 200000, Int_t FileStart_fp = 0)
// {}



