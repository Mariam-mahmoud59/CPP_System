#ifndef BILL_H
#define BILL_H

#include <QString>
#include <QDateTime>
#include <QVector>

struct BillItem {
    QString name;
    int quantity;
    double price;
    double total() const { return quantity * price; }
};

class Bill {
public:
    QString cashier;
    QDateTime dateTime;
    QVector<BillItem> items;
    double taxRate = 0.1; // 10% default
    double paid = 0.0;
    double change = 0.0;

    double subtotal() const {
        double sum = 0.0;
        for (const auto& item : items) sum += item.total();
        return sum;
    }
    double tax() const { return subtotal() * taxRate; }
    double total() const { return subtotal() + tax(); }
};

#endif // BILL_H 