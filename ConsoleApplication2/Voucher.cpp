#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "TravelAgency.h"

int Voucher::next_voucher_id_ = 1;

Voucher::Voucher()
    : country("Не вказано"),
      duration_days(0),
      base_price(0.0),
      insurance_cost_(0.0),
      has_insurance_(false),
      visa_required_(false),
      travel_dates_("Не вказано"),
      voucher_id_(next_voucher_id_++) {
  std::cout << "[Voucher #" << voucher_id_
            << "] конструктор без параметрів\n";
}

Voucher::Voucher(const std::string& country_in, int duration_days_in,
                 double base_price_in, bool visa_required_in,
                 const std::string& travel_dates_in)
    : country(country_in),
      duration_days(duration_days_in),
      base_price(base_price_in),
      insurance_cost_(0.0),
      has_insurance_(false),
      visa_required_(visa_required_in),
      travel_dates_(travel_dates_in),
      voucher_id_(next_voucher_id_++) {
  std::cout << "[Voucher #" << voucher_id_
            << "] конструктор з параметрами: " << country << "\n";
}

Voucher::Voucher(const Voucher& other)
    : country(other.country),
      duration_days(other.duration_days),
      base_price(other.base_price),
      insurance_cost_(other.insurance_cost_),
      has_insurance_(other.has_insurance_),
      visa_required_(other.visa_required_),
      travel_dates_(other.travel_dates_),
      voucher_id_(next_voucher_id_++) {
  std::cout << "[Voucher #" << voucher_id_
            << "] конструктор копіювання з путівки #" << other.voucher_id_
            << "\n";
}

Voucher::~Voucher() {
  std::cout << "[Voucher #" << voucher_id_ << "] деструктор: " << country
            << "\n";
}

double Voucher::insurance_cost() const { return insurance_cost_; }
bool Voucher::has_insurance() const { return has_insurance_; }
bool Voucher::visa_required() const { return visa_required_; }
const std::string& Voucher::travel_dates() const { return travel_dates_; }
int Voucher::voucher_id() const { return voucher_id_; }

void Voucher::DisplayInfo() const {
  std::cout << "--- Путівка #" << voucher_id_ << " ---\n"
            << "Країна: " << country << "\n"
            << "Тривалість: " << duration_days << " днів\n"
            << "Базова ціна: " << base_price << "\n"
            << "Дати подорожі: " << travel_dates_ << "\n"
            << "Потрібна віза: " << (visa_required_ ? "так" : "ні") << "\n"
            << "Страхування: "
            << (has_insurance_ ? std::to_string(insurance_cost_) : "немає")
            << "\n";
}

double Voucher::GetFinalPrice() const {
  return base_price + (has_insurance_ ? insurance_cost_ : 0.0);
}

double Voucher::GetFinalPrice(double additional_fee) const {
  return GetFinalPrice() + additional_fee;
}

void Voucher::ApplyDiscountForTourist(const Tourist& tourist) {
  if (tourist.age >= 60) {
    base_price *= 0.9;
  }
}

Voucher Voucher::CombineWith(const Voucher& other) const {
  Voucher combined(*this);
  combined.duration_days += other.duration_days;
  combined.base_price += other.base_price;
  combined.travel_dates_ = travel_dates_ + " + " + other.travel_dates_;
  return combined;
}

void Voucher::AddInsurance(double cost) {
  has_insurance_ = true;
  insurance_cost_ = cost;
}

void Voucher::SaveToFile(std::ofstream& out) const {
  out << country << '\n'
      << duration_days << '\n'
      << base_price << '\n'
      << insurance_cost_ << '\n'
      << has_insurance_ << '\n'
      << visa_required_ << '\n'
      << travel_dates_ << '\n'
      << voucher_id_ << '\n';
}

void Voucher::LoadFromFile(std::ifstream& in) {
  std::getline(in, country);
  in >> duration_days >> base_price >> insurance_cost_ >> has_insurance_ >>
      visa_required_;
  in.ignore();
  std::getline(in, travel_dates_);
  in >> voucher_id_;
}

void Voucher::GenerateAndSortRandomDurations() const {
  int size = std::rand() % 10 + 5;
  int* durations = new int[size];
  for (int i = 0; i < size; ++i) {
    durations[i] = std::rand() % 30 + 1;
  }
  std::sort(durations, durations + size);
  std::cout << "Відсортовані тривалості (розмір масиву " << size << "): ";
  for (int i = 0; i < size; ++i) {
    std::cout << durations[i] << " ";
  }
  std::cout << "\n";
  delete[] durations;
}
