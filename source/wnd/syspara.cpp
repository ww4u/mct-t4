#include "syspara.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

SysPara::SysPara()
{

}

void SysPara::init()
{
    mbAutoExpand = true;
    mbAutoLoad = true;
    mbAutoSearch = true;

    mIntfIndex = 0;
    mStyleIndex = 0;
}

int SysPara::save( const QString &fileName )
{
    QFile file( fileName );
    if ( file.open( QIODevice::WriteOnly ) )
    {}
    else
    { return -1; }

    QXmlStreamWriter writer( &file );

    writer.writeStartDocument();

    writer.writeStartElement("pref");

    int ret = serialOut( writer );

    writer.writeEndElement();

    writer.writeEndDocument();

    file.close();

    return ret;
}
int SysPara::load( const QString &fileName )
{
    QFile file( fileName );
    if ( file.open( QIODevice::ReadOnly ) )
    {}
    else
    { return -1; }

    QXmlStreamReader reader( &file );

    int ret = 0;
    while( reader.readNextStartElement() )
    {
        if ( reader.name() == "pref" )
        {
            ret = serialIn( reader );
        }
        else
        { reader.skipCurrentElement(); }
    }

    return ret;
}

int SysPara::serialOut( QXmlStreamWriter &writer )
{
    writer.writeStartElement( "common" );
        writer.writeTextElement( "language", QString::number( mLangIndex ) );
        writer.writeTextElement( "style", QString::number( mStyleIndex ) );

        writer.writeTextElement( "auto_expand", QString::number( mbAutoExpand ) );
        writer.writeTextElement( "auto_load", QString::number( mbAutoLoad ) );
        writer.writeTextElement( "auto_search", QString::number( mbAutoSearch ) );

        writer.writeTextElement( "intf", QString::number(mIntfIndex) );
    writer.writeEndElement();

    writer.writeStartElement( "plugins");
    foreach( const QString &str, mPlugins )
    {
        writer.writeTextElement( "plugin", str );
    }
    writer.writeEndElement();

    return 0;
}

int SysPara::serialIn( QXmlStreamReader &reader )
{
    while( reader.readNextStartElement() )
    {
        if ( reader.name() == "common" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "language" )
                { mLangIndex = reader.readElementText().toInt(); }
                else if ( reader.name() == "style" )
                { mStyleIndex = reader.readElementText().toInt(); }
                else if ( reader.name() == "auto_expand" )
                { mbAutoExpand = reader.readElementText().toInt() > 0; }
                else if ( reader.name() == "auto_load" )
                { mbAutoLoad = reader.readElementText().toInt() > 0; }
                else if ( reader.name() == "auto_search" )
                { mbAutoSearch = reader.readElementText().toInt() > 0; }
                else if ( reader.name() == "intf" )
                { mIntfIndex = reader.readElementText().toInt(); }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() =="plugins" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "plugin" )
                { mPlugins.append( reader.readElementText()); }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else
        { reader.skipCurrentElement(); }
    }

    return 0;
}
