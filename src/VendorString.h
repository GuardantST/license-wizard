#ifndef VENDORSTRING_H
#define VENDORSTRING_H

#include <QString>

// Returns the vendor code string (e.g. "DEMONVK") by the vendor public code
QString getVendorString(const uint32_t publicCode);

#endif // VENDORSTRING_H
