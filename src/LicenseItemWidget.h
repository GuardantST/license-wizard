#ifndef LICENSEITEMWIDGET_H
#define LICENSEITEMWIDGET_H

#include <QWidget>
#include "License.h"

namespace Ui {
class LicenseItemWidget;
}

class LicenseItemWidget : public QWidget
{
    Q_OBJECT

    // Allows recoloring via stylesheet
    Q_PROPERTY(bool m_selected
               READ isSelected
               WRITE setSelected
               DESIGNABLE true
               SCRIPTABLE true)

    // Make sure it can be bound to the stylesheets
    inline static const char SelectedPropName[] = "selected";

public:

    explicit LicenseItemWidget(
            const DongleType dongleType,
            const uint32_t licenseId,
            const uint32_t publicCode,
            const bool isRehostable,
            const bool isTrial,
            const bool isMaster,
            const bool isDetached,
            QWidget* parent = nullptr);
    ~LicenseItemWidget();

    void retranslate();

    bool isSelected() const;
    void setSelected(bool selected);

    void setUpdateAvailable();
    void setUpdateUnavailable();

signals:

    void signalLicenseUpdate(uint32_t licenseId, bool isMaster);
    void signalLicenseCheckUpdate(uint32_t licenseId, bool isMaster);
    void signalLicenseUpdateOffline(uint32_t licenseId);
    void signalGoRehost(uint32_t licenseId);
    void signalGoWrite(uint32_t dongleId, DongleType dongleType);
    void signalLicenseRemove(uint32_t licenseId);

    void signalLicenseIdCopiedToClipboard();

private:

    Ui::LicenseItemWidget *ui;

    const DongleType m_dongleType;
    const uint32_t m_licenseId;
    const uint32_t m_vendorPublicCode;
    const bool m_isMaster;

    inline void setLicenseNameText();
    inline void setVendorPublicCodeTooltip();

private slots:

    void onLicenseNameButtonClicked();
    void onLicenseUpdateButtonClicked();
    void onLicenseCheckUpdateActionTriggered();
    void onLicenseUpdateOfflineActionTriggered();
    void onLicenseRehostActionTriggered();
    void onLicenseWriteActionTriggered();
};

#endif // LICENSEITEMWIDGET_H
