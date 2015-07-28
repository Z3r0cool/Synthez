#ifndef MUSIC_H
#define MUSIC_H

#include "Track.h"

class Music
{
public:
    Music();

    int     getTempo() const;
    void    setTempo(int);
    int     getDuration() const;
    void    setDuration(int);
    int     getNbTrack() const;
    void    setNbTrack(int);
    Track   *getTrack(int);
    void    addTrack(Track*);
    //void    setTrack(Track*, int);

private:
    int     _tempo;
    int     _duration;
    int     _nbTrack;

    std::vector<Track*> _tracks;
};

#endif // MUSIC_H
