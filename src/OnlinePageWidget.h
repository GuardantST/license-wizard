#ifndef ONLINEPAGEWIDGET_H
#define ONLINEPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class OnlinePageWidget;
}

class OnlinePageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit OnlinePageWidget(QWidget* parent = nullptr);
    ~OnlinePageWidget() override;

    void retranslate();

public slots:

    void dropProgress();
    void dropVisibility();

signals:

    void signalGoOffline();

    void signalLicenseActivate(QString serialNumber);
    void signalLicenseInstall(QString licensePath);
    void signalLicenseRehost(QString rehostPath);

protected:

    bool eventFilter(QObject* watched, QEvent* event) override;

private:

    Ui::OnlinePageWidget *ui;

    inline void installStep2();

    void goStep2();

private slots:

    void onActionButtonToggled(const bool checked);
    void onSerialLineTextChanged(const QString& text);

    void onGetButtonClicked();
    void onFileSelected();
};

#endif // ONLINEPAGEWIDGET_H
