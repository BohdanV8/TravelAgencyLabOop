#include <iostream>

#include "Staff.h"

TravelAgent::TravelAgent(const std::string& full_name_in, int age_in,
                         const std::string& phone_number_in,
                         const std::string& passport_number,
                         const std::string& email, const std::string& city,
                         const std::string& office, double salary)
    : Person(full_name_in, age_in, phone_number_in, passport_number, email,
             city),
      office_(office),
      salary_(salary) {
  std::cout << "  [TravelAgent] конструктор: " << full_name << "\n";
}

TravelAgent::~TravelAgent() {
  std::cout << "  [TravelAgent] деструктор: " << full_name << "\n";
}

void TravelAgent::SellVoucher(Tourist& tourist, const Voucher& voucher) {
  std::cout << "Менеджер " << full_name << " продає путівку туристу "
            << tourist.full_name << "\n";
  tourist.BookVoucher(voucher);
  ++sales_count_;
  sales_total_ += voucher.GetFinalPrice();
}

double TravelAgent::CalculateCommission() const {
  return sales_total_ * commission_percent_ / 100.0;
}

double TravelAgent::CalculateMonthlyIncome() const {
  return salary_ + CalculateCommission();
}

void TravelAgent::ShowInheritedAccess() const {
  std::cout << "TravelAgent (protected-наслідування): члени Person стали "
               "protected\n"
            << "  всередині класу: " << full_name << ", " << age << ", "
            << GetContactInfo() << ", повнолітній: "
            << (IsAdult() ? "так" : "ні") << "\n"
            << "  ззовні доступні лише full_name та Introduce() через using\n";
}

void TravelAgent::DisplayInfo() const {
  Person::DisplayInfo();
  std::cout << "  Посада: " << position_ << "\n"
            << "  Офіс: " << office_ << "\n"
            << "  Робочий телефон: " << work_phone_ << "\n"
            << "  Рік прийому: " << hire_year_ << "\n"
            << "  Оклад: " << salary_ << "\n"
            << "  Комісія: " << commission_percent_ << "%\n"
            << "  Продано путівок: " << sales_count_ << "\n"
            << "  Сума продажів: " << sales_total_ << "\n";
}
