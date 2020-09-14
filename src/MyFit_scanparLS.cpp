#include "../incl/MyFitClass.hpp"
#include "../incl/MyFitClass.hpp"
#include "../incl/MyFitFunctions_20200704.hpp"
#include "../incl/RootFileNameClass.hpp"

#include "TGraph.h"
#include "TPave.h"

//对于LAB在340nm一下，名称角标从0到8   调用myfitclass.ReadTheDataFile_UVlaser(); offset的初始值要更改
//LAB 0-8, StartAtPosi 从2.3ns开始


void MyFit_scanparLS()
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
    int Nfile = 9+9;
    // for(int i = 9; i < 9+13; i++)
    for(int i = 5; i < 8; i++)
    // int i = 1;
              {
                  TString FileName = Name_SLS.FileNameSet_LS[i];

                  MyFitClass myfitclass(FileName);
                  // myfitclass.SetHistInfo(-1.5,16.5,0.03);

                  // myfitclass.SetModifiedHistInfo(-0,12.839,0.03);
                  myfitclass.SetModifiedHistInfo(0,12.839,0.03);
                  if(i < 9)
                  {
                      myfitclass.SetStartAtPeakPosi(3.1); //DUV
                  }
                  else if (i < 9+9)
                  {
                      // myfitclass.SetStartAtPeakPosi(16); //UV
                      myfitclass.SetStartAtPeakPosi(3.1); //UV
                  }
                  else if (i<9+13)
                  {
                      myfitclass.SetStartAtPeakPosi(3.1); //UV
                  }

                  myfitclass.ReadTheDataFile_StartAtPeak(FileName);
                  // myfitclass.ReadTheDataFile();
                  // myfitclass.ReadTheDataFile_UVlaser();   //注意要更改

                  myfitclass.MyTH1D_mod_StartAtPeak->GetXaxis()->SetTitle("time/ns");
                  myfitclass.MyTH1D_mod_StartAtPeak->GetYaxis()->SetTitle("counts");
                  // myfitclass.MyTH1D_mod_StartAtPeak->SetTitle("LAB_265;time/ns;counts");
                  // myfitclass.MyTH1D_mod_StartAtPeak->SetAxisRange(0,12.839,"x");
                  // auto tcraw = new TCanvas();
                
                  // myfitclass.MyTH1D_raw->Draw();


                  // auto tc4 = new TCanvas();
                  {
                      TF1 * ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus = new TF1("ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus",MyModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p10,-5,20,10);
                      TF1 * myfunc = new TF1("myfunc",MyModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p10,-5,20,10);
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParNames( "N","tauA1","tauA2","tauB","mean","sigma" ,"theta1","theta","N_delta" ,"start" );
                      myfunc->SetParNames( "N","tauA1","tauA2","tauB","mean","sigma" ,"theta1","theta","N_delta" ,"start" );

                      //"N","tauA1","tauA2","tauB","mean","sigma" ,"w1","w","N_delta" ,"start" 
                      //0       1     2        3     4      5       6    7     8        9

                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(1500, 1, 50,  0., 0.01, 2.8, 0.03, 0);  //200多
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(1500, 0.75, 4.51, 0.751, 0.2, 0.03, 0.8, 0.8, 0, 0);     //350nm以上

                      if(i < 9)
                      {
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(5000, 1.501 , 6, 1.5, 0.2, 0.03, 0.98, 0.83, 0, 0);     //350nm以上
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(5000, 1.501 , 6, 1.5, 0.2, 0.03, 0.01, 0.001, 0, 0);     //350nm以上
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(7, 0, 30);

                      }
                      else if (i < 9+6)
                      {
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(5000, 1.501 , 6, 1.5, 0.2, 0.03, 0.08, 0.03, 0, 0);     //350nm以上

                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(7, 0, 1000);

                      }
                      else if (i < 9+9)
                      {
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(5000, 1.501 , 6, 1.5, 0.2, 0.03, 0.8, 0.3, 0, 0);     //350nm以上
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(7, 100, 40000);

                      }
                      else if (i<9+13)
                      {
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(5000, 1.501 , 6, 1.5, 0.2, 0.03, 0.8, 0.3, 0, 0);     //350nm以上                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(500, 0.5001, 1.5, 0.2, 0.03, 100, 500, 5000, 0);     //350nm以上
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(7, 3000, 40000);
                      }
                      // Double_t p0_start = 10;
                      // Double_t p0_end = 5000;
                      // Double_t p1_start = 0.5;
                      // Double_t p1_end = 3;
                      // Double_t p2_start = 5.01;
                      // Double_t p2_end = 100.0;
                      // Double_t p3_start = 0.51;
                      // Double_t p3_end = 3.02;
                      // Double_t p4_start = 0.;
                      // Double_t p4_end = 0.5;
                      // Double_t p0 = 1200;
                      // Double_t p1;
                      // Double_t p2;
                      // Double_t p3;
                      // Double_t p4 = 0.3;
                      // Double_t p5 = 0.03;
                      // Double_t p6 ;
                      // Double_t p7 ;
                      // Double_t p8 = 0;
                      // Double_t p9 = 0;

                      // // Double_t p5_start = 0.5;
                      // // Double_t p5_end = 0.5;
                      // Double_t p6_start = 0.;
                      // Double_t p6_end = 1.0;
                      // Double_t p7_start = 0;
                      // Double_t p7_end = 1;
                      // for(int i_1 = 1 ; i_1 < 10; i_1 ++)
                      // {
                      //   for(int i_2 = 1; i_2 < 10; i_2 ++)
                      //   {
                      //      for(int i_3 = 1; i_3 < 10; i_3 ++)
                      //      {
                      //        for(int i_6 = 1; i_6 < 10; i_6 ++)
                      //        {
                      //          for(int i_7 = 1; i_7 < 10; i_7 ++)
                      //          {
                      //            p1 = p1_start + (p1_end-p1_start)/10.*i_1;
                      //            p2 = p2_start + (p2_end-p2_start)/10.*i_2;
                      //            p3 = p3_start + (p3_end-p3_start)/10.*i_3;
                      //            p6 = p6_start + (p6_end-p6_start)/10.*i_6;
                      //            p7 = p7_start + (p7_end-p7_start)/10.*i_7;
                                 
                      // //          }
                      //        }
                      //      }
                      //   }
                      // }
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9);     //350nm以上                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParameters(500, 0.5001, 1.5, 0.2, 0.03, 100, 500, 5000, 0);     //350nm以上

                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(0,10,5000);
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(1, 0.5, 3.01);
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(2, 3.03, 100);
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(3, 0.51, 3.02);
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(4, 0.2, 0.6);

                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(6, 0., 2.0);
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetParLimits(7, 0., 2.0);

                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->FixParameter(5,0.03);
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->FixParameter(8,0);
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->FixParameter(9,0);

                      // cout << "initial values = " << endl << p0 << "  " << p1 << "  " << p2 << "  " << p3 << "  " << p4 << "  " << p5 << "  " << p6 << "  " << p7 << "  " << p8 << "  " << p9 << endl;
                        // auto tc = new TCanvas();
                      ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->SetLineWidth(5);
                      // TFitResultPtr r = myfitclass.MyTH1D_mod_StartAtPeak->Fit("ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus","MES");
                    auto tc4 = new TCanvas();

                      cout << endl << endl;
                      cout << "func pars with limits " << endl;
                      myfitclass.MyTH1D_mod_StartAtPeak->Fit("ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus","ME");

                      myfitclass.MyTH1D_mod_StartAtPeak->DrawClone("E");
                      // tc->Delete();

                      //          }
                      //        }
                      //      }
                      //   }
                      // }

                    //   myfitclass.MyTH1D_mod_StartAtPeak->DrawClone("E");
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->Draw("same");
                      // ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->Draw();

// /* 
                      auto tc_myfunc = new TCanvas();
                      myfunc->SetParameters(ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetParameters());
                    //   myfunc->SetParLimits(0,10,5000);
                    //   myfunc->SetParLimits(1, 0.5, 3.01);
                    //   myfunc->SetParLimits(2, 5.03, 10);
                    //   myfunc->SetParLimits(3, 0.51, 3.02);
                    //   myfunc->SetParLimits(4, 0, 0.5);
                    //   myfunc->SetParLimits(6, 0.7, 1.0);
                    //   myfunc->SetParLimits(6, 0., 2.0);
                    //   myfunc->SetParLimits(7, 0., 2.0);
                    //   myfunc->SetUpperLimit


                      myfunc->FixParameter(5,0.03);
                      // myfunc->FixParameter(8,0);
                      myfunc->FixParameter(9,0);
                  // auto tc4 = new TCanvas();

                      cout << endl << endl;
                      cout << "func pars with no limits " << endl;
                      myfitclass.MyTH1D_mod_StartAtPeak->Fit("myfunc","ME");
                    //   myfitclass.MyTH1D_mod_StartAtPeak->DrawClone("E");
                      myfitclass.MyTH1D_mod_StartAtPeak->DrawClone("E");
                      // myfunc->Draw("same");
// */

                    //   cout << "test TFitResultPtr" << endl;
                    //   cout << "***************************************************************************************************************" << endl;


                      // TFitResultPtr r = myfitclass.MyTH1D_mod_StartAtPeak->Fit("ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus","S");
                      // r->Print("V");
                    //   cout << endl << endl;

                    //   cout << "***************************************************************************************************************" << endl;


                      TString myParNames = "N,tauA1,tauA2,tauB,mean,sigma ,w1,w,N_delta ,start";
                      Int_t myGetNpar = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetNpar();
                      Int_t myGetNDF = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetNDF();
                      Double_t myGetChiSquare = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetChisquare();
                      const Double_t * myGetParameters = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetParameters();
                      const Double_t * myGetParErrors = ModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus->GetParErrors();
                      TString outParsMeans;
                      TString outParsErrors;

                      poutMeans[pi][0] = myGetNDF;
                      poutMeans[pi][1] = myGetChiSquare;
                      poutErrors[pi][0] = 0;
                      poutErrors[pi][1] = 0;

                      for( pj = 2; pj < myGetNpar+2; pj ++)
                      {
                        poutMeans[pi][pj] = *(myGetParameters+pj-2);
                        poutErrors[pi][pj] = *(myGetParErrors+pj-2);
                      }
                      cout << endl;

                      for(int i = 0; i < 12; i ++)
                      {
                        cout << poutMeans[pi][i] << "  ";
                      }
                      cout << endl;
                      for(int i = 0; i < 12; i ++)
                      {
                        cout << poutErrors[pi][i] << "  ";
                      }
                      cout << endl;




                      Int_t myGetNpar_nolimits = myfunc->GetNpar();
                      Int_t myGetNDF_nolimits = myfunc->GetNDF();
                      Double_t myGetChiSquare_nolimits = myfunc->GetChisquare();
                      const Double_t * myGetParameters_nolimits = myfunc->GetParameters();
                      const Double_t * myGetParErrors_nolimits = myfunc->GetParErrors();


                      poutMeans_nolimits[pi][0] = myGetNDF_nolimits;
                      poutMeans_nolimits[pi][1] = myGetChiSquare_nolimits;
                      poutErrors_nolimits[pi][0] = 0;
                      poutErrors_nolimits[pi][1] = 0;

                      for( pj = 2; pj < myGetNpar_nolimits+2; pj ++)
                      {
                        poutMeans_nolimits[pi][pj] = *(myGetParameters_nolimits+pj-2);
                        poutErrors_nolimits[pi][pj] = *(myGetParErrors_nolimits+pj-2);
                      }


                      for(int i = 0; i < 12; i ++)
                      {
                        cout << poutMeans_nolimits[pi][i] << "  ";
                      }
                      cout << endl;
                      for(int i = 0; i < 12; i ++)
                      {
                        cout << poutErrors_nolimits[pi][i] << "  ";
                      }
                      cout << endl;


                      pi++;

                      for(int i = 0; i < myGetNpar; i ++)
                      {
                        outParsMeans += Form("%f, ", *(myGetParameters+i));
                        outParsErrors+= Form("%f ", *(myGetParErrors+i));
                      }
                      cout << myGetNpar << ", " <<  myGetNDF << ", " << myGetChiSquare << endl;
                      cout << outParsMeans << endl;
                      cout << outParsErrors << endl;





                  }
                  // TPaveStats *ptstats = new TPaveStats(0.7,0.7,0.9,0.9,"brNDC");
                  // ptstats->SetName("stats");
                  // ptstats->SetBorderSize(1);
                  // ptstats->SetFillColor(0);
                  // ptstats->SetTextAlign(12);
                  // ptstats->SetTextFont(42);
                  // TText *ptstats_LaTex = ptstats->AddText("");
                  // ptstats->SetOptStat(10);
                  // ptstats->SetOptFit(111);
                  // myfitclass.MyTH1D_mod_StartAtPeak->GetListOfFunctions()->Add(ptstats);
                  // ptstats->Draw();
                  // TString Fitfilename = myfitclass.MyTH1D_mod_StartAtPeak->GetTitle();
                  // Fitfilename += ".pdf";
                  // TString Fitrootfilename = myfitclass.MyTH1D_mod_StartAtPeak->GetTitle();
                  // Fitrootfilename += ".root";
                  // tc4->SaveAs(Fitfilename);
                  // tc4->SaveAs(Fitrootfilename);
              }
    
    ofstream outFile;
    outFile.open(parFileName);

    for(int i = 0; i < Nfile; i ++)
    {
      for(int j = 0; j < parNum; j ++)
      {
        outFile << poutMeans[i][j] << " \t ";
      }
      outFile << endl;
    }
    outFile << endl << endl;

    for(int i = 0; i < Nfile; i ++)
    {
      for(int j = 0; j < parNum; j ++)
      {
        outFile << poutErrors[i][j] << " \t ";
      }
      outFile << endl;
    }
    outFile.close();


    ofstream outFile_nolimits;
    outFile_nolimits.open(parFileName_nolimits);

    for(int i = 0; i < Nfile; i ++)
    {
      for(int j = 0; j < parNum; j ++)
      {
        outFile_nolimits << poutMeans_nolimits[i][j] << " \t ";
      }
      outFile_nolimits << endl;
    }
    outFile_nolimits << endl << endl;

    for(int i = 0; i < Nfile; i ++)
    {
      for(int j = 0; j < parNum; j ++)
      {
        outFile_nolimits << poutErrors_nolimits[i][j] << " \t ";
      }
      outFile_nolimits << endl;
    }
    outFile_nolimits.close();
























    cout << " poutMeans : "  << endl;
    for(int i = 0; i < Nfile; i ++)
    {
      for(int j = 0; j < parNum; j ++)
      {
        cout << poutMeans[i][j] << ", ";
      }
      cout << endl;
    }
    cout << endl << endl;

    cout << " poutErrors : "  << endl;
    for(int i = 0; i < Nfile; i ++)
    {
      for(int j = 0; j < parNum; j ++)
      {
        cout << poutErrors[i][j] << ", ";
      }
      cout << endl;
    }

    cout << endl << endl;




    // int i = 3 ;
    // TString FileName = Name_LAB.FileNameSet_LAB[7];
    // for(int i = 0; i < 5; i++)
    // for(int i = 5; i < 9; i++)
    // for(int i = 9; i < 13; i++)
    // int i = 0;

     // 1 单指数卷积单高斯
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              /*
              {
                  TString FileName = Name_LAB.FileNameSet_LAB[i];

                  MyFitClass myfitclass(FileName);
                  myfitclass.SetHistInfo(-1.5,16.5,0.03);
                  myfitclass.ReadTheDataFile();
                  // myfitclass.ReadTheDataFile_UVlaser();   //注意要更改
                  myfitclass.MyTH1D_mod->GetXaxis()->SetTitle("time/ns");
                  myfitclass.MyTH1D_mod->GetYaxis()->SetTitle("counts");
                  // myfitclass.MyTH1D_mod->SetTitle("LAB_265;time/ns;counts");
                  // myfitclass.MyTH1D_mod->SetAxisRange(-1,15,"x");

                  auto tc4 = new TCanvas();
                  {
                  TF1 * ModFunc_1exp_1gaus = new TF1("ModFunc_1exp_1gaus",MyModFunc_1Expo_1Gaus_p5,-5,20,5);
                  ModFunc_1exp_1gaus->SetParNames("N","tau1","offset","sigma","start");
                  // ModFunc_1exp_1gaus->SetParameters(600, 50, 2.2, 0.03, 0);
                  ModFunc_1exp_1gaus->SetParameters(600, 25, 2.2, 0.03, 0);
                  ModFunc_1exp_1gaus->FixParameter(3, 0.03);
                  ModFunc_1exp_1gaus->FixParameter(4, 0.0);

                  ModFunc_1exp_1gaus->SetParLimits(2, 2, 4);
                  ModFunc_1exp_1gaus->SetParLimits(0, 1000, 2500);
                  // ModFunc_1exp_1gaus->SetParLimits(1, 0.2, 20);  //320以上
                  // ModFunc_1exp_1gaus->SetParLimits(1, 0.2, 200);
                  ModFunc_1exp_1gaus->SetParLimits(1, 10, 50);

                  ModFunc_1exp_1gaus->SetLineWidth(5);
                  ModFunc_1exp_1gaus->SetLineColor(kGreen);
                  myfitclass.MyTH1D_mod->Fit("ModFunc_1exp_1gaus","ME");
                  myfitclass.MyTH1D_mod->Draw("E");
                  ModFunc_1exp_1gaus->Draw("same");
                  }

                  TPaveStats *ptstats = new TPaveStats(0.7,0.7,0.9,0.9,"brNDC");
                  ptstats->SetName("stats");
                  ptstats->SetBorderSize(1);
                  ptstats->SetFillColor(0);
                  ptstats->SetTextAlign(12);
                  ptstats->SetTextFont(42);
                  TText *ptstats_LaTex = ptstats->AddText("");
                  ptstats->SetOptStat(10);
                  ptstats->SetOptFit(111);
                  myfitclass.MyTH1D_mod->GetListOfFunctions()->Add(ptstats);
                  ptstats->Draw();
                  TString Fitfilename = myfitclass.MyTH1D_mod->GetTitle();
                  Fitfilename += ".pdf";
                  TString Fitrootfilename = myfitclass.MyTH1D_mod->GetTitle();
                  Fitrootfilename += ".root";
                  tc4->SaveAs(Fitfilename);
                  tc4->SaveAs(Fitrootfilename);
              }
              */
        // 2 单指数卷积三高斯
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /*
        {
            TString FileName = Name_LAB.FileNameSet_LAB[i];

            MyFitClass myfitclass(FileName);
            myfitclass.SetHistInfo(-1.5,16.5,0.03);
            // myfitclass.ReadTheDataFile();
            myfitclass.ReadTheDataFile_UVlaser();   //注意要更改
            myfitclass.MyTH1D_mod->GetXaxis()->SetTitle("time/ns");
            myfitclass.MyTH1D_mod->GetYaxis()->SetTitle("counts");
            // myfitclass.MyTH1D_mod->SetTitle("LAB_265;time/ns;counts");
            // myfitclass.MyTH1D_mod->SetAxisRange(-1,15,"x");

            auto tc4 = new TCanvas();
            {
            TF1 * ModFunc_1exp_3gaus = new TF1("ModFunc_1exp_3gaus",MyModFunc_1Expo_3Gaus_p11,-5,20,11);
            ModFunc_1exp_3gaus->SetParNames("N","tau1","offset","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2","start");
            //"N","tau1","offset","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2","start"
            // 0    1     2        3          4           5       6            7        8    9   10
            // ModFunc_1exp_3gaus->SetParameters(600, 50, 2.2, 0.03, 0);
            //20200706 w1= 0.868735 w2 = 0.0622654 w3=0.0490855
            // delta_2to1 = 0.24662  delta_3to1 = 0.42461  ns
            // sigma1 = 26.0384  sigma2 = 55.3101 sigma3 = 40.4223 ps
            //5
            // ModFunc_1exp_3gaus->SetParameters(600, 25, 2.7 );
            ModFunc_1exp_3gaus->SetParameters(600, 25, 4.3 );  //350以上将 offset更改为4.3

            ModFunc_1exp_3gaus->FixParameter(3, 0.0260384);
            // ModFunc_1exp_3gaus->FixParameter(3, 0.03);
            ModFunc_1exp_3gaus->FixParameter(4, 0.24662);
            ModFunc_1exp_3gaus->FixParameter(5, 0.0553101);
            ModFunc_1exp_3gaus->FixParameter(6, 0.42461);
            ModFunc_1exp_3gaus->FixParameter(7, 0.0404223);
            ModFunc_1exp_3gaus->FixParameter(8, 0.868735);
            // ModFunc_1exp_3gaus->FixParameter(8, 1);
            ModFunc_1exp_3gaus->FixParameter(9, 0.0622654);
            // ModFunc_1exp_3gaus->FixParameter(9, 0.);
            ModFunc_1exp_3gaus->FixParameter(10, 0.);

            ModFunc_1exp_3gaus->SetParLimits(0, 10, 2500);
            ModFunc_1exp_3gaus->SetParLimits(1, 0.001, 5);  //320以上
            // ModFunc_1exp_3gaus->SetParLimits(1, 10, 200);
            // ModFunc_1exp_3gaus->SetParLimits(2, 2, 4);
            ModFunc_1exp_3gaus->SetParLimits(2, 4, 5);

            ModFunc_1exp_3gaus->SetLineWidth(5);
            myfitclass.MyTH1D_mod->Fit("ModFunc_1exp_3gaus","ME"); 
            myfitclass.MyTH1D_mod->Draw("E");
            // ModFunc_1exp_3gaus->Draw("same");
            // ModFunc_1exp_3gaus->Draw();
            }

            TPaveStats *ptstats = new TPaveStats(0.7,0.7,0.9,0.9,"brNDC");
            ptstats->SetName("stats");
            ptstats->SetBorderSize(1);
            ptstats->SetFillColor(0);
            ptstats->SetTextAlign(12);
            ptstats->SetTextFont(42);
            TText *ptstats_LaTex = ptstats->AddText("");
            ptstats->SetOptStat(10);
            ptstats->SetOptFit(111);
            myfitclass.MyTH1D_mod->GetListOfFunctions()->Add(ptstats);
            ptstats->Draw();
            TString Fitfilename = myfitclass.MyTH1D_mod->GetTitle();
            Fitfilename += ".pdf";
            TString Fitrootfilename = myfitclass.MyTH1D_mod->GetTitle();
            Fitrootfilename += ".root";
            tc4->SaveAs(Fitfilename);
            tc4->SaveAs(Fitrootfilename);
        }
        */

      //3 双指数卷积单高斯  (指数+指数)*高斯
              /* 
              {
                  TString FileName = Name_LAB.FileNameSet_LAB[i];

                  MyFitClass myfitclass(FileName);
                  myfitclass.SetHistInfo(-1.5,16.5,0.03);

                  // myfitclass.ReadTheDataFile();
                  myfitclass.ReadTheDataFile_UVlaser();   //注意要更改

                  myfitclass.MyTH1D_mod->GetXaxis()->SetTitle("time/ns");
                  myfitclass.MyTH1D_mod->GetYaxis()->SetTitle("counts");
                  // myfitclass.MyTH1D_mod->SetTitle("LAB_265;time/ns;counts");
                  // myfitclass.MyTH1D_mod->SetAxisRange(-1,15,"x");

                  auto tc4 = new TCanvas();
                  {
                      TF1 * ModFunc_fastslow_gaus = new TF1("ModFunc_fastslow_gaus",MyModFunc_2Expo_delta_1Gaus_p8,-5,20,8);
                      ModFunc_fastslow_gaus->SetParNames("N","tau1","tau2","w","offset","sigma","N_delta","start");
                      //"N","tau1","tau2","w","offset","sigma","N_delta","start"
                      // 0    1       2    3    4         5     6         7
                      ModFunc_fastslow_gaus->SetParameters(600, 2, 40, 0.95, 2.3, 0.03, 0., 0.);

                      // "N","tau1","tau2","w","mean","sigma","N_delta","start"
                      // 0     1      2     3    4       5       6        7
                      ModFunc_fastslow_gaus->SetParLimits(0,100,4000);

                      // ModFunc_fastslow_gaus->SetParLimits(1,0.00001,200);
                      // ModFunc_fastslow_gaus->SetParLimits(2, 0.00001, 200);
                      // ModFunc_fastslow_gaus->SetParLimits(4, 2.2, 3);

                      ModFunc_fastslow_gaus->SetParLimits(1,0.00001,20);
                      ModFunc_fastslow_gaus->SetParLimits(2, 0.00001, 1);
                      ModFunc_fastslow_gaus->SetParLimits(4, 4, 5);
                      ModFunc_fastslow_gaus->SetParLimits(3, -1e-9, 1.000001);

                      // ModFunc_fastslow_gaus->FixParameter(2,30);
                      // ModFunc_fastslow_gaus->FixParameter(3,1);
                      ModFunc_fastslow_gaus->FixParameter(5,0.03);
                      ModFunc_fastslow_gaus->FixParameter(6,0)
                      ModFunc_fastslow_gaus->FixParameter(7,0);

                      ModFunc_fastslow_gaus->SetLineWidth(5);
                      myfitclass.MyTH1D_mod->Fit("ModFunc_fastslow_gaus","ME");
                      myfitclass.MyTH1D_mod->Draw("E");
                      // ModFunc_fastslow_gaus->Draw("same");
                  }
                  TPaveStats *ptstats = new TPaveStats(0.7,0.7,0.9,0.9,"brNDC");
                  ptstats->SetName("stats");
                  ptstats->SetBorderSize(1);
                  ptstats->SetFillColor(0);
                  ptstats->SetTextAlign(12);
                  ptstats->SetTextFont(42);
                  TText *ptstats_LaTex = ptstats->AddText("");
                  ptstats->SetOptStat(10);
                  ptstats->SetOptFit(111);
                  myfitclass.MyTH1D_mod->GetListOfFunctions()->Add(ptstats);
                  ptstats->Draw();
                  TString Fitfilename = myfitclass.MyTH1D_mod->GetTitle();
                  Fitfilename += ".pdf";
                  TString Fitrootfilename = myfitclass.MyTH1D_mod->GetTitle();
                  Fitrootfilename += ".root";
                  tc4->SaveAs(Fitfilename);
                  tc4->SaveAs(Fitrootfilename);
              }
              */
              //5 指数卷积指数 卷积高斯
              // int i = 4;
              /*
              {
                  TString FileName = Name_LAB.FileNameSet_LAB[i];

                  MyFitClass myfitclass(FileName);
                  myfitclass.SetHistInfo(-1.5,16.5,0.03);

                  myfitclass.ReadTheDataFile();
                  // myfitclass.ReadTheDataFile_UVlaser();   //注意要更改

                  myfitclass.MyTH1D_mod->GetXaxis()->SetTitle("time/ns");
                  myfitclass.MyTH1D_mod->GetYaxis()->SetTitle("counts");
                  // myfitclass.MyTH1D_mod->SetTitle("LAB_265;time/ns;counts");
                  // myfitclass.MyTH1D_mod->SetAxisRange(-1,15,"x");

                  auto tc4 = new TCanvas();
                  {
                      TF1 * ModFunc_1ExpoConv1Expo_1gaus = new TF1("ModFunc_1ExpoConv1Expo_1gaus",MyModFunc_1ExpoConv1Expo_1Gaus_p6,-5,20,6);
                      ModFunc_1ExpoConv1Expo_1gaus->SetParNames("N","tauA","tauB","offset","sigma","start");

                      // "N","tauA","tauB","offset","sigma","start"
                      // 0    1       2      3      4         5  
                      ModFunc_1ExpoConv1Expo_1gaus->SetParameters(1500, 0.2, 1,  2.3, 0.03, 0.);

                      // ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(0,100,4000);
                      ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(0,100,4000);

                      // ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(1,0.00001,200);
                      // ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(2, 0.00001, 200);
                      // ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(4, 2.2, 3);

                      // ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(1, 0.01,0.05);
                      ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(1, 0.01, 0.05);
                      // ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(2, 0.00001, 1);
                      ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(2, 0.01, 50);
                      ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(3, 2.2, 3);
                      // ModFunc_1ExpoConv1Expo_1gaus->SetParLimits(3, 4, 5);

                      // ModFunc_1ExpoConv1Expo_1gaus->FixParameter(2,30);
                      // ModFunc_1ExpoConv1Expo_1gaus->FixParameter(3,1);
                      ModFunc_1ExpoConv1Expo_1gaus->FixParameter(4,0.03);
                      ModFunc_1ExpoConv1Expo_1gaus->FixParameter(5,0);

                      ModFunc_1ExpoConv1Expo_1gaus->SetLineWidth(5);
                      myfitclass.MyTH1D_mod->Fit("ModFunc_1ExpoConv1Expo_1gaus","ME");
                      myfitclass.MyTH1D_mod->Draw("E");
                      // ModFunc_1ExpoConv1Expo_1gaus->Draw("same");
                  }
                  TPaveStats *ptstats = new TPaveStats(0.7,0.7,0.9,0.9,"brNDC");
                  ptstats->SetName("stats");
                  ptstats->SetBorderSize(1);
                  ptstats->SetFillColor(0);
                  ptstats->SetTextAlign(12);
                  ptstats->SetTextFont(42);
                  TText *ptstats_LaTex = ptstats->AddText("");
                  ptstats->SetOptStat(10);
                  ptstats->SetOptFit(111);
                  myfitclass.MyTH1D_mod->GetListOfFunctions()->Add(ptstats);
                  ptstats->Draw();
                  TString Fitfilename = myfitclass.MyTH1D_mod->GetTitle();
                  Fitfilename += ".pdf";
                  TString Fitrootfilename = myfitclass.MyTH1D_mod->GetTitle();
                  Fitrootfilename += ".root";
                  tc4->SaveAs(Fitfilename);
                  tc4->SaveAs(Fitrootfilename);
              }
               */

