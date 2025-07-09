#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QVariant>
#include <QDebug>

struct Product {
    int id = -1; // Add id for DB mapping
    QString name;
    QString category;
    double price;
    int quantity;
    int minStock;
    QString description;
};

class AddProductDialog : public QDialog {
    Q_OBJECT
public:
    AddProductDialog(QWidget *parent = nullptr);
    Product getProduct() const;

private:
    QLineEdit *nameEdit;
    QLineEdit *categoryEdit;
    QDoubleSpinBox *priceSpinBox;
    QSpinBox *quantitySpinBox;
    QSpinBox *minStockSpinBox;
    QLineEdit *descriptionEdit;
};

class InventoryScreen : public QWidget {
    Q_OBJECT
public:
    InventoryScreen(QWidget *parent = nullptr);
    QList<Product> getProducts() const;
    void loadProductsFromDatabase();

signals:
    void inventoryChanged();

private slots:
    void addProduct();
    void editProduct();
    void deleteProduct();
    void searchProducts();
    void refreshInventory();

private:
    void setupInventoryTable();
    void loadSampleData();
    void updateLowStockIndicator();
    
    QTableWidget *inventoryTable;
    QLineEdit *searchBox;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *refreshButton;
    QLabel *totalProductsLabel;
    QLabel *lowStockLabel;
    
    QList<Product> products;
}; 