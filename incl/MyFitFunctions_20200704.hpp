// 20200601
// 将3guas的参数的3个mean变成mean加上某个差值，差值作为参数，这样方便于固定参数

// 20200602
// 将tauB改成tauA+tauBtoA,避免tauB和tauA相等的情况 
// 下午，加了个相等的判断，如果相等 让tauB增加一个值

//16:12 更正了指数卷积高斯中公式的错误，将erfc中的除以根号2写成了乘以
//20200704 将三高斯响应函数的比例固定好

//20200806 增加多指数卷积高斯的函数

#ifndef MyFitFunctions_NEW_hpp
#define MyFitFunctions_NEW_hpp

#include <iostream>
#include "TF1.h"

Double_t MyFunc_3Expo_1Gaus_p8(Double_t * x, Double_t *par);
Double_t MyModFunc_3Expo_1Gaus_p8(Double_t * x, Double_t *par);
Double_t MyFunc_4Expo_1Gaus_p10(Double_t * x, Double_t *par);
Double_t MyModFunc_4Expo_1Gaus_p10(Double_t * x, Double_t *par);

Double_t MyFunc_1Expo_1Gaus_p4(Double_t * x, Double_t *par);
Double_t MyFunc_2Expo_1Gaus_p6(Double_t * x, Double_t *par);
Double_t MyFunc_1ExpoConv1Expo_1Gaus_p5(Double_t * x, Double_t *par);
Double_t MyFunc_2ExpoConv1Expo_1Gaus_p7(Double_t * x, Double_t *par);
Double_t MyFunc_1Expo_3Gaus_p10(Double_t * x, Double_t * par);
Double_t MyFunc_2Expo_3Gaus_p12(Double_t * x, Double_t *par);
Double_t MyFunc_1ExpoConv1Expo_3Gaus_p11(Double_t * x, Double_t *par);
Double_t MyFunc_2ExpoConv1Expo_1Gaus_p13(Double_t * x, Double_t *par);

Double_t MyModFunc_1Expo_1Gaus_p5(Double_t * x, Double_t *par);
Double_t MyModFunc_2Expo_1Gaus_p7(Double_t * x, Double_t *par);
Double_t MyModFunc_1ExpoConv1Expo_1Gaus_p6(Double_t * x, Double_t *par);
Double_t MyModFunc_2ExpoConv1Expo_1Gaus_p8(Double_t * x, Double_t *par);
Double_t MyModFunc_1Expo_3Gaus_p11(Double_t * x, Double_t *par);
Double_t MyModFunc_2Expo_3Gaus_p13(Double_t * x, Double_t *par);
Double_t MyModFunc_1ExpoConv1Expo_3Gaus_p12(Double_t * x, Double_t *par);
Double_t MyModFunc_2ExpoConv1Expo_3Gaus_p14(Double_t * x, Double_t *par);

Double_t MyaddGuas_p9(Double_t * x, Double_t *par);

Double_t MyFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p8(Double_t * x, Double_t *par);
Double_t MyModFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p9(Double_t * x, Double_t *par);

Double_t MyFunc_2Expo_delta_1Gaus_p7(Double_t * x, Double_t *par);
Double_t MyModFunc_2Expo_delta_1Gaus_p8(Double_t * x, Double_t *par);

Double_t MyModFunc_1ExpoConv1Expo_1Expo_1Expo_delta_3Gaus_p9(Double_t * x, Double_t *par);

//1
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

//2
Double_t MyFunc_2Expo_1Gaus_p6(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","mean","sigma"

    Double_t t = x[0];
    Double_t N = par[0] ;
    Double_t tau1 = par[1];
    Double_t tau2 = par[2];
    Double_t w = par[3];

    Double_t mean = par[4];
    Double_t sigma = par[5];

    Double_t par1[4] = {N,tau1,mean,sigma};
    Double_t par2[4] = {N,tau2,mean,sigma};

    Double_t f = w * MyFunc_1Expo_1Gaus_p4(&t,par1) + (1-w) * MyFunc_1Expo_1Gaus_p4(&t,par2);
    return f;
}

