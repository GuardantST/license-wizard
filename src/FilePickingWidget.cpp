#include "FilePickingWidget.h"
#include "ui_FilePickingWidget.h"
#include <cassert>

FilePickingWidget::FilePickingWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FilePickingWidget),
    m_fileType(FileType::Unknown),
    m_altFileType(FileType::Unknown),
    m_codesCount(-1)
{
    ui->setupUi(this);

    ui->selectLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->fingerprintLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->codesLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->selectButton->setObjectName(QStringLiteral("GButton"));
    ui->clearButton->setObjectName(QStringLiteral("GButtonCross"));
    ui->nameLabel->setObjectName(QStringLiteral("GLabelFileName"));
    ui->reselectLabel->setObjectName(QStringLiteral("GLabelFileError"));
    ui->reselectButton->setObjectName(QStringLiteral("GButtonInText"));
    ui->numberLabel->setObjectName(QStringLiteral("GLabelTipText"));

    connect(ui->selectButton, &QPushButton::clicked,
            this, &FilePickingWidget::onFileSelectionButtonClicked);
    connect(ui->reselectButton, &QPushButton::clicked,
            this, &FilePickingWidget::onFileReselectionButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked,
            this, &FilePickingWidget::onFileDeselectionButtonClicked);
}

FilePickingWidget::~FilePickingWidget()
{
    delete ui;
}

void FilePickingWidget::retranslate()
{
    ui->retranslateUi(this);
    setFileName();
    updateCodesCountText();
}

void FilePickingWidget::installForLicenseAndRehostFiles()
{
    if (m_fileType == FileType::Unknown)
    {
        m_fileType = FileType::License;
        m_altFileType = FileType::Rehost;
        ui->iconLabel->setObjectName(QStringLiteral("GLabelFileIconLicense"));
        ui->fingerprintLabel->setVisible(false);
        ui->codesLabel->setVisible(false);
        ui->numberLabel->setVisible(false);
    }
}

void FilePickingWidget::installForLicenseFiles()
{
    if (m_fileType == FileType::Unknown)
    {
        m_fileType = FileType::License;
        ui->iconLabel->setObjectName(QStringLiteral("GLabelFileIconLicense"));
        ui->fingerprintLabel->setVisible(false);
        ui->codesLabel->setVisible(false);
        ui->numberLabel->setVisible(false);
    }
}

void FilePickingWidget::installForRequestAndRehostFiles()
{
    if (m_fileType == FileType::Unknown)
    {
        m_fileType = FileType::Request;
        m_altFileType = FileType::Rehost;
        ui->iconLabel->setObjectName(QStringLiteral("GLabelFileIconRequest"));
        ui->fingerprintLabel->setVisible(false);
        ui->codesLabel->setVisible(false);
        ui->numberLabel->setVisible(false);
    }
}

void FilePickingWidget::installForFingerprintFiles()
{
    if (m_fileType == FileType::Unknown)
    {
        m_fileType = FileType::Fingerprint;
        ui->iconLabel->setObjectName(QStringLiteral("GLabelFileIconRequest"));
        ui->selectLabel->setVisible(false);
        ui->codesLabel->setVisible(false);
        ui->numberLabel->setVisible(false);
    }
}

void FilePickingWidget::installForCodeFiles()
{
    if (m_fileType == FileType::Unknown)
    {
        m_fileType = FileType::Codes;
        ui->iconLabel->setObjectName(QStringLiteral("GLabelFileIconLicense"));
        ui->selectLabel->setVisible(false);
        ui->fingerprintLabel->setVisible(false);
        ui->numberLabel->setVisible(false);
    }
}

void FilePickingWidget::dropProgress()
{
    m_filePath.clear();
    goNotSelected();
    m_codesCount = -1;
}

void FilePickingWidget::goSelected()
{
    if (m_fileType == FileType::Codes)
    {
        assert(!ui->selectLabel->isVisible());
        assert(!ui->fingerprintLabel->isVisible());
        ui->codesLabel->setVisible(false);
    }
    else if (m_fileType == FileType::Fingerprint)
    {
        assert(!ui->selectLabel->isVisible());
        ui->fingerprintLabel->setVisible(false);
        assert(!ui->codesLabel->isVisible());
    }
    else
    {
        ui->selectLabel->setVisible(false);
        assert(!ui->fingerprintLabel->isVisible());
        assert(!ui->codesLabel->isVisible());
    }
    ui->selectButton->setVisible(false);
    ui->nameFrame->setVisible(true);
    ui->reselectLabel->setVisible(false);
    ui->reselectButton->setVisible(true);
}

void FilePickingWidget::goNotSelected()
{
    if (m_fileType == FileType::Codes)
    {
        assert(!ui->selectLabel->isVisible());
        assert(!ui->fingerprintLabel->isVisible());
        ui->codesLabel->setVisible(true);
    }
    else if (m_fileType == FileType::Fingerprint)
    {
        assert(!ui->selectLabel->isVisible());
        ui->fingerprintLabel->setVisible(true);
        assert(!ui->codesLabel->isVisible());
    }
    else
    {
        ui->selectLabel->setVisible(true);
        assert(!ui->fingerprintLabel->isVisible());
        assert(!ui->codesLabel->isVisible());
    }
    ui->selectButton->setVisible(true);
    ui->nameFrame->setVisible(false);
    ui->reselectLabel->setVisible(false);
    ui->reselectButton->setVisible(false);
    if (m_fileType == FileType::Codes)
        ui->numberLabel->setVisible(false);
}

void FilePickingWidget::setFileName()
{
    ui->nameLabel->setText(filePathToName(m_filePath));
}

bool FilePickingWidget::queryFileOpen()
{
    const QString path = openFile(this, m_fileType, m_altFileType);
    if (path.isEmpty())
        return false;

    m_filePath = path;
    return true;
}

void FilePickingWidget::onFileSelectionButtonClicked()
{
    if (!m_filePath.isEmpty())
        return;

    if (!queryFileOpen())
        return;

    setFileName();
    goSelected();
    emit signalFileSelected();
}

void FilePickingWidget::onFileReselectionButtonClicked()
{
    if (m_filePath.isEmpty())
        return;

    if (!queryFileOpen())
        return;

    setFileName();
    goSelected();
    emit signalFileSelected();
}

void FilePickingWidget::onFileDeselectionButtonClicked()
{
    m_filePath.clear();
    goNotSelected();
    emit signalFileDeselected();
}

void FilePickingWidget::notifyError()
{
    ui->numberLabel->hide();
    ui->reselectLabel->setVisible(true);
}

void FilePickingWidget::notifyCodesCount(int count)
{
    assert(m_fileType == FileType::Codes &&
           m_altFileType == FileType::Unknown);
    m_codesCount = count;
    updateCodesCountText();
    ui->numberLabel->show();
}

void FilePickingWidget::updateCodesCountText()
{
    ui->numberLabel->setText(
                tr("There are %1 codes (keys) in this file").
                arg(m_codesCount));
}
