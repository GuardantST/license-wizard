#ifndef WRITESOMEPAGEWIDGET_H
#define WRITESOMEPAGEWIDGET_H

#include <QWidget>
#include "DeviceChecker.h"

class QPushButton;

namespace Ui {
class WriteSomePageWidget;
}

class WriteSomePageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit WriteSomePageWidget(QWidget* parent = nullptr);
    ~WriteSomePageWidget();

    void retranslate();

    void setSerialNumbers(const QStringList& serialNumbers);

    void notifyDevicesChanged(
            const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data);

    // Notification on serial numbers exhausted can be separated from the other
    //   errors, e.g. making the progress bar chunks yellow instead of red
    void notifyDongleLicenseSet();
    void notifyDongleLicenseSettingError();

signals:

    void signalGoList();

    void signalWriteDongles(
            QVector<uint32_t> dongleIds, QStringList serialNumbers);
    void signalBlinkDongle(uint32_t dongleId);

private:

    Ui::WriteSomePageWidget *ui;

    QStringList m_serialNumbers;
    void addDongle(const uint32_t dongleId, const DongleType dongleType);

    uint32_t getDongleId(QTreeWidgetItem* item) const;

    void updateWriteOnceButtonText(QPushButton* writeButton);

private slots:

    void onDongleWriteButtonClicked();
    void onDongleBlinkButtonClicked();
};

#endif // WRITESOMEPAGEWIDGET_H
