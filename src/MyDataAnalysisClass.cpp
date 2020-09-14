#ifndef MyDataAnalysisClass_cpp
#define MyDataAnalysisClass_cpp

#include "../incl/MyDataAnalysisClass.hpp"

//*****************************************************************************
void MyDataAnalysisClass::GetFileInfo(int FileMaxColumn_fp, int FileMaxRow_fp, double FileTimeUnitAverage_fp)
{
    FileMaxColumn = FileMaxColumn_fp;
    FileMaxRow = FileMaxRow_fp;
    FileTimeUnitAverage = FileTimeUnitAverage_fp;
}

void MyDataAnalysisClass::GetFileInfo( int FileMaxColumn_fp, int FileMaxRow_fp, double FileTimeOriginal_fp, double FileTimeUnitAverage_fp)
{
    FileMaxColumn = FileMaxColumn_fp;
    FileMaxRow = FileMaxRow_fp;
    FileTimeUnitAverage = FileTimeUnitAverage_fp;
    FileTimeOriginal = FileTimeOriginal_fp;
}

void MyDataAnalysisClass::GetDataPointer(double *Time_fp, double *Volts1_fp)
{
    rawdata_channel_t = Time_fp;
    rawdata_channel_1 = Volts1_fp;
}

void MyDataAnalysisClass::GetDataPointer(double *Time_fp, double *Volts1_fp, double *Volts2_fp)
{
    rawdata_channel_t = Time_fp;
    rawdata_channel_1 = Volts1_fp;
    rawdata_channel_2 = Volts2_fp;
}

MyDataAnalysisClass::MyDataAnalysisClass()
{
    cout << "create a default object " << endl;
}

//****************************************************************************

MyDataAnalysisClass::MyDataAnalysisClass(TString FileName_fp, bool check_fp)
{
    GetFileInformation(FileName_fp);
    CheckFileInformation(check_fp);
    newrawdatachannelNum = FileMaxColumn;

    switch (newrawdatachannelNum)
    {
    case 4:
        cout << " creating 4 " << endl;
        rawdata_channel_4 = new Double_t[FileMaxRow]();

    case 3:
        cout << " creating 3 " << endl;
        rawdata_channel_3 = new Double_t[FileMaxRow]();

    case 2:
        cout << " creating 2 " << endl;
        rawdata_channel_2 = new Double_t[FileMaxRow]();

    case 1:
        cout << " creating 1 " << endl;
        rawdata_channel_1 = new Double_t[FileMaxRow]();

    case 0:
        cout << " creating t " << endl;
        rawdata_channel_t = new Double_t[FileMaxRow]();
        break;

    case -1:
        cout << "new segment is not need " << endl;
        break;

    default:
        cout << " wrong FileMaxColumn " << endl;
        exit(EXIT_FAILURE);
        break;
    }
}

MyDataAnalysisClass::~MyDataAnalysisClass()
{
    switch (newrawdatachannelNum)
    {
    case 4:
        cout << " deleting 4 " << endl;
        delete[] rawdata_channel_4;
    case 3:
        cout << " deleting 3 " << endl;
        delete[] rawdata_channel_3;

    case 2:
        cout << " deleting 2 " << endl;
        delete[] rawdata_channel_2;

    case 1:
        cout << " deleting 1 " << endl;
        delete[] rawdata_channel_1;

    case 0:
        cout << " deleting 0 " << endl;
        delete[] rawdata_channel_t;
        break;

    case -1:
        cout << " end program.  no array need to delete " << endl;
        break;

    default:
        cout << "newrawdatachannelNum = " << newrawdatachannelNum << endl;
        cout << "no array need to delete " << endl;
        // exit(EXIT_FAILURE);
        // break;
    }
}

void MyDataAnalysisClass::GetFileInformation(TString FileName_fp)
{
    //get info: FileMaxRow, FileMaxColumn, FileTimeUnitAverage
    ifstream checkStream;
    checkStream.open(FileName_fp);
    if (checkStream.is_open())
    {
        cout << "open the check file successfully : " << FileName_fp << endl;
    }
    else
    {
        cout << "fail to open the file " << FileName_fp << endl;
        cout << "something wrong when get the file information " << endl;
        exit(EXIT_FAILURE);
    }

    TString firstline;
    firstline.ReadLine(checkStream);
    FileMaxRow = 1;
    FileMaxColumn = firstline.CountChar(',');

    cout << "by counting char ',', get the FileMaxColumn " << FileMaxColumn << endl;

    Double_t time_temp[3];
    //	TString rest_temp;
    char rest_temp[100];
    for (int i = 0; i < 3; i++)
    {
        checkStream >> time_temp[i];
        checkStream.getline(rest_temp, 40);
        cout << time_temp[i] << rest_temp << endl;
    }
    FileMaxRow += 3;

    FileTimeUnit1 = time_temp[1] - time_temp[0];
    FileTimeUnit2 = time_temp[2] - time_temp[1];
    FileTimeUnitAverage = (time_temp[2] - time_temp[0]) / 2;

    while (firstline.ReadLine(checkStream))
    {
        FileMaxRow++;
    }
    //为了考虑示波器保存数据可能产生错误，将FileMaxRow-5
    FileMaxRow -= 5;

    cout << "the raw quantity in a file is " << FileMaxRow << endl;
    checkStream.close();
}

