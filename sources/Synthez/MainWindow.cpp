#include "MainWindow.h"

MainWindow::MainWindow()
{
    _window = new QWidget();
    _layout = new QGridLayout();
    _group = new QButtonGroup();
    _timer = new QTimer();

    _layout->setVerticalSpacing(0);
    _layout->setHorizontalSpacing(0);
    _window->setStyleSheet("background: #373737");
    _window->setLayout(_layout);
    _window->setMinimumHeight(400);
    _window->setMinimumWidth(800);

    setCentralWidget(_window);

    createActions();
    createMenus();

    _music = new Music();
    _ready = false;
}

void MainWindow::createActions()
{
    // actNew = new QAction("&Nouveau", this);

    actOpen = new QAction("&Ouvrir", this);
    actOpen->setShortcut(QKeySequence("Ctrl+O"));
    connect(actOpen, SIGNAL(triggered()), this, SLOT(openFile()));

    actSave = new QAction("&Enregistrer sous", this);
    actSave->setShortcut(QKeySequence("Ctrl+S"));
    connect(actSave, SIGNAL(triggered()), this, SLOT(saveFile()));

    actQuit = new QAction("&Quitter", this);
    actQuit->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));


    actPlay = new QAction("&Play", this);
    actPlay->setIcon(QIcon("./icons/play.png"));
    connect(actPlay, SIGNAL(triggered()), this, SLOT(playSound()));

    actPause = new QAction("&Pause", this);
    actPause->setIcon(QIcon("./icons/pause.png"));
    connect(actPause, SIGNAL(triggered()), this, SLOT(pauseSound()));

    actStop = new QAction("&Stop", this);
    actStop->setIcon(QIcon("./icons/stop.png"));
    connect(actStop, SIGNAL(triggered()), this, SLOT(stopSound()));

    actChangeTempo = new QPushButton();
    connect(actChangeTempo, SIGNAL(clicked()), this, SLOT(changeTempo()));

    actAbout = new QAction("&A Propos", this);
    connect(actAbout, SIGNAL(triggered()), this, SLOT(about()));

    _timer->connect(_timer, SIGNAL(timeout()), this, SLOT(playSoundPlusOne()));
    connect(_group, SIGNAL(buttonClicked(int)), this, SLOT(buttonWasClicked(int)));
}

void MainWindow::createMenus()
{
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuMusique = menuBar()->addMenu("&Musique");
    QMenu *menuH = menuBar()->addMenu("&?");

    menuFichier->addAction(actOpen);
    menuFichier->addAction(actSave);
    menuFichier->addAction(actQuit);

    menuMusique->addAction(actPlay);
    menuMusique->addAction(actPause);
    menuMusique->addAction(actStop);

    menuH->addAction(actAbout);
}


void MainWindow::createGrid()
{
    QScrollArea     *frame = new QScrollArea();
    QWidget         *grid = new QWidget;
    QGridLayout     *gridlayout = new QGridLayout;

    grid->setLayout(gridlayout);
    grid->setStyleSheet("background: #616362;""border: 1px solid #696969");
    gridlayout->setVerticalSpacing(0);
    gridlayout->setHorizontalSpacing(0);

    createEntete(gridlayout);
    createSlider(gridlayout);
    createTracks(gridlayout);

    frame->setWidget(grid);
    frame->setStyleSheet("background: #575757");
    _layout->addWidget(frame, 0, 1);
    _ready = true;
}

void MainWindow::createEntete(QGridLayout *layout)
{
    QWidget         *entete = new QWidget;
    QGridLayout     *entetelayout = new QGridLayout;
    QLabel          *tempo = new QLabel();
    QLabel          *blankv = new QLabel();

    if (!_ready)
    {
        _tbMusic = addToolBar("Music");
        _tbMusic->addAction(actPlay);
        _tbMusic->addAction(actPause);
        _tbMusic->addAction(actStop);
    }

    entete->setLayout(entetelayout);
    entete->setStyleSheet("border: 0;");
    entetelayout->setVerticalSpacing(0);
    entetelayout->setHorizontalSpacing(0);
    tempo->setFixedWidth(100);
    tempo->setFixedHeight(30);
    tempo->setText("Tempo");
    tempo->setStyleSheet("border: 0;""color: #F5F5F5");
    entetelayout->addWidget(tempo, 0, 0);

    actChangeTempo->setFixedWidth(100);
    actChangeTempo->setText(ITOSTR(_music->getTempo()).c_str());
    actChangeTempo->setStyleSheet("border: 0;""color: #F5F5F5");
    entetelayout->addWidget(actChangeTempo, 0, 1);

    blankv->setFixedWidth(200);
    entetelayout->addWidget(blankv, 0, 2);

    for (int i = 3; i < _music->getDuration() + 3; i++)
    {
        QLabel  *label = new QLabel();

        label->setStyleSheet("border: 1px solid #373737;""background-color: #F5F5F5 ");
        label->setFixedWidth(40);
        label->setFixedHeight(30);
        label->setAlignment(Qt::AlignCenter);
        label->setText(ITOSTR(i - 3).c_str());
        entetelayout->addWidget(label, 0, i);
    }
    layout->addWidget(entete, 0, 0);
}

