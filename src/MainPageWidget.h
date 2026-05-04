#ifndef MAINPAGEWIDGET_H
#define MAINPAGEWIDGET_H

#include <QWidget>
#include "DeviceChecker.h"
#include "Notification.h"

namespace Ui {
class MainPageWidget;
}

class MainPageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit MainPageWidget(QWidget* parent = nullptr);
    ~MainPageWidget();

    void retranslate();

    void fillLangComboBox();
    void setLangComboBoxLocale(const QLocale& targetLocale);

    void notifyDevicesChanged(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    void notifyMessage(const Notification notification);

    void notifyLicenseUpdateAvailable(const uint32_t licenseId);
    void notifyLicenseUpdateUnavailable(const uint32_t licenseId);
    void notifyResponseObtained(const QByteArray& bytes);
    void notifyResponseObtainmentError();
    void notifyMassDongleLicenseSet();
    void notifyMassDongleLicenseSettingError();
    void notifySoloDongleLicenseSet();
    void notifySoloDongleLicenseSettingError();

    void jumpInitial();

signals:

    void signalGoSettings();

    void signalChangeLocale(QLocale locale);

    void signalLicenseCheckUpdate(uint32_t licenseId, bool isMaster);
    void signalLicenseActivate(QString serialNumber);
    void signalLicenseUpdate(uint32_t licenseId, bool isMaster);
    void signalLicenseInstall(QString licensePath);
    void signalLicenseRehost(QString rehostPath);
    void signalLicenseCreateActivationRequest(QString requestPath);
    void signalLicenseCreateUpdateRequest(
            QString requestPath, uint32_t licenseId);
    void signalLicenseGetFingerprint(QString fingerprintPath);
    void signalLicenseSendActivationRequest(
            QString requestPath, QString serialNumber);
    void signalLicenseSendUpdateRequest(QString requestPath);
    void signalLicenseSendRehostRequest(
            QString rehostPath, QString fingerprintPath);
    void signalLicenseExtractForRehost(QString rehostPath, uint32_t licenseId);
    void signalDongleBlink(uint32_t dongleId);
    void signalDongleWriteMass(
            QVector<uint32_t> dongleIds, QStringList serialNumbers);
    void signalDongleWriteSolo(uint32_t dongleId, QStringList serialNumbers);
    void signalLicenseRemove(uint32_t licenseId);

    void signalWriteLicenseResponseFile(
            QString licensePath, QByteArray responseData);

    void signalLicenseIdCopiedToClipboard();

private:

    Ui::MainPageWidget *ui;

    int m_notificationNumber;
    Notification m_notification;

    void goList();
    void goActivation();
    void goRehost(const uint32_t licenseId);
    void goWriteSome(const QStringList& serialNumbers);
    void goWriteOnce(const uint32_t dongleId, const DongleType dongleType);

    inline QString notificationText(const Notification notification);
    inline void notificationColor(
            const NotificationType notificationType, bool& red, bool& green);
    inline void removeNotification(const int notificationNumber);

private slots:

    void onGoList();
    void onGoActivation();
    void onGoRehost(uint32_t licenseId);
    void onGoWriteSome(QStringList serialNumbers);
    void onGoWriteOnce(uint32_t dongleId, DongleType dongleType);

    void onLangComboBoxCurrentItemChanged(int index);

    void onLicenseUpdateOffline(uint32_t licenseId);
};

#endif // MAINPAGEWIDGET_H
