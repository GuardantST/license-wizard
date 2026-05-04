#include "WriteOncePageWidget.h"
#include "ui_WriteOncePageWidget.h"
#include "Recognition.h"
#include <cassert>

WriteOncePageWidget::WriteOncePageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::WriteOncePageWidget),
    m_dongleId(InvalidLicenseId),
    m_dongleType(DongleType::Unknown)
{
    ui->setupUi(this);

    ui->backButton->setObjectName(QStringLiteral("GButtonBack"));
    ui->headerLabel->setObjectName(QStringLiteral("GLabelMainHeader"));
    ui->tipLabel->setObjectName(QStringLiteral("GLabelMainTip"));
    ui->serialButton->setObjectName(QStringLiteral("GButtonToggleableLeft"));
    ui->fileButton->setObjectName(QStringLiteral("GButtonToggleableRight"));
    ui->prepareFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->clearButton->setObjectName(QStringLiteral("GButtonCross"));
    ui->separatorLine->setObjectName(QStringLiteral("GLine"));
    ui->writeButton->setObjectName(QStringLiteral("GButton"));

    ui->backButton->adjustSize();
    ui->serialLine->setInputMask("NNNNNN-NNNNNN-NNNNNN-NNNNNN-NNNNNN");
    ui->serialLine->setPlaceholderText("Serial number");
    ui->serialLine->installEventFilter(this);
    ui->fileWidget->installForCodeFiles();

    connect(ui->backButton, &QPushButton::clicked,
            this, &WriteOncePageWidget::signalGoList);
    connect(ui->serialButton, &QPushButton::toggled,
            this, &WriteOncePageWidget::onActionButtonToggled);
    connect(ui->fileButton, &QPushButton::toggled,
            this, &WriteOncePageWidget::onActionButtonToggled);
    connect(ui->serialLine, &QLineEdit::textChanged,
            this, &WriteOncePageWidget::onSerialLineTextChanged);
    connect(ui->clearButton, &QPushButton::clicked,
            ui->serialLine, &QLineEdit::clear);
    connect(ui->fileWidget, &FilePickingWidget::signalFileSelected,
            this, &WriteOncePageWidget::onFileSelected);
    connect(ui->fileWidget, &FilePickingWidget::signalFileDeselected,
            this, &WriteOncePageWidget::onFileUnselected);
    connect(ui->writeButton, &QPushButton::clicked,
            this, &WriteOncePageWidget::onWriteButtonClicked);

    goPrepare();
    goPrepareSerial();
}

WriteOncePageWidget::~WriteOncePageWidget()
{
    delete ui;
}

bool WriteOncePageWidget::eventFilter(QObject* watched, QEvent* event)
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

void WriteOncePageWidget::retranslate()
{
    ui->retranslateUi(this);

    ui->backButton->adjustSize();

    ui->fileWidget->retranslate();

    updateHeaderText();
}

void WriteOncePageWidget::notifyDongleLicenseSet()
{
    // Nothing
}

void WriteOncePageWidget::notifyDongleLicenseSettingError()
{
    // Nothing
}

void WriteOncePageWidget::setDongle(
        const uint32_t dongleId, const DongleType dongleType)
{
    dropProgress();
    assert(isLicenseIdValid(dongleId));
    assert(dongleType == DongleType::Sign ||
           dongleType == DongleType::SignNet ||
           dongleType == DongleType::Time ||
           dongleType == DongleType::TimeNet);
    m_dongleId = dongleId;
    m_dongleType = dongleType;
    updateHeaderText();
}

void WriteOncePageWidget::dropProgress()
{
    m_serialNumbers.clear();
    ui->serialLine->clear();
    ui->fileWidget->dropProgress();
    goPrepare();
    if (!ui->serialButton->isChecked())
        ui->serialButton->toggle();
}

void WriteOncePageWidget::goPrepare()
{
    ui->writeButton->setEnabled(false);
}

void WriteOncePageWidget::goPrepareSerial()
{
    ui->fileWidget->hide();
    ui->separatorLine->hide();
    ui->writeFrame->show();
    ui->serialFrame->show();
}

void WriteOncePageWidget::goPrepareFile()
{
    ui->separatorLine->hide();
    ui->writeFrame->hide();
    ui->serialFrame->hide();
    ui->fileWidget->show();
}

void WriteOncePageWidget::updateHeaderText()
{
    ui->headerLabel->setText(
                tr("Write a license to the Guardant %1 key #%2").
                arg(dongleTypeStr(m_dongleType)).
                arg(dongleIdStr(m_dongleId)));
}

void WriteOncePageWidget::onActionButtonToggled(const bool checked)
{
    Q_UNUSED(checked);
    if (ui->serialButton->isChecked())
    {
        m_serialNumbers.clear();
        ui->serialLine->clear();
        goPrepareSerial();
    }
    else if (ui->fileButton->isChecked())
    {
        m_serialNumbers.clear();
        ui->fileWidget->dropProgress();
        goPrepareFile();
    }
}

void WriteOncePageWidget::onSerialLineTextChanged(const QString& text)
{
    Q_UNUSED(text);
    if (ui->prepareFrame->isVisible() &&
            ui->serialButton->isChecked())
        ui->writeButton->setEnabled(
                    ui->serialLine->text().size() ==
                    ui->serialLine->inputMask().size());
}

void WriteOncePageWidget::onWriteButtonClicked()
{
    QStringList serialNumbers;
    if (ui->serialFrame->isVisible())
        serialNumbers << ui->serialLine->text();
    else if (ui->fileWidget->isVisible())
        serialNumbers = m_serialNumbers;

    emit signalWriteDongle(m_dongleId, serialNumbers);
}

void WriteOncePageWidget::onFileSelected()
{
    const QString path = ui->fileWidget->selectedFilePath();
    const RecognizedFileType type = recognizeFile(path, &m_serialNumbers);
    switch (type)
    {
    case RecognizedFileType::Codes:
        assert(m_serialNumbers.count() > 0);
        ui->fileWidget->notifyCodesCount(m_serialNumbers.count());
        ui->separatorLine->show();
        ui->writeFrame->show();
        ui->writeButton->setEnabled(true);
        break;
    default:
        m_serialNumbers.clear();
        ui->fileWidget->notifyError();
        ui->separatorLine->hide();
        ui->writeFrame->hide();
        break;
    }
}

void WriteOncePageWidget::onFileUnselected()
{
    m_serialNumbers.clear();
    ui->fileWidget->dropProgress();
    goPrepareFile();
}
