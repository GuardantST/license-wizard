#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>

// QPushButton with a dynamically changed icon
// Icon is only changed between the normal (default) and highlight (on hover or
//   on pressed) states
// Note that the stylesheet needs to be defined anyway for the default state
class IconButton : public QPushButton
{
    Q_OBJECT

public:

    explicit IconButton(QWidget* parent = nullptr) :
        QPushButton(parent)
    {
    }

    explicit IconButton(const QString& text, QWidget* parent = nullptr) :
        QPushButton(text, parent)
    {
    }

    void setNormalIcon(const QIcon& icon)
    {
        m_normalIcon = icon;
    }

    void setHighlightIcon(const QIcon& icon)
    {
        m_highlightIcon = icon;
    }

protected:

    void enterEvent(QEvent* event) override
    {
        this->setIcon(m_highlightIcon);
        QPushButton::enterEvent(event);
    }

    void leaveEvent(QEvent* event) override
    {
        this->setIcon(m_normalIcon);
        QPushButton::leaveEvent(event);
    }

private:

    QIcon m_normalIcon;
    QIcon m_highlightIcon;
};

#endif // ICONBUTTON_H
