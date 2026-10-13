#include <iostream>
#include <stdexcept>

#include "Services.h"

namespace {

constexpr double kPricePerKm = 15.0;
constexpr double kAverageSpeedKmh = 60.0;

}  // namespace

TransferService::TransferService(const std::string& name, double base_price,
                                 const std::string& route, double distance_km)
    : TravelService(name, base_price), route_(route),
      distance_km_(distance_km) {
  std::cout << "  [TransferService] конструктор: " << name_ << "\n";
}

TransferService::~TransferService() {
  std::cout << "  [TransferService] деструктор: " << name_ << "\n";
}

std::string TransferService::Category() const { return "Трансфер"; }

double TransferService::CalculatePrice() const {
  return base_price_ + distance_km_ * kPricePerKm;
}

void TransferService::DisplayInfo() const {
  TravelService::DisplayInfo();
  std::cout << "  Маршрут: " << route_ << "\n"
            << "  Відстань: " << distance_km_ << " км\n"
            << "  Час у дорозі: " << TravelTimeHours() << " год\n";
}

void TransferService::Write(std::ofstream& out) const {
  TravelService::Write(out);
  out << route_ << '\n' << distance_km_ << '\n';
}

void TransferService::Read(std::ifstream& in) {
  TravelService::Read(in);
  std::string route;
  double distance_km = 0.0;
  std::getline(in, route);
  in >> distance_km;
  in.ignore();
  if (in.fail()) {
    throw std::runtime_error("пошкоджені дані про трансфер");
  }
  route_ = route;
  distance_km_ = distance_km;
}

double TransferService::TravelTimeHours() const {
  return distance_km_ / kAverageSpeedKmh;
}

void TransferService::PrintLabel() const {
  std::cout << "Мітка TransferService: " << name_ << " (" << route_ << ")\n";
}
