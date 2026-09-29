// travel_agency.h
//
// Лабораторна робота №2, третій рівень складності, варіант 8
// "Туристична агенція".
//
// Два класи: Voucher (Путівка) та Tourist (Турист).
// Клас Tourist містить в собі об'єкт класу Voucher (композиція,
// п.3 завдання третього рівня) без використання дружніх функцій.

#ifndef TRAVEL_AGENCY_TRAVEL_AGENCY_H_
#define TRAVEL_AGENCY_TRAVEL_AGENCY_H_

#include <fstream>
#include <string>

// Попереднє оголошення класу Tourist, оскільки метод Voucher повинен
// приймати об'єкт Tourist як параметр (п.4 - "один метод приймає в
// якості параметрів об'єкт класу").
class Tourist;

// ---------------------------------------------------------------------------
// Клас Voucher (Путівка).
// 8 полів: 3 публічні + 5 приватні (п.1, п.2 третього рівня).
// ---------------------------------------------------------------------------
class Voucher {
 public:
  // --- Публічні поля (3) ---
  std::string country;      // Країна подорожі
  int duration_days;        // Тривалість подорожі, днів
  double base_price;        // Базова ціна путівки

  Voucher();
  Voucher(const std::string& country_in, int duration_days_in,
          double base_price_in, bool visa_required_in,
          const std::string& travel_dates_in);

  // --- Доступ до приватних полів ---
  double insurance_cost() const;
  bool has_insurance() const;
  bool visa_required() const;
  const std::string& travel_dates() const;
  int voucher_id() const;

  // --- 6 методів обробки даних (п.4 третього рівня) ---

  // Виводить на екран усі поля путівки (використовує усі поля, п.2).
  void DisplayInfo() const;

  // Перевантажені методи (2 з 6 мають бути перевантаженими):
  // Повертає кінцеву ціну путівки без додаткових зборів.
  double GetFinalPrice() const;
  // Повертає кінцеву ціну путівки з урахуванням додаткового збору.
  double GetFinalPrice(double additional_fee) const;

  // Метод, що приймає об'єкт іншого класу (Tourist) як параметр:
  // знижка для туристів старшого віку.
  void ApplyDiscountForTourist(const Tourist& tourist);

  // Метод, що повертає тип класу (Voucher): об'єднання двох путівок
  // (напр., подовження туру за рахунок другої путівки).
  Voucher CombineWith(const Voucher& other) const;

  // Додає страхування до путівки за додаткову плату.
  void AddInsurance(double cost);

  // --- Запис/читання полів у файл (п.5 третього рівня) ---
  void SaveToFile(std::ofstream& out) const;
  void LoadFromFile(std::ifstream& in);

  // --- Додатковий метод (п.12 третього рівня) ---
  // Виділяє випадковий обсяг динамічної пам'яті, розміщує в ній
  // множину значень цілочисельного поля (тривалість поїздки),
  // сортує та виводить результат.
  void GenerateAndSortRandomDurations() const;

 private:
  // --- Приватні поля (5) ---
  double insurance_cost_;     // Вартість страхування
  bool has_insurance_;        // Чи оформлено страхування
  bool visa_required_;        // Чи потрібна віза для країни
  std::string travel_dates_;  // Дати подорожі
  int voucher_id_;            // Унікальний ідентифікатор путівки

  static int next_voucher_id_;  // Лічильник для генерації voucher_id_
};

// ---------------------------------------------------------------------------
// Клас Tourist (Турист).
// 8 полів: 3 публічні + 5 приватні (п.1, п.2 третього рівня).
// Приватне поле voucher_ типу Voucher реалізує композицію (п.3).
// ---------------------------------------------------------------------------
class Tourist {
 public:
  // --- Публічні поля (3) ---
  std::string full_name;      // ПІБ туриста
  int age;                    // Вік туриста
  std::string passport_number;  // Номер паспорта

  Tourist();
  Tourist(const std::string& full_name_in, int age_in,
          const std::string& passport_number_in);

  // --- Доступ до приватних полів ---
  const std::string& phone_number() const;
  void set_phone_number(const std::string& phone);
  const std::string& email() const;
  void set_email(const std::string& email_in);
  double total_paid() const;
  int tourist_id() const;
  const Voucher& voucher() const;

  // --- 6 методів обробки даних (п.4 третього рівня) ---

  // Виводить на екран усі поля туриста, включно з вкладеною путівкою.
  void DisplayInfo() const;

  // Перевантажені методи:
  // Повна вартість подорожі туриста без знижки.
  double CalculateTotalCost() const;
  // Повна вартість подорожі туриста зі знижкою у відсотках.
  double CalculateTotalCost(double discount_percent) const;

  // Метод, що приймає об'єкт іншого класу (Voucher) як параметр:
  // сценарій "турист купує путівку" (п.10 третього рівня).
  void BookVoucher(const Voucher& voucher_in);

  // Метод, що повертає тип класу (Tourist): створення "оновленого"
  // туриста (напр., після заміни паспорта).
  Tourist UpgradeTourist(const std::string& new_passport_number) const;

  // Оформлення візи для туриста на основі даних його путівки.
  bool ApplyForVisa();

  // --- Запис/читання полів у файл (п.5 третього рівня) ---
  void SaveToFile(std::ofstream& out) const;
  void LoadFromFile(std::ifstream& in);

  // --- Додатковий метод (п.12 третього рівня) ---
  // Виділяє випадковий обсяг динамічної пам'яті, розміщує в ній
  // множину значень цілочисельного поля (вік/ідентифікатор),
  // сортує та виводить результат.
  void GenerateAndSortRandomIds() const;

 private:
  // --- Приватні поля (5) ---
  std::string phone_number_;  // Контактний телефон
  std::string email_;         // Електронна пошта
  double total_paid_;         // Сплачена сума
  int tourist_id_;            // Унікальний ідентифікатор туриста
  Voucher voucher_;           // Композиція: путівка, оформлена туристом

  static int next_tourist_id_;  // Лічильник для генерації tourist_id_
};

#endif  // TRAVEL_AGENCY_TRAVEL_AGENCY_H_