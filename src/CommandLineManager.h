#ifndef COMMANDLINEMANAGER_H
#define COMMANDLINEMANAGER_H

#include "CommandLineParser.h"

class CommandLineManager : public QObject
{
    Q_OBJECT

public:

    CommandLineManager(CommandLineParser& parser);

    int run();

private:

    enum class Error
    {
        Ok,
        Internal,
        LicenseIdFormat,
        DongleIdFormat,
        SerialNumberFormat,
        FileNotFound,
        UrlEmptyOrFormat,
        FilePathFormat,
    };

    CommandLineParser& m_parser;

    Error performOperation(int& status);

    Error showHelp(int& status);
    Error showLicenseList(int& status);
    Error activate(int& status);
    Error update(int& status);
    Error createActivationRequest(int& status);
    Error createUpdateRequest(int& status);
    Error sendActivationRequest(int& status);
    Error sendUpdateRequest(int& status);
    Error install(int& status);
    Error getFingerprint(int& status);
    Error extractForRehost(int& status);
    Error rehost(int& status);
    Error sendRehostRequest(int& status);
    Error setDongleLicense(int& status);
    Error makeDongleBlink(int& status);
};

#endif // COMMANDLINEMANAGER_H
