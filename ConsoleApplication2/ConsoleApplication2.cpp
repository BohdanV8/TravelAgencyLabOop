#include <Windows.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "TravelAgency.h"

void PrintSection(const std::string& title) {
  std::cout << "\n========== " << title << " ==========\n";
}

void PrintCostPerDay(Tourist tourist) {
  int days = tourist.voucher().duration_days;
  if (days == 0) {
    std::cout << tourist.full_name << " ще не має путівки\n";
    return;
  }
  std::cout << "Вартість одного дня подорожі (об'єкт): " << tourist.full_name
            << " - " << tourist.CalculateTotalCost() / days << "\n";
}

void PrintCostPerDay(const Tourist* tourist) {
  int days = tourist->voucher().duration_days;
  if (days == 0) {
    std::cout << tourist->full_name << " ще не має путівки\n";
    return;
  }
  std::cout << "Вартість одного дня подорожі (адреса): " << tourist->full_name
            << " - " << tourist->CalculateTotalCost() / days << "\n";
}

Voucher CreateInsuredVoucher(const std::string& country, int days,
                             double price, bool visa_required,
                             const std::string& dates, double insurance_cost) {
  Voucher voucher(country, days, price, visa_required, dates);
  voucher.AddInsurance(insurance_cost);
  return voucher;
}

void DemoConstructors() {
  PrintSection("Три способи створення об'єктів");
  Tourist simple_tourist;
  Tourist explicit_tourist = Tourist("Шевченко Тарас", 30, "AA111111");
  Tourist short_tourist("Франко Іван", 40, "AA222222");

  PrintSection("Конструктор копіювання");
  Tourist copied_tourist(short_tourist);

  PrintSection("Конструктори класу Voucher");
  Voucher default_voucher;
  Voucher param_voucher("Франція", 6, 20000.0, true, "03.10-09.10");
  Voucher copied_voucher(param_voucher);

  PrintSection("Вихід з функції DemoConstructors");
}

void DemoBlockTracking() {
  PrintSection("Відстеження блоків програми");
  std::cout << "Вхід у зовнішній блок\n";
  Tourist outer_tourist("Зовнішній Турист", 33, "BB000001");
  {
    std::cout << "Вхід у внутрішній блок\n";
    Tourist inner_tourist("Внутрішній Турист", 22, "BB000002");
    std::cout << "Вихід з внутрішнього блоку\n";
  }
  std::cout << "Вихід із зовнішнього блоку\n";
}

void DemoStaticMember() {
  PrintSection("Статичне поле та статичний метод");
  std::cout << "Туристів зараз: " << Tourist::AliveCount() << "\n";
  Tourist first("Перший Турист", 20, "CC000001");
  Tourist second("Другий Турист", 21, "CC000002");
  std::cout << "Туристів зараз: " << Tourist::AliveCount() << "\n";
}

void DemoAssociation() {
  PrintSection("Клас асоціації: агенція, турист, путівка");
  TravelAgency agency("Світ мандрів");
  Tourist tourist("Мельник Олена", 65, "DD000001");
  Voucher voucher("Японія", 12, 40000.0, true, "01.11-12.11");

  Booking booking(agency, tourist, voucher);
  booking.Confirm();
  booking.DisplayInfo();
  agency.ShowClients();
}

void DemoAggregation() {
  PrintSection("Агрегація: агенція та турист");
  Tourist tourist("Бондар Сергій", 28, "EE000001");
  tourist.BookVoucher(Voucher("Чорногорія", 8, 14000.0, false, "02.07-10.07"));
  {
    TravelAgency agency("Тур-Експрес");
    agency.AddClient(&tourist);
    agency.ShowClients();
  }
  std::cout << "Агенції вже немає, а турист існує: " << tourist.full_name
            << "\n";
}

void DemoComposition() {
  PrintSection("Композиція: турист та його путівка");
  {
    Tourist tourist("Кравченко Ірина", 31, "FF000001");
    tourist.BookVoucher(Voucher("Португалія", 10, 22000.0, true,
                                "15.05-25.05"));
    std::cout << "Турист знищується разом із путівкою:\n";
  }
}

