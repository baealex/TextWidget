#include "setting.h"
#include "ui_setting.h"
#include  "ui_mainwindow.h"

setting::setting(MainWindow &ref, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting),
    windoRef(ref)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager();

    this->sslConfig = QSslConfiguration::defaultConfiguration();
    this->sslConfig.setProtocol(QSsl::TlsV1_2);

    this->request.setSslConfiguration(this->sslConfig);
    this->request.setUrl(QUrl("https://raw.githubusercontent.com/baealex/TextWidget/master/version"));

    connect(manager, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }
            QString response = reply->readAll();
            if(response == appVersion) {
                QMessageBox::information(this, tr("information"), tr("It's already the latest version."), tr("OK"));
            } else {
                QMessageBox::StandardButton reply = QMessageBox::question(this, tr("infomaion"), tr("The current version is ") + appVersion + tr(", and the new version is ") + response + tr(". Do you want a new version?"), QMessageBox::Yes|QMessageBox::No);
                if(reply == QMessageBox::Yes) {
                    QDesktopServices::openUrl(QUrl("https://www.dropbox.com/sh/g10z7q7ecs8fab9/AAADWShDyU6-PBkb2bGZc9t8a?dl=1"));
                }
            }
            ui->UpdateCheck->setEnabled(true);
        }
    );

    ui->FontSize->setValue(windoRef.config.textSize);
    ui->MoveSpeed->setValue(windoRef.config.moveSpeed);

    initialSet = false;

    if(windoRef.config.isStartUp == true){
        ui->AutoStart->setChecked(true);
    }

    if(windoRef.config.isTextBold == true){
        ui->Bold->setChecked(true);
    }

    if(windoRef.config.isAlwaysOnTop == true){
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
    QString fileName = windoRef.openTextSelector();
    QString text = windoRef.readTextFile(fileName);
    windoRef.ui->label->setText(text);
    windoRef.textLink.setLink(fileName);
    windoRef.textLink.save();
}

void setting::on_MoveSpeed_sliderMoved(int position)
{
    windoRef.setMoveSpeed(position);
    windoRef.config.moveSpeed = position;
    windoRef.config.save();
}

void setting::on_FontSize_valueChanged(int arg1)
{
    windoRef.setFontSize(arg1);
    windoRef.config.textSize = arg1;
    windoRef.config.save();
}

void setting::on_FontColorBtn_clicked(bool checked)
{
    Q_UNUSED(checked)
    QString color = ui->FontColor->text();
    if(color.at(0)!='#') {
        color = '#' + color;
    }
    windoRef.setFontColor(color);
    windoRef.config.textColor = color;
    windoRef.config.save();
}

void setting::on_AutoStart_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    if(initialSet == true){
        QFileInfo fileInfo(QCoreApplication::applicationFilePath());
        QString startDir = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation)
            + QDir::separator() + "Startup"
            + QDir::separator() + fileInfo.completeBaseName() + ".lnk";

        if(windoRef.config.isStartUp == false)
        {
            windoRef.config.isStartUp = true;
            windoRef.config.save();
            QFile::link(QCoreApplication::applicationFilePath(),startDir);
        }
        else
        {
            windoRef.config.isStartUp = false;
            windoRef.config.save();
            QFile file(startDir);
            file.remove();
        }
    }
}

void setting::on_Bold_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    if(initialSet == true){
        if(windoRef.config.isTextBold == false)
        {
            windoRef.config.isTextBold = true;
            windoRef.config.save();
            windoRef.setFontBold(windoRef.config.isTextBold);
        }
        else
        {
            windoRef.config.isTextBold = false;
            windoRef.config.save();
            windoRef.setFontBold(windoRef.config.isTextBold);
        }
    }
}

void setting::on_BackColorBtn_clicked()
{
    QString color = ui->BackColor->text();
    if(color == "x" || color == "X") {
        windoRef.config.backColor = color;
        windoRef.config.save();
        QMessageBox::information(this, tr("information"), tr("Please Restart Program"), tr("OK"));
        return;
    }
    else {
        if(color.at(0)!='#') {
            color = '#' + color;
        }
        windoRef.setBackColor(color);
        windoRef.config.backColor = color;
        windoRef.config.save();
    }
}

void setting::on_AlwaysOnTop_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    if(initialSet == true) {
        if(windoRef.config.isAlwaysOnTop == false) {
            windoRef.config.isAlwaysOnTop = true;
            windoRef.config.save();
            QMessageBox::information(this, tr("information"), tr("Please Restart Program"), tr("OK"));
        }
        else {
            windoRef.config.isAlwaysOnTop = false;
            windoRef.config.save();
            QMessageBox::information(this, tr("information"), tr("Please Restart Program"), tr("OK"));
        }
    }
}

void setting::on_UpdateCheck_clicked()
{
    ui->UpdateCheck->setEnabled(false);
    manager->get(this->request);
}
