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
    }

    for (int i = 0; i < fileNum; i++)
    {
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
        cout << endl;
    }

    for (int i = 0; i < fileNum; i++)
    {
        for (int j = 0; j < parNum; j++)
        {
            cout << ErrorArray[i][j] << "   ";
        }
        cout << endl;
    }

    Double_t *N_A = ParaTransArray[2];
    Double_t *N_B = ParaTransArray[7];
    Double_t *N_AB = ParaTransArray[8];
    Double_t *errN_A = ErrorTransArray[2];
    Double_t *errN_B = ErrorTransArray[7];
    Double_t *errN_AB = ErrorTransArray[8];

    // Double_t N_A[fileNum] = {0};
    // Double_t N_B[fileNum]= {0};
    // Double_t N_AB[fileNum] = {0};
    // Double_t errN_A[fileNum] = {0};
    // Double_t errN_B[fileNum]= {0};
    // Double_t errN_AB[fileNum] = {0};

    Double_t w_A[fileNum] = {0};
    Double_t w_B[fileNum] = {0};
    Double_t w_AB[fileNum] = {0};
    Double_t errw_A[fileNum] = {0};
    Double_t errw_B[fileNum] = {0};
    Double_t errw_AB[fileNum] = {0};

    Double_t NDFChi[fileNum] = {0};

    for (int i = 0; i < fileNum; i++)
    {
        w_A[i] = N_A[i] / (N_A[i] + N_B[i] + N_AB[i]);
        w_B[i] = N_B[i] / (N_A[i] + N_B[i] + N_AB[i]);
        w_AB[i] = N_AB[i] / (N_A[i] + N_B[i] + N_AB[i]);

        errw_A[i] = sqrt((N_B[i] + N_AB[i]) * (N_B[i] + N_AB[i]) * errN_A[i] * errN_A[i] + N_A[i] * N_A[i] * (errN_B[i] * errN_B[i] + errN_AB[i] * errN_AB[i])) / (N_A[i] + N_B[i] + N_AB[i]) / (N_A[i] + N_B[i] + N_AB[i]);
        errw_B[i] = sqrt((N_A[i] + N_AB[i]) * (N_A[i] + N_AB[i]) * errN_B[i] * errN_B[i] + N_B[i] * N_B[i] * (errN_A[i] * errN_A[i] + errN_AB[i] * errN_AB[i])) / (N_A[i] + N_B[i] + N_AB[i]) / (N_A[i] + N_B[i] + N_AB[i]);
        errw_AB[i] = sqrt((N_A[i] + N_B[i]) * (N_B[i] + N_A[i]) * errN_AB[i] * errN_AB[i] + N_AB[i] * N_AB[i] * (errN_A[i] * errN_A[i] + errN_B[i] * errN_B[i])) / (N_A[i] + N_B[i] + N_AB[i]) / (N_A[i] + N_B[i] + N_AB[i]);

        // errw_A[i] = sqrt( (N_B+N_AB)*(N_B+N_AB)*errN_A*errN_A + N_A*N_A*(errN_B*errN_B+errN_AB*errN_AB) )/(N_A+N_B+N_AB)/(N_A+N_B+N_AB);
        // errw_B[i] = sqrt( (N_A+N_AB)*(N_A+N_AB)*errN_B*errN_B + N_B*N_B*(errN_A*errN_A+errN_AB*errN_AB) )/(N_A+N_B+N_AB)/(N_A+N_B+N_AB);
        // errw_AB[i] = sqrt( (N_A+N_B)*(N_B+N_A)*errN_AB*errN_AB + N_AB*N_AB*(errN_A*errN_A+errN_B*errN_B) )/(N_A+N_B+N_AB)/(N_A+N_B+N_AB);
        NDFChi[i] = ParaTransArray[1][i] / ParaTransArray[0][i];
    }

    // "N","tauA1","tauA2","tauB","mean","sigma" ,"w1","w","N_delta" ,"start"
    // 0     1        2      3      4       5       6   7    8           9

    // "N_A","tauA","tauB","mean","sigma" ,"N_B","N_AB","N_delta" ,"start"
    // 0       1      2      3      4       5       6          7      8
    const char *parNames[] = {"NDF", "chisquare", "N", "tauA1", "tauA2", "tauB", "mean", "sigma", "w1", "w", "N_delta", "start"};

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

    // // /*
    //     // auto tg = new TGraphErrors(fileNum,wavelength,ParaTransArray[ipar],nullptr,ErrorTransArray[ipar]);
    //    auto tc = new TCanvas();
    //     auto tg = new TGraphErrors(fileNum,wavelength,w_A,nullptr,errw_A);
    //     auto tg2 = new TGraphErrors(fileNum,wavelength,w_B,nullptr,errw_B);
    //     auto tg3 = new TGraphErrors(fileNum,wavelength,w_AB,nullptr,errw_AB);
    //     tg->SetTitle("; wavelength[nm]; ");

    //     tg->SetMarkerStyle(8);
    //     tg2->SetMarkerStyle(34);
    //     tg3->SetMarkerStyle(46);
    //     tg2->SetMarkerColor(kRed);
    //     tg3->SetMarkerColor(kBlue);
    //     // tg->GetYaxis()->SetRangeUser(0,2);

    //     tg->Draw();
    //     tg2->Draw("samePE");
    //     tg3->Draw("samePE");

    //    TLegend *leg = new TLegend(0.8, 0.8, 0.95, 0.95);
    //    leg->AddEntry(tg,"w_A");
    //    leg->AddEntry(tg2,"w_B");
    //    leg->AddEntry(tg3,"w_AB");
    //    leg->Draw();
    //     // TString savename = TString(parNames[ipar]) + TString(".pdf");
    //     TString savename_www = TString("www") + TString(".pdf");
    //     tc->SaveAs(savename_www);
    // // */
    //     auto tc_tau = new TCanvas();
    //     auto tg_tau = new TGraphErrors(fileNum,wavelength,ParaTransArray[3],nullptr,ErrorTransArray[3]);
    //     auto tg2_tau = new TGraphErrors(fileNum,wavelength,ParaTransArray[4],nullptr,ErrorTransArray[4]);
    // //     auto tg3 = new TGraphErrors(fileNum,wavelength,ParaTransArray[ipar],nullptr,ErrorTransArray[ipar]);

    //     tg_tau->SetTitle("#tau; wavelength[nm]; #tau [ns]");

    //     // tg_tau->SetTitle("#tau_{unknow}; wavelength[nm]; #tau [ns]");
    //     // tg2_tau->SetTitle("#tau_{LAB}; wavelength[nm]; #tau [ns]");

    //     tg_tau->SetMarkerStyle(8);
    //     tg2_tau->SetMarkerStyle(34);
    // //     tg3->SetMarkerStyle(46);
    //     tg2_tau->SetMarkerColor(kRed);
    //     // tg3->SetMarkerColor(kBlue);
    //     tg_tau->GetYaxis()->SetRangeUser(0,4);

    //     // tg2_tau->Draw();
    //     tg_tau->Draw();
    //     tg2_tau->Draw("samePE");

    //     // tg2->Draw("samePE");
    // //     // tg3->Draw("samePE");

    //    TLegend *leg_tau = new TLegend(0.8, 0.8, 0.95, 0.95);
    //    leg_tau->AddEntry(tg,"#tau_PPO");
    //    leg_tau->AddEntry(tg2,"#tau_bis-MSB");
    // //    leg->AddEntry(tg3,"w_AB");
    //    leg_tau->Draw();
    // //     // TString savename = TString(parNames[ipar]) + TString(".pdf");
    //     TString savename = TString("tau_unknow") + TString(".pdf");
    //     tc_tau->SaveAs(savename);

    //     auto tc_tauLAB = new TCanvas();
    //     auto tg2_tauLAB = new TGraphErrors(fileNum,wavelength,ParaTransArray[4],nullptr,ErrorTransArray[4]);
    // //     auto tg3 = new TGraphErrors(fileNum,wavelength,ParaTransArray[ipar],nullptr,ErrorTransArray[ipar]);

    //     tg2_tauLAB->SetTitle("#tau_{LAB}; wavelength[nm]; #tau [ns]");

    //     tg2_tauLAB->SetMarkerStyle(8);
    // //     tg3->SetMarkerStyle(46);
    //     tg2_tauLAB->SetMarkerColor(kRed);
    //     // tg3->SetMarkerColor(kBlue);
    //     // tg2_tau->GetYaxis()->SetRangeUser(0,80);

    //     // tg2_tau->Draw();
    //     tg2_tauLAB->Draw();
    //     TString savenameLAB = TString("tau_LAB") + TString(".pdf");
    //     tc_tauLAB->SaveAs(savenameLAB);

    // //``````````````````````````````````````````````````````````````````````````````````````````````````````
    auto tc_NDFchi = new TCanvas();
    auto tg_NDFchi = new TGraphErrors(fileNum, wavelength, NDFChi, nullptr, nullptr);

    tg_NDFchi->SetTitle("NDF/Chi^2; wavelength[nm]; NDF/Chi^2 ");

    tg_NDFchi->SetMarkerStyle(8);
    tg_NDFchi->GetYaxis()->SetRangeUser(0, 3);

    tg_NDFchi->Draw();
    //    TLegend *leg = new TLegend(0.8, 0.8, 0.95, 0.95);
    //    leg->AddEntry(tg,"#tau_A");
    //    leg->AddEntry(tg2,"#tau_B");
    //    leg->Draw();
    //     // TString savename = TString(parNames[ipar]) + TString(".pdf");
    TString savename_NDFchi = TString("ndfchi") + TString(".pdf");
    tc_NDFchi->SaveAs(savename_NDFchi);

    // // /*
    //     // auto tg = new TGraphErrors(fileNum,wavelength,ParaTransArray[ipar],nullptr,ErrorTransArray[ipar]);
    //     auto tc_w = new TCanvas();
    //     auto tg_w = new TGraphErrors(fileNum,wavelength,ParaTransArray[5],nullptr,ErrorTransArray[5]);
    //     tg_w->SetTitle(" #omega; wavelength[nm]; ");
    //     // tg_w->SetTitle(" #omega; wavelength[nm]; ");

    //     tg_w->SetMarkerStyle(34);
    //     tg_w->SetMarkerColor(kBlue);
    //     // tg->GetYaxis()->SetRangeUser(0,2);

    //     tg_w->Draw();

    // //    TLegend *leg = new TLegend(0.8, 0.8, 0.95, 0.95);
    // //    leg->AddEntry(tg,"w_A");
    // //    leg->AddEntry(tg2,"w_B");
    // //    leg->AddEntry(tg3,"w_AB");
    // //    leg->Draw();
    // //     // TString savename = TString(parNames[ipar]) + TString(".pdf");
    //     TString savename_w = TString("w") + TString(".pdf");
    //     tc_w->SaveAs(savename_w);
    // // */

    auto tc_tau123 = new TCanvas();
    auto tg_tau1 = new TGraphErrors(fileNum, (wavelength+9), ParaTransArray[5], nullptr, ErrorTransArray[5]);
    auto tg_tau2 = new TGraphErrors(fileNum, (wavelength+9), ParaTransArray[7], nullptr, ErrorTransArray[7]);
    auto tg_tau3 = new TGraphErrors(fileNum, (wavelength+9), ParaTransArray[9], nullptr, ErrorTransArray[9]);
    //     auto tg3 = new TGraphErrors(fileNum,wavelength,ParaTransArray[ipar],nullptr,ErrorTransArray[ipar]);

    tg_tau1->SetTitle("#tau; wavelength[nm]; #tau [ns]");

    // tg_tau->SetTitle("#tau_{unknow}; wavelength[nm]; #tau [ns]");
    // tg2_tau->SetTitle("#tau_{LAB}; wavelength[nm]; #tau [ns]");

    tg_tau2->SetMarkerStyle(8);
    tg_tau3->SetMarkerStyle(34);
    //     tg3->SetMarkerStyle(46);
    tg_tau2->SetMarkerColor(kRed);
    tg_tau3->SetMarkerColor(kBlue);
    // tg3->SetMarkerColor(kBlue);
    tg_tau1->GetYaxis()->SetRangeUser(0, 5);

    // tg2_tau->Draw();
    tg_tau1->Draw();
    // tg_tau2->Draw("samePE");
    tg_tau3->Draw("samePE");

    // tg2->Draw("samePE");
    //     // tg3->Draw("samePE");

    TLegend *leg_tau123 = new TLegend(0.8, 0.8, 0.95, 0.95);
    leg_tau123->AddEntry(tg_tau1, "#tau1");
    //    leg_tau123->AddEntry(tg_tau2,"#tau2");
    leg_tau123->AddEntry(tg_tau3, "#tau3");
    //    leg->AddEntry(tg3,"w_AB");
    leg_tau123->Draw();
    //     // TString savename = TString(parNames[ipar]) + TString(".pdf");
    TString savename123 = TString("tau_123") + TString(".pdf");
    tc_tau123->SaveAs(savename123);

    auto tc_N123 = new TCanvas();
    auto tg_N1 = new TGraphErrors(fileNum, wavelength, ParaTransArray[4], nullptr, ErrorTransArray[4]);
    auto tg_N2 = new TGraphErrors(fileNum, wavelength, ParaTransArray[6], nullptr, ErrorTransArray[6]);
    auto tg_N3 = new TGraphErrors(fileNum, wavelength, ParaTransArray[8], nullptr, ErrorTransArray[8]);
    //     auto tg3 = new TGraphErrors(fileNum,wavelength,ParaTransArray[ipar],nullptr,ErrorTransArray[ipar]);

    tg_N1->SetTitle("#N; wavelength[nm]; ");

    // tg_N->SetTitle("#N_{unknow}; wavelength[nm]; #N [ns]");
    // tg2_N->SetTitle("#N_{LAB}; wavelength[nm]; #N [ns]");

    tg_N2->SetMarkerStyle(8);
    tg_N3->SetMarkerStyle(34);
    //     tg3->SetMarkerStyle(46);
    tg_N2->SetMarkerColor(kRed);
    tg_N3->SetMarkerColor(kBlue);
    // tg3->SetMarkerColor(kBlue);
    tg_N1->GetYaxis()->SetRangeUser(-1500, 3000);

    // tg2_N->Draw();
    tg_N1->Draw();
    // tg_N2->Draw("samePE");
    // tg_N3->Draw("samePE");
    tg_N3->Draw("samePE");

    // tg2->Draw("samePE");
    //     // tg3->Draw("samePE");

    TLegend *leg_N123 = new TLegend(0.8, 0.8, 0.95, 0.95);
    leg_N123->AddEntry(tg_N1, "#N1");
    //    leg_N123->AddEntry(tg_N2,"#N2");
    leg_N123->AddEntry(tg_N3, "#N3");
    //    leg->AddEntry(tg3,"w_AB");
    leg_N123->Draw();
    //     // TString savename = TString(parNames[ipar]) + TString(".pdf");
    TString savenameN123 = TString("N_123") + TString(".pdf");
    tc_N123->SaveAs(savenameN123);
}

void DrawDecayTime()
{
    // TString FileName = "LAB_265.txt";
    TString FileName = "SLS_350.txt";
    DrawDecayTime(FileName);
}
