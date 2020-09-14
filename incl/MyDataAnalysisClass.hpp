#ifndef MyDataAnalysisClass_hpp
#define MyDataAnalysisClass_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "TFile.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TString.h"
#include "TStyle.h"
#include "TLine.h"

using namespace std;
/* 
class PMTGainClass
{
public:
    double area;
    double baseline;
    double amplitude;
    double width;

    double baseline;
    double baselinesigma;  //for a criteria of the baseline and signal
    double amplitude;     //peak - baseline
    double area;          //10%~10%
    double starttime_CFT5;
    double starttime_CFT; // 10%
    double starttime_CFT15;
    double starttime_CFT20;
    double starttime_CFT30;
    double starttime_CFT50;
    double starttime_CFT90;
    double starttime_threshold;
    double peaktime;
    double width;    // 10%~10%
    double FWHM;     // 50%~50%
    double risetime; // 10%~90%
    double falltime; // 90%~10%
    double timebssigma3_left;
    double timebssigma3_right;
    double area_3sigma;
};*/
//20200703 将Signal的 double 改成 Double_t
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

#if defined(__ROOTCLING__)
#pragma link C++ class Signal + ;
#pragma link C++ class vector <Signal> + ;
#pragma link C++ class MyDataAnalysisClass + ;
#endif


class MyDataAnalysisClass
{
private:
    // the information of raw data file
    Int_t FileQuantity;            //!
    Int_t FileMaxColumn;           //! // t,1,2,3,4
    Int_t FileMaxRow;              //!//the raw number is from 0 to max-1
    Double_t FileTimeUnitAverage;  //!
    Double_t FileTimeOriginal = 0; //!
    Double_t FileTimeUnit1;        //!
    Double_t FileTimeUnit2;        //!

    Double_t *rawdata_channel_t = NULL; //!
    Double_t *rawdata_channel_1 = NULL; //!
    Double_t *rawdata_channel_2 = NULL; //!
    Double_t *rawdata_channel_3 = NULL; //!
    Double_t *rawdata_channel_4 = NULL; //!
    int newrawdatachannelNum = -1;      //!
                                        //构造函数如果是用new为数据分配内存时，将赋值为newrawdatachannelNum = FileMaxColumn
                                        //析构函数则根据newrawdatachaannelNum来释放内存
                                        //determine the segment allocation and deletes

public:
    MyDataAnalysisClass(TString FileName_fp, bool check_fp); //通过读取这个文件自动获得文件信息，并完成赋值
    MyDataAnalysisClass();                                   //只是创建一个默认对象
    ~MyDataAnalysisClass();                                  //

    // ~~~~~~~~~~~~~~~~~~1.读取信息类函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void GetFileInformation(TString FileName_fp); //直接读取一个文件获得文件的信息
    void CheckFileInformation(bool check_fp);     //输出文件信息

    //*******************************************************************************************
    //binany file assign
    void GetFileInfo(int FileMaxRow_fp, int FileMaxColumn_fp, double FileTimeUnitAverage_fp);
    void GetFileInfo(int FileMaxRow_fp, int FileMaxColumn_fp, double FileTimeOriginal_fp, double FileTimeUnitAverage_fp);

    void GetDataPointer(double *Time_fp, double *Volts1_fp, double *Volts2_fp);
    void GetDataPointer(double *Time_fp, double *Volts1_fp);

    TString ReadingFileName = "NameIsEmpty";
    bool ReadOneFile(TString FileName_fp, bool AutoStop_fp); //输入文件名，读取文件中的数据（csv文件）
    void ReadOneFile(TString FileName_fp);                   //输入文件名，读取文件中的数据（csv文件）

    //~~~~~~~~~~~~~~~~~~~检查输入信息类函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void ShowReadFile(); 
    void ShowTheReadRawDataOfAFile(bool SaveOrNot_fp = false, TString FigHeader_fp = "Fig");//看读进来了什么数据
    //*******************************************************************************************

