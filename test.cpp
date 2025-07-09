#include <QApplication>
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow window;
    QLabel *label = new QLabel("Hello World!");
    window.setCentralWidget(label);
    window.show();
    return app.exec();
} 