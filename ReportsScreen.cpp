#include "ReportsScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QHeaderView>
#include <QMessageBox>
#include <QFont>
#include <QFrame>
#include <QTabWidget>
#include <QCalendarWidget>

ReportsScreen::ReportsScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Header
    QLabel *headerLabel = new QLabel("Reports & Analytics");
    QFont headerFont = headerLabel->font();
    headerFont.setPointSize(24);
    headerFont.setBold(true);
    headerLabel->setFont(headerFont);
    headerLabel->setStyleSheet("color: #ffffff; margin-bottom: 10px;");
    mainLayout->addWidget(headerLabel);

    // Summary Cards
    setupSummaryCards();
    QHBoxLayout *summaryLayout = new QHBoxLayout;
    
    // Revenue Card
    QFrame *revenueCard = new QFrame;
    revenueCard->setStyleSheet("QFrame { background: #2d313a; border-radius: 10px; padding: 20px; }");
    QVBoxLayout *revenueLayout = new QVBoxLayout(revenueCard);
    QLabel *revenueTitle = new QLabel("Total Revenue");
    revenueTitle->setStyleSheet("color: #888888; font-size: 14px;");
    totalRevenueLabel = new QLabel("$0.00");
    totalRevenueLabel->setStyleSheet("color: #4CAF50; font-size: 24px; font-weight: bold;");
    revenueLayout->addWidget(revenueTitle);
    revenueLayout->addWidget(totalRevenueLabel);
    
    // Orders Card
    QFrame *ordersCard = new QFrame;
    ordersCard->setStyleSheet("QFrame { background: #2d313a; border-radius: 10px; padding: 20px; }");
    QVBoxLayout *ordersLayout = new QVBoxLayout(ordersCard);
    QLabel *ordersTitle = new QLabel("Total Orders");
    ordersTitle->setStyleSheet("color: #888888; font-size: 14px;");
    totalOrdersLabel = new QLabel("0");
    totalOrdersLabel->setStyleSheet("color: #2196F3; font-size: 24px; font-weight: bold;");
    ordersLayout->addWidget(ordersTitle);
    ordersLayout->addWidget(totalOrdersLabel);
    
    // Average Order Card
    QFrame *avgOrderCard = new QFrame;
    avgOrderCard->setStyleSheet("QFrame { background: #2d313a; border-radius: 10px; padding: 20px; }");
    QVBoxLayout *avgOrderLayout = new QVBoxLayout(avgOrderCard);
    QLabel *avgOrderTitle = new QLabel("Avg Order Value");
    avgOrderTitle->setStyleSheet("color: #888888; font-size: 14px;");
    averageOrderLabel = new QLabel("$0.00");
    averageOrderLabel->setStyleSheet("color: #FF9800; font-size: 24px; font-weight: bold;");
    avgOrderLayout->addWidget(avgOrderTitle);
    avgOrderLayout->addWidget(averageOrderLabel);
    
    // Top Product Card
    QFrame *topProductCard = new QFrame;
    topProductCard->setStyleSheet("QFrame { background: #2d313a; border-radius: 10px; padding: 20px; }");
    QVBoxLayout *topProductLayout = new QVBoxLayout(topProductCard);
    QLabel *topProductTitle = new QLabel("Top Product");
    topProductTitle->setStyleSheet("color: #888888; font-size: 14px;");
    topProductLabel = new QLabel("No data");
    topProductLabel->setStyleSheet("color: #9C27B0; font-size: 18px; font-weight: bold;");
    topProductLayout->addWidget(topProductTitle);
    topProductLayout->addWidget(topProductLabel);
    
    summaryLayout->addWidget(revenueCard);
    summaryLayout->addWidget(ordersCard);
    summaryLayout->addWidget(avgOrderCard);
    summaryLayout->addWidget(topProductCard);
    
    mainLayout->addLayout(summaryLayout);

    // Tab Widget for different reports
    tabWidget = new QTabWidget;
    tabWidget->setStyleSheet("QTabWidget::pane { border: 2px solid #444; border-radius: 8px; background: #2d313a; } QTabBar::tab { background: #3a3f4b; color: white; padding: 10px 20px; border: none; } QTabBar::tab:selected { background: #2196F3; } QTabBar::tab:hover { background: #1976D2; }");
    
    // Sales Report Tab
    QWidget *salesTab = new QWidget;
    setupSalesReport();
    QVBoxLayout *salesTabLayout = new QVBoxLayout(salesTab);
    
    // Sales Report Controls
    QHBoxLayout *salesControlsLayout = new QHBoxLayout;
    
    QLabel *periodLabel = new QLabel("Period:");
    periodLabel->setStyleSheet("color: #ffffff; font-size: 14px;");
    salesPeriodCombo = new QComboBox;
    salesPeriodCombo->addItems({"Today", "This Week", "This Month", "This Year", "Custom Range"});
    salesPeriodCombo->setStyleSheet("QComboBox { padding: 8px; border: 2px solid #444; border-radius: 6px; background: #2d313a; color: white; font-size: 14px; }");
    
    QLabel *startLabel = new QLabel("Start Date:");
    startLabel->setStyleSheet("color: #ffffff; font-size: 14px;");
    startDateEdit = new QDateEdit;
    startDateEdit->setCalendarPopup(true);
    startDateEdit->setDate(QDate::currentDate().addDays(-30));
    startDateEdit->setStyleSheet("QDateEdit { padding: 8px; border: 2px solid #444; border-radius: 6px; background: #2d313a; color: white; font-size: 14px; }");
    
    QLabel *endLabel = new QLabel("End Date:");
    endLabel->setStyleSheet("color: #ffffff; font-size: 14px;");
    endDateEdit = new QDateEdit;
    endDateEdit->setCalendarPopup(true);
    endDateEdit->setDate(QDate::currentDate());
    endDateEdit->setStyleSheet("QDateEdit { padding: 8px; border: 2px solid #444; border-radius: 6px; background: #2d313a; color: white; font-size: 14px; }");
    
    generateSalesBtn = new QPushButton("Generate Report");
    generateSalesBtn->setStyleSheet("QPushButton { background: #4CAF50; color: white; border: none; border-radius: 8px; padding: 10px; font-size: 14px; font-weight: bold; } QPushButton:hover { background: #45a049; }");
    connect(generateSalesBtn, &QPushButton::clicked, this, &ReportsScreen::generateSalesReport);
    
    exportSalesBtn = new QPushButton("Export");
    exportSalesBtn->setStyleSheet("QPushButton { background: #2196F3; color: white; border: none; border-radius: 8px; padding: 10px; font-size: 14px; font-weight: bold; } QPushButton:hover { background: #1976D2; }");
    connect(exportSalesBtn, &QPushButton::clicked, this, &ReportsScreen::exportReport);
    
    printSalesBtn = new QPushButton("Print");
    printSalesBtn->setStyleSheet("QPushButton { background: #FF9800; color: white; border: none; border-radius: 8px; padding: 10px; font-size: 14px; font-weight: bold; } QPushButton:hover { background: #F57C00; }");
    connect(printSalesBtn, &QPushButton::clicked, this, &ReportsScreen::printReport);
    
    salesControlsLayout->addWidget(periodLabel);
    salesControlsLayout->addWidget(salesPeriodCombo);
    salesControlsLayout->addWidget(startLabel);
    salesControlsLayout->addWidget(startDateEdit);
    salesControlsLayout->addWidget(endLabel);
    salesControlsLayout->addWidget(endDateEdit);
    salesControlsLayout->addStretch();
    salesControlsLayout->addWidget(generateSalesBtn);
    salesControlsLayout->addWidget(exportSalesBtn);
    salesControlsLayout->addWidget(printSalesBtn);
    
    salesTabLayout->addLayout(salesControlsLayout);
    salesTabLayout->addWidget(salesTable);
    
    // Inventory Report Tab
    QWidget *inventoryTab = new QWidget;
    setupInventoryReport();
    QVBoxLayout *inventoryTabLayout = new QVBoxLayout(inventoryTab);
    
    // Inventory Report Controls
    QHBoxLayout *inventoryControlsLayout = new QHBoxLayout;
    
    QLabel *categoryLabel = new QLabel("Category:");
    categoryLabel->setStyleSheet("color: #ffffff; font-size: 14px;");
    inventoryCategoryCombo = new QComboBox;
    inventoryCategoryCombo->addItems({"All Categories", "Beverages", "Food", "Desserts", "Snacks"});
    inventoryCategoryCombo->setStyleSheet("QComboBox { padding: 8px; border: 2px solid #444; border-radius: 6px; background: #2d313a; color: white; font-size: 14px; }");
    
    generateInventoryBtn = new QPushButton("Generate Report");
    generateInventoryBtn->setStyleSheet("QPushButton { background: #4CAF50; color: white; border: none; border-radius: 8px; padding: 10px; font-size: 14px; font-weight: bold; } QPushButton:hover { background: #45a049; }");
    connect(generateInventoryBtn, &QPushButton::clicked, this, &ReportsScreen::generateInventoryReport);
    
    exportInventoryBtn = new QPushButton("Export");
    exportInventoryBtn->setStyleSheet("QPushButton { background: #2196F3; color: white; border: none; border-radius: 8px; padding: 10px; font-size: 14px; font-weight: bold; } QPushButton:hover { background: #1976D2; }");
    connect(exportInventoryBtn, &QPushButton::clicked, this, &ReportsScreen::exportReport);
    
    printInventoryBtn = new QPushButton("Print");
    printInventoryBtn->setStyleSheet("QPushButton { background: #FF9800; color: white; border: none; border-radius: 8px; padding: 10px; font-size: 14px; font-weight: bold; } QPushButton:hover { background: #F57C00; }");
    connect(printInventoryBtn, &QPushButton::clicked, this, &ReportsScreen::printReport);
    
    inventoryControlsLayout->addWidget(categoryLabel);
    inventoryControlsLayout->addWidget(inventoryCategoryCombo);
    inventoryControlsLayout->addStretch();
    inventoryControlsLayout->addWidget(generateInventoryBtn);
    inventoryControlsLayout->addWidget(exportInventoryBtn);
    inventoryControlsLayout->addWidget(printInventoryBtn);
    
    inventoryTabLayout->addLayout(inventoryControlsLayout);
    inventoryTabLayout->addWidget(inventoryTable);
    
    tabWidget->addTab(salesTab, "Sales Report");
    tabWidget->addTab(inventoryTab, "Inventory Report");
    
    mainLayout->addWidget(tabWidget);
    
    refreshReports();
}

