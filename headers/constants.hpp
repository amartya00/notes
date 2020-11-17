#ifndef __SIGABRT_NOTES__CONSTANTS__
#define __SIGABRT_NOTES__CONSTANTS__

#include <QString>

namespace AppUI {
    namespace ButtonConstants {
        const QString LIME {"#82ec00"};
        const QString RED {"#ff0003"};
        const QString BACKGROUND_GRAY {"#3E3E3E"};

        const QString LIME_ROUNDED_CSS {"height: 30px; width: 80px; background: " + LIME + "; border-radius: 3px; font-size: 13px;"};
        const QString RED_ROUNDED_CSS {"height: 30px; width: 80px; background: " + RED + "; border-radius: 3px; font-size: 13px;"};
        const QString PLAIN_ROUNDED_CSS {
            "height: 30px; width: 80px; "
            "border: 1px solid black; "
            "border-radius: 3px; "
            "font-size: 13px; "
            "qproperty-iconSize: 24px;"
        };
        const QString PLAIN_ROUNDED_SQUARE_CSS {
            "height: 30px; width: 30px; "
            "border: 1px solid black; "
            "border-radius: 3px; "
            "font-size: 13px; "
        };
        
        const QString MAN_WINDOW_DARK_CSS {"background: #3E3E3E; color: white"};
        const QString TEXT_EDIT_DARK_BG_CSS {"background: #2E2F30; font-size: 15px; border: 1px solid black; border-radius: 3px;"};
    }
    
}

#endif
