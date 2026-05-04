#ifndef REMOTEPAGEWIDGET_H
#define REMOTEPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class RemotePageWidget;
}

class RemotePageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit RemotePageWidget(QWidget* parent = nullptr);
    ~RemotePageWidget() override;

    void retranslate();

    void notifyResponseObtained(const QByteArray& responseBytes);
    void notifyResponseObtainmentError();

public slots:

    void dropProgress();
    void dropVisibility();

signals:

    void signalLicenseSendActivationRequest(
            QString requestPath, QString serialNumber);
    void signalLicenseSendUpdateRequest(QString requestPath);
    void signalLicenseSendRehostRequest(
            QString rehostPath, QString fingerprintPath);

    void signalWriteLicenseResponseFile(
            QString licensePath, QByteArray responseData);

protected:

    bool eventFilter(QObject* watched, QEvent* event) override;

private:

    Ui::RemotePageWidget *ui;

    // Recently cached response bytes
    QByteArray m_responseBytes;

    inline void installStep2();

    void goStep2();
    void goStep3();
    void goStep3ActivationRequestFileSelected();
    void goStep3UpdateRequestFileSelected();
    void goStep3RehostFileSelected();
    void goStep3FingerprintFileSelected();
    void goStep4();

private slots:

    void onContinue2ButtonClicked();
    void onMainFileSelectedOrReselected();
    void onMainFileDeselected();
    void onAuxFileSelectedOrReselected();
    void onAuxFileDeselected();
    void onContinue3AnyButtonClicked();
    void onSerialLineTextChanged(const QString& text);
    void onFileSavingButtonClicked();
};

#endif // REMOTEPAGEWIDGET_H
