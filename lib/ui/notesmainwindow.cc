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
#include <ui/notesmainwindow.hpp>
#include <ui/models.hpp>

using AppUI::NotesMainWindow;
using AppBackend::Note;

void NotesMainWindow::connectTextBoxToolbar() noexcept {
    connect(&noteList, &NoteSidebar::noteSelected, &wordProcessor, &WordProcessor::refreshContent);
    connect(&noteList, &NoteSidebar::noteDeleted, &wordProcessor, &WordProcessor::refreshContent);
    connect(&noteList, &NoteSidebar::newNoteCreated, &wordProcessor, &WordProcessor::refreshContent);
    connect(&wordProcessor, &WordProcessor::noteSaved, &noteList, &NoteSidebar::updateView);
}

QString NotesMainWindow::getCss() const noexcept {
    return CSS_TEMPLATE.arg(mode == AppUI::Mode::DARK ? AppUI::Colours::VERY_DARK_GRAY : AppUI::Colours::WHITE);
}

AppUI::NotesMainWindow::NotesMainWindow(
    const std::size_t initWidth,
    const std::size_t initHeight,
    AppBackend::LocalDAO& dao,
    const AppUI::Mode& mode,
    const QString& accent):
    mode {mode},
    mainGrid {this},
    wordProcessor {this, iconMap, dao, mode, accent},
    noteList {this, iconMap, dao, mode, accent} {
        setStyleSheet(getCss());
        connectTextBoxToolbar();
        
        // Select the first note
        wordProcessor.refreshContent(dao.listRecords()[0], false);
        
        mainGrid.addLayout(&noteList, 0, 0);
        mainGrid.addLayout(&wordProcessor, 0, 1);
        setLayout(&mainGrid);
        this->resize(initWidth, initHeight);
}
