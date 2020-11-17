#ifndef __SIGABRT_NOTES_ACTIONBAY__
#define __SIGABRT_NOTES_ACTIONBAY__

#include <optional>

#include <QWidget>
#include <QHBoxLayout>
#include <QString>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QKeySequence>

namespace AppUI {
    struct ActionInfo {
        QString iconPath;
        bool checkable;
        std::optional<QKeySequence> shortcut;
    };

    class ActionBay: public QToolBar {
    private:
        std::unordered_map<QString, std::unique_ptr<QAction>> buttons;
        // QSpacerItem (like any other QLayoutItem) is deleted by the layout itself. Hence no unique_ptr
        // https://forum.qt.io/topic/64234/how-does-qspaceritem-get-deleted
        
    public:
        ActionBay(QWidget* parent, const std::vector<std::pair<QString, ActionInfo>>& buttonLabels) {
            for(const auto& label : buttonLabels) {
                QPixmap pixmap(label.second.iconPath);
                QIcon icon(pixmap);
                auto button {std::make_unique<QAction>(icon, label.first, parent)};
                button->setCheckable(label.second.checkable);
                if (label.second.shortcut != std::nullopt) {
                    button-> setShortcut(*label.second.shortcut);
                }
                addAction(button.get());
                buttons[label.first] = std::move(button);
            }
        }
        
        std::unique_ptr<QAction>& getButton(const QString& buttonLabel) {
            return buttons.at(buttonLabel);
        }
    };
}

#endif
