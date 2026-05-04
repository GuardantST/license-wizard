#ifndef GRDLICAPI_H
#define GRDLICAPI_H

#include "Common.h"
#include "Logger.h"
#include <grdlic/grdlic.h>
#include <sstream>

//#ifndef STUB_FUNCTIONS
//# define STUB_FUNCTIONS
//#endif

inline int getGrdLang()
{
    const QLocale& locale = User::instance().locale();
    if (locale.language() == QLocale::English)
        return GRD_LANG_EN;
    else if (locale.language() == QLocale::Russian)
        return GRD_LANG_RU;
    else if (locale.language() == QLocale::German)
        return GRD_LANG_DE;
    else if (locale.language() == QLocale::Spanish)
        return GRD_LANG_ES;
    else if (locale.language() == QLocale::Japanese)
        return GRD_LANG_JA;

    assert(false);
    return GRD_LANG_EN;
}

inline QString getErrorMessage(const int status)
{
    char buffer[256] = { 0 };
    const int result = GrdGetErrorMessage(
                status, getGrdLang(), buffer, sizeof(buffer));
    if (result != GRD_OK)
        return QString();
    return buffer;
}

inline void log(
        const QString& operation, const int status,
        const QString& serialNumber = QString(),
        const uint32_t licenseId = 0,
        const std::string& address = std::string(),
        const uint32_t port = 0,
        const QStringList& extras = QStringList())
{
    QString message = getErrorMessage(status);
    if (message.isEmpty())
        message = QObject::tr("NO DESCRIPTION");

    QStringList contexts;
    if (!serialNumber.isEmpty())
        contexts << QObject::tr("serial number") + " = " +
                    serialNumber;
    if (licenseId)
        contexts << QObject::tr("license ID") + " = " +
                    "0x" + QString::number(licenseId, 16).toUpper().
                    rightJustified(8, '0');
    if (!address.empty() && port)
    {
        contexts << QObject::tr("address") + " = " +
                    QString::fromStdString(address);
        contexts << QObject::tr("port") + " = " +
                    QString::number(port);
    }
    contexts << extras;

    loggerReport(
                operation + ": " +
                QObject::tr("status code") + " = " +
                QString::number(status) + ", " +
                QObject::tr("message") + " = " +
                message,
                contexts);
}

inline int licenseGetInfo(
        std::string& licenseInfo,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(licenseInfo);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    static const int remoteMode =
            GRD_LOCAL_MODE_ON;
    static const int dongleModel =
            GRD_DONGLE_MODEL_SIGN |
            GRD_DONGLE_MODEL_CODE |
            GRD_DONGLE_MODEL_DL;
    static const std::string visibility =
            []() -> std::string
    {
            std::stringstream ss;
            ss << "{" <<
                  "\"remoteMode\":" << std::dec << remoteMode << "," <<
                  "\"dongleModel\":" << std::dec << dongleModel <<
                  "}";
            return ss.str();
    } ();
    const GrdVendorCodes codes { 0, 0, 0 };

    char* licenseInfoStr = nullptr;
    const int status = GrdGetLicenseInfo(
                visibility.c_str(), &codes, &licenseInfoStr);
    if (needsLogging)
        log("GrdGetLicenseInfo", status);
    if (status)
        return status;

    licenseInfo = licenseInfoStr;
    GrdFree(licenseInfoStr);
    return GRD_OK;

#endif
}

inline int licenseCheckUpdate(
        const uint32_t licenseId,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(licenseId);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    const int status = GrdLicenseCheckUpdateIsAvailable(
                licenseId,
                host.c_str(), port);
    if (needsLogging)
        log("GrdLicenseCheckUpdateIsAvailable", status,
            QString(), licenseId, host, port);
    return status;

#endif
}

inline int licenseActivate(
        const QString& serialNumber,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(serialNumber);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    const int status = GrdLicenseActivate(
                serialNumber.toStdString().c_str(),
                host.c_str(), port,
                nullptr, nullptr);
    if (needsLogging)
        log("GrdLicenseActivate", status,
            serialNumber, 0, host, port);
    return status;

#endif
}

