#ifndef LISTPAGEWIDGET_H
#define LISTPAGEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include "DeviceChecker.h"

namespace Ui {
class ListPageWidget;
}

class ListPageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit ListPageWidget(QWidget* parent = nullptr);
    ~ListPageWidget();

    void retranslate();

    void notifyDevicesChanged(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    void notifyLicenseUpdateAvailable(const uint32_t licenseId);
    void notifyLicenseUpdateUnavailable(const uint32_t licenseId);

signals:

    void signalGoActivation();
    void signalGoRehost(uint32_t licenseId);
    void signalGoWrite(uint32_t dongleId, DongleType dongleType);

    void signalLicenseUpdate(uint32_t licenseId, bool isMaster);
    void signalLicenseCheckUpdate(uint32_t licenseId, bool isMaster);
    void signalLicenseUpdateOffline(uint32_t licenseId);
    void signalLicenseRemove(uint32_t licenseId);

    void signalLicenseIdCopiedToClipboard();

private:

    Ui::ListPageWidget *ui;

    QSharedPointer<QVector<DeviceChecker::LicenseInfo>> m_data;

    void goBlank();
    void goTree();

    void rebuildTree(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);
    void retranslateTree();

    QTreeWidgetItem* licenseItem(const uint32_t licenseId);

    inline QString setFeatureItemIconToolTipText(
            const DeviceChecker::FeatureInfo& featureInfo);

    bool changeLicense(const DeviceChecker::LicenseInfo& licenseInfo);
    bool changeProduct(
            const DeviceChecker::ProductInfo& productInfo,
            QTreeWidgetItem* licenseItem);
    bool changeFeature(
            const DeviceChecker::FeatureInfo& featureInfo,
            QTreeWidgetItem* productItem);

    void addLicense(const DeviceChecker::LicenseInfo& licenseInfo);
    void addProduct(
            const DeviceChecker::ProductInfo& productInfo,
            QTreeWidgetItem* licenseItem);
    void addFeature(
            const DeviceChecker::FeatureInfo& featureInfo,
            QTreeWidgetItem* productItem);

    void removeProduct(const uint32_t productId, QTreeWidgetItem* licenseItem);
    void removeFeature(const uint32_t featureId, QTreeWidgetItem* productItem);

private slots:

    void onCurrentItemChanged(
            QTreeWidgetItem *current, QTreeWidgetItem *previous);
};

#endif // LISTPAGEWIDGET_H
