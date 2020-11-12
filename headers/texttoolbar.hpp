#ifndef __SIGABRT_NOTES__TXT_TOOLBAR__
#define __SIGABRT_NOTES__TXT_TOOLBAR__

#include <QToolBar>
#include <QPixmap>

namespace AppUI {
    class TextToolbar : public QToolBar {
    private:
        QPixmap bold;
        
    public:
        TextToolbar(QWidget* parent): QToolBar(parent), bold {"resources/bold.png"} {
            addAction(QIcon(bold), "New File");
        }
    };
}

#endif
