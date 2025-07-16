#include "BillDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QDateTime>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QHBoxLayout>
#include <QFont>
#include <QFileDialog>

BillDialog::BillDialog(const Bill& bill, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Receipt / Bill");
    setMinimumWidth(400);
    setupUI(bill);
}

void BillDialog::setupUI(const Bill& bill) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    headerLabel = new QLabel("<b>Monster POS Receipt</b>", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(headerLabel);

    infoLabel = new QLabel(QString("%1%2Date: %3  Time: %4<br>Cashier: %5")
        .arg(bill.saleId != -1 ? QString("Sale ID: %1<br>").arg(bill.saleId) : "")
        .arg("")
        .arg(bill.dateTime.date().toString("yyyy-MM-dd"))
        .arg(bill.dateTime.time().toString("hh:mm:ss"))
        .arg(bill.cashier), this);
    layout->addWidget(infoLabel);

    itemsTable = new QTableWidget(bill.items.size(), 4, this);
    itemsTable->setHorizontalHeaderLabels({"Name", "Qty", "Price", "Total"});
    itemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    itemsTable->verticalHeader()->setVisible(false);
    itemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int i = 0; i < bill.items.size(); ++i) {
        const BillItem& item = bill.items[i];
        itemsTable->setItem(i, 0, new QTableWidgetItem(item.name));
        itemsTable->setItem(i, 1, new QTableWidgetItem(QString::number(item.quantity)));
        itemsTable->setItem(i, 2, new QTableWidgetItem(QString::number(item.price, 'f', 2)));
        itemsTable->setItem(i, 3, new QTableWidgetItem(QString::number(item.total(), 'f', 2)));
    }
    layout->addWidget(itemsTable);

    summaryLabel = new QLabel(QString(
        "<hr>Subtotal: %1<br>Tax (%2%): %3<br><b>Total: %4</b><br>Paid: %5<br>Change: %6")
        .arg(QString::number(bill.subtotal(), 'f', 2))
        .arg(int(bill.taxRate * 100))
        .arg(QString::number(bill.tax(), 'f', 2))
        .arg(QString::number(bill.total(), 'f', 2))
        .arg(QString::number(bill.paid, 'f', 2))
        .arg(QString::number(bill.change, 'f', 2)), this);
    layout->addWidget(summaryLabel);

    // Print, Export PDF, and Close buttons
    QHBoxLayout* btnLayout = new QHBoxLayout;
    printButton = new QPushButton("Print", this);
    connect(printButton, &QPushButton::clicked, this, &BillDialog::printBill);
    btnLayout->addWidget(printButton);
    exportPdfButton = new QPushButton("Export PDF", this);
    connect(exportPdfButton, &QPushButton::clicked, this, &BillDialog::exportPdf);
    btnLayout->addWidget(exportPdfButton);
    closeButton = new QPushButton("Close", this);
    connect(closeButton, &QPushButton::clicked, this, &BillDialog::accept);
    btnLayout->addWidget(closeButton);
    layout->addLayout(btnLayout);
}

void BillDialog::printBill() {
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Print Bill");
    if (dialog.exec() != QDialog::Accepted)
        return;
    QPainter painter(&printer);
    int y = 100;
    int x = 100;
    int lineHeight = 30;
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    painter.drawText(x, y, "Monster POS Receipt");
    y += lineHeight * 2;
    painter.drawText(x, y, infoLabel->text().replace("<br>", " ").replace("<b>", "").replace("</b>", ""));
    y += lineHeight * 2;
    painter.drawText(x, y, "Items:");
    y += lineHeight;
    painter.drawText(x, y, "Name         Qty   Price   Total");
    y += lineHeight;
    for (int i = 0; i < itemsTable->rowCount(); ++i) {
        QString name = itemsTable->item(i, 0)->text();
        QString qty = itemsTable->item(i, 1)->text();
        QString price = itemsTable->item(i, 2)->text();
        QString total = itemsTable->item(i, 3)->text();
        painter.drawText(x, y, QString("%1   %2   %3   %4").arg(name, -12).arg(qty, -4).arg(price, -6).arg(total, -6));
        y += lineHeight;
    }
    y += lineHeight;
    painter.drawText(x, y, summaryLabel->text().replace("<br>", " ").replace("<b>", "").replace("</b>", "").replace("<hr>", "----------------------"));
    painter.end();
}

void BillDialog::exportPdf() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Bill as PDF", "receipt.pdf", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    QPainter painter(&printer);
    int x = 100, y = 100, lineHeight = 30;
    painter.setFont(QFont("Arial", 12));
    painter.drawText(x, y, "Monster POS Receipt");
    y += lineHeight;
    painter.drawText(x, y, infoLabel->text().replace("<br>", " ").replace("<b>", "").replace("</b>", ""));
    y += lineHeight;
    painter.drawText(x, y, "----------------------------------------");
    y += lineHeight;
    painter.drawText(x, y, "Name         Qty   Price   Total");
    y += lineHeight;
    for (int i = 0; i < itemsTable->rowCount(); ++i) {
        QString name = itemsTable->item(i, 0)->text();
        QString price = itemsTable->item(i, 1)->text();
        QString qty = itemsTable->item(i, 2)->text();
        QString total = itemsTable->item(i, 3)->text();
        painter.drawText(x, y, QString("%1   %2   %3   %4").arg(name, -10).arg(qty, -4).arg(price, -7).arg(total));
        y += lineHeight;
    }
    y += lineHeight;
    painter.drawText(x, y, summaryLabel->text().replace("<br>", " ").replace("<b>", "").replace("</b>", "").replace("<hr>", "----------------------"));
    painter.end();
} 