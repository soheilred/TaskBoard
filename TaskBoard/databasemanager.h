#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QMap>
#include <QObject>
#include <QVector>
#include <QSqlDatabase>
#include "taskentry.h"
#include "projectentry.h"

enum TaskState{
    ToDo = 1,
    Today = 2,
    Done = 3
};


class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    struct DayEffort{
        QDateTime date;
        double effortMinutes;
    };

    struct EstimationError{
        QString taskTitle;
        int estimation;
        int effort;
        int estimationError() { return estimation - effort; }
        bool isValid() { return estimation != 0 && effort != 0; }
    };

    DatabaseManager(QSqlDatabase *db);
    virtual ~DatabaseManager();

    int size(TaskState state) const;

    TaskEntry getTaskEntry(int id) const;
    TaskEntry getTaskEntry(TaskState state, int index) const;
    QVector<TaskEntry> getTaskEntries(TaskState state) const;
    void addTaskEntry(TaskEntry entry);
    void updateTaskEntry(TaskEntry entry);
    void updateTaskField(int id, const QString &fieldName, int value);
    void removeTaskEntry(int id);
    void setTaskState(int id, int state);
    void sortTaskIntoColumn(int id, int state, int index);
    void insertIntoColumn(TaskState state, int beforeRow, int taskId);

    QStringList listOfProjects() const;
    QList <ProjectEntry> getActiveProjects() const;
    void addProjectEntry(ProjectEntry entry);
    ProjectEntry getProjectEntry(int index) const;
    void updateProjectEntry(ProjectEntry entry);

    void addRecord(int taskID, QDateTime startTime, int minutes);
    int getEffortForTask(int taskID) const;
    QMap<QString, QVector<double>> getProjectEfforts(QDate begin, QDate end);
    QMap<QString, double> getProjectEfforts(QDate date);
    QMap<QString, double> getSummedProjectEfforts(QDate begin, QDate end) const;
    QList<QPair<QString, double>> getSummedTaskEfforts(const QString &project, QDate begin, QDate end) const;
    QVector<DayEffort> getDayEffortsOfProject(int projectID);
    QVector<EstimationError> getEstimationErrors(QDate begin, QDate end);

signals:
    void dataChanged(int taskID);

private:
    QSqlDatabase *db;
    const int maximumInt;

    void openDatabase();
    bool dataBaseIsInitialized();
    void createTables();
    QSqlQuery taskQuery(TaskState state) const;
    TaskEntry buildTaskEntry(const QSqlQuery &query) const;
    ProjectEntry buildProjectEntry(const QSqlQuery &query) const;
    void rearrangeSortingOrder(TaskState state);
    void getSortingIndices(TaskState state, int row, int &currentIndex, int &previousIndex);
    int getNewSortingIndex(TaskState state);
    int getTodaysEffort(int taskID);
    void performRecordQuery(const QString &queryString, int taskID, QDateTime startTime, int minutes);
    QString getUpdatedClosedDate(int id, int state);
    QString getClosedDateString(int id);
    void executeQuery(QSqlQuery &query);
};

#endif // DATABASEMANAGER_H
