#ifndef TRAVEL_AGENCY_STAFF_H_
#define TRAVEL_AGENCY_STAFF_H_

#include <string>

#include "TravelAgency.h"

class Person {
 public:
  std::string full_name;
  int age;
  std::string phone_number;

  Person(const std::string& full_name_in, int age_in,
         const std::string& phone_number_in,
         const std::string& passport_number, const std::string& email,
         const std::string& city);
  ~Person();

  void Introduce() const;
  std::string GetContactInfo() const;
  bool IsAdult() const;
  int id() const;
  void DisplayInfo() const;

 protected:
  std::string passport_number_;
  std::string email_;
  std::string city_;

 private:
  int id_;
  std::string nationality_ = "Україна";

  static int next_id_;
};

class TourGuide : public Person {
 public:
  TourGuide(const std::string& full_name_in, int age_in,
            const std::string& phone_number_in,
            const std::string& passport_number, const std::string& email,
            const std::string& city, const std::string& languages,
            int experience_years, double daily_rate);
  ~TourGuide();

  void LeadTour(const std::string& country);
  void FinishTour(double tour_rating);
  double CalculateFee(int days) const;
  void ShowInheritedAccess() const;
  void DisplayInfo() const;

 private:
  std::string languages_;
  int experience_years_;
  double daily_rate_;
  int tours_led_ = 0;
  double rating_ = 5.0;
  std::string current_country_ = "немає";
  std::string specialization_ = "Екскурсійні тури";
  bool is_available_ = true;
};

class TravelAgent : protected Person {
 public:
  TravelAgent(const std::string& full_name_in, int age_in,
              const std::string& phone_number_in,
              const std::string& passport_number, const std::string& email,
              const std::string& city, const std::string& office,
              double salary);
  ~TravelAgent();

  using Person::full_name;
  using Person::Introduce;

  void SellVoucher(Tourist& tourist, const Voucher& voucher);
  double CalculateCommission() const;
  double CalculateMonthlyIncome() const;
  void ShowInheritedAccess() const;
  void DisplayInfo() const;

 private:
  std::string office_;
  double salary_;
  std::string position_ = "Менеджер з продажу";
  double commission_percent_ = 5.0;
  int sales_count_ = 0;
  double sales_total_ = 0.0;
  std::string work_phone_ = "+380-44-000-00-00";
  int hire_year_ = 2024;
};

class BusDriver : private Person {
 public:
  BusDriver(const std::string& full_name_in, int age_in,
            const std::string& phone_number_in,
            const std::string& passport_number, const std::string& email,
            const std::string& city, const std::string& bus_number,
            int seats);
  ~BusDriver();

  const std::string& name() const;
  bool CanTakeGroup(int group_size) const;
  void DriveTransfer(const std::string& route, double distance_km);
  double CalculateFuelUsed() const;
  void ShowInheritedAccess() const;
  void DisplayInfo() const;

 private:
  std::string bus_number_;
  int seats_;
  std::string license_category_ = "D";
  std::string current_route_ = "немає";
  int driving_experience_ = 10;
  int trips_done_ = 0;
  double km_driven_ = 0.0;
  double fuel_per_100km_ = 25.0;
};

class TourLeader : private TourGuide {
 public:
  TourLeader(const std::string& full_name_in, int age_in,
             const std::string& phone_number_in,
             const std::string& passport_number, const std::string& email,
             const std::string& city, const std::string& languages,
             const std::string& group_name, int max_group_size);
  ~TourLeader();

  using Person::full_name;
  using Person::Introduce;
  using TourGuide::LeadTour;

  int group_size() const;
  bool AddTourist(const Tourist& tourist);
  void HoldBriefing();
  void StartGroupTour(const std::string& country);
  void DisplayInfo() const;

 private:
  std::string group_name_;
  int max_group_size_;
  int group_size_ = 0;
  std::string meeting_point_ = "Аеропорт Бориспіль";
  std::string departure_time_ = "08:00";
  std::string emergency_phone_ = "+380-67-000-00-00";
  bool has_first_aid_kit_ = true;
  int briefings_held_ = 0;
};

class InsuranceSpecialist : virtual public Person {
 public:
  InsuranceSpecialist(const std::string& full_name_in, int age_in,
                      const std::string& phone_number_in,
                      const std::string& passport_number,
                      const std::string& email, const std::string& city,
                      const std::string& insurance_company,
                      double policy_price);
  ~InsuranceSpecialist();

  bool CanCover(double trip_cost) const;
  void IssuePolicy(Voucher& voucher);
  double CalculateEarnings() const;
  void ShowInsuranceInfo() const;
  void DisplayInfo() const;

 private:
  std::string insurance_company_;
  double policy_price_;
  int policies_issued_ = 0;
  double total_premiums_ = 0.0;
  double max_coverage_ = 50000.0;
  double commission_rate_ = 0.1;
  std::string license_number_ = "INS-2024-001";
  int certification_year_ = 2022;
};

class VisaSpecialist : virtual public Person {
 public:
  VisaSpecialist(const std::string& full_name_in, int age_in,
                 const std::string& phone_number_in,
                 const std::string& passport_number, const std::string& email,
                 const std::string& city, double visa_fee);
  ~VisaSpecialist();

  bool IsCountrySupported(const std::string& country) const;
  void ProcessVisa(Tourist& tourist);
  double CalculateEarnings() const;
  void ShowVisaInfo() const;
  void DisplayInfo() const;

 private:
  double visa_fee_;
  int processed_applications_ = 0;
  int approved_applications_ = 0;
  int processing_days_ = 10;
  std::string supported_countries_ = "Італія, Іспанія, Греція, Японія";
  std::string embassy_city_ = "Київ";
  std::string certificate_number_ = "VISA-2023-017";
  double total_fees_ = 0.0;
};

class TravelConsultant : public InsuranceSpecialist, public VisaSpecialist {
 public:
  TravelConsultant(const std::string& full_name_in, int age_in,
                   const std::string& phone_number_in,
                   const std::string& passport_number,
                   const std::string& email, const std::string& city,
                   const std::string& insurance_company, double policy_price,
                   double visa_fee, double consultation_fee);
  ~TravelConsultant();

  void PrepareFullPackage(Tourist& tourist, Voucher& voucher);
  double CalculateTotalEarnings() const;
  void DisplayInfo() const;

 private:
  double consultation_fee_;
  int clients_served_ = 0;
  double package_discount_percent_ = 5.0;
  std::string office_hours_ = "09:00-18:00";
  double rating_ = 5.0;
  std::string specialization_ = "Повний супровід подорожі";
  bool works_online_ = true;
  std::string languages_ = "українська, англійська";
};

#endif  // TRAVEL_AGENCY_STAFF_H_
