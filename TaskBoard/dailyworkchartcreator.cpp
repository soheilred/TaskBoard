#include "dailyworkchartcreator.h"
#include <QLabel>
#include <iostream>
using namespace std;

DailyWorkChartCreator::DailyWorkChartCreator(DatabaseManager *db,
                                             TimePeriodChooser *timeChooser,
                                             QObject *parent)
    : ProjectAnalyzer(db, parent)
{
    this->timeChooser = timeChooser;

    buildControls();
}

DailyWorkChartCreator::~DailyWorkChartCreator()
{
    delete timeChooser;
    delete subLayout;
    delete dummyElement;
}

QString DailyWorkChartCreator::getActionText() const
{
    return tr("Daily work");
}

void DailyWorkChartCreator::updateView()
{
    updatePlot();
}

void DailyWorkChartCreator::showControls()
{
    updatePlot();

    ProjectAnalyzer::showControls();
}

void DailyWorkChartCreator::buildControls()
{
    timeChooser->toggleCurrentWeek(true);

    controlsLayout = new QVBoxLayout();
    chartView = new DailyWorkChartView();
    viewWidget = chartView;

    connect(timeChooser, SIGNAL(periodChanged()),
            this, SLOT(updatePlot()));

    controlsLayout->addWidget(timeChooser);
    controlsLayout->addStretch();
    controlsWidget->setLayout(controlsLayout);

    colors.append(QColor("#DC050C"));
    colors.append(QColor("#E8601C"));
    colors.append(QColor("#F1932D"));
    colors.append(QColor("#F6C141"));
    colors.append(QColor("#F7EE55"));
    colors.append(QColor("#CAE0AB"));
    colors.append(QColor("#90C987"));
    colors.append(QColor("#4EB265"));
    colors.append(QColor("#7BAFDE"));
    colors.append(QColor("#5289C7"));
    colors.append(QColor("#1965B0"));
    colors.append(QColor("#D6C1DE"));
    colors.append(QColor("#B178A6"));
    colors.append(QColor("#882E72"));

    subLayout = new QCPLayoutGrid();
    dummyElement = new QCPLayoutElement();

    showOutsideLegend();
}

void DailyWorkChartCreator::updatePlot()
{
    chartView->clearPlottables();

    efforts = db->getProjectEfforts(timeChooser->beginDate(),
                                    timeChooser->endDate());

    formatAxes();

    plotEfforts();

    chartView->replot();
}

void DailyWorkChartCreator::formatAxes()
{
    chartView->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    chartView->xAxis->setDateTimeFormat("yyyy-MM-dd");

    chartView->xAxis->setRange(timeChooser->beginDateTime().addDays(-1).toTime_t(),
                               timeChooser->endDateTime().addDays(1).toTime_t());
    chartView->yAxis->setRange(0, 10);
    chartView->yAxis->setLabel(tr("Hours"));
}

void DailyWorkChartCreator::plotEfforts()
{
    setXTics();
    setYTics();

    buildBars();
}

void DailyWorkChartCreator::showOutsideLegend()
{
    chartView->legend->setVisible(true);
    chartView->plotLayout()->addElement(0, 1, subLayout);
    subLayout->addElement(0, 0, chartView->legend);
    subLayout->addElement(1, 0, dummyElement);
    subLayout->setRowStretchFactor(0, 0.01);
    subLayout->setMaximumSize(150, QWIDGETSIZE_MAX);
}

void DailyWorkChartCreator::setXTics()
{
    xTicks.clear();

    QDateTime date = timeChooser->beginDateTime();

    int days = timeChooser->beginDateTime().daysTo(timeChooser->endDateTime());

    for(int d=0; d<=days; d++){
        xTicks.append(date.toTime_t());
        date = date.addDays(1);
    }

    chartView->xAxis->setAutoTicks(false);
    chartView->xAxis->setTickVector(xTicks);
    chartView->xAxis->setSubTickCount(0);
    chartView->xAxis->setTickLabelRotation(60);
}

void DailyWorkChartCreator::setYTics()
{
    QVector<double> yTics;

    yTics << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;

    chartView->yAxis->setAutoTicks(false);
    chartView->yAxis->setTickVector(yTics);
    chartView->yAxis->setSubTickCount(3);
}

void DailyWorkChartCreator::buildBars()
{
    bars.clear();

    colorIndex = 0;

    QMapIterator <QString, QVector<double>> it(efforts);
    while(it.hasNext()){
        it.next();

        QCPBars *bar = new QCPBars(chartView->xAxis, chartView->yAxis);

        bar->setName(it.key());
        bar->setData(xTicks, it.value());

        styleBar(bar);

        if(!bars.isEmpty())
            bar->moveAbove(bars.last());

        bars.append(bar);
        chartView->addPlottable(bar);
    }
}

void DailyWorkChartCreator::styleBar(QCPBars *bar)
{
    QPen pen;
    pen.setWidthF(1.2);

    bar->setWidthType(QCPBars::wtPlotCoords);
    bar->setWidth(77760);

    QColor brushColor = colors[colorIndex];
    brushColor.setAlpha(125);

    pen.setColor(colors[colorIndex]);
    bar->setBrush(brushColor);
    bar->setPen(pen);

    nextColorIndex();
}

void DailyWorkChartCreator::nextColorIndex()
{
    if(colorIndex < colors.count() - 1)
        colorIndex++;
    else
        colorIndex = 0;
}

