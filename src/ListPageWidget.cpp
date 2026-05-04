#include "ListPageWidget.h"
#include "ui_ListPageWidget.h"
#include "ListItemDelegate.h"
#include "LicenseItemWidget.h"
#include "Feature.h"
#include <cassert>

ListPageWidget::ListPageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ListPageWidget)
{
    ui->setupUi(this);

    ui->headerLabel->setObjectName(QStringLiteral("GLabelMainHeader"));
    ui->activateButton->setObjectName(QStringLiteral("GButtonLicenseActivate"));
    ui->stackedWidget->setObjectName(QStringLiteral("GFrameWhite"));
    ui->headLabel->setObjectName(QStringLiteral("GLabelSectionHeader"));
    ui->questionLabel->setObjectName(QStringLiteral("GLabelQuestionText"));
    ui->serialIconLabel->setObjectName(QStringLiteral("GLabelProposalIconLicense"));
    ui->serialTextLabel->setObjectName(QStringLiteral("GLabelProposalText"));
    ui->serialTipLabel->setObjectName(QStringLiteral("GLabelProposalTip"));
    ui->dongleIconLabel->setObjectName(QStringLiteral("GLabelProposalIconDongle"));
    ui->dongleTextLabel->setObjectName(QStringLiteral("GLabelProposalText"));
    ui->dongleTipLabel->setObjectName(QStringLiteral("GLabelProposalTip"));
    ui->treePage->setObjectName(QStringLiteral("GTreeWidgetMain"));

    ui->treePage->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    ui->treePage->header()->setDefaultAlignment(Qt::AlignHCenter);
    ui->treePage->header()->resizeSection(0, 240);
    ui->treePage->header()->resizeSection(1, 200);
    ui->treePage->header()->resizeSection(2, 80);
    ui->treePage->header()->resizeSection(3, 120);
    ui->treePage->setItemDelegate(new ListItemDelegate());

    connect(ui->activateButton, &QPushButton::clicked,
            this, &ListPageWidget::signalGoActivation);
    connect(ui->treePage, &QTreeWidget::currentItemChanged,
            this, &ListPageWidget::onCurrentItemChanged);
}

ListPageWidget::~ListPageWidget()
{
    delete ui;
}

void ListPageWidget::retranslate()
{
    ui->retranslateUi(this);
    retranslateTree();
}

void ListPageWidget::notifyDevicesChanged(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    if (data->isEmpty())
    {
        goBlank();
        ui->treePage->clear();
        m_data.clear();
    }
    else
    {
        goTree();
        rebuildTree(data);
        m_data = data;
    }
}

void ListPageWidget::notifyLicenseUpdateAvailable(const uint32_t licenseId)
{
    QTreeWidgetItem* licItem = licenseItem(licenseId);
    if (licItem)
        dynamic_cast<LicenseItemWidget*>(
                ui->treePage->itemWidget(licItem, 0))->setUpdateAvailable();
}

void ListPageWidget::notifyLicenseUpdateUnavailable(const uint32_t licenseId)
{
    QTreeWidgetItem* licItem = licenseItem(licenseId);
    if (licItem)
        dynamic_cast<LicenseItemWidget*>(
                ui->treePage->itemWidget(licItem, 0))->setUpdateUnavailable();
}

void ListPageWidget::goBlank()
{
    ui->stackedWidget->setCurrentWidget(ui->blankPage);
}

void ListPageWidget::goTree()
{
    ui->stackedWidget->setCurrentWidget(ui->treePage);
}

void ListPageWidget::onCurrentItemChanged(
        QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QWidget* currentWidget = ui->treePage->itemWidget(current, 0);
    if (currentWidget)
    {
        LicenseItemWidget* item =
                dynamic_cast<LicenseItemWidget*>(currentWidget);
        if (item)
        {
            item->setSelected(true);
            item->style()->unpolish(item);
            item->style()->polish(item);
        }
    }
    QWidget* previousWidget = ui->treePage->itemWidget(previous, 0);
    if (previousWidget)
    {
        LicenseItemWidget* item =
                dynamic_cast<LicenseItemWidget*>(previousWidget);
        if (item)
        {
            item->setSelected(false);
            item->style()->unpolish(item);
            item->style()->polish(item);
        }
    }
}

static const char Dash[] = "\xE2\x80\x94"; // long dash in UTF-8

