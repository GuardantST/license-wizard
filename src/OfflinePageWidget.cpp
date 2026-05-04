#include "OfflinePageWidget.h"
#include "ui_OfflinePageWidget.h"
#include "Naming.h"
#include "Recognition.h"
#include <cassert>

OfflinePageWidget::OfflinePageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::OfflinePageWidget)
{
    ui->setupUi(this);

    ui->step2NumberLabel->setObjectName(QStringLiteral("GLabelStepNumber"));
    ui->step2HeadLabel->setObjectName(QStringLiteral("GLabelStepHeader"));
    ui->onlineButton->setObjectName(QStringLiteral("GButtonRefresh"));
    ui->step2BodyFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->newButton->setObjectName(QStringLiteral("GButtonToggleableLeft"));
    ui->updateButton->setObjectName(QStringLiteral("GButtonToggleableMiddle"));
    ui->rehostButton->setObjectName(QStringLiteral("GButtonToggleableRight"));
    ui->step2InstructionRequestLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->step2InstructionRehostLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->fileFrame->setObjectName(QStringLiteral("GFrameFileSaveRequest"));
    ui->fileIconLabel->setObjectName(QStringLiteral("GLabelFileIconRequest"));
    ui->fileNameLabel->setObjectName(QStringLiteral("GLabelFileName"));
    ui->fileSaveButton->setObjectName(QStringLiteral("GButtonFileSave"));
    ui->continue2Button->setObjectName(QStringLiteral("GButton"));
    ui->step2pBodyFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->step2pInstructionActivationLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->step2pInstructionUpdateLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->step2pInstructionRehostLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->step2pResultLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->continue2pButton->setObjectName(QStringLiteral("GButton"));
    ui->step3NumberLabel->setObjectName(QStringLiteral("GLabelStepNumber"));
    ui->step3HeadLabel->setObjectName(QStringLiteral("GLabelStepHeader"));
    ui->step3BodyFrame->setObjectName(QStringLiteral("GFrameWhite"));

    ui->fileWidget->installForLicenseFiles();

    connect(ui->onlineButton, &QPushButton::clicked,
            this, &OfflinePageWidget::signalGoOnline);

    connect(ui->newButton, &QPushButton::toggled,
            this, &OfflinePageWidget::onActionButtonToggled);
    connect(ui->updateButton, &QPushButton::toggled,
            this, &OfflinePageWidget::onActionButtonToggled);
    connect(ui->rehostButton, &QPushButton::toggled,
            this, &OfflinePageWidget::onActionButtonToggled);

    connect(ui->continue2Button, &QPushButton::clicked,
            this, &OfflinePageWidget::onContinue2ButtonClicked);
    connect(ui->continue2pButton, &QPushButton::clicked,
            this, &OfflinePageWidget::onContinue2PlusButtonClicked);

    connect(ui->fileSaveButton, &QPushButton::clicked,
            this, &OfflinePageWidget::onFileSavingButtonClicked);

    connect(ui->licenseWidget, &LicensePickingWidget::signalLicenseSelected,
            this, &OfflinePageWidget::onLicenseSelected);
    connect(ui->licenseWidget, &LicensePickingWidget::signalLicenseDeselected,
            this, &OfflinePageWidget::onLicenseDeselected);

    connect(ui->fileWidget, &FilePickingWidget::signalFileSelected,
            this, &OfflinePageWidget::onFileSelected);
}

OfflinePageWidget::~OfflinePageWidget()
{
    delete ui;
}

void OfflinePageWidget::retranslate()
{
    ui->retranslateUi(this);
    ui->fileWidget->retranslate();
    ui->licenseWidget->retranslate();
    setFileName();
}

void OfflinePageWidget::notifyDevicesChanged(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    ui->licenseWidget->notifyDevicesChanged(data);
    if (ui->updateButton->isChecked() &&
            !isLicenseIdValid(ui->licenseWidget->selectedLicenseId()))
        onLicenseDeselected();
}

void OfflinePageWidget::jumpUpdateOffline(const uint32_t licenseId)
{
    if (!ui->updateButton->isChecked())
        ui->updateButton->toggle();
    installStep2();
    ui->licenseWidget->selectLicense(licenseId);
}

void OfflinePageWidget::dropProgress()
{
    if (!ui->newButton->isChecked())
        ui->newButton->toggle();
    installStep2();
}

void OfflinePageWidget::dropVisibility()
{
    ui->step3BodyFrame->setVisible(false);
    ui->step3HeadFrame->setVisible(false);
    ui->continue2pButton->setVisible(false);
    ui->step2pBodyFrame->setVisible(false);
    ui->continue2Button->setVisible(false);
    ui->step2BodyFrame->setVisible(false);
    ui->step2HeadFrame->setVisible(false);
}

void OfflinePageWidget::onActionButtonToggled(const bool checked)
{
    if (checked)
        installStep2();
}

void OfflinePageWidget::onContinue2ButtonClicked()
{
    goStep2Plus();
}

void OfflinePageWidget::onContinue2PlusButtonClicked()
{
    goStep3();
}

void OfflinePageWidget::onLicenseSelected()
{
    goStep2LicenseSelected();
}

