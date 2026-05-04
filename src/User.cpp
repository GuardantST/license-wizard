#include "User.h"
#include "MainWindow.h"
#include <QSettings>
#include <QDir>
#include <QStandardPaths>
#include <QApplication>

static const char CommonTag[]     = "/Common";
static const char LangTag[]       = "/Lang";
static const char UrlTag[]        = "/URL";
static const char RecentPathTag[] = "/StandardPath";
static const char AutoCheckTag[]  = "/AutoCheck";

// We have to specify the language native names on our own, since
//   QLocale::nativeLanguageName() has mixed letter case (some starting from
//   upper case, some starting from lower case) and adds country description
static const QList<User::Locale> Locales = {
    {
        QLocale(QLocale::English, QLocale::UnitedStates),
        "English",
        QString()
    },
    {
        QLocale(QLocale::Spanish, QLocale::Spain),
        "Español",
        "Spanish"
    },
    {
        QLocale(QLocale::German, QLocale::Germany),
        "Deutsch",
        "German"
    },
    {
        QLocale(QLocale::Russian, QLocale::RussianFederation),
        "Русский",
        "Russian"
    },
    {
        QLocale(QLocale::Japanese, QLocale::Japan),
        "日本語",
        "Japanese"
    },
};

#ifndef IS_STANDALONE

inline static bool isRussianLocale(const QLocale& locale)
{
    return locale.language() == QLocale::Russian;
}

inline static bool isSystemLocaleRussian()
{
    return isRussianLocale(User::systemLocale());
}

#endif

const QList<User::Locale>& User::supportedLocales()
{
    return Locales;
}

QLocale User::systemLocale()
{
    QLocale resultLocale = QLocale::system();
    bool found = false;
    foreach (const User::Locale& candidateLocale, Locales)
    {
        if (resultLocale.language() == candidateLocale.locale.language())
        {
            found = true;
            break;
        }
    }
    if (!found)
        resultLocale = Locales.first().locale;
    return resultLocale;
}

const QString& User::defaultUrl()
{
    static const QString url =
#ifndef IS_STANDALONE
            isSystemLocaleRussian() ?
                "https://getlicense.guardant.ru" :
                "https://getlicense.guardant.com"
#else
            QString()
#endif
            ;
    return url;
}

struct Presettings
{
    QString url;
    bool isUrlFound;
    bool doAutoCheck;
    bool isAutoCheckFound;
};

static Presettings parsePresettingsFile()
{
    // Presettings file name
    const char defaultUrlIniFilePath[] = "station.ini";

    // Server address URL
    const char urlKeyName[] = "URL";
    // Automatic license update check on startup
    const char autoCheckKeyName[] = "AutoCheck";

    const char trueValueName[] = "TRUE";
    const char falseValueName[] = "FALSE";

    Presettings presettings;
    presettings.url = User::defaultUrl();
    presettings.isUrlFound = false;
    presettings.doAutoCheck = true;
    presettings.isAutoCheckFound = false;

    QFile file(defaultUrlIniFilePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Parsing the INI-file line by line
        // Sections are ignored and not even checked for sanity
        // Pairs of a key and a value are bound together using '=', do not use
        //   single or double quotes, extra tokens are ignored
        // Comments start with ';' or '#' and can only occupy the whole line,
        //   so that these characters only denote a comment if there are no or
        //   characters or whitespace characters before them only
        // Whitespaces are ignored
        // Letter case is ignored
        // Unexpected lines are not even checked for sanity
        // Note that the both comment characters, ';' and '#', can actually
        //   occur in a URL link
        // Note that if a key occurs more than once in a file, it's recent
        //   value is used
        while (!file.atEnd())
        {
            QString string = file.readLine();
            string = string.simplified(); // remove extra whitespaces

            // Skip: empty and whitespace-only lines, sections, whole-line
            //   comments
            if (string.isEmpty() || string.startsWith('[') ||
                    string.startsWith(';') || string.startsWith('#'))
            {
                continue;
            }
            else if (string.toLower().startsWith(
                         QString(urlKeyName).toLower()))
            {
                int index = string.indexOf('=');
                if (index < 0)
                    continue; // error

                string = string.right(string.size() - index - 1);
                string = string.simplified();

                index = string.indexOf(' ');
                if (index >= 0)
                    string = string.left(index);

                if (string.isEmpty())
                    continue; // error

                if (!checkUrlValid(string))
                    continue; // error

                presettings.url = string;
                presettings.isUrlFound = true;
            }
            else if (string.toLower().startsWith(
                         QString(autoCheckKeyName).toLower()))
            {
                int index = string.indexOf('=');
                if (index < 0)
                    continue; // error

                string = string.right(string.size() - index - 1);
                string = string.simplified();

                index = string.indexOf(' ');
                if (index >= 0)
                    string = string.left(index);

                if (string.isEmpty())
                    continue; // error

                if (string.toLower() == QString(falseValueName).toLower())
                {
                    presettings.doAutoCheck = false;
                    presettings.isAutoCheckFound = true;
                }
                else if (string.toLower() == QString(trueValueName).toLower())
                {
                    presettings.doAutoCheck = true;
                    presettings.isAutoCheckFound = true;
                }
                else
                    continue; // error
            }
            else // unexpected lines
            {
                // No equal sign is an obsolete format for URL but ok

                int index = string.indexOf(' ');
                if (index >= 0)
                    string = string.left(index);

                if (!checkUrlValid(string))
                    continue; // error

                presettings.url = string;
                presettings.isUrlFound = true;
            }
        }
    }
    return presettings;
}

inline static bool isEligiblePath(const QString& path)
{
    return !path.isEmpty() && QDir(path).exists();
}

void User::load()
{
    // Values from the presettings file have greater priority than the values
    //   from the application settings
    Presettings presettings = parsePresettingsFile();

    QSettings settings(qApp->organizationName(), qApp->applicationName());
    settings.beginGroup(CommonTag);
    m_locale = settings.value(LangTag, systemLocale().name()).toString();

    QString url = presettings.url;
    if (presettings.isUrlFound)
        m_url = url;
    else
        m_url = settings.value(UrlTag, url).toString();

    const QString recentPath = settings.value(
                RecentPathTag, QString()).toString();
    if (isEligiblePath(recentPath))
        m_recentPath = recentPath;

    bool doAutoCheck = presettings.doAutoCheck;
    if (presettings.isAutoCheckFound)
        m_doAutoCheck = doAutoCheck;
    else
        m_doAutoCheck = settings.value(AutoCheckTag, doAutoCheck).toBool();

    settings.endGroup();

    if (presettings.isUrlFound || presettings.isAutoCheckFound)
        save();
}

void User::save()
{
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    settings.beginGroup(CommonTag);
    settings.setValue(LangTag, m_locale.name());
    settings.setValue(UrlTag, m_url);
    settings.setValue(RecentPathTag, m_recentPath);
    settings.setValue(AutoCheckTag, m_doAutoCheck);
    settings.endGroup();
}

void User::setRecentPath(const QString& recentPath)
{
    if (isEligiblePath(recentPath))
        m_recentPath = recentPath;
    else if (!isEligiblePath(m_recentPath))
        m_recentPath = QStandardPaths::standardLocations(
                    QStandardPaths::DocumentsLocation).first();
    save();
}

QString User::documentsPath()
{
    return QStandardPaths::standardLocations(
                QStandardPaths::DocumentsLocation).first();
}
