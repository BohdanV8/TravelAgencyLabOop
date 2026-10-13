#include "TravelAgency.h"

#include <iostream>

TravelAgency::TravelAgency(const std::string& name) : name_(name) {
  std::cout << "[TravelAgency] конструктор з параметрами: " << name_ << "\n";
}

TravelAgency::~TravelAgency() {
  std::cout << "[TravelAgency] деструктор: " << name_
            << " (туристи продовжують існувати)\n";
}

const std::string& TravelAgency::name() const { return name_; }

void TravelAgency::AddClient(Tourist* tourist) {
  clients_.push_back(tourist);
  std::cout << "Агенція \"" << name_ << "\" обслуговує туриста "
            << tourist->full_name << "\n";
}

void TravelAgency::ShowClients() const {
  std::cout << "Клієнти агенції \"" << name_ << "\":\n";
  for (const Tourist* client : clients_) {
    std::cout << "  - " << client->full_name << ", путівка до "
              << client->voucher().country << "\n";
  }
}
