#ifndef __SIGABRT_NOTES__MODELS__
#define __SIGABRT_NOTES__MODELS__

#include <QString>
#include <QDateTime>

#include <optional>

namespace AppBackend {
    struct Note {
        long int id;
        std::optional<QDateTime> createTime;
        QString title;
        QString body;
    };
    
    struct NoteTitleInfo {
        long id;
        QString title;
    };
}

#endif
