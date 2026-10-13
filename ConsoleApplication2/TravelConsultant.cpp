#include <iostream>

#include "Staff.h"

TravelConsultant::TravelConsultant(
    const std::string& full_name_in, int age_in,
    const std::string& phone_number_in, const std::string& passport_number,
    const std::string& email, const std::string& city,
    const std::string& insurance_company, double policy_price,
    double visa_fee, double consultation_fee)
    : Person(full_name_in, age_in, phone_number_in, passport_number, email,
             city),
      InsuranceSpecialist(full_name_in, age_in, phone_number_in,
                          passport_number, email, city, insurance_company,
                          policy_price),
      VisaSpecialist(full_name_in, age_in, phone_number_in, passport_number,
                     email, city, visa_fee),
      consultation_fee_(consultation_fee) {
  std::cout << "  [TravelConsultant] конструктор: " << full_name << "\n";
}

TravelConsultant::~TravelConsultant() {
  std::cout << "  [TravelConsultant] деструктор: " << full_name << "\n";
}

void TravelConsultant::PrepareFullPackage(Tourist& tourist, Voucher& voucher) {
  std::cout << "Консультант " << full_name << " готує повний пакет для "
            << tourist.full_name << "\n";
  IssuePolicy(voucher);
  tourist.BookVoucher(voucher);
  ProcessVisa(tourist);
  ++clients_served_;
}

double TravelConsultant::CalculateTotalEarnings() const {
  return InsuranceSpecialist::CalculateEarnings() +
         VisaSpecialist::CalculateEarnings() +
         consultation_fee_ * clients_served_;
}

void TravelConsultant::DisplayInfo() const {
  Person::DisplayInfo();
  ShowInsuranceInfo();
  ShowVisaInfo();
  std::cout << "  Посада: туристичний консультант\n"
            << "  Спеціалізація: " << specialization_ << "\n"
            << "  Мови: " << languages_ << "\n"
            << "  Години роботи: " << office_hours_ << "\n"
            << "  Онлайн-консультації: " << (works_online_ ? "так" : "ні")
            << "\n"
            << "  Ціна консультації: " << consultation_fee_ << "\n"
            << "  Знижка на пакет: " << package_discount_percent_ << "%\n"
            << "  Обслуговано клієнтів: " << clients_served_ << "\n"
            << "  Рейтинг: " << rating_ << "\n";
}
