#include "VendorString.h"

#define nsk_MAX_CODE_LEN    6       // Количество влияемых символов в коде.
#define nsk_MAX_CHARS       40      // Сколько знаков в одном символе.

#define asc2binNSK_char1    ((uint8_t)'!')
#define asc2binNSK_char2    ((uint8_t)'#')
#define asc2binNSK_const1   0xF4240000ul
#define asc2binNSK_const2   0xFA3E8000ul

// Циклический сдвиг байта влево на 1
#define ROTL(x)        (((x) >> 7) | ((x) << 1))

// Digit to char conversion
// Many of magic numbers are historically approved
static uint8_t bin2ascNSK(uint8_t byDigit)
{
    if (byDigit <= 9)
        return '0' + byDigit;
    if (byDigit >= 10 && byDigit < 36)
        return ('A' - 10) + byDigit;
    if (byDigit == 36)
        return '+';
    if (byDigit == 37)
        return '-';
    if (byDigit == 38)
        return '&';

    return '_';
}

//- Demo Codes
#define GrdDC_DEMONVK       0x519175b7Lu  // Demo public code
#define GrdDC_DEMORDO       0x51917645Lu  // Demo private read code
#define GrdDC_DEMOPRF       0x51917603Lu  // Demo private write code
#define GrdDC_DEMOMST       0x5191758cLu  // Demo private master code

void uint32_tCodeToString(uint32_t dwCode, char* lpszCodeString, uint32_t dwCodeLen)
{
    uint16_t i = nsk_MAX_CODE_LEN;
    uint8_t cb = 0xFF;
    uint8_t* p = (uint8_t*)lpszCodeString;
    uint8_t dv = 0;
    uint8_t byTmp = 0;

    switch (dwCode)
    {
    case GrdDC_DEMONVK:
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
        strcpy_s(lpszCodeString, dwCodeLen, "DEMONVK");
#else
        strcpy(lpszCodeString, "DEMONVK");
#endif
        return;
    case GrdDC_DEMORDO:
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
        strcpy_s(lpszCodeString, dwCodeLen, "DEMORDO");
#else
        strcpy(lpszCodeString, "DEMORDO");
#endif
        return;
    case GrdDC_DEMOPRF:
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
        strcpy_s(lpszCodeString, dwCodeLen, "DEMOPRF");
#else
        strcpy(lpszCodeString, "DEMOPRF");
#endif
        return;
    case GrdDC_DEMOMST:
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
        strcpy_s(lpszCodeString, dwCodeLen, "DEMOMST");
#else
        strcpy(lpszCodeString, "DEMOMST");
#endif
        return;
    }

    if (dwCode >= asc2binNSK_const1)
        dv = asc2binNSK_char1;
    if (dwCode >= asc2binNSK_const2)
        dv = asc2binNSK_char2;

    p += i;
    *p = 0;

    do
    {
        byTmp = (uint8_t)(dwCode % nsk_MAX_CHARS);
        *--p = bin2ascNSK(byTmp);
        dwCode /= nsk_MAX_CHARS;
    }
    while (--i != 0);

    i = nsk_MAX_CODE_LEN;

    do
    {
        cb = ROTL(cb);
        cb = ROTL(cb);
        cb += *p++;
    }
    while ((--i) != 0);

    byTmp = cb % nsk_MAX_CHARS;
    *p++ = bin2ascNSK(byTmp);
    *p = 0;

    if (dv != 0)
        ((uint8_t*)lpszCodeString)[0] = dv;
}

QString getVendorString(const uint32_t publicCode)
{
    char string[8] = { 0 };
    uint32_tCodeToString(publicCode, string, sizeof(string));
    return string;
}
