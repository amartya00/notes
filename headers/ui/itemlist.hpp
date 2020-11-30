#ifndef __SIGABRT_NOTES_ITEMLIST__
#define __SIGABRT_NOTES_ITEMLIST__

#include <memory>
#include <vector>

#include <QListWidget>
#include <QListWidgetItem>
#include <QWidget>
#include <QStandardItemModel>
#include <QSizePolicy>
#include <QSpacerItem>

#include <backend/notesdao.hpp>
#include <backend/models.hpp>
#include <ui/constants.hpp>
#include <ui/models.hpp>

namespace AppUI {
    class ItemList : public QListWidget {
    private:
        QString accent;
        AppBackend::LocalDAO& dao;
        
        QString getCss() {
            return QString {
                "QListWidget {"
                "min-width: 200px;"
                "max-width: 200px;"
                "border: 0px solid; "
                "font-size: 20px;"
                "} "
                "QListWidget::item {"
                "height: 50px;"
                "width: 195px;"
                "border-bottom: 1px solid ; "
                "padding-bottom: 3px;"
                "}"
                "QListWidget::item:selected {"
                "border-bottom: 3px solid " + accent + ";"
                "color: " + accent + ";"
                "}"
            };
        }
        
    public :
        ItemList(QWidget* parent, AppBackend::LocalDAO& dao, const QString accent): 
            QListWidget(parent),
            accent {accent},
            dao {dao} {
            //accent = mode == AppUI::Mode::DARK? AppUI::Colours::WHITE : AppUI::Colours::GRAY;
            setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            setStyleSheet(getCss());
        }
        
        void updateView() {
            int current = currentRow();
            clear();
            const std::vector<long>& items {dao.listRecords()};
            for (auto id : items) {
                AppBackend::Note note {std::move(*dao.loadRecord(id))};
                addItem(new AppUI::NoteListItem(note.id, note.title));
            }
            setCurrentRow(current);
            update();
        }

        void selectFirst() {
            setCurrentRow(0);
            update();
        }

        void selectLast() {
            setCurrentRow(count()-1);
            update();
        }

        void deleteSelected() {
            for (const QListWidgetItem* current : selectedItems()) {
                const AppUI::NoteListItem* itm {reinterpret_cast<const AppUI::NoteListItem*>(current)};
                long id {itm->id};
                dao.deleteRecord(id);
            }
            updateView();
            selectFirst();
        }
    };
}

#endif
