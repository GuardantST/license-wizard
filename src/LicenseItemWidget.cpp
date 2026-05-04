#include "LicenseItemWidget.h"
#include "ui_LicenseItemWidget.h"
#include "VendorString.h"
#include <QMenu>
#include <QClipboard>

inline static bool canUpdate(const DongleType dongleType, const uint32_t licenseId)
{
    switch (dongleType)
    {
    case DongleType::Dl:
    case DongleType::DlNet:
        return true;
    case DongleType::Sign:
    case DongleType::SignNet:
    case DongleType::Time:
    case DongleType::TimeNet:
        return isLicenseIdValid(licenseId);
    case DongleType::Code:
    case DongleType::CodeNet:
    case DongleType::CodeTime:
    case DongleType::CodeTimeNet:
    case DongleType::Unknown:
    default:
        return false;
    }
}

inline static bool canWrite(const DongleType dongleType)
{
    return dongleVsLicense(dongleType);
}

LicenseItemWidget::LicenseItemWidget(
        const DongleType dongleType,
        const uint32_t licenseId,
        const uint32_t publicCode,
        const bool isRehostable,
        const bool isTrial,
        const bool isMaster,
        const bool isDetached,
        QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LicenseItemWidget),
    m_dongleType(dongleType),
    m_licenseId(licenseId),
    m_vendorPublicCode(publicCode),
    m_isMaster(isMaster)
{
    ui->setupUi(this);

    setSelected(false);

    // Needed for the correct background color setting
    this->setAttribute(Qt::WA_StyledBackground, true);

    switch (m_dongleType)
    {
    case DongleType::Sign:
    case DongleType::SignNet:
        ui->iconLabel->setObjectName(QStringLiteral("GLabelLicenseItemTypeSign"));
        break;
    case DongleType::Time:
    case DongleType::TimeNet:
        ui->iconLabel->setObjectName(QStringLiteral("GLabelLicenseItemTypeTime"));
        break;
    case DongleType::Code:
    case DongleType::CodeNet:
    case DongleType::CodeTime:
    case DongleType::CodeTimeNet:
        ui->iconLabel->setObjectName(QStringLiteral("GLabelLicenseItemTypeCode"));
        break;
    case DongleType::Dl:
    case DongleType::DlNet:
    default:
        ui->iconLabel->setObjectName(QStringLiteral("GLabelLicenseItemTypeDl"));
        break;
    }

    setLicenseNameText();
    setUpdateUnavailable();

    QMenu* optionsMenu = new QMenu(ui->optionsButton);
    if (canUpdate(dongleType, licenseId) && !isDetached)
    {
        optionsMenu->addAction(ui->actionCheckUpdates);
        optionsMenu->addAction(ui->actionOfflineUpdate);
    }
    if (isRehostable && !isMaster)
    {
        if (!optionsMenu->isEmpty())
            optionsMenu->addSeparator();
        optionsMenu->addAction(ui->actionRehost);
    }
    if (canWrite(dongleType) && !isMaster)
    {
        if (!optionsMenu->isEmpty())
            optionsMenu->addSeparator();
        optionsMenu->addAction(ui->actionWrite);
    }

    if (!optionsMenu->isEmpty())
        ui->optionsButton->setMenu(optionsMenu);
    else
        ui->optionsButton->setVisible(false);

    ui->nameButton->setObjectName(QStringLiteral("GButtonLicenseItem"));
    ui->nameButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    ui->nameButton->setNormalIcon(QIcon(":/icons/copySign.png"));
    ui->nameButton->setHighlightIcon(QIcon(":/icons/copySignHighlight.png"));

    ui->trialLabel->setObjectName(QStringLiteral("GLabelTrial"));
    if (!isTrial)
        ui->trialLabel->hide();

    ui->vendorLabel->setObjectName(QStringLiteral("GLabelTrial"));
    setVendorPublicCodeTooltip();

    ui->optionsButton->setObjectName(QStringLiteral("GButtonEllipsis"));
    ui->updateButton->setObjectName(QStringLiteral("GButtonOutline"));

    connect(ui->nameButton, &QPushButton::clicked,
            this, &LicenseItemWidget::onLicenseNameButtonClicked);
    connect(ui->updateButton, &QPushButton::clicked,
            this, &LicenseItemWidget::onLicenseUpdateButtonClicked);
    connect(ui->actionCheckUpdates, &QAction::triggered,
            this, &LicenseItemWidget::onLicenseCheckUpdateActionTriggered);
    connect(ui->actionOfflineUpdate, &QAction::triggered,
            this, &LicenseItemWidget::onLicenseUpdateOfflineActionTriggered);
    connect(ui->actionRehost, &QAction::triggered,
            this, &LicenseItemWidget::onLicenseRehostActionTriggered);
    connect(ui->actionWrite, &QAction::triggered,
            this, &LicenseItemWidget::onLicenseWriteActionTriggered);
}

LicenseItemWidget::~LicenseItemWidget()
{
    delete ui;
}

void LicenseItemWidget::retranslate()
{
    ui->retranslateUi(this);
    setVendorPublicCodeTooltip();
    setLicenseNameText();
}

bool LicenseItemWidget::isSelected() const
{
    return this->property(SelectedPropName).toBool();
}

void LicenseItemWidget::setSelected(bool selected)
{
    this->setProperty(SelectedPropName, selected);
}

void LicenseItemWidget::setUpdateAvailable()
{
    ui->updateButton->setVisible(true);
}

void LicenseItemWidget::setUpdateUnavailable()
{
    ui->updateButton->setVisible(false);
}

void LicenseItemWidget::setLicenseNameText()
{
    ui->nameButton->setText(buildLicenseTextFull(m_dongleType, m_licenseId));
}

void LicenseItemWidget::setVendorPublicCodeTooltip()
{
    ui->vendorLabel->setText(getVendorString(m_vendorPublicCode));
}

void LicenseItemWidget::onLicenseNameButtonClicked()
{
    QApplication::clipboard()->setText(
                QString::number(m_licenseId, 16).toUpper());
    emit signalLicenseIdCopiedToClipboard();
}

void LicenseItemWidget::onLicenseUpdateButtonClicked()
{
    emit signalLicenseUpdate(m_licenseId, m_isMaster);
}

void LicenseItemWidget::onLicenseCheckUpdateActionTriggered()
{
    emit signalLicenseCheckUpdate(m_licenseId, m_isMaster);
}

void LicenseItemWidget::onLicenseUpdateOfflineActionTriggered()
{
    emit signalLicenseUpdateOffline(m_licenseId);
}

void LicenseItemWidget::onLicenseRehostActionTriggered()
{
    emit signalGoRehost(m_licenseId);
}

void LicenseItemWidget::onLicenseWriteActionTriggered()
{
    emit signalGoWrite(m_licenseId, m_dongleType);
}