inline int licenseUpdate(
        const uint32_t licenseId,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(licenseId);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    const int status = GrdLicenseUpdate(
                licenseId,
                host.c_str(), port);
    if (needsLogging)
        log("GrdLicenseUpdate", status,
            QString(), licenseId, host, port);
    return status;

#endif
}

inline int licenseCreateActivationRequest(
        const QString& requestFilePath,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(requestFilePath);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    if (!checkFile(requestFilePath))
        return GRD_FILE_CREATION_ERROR;

    grd_uint8* outRequest;
    grd_uint32 outRequestSize;
    const int status = GrdLicenseCreateActivationRequest(
                reinterpret_cast<void**>(&outRequest), &outRequestSize);
    if (needsLogging)
        log("GrdLicenseCreateActivationRequest", status);
    if (status)
        return status;

    // Currently this API function returns Base64-encoded string, ending with
    //   "...A==\0", and outRequestSize also counts the trailing null character
    std::vector<grd_uint8> requestData(
                outRequest, outRequest + outRequestSize - 1);
    GrdFree(outRequest);

    bool isDiskSpaceIssue = false;
    if (!writeFile(requestFilePath, requestData, isDiskSpaceIssue))
    {
        if (needsLogging)
            loggerReport("Could not write the request file for "
                         "GrdLicenseCreateActivationRequest");
        if (isDiskSpaceIssue)
            return GRD_DISK_SPACE_IS_OVER;
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseCreateUpdateRequest(
        const uint32_t licenseId,
        const QString& requestFilePath,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(licenseId);
    Q_UNUSED(requestFilePath);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    if (!checkFile(requestFilePath))
        return GRD_FILE_CREATION_ERROR;

    grd_uint8* outRequest;
    grd_uint32 outRequestSize;
    const int status = GrdLicenseCreateUpdateRequest(
                licenseId,
                reinterpret_cast<void**>(&outRequest), &outRequestSize);
    if (needsLogging)
        log("GrdLicenseCreateUpdateRequest", status,
            QString(), licenseId);
    if (status)
        return status;

    // Currently this API function returns Base64-encoded string, ending with
    //   "...A==\0", and outRequestSize also counts the trailing null character
    std::vector<grd_uint8> requestData(
                outRequest, outRequest + outRequestSize - 1);
    GrdFree(outRequest);

    bool isDiskSpaceIssue = false;
    if (!writeFile(requestFilePath, requestData, isDiskSpaceIssue))
    {
        if (needsLogging)
            loggerReport("Could not write the request file for "
                         "GrdLicenseCreateUpdateRequest");
        if (isDiskSpaceIssue)
            return GRD_DISK_SPACE_IS_OVER;
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseSendActivationRequest(
        const QString& serialNumber,
        const QString& requestFilePath,
        QByteArray& licenseBytes,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(serialNumber);
    Q_UNUSED(requestFilePath);
    Q_UNUSED(licenseBytes);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    std::vector<uint8_t> requestData = readFile(requestFilePath);
    if (requestData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the request file for "
                         "GrdLicenseSendActivationRequest");
        return GRD_INTERNAL_ERROR;
    }

    grd_uint8* outResponse;
    grd_uint32 outResponseSize;
    const int status = GrdLicenseSendActivationRequest(
                serialNumber.toStdString().c_str(), nullptr,
                requestData.data(), static_cast<grd_uint32>(
                    requestData.size()),
                host.c_str(), port,
                reinterpret_cast<void**>(&outResponse), &outResponseSize);
    if (needsLogging)
        log("GrdLicenseSendActivationRequest", status,
            serialNumber, 0, host, port);
    if (status)
        return status;

    licenseBytes = QByteArray(
                reinterpret_cast<const char*>(outResponse),
                static_cast<int>(outResponseSize));
    GrdFree(outResponse);

    if (licenseBytes.isEmpty())
    {
        if (needsLogging)
            loggerReport("License data is empty for "
                         "GrdLicenseSendActivationRequest");
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseSendActivationRequest(
        const QString& serialNumber,
        const QString& requestFilePath,
        const QString& licenseFilePath,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(serialNumber);
    Q_UNUSED(requestFilePath);
    Q_UNUSED(licenseFilePath);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    std::vector<uint8_t> requestData = readFile(requestFilePath);
    if (requestData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the request file for "
                         "GrdLicenseSendActivationRequest");
        return GRD_INTERNAL_ERROR;
    }

    if (!checkFile(licenseFilePath))
        return GRD_FILE_CREATION_ERROR;

    grd_uint8* outResponse;
    grd_uint32 outResponseSize;
    const int status = GrdLicenseSendActivationRequest(
                serialNumber.toStdString().c_str(), nullptr,
                requestData.data(), static_cast<grd_uint32>(
                    requestData.size()),
                host.c_str(), port,
                reinterpret_cast<void**>(&outResponse), &outResponseSize);
    if (needsLogging)
        log("GrdLicenseSendActivationRequest", status,
            serialNumber, 0, host, port);
    if (status)
        return status;

    std::vector<uint8_t> licenseData(
                outResponse, outResponse + outResponseSize);
    GrdFree(outResponse);

    bool isDiskSpaceIssue = false;
    if (!writeFile(licenseFilePath, licenseData, isDiskSpaceIssue))
    {
        if (needsLogging)
            loggerReport("Could not write the license file for "
                         "GrdLicenseSendActivationRequest");
        if (isDiskSpaceIssue)
            return GRD_DISK_SPACE_IS_OVER;
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseSendUpdateRequest(
        const QString& requestFilePath,
        QByteArray& licenseBytes,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(requestFilePath);
    Q_UNUSED(licenseBytes);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    std::vector<uint8_t> requestData = readFile(requestFilePath);
    if (requestData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the request file for "
                         "GrdLicenseSendUpdateRequest");
        return GRD_INTERNAL_ERROR;
    }

    grd_uint8* outResponse;
    grd_uint32 outResponseSize;
    const int status = GrdLicenseSendUpdateRequest(
                requestData.data(), static_cast<grd_uint32>(
                    requestData.size()),
                host.c_str(), port,
                reinterpret_cast<void**>(&outResponse), &outResponseSize);
    if (needsLogging)
        log("GrdLicenseSendUpdateRequest", status,
            QString(), 0, host, port);
    if (status)
        return status;

    licenseBytes = QByteArray(
                reinterpret_cast<const char*>(outResponse),
                static_cast<int>(outResponseSize));
    GrdFree(outResponse);

    if (licenseBytes.isEmpty())
    {
        if (needsLogging)
            loggerReport("License data is empty for "
                         "GrdLicenseSendUpdateRequest");
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseSendUpdateRequest(
        const QString& requestFilePath,
        const QString& licenseFilePath,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(requestFilePath);
    Q_UNUSED(licenseFilePath);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    std::vector<uint8_t> requestData = readFile(requestFilePath);
    if (requestData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the request file for "
                         "GrdLicenseSendUpdateRequest");
        return GRD_INTERNAL_ERROR;
    }

    if (!checkFile(licenseFilePath))
        return GRD_FILE_CREATION_ERROR;

    grd_uint8* outResponse;
    grd_uint32 outResponseSize;
    const int status = GrdLicenseSendUpdateRequest(
                requestData.data(), static_cast<grd_uint32>(
                    requestData.size()),
                host.c_str(), port,
                reinterpret_cast<void**>(&outResponse), &outResponseSize);
    if (needsLogging)
        log("GrdLicenseSendUpdateRequest", status,
            QString(), 0, host, port);
    if (status)
        return status;

    std::vector<uint8_t> licenseData(
                outResponse, outResponse + outResponseSize);
    GrdFree(outResponse);

    bool isDiskSpaceIssue = false;
    if (!writeFile(licenseFilePath, licenseData, isDiskSpaceIssue))
    {
        if (needsLogging)
            loggerReport("Could not write the license file for "
                         "GrdLicenseSendUpdateRequest");
        if (isDiskSpaceIssue)
            return GRD_DISK_SPACE_IS_OVER;
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseInstall(
        const QString& licenseFilePath,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(licenseFilePath);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    std::vector<uint8_t> licenseData = readFile(licenseFilePath);
    if (licenseData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the license file for "
                         "GrdLicenseInstall");
        return GRD_INTERNAL_ERROR;
    }

    const int status = GrdLicenseInstall(
                licenseData.data(), static_cast<grd_uint32>(
                    licenseData.size()));
    if (needsLogging)
        log("GrdLicenseInstall", status);
    return status;

#endif
}

inline int licenseGetFingerprint(
        const QString& fingerprintFilePath,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(fingerprintFilePath);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    if (!checkFile(fingerprintFilePath))
        return GRD_FILE_CREATION_ERROR;

    char* fingerprintStr;
    const int status = GrdGetHostFingerprint(
                &fingerprintStr, nullptr);
    if (needsLogging)
        log("GrdGetHostFingerprint", status);
    if (status)
        return status;

    std::string fingerprint = fingerprintStr;
    GrdFree(fingerprintStr);
    std::vector<uint8_t> fingerprintData(
                fingerprint.begin(), fingerprint.end());

    bool isDiskSpaceIssue = false;
    if (!writeFile(fingerprintFilePath, fingerprintData, isDiskSpaceIssue))
    {
        if (needsLogging)
            loggerReport("Could not write the fingerprint file for "
                         "GrdGetHostFingerprint");
        if (isDiskSpaceIssue)
            return GRD_DISK_SPACE_IS_OVER;
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseExtractForRehost(
        const uint32_t licenseId,
        const QString& donorLicenseFilePath,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(licenseId);
    Q_UNUSED(donorLicenseFilePath);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    if (!checkFile(donorLicenseFilePath))
        return GRD_FILE_CREATION_ERROR;

    grd_uint8* outDonorLicense;
    grd_uint32 outDonorLicenseSize;
    const int status = GrdLicenseExtractForRehost(
                licenseId,
                reinterpret_cast<void**>(&outDonorLicense),
                &outDonorLicenseSize);
    if (needsLogging)
        log("GrdLicenseExtractForRehost", status,
            QString(), licenseId);
    if (status)
        return status;

    std::vector<uint8_t> licenseData(
                outDonorLicense, outDonorLicense + outDonorLicenseSize);
    GrdFree(outDonorLicense);

    bool isDiskSpaceIssue = false;
    if (!writeFile(donorLicenseFilePath, licenseData, isDiskSpaceIssue))
    {
        if (needsLogging)
            loggerReport("Could not write the rehost file for "
                         "GrdLicenseExtractForRehost");
        if (isDiskSpaceIssue)
            return GRD_DISK_SPACE_IS_OVER;
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseRehost(
        const QString& recipientLicenseFilePath,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(recipientLicenseFilePath);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    std::vector<uint8_t> licenseData = readFile(recipientLicenseFilePath);
    if (licenseData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the rehost file for "
                         "GrdLicenseRehost");
        return GRD_INTERNAL_ERROR;
    }

    const int status = GrdLicenseRehost(
                host.c_str(), port,
                licenseData.data(), static_cast<grd_uint32>(
                    licenseData.size()));
    if (needsLogging)
        log("GrdLicenseRehost", status,
            QString(), 0, host, port);
    return status;

#endif
}

inline int licenseSendRehostRequest(
        const QString& donorLicenseFilePath,
        const QString& fingerprintFilePath,
        QByteArray& recipientLicenseBytes,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(donorLicenseFilePath);
    Q_UNUSED(fingerprintFilePath);
    Q_UNUSED(recipientLicenseBytes);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    std::vector<uint8_t> donorLicenseData = readFile(donorLicenseFilePath);
    if (donorLicenseData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the rehost file for "
                         "GrdLicenseSendRehostRequest");
        return GRD_INTERNAL_ERROR;
    }

    std::vector<uint8_t> fingerprintData = readFile(fingerprintFilePath);
    if (fingerprintData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the fingerprint file for "
                         "GrdLicenseSendRehostRequest");
        return GRD_INTERNAL_ERROR;
    }

    // Make sure the string would be constructed properly
    fingerprintData.push_back('\0');

    std::string fingerprintStr(
                reinterpret_cast<char*>(fingerprintData.data()));
    grd_uint8* outRecipientLicense;
    grd_uint32 outRecipientLicenseSize;
    const int status = GrdLicenseSendRehostRequest(
                host.c_str(), port,
                donorLicenseData.data(), static_cast<grd_uint32>(
                    donorLicenseData.size()),
                fingerprintStr.c_str(),
                reinterpret_cast<void**>(&outRecipientLicense),
                &outRecipientLicenseSize);
    if (needsLogging)
        log("GrdLicenseSendRehostRequest", status,
            QString(), 0, host, port);
    if (status)
        return status;

    recipientLicenseBytes = QByteArray(
                reinterpret_cast<const char*>(outRecipientLicense),
                static_cast<int>(outRecipientLicenseSize));
    GrdFree(outRecipientLicense);

    if (recipientLicenseBytes.isEmpty())
    {
        if (needsLogging)
            loggerReport("License data is empty for "
                         "GrdLicenseSendRehostRequest");
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int licenseSendRehostRequest(
        const QString& donorLicenseFilePath,
        const QString& fingerprintFilePath,
        const QString& recipientLicenseFilePath,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(donorLicenseFilePath);
    Q_UNUSED(fingerprintFilePath);
    Q_UNUSED(recipientLicenseFilePath);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    std::vector<uint8_t> donorLicenseData = readFile(donorLicenseFilePath);
    if (donorLicenseData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the rehost file for "
                         "GrdLicenseSendRehostRequest");
        return GRD_INTERNAL_ERROR;
    }

    std::vector<uint8_t> fingerprintData = readFile(fingerprintFilePath);
    if (fingerprintData.empty())
    {
        if (needsLogging)
            loggerReport("Could not read the fingerprint file for "
                         "GrdLicenseSendRehostRequest");
        return GRD_INTERNAL_ERROR;
    }

    if (!checkFile(recipientLicenseFilePath))
        return GRD_FILE_CREATION_ERROR;

    // Make sure the string would be constructed properly
    fingerprintData.push_back('\0');

    std::string fingerprintStr(
                reinterpret_cast<char*>(fingerprintData.data()));
    grd_uint8* outRecipientLicense;
    grd_uint32 outRecipientLicenseSize;
    const int status = GrdLicenseSendRehostRequest(
                host.c_str(),port,
                donorLicenseData.data(), static_cast<grd_uint32>(
                    donorLicenseData.size()),
                fingerprintStr.c_str(),
                reinterpret_cast<void**>(&outRecipientLicense),
                &outRecipientLicenseSize);
    if (needsLogging)
        log("GrdLicenseSendRehostRequest", status,
            QString(), 0, host, port);
    if (status)
        return status;

    std::vector<uint8_t> recipientLicenseData(
                outRecipientLicense,
                outRecipientLicense + outRecipientLicenseSize);
    GrdFree(outRecipientLicense);

    bool isDiskSpaceIssue = false;
    if (!writeFile(recipientLicenseFilePath, recipientLicenseData,
                   isDiskSpaceIssue))
    {
        if (needsLogging)
            loggerReport("Could not write the license file for "
                         "GrdLicenseSendRehostRequest");
        if (isDiskSpaceIssue)
            return GRD_DISK_SPACE_IS_OVER;
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;

#endif
}

inline int dongleSetLicense(
        const uint32_t dongleId,
        const QString& serialNumber,
        const std::string& host, uint32_t port,
        const bool needsLogging)
{
#ifdef STUB_FUNCTIONS

    Q_UNUSED(dongleId);
    Q_UNUSED(serialNumber);
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(needsLogging);
    return GRD_OK;

#else

    const int status = GrdDongleSetLicense(
                static_cast<grd_uint32>(dongleId),
                serialNumber.toStdString().c_str(),
                static_cast<grd_uint32>(GRD_DRIVER_TYPE_WINUSB),
                host.c_str(), port);
    if (needsLogging)
        log("GrdDongleSetLicense", status,
            serialNumber, dongleId, host, port);
    return status;

#endif
}

inline int dongleBlink(const uint32_t dongleId)
{
    return GrdLedBlink(dongleId);
}

#endif // GRDLICAPI_H
