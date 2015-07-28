#include "Track.h"
#include <QDebug>
#include <unistd.h>

Track::Track(std::string trackname, bool isRythmic) : _trackname(trackname), _isRythmic(isRythmic)
{

}

std::string Track::getTrackname() const
{
    return _trackname;
}

void Track::setTrackname(std::string trackname)
{
    _trackname = trackname;
}

int Track::getNbSample() const
{
    return _samples.size();
}

void Track::setNbSample(int nbSample)
{
    _nbSample = nbSample;
}

std::vector<std::string> Track::getSoundfile()
{
    return _samples;
}

bool Track::getIsRythmic()
{
    return _isRythmic;
}

std::string Track::getSample(int sampleNum, int note)
{
    // TODO: pitch

    std::string ret = _samples[sampleNum];

    if (_isRythmic)
        return ret.append(LA);

    switch(note)
    {
        case 0: ret.append(DO); break;
        case 1: ret.append(REM); break;
        case 2: ret.append(RE); break;
        case 3: ret.append(MIM); break;
        case 4: ret.append(MI); break;
        case 5: ret.append(FA); break;
        case 6: ret.append(SOLM); break;
        case 7: ret.append(SOL); break;
        case 8: ret.append(LAM); break;
        case 9: ret.append(LA); break;
        case 10: ret.append(SIM); break;
        case 11: ret.append(SI); break;
        case 12: ret.append(DOM); break;
    }
    return ret;
}

bool Track::addSample(std::string soundfile)
{
    // TODO: If dossier existe
    _samples.push_back(soundfile);
    return true;

    //return false;
}

void Track::addTime(std::vector<bool> notes)
{
    _times.push_back(notes);
}

bool Track::getNoteAt(int time, int note)
{
    return (_times[time][note]);
}

void Track::addNoteAt(int pos, int note)
{
    _times[pos][note] = true;
}

void Track::delNoteAt(int pos, int note)
{
    _times[pos][note] = false;
}
