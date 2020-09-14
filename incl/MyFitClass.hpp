/*
本代码是用来读取衰减时间数据并将其画成直方图

定义对象，联系到数据文件MyFitClass(TString FileName_fp);
设置直方图信息  Set_rawHistInfo然后ReadRawDataToRawHist
              或者 Set_Modstart + Set_modHistInfo + ReadData_CFD10_ToHist
 */
//再可以添加的功能：对不同数据点进行保存

#ifndef MyFitClass_hpp
#define MyFitClass_hpp

#include <iostream>
#include <vector>
#include "TString.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1D.h"
#include "TTree.h"
#include "TStyle.h"
#include "TCanvas.h"

using namespace std;

struct Signal
{
    Double_t baseline;
    Double_t baselinesigma; //for a criteria of the baseline and signal
    Double_t amplitude;     //peak - baseline
    Double_t area;          //10%~10%
    Double_t starttime_CFT5;
    Double_t starttime_CFT; // 10%
    Double_t starttime_CFT15;
    Double_t starttime_CFT20;
    Double_t starttime_CFT30;
    Double_t starttime_CFT50;
    Double_t starttime_CFT90;
    Double_t starttime_threshold;
    Double_t peaktime;
    Double_t width;    // 10%~10%
    Double_t FWHM;     // 50%~50%
    Double_t risetime; // 10%~90%
    Double_t falltime; // 90%~10%
    Double_t timebssigma3_left;
    Double_t timebssigma3_right;
    Double_t area_3sigma;

    // bool theMaxSignal;
    Int_t startposition;
    Int_t endposition;
};

class MyFitClass
{
private:
    /* data */
public:
    MyFitClass();
    MyFitClass(TString FileName_fp);
    ~MyFitClass();

    //文件和直方图的信息
    TH1D * TheTH1D_raw_CFD10;//原始数据，直方图范围要画的宽
    TH1D * TheTH1D_mod_CFD10;//根据数据的信息设置Modstart点后对数据进行平移
    TString FileName;
    TString FigTitle;
    Double_t Data_lower;
    Double_t Data_upper;
    Double_t Data_binWidth;
    Int_t Data_binNum;

    void SetInitInfo(TString FileName_fp);
   
    bool isSet_rawHistInfo = kFALSE;
    bool isSet_modHistInfo = kFALSE;
    void Set_rawHistInfo(Double_t Data_lower_fp, Double_t Data_upper_fp, Double_t Data_binWidth_fp);
    void Set_modHistInfo(Double_t Data_lower_fp, Double_t Data_upper_fp, Double_t Data_binWidth_fp);

    void ReadRawDataToRawHist(TString FileName_fp);
    void ReadRawDataToRawHist();
    void ReadData_CFD10_ToHist(TString FileName_fp);
    void ReadData_CFD10_ToHist();

    Double_t Modstart = 0.0e-9; //LAB 0 注意单位是秒，非0时要注意乘以e-9
    void Set_Modstart(Double_t Modstart_fp);
    bool isSet_Modstart = kFALSE;


};

#if defined(__ROOTCLING__)
#pragma link C++ class Signal + ;
#pragma link C++ class vector < Signal> + ;
#pragma link C++ class MyFitClass + ;
#endif

MyFitClass::MyFitClass()
{
}


MyFitClass::MyFitClass(TString FileName_fp)
{
    FileName = FileName_fp;
    FigTitle = FileName(FileName.Last('/') + 1, FileName.Last('.') - FileName.Last('/') - 1);
}

MyFitClass::~MyFitClass()
{
    // if(isSet_modHistInfo == kTRUE)
    // {
    //     delete TheTH1D_mod_CFD10;
    // }
    // if(isSet_rawHistInfo == kTRUE)
    // {
    //     delete TheTH1D_raw_CFD10;
    // }
}

void MyFitClass::SetInitInfo(TString FileName_fp)
{
    FileName = FileName_fp;
    FigTitle = FileName(FileName.Last('/') + 1, FileName.Last('.') - FileName.Last('/') - 1);
}

void MyFitClass::Set_Modstart(Double_t Modstart_fp)
{
    Modstart = Modstart_fp; 
    isSet_Modstart = kTRUE;
};

void MyFitClass::Set_rawHistInfo(Double_t Data_lower_fp, Double_t Data_upper_fp, Double_t Data_binWidth_fp)
{
    Double_t Data_lower_temp = Data_lower_fp;
    Double_t Data_upper_temp = Data_upper_fp;
    Double_t Data_binWidth_temp = Data_binWidth_fp;
    Int_t Data_binNum_temp = Int_t((Data_upper_temp - Data_lower_temp) / Data_binWidth_temp + 0.5);
    // TheTH1D_raw_CFD10 = new TH1D("TheTH1D_raw_CFD10", FigTitle + TString("raw_CFD10"), Data_binNum_temp, Data_lower_temp, Data_upper_temp);
    TheTH1D_raw_CFD10 = new TH1D(FigTitle+TString("_raw_TH1D"), FigTitle + TString("raw_CFD10"), Data_binNum_temp, Data_lower_temp, Data_upper_temp);
    isSet_rawHistInfo = kTRUE;
}


