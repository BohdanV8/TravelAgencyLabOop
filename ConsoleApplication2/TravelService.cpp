#include <iostream>
#include <stdexcept>

#include "Services.h"

int TravelService::next_id_ = 1;
int TravelService::alive_count_ = 0;

TravelService::TravelService(const std::string& name, double base_price)
    : name_(name), base_price_(base_price), id_(next_id_++) {
  ++alive_count_;
  std::cout << "  [TravelService] конструктор: " << name_ << "\n";
}

TravelService::~TravelService() {
  --alive_count_;
  std::cout << "  [TravelService] деструктор: " << name_ << "\n";
}

void TravelService::DisplayInfo() const {
  std::cout << "Послуга #" << id_ << " \"" << name_ << "\" (" << Category()
            << "), базова ціна " << base_price_ << ", до сплати "
            << CalculatePrice() << "\n";
}

void TravelService::Write(std::ofstream& out) const {
  out << Category() << '\n' << name_ << '\n' << base_price_ << '\n';
}

void TravelService::Read(std::ifstream& in) {
  std::string category;
  if (!std::getline(in, category)) {
    throw std::runtime_error("файл порожній");
  }
  if (category != Category()) {
    throw std::logic_error("у файлі збережено послугу \"" + category +
                           "\", а очікувалась \"" + Category() + "\"");
  }
  std::string name;
  double base_price = 0.0;
  std::getline(in, name);
  in >> base_price;
  in.ignore();
  if (in.fail()) {
    throw std::runtime_error("пошкоджені дані про послугу");
  }
  name_ = name;
  base_price_ = base_price;
}

void TravelService::PrintLabel() const {
  std::cout << "Мітка TravelService: " << name_ << "\n";
}

const std::string& TravelService::name() const { return name_; }

int TravelService::id() const { return id_; }

int TravelService::AliveCount() { return alive_count_; }
