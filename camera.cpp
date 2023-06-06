
#include "camera.h"

Camera::Camera(QWidget* parent) : QWidget{ parent }
{
    initLayout();
    initCamera();
    playCamera();
}

Camera::~Camera()
{
#if QT_VERSION >= 0x060000
    delete m_graphicsVideoItem;
    delete m_cameraView;
    delete m_cameraScene;
#else
    delete m_viewfinder;
#endif
    delete mainLayout;
}

void Camera::initLayout()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
#if QT_VERSION >= 0x060000
    m_cameraScene = new QGraphicsScene();
    m_cameraView  = new QGraphicsView(m_cameraScene);
    m_cameraView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_cameraView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_cameraView->setScene(m_cameraScene);
    mainLayout->addWidget(m_cameraView);
    m_graphicsVideoItem = new QGraphicsVideoItem();
    m_captureSession.setVideoOutput(m_graphicsVideoItem);
    m_cameraScene->addItem(m_graphicsVideoItem);
#else
    m_viewfinder = new QCameraViewfinder();
    m_viewfinder->show();
    mainLayout->addWidget(m_viewfinder);
#endif
}

void Camera::initCamera()
{
#if QT_VERSION >= 0x060000
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty())
    {
        // todo throw
    }
    auto thisCamera = new QCamera(cameras.first());
    m_camera.reset(thisCamera);
    m_captureSession.setCamera(m_camera.data());
#else
    QCameraInfo defualtCamera = QCameraInfo::defaultCamera();
    if (defualtCamera.isNull())
    {
        // todo throw
    }
    m_camera.reset(new QCamera(defualtCamera, this));
    m_camera.data()->setViewfinder(m_viewfinder);
#endif
}

void Camera::resizeCameraShow(int x, int y, int width, int height)
{
    this->setGeometry(x, y, width, height);
#if QT_VERSION >= 0x060000
    m_graphicsVideoItem->setSize(QSizeF(width, height));
#endif
}

QSize Camera::getDefaultCamerResolution()
{
    if (m_camera.isNull())
    {
        // todo throw
    }
#if QT_VERSION >= 0x060000
    const QList<QCameraFormat> videoFormats = m_camera->cameraDevice().videoFormats();
    if (videoFormats.isEmpty())
    {
        // todo throw
    }
    auto defaultFormat = videoFormats.first();
    return defaultFormat.resolution();
#else
    QList<QSize> resolutionList = m_camera->supportedViewfinderResolutions();
    if (resolutionList.isEmpty())
    {
        // todo throw
    }
    return resolutionList.first();
#endif
}

void Camera::playCamera()
{
    m_camera->start();
}
