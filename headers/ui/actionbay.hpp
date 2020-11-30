#ifndef __SIGABRT_NOTES_ACTIONBAY__
#define __SIGABRT_NOTES_ACTIONBAY__

#include <optional>

#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QKeySequence>

#include <ui/constants.hpp>

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
        
        QString getCss();
        void setLightIcon(Action&);
        void setDarkIcon(Action&);
        void initAction(Action&);
        
    public:
        ActionBay(
            QWidget* parent, 
            const std::vector<std::pair<QString, ActionInfo>>& buttonLabels,
            AppUI::Mode mode
        );        
        std::unique_ptr<QAction>& getButton(const QString& buttonLabel);
    };
}

#endif
