#include "mainwindow.h"

#include <iostream>
#include <QApplication>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <VLCQtCore/Common.h>


using namespace std;

string explode(const string& s, const string& f, bool firsField);
int countSubstring(const std::string& str, const std::string& sub);
void split(vector<string>* results, const string& s, const string& f);

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
    VlcCommon::setPluginPath(a.applicationDirPath() + "/plugins");
    
    MainWindow w;

    QFile file("/home/worm/iptv.m3u");

    if(!file.exists()){
        qDebug() << "Esse arquivo não existe";
        return 0;
    }

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "erro ao abrir arquivo";
        return 0;
    }

    string canais = file.readAll().toStdString();
    string teste = explode(canais, "EXTM3U", false);

    vector<string> can = {};
    split(&can, teste, "#EXTINF:-1 ");


    w.show();
    w.MakeLista(can);
    return a.exec();
}

string explode(const string& s, const string& f, bool firstField){

   int pos = s.find(f) + f.size();

   if(firstField){
       return s.substr(0, --pos);
   }else{
       return s.substr(pos);
   }

}

void split(vector<string>* results, const string& s, const string& f){

    bool existMatchs = true;
    int currentPos = 0;
    int findPos = 0;
    int size = f.size();
    bool first = true;

    while(existMatchs){

        findPos = s.find(f, currentPos);

        if((size_t) findPos == string::npos){
            break;
        }

        string temp = s.substr(currentPos, findPos - currentPos);

        if(first){
           currentPos = findPos + size;
           first = false;
           continue;
        }

        results->push_back(temp);
        currentPos = findPos + size;

    }

}

int countSubstring(const std::string& str, const std::string& sub){

    if (sub.length() == 0) return 0;

    int count = 0;

    for(size_t offset = str.find(sub); offset != std::string::npos; offset = str.find(sub, offset + sub.length())){
        ++count;
    }

    return count;
}
















