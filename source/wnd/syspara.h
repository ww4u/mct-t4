#ifndef SYSPARA_H
#define SYSPARA_H

#include <QtCore>


class SysPara
{
public:
    SysPara();

public:
    void init();

public:
    int save( const QString &fileName );
    int load( const QString &fileName );

protected:
    int serialOut( QXmlStreamWriter &writer );
    int serialIn( QXmlStreamReader &reader );

public:
    //! \note change the constructor
    int mLangIndex;
    int mStyleIndex;

    bool mbAutoExpand, mbAutoLoad, mbAutoSearch;
    int mIntfIndex;

    //! addr,model,sn
    //! addr,model,sn
    QStringList mPlugins;

};

#endif // SYSPARA_H
