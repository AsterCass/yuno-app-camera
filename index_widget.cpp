
#include "index_widget.h"

IndexWidget::IndexWidget(QWidget* parent) : QWidget(parent)
{
    // index
    indexLayout = new QVBoxLayout();
    // set margin
    indexLayout->setSpacing(0);
    // indexFrame->setContentsMargins(0, 0, 0, 0);
    indexLayout->unsetContentsMargins();
    // cell
    indexLayout->addWidget(crateHeaderFrame());
    indexLayout->addWidget(createTitleFrame());
    indexLayout->addWidget(createMainFrame());
    // stretch
    indexLayout->setStretch(0, 1);
    indexLayout->setStretch(1, 2);
    indexLayout->setStretch(2, 12);
    setLayout(indexLayout);
    // init size
    resize(400, 640);
}

IndexWidget::~IndexWidget()
{
    // header
    delete wifiLabel;
    delete lineLabel;
    delete timeShow;
    delete networkLayout;
    delete networkFrame;
    delete headerLayout;
    delete headerFrame;
    // title
    delete titleLabel;
    delete btn;
    delete titleLayout;
    delete titleFrame;
    // main
    delete camera;
    delete mainFrame;
    // index
    delete indexLayout;
}

QWidget* IndexWidget::crateHeaderFrame()
{
    headerFrame = new QWidget();
    // backgroud color
    {
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, QColor(22, 93, 255));
        headerFrame->setAutoFillBackground(true);
        headerFrame->setPalette(pal);
    }
    // time
    {
        timeShow                 = new QLabel();
        QDateTime curDateTime    = QDateTime::currentDateTime();
        QString   curDateTimeStr = curDateTime.toString("yyyy.MM.dd hh:mm dddd");
        timeShow->setText(curDateTimeStr);
        QPalette pal = QPalette();
        pal.setColor(QPalette::WindowText, Qt::white);
        timeShow->setAutoFillBackground(true);
        timeShow->setPalette(pal);
    }
    // network
    {
        networkFrame  = new QWidget();
        networkLayout = new QVBoxLayout(networkFrame);
        networkLayout->setSpacing(0);
        networkLayout->setContentsMargins(0, 0, 0, 0);
        // line
        {
            lineLabel                     = new QLabel();
            const QHostAddress& localhost = QHostAddress(QHostAddress::LocalHost);
            for (const QHostAddress& address : QNetworkInterface::allAddresses())
            {
                if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
                {
                    lineLabel->setText(QString::fromUtf8("有线: ") + address.toString());
                    QPalette pal = QPalette();
                    pal.setColor(QPalette::WindowText, Qt::white);
                    lineLabel->setAutoFillBackground(true);
                    lineLabel->setPalette(pal);
                }
            }
        }
        // wifi
        {
            wifiLabel = new QLabel();
            wifiLabel->setText(QString::fromUtf8("无线: 192.168.0.1"));
            QPalette pal = QPalette();
            pal.setColor(QPalette::WindowText, Qt::white);
            wifiLabel->setAutoFillBackground(true);
            wifiLabel->setPalette(pal);
        }
        // comp
        networkLayout->addWidget(lineLabel);
        networkLayout->addWidget(wifiLabel);
    }
    // space
    {
        centerSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    }
    // layout
    headerLayout = new QHBoxLayout(headerFrame);
    headerLayout->addWidget(timeShow);
    headerLayout->addItem(centerSpacer);
    headerLayout->addWidget(networkFrame);
    // ret
    return headerFrame;
}

QWidget* IndexWidget::createTitleFrame()
{
    titleFrame = new QWidget();
    // backgroud color
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(91, 141, 255));
    titleFrame->setAutoFillBackground(true);
    titleFrame->setPalette(pal);
    // title
    {
        titleLabel = new QLabel();
        titleLabel->setText(QString::fromUtf8("橘子酒店 （文一路店）"));
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont font = titleLabel->font();
        font.setPointSize(16);
        titleLabel->setFont(font);
        QPalette pal = QPalette();
        pal.setColor(QPalette::WindowText, Qt::white);
        titleLabel->setAutoFillBackground(true);
        titleLabel->setPalette(pal);
    }
    // btn
    {
        btn = new QPushButton();
        btn->setText(QString::fromUtf8("this is a btn"));
        connect(btn, &QPushButton::clicked, this, &IndexWidget::checkFaceSuccess);
    }
    // laytout
    titleLayout = new QVBoxLayout(titleFrame);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(btn);
    // ret
    return titleFrame;
}

QWidget* IndexWidget::createMainFrame()
{
    mainFrame = new QWidget();
    mainFrame->setObjectName("mainFrame");
    mainFrame->setStyleSheet("#mainFrame{background-color:qlineargradient("
                             "spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff,stop:0.7 #ffffff ,stop:1 #165DFF)}");
    // camera
    camera = new Camera(mainFrame);
    return mainFrame;
}

void IndexWidget::checkFaceSuccess()
{
    qDebug() << "success";
}

void IndexWidget::resizeEvent(QResizeEvent*)
{
    // cover size param
    int height = 0;
    int width  = 0;
    int y      = 0;
    int x      = 0;
    // cover size comput
    QSize  cameraSize        = camera->getDefaultCamerResolution();
    double cameraAspectRatio = ( double )cameraSize.width() / cameraSize.height();
    QSize  widgetSize        = mainFrame->size();
    double widgetAspectRatio = ( double )widgetSize.width() / widgetSize.height();
    if (cameraAspectRatio > widgetAspectRatio)
    {
        height = widgetSize.height();
        width  = height * cameraAspectRatio;
        x      = (widgetSize.width() - width) / 2;
    }
    else
    {
        width  = widgetSize.width();
        height = width / cameraAspectRatio;
        y      = (widgetSize.height() - height) / 2;
    }
    camera->resizeCameraShow(x, y, width, height);
}
