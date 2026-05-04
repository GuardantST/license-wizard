#ifndef ACTIVATIONPAGEWIDGET_H
#define ACTIVATIONPAGEWIDGET_H

#include <QWidget>
#include "DeviceChecker.h"

namespace Ui {
class ActivationPageWidget;
}

class ActivationPageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit ActivationPageWidget(QWidget* parent = nullptr);
    ~ActivationPageWidget();

    void retranslate();

    void notifyDevicesChanged(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    void notifyResponseObtained(const QByteArray& bytes);
    void notifyResponseObtainmentError();

    void jumpInitial();
    void jumpUpdateOffline(const uint32_t licenseId);

signals:

    void signalGoList();
    void signalGoWrite(QStringList serialNumbers);

    void signalLicenseActivate(QString serialNumber);
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

    void signalWriteLicenseResponseFile(
            QString licensePath, QByteArray responseData);

private:

    Ui::ActivationPageWidget *ui;

    void goLocal();
    void goRemote();
    void goDongle();

private slots:

    void onThisButtonToggled(const bool checked);
    void onAnotherButtonToggled(const bool checked);
    void onDongleButtonToggled(const bool checked);
};

#endif // ACTIVATIONPAGEWIDGET_H