void ListPageWidget::rebuildTree(
        const QSharedPointer<QVector<DeviceChecker::LicenseInfo>> data)
{
    for (int i = 0; i < ui->treePage->topLevelItemCount(); )
    {
        QTreeWidgetItem* licenseItem = ui->treePage->topLevelItem(i);
        const uint32_t licenseId = itemLicenseId(licenseItem);
        bool found = false;
        for (int j = 0; j < data->size(); ++j)
        {
            const DeviceChecker::LicenseInfo& licenseInfo = data->at(j);
            if (licenseInfo.id == licenseId)
            {
                found = true;
                break;
            }
        }
        if (!found)
            delete ui->treePage->takeTopLevelItem(i);
        else
            ++i;
    }

    for (int i = 0; i < data->size(); ++i)
    {
        const DeviceChecker::LicenseInfo& licenseInfo = data->at(i);
        if (!changeLicense(licenseInfo))
            addLicense(licenseInfo);
    }

    // Sorting by license ID
    ui->treePage->sortItems(0, Qt::SortOrder::AscendingOrder);
}

bool ListPageWidget::changeLicense(
        const DeviceChecker::LicenseInfo& licenseInfo)
{
    bool found = false;
    for (int i = 0; i < ui->treePage->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* licenseItem = ui->treePage->topLevelItem(i);
        if (itemLicenseId(licenseItem) != licenseInfo.id)
            continue;

        found = true;

        QVector<uint32_t> products;
        for (int j = 0; j < licenseItem->childCount(); ++j)
        {
            QTreeWidgetItem* productItem = licenseItem->child(j);
            products << itemProductId(productItem);
        }

        for (int j = 0; j < licenseInfo.products.size(); ++j)
        {
            const DeviceChecker::ProductInfo& productInfo =
                    licenseInfo.products[j];
            if (!changeProduct(productInfo, licenseItem))
                addProduct(productInfo, licenseItem);
            products.removeAll(productInfo.id);
        }

        for (int j = 0; j < products.size(); ++j)
            removeProduct(products[j], licenseItem);

        break;
    }
    return found;
}

bool ListPageWidget::changeProduct(
        const DeviceChecker::ProductInfo& productInfo,
        QTreeWidgetItem* licenseItem)
{
    bool found = false;
    for (int i = 0; i < licenseItem->childCount(); ++i)
    {
        QTreeWidgetItem* productItem = licenseItem->child(i);
        if (itemProductId(productItem) != productInfo.id)
            continue;

        found = true;

        QWidget* productWidget = ui->treePage->itemWidget(productItem, 0);
        QLabel* productLabel = reinterpret_cast<QLabel*>(productWidget);
        productLabel->setText(productInfo.name);

        QVector<uint32_t> features;
        for (int j = 0; j < productItem->childCount(); ++j)
        {
            QTreeWidgetItem* featureItem = productItem->child(j);
            features << itemFeatureId(featureItem);
        }

        for (int j = 0; j < productInfo.features.size(); ++j)
        {
            const DeviceChecker::FeatureInfo& featureInfo =
                    productInfo.features[j];
            if (!changeFeature(featureInfo, productItem))
                addFeature(featureInfo, productItem);
            features.removeAll(featureInfo.id);
        }

        for (int j = 0; j < features.size(); ++j)
            removeFeature(features[j], productItem);

        break;
    }
    return found;
}

