#include <iostream>

#include "Staff.h"

int Person::next_id_ = 1;

Person::Person(const std::string& full_name_in, int age_in,
               const std::string& phone_number_in,
               const std::string& passport_number, const std::string& email,
               const std::string& city)
    : full_name(full_name_in),
      age(age_in),
      phone_number(phone_number_in),
      passport_number_(passport_number),
      email_(email),
      city_(city),
      id_(next_id_++) {
  std::cout << "  [Person] конструктор: " << full_name << "\n";
}

Person::~Person() {
  std::cout << "  [Person] деструктор: " << full_name << "\n";
}

void Person::Introduce() const {
  std::cout << "Добрий день, мене звати " << full_name << ", мені " << age
            << " років.\n";
}

std::string Person::GetContactInfo() const {
  return phone_number + ", " + email_;
}

bool Person::IsAdult() const { return age >= 18; }

int Person::id() const { return id_; }

void Person::DisplayInfo() const {
  std::cout << "Особа #" << id_ << ": " << full_name << "\n"
            << "  Вік: " << age << "\n"
            << "  Телефон: " << phone_number << "\n"
            << "  Паспорт: " << passport_number_ << "\n"
            << "  Email: " << email_ << "\n"
            << "  Місто: " << city_ << "\n"
            << "  Громадянство: " << nationality_ << "\n";
}