//3
Double_t MyFunc_1ExpoConv1Expo_1Gaus_p5(Double_t * x, Double_t *par)
{
    // "N","tauA","tauB","mean","sigma"    
    Double_t t = x[0];
    Double_t N = par[0] ;
    Double_t tauA = par[1];
    Double_t tauB = par[2];
    Double_t mean = par[3];
    Double_t sigma = par[4];

    if(tauA-tauB ==0 )
    {
        tauB = tauA+1e-18;
    }
    Double_t par1[4] = {N,tauA,mean,sigma};
    Double_t par2[4] = {N,tauB,mean,sigma};

    Double_t f = 1./(tauA-tauB)*(tauA* MyFunc_1Expo_1Gaus_p4(&t,par1) - tauB*MyFunc_1Expo_1Gaus_p4(&t,par2));
    return f;
}


//4
Double_t MyFunc_2ExpoConv1Expo_1Gaus_p7(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","tauB","mean","sigma"
    Double_t t = x[0];

    Double_t N = par[0] ;
    Double_t tauA1 = par[1];
    Double_t tauA2 = par[2];
    Double_t w = par[3];
    Double_t tauB = par[4];

    Double_t mean = par[5];
    Double_t sigma = par[6];

    Double_t par1[5] = {N,tauA1,tauB,mean,sigma};
    Double_t par2[5] = {N,tauA2,tauB,mean,sigma};

    Double_t f = w* MyFunc_1ExpoConv1Expo_1Gaus_p5(&t,par1) + (1-w)*MyFunc_1ExpoConv1Expo_1Gaus_p5(&t,par2);
    return f;
}

//20200706 w1= 0.868735 w2 = 0.00622654 w3=0.0490855
// delta_2to1 = 0.24662  delta_3to1 = 0.42461  ns
// sigma1 = 26.0384  sigma2 = 55.3101 sigma3 = 40.4223 ps
//5
Double_t MyFunc_1Expo_3Gaus_p10(Double_t * x, Double_t * par)
{
    // "N","tau1","mean1","sigma1","delta_2to1","sigma2","delta_2to1","sigma3","w1","w2"
    Double_t t = x[0];

    Double_t N = par[0];
    Double_t tau1 = par[1];

    Double_t mean1 = par[2];
    Double_t sigma1 = par[3];
    Double_t delta_2to1 = par[4];
    Double_t mean2 = mean1 + delta_2to1;
    Double_t sigma2 = par[5];   
    Double_t delta_3to1 = par[6];
    Double_t mean3 = mean1+delta_3to1;
    Double_t sigma3 = par[7];

    Double_t w1 = par[8];
    Double_t w2 = par[9];
    Double_t w3 = 1 - w1 - w2;

    Double_t par1[4] = {N,tau1,mean1,sigma1};
    Double_t par2[4] = {N,tau1,mean2,sigma2};
    Double_t par3[4] = {N,tau1,mean3,sigma3};

    Double_t f = w1 *MyFunc_1Expo_1Gaus_p4(&t,par1) + w2 *MyFunc_1Expo_1Gaus_p4(&t,par2) + w3 *MyFunc_1Expo_1Gaus_p4(&t,par3);
    return f;
}

//6
Double_t MyFunc_2Expo_3Gaus_p12(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","mean1","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2"

    Double_t t = x[0];

    Double_t N = par[0] ;
    Double_t tau1 = par[1];
    Double_t tau2 = par[2];
    Double_t w_fs = par[3];

    Double_t mean1 = par[4];
    Double_t sigma1 = par[5];
    Double_t delta_2to1 = par[6];
    Double_t sigma2 = par[7];   
    Double_t delta_3to1 = par[8];
    Double_t sigma3 = par[9];
    Double_t mean2 = mean1 + delta_2to1;
    Double_t mean3 = mean1+delta_3to1;

    Double_t w1 = par[10];
    Double_t w2 = par[11];
    Double_t w3 = 1 - w1 - w2;

    Double_t par1[6] = {N,tau1,tau2,w_fs,mean1,sigma1};
    Double_t par2[6] = {N,tau1,tau2,w_fs,mean2,sigma2};
    Double_t par3[6] = {N,tau1,tau2,w_fs,mean3,sigma3};

    Double_t f = w1*MyFunc_2Expo_1Gaus_p6(&t,par1)+w2*MyFunc_2Expo_1Gaus_p6(&t,par2)+w3*MyFunc_2Expo_1Gaus_p6(&t,par3);
    return f;
}


