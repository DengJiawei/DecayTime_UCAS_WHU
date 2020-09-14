// 本程序是用来将csv文件转化为bin文件
// 思路是将csv文件按照先前写的程序读取进来，然后将其得到的信息用二进制文件保存。
// 邓佳维 2020.9.3

#include <iostream>
#include "../incl/MyReadBinary.h"
#include "../incl/MyDataAnalysisClass.hpp"
#include "TH1.h"

// auto th = new TH1D("","",100,0,10);
// th->GetRandom();

//1 读取文件
void Trans_csvtobin()
{
    MyDataAnalysisClass myclass;

    TString FileName;
    myclass.ReadOneFile(FileName);

    TString binFileName;
    ofstream outFile(outFile,ios::out | ios::binary);
    if(!outFile)
    {
        cout << "cannot open file " << endl;
    }

    Double_t t;
    Double_t v0;
    Double_t v1;

    for(int i = 0 ; i < myclass.FileMaxColumn; i ++)
    {
        w = myclass.rawdata_channel_t[i];
        v0 = myclass.rawdata_channel_0[i];
        v1 = myclass.rawdata_channel_1[i];
        outFilee.write((char*)&w, sizeof(w));
        outFilee.write((char*)&v0, sizeof(v0));
        outFilee.write((char*)&v1, sizeof(v1));
    }
    outFile.close();

}


//2 保存文件