void DemoArraysAndPointers() {
  PrintSection("Масив туристів у статичній пам'яті");
  Tourist static_tourists[5] = {
      Tourist("Іваненко Іван", 25, "AB123456"),
      Tourist("Петренко Петро", 62, "AB234567"),
      Tourist("Сидоренко Оксана", 34, "AB345678"),
      Tourist("Коваль Марія", 45, "AB456789"),
      Tourist("Гончар Андрій", 19, "AB567890"),
  };

  PrintSection("Масив путівок у динамічній пам'яті");
  Voucher* dynamic_vouchers[5] = {
      new Voucher("Італія", 7, 15000.0, true, "01.06-08.06"),
      new Voucher("Туреччина", 10, 12000.0, false, "10.07-20.07"),
      new Voucher("Іспанія", 14, 25000.0, true, "01.08-15.08"),
      new Voucher("Єгипет", 5, 9000.0, false, "05.09-10.09"),
      new Voucher("Греція", 9, 18000.0, true, "12.09-21.09"),
  };

  PrintSection("Купівля путівок");
  for (int i = 0; i < 5; ++i) {
    static_tourists[i].set_phone_number("+380-00-000-00-0" +
                                        std::to_string(i));
    static_tourists[i].set_email("tourist" + std::to_string(i) + "@mail.com");
    dynamic_vouchers[i]->ApplyDiscountForTourist(static_tourists[i]);
    static_tourists[i].BookVoucher(*dynamic_vouchers[i]);
  }

  PrintSection("Інформація про туристів");
  for (int i = 0; i < 5; ++i) {
    static_tourists[i].DisplayInfo();
    std::cout << "Вартість без знижки: "
              << static_tourists[i].CalculateTotalCost() << "\n"
              << "Вартість зі знижкою 10%: "
              << static_tourists[i].CalculateTotalCost(10.0) << "\n";
    static_tourists[i].ApplyForVisa();
  }

  PrintSection("Функції поза класом");
  PrintCostPerDay(static_tourists[0]);
  PrintCostPerDay(&static_tourists[1]);

  PrintSection("Функція, що повертає об'єкт класу");
  Voucher insured = CreateInsuredVoucher("Австрія", 6, 21000.0, true,
                                         "20.12-26.12", 800.0);
  insured.DisplayInfo();

  PrintSection("Методи, що повертають об'єкт класу");
  Tourist upgraded = static_tourists[0].UpgradeTourist("CD999999");
  std::cout << "Оновлений паспорт туриста: " << upgraded.passport_number
            << "\n";
  Voucher combined = dynamic_vouchers[0]->CombineWith(*dynamic_vouchers[1]);
  std::cout << "Об'єднана путівка: " << combined.duration_days
            << " днів, ціна " << combined.base_price << "\n";

  dynamic_vouchers[2]->AddInsurance(500.0);
  std::cout << "Ціна путівки зі страхуванням: "
            << dynamic_vouchers[2]->GetFinalPrice() << "\n"
            << "Ціна путівки з додатковим збором 100: "
            << dynamic_vouchers[2]->GetFinalPrice(100.0) << "\n";

  PrintSection("Покажчики на об'єкти");
  Tourist* tourist_ptr = &static_tourists[3];
  std::cout << "Звернення через покажчик: " << tourist_ptr->full_name
            << ", вік " << tourist_ptr->age << "\n";

  Tourist* dynamic_tourist = new Tourist("Литвин Олег", 50, "GG000001");
  dynamic_tourist->DisplayInfo();
  delete dynamic_tourist;

  Voucher* voucher_array = new Voucher[2];
  voucher_array[0].country = "Польща";
  voucher_array[1].country = "Чехія";
  for (int i = 0; i < 2; ++i) {
    voucher_array[i].DisplayInfo();
  }
  delete[] voucher_array;

  PrintSection("Динамічна пам'ять та сортування");
  static_tourists[0].GenerateAndSortRandomIds();
  dynamic_vouchers[0]->GenerateAndSortRandomDurations();

  PrintSection("Запис у файл та читання з файлу");
  std::ofstream out_file("tourists_data.txt");
  if (out_file.is_open()) {
    for (int i = 0; i < 5; ++i) {
      static_tourists[i].SaveToFile(out_file);
    }
    out_file.close();
    std::cout << "Дані туристів збережено у tourists_data.txt\n";
  }

  std::ifstream in_file("tourists_data.txt");
  if (in_file.is_open()) {
    Tourist loaded_tourist;
    loaded_tourist.LoadFromFile(in_file);
    in_file.close();
    std::cout << "Зчитаний з файлу турист:\n";
    loaded_tourist.DisplayInfo();
  }

  PrintSection("Звільнення пам'яті");
  for (int i = 0; i < 5; ++i) {
    delete dynamic_vouchers[i];
  }
}

int main() {
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  DemoConstructors();
  DemoBlockTracking();
  DemoStaticMember();
  DemoAssociation();
  DemoAggregation();
  DemoComposition();
  DemoArraysAndPointers();

  PrintSection("Кінець програми");
  std::cout << "Туристів зараз: " << Tourist::AliveCount() << "\n";
  return 0;
}
