#include "DatabaseConnection.h"

template<typename T>
DatabaseConnection<T>::DatabaseConnection(const T& conn_str) {
    conn = std::make_unique<pqxx::connection>(conn_str);
}

template<typename T>
DatabaseConnection<T>::~DatabaseConnection() {
    if (conn && conn->is_open()) conn->disconnect();
}

template<typename T>
std::vector<std::vector<std::string>> DatabaseConnection<T>::executeQuery(const std::string& query) {
    pqxx::work w(*conn);
    pqxx::result r = w.exec(query);
    std::vector<std::vector<std::string>> result;
    for (auto row : r) {
        std::vector<std::string> temp;
        for (auto field : row)
            temp.push_back(field.c_str());
        result.push_back(temp);
    }
    w.commit();
    return result;
}

template<typename T>
void DatabaseConnection<T>::executeNonQuery(const std::string& query) {
    pqxx::work w(*conn);
    w.exec(query);
    w.commit();
}

template<typename T>
void DatabaseConnection<T>::beginTransaction() { txn = std::make_unique<pqxx::work>(*conn); }

template<typename T>
void DatabaseConnection<T>::commitTransaction() { if(txn){ txn->commit(); txn.reset(); } }

template<typename T>
void DatabaseConnection<T>::rollbackTransaction() { if(txn){ txn->abort(); txn.reset(); } }

// Нужно явно инстанцировать шаблон для string
template class DatabaseConnection<std::string>;
