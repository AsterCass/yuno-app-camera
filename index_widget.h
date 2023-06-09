
#ifndef INDEXWIDGET_H
#define INDEXWIDGET_H

// #include <./machine_service.h>
#include "camera.h"
#include <QDateTime>
#include <QDebug>
#include <QGridLayout>
#include <QHostAddress>
#include <QLabel>
#include <QNetworkInterface>
#include <QPushButton>
#include <QSpacerItem>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class IndexWidget : public QWidget

{
    Q_OBJECT

public:
    IndexWidget(QWidget* parent = nullptr);
    ~IndexWidget();

private slots:
    void checkFaceSuccess();

private:
    void resizeEvent(QResizeEvent*);

private:
    QWidget* crateHeaderFrame();
    QWidget* createTitleFrame();
    QWidget* createMainFrame();
    void     updateMsg();

private:
    // index
    QVBoxLayout* indexLayout;
    QTimer*      m_timer;
    // header
    QWidget*     headerFrame;
    QHBoxLayout* headerLayout;
    QLabel*      timeShow;
    QWidget*     networkFrame;
    QVBoxLayout* networkLayout;
    QLabel*      lineLabel;
    QLabel*      wifiLabel;
    QSpacerItem* centerSpacer;
    // title
    QWidget*     titleFrame;
    QVBoxLayout* titleLayout;
    QLabel*      titleLabel;
    QPushButton* btn;
    // main
    QWidget* mainFrame;
    QWidget* m_mainMaskFrame;
    Camera*  camera;
};

#endif  // INDEXWIDGET_H
