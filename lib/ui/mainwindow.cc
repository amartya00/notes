#include <memory>
#include <map>
#include <utility>
#include <random>

#include <QWidget>
#include <QGridLayout>
#include <QTextDocument>
#include <QTextEdit>
#include <QString>
#include <QFrame>
#include <QPushButton>
#include <QTextCursor>
#include <QKeySequence>

#include <ui/actionbay.hpp>
#include <ui/constants.hpp>
#include <ui/textbox.hpp>
#include <ui/itemlist.hpp>

#include <backend/notesdao.hpp>
#include <ui/mainwindow.hpp>
#include <ui/models.hpp>

void AppUI::MainWindow::connectTextBoxToolbar() noexcept {
    connect(&noteList, &NoteSidebar::noteSelected, &wordProcessor, &WordProcessor::refreshContent);
    connect(&noteList, &NoteSidebar::noteDeleted, &wordProcessor, &WordProcessor::refreshContent);
    connect(&noteList, &NoteSidebar::newNoteCreated, &wordProcessor, &WordProcessor::refreshContent);
    connect(&wordProcessor, &WordProcessor::noteSaved, &noteList, &NoteSidebar::updateView);
}

QString AppUI::MainWindow::getCss() const noexcept {
    return CSS_TEMPLATE.arg(mode == AppUI::Mode::DARK ? AppUI::Colours::VERY_DARK_GRAY : AppUI::Colours::WHITE);
}

AppBackend::Note AppUI::MainWindow::newNote() const noexcept {
    return AppBackend::Note {
        dao.genRandomId(),
        "Untitled note",
        "Untitled note\n"
    };
}

AppUI::MainWindow::MainWindow(
    const std::size_t initWidth,
    const std::size_t initHeight,
    AppBackend::LocalDAO& dao,
    const AppUI::Mode& mode,
    const QString& accent):
    dao {dao},
    mode {mode},
    mainGrid {this},
    wordProcessor {this, iconMap, dao, mode, accent},
    noteList {this, iconMap, dao, mode, accent} {
        setStyleSheet(getCss());
        connectTextBoxToolbar();
        
        // Select the first note
        wordProcessor.refreshContent(dao.listRecords()[0]);
        
        mainGrid.addLayout(&noteList, 0, 0);
        mainGrid.addLayout(&wordProcessor, 0, 1);
        setLayout(&mainGrid);
        this->resize(initWidth, initHeight);
}
