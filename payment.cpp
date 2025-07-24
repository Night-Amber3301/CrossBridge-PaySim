#include "payment.hpp"
#include <random>
#include <chrono>

std::string generateTxnId() {
    auto now = std::chrono::high_resolution_clock::now();
    return "txn_" + std::to_string(now.time_since_epoch().count());
}

std::string PaymentProcessor::authorizeCard(const std::string& cardNum, double amount) {
    if (cardNum.empty() || amount <= 0.0) return "";

    std::string txnId = generateTxnId();
    transactions[txnId] = "authorized";
    return txnId;
}

bool PaymentProcessor::completePayment(const std::string& txnId) {
    auto it = transactions.find(txnId);
    if (it != transactions.end() && it->second == "authorized") {
        it->second = "completed";
        return true;
    }
    return false;
}

bool PaymentProcessor::refundPayment(const std::string& txnId) {
    auto it = transactions.find(txnId);
    if (it != transactions.end() && it->second == "completed") {
        it->second = "refunded";
        return true;
    }
    return false;
}