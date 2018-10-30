#ifndef DIAGNOSISITEM_H
#define DIAGNOSISITEM_H

#include <QtCore>

class DiagnosisItem
{
public:
    static int columns();
    static QString header( int col );

public:
    DiagnosisItem();

public:
    int mNr;
    QString mType;
    QString mTs;
    QString mAddInfo;
    int mCounter;
    QString mMessage;
};

#endif // DIAGNOSISITEM_H
