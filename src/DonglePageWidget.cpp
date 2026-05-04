#include "DonglePageWidget.h"
#include "ui_DonglePageWidget.h"
#include "Recognition.h"
#include <cassert>

DonglePageWidget::DonglePageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DonglePageWidget)
{
    ui->setupUi(this);

    ui->step2NumberLabel->setObjectName(QStringLiteral("GLabelStepNumber"));
    ui->serialButton->setObjectName(QStringLiteral("GButtonToggleableLeft"));
    ui->fileButton->setObjectName(QStringLiteral("GButtonToggleableRight"));
    ui->step2BodyFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->continueButton->setObjectName(QStringLiteral("GButton"));
    ui->clearButton->setObjectName(QStringLiteral("GButtonCross"));

    ui->serialLine->setInputMask("NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN");
    ui->serialLine->setPlaceholderText("Serial number");
    ui->serialLine->installEventFilter(this);
    ui->fileWidget->installForCodeFiles();

    connect(ui->serialButton, &QPushButton::toggled,
            this, &DonglePageWidget::onActionButtonToggled);
    connect(ui->fileButton, &QPushButton::toggled,
            this, &DonglePageWidget::onActionButtonToggled);

    connect(ui->serialLine, &QLineEdit::textChanged,
            this, &DonglePageWidget::onSerialLineTextChanged);
    connect(ui->clearButton, &QPushButton::clicked,
            ui->serialLine, &QLineEdit::clear);

    connect(ui->continueButton, &QPushButton::clicked,
            this, &DonglePageWidget::onContinueButtonClicked);
    connect(ui->fileWidget, &FilePickingWidget::signalFileSelected,
            this, &DonglePageWidget::onFileSelected);
}

DonglePageWidget::~DonglePageWidget()
{
    delete ui;
}

void DonglePageWidget::retranslate()
{
    ui->retranslateUi(this);
    ui->fileWidget->retranslate();
}

void DonglePageWidget::dropProgress()
{
    if (!ui->serialButton->isChecked())
        ui->serialButton->toggle();
    installStep2();
}

void DonglePageWidget::dropVisibility()
{
    ui->step2BodyFrame->setVisible(false);
    ui->step2HeadFrame->setVisible(false);
}

bool DonglePageWidget::eventFilter(QObject* watched, QEvent* event)
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

void DonglePageWidget::installStep2()
{
    ui->serialLine->clear();
    ui->fileWidget->dropProgress();
    goStep2();
    ui->serialLine->setFocus();
}

void DonglePageWidget::goStep2()
{
    const bool isSerial = ui->serialButton->isChecked();

    ui->step2HeadFrame->setVisible(true);
    ui->step2BodyFrame->setVisible(true);

    ui->serialFrame->setVisible(isSerial);
    ui->continueButton->setVisible(isSerial);
    ui->fileWidget->setVisible(!isSerial);
}

void DonglePageWidget::onActionButtonToggled(const bool checked)
{
    if (checked)
        installStep2();
}

void DonglePageWidget::onSerialLineTextChanged(const QString& text)
{
    Q_UNUSED(text);
    ui->continueButton->setEnabled(
                ui->serialLine->text().size() ==
                ui->serialLine->inputMask().size());
}

void DonglePageWidget::onContinueButtonClicked()
{
    emit signalGoWrite(QStringList() << ui->serialLine->text());
}

void DonglePageWidget::onFileSelected()
{
    const QString path = ui->fileWidget->selectedFilePath();
    QStringList strings;
    const RecognizedFileType type = recognizeFile(path, &strings);
    switch (type)
    {
    case RecognizedFileType::Codes:
        assert(!strings.isEmpty());
        emit signalGoWrite(strings);
        break;
    default:
        ui->fileWidget->notifyError();
        break;
    }
}
