#include <backend/models.hpp>
#include <backend/notesdao.hpp>

#include <algorithm>
#include <exception>
#include <memory>
#include <cstdlib>
#include <optional>
#include <unordered_map>
#include <random>
#include <utility>

#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include <backend/models.hpp>

namespace NotesTable = AppBackend::NotesTableConstants;

AppBackend::LocalDAO::LocalDAO(const QSqlDatabase& database): database {database} {
    std::lock_guard<std::shared_mutex> writerLock(lock);
    initTable();
    initCache();
}

void AppBackend::LocalDAO::initTable() {
    if(!database.tables().contains(NotesTable::TABLE_NAME)) {
        QSqlQuery createQuery {NotesTable::CREATE_TABLE_SQL_STRING};
        if (!createQuery.isActive()) {
            qWarning() << "Failed to create table" << createQuery.lastError().text();
        } else {
            qWarning() << "Successfully created table";
        }
    }
}

void AppBackend::LocalDAO::initCache() {
    QSqlQuery query;
    query.prepare(NotesTable::SELCT_ALL_SQL_STRING);
    if(!query.exec()) {
        qWarning() << "Failed to retrieve any items because " << query.lastError().text();
    } else {
        while (query.next()) {
            long id {static_cast<long>(query.value("id").toLongLong())};
            QString title {query.value("title").toString()};
            QString body {query.value("body").toString()};
            qWarning() << "Loaded note with ID " << id;

            noteIdList.push_back(id);
            noteMap.insert(std::make_pair(id, AppBackend::Note {id, title, body}));
        }
    }
}


bool AppBackend::LocalDAO::upsertRecord(const AppBackend::Note& note) {
    std::lock_guard<std::shared_mutex> writerLock(lock);
    // Write through to the backing store
    QSqlQuery query;
    query.prepare(NotesTable::UPSERT_NOTE_SQL_STRING);
    query.bindValue(":id", QVariant::fromValue(note.id));
    query.bindValue(":title", QVariant::fromValue(note.title));
    query.bindValue(":body", QVariant::fromValue(note.body));
    if(!query.exec()) {
        qWarning() << "Failed to insert query with id " << note.id << " because " << query.lastError().text();
        throw std::runtime_error("Failed to insert query.");
    }

    // Update / insert into cache
    noteMap[note.id] = note;
    
    // Insert the ID if needed
    if (std::find(noteIdList.begin(), noteIdList.end(), note.id) == noteIdList.end()) {
        noteIdList.push_back(note.id);
    }
    return true;
}

const std::optional<AppBackend::Note> AppBackend::LocalDAO::loadRecord(const long id) const {
    std::shared_lock<std::shared_mutex> readerLock(lock);
    if (noteMap.find(id) != noteMap.end()) {
        return noteMap.at(id);
    } else {
        return std::nullopt;
    }
}

const std::vector<long>& AppBackend::LocalDAO::listRecords() const {
    std::shared_lock<std::shared_mutex> readerLock(lock);
    return noteIdList;
}

long AppBackend::LocalDAO::genRandomId() const noexcept {
    std::random_device rd;     
    std::mt19937_64 eng(rd()); 
    std::uniform_int_distribution<long> distr;
    long retval {distr(eng)};
    return retval;
}

long AppBackend::LocalDAO::genRandomId() noexcept {
    std::random_device rd;     
    std::mt19937_64 eng(rd()); 
    std::uniform_int_distribution<long> distr;
    long retval {distr(eng)};
    return retval;
}