//(rise time乘以双指数 )卷积高斯
              // int i  = 13;
                  // for(int i = 0; i < 5; i++)
    // for(int i = 5; i < 9; i++)
    // for(int i = 9; i < 13; i++)
    // int i = 0;
              // {
              //     TString FileName = Name_LAB.FileNameSet_LAB[i];

              //     MyFitClass myfitclass(FileName);
              //     myfitclass.SetHistInfo(-1.5,16.5,0.03);

              //     // myfitclass.ReadTheDataFile();
              //     myfitclass.ReadTheDataFile_UVlaser();   //注意要更改

              //     myfitclass.MyTH1D_mod->GetXaxis()->SetTitle("time/ns");
              //     myfitclass.MyTH1D_mod->GetYaxis()->SetTitle("counts");
              //     // myfitclass.MyTH1D_mod->SetTitle("LAB_265;time/ns;counts");
              //     // myfitclass.MyTH1D_mod->SetAxisRange(-1,15,"x");

              //     auto tc4 = new TCanvas();
              //     {
              //         TF1 * ModFunc_2ExpoConv1Expo_1gaus = new TF1("ModFunc_2ExpoConv1Expo_1gaus",MyModFunc_2ExpoConv1Expo_1Gaus_p8,-5,20,8);
              //         ModFunc_2ExpoConv1Expo_1gaus->SetParNames("N","tau1","tau2","w","tauB","offset","sigma","start");

              //         //"N","tau1","tau2","w","tauB","offset","sigma","start"
              //         // 0    1       2   3      4     5       6       7
              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParameters(1500, 1, 50,  0., 0.01, 2.8, 0.03, 0);  //200多
              //         ModFunc_2ExpoConv1Expo_1gaus->SetParameters(1500, 0.1, 20,  0.99, 0.01, 4.2, 0.03, 0);     //350nm以上

              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(0,100,4000);
              //         ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(0,100,5000);
                      
              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(1, 0.01,0.05);
              //         ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(1, 0.007, 1);
              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(2, 0.00001, 1);
              //         ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(2, 1,60);
              //         ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(3, 0, 1);
              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(3, 0, 1.000000);
              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(4, 0.005, 1);
              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(5, 2.2, 3.);


              //         //350nm以上
              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(1,0.00001,200);
              //         // ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(2, 0.00001, 200);
              //         ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(4, 0.008, 0.1);

              //         ModFunc_2ExpoConv1Expo_1gaus->SetParLimits(5, 4, 5);

              //         ModFunc_2ExpoConv1Expo_1gaus->FixParameter(6,0.03);
              //         ModFunc_2ExpoConv1Expo_1gaus->FixParameter(7,0);

              //         ModFunc_2ExpoConv1Expo_1gaus->SetLineWidth(5);
              //         myfitclass.MyTH1D_mod->Fit("ModFunc_2ExpoConv1Expo_1gaus","ME");
              //         myfitclass.MyTH1D_mod->Draw("E");
              //         // ModFunc_2ExpoConv1Expo_1gaus->Draw("same");
              //     }
              //     TPaveStats *ptstats = new TPaveStats(0.7,0.7,0.9,0.9,"brNDC");
              //     ptstats->SetName("stats");
              //     ptstats->SetBorderSize(1);
              //     ptstats->SetFillColor(0);
              //     ptstats->SetTextAlign(12);
              //     ptstats->SetTextFont(42);
              //     TText *ptstats_LaTex = ptstats->AddText("");
              //     ptstats->SetOptStat(10);
              //     ptstats->SetOptFit(111);
              //     myfitclass.MyTH1D_mod->GetListOfFunctions()->Add(ptstats);
              //     ptstats->Draw();
              //     TString Fitfilename = myfitclass.MyTH1D_mod->GetTitle();
              //     Fitfilename += ".pdf";
              //     TString Fitrootfilename = myfitclass.MyTH1D_mod->GetTitle();
              //     Fitrootfilename += ".root";
              //     tc4->SaveAs(Fitfilename);
              //     tc4->SaveAs(Fitrootfilename);
              // }


  //（risetime乘以双指数 + delta）卷积高斯

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // LAB_270 280 290 300 单指数单高斯
/*
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    auto tc4 = new TCanvas();
    TF1 * ModFunc_fastslow_gaus = new TF1("ModFunc_fastslow_gaus",MyModFunc_2Expo_delta_1Gaus_p8,-5,20,8);
    ModFunc_fastslow_gaus->SetParNames("N","tau1","tau2","w","offset","sigma","N_delta","start");
    ModFunc_fastslow_gaus->SetParameters(600, 2, 40, 0.95, 2.3, 0.03, 0.1, 0);

    // "N","tau1","tau2","w","mean","sigma","N_delta","start"
    // 0     1      2     3    4       5       6        7
    ModFunc_fastslow_gaus->SetParLimits(2, 10, 50);
    ModFunc_fastslow_gaus->SetParLimits(0,100,4000);
    ModFunc_fastslow_gaus->SetParLimits(1,10,60);
  
    ModFunc_fastslow_gaus->SetParLimits(4, 2.2, 2.7);
    ModFunc_fastslow_gaus->SetParLimits(4, 2.2, 4);
    ModFunc_fastslow_gaus->FixParameter(2,30);
    ModFunc_fastslow_gaus->FixParameter(5,0.03);
    ModFunc_fastslow_gaus->FixParameter(6,0);
    ModFunc_fastslow_gaus->FixParameter(7,0);
    ModFunc_fastslow_gaus->FixParameter(3,1);

    ModFunc_fastslow_gaus->SetLineWidth(5);
    myfitclass.MyTH1D_mod->Fit("ModFunc_fastslow_gaus","ME");
    myfitclass.MyTH1D_mod->Draw("E");
    // ModFunc_fastslow_gaus->Draw("same");

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
  //LAB 310,320,330,340 两个指数相加卷积1高斯
/* 
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    auto tc4 = new TCanvas();
    TF1 * ModFunc_fastslow_gaus = new TF1("ModFunc_fastslow_gaus",MyModFunc_2Expo_delta_1Gaus_p8,-5,20,8);
    ModFunc_fastslow_gaus->SetParNames("N","tau1","tau2","w","offset","sigma","N_delta","start");
    ModFunc_fastslow_gaus->SetParameters(600, 2, 80, 0.95, 2.3, 0.03, 0.1, 0);

    // "N","tau1","tau2","w","mean","sigma","N_delta","start"
    // 0     1      2     3    4       5       6        7
    ModFunc_fastslow_gaus->SetParLimits(0,100,4000);
    ModFunc_fastslow_gaus->SetParLimits(1,0.5,10);

    ModFunc_fastslow_gaus->SetParLimits(2, 70, 120);

    ModFunc_fastslow_gaus->SetParLimits(3,0.001,0.9999);
    ModFunc_fastslow_gaus->SetParLimits(4, 2.2, 2.7);
    // ModFunc_fastslow_gaus->SetParLimits(4, 2.2, 4);
    // ModFunc_fastslow_gaus->FixParameter(2,30);

    ModFunc_fastslow_gaus->FixParameter(5,0.03);
    ModFunc_fastslow_gaus->FixParameter(6,0);
    ModFunc_fastslow_gaus->FixParameter(7,0);
    // ModFunc_fastslow_gaus->FixParameter(3,1);

    ModFunc_fastslow_gaus->SetLineWidth(5);
    myfitclass.MyTH1D_mod->Fit("ModFunc_fastslow_gaus","ME");
    myfitclass.MyTH1D_mod->Draw("E");
    // ModFunc_fastslow_gaus->Draw("same");

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // auto tc4 = new TCanvas();
    // TF1 * ModFunc_fastslow_gaus = new TF1("ModFunc_fastslow_gaus",MyModFunc_2Expo_delta_1Gaus_p8,-5,20,8);
    // ModFunc_fastslow_gaus->SetParNames("N","tau1","tau2","w","offset","sigma","N_delta","start");
    // ModFunc_fastslow_gaus->SetParameters(600, 2, 80, 0.95, 2.3, 0.03, 0.1, 0);

    // // "N","tau1","tau2","w","mean","sigma","N_delta","start"
    // // 0     1      2     3    4       5       6        7
    // ModFunc_fastslow_gaus->SetParLimits(0,100,4000);
    // ModFunc_fastslow_gaus->SetParLimits(1,0.5,10);

    // ModFunc_fastslow_gaus->SetParLimits(2, 70, 120);

    // ModFunc_fastslow_gaus->SetParLimits(3,0.001,0.9999);
    // ModFunc_fastslow_gaus->SetParLimits(4, 2.2, 2.7);
    // // ModFunc_fastslow_gaus->SetParLimits(4, 2.2, 4);
    // // ModFunc_fastslow_gaus->FixParameter(2,30);

    // ModFunc_fastslow_gaus->FixParameter(5,0.03);
    // ModFunc_fastslow_gaus->FixParameter(6,0);
    // ModFunc_fastslow_gaus->FixParameter(7,0);
    // // ModFunc_fastslow_gaus->FixParameter(3,1);

    // ModFunc_fastslow_gaus->SetLineWidth(5);
    // myfitclass.MyTH1D_mod->Fit("ModFunc_fastslow_gaus","ME");
    // myfitclass.MyTH1D_mod->Draw("E");
    // // ModFunc_fastslow_gaus->Draw("same");

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



}
