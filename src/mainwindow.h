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
#include <QTimer>

#include "fileio.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int windowPosX;
    int windowPosY;
    int windowWidth;
    int windowHeight;
    int moveSpeed;

    QRect rect;
    QFont font;

    bool isMouseDown;

public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();

    Ui::MainWindow *ui;
    Config config;
    TextLink textLink;

    QString openTextSelector();
    QString readTextFile(QString fileName);

    void setWindowSize(int weight, int height);
    void setWindowPos(int x, int y);
    void setMoveSpeed(int speed);
    void setFontSize(int size);
    void setFontColor(QString color);
    void setBackColor(QString color);
    void setFontBold(int isTextBold);

    int getMoveSpeed();

private slots:
    void loadText();
    void loadConfig();
    void openTextFileSlot();
    void openTextSeletorSlot();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void scrollUp();
    void scrollDown();
    void openSetting();

protected:
   void resizeEvent(QResizeEvent *event);
   void mousePressEvent(QMouseEvent * event);
   void mouseReleaseEvent(QMouseEvent * event);
   void mouseMoveEvent(QMouseEvent * event);
   int m_nMouseClick_X_Coordinate;
   int m_nMouseClick_Y_Coordinate;
};

#endif // MAINWINDOW_H
