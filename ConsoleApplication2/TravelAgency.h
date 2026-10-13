#ifndef TRAVEL_AGENCY_TRAVEL_AGENCY_H_
#define TRAVEL_AGENCY_TRAVEL_AGENCY_H_

#include <fstream>
#include <string>
#include <vector>

class Tourist;

class Voucher {
 public:
  std::string country;
  int duration_days;
  double base_price;

  Voucher();
  Voucher(const std::string& country_in, int duration_days_in,
          double base_price_in, bool visa_required_in,
          const std::string& travel_dates_in);
  Voucher(const Voucher& other);
  ~Voucher();

  double insurance_cost() const;
  bool has_insurance() const;
  bool visa_required() const;
  const std::string& travel_dates() const;
  int voucher_id() const;

  void DisplayInfo() const;
  double GetFinalPrice() const;
  double GetFinalPrice(double additional_fee) const;
  void ApplyDiscountForTourist(const Tourist& tourist);
  Voucher CombineWith(const Voucher& other) const;
  void AddInsurance(double cost);

  void SaveToFile(std::ofstream& out) const;
  void LoadFromFile(std::ifstream& in);

  void GenerateAndSortRandomDurations() const;

 private:
  double insurance_cost_;
  bool has_insurance_;
  bool visa_required_;
  std::string travel_dates_;
  int voucher_id_;

  static int next_voucher_id_;
};

class Tourist {
 public:
  std::string full_name;
  int age;
  std::string passport_number;

  Tourist();
  Tourist(const std::string& full_name_in, int age_in,
          const std::string& passport_number_in);
  Tourist(const Tourist& other);
  ~Tourist();

  static int AliveCount();

  const std::string& phone_number() const;
  void set_phone_number(const std::string& phone);
  const std::string& email() const;
  void set_email(const std::string& email_in);
  double total_paid() const;
  int tourist_id() const;
  const Voucher& voucher() const;

  void DisplayInfo() const;
  double CalculateTotalCost() const;
  double CalculateTotalCost(double discount_percent) const;
  void BookVoucher(const Voucher& voucher_in);
  Tourist UpgradeTourist(const std::string& new_passport_number) const;
  bool ApplyForVisa();

  void SaveToFile(std::ofstream& out) const;
  void LoadFromFile(std::ifstream& in);

  void GenerateAndSortRandomIds() const;

 private:
  std::string phone_number_;
  std::string email_;
  double total_paid_;
  int tourist_id_;
  Voucher voucher_;

  static int next_tourist_id_;
  static int alive_count_;
};

class TravelAgency {
 public:
  explicit TravelAgency(const std::string& name);
  ~TravelAgency();

  const std::string& name() const;
  void AddClient(Tourist* tourist);
  void ShowClients() const;

 private:
  const std::string name_;
  std::vector<Tourist*> clients_;
};

class Booking {
 public:
  Booking(TravelAgency& agency, Tourist& tourist, Voucher& voucher);
  ~Booking();

  void Confirm();
  void DisplayInfo() const;

 private:
  const int booking_number_;
  TravelAgency& agency_;
  Tourist& tourist_;
  Voucher& voucher_;

  static int next_booking_number_;
};

#endif  // TRAVEL_AGENCY_TRAVEL_AGENCY_H_
