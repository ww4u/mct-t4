#ifndef H2STATUS_H
#define H2STATUS_H

#include <QTranslator>
#include <QWidget>

namespace Ui {
class H2Status;
}

class H2Status : public QWidget
{
    Q_OBJECT

public:
    explicit H2Status(QWidget *parent = 0);
    ~H2Status();

    void changeLanguage(QString qmFile);

private slots:
    void on_chkMct_clicked();

private:
    Ui::H2Status *ui;
    QTranslator m_translator;
};

#endif // H2STATUS_H
