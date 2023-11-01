#include "viewpager.h"
#include "qstyle.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QButtonGroup>
#include <QBitmap>
#include <QPainterPath>
#include "../style.h"
viewpager::viewpager(QWidget *parent)
: QWidget(parent)
, m_currentDrawImageIndx(0)
{
// 添加ImageOpacity属性;
    this->setProperty("ImageOpacity", 1.0);
// 动画切换类;
    m_opacityAnimation = new QPropertyAnimation(this, "ImageOpacity");
// 这里要设置的动画时间小于图片切换时间;
    m_opacityAnimation->setDuration(1500);
// 设置ImageOpacity属性值的变化范围;
    m_opacityAnimation->setStartValue(1.0);
    m_opacityAnimation->setEndValue(0.0);
// 透明度变化及时更新绘图;
    connect(m_opacityAnimation, SIGNAL(valueChanged(const QVariant &)), this, SLOT(update()));
// 设置图片切换时钟槽函数;
    connect(&m_imageChangeTimer, SIGNAL(timeout()), this, SLOT(onImageChangeTimeout()));
//    this->setFixedSize(QSize(400, 250));
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setAttribute(Qt::WA_StyledBackground);

//    this->setStyle(my_viewpager_style);
}
viewpager::~viewpager()
{
}
void viewpager::initChangeImageButton()
{
// 注意图片过多按钮可能放置不下;
    QButtonGroup *changeButtonGroup = new QButtonGroup;
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    for (int i = 0; i < m_imageFileNameList.count(); i++)
{
    QPushButton *pButton = new QPushButton;
        pButton->setAttribute(Qt::WA_StyledBackground);
        pButton->setAttribute(Qt::WA_TranslucentBackground);
        // 设置按钮样式及悬浮、按下时的状态
    pButton->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                      "QPushButton:hover{background-color:red; color: black;border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                                      "QPushButton:pressed,QPushButton:checked{background-color:red;border-style: inset;border:2px groove gray;border-radius:10px;padding:2px 4px;}");

    pButton->setFixedSize(QSize(16, 16));
    pButton->setCheckable(true);
    pButton->setFlat(true);
    pButton->setDefault(false);
    changeButtonGroup->addButton(pButton, i);
    m_pButtonChangeImageList.append(pButton);
    hLayout->addWidget(pButton);
}
    hLayout->addStretch();
    hLayout->setSpacing(10);
    hLayout->setMargin(0);
    connect(changeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onImageSwitchButtonClicked(int)));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(hLayout);
    mainLayout->setContentsMargins(0, 0, 0, 20);
}
void viewpager::setImageList(QStringList imageFileNameList)
{
    m_imageFileNameList = imageFileNameList;
}
void viewpager::addImage(QString imageFileName)
{
    m_imageFileNameList.append(imageFileName);
}
void viewpager::startPlay()
{
// 添加完图片之后，根据图片多少设置图片切换按钮;
    initChangeImageButton();
    if (m_imageFileNameList.count() == 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
    }
    else if (m_imageFileNameList.count() > 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
        m_currentPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
        m_imageChangeTimer.start(2000);
        update();
    }
}

viewpager &viewpager::getInstance(QWidget *parent)
{
    static viewpager instance(parent);
    return instance;
}

void viewpager::setStyle(QString style)
{
    this->style()->unpolish(this);
    this->setStyleSheet(style);
    this->style()->polish(this);
    this->update();
}
void viewpager::onImageChangeTimeout()
{
// 设置前后的图片;
    m_currentPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
    m_currentDrawImageIndx++;
    if (m_currentDrawImageIndx >= m_imageFileNameList.count())
    {
        m_currentDrawImageIndx = 0;
    }
        m_nextPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
    // 动画类重新开始;
    m_opacityAnimation->start();
}
void viewpager::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect imageRect = this->rect();
    // 如果图片列表为空，显示默认图片;
    if (m_imageFileNameList.isEmpty())
    {
        return;
    }
    // 如果只有一张图片;
    else if (m_imageFileNameList.count() == 1)
    {
        QPixmap backPixmap = QPixmap(m_imageFileNameList.first());
        QPixmap newPixmap = getRoundRectPixmap(backPixmap,backPixmap.size(),10);
        painter.drawPixmap(imageRect, newPixmap.scaled(imageRect.size()));//动态画出图片
    }
    // 多张图片;
    else if (m_imageFileNameList.count() > 1)
    {
        float imageOpacity = this->property("ImageOpacity").toFloat();
        painter.setOpacity(1);//设置透明度为1(不透明)
        this->m_nextPixmap = getRoundRectPixmap(m_nextPixmap,m_nextPixmap.size(),10);
        painter.drawPixmap(imageRect, m_nextPixmap.scaled(imageRect.size()));//画出下一张图片
        painter.setOpacity(imageOpacity);
        this->m_currentPixmap = getRoundRectPixmap(m_currentPixmap,m_currentPixmap.size(),10);
        painter.drawPixmap(imageRect, m_currentPixmap.scaled(imageRect.size())); //画出当前图片
    }
}
void viewpager::onImageSwitchButtonClicked(int buttonId)
{
    m_currentDrawImageIndx = buttonId - 1;
    if (m_currentDrawImageIndx == -1)
    {
        m_currentDrawImageIndx = m_imageFileNameList.count() - 1;
    }
    onImageChangeTimeout();
    m_imageChangeTimer.start(2000);
    update();
}
void viewpager::mousePressEvent(QMouseEvent *event)
{
    // 这里可以对当前图片进行点击然后触发每个图片对应的效果;
    // 比如web上好多类似的弹出对应的广告页面等功能;
    qDebug() << m_currentDrawImageIndx;
    //return __super::mousePressEvent(event);
}
QPixmap viewpager::getRoundRectPixmap(QPixmap srcPixMap, const QSize & size, int radius)
{
    //不处理空数据或者错误数据
    if (srcPixMap.isNull()) {
        return srcPixMap;
    }

    //获取图片尺寸
    int imageWidth = size.width();
    int imageHeight = size.height();

    //处理大尺寸的图片,保证图片显示区域完整
    QPixmap newPixMap = srcPixMap.scaled(imageWidth, (imageHeight == 0 ? imageWidth : imageHeight),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPixmap destImage(imageWidth, imageHeight);
    destImage.fill(Qt::transparent);
    QPainter painter(&destImage);
    // 抗锯齿
    painter.setRenderHints(QPainter::Antialiasing, true);
    // 图片平滑处理
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    // 将图片裁剪为圆角
    QPainterPath path;
    QRect rect(0, 0, imageWidth, imageHeight);
    path.addRoundedRect(rect, radius, radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, imageWidth, imageHeight, newPixMap);
    return destImage;
}

