#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include <cstring>
#include "Music.h"
#include "tinyxml.h"

class Loader
{
public:
    Loader(QString&);

    bool load();
    bool parse(Music*);

private:
    TiXmlDocument   _doc;
};

#endif // LOADER_H
