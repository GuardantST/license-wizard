#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include "User.h"

// Usage scenarios:
// license_wizard --help [...]
// license_wizard --console --list
// license_wizard --console --activate <serial_number> --host <url>
// license_wizard --console --update <license_ID> --host <url>
// license_wizard --console --activate-request <request_file_path>
// license_wizard --console --update-request <license_ID> <request_file_path>
// license_wizard --console --activate-response <serial_number> <request_file_path> <license_file_path> --host <url>
// license_wizard --console --update-response <request_file_path> <license_file_path> --host <url>
// license_wizard --console --activate-offline <license_file_path>
// license_wizard --console --update-offline <license_file_path>
// license_wizard --console --rehost-extract <license_ID> <rehost_license_file_path>
// license_wizard --console --rehost <rehost_license_file_path> --host <url>
// license_wizard --console --rehost-request <fingerprint_file_path>
// license_wizard --console --rehost-response <rehost_file_path> <fingerprint_file_path> <license_file_path> --host <url>
// license_wizard --console --rehost-offline <license_file_path>
// license_wizard --console --dongle-set-license <dongle_ID> <serial_number> --host <url>
// license_wizard --console --dongle-blink <dongle_ID>

class CommandLineParser
{
public:

    enum class ConsoleError
    {
        Ok,
        ConsoleOption, // console (or help) option must be set first
        HostOption, // host option expected
        HostValue, // empty (unexpected) host option value
        ArgumentValue, // empty (unexpected) operation argument value
        ArgumentCount, // wrong program arguments count (too small or too big)
        NoOperation, // no operation specified
        Unexpected = -1
    };

    enum class CommandOperation
    {
        Help,
        List,
        Activate, // online
        Update, // online
        CreateActivationRequest,
        CreateUpdateRequest,
        SendActivationRequest,
        SendUpdateRequest,
        ActivateOffline,
        UpdateOffline,
        ExtractForRehost,
        Rehost, // online
        GetFingerprint,
        SendRehostRequest,
        RehostOffline,
        DongleInstall,
        DongleBlink,
    };

    CommandLineParser();

    void run(int argc, char* argv[]);

    ConsoleError error() const
    {
        return m_error;
    }

    bool hasError() const
    {
        return m_error != ConsoleError::Ok;
    }

    bool isConsoleMode() const
    {
        return m_console;
    }

    CommandOperation operation() const
    {
        return m_operation;
    }

    const QStringList& arguments() const
    {
        return m_arguments;
    }

    const QString& url() const
    {
        return m_url;
    }

private:

    ConsoleError m_error;
    bool m_console;
    CommandOperation m_operation;
    QStringList m_arguments;
    QString m_url;

    ConsoleError parse(int argc, char* argv[]);
};

#endif // COMMANDLINEPARSER_H
