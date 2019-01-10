#include "pluginfactory.h"

#include "../t4/t4.h"

//! factory
XPlugin *PluginFactory::createPlugin( const QString &name,
                              const QString &addr )
{
    if ( name == "mrx-t4" )
    {
        return new MRX_T4( );
    }
    else
    {
        return NULL;
    }
}

PluginFactory::PluginFactory()
{

}
