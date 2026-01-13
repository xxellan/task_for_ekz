#include <iostream>
#include <memory>
#include "User.h"
#include "Product.h"
#include "Payment.h"

int main() {
    std::cout << "=== Интернет-магазин ===\n";

    auto admin = std::make_unique<Admin>(1, "Иван Петров");
    auto manager = std::make_unique<Manager>(2, "Петр Сидоров");
    auto customer = std::make_unique<Customer>(3, "Александр Смирнов");

    auto laptop = std::make_shared<Product>(1, "Ноутбук Dell", 50000, 10);
    auto mouse = std::make_shared<Product>(2, "Мышка Logitech", 1500, 50);

    auto order = customer->createOrder(101);
    order->addItem(laptop, 1);
    order->addItem(mouse, 2);

    order->displayItems();

    std::cout << "\n=== Оплата заказа ===\n";
    auto payment = std::make_unique<CardPayment>("1234567890123456");
    customer->payOrder(101, std::move(payment));

    order->displayItems();

    return 0;
}