void MyDataAnalysisClass::CheckFileInformation(bool check_fp)
{
    cout << endl
         << endl;
    cout << " Make sure the file informations following are right " << endl;
    cout << " ******************************************************************* " << endl;
    cout << " the file max row is " << FileMaxRow << endl;
    cout << " the file max column is " << FileMaxColumn << endl;
    cout << " the file time original is " << FileTimeOriginal << endl;
    cout << " the file time units are " << FileTimeUnit1 << "  and  " << FileTimeUnit2 << endl;
    cout << " the file time unit average is " << FileTimeUnitAverage << endl;
    cout << " ******************************************************************* " << endl;
    cout << endl
         << endl;

    if(check_fp)
    {
        cout << " input \"yes\" to continue ,input \"no\" to modify and others to quit " << endl;
        TString mks;
        if (cin >> mks)
        {
            if (mks == "yes")
            {
                cout << "finish check the file information " << endl;
            }
            else if (mks == "no")
            {
                cout << "the file information is wrong,please check it again " << endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                cout << " you choose to quit the program " << endl;
                exit(EXIT_FAILURE);
            }
        }

    }
    
}

bool MyDataAnalysisClass::ReadOneFile(TString FileName_fp, bool AutoStop_fp)
{
    ReadingFileName = FileName_fp;
    bool readonefile = true;
    ifstream readStream;
    readStream.open(FileName_fp);
    if (readStream.is_open())
    {
        readonefile = true;
        cout << "open the file named " << FileName_fp << endl;
    }
    else
    {
        readonefile = false;
        cout << "cannot open the file " << FileName_fp << "please check it again " << endl;
        if(AutoStop_fp == true)
        {
            exit(EXIT_FAILURE); //system("pause")
        }
        readStream.close();
        return false;
    }

    char douhao;
    switch (FileMaxColumn)
    {
    case 4:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k] >> douhao >> rawdata_channel_1[k] >> douhao >> rawdata_channel_2[k] >> douhao >> rawdata_channel_3[k] >> douhao >> rawdata_channel_4[k];
        }
        break;

    case 3:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k] >> douhao >> rawdata_channel_1[k] >> douhao >> rawdata_channel_2[k] >> douhao >> rawdata_channel_3[k];
        }
        break;

    case 2:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k] >> douhao >> rawdata_channel_1[k] >> douhao >> rawdata_channel_2[k];
        }
        break;

    case 1:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k] >> douhao >> rawdata_channel_1[k];
        }
        break;

    case 0:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k];
        }
        break;

    default:
        readonefile = false;
        cout << " wrong FileMaxRow or wrong file " << endl;
        if(AutoStop_fp == true)
        {
            exit(EXIT_FAILURE); 
        }
        break;
    }
    if(readStream.fail())
    {
        readonefile = false;
        cerr << "readStream.fail == 1, so something wrong " << endl;
        if(AutoStop_fp == true)
        {
            exit(EXIT_FAILURE);
        }
    }
    readStream.close();
    return readonefile;
}
void MyDataAnalysisClass::ReadOneFile(TString FileName_fp)
{
    ReadingFileName = FileName_fp;
    ifstream readStream;
    readStream.open(FileName_fp);
    if (readStream.is_open())
    {
        cout << "open the file named " << FileName_fp << endl;
    }
    else
    {
        cout << "cannot open the file " << FileName_fp << "please check it again " << endl;
        exit(EXIT_FAILURE); //system("pause")
    }

    char douhao;
    switch (FileMaxColumn)
    {
    case 4:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k] >> douhao >> rawdata_channel_1[k] >> douhao >> rawdata_channel_2[k] >> douhao >> rawdata_channel_3[k] >> douhao >> rawdata_channel_4[k];
        }
        break;

    case 3:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k] >> douhao >> rawdata_channel_1[k] >> douhao >> rawdata_channel_2[k] >> douhao >> rawdata_channel_3[k];
        }
        break;

    case 2:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k] >> douhao >> rawdata_channel_1[k] >> douhao >> rawdata_channel_2[k];
        }
        break;

    case 1:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k] >> douhao >> rawdata_channel_1[k];
        }
        break;

    case 0:
        for (int k = 0; k < FileMaxRow; k++)
        {
            readStream >> rawdata_channel_t[k];
        }
        break;

    default:
        cout << " wrong FileMaxRow or wrong file " << endl;
        exit(EXIT_FAILURE);
        break;
    }
    if(readStream.fail())
    {
        cerr << "readStream.fail == 1, so something wrong " << endl;
        exit(EXIT_FAILURE);
    }
    readStream.close();
}

void MyDataAnalysisClass::ShowTheReadRawDataOfAFile(bool SaveOrNot_fp , TString FigHeader_fp)
{
    auto tc = new TCanvas("tc","tc",1200,800);
    TGraph * tg1;
    TGraph * tg2;
    TGraph * tg3;
    TGraph * tg4;
    
    switch (FileMaxColumn)
    {
    case 4:
        tg1 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_1);
        tg2 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_2);
        tg3 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_3);
        tg4 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_4);
        tc->Divide(2,2);
        tc->cd(1);
        tg1->Draw();
        tc->cd(2);
        tg2->Draw();
        tc->cd(3);
        tg3->Draw();
        tc->cd(4);
        tg4->Draw();
        break;

    case 3:
        tg1 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_1);
        tg2 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_2);
        tg3 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_3);
        tc->Divide(2,2);
        tc->cd(1);
        tg1->Draw();
        tc->cd(2);
        tg2->Draw();
        tc->cd(3);
        tg3->Draw();
        break;

    case 2:
        tg1 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_1);
        tg2 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_2);
        tc->Divide(1,2);
        tc->cd(1);
        tg1->Draw();
        tc->cd(2);
        tg2->Draw();
        break;

    case 1:
        tg1 = new TGraph(FileMaxRow,rawdata_channel_t,rawdata_channel_1);
        tg1->Draw();

        break;

    case 0:
        cout << " FileMaxRow is 0, which means only time data is input " << endl;
        break;

    default:
        cout << " wrong FileMaxRow or wrong file " << endl;
        exit(EXIT_FAILURE);
        break;
    }

    if(SaveOrNot_fp)
    {
        tc->SaveAs(FigHeader_fp + TString(".root"));
        tc->SaveAs(FigHeader_fp + TString(".pdf"));
    }

}

