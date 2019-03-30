
#include <QThread>
#include <QException>
void localSleep( int ms )
{
    while( ms > 0 )
    {
        if ( QThread::currentThread()->isInterruptionRequested() )
        {
            throw QException();
//            return;
        }

        QThread::msleep( 10 );
        ms -= 10;
    }
}
