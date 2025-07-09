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

struct Product {
    QString name;
    QString category;
    double price;
    int quantity;
    int minStock;
    QString description;
};

class AddProductDialog : public QDialog {
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
public:
    InventoryScreen(QWidget *parent = nullptr);

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