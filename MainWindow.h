#pragma once
#include <QMainWindow>
class DashboardScreen;
class SalesScreen;
class InventoryScreen;
class ReportsScreen;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); // Only declaration
    void setUserRole(const QString& role);
    void setUsername(const QString& username); // Set current user
private:
    DashboardScreen *dashboardScreen;
    SalesScreen *salesScreen;
    InventoryScreen *inventoryScreen;
    ReportsScreen *reportsScreen;
    QString userRole;
    QString username; // Current user
}; 