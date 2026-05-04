#ifndef DEVICECHECKER_H
#define DEVICECHECKER_H

#include <QSharedPointer>
#include <QVector>
#include <QTimer>
#include "License.h"

class DeviceChecker : public QObject
{
    Q_OBJECT

public:

    struct FeatureInfo
    {
        uint32_t id;
        uint32_t flags;
        uint64_t validFromDate;
        uint64_t validUpToDate;
        uint64_t restOfLifeTime;
        uint32_t curRunCounter;
        uint32_t maxRunCounter;
        uint32_t maxConcurrentResource;
        uint32_t detachedResource;
        uint32_t consumptionMode;
        QString name;
    };

    struct ProductInfo
    {
        uint32_t id;
        QString name;
        QVector<FeatureInfo> features;
    };

    struct LicenseInfo
    {
        uint32_t id;
        uint32_t publicCode;
        bool empty;
        DongleType dongleType;
        QVector<ProductInfo> products;
        bool isRehostable;
        bool isTrial;
        bool isMaster;
        bool isDetached;
        bool isBroken;
    };

    DeviceChecker(const uint periodMsecs);

    static QSharedPointer<QVector<LicenseInfo>> parse(
            const std::string& licenseInfoStr);

    static bool hasValidLicenses(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

public slots:

    void start();
    void stop();

    void check();

signals:

    void signalDevicesChanged(QSharedPointer<QVector<LicenseInfo>> data);
    void signalStopped();

private:

    // Timer for tracking licenses and dongles, which can be activated,
    //   updated, inserted or removed basically any moment
    // Note that the main thread may not be able to draw the licenses on time
    //   in the main window and thus get flooded
    QTimer m_timer;
    // License check period, in milliseconds
    const uint m_periodMsecs;
    // First check flag
    bool m_firstCheck;

    // Recent result, in form of license info JSON array string and a list of
    //   license info structures
    std::string m_licenseInfoStr;
    QSharedPointer<QVector<LicenseInfo>> m_data;

    bool changed();
    void notify();
};

#endif // DEVICECHECKER_H
