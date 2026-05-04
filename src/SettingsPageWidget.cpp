#include "SettingsPageWidget.h"
#include "ui_SettingsPageWidget.h"
#include "Logger.h"
#include "Url.h"
#include "User.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMutex>
#include <QStyledItemDelegate>

SettingsPageWidget::SettingsPageWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SettingsPageWidget)
{
    ui->setupUi(this);
    ui->backButton->adjustSize();

    // Needed for the correct combo box item stylesheet setting
    QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
    ui->langComboBox->setItemDelegate(itemDelegate);

    ui->headerLabel->setObjectName(QStringLiteral("GLabelMainHeader"));
    ui->backButton->setObjectName(QStringLiteral("GButtonBack"));
    ui->serverFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->serverLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->serverTipLabel->setObjectName(QStringLiteral("GLabelMainTip"));
    ui->autoLabel->setObjectName(QStringLiteral("GLabelNormalText"));
    ui->logFrame->setObjectName(QStringLiteral("GFrameWhite"));
    ui->logButton->setObjectName(QStringLiteral("GButtonInTextBigger"));
    ui->altButton->setObjectName(QStringLiteral("GButtonLogDirectory"));
    ui->bottomLine->setObjectName(QStringLiteral("GLine"));

    connect(ui->backButton, &QPushButton::clicked,
            this, &SettingsPageWidget::signalGoMain);
    connect(ui->serverLine, &QLineEdit::editingFinished,
            this, &SettingsPageWidget::onServerLineEditingFinished);
    connect(ui->autoCheckBox, &QCheckBox::clicked,
            this, &SettingsPageWidget::signalSetAutoCheck);
    connect(ui->logButton, &QPushButton::clicked,
            this, &SettingsPageWidget::onLogButtonClicked);
    connect(ui->altButton, &QPushButton::clicked,
            this, &SettingsPageWidget::onLogButtonClicked);

    connect(ui->langComboBox, static_cast<void (QComboBox::*)(int)>(
                &QComboBox::currentIndexChanged),
            this, &SettingsPageWidget::onLangComboBoxCurrentItemChanged);
}

SettingsPageWidget::~SettingsPageWidget()
{
    delete ui;
}

void SettingsPageWidget::retranslate()
{
    ui->retranslateUi(this);
    ui->backButton->adjustSize();
}

void SettingsPageWidget::fillLangComboBox()
{
    // Since the QComboBox cannot have a one-for-all icon (icons are only set
    //   per an item), and since the box model padding affects both the text
    //   and the image, we have to add a whitespace-only prefix (for left-to-
    //   right languages), according to the font metrics (Roboto, 13px) for the
    //   needed icon size (12 * 12) plus distance between the icon and the
    //   text, which is 12 px + 5 px = 17 px -> 16 px or 6 spaces
    // Note the QComboBox menu needed and implemented have different widths,
    //   and unwanted text elision can happen on any stylesheet property change
    constexpr char spaces[] = "      ";
    const QList<User::Locale>& locales = User::supportedLocales();
    const QLocale& current = User::instance().locale();
    int index = -1;
    foreach (const User::Locale& locale, locales)
    {
        QString name = spaces + locale.nativeName;
        if (!locale.commonName.isEmpty())
            name += " (" + locale.commonName + ")";
        ui->langComboBox->addItem(name, locale.locale);
        if (locale.locale.language() == current.language())
            index = ui->langComboBox->count() - 1;
    }

    if (index == -1) // unexpected value in the Registry
    {
        // Use English
        index = 0;
        User::instance().setLocale(locales.first().locale);
    }
    ui->langComboBox->setCurrentIndex(index);
}

void SettingsPageWidget::setLangComboBoxLocale(const QLocale& targetLocale)
{
    for (int index = 0; index < ui->langComboBox->count(); ++index)
    {
        const QLocale itemLocale =
                ui->langComboBox->itemData(index).toLocale();
        if (itemLocale == targetLocale)
        {
            if (ui->langComboBox->currentIndex() != index)
                ui->langComboBox->setCurrentIndex(index);
            break;
        }
    }
}

void SettingsPageWidget::setUrl(const QString& url)
{
    ui->serverLine->setText(url);
}

void SettingsPageWidget::setAutoCheck(const bool autoCheck)
{
    ui->autoCheckBox->setCheckState(autoCheck ? Qt::Checked : Qt::Unchecked);
}

void SettingsPageWidget::onServerLineEditingFinished()
{
    // Qt emits signal QLineEdit::editingFinished in a weird way: once Enter
    //   key is pressed, two signals are emitted one right after another (one
    //   for QLineEdit::keyPressEvent and one for QLineEdit::focusOutEvent),
    //   while pressing the Tab key or clicking on some other focus-changing
    //   widget emits only one signal; because of this weird issue, we have to
    //   utilize a mutex here to prevent spam...
    static QMutex mutex;
    if (mutex.tryLock())
    {
        emit signalUpdateUrl(ui->serverLine->text());
        mutex.unlock();
    }
}

void SettingsPageWidget::onLogButtonClicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(loggerGetLogLocation()));
}

void SettingsPageWidget::onLangComboBoxCurrentItemChanged(int index)
{
    QLocale locale = ui->langComboBox->itemData(index).toLocale();
    emit signalChangeLocale(locale);
}
