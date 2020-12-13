#ifndef __SIGABRT_NOTES_ACTIONBAY__
#define __SIGABRT_NOTES_ACTIONBAY__

#include <optional>

#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QKeySequence>

#include <ui/constants.hpp>
#include <ui/models.hpp>

namespace AppUI {
    

    class ActionBay: public QToolBar {
    private:
        const QString CSS_TEMPLATE {
            "QToolBar {background-color: %1; border: none; } "
            "QToolButton {"
            "height: 30px; "
            "width: 30px; "
            "margin-right: 8px; "
            "qproperty-iconSize: 24px;"
            "} "
            "QToolButton:checked {"
            "border: 2px solid %2; "
            "border-radius: 3px;"
            "} "
            "QToolButton:!checked {"
            "} "
            "QToolButton:hover {"
            "border: 1px solid %2; "
            "border-radius: 3px;"
            "} "
            "QToolButton:pressed {"
            "border: 2px solid %2; "
            "border-radius: 2px;"
            "} "
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
            AppUI::Mode mode,
            const QString& accent
        );        
        
        QAction& getButton(const QString& buttonLabel);
    };
}

#endif
