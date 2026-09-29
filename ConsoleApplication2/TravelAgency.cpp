// travel_agency.cpp
//
// Реалізація методів класів Voucher та Tourist.
// Кожен коментар з номером пункту посилається на завдання третього
// рівня лабораторної роботи №2 (п.11 - коментарі в тексті програми).

#include "TravelAgency.h"

#include <algorithm>  // std::sort
#include <cstdlib>    // std::rand
#include <ctime>      // std::time
#include <iostream>

int Voucher::next_voucher_id_ = 1;
int Tourist::next_tourist_id_ = 1;

// ===================== Voucher =====================

Voucher::Voucher()
    : country("Не вказано"),
    duration_days(0),
    base_price(0.0),
    insurance_cost_(0.0),
    has_insurance_(false),
    visa_required_(false),
    travel_dates_("Не вказано"),
    voucher_id_(next_voucher_id_++) {
}

Voucher::Voucher(const std::string& country_in, int duration_days_in,
    double base_price_in, bool visa_required_in,
    const std::string& travel_dates_in)
    : country(country_in),
    duration_days(duration_days_in),
    base_price(base_price_in),
    insurance_cost_(0.0),
    has_insurance_(false),
    visa_required_(visa_required_in),
    travel_dates_(travel_dates_in),
    voucher_id_(next_voucher_id_++) {
}

double Voucher::insurance_cost() const { return insurance_cost_; }
bool Voucher::has_insurance() const { return has_insurance_; }
bool Voucher::visa_required() const { return visa_required_; }
const std::string& Voucher::travel_dates() const { return travel_dates_; }
int Voucher::voucher_id() const { return voucher_id_; }

// Використовує усі 8 полів класу (п.2 третього рівня).
void Voucher::DisplayInfo() const {
    std::cout << "--- Путівка #" << voucher_id_ << " ---\n"
        << "Країна: " << country << "\n"
        << "Тривалість: " << duration_days << " днів\n"
        << "Базова ціна: " << base_price << "\n"
        << "Дати подорожі: " << travel_dates_ << "\n"
        << "Потрібна віза: " << (visa_required_ ? "так" : "ні") << "\n"
        << "Страхування: "
        << (has_insurance_ ? std::to_string(insurance_cost_) : "немає")
        << "\n";
}

// Перевантаження №1: без додаткового збору.
double Voucher::GetFinalPrice() const {
    return base_price + (has_insurance_ ? insurance_cost_ : 0.0);
}

// Перевантаження №2: з додатковим збором (напр., за терміновість).
double Voucher::GetFinalPrice(double additional_fee) const {
    return GetFinalPrice() + additional_fee;
}

// Метод приймає об'єкт класу Tourist як параметр.
void Voucher::ApplyDiscountForTourist(const Tourist& tourist) {
    // Знижка для туристів віком від 60 років.
    if (tourist.age >= 60) {
        base_price *= 0.9;
    }
}

// Метод повертає тип класу Voucher.
Voucher Voucher::CombineWith(const Voucher& other) const {
    Voucher combined(*this);
    combined.duration_days += other.duration_days;
    combined.base_price += other.base_price;
    combined.travel_dates_ = travel_dates_ + " + " + other.travel_dates_;
    return combined;
}

void Voucher::AddInsurance(double cost) {
    has_insurance_ = true;
    insurance_cost_ = cost;
}

void Voucher::SaveToFile(std::ofstream& out) const {
    out << country << '\n'
        << duration_days << '\n'
        << base_price << '\n'
        << insurance_cost_ << '\n'
        << has_insurance_ << '\n'
        << visa_required_ << '\n'
        << travel_dates_ << '\n'
        << voucher_id_ << '\n';
}

void Voucher::LoadFromFile(std::ifstream& in) {
    std::getline(in, country);
    in >> duration_days >> base_price >> insurance_cost_ >> has_insurance_ >>
        visa_required_;
    in.ignore();
    std::getline(in, travel_dates_);
    in >> voucher_id_;
}

// Додатковий метод: динамічний масив випадкового розміру із значень
// цілочисельного поля duration_days, з подальшим сортуванням.
void Voucher::GenerateAndSortRandomDurations() const {
    int size = std::rand() % 10 + 5;  // випадковий розмір від 5 до 14
    int* durations = new int[size];
    for (int i = 0; i < size; ++i) {
        durations[i] = std::rand() % 30 + 1;  // 1..30 днів
    }
    std::sort(durations, durations + size);
    std::cout << "Відсортовані тривалості (розмір масиву " << size
        << "): ";
    for (int i = 0; i < size; ++i) {
        std::cout << durations[i] << " ";
    }
    std::cout << "\n";
    delete[] durations;
}

