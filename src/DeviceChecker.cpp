#include "DeviceChecker.h"
#include "GrdLicApi.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMutex>

DeviceChecker::DeviceChecker(const uint periodMsecs) :
    m_timer(this),
    m_periodMsecs(periodMsecs),
    m_firstCheck(true),
    m_data(QSharedPointer<QVector<LicenseInfo>>::create())
{
}

void DeviceChecker::start()
{
    connect(&m_timer, &QTimer::timeout, this, &DeviceChecker::check);
    QTimer::singleShot(0, this, &DeviceChecker::check); // first check
    m_timer.start(static_cast<int>(m_periodMsecs));
}

void DeviceChecker::stop()
{
    m_timer.stop();
    disconnect(&m_timer, &QTimer::timeout, this, &DeviceChecker::check);
}

void DeviceChecker::check()
{
    // The notification signal is connected to the main window slot in the
    //   blocking queue mode, so that tryLock() optimization is not fine enough
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if (changed())
        notify();
}

bool DeviceChecker::changed()
{
    std::string licenseInfoStr;
    bool error = false;
    int status = licenseGetInfo(licenseInfoStr, false);
    if (status != GRD_OK && status != GRD_NO_RESULTS_FOUND)
    {
        error = true;
        licenseInfoStr.clear();
    }

    // Do not update in case of an error to avoid extra parsing
    if (error ||
            (licenseInfoStr.empty() && m_licenseInfoStr.empty() &&
             !m_firstCheck))
        return false;

    // Check if modified, extra fast
    bool changed =
            (licenseInfoStr.length() !=
             m_licenseInfoStr.length()) ||
            (std::hash<std::string>()(licenseInfoStr) !=
             std::hash<std::string>()(m_licenseInfoStr));
    if (changed)
    {
        m_licenseInfoStr = licenseInfoStr;
        QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data =
                parse(m_licenseInfoStr);
        m_data = data;
    }
    if (m_firstCheck)
    {
        changed = true;
        m_firstCheck = false;
    }
    return changed;
}

void DeviceChecker::notify()
{
    emit signalDevicesChanged(m_data);
}

