#ifndef DONGLEPAGEWIDGET_H
#define DONGLEPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class DonglePageWidget;
}

class DonglePageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit DonglePageWidget(QWidget* parent = nullptr);
    ~DonglePageWidget() override;

    void retranslate();

public slots:

    void dropProgress();
    void dropVisibility();

signals:

    void signalGoWrite(QStringList serialNumbers);

protected:

    bool eventFilter(QObject* watched, QEvent* event) override;

private:

    Ui::DonglePageWidget *ui;

    inline void installStep2();

    void goStep2();

private slots:

    void onActionButtonToggled(const bool checked);
    void onSerialLineTextChanged(const QString& text);

    void onContinueButtonClicked();
    void onFileSelected();
};

#endif // DONGLEPAGEWIDGET_H