//****************************************************************************

void MyDataAnalysisClass::FindAverageBaseline(Double_t &mean_fp, Double_t &sigma_fp, const Double_t *data_fp, const Int_t dataquantity_fp)
{
    cout << " find average baseline :  dataquantity = " << dataquantity_fp << endl;
    Double_t dataMax = 0;
    Double_t dataMin = 0;

    for (int i = 0; i < dataquantity_fp; i++)
    {
        if (data_fp[i] > dataMax)
        {
            dataMax = data_fp[i];
        }
        if (data_fp[i] < dataMin)
        {
            dataMin = data_fp[i];
        }
    }
    if (dataMin >= 0)
    {
        cout << "the dataMin is positive ,please check the data " << endl;
        exit(EXIT_FAILURE);
    }
    if (dataMax <= 0)
    {
        cout << "the dataMax is nagetive ,please check the data " << endl;
        exit(EXIT_FAILURE);
    }

    cout << "max  = " << dataMax << endl;
    cout << "min  = " << dataMin << endl;

    dataMin = -0.1;
    dataMax = 0.1;

    double binWidth_fp = 0.005;
    Int_t BinNum = int(2.0 * (dataMax - dataMin) / binWidth_fp + 0.5);

    //    auto hist_temp = new TH1D("hist_temp", "hist_temp", BinNum, 2 * dataMin, 2 * dataMax);
    //    auto hist_temp = new TH1D("hist_temp", "hist_temp", 40, -0.1, 0.1);
    TH1D hist_temp("hist_temp", "hist_temp", 40, -0.1, 0.1);
    for (int i = 0; i < dataquantity_fp; i++)
    {
        if (data_fp[i] > -0.1 && data_fp[i] < 0.1)
            hist_temp.Fill(data_fp[i]);
    }

    TF1 gausf("gausf", "gaus", 2 * dataMin, 2 * dataMax);

    gausf.SetParameter(0, hist_temp.GetMaximum());
    gausf.SetParameter(1, hist_temp.GetMean());
    gausf.SetParLimits(1, -0.2, 0.2);
    gausf.SetParameter(2, hist_temp.GetStdDev());
    gausf.SetParLimits(2, -0.2, 0.2);

    //注意加上“N”不画图像
    hist_temp.Fit("gausf", "QMN");

    mean_fp = gausf.GetParameter(1);
    sigma_fp = gausf.GetParameter(2);

    cout << "the baseline is " << mean_fp << " +- " << sigma_fp << endl;
}

void MyDataAnalysisClass::FindAverageBaseline(Double_t &mean_fp, Double_t &sigma_fp, const Double_t *data_fp, const Int_t dataquantity_fp, TString savename_fp)
{
    cout << " find average baseline " << endl;
    Double_t dataMax = 0;
    Double_t dataMin = 0;
    cout << " the dataquantity_fp = " << dataquantity_fp << endl;
    for (int i = 0; i < dataquantity_fp; i++)
    {
        if (data_fp[i] > dataMax)
        {
            dataMax = data_fp[i];
        }
        if (data_fp[i] < dataMin)
        {
            dataMin = data_fp[i];
        }
    }
    if (dataMin >= 0)
    {
        cout << "the dataMin is positive ,please check the data " << endl;
        exit(EXIT_FAILURE);
    }
    if (dataMax <= 0)
    {
        cout << "the dataMax is nagetive ,please check the data " << endl;
        exit(EXIT_FAILURE);
    }

    cout << "max  = " << dataMax << endl;
    cout << "min  = " << dataMin << endl;
    double binWidth_fp = 0.005;
    Int_t BinNum = int(0.5 + 2 * (dataMax - dataMin) / binWidth_fp);

    auto tc_temp = new TCanvas();
    //    auto hist_temp = new TH1D("hist_temp", "hist_temp", BinNum, 2 * dataMin, 2 * dataMax);
    auto hist_temp = new TH1D("hist_temp", "hist_temp", 40, -0.1, 0.1);
    for (int i = 0; i < dataquantity_fp; i++)
    {
        if (data_fp[i] > -0.1 && data_fp[i] < 0.1)
            hist_temp->Fill(data_fp[i]);
    }
    auto gausf = new TF1("gausf", "gaus", 2 * dataMin, 2 * dataMax);

    gausf->SetParameter(0, hist_temp->GetMaximum());
    gausf->SetParameter(1, hist_temp->GetMean());
    gausf->SetParLimits(1, -0.2, 0.2);
    gausf->SetParameter(2, hist_temp->GetStdDev());
    gausf->SetParLimits(2, -0.2, 0.2);

    hist_temp->Fit("gausf", "QM");

    mean_fp = gausf->GetParameter(1);
    sigma_fp = gausf->GetParameter(2);
    cout << "the baseline is " << mean_fp << " +- " << sigma_fp << endl;
    //hist_temp->Draw();
    tc_temp->Draw();
    tc_temp->SaveAs(savename_fp);
    delete hist_temp;
    delete gausf;
    delete tc_temp;
}

