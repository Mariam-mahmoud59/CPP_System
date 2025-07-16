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
#include <QSqlQuery>
#include <QFileDialog>
#include <QProcess>
#include <QDir>
#include <QProcessEnvironment>
#include <QSqlError>
#include <QDebug>

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

    // Backup Button
    backupBtn = new QPushButton("Backup Data");
    backupBtn->setStyleSheet("QPushButton { background: #607D8B; color: white; border: none; border-radius: 8px; padding: 10px; font-size: 14px; font-weight: bold; } QPushButton:hover { background: #455A64; }");
    connect(backupBtn, &QPushButton::clicked, this, &ReportsScreen::backupDatabase);
    mainLayout->addWidget(backupBtn, 0, Qt::AlignRight);

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
    cashierCombo = new QComboBox;
    cashierCombo->setStyleSheet("QComboBox { padding: 8px; border: 2px solid #444; border-radius: 6px; background: #2d313a; color: white; font-size: 14px; }");
    cashierCombo->addItem("All Cashiers");
    cashierCombo->setVisible(false); // Only show for admins
    
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
    salesControlsLayout->addWidget(cashierCombo);
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

    // Activity Log Tab
    QWidget *activityTab = new QWidget;
    QVBoxLayout *activityLayout = new QVBoxLayout(activityTab);
    activityLogTable = new QTableWidget;
    activityLogTable->setColumnCount(4);
    activityLogTable->setHorizontalHeaderLabels({"User", "Action", "Details", "Timestamp"});
    activityLogTable->setStyleSheet("QTableWidget { background: #2d313a; border: 2px solid #444; border-radius: 8px; color: white; gridline-color: #444; } QHeaderView::section { background: #3a3f4b; color: white; padding: 8px; border: none; } QTableWidget::item { padding: 8px; }");
    activityLogTable->horizontalHeader()->setStretchLastSection(true);
    activityLogTable->setAlternatingRowColors(true);
    activityLogTable->setMinimumHeight(200);
    activityLayout->addWidget(activityLogTable);
    QPushButton *refreshLogBtn = new QPushButton("Refresh Log");
    refreshLogBtn->setStyleSheet("QPushButton { background: #607D8B; color: white; border: none; border-radius: 8px; padding: 8px; font-size: 13px; font-weight: bold; } QPushButton:hover { background: #455A64; }");
    connect(refreshLogBtn, &QPushButton::clicked, this, &ReportsScreen::refreshActivityLog);
    activityLayout->addWidget(refreshLogBtn, 0, Qt::AlignRight);
    tabWidget->addTab(activityTab, "Activity Log");
    refreshActivityLog();
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

void ReportsScreen::setUserRole(const QString& role) {
    userRole = role;
    updateCashierFilter();
}

void ReportsScreen::setUsername(const QString& uname) {
    username = uname;
}

void ReportsScreen::updateCashierFilter() {
    if (userRole == "admin") {
        cashierCombo->setVisible(true);
        cashierCombo->clear();
        cashierCombo->addItem("All Cashiers");
        QSqlQuery q("SELECT username FROM users WHERE role = 'cashier'");
        while (q.next()) {
            cashierCombo->addItem(q.value(0).toString());
        }
    } else {
        cashierCombo->setVisible(false);
    }
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
    // Log export
    logActivity(username, "Export Report", "Report exported by user");
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

void ReportsScreen::backupDatabase() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Database Backup", QDir::homePath() + "/MonsterDB_backup.sql", "SQL Files (*.sql)");
    if (fileName.isEmpty()) return;

    // Adjust these as needed for your environment
    QString pgDumpPath = "pg_dump"; // Assumes pg_dump is in PATH
    QString dbName = "MonsterDB";
    QString user = "postgres";
    QString host = "localhost";
    QString port = "5432";
    QString password = "Monsterxd2005@#@#";

    // Set PGPASSWORD env variable for non-interactive password passing
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PGPASSWORD", password);

    QStringList args;
    args << "-h" << host << "-p" << port << "-U" << user << "-F" << "p" << "-f" << fileName << dbName;

    QProcess process;
    process.setProcessEnvironment(env);
    process.start(pgDumpPath, args);
    if (!process.waitForStarted()) {
        QMessageBox::critical(this, "Backup Failed", "Could not start pg_dump. Make sure PostgreSQL tools are installed and in your PATH.");
        return;
    }
    process.waitForFinished(-1);
    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
        QMessageBox::information(this, "Backup Complete", "Database backup was created successfully!\n\n" + fileName);
        // Log backup action
        logActivity(userRole, "Backup Database", fileName);
    } else {
        QString err = process.readAllStandardError();
        QMessageBox::critical(this, "Backup Failed", "pg_dump failed.\n\n" + err);
    }
}

void ReportsScreen::logActivity(const QString& username, const QString& action, const QString& details) {
    QSqlQuery q;
    q.prepare("INSERT INTO activity_log (username, action, details) VALUES (?, ?, ?)");
    q.addBindValue(username);
    q.addBindValue(action);
    q.addBindValue(details);
    if (!q.exec()) {
        qDebug() << "Failed to log activity:" << q.lastError().text();
    }
}

void ReportsScreen::refreshActivityLog() {
    activityLogTable->setRowCount(0);
    QSqlQuery q("SELECT username, action, details, timestamp FROM activity_log ORDER BY timestamp DESC LIMIT 100");
    int row = 0;
    while (q.next()) {
        activityLogTable->insertRow(row);
        for (int col = 0; col < 4; ++col) {
            activityLogTable->setItem(row, col, new QTableWidgetItem(q.value(col).toString()));
        }
        ++row;
    }
} 