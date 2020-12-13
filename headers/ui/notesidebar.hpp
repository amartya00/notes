#ifndef __SIGABRT_NOTES_NOTESIDEBAR__
#define __SIGABRT_NOTES_NOTESIDEBAR__

#include <utility>

#include <QVBoxLayout>
#include <QWidget>

#include <ui/itemlist.hpp>
#include <ui/actionbay.hpp>
#include <ui/models.hpp>

#include <backend/notesdao.hpp>

namespace AppUI {
    class NoteSidebar : public QVBoxLayout {
        Q_OBJECT
    private:
        const QString newButtonLight;
        const QString newButtonDark;
        const QString deleteButtonLight;
        const QString deleteButtonDark;

        AppBackend::LocalDAO& dao;
        AppUI::ItemList notes;
        AppUI::ActionBay toolbar;

        std::vector<std::pair<QString, AppUI::ActionInfo>> generateToolbarStructs() const  noexcept;
        void connectInternal() noexcept;
        void createDefaultNoteIfEmpty();
        AppBackend::Note newNote() const noexcept;
    public:
        NoteSidebar(
            QWidget* parent,
            const std::unordered_map<QString, QString>& buttons,
            AppBackend::LocalDAO& dao,
            const AppUI::Mode mode,
            const QString& accent
        );
        ~NoteSidebar();
        void updateView() noexcept;

    signals:
        void newNoteCreated(const long noteId);
        void noteSelected(const long noteId);
        void noteDeleted(const long noteId);
    };
}

#endif
