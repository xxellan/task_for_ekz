#pragma once
#include "User.h"
#include "DatabaseConnection.h"

class Admin : public User {
public:
    Admin(int uid, const std::string& uname, const std::string& uemail)
        : User(uid, uname, uemail, "admin") {}

    void createOrder(std::shared_ptr<Order> order) override {
        // Админ не создаёт заказы, но можно оставить пустой
    }

    void viewOrderStatus(int orderId) override {
        // Можно выводить через SQL getOrderStatus
    }

    void cancelOrder(int orderId) override {}

    void addProduct(DatabaseConnection<std::string>& db, const std::string& name, double price, int stock);
    void updateProduct(DatabaseConnection<std::string>& db, int productId, double price, int stock);
    void deleteProduct(DatabaseConnection<std::string>& db, int productId);
};
