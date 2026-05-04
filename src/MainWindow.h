#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QThread>
#include "DeviceChecker.h"
#include "Notification.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

signals:

    void signalCreated();
    void signalCloseWindow();
    void signalCheckLicenses();

protected:

    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    void changeEvent(QEvent *event) override;

private:

    Ui::MainWindow *ui;

    // List of all supported translators
    QMap<QString, QTranslator*> m_translators;

    bool m_initialized;
    QThread m_deviceThread;
    const DeviceChecker* const m_deviceChecker;

    const DeviceChecker* buildDeviceChecker();

    void initializeTranslatorList();
    void installLocale();
    void changeLocale(const QLocale& locale);
    void setTranslator(const QLocale& locale);

    void retranslateSelf();

    void updateWindowTitle();

    void goMain();
    void goSettings();

    int doWriteLicenseResponseFile(
            const QString& licensePath, const QByteArray& responseData,
            const bool needsLogging);
    
    void issueNotification(const Notification notification);
    void issueApiError(const int status);

    void freeze();
    void unfreeze();

    void enforce();

private slots:

    void onLocaleChangeRequired(QLocale locale);

    void onGoMain();
    void onGoSettings();

    void onDevicesChanged(
            QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    void onServerAddressChanged(QString url);

    void onAutoCheckFlagChanged(const bool autoCheck);

    void onStartupLicenseUpdatesChecked(
            QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    // API operations normally take not more than 30 seconds (this this the
    //   worst case), so they are performed instantly, in the main GUI thread
    void onLicenseCheckUpdate(
            uint32_t licenseId, bool isMaster);
    void onLicenseActivate(
            QString serialNumber);
    void onLicenseUpdate(
            uint32_t licenseId, bool isMaster);
    void onLicenseCreateActivationRequest(
            QString requestPath);
    void onLicenseCreateUpdateRequest(
            QString requestPath, uint32_t licenseId);
    void onLicenseSendActivationRequest(
            QString requestPath, QString serialNumber);
    void onLicenseSendUpdateRequest(
            QString requestPath);
    void onLicenseInstall(
            QString licensePath);
    void onLicenseGetFingerprint(
            QString fingerprintPath);
    void onLicenseExtractForRehost(
            QString rehostPath, uint32_t licenseId);
    void onLicenseRehost(
            QString rehostPath);
    void onLicenseSendRehostRequest(
            QString rehostPath, QString fingerprintPath);
    void onDongleBlink(
            uint32_t dongleId);
    void onDongleWriteMass(
            QVector<uint32_t> dongleIds, QStringList serialNumbers);
    void onDongleWriteSolo(
            uint32_t dongleId, QStringList serialNumbers);

    void onWriteLicenseResponseFile(
            QString filePath, QByteArray data);

    void onLicenseIdCopiedToClipboard();
};

#endif // MAINWINDOW_H
