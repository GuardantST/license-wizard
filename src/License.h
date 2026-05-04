#ifndef LICENSE_H
#define LICENSE_H

#include <QVariant>

static const int LicenseIdRole = Qt::UserRole;
static const int ProductIdRole = Qt::UserRole;
static const int FeatureIdRole = Qt::UserRole;
static const int DongleTypeRole = Qt::UserRole + 1;

static const uint32_t NullLicenseId = 0;
static const uint32_t InvalidLicenseId = 0xFFFFFFFF;

inline bool isLicenseIdValid(const uint32_t licenseId)
{
    return licenseId != NullLicenseId && licenseId != InvalidLicenseId;
}

inline QString licenseIdStr(const uint32_t licenseId)
{
    return QString::number(licenseId, 16).toUpper().rightJustified(8, '0');
}

inline QString dongleIdStr(const uint32_t dongleId)
{
    return licenseIdStr(dongleId);
}

enum class DongleType
{
    Unknown,
    Sign,
    SignNet,
    Time,
    TimeNet,
    Code,
    CodeNet,
    CodeTime,
    CodeTimeNet,
    Dl,
    DlNet,
};

inline DongleType dongleTypeValue(const uint32_t dongleTypeFlags)
{
    const bool isDongleVsLicense = dongleTypeFlags & 0x20;
    const bool isCodeVsSign = dongleTypeFlags & 0x400;
    const bool isTime = dongleTypeFlags & 0x40;
    const bool isNet = dongleTypeFlags & 5; // combined flag

    if (isDongleVsLicense)
    {
        if (isCodeVsSign)
        {
            if (isTime)
            {
                if (isNet)
                    return DongleType::CodeTimeNet;
                else
                    return DongleType::CodeTime;
            }
            else
            {
                if (isNet)
                    return DongleType::CodeNet;
                else
                    return DongleType::Code;
            }
        }
        else
        {
            if (isTime)
            {
                if (isNet)
                    return DongleType::TimeNet;
                else
                    return DongleType::Time;
            }
            else
            {
                if (isNet)
                    return DongleType::SignNet;
                else
                    return DongleType::Sign;
            }
        }
    }
    else
    {
        if (!isCodeVsSign && isTime)
        {
            if (isNet)
                return DongleType::DlNet;
            else
                return DongleType::Dl;
        }
        else
            return DongleType::Unknown;
    }
}

inline DongleType getDongleTypeFromModel(const uint32_t dongleModel)
{
    switch (dongleModel)
    {
    case 0x400: // GRD_DONGLE_MODEL_DL
        return DongleType::Dl;
    case 0x100: // GRD_DONGLE_MODEL_CODE
        return DongleType::Code;
    case 0x80: // GRD_DONGLE_MODEL_SIGN
        return DongleType::Sign;
    default:
        return DongleType::Unknown;
    }
}

inline DongleType dongleTypeCheck(const DongleType dongleType)
{
    switch (dongleType)
    {
    case DongleType::Sign:
    case DongleType::SignNet:
    case DongleType::Time:
    case DongleType::TimeNet:
    case DongleType::Code:
    case DongleType::CodeNet:
    case DongleType::CodeTime:
    case DongleType::CodeTimeNet:
    case DongleType::Dl:
    case DongleType::DlNet:
    case DongleType::Unknown:
        return dongleType;
    default:
        return DongleType::Unknown;
    }
}

inline bool dongleVsLicense(const DongleType dongleType)
{
    switch (dongleType)
    {
    case DongleType::Sign:
    case DongleType::SignNet:
    case DongleType::Time:
    case DongleType::TimeNet:
    case DongleType::Code:
    case DongleType::CodeNet:
    case DongleType::CodeTime:
    case DongleType::CodeTimeNet:
        return true;
    case DongleType::Dl:
    case DongleType::DlNet:
    case DongleType::Unknown:
    default:
        return false;
    }
}

inline QString dongleTypeStr(DongleType dongleType)
{
    switch (dongleType)
    {
    case DongleType::Sign:
        return "Sign";
    case DongleType::SignNet:
        return "Sign Net";
    case DongleType::Time:
        return "Time";
    case DongleType::TimeNet:
        return "Time Net";
    case DongleType::Code:
        return "Code";
    case DongleType::CodeNet:
        return "Code Net";
    case DongleType::CodeTime:
        return "Code Time";
    case DongleType::CodeTimeNet:
        return "Code Time Net";
    case DongleType::Dl:
        return "DL";
    case DongleType::DlNet:
        return "DL Net";
    case DongleType::Unknown:
    default:
        return "";
    }
}

inline QString dongleTypeSignature(const DongleType dongleType)
{
    switch (dongleType)
    {
    case DongleType::Sign:
        return "S";
    case DongleType::SignNet:
        return "SN";
    case DongleType::Time:
        return "T";
    case DongleType::TimeNet:
        return "TN";
    case DongleType::Code:
        return "C";
    case DongleType::CodeNet:
        return "CN";
    case DongleType::CodeTime:
        return "CT";
    case DongleType::CodeTimeNet:
        return "CTN";
    case DongleType::Dl:
        return "DL";
    case DongleType::DlNet:
        return "DLN";
    case DongleType::Unknown:
    default:
        return "G";
    }
}

inline QString buildLicenseText(const DongleType dongleType,
                                const uint32_t licenseId)
{
    return "Guardant " + dongleTypeStr(dongleType) + " #" +
            licenseIdStr(licenseId);
}

inline QString buildLicenseTextFull(const DongleType dongleType,
                                    const uint32_t licenseId)
{
    return (dongleVsLicense(dongleType) ?
                QObject::tr("Key") :
                QObject::tr("License")) +
            " " + buildLicenseText(dongleType, licenseId);
}

#include <QTreeWidgetItem>

inline uint32_t itemLicenseId(const QTreeWidgetItem* const item)
{
    return static_cast<uint32_t>(item->data(0, LicenseIdRole).toUInt());
}

inline uint32_t itemProductId(const QTreeWidgetItem* const item)
{
    return static_cast<uint32_t>(item->data(0, ProductIdRole).toUInt());
}

inline uint32_t itemFeatureId(const QTreeWidgetItem* const item)
{
    return static_cast<uint32_t>(item->data(0, FeatureIdRole).toUInt());
}

inline DongleType itemDongleType(const QTreeWidgetItem* const item)
{
    return static_cast<DongleType>(item->data(0, DongleTypeRole).toUInt());
}

inline void setItemLicenseId(
        QTreeWidgetItem* const item,
        const uint32_t licenseId)
{
    item->setData(0, LicenseIdRole, licenseId);
}

inline void setItemProductId(
        QTreeWidgetItem* const item,
        const uint32_t productId)
{
    item->setData(0, ProductIdRole, productId);
}

inline void setItemFeatureId(
        QTreeWidgetItem* const item,
        const uint32_t featureId)
{
    item->setData(0, FeatureIdRole, featureId);
}

inline void setItemData(
        QTreeWidgetItem* const item,
        const DongleType dongleType, const uint32_t licenseId)
{
    item->setData(0, LicenseIdRole, licenseId);
    item->setData(0, DongleTypeRole, static_cast<int>(dongleType));
}

inline QString buildLicenseText(const QTreeWidgetItem* const item)
{
    return buildLicenseText(itemDongleType(item), itemLicenseId(item));
}

#endif // LICENSE_H
