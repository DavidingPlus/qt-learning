#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QProgressDialog>
#include <QNetworkAccessManager>
#include <QUrl>

#include <memory>

QT_BEGIN_NAMESPACE
class QFile;
class QLabel;
class QLineEdit;
class QPushButton;
class QSslError;
class QAuthenticator;
class QNetworkReply;
class QCheckBox;

QT_END_NAMESPACE

class ProgressDialog : public QProgressDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(const QUrl& url, QWidget* parent = nullptr);
    ~ProgressDialog();

public slots:
    void networkReplyProgress(qint64 bytesRead, qint64 totalBytes);
};

class HttpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HttpWindow(QWidget* parent = nullptr);
    ~HttpWindow();

    void startRequest(const QUrl& requestedUrl);

private slots:
    void downloadFile();
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void enableDownloadButton();
    void slotAuthenticationRequired(QNetworkReply*, QAuthenticator* authenticator);
#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply*, const QList<QSslError>& errors);
#endif

private:
    std::unique_ptr<QFile> openFileForWrite(const QString& fileName);

    QLabel* statusLabel;
    QLineEdit* urlLineEdit;
    QPushButton* downloadButton;
    QCheckBox* launchCheckBox;
    QLineEdit* defaultFileLineEdit;
    QLineEdit* downloadDirectoryLineEdit;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply* reply;
    std::unique_ptr<QFile> file;
    bool httpRequestAborted;
};

#endif
