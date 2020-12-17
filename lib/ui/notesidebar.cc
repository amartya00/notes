#include <QWidget>
#include <QVBoxLayout>

#include <ui/notesidebar.hpp>
#include <ui/constants.hpp>
#include <backend/notesdao.hpp>

#include <iostream>

namespace Colours = AppUI::Colours;
using AppUI::NoteSidebar;
using AppUI::Mode;
using AppBackend::LocalDAO;
using AppBackend::Note;

NoteSidebar::NoteSidebar(
    QWidget* parent,
    const std::unordered_map<QString, QString>& buttons,
    LocalDAO& dao,
    const Mode mode,
    const QString& accent
): 
    newButtonLight {buttons.at("NewButtonLight")},
    newButtonDark {buttons.at("NewButtonDark")},
    deleteButtonLight {buttons.at("DeleteButtonLight")},
    deleteButtonDark {buttons.at("DeleteButtonDark")},
    dao {dao},
    notes {parent, dao, mode, accent},
    toolbar {parent, generateToolbarStructs(), mode, accent} {
        addWidget(&notes);
        addWidget(&toolbar);
        createDefaultNoteIfEmpty();
        notes.updateView();
        notes.selectFirst();
        connectInternal();
}

NoteSidebar::~NoteSidebar() {
}

std::vector<std::pair<QString, AppUI::ActionInfo>> NoteSidebar::generateToolbarStructs() const  noexcept {
    return {
        {
            "new",
            {
                newButtonLight,
                newButtonDark,
                false,
                QKeySequence::New
            }
        },
        {
            "delete",
            {
                deleteButtonLight,
                deleteButtonDark,
                false,
                QKeySequence::Delete
            }
        }
    };
}

void NoteSidebar::connectInternal() noexcept {
    connect(
        &toolbar.getButton("new"), 
        &QAction::triggered, 
        &notes,
        [this]() {
            AppBackend::Note note {newNote()};
            dao.upsertRecord(note);
            notes.updateView();
            notes.selectLast();
            emit newNoteCreated(note.id, true);
        });
    connect(
        &notes, 
        &QListWidget::itemClicked, 
        &toolbar,
        [this](const QListWidgetItem* itm) {
            const AppUI::NoteListItem* listItm {reinterpret_cast<const AppUI::NoteListItem*>(itm)};
            emit noteSelected(listItm->id, true);
        });
    connect(
        &toolbar.getButton("delete"),
        &QAction::triggered,
        &notes,
        [this]() {
            notes.deleteSelected();
            createDefaultNoteIfEmpty();
            notes.updateView();
            notes.selectFirst();
            emit noteDeleted(dao.listRecords()[0], false);
        });
}

void NoteSidebar::updateView() noexcept {
    notes.updateView();
}

void NoteSidebar::createDefaultNoteIfEmpty() {
    if (dao.listRecords().size() == 0) {
        Note note {newNote()};
        dao.upsertRecord(note);
    }
}

Note NoteSidebar::newNote() const noexcept {
    return AppBackend::Note {
        dao.genRandomId(),
        QDateTime::currentDateTime(),
        "Untitled note",
        "Untitled note\n"
    };
}
