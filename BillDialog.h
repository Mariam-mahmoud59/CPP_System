#ifndef BILLDIALOG_H
#define BILLDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include "Bill.h"

class BillDialog : public QDialog {
    Q_OBJECT
public:
    explicit BillDialog(const Bill& bill, QWidget* parent = nullptr);
private:
    QLabel* headerLabel;
    QLabel* infoLabel;
    QTableWidget* itemsTable;
    QLabel* summaryLabel;
    QPushButton* printButton;
    QPushButton* closeButton;
    QPushButton* exportPdfButton;
    void setupUI(const Bill& bill);
private slots:
    void printBill();
    void exportPdf();
};

#endif // BILLDIALOG_H