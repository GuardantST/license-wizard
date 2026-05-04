#ifndef LICENSEPICKINGWIDGET_H
#define LICENSEPICKINGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTreeWidget>
#include "DeviceChecker.h"

namespace Ui {
class LicensePickingWidget;
}

class LicensePickingWidget : public QWidget
{
    Q_OBJECT

public:

    explicit LicensePickingWidget(QWidget* parent = nullptr);
    ~LicensePickingWidget();

    void retranslate();

    void notifyDevicesChanged(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    bool selectLicense(const uint32_t licenseId);
    void deselectLicense();

    uint32_t selectedLicenseId() const;
    DongleType selectedDongleType() const;

public slots:

    void dropProgress();

signals:

    void signalLicenseSelected();
    void signalLicenseDeselected();

private:

    Ui::LicensePickingWidget *ui;

    inline void installSelf();

    void goTree();
    void goSelected();
    void goBlank();

    inline void goTreeOrBlank();

    void rebuildTree(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);
    void retranslateTree();

    inline void setSelectButtonText(QPushButton* selectButton);
    inline void setLicenseItemText(QTreeWidgetItem* licItem);

    void noteLicenseSelected(QTreeWidgetItem* licItem);
    void noteLicenseDeselected();

private slots:

    void onLicenseDeselectionButtonClicked();

    void onTreeWidgetExpandedOrCollapsed(const QModelIndex& index);
};

#endif // LICENSEPICKINGWIDGET_H