bool ListPageWidget::changeFeature(
        const DeviceChecker::FeatureInfo& featureInfo,
        QTreeWidgetItem* productItem)
{
    bool found = false;
    for (int i = 0; i < productItem->childCount(); ++i)
    {
        QTreeWidgetItem* featureItem = productItem->child(i);
        if (itemFeatureId(featureItem) != featureInfo.id)
            continue;

        found = true;

        // Feature name
        QWidget* featNameWidget = ui->treePage->itemWidget(featureItem, 0);
        QLabel* featNameLabel = reinterpret_cast<QLabel*>(featNameWidget);
        featNameLabel->setText(featureInfo.name);

        // Feature date
        QWidget* featDateWidget = ui->treePage->itemWidget(featureItem, 1);
        QLabel* featDateLabel = reinterpret_cast<QLabel*>(featDateWidget);
        featDateLabel->setText(featureDate(featureInfo, Dash));

        // Feature resource
        if (featureInfo.maxConcurrentResource)
        {
            QWidget* widget = ui->treePage->itemWidget(featureItem, 2);
            QLayout* widgetLayout = widget->layout();
            if (widgetLayout != nullptr)
            {
                QHBoxLayout* layout = reinterpret_cast<QHBoxLayout*>(
                            widgetLayout);

                QWidget* iconWidget = layout->itemAt(1)->widget();
                QLabel* iconLabel = reinterpret_cast<QLabel*>(iconWidget);
                const FeatureConsumptionMode fcm =
                        featureConsumptionModeValue(featureInfo);
                if (fcm == FeatureConsumptionMode::PerStation)
                    iconLabel->setObjectName(
                                QStringLiteral("GLabelModePerStation"));
                else if (fcm == FeatureConsumptionMode::PerLogin)
                    iconLabel->setObjectName(
                                QStringLiteral("GLabelModePerLogin"));
                else if (fcm == FeatureConsumptionMode::PerProcess)
                    iconLabel->setObjectName(
                                QStringLiteral("GLabelModePerProcess"));
                iconLabel->setToolTip(
                            setFeatureItemIconToolTipText(featureInfo));
                iconLabel->style()->unpolish(iconLabel);
                iconLabel->style()->polish(iconLabel);
                iconLabel->adjustSize();

                QWidget* textWidget = layout->itemAt(2)->widget();
                QLabel* textLabel = reinterpret_cast<QLabel*>(textWidget);
                textLabel->setText(
                            QString::number(
                                featureInfo.maxConcurrentResource -
                                featureInfo.detachedResource));
                textLabel->style()->unpolish(textLabel);
                textLabel->style()->polish(textLabel);
                textLabel->adjustSize();
            }
        }
        else
        {
            QLabel* featResLabel = new QLabel(Dash);
            featResLabel->setObjectName(QStringLiteral("GLabelFeatureItem"));
            featResLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
            ui->treePage->setItemWidget(featureItem, 2, featResLabel);
        }

        // Feature VM enabled
        QWidget* featVmWidget = ui->treePage->itemWidget(featureItem, 3);
        QLabel* featVmLabel = reinterpret_cast<QLabel*>(featVmWidget);
        const bool isVmForbidden = featureIsVmForbidden(featureInfo);
        featVmLabel->setText(isVmForbidden ? Dash : QString());
        if (!isVmForbidden)
            featVmLabel->setObjectName(QStringLiteral("GLabelMarkIconTick"));
        else
            featVmLabel->setObjectName(QStringLiteral("GLabelFeatureItem"));

        break;
    }
    return found;
}

void ListPageWidget::addLicense(const DeviceChecker::LicenseInfo& licenseInfo)
{

    QTreeWidgetItem* licenseItem = new QTreeWidgetItem();
    setItemLicenseId(licenseItem, licenseInfo.id);
    ui->treePage->addTopLevelItem(licenseItem);
    ui->treePage->setFirstItemColumnSpanned(licenseItem, true);

    LicenseItemWidget* licenseWidget = new LicenseItemWidget(
                licenseInfo.dongleType, licenseInfo.id, licenseInfo.publicCode,
                licenseInfo.isRehostable, licenseInfo.isTrial,
                licenseInfo.isMaster, licenseInfo.isDetached);
    ui->treePage->setItemWidget(licenseItem, 0, licenseWidget);

    connect(licenseWidget, &LicenseItemWidget::signalLicenseUpdate,
            this, &ListPageWidget::signalLicenseUpdate);
    connect(licenseWidget, &LicenseItemWidget::signalLicenseCheckUpdate,
            this, &ListPageWidget::signalLicenseCheckUpdate);
    connect(licenseWidget, &LicenseItemWidget::signalLicenseUpdateOffline,
            this, &ListPageWidget::signalLicenseUpdateOffline);
    connect(licenseWidget, &LicenseItemWidget::signalGoRehost,
            this, &ListPageWidget::signalGoRehost);
    connect(licenseWidget, &LicenseItemWidget::signalGoWrite,
            this, &ListPageWidget::signalGoWrite);
    connect(licenseWidget, &LicenseItemWidget::signalLicenseRemove,
            this, &ListPageWidget::signalLicenseRemove);
    connect(licenseWidget, &LicenseItemWidget::signalLicenseIdCopiedToClipboard,
            this, &ListPageWidget::signalLicenseIdCopiedToClipboard);

    for (int i = 0; i < licenseInfo.products.size(); ++i)
        addProduct(licenseInfo.products[i], licenseItem);

    ui->treePage->expandItem(licenseItem);
}

