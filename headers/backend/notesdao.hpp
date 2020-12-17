#ifndef __SIGABRT_NOTES__NOTESDAO__
#define __SIGABRT_NOTES__NOTESDAO__

#include <algorithm>
#include <exception>
#include <memory>
#include <cstdlib>
#include <optional>
#include <unordered_map>
#include <utility>
#include <shared_mutex>

#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include <backend/models.hpp>

namespace AppBackend {
    namespace NotesTableConstants {
        const QString TABLE_NAME {"notes"};
        
        const QString UPSERT_NOTE_SQL_STRING {
            "INSERT into notes "
            "  (id, create_time, title, body, lut)"
            "VALUES"
            "  ( :id, :create_time, :title, :body, CURRENT_TIMESTAMP )"
            "ON CONFLICT(id) DO UPDATE SET"
            "  title = :title, body = :body, lut = CURRENT_TIMESTAMP"
        };
        const QString CREATE_TABLE_SQL_STRING {
            "CREATE TABLE notes ("
            "  id BIGINT PRIMARY KEY, "
            "  create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
            "  title TEXT,"
            "  body TEXT,"
            "  lut TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
            ");"  
        };
        const QString INDEX_CREATE_TIME {
            "CREATE INDEX create_time ON notes (create_time)"
        };
        const QString SELCT_ALL_SQL_STRING {"SELECT id,create_time,title,body FROM notes"};
        const QString DELETE_NOTE_SQL_STRING {
            "DELETE FROM notes WHERE "
            "  id = :id"
        };
    }
    
    class LocalDAO {
    private:
        QSqlDatabase database;
        mutable std::shared_mutex lock;
        std::vector<long> noteIdList;
        std::unordered_map<long, AppBackend::Note> noteMap;
        
        void initTable();
        void initCache();

    public:
        LocalDAO(const QSqlDatabase& database);
        void upsertRecord(const AppBackend::Note&);
        // We cannot pass references in optional.
        const std::optional<AppBackend::Note> loadRecord(const long) const;
        const std::vector<long>& listRecords() const;
        long genRandomId() const noexcept;
        void deleteRecord(const long id);
    };
}

#endif
