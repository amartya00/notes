#ifndef __SIGABRT_NOTES__BUTTONBAY__
#define __SIGABRT_NOTES__BUTTONBAY__

#include <memory>
#include <vector>
#include <unordered_map>

#include <QPushButton>
#include <QHBoxLayout>
#include <QString>
#include <QSpacerItem>

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
        ButtonBay(QWidget* parent, const std::vector<std::pair<QString, ButtonInfo>>& buttonLabels);
        std::unique_ptr<QPushButton>& getButton(const QString& buttonLabel);
    };
}

#endif
