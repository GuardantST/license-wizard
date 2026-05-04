#ifndef WRITEONEPAGEWIDGET_H
#define WRITEONEPAGEWIDGET_H

#include <QWidget>
#include "License.h"

namespace Ui {
class WriteOncePageWidget;
}

class WriteOncePageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit WriteOncePageWidget(QWidget* parent = nullptr);
    ~WriteOncePageWidget() override;

    void retranslate();

    void notifyDongleLicenseSet();
    void notifyDongleLicenseSettingError();

    void setDongle(const uint32_t dongleId, const DongleType dongleType);

public slots:

    void dropProgress();

signals:

    void signalGoList();

    void signalWriteDongle(uint32_t dongleId, QStringList serialNumbers);

protected:

    bool eventFilter(QObject* watched, QEvent* event) override;

private:

    Ui::WriteOncePageWidget *ui;

    uint32_t m_dongleId;
    DongleType m_dongleType;

    QStringList m_serialNumbers;

    void goPrepare();
    void goPrepareSerial();
    void goPrepareFile();

    void updateHeaderText();

private slots:

    void onActionButtonToggled(const bool checked);
    void onSerialLineTextChanged(const QString& text);
    void onWriteButtonClicked();
    void onFileSelected();
    void onFileUnselected();
};

#endif // WRITEONEPAGEWIDGET_H
