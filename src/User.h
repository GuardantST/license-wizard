#ifndef USER_H
#define USER_H

#include <QVariant>
#include <QLocale>
#include "Url.h"

// Single class for all configuration-related code and related functionality
class User
{
private:

    User()
    {
        load();
    }

    ~User()
    {
    }

    User(const User&) = delete;
    User& operator=(const User&) = delete;
    User(User&&) = delete;
    User& operator=(User&&) = delete;

public:

    static User& instance()
    {
        static User* singleton = new User();
        return *singleton;
    }

    const QLocale& locale() const
    {
        return m_locale;
    }

    void setLocale(const QLocale& locale)
    {
        m_locale = locale;
        save();
    }

    const QString& url() const
    {
        return m_url;
    }

    bool getHostAndPort(std::string& host, uint32_t& port)
    {
        return decomposeUrl(m_url, host, port);
    }

    void setUrl(const QString& url)
    {
        m_url = url;
        save();
    }

    const QString& recentPath() const
    {
        return m_recentPath;
    }

    void setRecentPath(const QString& recentPath);

    bool doAutoCheck() const
    {
        return m_doAutoCheck;
    }

    void setAutoCheck(const bool autoCheck)
    {
        m_doAutoCheck = autoCheck;
        save();
    }

    static const QString& defaultUrl();

    struct Locale
    {
        QLocale locale;
        QString nativeName; // native language name (in native language)
        QString commonName; // common language name (in English)
    };

    static const QList<Locale>& supportedLocales();

    static QLocale systemLocale();

    static QString documentsPath();

private:

    // Currently used locale
    QLocale m_locale;

    // Address of the license activation server
    QString m_url;

    // Recently chosen (by the user via dialogs) file opening and file saving
    //   location (used for QFileDialog)
    QString m_recentPath;

    // Automatic license update checking on application startup flag
    bool m_doAutoCheck;

    void load();
    void save();
};

#endif // USER_H
