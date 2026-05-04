#include "MainPageWidget.h"
#include "ui_MainPageWidget.h"
#include "User.h"
#include "GrdLicApi.h"
#include <QTimer>
#include <QStyledItemDelegate>
#include <cassert>

MainPageWidget::MainPageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::MainPageWidget),
    m_notificationNumber(0),
    m_notification(NotificationType::None)
{
    ui->setupUi(this);

    // Needed for the correct combo box item stylesheet setting
    QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
    ui->langComboBox->setItemDelegate(itemDelegate);

    ui->settingsButton->setObjectName(QStringLiteral("GButtonSettings"));

    // Setting object name for the notification label needs to be done here,
    //   otherwise Qt could not make room for it (for some reason), and padding
    //   would not be taken into account...
    ui->notificationLabel->setObjectName(
                QStringLiteral("GLabelNotificationGray"));

    ui->notificationLabel->setVisible(false);

    connect(ui->settingsButton, &QPushButton::clicked,
            this, &MainPageWidget::signalGoSettings);
    connect(ui->langComboBox, static_cast<void (QComboBox::*)(int)>(
                &QComboBox::currentIndexChanged),
            this, &MainPageWidget::onLangComboBoxCurrentItemChanged);

    connect(ui->listPage, &ListPageWidget::signalGoActivation,
            this, &MainPageWidget::onGoActivation);
    connect(ui->listPage, &ListPageWidget::signalGoRehost,
            this, &MainPageWidget::onGoRehost);
    connect(ui->listPage, &ListPageWidget::signalGoWrite,
            this, &MainPageWidget::onGoWriteOnce);
    connect(ui->activationPage, &ActivationPageWidget::signalGoList,
            this, &MainPageWidget::onGoList);
    connect(ui->activationPage, &ActivationPageWidget::signalGoWrite,
            this, &MainPageWidget::onGoWriteSome);
    connect(ui->rehostPage, &RehostPageWidget::signalGoList,
            this, &MainPageWidget::onGoList);
    connect(ui->writeSomePage, &WriteSomePageWidget::signalGoList,
            this, &MainPageWidget::onGoList);
    connect(ui->writeOncePage, &WriteOncePageWidget::signalGoList,
            this, &MainPageWidget::onGoList);

    connect(ui->listPage, &ListPageWidget::signalLicenseUpdate,
            this, &MainPageWidget::signalLicenseUpdate);
    connect(ui->listPage, &ListPageWidget::signalLicenseCheckUpdate,
            this, &MainPageWidget::signalLicenseCheckUpdate);
    connect(ui->listPage, &ListPageWidget::signalLicenseUpdateOffline,
            this, &MainPageWidget::onLicenseUpdateOffline);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseActivate,
            this, &MainPageWidget::signalLicenseActivate);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseInstall,
            this, &MainPageWidget::signalLicenseInstall);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseRehost,
            this, &MainPageWidget::signalLicenseRehost);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseCreateActivationRequest,
            this, &MainPageWidget::signalLicenseCreateActivationRequest);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseCreateUpdateRequest,
            this, &MainPageWidget::signalLicenseCreateUpdateRequest);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseGetFingerprint,
            this, &MainPageWidget::signalLicenseGetFingerprint);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseSendActivationRequest,
            this, &MainPageWidget::signalLicenseSendActivationRequest);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseSendUpdateRequest,
            this, &MainPageWidget::signalLicenseSendUpdateRequest);
    connect(ui->activationPage, &ActivationPageWidget::signalLicenseSendRehostRequest,
            this, &MainPageWidget::signalLicenseSendRehostRequest);
    connect(ui->activationPage, &ActivationPageWidget::signalWriteLicenseResponseFile,
            this, &MainPageWidget::signalWriteLicenseResponseFile);
    connect(ui->rehostPage, &RehostPageWidget::signalLicenseExtractForRehost,
            this, &MainPageWidget::signalLicenseExtractForRehost);
    connect(ui->writeSomePage, &WriteSomePageWidget::signalBlinkDongle,
            this, &MainPageWidget::signalDongleBlink);
    connect(ui->writeSomePage, &WriteSomePageWidget::signalWriteDongles,
            this, &MainPageWidget::signalDongleWriteMass);
    connect(ui->writeOncePage, &WriteOncePageWidget::signalWriteDongle,
            this, &MainPageWidget::signalDongleWriteSolo);
    connect(ui->listPage, &ListPageWidget::signalLicenseRemove,
            this, &MainPageWidget::signalLicenseRemove);
    connect(ui->listPage, &ListPageWidget::signalLicenseIdCopiedToClipboard,
            this, &MainPageWidget::signalLicenseIdCopiedToClipboard);
}

