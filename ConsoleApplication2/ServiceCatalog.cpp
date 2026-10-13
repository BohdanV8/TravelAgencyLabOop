#include <iostream>
#include <stdexcept>

#include "Services.h"

ServiceCatalog::ServiceCatalog(int dynamic_capacity)
    : dynamic_services_(nullptr), dynamic_capacity_(dynamic_capacity) {
  if (dynamic_capacity <= 0) {
    throw std::invalid_argument("місткість каталогу має бути більшою за 0");
  }
  dynamic_services_ = new TravelService*[dynamic_capacity];
}

ServiceCatalog::~ServiceCatalog() {
  for (int i = 0; i < dynamic_count_; ++i) {
    delete dynamic_services_[i];
  }
  delete[] dynamic_services_;
}

void ServiceCatalog::AddStatic(TravelService* service) {
  if (service == nullptr) {
    throw std::invalid_argument("порожній покажчик на послугу");
  }
  if (static_count_ == kStaticCapacity) {
    throw std::overflow_error("статичний масив заповнений");
  }
  static_services_[static_count_++] = service;
}

void ServiceCatalog::AddDynamic(TravelService* service) {
  if (service == nullptr) {
    throw std::invalid_argument("порожній покажчик на послугу");
  }
  if (dynamic_count_ == dynamic_capacity_) {
    delete service;
    throw std::overflow_error("динамічний масив заповнений, об'єкт знищено");
  }
  dynamic_services_[dynamic_count_++] = service;
}

void ServiceCatalog::RemoveDynamic(int index) {
  if (index < 0 || index >= dynamic_count_) {
    throw std::out_of_range("немає послуги з номером " +
                            std::to_string(index + 1));
  }
  delete dynamic_services_[index];
  for (int i = index; i < dynamic_count_ - 1; ++i) {
    dynamic_services_[i] = dynamic_services_[i + 1];
  }
  --dynamic_count_;
}

int ServiceCatalog::Service_Static(double max_price) {
  if (max_price < 0) {
    throw std::invalid_argument("ціна не може бути від'ємною");
  }
  if (static_count_ == 0) {
    throw std::runtime_error("статичний масив порожній");
  }
  int kept = 0;
  for (int i = 0; i < static_count_; ++i) {
    if (static_services_[i]->CalculatePrice() > max_price) {
      std::cout << "Прибрано зі статичного масиву: "
                << static_services_[i]->name() << "\n";
    } else {
      static_services_[kept++] = static_services_[i];
    }
  }
  int removed = static_count_ - kept;
  static_count_ = kept;
  return removed;
}

int ServiceCatalog::Service_Dinamic(double max_price) {
  if (max_price < 0) {
    throw std::invalid_argument("ціна не може бути від'ємною");
  }
  if (dynamic_count_ == 0) {
    throw std::runtime_error("динамічний масив порожній");
  }
  int kept = 0;
  for (int i = 0; i < dynamic_count_; ++i) {
    if (dynamic_services_[i]->CalculatePrice() > max_price) {
      std::cout << "Видалено з динамічного масиву: "
                << dynamic_services_[i]->name() << "\n";
      delete dynamic_services_[i];
    } else {
      dynamic_services_[kept++] = dynamic_services_[i];
    }
  }
  int removed = dynamic_count_ - kept;
  dynamic_count_ = kept;
  return removed;
}

void ServiceCatalog::ShowAll() const {
  std::cout << "Статичні послуги (" << static_count_ << "):\n";
  for (int i = 0; i < static_count_; ++i) {
    std::cout << "  " << i + 1 << ". " << static_services_[i]->name() << " - "
              << static_services_[i]->Category() << ", "
              << static_services_[i]->CalculatePrice() << "\n";
  }
  std::cout << "Динамічні послуги (" << dynamic_count_ << "):\n";
  for (int i = 0; i < dynamic_count_; ++i) {
    std::cout << "  " << i + 1 << ". " << dynamic_services_[i]->name()
              << " - " << dynamic_services_[i]->Category() << ", "
              << dynamic_services_[i]->CalculatePrice() << "\n";
  }
}
