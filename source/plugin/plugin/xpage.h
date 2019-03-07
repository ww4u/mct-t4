#ifndef XPAGE_H
#define XPAGE_H

#include <QtWidgets>
#include "../../sys/sysapi.h"
#include "../../../include/mystd.h"

class XPlugin;
class XSetting;
class WorkingApi;

#define set_page_attr( attr )   mAttr = (attr);
#define set_page_rstable( )     set_page_attr( page_rst_able )

#define check_para1()       if ( setting.mPara1.isValid() )\
                            {}\
                            else\
                            { return; }

class XPage : public QWidget
{
    Q_OBJECT

public:
    enum PageAttr
    {
        page_attr_unk = 0,
        page_rst_able = 1
    };

    enum eXSetting
    {
        e_setting_unk = 0,
        e_setting_op_able,
        e_setting_opened,

        e_setting_mission_working,

        e_setting_user = 1024,
    };

public:
    typedef bool (XPage::*isEnable)( void *context );
    typedef void (XPage::*preDo)( void *context );
    typedef int (XPage::*procDo)( void *context );
    typedef void (XPage::*postDo)( void *context, int ret );

    typedef int (XPage::*onMsg)( QVariant var );

public:
    explicit XPage(QWidget *parent = nullptr);

protected:
    virtual void changeEvent(QEvent *event);
    virtual void focusInEvent(QFocusEvent *event);

protected:
    virtual void retranslateUi();

public:
    void attachPlugin( XPlugin *pPlugin );
    XPlugin *pulgin();

    virtual void adapteToUserMode( sysPara::eSysMode mode );
    PageAttr pageAttr();
    virtual void rst();

    virtual void connectPlugin();
    virtual void attachWorkings();

    virtual void updateUi();        //! data -> ui
    virtual void updateData();

    virtual int upload();
    virtual int download();
    virtual int diff();

    virtual void onSetting( XSetting setting );
public:
    QString model();
    void showFocusHelp();

    void attachUpdateWorking( XPage::procDo proc,
                              void *pContext = NULL,
                              int tmo = 100
                        );
    void attachUpdateWorking( XPage::procDo proc,
                        XPage::preDo pre,
                        XPage::postDo post,
                        void *pContext = NULL,
                        int tmo = 100
                        );

    void attachMissionWorking( XPage *pObj,
                        XPage::onMsg onmsg,
                        QVariant var
                        );

    void attachEmergencyWorking( XPage *pObj,
                        XPage::onMsg onmsg,
                        QVariant var
                        );

protected:
    void setUri( const QString &uri );
    QString Uri( );

    void setContextHelp( const QString &str );
    QString contextHelp();

public:
    int save( const QString &fileName );
    int load( const QString &fileName );

protected:
    virtual int serialOut( QXmlStreamWriter &writer );
    virtual int serialIn( QXmlStreamReader &reader );

protected:
    virtual void spyEdited();
    void spySetting( int setting );
    bool filterSetting( XSetting setting );

    virtual void enterMission();
    virtual void exitMission();

    virtual void setOpened( bool b );

signals:
    void signal_request_save();
    void signal_focus_changed( const QString &model,
                               const QString &contextHelp );

protected slots:
    void slot_plugin_setting_changed( XSetting setting );
    void slot_modified();

    virtual void slot_enter_mission( WorkingApi *api );
    virtual void slot_exit_mission( WorkingApi *api, int ret );

    virtual void slot_request_save();
    virtual void slot_request_load();

protected:
    QList< int > mSpySetting;

    XPlugin *m_pPlugin;

    PageAttr mAttr;

    QString mUri;

    QString mContextHelp;

    bool mbMissionWorking;


};

class XSetting
{
public:
    XPage::eXSetting mSetting;
    QVariant mPara1, mPara2, mPara3;
};
Q_DECLARE_METATYPE(XSetting)


#endif // XPAGE_H
