#include "OnlinePageWidget.h"
#include "ui_OnlinePageWidget.h"
#include "Recognition.h"

OnlinePageWidget::OnlinePageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::OnlinePageWidget)
{
    ui->setupUi(this);

    ui->step2NumberLabel->setObjectName(QStringLiteral("GLabelStepNumber"));
    ui->serialButton->setObjectName(QStringLiteral("GButtonToggleableLeft"));
    ui->fileButton->setObjectName(QStringLiteral("GButtonToggleableRight"));
    ui->offlineButton->setObjectName(QStringLiteral("GButtonOfflineActivate"));
    ui->step2BodyFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->getButton->setObjectName(QStringLiteral("GButton"));
    ui->clearButton->setObjectName(QStringLiteral("GButtonCross"));

    ui->serialLine->setInputMask("NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN");
    ui->serialLine->setPlaceholderText("Serial number");
    ui->serialLine->installEventFilter(this);
    ui->fileWidget->installForLicenseAndRehostFiles();

    connect(ui->offlineButton, &QPushButton::clicked,
            this, &OnlinePageWidget::signalGoOffline);

    connect(ui->serialButton, &QPushButton::toggled,
            this, &OnlinePageWidget::onActionButtonToggled);
    connect(ui->fileButton, &QPushButton::toggled,
            this, &OnlinePageWidget::onActionButtonToggled);

    connect(ui->serialLine, &QLineEdit::textChanged,
            this, &OnlinePageWidget::onSerialLineTextChanged);
    connect(ui->clearButton, &QPushButton::clicked,
            ui->serialLine, &QLineEdit::clear);

    connect(ui->getButton, &QPushButton::clicked,
            this, &OnlinePageWidget::onGetButtonClicked);
    connect(ui->fileWidget, &FilePickingWidget::signalFileSelected,
            this, &OnlinePageWidget::onFileSelected);
}

OnlinePageWidget::~OnlinePageWidget()
{
    delete ui;
}

void OnlinePageWidget::retranslate()
{
    ui->retranslateUi(this);
    ui->fileWidget->retranslate();
}

void OnlinePageWidget::dropProgress()
{
    if (!ui->serialButton->isChecked())
        ui->serialButton->toggle();
    installStep2();
}

void OnlinePageWidget::dropVisibility()
{
    ui->step2BodyFrame->setVisible(false);
    ui->step2HeadFrame->setVisible(false);
}

bool OnlinePageWidget::eventFilter(QObject* watched, QEvent* event)
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

void OnlinePageWidget::installStep2()
{
    ui->serialLine->clear();
    ui->fileWidget->dropProgress();
    goStep2();
    ui->serialLine->setFocus();
}

void OnlinePageWidget::goStep2()
{
    const bool isSerial = ui->serialButton->isChecked();

    ui->step2HeadFrame->setVisible(true);
    ui->step2BodyFrame->setVisible(true);

    ui->serialFrame->setVisible(isSerial);
    ui->getButton->setVisible(isSerial);
    ui->fileWidget->setVisible(!isSerial);
}

void OnlinePageWidget::onActionButtonToggled(const bool checked)
{
    if (checked)
        installStep2();
}

void OnlinePageWidget::onSerialLineTextChanged(const QString& text)
{
    Q_UNUSED(text);
    ui->getButton->setEnabled(
                ui->serialLine->text().size() ==
                ui->serialLine->inputMask().size());
}

void OnlinePageWidget::onGetButtonClicked()
{
    emit signalLicenseActivate(ui->serialLine->text());
}

void OnlinePageWidget::onFileSelected()
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
    case RecognizedFileType::RehostDonorLicense:
        emit signalLicenseRehost(path);
        break;
    default:
        ui->fileWidget->notifyError();
        break;
    }
}
