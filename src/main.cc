#include <iostream>

#include <QApplication>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>
#include <QFontDatabase>

#include <ui/notesmainwindow.hpp>
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

    void loadFonts() {
        QFontDatabase::addApplicationFont(":/resources/fonts/Ubuntu-Bold.ttf");
        QFontDatabase::addApplicationFont(":/resources/fonts/Ubuntu-Regular.ttf");
        QFontDatabase::addApplicationFont(":/resources/fonts/Ubuntu-Italic.ttf");
        QFontDatabase::addApplicationFont(":/resources/fonts/Ubuntu-BoldItalic.ttf");
        QFontDatabase::addApplicationFont(":/resources/fonts/UbuntuCondensed-Regular.ttf");
    }
}



int main(int argc, char* argv[]) {
    

    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    // Initialize data and resources for application
    initWorkingDirectory();
    AppBackend::LocalDAO dao {getDatabase()};
    loadFonts();
    
    AppUI::NotesMainWindow window {700, 500, dao, AppUI::Mode::DARK, AppUI::Colours::BLUE};
    window.setWindowTitle("Notes");
    window.show();
    app.exec();
}