QSharedPointer<QVector<DeviceChecker::LicenseInfo>> DeviceChecker::parse(
        const std::string& licenseInfoStr)
{
    constexpr uint32_t masterPublicVendorCode = 0x65D3F66F;

    QSharedPointer<QVector<LicenseInfo>> data =
            QSharedPointer<QVector<LicenseInfo>>::create();

    QJsonDocument doc = QJsonDocument::fromJson(licenseInfoStr.c_str());

    QJsonObject rootObj = doc.object();

    QJsonArray licenseArr = rootObj["licenses"].toArray();
    const int licenseCount = rootObj["licenseCount"].toInt();

    for (int i = 0; i < licenseCount; ++i)
    {
        QJsonObject licenseObj = licenseArr[i].toObject();

        const bool isBroken = licenseObj["isBroken"].toVariant().toBool();
        if (isBroken)
        {
            const uint32_t licenseId = static_cast<uint32_t>(
                        licenseObj["licenseId"].toVariant().toUInt());
            const uint32_t publicCode = static_cast<uint32_t>(
                        licenseObj["vendorPublicCode"].toVariant().toUInt());
            const uint32_t dongleModel = static_cast<uint32_t>(
                        licenseObj["dongleModel"].toVariant().toUInt());

            const DongleType dongleType = getDongleTypeFromModel(
                        dongleModel);

            LicenseInfo licenseInfo;
            licenseInfo.id = licenseId;
            licenseInfo.publicCode = publicCode;
            licenseInfo.empty = true;
            licenseInfo.dongleType = dongleType;
            licenseInfo.isRehostable = false;
            licenseInfo.isTrial = false;
            licenseInfo.isMaster = false;
            licenseInfo.isDetached = false;
            licenseInfo.isBroken = true;

            data->append(licenseInfo);

            continue;
        }

        QJsonObject dongleInfoObj = licenseObj["dongleInfo"].toObject();

        const uint32_t dongleTypeFlags = static_cast<uint32_t>(
                    dongleInfoObj["typeFlags"].toVariant().toUInt());
        const uint32_t dongleId = static_cast<uint32_t>(
                    dongleInfoObj["dongleId"].toVariant().toUInt());
        const uint32_t donglePublicVendorCode = static_cast<uint32_t>(
                    dongleInfoObj["publicCode"].toVariant().toUInt());
        const bool isMaster =
                (donglePublicVendorCode == masterPublicVendorCode);

        QJsonObject licenseInfoObj = licenseObj["licenseInfo"].toObject();

        const bool empty = licenseInfoObj.isEmpty();
        const uint32_t licenseId =
                !licenseInfoObj.isEmpty() ?
                    static_cast<uint32_t>(
                        licenseInfoObj["licenseId"].toVariant().toUInt()) :
            dongleId;

        QJsonObject flagsObj = licenseObj["flagsAsFields"].toObject();

        const bool isRehostable = flagsObj["isRehostAllowed"].toBool();
        const bool isTrial = flagsObj["isTrial"].toBool();
        const bool isDetached = flagsObj["isDetached"].toBool();

        LicenseInfo licenseInfo;
        licenseInfo.id = licenseId;
        licenseInfo.publicCode = donglePublicVendorCode;
        licenseInfo.empty = empty;
        licenseInfo.dongleType = dongleTypeValue(dongleTypeFlags);
        licenseInfo.isRehostable = isRehostable;
        licenseInfo.isTrial = isTrial;
        licenseInfo.isMaster = isMaster;
        licenseInfo.isDetached = isDetached;
        licenseInfo.isBroken = false;

        const uint64_t trialBirthDate = isTrial ?
                    static_cast<uint64_t>(
                        dongleInfoObj["containerActivationTime"].toVariant().
                    toULongLong()) : 0;
        const uint64_t trialDeathDate = isTrial ?
                    static_cast<uint64_t>(
                        dongleInfoObj["containerDeathTime"].toVariant().
                    toULongLong()) : 0;

        QJsonArray productArr = licenseInfoObj["products"].toArray();
        const int productCount = licenseInfoObj["productsCount"].toInt();

        for (int j = 0; j < productCount; ++j)
        {
            QJsonObject productObj = productArr[j].toObject();

            const uint32_t productId = static_cast<uint32_t>(
                        productObj["number"].toVariant().toUInt());
            QString productName = productObj["name"].toString();

            ProductInfo productInfo;
            productInfo.id = productId;
            productInfo.name = productName;

            QJsonArray featureArr = productObj["features"].toArray();
            const int featureCount = productObj["featuresCount"].toInt();

            for (int k = 0; k < featureCount; ++k)
            {
                QJsonObject featureObj = featureArr[k].toObject();

                const uint32_t featureId = static_cast<uint32_t>(
                            featureObj["number"].toVariant().toUInt());
                QString featureName = featureObj["name"].toString();
                const uint32_t featureFlags = static_cast<uint32_t>(
                            featureObj["flags"].toVariant().toUInt());
                uint64_t featureValidFromDate = static_cast<uint64_t>(
                            featureObj["validFromDate"].toVariant().
                        toULongLong());
                uint64_t featureValidUpToDate = static_cast<uint64_t>(
                            featureObj["validUpToDate"].toVariant().
                        toULongLong());
                const uint64_t featureRestOfLifeTime = static_cast<uint64_t>(
                            featureObj["restOfLifeTime"].toVariant().
                        toULongLong());
                const uint32_t featureMaxRunCounter = static_cast<uint32_t>(
                            featureObj["maxRunCounter"].toVariant().toUInt());
                const uint32_t featureConsumptionMode = static_cast<uint32_t>(
                            featureObj["consumptionMode"].toVariant().
                        toUInt());
                const uint16_t featureMaxConcurrentResource =
                        static_cast<uint16_t>(
                            featureObj["maxConcurrentResource"].toVariant().
                        toUInt());
                const uint16_t featureDetachedResource = static_cast<uint16_t>(
                            featureObj["detachedResource"].toVariant().
                        toUInt());
                const uint32_t featureCurrentRunCounterValue =
                        static_cast<uint32_t>(
                            featureObj["currentRunCounterValue"].toVariant().
                        toUInt());

                // Fixup time limit for features in trial licenses
                if (featureValidFromDate && trialBirthDate)
                    featureValidFromDate = qMax(
                                featureValidFromDate, trialBirthDate);
                if (featureValidUpToDate && trialDeathDate)
                    featureValidUpToDate = qMin(
                                featureValidUpToDate, trialDeathDate);

                // Impose time limit on unlimited features in trial licenses
                // See featureDate() in "Feature.h"
                if (!featureValidFromDate && !featureValidUpToDate &&
                        !featureMaxRunCounter && !featureRestOfLifeTime &&
                        trialBirthDate && trialDeathDate)
                {
                    featureValidFromDate = trialBirthDate;
                    featureValidUpToDate = trialDeathDate;
                }

                FeatureInfo featureInfo;
                featureInfo.id = featureId;
                featureInfo.name = featureName;
                featureInfo.flags = featureFlags;
                featureInfo.validFromDate = featureValidFromDate;
                featureInfo.validUpToDate = featureValidUpToDate;
                featureInfo.restOfLifeTime = featureRestOfLifeTime;
                featureInfo.curRunCounter = featureCurrentRunCounterValue;
                featureInfo.maxRunCounter = featureMaxRunCounter;
                featureInfo.maxConcurrentResource = featureMaxConcurrentResource;
                featureInfo.detachedResource = featureDetachedResource;
                featureInfo.consumptionMode = featureConsumptionMode;

                productInfo.features << featureInfo;
            }

            std::sort(productInfo.features.begin(),
                      productInfo.features.end(),
                      [](const FeatureInfo& first, const FeatureInfo& second) {
                return first.id < second.id;
            });

            licenseInfo.products << productInfo;
        }

        std::sort(licenseInfo.products.begin(),
                  licenseInfo.products.end(),
                  [](const ProductInfo& first, const ProductInfo& second) {
            return first.id < second.id;
        });

        data->append(licenseInfo);
    }

    std::sort(data->begin(),
              data->end(),
              [](const LicenseInfo& first, const LicenseInfo& second) {
        return first.id < second.id;
    });

    return data;
}

bool DeviceChecker::hasValidLicenses(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    if (data->isEmpty())
        return false;

    for (int j = 0; j < data->size(); ++j)
    {
        const DeviceChecker::LicenseInfo& licenseInfo = data->at(j);
        if (!licenseInfo.isBroken)
            return true;
    }
    return false;
}
