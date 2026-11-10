#include "Excursion.h"

#include <stdexcept>

Excursion::Excursion()
    : title_("Без назви"), city_("Не вказано"), price_(0.0), hours_(0.0) {}

Excursion::Excursion(const std::string& title, const std::string& city,
                     double price, double hours)
    : title_(title), city_(city), price_(price), hours_(hours) {
  if (price < 0 || hours <= 0) {
    throw std::invalid_argument("некоректна ціна або тривалість екскурсії");
  }
}

const std::string& Excursion::title() const { return title_; }

const std::string& Excursion::city() const { return city_; }

double Excursion::price() const { return price_; }

double Excursion::hours() const { return hours_; }

Excursion Excursion::operator+(const Excursion& other) const {
  std::string city = city_ == other.city_ ? city_ : city_ + " / " + other.city_;
  return Excursion(title_ + " + " + other.title_, city, price_ + other.price_,
                   hours_ + other.hours_);
}

bool Excursion::operator==(const Excursion& other) const {
  return title_ == other.title_ && city_ == other.city_;
}

bool Excursion::operator<(const Excursion& other) const {
  if (price_ != other.price_) {
    return price_ < other.price_;
  }
  if (title_ != other.title_) {
    return title_ < other.title_;
  }
  return city_ < other.city_;
}

std::ostream& operator<<(std::ostream& out, const Excursion& excursion) {
  return out << "\"" << excursion.title_ << "\" (" << excursion.city_ << ", "
             << excursion.hours_ << " год, " << excursion.price_ << " грн)";
}
