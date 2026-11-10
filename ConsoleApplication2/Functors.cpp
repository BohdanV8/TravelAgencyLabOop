#include "Functors.h"

#include <iostream>

#include "Excursion.h"
#include "Services.h"

PriceAtMost::PriceAtMost(double limit) : limit_(limit) {}

bool PriceAtMost::operator()(const Excursion& excursion) const {
  return excursion.price() <= limit_;
}

InCity::InCity(const std::string& city) : city_(city) {}

bool InCity::operator()(const Excursion& excursion) const {
  return excursion.city() == city_;
}

bool ByServicePrice::operator()(const TravelService* left,
                                const TravelService* right) const {
  return left->CalculatePrice() < right->CalculatePrice();
}

ExcursionPrinter::ExcursionPrinter() : printed_(0) {}

void ExcursionPrinter::operator()(const Excursion& excursion) {
  ++printed_;
  std::cout << "  " << printed_ << ". " << excursion << "\n";
}

int ExcursionPrinter::printed() const { return printed_; }
