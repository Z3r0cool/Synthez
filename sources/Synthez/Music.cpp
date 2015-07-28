#include "Music.h"

Music::Music() : _tempo(0), _duration(0), _nbTrack(0)
{

}

int Music::getTempo() const
{
    return _tempo;
}

void Music::setTempo(int tempo)
{
    _tempo = tempo;
}

int Music::getDuration() const
{
    return _duration;
}

void Music::setDuration(int duration)
{
    _duration = duration;
}

int Music::getNbTrack() const
{
    return _nbTrack;
}

void Music::setNbTrack(int nbTrack)
{
    _nbTrack = nbTrack;
}

Track *Music::getTrack(int trackNum)
{
    return _tracks[trackNum];
}

void Music::addTrack(Track *track)
{
    _tracks.push_back(track);
}
