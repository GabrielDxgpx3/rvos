#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QListWidget>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class VlcWidgetVideo;

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void MakeLista(std::vector<std::string>);

private slots:
    void on_lista_doubleClicked();

private:
    Ui::MainWindow *ui;
    QListWidget* lista;
    QFrame* infoFrame;

    VlcWidgetVideo* videoFrame;
    VlcInstance* vlcinstance;
    VlcMedia* vlcmedia;
    VlcMediaPlayer* vlcplayer;
};
#endif // MAINWINDOW_H
