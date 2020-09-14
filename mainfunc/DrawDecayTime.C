/*
    数据分析的思路:  
    1 读取文件得到拟合得到的参数。
        （1）用数组依次读取每个条件下的参数（一般关于波长），进行转置（为画直方图）

    2 画直方图
        （1）画图，注意标题等格式

    author: 邓佳维
    date: 20200901
 */

#include "TGraph.h"
#include "TString.h"
#include "TGraphErrors.h"
#include <fstream>
#include <vector>
#include <TCanvas.h>

void DrawDecayTime(TString FileName_fp)
{
    // const Int_t parNum = 11;
    // const Int_t fileNum = 9+9;
    const Int_t parNum = 12;
    const Int_t fileNum = 14;

    TString FileName = FileName_fp;
    ifstream inFile;
    inFile.open(FileName);
    if (inFile.is_open())
    {
        cout << "open the file " << FileName << " successfully " << endl;
    }
    else
    {
        cout << "fail to open " << FileName << endl;
    }

    //用来读取保存文件中的数据
    Double_t ParameterArray[fileNum][parNum] = {0};
    Double_t ErrorArray[fileNum][parNum] = {0};
    Double_t ParaTransArray[parNum][fileNum] = {0};
    Double_t ErrorTransArray[parNum][fileNum] = {0};

    for (int i = 0; i < fileNum; i++)
    {
        for (int j = 0; j < parNum; j++)
        {
            inFile >> ParameterArray[i][j];
        }
        for (int j = 0; j < parNum; j++)
        {
            inFile >> ErrorArray[i][j];
        }
    }

    inFile.close();

    for (int i = 0; i < fileNum; i++)
    {
        for (int j = 0; j < parNum; j++)
        {
            ParaTransArray[j][i] = ParameterArray[i][j];
            ErrorTransArray[j][i] = ErrorArray[i][j];
        }
    }

    for (int i = 0; i < fileNum; i++)
    {
        for (int j = 0; j < parNum; j++)
        {
            cout << ParameterArray[i][j] << "   ";
        }
        for (int j = 0; j < parNum; j++)
        {
            cout << ErrorArray[i][j] << "   ";
        }
        cout << endl;
    }

    Double_t tauA1[fileNum];
    Double_t tauA2[fileNum];
    Double_t tauB[fileNum];
    Double_t w_PPO_fastslow[fileNum];
    Double_t w_PPO_bisMSB[fileNum];

    Double_t tauA1_error[fileNum];
    Double_t tauA2_error[fileNum];
    Double_t tauB_error[fileNum];
    Double_t w_PPO_fastslow_error[fileNum];
    Double_t w_PPO_bisMSB_error[fileNum];

    for (int i = 0; i < fileNum; i++)
    {
        tauA1[i] = ParaTransArray[3][i];
        tauA2[i] = ParaTransArray[4][i];
        tauB[i] = ParaTransArray[5][i];
        w_PPO_fastslow[i] = ParaTransArray[8][i];
        w_PPO_bisMSB[i] = ParaTransArray[9][i];

        tauA1_error[i] = ErrorTransArray[3][i];
        tauA2_error[i] = ErrorTransArray[4][i];
        tauB_error[i] = ErrorTransArray[5][i];
        w_PPO_fastslow_error[i] = ErrorTransArray[8][i];
        w_PPO_bisMSB_error[i] = ErrorTransArray[9][i];
    }
    for (int i = 0; i < fileNum; i++)
    {
        w_PPO_fastslow[i] = sin(w_PPO_fastslow[i]) * sin(w_PPO_fastslow[i]);
        w_PPO_bisMSB[i] = sin(w_PPO_bisMSB[i]) * sin(w_PPO_bisMSB[i]);
        w_PPO_fastslow_error[i] = abs(sin(2 * w_PPO_fastslow[i])) * w_PPO_fastslow_error[i];
        w_PPO_bisMSB_error[i] = abs(sin(2 * w_PPO_bisMSB[i])) * w_PPO_bisMSB_error[i];
    }

    Double_t NDFChi[fileNum] = {0};
    for (int i = 0; i < fileNum; i++)
    {
        NDFChi[i] = ParaTransArray[0][i] / ParaTransArray[1][i];
    }

    const char *parNames[] = {"chisquare", "NDF", "N", "tauA1", "tauA2", "tauB", "mean", "sigma", "theta_w_fastslow", "theta_ppo", "N_delta", "start"};

    Int_t ipar = 1;
    Double_t wavelength[fileNum];
    for (int i = 0; i < 9; i++)
    {
        wavelength[i] = 260 + i * 10;
    }
    wavelength[0] = 265;
    for (int i = 9; i < 9 + 14; i++)
    {
        wavelength[i] = 355 + (i - 9) * 10;
    }

    // //``````````````````````````````````````````````````````````````````````````````````````````````````````
    auto tc_NDFchi = new TCanvas();
    auto tg_NDFchi = new TGraphErrors(fileNum, wavelength + 9, NDFChi, nullptr, nullptr);
    tg_NDFchi->SetTitle("NDF/Chi^2; wavelength[nm]; NDF/Chi^2 ");
    tg_NDFchi->SetMarkerStyle(8);
    tg_NDFchi->GetYaxis()->SetRangeUser(0, 5);
    tg_NDFchi->Draw();
    TString savename_NDFchi = TString("ndfchi") + TString(".pdf");
    tc_NDFchi->SaveAs(savename_NDFchi);

    auto tc_tau123 = new TCanvas();
    auto tg_tauA1 = new TGraphErrors(fileNum, (wavelength + 9), tauA1, nullptr, tauA1_error);
    auto tg_tauA2 = new TGraphErrors(fileNum, (wavelength + 9), tauA2, nullptr, tauA2_error);
    auto tg_tauB = new TGraphErrors(fileNum, (wavelength + 9), tauB, nullptr, tauB_error);
    auto tg_w_PPO_fastslow = new TGraphErrors(fileNum, (wavelength + 9), w_PPO_fastslow, nullptr, w_PPO_fastslow_error);
    auto tg_w_PPO_bisMSB = new TGraphErrors(fileNum, (wavelength + 9), w_PPO_bisMSB, nullptr, w_PPO_bisMSB_error);

    tg_tauA1->SetTitle("#tau; wavelength[nm]; #tau [ns]");

    tg_tauA2->SetMarkerStyle(8);
    tg_tauB->SetMarkerStyle(34);
    //tg3->SetMarkerStyle(46);
    tg_tauA2->SetMarkerColor(kRed);
    tg_tauB->SetMarkerColor(kBlue);
    tg_tauA1->GetYaxis()->SetRangeUser(0, 5);

    tg_tauA1->Draw();
    tg_tauA2->Draw("samePE");
    tg_tauB->Draw("samePE");

    TLegend *leg_tau123 = new TLegend(0.8, 0.8, 0.95, 0.95);
    leg_tau123->AddEntry(tg_tauA1, "#tauA1");
    leg_tau123->AddEntry(tg_tauA2, "#tauA2");
    leg_tau123->AddEntry(tg_tauB, "#tauB");
    leg_tau123->Draw();
    TString savename123 = TString("tau_123") + TString(".pdf");
    tc_tau123->SaveAs(savename123);

    auto tc_w_PPO_fastslow = new TCanvas();
    tg_w_PPO_fastslow->SetTitle("w_PPO_fastslow;wavelength(nm);");
    tg_w_PPO_fastslow->Draw();

    auto tc_w_PPO_bisMSB = new TCanvas();
    tg_w_PPO_bisMSB->SetTitle("w_PPO_bisMSB;wavelength(nm);");
    tg_w_PPO_bisMSB->Draw();
}

void DrawDecayTime()
{
    // TString FileName = "LAB_265.txt";
    // TString FileName = "SLS_350.txt";
    TString FileName = "../src/datafile.txt";
    DrawDecayTime(FileName);
}
