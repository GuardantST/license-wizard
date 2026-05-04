#include "RemotePageWidget.h"
#include "ui_RemotePageWidget.h"
#include "Recognition.h"
#include "Naming.h"
#include <cassert>

RemotePageWidget::RemotePageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::RemotePageWidget)
{
    ui->setupUi(this);

    ui->step2NumberLabel->setObjectName(QStringLiteral("GLabelStepNumber"));
    ui->step2HeadLabel->setObjectName(QStringLiteral("GLabelStepHeader"));
    ui->step2BodyFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->step2InstructionLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->step2ResultLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->continue2Button->setObjectName(QStringLiteral("GButton"));
    ui->step3NumberLabel->setObjectName(QStringLiteral("GLabelStepNumber"));
    ui->step3HeadLabel->setObjectName(QStringLiteral("GLabelStepHeader"));
    ui->step3BodyFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->clearButton->setObjectName(QStringLiteral("GButtonCross"));
    ui->separatorLine->setObjectName(QStringLiteral("GLine"));
    ui->continue3aButton->setObjectName(QStringLiteral("GButton"));
    ui->continue3uButton->setObjectName(QStringLiteral("GButton"));
    ui->continue3rButton->setObjectName(QStringLiteral("GButton"));
    ui->step4NumberLabel->setObjectName(QStringLiteral("GLabelStepNumber"));
    ui->step4HeadLabel->setObjectName(QStringLiteral("GLabelStepHeader"));
    ui->step4BodyFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->step4InstructionLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->step4ResultLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->fileFrame->setObjectName(QStringLiteral("GFrameFileSaveLicense"));
    ui->fileIconLabel->setObjectName(QStringLiteral("GLabelFileIconLicense"));
    ui->fileNameLabel->setObjectName(QStringLiteral("GLabelFileName"));
    ui->fileSaveButton->setObjectName(QStringLiteral("GButtonFileSave"));

    ui->serialLine->setInputMask("NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN");
    ui->serialLine->setPlaceholderText("Serial number");
    ui->serialLine->installEventFilter(this);
    ui->mainFileWidget->installForRequestAndRehostFiles();
    ui->auxFileWidget->installForFingerprintFiles();

    connect(ui->continue2Button, &QPushButton::clicked,
            this, &RemotePageWidget::onContinue2ButtonClicked);
    connect(ui->continue3aButton, &QPushButton::clicked,
            this, &RemotePageWidget::onContinue3AnyButtonClicked);
    connect(ui->continue3uButton, &QPushButton::clicked,
            this, &RemotePageWidget::onContinue3AnyButtonClicked);
    connect(ui->continue3rButton, &QPushButton::clicked,
            this, &RemotePageWidget::onContinue3AnyButtonClicked);

    connect(ui->mainFileWidget, &FilePickingWidget::signalFileSelected,
            this, &RemotePageWidget::onMainFileSelectedOrReselected);
    connect(ui->mainFileWidget, &FilePickingWidget::signalFileDeselected,
            this, &RemotePageWidget::onMainFileDeselected);
    connect(ui->auxFileWidget, &FilePickingWidget::signalFileSelected,
            this, &RemotePageWidget::onAuxFileSelectedOrReselected);
    connect(ui->auxFileWidget, &FilePickingWidget::signalFileDeselected,
            this, &RemotePageWidget::onAuxFileDeselected);

    connect(ui->serialLine, &QLineEdit::textChanged,
            this, &RemotePageWidget::onSerialLineTextChanged);
    connect(ui->clearButton, &QPushButton::clicked,
            ui->serialLine, &QLineEdit::clear);

    connect(ui->fileSaveButton, &QPushButton::clicked,
            this, &RemotePageWidget::onFileSavingButtonClicked);
}

RemotePageWidget::~RemotePageWidget()
{
    delete ui;
}

void RemotePageWidget::retranslate()
{
    const QString fileNameText = ui->fileNameLabel->text();
    ui->retranslateUi(this);
    ui->mainFileWidget->retranslate();
    ui->auxFileWidget->retranslate();
    ui->fileNameLabel->setText(fileNameText);
}

void RemotePageWidget::notifyResponseObtained(const QByteArray& responseBytes)
{
    m_responseBytes = responseBytes;
    goStep4();
}

void RemotePageWidget::notifyResponseObtainmentError()
{
    m_responseBytes.clear();
}

void RemotePageWidget::dropProgress()
{
    m_responseBytes.clear();
    installStep2();
}

void RemotePageWidget::dropVisibility()
{
    ui->step4BodyFrame->setVisible(false);
    ui->step4HeadFrame->setVisible(false);
    ui->step3BodyFrame->setVisible(false);
    ui->step3HeadFrame->setVisible(false);
    ui->continue2Button->setVisible(false);
    ui->step2BodyFrame->setVisible(false);
    ui->step2HeadFrame->setVisible(false);
}

