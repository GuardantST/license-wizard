#ifndef SETTINGSPAGEWIDGET_H
#define SETTINGSPAGEWIDGET_H

#include <QWidget>
#include <QLocale>

namespace Ui {
class SettingsPageWidget;
}

class SettingsPageWidget : public QWidget
{
    Q_OBJECT

public:

    explicit SettingsPageWidget(QWidget* parent = nullptr);
    ~SettingsPageWidget();

    void retranslate();

    void fillLangComboBox();
    void setLangComboBoxLocale(const QLocale& targetLocale);

    void setUrl(const QString& url);
    void setAutoCheck(const bool autoCheck);

signals:

    void signalGoMain();

    void signalChangeLocale(QLocale locale);

    void signalUpdateUrl(QString url);

    void signalSetAutoCheck(bool autoCheck);

private:

    Ui::SettingsPageWidget *ui;

private slots:

    void onServerLineEditingFinished();
    void onLogButtonClicked();

    void onLangComboBoxCurrentItemChanged(int index);
};

#endif // SETTINGSPAGEWIDGET_H
