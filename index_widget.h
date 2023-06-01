
#ifndef INDEXWIDGET_H
#define INDEXWIDGET_H

// #include <./machine_service.h>
#include "camera.h"
#include <QDateTime>
#include <QDebug>
#include <QHostAddress>
#include <QLabel>
#include <QNetworkInterface>
#include <QPushButton>
#include <QSpacerItem>
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

private:
    // index
    QVBoxLayout* indexLayout;
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
    Camera*  camera;
};

#endif  // INDEXWIDGET_H
