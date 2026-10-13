#include <iostream>

#include "TravelAgency.h"

int Booking::next_booking_number_ = 1;

Booking::Booking(TravelAgency& agency, Tourist& tourist, Voucher& voucher)
    : booking_number_(next_booking_number_++),
      agency_(agency),
      tourist_(tourist),
      voucher_(voucher) {
  std::cout << "[Booking #" << booking_number_
            << "] конструктор з параметрами\n";
}

Booking::~Booking() {
  std::cout << "[Booking #" << booking_number_ << "] деструктор\n";
}

void Booking::Confirm() {
  std::cout << "Бронювання #" << booking_number_ << " підтверджено\n";
  voucher_.ApplyDiscountForTourist(tourist_);
  tourist_.BookVoucher(voucher_);
  tourist_.ApplyForVisa();
  agency_.AddClient(&tourist_);
}

void Booking::DisplayInfo() const {
  std::cout << "Бронювання #" << booking_number_ << ": " << tourist_.full_name
            << " -> " << voucher_.country << " через агенцію \""
            << agency_.name() << "\"\n";
}
