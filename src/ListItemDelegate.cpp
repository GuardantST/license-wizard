#include "ListItemDelegate.h"
#include <cassert>

ListItemDelegate::ListItemDelegate(QObject* parent) :
    QStyledItemDelegate(parent)
{
    setLicenseItemHeight(0);
    setProductItemHeight(0);
    setFeatureItemHeight(0);
}

bool ListItemDelegate::isLicenseItem(const QModelIndex &index) const
{
    return !index.parent().isValid();
}

bool ListItemDelegate::isProductItem(const QModelIndex &index) const
{
    return index.parent().isValid() && index.child(0, 0).isValid();
}

bool ListItemDelegate::isFeatureItem(const QModelIndex &index) const
{
    return index.parent().isValid() && !index.child(0, 0).isValid();
}

int ListItemDelegate::licenseItemHeight() const
{
    const int height = this->property(LicenseItemHeightPropName).toInt();
    return height ? height : DefaultLicenseItemHeight;
}

int ListItemDelegate::productItemHeight() const
{
    const int height = this->property(ProductItemHeightPropName).toInt();
    return height ? height : DefaultProductItemHeight;
}

int ListItemDelegate::featureItemHeight() const
{
    const int height = this->property(FeatureItemHeightPropName).toInt();
    return height ? height : DefaultFeatureItemHeight;
}

void ListItemDelegate::setLicenseItemHeight(const int height)
{
    if (height > 0)
        this->setProperty(LicenseItemHeightPropName, height);
}

void ListItemDelegate::setProductItemHeight(const int height)
{
    if (height > 0)
        this->setProperty(ProductItemHeightPropName, height);
}

void ListItemDelegate::setFeatureItemHeight(const int height)
{
    if (height > 0)
        this->setProperty(FeatureItemHeightPropName, height);
}

QSize ListItemDelegate::sizeHint(
        const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    if (isLicenseItem(index))
        result.setHeight(licenseItemHeight());
    else if (isProductItem(index))
        result.setHeight(productItemHeight());
    else if (isFeatureItem(index))
        result.setHeight(featureItemHeight());
    else
        assert(false);
    return result;
}
