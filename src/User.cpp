#include "User.h"

User::User(int uid, const std::string& uname) : id(uid), name(uname) {}
std::shared_ptr<Order> User::createOrder(int orderId) {
    auto o = std::make_shared<Order>(orderId);
    orders.push_back(o);
    return o;
}
const std::vector<std::shared_ptr<Order>>& User::getOrders() const { return orders; }

Admin::Admin(int uid, const std::string& uname) : User(uid, uname) {}
void Admin::displayMenu() { std::cout << "Меню администратора\n"; }
void Admin::viewOrders() const { for (auto& o : orders) o->displayItems(); }

Manager::Manager(int uid, const std::string& uname) : User(uid, uname) {}
void Manager::displayMenu() { std::cout << "Меню менеджера\n"; }

Customer::Customer(int uid, const std::string& uname) : User(uid, uname) {}
void Customer::displayMenu() { std::cout << "Меню покупателя\n"; }
void Customer::payOrder(int orderId, std::unique_ptr<PaymentStrategy> strategy) {
    for (auto& o : orders)
        if (o->getId() == orderId) o->pay(std::move(strategy));
}
