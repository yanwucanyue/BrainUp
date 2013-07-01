#include "CRecordData.h"

CRecordData::CRecordData(QObject *parent) :
    QObject(parent)
{
    // 初始化
    SetNumofRecDatSec(0);
    for(int i=0; i<MAX_REC_SEC_NUM; i++)
    {
        SetRecDatSec(i, NULL);
        SetDatSecStat(i, SEC_NOT_RDY);
    }
}

CRecordData::~CRecordData()
{

}

int CRecordData::StartRecord(bool bIsSection)
{
    if(true == bIsSection)
    {

    }
    else
    {
        SetNumofRecDatSec(0);

        // 初始化一个buffer储存raw数据
        QBuffer* bufRecord = new QBuffer();
        bufRecord->open( QIODevice::WriteOnly | QIODevice::Truncate );

        SetRecDatSec(m_iNumOfRecDatSec, bufRecord);
        SetNumofRecDatSec(m_iNumOfRecDatSec+1);

        // 设置录音格式
        QAudioFormat format;
        format.setSampleRate(8000);
        format.setChannelCount(1);
        format.setSampleSize(8);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::UnSignedInt);

        // 设置录音设备
        audioInput = new QAudioInput(format, this);
        audioInput->start(bufRecord);
    }

}

int CRecordData::StopRecord()
{

}

void CRecordData::SetRecDatSec(int index, QBuffer *pBufRecDatSec)
{
    m_arrRecDatSec[index] = pBufRecDatSec;
}

void CRecordData::SetDatSecStat(int index, DatStatus iDatSecStat)
{
    m_arrDatSecStat[index] = iDatSecStat;
}

void CRecordData::SetNumofRecDatSec(int iNumOfRecDatSec)
{
    m_iNumOfRecDatSec = iNumOfRecDatSec;
}

QBuffer* CRecordData::Raw2Wav(QBuffer *bufRawRecord)
{
    HEADER pcmHEADER;
    FMT pcmFMT;
    DATA pcmDATA;

    QFile *fp, *fpCopy;
    fp = new QFile();
    fpCopy = new QFile();
    fp->setFileName("record.raw");
    fp->open( QIODevice::ReadOnly );
    fpCopy->setFileName("record.wav");
    fpCopy->open( QIODevice::ReadWrite | QIODevice::Append );



    qstrcpy(pcmHEADER.fccID, "RIFF");
    qstrcpy(pcmHEADER.fccType, "WAVE");
    pcmFMT.dwSamplesPerSec = 44100;
    pcmFMT.dwAvgBytesPerSec = pcmFMT.dwSamplesPerSec*2*2;
    pcmFMT.uiBitsPerSample = 16;

    qstrcpy(pcmFMT.fccID, "fmt ");
    pcmFMT.dwSize = 16;
    pcmFMT.wBlockAlign = 4;
    pcmFMT.wChannels = 2;
    pcmFMT.wFormatTag = 1;


    QByteArray fpDate = fp->readAll();

    qstrcpy(pcmDATA.fccID, "data");
    pcmDATA.dwSize = fpDate.length();
    pcmHEADER.dwSize = 44+fpDate.length()-8; //根据pcmDATA.dwsize得出pcmHEADER.dwsize的值

    QByteArray se;
    se.resize(44);
    memcpy(se.data(),&pcmHEADER,sizeof(pcmHEADER));
    memcpy(se.data()+sizeof(pcmHEADER),&pcmFMT,sizeof(pcmFMT));
    memcpy(se.data()+sizeof(pcmHEADER)+sizeof(pcmFMT),&pcmDATA,sizeof(pcmDATA));

    fpCopy->write(se);

    fpCopy->seek(44);

    fpCopy->write(fpDate);


    fpCopy->close();
    fp->close();
}
