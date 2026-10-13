#include <Windows.h>

#include <iostream>
#include <string>

#include "Staff.h"
#include "TravelAgency.h"

void PrintSection(const std::string& title) {
  std::cout << "\n========== " << title << " ==========\n";
}

void DemoAccessControl() {
  PrintSection("Керування доступом: public, protected, private");
  TourGuide guide("Олійник Андрій", 35, "+380-50-111-11-11", "GA111111",
                  "guide@mail.com", "Львів", "англійська, італійська", 8,
                  1500.0);
  TravelAgent agent("Савченко Ірина", 29, "+380-50-222-22-22", "AG222222",
                    "agent@mail.com", "Київ", "Офіс на Хрещатику", 25000.0);
  BusDriver driver("Мороз Василь", 47, "+380-50-333-33-33", "DR333333",
                   "driver@mail.com", "Київ", "AA1234BB", 30);

  std::cout << "\nTourGuide - public: члени Person доступні ззовні\n";
  std::cout << guide.full_name << ", " << guide.age << ", "
            << guide.phone_number << "\n";
  guide.Introduce();
  std::cout << "Контакти: " << guide.GetContactInfo() << "\n";
  std::cout << "Повнолітній: " << (guide.IsAdult() ? "так" : "ні") << "\n";
  guide.ShowInheritedAccess();

  std::cout << "\nTravelAgent - protected\n";
  std::cout << "Через using: " << agent.full_name << "\n";
  agent.Introduce();
  agent.ShowInheritedAccess();

  std::cout << "\nBusDriver - private\n";
  std::cout << "Через власний метод: " << driver.name() << "\n";
  driver.ShowInheritedAccess();

  PrintSection("Вихід з функції DemoAccessControl");
}

void DemoPrivateInheritance() {
  PrintSection("Закрите наслідування: TourLeader : private TourGuide");
  TourLeader leader("Ткаченко Олена", 41, "+380-50-444-44-44", "TL444444",
                    "leader@mail.com", "Одеса", "англійська, іспанська",
                    "Сонячна Іспанія", 15);

  std::cout << "\nМетод класу Person:\n";
  leader.Introduce();
  std::cout << "\nМетод класу TourGuide:\n";
  leader.LeadTour("Іспанія");
  std::cout << "\nВласні методи TourLeader:\n";
  leader.HoldBriefing();
  leader.DisplayInfo();

  PrintSection("Вихід з функції DemoPrivateInheritance");
}

void DemoScopeResolution() {
  PrintSection("Оператор :: для доступу до членів базових класів");
  TravelConsultant consultant("Гриценко Марина", 38, "+380-50-555-55-55",
                              "TC555555", "consultant@mail.com", "Київ",
                              "Уніка", 900.0, 1600.0, 500.0);

  std::cout << "\nconsultant.Person::Introduce():\n";
  consultant.Person::Introduce();
  std::cout << "\nconsultant.InsuranceSpecialist::DisplayInfo():\n";
  consultant.InsuranceSpecialist::DisplayInfo();
  std::cout << "\nconsultant.VisaSpecialist::IsCountrySupported(\"Японія\"): "
            << (consultant.VisaSpecialist::IsCountrySupported("Японія")
                    ? "так"
                    : "ні")
            << "\n";

  PrintSection("Вихід з функції DemoScopeResolution");
}

void DemoConstructionOrder() {
  PrintSection("Порядок конструкторів і деструкторів");

  std::cout << "\nВхід у блок: просте наслідування (Person -> TourGuide)\n";
  {
    TourGuide guide("Блок Гід", 30, "+380-00-000-00-01", "BL000001",
                    "block1@mail.com", "Київ", "англійська", 3, 1000.0);
    std::cout << "Вихід з блоку\n";
  }

  std::cout << "\nВхід у блок: два рівні (Person -> TourGuide -> "
               "TourLeader)\n";
  {
    TourLeader leader("Блок Керівник", 45, "+380-00-000-00-02", "BL000002",
                      "block2@mail.com", "Київ", "англійська", "Тестова", 10);
    std::cout << "Вихід з блоку\n";
  }

  std::cout << "\nВхід у блок: множинне наслідування (TravelConsultant)\n";
  {
    TravelConsultant consultant("Блок Консультант", 33, "+380-00-000-00-03",
                                "BL000003", "block3@mail.com", "Київ",
                                "Уніка", 900.0, 1600.0, 500.0);
    std::cout << "Вихід з блоку\n";
  }
}

void RunAgencyScenario() {
  PrintSection("Сценарій роботи туристичної агенції");
  TravelAgency agency("Світ мандрів");
  TravelAgent agent("Савченко Ірина", 29, "+380-50-222-22-22", "AG222222",
                    "agent@mail.com", "Київ", "Офіс на Хрещатику", 25000.0);
  TravelConsultant consultant("Гриценко Марина", 38, "+380-50-555-55-55",
                              "TC555555", "consultant@mail.com", "Київ",
                              "Уніка", 900.0, 1600.0, 500.0);
  TourLeader leader("Ткаченко Олена", 41, "+380-50-444-44-44", "TL444444",
                    "leader@mail.com", "Одеса", "англійська, італійська",
                    "Італійські канікули", 2);
  BusDriver driver("Мороз Василь", 47, "+380-50-333-33-33", "DR333333",
                   "driver@mail.com", "Київ", "AA1234BB", 30);

  Tourist first_tourist("Іваненко Іван", 25, "AB123456");
  Tourist second_tourist("Петренко Петро", 62, "AB234567");
  Tourist third_tourist("Коваль Марія", 45, "AB456789");
  Voucher italy_with_visa("Італія", 7, 15000.0, true, "01.06-08.06");
  Voucher italy_without_visa("Італія", 7, 15000.0, false, "01.06-08.06");

  PrintSection("Продаж путівок");
  consultant.PrepareFullPackage(first_tourist, italy_with_visa);
  agent.SellVoucher(second_tourist, italy_without_visa);
  agent.SellVoucher(third_tourist, italy_without_visa);
  agency.AddClient(&first_tourist);
  agency.AddClient(&second_tourist);
  agency.AddClient(&third_tourist);

  PrintSection("Формування групи");
  leader.AddTourist(first_tourist);
  leader.AddTourist(second_tourist);
  leader.AddTourist(third_tourist);
  leader.HoldBriefing();

  PrintSection("Трансфер і початок туру");
  if (driver.CanTakeGroup(leader.group_size())) {
    driver.DriveTransfer("Київ - аеропорт Бориспіль", 40.0);
  }
  leader.StartGroupTour("Італія");

  PrintSection("Підсумки");
  agency.ShowClients();
  std::cout << "Дохід менеджера " << agent.full_name << ": "
            << agent.CalculateMonthlyIncome() << "\n"
            << "Дохід консультанта " << consultant.full_name << ": "
            << consultant.CalculateTotalEarnings() << "\n"
            << "Пальне, витрачене водієм " << driver.name() << ": "
            << driver.CalculateFuelUsed() << " л\n";

  PrintSection("Інформація про працівників");
  agent.DisplayInfo();
  consultant.DisplayInfo();
  driver.DisplayInfo();

  PrintSection("Вихід з функції RunAgencyScenario");
}

int main() {
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);

  DemoAccessControl();
  DemoPrivateInheritance();
  DemoScopeResolution();
  DemoConstructionOrder();
  RunAgencyScenario();

  PrintSection("Кінець програми");
  return 0;
}
