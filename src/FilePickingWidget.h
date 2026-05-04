#ifndef FILEPICKINGWIDGET_H
#define FILEPICKINGWIDGET_H

#include <QWidget>
#include "Common.h"

namespace Ui {
class FilePickingWidget;
}

class FilePickingWidget : public QWidget
{
    Q_OBJECT

public:

    explicit FilePickingWidget(QWidget* parent = nullptr);
    ~FilePickingWidget();

    void installForLicenseAndRehostFiles();
    void installForLicenseFiles();
    void installForRequestAndRehostFiles();
    void installForFingerprintFiles();
    void installForCodeFiles();

    QString selectedFilePath() const
    {
        return m_filePath;
    }

    void retranslate();

public slots:

    void dropProgress();

    void notifyError();

    void notifyCodesCount(int count);

signals:

    void signalFileSelected();
    void signalFileDeselected();

private:

    Ui::FilePickingWidget *ui;

    FileType m_fileType;
    FileType m_altFileType;

    QString m_filePath;

    int m_codesCount;

    void goSelected();
    void goNotSelected();

    void updateCodesCountText();

    inline void setFileName();

    inline bool queryFileOpen();

private slots:

    void onFileSelectionButtonClicked();
    void onFileReselectionButtonClicked();
    void onFileDeselectionButtonClicked();
};

#endif // FILEPICKINGWIDGET_H