//ok
void MyDataAnalysisClass::DrawHist_BybinWidth_GausFit(Double_t &mean_fp, Double_t &sigma_fp, const Double_t *data_fp, const Int_t dataquantity_fp, const Double_t binWidth_fp)
{
    //    cout << " draw hist by bin width " << endl;
    Double_t dataMax = 0;
    Double_t dataMin = 0;
    //
    //    for (int i = 0; i < dataquantity_fp; i++)
    //    {
    //        if (data_fp[i] > dataMax)
    //        {
    //            dataMax = data_fp[i];
    //        }
    //        if (data_fp[i] < dataMin)
    //        {
    //            dataMin = data_fp[i];
    //        }
    //    }
    //    cout << "max  = " << dataMax << endl;
    //    cout << "min  = " << dataMin << endl;
    dataMin = -0.1;
    dataMax = 0.1;
    Int_t binNum_temp = int(0.5 + 2 * (dataMax - dataMin) / binWidth_fp);

    //    auto tc_temp = new TCanvas();
    auto hist_temp = new TH1D("hist_temp", "hist_temp", binNum_temp, 2 * dataMin, 2 * dataMax);
    for (int i = 0; i < dataquantity_fp; i++)
    {
        hist_temp->Fill(data_fp[i]);
    }
    auto gausf = new TF1("gausf", "gaus", 2 * dataMin, 2 * dataMax);
    gausf->SetParameter(0, hist_temp->GetMaximum());
    gausf->SetParLimits(0, 1, hist_temp->GetEntries());
    gausf->SetParameter(1, hist_temp->GetMean());
    gausf->SetParLimits(1, -0.08, 0.08);
    gausf->SetParameter(2, hist_temp->GetStdDev());
    gausf->SetParLimits(2, 0.001, 0.1);
    hist_temp->Fit("gausf", "QMN");

    mean_fp = gausf->GetParameter(1);
    sigma_fp = gausf->GetParameter(2);
    cout << "the baseline is " << mean_fp << " +- " << sigma_fp << endl;

    delete hist_temp;
    delete gausf;
    //    delete tc_temp;
}

void MyDataAnalysisClass::DrawHist_BybinWidth_GausFit(Double_t &mean_fp, Double_t &sigma_fp, const Double_t *data_fp, const Int_t dataquantity_fp, const Double_t binWidth_fp, bool check_fp, TString savename_fp)
{
    cout << " draw hist by bin width " << endl;
    Double_t dataMax = 0;
    Double_t dataMin = 0;

    //    for (int i = 0; i < dataquantity_fp; i++)
    //    {
    //        if (data_fp[i] > dataMax)
    //        {
    //            dataMax = data_fp[i];
    //        }
    //        if (data_fp[i] < dataMin)
    //        {
    //            dataMin = data_fp[i];
    //        }
    //    }
    //
    //    cout << "max  = " << dataMax << endl;
    //    cout << "min  = " << dataMin << endl;
    dataMin = -0.1;
    dataMax = 0.1;
    Int_t binNum_temp = int(0.5 + 2 * (dataMax - dataMin) / binWidth_fp);

    auto tc_temp = new TCanvas();
    auto hist_temp = new TH1D("hist_temp", "hist_temp", binNum_temp, 2 * dataMin, 2 * dataMax);
    for (int i = 0; i < dataquantity_fp; i++)
    {
        hist_temp->Fill(data_fp[i]);
    }
    auto gausf = new TF1("gausf", "gaus", 2 * dataMin, 2 * dataMax);
    gausf->SetParameter(0, hist_temp->GetMaximum());
    gausf->SetParLimits(0, 1, hist_temp->GetEntries());
    gausf->SetParameter(1, hist_temp->GetMean());
    gausf->SetParLimits(1, -0.1, 0.1);
    gausf->SetParameter(2, hist_temp->GetStdDev());
    gausf->SetParLimits(2, 0.001, 0.1);
    hist_temp->Fit("gausf", "QM");

    mean_fp = gausf->GetParameter(1);
    sigma_fp = gausf->GetParameter(2);
    cout << "the baseline is " << mean_fp << " +- " << sigma_fp << endl;
    if (check_fp)
    {
        tc_temp->SaveAs(savename_fp);
    }
    delete hist_temp;
    delete gausf;
    delete tc_temp;
}

void MyDataAnalysisClass::GetLaserReferTimeInOneFile_PMT()
{
    vLaserReferTimeInOneFile.clear();
    const double laserthreshold = 0.4;
    const double laserthreshold2 = 0.2;
    const double *data_temp = this->rawdata_channel_2;
    const double *time_temp = this->rawdata_channel_t;
    // auto tcc = new TCanvas();
    // auto tg = new TGraph(FileMaxRow,time_temp,data_temp);
    // tg->Draw();
    // tcc->Draw();
    // for (int i = 0; i < 20; i++)
    // {
    //     cout << "data_temp[i]  = " << data_temp[i]  << endl;
    // }
    
    for (int i = 0; i < FileMaxRow; i++)
    {   
        if (data_temp[i] > laserthreshold)
        {
            // cout << " in loop, i = " << i << endl;
            int rightH_temp = i;
            for (int j = i; j > 0; j--)
            {
                if (data_temp[j] < laserthreshold2)
                {
                    double AreferTime_temp = time_temp[j] + (time_temp[j + 1] - time_temp[j]) * (laserthreshold2 - data_temp[j]) / (data_temp[j + 1] - data_temp[j]);
                    vLaserReferTimeInOneFile.push_back(AreferTime_temp);
                    break;
                }
            }

            for (; data_temp[rightH_temp] > laserthreshold2 && rightH_temp < FileMaxRow; rightH_temp++)
            {
            }
            i = rightH_temp;
        }
    }
    
}

