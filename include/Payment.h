#pragma once
#include <iostream>

class Payment {
public:
    virtual ~Payment() = default;
    virtual void pay() = 0;
};

class CardPayment : public Payment {
public:
    void pay() override { std::cout << "Оплата картой проведена\n"; }
};

class EWalletPayment : public Payment {
public:
    void pay() override { std::cout << "Оплата электронным кошельком проведена\n"; }
};

class SBPPayment : public Payment {
public:
    void pay() override { std::cout << "Оплата через СБП проведена\n"; }
};
