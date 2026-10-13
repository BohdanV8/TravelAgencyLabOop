#include <iostream>

#include "Staff.h"

TourGuide::TourGuide(const std::string& full_name_in, int age_in,
                     const std::string& phone_number_in,
                     const std::string& passport_number,
                     const std::string& email, const std::string& city,
                     const std::string& languages, int experience_years,
                     double daily_rate)
    : Person(full_name_in, age_in, phone_number_in, passport_number, email,
             city),
      languages_(languages),
      experience_years_(experience_years),
      daily_rate_(daily_rate) {
  std::cout << "  [TourGuide] конструктор: " << full_name << "\n";
}

TourGuide::~TourGuide() {
  std::cout << "  [TourGuide] деструктор: " << full_name << "\n";
}

void TourGuide::LeadTour(const std::string& country) {
  current_country_ = country;
  is_available_ = false;
  ++tours_led_;
  std::cout << "Гід " << full_name << " веде екскурсію: " << country << "\n";
}

void TourGuide::FinishTour(double tour_rating) {
  rating_ = (rating_ + tour_rating) / 2;
  current_country_ = "немає";
  is_available_ = true;
  std::cout << "Гід " << full_name << " завершив тур, рейтинг: " << rating_
            << "\n";
}

double TourGuide::CalculateFee(int days) const { return daily_rate_ * days; }

void TourGuide::ShowInheritedAccess() const {
  std::cout << "TourGuide (public-наслідування) всередині класу бачить:\n"
            << "  public:    " << full_name << ", " << age << ", "
            << phone_number << "\n"
            << "  protected: " << passport_number_ << ", " << email_ << ", "
            << city_ << "\n"
            << "  private Person доступні лише через методи, id = " << id()
            << "\n";
}

void TourGuide::DisplayInfo() const {
  Person::DisplayInfo();
  std::cout << "  Посада: гід\n"
            << "  Мови: " << languages_ << "\n"
            << "  Досвід: " << experience_years_ << " років\n"
            << "  Ставка за день: " << daily_rate_ << "\n"
            << "  Проведено турів: " << tours_led_ << "\n"
            << "  Рейтинг: " << rating_ << "\n"
            << "  Поточна країна: " << current_country_ << "\n"
            << "  Спеціалізація: " << specialization_ << "\n"
            << "  Вільний: " << (is_available_ ? "так" : "ні") << "\n";
}
