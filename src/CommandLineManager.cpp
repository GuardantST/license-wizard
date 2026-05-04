#include "CommandLineManager.h"
#include "GrdLicApi.h"
#include "Feature.h"
#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <iostream>
#include <cassert>
#ifdef Q_OS_WIN
# include <Windows.h>
#endif

using CommandOperation = CommandLineParser::CommandOperation;
using ConsoleError = CommandLineParser::ConsoleError;

#ifdef Q_OS_WIN

static std::string convert(const QString& qstr)
{
    if (qstr.isEmpty())
        return std::string();

    const std::wstring wstr = qstr.toStdWString();
    if (wstr.empty())
    {
        assert(false);
        return std::string();
    }

    CPINFO cpInfo;
    memset(&cpInfo, 0, sizeof(CPINFO));

    DWORD err = 0;
    SetLastError(err);

    const BOOL gotInfo = GetCPInfo(GetConsoleOutputCP(), &cpInfo);
    if (gotInfo != TRUE)
    {
        assert(false);
        return std::string();
    }

    err = GetLastError();
    if (err != 0)
    {
        assert(false);
        return std::string();
    }

    int converted = WideCharToMultiByte(
                GetConsoleOutputCP(), 0,
                wstr.data(), static_cast<int>(wstr.size()),
                nullptr, 0,
                reinterpret_cast<LPCCH>(cpInfo.DefaultChar),
                nullptr);
    if (converted <= 0)
    {
        assert(false);
        return std::string();
    }

    err = GetLastError();
    if (err != 0)
    {
        assert(false);
        return std::string();
    }

    std::string str(static_cast<size_t>(converted), '\0');
    char* strData = const_cast<char*>(str.data());
    BOOL isDefaultCharUsed = FALSE;
    converted = WideCharToMultiByte(
                GetConsoleOutputCP(), 0,
                wstr.data(), static_cast<int>(wstr.size()),
                strData, static_cast<int>(str.size()),
                reinterpret_cast<LPCCH>(cpInfo.DefaultChar),
                &isDefaultCharUsed);
    if (converted <= 0)
    {
        assert(false);
        return std::string();
    }

    err = GetLastError();
    if (err != 0)
    {
        assert(false);
        return std::string();
    }

    return str;
}

#endif

inline static std::string native(const QString& string)
{
#ifdef Q_OS_WIN
    return convert(string);
#else
    return string.toStdString();
#endif
}

inline static void print(const QString& string = QString())
{
    std::cout << native(string) << "\n";
}

inline static void printHelp()
{
    // Mind the 80 character line limit
    std::cout << native(CommandLineManager::tr(
"Usage:\n"
"license_wizard\n"
"    start in graphical mode\n"
"license_wizard --help\n"
"    show this help message\n"
"license_wizard --console <operation> <arguments>\n"
"    start in console mode, applying the specified operation with the\n"
"        specified arguments\n"
"\n"
"Operations and their arguments:\n"
"--list\n"
"    show the licenses list\n"
"--activate <serial_number> --host <url>\n"
"    activate with a serial number\n"
"--update <license_ID> --host <url>\n"
"    update the specified license\n"
"--activate-request <request_file_path>\n"
"    create an activation request\n"
"--update-request <license_ID> <request_file_path>\n"
"    create an update request for the specified license\n"
"--activate-response <serial_number> <request_file_path> <license_file_path>\n"
"        --host <url>\n"
"    send the activation request\n"
"--update-response <request_file_path> <license_file_path> --host <url>\n"
"    send the update request\n"
"--activate-offline <license_file_path>\n"
"    activate with the license file\n"
"--update-offline <license_file_path>\n"
"    update with the license file\n"
"--rehost-extract <license_ID> <rehost_file_path>\n"
"    extract the license for rehost\n"
"--rehost <rehost_file_path> --host <url>\n"
"    rehost the specified license\n"
"--rehost-request <fingerprint_file_path>\n"
"    create a rehost request\n"
"--rehost-response <rehost_file_path> <fingerprint_file_path>\n"
"        <license_file_path> --host <url>\n"
"    send the rehost request\n"
"--rehost-offline <license_file_path>\n"
"    rehost with the license file\n"
"--dongle-set-license <dongle_ID> <serial_number> --host <url>\n"
"    activate on the specifed key with a serial number\n"
"--dongle-blink <dongle_ID>\n"
"    activate the specifed key LED blinking\n"
              ));
}

