#ifndef TRAVEL_AGENCY_COLLECTION_H_
#define TRAVEL_AGENCY_COLLECTION_H_

#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Collection {
 public:
  Collection(const std::string& title, int capacity);
  Collection(const Collection&) = delete;
  Collection& operator=(const Collection&) = delete;
  ~Collection();

  void Add(const T& item);
  void RemoveAt(int index);
  T& operator[](int index);
  const T& operator[](int index) const;
  int Size() const;
  bool Contains(const T& item) const;
  T Total() const;
  const T& LastRemoved() const;
  void Print() const;

 private:
  void Grow();
  void CheckIndex(int index) const;

  std::string title_;
  T* items_;
  int size_;
  int capacity_;
  T last_removed_;
  bool has_last_removed_;
};

template <typename T>
Collection<T>::Collection(const std::string& title, int capacity)
    : title_(title),
      items_(nullptr),
      size_(0),
      capacity_(capacity),
      last_removed_(),
      has_last_removed_(false) {
  if (capacity <= 0) {
    throw std::invalid_argument("місткість колекції має бути більшою за 0");
  }
  items_ = new T[capacity];
}

template <typename T>
Collection<T>::~Collection() {
  delete[] items_;
}

template <typename T>
void Collection<T>::Add(const T& item) {
  if (size_ == capacity_) {
    Grow();
  }
  items_[size_++] = item;
}

template <typename T>
void Collection<T>::RemoveAt(int index) {
  CheckIndex(index);
  last_removed_ = items_[index];
  has_last_removed_ = true;
  for (int i = index; i < size_ - 1; ++i) {
    items_[i] = items_[i + 1];
  }
  --size_;
}

template <typename T>
T& Collection<T>::operator[](int index) {
  CheckIndex(index);
  return items_[index];
}

template <typename T>
const T& Collection<T>::operator[](int index) const {
  CheckIndex(index);
  return items_[index];
}

template <typename T>
int Collection<T>::Size() const {
  return size_;
}

template <typename T>
bool Collection<T>::Contains(const T& item) const {
  for (int i = 0; i < size_; ++i) {
    if (items_[i] == item) {
      return true;
    }
  }
  return false;
}

template <typename T>
T Collection<T>::Total() const {
  if (size_ == 0) {
    throw std::runtime_error("колекція \"" + title_ + "\" порожня");
  }
  T total = items_[0];
  for (int i = 1; i < size_; ++i) {
    total = total + items_[i];
  }
  return total;
}

template <typename T>
const T& Collection<T>::LastRemoved() const {
  if (!has_last_removed_) {
    throw std::logic_error("з колекції ще нічого не видаляли");
  }
  return last_removed_;
}

template <typename T>
void Collection<T>::Print() const {
  std::cout << title_ << " (" << size_ << " з " << capacity_ << "):\n";
  for (int i = 0; i < size_; ++i) {
    std::cout << "  [" << i << "] " << items_[i] << "\n";
  }
}

template <typename T>
void Collection<T>::Grow() {
  int new_capacity = capacity_ * 2;
  T* new_items = new T[new_capacity];
  for (int i = 0; i < size_; ++i) {
    new_items[i] = items_[i];
  }
  delete[] items_;
  items_ = new_items;
  capacity_ = new_capacity;
}

template <typename T>
void Collection<T>::CheckIndex(int index) const {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("індекс " + std::to_string(index) +
                            " поза межами колекції \"" + title_ + "\"");
  }
}

#endif  // TRAVEL_AGENCY_COLLECTION_H_
