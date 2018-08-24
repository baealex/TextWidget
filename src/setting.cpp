#include "setting.h"
#include "ui_setting.h"
#include  "ui_mainwindow.h"

setting::setting(MainWindow &ref,QWidget *parent) :
    QDialog(parent),
    Windoref(ref),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    ui->FontSize->setValue(Windoref.setData.TextSize);
    ui->MoveSpeed->setValue(Windoref.setData.Speed);

    initialSet = false;

    if(Windoref.setData.StartUp == 1){
        ui->AutoStart->setChecked(true);
    }

    if(Windoref.setData.TextBold == 1){
        ui->Bold->setChecked(true);
    }

    if(Windoref.setData.AlwaysOnTop == 1){
        ui->AlwaysOnTop->setChecked(true);
    }

    initialSet = true;

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setStyleSheet("background-color:#fff");
}

setting::~setting()
{
    delete ui;
}

void setting::on_textChanger_clicked()
{
    QFile *file = new QFile;
    QString name = QFileDialog::getOpenFileName(this,
                                                "Select text file.",
                                                "",
                                                tr("Text files (*.txt) ;; Source files(*.c *.cpp *.java *.h)"));
    file->setFileName(name);
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    in.setCodec("UTF-8");
    in.setCodec("Windows-949");
    QString mText = in.readAll();
    file->close();
    Windoref.ui->label->setText(mText);

    Windoref.Link.setLink(name);
    Windoref.Link.SAVE();
}

void setting::on_Homepage_clicked()
{
    QDesktopServices::openUrl(QUrl("http://baealex.tistory.com"));
}

void setting::on_MoveSpeed_sliderMoved(int position)
{
    Windoref.setSpeed(position);
    Windoref.setData.Speed = position;
    Windoref.setData.SAVE();
}

void setting::on_FontSize_valueChanged(int arg1)
{
    Windoref.FontResize(arg1);
    Windoref.setData.TextSize = arg1;
    Windoref.setData.SAVE();
}

void setting::on_FontColorBtn_clicked(bool checked)
{
    QString color = ui->FontColor->text();
    if(color.at(0)!='#') {
        color = '#' + color;
    }
    Windoref.SetFontColor(color);
    Windoref.setData.TextColor = color;
    Windoref.setData.SAVE();
}

void setting::on_AutoStart_stateChanged(int arg1)
{
    if(initialSet == true){
        QFileInfo fileInfo(QCoreApplication::applicationFilePath());
        QString startDir = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation)
                + QDir::separator() + "Startup"
                + QDir::separator() + fileInfo.completeBaseName() + ".lnk";

        if(Windoref.setData.StartUp == 0)
        {
            Windoref.setData.StartUp = 1;
            Windoref.setData.SAVE();
            QFile::link(QCoreApplication::applicationFilePath(),startDir);
        }
        else
        {
            Windoref.setData.StartUp = 0;
            Windoref.setData.SAVE();
            QFile file(startDir);
            file.remove();
        }
    }
}

void setting::on_Bold_stateChanged(int arg1)
{
    if(initialSet == true){
        if(Windoref.setData.TextBold == 0)
        {
            Windoref.setData.TextBold = 1;
            Windoref.setData.SAVE();
            Windoref.SetFontBold(Windoref.setData.TextBold);
        }
        else
        {
            Windoref.setData.TextBold = 0;
            Windoref.setData.SAVE();
            Windoref.SetFontBold(Windoref.setData.TextBold);
        }
    }
}

#include <QMessageBox>
void setting::on_BackColorBtn_clicked()
{
    QString color = ui->BackColor->text();
    if(color == "x" || color == "X") {
        Windoref.setData.BackColor = color;
        Windoref.setData.SAVE();
        QMessageBox::information(this,"information","Please Restart Program","OK");
        return;
    }
    else {
        if(color.at(0)!='#') {
            color = '#' + color;
        }
        Windoref.SetBackColor(color);
        Windoref.setData.BackColor = color;
        Windoref.setData.SAVE();
    }
}

void setting::on_AlwaysOnTop_stateChanged(int arg1)
{
    if(initialSet == true) {
        if(Windoref.setData.AlwaysOnTop == 0) {
            Windoref.setData.AlwaysOnTop = 1;
            Windoref.setData.SAVE();
            QMessageBox::information(this,"information","Please Restart Program","OK");
        }
        else {
            Windoref.setData.AlwaysOnTop = 0;
            Windoref.setData.SAVE();
            QMessageBox::information(this,"information","Please Restart Program","OK");
        }
    }
}
