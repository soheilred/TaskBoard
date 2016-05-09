#include "burnupchartcreator.h"
#include "dailyworkchartcreator.h"
#include "estimationerrorchartcreator.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");

    DatabaseManager *db = new DatabaseManager(&dataBase);

    TimerController *timerController = new TimerController(new QTimer());

    timerController->injectDisplay(new TimeDisplay());
    timerController->injectDatabase(db);

    StatisticsWindow *statsWindow = new StatisticsWindow();
    statsWindow->addAnalyzer(new BurnUpChartCreator(db));
    statsWindow->addAnalyzer(new DailyWorkChartCreator(db));
    statsWindow->addAnalyzer(new EstimationErrorChartCreator(db));

    MainWindow w(timerController, statsWindow, 0);

    w.injectColumnWidgets(new TaskColumn(new EditTaskDialog(new EditProjectDialog(),
                                                            new TaskRecordsDialog(&dataBase))),
                          new TaskColumn(new EditTaskDialog(new EditProjectDialog(),
                                                            new TaskRecordsDialog(&dataBase))),
                          new TaskColumn(new EditTaskDialog(new EditProjectDialog(),
                                                            new TaskRecordsDialog(&dataBase))));

    w.injectModels(new TaskModel(db),
                   new TaskModel(db),
                   new TaskModel(db));


    w.show();

    return a.exec();
}