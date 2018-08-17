#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include <QResizeEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QPropertyAnimation>
#include <QFontDatabase>
#include <QDesktopServices>

#include "fileio.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int posX;
    int posY;
    int Width;
    int Height;
    int Speed;
    QRect rec;
    QFont font;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
    SettingData setData;
    TextLink Link;

    void setSize(int w, int h);
    void setPos(int x, int y);
    void setSpeed(int s);
    void FontResize(int s);
    void SetFontColor(QString color);
    int getSpeed();

private slots:
    void TextLoading();
    void SetLoading();

    void ReloadText();
    void Openfile();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void PageUp();
    void PageDown();
    void Edit();

protected:
   void resizeEvent(QResizeEvent *event);
   void mousePressEvent(QMouseEvent * event);
   void mouseReleaseEvent(QMouseEvent * event);
   void mouseMoveEvent(QMouseEvent * event);
   int m_nMouseClick_X_Coordinate;
   int m_nMouseClick_Y_Coordinate;
};

#endif // MAINWINDOW_H
