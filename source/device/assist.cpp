
#include <QThread>

void localSleep( int ms )
{
    while( ms > 0 )
    {
        if ( QThread::currentThread()->isInterruptionRequested() )
        { return; }

        QThread::msleep( 10 );
        ms -= 10;
    }
}
