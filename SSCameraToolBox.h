#ifndef SSCAMERATOOLBOX_H
#define SSCAMERATOOLBOX_H

#include "SSToolBox.h"

class SSCameraToolBox : public SSToolBox
{
    Q_OBJECT
public:
    explicit SSCameraToolBox(QWidget *parent = nullptr);

signals:

public slots:
    void buttonClicked();

private:
    void createResolutionBar();
    void createExposureBar();
    void createWhiteBalanceBar();
    void createImageAdjustmentBar();
    void createHistogramBar();


private:
    //分辨率
    SSToolBoxItem *m_pPatientBar;

    //曝光
    SSToolBoxItem *m_pExposureBar;

    //白平衡
    SSToolBoxItem *m_pWhiteBalanceBar;

    //图像调整
    SSToolBoxItem *m_pImageAdjustment;

    //直方图
    SSToolBoxItem *m_pHistogram;
};

#endif // SSCAMERATOOLBOX_H
