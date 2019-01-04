#ifndef XROBO_H
#define XROBO_H

#include <QObject>
#include <QStackedWidget>
#include <QApplication>
#include <QTranslator>

class XRobo : public QObject
{
    Q_OBJECT
public:
    explicit XRobo( QStackedWidget *pWig, QObject *parent = nullptr);

public:
    QString addr() const;
    void setAddr(const QString &addr);

public slots:
    virtual void changeLanguage(QString qmFile);
    virtual void translateUI();

protected:
    QString m_addr;
    QTranslator m_translator;
};

#endif // XROBO_H
