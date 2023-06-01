
#include "camera.h"

Camera::Camera(QWidget* parent) : QWidget{ parent }
{
    initLayout();
    initCamera();
    m_camera->start();
}

Camera::~Camera()
{
    delete m_graphicsVideoItem;
    delete m_cameraView;
    delete m_cameraScene;
}

void Camera::initLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    m_cameraScene = new QGraphicsScene();
    m_cameraView  = new QGraphicsView(m_cameraScene);
    m_cameraView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_cameraView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_cameraView->setScene(m_cameraScene);
    mainLayout->addWidget(m_cameraView);
    m_graphicsVideoItem = new QGraphicsVideoItem();
    m_captureSession.setVideoOutput(m_graphicsVideoItem);
    m_cameraScene->addItem(m_graphicsVideoItem);
}

void Camera::initCamera()
{
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty())
    {
        // todo throw
    }
    auto thisCamera = new QCamera(cameras.first());
    m_camera.reset(thisCamera);
    m_captureSession.setCamera(m_camera.data());
}

void Camera::resizeCameraShow(int x, int y, int width, int height)
{
    this->setGeometry(x, y, width, height);
    m_graphicsVideoItem->setSize(QSizeF(width, height));
}

QSize Camera::getDefaultCamerResolution()
{
    if (m_camera.isNull())
    {
        // todo throw
    }
    const QList<QCameraFormat> videoFormats = m_camera->cameraDevice().videoFormats();
    if (videoFormats.isEmpty())
    {
        // todo throw
    }
    auto defaultFormat = videoFormats.first();
    return defaultFormat.resolution();
}