inline static QString operationName(
        const CommandOperation operation)
{
    switch (operation)
    {
    case CommandOperation::Activate:
    case CommandOperation::ActivateOffline:
        return CommandLineManager::tr("License activation");
    case CommandOperation::Update:
    case CommandOperation::UpdateOffline:
        return CommandLineManager::tr("License update");
    case CommandOperation::CreateActivationRequest:
        return CommandLineManager::tr("License activation request creation");
    case CommandOperation::CreateUpdateRequest:
        return CommandLineManager::tr("License update request creation");
    case CommandOperation::SendActivationRequest:
        return CommandLineManager::tr("License activation request sending");
    case CommandOperation::SendUpdateRequest:
        return CommandLineManager::tr("License update request sending");
    case CommandOperation::GetFingerprint:
        return CommandLineManager::tr("License rehost request creation");
    case CommandOperation::ExtractForRehost:
        return CommandLineManager::tr("License extraction");
    case CommandOperation::Rehost:
    case CommandOperation::RehostOffline:
        return CommandLineManager::tr("License rehost");
    case CommandOperation::SendRehostRequest:
        return CommandLineManager::tr("License rehost request sending");
    case CommandOperation::DongleInstall:
        return CommandLineManager::tr("Setting license to the key");
    case CommandOperation::Help:
    case CommandOperation::List:
    case CommandOperation::DongleBlink:
    default:
        return CommandLineManager::tr("Unexpected operation");
    }
}

inline static uint32_t convertLicenseId(const QString& value)
{
    // Possible formats are only "0x02468ACE" or "02468ACE"
    // Leading zero MUST NOT be trimmed
    // Values of 0 and 0xFFFFFFFF are treated as invalid
    if (value.size() != 8 && value.size() != 10)
        return 0;
    bool ok = false;
    uint32_t result = static_cast<uint32_t>(value.toUInt(&ok, 16));
    if (!ok || result == 0 || result == 0xFFFFFFFF)
        return 0;
    return result;
}

inline static bool checkSerialNumberFormat(const QString& serialNumber)
{
    // 5 groups by 6 Base62 chars, separated with a dash
    static const QRegExp regex(
                "(([A-Za-z0-9]{6}\\-){4}([A-Za-z0-9]{6}))");
    return regex.exactMatch(serialNumber);
}

static bool checkFilePath(const QString& path)
{
    // Check if the target path is accessible
    QDir dir(path);
    if (!dir.isAbsolute() && !dir.isRelative())
        return false;

    // Since Qt under Windows swallows for example "D:/Temp/sample.txt/" as
    //   acceptable, but the API cannot handle it properly for obvious reasons,
    //   this case must be filtered
    // Repeated separators, like in "D:///Temp/sample.txt", are fine though
    if (path.endsWith('/') || path.endsWith('\\'))
        return false;

    // Check if the parent directory is applicable
    if (!dir.cdUp())
        return false;

    // Check if the parent directory is accessible and is actually a directory
    QFileInfo parentInfo(dir.path());
    if (!parentInfo.exists())
        return false;
    if (!parentInfo.isDir())
        return false;
#ifndef Q_OS_WIN
    // QFileInfo::isWritable() is optimized for NTFS under Windows
    if (!parentInfo.isWritable())
        return false;
#endif

    // Check if the target file is accessible and is a regular file
    QFileInfo targetInfo(path);
    if (!targetInfo.exists())
        return true; // it is OK if there is nothing at the specified path
    if (!targetInfo.isFile())
        return false;
#ifndef Q_OS_WIN
    // QFileInfo::isWritable() is optimized for NTFS under Windows
    if (!targetInfo.isWritable())
        return false;
#endif
    return true;
}

