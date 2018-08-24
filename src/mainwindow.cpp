#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(setData.AlwaysOnTop == 1) {
        this-> setWindowFlags(Qt :: FramelessWindowHint | Qt :: WindowStaysOnTopHint);
    }
    else {
        this-> setWindowFlags(Qt :: FramelessWindowHint);
    }

    if(setData.BackColor=="x" || setData.BackColor=="X") {
        setAttribute(Qt::WA_TranslucentBackground,true);
    }
    else {
        SetBackColor(setData.BackColor);
    }

    rec = QApplication::desktop()->screenGeometry();

    int id = QFontDatabase::addApplicationFont(":new/Font/NotoSansKR.otf");
    font.setFamily(QFontDatabase::applicationFontFamilies(id).at(0));

    TextLoading();
    SetLoading();

    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(moveUp()));
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(moveDown()));
    new QShortcut(QKeySequence(Qt::Key_Left), this, SLOT(moveLeft()));
    new QShortcut(QKeySequence(Qt::Key_Right), this, SLOT(moveRight()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(ReloadText()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(Openfile()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(PageUp()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X), this, SLOT(PageDown()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_E), this, SLOT(Edit()));
}

void MainWindow::Openfile()
{
    QString dir = Link.getLink();
    QDesktopServices::openUrl(dir);
}

void MainWindow::ReloadText()
{
    TextLoading();
}

void MainWindow::setSpeed(int s)
{
    Speed = s;
}

void MainWindow::setPos(int x, int y)
{
    posX = x;
    posY = y;
}

void MainWindow::setSize(int w, int h)
{
    Width = w;
    Height = h;

    this->setGeometry(QRect(posX,posY,Width, Height));
}

void MainWindow::TextLoading()
{
    QString fileName = Link.getLink();

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
        ui->label->setText("Not Data");
    }
    file->close();
    delete file;
}

void MainWindow::FontResize(int s)
{
    font.setPixelSize(s);
    ui->label->setFont(font);
}

void MainWindow::SetFontColor(QString color)
{
    ui->label->setStyleSheet("color:"+color);
}

void MainWindow::SetFontBold(int mBool)
{
    if(mBool==1)
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

void MainWindow::SetBackColor(QString color)
{
    this->setStyleSheet("background-color:"+color);
}

void MainWindow::SetLoading()
{
    setSpeed(setData.Speed);
    FontResize(setData.TextSize);
    SetFontColor(setData.TextColor);
    setPos(setData.PosX, setData.PosY);
    setSize(setData.Width, setData.Height);
    SetFontBold(setData.TextBold);
}

void MainWindow::moveUp()
{
    if(posY > 0)
    {
        posY-=Speed;
        move(posX,posY);

        setData.PosX = posX;
        setData.PosY = posY;
        setData.SAVE();
    }
}

void MainWindow::moveDown()
{
    if(posY < rec.height() - this->geometry().height())
    {
        posY+=Speed;
        move(posX,posY);

        setData.PosX = posX;
        setData.PosY = posY;
        setData.SAVE();
    }
}

void MainWindow::moveLeft()
{
    if(posX > 0)
    {
        posX-=Speed;
        move(posX,posY);

        setData.PosX = posX;
        setData.PosY = posY;
        setData.SAVE();
    }
}

void MainWindow::moveRight()
{
    if(posY < rec.width() - this->geometry().width())
    {
        posX+=Speed;
        move(posX,posY);

        setData.PosX = posX;
        setData.PosY = posY;
        setData.SAVE();
    }
}

void MainWindow::PageUp()
{
    QPropertyAnimation *Text_Animation = new QPropertyAnimation(ui->label,"geometry");
    Text_Animation->setDuration(200);

    Text_Animation->setStartValue(QRect(ui->label->geometry().x(),
                                        ui->label->geometry().y(),
                                        ui->label->geometry().width(),
                                        ui->label->geometry().height()));
    Text_Animation->setEndValue(QRect(ui->label->geometry().x(),
                                      ui->label->geometry().y()+Speed,
                                      ui->label->geometry().width(),
                                      ui->label->geometry().height()-Speed));
    Text_Animation->start();
}

void MainWindow::PageDown()
{
    QPropertyAnimation *Text_Animation = new QPropertyAnimation(ui->label,"geometry");
    Text_Animation->setDuration(200);

    Text_Animation->setStartValue(QRect(ui->label->geometry().x(),
                                        ui->label->geometry().y(),
                                        ui->label->geometry().width(),
                                        ui->label->geometry().height()));
    Text_Animation->setEndValue(QRect(ui->label->geometry().x(),
                                      ui->label->geometry().y()-Speed,
                                      ui->label->geometry().width(),
                                      ui->label->geometry().height()+Speed));
    Text_Animation->start();
}



void MainWindow::Edit()
{
    setting set(*this,this);
    set.exec();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->label->setGeometry(QRect(0,0,this->geometry().width(),this->geometry().height()));
    setData.Height = this->geometry().height();
    setData.Width = this->geometry().width();
    setData.SAVE();
}

bool isMouseDown;

void MainWindow::mousePressEvent(QMouseEvent *event) {
   if (event->button() == Qt::LeftButton) {
      m_nMouseClick_X_Coordinate = event->x();
      m_nMouseClick_Y_Coordinate = event->y();
      isMouseDown = true;
   }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
   isMouseDown = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
   if (isMouseDown == true) {
      move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
      posX = event->globalX()-m_nMouseClick_X_Coordinate;
      posY = event->globalY()-m_nMouseClick_Y_Coordinate;
      setData.PosX = posX;
      setData.PosY = posY;
      setData.SAVE();
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}