void MyDataAnalysisClass::GetLaserReferTimeInOneFile_nano()
{
    vLaserReferTimeInOneFile.clear();
    const double laserthreshold = 0.4;
    const double laserthreshold2 = 0.2;
    const double *data_temp = this->rawdata_channel_1;
    const double *time_temp = this->rawdata_channel_t;
    // auto tcc = new TCanvas();
    // auto tg = new TGraph(FileMaxRow,time_temp,data_temp);
    // tg->Draw();
    // tcc->Draw();
    // for (int i = 0; i < 20; i++)
    // {
    //     cout << "data_temp[i]  = " << data_temp[i]  << endl;
    // }
    
    for (int i = 0; i < FileMaxRow; i++)
    {   
        if (data_temp[i] > laserthreshold)
        {
            // cout << " in loop, i = " << i << endl;
            int rightH_temp = i;
            for (int j = i; j > 0; j--)
            {
                if (data_temp[j] < laserthreshold2)
                {
                    double AreferTime_temp = time_temp[j] + (time_temp[j + 1] - time_temp[j]) * (laserthreshold2 - data_temp[j]) / (data_temp[j + 1] - data_temp[j]);
                    vLaserReferTimeInOneFile.push_back(AreferTime_temp);
                    break;
                }
            }

            for (; data_temp[rightH_temp] > laserthreshold2 && rightH_temp < FileMaxRow; rightH_temp++)
            {
            }
            i = rightH_temp;
        }
    }
    
}

void MyDataAnalysisClass::CheckReadData_DecayTime()
{
    auto tc = new TCanvas();
    if (FileMaxColumn == 1)
    {
        auto tg = new TGraph(FileMaxRow, rawdata_channel_t, rawdata_channel_1);
        tg->Draw();
    }
    else if (FileMaxColumn == 2)
    {
        tc->Divide(1, 2);
        tc->cd(1);
        auto tg = new TGraph(FileMaxRow, rawdata_channel_t, rawdata_channel_1);
        tg->Draw();
        tc->cd(2);
        auto tg2 = new TGraph(FileMaxRow, rawdata_channel_t, rawdata_channel_2);
        tg2->Draw();
    }
    tc->SaveAs(Form("%d.png", FileOrderi));
}

void MyDataAnalysisClass::GetSignalInfo(vector<Signal> &vSignal_fp, const Int_t start_fp, const Int_t end_fp, const Double_t baseline_fp, const Double_t baselinesigma_fp)
{
    Signal signalinfo_temp;
    GetSignalInfo(signalinfo_temp, start_fp, end_fp, baseline_fp, baselinesigma_fp);
    vSignal_fp.push_back(signalinfo_temp);
}

