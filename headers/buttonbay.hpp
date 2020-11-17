#ifndef __SIGABRT_NOTES__BUTTONBAY__
#define __SIGABRT_NOTES__BUTTONBAY__

#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QString>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QIcon>
#include <QPixmap>

namespace AppUI {
    struct ButtonInfo {
        QString css;
        QString iconPath;
    };
    
    class ButtonBay: public QHBoxLayout {
    private:
        std::unordered_map<QString, std::unique_ptr<QPushButton>> buttons;
        // QSpacerItem (like any other QLayoutItem) is deleted by the layout itself. Hence no unique_ptr
        // https://forum.qt.io/topic/64234/how-does-qspaceritem-get-deleted
        QSpacerItem* spacer;
        
    public:
        ButtonBay(QWidget* parent, const std::vector<std::pair<QString, ButtonInfo>>& buttonLabels): 
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
        
        std::unique_ptr<QPushButton>& getButton(const QString& buttonLabel) {
            return buttons.at(buttonLabel);
        }
    };
}

#endif
