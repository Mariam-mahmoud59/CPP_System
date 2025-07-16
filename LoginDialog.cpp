#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("User Login");
    setModal(true);
    setMinimumWidth(300);
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* userLabel = new QLabel("Username:", this);
    usernameEdit = new QLineEdit(this);
    QLabel* passLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login", this);
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::tryLogin);
    layout->addWidget(userLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);
}

QString LoginDialog::getUsername() const { return usernameEdit->text(); }
QString LoginDialog::getPassword() const { return passwordEdit->text(); }

void LoginDialog::tryLogin() {
    if (usernameEdit->text().isEmpty() || passwordEdit->text().isEmpty()) {
        emit loginFailed("Please enter both username and password.");
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
        return;
    }
    accept();
} 