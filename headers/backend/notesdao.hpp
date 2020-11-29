#ifndef __SIGABRT_NOTES__NOTESDAO__
#define __SIGABRT_NOTES__NOTESDAO__

#include <algorithm>
#include <exception>
#include <memory>
#include <cstdlib>
#include <optional>
#include <unordered_map>
#include <utility>

#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include <backend/models.hpp>

namespace AppBackend {
    class LocalDAO {
    private:
        const QString DRIVER {"QSQLITE"};
        const QDir root {
            QDir::cleanPath(
                QDir::homePath() +
                QDir::separator() +
                ".notes"
            )
        };
        const QDir databasePath {
            root.filePath("notes.db")
        };
        const QString TABLE {"notes"};
        QSqlDatabase database;
        
        void initWorkingDir() {
            if(!root.exists()) {
                qWarning() << "First run. Creating root folder " << root.absolutePath();
                root.mkdir(root.absolutePath());
            }
        }
        
        std::vector<long> noteIdList;
        std::unordered_map<long, AppBackend::Note> noteMap;
        
        void connect() {
            if(QSqlDatabase::isDriverAvailable(DRIVER)) {
                database = QSqlDatabase::addDatabase(DRIVER);
                database.setDatabaseName(databasePath.absolutePath());
                if(!database.open()){
                    throw std::runtime_error("Could not open database.");
                }
            } else {
                throw std::runtime_error("SQLITE driver not available.");
            }
        }
        
        void initTable() {
            if(!database.tables().contains(TABLE)) {
                QSqlQuery createQuery {
                    "CREATE TABLE notes ("
                    "  id BIGINT PRIMARY KEY, "
                    "  title TEXT,"
                    "  body TEXT,"
                    "  lut TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                    ");"
                };
                if (!createQuery.isActive()) {
                    qWarning() << "Failed to create table" << createQuery.lastError().text();
                } else {
                    qWarning() << "Successfully created table";
                }
            } else {
                qWarning() << "Table already there";
            }
        }
        
        void initCache() {
            QString queryStr;
            QSqlQuery query;

            queryStr = "SELECT id,title,body FROM notes";
            query.prepare(queryStr);

            if(!query.exec()) {
                qWarning() << "Failed to retrieve any items because " << query.lastError().text();
            } else {
                while (query.next()) {
                    long id {static_cast<long>(query.value("id").toLongLong())};
                    QString title {query.value("title").toString()};
                    QString body {query.value("body").toString()};
                    
                    noteIdList.push_back(id);
                    noteMap.insert(std::make_pair(id, AppBackend::Note {id, title, body}));
                }
            }
        }
    public:
        LocalDAO() {
            initWorkingDir();
            connect();
            initTable();
            initCache();
        }

        bool upsertRecord(const AppBackend::Note& note) {
            // Write through to the backing store
            QSqlQuery query;
            query.prepare(
                "INSERT into notes "
                "  (id, title, body, lut)"
                "VALUES"
                "  ( :id, :title, :body, CURRENT_TIMESTAMP )"
                "ON CONFLICT(id) DO UPDATE SET"
                "  title = :title, body = :body, lut = CURRENT_TIMESTAMP"
            );
            query.bindValue(":id", QVariant::fromValue(note.id));
            query.bindValue(":title", QVariant::fromValue(note.title));
            query.bindValue(":body", QVariant::fromValue(note.body));
            if(!query.exec()) {
                qWarning() << "Failed to insert query with id " << note.id << " because " << query.lastError().text();
                throw std::runtime_error("Failed to insert. " + std::string(__FILE__) + " " + std::to_string(__LINE__));
            } else {
                qWarning() << "Save to insert query with id " << note.id;
            }
            
            // Update / insert into cache
            noteMap[note.id] = note;
            
            // Insert the ID if needed
            if (std::find(noteIdList.begin(), noteIdList.end(), note.id) == noteIdList.end()) {
                noteIdList.push_back(note.id);
            }
            return true;
        }

        const std::optional<AppBackend::Note> loadRecord(const long id) const {
            if (noteMap.find(id) != noteMap.end()) {
                return noteMap.at(id);
            } else {
                return std::nullopt;
            }
        }

        const std::vector<long>& listRecords() const {
            return noteIdList;
        }
    };
}

#endif
