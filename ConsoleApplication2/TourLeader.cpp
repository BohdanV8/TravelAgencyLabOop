#include <iostream>

#include "Staff.h"

namespace {

constexpr int kLeaderExperienceYears = 5;
constexpr double kLeaderDailyRate = 2000.0;

}  // namespace

TourLeader::TourLeader(const std::string& full_name_in, int age_in,
                       const std::string& phone_number_in,
                       const std::string& passport_number,
                       const std::string& email, const std::string& city,
                       const std::string& languages,
                       const std::string& group_name, int max_group_size)
    : TourGuide(full_name_in, age_in, phone_number_in, passport_number, email,
                city, languages, kLeaderExperienceYears, kLeaderDailyRate),
      group_name_(group_name),
      max_group_size_(max_group_size) {
  std::cout << "  [TourLeader] конструктор: " << full_name << "\n";
}

TourLeader::~TourLeader() {
  std::cout << "  [TourLeader] деструктор: " << full_name << "\n";
}

int TourLeader::group_size() const { return group_size_; }

bool TourLeader::AddTourist(const Tourist& tourist) {
  if (group_size_ >= max_group_size_) {
    std::cout << "Група \"" << group_name_ << "\" заповнена, "
              << tourist.full_name << " не додано\n";
    return false;
  }
  ++group_size_;
  std::cout << tourist.full_name << " доданий(а) до групи \"" << group_name_
            << "\" (" << group_size_ << "/" << max_group_size_ << ")\n";
  return true;
}

void TourLeader::HoldBriefing() {
  ++briefings_held_;
  std::cout << "Керівник " << full_name << " проводить інструктаж: збір о "
            << departure_time_ << ", місце - " << meeting_point_
            << ", екстрений телефон " << emergency_phone_ << "\n";
}

void TourLeader::StartGroupTour(const std::string& country) {
  std::cout << "Група \"" << group_name_ << "\" з " << group_size_
            << " туристів вирушає в тур\n";
  LeadTour(country);
}

void TourLeader::DisplayInfo() const {
  TourGuide::DisplayInfo();
  std::cout << "  Роль: керівник групи\n"
            << "  Група: " << group_name_ << "\n"
            << "  Учасників: " << group_size_ << "/" << max_group_size_
            << "\n"
            << "  Місце збору: " << meeting_point_ << "\n"
            << "  Час відправлення: " << departure_time_ << "\n"
            << "  Екстрений телефон: " << emergency_phone_ << "\n"
            << "  Аптечка: " << (has_first_aid_kit_ ? "є" : "немає") << "\n"
            << "  Проведено інструктажів: " << briefings_held_ << "\n";
}