// ===================== Tourist =====================

Tourist::Tourist()
    : full_name("Не вказано"),
    age(0),
    passport_number("Не вказано"),
    phone_number_(""),
    email_(""),
    total_paid_(0.0),
    tourist_id_(next_tourist_id_++),
    voucher_() {
}

Tourist::Tourist(const std::string& full_name_in, int age_in,
    const std::string& passport_number_in)
    : full_name(full_name_in),
    age(age_in),
    passport_number(passport_number_in),
    phone_number_(""),
    email_(""),
    total_paid_(0.0),
    tourist_id_(next_tourist_id_++),
    voucher_() {
}

const std::string& Tourist::phone_number() const { return phone_number_; }
void Tourist::set_phone_number(const std::string& phone) {
    phone_number_ = phone;
}
const std::string& Tourist::email() const { return email_; }
void Tourist::set_email(const std::string& email_in) { email_ = email_in; }
double Tourist::total_paid() const { return total_paid_; }
int Tourist::tourist_id() const { return tourist_id_; }
const Voucher& Tourist::voucher() const { return voucher_; }

// Використовує усі 8 полів класу, включно з вкладеним об'єктом voucher_.
void Tourist::DisplayInfo() const {
    std::cout << "=== Турист #" << tourist_id_ << " ===\n"
        << "ПІБ: " << full_name << "\n"
        << "Вік: " << age << "\n"
        << "Паспорт: " << passport_number << "\n"
        << "Телефон: " << phone_number_ << "\n"
        << "Email: " << email_ << "\n"
        << "Сплачено: " << total_paid_ << "\n";
    voucher_.DisplayInfo();
}

// Перевантаження №1: повна вартість без знижки.
double Tourist::CalculateTotalCost() const { return voucher_.GetFinalPrice(); }

// Перевантаження №2: вартість зі знижкою у відсотках.
double Tourist::CalculateTotalCost(double discount_percent) const {
    double cost = CalculateTotalCost();
    return cost - cost * (discount_percent / 100.0);
}

// Метод приймає об'єкт класу Voucher як параметр і демонструє сценарій
// взаємодії двох об'єктів "турист купує путівку" (п.10 третього рівня).
void Tourist::BookVoucher(const Voucher& voucher_in) {
    voucher_ = voucher_in;
    total_paid_ += voucher_.GetFinalPrice();
    std::cout << full_name << " придбав(ла) путівку до " << voucher_.country
        << " на суму " << voucher_.GetFinalPrice() << "\n";
}

// Метод повертає тип класу Tourist.
Tourist Tourist::UpgradeTourist(const std::string& new_passport_number) const {
    Tourist upgraded(*this);
    upgraded.passport_number = new_passport_number;
    return upgraded;
}

// Оформлення візи на основі даних путівки, вкладеної в туриста.
bool Tourist::ApplyForVisa() {
    if (voucher_.visa_required()) {
        std::cout << full_name << " подав(ла) заявку на візу до "
            << voucher_.country << "\n";
        return true;
    }
    std::cout << "Віза для " << full_name << " не потрібна\n";
    return false;
}

void Tourist::SaveToFile(std::ofstream& out) const {
    out << full_name << '\n'
        << age << '\n'
        << passport_number << '\n'
        << phone_number_ << '\n'
        << email_ << '\n'
        << total_paid_ << '\n'
        << tourist_id_ << '\n';
    voucher_.SaveToFile(out);
}

void Tourist::LoadFromFile(std::ifstream& in) {
    std::getline(in, full_name);
    in >> age;
    in.ignore();
    std::getline(in, passport_number);
    std::getline(in, phone_number_);
    std::getline(in, email_);
    in >> total_paid_ >> tourist_id_;
    in.ignore();
    voucher_.LoadFromFile(in);
}

// Додатковий метод: динамічний масив випадкового розміру із значень
// цілочисельного поля age, з подальшим сортуванням (п.12 третього рівня).
void Tourist::GenerateAndSortRandomIds() const {
    int size = std::rand() % 10 + 5;  // випадковий розмір від 5 до 14
    int* ages = new int[size];
    for (int i = 0; i < size; ++i) {
        ages[i] = std::rand() % 60 + 18;  // 18..77 років
    }
    std::sort(ages, ages + size);
    std::cout << "Відсортовані значення віку (розмір масиву " << size
        << "): ";
    for (int i = 0; i < size; ++i) {
        std::cout << ages[i] << " ";
    }
    std::cout << "\n";
    delete[] ages;
}