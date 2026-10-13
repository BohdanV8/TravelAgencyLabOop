#include <iostream>
#include <stdexcept>

#include "Services.h"

namespace {

constexpr double kFeePerRiskLevel = 0.01;

}  // namespace

InsuranceService::InsuranceService(const std::string& name, double base_price,
                                   double coverage_amount, int risk_level)
    : TravelService(name, base_price),
      coverage_amount_(coverage_amount),
      risk_level_(risk_level) {
  std::cout << "  [InsuranceService] конструктор: " << name_ << "\n";
}

InsuranceService::~InsuranceService() {
  std::cout << "  [InsuranceService] деструктор: " << name_ << "\n";
}

std::string InsuranceService::Category() const { return "Страхування"; }

double InsuranceService::CalculatePrice() const {
  return base_price_ + InsuranceFee();
}

void InsuranceService::DisplayInfo() const {
  TravelService::DisplayInfo();
  PrintInsuranceDetails();
}

void InsuranceService::Write(std::ofstream& out) const {
  TravelService::Write(out);
  WriteInsuranceFields(out);
}

void InsuranceService::Read(std::ifstream& in) {
  TravelService::Read(in);
  ReadInsuranceFields(in);
}

bool InsuranceService::CoversTrip(double trip_cost) const {
  return trip_cost <= coverage_amount_;
}

double InsuranceService::InsuranceFee() const {
  return coverage_amount_ * kFeePerRiskLevel * risk_level_;
}

void InsuranceService::PrintInsuranceDetails() const {
  std::cout << "  Сума покриття: " << coverage_amount_ << "\n"
            << "  Рівень ризику: " << risk_level_ << "\n";
}

void InsuranceService::WriteInsuranceFields(std::ofstream& out) const {
  out << coverage_amount_ << '\n' << risk_level_ << '\n';
}

void InsuranceService::ReadInsuranceFields(std::ifstream& in) {
  double coverage_amount = 0.0;
  int risk_level = 0;
  in >> coverage_amount >> risk_level;
  in.ignore();
  if (in.fail()) {
    throw std::runtime_error("пошкоджені дані про страхування");
  }
  coverage_amount_ = coverage_amount;
  risk_level_ = risk_level;
}
