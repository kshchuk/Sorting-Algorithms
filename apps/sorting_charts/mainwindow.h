#pragma once

#include "chart_data.hpp"
#include <QMetaType>
#include <QMainWindow>
#include <QTabWidget>
#include <QChartView>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QProgressBar>
#include <QThread>

class ChartRunner : public QObject {
    Q_OBJECT
public:
    explicit ChartRunner(QObject* parent = nullptr) : QObject(parent) {}
public slots:
    void run(bool useInt);
signals:
    void progressUpdate(int current, int total, const QString& message);
    void resultsReady(chart_data::ChartResults results);
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
signals:
    void startRun(bool useInt);
private slots:
    void onRunClicked();
    void onProgressUpdate(int current, int total, const QString& message);
    void onResultsReady(chart_data::ChartResults results);
    void onSaveChart();
private:
    void setupCharts();
    void updateChart(const QString& distName, const chart_data::ChartResults& results);

    QTabWidget* m_tabs = nullptr;
    QChartView* m_chartUniform = nullptr;
    QChartView* m_chartNormal = nullptr;
    QPushButton* m_runBtn = nullptr;
    QPushButton* m_saveBtn = nullptr;
    QComboBox* m_typeCombo = nullptr;
    bool m_lastTypeInt = true;
    QProgressBar* m_progressBar = nullptr;
    QLabel* m_statusLabel = nullptr;
    ChartRunner* m_runner = nullptr;
    QThread* m_workerThread = nullptr;
};

Q_DECLARE_METATYPE(chart_data::ChartResults)