MainPageWidget::~MainPageWidget()
{
    delete ui;
}

void MainPageWidget::retranslate()
{
    ui->retranslateUi(this);
    ui->listPage->retranslate();
    ui->activationPage->retranslate();
    ui->rehostPage->retranslate();
    ui->writeSomePage->retranslate();
    ui->writeOncePage->retranslate();
    if (m_notification.m_type != NotificationType::None)
        ui->notificationLabel->setText(notificationText(m_notification));
}

void MainPageWidget::fillLangComboBox()
{
    // Since the QComboBox cannot have a one-for-all icon (icons are only set
    //   per an item), and since the box model padding affects both the text
    //   and the image, we have to add a whitespace-only prefix (for left-to-
    //   right languages), according to the font metrics (Roboto, 13px) for the
    //   needed icon size (12 * 12) plus distance between the icon and the
    //   text, which is 12 px + 5 px = 17 px -> 16 px or 6 spaces
    // Note the QComboBox menu needed and implemented have different widths,
    //   and unwanted text elision can happen on any stylesheet property change
    constexpr char spaces[] = "      ";
    const QList<User::Locale>& locales = User::supportedLocales();
    const QLocale& current = User::instance().locale();
    int index = -1;
    foreach (const User::Locale& locale, locales)
    {
        QString name = spaces + locale.nativeName;
        if (!locale.commonName.isEmpty())
            name += " (" + locale.commonName + ")";
        ui->langComboBox->addItem(name, locale.locale);
        if (locale.locale.language() == current.language())
            index = ui->langComboBox->count() - 1;
    }

    if (index == -1) // unexpected value in the Registry
    {
        // Use English
        index = 0;
        User::instance().setLocale(locales.first().locale);
    }
    ui->langComboBox->setCurrentIndex(index);
}

void MainPageWidget::setLangComboBoxLocale(const QLocale& targetLocale)
{
    for (int index = 0; index < ui->langComboBox->count(); ++index)
    {
        const QLocale itemLocale =
                ui->langComboBox->itemData(index).toLocale();
        if (itemLocale == targetLocale)
        {
            if (ui->langComboBox->currentIndex() != index)
                ui->langComboBox->setCurrentIndex(index);
            break;
        }
    }
}

void MainPageWidget::notifyDevicesChanged(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    ui->listPage->notifyDevicesChanged(data);
    ui->activationPage->notifyDevicesChanged(data);
    ui->writeSomePage->notifyDevicesChanged(data);
}

void MainPageWidget::notifyLicenseUpdateAvailable(const uint32_t licenseId)
{
    ui->listPage->notifyLicenseUpdateAvailable(licenseId);
}

void MainPageWidget::notifyLicenseUpdateUnavailable(const uint32_t licenseId)
{
    ui->listPage->notifyLicenseUpdateUnavailable(licenseId);
}

void MainPageWidget::notifyResponseObtained(const QByteArray& bytes)
{
    ui->activationPage->notifyResponseObtained(bytes);
}

void MainPageWidget::notifyResponseObtainmentError()
{
    ui->activationPage->notifyResponseObtainmentError();
}

void MainPageWidget::notifyMassDongleLicenseSet()
{
    ui->writeSomePage->notifyDongleLicenseSet();
}

void MainPageWidget::notifyMassDongleLicenseSettingError()
{
    ui->writeSomePage->notifyDongleLicenseSettingError();
}

void MainPageWidget::notifySoloDongleLicenseSet()
{
    ui->writeOncePage->notifyDongleLicenseSet();
}

void MainPageWidget::notifySoloDongleLicenseSettingError()
{
    ui->writeOncePage->notifyDongleLicenseSettingError();
}

void MainPageWidget::jumpInitial()
{
    ui->activationPage->jumpInitial();
    goList();
}

void MainPageWidget::goList()
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}

void MainPageWidget::goActivation()
{
    ui->stackedWidget->setCurrentWidget(ui->activationPage);
}

void MainPageWidget::goRehost(const uint32_t licenseId)
{
    ui->rehostPage->setLicense(licenseId);
    ui->stackedWidget->setCurrentWidget(ui->rehostPage);
}

void MainPageWidget::goWriteSome(const QStringList& serialNumbers)
{
    ui->writeSomePage->setSerialNumbers(serialNumbers);
    ui->stackedWidget->setCurrentWidget(ui->writeSomePage);
}

void MainPageWidget::goWriteOnce(
        const uint32_t dongleId, const DongleType dongleType)
{
    ui->writeOncePage->setDongle(dongleId, dongleType);
    ui->stackedWidget->setCurrentWidget(ui->writeOncePage);
}

