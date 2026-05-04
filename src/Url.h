#ifndef URL_H
#define URL_H

#include <QString>

// Check the URL
// Eventually we came to the following format:
// - protocol must be "https://" only
// - host must be formatted properly - either with octets, or with domains
// - port may not be specified, default port is 443
bool checkUrlValid(const QString& candidate);

// Check the URL first and then decompose it
bool decomposeUrl(const QString& candidate, std::string& host, uint32_t& port);

#endif // URL_H
