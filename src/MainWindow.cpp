#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GrdLicApi.h"
#include "Version.h"
#include <QFile>
#include <QFontDatabase>
#include <QMessageBox>
#include <QHostInfo>
#include <cassert>

inline static bool isDefaultLocale(const QLocale& locale)
{
    return locale.language() == QLocale::English;
}

const DeviceChecker* MainWindow::buildDeviceChecker()
{
    const int deviceCheckerPeriodMsecs = 3000;
    DeviceChecker* deviceChecker = new DeviceChecker(deviceCheckerPeriodMsecs);
    deviceChecker->moveToThread(&m_deviceThread);
    return deviceChecker;
}

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_initialized(false),
    m_deviceChecker(buildDeviceChecker())
{
    ui->setupUi(this);

    QFile qss;
    qss.setFileName(":/styles/default.qss");
    qss.open(QFile::ReadOnly);
    QString stylesheet = qss.readAll();
    qApp->setStyleSheet(stylesheet);

    QFontDatabase::addApplicationFont(":/fonts/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Light.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont(":/fonts/NotoSansJP-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/NotoSansJP-Medium.ttf");

    qRegisterMetaType<QSharedPointer<QVector<DeviceChecker::LicenseInfo>>>(
                "QSharedPointer<QVector<LicenseInfo>>");

#ifdef Q_OS_LINUX
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-value"
#endif
    // Translations for QLineEdit
    QT_TRANSLATE_NOOP("QLineEdit", "&Undo");
    QT_TRANSLATE_NOOP("QLineEdit", "&Redo");
    QT_TRANSLATE_NOOP("QLineEdit", "Cu&t");
    QT_TRANSLATE_NOOP("QLineEdit", "&Copy");
    QT_TRANSLATE_NOOP("QLineEdit", "&Paste");
    QT_TRANSLATE_NOOP("QLineEdit", "Delete");
    QT_TRANSLATE_NOOP("QLineEdit", "Select All");
#ifdef Q_OS_LINUX
# pragma GCC diagnostic pop
#endif

    ui->settingsPage->setUrl(User::instance().url());
    ui->settingsPage->setAutoCheck(User::instance().doAutoCheck());

    connect(ui->mainPage, &MainPageWidget::signalGoSettings,
            this, &MainWindow::onGoSettings);
    connect(ui->settingsPage, &SettingsPageWidget::signalGoMain,
            this, &MainWindow::onGoMain);

    connect(ui->mainPage, &MainPageWidget::signalLicenseCheckUpdate,
            this, &MainWindow::onLicenseCheckUpdate);
    connect(ui->mainPage, &MainPageWidget::signalLicenseActivate,
            this, &MainWindow::onLicenseActivate);
    connect(ui->mainPage, &MainPageWidget::signalLicenseUpdate,
            this, &MainWindow::onLicenseUpdate);
    connect(ui->mainPage, &MainPageWidget::signalLicenseInstall,
            this, &MainWindow::onLicenseInstall);
    connect(ui->mainPage, &MainPageWidget::signalLicenseRehost,
            this, &MainWindow::onLicenseRehost);
    connect(ui->mainPage, &MainPageWidget::signalLicenseCreateActivationRequest,
            this, &MainWindow::onLicenseCreateActivationRequest);
    connect(ui->mainPage, &MainPageWidget::signalLicenseCreateUpdateRequest,
            this, &MainWindow::onLicenseCreateUpdateRequest);
    connect(ui->mainPage, &MainPageWidget::signalLicenseGetFingerprint,
            this, &MainWindow::onLicenseGetFingerprint);
    connect(ui->mainPage, &MainPageWidget::signalLicenseSendActivationRequest,
            this, &MainWindow::onLicenseSendActivationRequest);
    connect(ui->mainPage, &MainPageWidget::signalLicenseSendUpdateRequest,
            this, &MainWindow::onLicenseSendUpdateRequest);
    connect(ui->mainPage, &MainPageWidget::signalLicenseSendRehostRequest,
            this, &MainWindow::onLicenseSendRehostRequest);
    connect(ui->mainPage, &MainPageWidget::signalLicenseExtractForRehost,
            this, &MainWindow::onLicenseExtractForRehost);
    connect(ui->mainPage, &MainPageWidget::signalDongleBlink,
            this, &MainWindow::onDongleBlink);
    connect(ui->mainPage, &MainPageWidget::signalDongleWriteMass,
            this, &MainWindow::onDongleWriteMass);
    connect(ui->mainPage, &MainPageWidget::signalDongleWriteSolo,
            this, &MainWindow::onDongleWriteSolo);
    connect(ui->mainPage, &MainPageWidget::signalWriteLicenseResponseFile,
            this, &MainWindow::onWriteLicenseResponseFile);
    connect(ui->mainPage, &MainPageWidget::signalLicenseIdCopiedToClipboard,
            this, &MainWindow::onLicenseIdCopiedToClipboard);

    connect(ui->settingsPage, &SettingsPageWidget::signalUpdateUrl,
            this, &MainWindow::onServerAddressChanged);
    connect(ui->settingsPage, &SettingsPageWidget::signalSetAutoCheck,
            this, &MainWindow::onAutoCheckFlagChanged);

    connect(&m_deviceThread, &QThread::finished,
            this, &QObject::deleteLater);
    connect(this, &MainWindow::signalCreated,
            m_deviceChecker, &DeviceChecker::start);
    connect(this, &MainWindow::signalCloseWindow,
            m_deviceChecker, &DeviceChecker::stop);

    // This is needed for the looped check on timer period expiration
    connect(m_deviceChecker, &DeviceChecker::signalDevicesChanged,
            this, &MainWindow::onDevicesChanged,
            Qt::ConnectionType::BlockingQueuedConnection);

    // This is needed for the first check only
    connect(m_deviceChecker, &DeviceChecker::signalDevicesChanged,
            this, &MainWindow::onStartupLicenseUpdatesChecked,
            Qt::ConnectionType::BlockingQueuedConnection);

    // This is needed for the forcible check on license change (installation,
    //   update, rehost, etc) only
    connect(this, &MainWindow::signalCheckLicenses,
            m_deviceChecker, &DeviceChecker::check);

    // Order is important here
    ui->mainPage->fillLangComboBox();
    ui->settingsPage->fillLangComboBox();
    connect(ui->mainPage, &MainPageWidget::signalChangeLocale,
            this, &MainWindow::onLocaleChangeRequired);
    connect(ui->settingsPage, &SettingsPageWidget::signalChangeLocale,
            this, &MainWindow::onLocaleChangeRequired);

    updateWindowTitle();

    initializeTranslatorList();
    installLocale();

    QString string = QObject::tr("Guardant License Wizard") + ' ' +
            getVersionString();
#ifdef _DEBUG
    string += QObject::tr(" (debug build)");
#elif !defined(IS_PRODUCTION)
    string += QObject::tr(" (preview build)");
#endif
    loggerReport(string);

    string = QObject::tr("File path: ") + qApp->applicationFilePath();
    loggerReport(string);

    string = QObject::tr("Domain name: ") + QHostInfo::localDomainName();
    loggerReport(string);

    string = QObject::tr("Host name: ") + QHostInfo::localHostName();
    loggerReport(string);

    m_deviceThread.start();
}

MainWindow::~MainWindow()
{
    foreach (const auto& it, m_translators)
        if (it != nullptr)
            delete it;
    if (m_deviceThread.isRunning())
    {
        m_deviceThread.quit();
        m_deviceThread.wait();
    }
    delete ui;
}

void MainWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);
    if (m_initialized)
        return;

    m_initialized = true;

    // This signal cannot be emitted from the constructor
    emit signalCreated();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    // Make sure all signals, emited from the device checker, are disconnected
    disconnect(m_deviceChecker, &DeviceChecker::signalDevicesChanged,
               this, &MainWindow::onStartupLicenseUpdatesChecked);
    disconnect(m_deviceChecker, &DeviceChecker::signalDevicesChanged,
               this, &MainWindow::onDevicesChanged);

    // This signal cannot be emitted from the destructor
    emit signalCloseWindow();

    QMainWindow::closeEvent(event);

    loggerReport(QObject::tr("Guardant License Wizard") + " " +
                 QObject::tr("finished"));
}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateSelf();
    QMainWindow::changeEvent(event);
}

