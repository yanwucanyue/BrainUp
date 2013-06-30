/**
 * @file CRecordCtrl.h
 * @class CRecordCtrl
 * @brief 录音控制器
 */
#ifndef CRECORDCTRL_H
#define CRECORDCTRL_H

#include <QObject>

class CRecordCtrl : public QObject
{
    Q_OBJECT
public:
    explicit CRecordCtrl(QObject *parent = 0);
    
signals:
    
public slots:

    /**
     * @brief 槽：控制录音开始。
     */
    void StartRecordHandler();

    /**
     * @brief 槽：控制录音结束。
     */
    void StopRecordHandler();
};

#endif // CRECORDCTRL_H
