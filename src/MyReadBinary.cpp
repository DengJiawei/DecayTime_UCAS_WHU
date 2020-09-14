#ifndef MyReadBinary_cpp
#define MyReadBinary_cpp

#include "MyReadBinary.h"

/* Globals */
double xOrg = 0L;
double xInc = 0L; /* Values necessary to create time data */
double Time[MAX_LENGTH];  //arrays to store data in a binary file
float Volts[MAX_LENGTH];
float Volts1[MAX_LENGTH];
float Volts2[MAX_LENGTH];

ifstream inFile; // define readfile stream

int pointNum = 0; //文件记录数据点的个数 the quantity of data point


void showFileHeader(FileHeader fileHeader)
{
    //cout << "sizeof(fileHeader.Cookie) = " << sizeof(fileHeader.Cookie) << endl;
    cout << "Cookie = " << fileHeader.Cookie << endl;
    // cout << "sizeof(fileHeader.Cookie) = " << sizeof(fileHeader.Cookie) << endl;
    cout << "Version = " << fileHeader.Version << endl;
    // cout << "sizeof(fileHeader.Version) = " << sizeof(fileHeader.Version) << endl;
    cout << "FileSize = " << fileHeader.FileSize << endl;
    // cout << "sizeof(fileHeader.FileSize) = " << sizeof(fileHeader.FileSize) << endl;
    cout << "NumberOfWaveforms = " << fileHeader.NumberOfWaveforms << endl;
    // cout << "sizeof(fileHeader.NumberOfWaveforms) = " << sizeof(fileHeader.NumberOfWaveforms) << endl;

    // cout << "sizeof(fileHeader) = " << sizeof(fileHeader) << endl;
}

void showWaveformHeader(WaveformHeader waveformHeader)
{
    // cout << "HeaderSize = " << sizeof(waveformHeader.HeaderSize) << endl;
    // cout << "waveformtype = " << sizeof(waveformHeader.WaveformType) << endl;
    // cout << "NWaveformBuffers = " << sizeof(waveformHeader.NWaveformBuffers) << endl;
    // cout << "Points " << sizeof(waveformHeader.Points) << endl;
    // cout << "Count = " << sizeof(waveformHeader.Count) << endl;
    // cout << "XDisplayRange = " << sizeof(waveformHeader.XDisplayRange) << endl;
    // cout << "XDisplayOrigin = " << sizeof(waveformHeader.XDisplayOrigin) << endl;
    // cout << "XIncrement = " << sizeof(waveformHeader.XIncrement) << endl;
    // cout << "XOrigin = " << sizeof(waveformHeader.XOrigin) << endl;
    // cout << "XUnits = " << sizeof(waveformHeader.XUnits) << endl;
    // cout << "YUnits = " << sizeof(waveformHeader.YUnits) << endl;
    // cout << "Data = " << sizeof(waveformHeader.Date) << endl;
    // cout << "Time = " << sizeof(waveformHeader.Time) << endl;
    // cout << "Fream = " << sizeof(waveformHeader.Frame) << endl;
    // cout << "WaveformLabel = " << sizeof(waveformHeader.WaveformLabel) << endl;
    // cout << "TimeTag = " << sizeof(waveformHeader.TimeTag) << endl;
    // cout << "SegmentIndex = " << sizeof(waveformHeader.SegmentIndex) << endl;
    // cout << "sizoof(waveformHeader) = " << sizeof(waveformHeader) << endl;
    // cout << endl
    //      << endl;

    cout << "HeaderSize = " << waveformHeader.HeaderSize << endl;
    cout << "waveformtype = " << waveformHeader.WaveformType << endl;
    cout << "NWaveformBuffers = " << waveformHeader.NWaveformBuffers << endl;
    cout << "Points " << waveformHeader.Points << endl;
    cout << "Count = " << waveformHeader.Count << endl;
    cout << "XDisplayRange = " << waveformHeader.XDisplayRange << endl;
    cout << "XDisplayOrigin = " << waveformHeader.XDisplayOrigin << endl;
    cout << "XIncrement = " << waveformHeader.XIncrement << endl;
    cout << "XOrigin = " << waveformHeader.XOrigin << endl;
    cout << "XUnits = " << waveformHeader.XUnits << endl;
    cout << "YUnits = " << waveformHeader.YUnits << endl;
    cout << "Data = " << waveformHeader.Date << endl;
    cout << "Time = " << waveformHeader.Time << endl;
    cout << "Fream = " << waveformHeader.Frame << endl;
    cout << "WaveformLabel = " << waveformHeader.WaveformLabel << endl;
    cout << "TimeTag = " << waveformHeader.TimeTag << endl;
    cout << "SegmentIndex = " << waveformHeader.SegmentIndex << endl;
}