    int FileOrderi = 0;           //for cerr output check
    int FileWrongProcess = 0; // to skip the wrong process
    void CheckResultsofOneFile();
    void DrawResultsForCheck();

    //~~~~~~~~~~~~~~~~~~2.处理数据类函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //*******************************************************************************************
    //函数参数中要输出、赋值的（引用）放在前面，需要传入的放在后面
    void DrawHist_BybinWidth_GausFit(Double_t &mean_fp, Double_t &sigma_fp, const Double_t *data_fp, const Int_t dataquantity_fp, const Double_t binWidth_fp);
    void DrawHist_BybinWidth_GausFit(Double_t &mean_fp, Double_t &sigma_fp, const Double_t *data_fp, const Int_t dataquantity_fp, const Double_t binWidth_fp, bool check_fp, TString savename_fp);

    //用来大致确定信号范围的
    void FindAverageBaseline(Double_t &mean_fp, Double_t &sigma_fp, const Double_t *data_fp, const Int_t dataquantity_fp, TString savename_fp);
    void FindAverageBaseline(Double_t &mean_fp, Double_t &sigma_fp, const Double_t *data_fp, const Int_t dataquantity_fp);

    //给定信号的范围，先确定基线，然后数最高峰值，然后计算面积、时间等
    //计算出来的信息在signal的struct后面push_back
    void GetSignalInfo(vector<Signal> &vSignal_fp, const Int_t start_fp, const Int_t end_fp, const Double_t baseline_fp, const Double_t baselinesigma_fp);
    void GetSignalInfo(Signal &vSignal_fp, const Int_t start_fp, const Int_t end_fp, const Double_t baseline_fp, const Double_t baselinesigma_fp);

    void FitSignal(Signal &vSignal_fp, const Int_t start_fp, const Int_t end_fp, const Double_t baseline_fp);
    void FitSignal();
    //*******************************************************************
    //分析时需要用到的信息：基线，判断的依据，PMT信号的位置，laser信号的时间
    //laer
    vector<double> vLaserReferTimeInOneFile;
    void GetLaserReferTimeInOneFile_PMT(); //固定的一个点可以将来考虑用平滑曲线拟合来提升
    void GetLaserReferTimeInOneFile_nano(); 

    //PMT
    // //for SPE 增益刻度只是比衰减时间多一个分区
    // //measure informations
    // vector<Int_t> UnitFlag; //单光子刻度时候分区间
    // void SetUnitFlag(const Double_t TimeSignalStart, const Double_t SignalPeriod_fp, const Int_t SignalQuantity);
    //LED单光子刻度～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
    vector<Int_t> vUnitFlagStart; //单光子刻度区间的起始
    vector<Int_t> vUnitFlagEnd;
    vector<Int_t> vUnitSignalStart; //LED 的信号区间
    vector<Int_t> vUnitSignalEnd;
    void SetvUnitFlag(const Double_t FlagTimestart, const Double_t LEDPeriod, const Double_t SignalTimestart, const Double_t SignalWidth, const Int_t SignalQuantity);
    void SetvUnitFlag(const Double_t FlagTimestart, const Double_t LEDPeriod, const Int_t SignalQuantity);
    double *Sum_T; //用来画所有的T和V
    double *Sum_V;
    int *tflag = 0;
    double GetAreaSum(int nstart_fp, int nend_fp, double baseline_fp); //计算信号(rawdata_channel1)区间的面积
    double GetAreaSum(int nstart_fp, int nend_fp, double tstart_fp, double tend_fp, double baseline_fp);
    int iFindThePeakPosition(int nstart_fp, int nend_fp);
    double dFindThePeakAmplitude(int nstart_fp, int need_fp);
    // void DrawAllFileToSetFlag(TString FileHeader_fp, int FileNum_fp = 0, TString FileNameSuffix_fp = ".csv");
    void DrawAllFileToSetFlag(TString FileHeader_fp, int FileNum_fp = 0, TString FileNameSuffix_fp = ".csv", int Quantity_fp = -1);

