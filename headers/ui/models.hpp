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
}

#endif