void showWaveformDataHeader(WaveformDataHeader waveformDataHeader)
{
    cout << "HeaderSize = " << waveformDataHeader.HeaderSize << endl;
    cout << "BufferType = " << waveformDataHeader.BufferType << endl;
    cout << "BytesPerPoint = " << waveformDataHeader.BytesPerPoint << endl;
    cout << "BufferSize = " << waveformDataHeader.BufferSize << endl;
}

bool MyReadBinary_2chan(TString InputFileName)
{

    FileHeader fileHeader;
    WaveformHeader waveformHeader;
    WaveformDataHeader waveformDataHeader;
    WaveformHeader waveformHeader2;
    WaveformDataHeader waveformDataHeader2;

    inFile.open(InputFileName, std::ios::binary);
    if (inFile.is_open())
    {
        cout << "success open " << InputFileName << endl;
    }
    else
    {
        cout << "fail to open " << InputFileName << endl;
        return false;
        // exit(EXIT_FAILURE);
    }

    inFile.read((char *)&fileHeader, sizeof(FileHeader));
    inFile.read((char *)&waveformHeader, sizeof(WaveformHeader));
    inFile.read((char *)&waveformDataHeader, sizeof(WaveformDataHeader));
    inFile.read((char *)Volts1, waveformDataHeader.BufferSize);
    inFile.read((char *)&waveformHeader2, sizeof(WaveformHeader));
    inFile.read((char *)&waveformDataHeader2, sizeof(WaveformDataHeader));
    inFile.read((char *)Volts2, waveformDataHeader.BufferSize);

    inFile.close();

    if (fileHeader.NumberOfWaveforms != 2)
    {
        cout << "fileHeader.NumberOfWaveforms !=2 " << endl;
        exit(EXIT_FAILURE);
    }

    // cout << "waveformHeader.Points = " << waveformHeader.Points <<endl;
    // cout << "waveformHeader2.Points = " << waveformHeader2.Points << endl;
    pointNum = min(waveformHeader.Points, waveformHeader2.Points);
    cout << "pointNum = " << pointNum << endl;
    xInc = waveformHeader.XIncrement;
    xOrg = waveformHeader.XOrigin;
    for (int i = 0; i < pointNum; i++)
    {
        Time[i] = (i * xInc) + xOrg; /* calculate time */
    }

    //check pointNum, segment, sizeof
    bool checkfileheader = (fileHeader.NumberOfWaveforms == 2) &&
                           (sizeof(FileHeader) == 12);
    bool checkwaveformheader = (abs(waveformHeader.Points - waveformHeader2.Points) < 2) &&
                               (waveformHeader.HeaderSize == waveformHeader2.HeaderSize) &&
                               (waveformHeader.HeaderSize == 140);
    bool checkwaveformdataheader = (waveformDataHeader.HeaderSize == waveformDataHeader2.HeaderSize) &&
                                   (waveformDataHeader.HeaderSize == 12) &&
                                   (waveformDataHeader.BufferSize / waveformDataHeader.BytesPerPoint == waveformHeader.Points) &&
                                   (waveformDataHeader2.BufferSize / waveformDataHeader2.BytesPerPoint == waveformHeader2.Points);
    bool checkall = (fileHeader.FileSize == (12 * 3 + 140 * 2 + waveformDataHeader.BufferSize + waveformDataHeader2.BufferSize));
    if (checkfileheader && checkwaveformheader && checkwaveformdataheader && checkall)
    {
        cout << "reading right binary file " << endl;
    }
    else
    {
        cout << endl
             << endl
             << endl;
        cout << "check the following info " << endl;
        cout << endl;
        showFileHeader(fileHeader);
        cout << endl;
        showWaveformHeader(waveformHeader);
        cout << endl;
        showWaveformDataHeader(waveformDataHeader);
        cout << endl;
        showWaveformHeader(waveformHeader2);
        cout << endl;
        showWaveformDataHeader(waveformDataHeader2);
        cout << endl;
        cout << "the binary file is something wrong, check plz " << endl;
        cout << checkfileheader << checkwaveformheader << checkwaveformdataheader << checkall << endl;
        exit(EXIT_FAILURE);
    }
    return true;
}

