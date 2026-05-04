#include "LocalPageWidget.h"
#include "ui_LocalPageWidget.h"

LocalPageWidget::LocalPageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LocalPageWidget)
{
    ui->setupUi(this);

    connect(ui->onlinePage, &OnlinePageWidget::signalGoOffline,
            this, &LocalPageWidget::onGoOffline);
    connect(ui->offlinePage, &OfflinePageWidget::signalGoOnline,
            this, &LocalPageWidget::onGoOnline);

    connect(ui->onlinePage, &OnlinePageWidget::signalLicenseActivate,
            this, &LocalPageWidget::signalLicenseActivate);
    connect(ui->onlinePage, &OnlinePageWidget::signalLicenseInstall,
            this, &LocalPageWidget::signalLicenseInstall);
    connect(ui->onlinePage, &OnlinePageWidget::signalLicenseRehost,
            this, &LocalPageWidget::signalLicenseRehost);
    connect(ui->offlinePage, &OfflinePageWidget::signalLicenseInstall,
            this, &LocalPageWidget::signalLicenseInstall);
    connect(ui->offlinePage, &OfflinePageWidget::signalLicenseCreateActivationRequest,
            this, &LocalPageWidget::signalLicenseCreateActivationRequest);
    connect(ui->offlinePage, &OfflinePageWidget::signalLicenseCreateUpdateRequest,
            this, &LocalPageWidget::signalLicenseCreateUpdateRequest);
    connect(ui->offlinePage, &OfflinePageWidget::signalLicenseGetFingerprint,
            this, &LocalPageWidget::signalLicenseGetFingerprint);
}

LocalPageWidget::~LocalPageWidget()
{
    delete ui;
}

void LocalPageWidget::retranslate()
{
    ui->retranslateUi(this);
    ui->onlinePage->retranslate();
    ui->offlinePage->retranslate();
}

void LocalPageWidget::notifyDevicesChanged(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    ui->offlinePage->notifyDevicesChanged(data);
}

void LocalPageWidget::jumpUpdateOffline(const uint32_t licenseId)
{
    goOffline();
    ui->offlinePage->jumpUpdateOffline(licenseId);
}

void LocalPageWidget::dropProgress()
{
    goOnline();
}

void LocalPageWidget::dropVisibility()
{
    ui->onlinePage->dropVisibility();
    ui->offlinePage->dropVisibility();
}

void LocalPageWidget::goOnline()
{
    ui->onlinePage->dropProgress();
    ui->offlinePage->dropVisibility();
    ui->stackedWidget->setCurrentWidget(ui->onlinePage);
}

void LocalPageWidget::goOffline()
{
    ui->onlinePage->dropVisibility();
    ui->offlinePage->dropProgress();
    ui->stackedWidget->setCurrentWidget(ui->offlinePage);
}

void LocalPageWidget::onGoOnline()
{
    goOnline();
}

void LocalPageWidget::onGoOffline()
{
    goOffline();
}