void MyDataAnalysisClass::GetSignalInfo(Signal &vSignal_fp, const Int_t start_fp, const Int_t end_fp, const Double_t baseline_fp, const Double_t baselinesigma_fp)
{
    Signal signalinfo_temp;

    const Double_t *data_temp = this->rawdata_channel_1;
    const Double_t *time_temp = this->rawdata_channel_t;

    double peak = *(data_temp + start_fp);
    double peaktime_temp = 0;
    int peakposition = start_fp;

    for (int i = start_fp; i < end_fp; i++)
    {
        if (*(data_temp + i) < peak)
        {
            peak = *(data_temp + i);
            peakposition = i;
        }
    }
    peaktime_temp = *(time_temp + peakposition);
    //    cout << "during " << start_fp << "(" << rawdata_channel_t[start_fp] << ") and " << end_fp << "(" << rawdata_channel_t[end_fp]<< "), the peak is " << peak << "; its position is " <<  peakposition << endl;

    signalinfo_temp.baseline = baseline_fp;
    signalinfo_temp.baselinesigma = baselinesigma_fp;
    signalinfo_temp.amplitude = peak - baseline_fp;

    double Asigma3 = baseline_fp - 3 * baselinesigma_fp;
    double Asigma3_tl;
    double Asigma3_tr;
    int Asigma3_posi_l;
    int Asigma3_posi_r;
    double area_3sigma_temp = 0;

    double A5_A = 0.05 * (peak - baseline_fp) + baseline_fp;
    double A10_A = 0.1 * (peak - baseline_fp) + baseline_fp;
    double A15_A = 0.15 * (peak - baseline_fp) + baseline_fp;
    double A20_A = 0.2 * (peak - baseline_fp) + baseline_fp;
    double A30_A = 0.3 * (peak - baseline_fp) + baseline_fp;
    double A50_A = 0.5 * (peak - baseline_fp) + baseline_fp;
    double A90_A = 0.9 * (peak - baseline_fp) + baseline_fp;

    double A5_tl = 0.;
    double A10_tl = 0.;
    double A15_tl = 0.;
    double A20_tl = 0.;
    double A30_tl = 0.;
    double A50_tl = 0.;
    double A90_tl = 0.;
    double A10_tr = 0.;
    double A50_tr = 0.;
    double A90_tr = 0.;

    int A90_position_l = 0;
    int A90_position_r = 0;
    int A10_position_l = 0;
    int A10_position_r = 0;
    // int A50_position_l = 0;
    // int A50_position_r = 0;

    double Ampl_temp[7] = {A90_A, A50_A, A30_A, A20_A, A15_A, A10_A, A5_A};
    int Posi_temp[7] = {0};
    double PosiTime_temp[7] = {0};
    int i_temp = 0;
    for (int i = peakposition; i > 0; i--)
    {
        if (*(data_temp + i) > Ampl_temp[i_temp])
        {
            Posi_temp[i_temp] = i;
            PosiTime_temp[i_temp] = time_temp[i] + (Ampl_temp[i_temp] - data_temp[i]) / (data_temp[i + 1] - data_temp[i]) * (time_temp[i + 1] - time_temp[i]);
            i_temp++;
            if (i_temp > 6)
            {
                break;
            }
        }
    }

    double Ampl_r_temp[3] = {A90_A, A50_A, A10_A};
    int Posi_r_temp[3] = {0};
    double PosiTime_r_temp[3] = {0};
    int i_r_temp = 0;

    for (int i = peakposition; i < FileMaxRow; i++)
    {
        if (*(data_temp + i) > Ampl_r_temp[i_r_temp])
        {
            Posi_r_temp[i_r_temp] = i;
            PosiTime_r_temp[i_r_temp] = time_temp[i] + (Ampl_r_temp[i_r_temp] - data_temp[i]) / (data_temp[i - 1] - data_temp[i]) * (time_temp[i - 1] - time_temp[i]);
            i_r_temp++;
            if (i_r_temp > 2)
            {
                break;
            }
        }
    }
    A10_position_l = Posi_temp[5];
    A90_position_l = Posi_temp[0];
    A10_position_r = Posi_r_temp[2];
    A90_position_r = Posi_r_temp[0];

    A5_tl = PosiTime_temp[6];
    A10_tl = PosiTime_temp[5];
    A15_tl = PosiTime_temp[4];
    A20_tl = PosiTime_temp[3];
    A30_tl = PosiTime_temp[2];
    A50_tl = PosiTime_temp[1];
    A90_tl = PosiTime_temp[0];

    A90_tr = PosiTime_r_temp[0];
    A50_tr = PosiTime_r_temp[1];
    A10_tr = PosiTime_r_temp[2];

    signalinfo_temp.risetime = A90_tl - A10_tl;
    signalinfo_temp.falltime = A10_tr - A90_tr;
    signalinfo_temp.starttime_CFT5 = A5_tl;
    signalinfo_temp.starttime_CFT = A10_tl;
    signalinfo_temp.starttime_CFT15 = A15_tl;
    signalinfo_temp.starttime_CFT20 = A20_tl;
    signalinfo_temp.starttime_CFT30 = A30_tl;
    signalinfo_temp.starttime_CFT50 = A50_tl;
    signalinfo_temp.starttime_CFT90 = A90_tl;
    signalinfo_temp.peaktime = peaktime_temp;
    signalinfo_temp.width = A10_tr - A10_tl;
    signalinfo_temp.FWHM = A50_tr - A50_tl;

    for (int i = peakposition; i > 0; i--)
    {
        if (*(data_temp + i) > Asigma3)
        {
            Asigma3_posi_l = i;
            Asigma3_tl = time_temp[i] + (Asigma3 - data_temp[i]) / (data_temp[i + 1] - data_temp[i]) * (time_temp[i + 1] - time_temp[i]);
            break;
        }
    }
    for (int i = peakposition; i < FileMaxRow; i++)
    {
        if (*(data_temp + i) > Asigma3)
        {
            Asigma3_posi_r = i;
            Asigma3_tr = time_temp[i] + (Asigma3 - data_temp[i]) / (data_temp[i - 1] - data_temp[i]) * (time_temp[i - 1] - time_temp[i]);
            break;
        }
    }
    for(int i = Asigma3_posi_l; i < Asigma3_posi_r; i ++)
    {
        area_3sigma_temp += (data_temp[i + 1] + data_temp[i]) / 2.0 * (time_temp[i + 1] - time_temp[i]);
    }
    area_3sigma_temp -= baseline_fp * (time_temp[Asigma3_posi_l] - time_temp[Asigma3_posi_r]);
    signalinfo_temp.timebssigma3_left = Asigma3_tl;
    signalinfo_temp.timebssigma3_right = Asigma3_tr;
    signalinfo_temp.area_3sigma = area_3sigma_temp;

    for (int i = peakposition; i > 0; i--)
    {
        if (*(data_temp + i) > PMTThreshold)
        {
            signalinfo_temp.starttime_threshold = time_temp[i] + (PMTThreshold - data_temp[i]) / (data_temp[i + 1] - data_temp[i]) * (time_temp[i + 1] - time_temp[i]);
            break;
        }
    }

    double area_temp = 0;
    for (int i = A10_position_l; i < A10_position_r; i++)
    {
        area_temp += (data_temp[i + 1] + data_temp[i]) / 2.0 * (time_temp[i + 1] - time_temp[i]);
    }
    area_temp -= baseline_fp * (time_temp[A10_position_r] - time_temp[A10_position_l]);
    signalinfo_temp.area = area_temp;
    signalinfo_temp.startposition = A10_position_l;
    signalinfo_temp.endposition = A10_position_r;
    vSignal_fp = signalinfo_temp;
}

// void MyDataAnalysisClass::FitSignal(Signal &vSignal_fp, const Int_t start_fp, const Int_t end_fp, const Double_t baseline_fp)
void MyDataAnalysisClass::FitSignal()
{
    auto tc = new TCanvas();

    auto tg = new TGraph(FileMaxRow, rawdata_channel_t, rawdata_channel_1);
    tg->Draw();
    auto bl = new TF1("bl", "[0]", -20e-9, 20e-9);
    bl->SetParameter(0, OneSignal_DT.baseline);
    bl->SetLineColor(kGreen);
    bl->Draw("same");

    // auto ex = new TF1("ex","[0]*exp((x-[1])/[2])",OneSignal_DT.starttime_CFT5-1e-9,OneSignal_DT.starttime_CFT50);
    // ex->SetParameters(-0.1,-10.5e-9,10e-9);

    auto ex = new TF1("ex", "[0]*(x-[1])*(x-[1])", OneSignal_DT.starttime_CFT5, OneSignal_DT.starttime_CFT50);
    ex->SetParameters(-0.1, -10.6e-9);

    tg->Fit("ex", "R");
    ex->Draw("same");
}

