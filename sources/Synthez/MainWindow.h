#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QGridLayout>
#include <QIcon>
#include <QTimer>
#include <QSound>
#include <sstream>

#include "Music.h"
#include "Loader.h"

#define ITOSTR( x ) dynamic_cast< std::ostringstream & >( \
                ( std::ostringstream() << std::dec << x ) ).str()

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    QWidget         *_window;
    QGridLayout     *_layout;
    QButtonGroup    *_group;
    QSlider         *_slider;
    QTimer          *_timer;
    QToolBar        *_tbMusic;

    bool            _ready;

    // Actions
    QAction     *actOpen;
    QAction     *actSave;
    QAction     *actQuit;
    QAction     *actPlay;
    QAction     *actPause;
    QAction     *actStop;

    QAction     *actAbout;

    // Updates param
    QPushButton *actChangeTempo;
    QPushButton *actChangeDuration;

    void        createActions();
    void        createMenus();

    void        createGrid();
    void        createEntete(QGridLayout*);
    void        createSlider(QGridLayout*);
    void        createTracks(QGridLayout*);

    std::string parseContent();

    Music       *_music;
    std::vector <std::vector<int> > _vecButtons;
    std::vector<bool>               _buttons;

private slots:
    void        openFile();
    void        saveFile();
    void        playSound();
    void        playSoundPlusOne();
    void        pauseSound();
    void        stopSound();

    void        buttonWasClicked(int);

    void        changeTempo();
    void        changeDuration();
    void        about();
};

#endif // MAINWINDOW_H
