#ifndef FILEIO_H
#define FILEIO_H

#include <QTextStream>
#include <QFile>

class TextLink{
private:
    QString LINK;
    QFile *file;
public:
    TextLink(){
        file = new QFile;
        file->setFileName("TextLink.txt");
        if(file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            LOAD();
        }
    }
    void setLink(QString Temp){
        LINK = Temp;
    }
    QString getLink(){
        return LINK;
    }
    void SAVE()
    {
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out.setCodec("UTF-8");
        out << LINK;
        file->close();
    }
    void LOAD()
    {
        file->open(QIODevice::ReadOnly);
        QTextStream in(file);
        in.setCodec("UTF-8");
        LINK = in.readAll();
        file->close();
    }
    ~TextLink(){
        delete file;
    }
};

class SettingData{
private:
    QFile *file;
public:
    int AlwaysOnTop;
    int StartUp;
    int PosX;
    int PosY;
    int Width;
    int Height;
    int Speed;
    int TextSize;
    QString TextColor;
    SettingData(){
        file = new QFile;
        file->setFileName("USerconfig.dll");
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            AlwaysOnTop = 0;
            StartUp = 0;
            PosX = 100;
            PosY = 100;
            Width = 400;
            Height = 300;
            Speed = 50;
            TextSize = 12;
            TextColor = "#000000";
        }
        else
        {
            LOAD();
        }
    }
    void SAVE(){
        file->open(QIODevice::WriteOnly);
        QTextStream out(file);
        out << AlwaysOnTop << "\n" << StartUp << "\n"
            << PosX << "\n" << PosY << "\n" << Width << "\n" << Height << "\n"
            << Speed << "\n" << TextSize << "\n" << TextColor;
        file->close();
    }
    void LOAD(){
         file->open(QIODevice::ReadOnly);
         QTextStream in(file);
         AlwaysOnTop = in.readLine().toInt();
         StartUp = in.readLine().toInt();
         PosX = in.readLine().toInt();
         PosY = in.readLine().toInt();
         Width = in.readLine().toInt();
         Height = in.readLine().toInt();
         Speed = in.readLine().toInt();
         TextSize = in.readLine().toInt();
         TextColor = in.readLine();
         file->close();
    }
    ~SettingData(){
        delete file;
    }
};

#endif // FILEIO_H
