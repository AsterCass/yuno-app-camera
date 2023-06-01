
#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>

#include <QDebug>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QScopedPointer>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGlobal>

#if QT_VERSION >= 0x060000
#include <QCameraFormat>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#else
#endif

class Camera : public QWidget
{
    Q_OBJECT
public:
    explicit Camera(QWidget* parent = nullptr);
    ~Camera();

public:
    QSize getDefaultCamerResolution();
    void  resizeCameraShow(int x, int y, int width, int height);

private:
    void initLayout();
    void initCamera();

private:
    QScopedPointer<QCamera> m_camera;
    QGraphicsVideoItem*     m_graphicsVideoItem;
    QGraphicsView*          m_cameraView;
    QGraphicsScene*         m_cameraScene;
#if QT_VERSION >= 0x060000
    QMediaCaptureSession m_captureSession;
#else
#endif

signals:
};

#endif  // CAMERA_H
