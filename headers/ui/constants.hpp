#ifndef __SIGABRT_NOTES__CONSTANTS__
#define __SIGABRT_NOTES__CONSTANTS__

#include <unordered_map>

#include <QString>
#include <QFontDatabase>

namespace AppUI {
    enum class Mode {
        LIGHT, DARK
    };
    
    namespace Colours {
        const QString LIME {"#82ec00"};
        const QString RED {"#ff0003"};
        const QString GRAY {"#3E3E3E"};
        const QString DARK_GRAY {"#2E2F30"};
        const QString VERY_DARK_GRAY {"#202021"};
        const QString BLUE {"#2B78FE"};
        const QString DARK_PINK {"#9D2689"};
        const QString WHITE {"#FFFFFF"};
        const QString BLACK {"#000000"};
        const QString PURPLE {"#8B7DED"};
    }
}

#endif