void MainWindow::createSlider(QGridLayout *layout)
{
    QWidget         *slid = new QWidget;
    QGridLayout     *slidlayout = new QGridLayout;
    QLabel          *blankv = new QLabel();

    _slider = new QSlider(Qt::Horizontal);
    slid->setLayout(slidlayout);
    slid->setStyleSheet("border: 0;""color: #F5F5F5");

    blankv->setFixedWidth(380);

    _slider->setGeometry(10, 60, 150, 20);
    _slider->setMinimum(0);
    _slider->setMaximum(_music->getDuration());
    _slider->setSingleStep(1);
    slidlayout->addWidget(_slider, 0, 1);
    slidlayout->addWidget(blankv, 0, 0);

    layout->addWidget(slid, 1, 0);
}

void MainWindow::createTracks(QGridLayout *layout)
{
    int bid = 0;

    for (int itrack = 0; itrack < _music->getNbTrack(); ++itrack)
    {
        QWidget         *track = new QWidget;
        QGridLayout     *tracklayout = new QGridLayout;
        QLabel          *trackname = new QLabel();
        QLabel          *trackna = new QLabel();
        QLabel          *tracksoundfile = new QLabel();

        QLabel          *labelDo = new QLabel("Do");
        QLabel          *labelRem = new QLabel("Ré#");
        QLabel          *labelRe = new QLabel("Re");
        QLabel          *labelMim = new QLabel("Mi#");
        QLabel          *labelMi = new QLabel("Mi");
        QLabel          *labelFa = new QLabel("Fa");
        QLabel          *labelSolm = new QLabel("Sol#");
        QLabel          *labelSol = new QLabel("Sol");
        QLabel          *labelLam = new QLabel("La#");
        QLabel          *labelLa = new QLabel("La");
        QLabel          *labelSim = new QLabel("Si#");
        QLabel          *labelSi = new QLabel("Si");
        QLabel          *labelDom = new QLabel("Do#");

        track->setLayout(tracklayout);
        track->setStyleSheet("background: #F5F5F5;");
        tracklayout->setVerticalSpacing(0);
        tracklayout->setHorizontalSpacing(0);

        trackname->setFixedWidth(100);
        trackname->setFixedHeight(30);
        trackname->setStyleSheet("border: 0;""font-weight: bold;");
        trackname->setText("Trackname");

        tracksoundfile->setFixedWidth(100);
        tracksoundfile->setFixedHeight(30);
        tracksoundfile->setStyleSheet("border: 0;""font-weight: bold;");
        tracksoundfile->setText("Soundfile");

        trackna->setFixedWidth(100);
        trackna->setText(_music->getTrack(itrack)->getTrackname().c_str());
        trackna->setStyleSheet("border: 0;""font-style: italic;");

        tracklayout->addWidget(trackname, 0, 0);
        tracklayout->addWidget(trackna, 0 ,1);

        if (!_music->getTrack(itrack)->getIsRythmic())
        {
            tracklayout->addWidget(tracksoundfile, 1, 0);
            std::vector<std::string> sfs = _music->getTrack(itrack)->getSoundfile();
            int cnt = 1;
            for (std::vector<std::string>::iterator it = sfs.begin(); it != sfs.end(); ++it)
            {
                QLabel *labelR = new QLabel();

                labelR->setFixedWidth(200);
                labelR->setFixedHeight(30);
                labelR->setStyleSheet("border: 0;""font-style: italic;");
                std::string txt = *it;
                labelR->setText(txt.c_str());
                tracklayout->addWidget(labelR, cnt, 1);
                cnt++;
            }
        }

        labelDo->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelRem->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelRe->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelMim->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelMi->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelFa->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelSolm->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelSol->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelLam->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelLa->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelSim->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelSi->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
        labelDom->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");

        if (!_music->getTrack(itrack)->getIsRythmic())
        {
            tracklayout->addWidget(labelDo, 0, 2);
            tracklayout->addWidget(labelRem, 1, 2);
            tracklayout->addWidget(labelRe, 2, 2);
            tracklayout->addWidget(labelMim, 3, 2);
            tracklayout->addWidget(labelMi, 4, 2);
            tracklayout->addWidget(labelFa, 5, 2);
            tracklayout->addWidget(labelSolm, 6, 2);
            tracklayout->addWidget(labelSol, 7, 2);
            tracklayout->addWidget(labelLam, 8, 2);
            tracklayout->addWidget(labelLa, 9, 2);
            tracklayout->addWidget(labelSim, 10, 2);
            tracklayout->addWidget(labelSi, 11, 2);
            tracklayout->addWidget(labelDom, 12, 2);
        }
        else
        {
            std::vector<std::string> sfs = _music->getTrack(itrack)->getSoundfile();
            int cnt = 0;
            for (std::vector<std::string>::iterator it = sfs.begin(); it != sfs.end(); ++it)
            {
                QLabel *labelR = new QLabel();

                labelR->setFixedWidth(200);
                labelR->setFixedHeight(30);
                labelR->setStyleSheet("border: 1px solid #E8E8E8;""margin-left: 20px;""margin-right: 10px");
                std::string txt = *it;
                labelR->setText(txt.c_str());
                tracklayout->addWidget(labelR, cnt, 2);
                cnt++;
            }
        }

        for (int i = 3; i < _music->getDuration() + 3; ++i)
        {
            if (!_music->getTrack(itrack)->getIsRythmic())
            {
                for (int j = 0; j < 13; j++)
                {
                    QPushButton         *actSound = new QPushButton();
                    std::vector<int>    vecInt;

                    if (_music->getTrack(itrack)->getNoteAt(i - 3, j))
                    {
                        actSound->setStyleSheet("border: 1px solid #E8E8E8;" "background-color: #31A400");
                        _buttons.push_back(true);
                        vecInt.push_back(true);
                    }
                    else
                    {
                        actSound->setStyleSheet("border: 1px solid #E8E8E8;");
                        _buttons.push_back(false);
                        vecInt.push_back(false);
                    }
                    vecInt.push_back(i - 3);
                    vecInt.push_back(j);
                    _vecButtons.push_back(vecInt);
                    actSound->setFixedWidth(40);
                    actSound->setFixedHeight(30);
                    actSound->setText("");
                    tracklayout->addWidget(actSound, j, i);
                    _group->addButton(actSound, bid);
                    bid++;
                }
            }
            else
            {
                for (int nbsample = 0; nbsample < _music->getTrack(itrack)->getNbSample(); ++nbsample)
                {
                    QPushButton         *actSound = new QPushButton();
                    std::vector<int>    vecInt;

                    if (_music->getTrack(itrack)->getNoteAt(i - 3, nbsample))
                    {
                        actSound->setStyleSheet("border: 1px solid #E8E8E8;" "background-color: #31A400");
                        _buttons.push_back(true);
                        vecInt.push_back(true);
                    }
                    else
                    {
                        actSound->setStyleSheet("border: 1px solid #E8E8E8;");
                        _buttons.push_back(false);
                        vecInt.push_back(false);
                    }
                    vecInt.push_back(i - 3);
                    vecInt.push_back(nbsample);
                    _vecButtons.push_back(vecInt);
                    actSound->setFixedWidth(40);
                    actSound->setFixedHeight(30);
                    actSound->setText("");
                    tracklayout->addWidget(actSound, nbsample, i);
                    _group->addButton(actSound, bid);
                    bid++;
                }
            }
        }
        layout->addWidget(track, itrack + 2, 0);
    }
}