void MainWindow::initializeTranslatorList()
{
    const QList<User::Locale>& locales = User::supportedLocales();
    foreach (const User::Locale& locale, locales)
    {
        // Skip the English locale
        if (locale.locale == locales.first().locale)
            continue;

        // Fill the list of translators lazily
        m_translators.insert(locale.locale.name(), nullptr);
    }
}

void MainWindow::installLocale()
{
    const QLocale& locale = User::instance().locale();
    setTranslator(locale);
    ui->mainPage->setLangComboBoxLocale(locale);
    ui->settingsPage->setLangComboBoxLocale(locale);
}

void MainWindow::changeLocale(const QLocale& locale)
{
    User::instance().setLocale(locale);
    setTranslator(locale);
    ui->mainPage->setLangComboBoxLocale(locale);
    ui->settingsPage->setLangComboBoxLocale(locale);
}

void MainWindow::setTranslator(const QLocale& locale)
{
    foreach (QTranslator* translator, m_translators)
        if (translator != nullptr)
            qApp->removeTranslator(translator);

    if (isDefaultLocale(locale))
        return;

    QTranslator* translator = m_translators[locale.name()];
    if (translator == nullptr)
    {
        translator = new QTranslator(this);
        // Files: ":/translation/i18n-ru_RU"
        if (!translator->load(
                    locale, "i18n", "-", ":/translation"))
            assert(false);
        m_translators.insert(locale.name(), translator);
    }
    if (!qApp->installTranslator(translator))
        assert(false);
}

