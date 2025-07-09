#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QSpinBox>
#include <QComboBox>

struct CartItem {
    QString name;
    double price;
    int quantity;
    double total;
};

class SalesScreen : public QWidget {
public:
    SalesScreen(QWidget *parent = nullptr);
    void addProductToSales(const QString &name, double price, int quantity);
    void reloadProductsFromDatabase();

public slots:
    void onInventoryChanged();

private slots:
    void addToCart();
    void removeFromCart();
    void updateTotal();
    void processPayment();
    void clearCart();
    void searchProducts();

private:
    void setupProductList();
    void setupCart();
    void setupPayment();
    void updateCartTable();
    
    QListWidget *productList;
    QTableWidget *cartTable;
    QLineEdit *searchBox;
    QLabel *totalLabel;
    QLabel *taxLabel;
    QLabel *finalTotalLabel;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *clearButton;
    QPushButton *paymentButton;
    QSpinBox *quantitySpinBox;
    QComboBox *paymentMethodCombo;
    
    QList<CartItem> cartItems;
    double subtotal;
    double tax;
    double finalTotal;
}; 