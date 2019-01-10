#ifndef XPAGE_H
#define XPAGE_H

#include <QWidget>

class XPlugin;

class XPage : public QWidget
{
    Q_OBJECT
public:
    explicit XPage(QWidget *parent = nullptr);

public:
    void attachPlugin( XPlugin *pPlugin );
    XPlugin *pulgin();

signals:

public slots:

protected:
    XPlugin *m_pPlugin;
};

#endif // XPAGE_H