void MainWindow::retranslateSelf()
{
    ui->retranslateUi(this);
    ui->mainPage->retranslate();
    ui->settingsPage->retranslate();

    updateWindowTitle();
}

void MainWindow::updateWindowTitle()
{
    QString title = QObject::tr("Guardant License Wizard");
    title += ' ' + getVersionString();
#ifdef Q_OS_WIN64
    title += " (x64)";
#endif
#ifdef _DEBUG
    title += QObject::tr(" (debug build)");
#elif !defined(IS_PRODUCTION)
    title += QObject::tr(" (preview build)");
#endif
    setWindowTitle(title);
}

void MainWindow::goMain()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

void MainWindow::goSettings()
{
    ui->stackedWidget->setCurrentWidget(ui->settingsPage);
}

void MainWindow::onLocaleChangeRequired(QLocale locale)
{
    changeLocale(locale);
}

void MainWindow::onGoMain()
{
    goMain();
}

void MainWindow::onGoSettings()
{
    goSettings();
}

void MainWindow::onDevicesChanged(
        QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    // Once signals from the device checker start coming too frequently, the
    //   main thread gets uncapable of processing the data on time, and GUI
    //   becomes less responsive, up to practically unresponsive
    // Synchronization is not an issue here, unless we do such tricks like
    //   calling QCoreApplication::processEvents(), which can cause repeated
    //   function calls in one thread
    ui->mainPage->notifyDevicesChanged(data);
}

void MainWindow::onServerAddressChanged(QString url)
{
    User& user = User::instance();
    if (checkUrlValid(url))
    {
        user.setUrl(url);
    }
    else
    {
        QMessageBox::critical(
                    this,
                    QObject::tr("Guardant License Wizard"),
                    tr("Entered data is not URL"));
    }
    ui->settingsPage->setUrl(user.url());
}

void MainWindow::onAutoCheckFlagChanged(const bool autoCheck)
{
    User::instance().setAutoCheck(autoCheck);
}

int MainWindow::doWriteLicenseResponseFile(
        const QString& licensePath, const QByteArray& responseData,
        const bool needsLogging)
{
    std::vector<uint8_t> responseBytes(
                responseData.begin(), responseData.end());
    if (responseBytes.empty())
    {
        if (needsLogging)
            loggerReport("Could not get bytes for the license response data");
        return GRD_INTERNAL_ERROR;
    }

    if (!checkFile(licensePath))
        return GRD_FILE_CREATION_ERROR;

    bool isDiskSpaceIssue = false;
    if (!writeFile(licensePath, responseBytes, isDiskSpaceIssue))
    {
        if (needsLogging)
            loggerReport("Could not write the license response file");
        if (isDiskSpaceIssue)
            return GRD_DISK_SPACE_IS_OVER;
        return GRD_INTERNAL_ERROR;
    }

    return GRD_OK;
}

void MainWindow::issueNotification(const Notification notification)
{
    ui->mainPage->notifyMessage(notification);
}

void MainWindow::issueApiError(const int status)
{
    issueNotification(Notification(NotificationType::ApiError, status));
}

void MainWindow::enforce()
{
    emit signalCheckLicenses();
}

