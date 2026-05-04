#include "LicensePickingWidget.h"
#include "ui_LicensePickingWidget.h"

LicensePickingWidget::LicensePickingWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LicensePickingWidget)
{
    ui->setupUi(this);

    ui->headerLabel->setObjectName(QStringLiteral("GLabelLicensePickingGray"));
    ui->treeWidget->setObjectName(QStringLiteral("GTreeWidgetAux"));
    ui->pickedFrame->setObjectName(QStringLiteral("GFrameGray"));
    ui->licenseLabel->setObjectName(QStringLiteral("GLabelLicensePickingBlack"));
    ui->clearButton->setObjectName(QStringLiteral("GButtonCross"));
    ui->blankLabel->setObjectName(QStringLiteral("GLabelLicensePickingGray"));

    ui->treeWidget->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    ui->treeWidget->setSizeAdjustPolicy(QTreeWidget::AdjustToContents);
    ui->treeWidget->setColumnWidth(0, 520);
    ui->treeWidget->setColumnWidth(1, 100);

    connect(ui->clearButton, &QPushButton::clicked,
            this, &LicensePickingWidget::onLicenseDeselectionButtonClicked);

    connect(ui->treeWidget, &QTreeWidget::expanded,
            this, &LicensePickingWidget::onTreeWidgetExpandedOrCollapsed);
    connect(ui->treeWidget, &QTreeWidget::collapsed,
            this, &LicensePickingWidget::onTreeWidgetExpandedOrCollapsed);
}

LicensePickingWidget::~LicensePickingWidget()
{
    delete ui;
}

void LicensePickingWidget::retranslate()
{
    ui->retranslateUi(this);
    retranslateTree();
}

void LicensePickingWidget::dropProgress()
{
    installSelf();
}

void LicensePickingWidget::installSelf()
{
    goTreeOrBlank();
}

void LicensePickingWidget::notifyDevicesChanged(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    rebuildTree(data);
    ui->treeWidget->expandAll();
    if (!isLicenseIdValid(selectedLicenseId()))
        goTreeOrBlank();
}

bool LicensePickingWidget::selectLicense(const uint32_t licenseId)
{
    if (!isLicenseIdValid(licenseId))
        return false;

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);
        if (itemLicenseId(item) == licenseId)
        {
            noteLicenseSelected(item);
            return true;
        }
    }
    return false;
}

void LicensePickingWidget::deselectLicense()
{
    noteLicenseDeselected();
}

uint32_t LicensePickingWidget::selectedLicenseId() const
{
    if (!ui->pickedFrame->isVisible())
        return InvalidLicenseId;

    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if (!item)
        return InvalidLicenseId;

    const uint32_t licenseId = itemLicenseId(item);
    if (licenseId == NullLicenseId)
        return InvalidLicenseId;
    return licenseId;
}

DongleType LicensePickingWidget::selectedDongleType() const
{
    if (!ui->pickedFrame->isVisible())
        return DongleType::Unknown;

    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if (!item)
        return DongleType::Unknown;

    DongleType dongleType = itemDongleType(item);
    dongleType = dongleTypeCheck(dongleType);
    return dongleType;
}

void LicensePickingWidget::goTree()
{
    ui->headerLabel->setVisible(true);
    ui->treeWidget->setVisible(true);
    ui->pickedFrame->setVisible(false);
    ui->blankLabel->setVisible(false);
}

void LicensePickingWidget::goSelected()
{
    ui->headerLabel->setVisible(false);
    ui->treeWidget->setVisible(false);
    ui->pickedFrame->setVisible(true);
    ui->blankLabel->setVisible(false);
}

void LicensePickingWidget::goBlank()
{
    ui->headerLabel->setVisible(false);
    ui->treeWidget->setVisible(false);
    ui->pickedFrame->setVisible(false);
    ui->blankLabel->setVisible(true);
}

void LicensePickingWidget::goTreeOrBlank()
{
    if (ui->treeWidget->topLevelItemCount())
        goTree();
    else
        goBlank();
}

inline static bool canUpdate(
        const DongleType dongleType, const uint32_t licenseId)
{
    switch (dongleType)
    {
    case DongleType::Dl:
    case DongleType::DlNet:
        return true;
    case DongleType::Sign:
    case DongleType::SignNet:
    case DongleType::Time:
    case DongleType::TimeNet:
        return isLicenseIdValid(licenseId);
    case DongleType::Code:
    case DongleType::CodeNet:
    case DongleType::CodeTime:
    case DongleType::CodeTimeNet:
    case DongleType::Unknown:
    default:
        return false;
    }
}

