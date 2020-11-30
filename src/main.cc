#include <iostream>

#include <QApplication>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>

#include <ui/mainwindow.hpp>
#include <backend/notesdao.hpp>

namespace {
    const QDir root {
        QDir::cleanPath(
            QDir::homePath() +
            QDir::separator() +
            ".notes"
        )
    };
    
    void initWorkingDirectory() {
        if(!root.exists()) {
            qWarning() << "First run. Creating root folder " << root.absolutePath();
            root.mkdir(root.absolutePath());
        }
    }

    QSqlDatabase getDatabase() {
        const QString DRIVER {"QSQLITE"};
        
        const QDir databasePath {
            root.filePath("notes.db")
        };
        if(QSqlDatabase::isDriverAvailable(DRIVER)) {
            QSqlDatabase database {QSqlDatabase::addDatabase(DRIVER)};
            database.setDatabaseName(databasePath.absolutePath());
            if(!database.open()){
                throw std::runtime_error("Could not open database.");
            }
            return database;
        } else {
            throw std::runtime_error("SQLITE driver not available.");
        }
    }
}



int main(int argc, char* argv[]) {
    initWorkingDirectory();
    AppBackend::LocalDAO dao {getDatabase()};
    
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    AppUI::MainWindow window {700, 500, dao};
    window.setWindowTitle("Simple example");
    window.show();
    app.exec();
}
