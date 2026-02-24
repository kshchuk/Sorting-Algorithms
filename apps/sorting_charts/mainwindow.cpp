#include "mainwindow.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

void ChartRunner::run(bool useInt) {
    chart_data::ChartResults results = chart_data::run(useInt, [this](int current, int total, const std::string& message) {
        emit progressUpdate(current, total, QString::fromStdString(message));
    });
    emit resultsReady(results);
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    qRegisterMetaType<chart_data::ChartResults>("chart_data::ChartResults");
    auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* mainLayout = new QVBoxLayout(central);

    auto* topBar = new QHBoxLayout();
    m_typeCombo = new QComboBox(this);
    m_typeCombo->addItem(tr("int"), true);
    m_typeCombo->addItem(tr("double"), false);
    topBar->addWidget(m_typeCombo);

    m_runBtn = new QPushButton(tr("Run benchmarks"), this);
    connect(m_runBtn, &QPushButton::clicked, this, &MainWindow::onRunClicked);
    topBar->addWidget(m_runBtn);

    m_saveBtn = new QPushButton(tr("Save chart"), this);
    connect(m_saveBtn, &QPushButton::clicked, this, &MainWindow::onSaveChart);
    topBar->addWidget(m_saveBtn);

    m_statusLabel = new QLabel(tr("Click Run to measure sorting times."), this);
    topBar->addWidget(m_statusLabel);
    topBar->addStretch();
    mainLayout->addLayout(topBar);

    m_progressBar = new QProgressBar(this);
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(0);
    m_progressBar->setTextVisible(true);
    mainLayout->addWidget(m_progressBar);

    m_tabs = new QTabWidget(this);
    m_chartUniform = new QChartView(this);
    m_chartUniform->setChart(new QChart());
    m_chartNormal = new QChartView(this);
    m_chartNormal->setChart(new QChart());
    m_tabs->addTab(m_chartUniform, tr("Uniform distribution"));
    m_tabs->addTab(m_chartNormal, tr("Normal distribution"));
    mainLayout->addWidget(m_tabs);

    setupCharts();

    m_workerThread = new QThread(this);
    m_runner = new ChartRunner();
    m_runner->moveToThread(m_workerThread);
    connect(this, &MainWindow::startRun, m_runner, &ChartRunner::run);
    connect(m_runner, &ChartRunner::progressUpdate, this, &MainWindow::onProgressUpdate);
    connect(m_runner, &ChartRunner::resultsReady, this, &MainWindow::onResultsReady);
    m_workerThread->start();

    setWindowTitle(tr("Sorting algorithms: time vs size"));
    resize(900, 600);
}

MainWindow::~MainWindow() {
    if (m_workerThread && m_workerThread->isRunning()) {
        m_workerThread->quit();
        m_workerThread->wait(3000);
    }
}

void MainWindow::setupCharts() {
    for (QChartView* view : { m_chartUniform, m_chartNormal }) {
        QChart* ch = view->chart();
        ch->setTitle(tr("Execution time vs array size"));
        ch->legend()->setAlignment(Qt::AlignRight);
        auto* axisX = new QValueAxis();
        axisX->setTitleText(tr("Array size (n)"));
        auto* axisY = new QValueAxis();
        axisY->setTitleText(tr("Time (ms)"));
        ch->addAxis(axisX, Qt::AlignBottom);
        ch->addAxis(axisY, Qt::AlignLeft);
    }
}

void MainWindow::onRunClicked() {
    bool useInt = m_typeCombo->currentData().toBool();
    m_lastTypeInt = useInt;
    m_runBtn->setEnabled(false);
    m_statusLabel->setText(tr("Running benchmarks…"));
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(0);
    emit startRun(useInt);
}

void MainWindow::onProgressUpdate(int current, int total, const QString& message) {
    if (total > 0) {
        m_progressBar->setRange(0, total);
        m_progressBar->setValue(current);
        m_statusLabel->setText(tr("Running benchmarks… %1/%2 %3").arg(current).arg(total).arg(message));
    }
}

void MainWindow::onResultsReady(chart_data::ChartResults results) {
    m_runBtn->setEnabled(true);
    m_progressBar->setValue(m_progressBar->maximum());
    m_statusLabel->setText(tr("Done."));
    updateChart(QStringLiteral("Uniform"), results);
    updateChart(QStringLiteral("Normal"), results);
}

void MainWindow::updateChart(const QString& distName, const chart_data::ChartResults& results) {
    auto it = results.find(distName.toStdString());
    if (it == results.end()) return;

    QChartView* view = (distName == QLatin1String("Uniform")) ? m_chartUniform : m_chartNormal;
    QChart* chart = view->chart();
    chart->removeAllSeries();

    const QString typeStr = m_lastTypeInt ? QStringLiteral("int") : QStringLiteral("double");
    chart->setTitle(tr("Execution time vs array size — %1, %2").arg(distName).arg(typeStr));

    for (const auto& algoEntry : it->second) {
        const std::string& algoName = algoEntry.first;
        const auto& points = algoEntry.second;
        auto* series = new QLineSeries();
        series->setName(QString::fromStdString(algoName));
        for (const auto& p : points) {
            series->append(p.first, p.second);
        }
        chart->addSeries(series);
        const auto axes = chart->axes();
        for (QAbstractAxis* axis : axes) {
            series->attachAxis(axis);
        }
    }
    chart->legend()->setAlignment(Qt::AlignRight);
}

void MainWindow::onSaveChart() {
    QChartView* view = qobject_cast<QChartView*>(m_tabs->currentWidget());
    if (!view) return;
    QString filter = tr("PNG images (*.png)");
    QString path = QFileDialog::getSaveFileName(this, tr("Save chart"), QString(), filter, &filter);
    if (path.isEmpty()) return;
    if (!path.endsWith(QStringLiteral(".png"), Qt::CaseInsensitive))
        path += QStringLiteral(".png");
    QPixmap pix = view->grab();
    if (!pix.save(path)) {
        QMessageBox::warning(this, tr("Save failed"), tr("Could not save to %1").arg(path));
    } else {
        m_statusLabel->setText(tr("Saved to %1").arg(path));
    }
}
