#ifndef LOGGER_H
#define LOGGER_H

#include <QStringList>

QString loggerGetLogLocation();

void loggerReport(
        const QString& message, const QStringList& contexts = QStringList());

#endif // LOGGER_H
