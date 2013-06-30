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
        SECTION_NOT_READY, /**< 该编号对应的数据还没有准备好 */
        SECTION_READY,     /**< 该编号对应的数据已经准备好，但是未被读取 */
        SECTION_HAS_READ   /**< 该编号对应的数据已经准备好并被读取 */
    };

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
    QBuffer* GetRecDataSec(int iNumOfRecDatSec);

    /**
     * @brief m_iNumOfRecDatSec的getter。
     * @return m_iNumOfRecDatSec的值
     */
    int GetNumOfRecDatSec() const;

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
