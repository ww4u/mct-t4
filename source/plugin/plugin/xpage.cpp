#include "xpage.h"

#include "xplugin.h"
#include "xpluginworkingthread.h"
XPage::XPage(QWidget *parent) : QWidget(parent)
{
    mUri = "data";
    m_pPlugin = NULL;
    mbMissionWorking = false;

    mAttr = page_attr_unk;
}

void XPage::changeEvent(QEvent *event)
{
    if ( event->type() == QEvent::LanguageChange )
    {
//        logDbg();
        retranslateUi();
        event->accept();
    }
    else
    { QWidget::changeEvent( event ); }
}

void XPage::retranslateUi()
{}

void XPage::attachPlugin( XPlugin *pPlugin )
{
    Q_ASSERT( NULL != pPlugin );

    mUri = "data";
    m_pPlugin = pPlugin;


    //! virtual
    connectPlugin();

    updateUi();
}
XPlugin *XPage::pulgin()
{ return m_pPlugin; }

void XPage::adapteToUserMode( sysPara::eSysMode mode )
{

}

XPage::PageAttr XPage::pageAttr()
{ return mAttr; }

void XPage::rst()
{}

void XPage::connectPlugin()
{
    Q_ASSERT( NULL != m_pPlugin );

    connect( m_pPlugin, SIGNAL(signal_setting_changed( XSetting ) ),
             this, SLOT(slot_plugin_setting_changed( XSetting)) ) ;
    //! request save
    connect( this, SIGNAL(signal_request_save()),
             m_pPlugin, SLOT(slot_save_setting()) );

    //! plugin->pages
    connect( m_pPlugin, SIGNAL(signal_request_save()),
             this, SLOT(slot_request_save()) );
    connect( m_pPlugin, SIGNAL(signal_request_load()),
             this, SLOT(slot_request_load()) );

    //! \note only for mission
    connect( m_pPlugin->m_pMissionWorking, SIGNAL( signal_enter_working(WorkingApi *)),
             this, SLOT(slot_enter_mission(WorkingApi *)));
    connect( m_pPlugin->m_pMissionWorking, SIGNAL(signal_exit_working(WorkingApi *, int)),
             this, SLOT(slot_exit_mission(WorkingApi *, int)));
}

void XPage::attachWorkings()
{}

//! data -> ui
void XPage::updateUi()
{}

void XPage::updateData()
{}

//! exchange
int XPage::upload()
{ return 0; }
int XPage::download()
{ return 0; }
int XPage::diff()
{ return 0; }

void XPage::onSetting( XSetting setting )
{
    if ( setting.mSetting == XPage::e_setting_opened )
    {
        check_para1();

        //! enable/disable
        setOpened( setting.mPara1.toBool() );
    }
    else if ( setting.mSetting == XPage::e_setting_mission_working )
    {
        check_para1();

        mbMissionWorking = setting.mPara1.toBool();

        if ( mbMissionWorking )
        { enterMission(); }
        else
        { exitMission(); }
    }
    else
    {}
}

void XPage::attachUpdateWorking( XPage::procDo proc,
                           void *pContext
                    )
{
    Q_ASSERT( NULL != m_pPlugin );

    m_pPlugin->attachUpdateWorking( this, proc, pContext );
}
void XPage::attachUpdateWorking( XPage::procDo proc,
                    XPage::preDo pre,
                    XPage::postDo post,
                    void *pContext
                    )
{
    Q_ASSERT( NULL != m_pPlugin );

    m_pPlugin->attachUpdateWorking( this, proc, pre, post, pContext );
}

void XPage::attachMissionWorking( XPage *pObj,
                    XPage::onMsg onmsg,
                    QVariant var
                    )
{
    Q_ASSERT( NULL != m_pPlugin );

    m_pPlugin->attachMissionWorking( this, onmsg, var );
}

void XPage::attachEmergencyWorking( XPage *pObj,
                    XPage::onMsg onmsg,
                    QVariant var
                    )
{
    Q_ASSERT( NULL != m_pPlugin );

    m_pPlugin->attachEmergencyWorking( this, onmsg, var );
}

void XPage::setUri( const QString &uri )
{ mUri = uri; }
QString XPage::Uri( )
{ return mUri; }

int XPage::save( const QString &fileName )
{
    QFile file( fileName );
    if ( file.open( QIODevice::WriteOnly ) )
    {}
    else
    { return -1; }

    int ret;
    QXmlStreamWriter writer( &file );

    writer.writeStartDocument();
    writer.writeStartElement( mUri );
        ret = serialOut( writer );
    writer.writeEndElement();
    writer.writeEndDocument();

    return ret;
}
int XPage::load( const QString &fileName )
{
    QFile file( fileName );
    if ( file.open( QIODevice::ReadOnly ) )
    {}
    else
    { return -1; }

    int ret;
    QXmlStreamReader reader( &file );

    while ( reader.readNextStartElement() )
    {
        if ( reader.name() == mUri )
        {
            ret = serialIn( reader );
        }
        else
        { reader.skipCurrentElement(); }
    }

    return ret;
}

int XPage::serialOut( QXmlStreamWriter &writer )
{ return -1; }
int XPage::serialIn( QXmlStreamReader &reader )
{ return -1; }

void XPage::spyEdited()
{

}

void XPage::spySetting( int setting )
{
    if ( mSpySetting.contains( setting ) )
    {}
    else
    { mSpySetting.append( setting ); }
}

bool XPage::filterSetting( XSetting setting )
{
    foreach (int set, mSpySetting)
    {
        if ( set == setting.mSetting )
        { return false; }
    }

    return true;
}

void XPage::enterMission()
{}
void XPage::exitMission()
{}

void XPage::setOpened( bool b )
{
    setEnabled( b );
}

void XPage::slot_plugin_setting_changed( XSetting setting )
{
    do
    {
        //! sys setting
        if ( (int)setting.mSetting < (int)e_setting_user )
        { break; }

        //! not in filter
        if ( filterSetting( setting ) )
        { return; }

    }while( 0 );

    onSetting( setting );
}

void XPage::slot_enter_mission( WorkingApi *api )
{
    Q_ASSERT( NULL != m_pPlugin );

    m_pPlugin->emit_setting_changed( XPage::e_setting_mission_working, true );
}
void XPage::slot_exit_mission( WorkingApi *api, int ret )
{
    m_pPlugin->emit_setting_changed( XPage::e_setting_mission_working, false );
}

void XPage::slot_request_save()
{}
void XPage::slot_request_load()
{}

void XPage::slot_modified()
{
    updateData();

    emit signal_request_save();
}
