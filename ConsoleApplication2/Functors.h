#ifndef TRAVEL_AGENCY_FUNCTORS_H_
#define TRAVEL_AGENCY_FUNCTORS_H_

#include <string>

class Excursion;
class TravelService;

class PriceAtMost {
 public:
  explicit PriceAtMost(double limit);

  bool operator()(const Excursion& excursion) const;

 private:
  double limit_;
};

class InCity {
 public:
  explicit InCity(const std::string& city);

  bool operator()(const Excursion& excursion) const;

 private:
  std::string city_;
};

class ByServicePrice {
 public:
  bool operator()(const TravelService* left,
                  const TravelService* right) const;
};

class ExcursionPrinter {
 public:
  ExcursionPrinter();

  void operator()(const Excursion& excursion);
  int printed() const;

 private:
  int printed_;
};

#endif  // TRAVEL_AGENCY_FUNCTORS_H_
