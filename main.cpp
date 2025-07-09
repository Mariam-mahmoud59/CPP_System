#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // --- PostgreSQL Connection Setup ---
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");           // <-- Replace if needed
    db.setPort(5432);                      // <-- Replace if needed
    db.setDatabaseName("MonsterDB");       // <-- Replace with your DB name
    db.setUserName("postgres");            // <-- Replace with your username
    db.setPassword("Monsterxd2005@#@#");       // <-- Replace with your password

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return -1; // Exit if DB connection fails
    } else {
        qDebug() << "Connected to PostgreSQL!";
    }

    MainWindow w;
    w.show();
    return app.exec();
}