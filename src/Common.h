#ifndef COMMON_H
#define COMMON_H

#include "User.h"
#include <QFileDialog>
#include <QStorageInfo>
#include <cassert>

enum class FileType
{
    Unknown,
    Request, // license activation or update request file (ex *.toserver)
    License, // license activation or update response file (ex *.fromserver), or license rehost response (recipient) file
    Rehost, // license rehost extract (donor) file
    Fingerprint, // fingerprint file
    Codes, // file with codes for writing a license to a dongle
};

static const char RequestFileExtension[]     = "request";
static const char FingerprintFileExtension[] = "fingerprint";
static const char RehostFileExtension[]      = "rehost";
static const char LicenseFileExtension[]     = "license";

inline QString makeCaption(const FileType type)
{
    switch (type)
    {
    case FileType::Request:
        return QObject::tr("Request file");
    case FileType::License:
        return QObject::tr("License file");
    case FileType::Rehost:
        return QObject::tr("Rehost file");
    case FileType::Fingerprint:
        return QObject::tr("Fingerprint file");
    default:
        return QString();
    }
}

inline QString makeExtension(const FileType type)
{
    switch (type)
    {
    case FileType::Request:
        return QObject::tr("Request files") +
                " (*." + RequestFileExtension + ")";
    case FileType::License:
        return QObject::tr("License files") +
                " (*." + LicenseFileExtension + ")";
    case FileType::Rehost:
        return QObject::tr("Rehost files") +
                " (*." + RehostFileExtension + ")";
    case FileType::Fingerprint:
        return QObject::tr("Fingerprint files") +
                " (*." + FingerprintFileExtension + ")";
    default:
        return QString();
    }
}

inline QString makeExtensions(const FileType type, const FileType altType)
{
    QString result;
    if (type == FileType::License && altType == FileType::Rehost)
        result = QObject::tr("License and rehost files") +
                " (*." + LicenseFileExtension +
                " *." + RehostFileExtension + ")";
    else if (type == FileType::Request && altType == FileType::Rehost)
        result = QObject::tr("Request and rehost files") +
                " (*." + RequestFileExtension +
                " *." + RehostFileExtension + ")";
    else
        result = makeExtension(type);
    if (!result.isEmpty())
        result += ";;";
    result += QObject::tr("All files");
#ifdef Q_OS_WIN
    result += " (*.*)";
#else
    result += " (*)";
#endif
    return result;
}

inline QString openFile(
        QWidget* parent, const FileType fileType,
        const FileType altFileType = FileType::Unknown)
{
    User& user = User::instance();
    QString defaultPath;
    if (user.recentPath().isEmpty() || !QDir(user.recentPath()).exists())
        defaultPath = User::documentsPath();
    else
        defaultPath = user.recentPath();
    const QString result = QFileDialog::getOpenFileName(
                parent, makeCaption(fileType), defaultPath,
                makeExtensions(fileType, altFileType));
    if (!result.isEmpty())
        user.setRecentPath(QFileInfo(result).absoluteDir().absolutePath());
    return result;
}

inline QString saveFile(
        QWidget* parent, const FileType fileType,
        const QString& defaultName = QString())
{
    User& user = User::instance();
    QString defaultPath;
    if (user.recentPath().isEmpty() || !QDir(user.recentPath()).exists())
        defaultPath = User::documentsPath();
    else
        defaultPath = user.recentPath();
    if (!defaultName.isEmpty())
        defaultPath += '/' + defaultName;
    const QString result = QFileDialog::getSaveFileName(
                parent, makeCaption(fileType), defaultPath,
                makeExtensions(fileType, FileType::Unknown));
    if (!result.isEmpty())
        user.setRecentPath(QFileInfo(result).absoluteDir().absolutePath());
    return result;
}

inline bool isEnoughDiskSpace(
        const size_t size, const QString& filePath = QString())
{
    QStorageInfo storageInfo = QStorageInfo::root();
    qint64 freeBytesCount = storageInfo.bytesAvailable();

    qint64 fileSlack = 0;
    if (!filePath.isEmpty())
    {
        // Block size: returns -1 for Windows with NTFS
        int blockSize = storageInfo.blockSize();
        if (blockSize == -1)
            blockSize = 4096;

        QFileInfo fileInfo = QFileInfo(filePath);
        fileSlack = blockSize - fileInfo.size() % blockSize;
        if (fileSlack == blockSize)
            fileSlack = 0;
    }
    return freeBytesCount + fileSlack >= static_cast<qint64>(size);
}

inline bool checkFile(const QString& path)
{
    QFile file(path);
    file.open(QFile::OpenModeFlag::ReadWrite);
    if (!file.isOpen())
        return false;
    return true;
}

inline std::vector<uint8_t> readFile(const QString& path)
{
    QFile file(path);
    file.open(QFile::OpenModeFlag::ReadOnly);
    if (!file.isOpen())
        return std::vector<uint8_t>();
    QByteArray bytes = file.readAll();
    if (bytes.isEmpty())
        return std::vector<uint8_t>();
    return std::vector<uint8_t>(bytes.begin(), bytes.end());
}

inline bool writeFile(const QString& path, const std::vector<uint8_t>& data,
                      bool& isDiskSpaceIssue)
{
    assert(!isDiskSpaceIssue);
    QFile file(path);
    file.open(QFile::OpenModeFlag::WriteOnly);
    if (!file.isOpen())
        return false;
    if (!isEnoughDiskSpace(data.size(), file.fileName()))
    {
        isDiskSpaceIssue = true;
        return false;
    }
    const qint64 written = file.write(
                reinterpret_cast<const char*>(data.data()),
                static_cast<qint64>(data.size()));
    if (written != static_cast<qint64>(data.size()))
    {
        if (written >= 0)
            isDiskSpaceIssue = true;
        return false;
    }
    return true;
}

inline QString filePathToName(const QString& path)
{
    const int posSlash = path.lastIndexOf('/');
    const int posBackslash = path.lastIndexOf('\\');
    if (posSlash <= 0 && posBackslash <= 0)
        return path;

    if (posSlash <= posBackslash)
        return path.right(path.size() - posBackslash - 1);
    else
        return path.right(path.size() - posSlash - 1);
}

inline QString filePathToBaseName(const QString& path)
{
    QString name = filePathToName(path);
    const int posDot = name.lastIndexOf('.');
    if (posDot != -1 && posDot != 0 && posDot != name.size() - 1)
        return name.left(posDot);
    return name;
}

#endif // COMMON_H
