#ifndef REHOSTPAGEWIDGET_H
#define REHOSTPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class RehostPageWidget;
}

class RehostPageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit RehostPageWidget(QWidget* parent = nullptr);
    ~RehostPageWidget();

    void retranslate();

    void setLicense(const uint32_t licenseId);

signals:

    void signalGoList();

    void signalLicenseExtractForRehost(QString rehostPath, uint32_t licenseId);

private:

    Ui::RehostPageWidget *ui;

    uint32_t m_licenseId;

    void setTexts();

private slots:

    void onFileSavingButtonClicked();
};

#endif // REHOSTPAGEWIDGET_H
