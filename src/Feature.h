#ifndef FEATURE_H
#define FEATURE_H

#include "DeviceChecker.h"
#include <QDateTime>

inline QString getDateString(const uint64_t date)
{
    return QDateTime::fromTime_t(
                static_cast<uint32_t>(date),
                Qt::TimeSpec::UTC).toString("dd.MM.yyyy");
}

inline QString featureDate(
        const DeviceChecker::FeatureInfo& featureInfo,
        const QString& dateDelimiter)
{
    const uint64_t secsInDay = 86400;

    const QString validFromDate =
            featureInfo.validFromDate ?
                getDateString(featureInfo.validFromDate) : QString();
    const QString validUpToDate =
            featureInfo.validUpToDate ?
                getDateString(featureInfo.validUpToDate) : QString();
    if (validFromDate.isEmpty() && validUpToDate.isEmpty())
    {
        if (featureInfo.maxRunCounter)
            return QObject::tr("Number of launches: ") +
                      QString::number(featureInfo.curRunCounter) + " / " +
                      QString::number(featureInfo.maxRunCounter);
        else if (featureInfo.restOfLifeTime)
            return QObject::tr("Number of days: ") +
                      QString::number(featureInfo.restOfLifeTime / secsInDay);
        else
            return QObject::tr("No restrictions");
    }
    else if (validFromDate.isEmpty())
    {
        return validUpToDate;
    }
    else if (validUpToDate.isEmpty())
    {
        return validFromDate + dateDelimiter + getDateString(
                    featureInfo.validFromDate +
                    featureInfo.restOfLifeTime);
    }
    else
    {
        return validFromDate + dateDelimiter + validUpToDate;
    }
}

enum class FeatureConsumptionMode
{
    PerStation,
    PerLogin,
    PerProcess,
    None = -1
};

inline FeatureConsumptionMode featureConsumptionModeValue(
        const DeviceChecker::FeatureInfo& featureInfo)
{
    const uint32_t perStationFlag = 0; // GRD_CONSUMPTION_MODE_PERSTATION
    const uint32_t perLoginFlag   = 1; // GRD_CONSUMPTION_MODE_PERLOGIN
    const uint32_t perProcessFlag = 2; // GRD_CONSUMPTION_MODE_PERPROCESS

    FeatureConsumptionMode result = FeatureConsumptionMode::None;
    if (featureInfo.consumptionMode == perStationFlag)
        result = FeatureConsumptionMode::PerStation;
    else if (featureInfo.consumptionMode == perLoginFlag)
        result = FeatureConsumptionMode::PerLogin;
    else if (featureInfo.consumptionMode == perProcessFlag)
        result = FeatureConsumptionMode::PerProcess;
    return result;
}

inline QString featureResource(
        const DeviceChecker::FeatureInfo& featureInfo,
        const QString& noneDelimiter)
{
    if (featureInfo.maxConcurrentResource)
    {
        switch (featureConsumptionModeValue(featureInfo))
        {
        case FeatureConsumptionMode::PerStation:
            return QObject::tr("Work station") + ", " +
                    QString::number(featureInfo.maxConcurrentResource);
        case FeatureConsumptionMode::PerLogin:
            return QObject::tr("Connection") + ", " +
                    QString::number(featureInfo.maxConcurrentResource);
        case FeatureConsumptionMode::PerProcess:
            return QObject::tr("Program copy") + ", " +
                    QString::number(featureInfo.maxConcurrentResource);
        case FeatureConsumptionMode::None:
        default:
            break;
        }
    }
    return noneDelimiter;
}

inline bool featureIsVmForbidden(const DeviceChecker::FeatureInfo& featureInfo)
{
    const uint32_t vmForbiddenFlag = 4; // FEATURE_VM_FORBIDDEN
    return featureInfo.flags & vmForbiddenFlag;
}

#endif // FEATURE_H