void ListPageWidget::addProduct(
        const DeviceChecker::ProductInfo& productInfo,
        QTreeWidgetItem* licenseItem)
{
    QTreeWidgetItem* productItem = new QTreeWidgetItem(licenseItem);
    setItemProductId(productItem, productInfo.id);
    ui->treePage->addTopLevelItem(productItem);
    productItem->setToolTip(
                0, '(' + QString::number(productInfo.id) + ')' + ' ' +
                productInfo.name);
    ui->treePage->setFirstItemColumnSpanned(productItem, true);

    QLabel* prodLabel = new QLabel(productInfo.name);
    prodLabel->setObjectName(QStringLiteral("GLabelProductItem"));
    ui->treePage->setItemWidget(productItem, 0, prodLabel);

    for (int i = 0; i < productInfo.features.size(); ++i)
        addFeature(productInfo.features[i], productItem);

    ui->treePage->expandItem(productItem);
}

void ListPageWidget::addFeature(
        const DeviceChecker::FeatureInfo& featureInfo,
        QTreeWidgetItem* productItem)
{
    QTreeWidgetItem* featureItem = new QTreeWidgetItem(productItem);
    setItemFeatureId(featureItem, featureInfo.id);
    ui->treePage->addTopLevelItem(featureItem);
    featureItem->setToolTip(
                0, '(' + QString::number(featureInfo.id) + ')' + ' ' +
                featureInfo.name);

    QLabel* featNameLabel = new QLabel(featureInfo.name);
    featNameLabel->setObjectName(QStringLiteral("GLabelFeatureItem"));
    ui->treePage->setItemWidget(featureItem, 0, featNameLabel);

    QLabel* featDateLabel = new QLabel(
                featureDate(featureInfo, Dash));
    featDateLabel->setObjectName(QStringLiteral("GLabelFeatureItem"));
    featDateLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    ui->treePage->setItemWidget(featureItem, 1, featDateLabel);

    if (featureInfo.maxConcurrentResource)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);

        QLabel* iconLabel = new QLabel();
        const FeatureConsumptionMode fcm =
                featureConsumptionModeValue(featureInfo);
        if (fcm == FeatureConsumptionMode::PerStation)
            iconLabel->setObjectName(QStringLiteral("GLabelModePerStation"));
        else if (fcm == FeatureConsumptionMode::PerLogin)
            iconLabel->setObjectName(QStringLiteral("GLabelModePerLogin"));
        else if (fcm == FeatureConsumptionMode::PerProcess)
            iconLabel->setObjectName(QStringLiteral("GLabelModePerProcess"));
        iconLabel->setToolTip(
                    setFeatureItemIconToolTipText(featureInfo));
        iconLabel->adjustSize();
        iconLabel->setSizePolicy(
                    QSizePolicy::Minimum, QSizePolicy::Minimum);
        iconLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        QLabel* textLabel = new QLabel();
        textLabel->setObjectName(QStringLiteral("GLabelModeNumber"));
        textLabel->setText(
                    QString::number(
                        featureInfo.maxConcurrentResource -
                        featureInfo.detachedResource));
        textLabel->setSizePolicy(
                    QSizePolicy::Maximum, QSizePolicy::Maximum);
        textLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        QSpacerItem* leftSpacer = new QSpacerItem(
                    20, 20,
                    QSizePolicy::Expanding, QSizePolicy::Minimum);
        QSpacerItem* rightSpacer = new QSpacerItem(
                    20, 20,
                    QSizePolicy::Expanding, QSizePolicy::Minimum);

        layout->addItem(leftSpacer);
        layout->addWidget(iconLabel, 1);
        layout->addWidget(textLabel, 2);
        layout->addItem(rightSpacer);
        ui->treePage->setItemWidget(featureItem, 2, widget);
    }
    else
    {
        QLabel* featResLabel = new QLabel(Dash);
        featResLabel->setObjectName(QStringLiteral("GLabelFeatureItem"));
        featResLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ui->treePage->setItemWidget(featureItem, 2, featResLabel);
    }

    const bool isVmForbidden = featureIsVmForbidden(featureInfo);
    QLabel* featVmLabel = new QLabel(
                isVmForbidden ? Dash : QString());
    if (!isVmForbidden)
        featVmLabel->setObjectName(QStringLiteral("GLabelMarkIconTick"));
    else
        featVmLabel->setObjectName(QStringLiteral("GLabelFeatureItem"));
    featVmLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    ui->treePage->setItemWidget(featureItem, 3, featVmLabel);

    featureItem->setTextAlignment(0, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    featureItem->setTextAlignment(1, Qt::AlignmentFlag::AlignCenter);
    featureItem->setTextAlignment(2, Qt::AlignmentFlag::AlignCenter);
    featureItem->setTextAlignment(3, Qt::AlignmentFlag::AlignCenter);

    ui->treePage->expandItem(featureItem);
}