void ReportsScreen::setupSummaryCards() {
    // This method is called in the constructor to set up summary cards
    // The actual setup is done inline in the constructor for better organization
}

void ReportsScreen::setupSalesReport() {
    salesTable = new QTableWidget;
    salesTable->setColumnCount(5);
    salesTable->setHorizontalHeaderLabels({"Date", "Total Sales", "Orders", "Avg Order", "Top Product"});
    salesTable->setStyleSheet("QTableWidget { background: #2d313a; border: 2px solid #444; border-radius: 8px; color: white; gridline-color: #444; } QHeaderView::section { background: #3a3f4b; color: white; padding: 8px; border: none; } QTableWidget::item { padding: 8px; }");
    salesTable->horizontalHeader()->setStretchLastSection(true);
    salesTable->setAlternatingRowColors(true);
    salesTable->setMinimumHeight(300);
}

void ReportsScreen::setupInventoryReport() {
    inventoryTable = new QTableWidget;
    inventoryTable->setColumnCount(5);
    inventoryTable->setHorizontalHeaderLabels({"Category", "Total Items", "Low Stock", "Total Value", "Most Expensive"});
    inventoryTable->setStyleSheet("QTableWidget { background: #2d313a; border: 2px solid #444; border-radius: 8px; color: white; gridline-color: #444; } QHeaderView::section { background: #3a3f4b; color: white; padding: 8px; border: none; } QTableWidget::item { padding: 8px; }");
    inventoryTable->horizontalHeader()->setStretchLastSection(true);
    inventoryTable->setAlternatingRowColors(true);
    inventoryTable->setMinimumHeight(300);
}