//7
Double_t MyFunc_1ExpoConv1Expo_3Gaus_p11(Double_t * x, Double_t *par)
{
    // "N","tauA","tauB","mean1","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2"
    Double_t t = x[0];
    Double_t N = par[0] ;
    Double_t tauA = par[1];
    Double_t tauB = par[2];

    int gausi = 3;  
    Double_t gauspar[8];
    for(int i = 0; i < 8; ++i)
    {
        gauspar[i] = *(par+gausi+i);
    }
    Double_t mean1 = gauspar[0];
    Double_t sigma1 = gauspar[1];
    Double_t delta_2to1 = gauspar[2];
    Double_t sigma2 = gauspar[3];
    Double_t delta_3to1 = gauspar[4];
    Double_t sigma3 = gauspar[5];
    Double_t w1 = gauspar[6];
    Double_t w2 = gauspar[7];
    Double_t w3 = 1 - w1 - w2;

    Double_t mean2 = mean1 + delta_2to1;
    Double_t mean3 = mean1+delta_3to1;

    Double_t par1[5] = {N,tauA,tauB,mean1,sigma1};
    Double_t par2[5] = {N,tauA,tauB,mean2,sigma2};
    Double_t par3[5] = {N,tauA,tauB,mean3,sigma3};
    Double_t f = w1* MyFunc_1ExpoConv1Expo_1Gaus_p5(&t,par1) + w2* MyFunc_1ExpoConv1Expo_1Gaus_p5(&t,par2) + w3* MyFunc_1ExpoConv1Expo_1Gaus_p5(&t,par3);
    return f;
}

//8
Double_t MyFunc_2ExpoConv1Expo_1Gaus_p13(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","tauB","mean1","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2"
    Double_t t = x[0];

    Double_t N = par[0] ;
    Double_t tauA1 = par[1];
    Double_t tauA2 = par[2];
    Double_t w = par[3];
    Double_t tauB = par[4];

    int gausi = 5;  
    Double_t gauspar[8];
    for(int i = 0; i < 8; ++i)
    {
        gauspar[i] = *(par+gausi+i);
    }
    Double_t mean1 = gauspar[0];
    Double_t sigma1 = gauspar[1];
    Double_t delta_2to1 = gauspar[2];
    Double_t sigma2 = gauspar[3];
    Double_t delta_3to1 = gauspar[4];
    Double_t sigma3 = gauspar[5];
    Double_t w1 = gauspar[6];
    Double_t w2 = gauspar[7];
    Double_t w3 = 1 - w1 - w2;
    Double_t mean2 = mean1 + delta_2to1;
    Double_t mean3 = mean1+delta_3to1;

    Double_t par1[7] = {N,tauA1,tauA2,w,tauB,mean1,sigma1};
    Double_t par2[7] = {N,tauA1,tauA2,w,tauB,mean2,sigma2};
    Double_t par3[7] = {N,tauA1,tauA2,w,tauB,mean3,sigma3};
    Double_t f = w1 * MyFunc_2ExpoConv1Expo_1Gaus_p7(&t,par1) + w2 * MyFunc_2ExpoConv1Expo_1Gaus_p7(&t,par2)+ w3 * MyFunc_2ExpoConv1Expo_1Gaus_p7(&t,par3);
    return f;
}

// 2020.5.31
// 将相加改成循环

//m1
Double_t MyModFunc_1Expo_1Gaus_p5(Double_t * x, Double_t *par)
{
    // "N","tau1","mean","sigma","start"
    Double_t t = x[0];
    Double_t start = par[4];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_1Expo_1Gaus_p4(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;
}

//m2
// Int_t n = 0;
Double_t MyModFunc_2Expo_1Gaus_p7(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","mean","sigma","start"

    Double_t t = x[0];
    Double_t start = par[6];
    Double_t period = 12.839;

    Double_t tpar[20];
    Double_t fall = 0;
    for(int i = 0; i < 20; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_2Expo_1Gaus_p6(tpar+i,par);
        // cout << "fall = " << fall << endl;
    }
    // n++;
    // cout << "return once " << n <<endl;

    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}

//m3
Double_t MyModFunc_1ExpoConv1Expo_1Gaus_p6(Double_t * x, Double_t *par)
{
    // "N","tauA","tauB","mean","sigma","start"
    Double_t t = x[0];
    Double_t start = par[5];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_1ExpoConv1Expo_1Gaus_p5(tpar+i,par);
    }

    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}