inline static bool checkFileExists(const QString& path)
{
    return QFile::exists(path);
}

CommandLineManager::CommandLineManager(CommandLineParser& parser) :
    QObject(),
    m_parser(parser)
{
}

int CommandLineManager::run()
{
    const QLocale locale = User::systemLocale();
    if (locale.language() != QLocale::English)
    {
        QTranslator* translator = new QTranslator(this);
        // Files: ":/translation/i18n-ru_RU"
        if (!translator->load(
                    locale, "i18n", "-", ":/translation"))
            assert(false);
        QCoreApplication::installTranslator(translator);
    }

#ifdef Q_OS_WIN
    print(QString());
    print(QString());
#endif

    int status = GRD_INTERNAL_ERROR;
    const Error error = performOperation(status);
    if (error != Error::Ok)
    {
        switch (error)
        {
        case Error::LicenseIdFormat:
            print(tr("Incorrect license ID format\n"
                     "Expected 0xNNNNNNNN, where each N is a hexadecimal "
                     "digit"));
            break;
        case Error::DongleIdFormat:
            print(tr("Incorrect dongle ID format\n"
                     "Expected 0xNNNNNNNN, where each N is a hexadecimal "
                     "digit"));
            break;
        case Error::SerialNumberFormat:
            print(tr("Incorrect serial number format\n"
                     "Expected NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN, where each "
                     "N is a Latin letter in upper or lower case or a digit"));
            break;
        case Error::FileNotFound:
            print(tr("File not found: %1"));
            break;
        case Error::UrlEmptyOrFormat:
            print(tr("Incorrect host URL format"));
            break;
        case Error::FilePathFormat:
            print(tr("Incorrect file path"));
            break;
        case Error::Ok:
        case Error::Internal:
        default:
            assert(false);
            print(tr("Internal error"));
            break;
        }
        status = -1;
    }
    else if (status)
    {
        QString message = getErrorMessage(status);
        if (message.isEmpty())
            message = tr("Internal error");
        print(message);
    }
    else // error == Error::Ok, status == GRD_OK
    {
        if (m_parser.operation() != CommandOperation::Help &&
                m_parser.operation() != CommandOperation::List &&
                m_parser.operation() != CommandOperation::DongleBlink)
        {
            print(tr("%1 completed").arg(operationName(m_parser.operation())));
        }
    }

#ifdef Q_OS_WIN
    print("\n");
#endif

    return static_cast<int>(status);
}

CommandLineManager::Error CommandLineManager::performOperation(int& status)
{
    switch (m_parser.operation())
    {
    case CommandOperation::Help:
        return showHelp(status);
    case CommandOperation::List:
        return showLicenseList(status);
    case CommandOperation::Activate:
        return activate(status);
    case CommandOperation::Update:
        return update(status);
    case CommandOperation::CreateActivationRequest:
        return createActivationRequest(status);
    case CommandOperation::CreateUpdateRequest:
        return createUpdateRequest(status);
    case CommandOperation::SendActivationRequest:
        return sendActivationRequest(status);
    case CommandOperation::SendUpdateRequest:
        return sendUpdateRequest(status);
    case CommandOperation::ExtractForRehost:
        return extractForRehost(status);
    case CommandOperation::Rehost:
        return rehost(status);
    case CommandOperation::GetFingerprint:
        return getFingerprint(status);
    case CommandOperation::SendRehostRequest:
        return sendRehostRequest(status);
    case CommandOperation::ActivateOffline:
    case CommandOperation::UpdateOffline:
    case CommandOperation::RehostOffline:
        return install(status);
    case CommandOperation::DongleInstall:
        return setDongleLicense(status);
    case CommandOperation::DongleBlink:
        return makeDongleBlink(status);
    default:
        assert(false);
        return showHelp(status);
    }
}

