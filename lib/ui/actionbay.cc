#include <optional>

#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolBar>
#include <QKeySequence>

#include <ui/constants.hpp>
#include <ui/actionbay.hpp>
        
QString AppUI::ActionBay::getCss() {
    return QString {
        "QToolBar {background-color: " + AppUI::Colours::GRAY + "; border: none} "
        "QToolButton {"
        "height: 30px; "
        "width: 30px; "
        "margin-right: 8px; "
        "qproperty-iconSize: 24px;"
        "} "
        "QToolButton:checked {"
        "border: 2px solid " + accent + "; "
        "border-radius: 3px;"
        "} "
        "QToolButton:!checked {"
        "} "
        "QToolButton:hover {"
        "border: 1px solid " + accent + "; "
        "border-radius: 3px;"
        "} "
        "QToolButton:pressed {"
        "border: 2px solid " + accent + "; "
        "border-radius: 2px;"
        "} "
    };
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
    AppUI::Mode mode
): mode {mode} {
    // Set accent according to mode
    accent = mode == AppUI::Mode::DARK? AppUI::Colours::WHITE : AppUI::Colours::BLACK;

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
