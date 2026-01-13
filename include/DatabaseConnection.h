#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <pqxx/pqxx>

template<typename T>
class DatabaseConnection {
private:
    std::unique_ptr<pqxx::connection> conn;
    std::unique_ptr<pqxx::work> txn;

public:
    // Конструктор
    DatabaseConnection(const std::string& conn_str) {
        try {
            conn = std::make_unique<pqxx::connection>(conn_str);
            if (!conn->is_open()) {
                throw std::runtime_error("Не удалось подключиться к БД");
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка подключения: " << e.what() << std::endl;
            throw;
        }
    }

    // Деструктор
    ~DatabaseConnection() {
        if (conn && conn->is_open()) conn->disconnect();
    }

    // Начало транзакции
    void beginTransaction() {
        txn = std::make_unique<pqxx::work>(*conn);
    }

    // Завершение транзакции
    void commitTransaction() {
        if (txn) {
            txn->commit();
            txn.reset();
        }
    }

    // Откат транзакции
    void rollbackTransaction() {
        if (txn) {
            txn->abort();
            txn.reset();
        }
    }

    // Выполнение SELECT
    std::vector<std::vector<std::string>> executeQuery(const std::string& query) {
        pqxx::work w(*conn);
        pqxx::result res = w.exec(query);
        std::vector<std::vector<std::string>> result;
        for (auto row : res) {
            std::vector<std::string> r;
            for (auto field : row) r.push_back(field.c_str());
            result.push_back(r);
        }
        return result;
    }

    void executeNonQuery(const std::string& query) {
        if (txn) {
            txn->exec(query);
        } else {
            pqxx::work w(*conn);
            w.exec(query);
            w.commit();
        }
    }

    // Создание функции или процедуры
    void createFunction(const std::string& sql) {
        executeNonQuery(sql);
    }

    // Создание триггера
    void createTrigger(const std::string& sql) {
        executeNonQuery(sql);
    }

    // Получение статуса транзакции
    bool getTransactionStatus() {
        return txn != nullptr;
    }
};
