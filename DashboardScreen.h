#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class DashboardScreen : public QWidget {
    Q_OBJECT
public:
    DashboardScreen(QWidget *parent = nullptr);
    void updateMetrics();

private:
    QLabel *totalSalesLabel;
    QLabel *todaySalesLabel;
    QLabel *totalOrdersLabel;
    QLabel *lowStockLabel;
    QPushButton *newSaleBtn;
    QPushButton *viewInventoryBtn;
    QPushButton *viewReportsBtn;
    QPushButton *settingsBtn;
}; 