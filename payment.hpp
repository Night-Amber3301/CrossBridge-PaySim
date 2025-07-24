#pragma once
#include <string>
#include <unordered_map>

class PaymentProcessor {
private:
    std::unordered_map<std::string, std::string> transactions; // txnId -> status

public:
    std::string authorizeCard(const std::string& cardNum, double amount);
    bool completePayment(const std::string& txnId);
    bool refundPayment(const std::string& txnId);
};