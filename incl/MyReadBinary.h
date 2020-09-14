#ifndef MyReadBinary_h
#define MyReadBinary_h
//读取二进制文件，确定点的个数 int pointNum ，两个点的时间间隔 double xInc，起始时间 double xOrg
// double [] Time, Volts1, Volts2 为数据数组
//2020.5.20 将#pragma pack(4)变成#pragma pack（push,4) and #pragma pack(pop)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <TString.h>

using namespace std;

#pragma pack(push,4)
// #define MAX_LENGTH 10000000
#define MAX_LENGTH 1200000
#define DATE_TIME_STRING_LENGTH 16
#define FRAME_STRING_LENGTH 24
#define SIGNAL_STRING_LENGTH 16

typedef struct
{
    char Cookie[2];
    char Version[2];
    int FileSize;
    int NumberOfWaveforms;
} FileHeader; //2,2,4,4

void showFileHeader(FileHeader fileHeader);

// const char COOKIE[2] = {'A', 'G'};
// const char VERSION[2] = {'1', '0'};

typedef struct
{
    int HeaderSize;
    int WaveformType;
    int NWaveformBuffers;
    int Points;
    int Count;
    float XDisplayRange;
    double XDisplayOrigin;
    double XIncrement;
    double XOrigin;
    int XUnits;
    int YUnits;
    char Date[DATE_TIME_STRING_LENGTH];
    char Time[DATE_TIME_STRING_LENGTH];
    char Frame[FRAME_STRING_LENGTH];
    char WaveformLabel[SIGNAL_STRING_LENGTH];
    double TimeTag;
    unsigned int SegmentIndex;
} WaveformHeader;

void showWaveformHeader(WaveformHeader waveformHeader);

typedef struct
{
    int HeaderSize;
    short BufferType;
    short BytesPerPoint;
    int BufferSize;
} WaveformDataHeader;

void showWaveformDataHeader(WaveformDataHeader waveformDataHeader);


/* Globals */
extern double xOrg;
extern double xInc ; /* Values necessary to create time data */
extern double Time[MAX_LENGTH];  //arrays to store data in a binary file
extern float Volts[MAX_LENGTH];
extern float Volts1[MAX_LENGTH];
extern float Volts2[MAX_LENGTH];

extern ifstream inFile; // define readfile stream

extern int pointNum; //文件记录数据点的个数 the quantity of data point

bool MyReadBinary_2chan(TString InputFileName); 
bool MyReadBinary_1chan(TString InputFileName);
void ShowBinaryInfo(TString InputFileName);

#pragma pack(pop)
#endif