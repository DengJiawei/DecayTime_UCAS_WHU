#include "../incl/MyFitClass.hpp"
#include "../incl/MyFitFunctions.hpp"
#include "../incl/RootFileNameClass.hpp"

#include "TGraph.h"
#include "TPave.h"

void CoutTheFitFuncResults(TF1 * func_fp)
{
    Int_t myGetNpar = func_fp->GetNpar();
    Int_t myGetNDF = func_fp->GetNDF();
    Double_t myGetChiSquare = func_fp->GetChisquare();
    const Double_t *myGetParameters = func_fp->GetParameters();
    const Double_t *myGetParErrors = func_fp->GetParErrors();
    
    cout << endl;
    cout << endl << "**********************************************************************" << endl;
    cout << func_fp->GetName() << endl;
    // cout << func_fp->GetTitle() << endl;
    cout << myGetChiSquare << "    " << myGetNDF << "     ";
    for(int i = 0; i < myGetNpar; i ++)
    {
        cout << *(myGetParameters+i) << "    " ;
    }
    cout << endl;
    cout << 0 << "    " << 0 << "    " ;
    for(int i = 0; i < myGetNpar; i ++)
    {
        cout << *(myGetParErrors+i) << "    ";
    }

    cout << endl << "**********************************************************************" << endl;
    cout << endl;
    // func_fp->Gets
}

void CoutTheTranslate_wtoN(TF1 * myfunc)
{        
    Double_t N = myfunc->GetParameter(0);
    Double_t tauA1 = myfunc->GetParameter(1);
    Double_t tauA2 = myfunc->GetParameter(2);
    Double_t tauB = myfunc->GetParameter(3);
    Double_t mean = myfunc->GetParameter(4);
    Double_t sigma = myfunc->GetParameter(5);
    Double_t w1= myfunc->GetParameter(6);
    Double_t w = myfunc->GetParameter(7);
    Double_t N_delta =myfunc->GetParameter(8);

    Double_t N_A1 = N*(  w*w1*tauA1/(tauA1-tauB) + (1-w)   );
    Double_t N_A2 = N*(  w*(1-w1)*tauA2/(tauA2-tauB) + (1-w)  );
    Double_t N_B = N*(  w*w1*(-tauB)/(tauA1-tauB) +  w*(1-w1)*(-tauB)/(tauA2-tauB) );

    cout << "N_A1  = " << N_A1 << endl; 
    cout << "N_A2  = " << N_A2 << endl; 
    cout << "N_B  = " << N_B << endl; 

}


