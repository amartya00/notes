#include <backend/notesdao.hpp>
#include <backend/models.hpp>
#include <ui/itemlist.hpp>
#include <ui/models.hpp>
#include <ui/constants.hpp>

namespace Colours = AppUI::Colours;
using AppUI::Mode;
using AppUI::ItemList;
using AppUI::NoteListItem;
using AppBackend::LocalDAO;
using AppBackend::Note;

QString ItemList::getCss() const noexcept {
    return CSS_TEMPLATE.arg(accent, Colours::BLACK, mode == Mode::DARK? Colours::WHITE : Colours::BLACK);
}

ItemList::ItemList(QWidget* parent, LocalDAO& dao, const Mode mode, const QString accent): 
    QListWidget(parent),
    mode {mode},
    accent {accent},
    dao {dao} {
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setStyleSheet(getCss());
}

void ItemList::updateView() noexcept {
    int current = currentRow();
    clear();
    const std::vector<long>& items {dao.listRecords()};
    for (auto id : items) {
        Note note {std::move(*dao.loadRecord(id))};
        QString text = "<h2>%1</h2></br><p>%2";
        addItem(new NoteListItem(note.id, text.arg(note.title, (*note.createTime).toString())));
    }
    setCurrentRow(current);
    update();
}

void ItemList::selectFirst() noexcept {
    setCurrentRow(0);
    update();
}

void ItemList::selectLast() noexcept {
    setCurrentRow(count()-1);
    update();
}

void ItemList::deleteSelected() {
    for (const QListWidgetItem* current : selectedItems()) {
        const AppUI::NoteListItem* itm {reinterpret_cast<const AppUI::NoteListItem*>(current)};
        long id {itm->id};
        dao.deleteRecord(id);
    }
    selectFirst();
}