void MainPageWidget::onGoList()
{
    ui->activationPage->jumpInitial();
    goList();
}

void MainPageWidget::onGoActivation()
{
    goActivation();
}

void MainPageWidget::onGoRehost(uint32_t licenseId)
{
    goRehost(licenseId);
}

void MainPageWidget::onGoWriteSome(QStringList serialNumbers)
{
    goWriteSome(serialNumbers);
}

void MainPageWidget::onGoWriteOnce(uint32_t dongleId, DongleType dongleType)
{
    goWriteOnce(dongleId, dongleType);
}

void MainPageWidget::onLicenseUpdateOffline(uint32_t licenseId)
{
    goActivation();
    ui->activationPage->jumpUpdateOffline(licenseId);
}

void MainPageWidget::onLangComboBoxCurrentItemChanged(int index)
{
    QLocale locale = ui->langComboBox->itemData(index).toLocale();
    emit signalChangeLocale(locale);
}

QString MainPageWidget::notificationText(
        const Notification notification)
{
    switch (notification.m_type)
    {
    case NotificationType::InternalError:
        return tr("Internal error");
    case NotificationType::LicenseInstalled:
        return tr("License installed");
    case NotificationType::LicenseUpdated:
        return tr("License updated");
    case NotificationType::LicenseUpdateAvailable:
        return tr("License update available");
    case NotificationType::LicenseUpdateAvailableAll:
        return tr("Licenses updates available");
    case NotificationType::NoMoreLicenseUpdates:
        return tr("No more license updates");
    case NotificationType::CannotCheckLicenseUpdate:
        return tr("Unable to check license updates");
    case NotificationType::CannotCheckLicenseUpdateAll:
        return tr("Unable to check licenses updates");
    case NotificationType::CannotUpdateLicense:
        return tr("Unable to update the license");
    case NotificationType::LicenseExtracted:
        return tr("License extracted");
    case NotificationType::ApiError:
    {
        const int status = notification.m_status;
        QString message = getErrorMessage(status);
        if (message.isEmpty())
            message = tr("Internal error");
        return message;
    }
    case NotificationType::LicenseIdCopiedToClipboard:
        return tr("License ID copied to clipboard");
    case NotificationType::None:
    default:
        return QString();
    }
}

void MainPageWidget::notificationColor(
        const NotificationType notificationType, bool& red, bool& green)
{
    switch (notificationType)
    {
    case NotificationType::InternalError:
    case NotificationType::ApiError:
        red = true;
        break;
    case NotificationType::LicenseInstalled:
    case NotificationType::LicenseUpdated:
    case NotificationType::LicenseExtracted:
        green = true;
        break;
    case NotificationType::LicenseUpdateAvailable:
    case NotificationType::LicenseUpdateAvailableAll:
    case NotificationType::NoMoreLicenseUpdates:
    case NotificationType::CannotCheckLicenseUpdate:
    case NotificationType::CannotCheckLicenseUpdateAll:
    case NotificationType::CannotUpdateLicense:
    case NotificationType::LicenseIdCopiedToClipboard:
    case NotificationType::None:
    default:
        break;
    }
}

void MainPageWidget::notifyMessage(const Notification notification)
{
    // Note that the calling thread has to wait for 2 seconds
    // Only one notification message is possible simultaneously yet
    // Logic is simple - show, wait, disperse

    bool red = false;
    bool green = false;
    notificationColor(notification.m_type, red, green);

    if (ui->notificationLabel->isVisible())
        removeNotification(m_notificationNumber);

    m_notificationNumber++;
    m_notification = notification;

    if (red)
        ui->notificationLabel->setObjectName(
                    QStringLiteral("GLabelNotificationRed"));
    else if (green)
        ui->notificationLabel->setObjectName(
                    QStringLiteral("GLabelNotificationGreen"));
    else
        ui->notificationLabel->setObjectName(
                    QStringLiteral("GLabelNotificationGray"));
    ui->notificationLabel->style()->unpolish(ui->notificationLabel);
    ui->notificationLabel->style()->polish(ui->notificationLabel);
    ui->notificationLabel->setText(notificationText(notification));
    ui->notificationLabel->setVisible(true);

    const int notificationNumber = m_notificationNumber;
    QTimer::singleShot(2000, this, [this, notificationNumber]
    {
        removeNotification(notificationNumber);
    });
}

void MainPageWidget::removeNotification(const int notificationNumber)
{
    // Check if current notification, since one or even several more
    //   notifications might have come recently
    if (notificationNumber == m_notificationNumber)
    {
        ui->notificationLabel->setVisible(false);
        ui->notificationLabel->setText(QString());
        m_notification = Notification(NotificationType::None);
    }
}
