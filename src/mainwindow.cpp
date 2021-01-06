#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(config.isAlwaysOnTop == true) {
        this-> setWindowFlags(Qt :: FramelessWindowHint | Qt :: WindowStaysOnTopHint);
    }
    else {
        this-> setWindowFlags(Qt :: FramelessWindowHint);
    }

    if(config.backColor == "x" || config.backColor == "X") {
        this->setAttribute(Qt::WA_TranslucentBackground, true);
    }
    else {
        this->setBackColor(config.backColor);
    }

    rect = QApplication::desktop()->screenGeometry();
    int fontId = QFontDatabase::addApplicationFont(":new/Font/NotoSansKR.otf");
    font.setFamily(QFontDatabase::applicationFontFamilies(fontId).at(0));

    loadText();
    loadConfig();

    /* Set Shortcut */
    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(moveUp()));
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(moveDown()));
    new QShortcut(QKeySequence(Qt::Key_Left), this, SLOT(moveLeft()));
    new QShortcut(QKeySequence(Qt::Key_Right), this, SLOT(moveRight()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(scrollUp()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X), this, SLOT(scrollDown()));

    // todo: text file watching and auto refesh
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(loadText()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this, SLOT(openSetting()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_E), this, SLOT(openTextFileSlot()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(openTextSeletorSlot()));
}

QString MainWindow::openTextSelector()
{
    return QFileDialog::getOpenFileName(
        this,
        tr("Select text file."),
        "",
        tr("Text files (*.txt *.log) ;; Source files(*.c *.cpp *.java *.h *.py *.rs *.js *.rb)"));
}

QString MainWindow::readTextFile(QString name)
{
    QFile *file = new QFile;
    file->setFileName(name);
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    in.setCodec("UTF-8");
    in.setCodec("Windows-949");
    QString text = in.readAll();
    file->close();
    delete file;
    return text;
}

void MainWindow::openTextFileSlot()
{
    QString dir = textLink.getLink();
    QDesktopServices::openUrl(QUrl::fromLocalFile(dir));
}

void MainWindow::openTextSeletorSlot()
{
    QString fileName = this->openTextSelector();
    QString text = this->readTextFile(fileName);
    ui->label->setText(text);
    textLink.setLink(fileName);
    textLink.save();
}

void MainWindow::setMoveSpeed(int speed)
{
    this->moveSpeed = speed;
}

void MainWindow::setWindowPos(int x, int y)
{
    this->windowPosX = x;
    this->windowPosY = y;
}

void MainWindow::setWindowSize(int width, int height)
{
    this->windowWidth = width;
    this->windowHeight = height;
    this->setGeometry(QRect(windowPosX, windowPosY, width, height));
}

void MainWindow::loadText()
{
    QString fileName = textLink.getLink();

    QFile *file = new QFile;
    file->setFileName(fileName);
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        in.setCodec("UTF-8");
        in.setCodec("Windows-949");
        QString mText = in.readAll();
        ui->label->setText(mText);
    }
    else
    {
        ui->label->setText(tr("is empty..."));
    }
    file->close();
    delete file;
}

void MainWindow::setFontSize(int size)
{
    font.setPixelSize(size);
    ui->label->setFont(font);
}

void MainWindow::setFontColor(QString color)
{
    ui->label->setStyleSheet("color:" + color);
}

void MainWindow::setFontBold(int mBool)
{
    if(mBool == true)
    {
        font.setBold(true);
        ui->label->setFont(font);
    }
    else
    {
        font.setBold(false);
        ui->label->setFont(font);
    }
}

void MainWindow::setBackColor(QString color)
{
    this->setStyleSheet("background-color:"+color);
}

void MainWindow::loadConfig()
{
    setMoveSpeed(config.moveSpeed);
    setFontSize(config.textSize);
    setFontColor(config.textColor);
    setWindowPos(config.windowPosX, config.windowPosY);
    setWindowSize(config.windowWidth, config.windowHeight);
    setFontBold(config.isTextBold);
}

void MainWindow::moveUp()
{
    if(windowPosY > 0)
    {
        windowPosY -= moveSpeed;
        move(windowPosX, windowPosY);

        config.windowPosX = windowPosX;
        config.windowPosY = windowPosY;
        config.save();
    }
}

void MainWindow::moveDown()
{
    if(windowPosY < rect.height() - this->geometry().height())
    {
        windowPosY += moveSpeed;
        move(windowPosX, windowPosY);

        config.windowPosX = windowPosX;
        config.windowPosY = windowPosY;
        config.save();
    }
}

void MainWindow::moveLeft()
{
    if(windowPosX > 0)
    {
        windowPosX -= moveSpeed;
        move(windowPosX,windowPosY);

        config.windowPosX = windowPosX;
        config.windowPosY = windowPosY;
        config.save();
    }
}

void MainWindow::moveRight()
{
    if(windowPosY < rect.width() - this->geometry().width())
    {
        windowPosX += moveSpeed;
        move(windowPosX,windowPosY);

        config.windowPosX = windowPosX;
        config.windowPosY = windowPosY;
        config.save();
    }
}

void MainWindow::scrollUp()
{
    QPropertyAnimation *textAnimation = new QPropertyAnimation(ui->label, "geometry");
    textAnimation->setDuration(200);
    textAnimation->setStartValue(QRect(
        ui->label->geometry().x(),
        ui->label->geometry().y(),
        ui->label->geometry().width(),
        ui->label->geometry().height()));
    textAnimation->setEndValue(QRect(
        ui->label->geometry().x(),
        ui->label->geometry().y() + this->moveSpeed,
        ui->label->geometry().width(),
        ui->label->geometry().height() - this->moveSpeed));
    textAnimation->start();
}

void MainWindow::scrollDown()
{
    QPropertyAnimation *textAnimation = new QPropertyAnimation(ui->label,"geometry");
    textAnimation->setDuration(200);
    textAnimation->setStartValue(QRect(
        ui->label->geometry().x(),
        ui->label->geometry().y(),
        ui->label->geometry().width(),
        ui->label->geometry().height()));
    textAnimation->setEndValue(QRect(
        ui->label->geometry().x(),
        ui->label->geometry().y() - this->moveSpeed,
        ui->label->geometry().width(),
        ui->label->geometry().height() + this->moveSpeed));
    textAnimation->start();
}

void MainWindow::openSetting()
{
    setting set(*this, this);
    set.exec();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->label->setGeometry(QRect(0,0,this->geometry().width(),this->geometry().height()));
    config.windowHeight = this->geometry().height();
    config.windowWidth = this->geometry().width();
    config.save();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_nMouseClick_X_Coordinate = event->x();
        m_nMouseClick_Y_Coordinate = event->y();
        this->isMouseDown = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    this->isMouseDown = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (isMouseDown == true) {
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
        windowPosX = event->globalX() - m_nMouseClick_X_Coordinate;
        windowPosY = event->globalY() - m_nMouseClick_Y_Coordinate;
        config.windowPosX = windowPosX;
        config.windowPosY = windowPosY;
        config.save();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