void MyDataAnalysisClass::DrawResultsForCheck()
{

    auto tc = new TCanvas();
    int startps = OneSignal_DT.startposition - int(1e-9 / FileTimeUnitAverage);
    int endps = OneSignal_DT.endposition + int(0e-9 / FileTimeUnitAverage);
    cout << "startps = " << startps << endl;
    cout << "ends = " << endps << endl;
    auto tg = new TGraph(endps - startps, rawdata_channel_t + startps, rawdata_channel_1 + startps);
    tg->Draw();
    // gPad->Modified();
    // gPad->Update();
    TLine *base = new TLine(-1., OneSignal_DT.baseline, 1, OneSignal_DT.baseline);
    base->SetLineColor(kRed);
    // cout << "OneSignal_DT.baseline = " << OneSignal_DT.baseline << endl;
    // cout << "gPad->GetUxmin() = " << gPad->GetUxmin() << endl;
    // TLine *base = new TLine(gPad->GetUxmin(),OneSignal_DT.baseline,gPad->GetUxmax(),OneSignal_DT.baseline);
    base->Draw("same");
    TLine *tp = new TLine(OneSignal_DT.starttime_CFT, 1, OneSignal_DT.starttime_CFT, -1);
    tp->SetLineColor(kRed);
    // TLine *tp = new TLine(OneSignal_DT.starttime_CFT,gPad->GetUymin(),OneSignal_DT.starttime_CFT,gPad->GetUymin());
    tp->Draw("same");
    tc->Draw();
    tc->SaveAs(Form("result%d.png", FileOrderi));

    delete tc;
    delete tg;
    delete base;
    delete tp;
}


//LED PMT刻度~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MyDataAnalysisClass::SetvUnitFlag(const Double_t FlagTimestart,const Double_t LEDPeriod, const Double_t SignalTimestart, const Double_t SignalWidth, const Int_t SignalQuantity)
{
    cout << " make sure the rawdata_time have already been assigned " << endl;
    vUnitFlagStart.clear();
    vUnitFlagEnd.clear();
    vUnitSignalEnd.clear();
    vUnitSignalEnd.clear();

    Int_t Bins_LEDPeriod = (int)(LEDPeriod/FileTimeUnitAverage +0.5);
    Int_t Bins_SignalPeriod = (int)(SignalWidth/FileTimeUnitAverage +0.5);
    Int_t Num_LEDstart = 0;
    Int_t Num_SignalStart = 0;

    for (int i = 0; i < FileMaxRow; i++)
    {
        if (rawdata_channel_t[i] > FlagTimestart)
        {
            Num_LEDstart = i;
            for(int j = i; j < FileMaxRow; j ++)
            {
                if(rawdata_channel_t[j] > SignalTimestart)
                {
                    Num_SignalStart = j;
                    break;
                }
            }
            break;
        }
    }

    // cout << " flag start time = " << NumStart << " " << rawdata_channel_t[NumStart] << endl;
    for (int i = 0; i < SignalQuantity; i++)
    {
        vUnitFlagStart.push_back(Num_LEDstart + i*Bins_LEDPeriod);
        vUnitFlagEnd.push_back(Num_LEDstart + (i+1)*Bins_LEDPeriod);
        vUnitSignalStart.push_back(Num_SignalStart + i * Bins_SignalPeriod);
        vUnitSignalEnd.push_back(Num_SignalStart + (i+1) * Bins_SignalPeriod);
    }
}

void MyDataAnalysisClass::SetvUnitFlag(const Double_t FlagTimestart,const Double_t LEDPeriod, const Int_t SignalQuantity)
{
    double SignalTimeStart = FlagTimestart;
    double SignalWidth = LEDPeriod;
    SetvUnitFlag(FlagTimestart, LEDPeriod, SignalTimeStart, SignalWidth, SignalQuantity);
}


double MyDataAnalysisClass::GetAreaSum(int nstart_fp, int nend_fp, double baseline_fp)
{
    const double * pdata_temp = rawdata_channel_1;
    const double * ptime_temp = rawdata_channel_t;
    double s_temp = 0;
    for(int i = nstart_fp; i < nend_fp; i ++)
    {
        s_temp += 0.5*(pdata_temp[i]+pdata_temp[i+1])*(ptime_temp[i+1]-ptime_temp[i]);
    }
    s_temp -= (ptime_temp[nend_fp]-ptime_temp[nstart_fp])*baseline_fp;
    return s_temp;
}

double MyDataAnalysisClass::GetAreaSum(int nstart_fp, int nend_fp, double tstart_fp, double tend_fp, double baseline_fp)
{
    const double * pdata_temp = rawdata_channel_1;
    const double * ptime_temp = rawdata_channel_t;
    double most_temp = GetAreaSum(nstart_fp,nend_fp,baseline_fp);

    double V_l = pdata_temp[nstart_fp-1] + (tstart_fp-ptime_temp[nstart_fp-1])*(pdata_temp[nstart_fp-1]-pdata_temp[nstart_fp])/(ptime_temp[nstart_fp-1]-ptime_temp[nstart_fp]);
    double V_r = pdata_temp[nend_fp+1] + (tend_fp-ptime_temp[nend_fp+1])*(pdata_temp[nend_fp+1]-pdata_temp[nend_fp])/(ptime_temp[nend_fp+1]-ptime_temp[nend_fp]);
    double s_l = 0.5*(V_l+pdata_temp[nstart_fp])*(ptime_temp[nstart_fp]-tstart_fp);
    double s_r = 0.5*(V_l+pdata_temp[nend_fp])*(tend_fp-ptime_temp[nstart_fp]);
    return (most_temp + s_l + s_r);
}

