#ifndef NAMING_H
#define NAMING_H

#include "Common.h"
#include "License.h"

inline QString buildActivationRequestFileName()
{
    return QSysInfo::machineHostName() +
            ".activation." + RequestFileExtension;
}

inline QString buildUpdateRequestFileName(
        const uint32_t licenseId, const DongleType dongleType)
{
    return QSysInfo::machineHostName() + "-" +
            dongleTypeSignature(dongleType) + "_" +
            licenseIdStr(licenseId) +
            ".update." + RequestFileExtension;
}

inline QString buildFingerprintFileName()
{
    return QSysInfo::machineHostName() +
            "." + FingerprintFileExtension;
}

inline QString buildRehostExtractFileName(const uint32_t licenseId)
{
    return dongleTypeSignature(DongleType::Dl) + "_" +
            licenseIdStr(licenseId) +
            "." + RehostFileExtension;
}

inline QString buildResponseFileName(const QString& requestFilePath)
{
    return filePathToBaseName(requestFilePath) + // remove extension, if any
            "." + LicenseFileExtension;
}

inline QString buildRehostResponseFileName(
        const QString& requestFilePath, const QString& fingerprintFilePath)
{
    // Beautifying logic:
    // 1. Default scenario:
    // - fingerprint file name ~ "AnotherPC.fingerprint"
    // - request file name ~ "DL_0123CDEF.rehost"
    // - response (license) file name ~ "AnotherPC-DL_0123CDEF.rehost.license"
    // 2. Customized scenarios:
    // - if fingerprint file base name contains dots, omit it
    // - if request file base name does not contain dots, coupling is possible
    // - if coupling is possible and fingerprint file base name is not omitted,
    //     join the parts with dash, otherwise use the request file name only
    QString firstPart = filePathToBaseName(fingerprintFilePath);
    if (firstPart.contains("."))
        firstPart.clear();
    const QString secondPart = filePathToName(requestFilePath);
    if (!secondPart.endsWith(QString(".") + RehostFileExtension) ||
            secondPart.count(".") != 1 ||
            firstPart.isEmpty())
        return filePathToBaseName(secondPart) + // remove extension if any
                "." + LicenseFileExtension;
    return firstPart + "-" + secondPart +
            "." + LicenseFileExtension;
}

#endif // NAMING_H
