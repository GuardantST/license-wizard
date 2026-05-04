#include "Url.h"
#include <QUrl>
#include <cassert>

bool checkUrlValid(const QString& candidate)
{
    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    return decomposeUrl(candidate, host, port);
}

bool decomposeUrl(const QString& candidate, std::string& host, uint32_t& port)
{
    const char httpsScheme[] = "https";
    const int httpsPort = 443;
    const char httpsProtocol[] = "https://";

    if (candidate.isEmpty())
        return false;

    // We have to check Latin letters manually, because QChar::isLetter() can
    //   detect any letter and there is no function to check if it is a Latin
    //   letter only...
    foreach (QChar c, candidate)
        if (!(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) &&
                !c.isNumber() && c != ':' && c != '/' && c != '-' &&
                c != '.' && c != '_')
            return false;

    // QUrl::fromUserInput() can change the specified string up to it's needs,
    //   e.g. "server:" is turned into "server"
    if (candidate.endsWith(':'))
        return false;

    // URL paths are acceptable, e.g. https://server.com/mirror/tokyo
    QUrl url(QUrl::fromUserInput(candidate));
    if (url.isEmpty() || url.host().isEmpty() || url.scheme() != httpsScheme ||
            !url.userInfo().isEmpty() || url.hasQuery() || url.hasFragment())
        return false;

    // QUrl::fromUserInput() can change the specified string up to it's needs,
    //   e.g. "192.168.1" is turned into "192.168.0.1" or "192.168.1024" is
    //   turned into "192.168.4.0", while "192.168.256.1" and "192.168.257.1"
    //   and "192.168.1.2.0" are fine for it, while "192.1680" is turned into
    //   "192.0.6.144"; QUrl::host() returns that maybe-changed value; so that,
    //   we have to check the candidate string manually for the appropriate
    //   octets count and values first
    if (candidate.contains('.'))
    {
        QString modded = candidate;
        if (!modded.startsWith(httpsProtocol))
            assert(false);
        modded = modded.right(
                    modded.size() -
                    static_cast<int>(sizeof(httpsProtocol) - 1));
        if (modded.contains(':'))
        {
            int pos = modded.lastIndexOf(':');
            modded = modded.left(pos);
        }

        QStringList sections = modded.split('.');
        if (sections[sections.count() - 1].isEmpty())
            return false;
        if (sections[sections.count() - 1][0].isNumber()) // octets
        {
            if (sections.count() != 4)
                return false;

            foreach (const QString& octet, sections)
            {
                bool ok = false;
                const int value = octet.toInt(&ok);
                if (!ok || value < 0 || value > 255)
                    return false;
            }
        }
    }

    if (url.port() == -1)
        url.setPort(httpsPort);
    if (url.port() <= 0 || url.port() > UINT16_MAX)
        return false;

    // Remove scheme (protocol) and port
    QString string = url.adjusted(
                QUrl::RemoveScheme | QUrl::RemovePort).toString();
    // Removing the scheme, e.g. in "https://server:443", only removes "https"
    //   and does not remove that double slash
    string = string.right(string.size() - 2);
    // Remove the trailing slash, but not sure if URL path would be clobbered
    //   as well
    if (string.endsWith('/'))
        string = string.left(string.size() - 1);

    host = string.toStdString();
    port = static_cast<uint32_t>(url.port());
    return true;
}