int MyDataAnalysisClass::iFindThePeakPosition(int nstart_fp, int nend_fp)
{
    const double * pdata_temp = rawdata_channel_1;
    double A_peak = pdata_temp[nstart_fp];
    int posi_peak = nstart_fp;
    for(int i = nstart_fp; i < nend_fp; i ++)
    {
        if(pdata_temp[i] < A_peak)
        {
            A_peak = pdata_temp[i];
            posi_peak = i;
        }
    }
    return posi_peak;
}

double MyDataAnalysisClass::dFindThePeakAmplitude(int nstart_fp, int nend_fp)
{
    const double * pdata_temp = rawdata_channel_1;
    double A_peak = pdata_temp[nstart_fp];
    int posi_peak = nstart_fp;
    for(int i = nstart_fp; i < nend_fp; i ++)
    {
        if(pdata_temp[i] < A_peak)
        {
            A_peak = pdata_temp[i];
            posi_peak = i;
        }
    }
    return pdata_temp[posi_peak];
}


// void MyDataAnalysisClass::

void MyDataAnalysisClass::WorkOnAFile_PMTGain_byAmpl()
{
    vUnitBaseline.clear();
    vUnitBaselineSigma.clear();
    vUnitPeak.clear();
    vUnitPeakPosi.clear();
    vUnitAmplitude.clear();
    vUnitArea_2ns.clear();
    vEverySignalsInAFile_Gain.clear();
    const Double_t *data_temp = this->rawdata_channel_1;
    const int move_1ns = int(1e-9 / FileTimeUnitAverage + 0.5);

    for(int i = 0; i < vUnitSignalStart.size(); i ++)
    {
        // Signal signal_temp;
        double ampl = dFindThePeakAmplitude(vUnitSignalStart.at(i),vUnitSignalEnd.at(i));
        int peakposi = iFindThePeakPosition(vUnitSignalStart.at(i),vUnitSignalEnd.at(i));
        vUnitPeak.push_back(ampl);        
        vUnitPeakPosi.push_back(peakposi);

        double meanInUnit = 0;
        double sigmaInUnit = 0;
        if(peakposi < 11*move_1ns)
        {
            peakposi = 11*move_1ns;
        }
        DrawHist_BybinWidth_GausFit(meanInUnit, sigmaInUnit, data_temp + peakposi - 11 * move_1ns, 10 * move_1ns, 0.002);
        double area_1_1 = GetAreaSum(peakposi-move_1ns,peakposi+move_1ns,meanInUnit);
        GetSignalInfo(vEverySignalsInAFile_Gain, peakposi-move_1ns, peakposi+move_1ns, meanInUnit, sigmaInUnit);

        vUnitBaseline.push_back(meanInUnit);
        vUnitBaselineSigma.push_back(sigmaInUnit);
        vUnitAmplitude.push_back(ampl-meanInUnit);
        vUnitArea_2ns.push_back(area_1_1);
    }
}

// void MyDataAnalysisClass::DrawAllFileToSetFlag(TString FileHeader_fp, int FileNum_fp = 0, TString FileNameSuffix_fp = ".csv", int Quantity_fp = -1)
void MyDataAnalysisClass::DrawAllFileToSetFlag(TString FileHeader_fp, int FileNum_fp, TString FileNameSuffix_fp , int Quantity_fp )
{
    int fi = FileNum_fp;
    TString FileName_temp = FileHeader_fp + Form("%05d",fi) + FileNameSuffix_fp;
    Sum_T = new double[FileMaxRow]();
    Sum_V = new double[FileMaxRow]();
    if(ReadOneFile(FileName_temp,false) == true)
    {
        for(int i = 0; i < FileMaxRow; i ++)
        {
            Sum_T[i] = rawdata_channel_t[i];
            Sum_V[i] = rawdata_channel_1[i];
        }
    }
    fi ++;
    FileName_temp = FileHeader_fp + Form("%05d",fi) + FileNameSuffix_fp;
    // cout << "FileName_temp = " << FileName_temp << endl;
    while(ReadOneFile(FileName_temp,false) == true)
    {
        for(int i = 0; i < FileMaxRow; i ++)
        {
            Sum_V[i] += rawdata_channel_1[i];
        }
        fi++;
        FileName_temp = FileHeader_fp + Form("%05d",fi) + FileNameSuffix_fp;
        // cout << "the file is " << FileName_temp << endl;
        if(Quantity_fp != -1)
        {
            if(fi > FileNum_fp+Quantity_fp-1) //因为前面读过了两次，但fi++了，所以-1
            {
                break;
            }
        }
    }
    auto tc = new TCanvas();
    auto tg = new TGraph(FileMaxRow, Sum_T, Sum_V);
    tg->Draw();
}

void MyDataAnalysisClass::AccumulateTimeAndVolt(int Filei_fp)
{
    if(Filei_fp == 0)
    {
        Sum_T = new double[FileMaxRow]();
        Sum_V = new double[FileMaxRow]();
        for(int i = 0; i < FileMaxRow; i ++)
        {
            Sum_T[i] = rawdata_channel_t[i];
            Sum_V[i] += rawdata_channel_1[i];
        }
    }
    else
    {
        for(int i = 0; i < FileMaxRow; i ++)
        {
            Sum_V[i] += rawdata_channel_1[i];
        }
    }
}

void MyDataAnalysisClass::DrawAllFileTimeAndVolt()
{
    auto tc = new TCanvas();
    auto tg = new TGraph(FileMaxRow,Sum_T,Sum_V);
    tg->Draw();
}


#endif