//m4
Double_t MyModFunc_2ExpoConv1Expo_1Gaus_p8(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","tauB","mean","sigma","start"
    Double_t t = x[0];
    Double_t start = par[7];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_2ExpoConv1Expo_1Gaus_p7(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}

//m5
Double_t MyModFunc_1Expo_3Gaus_p11(Double_t * x, Double_t *par)
{
    // "N","tau1","mean1","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2","start"
    Double_t t = x[0];
    Double_t start = par[10];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_1Expo_3Gaus_p10(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}
//m6
Double_t MyModFunc_2Expo_3Gaus_p13(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","mean1","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2","start"
    Double_t t = x[0];
    Double_t start = par[12];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_2Expo_3Gaus_p12(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}
//m7
Double_t MyModFunc_1ExpoConv1Expo_3Gaus_p12(Double_t * x, Double_t *par)
{
    // "N","tauA","tauB","mean1","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2","start"
    Double_t t = x[0];
    Double_t start = par[11];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_1ExpoConv1Expo_3Gaus_p11(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}

//m8
Double_t MyModFunc_2ExpoConv1Expo_3Gaus_p14(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","tauB","mean1","sigma1","delta_2to1","sigma2","delta_3to1","sigma3","w1","w2","start"
    Double_t t = x[0];
    Double_t start = par[13];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_2ExpoConv1Expo_1Gaus_p13(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}


Double_t MyaddGuas_p9(Double_t * x, Double_t *par)
{
    Double_t t = x[0];
    Double_t gaus_mean = par[5];
    Double_t gaus_sigma = par[6];
    Double_t gaus_N = par[8];
    
    double f = MyModFunc_2ExpoConv1Expo_1Gaus_p8(x,par) + gaus_N*exp(-0.5*(t-gaus_mean)*(t-gaus_mean)/gaus_sigma/gaus_sigma);
    return f;
}

/*//20200603w_A,w_B,w_AB有可能出现负数的情况，更改参数，还是多变成
Double_t MyFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p8(Double_t * x, Double_t *par)
{
    // （指数卷积指数+指数+delta）卷积高斯
    // "N","tauA","tauB","mean","sigma" ,"w_AB","w_A","w_B","N_delta"   把w_B改了
    // "N","tauA","tauB","mean","sigma" ,"w_AB","w_A","N_delta"   
    Double_t t = x[0];
    Double_t N = par[0] ;
    Double_t tauA = par[1];
    Double_t tauB = par[2];
    Double_t mean = par[3];
    Double_t sigma = par[4];
    Double_t w_AB = par[5];
    Double_t w_A = par[6];
    Double_t w_B = 1 - w_AB - w_A;
    Double_t N_delta = par[7];

    if(tauA-tauB ==0 )
    {
        tauB = tauA+1e-16;
        // cout << "tauA = " << tauA << "  tauB = " << tauB << endl;
    }
    Double_t par1[4] = {N,tauA,mean,sigma};
    Double_t par2[4] = {N,tauB,mean,sigma};
    Double_t f_gaus = N_delta* exp(-0.5*(t-mean)*(t-mean)/(sigma*sigma));
    Double_t f_allexp =1/(tauA-tauB)* ( (w_AB*tauA+w_A)*MyFunc_1Expo_1Gaus_p4(&t,par1) + (w_B-w_AB*tauB)*MyFunc_1Expo_1Gaus_p4(&t,par2) );
    Double_t f = f_allexp + f_gaus;
    return f;
}
*/

// Double_t MyFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p8(Double_t * x, Double_t *par)
// {
//     // （指数卷积指数+指数+delta）卷积高斯
//     // "N","tauA","tauB","mean","sigma" ,"w_AB","w_A","w_B","N_delta"   把w_B改了
//     // "N","tauA","tauB","mean","sigma" ,"w_AB","w_A","N_delta"   
//     // "w_B","tauA","tauB","mean","sigma" ,"w_AB","w_A","N_delta"   

//     Double_t t = x[0];
//     // Double_t N = par[0] ;
//     Double_t N = 1 ;
//     Double_t tauA = par[1];
//     Double_t tauB = par[2];
//     Double_t mean = par[3];
//     Double_t sigma = par[4];
//     Double_t w_AB = par[5];
//     Double_t w_A = par[6];
//     Double_t w_B = par[0];
//     // //增加判断条件，如果放入的 w_AB w_A w_B 不在（0，1），则将函数值返回一个特别大大
//     // if(w_AB <0 || w_AB > 1 || w_A < 0 || w_A > 1 || w_AB+w_A > 1)
//     // {
//     //     return 0;
//     // }
//     Double_t N_delta = par[7];

//     if(tauA-tauB ==0 )
//     {
//         tauB = tauA+1e-16;
//         // cout << "tauA = " << tauA << "  tauB = " << tauB << endl;
//     }
//     Double_t par1[4] = {N,tauA,mean,sigma};
//     Double_t par2[4] = {N,tauB,mean,sigma};
//     Double_t f_gaus = N_delta* exp(-0.5*(t-mean)*(t-mean)/(sigma*sigma));
//     Double_t f_allexp =1/(tauA-tauB)* ( (w_AB*tauA+w_A)*MyFunc_1Expo_1Gaus_p4(&t,par1) + (w_B-w_AB*tauB)*MyFunc_1Expo_1Gaus_p4(&t,par2) );
//     Double_t f = f_allexp + f_gaus;
//     return f;
// }


Double_t MyFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p8(Double_t * x, Double_t *par)
{
    // （指数卷积指数AB+指数A+指数B+delta）卷积高斯
    // "N_A","tauA","tauB","mean","sigma" ,"N_B","N_AB","N_delta"   
    Double_t t = x[0];
    Double_t N_A = par[0];
    Double_t tauA = par[1];
    Double_t tauB = par[2];
    Double_t mean = par[3];
    Double_t sigma = par[4];
    Double_t N_B= par[5];
    Double_t N_AB = par[6];
    Double_t N_delta = par[7];
    if(tauA-tauB ==0 )
    {
        tauB = tauA+1e-18;
        // Double_t par_AB[4] = {N_A+N_B,tauA,mean,sigma};
        // Double_t f_exp_ab = MyFunc_1Expo_1Gaus_p4(&t,par_AB);
        // Double_t f_exp_a_b = N_AB*exp((mean-t)/tauA + 0.5*sigma*sigma/(tauA*tauA))* ( (tauA*(mean-t)+sigma*sigma)/tauA/tauA/tauA);
        // return (f_exp_ab + f_exp_a_b);
    }
    Double_t N_fa = N_A + N_AB*tauA/(tauA-tauB);
    Double_t N_fb = N_B - N_AB*tauB/(tauA-tauB);
    Double_t par1[4] = {N_fa,tauA,mean,sigma};
    Double_t par2[4] = {N_fb,tauB,mean,sigma};
    Double_t f_gaus = N_delta* exp(-0.5*(t-mean)*(t-mean)/(sigma*sigma));
    Double_t f_allexp = MyFunc_1Expo_1Gaus_p4(&t,par1) + MyFunc_1Expo_1Gaus_p4(&t,par2);
    Double_t f = f_allexp + f_gaus;
    return f;
}


Double_t MyModFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p9(Double_t * x, Double_t *par)
{
    //  "N_A","tauA","tauB","mean","sigma" ,"N_B","N_AB","N_delta" ,"start"  
    Double_t t = x[0];
    Double_t start = par[8];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p8(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;
}




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
    Double_t w1= sin(par[6]/TMath::Pi()*180)*sin(par[6]/TMath::Pi()*180);
    Double_t w = sin(par[7]/TMath::Pi()*180)*sin(par[7]/TMath::Pi()*180);
    // Double_t w1= par[6];
    // Double_t w = par[7];
    Double_t N_delta = par[8];

    if(tauA1-tauB ==0 )
    {
        tauB = tauA1+1e-18;
    }    
    if(tauA2-tauB ==0 )
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



Double_t MyFunc_2Expo_delta_1Gaus_p7(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","mean","sigma","N_delta"
    Double_t t = x[0];
    Double_t N = par[0] ;
    Double_t tau1 = par[1];
    Double_t tau2 = par[2];
    Double_t w = par[3];

    Double_t mean = par[4];
    Double_t sigma = par[5];
    Double_t N_delta = par[6];

    Double_t par1[4] = {N,tau1,mean,sigma};
    Double_t par2[4] = {N,tau2,mean,sigma};
    Double_t f_gaus = N_delta* exp(-0.5*(t-mean)*(t-mean)/(sigma*sigma));

    Double_t f_exp = w * MyFunc_1Expo_1Gaus_p4(&t,par1) + (1-w) * MyFunc_1Expo_1Gaus_p4(&t,par2);
    Double_t f = f_gaus + f_exp;
    return f;

}

Double_t MyModFunc_2Expo_delta_1Gaus_p8(Double_t * x, Double_t *par)
{
    // "N","tau1","tau2","w","mean","sigma","N_delta","start"
    Double_t t = x[0];
    Double_t start = par[7];
    Double_t period = 12.839;
    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_2Expo_delta_1Gaus_p7(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;
}

Double_t MyModFunc_1ExpoConv1Expo_1Expo_1Expo_delta_3Gaus_p9(Double_t * x, Double_t *par)
{
    // （指数卷积指数AB+指数A+指数B+delta）卷积高斯
    // "N_A","tauA","tauB","mean","sigma" ,"N_B","N_AB","N_delta"   
    Double_t t = x[0];
    Double_t N_A = par[0];
    Double_t tauA = par[1];
    Double_t tauB = par[2];
    Double_t mean = par[3];
    Double_t sigma = par[4];
    Double_t N_B= par[5];
    Double_t N_AB = par[6];
    Double_t N_delta = par[7];
    Double_t start = par[8];

    Double_t delta_2to1 = 0.24662 ;
    Double_t mean2 = mean + delta_2to1;
    Double_t sigma2 = 55.3101;   
    Double_t delta_3to1 = 0.42461;
    Double_t mean3 = mean+delta_3to1;
    Double_t sigma3 = 40.4223;
    // Double_t mean1 = mean;
    // Double_t sigma1 = par[3];
    //20200706 w1= 0.868735 w2 = 0.00622654 w3=0.0490855
// delta_2to1 = 0.24662  delta_3to1 = 0.42461  ns
// sigma1 = 26.0384  sigma2 = 55.3101 sigma3 = 40.4223 ps
    Double_t par1[9] = { N_A, tauA , tauB , mean , sigma  , N_B , N_AB , N_delta, start };
    Double_t par2[9] = { N_A , tauA , tauB , mean2 , sigma2  , N_B , N_AB , N_delta,start};
    Double_t par3[9] = { N_A , tauA , tauB , mean3 , sigma3  , N_B , N_AB , N_delta ,start};
    Double_t f_allexp = 0.868735*MyModFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p9(&t,par1) + 0.00622654*MyModFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p9(&t,par2)+0.0490855*MyModFunc_1ExpoConv1Expo_1Expo_1Expo_delta_1Gaus_p9(&t,par3);
    Double_t f = f_allexp;
    return f;
}




Double_t MyFunc_3Expo_1Gaus_p8(Double_t * x, Double_t *par)
{
    //"mean","sigma","N1","tau1","N2","tau2","N3","tau3"
    Double_t t = x[0];

    Double_t mean = par[0];
    Double_t sigma = par[1];
    Double_t N1 = par[2] ;
    Double_t tau1 = par[3];
    Double_t N2 = par[4] ;
    Double_t tau2= par[5];
    Double_t N3 = par[6] ;
    Double_t tau3 = par[7];


    Double_t par1[4] = {N1,tau1,mean,sigma};
    Double_t par2[4] = {N2,tau2,mean,sigma};
    Double_t par3[4] = {N3,tau3,mean,sigma};
    Double_t f = MyFunc_1Expo_1Gaus_p4(&t,par1)+ MyFunc_1Expo_1Gaus_p4(&t,par2) + MyFunc_1Expo_1Gaus_p4(&t,par3);
    return f;
}
Double_t MyModFunc_3Expo_1Gaus_p9(Double_t * x, Double_t *par)
{
    Double_t t = x[0];
    Double_t start = par[8];
    Double_t period = 12.839;

    Double_t tpar[10];
    Double_t fall = 0;
    for(int i = 0; i < 10; i ++)
    {
        tpar[i] = x[0]+ i*period;
        fall+= MyFunc_3Expo_1Gaus_p8(tpar+i,par);
    }
    Double_t f = (t> start && t < start+period)?(fall):0;
    return f;

}



#endif