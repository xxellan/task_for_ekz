#include "Order.h"

OrderItem::OrderItem(std::shared_ptr<Product> p, int q) : product(p), quantity(q) {}
double OrderItem::getTotal() const { return product->getPrice() * quantity; }
void OrderItem::display() const {
    std::cout << product->getName() << " x" << quantity << " = " << getTotal() << " руб.\n";
}

Order::Order(int oid) : id(oid), status("pending") {}
int Order::getId() const { return id; }
std::string Order::getStatus() const { return status; }
void Order::setStatus(const std::string& s) { status = s; }

void Order::addItem(std::shared_ptr<Product> p, int qty) {
    items.push_back(std::make_unique<OrderItem>(p, qty));
}

double Order::getTotal() const {
    double total = 0;
    for (auto& item : items) total += item->getTotal();
    return total;
}

void Order::pay(std::unique_ptr<PaymentStrategy> strategy) {
    payment = std::move(strategy);
    if (payment) payment->pay(getTotal());
    status = "completed";
}

void Order::displayItems() const {
    std::cout << "Заказ #" << id << ":\n";
    for (auto& item : items) item->display();
    std::cout << "Итого: " << getTotal() << " руб.\n";
    std::cout << "Статус: " << status << "\n";
}
