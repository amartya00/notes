#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QIcon>

#include <ui/mainwindow.hpp>

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    AppUI::MainWindow window {700, 500};
    window.setWindowTitle("Simple example");
    window.show();
    app.exec();
}
