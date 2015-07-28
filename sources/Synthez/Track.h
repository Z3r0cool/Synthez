#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <string>

/*
#define DO      1
#define REM     1.06
#define RE      1.12
#define MIM     1.19
#define MI      1.26
#define FA      1.33
#define SOLM    1.41
#define SOL     1.5
#define LAM     1.59
#define LA      1.68
#define SIM     1.78
#define SI      1.89
#define DOM     2
*/

#define DO      "c.wav"
#define REM     "d#.wav"
#define RE      "d.wav"
#define MIM     "e.wav"
#define MI      "e.wav"
#define FA      "f.wav"
#define SOLM    "g#.wav"
#define SOL     "g.wav"
#define LAM     "a#.wav"
#define LA      "a.wav"
#define SIM     "b#.wav"
#define SI      "b.wav"
#define DOM     "c#.wav"

class Track
{
public:
    Track(std::string, bool);

    std::string getTrackname() const;
    void        setTrackname(std::string);
    int         getNbSample() const;
    void        setNbSample(int);
    std::string getSample(int, int);
    bool        addSample(std::string);
    //bool        setSample(std::string, int);
    void        addTime(std::vector<bool>);
    bool        getNoteAt(int, int);
    void        addNoteAt(int, int);
    void        delNoteAt(int, int);
    std::vector<std::string>    getSoundfile();
    bool        getIsRythmic();

private:
    std::string                        _trackname;
    int                                _nbSample;
    std::vector<std::string>           _samples;
    std::vector< std::vector<bool> >   _times;
    bool                               _isRythmic;
};

#endif // TRACK_H
