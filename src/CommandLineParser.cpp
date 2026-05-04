#include "CommandLineParser.h"
#include <QVector>
#include <cassert>

static const char HelpOption[]    = "--help";
static const char ConsoleOption[] = "--console";
static const char HostOption[]    = "--host";

struct OperationDescription
{
    const char* option;
    const CommandLineParser::CommandOperation operation;
    const int argumentsCount;
    const bool isHostNeeded;
};

static const QVector<OperationDescription> Operations = {
    // Show the list of installed licenses: "--list"
    { "--list"               , CommandLineParser::CommandOperation::List                    , 0, false },
    // Activate a license from serial number: "--activate" with <serial_number>
    { "--activate"           , CommandLineParser::CommandOperation::Activate                , 1, true },
    // Update the license by license ID: "--update" with <license_ID>
    { "--update"             , CommandLineParser::CommandOperation::Update                  , 1, true },
    // Activation request creation: "--activate-request" with <request_file_path>
    { "--activate-request"   , CommandLineParser::CommandOperation::CreateActivationRequest , 1, false },
    // Update request creation by license ID: "--update-request" with <license_ID> and <request_file_path>
    { "--update-request"     , CommandLineParser::CommandOperation::CreateUpdateRequest     , 2, false },
    // Activation request sending with serial number: "--activate-response" with <serial_number>, <request_file_path>, and <license_file_path>
    { "--activate-response"  , CommandLineParser::CommandOperation::SendActivationRequest   , 3, true },
    // Update request sending: "--update-response" with <request_file_path> and <license_file_path>
    { "--update-response"    , CommandLineParser::CommandOperation::SendUpdateRequest       , 2, true },
    // Activate a license from license file: "--activate-offline" with <license_file_path>
    { "--activate-offline"   , CommandLineParser::CommandOperation::ActivateOffline         , 1, false },
    // Update the license from license file: "--update-offline" with <license_file_path>
    { "--update-offline"     , CommandLineParser::CommandOperation::UpdateOffline           , 1, false },
    // Extract license from the current PC for rehost: "--rehost-extract" with <license_ID> and <rehost_file_path>
    { "--rehost-extract"     , CommandLineParser::CommandOperation::ExtractForRehost        , 2, false },
    // Install a rehosted license on the current PC: "--rehost" with <rehost_file_path>
    { "--rehost"             , CommandLineParser::CommandOperation::Rehost                  , 1, true },
    // Get fingerprint of the current PC for rehost: "--rehost-request" with <fingerprint_file_path>
    { "--rehost-request"     , CommandLineParser::CommandOperation::GetFingerprint          , 1, false },
    // Confirm the license rehost operation for this or another PC: "--rehost-response" with <rehost_file_path>, <fingerprint_file_path>, and <license_file_path>
    { "--rehost-response"    , CommandLineParser::CommandOperation::SendRehostRequest       , 3, true },
    // Install a rehosted license from license file: "--rehost-offline" with <license_file_path>
    { "--rehost-offline"     , CommandLineParser::CommandOperation::RehostOffline           , 1, false },
    // Set a license to the dongle from the serial number: "--dongle-set-license" with <dongle_ID> and <serial_number>
    { "--dongle-set-license" , CommandLineParser::CommandOperation::DongleInstall           , 2, true },
    // Activate the dongle LED blinking: "--dongle-blink" with <dongle_ID>
    { "--dongle-blink"       , CommandLineParser::CommandOperation::DongleBlink             , 1, false },
};

CommandLineParser::CommandLineParser() :
    m_error(ConsoleError::Unexpected),
    m_console(false),
    m_operation(CommandOperation::Help)
{
}

void CommandLineParser::run(int argc, char* argv[])
{
    m_error = parse(argc, argv);
}

inline static QString convert(const char* arg)
{
#ifdef Q_OS_WIN
    return QString::fromLocal8Bit(arg);
#else
    return arg;
#endif
}

CommandLineParser::ConsoleError CommandLineParser::parse(
        int argc, char* argv[])
{
    if (argc == 1)
        return ConsoleError::Ok;

    m_console = true;
    int current = 1;
    bool found = false;
    const QString first = convert(argv[current++])
#ifdef Q_OS_WIN
            .toLower()
#endif
            ;
    if (first == HelpOption)
        return ConsoleError::Ok;
    else if (first != ConsoleOption)
        return ConsoleError::ConsoleOption;

    if (argc <= current)
        return ConsoleError::ArgumentCount;

    // Now one of action options is awaited
    const QString second = convert(argv[current++])
#ifdef Q_OS_WIN
            .toLower()
#endif
            ;
    for (auto it = Operations.cbegin(); it != Operations.cend(); ++it)
    {
        if (second == it->option)
        {
            found = true;

            // Check argc for parameters count and host option with it's value
            //   if needed
            int expected = current + it->argumentsCount +
                    (it->isHostNeeded ? 2 : 0);
            if (argc != expected)
                return ConsoleError::ArgumentCount;

            for (int i = 0; i < it->argumentsCount; ++i)
            {
                const QString argument = convert(argv[current++]);
                if (argument.isEmpty())
                    return ConsoleError::ArgumentValue;

                m_arguments << argument;
            }

            if (it->isHostNeeded)
            {
                const QString host = convert(argv[current++])
#ifdef Q_OS_WIN
                        .toLower()
#endif
                        ;
                if (host != HostOption)
                    return ConsoleError::HostOption;

                const QString url = convert(argv[current++]);
                if (url.isEmpty())
                    return ConsoleError::HostValue;

                m_url = url;
            }

            m_operation = it->operation;

            break;
        }
    }

    return found ? ConsoleError::Ok : ConsoleError::NoOperation;
}
