#ifndef TRAVEL_AGENCY_EXCURSION_H_
#define TRAVEL_AGENCY_EXCURSION_H_

#include <ostream>
#include <string>

class Excursion {
 public:
  Excursion();
  Excursion(const std::string& title, const std::string& city, double price,
            double hours);

  const std::string& title() const;
  const std::string& city() const;
  double price() const;
  double hours() const;

  Excursion operator+(const Excursion& other) const;
  bool operator==(const Excursion& other) const;

  friend std::ostream& operator<<(std::ostream& out,
                                  const Excursion& excursion);

 private:
  std::string title_;
  std::string city_;
  double price_;
  double hours_;
};

#endif  // TRAVEL_AGENCY_EXCURSION_H_
