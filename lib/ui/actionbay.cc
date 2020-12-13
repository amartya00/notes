#include <optional>

#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QKeySequence>

#include <ui/constants.hpp>
#include <ui/actionbay.hpp>
#include <ui/models.hpp>

using AppUI::ActionBay;
using AppUI::ActionInfo;
using AppUI::Action;
        
QString ActionBay::getCss() {
    return CSS_TEMPLATE.arg(
        mode == AppUI::Mode::DARK? AppUI::Colours::VERY_DARK_GRAY : AppUI::Colours::WHITE,
        accent
    );
}
        
void ActionBay::setLightIcon(Action& action) {
    QPixmap pixmap(action.info.lightIconPath);
    QIcon icon(pixmap);
    action.button->setIcon(icon);
    action.button->setIconVisibleInMenu(true);
}

void ActionBay::setDarkIcon(Action& action) {
    QPixmap pixmap(action.info.darkIconPath);
    QIcon icon(pixmap);
    action.button->setIcon(icon);
}

void ActionBay::initAction(Action& action) {
    mode == AppUI::Mode::DARK? setDarkIcon(action) : setLightIcon(action);
    action.button->setCheckable(action.info.checkable);
    if (action.info.shortcut != std::nullopt) {
        action.button->setShortcut(*action.info.shortcut);
    }
}
        
ActionBay::ActionBay(
    QWidget* parent, 
    const std::vector<std::pair<QString, ActionInfo>>& buttonLabels,
    AppUI::Mode mode,
    const QString& accent
): mode {mode}, accent {accent} {
    // Populate the button map
    for(const auto& label : buttonLabels) {
        buttons.emplace(
            label.first,
            Action {
                label.second,
                std::make_unique<QAction>(parent)
            }
        );
        initAction(buttons.at(label.first));
        addAction(buttons.at(label.first).button.get());
    }
    // Set the stylesheet
    setStyleSheet(getCss());
}

QAction& ActionBay::getButton(const QString& buttonLabel) {
    return *buttons.at(buttonLabel).button;
}
