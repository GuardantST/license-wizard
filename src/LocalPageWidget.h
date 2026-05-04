#ifndef LOCALPAGEWIDGET_H
#define LOCALPAGEWIDGET_H

#include <QWidget>
#include "DeviceChecker.h"

namespace Ui {
class LocalPageWidget;
}

class LocalPageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit LocalPageWidget(QWidget* parent = nullptr);
    ~LocalPageWidget();

    void retranslate();

    void notifyDevicesChanged(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    void jumpUpdateOffline(const uint32_t licenseId);

public slots:

    void dropProgress();
    void dropVisibility();

signals:

    void signalLicenseActivate(QString serialNumber);
    void signalLicenseInstall(QString licensePath);
    void signalLicenseRehost(QString rehostPath);
    void signalLicenseCreateActivationRequest(QString requestPath);
    void signalLicenseCreateUpdateRequest(
            QString requestPath, uint32_t licenseId);
    void signalLicenseGetFingerprint(QString fingerprintPath);

private:

    Ui::LocalPageWidget *ui;

    void goOnline();
    void goOffline();

private slots:

    void onGoOnline();
    void onGoOffline();
};

#endif // LOCALPAGEWIDGET_H
