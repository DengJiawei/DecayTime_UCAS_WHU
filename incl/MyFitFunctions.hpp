
#ifndef MyFitFunctions_hpp
#define MyFitFunctions_hpp

#include <iostream>
#include "TF1.h"

//数学方面的函数形式
//仪器响应函数为单高斯
Double_t MyFunc_1Expo_1Gaus_p4(Double_t * x, Double_t *par);
Double_t MyFunc_2Expo_1Gaus_p6(Double_t * x, Double_t *par);
Double_t MyFunc_3Expo_1Gaus_p8(Double_t * x, Double_t *par);
// Double_t MyFunc_4Expo_1Gaus_p10(Double_t * x, Double_t *par);//暂时忽略这个模型

Double_t MyFunc_2Expo_delta_1Gaus_p7(Double_t * x, Double_t *par);
Double_t MyFunc_3Expo_delta_1Gaus_p9(Double_t * x, Double_t *par);

//物理模型
Double_t MyFunc_1ExpoConv1Expo_1Gaus_p5(Double_t * x, Double_t *par);
Double_t MyFunc_2ExpoConv1Expo_1Gaus_p7(Double_t * x, Double_t *par);

//PPO(1) + bis-MSB(1) + PPO(1)->bis-MSB(1) + Rayleigh
Double_t MyFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p8(Double_t * x, Double_t *par);

//PPO(2)  + PPO(2)->bis-MSB(1) + Rayleigh (LXB)
Double_t MyFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p9(Double_t * x, Double_t *par);

//仪器响应函数为三高斯
Double_t MyFunc_1Expo_3Gaus_p10(Double_t * x, Double_t * par);
Double_t MyFunc_2Expo_3Gaus_p12(Double_t * x, Double_t *par);

//以上函数取模
Double_t MyModFunc_1Expo_1Gaus_p5(Double_t * x, Double_t *par);
Double_t MyModFunc_2Expo_1Gaus_p7(Double_t * x, Double_t *par);
Double_t MyModFunc_3Expo_1Gaus_p9(Double_t * x, Double_t *par);
// Double_t MyModFunc_4Expo_1Gaus_p11(Double_t * x, Double_t *par);//暂时忽略这个模型

Double_t MyModFunc_2Expo_delta_1Gaus_p8(Double_t * x, Double_t *par);
Double_t MyModFunc_3Expo_delta_1Gaus_p10(Double_t * x, Double_t *par);
Double_t MyModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p10(Double_t * x, Double_t *par);


//函数具体实现形式
//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～

Double_t MyFunc_1Expo_1Gaus_p4(Double_t * x, Double_t *par)
{
    // "N","tau1","mean","sigma"
    Double_t t = x[0];
    Double_t N = par[0];
    Double_t tau1 = par[1];

    Double_t mean = par[2];
    Double_t sigma = par[3];  //假定大于0，在表达式中消去根号里的项
    Double_t f = N* 0.5/tau1 * exp((mean-t)/tau1 + 0.5*sigma*sigma/(tau1*tau1)) * erfc(0.5*sqrt(2.0)*((mean-t)/sigma+sigma/tau1));
   
    return f;
}