void ReportsScreen::loadSampleData() {
    // This method is no longer used - all data comes from user interactions
    salesData.clear();
    inventoryData.clear();
}

void ReportsScreen::generateSalesReport() {
    if (salesData.isEmpty()) {
        QMessageBox::information(this, "No Data", "No sales data available. Make some sales first!");
        return;
    }
    
    salesTable->setRowCount(salesData.size());
    
    for (int i = 0; i < salesData.size(); ++i) {
        const SalesReport &report = salesData[i];
        
        salesTable->setItem(i, 0, new QTableWidgetItem(report.date));
        salesTable->setItem(i, 1, new QTableWidgetItem(QString("$%1").arg(report.totalSales, 0, 'f', 2)));
        salesTable->setItem(i, 2, new QTableWidgetItem(QString::number(report.totalOrders)));
        salesTable->setItem(i, 3, new QTableWidgetItem(QString("$%1").arg(report.averageOrderValue, 0, 'f', 2)));
        salesTable->setItem(i, 4, new QTableWidgetItem(QString("%1 (%2 sold)").arg(report.topProduct).arg(report.topProductQuantity)));
    }
    
    QMessageBox::information(this, "Success", "Sales report generated successfully!");
}

void ReportsScreen::generateInventoryReport() {
    if (inventoryData.isEmpty()) {
        QMessageBox::information(this, "No Data", "No inventory data available. Add some products first!");
        return;
    }
    
    inventoryTable->setRowCount(inventoryData.size());
    
    for (int i = 0; i < inventoryData.size(); ++i) {
        const InventoryReport &report = inventoryData[i];
        
        inventoryTable->setItem(i, 0, new QTableWidgetItem(report.category));
        inventoryTable->setItem(i, 1, new QTableWidgetItem(QString::number(report.totalItems)));
        
        QTableWidgetItem *lowStockItem = new QTableWidgetItem(QString::number(report.lowStockItems));
        if (report.lowStockItems > 0) {
            lowStockItem->setForeground(QColor("#F44336"));
        }
        inventoryTable->setItem(i, 2, lowStockItem);
        
        inventoryTable->setItem(i, 3, new QTableWidgetItem(QString("$%1").arg(report.totalValue, 0, 'f', 2)));
        inventoryTable->setItem(i, 4, new QTableWidgetItem(report.mostExpensiveItem));
    }
    
    QMessageBox::information(this, "Success", "Inventory report generated successfully!");
}

void ReportsScreen::exportReport() {
    QString currentTab = tabWidget->tabText(tabWidget->currentIndex());
    QMessageBox::information(this, "Export", QString("Exporting %1 report...\n\nThis would save the report to a file in a real application.").arg(currentTab));
}

void ReportsScreen::printReport() {
    QString currentTab = tabWidget->tabText(tabWidget->currentIndex());
    QMessageBox::information(this, "Print", QString("Printing %1 report...\n\nThis would open the print dialog in a real application.").arg(currentTab));
}

void ReportsScreen::refreshReports() {
    // Update summary cards with latest data from user interactions
    // For now, we'll keep the zero values until data is added through sales/inventory
    totalRevenueLabel->setText("$0.00");
    totalOrdersLabel->setText("0");
    averageOrderLabel->setText("$0.00");
    topProductLabel->setText("No data");
} 