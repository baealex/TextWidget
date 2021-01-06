#ifndef FILEIO_H
#define FILEIO_H

#include <QTextStream>
#include <QFile>

class TextLink {
private:
    QString link;
    QFile *file;

public:
    TextLink() {
        file = new QFile("temp.txt");
        if(file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            load();
        }
        file->close();
    }

    void setLink(QString link){
        this->link = link;
    }

    QString getLink(){
        return this->link;
    }

    void save()
    {
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out.setCodec("UTF-8");
        out.setCodec("Windows-949");
        out << this->link;
        file->close();
    }

    void load()
    {
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        in.setCodec("UTF-8");
        in.setCodec("Windows-949");
        this->link = in.readAll();
        file->close();
    }

    ~TextLink(){
        delete file;
    }
};

class Config {
private:
    QFile *file;

public:
    bool isAlwaysOnTop;
    bool isStartUp;
    int windowPosX;
    int windowPosY;
    int windowWidth;
    int windowHeight;
    int moveSpeed;
    int textSize;
    QString textColor;
    QString backColor;
    bool isTextBold;

    Config(){
        file = new QFile("config.conf");
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            isAlwaysOnTop = 0;
            isStartUp = 0;
            windowPosX = 100;
            windowPosY = 100;
            windowWidth = 400;
            windowHeight = 300;
            moveSpeed = 50;
            textSize = 12;
            textColor = "#000000";
            backColor = "x";
            isTextBold = 0;
        }
        else
        {
            load();
        }
    }

    void save(){
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out << isAlwaysOnTop << "\n"
            << isStartUp << "\n"
            << windowPosX << "\n"
            << windowPosY << "\n"
            << windowWidth << "\n"
            << windowHeight << "\n"
            << moveSpeed << "\n"
            << textSize << "\n"
            << textColor << "\n"
            << backColor << "\n"
            << isTextBold;
        file->close();
    }

    void load(){
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        isAlwaysOnTop = in.readLine().toInt();
        isStartUp = in.readLine().toInt();
        windowPosX = in.readLine().toInt();
        windowPosY = in.readLine().toInt();
        windowWidth = in.readLine().toInt();
        windowHeight = in.readLine().toInt();
        moveSpeed = in.readLine().toInt();
        textSize = in.readLine().toInt();
        textColor = in.readLine();
        backColor = in.readLine();
        isTextBold = in.readLine().toInt();
        file->close();
    }

    ~Config(){
        delete file;
    }
};

#endif // FILEIO_H
