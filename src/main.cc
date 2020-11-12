#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QIcon>

#include <mainwindow.hpp>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    AppUI::MainWindow window {700, 500};
    window.setWindowTitle("Simple example");
    window.show();

    return app.exec();
}
