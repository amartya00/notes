#ifndef __SIGABRT_NOTES_ITEMLIST__
#define __SIGABRT_NOTES_ITEMLIST__

#include <memory>
#include <vector>
#include <unordered_map>

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
        const QString CSS_TEMPLATE {
            "QListWidget {"
            "min-width: 200px;"
            "max-width: 200px;"
            "border: none; "
            "font-family: 'Ubuntu Condensed';"
            "font-size: 20px;"
            "font-weight: bold;"
            "text-align: center;"
            "} "
            "QListWidget::item {"
            "color: %3;"
            "height: 30px;"
            "width: 180px;"
            "border: none;"
            "text-align: center;"
            "margin-bottom: 5px;"
            "}"
            "QListWidget::item:selected {"
            "background: %1;"
            "color: %2;"
            "border: none;"
            "border-radius: 3px;"
            "text-align: center;"
            "margin-bottom: 5px;"
            "}"
        };
        AppUI::Mode mode;
        QString accent;
        AppBackend::LocalDAO& dao;
        QString getCss() const noexcept;
        
    public :
        ItemList(QWidget* parent, AppBackend::LocalDAO& dao, const AppUI::Mode mode, const QString accent);
        void updateView() noexcept;
        void selectFirst() noexcept;
        void selectLast() noexcept;
        void deleteSelected();
    };
}

#endif
