#ifndef VERSION_H
#define VERSION_H

#include <QString>
#include "ver.h"

inline QString getVersionString()
{
    // LW_VERSION format: (major, unused, minor, patch)
    const char numbers[] = { LW_VERSION };
    QString string = QString::number(numbers[0]) + '.' +
            QString::number(numbers[2]) + '.' + QString::number(numbers[3]);
    return string;
}

#endif // VERSION_H
