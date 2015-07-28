#include "Loader.h"
#include "Track.h"
#include <QDebug>

Loader::Loader(QString &filename)
{
    TiXmlDocument   doc(filename.toStdString().c_str());

    _doc = doc;
}

bool Loader::load()
{
    if (!_doc.LoadFile())
        return false;
    return true;
}

bool Loader::parse(Music *music)
{
    TiXmlElement    *pRoot;
    TiXmlElement    *pParm;
    TiXmlElement    *pParmm;
    TiXmlElement    *pParmNote;

    if ((pRoot = _doc.FirstChildElement("music")))
    {
        int tempo;
        int duration;
        int attime;
        int value;
        bool isr;

        if (!(pRoot->QueryIntAttribute("tempo", &tempo)))
            music->setTempo(tempo);
        if (!(pRoot->QueryIntAttribute("duration", &duration)))
            music->setDuration(int(duration));

        // Seek for tracks
        for (pParm = pRoot->FirstChildElement("track"); pParm != NULL; pParm = pParm->NextSiblingElement("track"))
        {
            Track           *newtrack;
            std::string     trackname;

            if (pParm->Attribute("name"))
                trackname = pParm->Attribute("name");
            else
                trackname = "Non défini";

            !std::strcmp(pParm->Attribute("type"), "M") ? isr = false : isr = true;
            newtrack = new Track(trackname, isr);
            if (pParm->Attribute("type"))
            {
                // Searching for soundfiles
                for (pParmm = pParm->FirstChildElement("soundfile"); pParmm != NULL; pParmm = pParmm->NextSiblingElement("soundfile"))
                {
                    if (pParmm->Attribute("src"))
                    {
                        if (newtrack->addSample(pParmm->Attribute("src")))
                            newtrack->setNbSample(newtrack->getNbSample() + 1);
                    }
                }

                attime = 0;
                for (pParmm = pParm->FirstChildElement("time"); pParmm != NULL; pParmm = pParmm->NextSiblingElement("time"))
                {
                    std::vector<bool> notes;
                    for (pParmNote = pParmm->FirstChildElement("note"); pParmNote != NULL; pParmNote = pParmNote->NextSiblingElement("note"))
                    {
                        pParmNote->QueryIntAttribute("value", &value);
                        value == 1 ? notes.push_back(true) : notes.push_back(false);
                    }
                    newtrack->addTime(notes);
                    attime++;
                }

                // If pas tous les times
                if (attime < music->getDuration())
                {
                    for (int i = attime; i < music->getDuration(); ++i)
                    {
                        std::vector<bool> notes;

                        for (int i = 0; i <= 13; ++i)
                            notes.push_back(false);
                        newtrack->addTime(notes);
                    }
                }
            }
            music->addTrack(newtrack);
            music->setNbTrack(music->getNbTrack() + 1);
        }
        return true;
    }
    return false;
}
