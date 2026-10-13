#include <iostream>
#include <stdexcept>

#include "Services.h"

namespace {

constexpr double kUrgentFee = 1000.0;
constexpr int kRegularProcessingDays = 10;
constexpr int kUrgentProcessingDays = 3;

}  // namespace

VisaService::VisaService(const std::string& name, double base_price,
                         const std::string& country, bool is_urgent)
    : TravelService(name, base_price), country_(country),
      is_urgent_(is_urgent) {
  std::cout << "  [VisaService] конструктор: " << name_ << "\n";
}

VisaService::~VisaService() {
  std::cout << "  [VisaService] деструктор: " << name_ << "\n";
}

std::string VisaService::Category() const { return "Віза"; }

double VisaService::CalculatePrice() const { return base_price_ + VisaFee(); }

void VisaService::DisplayInfo() const {
  TravelService::DisplayInfo();
  PrintVisaDetails();
}

void VisaService::Write(std::ofstream& out) const {
  TravelService::Write(out);
  WriteVisaFields(out);
}

void VisaService::Read(std::ifstream& in) {
  TravelService::Read(in);
  ReadVisaFields(in);
}

int VisaService::ProcessingDays() const {
  return is_urgent_ ? kUrgentProcessingDays : kRegularProcessingDays;
}

double VisaService::VisaFee() const { return is_urgent_ ? kUrgentFee : 0.0; }

void VisaService::PrintVisaDetails() const {
  std::cout << "  Країна: " << country_ << "\n"
            << "  Термінова: " << (is_urgent_ ? "так" : "ні") << "\n"
            << "  Термін оформлення: " << ProcessingDays() << " днів\n";
}

void VisaService::WriteVisaFields(std::ofstream& out) const {
  out << country_ << '\n' << is_urgent_ << '\n';
}

void VisaService::ReadVisaFields(std::ifstream& in) {
  std::string country;
  bool is_urgent = false;
  std::getline(in, country);
  in >> is_urgent;
  in.ignore();
  if (in.fail()) {
    throw std::runtime_error("пошкоджені дані про візу");
  }
  country_ = country;
  is_urgent_ = is_urgent;
}