    void AccumulateTimeAndVolt(int Filei_fp);
    void DrawAllFileTimeAndVolt();

    // void DrawHist_BybinWidth_GausFit
    // void GetSignalInfo
    void WorkOnAFile_PMTGain_byAmpl();

    //输出
    vector<double> vUnitBaseline;
    vector<double> vUnitBaselineSigma;
    vector<int> vUnitPeakPosi;
    vector<double> vUnitPeak;
    vector<double> vUnitArea_2ns;
    vector<double> vUnitAmplitude;
    vector<Signal> vEverySignalsInAFile_Gain;
    //********************************************************************************

    vector<double> vUnitThresholdInOneFile;
    vector<double> vUnitThreshold2InOneFile;
    vector<int> vSignalPosiInOneFile_start; //!
    vector<int> vSignalPosiInOneFile_end;   //!

    vector<double> vBaselineInOneFile; //SPE每个单元的基线中心值
    vector<double> vBaselineSigmaInOneFile;
    vector<double> vSignalsBaseline; //信号的基线
    vector<double> vSignalsBaselineSigma;
    vector<double> vSignalsDeltaBaseline;
    vector<double> vSignalsDeltaBaselineSigma;

    //output data
    vector<Signal> vSignalsInSingleFile;
    vector<double> vSignalsUnitSumInSingleFile;

    void CheckOverPulse(vector<int> vCheckSignal_start_fp, vector<int> vCheckSignal_end_fp, int vChecki_fp, vector<int> &vOverPulse_fp, vector<double> &vOverAmpl_fp, double baseline_fp);
    //    void WorkOnAFile_SPE();
    void FindTheAmplitude_min(const double *data_fp, int start_fp, int end_fp, double &A_fp);

    //    因为有的时候并没有信号点，所以要确定出一个高度
    // Double_t SignalThresholdByMe = -0.50;
    // void SetSignalThresholdByMe(Double_t);

    //找最大和找所有的不同之处在于确定信号的方法不一样，确定了信号后就是一样的了。

    //1:find the max signal in a unit
    //analysis function
    void FindtheMaxSignalInUnit(const Double_t *pdata_fp, const int start_fp, const int end_fp);

    //decay time analysis
    const double PMTThreshold = -0.10; //这个阈值与示波器取数的阈值不相同也没有关系，但是一般还是设做相同
    double PMTSignalThreshold = -0.1;
    void SetPMTSignalThreshold(double PMTSignalThreshold_fp);
    //    void GetPMTTime()

    void WorkOnAFile_DecayTime();
    bool WorkOnAFile_DecayTime_SignalByFindingMax();
    Signal OneSignal_DT;
    double OneDecayTime;
    void CheckReadData_DecayTime();

    void GetNanoTimeandPeak();
    double NanoTime;
    int NanoThrePosi;
    double NanoPeak;
    int NanoPeakPosi;
    double baseline_nano;

    void WorkOnAFile_nano();
    // void GetPeak_Nano();
    // void GetThreTime_Nano();

    void WorkOnAFile_laserSPEGainCali();
    void FindThePeakPosition(const double *data_fp, int start_fp, int end_fp, int &peakposi_fp);

    void WorkOnAFile_PMTGain();

    //~~~~~~~~~~~~~~~~~~检查输入和计算结果的函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //******************************************************************