void OfflinePageWidget::onLicenseDeselected()
{
    goStep2();
}

void OfflinePageWidget::onFileSavingButtonClicked()
{
    if (ui->newButton->isChecked())
    {
        const QString requestPath = saveFile(
                    this, FileType::Request, ui->fileNameLabel->text());
        if (requestPath.isEmpty())
            return;

        emit signalLicenseCreateActivationRequest(requestPath);
    }
    else if (ui->updateButton->isChecked())
    {
        const QString requestPath = saveFile(
                    this, FileType::Request, ui->fileNameLabel->text());
        if (requestPath.isEmpty())
            return;

        const uint32_t licenseId = ui->licenseWidget->selectedLicenseId();
        if (!isLicenseIdValid(licenseId))
        {
            assert(false);
            return;
        }

        emit signalLicenseCreateUpdateRequest(requestPath, licenseId);
    }
    else if (ui->rehostButton->isChecked())
    {
        const QString fingerprintPath = saveFile(
                    this, FileType::Fingerprint, ui->fileNameLabel->text());
        if (fingerprintPath.isEmpty())
            return;

        emit signalLicenseGetFingerprint(fingerprintPath);
    }
    else
    {
        assert(false);
    }
}

void OfflinePageWidget::onFileSelected()
{
    const QString path = ui->fileWidget->selectedFilePath();
    const RecognizedFileType type = recognizeFile(path);
    switch (type)
    {
    case RecognizedFileType::ActivationResponse:
    case RecognizedFileType::UpdateResponse:
    case RecognizedFileType::RehostRecipientLicense:
        emit signalLicenseInstall(path);
        break;
    default:
        assert(false);
        ui->fileWidget->notifyError();
        break;
    }
}

void OfflinePageWidget::installStep2()
{
    ui->fileWidget->dropProgress();
    ui->licenseWidget->dropProgress();
    goStep2();
}

void OfflinePageWidget::goStep2()
{
    // Step 2 can be proceeded or returned to from any point
    // Step 2 can lead to step 2 with license selected (when update button is
    //   toggled only) or to step 2 plus (when either new button or trasfer
    //   button is toggled only)
    // Make sure that by the moment this function is called, the following
    //   conditions are met:
    // - new button is already set toggled, if needed
    // - license picking widget progress is dropped
    // - file picking widget progress is dropped

    const bool isUpdate = ui->updateButton->isChecked();

    ui->step2HeadFrame->setVisible(true);
    ui->step2BodyFrame->setVisible(true);
    ui->continue2Button->setVisible(!isUpdate);
    ui->step2pBodyFrame->setVisible(false);
    ui->continue2pButton->setVisible(false);
    ui->step3HeadFrame->setVisible(false);
    ui->step3BodyFrame->setVisible(false);

    ui->licenseWidget->setVisible(isUpdate);
    ui->step2InstructionFrame->setVisible(!isUpdate);
    ui->step2InstructionRequestLabel->setVisible(
                ui->newButton->isChecked() || ui->updateButton->isChecked());
    ui->step2InstructionRehostLabel->setVisible(
                ui->rehostButton->isChecked());
    ui->fileFrame->setVisible(!isUpdate);
    setFileName();
}

void OfflinePageWidget::goStep2LicenseSelected()
{
    // Step 2 with license selected can be procceded to from step 2 (when
    //   update button is toggled only) only and cannot be returned to
    // Step 2 can lead to step 2 plus only

    if (ui->updateButton->isChecked())
    {
        ui->continue2Button->setVisible(true);

        ui->step2InstructionFrame->setVisible(true);
        ui->fileFrame->setVisible(true);
        setFileName();
    }
    else
    {
        assert(false);
    }
}

void OfflinePageWidget::goStep2Plus()
{
    // Step 2 plus can be procceded to from step 2 or step 2 with license
    //   selected only and cannot be returned to
    // Step 2 plus can lead to step 3 only

    ui->continue2Button->setVisible(false);
    ui->step2pBodyFrame->setVisible(true);
    ui->step2pInstructionActivationLabel->setVisible(
                ui->newButton->isChecked());
    ui->step2pInstructionUpdateLabel->setVisible(
                ui->updateButton->isChecked());
    ui->step2pInstructionRehostLabel->setVisible(
                ui->rehostButton->isChecked());
    ui->continue2pButton->setVisible(true);
}

void OfflinePageWidget::goStep3()
{
    // Step 3 can be procceded to from step 2 plus only and cannot be returned
    //   to
    // Step 3 cannot lead anywhere

    ui->continue2pButton->setVisible(false);
    ui->step3HeadFrame->setVisible(true);
    ui->step3BodyFrame->setVisible(true);
}

void OfflinePageWidget::setFileName()
{
    if (ui->newButton->isChecked())
        ui->fileNameLabel->setText(buildActivationRequestFileName());
    else if (ui->updateButton->isChecked())
        ui->fileNameLabel->setText(
                    buildUpdateRequestFileName(
                        ui->licenseWidget->selectedLicenseId(),
                        ui->licenseWidget->selectedDongleType()));
    else if (ui->rehostButton->isChecked())
        ui->fileNameLabel->setText(buildFingerprintFileName());
}
