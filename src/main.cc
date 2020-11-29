#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QIcon>

#include <ui/mainwindow.hpp>
#include <backend/notesdao.hpp>

int main(int argc, char* argv[]) {
    AppBackend::LocalDAO dao;
    
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    AppUI::MainWindow window {700, 500, dao};
    window.setWindowTitle("Simple example");
    window.show();
    app.exec();
}
