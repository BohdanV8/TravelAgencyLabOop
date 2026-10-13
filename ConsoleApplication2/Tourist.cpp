#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "TravelAgency.h"

int Tourist::next_tourist_id_ = 1;
int Tourist::alive_count_ = 0;

Tourist::Tourist()
    : full_name("Не вказано"),
      age(0),
      passport_number("Не вказано"),
      total_paid_(0.0),
      tourist_id_(next_tourist_id_++) {
  ++alive_count_;
  std::cout << "[Tourist #" << tourist_id_
            << "] конструктор без параметрів\n";
}

Tourist::Tourist(const std::string& full_name_in, int age_in,
                 const std::string& passport_number_in)
    : full_name(full_name_in),
      age(age_in),
      passport_number(passport_number_in),
      total_paid_(0.0),
      tourist_id_(next_tourist_id_++) {
  ++alive_count_;
  std::cout << "[Tourist #" << tourist_id_
            << "] конструктор з параметрами: " << full_name << "\n";
}

Tourist::Tourist(const Tourist& other)
    : full_name(other.full_name),
      age(other.age),
      passport_number(other.passport_number),
      phone_number_(other.phone_number_),
      email_(other.email_),
      total_paid_(other.total_paid_),
      tourist_id_(next_tourist_id_++),
      voucher_(other.voucher_) {
  ++alive_count_;
  std::cout << "[Tourist #" << tourist_id_
            << "] конструктор копіювання з туриста #" << other.tourist_id_
            << "\n";
}

Tourist::~Tourist() {
  --alive_count_;
  std::cout << "[Tourist #" << tourist_id_ << "] деструктор: " << full_name
            << "\n";
}

int Tourist::AliveCount() { return alive_count_; }

const std::string& Tourist::phone_number() const { return phone_number_; }

void Tourist::set_phone_number(const std::string& phone) {
  phone_number_ = phone;
}

const std::string& Tourist::email() const { return email_; }
void Tourist::set_email(const std::string& email_in) { email_ = email_in; }
double Tourist::total_paid() const { return total_paid_; }
int Tourist::tourist_id() const { return tourist_id_; }
const Voucher& Tourist::voucher() const { return voucher_; }

void Tourist::DisplayInfo() const {
  std::cout << "=== Турист #" << tourist_id_ << " ===\n"
            << "ПІБ: " << full_name << "\n"
            << "Вік: " << age << "\n"
            << "Паспорт: " << passport_number << "\n"
            << "Телефон: " << phone_number_ << "\n"
            << "Email: " << email_ << "\n"
            << "Сплачено: " << total_paid_ << "\n";
  voucher_.DisplayInfo();
}

double Tourist::CalculateTotalCost() const { return voucher_.GetFinalPrice(); }

double Tourist::CalculateTotalCost(double discount_percent) const {
  double cost = CalculateTotalCost();
  return cost - cost * (discount_percent / 100.0);
}

void Tourist::BookVoucher(const Voucher& voucher_in) {
  voucher_ = voucher_in;
  total_paid_ += voucher_.GetFinalPrice();
  std::cout << full_name << " придбав(ла) путівку до " << voucher_.country
            << " на суму " << voucher_.GetFinalPrice() << "\n";
}

Tourist Tourist::UpgradeTourist(const std::string& new_passport_number) const {
  Tourist upgraded(*this);
  upgraded.passport_number = new_passport_number;
  return upgraded;
}

bool Tourist::ApplyForVisa() {
  if (voucher_.visa_required()) {
    std::cout << full_name << " подав(ла) заявку на візу до "
              << voucher_.country << "\n";
    return true;
  }
  std::cout << "Віза для " << full_name << " не потрібна\n";
  return false;
}

void Tourist::SaveToFile(std::ofstream& out) const {
  out << full_name << '\n'
      << age << '\n'
      << passport_number << '\n'
      << phone_number_ << '\n'
      << email_ << '\n'
      << total_paid_ << '\n'
      << tourist_id_ << '\n';
  voucher_.SaveToFile(out);
}

void Tourist::LoadFromFile(std::ifstream& in) {
  std::getline(in, full_name);
  in >> age;
  in.ignore();
  std::getline(in, passport_number);
  std::getline(in, phone_number_);
  std::getline(in, email_);
  in >> total_paid_ >> tourist_id_;
  in.ignore();
  voucher_.LoadFromFile(in);
}

void Tourist::GenerateAndSortRandomIds() const {
  int size = std::rand() % 10 + 5;
  int* ages = new int[size];
  for (int i = 0; i < size; ++i) {
    ages[i] = std::rand() % 60 + 18;
  }
  std::sort(ages, ages + size);
  std::cout << "Відсортовані значення віку (розмір масиву " << size << "): ";
  for (int i = 0; i < size; ++i) {
    std::cout << ages[i] << " ";
  }
  std::cout << "\n";
  delete[] ages;
}