CommandLineManager::Error CommandLineManager::showHelp(int& status)
{
    if (m_parser.hasError())
    {
        switch (m_parser.error())
        {
        case ConsoleError::Ok:
            break;
        case ConsoleError::ConsoleOption:
            print(tr("Option %1 must go first").
                  arg("--console"));
            break;
        case ConsoleError::HostOption:
            print(tr("Option %1 must go last").
                  arg("--host"));
            break;
        case ConsoleError::ArgumentCount:
            print(tr("Incorrect number of arguments"));
            break;
        case ConsoleError::HostValue:
            print(tr("Option %1 has incorrect value").
                  arg("--host"));
            break;
        case ConsoleError::ArgumentValue:
            print(tr("Parameter has incorrect value"));
            break;
        case ConsoleError::NoOperation:
            print(tr("Unrecognized operation"));
            break;
        case ConsoleError::Unexpected:
        default:
            print(tr("Internal error"));
            break;
        }
        if (m_parser.error() != ConsoleError::Ok)
            print();
    }

    printHelp();
    status = GRD_OK;
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::showLicenseList(int& status)
{
    std::string licenseInfoStr;
    status = licenseGetInfo(
                licenseInfoStr,
                false);
    if (status != GRD_OK && status != GRD_NO_RESULTS_FOUND)
        return Error::Ok;

    const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data =
            DeviceChecker::parse(licenseInfoStr);

    if (data.data()->isEmpty())
    {
        print(tr("No licenses installed!"));
    }

    for (auto licIt : *data.data())
    {
        print(buildLicenseText(licIt.dongleType, licIt.id));

        for (auto prodIt : licIt.products)
        {
            print(prodIt.name + " (" + QString::number(prodIt.id) + ")");

            for (auto featIt : prodIt.features)
            {
                print(featIt.name + " (" + QString::number(featIt.id) + ")");
                print(featureDate(featIt, "-"));
                print(featureResource(featIt, "-"));
                print(featureIsVmForbidden(featIt) ? "+" : "-");
            }
        }
    }

    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::activate(int& status)
{
    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(m_parser.url(), host, port))
        return Error::UrlEmptyOrFormat;
    const QString serialNumber = m_parser.arguments().at(0);
    if (!checkSerialNumberFormat(serialNumber))
        return Error::SerialNumberFormat;
    status = licenseActivate(
                serialNumber,
                host, port,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::update(int& status)
{
    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(m_parser.url(), host, port))
        return Error::UrlEmptyOrFormat;
    const uint32_t licenseId = convertLicenseId(m_parser.arguments().at(0));
    if (licenseId == 0)
        return Error::LicenseIdFormat;
    status = licenseUpdate(
                licenseId,
                host, port,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::createActivationRequest(
        int& status)
{
    const QString requestFilePath = m_parser.arguments().at(0);
    if (!checkFilePath(requestFilePath))
        return Error::FilePathFormat;
    status = licenseCreateActivationRequest(
                requestFilePath,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::createUpdateRequest(int& status)
{
    const uint32_t licenseId = convertLicenseId(m_parser.arguments().at(0));
    if (licenseId == 0)
        return Error::LicenseIdFormat;
    const QString requestFilePath = m_parser.arguments().at(1);
    if (!checkFilePath(requestFilePath))
        return Error::FilePathFormat;
    status = licenseCreateUpdateRequest(
                licenseId, requestFilePath,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::sendActivationRequest(
        int& status)
{
    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(m_parser.url(), host, port))
        return Error::UrlEmptyOrFormat;
    const QString serialNumber = m_parser.arguments().at(0);
    if (!checkSerialNumberFormat(serialNumber))
        return Error::SerialNumberFormat;
    const QString requestFilePath = m_parser.arguments().at(1);
    if (!checkFileExists(requestFilePath))
        return Error::FileNotFound;
    const QString licenseFilePath = m_parser.arguments().at(2);
    if (!checkFilePath(licenseFilePath))
        return Error::FilePathFormat;
    status = licenseSendActivationRequest(
                serialNumber, requestFilePath, licenseFilePath,
                host, port,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::sendUpdateRequest(int& status)
{
    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(m_parser.url(), host, port))
        return Error::UrlEmptyOrFormat;
    const QString requestFilePath = m_parser.arguments().at(0);
    if (!checkFileExists(requestFilePath))
        return Error::FileNotFound;
    const QString licenseFilePath = m_parser.arguments().at(1);
    if (!checkFilePath(licenseFilePath))
        return Error::FilePathFormat;
    status = licenseSendUpdateRequest(
                requestFilePath, licenseFilePath,
                host, port,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::install(int& status)
{
    const QString licenseFilePath = m_parser.arguments().at(0);
    if (!checkFileExists(licenseFilePath))
        return Error::FileNotFound;
    status = licenseInstall(
                licenseFilePath,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::getFingerprint(int& status)
{
    const QString fingerprintFilePath = m_parser.arguments().at(0);
    if (!checkFilePath(fingerprintFilePath))
        return Error::FilePathFormat;
    status = licenseGetFingerprint(
                fingerprintFilePath,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::extractForRehost(int& status)
{
    const uint32_t licenseId = convertLicenseId(m_parser.arguments().at(0));
    if (licenseId == 0)
        return Error::LicenseIdFormat;
    const QString donorLicenseFilePath = m_parser.arguments().at(1);
    if (!checkFilePath(donorLicenseFilePath))
        return Error::FilePathFormat;
    status = licenseExtractForRehost(
                licenseId, donorLicenseFilePath,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::rehost(int& status)
{
    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(m_parser.url(), host, port))
        return Error::UrlEmptyOrFormat;
    const QString recipientLicenseFilePath = m_parser.arguments().at(0);
    if (!checkFileExists(recipientLicenseFilePath))
        return Error::FileNotFound;
    status = licenseRehost(
                recipientLicenseFilePath,
                host, port,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::sendRehostRequest(int& status)
{
    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(m_parser.url(), host, port))
        return Error::UrlEmptyOrFormat;
    const QString donorLicenseFilePath = m_parser.arguments().at(0);
    if (!checkFileExists(donorLicenseFilePath))
        return Error::FileNotFound;
    const QString fingerprintFilePath = m_parser.arguments().at(1);
    if (!checkFileExists(fingerprintFilePath))
        return Error::FileNotFound;
    const QString recipientLicenseFilePath = m_parser.arguments().at(2);
    if (!checkFilePath(recipientLicenseFilePath))
        return Error::FilePathFormat;
    status = licenseSendRehostRequest(
                donorLicenseFilePath, fingerprintFilePath,
                recipientLicenseFilePath,
                host, port,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::setDongleLicense(int& status)
{
    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(m_parser.url(), host, port))
        return Error::UrlEmptyOrFormat;
    const uint32_t dongleId = convertLicenseId(m_parser.arguments().at(0));
    if (dongleId == 0)
        return Error::DongleIdFormat;
    const QString serialNumber = m_parser.arguments().at(1);
    if (!checkSerialNumberFormat(serialNumber))
        return Error::SerialNumberFormat;
    status = dongleSetLicense(
                dongleId, serialNumber,
                host, port,
                false);
    return Error::Ok;
}

CommandLineManager::Error CommandLineManager::makeDongleBlink(int& status)
{
    const uint32_t dongleId = convertLicenseId(m_parser.arguments().at(0));
    if (dongleId == 0)
        return Error::DongleIdFormat;
    status = dongleBlink(dongleId);
    return Error::Ok;
}
