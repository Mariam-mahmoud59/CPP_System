#include "DashboardScreen.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QFont>
#include <QStyle>

DashboardScreen::DashboardScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Header
    QLabel *headerLabel = new QLabel("Dashboard");
    QFont headerFont = headerLabel->font();
    headerFont.setPointSize(24);
    headerFont.setBold(true);
    headerLabel->setFont(headerFont);
    headerLabel->setStyleSheet("color: #ffffff; margin-bottom: 10px;");
    mainLayout->addWidget(headerLabel);

    // Metrics Grid
    QGridLayout *metricsLayout = new QGridLayout;
    metricsLayout->setSpacing(20);

    // Create metric cards
    QFrame *totalSalesCard = new QFrame;
    totalSalesCard->setFrameStyle(QFrame::Box);
    totalSalesCard->setStyleSheet("QFrame { background: #2d313a; border-radius: 10px; padding: 20px; }");
    QVBoxLayout *totalSalesLayout = new QVBoxLayout(totalSalesCard);
    QLabel *totalSalesTitle = new QLabel("Total Sales");
    totalSalesTitle->setStyleSheet("color: #888888; font-size: 14px;");
    totalSalesLabel = new QLabel("$0.00");
    totalSalesLabel->setStyleSheet("color: #4CAF50; font-size: 24px; font-weight: bold;");
    totalSalesLayout->addWidget(totalSalesTitle);
    totalSalesLayout->addWidget(totalSalesLabel);

    QFrame *todaySalesCard = new QFrame;
    todaySalesCard->setFrameStyle(QFrame::Box);
    todaySalesCard->setStyleSheet("QFrame { background: #2d313a; border-radius: 10px; padding: 20px; }");
    QVBoxLayout *todaySalesLayout = new QVBoxLayout(todaySalesCard);
    QLabel *todaySalesTitle = new QLabel("Today's Sales");
    todaySalesTitle->setStyleSheet("color: #888888; font-size: 14px;");
    todaySalesLabel = new QLabel("$0.00");
    todaySalesLabel->setStyleSheet("color: #2196F3; font-size: 24px; font-weight: bold;");
    todaySalesLayout->addWidget(todaySalesTitle);
    todaySalesLayout->addWidget(todaySalesLabel);

    QFrame *totalOrdersCard = new QFrame;
    totalOrdersCard->setFrameStyle(QFrame::Box);
    totalOrdersCard->setStyleSheet("QFrame { background: #2d313a; border-radius: 10px; padding: 20px; }");
    QVBoxLayout *totalOrdersLayout = new QVBoxLayout(totalOrdersCard);
    QLabel *totalOrdersTitle = new QLabel("Total Orders");
    totalOrdersTitle->setStyleSheet("color: #888888; font-size: 14px;");
    totalOrdersLabel = new QLabel("0");
    totalOrdersLabel->setStyleSheet("color: #FF9800; font-size: 24px; font-weight: bold;");
    totalOrdersLayout->addWidget(totalOrdersTitle);
    totalOrdersLayout->addWidget(totalOrdersLabel);

    QFrame *lowStockCard = new QFrame;
    lowStockCard->setFrameStyle(QFrame::Box);
    lowStockCard->setStyleSheet("QFrame { background: #2d313a; border-radius: 10px; padding: 20px; }");
    QVBoxLayout *lowStockLayout = new QVBoxLayout(lowStockCard);
    QLabel *lowStockTitle = new QLabel("Low Stock Items");
    lowStockTitle->setStyleSheet("color: #888888; font-size: 14px;");
    lowStockLabel = new QLabel("0");
    lowStockLabel->setStyleSheet("color: #F44336; font-size: 24px; font-weight: bold;");
    lowStockLayout->addWidget(lowStockTitle);
    lowStockLayout->addWidget(lowStockLabel);

    metricsLayout->addWidget(totalSalesCard, 0, 0);
    metricsLayout->addWidget(todaySalesCard, 0, 1);
    metricsLayout->addWidget(totalOrdersCard, 0, 2);
    metricsLayout->addWidget(lowStockCard, 0, 3);

    mainLayout->addLayout(metricsLayout);

    // Quick Actions Section
    QLabel *actionsLabel = new QLabel("Quick Actions");
    QFont actionsFont = actionsLabel->font();
    actionsFont.setPointSize(18);
    actionsFont.setBold(true);
    actionsLabel->setFont(actionsFont);
    actionsLabel->setStyleSheet("color: #ffffff; margin-top: 20px;");
    mainLayout->addWidget(actionsLabel);

    QHBoxLayout *actionsLayout = new QHBoxLayout;
    actionsLayout->setSpacing(15);

    newSaleBtn = new QPushButton("New Sale");
    newSaleBtn->setMinimumHeight(60);
    newSaleBtn->setStyleSheet("QPushButton { background: #4CAF50; color: white; border: none; border-radius: 10px; font-size: 16px; font-weight: bold; } QPushButton:hover { background: #45a049; }");

    viewInventoryBtn = new QPushButton("View Inventory");
    viewInventoryBtn->setMinimumHeight(60);
    viewInventoryBtn->setStyleSheet("QPushButton { background: #2196F3; color: white; border: none; border-radius: 10px; font-size: 16px; font-weight: bold; } QPushButton:hover { background: #1976D2; }");

    viewReportsBtn = new QPushButton("View Reports");
    viewReportsBtn->setMinimumHeight(60);
    viewReportsBtn->setStyleSheet("QPushButton { background: #FF9800; color: white; border: none; border-radius: 10px; font-size: 16px; font-weight: bold; } QPushButton:hover { background: #F57C00; }");

    settingsBtn = new QPushButton("Settings");
    settingsBtn->setMinimumHeight(60);
    settingsBtn->setStyleSheet("QPushButton { background: #9E9E9E; color: white; border: none; border-radius: 10px; font-size: 16px; font-weight: bold; } QPushButton:hover { background: #757575; }");

    actionsLayout->addWidget(newSaleBtn);
    actionsLayout->addWidget(viewInventoryBtn);
    actionsLayout->addWidget(viewReportsBtn);
    actionsLayout->addWidget(settingsBtn);

    mainLayout->addLayout(actionsLayout);
    mainLayout->addStretch();
}

void DashboardScreen::updateMetrics() {
    // This method will be called to refresh dashboard metrics
    // All data will come from user interactions and database
    // For now, we'll keep the zero values until data is added
} 