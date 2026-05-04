#include "WriteSomePageWidget.h"
#include "ui_WriteSomePageWidget.h"
#include <cassert>

// Note that a QTreeWidget has the capability to place check boxes for it's
//   items, but the workaround seems to be unfinished, since one cannot simply
//   check and uncheck the items, and even more, there is no capability to
//   process checking automatically (e.g. when a child item is checked or
//   unchecked, a parent item is to be unchecked or partially checked as well),
//   so it is much simpler to place a check box manually and process checking
//   manually in a separate function

WriteSomePageWidget::WriteSomePageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::WriteSomePageWidget)
{
    ui->setupUi(this);

    ui->backButton->setObjectName(QStringLiteral("GButtonBack"));
    ui->headerLabel->setObjectName(QStringLiteral("GLabelMainHeader"));
    ui->tipLabel->setObjectName(QStringLiteral("GLabelMainTip"));
    ui->insertLabel->setObjectName(QStringLiteral("GLabelPromptText"));
    ui->refreshButton->setObjectName(QStringLiteral("GButtonRefreshSmaller"));
    ui->treeWidget->setObjectName(QStringLiteral("GListDongle"));

    ui->backButton->adjustSize();
    ui->treeWidget->setColumnWidth(0, 40);
    ui->treeWidget->setColumnWidth(1, 180);
    ui->treeWidget->setColumnWidth(2, 240);
    ui->treeWidget->setColumnWidth(3, 110);
    ui->treeWidget->setColumnWidth(4, 55);
    ui->treeWidget->header()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->stackedWidget->setCurrentWidget(ui->blankPage);

    connect(ui->backButton, &QPushButton::clicked,
            this, &WriteSomePageWidget::signalGoList);
}

WriteSomePageWidget::~WriteSomePageWidget()
{
    delete ui;
}

void WriteSomePageWidget::retranslate()
{
    ui->retranslateUi(this);

    ui->backButton->adjustSize();

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);
        if (item == nullptr)
        {
            assert(false);
            continue;
        }

        QWidget* widget = ui->treeWidget->itemWidget(item, 3);
        if (widget == nullptr)
        {
            assert(false);
            continue;
        }

        QFrame* frame = qobject_cast<QFrame*>(widget);
        if (frame == nullptr)
        {
            assert(false);
            continue;
        }

        QLayout* layout = frame->layout();
        if (layout == nullptr)
        {
            assert(false);
            continue;
        }

        QLayoutItem* layoutItem = layout->itemAt(0);
        if (layoutItem == nullptr)
        {
            assert(false);
            continue;
        }

        widget = layoutItem->widget();
        if (widget == nullptr)
        {
            assert(false);
            continue;
        }

        QPushButton* writeButton = qobject_cast<QPushButton*>(widget);
        if (writeButton == nullptr)
        {
            assert(false);
            continue;
        }

        updateWriteOnceButtonText(writeButton);
    }
}

void WriteSomePageWidget::setSerialNumbers(const QStringList& serialNumbers)
{
    m_serialNumbers = serialNumbers;
}

void WriteSomePageWidget::notifyDevicesChanged(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    setEnabled(false);

    using LicenseInfo = DeviceChecker::LicenseInfo;

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); )
    {
        QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);
        const uint32_t itemDongleId = getDongleId(item);
        if (!isLicenseIdValid(itemDongleId))
        {
            assert(false);
            continue;
        }

        bool found = false;
        for (int j = 0; j < data->size(); ++j)
        {
            const LicenseInfo& licenseInfo = data->at(j);
            if (licenseInfo.id == itemDongleId)
            {
                found = true;
                break;
            }
        }
        if (!found)
            delete ui->treeWidget->takeTopLevelItem(i);
        else
            ++i;
    }

    for (int i = 0; i < data->size(); ++i)
    {
        const LicenseInfo& licenseInfo = data->at(i);
        const bool isMaster = licenseInfo.isMaster;
        if (isMaster)
            continue;

        const uint32_t infoDongleId = licenseInfo.id;
        bool found = false;
        for (int j = 0; j < ui->treeWidget->topLevelItemCount(); ++j)
        {
            QTreeWidgetItem* item = ui->treeWidget->topLevelItem(j);
            const uint32_t itemDongleId = getDongleId(item);
            if (!isLicenseIdValid(itemDongleId))
            {
                assert(false);
                continue;
            }

            if (itemDongleId == infoDongleId)
            {
                found = true;
                break;
            }
        }
        if (found)
            continue;

        if (!dongleVsLicense(licenseInfo.dongleType))
            continue;

        addDongle(licenseInfo.id, licenseInfo.dongleType);
    }

    // No sorting is applied, so that this list of dongles would be ordered
    //   like the main list of licenses is, but with the dongle filter applied

    if (ui->treeWidget->topLevelItemCount() > 0)
        ui->stackedWidget->setCurrentWidget(ui->listPage);
    else
        ui->stackedWidget->setCurrentWidget(ui->blankPage);

    setEnabled(true);
}

