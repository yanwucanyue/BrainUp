/**
 * @file CRecordData.h
 * @class CRecordData
 * @brief 处理录音的模型。
 */

#ifndef CRECORDDATA_H
#define CRECORDDATA_H

#include <QObject>
#include <QVector>
#include <QBuffer>
#include <QAudioInput>

#define MAX_REC_SEC_NUM 32 /**< 最大录音段数 */
#define SECOND_PER_SEC 5 /**< 每段最大录音数 */

class CRecordData : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief 表示数据状态的枚举变量
     */
    enum DatStatus
    {
        SEC_NOT_RDY, /**< 该编号对应的数据还没有准备好 */
        SEC_RDY,     /**< 该编号对应的数据已经准备好，但是未被读取 */
        SEC_HAS_READ   /**< 该编号对应的数据已经准备好并被读取 */
    };

    /**
     * @brief WAV头文件
    typedef struct
    {
        char fccID[4]; //"RIFF"
        unsigned long dwSize;//length-8
        char fccType[4]; //"WAVE"
    }HEADER;

    typedef struct
    {
        char fccID[4]; //"fmt "
        unsigned long dwSize; //16
        unsigned short wFormatTag; //1
        unsigned short wChannels; //1 or 2
        unsigned long dwSamplesPerSec; //44100
        unsigned long dwAvgBytesPerSec; //
        unsigned short wBlockAlign; //声道数*量化数/8
        unsigned short uiBitsPerSample; //量化数 8 or 16
    }FMT;

    typedef struct
    {
        char fccID[4]; //"data"
        unsigned long dwSize; //length-44
    }DATA;


    /**
     * @brief 构造函数。
     * @param parent 父指针
     */
    explicit CRecordData(QObject *parent = 0);

    /**
     * @brief 析构函数。
     */
    ~CRecordData();
    
    /**
     * @brief 启动录音的接口
     * @param bIsSection 是将所有录成一段还是分成分段录音。
     * @return
     * 所有录音分段的段数。如果返回为0，则说明CRecordData没有处在录音状态，成功启动录音；
     * 如果返回大于0，则说明CRecordData处在录音状态，启动录音失败。
     */
    int StartRecord(bool bIsSection);
    /**
     * @brief 停止录音的接口。
     * @return 所有录音分段的段数。
     */
    int StopRecord();

    /**
     * @brief 获取对应段序号的数据。
     * @param iNumOfRecDatSec 段序号。
     * @return 对应的QBuffer数据指针。
     */
    QBuffer* GetRecDataSec(int iNumOfRecDatSec) const;

    /**
     * @brief 获取对应段序号的状态。
     * @param iNumOfRecDatSec 段序号。
     * @return 对应的状态。
     */
    DatStatus GetDatSecStat(int iNumOfRecDatSec) const;

    /**
     * @brief m_iNumOfRecDatSec的getter。
     * @return m_iNumOfRecDatSec的值。
     */
    int GetNumOfRecDatSec() const;

private:
    /**
     * @brief m_iNumOfRecDatSec的setter,私有，不允许外部修改值。
     * @param iNumOfRecDatSec 设置值。
     */
    void SetNumofRecDatSec(int iNumOfRecDatSec);

    /**
     * @brief SetRecDatSec 设置对应段序号的数据。
     * @param index 储存数据的段序号。
     * @param pRecDatSec 需要储存的数据。
     */
    void SetRecDatSec(int index, QBuffer* pRecDatSec);

    /**
     * @brief SetDatSecStat 设置对应段序号数据的状态。
     * @param index 储存状态的段序号。
     * @param iDatSecStat 更改的状态。
     */
    void SetDatSecStat(int index, DatStatus iDatSecStat);

    /**
     * @brief 将录音的RAW数据转换为带文件头的WAV数据
     * @param bufRawRecord 储存RAW数据的缓存
     * @return 带文件头的WAV数据缓存
     */
    QBuffer* Raw2Wav(QBuffer* bufRawRecord);

private:
    /**
     * @brief 储存所有数据段指针的数组。
     */
    QBuffer* m_arrRecDatSec[MAX_REC_SEC_NUM];

    /**
     * @brief 储存所有数据段状态的数组。
     */
    DatStatus m_arrDatSecStat[MAX_REC_SEC_NUM];

    /**
     * @brief 所有录音分段的段数。
     */
    int m_iNumOfRecDatSec;

signals:
    /**
     * @brief 信号：某段数据准备好。
     * @details 当一段数据准备就绪可以读取，则发送该信号。
     * @param iCurrentNumOfSec 数据就绪的段序号。
     */
    void SigSectionReady(int iCurrentNumOfSec);
};

#endif // CRECORDDATA_H
