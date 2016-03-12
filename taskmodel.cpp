#include "taskmodel.h"
#include <QDebug>

TaskModel::TaskModel(DatabaseManager *db, QObject *parent)
    : QAbstractListModel(parent)
{
    this->db = db;
}

TaskModel::~TaskModel()
{

}

void TaskModel::setFilterString(const QString &s)
{
    filterString = s;
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    return db->size(filterString);
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    QVariant();
}

TaskEntry TaskModel::getTask(const QModelIndex &index) const
{
    return db->getTaskEntry(filterString, index.row());
}