    //~~~~~~~~~~~~~~~~~~3.输出结果和检查输出结果~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};



void MyDataAnalysisClass::SetPMTSignalThreshold(double PMTSignalThreshold_fp)
{
    PMTSignalThreshold = PMTSignalThreshold_fp;
}
//***************************************************************
/* 
void MyDataAnalysisClass::SetSignalThresholdByMe(Double_t base_fp)
{
    SignalThresholdByMe = base_fp;
}


//ok
//input the pulse information of a data file, assign the vector of pulse positions
void MyDataAnalysisClass::SetUnitFlag(const Double_t TimeSignalStart_fp, const Double_t SignalPeriod_fp, const Int_t SignalQuantity_fp)
{
    cout << " make sure the rawdata_time have already been assigned " << endl;
    UnitFlag.clear();
    Int_t NumStart = 0;
    Int_t RowsPerPeriod = (int)(SignalPeriod_fp / FileTimeUnitAverage);
    for (int i = 0; i < FileMaxRow; i++)
    {
        if (rawdata_channel_t[i] > TimeSignalStart_fp)
        {
            NumStart = i;
            break;
        }
    }
    cout << " flag start time = " << NumStart << " " << rawdata_channel_t[NumStart] << endl;
    for (int i = 0; i < SignalQuantity_fp + 1; i++)
    {
        UnitFlag.push_back(NumStart + i * RowsPerPeriod);
    }
}

//在单元里面找到极值，然后得到基线，然后在得到信号的各种信息
void MyDataAnalysisClass::FindtheMaxSignalInUnit(const Double_t *pdata_fp, const int start_fp, const int end_fp)
{
    Double_t max_temp = *(pdata_fp + start_fp);
    for (int i = start_fp; i < end_fp; i++)
    {
        if (*(pdata_fp + i) < max_temp)
        {
            max_temp = *(pdata_fp + i);
        }
    }
    //基线

    //得到信号信息
    Signal signal_temp;
    signal_temp.baseline = 0;
    signal_temp.amplitude = 0;
    signal_temp.area = 0;
    signal_temp.starttime_CFT = 0;
    signal_temp.starttime_threshold = 0;
    signal_temp.width = 0;

    vSignalsInSingleFile.push_back(signal_temp);
}

//传入信号的vector和有嫌疑的位置
//输出过脉冲的位置

void MyDataAnalysisClass::CheckOverPulse(vector<int> vCheckSignal_start_fp, vector<int> vCheckSignal_end_fp, int vChecki_fp, vector<int> &vOverPulse_fp, vector<double> &vOverAmpl_fp, double baseline_fp)
{
    const double *pdata_fp = this->rawdata_channel_1;

    int minp = vCheckSignal_start_fp.at(vChecki_fp);
    double min = pdata_fp[minp];
    int maxp = vCheckSignal_end_fp.at(vChecki_fp);
    double max = pdata_fp[maxp];

    for (int i = vCheckSignal_start_fp.at(vChecki_fp); i < vCheckSignal_end_fp.at(vChecki_fp); i++)
    {
        if (pdata_fp[i] < min)
        {
            min = pdata_fp[i];
            minp = i;
        }
    }

    double realSignalAmpl = pdata_fp[minp];
    for (int i = vCheckSignal_start_fp.at(vChecki_fp); i > vCheckSignal_start_fp.at(vChecki_fp) - int(6e-9 / FileTimeUnitAverage + 0.5); i--)
    {
        if (pdata_fp[i] < realSignalAmpl)
        {
            realSignalAmpl = pdata_fp[i];
        }
    }

    for (int i = vCheckSignal_end_fp.at(vChecki_fp); i < vCheckSignal_end_fp.at(vChecki_fp) + int(1e-9 / FileTimeUnitAverage); i++)
    {
        if (pdata_fp[i] > max)
        {
            max = pdata_fp[i];
            maxp = i;
        }
    }

    if (max < baseline_fp)
    {
        cout << "the overpulse max < baseline, there is no positive amplitude " << endl;
    }
    else
    {
        //check
        //        cout << "max = " << max << "       max position = " << maxp << endl;
        //        cout << "min = " << min << "       min position = " << minp << endl;
        //        cout <<"realSignalAmpl =  " << realSignalAmpl << endl;
        //        cout << "baseline = " << baseline_fp << endl;
        //        cout << "int((0.6e-9)/FileTimeUnitAverage) =  " << int((0.6e-9)/FileTimeUnitAverage) << endl;
        //
        //        cout << "abs( (max-min-2*baseline_fp)/(max-min) ) = " << abs( (max+min-2*baseline_fp)/(max-min) ) << endl;
        //        cout << "maxp-minp< int(0.6e-9)/FileTimeUnitAverage = " <<  (maxp-minp < int((0.6e-9)/FileTimeUnitAverage) ) << endl;
        //        cout << " (realSignalAmpl-baseline_fp) / (min-baseline_fp)  = " << ( (realSignalAmpl-baseline_fp) / (min-baseline_fp) ) << endl;
        //
        //        cout << " (realSignalAmpl-baseline_fp) / (min-baseline_fp) > 6    =   " << ( (realSignalAmpl-baseline_fp) / (min-baseline_fp) > 6) << endl;

        //正向幅度起码要为负向的一半
        if (abs((max + min - 2 * baseline_fp) / (max - min)) < 0.66 && (maxp - minp < int(0.6e-9 / FileTimeUnitAverage + 0.5)) && ((realSignalAmpl - baseline_fp) / (min - baseline_fp) > 6))
        {
            cout << " this is a overpluse " << endl;
            vOverPulse_fp.push_back(vChecki_fp);
            vOverAmpl_fp.push_back(min - baseline_fp);
        }
        else
        {
            cout << "this is NOT a down up overshoot " << endl;
        }
    }
    cout << endl
         << endl
         << endl;
}

void MyDataAnalysisClass::FindTheAmplitude_min(const double *data_fp, int start_fp, int end_fp, double &A_fp)
{
    double min = data_fp[start_fp];
    for (int i = start_fp; i < end_fp; i++)
    {
        if (min > data_fp[i])
        {
            min = data_fp[i];
        }
    }
    A_fp = min;
}
 */
void MyDataAnalysisClass::WorkOnAFile_DecayTime()
{
    cout << "deal decay time " << endl;
    const Double_t *data_temp = this->rawdata_channel_1;
    const Double_t *time_temp = this->rawdata_channel_t;
    const Double_t *laser_temp = this->rawdata_channel_2;

    const int move_1ns = int(1e-9 / FileTimeUnitAverage + 0.5);

    //get the baseline
    vSignalPosiInOneFile_start.clear();
    vSignalPosiInOneFile_end.clear();

    Double_t meanInUnit = 0;
    Double_t sigmaInUnit = 0;

    for (int ii = 0; ii < FileMaxRow; ii++)
    {
        if (*(data_temp + ii) < PMTSignalThreshold)
        {
            vSignalPosiInOneFile_start.push_back(ii);
            while (*(data_temp + ii) < PMTSignalThreshold)
            {
                ii++;
            }
            vSignalPosiInOneFile_end.push_back(ii);
            break;
        }
    }

    DrawHist_BybinWidth_GausFit(meanInUnit, sigmaInUnit, data_temp + vSignalPosiInOneFile_start.at(0) - 5 * move_1ns, 4 * move_1ns, 0.002);
    // DrawHist_BybinWidth_GausFit(meanInUnit, sigmaInUnit, data_temp + vSignalPosiInOneFile_start.at(0) - 5 * move_1ns, 4 * move_1ns, 0.002,kTRUE,Form("%d.pdf",FileOrderi));
    //DrawHist_BybinWidth_GausFit(meanInUnit, sigmaInUnit, data_temp+vSignalPosiInOneFile_start.at(0)-5*move_1ns, 4 * move_1ns, 0.005,kTRUE,"657.pdf");

    Double_t baseline_DT = meanInUnit;
    Double_t baselinesigma_DT = sigmaInUnit;
    // cout << "vSignalPosiInOneFile_start.size() = " << vSignalPosiInOneFile_start.size() << endl;
    if (vSignalPosiInOneFile_start.size() != vSignalPosiInOneFile_end.size())
    {
        cerr << "vSignalPosiInOneFile_start.size() != vSignalPosiInOneFile_end.size()" << endl;
        exit(EXIT_FAILURE);
    }

    int deletei = 0;

    if (vSignalPosiInOneFile_start.size() > 1)
    {
        cout << "vSignalPosiInOneFile_start.size() > 1, something wrong " << endl;
        for (unsigned i = 0; i < vSignalPosiInOneFile_start.size(); i++)
        {
            cerr << "vSignal i = " << vSignalPosiInOneFile_start.at(i) << endl;
        }
        // exit(EXIT_FAILURE);
    }
    GetSignalInfo(OneSignal_DT, vSignalPosiInOneFile_start.at(0), vSignalPosiInOneFile_end.at(0), baseline_DT, baselinesigma_DT);
    GetLaserReferTimeInOneFile_PMT();

    OneDecayTime = OneSignal_DT.starttime_CFT - vLaserReferTimeInOneFile.at(0);
}

bool MyDataAnalysisClass::WorkOnAFile_DecayTime_SignalByFindingMax()
{
    cout << "deal decay time " << endl;
    const Double_t *data_temp = this->rawdata_channel_1;
    const Double_t *time_temp = this->rawdata_channel_t;
    const Double_t *laser_temp = this->rawdata_channel_2;

    const int move_1ns = int(1e-9 / FileTimeUnitAverage + 0.5);

    //get the baseline
    vSignalPosiInOneFile_start.clear();
    vSignalPosiInOneFile_end.clear();

    Double_t meanInUnit = 0;
    Double_t sigmaInUnit = 0;

    Int_t PeakPosition_temp = 0;
    Double_t PeakAmplitude_temp = *(data_temp);

    for(int ii = 0; ii < FileMaxRow; ii++)
    {
        if(*(data_temp+ii)< PeakAmplitude_temp)
        {
            PeakPosition_temp = ii;
            PeakAmplitude_temp = *(data_temp+ii);
        }
        
    }
    cout << "PeakAmplitude_temp = " <<  PeakAmplitude_temp << endl;
    cout << "*(time_temp+PeakPosition_temp) = " << *(time_temp+PeakPosition_temp) << endl;

    //因为基线是取信号前4ns
    if(PeakPosition_temp < 4*move_1ns)
    {
        cerr << " in function WorkOnAFile_DecayTime_SignalByFindingMax() !!!PeakPosition_temp < 4*move_1ns " << endl;
        cerr << "the ReadingFileName is " << ReadingFileName << endl;
        // exit(EXIT_FAILURE);
        return false;
    }

    vSignalPosiInOneFile_start.push_back(PeakPosition_temp-2*move_1ns);
    vSignalPosiInOneFile_end.push_back(PeakPosition_temp+2*move_1ns);

    for (int ii = 0; ii < FileMaxRow; ii++)
    {
        if (*(data_temp + ii) < PMTSignalThreshold)
        {
            vSignalPosiInOneFile_start.push_back(ii);
            while (*(data_temp + ii) < PMTSignalThreshold)
            {
                ii++;
            }
            vSignalPosiInOneFile_end.push_back(ii);
            break;
        }
    }

    DrawHist_BybinWidth_GausFit(meanInUnit, sigmaInUnit, data_temp + vSignalPosiInOneFile_start.at(0) - 5 * move_1ns, 4 * move_1ns, 0.002);
    // DrawHist_BybinWidth_GausFit(meanInUnit, sigmaInUnit, data_temp + vSignalPosiInOneFile_start.at(0) - 5 * move_1ns, 4 * move_1ns, 0.002,kTRUE,Form("%d.pdf",FileOrderi));
    //DrawHist_BybinWidth_GausFit(meanInUnit, sigmaInUnit, data_temp+vSignalPosiInOneFile_start.at(0)-5*move_1ns, 4 * move_1ns, 0.005,kTRUE,"657.pdf");

    Double_t baseline_DT = meanInUnit;
    Double_t baselinesigma_DT = sigmaInUnit;
    // cout << "vSignalPosiInOneFile_start.size() = " << vSignalPosiInOneFile_start.size() << endl;
    if (vSignalPosiInOneFile_start.size() != vSignalPosiInOneFile_end.size())
    {
        cerr << "vSignalPosiInOneFile_start.size() != vSignalPosiInOneFile_end.size()" << endl;
        // exit(EXIT_FAILURE);
        return false;
    }

    int deletei = 0;
    GetSignalInfo(OneSignal_DT, vSignalPosiInOneFile_start.at(0), vSignalPosiInOneFile_end.at(0), baseline_DT, baselinesigma_DT);
    GetLaserReferTimeInOneFile_PMT();

    OneDecayTime = OneSignal_DT.starttime_CFT - vLaserReferTimeInOneFile.at(0);
    return true;
}

void MyDataAnalysisClass::WorkOnAFile_nano()
{
    const double nanothreshold = 0.1;
    const Double_t *data_temp = this->rawdata_channel_2;
    const Double_t *time_temp = this->rawdata_channel_t;
    const Double_t *laser_temp = this->rawdata_channel_1;
    const int move_1ns = int(1e-9 / FileTimeUnitAverage + 0.5);

    int nanothreposi_temp = 0;

    vSignalPosiInOneFile_start.clear();
    vSignalPosiInOneFile_end.clear();

    Double_t meanInUnit = 0;
    Double_t sigmaInUnit = 0;

    for (int i = 0; i < FileMaxRow; i++)
    {
        if (data_temp[i] > nanothreshold)
        {
            nanothreposi_temp = i;
            break;
        }
    }
    cout << "nanothreposi_temp = " << nanothreposi_temp << endl;
    cout << "move_1ns = " << move_1ns << endl;
    if (nanothreposi_temp - 9 * move_1ns < 0)
    {
        cerr << "FileOrder i =  " << FileOrderi << endl;
        cerr << "NanoThrePosi - 9 * move_1ns < 0, the array address is wrong" << endl;
        FileWrongProcess = 1;
        exit(EXIT_FAILURE);
        return;
    }
    DrawHist_BybinWidth_GausFit(meanInUnit, sigmaInUnit, data_temp + nanothreposi_temp - 9 * move_1ns, 8 * move_1ns, 0.005, true, "10.pdf");

    baseline_nano = meanInUnit;

    double peak_temp = *(data_temp + nanothreposi_temp);
    int peakposi_temp = nanothreposi_temp;
    for (int i = nanothreposi_temp; i < nanothreposi_temp + int(6e-9 / FileTimeUnitAverage); i++)
    {
        if (*(data_temp + i) > peak_temp)
        {
            peak_temp = *(data_temp + i);
            peakposi_temp = i;
        }
    }

    if (peak_temp < 0.25 || peak_temp > 0.45)
    {
        cerr << "FileOrder i =  " << FileOrderi << endl;
        cerr << "nano signal peak is " << peak_temp << endl;
        FileWrongProcess = 1;
        return;
    }

    NanoPeak = peak_temp;
    NanoPeakPosi = peakposi_temp;

    double nanoreferA = nanothreshold + baseline_nano;

    for (int i = nanothreposi_temp - 2 * move_1ns; i < NanoPeakPosi; i++)
    {
        if (*(data_temp + i) > nanoreferA)
        {
            NanoTime = time_temp[i] + (time_temp[i - 1] - time_temp[i]) * (nanoreferA - data_temp[i]) / (data_temp[i - 1] - data_temp[i]);
            NanoThrePosi = i;
            break;
        }
    }
    GetLaserReferTimeInOneFile_nano();
    OneDecayTime = NanoTime - vLaserReferTimeInOneFile.at(0);
}

#endif
