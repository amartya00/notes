#ifndef __SIGABRT_NOTES_UI_MODELS__
#define __SIGABRT_NOTES_UI_MODELS__

#include <QListWidgetItem>
#include <QString>

namespace AppUI {
    class NoteListItem : public QListWidgetItem {
    public:
        const long id;
        NoteListItem(const long id, const QString& text): 
            QListWidgetItem(text),
            id {id} {
                
            }
    };

    struct ActionInfo {
        QString lightIconPath;
        QString darkIconPath;
        bool checkable;
        std::optional<QKeySequence> shortcut;
    };

    struct Action {
        ActionInfo info;
        // Using a pointer instead of a stack allocated button because the deleted copy constructor
        // and lack of default constructor makes it incompatible as a value in hash map.
        std::unique_ptr<QAction> button {nullptr};
    };
}

#endif
