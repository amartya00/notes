#include <optional>

#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QKeySequence>

#include <ui/constants.hpp>
#include <ui/actionbay.hpp>
        
QString AppUI::ActionBay::getCss() {
    
    return CSS_TEMPLATE.arg(
        mode == AppUI::Mode::DARK? AppUI::Colours::VERY_DARK_GRAY : AppUI::Colours::WHITE,
        accent
    );
}
        
void AppUI::ActionBay::setLightIcon(Action& action) {
    QPixmap pixmap(action.info.lightIconPath);
    QIcon icon(pixmap);
    action.button->setIcon(icon);
    action.button->setIconVisibleInMenu(true);
}

void AppUI::ActionBay::setDarkIcon(Action& action) {
    QPixmap pixmap(action.info.darkIconPath);
    QIcon icon(pixmap);
    action.button->setIcon(icon);
}

void AppUI::ActionBay::initAction(Action& action) {
    mode == AppUI::Mode::DARK? setDarkIcon(action) : setLightIcon(action);
    action.button->setCheckable(action.info.checkable);
    if (action.info.shortcut != std::nullopt) {
        action.button->setShortcut(*action.info.shortcut);
    }
}
        
AppUI::ActionBay::ActionBay(
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
        
std::unique_ptr<QAction>& AppUI::ActionBay::getButton(const QString& buttonLabel) {
    return buttons.at(buttonLabel).button;
}
