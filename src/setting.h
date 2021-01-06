#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QFileDialog>
#include <QDesktopServices>

#include "fileio.h"
#include  "mainwindow.h"

namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(MainWindow &ref, QWidget *parent = 0);
    ~setting();

private slots:
    void on_textChanger_clicked();
    void on_Homepage_clicked();
    void on_MoveSpeed_sliderMoved(int position);
    void on_FontSize_valueChanged(int arg1);
    void on_FontColorBtn_clicked(bool checked);
    void on_AutoStart_stateChanged(int arg1);
    void on_Bold_stateChanged(int arg1);
    void on_BackColorBtn_clicked();
    void on_AlwaysOnTop_stateChanged(int arg1);

private:
    Ui::setting *ui;
    MainWindow &windoRef;
    bool initialSet;
};

#endif // SETTING_H
