#include <iostream>

#include "Staff.h"

InsuranceSpecialist::InsuranceSpecialist(
    const std::string& full_name_in, int age_in,
    const std::string& phone_number_in, const std::string& passport_number,
    const std::string& email, const std::string& city,
    const std::string& insurance_company, double policy_price)
    : Person(full_name_in, age_in, phone_number_in, passport_number, email,
             city),
      insurance_company_(insurance_company),
      policy_price_(policy_price) {
  std::cout << "  [InsuranceSpecialist] конструктор: " << full_name << "\n";
}

InsuranceSpecialist::~InsuranceSpecialist() {
  std::cout << "  [InsuranceSpecialist] деструктор: " << full_name << "\n";
}

bool InsuranceSpecialist::CanCover(double trip_cost) const {
  return trip_cost <= max_coverage_;
}

void InsuranceSpecialist::IssuePolicy(Voucher& voucher) {
  if (!CanCover(voucher.GetFinalPrice())) {
    std::cout << "Поліс для туру до " << voucher.country
              << " неможливо оформити: вартість перевищує покриття\n";
    return;
  }
  voucher.AddInsurance(policy_price_);
  ++policies_issued_;
  total_premiums_ += policy_price_;
  std::cout << "Оформлено страховий поліс \"" << insurance_company_
            << "\" для туру до " << voucher.country << " за "
            << policy_price_ << "\n";
}

double InsuranceSpecialist::CalculateEarnings() const {
  return total_premiums_ * commission_rate_;
}

void InsuranceSpecialist::ShowInsuranceInfo() const {
  std::cout << "  Страхова компанія: " << insurance_company_ << "\n"
            << "  Ліцензія: " << license_number_ << "\n"
            << "  Сертифікований з: " << certification_year_ << "\n"
            << "  Ціна поліса: " << policy_price_ << "\n"
            << "  Максимальне покриття: " << max_coverage_ << "\n"
            << "  Оформлено полісів: " << policies_issued_ << "\n"
            << "  Сума внесків: " << total_premiums_ << "\n"
            << "  Комісія: " << commission_rate_ * 100 << "%\n";
}

void InsuranceSpecialist::DisplayInfo() const {
  Person::DisplayInfo();
  ShowInsuranceInfo();
}