void WriteSomePageWidget::notifyDongleLicenseSet()
{
    // Nothing
}

void WriteSomePageWidget::notifyDongleLicenseSettingError()
{
    // Nothing
}

inline static void setTypeIcon(QLabel* typeIcon, const DongleType type)
{
    switch (type)
    {
    case DongleType::Sign:
    case DongleType::SignNet:
        typeIcon->setObjectName(QStringLiteral("GLabelLicenseItemTypeSign"));
        break;
    case DongleType::Time:
    case DongleType::TimeNet:
        typeIcon->setObjectName(QStringLiteral("GLabelLicenseItemTypeTime"));
        break;
    case DongleType::Code:
    case DongleType::CodeNet:
    case DongleType::CodeTime:
    case DongleType::CodeTimeNet:
        typeIcon->setObjectName(QStringLiteral("GLabelLicenseItemTypeCode"));
        break;
    case DongleType::Dl:
    case DongleType::DlNet:
    case DongleType::Unknown:
    default:
        assert(false);
        typeIcon->setObjectName(QStringLiteral("GLabelLicenseItemTypeDl"));
        break;
    }
}

inline static void setTypeText(QLabel* typeLabel, const DongleType type)
{
    QString text = dongleTypeStr(type);
    if (!text.isEmpty())
        text = "Guardant " + text;
    typeLabel->setText(text);
}

void WriteSomePageWidget::addDongle(
        const uint32_t dongleId, const DongleType dongleType)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setData(0, LicenseIdRole, dongleId);
    item->setData(0, DongleTypeRole, static_cast<int>(dongleType));
    ui->treeWidget->addTopLevelItem(item);

    QLabel* typeIcon = new QLabel();
    typeIcon->style()->unpolish(typeIcon);
    setTypeIcon(typeIcon, dongleType);
    typeIcon->style()->polish(typeIcon);
    ui->treeWidget->setItemWidget(item, 0, typeIcon);

    QLabel* typeLabel = new QLabel();
    setTypeText(typeLabel, dongleType);
    typeLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->treeWidget->setItemWidget(item, 1, typeLabel);

    QLabel* idLabel = new QLabel(dongleIdStr(dongleId));
    idLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->treeWidget->setItemWidget(item, 2, idLabel);

    QPushButton* writeButton = new QPushButton();
    updateWriteOnceButtonText(writeButton);
    writeButton->setObjectName(QStringLiteral("GButtonWrite"));
    writeButton->setMinimumWidth(100);
    writeButton->setMaximumWidth(100);
    writeButton->setMinimumHeight(30);
    writeButton->setMaximumHeight(30);
    connect(writeButton, &QPushButton::clicked,
            this, &WriteSomePageWidget::onDongleWriteButtonClicked);
    QGridLayout* writeLayout = new QGridLayout();
    writeLayout->setSpacing(0);
    writeLayout->setContentsMargins(0, 0, 0, 0);
    writeLayout->addWidget(writeButton);
    QFrame* writeFrame = new QFrame();
    writeFrame->setLayout(writeLayout);
    ui->treeWidget->setItemWidget(item, 3, writeFrame);

    QPushButton* blinkButton = new QPushButton();
    blinkButton->setObjectName(QStringLiteral("GButtonBlink"));
    blinkButton->setMinimumWidth(45);
    blinkButton->setMaximumWidth(45);
    blinkButton->setMinimumHeight(30);
    blinkButton->setMaximumHeight(30);
    connect(blinkButton, &QPushButton::clicked,
            this, &WriteSomePageWidget::onDongleBlinkButtonClicked);
    QGridLayout* blinkLayout = new QGridLayout();
    blinkLayout->setSpacing(0);
    blinkLayout->setContentsMargins(0, 0, 0, 0);
    blinkLayout->addWidget(blinkButton);
    QFrame* blinkFrame = new QFrame();
    blinkFrame->setLayout(blinkLayout);
    ui->treeWidget->setItemWidget(item, 4, blinkFrame);
}

