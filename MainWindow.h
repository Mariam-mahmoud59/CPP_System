#pragma once
#include <QMainWindow>
class DashboardScreen;
class SalesScreen;
class InventoryScreen;
class ReportsScreen;

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); // Only declaration
private:
    DashboardScreen *dashboardScreen;
    SalesScreen *salesScreen;
    InventoryScreen *inventoryScreen;
    ReportsScreen *reportsScreen;
}; 