bool MyReadBinary_1chan(TString InputFileName)
{

    FileHeader fileHeader;
    WaveformHeader waveformHeader;
    WaveformDataHeader waveformDataHeader;

    inFile.open(InputFileName, std::ios::binary);
    if (inFile.is_open())
    {
        cout << "success open " << InputFileName << endl;
    }
    else
    {
        cout << "fail to open " << InputFileName << endl;
        return false;
        // exit(EXIT_FAILURE);
    }

    inFile.read((char *)&fileHeader, sizeof(FileHeader));
    inFile.read((char *)&waveformHeader, sizeof(WaveformHeader));
    inFile.read((char *)&waveformDataHeader, sizeof(WaveformDataHeader));
    inFile.read((char *)Volts1, waveformDataHeader.BufferSize);

    inFile.close();
    if (fileHeader.NumberOfWaveforms != 1)
    {
        cout << "fileHeader.NumberOfWaveforms !=1 " << endl;
        exit(EXIT_FAILURE);
    }

    pointNum = waveformHeader.Points;
    xInc = waveformHeader.XIncrement;
    xOrg = waveformHeader.XOrigin;
    for (int i = 0; i < pointNum; i++)
    {
        Time[i] = (i * xInc) + xOrg; /* calculate time */
    }

    //check pointNum, segment, sizeof
    bool checkfileheader1 = (fileHeader.NumberOfWaveforms == 1) &&
                            (sizeof(FileHeader) == 12);
    bool checkwaveformheader1 = (waveformHeader.HeaderSize == 140);
    bool checkwaveformdataheader1 = (waveformDataHeader.HeaderSize == 12) &&
                                    (waveformDataHeader.BufferSize / waveformDataHeader.BytesPerPoint == waveformHeader.Points);
    bool checkall = (fileHeader.FileSize == (12 * 2 + 140 * 1 + waveformDataHeader.BufferSize));
    if (checkfileheader1 && checkwaveformheader1 && checkwaveformdataheader1 && checkall)
    {
        cout << "reading right binary file " << endl;
    }
    else
    {
        showFileHeader(fileHeader);
        showWaveformHeader(waveformHeader);
        showWaveformDataHeader(waveformDataHeader);
        cout << "the binary file is something wrong, check plz " << endl;
        cout << checkfileheader1 << checkwaveformheader1 << checkwaveformdataheader1 << checkall << endl;
        exit(EXIT_FAILURE);
    }
    return true;
}

void ShowBinaryInfo(TString InputFileName)
{

    FileHeader fileHeader;
    WaveformHeader waveformHeader;
    WaveformDataHeader waveformDataHeader;
    WaveformHeader waveformHeader2;
    WaveformDataHeader waveformDataHeader2;

    inFile.open(InputFileName, std::ios::binary);
    if (inFile.is_open())
    {
        cout << "success open " << InputFileName << endl;
    }
    else
    {
        cout << "fail to open " << InputFileName << endl;
        exit(EXIT_FAILURE);
    }

    inFile.read((char *)&fileHeader, sizeof(FileHeader));
    inFile.read((char *)&waveformHeader, sizeof(WaveformHeader));
    inFile.read((char *)&waveformDataHeader, sizeof(WaveformDataHeader));

    if(fileHeader.NumberOfWaveforms == 2)
    {
        inFile.read((char *)&waveformHeader2, sizeof(WaveformHeader));
        inFile.read((char *)&waveformDataHeader2, sizeof(WaveformDataHeader));
        inFile.read((char *)Volts2, waveformDataHeader.BufferSize);
    }

    inFile.close();
    showFileHeader(fileHeader);
    showWaveformHeader(waveformHeader);
    showWaveformDataHeader(waveformDataHeader);

}

#endif