/*
**
**
*/

void MainWindow::openFile()
{
    QString     filename = QFileDialog::getOpenFileName(this, tr("Ouvrir fichier"), QString(), tr("Fichier XML (*.xml)"));
    Loader      loader(filename);

    if (!filename.isEmpty())
    {
        if (loader.load())
        {
            if (!loader.parse(_music))
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier d'entrée est corrompu !"));
            else
                createGrid();
        }
        else
            QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier !"));
    }
}

std::string MainWindow::parseContent()
{
    std::string ret;

    ret = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
    ret += "<music tempo=\"";
    ret += ITOSTR(_music->getTempo());
    ret += "\" duration=\"";
    ret += ITOSTR(_music->getDuration());
    ret += "\">\n";

    for (int i = 0; i < _music->getNbTrack(); ++i)
    {
        ret += "<track id=\"";
        ret += ITOSTR(i);
        ret += "\" name=\"";
        ret += _music->getTrack(i)->getTrackname();
        ret += "\" type=\"";
        _music->getTrack(i)->getIsRythmic() ? ret += "R" : ret += "M";
        ret += "\">\n";


        std::vector<std::string> sf = _music->getTrack(i)->getSoundfile();
        for (int j = 0; j < int(sf.size()); ++j)
        {
            ret += "<soundfile src=\"";
            ret += sf[j];
            ret += "\"></soundfile>\n";
        }
        for (int k = 0; k <= _music->getDuration() - 1; ++k)
        {
            ret += "<time id=\"";
            ret += ITOSTR(k);
            ret += "\">\n";
            if (!_music->getTrack(i)->getIsRythmic())
            {
                for (int m = 0; m < 13; ++m)
                {
                    ret += "<note value=\"";
                    if (_music->getTrack(i)->getNoteAt(k, m))
                        ret += "1";
                    else
                        ret += "0";
                    ret += "\"></note>\n";
                }
            }
            else
            {
                for (int s = 0; s < _music->getTrack(i)->getNbSample(); ++s)
                {
                    ret += "<note value=\"";
                    _music->getTrack(i)->getNoteAt(k, s) ? ret += "1" : ret += "0";
                    ret += "\"></note>\n";
                }
            }
            ret += "</time>\n";
        }
        ret += "</track>\n";
    }
    ret += "</music>\n";
    return ret;
}

