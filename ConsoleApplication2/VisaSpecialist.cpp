#include <iostream>

#include "Staff.h"

VisaSpecialist::VisaSpecialist(const std::string& full_name_in, int age_in,
                               const std::string& phone_number_in,
                               const std::string& passport_number,
                               const std::string& email,
                               const std::string& city, double visa_fee)
    : Person(full_name_in, age_in, phone_number_in, passport_number, email,
             city),
      visa_fee_(visa_fee) {
  std::cout << "  [VisaSpecialist] конструктор: " << full_name << "\n";
}

VisaSpecialist::~VisaSpecialist() {
  std::cout << "  [VisaSpecialist] деструктор: " << full_name << "\n";
}

bool VisaSpecialist::IsCountrySupported(const std::string& country) const {
  return supported_countries_.find(country) != std::string::npos;
}

void VisaSpecialist::ProcessVisa(Tourist& tourist) {
  if (!tourist.ApplyForVisa()) {
    return;
  }
  ++processed_applications_;
  const std::string& country = tourist.voucher().country;
  if (IsCountrySupported(country)) {
    ++approved_applications_;
    total_fees_ += visa_fee_;
    std::cout << "Візу до " << country << " для " << tourist.full_name
              << " буде готово за " << processing_days_ << " днів\n";
  } else {
    std::cout << "Агенція не оформлює візи до " << country << "\n";
  }
}

double VisaSpecialist::CalculateEarnings() const { return total_fees_; }

void VisaSpecialist::ShowVisaInfo() const {
  std::cout << "  Сертифікат: " << certificate_number_ << "\n"
            << "  Посольства у місті: " << embassy_city_ << "\n"
            << "  Країни: " << supported_countries_ << "\n"
            << "  Візовий збір: " << visa_fee_ << "\n"
            << "  Термін оформлення: " << processing_days_ << " днів\n"
            << "  Розглянуто заявок: " << processed_applications_ << "\n"
            << "  Схвалено заявок: " << approved_applications_ << "\n"
            << "  Отримано зборів: " << total_fees_ << "\n";
}

void VisaSpecialist::DisplayInfo() const {
  Person::DisplayInfo();
  ShowVisaInfo();
}
