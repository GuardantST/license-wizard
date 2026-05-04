#include <QtPlugin>
#ifdef Q_OS_WIN
# include <Windows.h>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_LINUX)
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
#endif
#include "CommandLineManager.h"
#include "MainWindow.h"
#include <QApplication>
#include <cassert>

// Both CLI and GUI versions are available, but under Windows OS CLI cannot be
//   impemented directly, since the mode is set as a linker option during
//   build, so it is implemented via a bypass

int main(int argc, char* argv[])
{
    const char organizationName[]   = "Guardant";
    const char organizationDomain[] = "guardant.ru";
    const char applicationName[]    = "License Wizard";

    CommandLineParser parser;
    parser.run(argc, argv);
    int result;
    if (parser.hasError() || parser.isConsoleMode())
    {
#ifdef Q_OS_WIN
        if (AttachConsole(ATTACH_PARENT_PROCESS))
        {
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
        }
        else
        {
            assert(false);
        }
#endif

        QCoreApplication application(argc, argv);
        application.setOrganizationDomain(organizationDomain);
        application.setOrganizationName(organizationName);
        application.setApplicationName(applicationName);

        result = CommandLineManager(parser).run();
    }
    else
    {
        QApplication application(argc, argv);
        application.setAttribute(Qt::AA_DontShowIconsInMenus);
        application.setOrganizationDomain(organizationDomain);
        application.setOrganizationName(organizationName);
        application.setApplicationName(applicationName);

        MainWindow window;
        window.show();
        result = application.exec();
    }

    return result;
}