void LicensePickingWidget::rebuildTree(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    using LicenseInfo = DeviceChecker::LicenseInfo;
    using ProductInfo = DeviceChecker::ProductInfo;

    const uint32_t targetLicenseId = selectedLicenseId();

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); )
    {
        QTreeWidgetItem* licenseItem = ui->treeWidget->topLevelItem(i);
        const uint32_t licenseId = itemLicenseId(licenseItem);
        bool found = false;
        for (int j = 0; j < data->size(); ++j)
        {
            const LicenseInfo& licenseInfo = data->at(j);
            if (licenseInfo.id == licenseId)
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
        if (!canUpdate(licenseInfo.dongleType, licenseInfo.id) ||
                licenseInfo.isDetached)
            continue;

        bool found = false;
        for (int j = 0; j < ui->treeWidget->topLevelItemCount(); ++j)
        {
            QTreeWidgetItem* licenseItem = ui->treeWidget->topLevelItem(j);
            if (itemLicenseId(licenseItem) == licenseInfo.id)
            {
                found = true;
                break;
            }
        }
        if (found)
            continue;

        QTreeWidgetItem* licenseItem = new QTreeWidgetItem();
        setItemData(licenseItem, licenseInfo.dongleType, licenseInfo.id);
        ui->treeWidget->addTopLevelItem(licenseItem);
        setLicenseItemText(licenseItem);

        QWidget* widget = new QWidget();
        QGridLayout* layout = new QGridLayout();
        layout->setSpacing(0);
        layout->setMargin(0);
        widget->setLayout(layout);
        QPushButton* button = new QPushButton();
        setSelectButtonText(button);
        button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        button->setObjectName(QStringLiteral("GButtonOutline"));
        widget->layout()->addWidget(button);
        ui->treeWidget->setItemWidget(licenseItem, 1, widget);

        connect(button, &QPushButton::clicked, this,
                [this, licenseItem] {
            noteLicenseSelected(licenseItem);
        });

        for (int j = 0; j < licenseInfo.products.size(); ++j)
        {
            const ProductInfo& productInfo = licenseInfo.products[j];

            QTreeWidgetItem* productItem = new QTreeWidgetItem(
                        licenseItem, QStringList() << productInfo.name);
            ui->treeWidget->addTopLevelItem(productItem);
            ui->treeWidget->setFirstItemColumnSpanned(productItem, true);
        }
    }

    // Sorting by license ID
    ui->treeWidget->sortItems(0, Qt::SortOrder::AscendingOrder);

    // Find the recently selected license by ID and select it again, if it is
    //   still there
    if (!isLicenseIdValid(targetLicenseId))
    {
        for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
        {
            QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);
            if (itemLicenseId(item) == targetLicenseId)
                ui->treeWidget->setCurrentItem(item);
        }
    }
}

void LicensePickingWidget::retranslateTree()
{
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* licItem = ui->treeWidget->topLevelItem(i);
        if (licItem != nullptr)
        {
            QWidget* licWidget = ui->treeWidget->itemWidget(licItem, 1);
            if (licWidget != nullptr)
            {
                QLayout* layout = licWidget->layout();
                if (layout != nullptr)
                {
                    QLayoutItem* item = layout->itemAt(0);
                    if (item != nullptr)
                    {
                        QWidget* buttonWidget = item->widget();
                        if (buttonWidget != nullptr)
                        {
                            QPushButton* button = dynamic_cast<QPushButton*>(
                                        buttonWidget);
                            if (button != nullptr)
                                setSelectButtonText(button);
                        }
                    }
                }
            }

            setLicenseItemText(licItem);
        }
    }

    // While the picked frame is shown, current item is supposed to remain the
    //   same, since once the select button has been clicked, current item get
    //   changed correspondingly as well, and cannot be changed until picked
    //   frame gets hidden
    if (ui->pickedFrame->isVisible())
        if (ui->treeWidget->currentItem() && // some item is selected
                !ui->treeWidget->currentItem()->parent()) // item has no parent
            ui->licenseLabel->setText(buildLicenseText(
                                          ui->treeWidget->currentItem()));
}

void LicensePickingWidget::setSelectButtonText(QPushButton* selectButton)
{
    selectButton->setText(tr("Select"));
}

void LicensePickingWidget::setLicenseItemText(QTreeWidgetItem* licItem)
{
    licItem->setText(0, buildLicenseText(licItem));
}

void LicensePickingWidget::noteLicenseSelected(QTreeWidgetItem* licItem)
{
    ui->treeWidget->setCurrentItem(licItem);
    ui->licenseLabel->setText(ui->treeWidget->currentItem()->text(0));
    goSelected();
    emit signalLicenseSelected();
}

void LicensePickingWidget::noteLicenseDeselected()
{
    ui->treeWidget->selectionModel()->clearSelection();
    ui->licenseLabel->setText(QString());
    goTreeOrBlank();
    emit signalLicenseDeselected();
}

void LicensePickingWidget::onLicenseDeselectionButtonClicked()
{
    noteLicenseDeselected();
}

void LicensePickingWidget::onTreeWidgetExpandedOrCollapsed(
        const QModelIndex& index)
{
    Q_UNUSED(index);

    // This counting is viable for the current stylesheets applied

    int height =
            ui->treeWidget->contentsMargins().top() +
            ui->treeWidget->contentsMargins().bottom();

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* licItem = ui->treeWidget->topLevelItem(i);

        height += ui->treeWidget->visualItemRect(licItem).height();
        if (licItem->isExpanded() && licItem->childCount())
        {
            QTreeWidgetItem* prodItem = licItem->child(0);
            height += licItem->childCount() *
                    ui->treeWidget->visualItemRect(prodItem).height();
        }
    }

    ui->treeWidget->setMaximumHeight(height);
    ui->treeWidget->setMinimumHeight(height);
}
