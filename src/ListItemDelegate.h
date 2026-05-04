#ifndef LISTITEMDELEGATE_H
#define LISTITEMDELEGATE_H

#include <QStyledItemDelegate>

// See: https://stackoverflow.com/questions/52692448/formatting-child-items-in-qtreewidget-pyqt5

class ListItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    // Allows default height setting via stylesheet
    Q_PROPERTY(int m_licenseItemHeight
               READ licenseItemHeight
               WRITE setLicenseItemHeight)
    Q_PROPERTY(int m_productItemHeight
               READ productItemHeight
               WRITE setProductItemHeight)
    Q_PROPERTY(int m_featureItemHeight
               READ featureItemHeight
               WRITE setFeatureItemHeight)

    // Make sure it can be bound to the stylesheets
    inline static const char LicenseItemHeightPropName[] = "licenseItemHeight";
    inline static const char ProductItemHeightPropName[] = "productItemHeight";
    inline static const char FeatureItemHeightPropName[] = "featureItemHeight";

public:

    explicit ListItemDelegate(QObject* parent = nullptr);

    ~ListItemDelegate() override
    {
    }

    QSize sizeHint(
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const override;

    int licenseItemHeight() const;
    int productItemHeight() const;
    int featureItemHeight() const;

    void setLicenseItemHeight(const int height);
    void setProductItemHeight(const int height);
    void setFeatureItemHeight(const int height);

protected:

    inline bool isLicenseItem(const QModelIndex &index) const;
    inline bool isProductItem(const QModelIndex &index) const;
    inline bool isFeatureItem(const QModelIndex &index) const;

private:

    // Make sure it can be tuned here
    static const int DefaultLicenseItemHeight = 25;
    static const int DefaultProductItemHeight = 35;
    static const int DefaultFeatureItemHeight = 35;
};

#endif // LISTITEMDELEGATE_H
