#ifndef MEGALOGLISTMODEL_H
#define MEGALOGLISTMODEL_H

#include <QAbstractListModel>

class LogStr
{
public:
    enum eLogLevel
    {
        log_info,
        log_warning,
        log_error
    };
public:
    eLogLevel mLevel;
    QString mStr;
};

class MegaLogListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MegaLogListModel(QObject *parent = nullptr);
    ~MegaLogListModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public:
    void append( const QString &content, LogStr::eLogLevel lev=LogStr::log_info );
    void clear();

private:
//    QStringList mItemList;
    QList< LogStr *> mItemList;
    int mMaxCount;

};

#endif // MEGALISTMODEL_H
