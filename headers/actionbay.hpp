#ifndef __SIGABRT_NOTES_ACTIONBAY__
#define __SIGABRT_NOTES_ACTIONBAY__

#include <optional>

#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QKeySequence>

#include <constants.hpp>

namespace AppUI {
    struct ActionInfo {
        QString lightIconPath;
        QString darkIconPath;
        bool checkable;
        std::optional<QKeySequence> shortcut;
    };

    class ActionBay: public QToolBar {
    private:
        struct Action {
            ActionInfo info;
            std::unique_ptr<QAction> button;
        };
        
        std::unordered_map<QString, Action> buttons;
        AppUI::Mode mode;
        QString accent;
        
        QString getCss() {
            return QString {
                "QToolButton {"
                "height: 30px; "
                "width: 30px; "
                "margin-right: 8px; "
                "} "
                "QToolButton:checked {"
                
                "border: 2px solid " + accent + "; "
                "border-radius: 3px;"
                "} "
                "QToolButton:!checked {"
                "border: 1px solid " + accent + "; "
                "border-radius: 2px;"
                "} "
            };
        }
        
        void setLightIcon(Action& action) {
            QPixmap pixmap(action.info.lightIconPath);
            QIcon icon(pixmap);
            action.button->setIcon(icon);
            action.button->setIconVisibleInMenu(true);
        }
        
        void setDarkIcon(Action& action) {
            QPixmap pixmap(action.info.darkIconPath);
            QIcon icon(pixmap);
            action.button->setIcon(icon);
        }
        
        void initAction(Action& action) {
            mode == AppUI::Mode::DARK? setDarkIcon(action) : setLightIcon(action);
            action.button->setCheckable(action.info.checkable);
            if (action.info.shortcut != std::nullopt) {
                action.button->setShortcut(*action.info.shortcut);
            }
        }
        
    public:
        ActionBay(
            QWidget* parent, 
            const std::vector<std::pair<QString, ActionInfo>>& buttonLabels,
            AppUI::Mode mode,
            const QString& accent
        ): mode {mode}, accent {accent} {
            // Populate the button map
            for(const auto& label : buttonLabels) {
                Action action {
                    label.second,
                    {std::make_unique<QAction>(parent)}
                };
                initAction(action);
                addAction(action.button.get());
                buttons[label.first] = std::move(action);
            }
            // Set the stylesheet
            setStyleSheet(getCss());
        }
        
        std::unique_ptr<QAction>& getButton(const QString& buttonLabel) {
            return buttons.at(buttonLabel).button;
        }
    };
}

#endif
