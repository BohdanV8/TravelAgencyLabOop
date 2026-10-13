#include <iostream>

#include "Staff.h"

BusDriver::BusDriver(const std::string& full_name_in, int age_in,
                     const std::string& phone_number_in,
                     const std::string& passport_number,
                     const std::string& email, const std::string& city,
                     const std::string& bus_number, int seats)
    : Person(full_name_in, age_in, phone_number_in, passport_number, email,
             city),
      bus_number_(bus_number),
      seats_(seats) {
  std::cout << "  [BusDriver] конструктор: " << full_name << "\n";
}

BusDriver::~BusDriver() {
  std::cout << "  [BusDriver] деструктор: " << full_name << "\n";
}

const std::string& BusDriver::name() const { return full_name; }

bool BusDriver::CanTakeGroup(int group_size) const {
  return group_size <= seats_;
}

void BusDriver::DriveTransfer(const std::string& route, double distance_km) {
  current_route_ = route;
  km_driven_ += distance_km;
  ++trips_done_;
  std::cout << "Водій " << full_name << " везе групу автобусом "
            << bus_number_ << " за маршрутом " << route << " (" << distance_km
            << " км)\n";
}

double BusDriver::CalculateFuelUsed() const {
  return km_driven_ * fuel_per_100km_ / 100.0;
}

void BusDriver::ShowInheritedAccess() const {
  std::cout << "BusDriver (private-наслідування): члени Person стали private\n"
            << "  всередині класу: " << full_name << ", " << age << ", "
            << phone_number << "\n"
            << "  ззовні доступ лише через власні методи, напр. name()\n";
}

void BusDriver::DisplayInfo() const {
  Person::DisplayInfo();
  std::cout << "  Посада: водій трансферу\n"
            << "  Категорія прав: " << license_category_ << "\n"
            << "  Стаж водіння: " << driving_experience_ << " років\n"
            << "  Автобус: " << bus_number_ << "\n"
            << "  Кількість місць: " << seats_ << "\n"
            << "  Поточний маршрут: " << current_route_ << "\n"
            << "  Поїздок: " << trips_done_ << "\n"
            << "  Пробіг: " << km_driven_ << " км\n"
            << "  Витрата пального: " << fuel_per_100km_ << " л/100 км\n";
}