uint32_t WriteSomePageWidget::getDongleId(QTreeWidgetItem* item) const
{
    uint32_t dongleId = InvalidLicenseId;
    QVariant variant = item->data(0, LicenseIdRole);
    if (!variant.isValid())
    {
        assert(false);
        return InvalidLicenseId;
    }

    bool ok = false;
    dongleId = variant.toUInt(&ok);
    if (!ok || !isLicenseIdValid(dongleId))
    {
        assert(false);
        return InvalidLicenseId;
    }

    return dongleId;
}

template<typename TQWidget>
static TQWidget* toWidget(QWidget* widget)
{
    if (widget == nullptr)
    {
        assert(false);
        return nullptr;
    }

    QLayout* layout = widget->layout();
    if (layout == nullptr)
    {
        assert(false);
        return nullptr;
    }

    QLayoutItem* layoutItem = layout->itemAt(0);
    if (layoutItem == nullptr)
    {
        assert(false);
        return nullptr;
    }

    widget = layoutItem->widget();
    if (widget == nullptr)
    {
        assert(false);
        return nullptr;
    }

    TQWidget* target = qobject_cast<TQWidget*>(widget);
    assert(target != nullptr);
    return target;
}

void WriteSomePageWidget::updateWriteOnceButtonText(QPushButton* writeButton)
{
    writeButton->setText(tr("Write"));
}

void WriteSomePageWidget::onDongleWriteButtonClicked()
{
    QObject* object = sender();
    if (object == nullptr)
    {
        assert(false);
        return;
    }

    QPushButton* senderWriteButton = qobject_cast<QPushButton*>(object);
    if (senderWriteButton == nullptr)
    {
        assert(false);
        return;
    }

    uint32_t dongleId = InvalidLicenseId;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);
        if (item == nullptr)
        {
            assert(false);
            continue;
        }

        QWidget* widget = ui->treeWidget->itemWidget(item, 3);
        QPushButton* writeButton = toWidget<QPushButton>(widget);
        if (writeButton == nullptr)
        {
            assert(false);
            continue;
        }

        if (writeButton != senderWriteButton)
            continue;

        dongleId = getDongleId(item);
        break;
    }

    if (!isLicenseIdValid(dongleId))
    {
        assert(false);
        return;
    }

    assert(!m_serialNumbers.isEmpty());

    emit signalWriteDongles(QVector<uint32_t>() << dongleId, m_serialNumbers);
}

void WriteSomePageWidget::onDongleBlinkButtonClicked()
{
    QObject* object = sender();
    if (object == nullptr)
    {
        assert(false);
        return;
    }

    QPushButton* senderBlinkButton = qobject_cast<QPushButton*>(object);
    if (senderBlinkButton == nullptr)
    {
        assert(false);
        return;
    }

    uint32_t dongleId = InvalidLicenseId;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);
        if (item == nullptr)
        {
            assert(false);
            continue;
        }

        QWidget* widget = ui->treeWidget->itemWidget(item, 4);
        QPushButton* blinkButton = toWidget<QPushButton>(widget);
        if (blinkButton == nullptr)
        {
            assert(false);
            continue;
        }

        if (blinkButton != senderBlinkButton)
            continue;

        dongleId = getDongleId(item);
        break;
    }

    if (!isLicenseIdValid(dongleId))
    {
        assert(false);
        return;
    }

    emit signalBlinkDongle(dongleId);
}