void MainWindow::onStartupLicenseUpdatesChecked(
        QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    // This is only for the first check
    disconnect(m_deviceChecker, &DeviceChecker::signalDevicesChanged,
               this, &MainWindow::onStartupLicenseUpdatesChecked);

    if (!DeviceChecker::hasValidLicenses(data))
        return;

    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    if (!User::instance().doAutoCheck())
    {
        unfreeze();
        return;
    }

    bool hasUpdates = false;
    int status = GRD_OK;
    for (auto it : * data.data())
    {
        if (it.empty)
            continue;

        const uint32_t licenseId = it.id;
        //const bool isMaster = it.isMaster; // unused
        status = licenseCheckUpdate(
                    licenseId,
                    host, port,
                    true);
        if (status == GRD_OK)
        {
            ui->mainPage->notifyLicenseUpdateAvailable(licenseId);
            hasUpdates = true;
        }
        else if (status == GRD_DONGLE_NOT_FOUND &&
                 dongleVsLicense(it.dongleType))
            continue; // skip
        else if (status != GRD_NO_UPDATES_AVAILABLE)
            break;
    }

    unfreeze();

    if (status == GRD_OK || status == GRD_NO_UPDATES_AVAILABLE)
    {
        issueNotification(
                    hasUpdates ?
                        NotificationType::LicenseUpdateAvailableAll :
                        NotificationType::NoMoreLicenseUpdates);
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseCheckUpdate(uint32_t licenseId, bool isMaster)
{
    // Not yet used
    Q_UNUSED(isMaster);

    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    const int status = licenseCheckUpdate(
                licenseId,
                host, port,
                true);

    unfreeze();

    if (status == GRD_OK)
    {
        issueNotification(NotificationType::LicenseUpdateAvailable);
        ui->mainPage->notifyLicenseUpdateAvailable(licenseId);
    }
    else if (status == GRD_NO_UPDATES_AVAILABLE)
    {
        issueNotification(NotificationType::NoMoreLicenseUpdates);
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseActivate(QString serialNumber)
{
    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        // Only possible for the standalone version, on first run, with no URL
        //   set yet
        assert(user.url().isEmpty());
        return;
    }

    freeze();

    const int status = licenseActivate(
                serialNumber,
                host, port,
                true);

    unfreeze();

    if (!status)
    {
        issueNotification(NotificationType::LicenseInstalled);
        ui->mainPage->jumpInitial();
        enforce();
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseUpdate(uint32_t licenseId, bool isMaster)
{
    // Not yet used
    Q_UNUSED(isMaster);

    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    const int status = licenseUpdate(
                licenseId,
                host, port,
                true);

    unfreeze();

    if (!status)
    {
        issueNotification(NotificationType::LicenseUpdated);
        ui->mainPage->notifyLicenseUpdateUnavailable(licenseId);
        enforce();
    }
    else
    {
        issueApiError(status);
        ui->mainPage->notifyLicenseUpdateAvailable(licenseId);
    }
}

void MainWindow::onLicenseCreateActivationRequest(QString requestPath)
{
    freeze();

    const int status = licenseCreateActivationRequest(
                requestPath,
                true);

    unfreeze();

    if (!status)
    {
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseCreateUpdateRequest(
        QString requestPath, uint32_t licenseId)
{
    freeze();

    const int status = licenseCreateUpdateRequest(
                licenseId, requestPath,
                true);

    unfreeze();

    if (!status)
    {
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseSendActivationRequest(
        QString requestPath, QString serialNumber)
{
    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    QByteArray responseBytes;
    const int status = licenseSendActivationRequest(
                serialNumber, requestPath, responseBytes,
                host, port,
                true);

    unfreeze();

    if (!status)
    {
        ui->mainPage->notifyResponseObtained(responseBytes);
    }
    else
    {
        issueApiError(status);
        ui->mainPage->notifyResponseObtainmentError();
    }
}

void MainWindow::onLicenseSendUpdateRequest(QString requestPath)
{
    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    QByteArray responseBytes;
    const int status = licenseSendUpdateRequest(
                requestPath, responseBytes,
                host, port,
                true);

    unfreeze();

    if (!status)
    {
        ui->mainPage->notifyResponseObtained(responseBytes);
    }
    else
    {
        issueApiError(status);
        ui->mainPage->notifyResponseObtainmentError();
    }
}

void MainWindow::onLicenseInstall(QString licensePath)
{
    freeze();

    const int status = licenseInstall(
                licensePath,
                true);

    unfreeze();

    if (!status)
    {
        issueNotification(NotificationType::LicenseInstalled);
        ui->mainPage->jumpInitial();
        enforce();
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseGetFingerprint(QString fingerprintPath)
{
    freeze();

    const int status = licenseGetFingerprint(
                fingerprintPath,
                true);

    unfreeze();

    if (!status)
    {
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseExtractForRehost(
        QString rehostPath, uint32_t licenseId)
{
    freeze();

    const int status = licenseExtractForRehost(
                licenseId, rehostPath,
                true);

    unfreeze();

    if (!status)
    {
        issueNotification(NotificationType::LicenseExtracted);
        ui->mainPage->jumpInitial();
        enforce();
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseRehost(QString rehostPath)
{
    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    const int status = licenseRehost(
                rehostPath,
                host, port,
                true);

    unfreeze();

    if (!status)
    {
        issueNotification(NotificationType::LicenseInstalled);
        ui->mainPage->jumpInitial();
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseSendRehostRequest(
        QString rehostPath, QString fingerprintPath)
{
    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    QByteArray responseBytes;
    const int status = licenseSendRehostRequest(
                rehostPath, fingerprintPath, responseBytes,
                host, port,
                true);

    unfreeze();

    if (!status)
    {
        ui->mainPage->notifyResponseObtained(responseBytes);
    }
    else
    {
        issueApiError(status);
        ui->mainPage->notifyResponseObtainmentError();
    }
}

void MainWindow::onDongleBlink(uint32_t dongleId)
{
    dongleBlink(dongleId);
}

void MainWindow::onDongleWriteMass(
        QVector<uint32_t> dongleIds, QStringList serialNumbers)
{
    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    // Try to apply serial numbers to dongles one by one, remembering the index
    //   of the recently attempted serial number for all dongles
    // Here we assume that if a license (serial number) cannot be written to
    //   one of these dongles, it cannot be written to any other of these
    //   dongles as well
    // The count of serial numbers can be less than the count of dongles
    int written = 0;
    int j = 0;
    for (int i = 0; i < dongleIds.size(); ++i)
    {
        if (j == serialNumbers.size())
        {
            // Issue this notification as if it has been issued by the API
            issueApiError(GRD_LICENSE_ALREADY_ACTIVATED);
            ui->mainPage->notifyMassDongleLicenseSettingError();
            break;
        }

        bool doBreak = false;
        const uint32_t dongleId = dongleIds[i];
        for (; j < serialNumbers.size(); ++j)
        {
            const QString& serialNumber = serialNumbers[j];
            const int status = dongleSetLicense(
                        dongleId, serialNumber,
                        host, port,
                        true);
            if (!status)
            {
                ui->mainPage->notifyMassDongleLicenseSet();
                ++written;
                break;
            }
            else if (status != GRD_LICENSE_ALREADY_ACTIVATED)
            {
                issueApiError(status);
                ui->mainPage->notifyMassDongleLicenseSettingError();
                doBreak = true;
                break;
            }
        }

        if (doBreak)
            break;
    }

    if (written == dongleIds.size())
    {
        issueNotification(NotificationType::LicenseInstalled);
        enforce();
    }

    unfreeze();
}

void MainWindow::onDongleWriteSolo(
        uint32_t dongleId, QStringList serialNumbers)
{
    User& user = User::instance();

    std::string host;
    uint32_t port = static_cast<uint32_t>(-1);
    if (!decomposeUrl(user.url(), host, port))
    {
        assert(false);
        return;
    }

    freeze();

    // Try to apply serial numbers to the dongle one by one
    bool isWrittenOrError = false;
    for (int i = 0; i < serialNumbers.size(); ++i)
    {
        const QString& serialNumber = serialNumbers[i];
        const int status = dongleSetLicense(
                    dongleId, serialNumber,
                    host, port,
                    true);
        if (!status)
        {
            issueNotification(NotificationType::LicenseInstalled);
            ui->mainPage->notifySoloDongleLicenseSet();
            ui->mainPage->jumpInitial();
            enforce();
            isWrittenOrError = true;
            break;
        }
        else if (status != GRD_LICENSE_ALREADY_ACTIVATED)
        {
            issueApiError(status);
            ui->mainPage->notifySoloDongleLicenseSettingError();
            isWrittenOrError = true;
            break;
        }
    }

    if (!isWrittenOrError)
    {
        // Issue this notification as if it has been issued by the API
        issueApiError(GRD_LICENSE_ALREADY_ACTIVATED);
        ui->mainPage->notifySoloDongleLicenseSet();
    }

    unfreeze();
}

void MainWindow::onWriteLicenseResponseFile(
        QString filePath, QByteArray data)
{
    const int status = doWriteLicenseResponseFile(
                filePath, data,
                true);

    if (!status)
    {
    }
    else
    {
        issueApiError(status);
    }
}

void MainWindow::onLicenseIdCopiedToClipboard()
{
    issueNotification(Notification(
                          NotificationType::LicenseIdCopiedToClipboard));
}

void MainWindow::freeze()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setDisabled(true);
}

void MainWindow::unfreeze()
{
    setEnabled(true);
    QApplication::restoreOverrideCursor();
}