void MyFitClass::Set_modHistInfo(Double_t Data_lower_fp, Double_t Data_upper_fp, Double_t Data_binWidth_fp)
{
    Data_lower = Data_lower_fp;
    Data_upper = Data_upper_fp;
    Data_binWidth = Data_binWidth_fp;
    Data_binNum = Int_t((Data_upper - Data_lower) / Data_binWidth + 0.5);
    // TheTH1D_mod_CFD10 = new TH1D("TheTH1D_mod_CFD10", FigTitle + TString("mod_CFD10"), Data_binNum, Data_lower, Data_upper);
    TheTH1D_mod_CFD10 = new TH1D(FigTitle+TString("_mod_TH1D"), FigTitle + TString("mod_CFD10"), Data_binNum, Data_lower, Data_upper);
    isSet_modHistInfo = kTRUE;
}


void MyFitClass::ReadRawDataToRawHist(TString FileName_fp)
{
    if(isSet_rawHistInfo == kFALSE)
    {
        cout << "Haven't Set_rawHistInfo!" << endl;
        cout << " please input the hist lower , upper and binWidth ; or quit" << endl;

        Double_t Data_lower_temp;
        Double_t Data_upper_temp;
        Double_t Data_binWidth_temp;
        cin >> Data_lower_temp >> Data_upper_temp >> Data_binWidth_temp;
        cout << " finish input " << endl;
        Set_rawHistInfo(Data_lower_temp,Data_lower_temp,Data_binWidth_temp);
    }
    // gStyle->SetOptStat("e");
    // gStyle->SetOptFit(111);
    // gStyle->SetOptStat(111111);
    // gStyle->SetOptFit(1111);
    TString treeName = "tree";
    TFile *getFile = TFile::Open(FileName_fp);
    if(getFile->IsOpen())
    {
        cout << "open the data file " << FileName_fp << " successfully! " << endl;
    }
    else
    {
        cout << "cannot open the file " << FileName_fp << endl;
        exit(EXIT_FAILURE);
    }
    TTree *readTree = (TTree *)getFile->Get(treeName);

    Signal *OneSignal_DT = 0;
    double OneDecayTime;
    vector<Double_t> *vLaserReferTimeInOneFile = 0;

    readTree->SetBranchAddress("OneDecayTime", &OneDecayTime);
    readTree->SetBranchAddress("signal", &OneSignal_DT);
    readTree->SetBranchAddress("vLaserReferTimeInOneFile", &vLaserReferTimeInOneFile);

    for (unsigned i = 0; i < readTree->GetEntries(); i++)
    {
        readTree->GetEntry(i);
        TheTH1D_raw_CFD10->Fill(OneDecayTime * 1e9);
        if(i < 100)
        {
            cout << OneDecayTime * 1e9 << endl;
        }
    }
    getFile->Close();
}

void MyFitClass::ReadRawDataToRawHist()
{
    ReadRawDataToRawHist(FileName);
}



void MyFitClass::ReadData_CFD10_ToHist(TString FileName_fp)
{
    if(isSet_modHistInfo == kFALSE)
    {
        cout << "Haven't Set_modHistInfo!" << endl;
        cout << " please input the hist lower , upper and binWidth ; or quit" << endl;

        Double_t Data_lower_temp;
        Double_t Data_upper_temp;
        Double_t Data_binWidth_temp;
        cin >> Data_lower_temp >> Data_upper_temp >> Data_binWidth_temp;
        cout << " finish input " << endl;
        Set_modHistInfo(Data_lower_temp,Data_lower_temp,Data_binWidth_temp);
    }

    if(isSet_Modstart == kFALSE)
    {
        cout << " please use Set_Modstart() to set the Modstart value " << endl;
        exit(EXIT_FAILURE);
    }
    // gStyle->SetOptStat("e");
    // gStyle->SetOptFit(111);
    // gStyle->SetOptStat(111111);
    // gStyle->SetOptFit(1111);
    TString treeName = "tree";
    TFile *getFile = TFile::Open(FileName_fp);
    if(getFile->IsOpen())
    {
        cout << "open the data file " << FileName_fp << " successfully! " << endl;
    }
    else
    {
        cout << "cannot open the file " << FileName_fp << endl;
        exit(EXIT_FAILURE);
    }

    TTree *readTree = (TTree *)getFile->Get(treeName);
    Signal *OneSignal_DT = 0;
    double OneDecayTime;
    vector<Double_t> *vLaserReferTimeInOneFile = 0;

    readTree->SetBranchAddress("OneDecayTime", &OneDecayTime);
    readTree->SetBranchAddress("signal", &OneSignal_DT);
    readTree->SetBranchAddress("vLaserReferTimeInOneFile", &vLaserReferTimeInOneFile);

    for (unsigned i = 0; i < readTree->GetEntries(); i++)
    {
        readTree->GetEntry(i);
        TheTH1D_mod_CFD10->Fill( (OneDecayTime > Modstart) ? ((OneDecayTime-Modstart) * 1e9) : ((OneDecayTime-Modstart) * 1e9 + 12.839) );
    }
    cout << "finish filling data " << endl;
    getFile->Close();
}

void MyFitClass::ReadData_CFD10_ToHist()
{
    ReadData_CFD10_ToHist(FileName);
}



#endif
