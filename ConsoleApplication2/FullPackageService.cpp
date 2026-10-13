#include <iostream>
#include <stdexcept>

#include "Services.h"

namespace {

constexpr int kPriorityDaysSaved = 2;

}  // namespace

FullPackageService::FullPackageService(const std::string& name,
                                       double base_price,
                                       double coverage_amount, int risk_level,
                                       const std::string& country,
                                       bool is_urgent, double discount_percent)
    : TravelService(name, base_price),
      InsuranceService(name, base_price, coverage_amount, risk_level),
      VisaService(name, base_price, country, is_urgent),
      discount_percent_(discount_percent) {
  std::cout << "  [FullPackageService] конструктор: " << name_ << "\n";
}

FullPackageService::~FullPackageService() {
  std::cout << "  [FullPackageService] деструктор: " << name_ << "\n";
}

std::string FullPackageService::Category() const { return "Повний пакет"; }

double FullPackageService::CalculatePrice() const {
  return PriceWithoutDiscount() * (1.0 - discount_percent_ / 100.0);
}

void FullPackageService::DisplayInfo() const {
  TravelService::DisplayInfo();
  PrintInsuranceDetails();
  PrintVisaDetails();
  std::cout << "  Знижка: " << discount_percent_ << "%\n"
            << "  Економія: " << Savings() << "\n";
}

void FullPackageService::Write(std::ofstream& out) const {
  TravelService::Write(out);
  WriteInsuranceFields(out);
  WriteVisaFields(out);
  out << discount_percent_ << '\n';
}

void FullPackageService::Read(std::ifstream& in) {
  TravelService::Read(in);
  ReadInsuranceFields(in);
  ReadVisaFields(in);
  double discount_percent = 0.0;
  in >> discount_percent;
  in.ignore();
  if (in.fail()) {
    throw std::runtime_error("пошкоджені дані про пакет");
  }
  discount_percent_ = discount_percent;
}

int FullPackageService::ProcessingDays() const {
  return VisaService::ProcessingDays() - kPriorityDaysSaved;
}

double FullPackageService::Savings() const {
  return PriceWithoutDiscount() - CalculatePrice();
}

double FullPackageService::PriceWithoutDiscount() const {
  return base_price_ + InsuranceFee() + VisaFee();
}