void ListPageWidget::removeProduct(
        const uint32_t productId,
        QTreeWidgetItem* licenseItem)
{
    for (int i = 0; i < licenseItem->childCount(); ++i)
    {
        QTreeWidgetItem* productItem = licenseItem->child(i);
        if (itemProductId(productItem) == productId)
        {
            ui->treePage->itemWidget(productItem, 0)->deleteLater();
            delete licenseItem->takeChild(i);
            break;
        }
    }
}

void ListPageWidget::removeFeature(
        const uint32_t featureId,
        QTreeWidgetItem* productItem)
{
    for (int i = 0; i < productItem->childCount(); ++i)
    {
        QTreeWidgetItem* featureItem = productItem->child(i);
        if (itemFeatureId(featureItem) == featureId)
        {
            ui->treePage->itemWidget(featureItem, 0)->deleteLater();
            delete productItem->takeChild(i);
            break;
        }
    }
}

void ListPageWidget::retranslateTree()
{
    using LicenseInfo = DeviceChecker::LicenseInfo;
    using ProductInfo = DeviceChecker::ProductInfo;
    using FeatureInfo = DeviceChecker::FeatureInfo;

    for (int i = 0; i < ui->treePage->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* licenseItem = ui->treePage->topLevelItem(i);

        int index = -1;
        for (int j = 0; j < m_data->size(); ++j)
        {
            if (m_data->at(j).id == itemLicenseId(licenseItem))
            {
                index = j;
                break;
            }
        }
        if (index == -1)
        {
            assert(false);
            continue;
        }

        const LicenseInfo& licenseInfo = m_data->at(index);

        QWidget* widget = ui->treePage->itemWidget(licenseItem, 0);
        LicenseItemWidget* licenseItemWidget =
                qobject_cast<LicenseItemWidget*>(widget);
        licenseItemWidget->retranslate();

        for (int j = 0; j < licenseItem->childCount(); ++j)
        {
            const ProductInfo& productInfo = licenseInfo.products[j];

            QTreeWidgetItem* productItem = licenseItem->child(j);
            assert(itemProductId(productItem) == productInfo.id);

            for (int k = 0; k < productItem->childCount(); ++k)
            {
                const FeatureInfo& featureInfo = productInfo.features[k];

                QTreeWidgetItem* featureItem = productItem->child(k);
                assert(itemFeatureId(featureItem) == featureInfo.id);

                QWidget* widget = ui->treePage->itemWidget(featureItem, 1);
                QLabel* label = qobject_cast<QLabel*>(widget);
                label->setText(featureDate(featureInfo, Dash));

                if (featureInfo.maxConcurrentResource)
                {
                    QWidget* widget = ui->treePage->itemWidget(featureItem, 2);
                    QLayout* layout = widget->layout();
                    QLayoutItem* iconItem = layout->itemAt(1);
                    QWidget* iconWidget = iconItem->widget();
                    QLabel* iconLabel = qobject_cast<QLabel*>(iconWidget);
                    iconLabel->setToolTip(
                                setFeatureItemIconToolTipText(featureInfo));
                }
            }
        }
    }
}

QTreeWidgetItem* ListPageWidget::licenseItem(const uint32_t licenseId)
{
    QTreeWidgetItem* foundItem = nullptr;
    for (int i = 0; i < ui->treePage->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem* licItem = ui->treePage->topLevelItem(i);
        if (itemLicenseId(licItem) == licenseId)
            foundItem = licItem;
    }
    return foundItem;
}

QString ListPageWidget::setFeatureItemIconToolTipText(
        const DeviceChecker::FeatureInfo& featureInfo)
{
    switch (featureConsumptionModeValue(featureInfo))
    {
    case FeatureConsumptionMode::PerStation:
        return tr("The number of machines on which the Feature is running "
                  "simultaneously");
    case FeatureConsumptionMode::PerLogin:
        return tr("The number of API connections");
    case FeatureConsumptionMode::PerProcess:
        return tr("The number of running instances of the Feature");
    case FeatureConsumptionMode::None:
    default:
        return QString();
    }
}
