
#include "index_widget.h"

IndexWidget::IndexWidget(QWidget* parent) : QWidget(parent)
{
    // index
    indexLayout = new QVBoxLayout();
    // set margin
    indexLayout->setSpacing(0);
#if QT_VERSION >= 0x060000
    // indexFrame->setContentsMargins(0, 0, 0, 0);
    indexLayout->unsetContentsMargins();
#else
    indexLayout->setMargin(0);
#endif
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
    // timer
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &IndexWidget::updateMsg);
    m_timer->start(10000);
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
    delete m_mainMaskFrame;
    delete mainFrame;
    // index
    delete m_timer;
    delete indexLayout;
}

void IndexWidget::updateMsg()
{
    // update  time
    QDateTime curDateTime    = QDateTime::currentDateTime();
    QString   curDateTimeStr = curDateTime.toString("yyyy.MM.dd hh:mm dddd");
    timeShow->setText(curDateTimeStr);
    // update ip
    bool hasWired    = false;
    bool hasWireless = false;
    for (const QNetworkInterface& address : QNetworkInterface::allInterfaces())
    {
        if (!address.flags().testFlag(QNetworkInterface::IsRunning))
        {
            continue;
        }
        for (const QNetworkAddressEntry& entry : address.addressEntries())
        {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol && entry.ip() != QHostAddress(QHostAddress::LocalHost))
            {
                if (address.type() == QNetworkInterface::Wifi)
                {
                    hasWireless = true;
                    wifiLabel->setText(QString::fromUtf8("无线: ") + entry.ip().toString());
                }
                else
                {
                    hasWired = true;
                    lineLabel->setText(QString::fromUtf8("有线: ") + entry.ip().toString());
                }
            }
        }
    }
    if (!hasWired)
    {
        lineLabel->setText(QString::fromUtf8("有线：无连接"));
    }
    if (!hasWireless)
    {
        wifiLabel->setText(QString::fromUtf8("无线：无连接"));
    }
    // else
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
        QFont font = timeShow->font();
        font.setPointSize(8);
        timeShow->setFont(font);
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
            lineLabel = new QLabel();
            lineLabel->setText(QString::fromUtf8("有线: 未连接"));
            QFont font = lineLabel->font();
            font.setPointSize(6);
            lineLabel->setFont(font);
            QPalette pal = QPalette();
            pal.setColor(QPalette::WindowText, Qt::white);
            lineLabel->setAutoFillBackground(true);
            lineLabel->setPalette(pal);
        }
        // wifi
        {
            wifiLabel = new QLabel();
            wifiLabel->setText(QString::fromUtf8("无线: 未连接"));
            QFont font = wifiLabel->font();
            font.setPointSize(6);
            wifiLabel->setFont(font);
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
    // camera
    camera = new Camera(mainFrame);
    // mask
    m_mainMaskFrame = new QWidget(mainFrame);
    m_mainMaskFrame->setObjectName("mainFrame");
    m_mainMaskFrame->setStyleSheet("#mainFrame{background-color:qlineargradient("
                                   "spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0,0 ),stop:0.7 rgba(0, 0, 0,0 ) ,stop:1 #165DFF)}");
    return mainFrame;
}

void IndexWidget::checkFaceSuccess()
{
    qDebug() << "success";
    camera->playCamera();
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
    // mask
    m_mainMaskFrame->resize(widgetSize.width(), widgetSize.height());
}
