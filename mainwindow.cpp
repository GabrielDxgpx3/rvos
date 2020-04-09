#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QScreen>
#include <regex>
#include <QDebug>
#include <iostream>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

using namespace std;

struct canal{
    string nome;
    string logo;
    string url;
};


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //this->setWindowState(Qt::WindowFullScreen);

    this->infoFrame = new QFrame(this);
    this->lista = new QListWidget;

    //player = new QMediaPlayer(this);
    //QVideoWidget* vw = new QVideoWidget(this);
    
    vlcinstance = new VlcInstance(VlcCommon::args(), this);
    vlcplayer = new VlcMediaPlayer(vlcinstance);
    vlcplayer->setVideoWidget(ui->videoFrame);

    ui->videoFrame->setMediaPlayer(vlcplayer);



    /*connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onPlayerStateChange(QMediaPlayer::MediaStatus)));


    player->setVideoOutput(vw);
    player->setMedia(QUrl("http://tv.factoryiptv.com:80/a9lh0j3khOcB/c6khh0ChFPL/50614"))*/;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();


    int h = screenGeometry.height() * 0.65;
    int w = screenGeometry.width() * 0.65;
    int res_w = screenGeometry.width() * 0.35;

    ui->videoFrame->setMinimumWidth(w);
    ui->videoFrame->setMinimumHeight(h);

    ui->infoFrame->setMinimumWidth(w);


    this->lista->setMinimumWidth(res_w);



}

void MainWindow::MakeLista(vector<string> canais){

    regex logo_r("tvg-logo=\"([^\"]+)\"");
    //regex nome_r("tvg-name=\"([^\"]+)\"");
    regex nome_r("(\",)([^\n]+)");
    regex url_r("\n(https?\\S+)");
    smatch mth;


    for(int i = 0; i < (int) canais.size(); i++){

        QListWidgetItem* widgetItem = new QListWidgetItem(ui->lista);

        regex_search(canais.at(i), mth, logo_r);
        widgetItem->setData(0, QString::fromStdString(mth[1]));

        QUrl urlLogo =  QUrl(QString::fromStdString(mth[1]));
       // QImage logo = QImage(url.toLocalFile());


        widgetItem->setIcon(QIcon(urlLogo.toLocalFile()));
        qDebug() << urlLogo;

        regex_search(canais.at(i), mth, nome_r);

        widgetItem->setFont(QFont("Lato Black", 16));
        widgetItem->setText(QString::fromStdString(mth[2]));


        regex_search(canais.at(i), mth, url_r);
        widgetItem->setData(1, QString::fromStdString(mth[1]));
    }

}

void MainWindow::on_lista_doubleClicked(){

    QString url = ui->lista->currentItem()->data(1).toString();
    qDebug() << url;

    vlcmedia = new VlcMedia(url, vlcinstance);
    vlcplayer->open(vlcmedia);
    vlcplayer->play();



}


MainWindow::~MainWindow(){
    delete ui;
}



