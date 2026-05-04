#ifndef OFFLINEPAGEWIDGET_H
#define OFFLINEPAGEWIDGET_H

#include <QWidget>
#include "DeviceChecker.h"

namespace Ui {
class OfflinePageWidget;
}

class OfflinePageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit OfflinePageWidget(QWidget* parent = nullptr);
    ~OfflinePageWidget();

    void retranslate();

    void notifyDevicesChanged(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    void jumpUpdateOffline(const uint32_t licenseId);

public slots:

    void dropProgress();
    void dropVisibility();

signals:

    void signalGoOnline();

    void signalLicenseInstall(QString licensePath);
    void signalLicenseCreateActivationRequest(QString requestPath);
    void signalLicenseCreateUpdateRequest(
            QString requestPath, uint32_t licenseId);
    void signalLicenseGetFingerprint(QString fingerprintPath);

private:

    Ui::OfflinePageWidget *ui;

    inline void installStep2();

    void goStep2();
    void goStep2LicenseSelected();
    void goStep2Plus();
    void goStep3();

    inline void setFileName();

private slots:

    void onActionButtonToggled(const bool checked);
    void onContinue2ButtonClicked();
    void onContinue2PlusButtonClicked();
    void onLicenseSelected();
    void onLicenseDeselected();
    void onFileSavingButtonClicked();

    void onFileSelected();
};

#endif // OFFLINEPAGEWIDGET_H