void MyFit_FindMinimalChi2()
{
    TString parFileName = "LS_350.txt";
    TString parFileName_nolimits = "LS_350_nolimits.txt";
    RootFileNameClass Name_SLS;
    const int parNum = 12;
    int pi = 0;
    int pj = 0;
    Double_t poutMeans[30][12] = {};
    Double_t poutErrors[30][12] = {};

    Double_t poutMeans_nolimits[30][12] = {};
    Double_t poutErrors_nolimits[30][12] = {};
    int Nfile = 9 + 9;
    // for(int i = 9; i < 9+13; i++)
    MyFitClass myfitclass;

    // for (int i = 0; i < 1; i++)
    // for (int i = 0; i < 4; i++)
    int i = 8;
    {
        TString FileName = Name_SLS.FileNameSet_LS[i];
        myfitclass.SetInitInfo(FileName);
        // MyFitClass myfitclass(FileName);
        myfitclass.Set_rawHistInfo(-50, 32.839, 0.03);
        myfitclass.Set_modHistInfo(0, 12.839, 0.03);
        if (i < 9)
        {
            myfitclass.Set_Modstart(3.1e-9); //DUV
        }
        else if (i < 9 + 9)
        {
            // myfitclass.SetStartAtPeakPosi(16); //UV
            myfitclass.Set_Modstart(3.1e-9); //UV
        }
        else if (i < 9 + 13)
        {
            myfitclass.Set_Modstart(3.1e-9); //UV
        }
        // myfitclass.ReadRawDataToRawHist(FileName);
        myfitclass.ReadData_CFD10_ToHist(FileName);

        myfitclass.TheTH1D_mod_CFD10->GetXaxis()->SetTitle("time/ns");
        myfitclass.TheTH1D_mod_CFD10->GetYaxis()->SetTitle("counts");
        // auto tc_raw = new TCanvas();
        // myfitclass.TheTH1D_raw_CFD10->Draw("E");

        auto tc_mod = new TCanvas();
        // myfitclass.TheTH1D_mod_CFD10->Draw("E");
        //拟合部分
        //～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
        //1 李晓波模型
        // /*
        // TF1 *myfunc = new TF1("2exp", MyModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p10_value, -5, 20, 10);
        TF1 *myfunc = new TF1("2exp", MyModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p10, -5, 20, 10);
        // myfunc->SetParNames("N", "tauA1", "tauA2", "tauB", "mean", "sigma", "w_PPO_slowtofast", "w_PPOtobis-MSB", "N_delta", "start");
        myfunc->SetParNames("N", "tauA1", "tauA2", "tauB", "mean", "sigma", "theta_PPO_slowtofast", "theta_PPOtobis-MSB", "N_delta", "start");

        // myfunc->SetParameters(5000, 1, 10, 5.1, 0.3, 0.03, 0, 0, 0, 0);
        // myfunc->SetParameters(5000, 1.3, 10, 1.32, 0.33, 0.03, 0.1, 0.1, 0, 0);//0-6
        myfunc->SetParameters(5000, 1.3, 10, 1.32, 0.33, 0.03, 0.1, 0.1, 300, 0);//7,8
        // myfunc->SetParameters(741, 1.5, 0.1, 0.4, 0.33, 0.03, 0.1, 0.1, 10000, 0);//9,10
        // myfunc->SetParameters(741, 1.5, 00.15, 0.14, 0.33, 0.03, 0.1, 0.1, 10000, 0);//11
        myfunc->SetParLimits(0, 100, 5000);
        myfunc->SetParLimits(1, 0, 5);
        myfunc->SetParLimits(2, 0, 10);
        myfunc->SetParLimits(3, 0, 10);
        myfunc->SetParLimits(4, 0, 1);
        myfunc->SetParLimits(5, 0, 0.1);
        // myfunc->SetParLimits(6, -45, 45);
        // myfunc->SetParLimits(7, -45, 45);
        myfunc->SetParLimits(6, -15, 90);
        myfunc->SetParLimits(7, -15, 90);

        myfunc->SetParLimits(8, 1, 50000);

        // myfunc->SetParLimits(6, 1e-3, 1-1e-3);
        // myfunc->SetParLimits(7, 1e-3, 1-1e-3);



        // myfunc->FixParameter(6, 0.0);
        // myfunc->FixParameter(1, 0.5);
        myfunc->FixParameter(1, 1.5);


        myfunc->FixParameter(5, 0.03);
        // myfunc->FixParameter(8, 0.0);
        myfunc->FixParameter(9, 0.0);

        // TFitResultPtr r = myfitclass.TheTH1D_mod_CFD10->Fit("2exp","ME");
        // Int_t fitStatus = r;
        // cout << "fitStatus = " << fitStatus << endl;

        myfitclass.TheTH1D_mod_CFD10->Fit("2exp", "ME");
        myfitclass.TheTH1D_mod_CFD10->Draw("E");

        CoutTheFitFuncResults(myfunc);
        CoutTheTranslate_wtoN(myfunc);


        // */
        //～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
        // gStyle->SetOptStat("e");
        // gStyle->SetOptFit(111);
        // gStyle->SetOptStat(111111);
        // gStyle->SetOptFit(1111);

        //～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
        /* 
        TF1 *myfunc = new TF1("3exp", MyModFunc_3Expo_1Gaus_p9, -5, 20, 9);
        myfunc->SetParNames("N1", "tau1", "N2", "tau2", "N3", "tau3", "mean", "sigma", "start");

        // myfunc->SetParameters(1000, 1.4, 10, 5.1, 10, 1.5, 0.3,  0.03, 0);
        myfunc->SetParameters(-278, 0.43, 1528, 1.327, 240, 1.326, 0.45, 0.035, 0);
        // myfunc->SetParLimits(0, 100, 3000);
        myfunc->SetParLimits(1, 0.1, 5);
        // myfunc->SetParLimits(2, 1, 1000);
        myfunc->SetParLimits(3, 0.1, 10);
        // myfunc->SetParLimits(4, 1, 1000);
        myfunc->SetParLimits(5, 0.1, 10);
        // myfunc->SetParLimits(6, 0, 1);
        // myfunc->SetParLimits(7, 0, 0.1);
        myfunc->FixParameter(8, 0.0);
        // myfunc->FixParameter(0, 0.0);
        // myfunc->FixParameter(1, 1);

        myfitclass.TheTH1D_mod_CFD10->Fit("3exp", "ME");
        myfitclass.TheTH1D_mod_CFD10->Draw("E");
        */

        TPaveStats *ptstats = new TPaveStats(0.7, 0.7, 0.9, 0.9, "brNDC");
        ptstats->SetName("stats");
        ptstats->SetBorderSize(1);
        ptstats->SetFillColor(0);
        ptstats->SetTextAlign(12);
        ptstats->SetTextFont(42);
        TText *ptstats_LaTex = ptstats->AddText("");
        ptstats->SetOptStat(10);
        ptstats->SetOptFit(111);
        myfitclass.TheTH1D_mod_CFD10->GetListOfFunctions()->Add(ptstats);
        ptstats->Draw();

        TString Fitfilename = myfitclass.TheTH1D_mod_CFD10->GetTitle();
        Fitfilename += ".pdf";
        // TString Fitrootfilename = myfitclass.TheTH1D_mod_CFD10->GetTitle();
        // Fitrootfilename += ".root";
        tc_mod->SaveAs(Fitfilename);
        // tc4->SaveAs(Fitrootfilename);


        //～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～

        //     //   cout << "test TFitResultPtr" << endl;
        //     //   cout << "***************************************************************************************************************" << endl;

        //     // TFitResultPtr r = myfitclass.MyTH1D_mod_StartAtPeak->Fit("ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus","S");
        //     // r->Print("V");
        //     //   cout << endl << endl;

        //     //   cout << "***************************************************************************************************************" << endl;

        //     TString myParNames = "N,tauA1,tauA2,tauB,mean,sigma ,w1,w,N_delta ,start";
        //     Int_t myGetNpar = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetNpar();
        //     Int_t myGetNDF = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetNDF();
        //     Double_t myGetChiSquare = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetChisquare();
        //     const Double_t *myGetParameters = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetParameters();
        //     const Double_t *myGetParErrors = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetParErrors();
        //     TString outParsMeans;
        //     TString outParsErrors;

        //     poutMeans[pi][0] = myGetNDF;
        //     poutMeans[pi][1] = myGetChiSquare;
        //     poutErrors[pi][0] = 0;
        //     poutErrors[pi][1] = 0;

        //     for (pj = 2; pj < myGetNpar + 2; pj++)
        //     {
        //         poutMeans[pi][pj] = *(myGetParameters + pj - 2);
        //         poutErrors[pi][pj] = *(myGetParErrors + pj - 2);
        //     }
        //     cout << endl;

        //     for (int i = 0; i < 12; i++)
        //     {
        //         cout << poutMeans[pi][i] << "  ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < 12; i++)
        //     {
        //         cout << poutErrors[pi][i] << "  ";
        //     }
        //     cout << endl;

        //     Int_t myGetNpar_nolimits = myfunc->GetNpar();
        //     Int_t myGetNDF_nolimits = myfunc->GetNDF();
        //     Double_t myGetChiSquare_nolimits = myfunc->GetChisquare();
        //     const Double_t *myGetParameters_nolimits = myfunc->GetParameters();
        //     const Double_t *myGetParErrors_nolimits = myfunc->GetParErrors();

        //     poutMeans_nolimits[pi][0] = myGetNDF_nolimits;
        //     poutMeans_nolimits[pi][1] = myGetChiSquare_nolimits;
        //     poutErrors_nolimits[pi][0] = 0;
        //     poutErrors_nolimits[pi][1] = 0;

        //     for (pj = 2; pj < myGetNpar_nolimits + 2; pj++)
        //     {
        //         poutMeans_nolimits[pi][pj] = *(myGetParameters_nolimits + pj - 2);
        //         poutErrors_nolimits[pi][pj] = *(myGetParErrors_nolimits + pj - 2);
        //     }

        //     for (int i = 0; i < 12; i++)
        //     {
        //         cout << poutMeans_nolimits[pi][i] << "  ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < 12; i++)
        //     {
        //         cout << poutErrors_nolimits[pi][i] << "  ";
        //     }
        //     cout << endl;

        //     pi++;

        //     for (int i = 0; i < myGetNpar; i++)
        //     {
        //         outParsMeans += Form("%f, ", *(myGetParameters + i));
        //         outParsErrors += Form("%f ", *(myGetParErrors + i));
        //     }
        //     cout << myGetNpar << ", " << myGetNDF << ", " << myGetChiSquare << endl;
        //     cout << outParsMeans << endl;
        //     cout << outParsErrors << endl;
        // }
    }

    // ofstream outFile;
    // outFile.open(parFileName);

    // for (int i = 0; i < Nfile; i++)
    // {
    //     for (int j = 0; j < parNum; j++)
    //     {
    //         outFile << poutMeans[i][j] << " \t ";
    //     }
    //     outFile << endl;
    // }
    // outFile << endl
    //         << endl;

    // for (int i = 0; i < Nfile; i++)
    // {
    //     for (int j = 0; j < parNum; j++)
    //     {
    //         outFile << poutErrors[i][j] << " \t ";
    //     }
    //     outFile << endl;
    // }
    // outFile.close();

    // ofstream outFile_nolimits;
    // outFile_nolimits.open(parFileName_nolimits);

    // for (int i = 0; i < Nfile; i++)
    // {
    //     for (int j = 0; j < parNum; j++)
    //     {
    //         outFile_nolimits << poutMeans_nolimits[i][j] << " \t ";
    //     }
    //     outFile_nolimits << endl;
    // }
    // outFile_nolimits << endl
    //                  << endl;

    // for (int i = 0; i < Nfile; i++)
    // {
    //     for (int j = 0; j < parNum; j++)
    //     {
    //         outFile_nolimits << poutErrors_nolimits[i][j] << " \t ";
    //     }
    //     outFile_nolimits << endl;
    // }
    // outFile_nolimits.close();

    // cout << " poutMeans : " << endl;
    // for (int i = 0; i < Nfile; i++)
    // {
    //     for (int j = 0; j < parNum; j++)
    //     {
    //         cout << poutMeans[i][j] << ", ";
    //     }
    //     cout << endl;
    // }
    // cout << endl
    //      << endl;

    // cout << " poutErrors : " << endl;
    // for (int i = 0; i < Nfile; i++)
    // {
    //     for (int j = 0; j < parNum; j++)
    //     {
    //         cout << poutErrors[i][j] << ", ";
    //     }
    //     cout << endl;
    // }

    // cout << endl
    //      << endl;
}
