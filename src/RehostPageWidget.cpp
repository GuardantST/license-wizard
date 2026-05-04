#include "RehostPageWidget.h"
#include "ui_RehostPageWidget.h"
#include "Naming.h"

RehostPageWidget::RehostPageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::RehostPageWidget),
    m_licenseId(InvalidLicenseId)
{
    ui->setupUi(this);
    ui->backButton->adjustSize();

    ui->backButton->setObjectName(QStringLiteral("GButtonBack"));
    ui->headerLabel->setObjectName(QStringLiteral("GLabelMainHeader"));
    ui->rehostFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->fileFrame->setObjectName(QStringLiteral("GFrameFileSaveRehost"));
    ui->fileIconLabel->setObjectName(QStringLiteral("GLabelFileIconRehost"));
    ui->fileNameLabel->setObjectName(QStringLiteral("GLabelFileName"));
    ui->fileTipLabel->setObjectName(QStringLiteral("GLabelFileTipRehost"));
    ui->fileSaveButton->setObjectName(QStringLiteral("GButtonFileExtract"));
    ui->rehostInstructionLabel->setObjectName(QStringLiteral("GLabelNormalText"));

    connect(ui->backButton, &QPushButton::clicked,
            this, &RehostPageWidget::signalGoList);

    connect(ui->fileSaveButton, &QPushButton::clicked,
            this, &RehostPageWidget::onFileSavingButtonClicked);
}

RehostPageWidget::~RehostPageWidget()
{
    delete ui;
}

void RehostPageWidget::retranslate()
{
    ui->retranslateUi(this);
    ui->backButton->adjustSize();
    setTexts();
}

void RehostPageWidget::setLicense(const uint32_t licenseId)
{
    if (!isLicenseIdValid(licenseId))
        return;

    m_licenseId = licenseId;
    setTexts();
}

void RehostPageWidget::setTexts()
{
    ui->fileNameLabel->setText(buildRehostExtractFileName(m_licenseId));
    ui->headerLabel->setText(
                tr("License rehost ") +
                buildLicenseText(DongleType::Dl, m_licenseId));
}

void RehostPageWidget::onFileSavingButtonClicked()
{
    const QString rehostPath = saveFile(
                this, FileType::Rehost, ui->fileNameLabel->text());
    if (rehostPath.isEmpty())
        return;

    emit signalLicenseExtractForRehost(rehostPath, m_licenseId);
}