bool RemotePageWidget::eventFilter(QObject* watched, QEvent* event)
{
    // Set cursor to the beginning
    if (watched == ui->serialLine)
    {
        if (event->type() == QEvent::MouseButtonPress ||
                event->type() == QEvent::MouseButtonDblClick)
        {
            ui->serialLine->setCursorPosition(0);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void RemotePageWidget::installStep2()
{
    ui->mainFileWidget->dropProgress();
    ui->auxFileWidget->dropProgress();
    ui->serialLine->clear();
    goStep2();
}

void RemotePageWidget::goStep2()
{
    // Step 2 can be proceeded or returned to from any point
    // Step 2 can lead to step 3 only
    // Make sure that by the moment this function is called, the following
    //   conditions are met:
    // - main file picking widget progress is dropped
    // - aux file picking widget progress is dropped
    // - serial line text is cleared

    ui->step2HeadFrame->setVisible(true);
    ui->step2BodyFrame->setVisible(true);
    ui->continue2Button->setVisible(true);
    ui->step3HeadFrame->setVisible(false);
    ui->step3BodyFrame->setVisible(false);
    ui->step4HeadFrame->setVisible(false);
    ui->step4BodyFrame->setVisible(false);
}

void RemotePageWidget::goStep3()
{
    // Step 3 can be proceeded to from step 2 only and returned to from any
    //   following step
    // Step 3 can lead to step 3 with activation request file selected, step 3
    //   with update request file selected, or step 3 with rehost file selected
    //   only
    // Make sure that by the moment this function is called, the following
    //   conditions are met:
    // - main file picking widget progress is dropped
    // - aux file picking widget progress is dropped
    // - serial line text is cleared

    ui->continue2Button->setVisible(false);
    ui->step3HeadFrame->setVisible(true);
    ui->step3BodyFrame->setVisible(true);
    ui->step4HeadFrame->setVisible(false);
    ui->step4BodyFrame->setVisible(false);

    ui->auxFileWidget->setVisible(false);
    ui->serialFrame->setVisible(false);
    ui->separatorLine->setVisible(false);
    ui->buttonFrame->setVisible(false);
}

void RemotePageWidget::goStep3ActivationRequestFileSelected()
{
    // Step 3 with activation request file selected can be proceeded to from
    //   step 3, can be jumped to from step 3 with update request file
    //   selected, step 3 with rehost file selected, or step 3 with fingerprint
    //   file selected only, and cannot be returned to
    // Step 3 with activation request file selected can lead to step 4 only
    // Make sure that by the moment this function is called, the following
    //   conditions are met:
    // - main file picking widget has some file picked
    // - aux file picking widget progress is dropped

    ui->auxFileWidget->dropProgress();
    ui->serialLine->clear();

    ui->step4HeadFrame->setVisible(false);
    ui->step4BodyFrame->setVisible(false);

    ui->auxFileWidget->setVisible(false);
    ui->serialFrame->setVisible(true);
    ui->separatorLine->setVisible(true);
    ui->buttonFrame->setVisible(true);

    ui->continue3aButton->setVisible(true);
    ui->continue3uButton->setVisible(false);
    ui->continue3rButton->setVisible(false);
}

void RemotePageWidget::goStep3UpdateRequestFileSelected()
{
    // Step 3 with update request file selected can be proceeded to from step
    //   3, can be jumped to from step 3 with activation request file
    //   selected, step 3 with rehost file selected, or step 3 with fingerprint
    //   file selected only, and cannot be returned to
    // Step 3 with update request file selected can lead to step 4 only
    // Make sure that by the moment this function is called, the following
    //   conditions are met:
    // - main file picking widget has some file picked
    // - aux file picking widget progress is dropped

    ui->auxFileWidget->dropProgress();
    ui->serialLine->clear();

    ui->step4HeadFrame->setVisible(false);
    ui->step4BodyFrame->setVisible(false);

    ui->auxFileWidget->setVisible(false);
    ui->serialFrame->setVisible(false);
    ui->separatorLine->setVisible(true);
    ui->buttonFrame->setVisible(true);

    ui->continue3aButton->setVisible(false);
    ui->continue3uButton->setVisible(true);
    ui->continue3rButton->setVisible(false);
}

void RemotePageWidget::goStep3RehostFileSelected()
{
    // Step 3 with rehost file selected can be proceeded to from step 3 only,
    //   can be jumped to from step 3 with activation request file selected,
    //   step 3 with update file selected, and can be returned to from step 3
    //   with fingerprint file selected or step 4 only
    // Step 3 with rehost file selected can lead to step 3 with fingerprint
    //   file selected only
    // Make sure that by the moment this function is called, the following
    //   conditions are met:
    // - main file picking widget has some file picked
    // - aux file picking widget progress is dropped

    ui->serialLine->clear();

    ui->step4HeadFrame->setVisible(false);
    ui->step4BodyFrame->setVisible(false);

    ui->auxFileWidget->setVisible(true);
    ui->serialFrame->setVisible(false);
    ui->separatorLine->setVisible(false);
    ui->buttonFrame->setVisible(false);
}

void RemotePageWidget::goStep3FingerprintFileSelected()
{
    // Step 3 with fingerprint file selected can be proceeded to from step 3
    //   with rehost file selected only and can be returned to from step 4
    // Step 3 with fingerprint file selected can lead to step 4 only
    // Make sure that by the moment this function is called, the following
    //   conditions are met:
    // - main file picking widget has some file picked
    // - aux file picking widget has some file picked

    ui->step4HeadFrame->setVisible(false);
    ui->step4BodyFrame->setVisible(false);

    ui->separatorLine->setVisible(true);
    ui->buttonFrame->setVisible(true);

    ui->continue3aButton->setVisible(false);
    ui->continue3uButton->setVisible(false);
    ui->continue3rButton->setVisible(true);
}

void RemotePageWidget::goStep4()
{
    // Step 4 can be procceded to from step 3 with activation request file
    //   selected, step 3 with update request file selected, or step 3 with
    //   fingerprint file selected only and cannot be returned to
    // Step 4 cannot lead anywhere
    // Make sure that by the moment this function is called, the following
    //   conditions are met:
    // - main file picking widget has some file picked
    // - aux file picking widget has some file picked

    // Here it must go first, because continue 3 activation, update and rehost
    //   buttons are checked for being visible first
    if (ui->continue3aButton->isVisible() || ui->continue3uButton->isVisible())
        ui->fileNameLabel->setText(
                    buildResponseFileName(
                        ui->mainFileWidget->selectedFilePath()));
    else if (ui->continue3rButton->isVisible())
        ui->fileNameLabel->setText(
                    buildRehostResponseFileName(
                        ui->mainFileWidget->selectedFilePath(),
                        ui->auxFileWidget->selectedFilePath()));
    else
        assert(false);

    ui->step4HeadFrame->setVisible(true);
    ui->step4BodyFrame->setVisible(true);

    ui->separatorLine->setVisible(false);
    ui->buttonFrame->setVisible(false);
}

void RemotePageWidget::onContinue2ButtonClicked()
{
    goStep3();
}

void RemotePageWidget::onMainFileSelectedOrReselected()
{
    const QString path = ui->mainFileWidget->selectedFilePath();
    const RecognizedFileType type = recognizeFile(path);
    switch (type)
    {
    case RecognizedFileType::ActivationRequest:
        goStep3ActivationRequestFileSelected();
        break;
    case RecognizedFileType::UpdateRequest:
        goStep3UpdateRequestFileSelected();
        break;
    case RecognizedFileType::RehostDonorLicense:
        ui->auxFileWidget->dropProgress();
        goStep3RehostFileSelected();
        break;
    default:
        assert(false);
        ui->mainFileWidget->notifyError();
        break;
    }
}

void RemotePageWidget::onMainFileDeselected()
{
    goStep3();
}

void RemotePageWidget::onAuxFileSelectedOrReselected()
{
    const QString path = ui->auxFileWidget->selectedFilePath();
    const RecognizedFileType type = recognizeFile(path);
    switch (type)
    {
    case RecognizedFileType::RehostFingerprint:
        break;
    default:
        assert(false);
        ui->auxFileWidget->notifyError();
        return;
    }

    goStep3FingerprintFileSelected();
}

void RemotePageWidget::onAuxFileDeselected()
{
    goStep3RehostFileSelected();
}

void RemotePageWidget::onContinue3AnyButtonClicked()
{
    if (ui->continue3aButton->isVisible())
        emit signalLicenseSendActivationRequest(
                ui->mainFileWidget->selectedFilePath(),
                ui->serialLine->text());
    else if (ui->continue3uButton->isVisible())
        emit signalLicenseSendUpdateRequest(
                ui->mainFileWidget->selectedFilePath());
    else if (ui->continue3rButton->isVisible())
        emit signalLicenseSendRehostRequest(
                ui->mainFileWidget->selectedFilePath(),
                ui->auxFileWidget->selectedFilePath());
    else
        assert(false);
}

void RemotePageWidget::onSerialLineTextChanged(const QString& text)
{
    Q_UNUSED(text);
    ui->continue3aButton->setEnabled(
                ui->serialLine->text().size() ==
                ui->serialLine->inputMask().size());
}

void RemotePageWidget::onFileSavingButtonClicked()
{
    const QString licensePath = saveFile(
                this, FileType::License, ui->fileNameLabel->text());
    if (licensePath.isEmpty())
        return;

    if (m_responseBytes.isEmpty())
    {
        assert(false);
        return;
    }

    emit signalWriteLicenseResponseFile(licensePath, m_responseBytes);
}
