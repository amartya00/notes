#include <QWidget>
#include <QString>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <ui/buttonbay.hpp>

AppUI::ButtonBay::ButtonBay(QWidget* parent, const std::vector<std::pair<QString, ButtonInfo>>& buttonLabels): 
            QHBoxLayout(nullptr),
            spacer {new QSpacerItem(10, 10, QSizePolicy::Expanding)} {
            for(const auto& label : buttonLabels) {
                auto button {std::make_unique<QPushButton>(label.first, parent)};
                button->setStyleSheet(label.second.css);
                QPixmap pixmap(label.second.iconPath);
                QIcon icon(pixmap);
                button -> setIcon(icon);
                addWidget(button.get());
                buttons[label.first] = std::move(button);
            }
            addSpacerItem(spacer);
        }
        
        std::unique_ptr<QPushButton>& AppUI::ButtonBay::getButton(const QString& buttonLabel) {
            return buttons.at(buttonLabel);
        }
