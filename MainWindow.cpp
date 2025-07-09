#include "MainWindow.h"
#include "DashboardScreen.h"
#include "SalesScreen.h"
#include "InventoryScreen.h"
#include "ReportsScreen.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QStyleFactory>
#include <QApplication>
#include <QObject>
#include <QColor>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    // Sidebar
    QWidget *sidebar = new QWidget;
    sidebar->setFixedWidth(180);
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setSpacing(20);
    sidebarLayout->setContentsMargins(20, 40, 20, 20);

    QPushButton *dashboardBtn = new QPushButton("Dashboard");
    QPushButton *salesBtn = new QPushButton("Sales");
    QPushButton *inventoryBtn = new QPushButton("Inventory");
    QPushButton *reportsBtn = new QPushButton("Reports");
    dashboardBtn->setMinimumHeight(40);
    salesBtn->setMinimumHeight(40);
    inventoryBtn->setMinimumHeight(40);
    reportsBtn->setMinimumHeight(40);
    sidebarLayout->addWidget(dashboardBtn);
    sidebarLayout->addWidget(salesBtn);
    sidebarLayout->addWidget(inventoryBtn);
    sidebarLayout->addWidget(reportsBtn);
    sidebarLayout->addStretch();
    sidebar->setLayout(sidebarLayout);
    sidebar->setStyleSheet("background:#23272e;border-radius:10px;");

    // Screens
    dashboardScreen = new DashboardScreen;
    salesScreen = new SalesScreen;
    inventoryScreen = new InventoryScreen;
    reportsScreen = new ReportsScreen;

    QStackedWidget *stack = new QStackedWidget;
    stack->addWidget(dashboardScreen);
    stack->addWidget(salesScreen);
    stack->addWidget(inventoryScreen);
    stack->addWidget(reportsScreen);

    QObject::connect(dashboardBtn, &QPushButton::clicked, [stack](){ stack->setCurrentIndex(0); });
    QObject::connect(salesBtn, &QPushButton::clicked, [stack](){ stack->setCurrentIndex(1); });
    QObject::connect(inventoryBtn, &QPushButton::clicked, [stack](){ stack->setCurrentIndex(2); });
    QObject::connect(reportsBtn, &QPushButton::clicked, [stack](){ stack->setCurrentIndex(3); });

    // Connect inventory changes to sales screen
    QObject::connect(inventoryScreen, &InventoryScreen::inventoryChanged, salesScreen, &SalesScreen::onInventoryChanged);

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stack, 1);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    setCentralWidget(central);
    setWindowTitle("POS System");
    resize(900, 600);

    // Dark theme styling
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(40, 44, 52));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(30, 34, 40));
    darkPalette.setColor(QPalette::AlternateBase, QColor(40, 44, 52));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(50, 54, 62));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    qApp->setPalette(darkPalette);
    setStyleSheet("QMainWindow { background: #282c34; } QLabel { color: #fff; font-size: 20px; } QPushButton { color: #fff; background: #2d313a; border: none; border-radius: 8px; font-size: 16px; } QPushButton:hover { background: #3a3f4b; }");
}

MainWindow::~MainWindow() {} 