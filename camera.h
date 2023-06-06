
#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>

#include <QDebug>
#include <QScopedPointer>
#include <QVBoxLayout>
#include <QWidget>

#if QT_VERSION >= 0x060000
#include <QCameraFormat>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#else
#include <QCameraInfo>
#include <QCameraViewfinder>
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
    void  playCamera();

private:
    void initLayout();
    void initCamera();

private:
    QVBoxLayout*            mainLayout;
    QScopedPointer<QCamera> m_camera;
#if QT_VERSION >= 0x060000
    QGraphicsVideoItem*  m_graphicsVideoItem;
    QGraphicsView*       m_cameraView;
    QGraphicsScene*      m_cameraScene;
    QMediaCaptureSession m_captureSession;
#else
    QCameraViewfinder* m_viewfinder;
#endif

signals:
};

#endif  // CAMERA_H