Double_t MyModFunc_1Expo_1Gaus_p5(Double_t * x, Double_t *par)
{
    // "N","tau1","mean","sigma","start"
    Double_t t = x[0];
    Double_t start = par[4];
    Double_t period = 12.839;
    Double_t tpar[20];
    Double_t fall = 0;
    for(int i = 0; i < 20; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_1Expo_1Gaus_p4(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;
}

//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
Double_t MyFunc_2Expo_1Gaus_p6(Double_t * x, Double_t *par)
{
    // "N1","tau1","N2","tau2","mean","sigma"
    Double_t t = x[0];
    Double_t N1 = par[0] ;
    Double_t tau1 = par[1];
    Double_t N2 = par[2];
    Double_t tau2 = par[3];
    Double_t mean = par[4];
    Double_t sigma = par[5];

    Double_t par1[4] = {N1,tau1,mean,sigma};
    Double_t par2[4] = {N2,tau2,mean,sigma};

    Double_t f =  MyFunc_1Expo_1Gaus_p4(&t,par1) + MyFunc_1Expo_1Gaus_p4(&t,par2);
    return f;
}

Double_t MyModFunc_2Expo_1Gaus_p7(Double_t * x, Double_t *par)
{
    // "N1","tau1","N2","tau2","mean","sigma","start"
    Double_t t = x[0];
    Double_t start = par[6];
    Double_t period = 12.839;

    Double_t tpar[20];
    Double_t fall = 0;
    for(int i = 0; i < 20; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_2Expo_1Gaus_p6(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}

//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～

Double_t MyFunc_3Expo_1Gaus_p8(Double_t * x, Double_t *par)
{
    // "N1","tau1","N2","tau2","N3","tau3","mean","sigma"
    Double_t t = x[0];
    Double_t N1 = par[0] ;
    Double_t tau1 = par[1];
    Double_t N2 = par[2];
    Double_t tau2 = par[3];
    Double_t N3 = par[4];
    Double_t tau3 = par[5];
    Double_t mean = par[6];
    Double_t sigma = par[7];

    Double_t par1[4] = {N1,tau1,mean,sigma};
    Double_t par2[4] = {N2,tau2,mean,sigma};
    Double_t par3[4] = {N3,tau3,mean,sigma};

    Double_t f =  MyFunc_1Expo_1Gaus_p4(&t,par1) + MyFunc_1Expo_1Gaus_p4(&t,par2) +  MyFunc_1Expo_1Gaus_p4(&t,par3);
    return f;
}

Double_t MyModFunc_3Expo_1Gaus_p9(Double_t * x, Double_t *par)
{
    //  "N1","tau1","N2","tau2","N3","tau3","mean","sigma","start"
    Double_t t = x[0];
    Double_t start = par[8];
    Double_t period = 12.839;

    Double_t tpar[20];
    Double_t fall = 0;
    for(int i = 0; i < 20; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_3Expo_1Gaus_p8(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}

//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～

Double_t MyFunc_2Expo_delta_1Gaus_p7(Double_t * x, Double_t *par)
{
    // "N1","tau1","N2","tau2","mean","sigma","N_delta"
    Double_t t = x[0];
    Double_t N1 = par[0] ;
    Double_t tau1 = par[1];
    Double_t N2 = par[2];
    Double_t tau2 = par[3];
    Double_t mean = par[4];
    Double_t sigma = par[5];
    Double_t N_delta = par[6];

    Double_t f_gaus = N_delta* exp(-0.5*(t-mean)*(t-mean)/(sigma*sigma));
    Double_t par1[6] = {N1,tau1,N2,tau2,mean,sigma};
    Double_t f_2expo = MyFunc_2Expo_1Gaus_p6(&t,par1);
    Double_t f = f_gaus + f_2expo;
    return f;
}

Double_t MyModFunc_2Expo_delta_1Gaus_p8(Double_t * x, Double_t *par)
{
    // "N1","tau1","N2","tau2","mean","sigma","N_delta","start"
    Double_t t = x[0];
    Double_t start = par[7];
    Double_t period = 12.839;

    Double_t tpar[20];
    Double_t fall = 0;
    for(int i = 0; i < 20; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_2Expo_delta_1Gaus_p7(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}


//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～

Double_t MyFunc_3Expo_delta_1Gaus_p9(Double_t * x, Double_t *par)
{
    // "N1","tau1","N2","tau2","N3","tau3","mean","sigma","N_delta"
    Double_t t = x[0];
    Double_t N1 = par[0] ;
    Double_t tau1 = par[1];
    Double_t N2 = par[2];
    Double_t tau2 = par[3];
    Double_t N3 = par[4];
    Double_t tau3 = par[5];
    Double_t mean = par[6];
    Double_t sigma = par[7];
    Double_t N_delta = par[8];

    Double_t par1[8] = {N1,tau1,N2,tau2,N3,tau3,mean,sigma};

    Double_t f_gaus = N_delta* exp(-0.5*(t-mean)*(t-mean)/(sigma*sigma));
    Double_t f_3expo = MyFunc_3Expo_1Gaus_p8(&t,par1);
    Double_t f = f_gaus + f_3expo;
    return f;
}

Double_t MyModFunc_3Expo_delta_1Gaus_p10(Double_t * x, Double_t *par)
{
    // "N1","tau1","N2","tau2","N3","tau3","mean","sigma","N_delta","start"
    Double_t t = x[0];
    Double_t start = par[9];
    Double_t period = 12.839;

    Double_t tpar[20];
    Double_t fall = 0;
    for(int i = 0; i < 20; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_3Expo_delta_1Gaus_p9(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;
}

//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～

//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～

Double_t MyFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p9(Double_t * x, Double_t *par)
{
    // （ w两个指数卷积指数+这两个指数(比例用12,参数为w1）+delta）卷积高斯
    // w( w1* nexpA1 + (1-w1) nexpA2 )卷积 nexpB + (1-w)*nexpB
    // "N","tauA1","tauA2","tauB","mean","sigma" ,"w1","w","N_delta"   
    Double_t t = x[0];
    Double_t N = par[0];
    Double_t tauA1 = par[1];
    Double_t tauA2 = par[2];
    Double_t tauB = par[3];
    Double_t mean = par[4];
    Double_t sigma = par[5];
    Double_t w1= sin(par[6]*TMath::Pi()/180)*sin(par[6]*TMath::Pi()/180);
    Double_t w = sin(par[7]*TMath::Pi()/180)*sin(par[7]*TMath::Pi()/180);
    // Double_t w1= par[6];
    // Double_t w = par[7];
    Double_t N_delta = par[8];

    if( abs(tauA1-tauB) < 1e-18 )
    {
        tauB = tauA1+1e-18;
    }    
    if(abs(tauA2-tauB) < 1e-18 )
    {
        tauB = tauA2+1e-18;
    }

    Double_t N_A1 = N*(  w*w1*tauA1/(tauA1-tauB) + (1-w)   );
    Double_t N_A2 = N*(  w*(1-w1)*tauA2/(tauA2-tauB) + (1-w)  );

    Double_t N_B = N*(  w*w1*(-tauB)/(tauA1-tauB) +  w*(1-w1)*(-tauB)/(tauA2-tauB) );

    Double_t par1[4] = {N_A1,tauA1,mean,sigma};
    Double_t par2[4] = {N_A2,tauA2,mean,sigma};
    Double_t par3[4] = {N_B,tauB,mean,sigma};
    Double_t f_gaus = N_delta* exp(-0.5*(t-mean)*(t-mean)/(sigma*sigma));
    Double_t f_allexp = MyFunc_1Expo_1Gaus_p4(&t,par1) + MyFunc_1Expo_1Gaus_p4(&t,par2) + MyFunc_1Expo_1Gaus_p4(&t,par3) ;
    Double_t f = f_allexp + f_gaus;
    return f;
}


Double_t MyModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p10(Double_t * x, Double_t *par)
{
    // "N","tauA1","tauA2","tauB","mean","sigma" ,"w1","w","N_delta" ,"start" 

    Double_t t = x[0];
    Double_t start = par[9];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t f_all = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        f_all+= MyFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p9(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(f_all):0;
    return f;
}




Double_t MyFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p9_value(Double_t * x, Double_t *par)
{
    // （ w两个指数卷积指数+这两个指数(比例用12,参数为w1）+delta）卷积高斯
    // w( w1* nexpA1 + (1-w1) nexpA2 )卷积 nexpB + (1-w)*nexpB
    // "N","tauA1","tauA2","tauB","mean","sigma" ,"w1","w","N_delta"   
    Double_t t = x[0];
    Double_t N = par[0];
    Double_t tauA1 = par[1];
    Double_t tauA2 = par[2];
    Double_t tauB = par[3];
    Double_t mean = par[4];
    Double_t sigma = par[5];
    Double_t w1= par[6];
    Double_t w = par[7];
    Double_t N_delta = par[8];

    if(abs(tauA1-tauB) < 1e-18 )
    {
        tauB = tauA1+1e-18;
    }    
    if(abs(tauA2-tauB) < 1e-18)
    {
        tauB = tauA2+1e-18;
    }

    Double_t N_A1 = N*(  w*w1*tauA1/(tauA1-tauB) + (1-w)   );
    Double_t N_A2 = N*(  w*(1-w1)*tauA2/(tauA2-tauB) + (1-w)  );

    Double_t N_B = N*(  w*w1*(-tauB)/(tauA1-tauB) +  w*(1-w1)*(-tauB)/(tauA2-tauB) );

    Double_t par1[4] = {N_A1,tauA1,mean,sigma};
    Double_t par2[4] = {N_A2,tauA2,mean,sigma};
    Double_t par3[4] = {N_B,tauB,mean,sigma};
    Double_t f_gaus = N_delta* exp(-0.5*(t-mean)*(t-mean)/(sigma*sigma));
    Double_t f_allexp = MyFunc_1Expo_1Gaus_p4(&t,par1) + MyFunc_1Expo_1Gaus_p4(&t,par2) + MyFunc_1Expo_1Gaus_p4(&t,par3) ;
    Double_t f = f_allexp + f_gaus;
    return f;
}


Double_t MyModFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p10_value(Double_t * x, Double_t *par)
{
    // "N","tauA1","tauA2","tauB","mean","sigma" ,"w1","w","N_delta" ,"start" 

    Double_t t = x[0];
    Double_t start = par[9];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t f_all = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        f_all+= MyFunc_2ExpoConv1Expo_2Expo_delta_1Gaus_p9_value(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(f_all):0;
    return f;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




#endif
