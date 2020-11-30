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

#include <ui/buttonbay.hpp>
#include <ui/actionbay.hpp>
#include <ui/constants.hpp>
#include <ui/textbox.hpp>
#include <ui/itemlist.hpp>

#include <backend/notesdao.hpp>
#include <ui/mainwindow.hpp>
#include <ui/models.hpp>

void AppUI::MainWindow::connectTextBoxToolbar() {
    connect(actionBay->getButton("bold").get(), &QAction::toggled, textBox.get(), &AppUI::TextBox::boldSelection);
    connect(actionBay->getButton("italics").get(), &QAction::toggled, textBox.get(), &AppUI::TextBox::italicsSelection);
    connect(actionBay->getButton("underline").get(), &QAction::toggled, textBox.get(), &AppUI::TextBox::underlineSelection);
    connect(
        actionBay->getButton("h1").get(), 
        &QAction::toggled, 
        textBox.get(),
        [this](bool isSet) {
            if (isSet) {
                actionBay->getButton("h2")->setChecked(false);
                actionBay->getButton("h3")->setChecked(false);
                actionBay->getButton("p")->setChecked(false);
            } else {
                actionBay->getButton("p")->setChecked(true);
            }
            textBox->heading1Selection(isSet);
        });
    connect(
        actionBay->getButton("h2").get(), 
        &QAction::toggled, 
        textBox.get(),
        [this](bool isSet) {
            if (isSet) {
                actionBay->getButton("h1")->setChecked(false);
                actionBay->getButton("h3")->setChecked(false);
                actionBay->getButton("p")->setChecked(false);
            } else {
                actionBay->getButton("p")->setChecked(true);
            }
            textBox->heading2Selection(isSet);
        });
    connect(
        actionBay->getButton("h3").get(), 
        &QAction::toggled, 
        textBox.get(),
        [this](bool isSet) {
            if (isSet) {
                actionBay->getButton("h1")->setChecked(false);
                actionBay->getButton("h2")->setChecked(false);
                actionBay->getButton("p")->setChecked(false);
            } else {
                actionBay->getButton("p")->setChecked(true);
            }
            textBox->heading3Selection(isSet);
        });
    connect(
        actionBay->getButton("p").get(), 
        &QAction::toggled, 
        textBox.get(),
        [this](bool isSet) {
            if (isSet) {
                actionBay->getButton("h1")->setChecked(false);
                actionBay->getButton("h2")->setChecked(false);
                actionBay->getButton("h3")->setChecked(false);
            }
            textBox->pSelection();
        });
    connect(actionBay->getButton("save").get(), &QAction::triggered, textBox.get(), &AppUI::TextBox::save);
    connect(actionBay->getButton("save").get(), &QAction::triggered, noteList.get(), &AppUI::ItemList::updateView);
    connect(
        listActionBay->getButton("new").get(), 
        &QAction::triggered, 
        textBox.get(),
        [this]() {
            AppBackend::Note note {newNote()};
            dao.upsertRecord(note);
            textBox->refreshContent(note.id);
            noteList->updateView();
            noteList->selectLast();
        });
    connect(
        noteList.get(), 
        &QListWidget::itemClicked, 
        textBox.get(),
        [this](const QListWidgetItem* itm) {
            const AppUI::NoteListItem* listItm {reinterpret_cast<const AppUI::NoteListItem*>(itm)};
            textBox->refreshContent(listItm->id);
        });
    connect(
        listActionBay->getButton("delete").get(),
        &QAction::triggered, 
        textBox.get(),
        [this]() {
            noteList->deleteSelected();
            textBox->resetView();
        });
}

AppBackend::Note AppUI::MainWindow::newNote() const noexcept {
    qWarning() << "Generating new note.";
    return AppBackend::Note {
        dao.genRandomId(),
        "Untitled note",
        "Untitled note\n"
    };
}

AppBackend::Note AppUI::MainWindow::newNote() noexcept {
    qWarning() << "Generating new note.";
    return AppBackend::Note {
        dao.genRandomId(),
        "Untitled note",
        "Untitled note\n"
    };
}

AppUI::MainWindow::MainWindow(const std::size_t initWidth, const std::size_t initHeight, AppBackend::LocalDAO& dao): 
    dao {dao},
    mainGrid {std::make_unique<QGridLayout>(this)},
    textBox {std::make_unique<AppUI::TextBox>(this, dao)},
    actionBay {std::make_unique<AppUI::ActionBay>(this, toolbar, AppUI::Mode::DARK)},
    noteList {std::make_unique<AppUI::ItemList>(this, dao, AppUI::Colours::DARK_PINK)},
    listActionBay {std::make_unique<AppUI::ActionBay>(this, listToolbar, AppUI::Mode::DARK)} {
    
        connectTextBoxToolbar();
        
        textBox->resetView();
        noteList->updateView();
        noteList->selectFirst();

        mainGrid->addWidget(noteList.get(), 0, 0);
        mainGrid->addWidget(listActionBay.get(), 1, 0);
        mainGrid->addWidget(textBox.get(), 0, 1);
        mainGrid->addWidget(actionBay.get(), 1, 1);
        setLayout(mainGrid.get());
        this->setStyleSheet(AppUI::ButtonConstants::MAN_WINDOW_DARK_CSS);
        this->resize(initWidth, initHeight);
}
