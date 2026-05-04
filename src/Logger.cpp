#include "Logger.h"
#include "Common.h"
#include <QDateTime>
#include <QTimeZone>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <cassert>

QString loggerGetLogLocation()
{
    static QString location;
    if (location.isEmpty())
    {
        // First location according to the Qt documentation is:
        //   "C:/Users/<USER>/AppData/Roaming/<APPNAME>" under Windows
        //   "~/.local/share/<APPNAME>" under Linux
        //   "~/Library/Application Support/<APPNAME>" under macOS
        QStringList locations = QStandardPaths::standardLocations(
                    QStandardPaths::AppDataLocation);
        if (!locations.isEmpty())
            location = locations.first();
        else
            assert(false);
    }
    return location;
}

void loggerReport(const QString& message, const QStringList& contexts)
{
    const char logFileName[] = "license_wizard.log";

    static bool firstCall = true;

    QDir().mkpath(loggerGetLogLocation());
    QFile file(loggerGetLogLocation() + "/" + logFileName);
    file.open(QFile::OpenModeFlag::Append);
    if (!file.isOpen())
    {
        assert(false);
        return;
    }

    QString text;
    if (firstCall)
    {
        if (file.size() != 0)
            text += "\n";

        // 80 asterisks and a new line
        text += "****************************************"
                "****************************************"
                "\n";
        firstCall = false;
    }

    const QDateTime time = QDateTime::currentDateTime();
    const QString timedatestamp = time.toString("dd.MM.yyyy hh:mm:ss");
#ifdef Q_OS_WIN
    const QString timezone = time.timeZone().displayName(
                time, QTimeZone::OffsetName);
#else
    // See: https://en.wikipedia.org/wiki/List_of_time_zone_abbreviations
    int delta = time.timeZone().offsetFromUtc(time);
    delta /= 30 * 60; // suppose resolution of a half of an hour
    const bool half = (delta % 2 == 1);
    delta /= 2;
    QString timezone = "UTC";
    if (delta >= 0)
        timezone += '+';
    else
        timezone += '-';
    if (delta < 0)
        delta = -delta;
    if (delta >= 0 && delta < 10)
        timezone += '0';
    timezone += QString::number(delta) + ':' + (half ? "30" : "00");
#endif
    text += timedatestamp + ' ' + timezone + " | " + message + "\n";
    foreach (const QString& context, contexts)
        text += "  " + context + "\n";
    if (isEnoughDiskSpace(
                static_cast<size_t>(text.toUtf8().size()), file.fileName()))
        file.write(text.toUtf8());
    file.close();
}
