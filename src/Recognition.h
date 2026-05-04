#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <QVariant>
#include <QFile>

enum class RecognizedFileType
{
    Unknown,
    ActivationRequest, // request file
    UpdateRequest, // request file
    ActivationResponse, // license file
    UpdateResponse, // license file
    RehostFingerprint, // fingerprint file
    RehostDonorLicense, // rehost file
    RehostRecipientLicense, // license file
    Codes, // file with codes for writing a license to a dongle
};

inline RecognizedFileType recognizeFile(
        QString path, QStringList* stringsPtr = nullptr)
{
    const uint32_t requestMagic = 0x647FD9C3;
    const uint32_t responseMagic = 0xEC6B511D;
    const uint32_t rehostMagic = 0x6D154CAF;
    const uint32_t requestDongleMagic = 0x741E3977;
    const uint32_t responseDongleMagic = 0x8BCF08F1;

    const uint32_t numberOffset = 8;

    const uint32_t typeOffset = 80;
    const uint32_t activationType = 1;
    const uint32_t updateType = 2;
    const uint32_t rehostType = 4;

    QFile file(path);
    file.open(QFile::OpenModeFlag::ReadOnly);
    if (!file.isOpen())
        return RecognizedFileType::Unknown;

    QByteArray bytes = file.readAll();
    if (bytes.startsWith("{") && bytes.endsWith("}"))
    {
        if (bytes.contains("\"hostName\":") &&
                bytes.contains("\"fingerprint\":"))
            return RecognizedFileType::RehostFingerprint;
        else
            return RecognizedFileType::Unknown;
    }

    if (bytes.contains('-'))
    {
        QString string = QString::fromUtf8(bytes);
        if (!string.isEmpty())
        {
            const char pattern[] =
                    "([A-HJ-NP-Za-km-z1-9]{6}\\-){4}"
                    "[A-HJ-NP-Za-km-z1-9]{6}";

            QStringList strings = string.split('\n');
            for (int i = 0; i < strings.count(); ++i)
                while (strings[i].endsWith('\r') || strings[i].endsWith('\n'))
                    strings[i] = strings[i].left(strings[i].size() - 1);

            int count = 0;
            for (int i = 0; i < strings.count(); ++i)
            {
                if (strings[i].contains(QRegExp(pattern)))
                    count++;
                else
                    break;
            }
            if (count > 0)
            {
                while (strings.count() > count)
                    strings.takeLast();
                if (stringsPtr != nullptr)
                    *stringsPtr = strings;
                return RecognizedFileType::Codes;
            }
        }
    }

    bytes = QByteArray::fromBase64(bytes);
    if (bytes.isEmpty())
        return RecognizedFileType::Unknown;

    const uint32_t magic = *reinterpret_cast<uint32_t*>(bytes.data());
    if (magic == requestMagic)
    {
        if (*(bytes.data() + numberOffset) == '\0')
            return RecognizedFileType::ActivationRequest;
        else
            return RecognizedFileType::UpdateRequest;
    }
    else if (magic == requestDongleMagic)
    {
        return RecognizedFileType::UpdateRequest;
    }
    else if (magic == responseDongleMagic)
    {
        return RecognizedFileType::UpdateResponse;
    }
    else if (magic == responseMagic)
    {
        const uint32_t type = *(reinterpret_cast<uint32_t*>(
                                    bytes.data() + typeOffset));
        if (type == activationType)
            return RecognizedFileType::ActivationResponse;
        else if (type == updateType)
            return RecognizedFileType::UpdateResponse;
        else if (type == rehostType)
            return RecognizedFileType::RehostRecipientLicense;
        else
            return RecognizedFileType::Unknown;
    }
    else if (magic == rehostMagic)
        return RecognizedFileType::RehostDonorLicense;
    return RecognizedFileType::Unknown;
}

#endif // RECOGNITION_H