void MainWindow::saveFile()
{
    QString     filename = QFileDialog::getSaveFileName(this, tr("Enregistrer sous"), QString(), tr("Fichier XML (*.xml)"));
    QString     txt = parseContent().c_str();
    QFile       file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream flux(&file);

        flux << txt;
        file.close();
    }
    else
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'enregistrer le fichier !"));
}

void MainWindow::playSound()
{
    if (_ready)
        _timer->start(60000/_music->getTempo());
    else
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun fichier chargé !"));
}

void MainWindow::playSoundPlusOne()
{
    for (int j = 0; j < _music->getNbTrack(); j++)
        if (!_music->getTrack(j)->getIsRythmic())
        {
            for (int i = 0; i < 13; i++)
                if (_music->getTrack(j)->getNoteAt(_slider->value(), i))
                    for (int k = 0; k < _music->getTrack(j)->getNbSample(); ++k)
                        QSound::play(_music->getTrack(j)->getSample(k, i).c_str());
        }
        else
        {
            for (int i = 0; i < _music->getTrack(j)->getNbSample(); ++i)
                if (_music->getTrack(j)->getNoteAt(_slider->value(), i))
                    QSound::play(_music->getTrack(j)->getSample(i, 0).c_str());
        }

    if (_slider->value() >= _music->getDuration() - 1)
        _timer->stop();

    _slider->setValue(_slider->value() + 1);
}

void MainWindow::pauseSound()
{
    if (_ready)
        _timer->stop();
    else
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun fichier chargé !"));
}

void MainWindow::stopSound()
{
    if (_ready)
    {
        _timer->stop();
        _slider->setValue(0);
    }
    else
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun fichier chargé !"));
}

void MainWindow::buttonWasClicked(int bid)
{
    int trackid = 0;

    if (bid < ((13 * _music->getDuration()) * 1))
        trackid = 0;
    else if (bid < ((13 * _music->getDuration()) * 2))
        trackid = 1;
    else if (bid < ((13 * _music->getDuration()) * 3))
        trackid = 2;
    else if (bid < ((13 * _music->getDuration()) * 4))
        trackid = 3;
    else if (bid < ((13 * _music->getDuration()) * 5))
        trackid = 4;

    if (_buttons[bid])
    {
        _buttons[bid] = false;
        _vecButtons[bid][0] = false;
        _music->getTrack(trackid)->delNoteAt(_vecButtons[bid][1], _vecButtons[bid][2]);
        _group->button(bid)->setStyleSheet("border: 1px solid #E8E8E8;""background-color: ");
    }
    else
    {
        _buttons[bid] = true;
        _vecButtons[bid][0] = true;
        _music->getTrack(trackid)->addNoteAt(_vecButtons[bid][1], _vecButtons[bid][2]);
        _group->button(bid)->setStyleSheet("border: 1px solid #E8E8E8;""background-color: #31A400");
    }
}

void MainWindow::changeTempo()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Changement du tempo"),tr("Nouvelle valeur :"), QLineEdit::Normal, ITOSTR(_music->getTempo()).c_str(), &ok);
    if (ok && !text.isEmpty())
    {
        _music->setTempo(text.toInt());
        actChangeTempo->setText(text);
        QMessageBox::information(this, tr("Changement du tempo"), tr("Le tempo a était changé !"));
    }
}

void MainWindow::changeDuration()
{
    // Todo
}

void MainWindow::about()
{
    QMessageBox::information(this, tr("A propos"), tr("Synthez is an audio sampler developped on c++ with Qt.\n\nIt's an open source project, find sources on github:\ngithub.com/Z3r0cool/Synthez/\n\nMaxime TATON (taton_m)\n"));
}
