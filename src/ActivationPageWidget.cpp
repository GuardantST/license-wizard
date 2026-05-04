#include "ActivationPageWidget.h"
#include "ui_ActivationPageWidget.h"
#include <QMutex>

// Child widgets (local page, it's online and offline pages, activation page)
//   use the two function for appropriate resizing and size adjusting:
// 1. dropProgress() - brings the widget to the initial state, making all
//   initially needed child widgets visible again, but remaining all the other
//   (not needed initially) child widgets invisible
// 2. dropVisibility() - makes all child widgets invisible, which leads to the
//   appropriate automatic resizing for the ActivationPageWidget's scrollArea

ActivationPageWidget::ActivationPageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ActivationPageWidget)
{
    ui->setupUi(this);
    ui->backButton->adjustSize();

    ui->backButton->setObjectName(QStringLiteral("GButtonBack"));
    ui->headerLabel->setObjectName(QStringLiteral("GLabelMainHeader"));
    ui->tipLabel->setObjectName(QStringLiteral("GLabelMainTip"));
    ui->step1NumberLabel->setObjectName(QStringLiteral("GLabelStepNumber"));
    ui->step1HeadLabel->setObjectName(QStringLiteral("GLabelStepHeader"));
    ui->thisButton->setObjectName(QStringLiteral("GButtonGiant"));
    ui->anotherButton->setObjectName(QStringLiteral("GButtonGiant"));
    ui->dongleButton->setObjectName(QStringLiteral("GButtonGiant"));

    connect(ui->backButton, &QPushButton::clicked,
            this, &ActivationPageWidget::signalGoList);

    connect(ui->thisButton, &QPushButton::toggled,
            this, &ActivationPageWidget::onThisButtonToggled);
    connect(ui->anotherButton, &QPushButton::toggled,
            this, &ActivationPageWidget::onAnotherButtonToggled);
    connect(ui->dongleButton, &QPushButton::toggled,
            this, &ActivationPageWidget::onDongleButtonToggled);

    connect(ui->localPage, &LocalPageWidget::signalLicenseActivate,
            this, &ActivationPageWidget::signalLicenseActivate);
    connect(ui->localPage, &LocalPageWidget::signalLicenseInstall,
            this, &ActivationPageWidget::signalLicenseInstall);
    connect(ui->localPage, &LocalPageWidget::signalLicenseRehost,
            this, &ActivationPageWidget::signalLicenseRehost);
    connect(ui->localPage, &LocalPageWidget::signalLicenseCreateActivationRequest,
            this, &ActivationPageWidget::signalLicenseCreateActivationRequest);
    connect(ui->localPage, &LocalPageWidget::signalLicenseCreateUpdateRequest,
            this, &ActivationPageWidget::signalLicenseCreateUpdateRequest);
    connect(ui->localPage, &LocalPageWidget::signalLicenseGetFingerprint,
            this, &ActivationPageWidget::signalLicenseGetFingerprint);
    connect(ui->remotePage, &RemotePageWidget::signalLicenseSendActivationRequest,
            this, &ActivationPageWidget::signalLicenseSendActivationRequest);
    connect(ui->remotePage, &RemotePageWidget::signalLicenseSendUpdateRequest,
            this, &ActivationPageWidget::signalLicenseSendUpdateRequest);
    connect(ui->remotePage, &RemotePageWidget::signalLicenseSendRehostRequest,
            this, &ActivationPageWidget::signalLicenseSendRehostRequest);
    connect(ui->remotePage, &RemotePageWidget::signalWriteLicenseResponseFile,
            this, &ActivationPageWidget::signalWriteLicenseResponseFile);
    connect(ui->donglePage, &DonglePageWidget::signalGoWrite,
            this, &ActivationPageWidget::signalGoWrite);

    // This is important
    ui->localPage->dropProgress();
    ui->remotePage->dropVisibility();
    ui->donglePage->dropVisibility();
}

ActivationPageWidget::~ActivationPageWidget()
{
    delete ui;
}

void ActivationPageWidget::retranslate()
{
    ui->retranslateUi(this);
    ui->backButton->adjustSize();
    ui->localPage->retranslate();
    ui->remotePage->retranslate();
    ui->donglePage->retranslate();
}

void ActivationPageWidget::notifyDevicesChanged(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    // Skip updates if they come too frequenty
    static QMutex mutex;
    if (mutex.tryLock())
    {
        ui->localPage->notifyDevicesChanged(data);
        mutex.unlock();
    }
}

void ActivationPageWidget::notifyResponseObtained(const QByteArray& bytes)
{
    ui->remotePage->notifyResponseObtained(bytes);
}

void ActivationPageWidget::notifyResponseObtainmentError()
{
    ui->remotePage->notifyResponseObtainmentError();
}

void ActivationPageWidget::jumpInitial()
{
    ui->thisButton->setAutoExclusive(false);
    ui->anotherButton->setAutoExclusive(false);
    ui->dongleButton->setAutoExclusive(false);
    ui->thisButton->setChecked(false);
    ui->anotherButton->setChecked(false);
    ui->dongleButton->setChecked(false);
    ui->thisButton->setAutoExclusive(true);
    ui->anotherButton->setAutoExclusive(true);
    ui->dongleButton->setAutoExclusive(true);
    ui->localPage->dropProgress();
    ui->remotePage->dropVisibility();
    ui->donglePage->dropVisibility();
    ui->stackedWidget->setCurrentWidget(ui->blankPage);
}

void ActivationPageWidget::jumpUpdateOffline(const uint32_t licenseId)
{
    ui->thisButton->setChecked(true);
    ui->localPage->jumpUpdateOffline(licenseId);
}

void ActivationPageWidget::goLocal()
{
    ui->localPage->dropProgress();
    ui->remotePage->dropVisibility();
    ui->donglePage->dropVisibility();
    ui->stackedWidget->setCurrentWidget(ui->localPage);
}

void ActivationPageWidget::goRemote()
{
    ui->localPage->dropVisibility();
    ui->remotePage->dropProgress();
    ui->donglePage->dropVisibility();
    ui->stackedWidget->setCurrentWidget(ui->remotePage);
}

void ActivationPageWidget::goDongle()
{
    ui->localPage->dropVisibility();
    ui->remotePage->dropVisibility();
    ui->donglePage->dropProgress();
    ui->stackedWidget->setCurrentWidget(ui->donglePage);
}

void ActivationPageWidget::onThisButtonToggled(const bool checked)
{
    if (checked)
        goLocal();
}

void ActivationPageWidget::onAnotherButtonToggled(const bool checked)
{
    if (checked)
        goRemote();
}

void ActivationPageWidget::onDongleButtonToggled(const bool checked)
{
    if (checked)
        goDongle();
}
