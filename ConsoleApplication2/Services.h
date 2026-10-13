#ifndef TRAVEL_AGENCY_SERVICES_H_
#define TRAVEL_AGENCY_SERVICES_H_

#include <fstream>
#include <string>

class TravelService {
 public:
  TravelService(const std::string& name, double base_price);
  virtual ~TravelService();

  virtual std::string Category() const = 0;
  virtual double CalculatePrice() const = 0;
  virtual void DisplayInfo() const;
  virtual void Write(std::ofstream& out) const;
  virtual void Read(std::ifstream& in);

  void PrintLabel() const;
  const std::string& name() const;
  int id() const;

  static int AliveCount();

 protected:
  std::string name_;
  double base_price_;

 private:
  int id_;

  static int next_id_;
  static int alive_count_;
};

class InsuranceService : virtual public TravelService {
 public:
  InsuranceService(const std::string& name, double base_price,
                   double coverage_amount, int risk_level);
  ~InsuranceService() override;

  std::string Category() const override;
  double CalculatePrice() const override;
  void DisplayInfo() const override;
  void Write(std::ofstream& out) const override;
  void Read(std::ifstream& in) override;

  virtual bool CoversTrip(double trip_cost) const;

 protected:
  double InsuranceFee() const;
  void PrintInsuranceDetails() const;
  void WriteInsuranceFields(std::ofstream& out) const;
  void ReadInsuranceFields(std::ifstream& in);

 private:
  double coverage_amount_;
  int risk_level_;
};

class VisaService : virtual public TravelService {
 public:
  VisaService(const std::string& name, double base_price,
              const std::string& country, bool is_urgent);
  ~VisaService() override;

  std::string Category() const override;
  double CalculatePrice() const override;
  void DisplayInfo() const override;
  void Write(std::ofstream& out) const override;
  void Read(std::ifstream& in) override;

  virtual int ProcessingDays() const;

 protected:
  double VisaFee() const;
  void PrintVisaDetails() const;
  void WriteVisaFields(std::ofstream& out) const;
  void ReadVisaFields(std::ifstream& in);

 private:
  std::string country_;
  bool is_urgent_;
};

class TransferService : public TravelService {
 public:
  TransferService(const std::string& name, double base_price,
                  const std::string& route, double distance_km);
  ~TransferService() override;

  std::string Category() const override;
  double CalculatePrice() const override;
  void DisplayInfo() const override;
  void Write(std::ofstream& out) const override;
  void Read(std::ifstream& in) override;

  virtual double TravelTimeHours() const;

  void PrintLabel() const;

 private:
  std::string route_;
  double distance_km_;
};

class FullPackageService : public InsuranceService, public VisaService {
 public:
  FullPackageService(const std::string& name, double base_price,
                     double coverage_amount, int risk_level,
                     const std::string& country, bool is_urgent,
                     double discount_percent);
  ~FullPackageService() override;

  std::string Category() const override;
  double CalculatePrice() const override;
  void DisplayInfo() const override;
  void Write(std::ofstream& out) const override;
  void Read(std::ifstream& in) override;
  int ProcessingDays() const override;

  virtual double Savings() const;

 private:
  double PriceWithoutDiscount() const;

  double discount_percent_;
};

class ServiceCatalog {
 public:
  static const int kStaticCapacity = 5;

  explicit ServiceCatalog(int dynamic_capacity);
  ServiceCatalog(const ServiceCatalog&) = delete;
  ServiceCatalog& operator=(const ServiceCatalog&) = delete;
  ~ServiceCatalog();

  void AddStatic(TravelService* service);
  void AddDynamic(TravelService* service);
  void RemoveDynamic(int index);
  int Service_Static(double max_price);
  int Service_Dinamic(double max_price);
  void ShowAll() const;

 private:
  TravelService* static_services_[kStaticCapacity] = {};
  int static_count_ = 0;
  TravelService** dynamic_services_;
  int dynamic_capacity_;
  int dynamic_count_ = 0;
};

#endif  // TRAVEL_AGENCY_SERVICES_H_
