#include <Windows.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

#include "Collection.h"
#include "Excursion.h"
#include "Services.h"
#include "Staff.h"
#include "StlDemos.h"
#include "TravelAgency.h"

void PrintSection(const std::string& title) {
  std::cout << "\n========== " << title << " ==========\n";
}

void PrintError(const std::exception& error) {
  std::cout << "Помилка: " << error.what() << "\n";
}

void DemoVirtualDestructors() {
  PrintSection("Віртуальний деструктор (TravelService)");
  TravelService* service =
      new TransferService("Трансфер до готелю", 300.0, "Аеропорт - готель", 25);
  delete service;

  PrintSection("Невіртуальний деструктор (Person з ЛР4)");
  Person* person =
      new TourGuide("Олійник Андрій", 35, "+380-50-111-11-11", "GA111111",
                    "guide@mail.com", "Львів", "англійська", 8, 1500.0);
  delete person;
  std::cout << "Деструктор TourGuide не викликано\n";
}

void ShowPrice(const TravelService& service) {
  std::cout << service.Category() << " \"" << service.name()
            << "\": " << service.CalculatePrice() << "\n";
}

void DemoPolymorphism(TravelService* services[], int count) {
  PrintSection("Поліморфізм: виклик через покажчик");
  TravelService* pointer = services[0];
  pointer->DisplayInfo();

  PrintSection("Поліморфізм: виклик через посилання");
  for (int i = 0; i < count; ++i) {
    ShowPrice(*services[i]);
  }

  PrintSection("Поліморфізм: виклик через масив покажчиків");
  for (int i = 0; i < count; ++i) {
    services[i]->DisplayInfo();
  }

  PrintSection("Зміна форми об'єкта");
  TravelService* current = nullptr;
  for (int i = 0; i < count; ++i) {
    current = services[i];
    std::cout << "current зараз є \"" << current->Category()
              << "\", ціна: " << current->CalculatePrice() << "\n";
  }
}

void DemoBinding(TransferService& transfer) {
  PrintSection("Раннє та пізнє зв'язування");
  TravelService* base_pointer = &transfer;

  std::cout << "Раннє зв'язування (невіртуальний метод через покажчик на "
               "базовий клас):\n";
  base_pointer->PrintLabel();
  std::cout << "Раннє зв'язування (виклик через сам об'єкт):\n";
  transfer.PrintLabel();

  std::cout << "Пізнє зв'язування (віртуальний метод через покажчик на "
               "базовий клас):\n";
  std::cout << base_pointer->Category() << ", ціна "
            << base_pointer->CalculatePrice() << "\n";
}

void DemoVirtualBypass(TravelService& service) {
  PrintSection("Обхід механізму віртуальних функцій");
  TravelService* pointer = &service;
  std::cout << "Звичайний віртуальний виклик pointer->DisplayInfo():\n";
  pointer->DisplayInfo();
  std::cout << "Обхід через pointer->TravelService::DisplayInfo():\n";
  pointer->TravelService::DisplayInfo();
}

void DemoOwnVirtualFunctions(InsuranceService& insurance,
                             VisaService& visa, TransferService& transfer,
                             FullPackageService& package) {
  PrintSection("Власні віртуальні функції похідних класів");
  std::cout << "Страховка покриває тур за 40000: "
            << (insurance.CoversTrip(40000.0) ? "так" : "ні") << "\n";
  std::cout << "Термін оформлення візи: " << visa.ProcessingDays()
            << " днів\n";
  std::cout << "Час трансферу: " << transfer.TravelTimeHours() << " год\n";
  std::cout << "Економія на пакеті: " << package.Savings() << "\n";

  VisaService* visa_pointer = &package;
  std::cout << "Термін візи в пакеті (через VisaService*): "
            << visa_pointer->ProcessingDays() << " днів\n";
}

void DemoMemoryErrors(ServiceCatalog& catalog) {
  PrintSection("Виключні ситуації: динамічна пам'ять");

  try {
    volatile std::size_t huge_count = (std::numeric_limits<std::size_t>::max)() / 16;
    std::size_t count = huge_count;
    double* buffer = new double[count];
    delete[] buffer;
  } catch (const std::bad_alloc& error) {
    std::cout << "Помилка виділення пам'яті: " << error.what() << "\n";
  }

  try {
    ServiceCatalog empty_catalog(0);
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }

  try {
    catalog.AddDynamic(nullptr);
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }

  try {
    catalog.AddDynamic(
        new VisaService("Зайва віза", 500.0, "Греція", false));
  } catch (const std::overflow_error& error) {
    PrintError(error);
  }
}

void PrintVoucher(const std::string& label, const Voucher& voucher) {
  std::cout << label << ": путівка #" << voucher.voucher_id() << " ("
            << voucher.country << "), " << voucher.duration_days
            << " днів, ціна " << voucher.base_price << "\n";
}

void DemoUnaryOperators() {
  PrintSection("Унарні оператори ++ та -- (Voucher)");
  Voucher voucher("Італія", 7, 20000.0, true, "01.06 - 08.06");
  PrintVoucher("Початкова", voucher);

  ++voucher;
  PrintVoucher("Після ++voucher", voucher);
  Voucher before_increment = voucher++;
  PrintVoucher("Результат voucher++ (старе значення)", before_increment);
  PrintVoucher("Сама путівка після voucher++", voucher);

  --voucher;
  PrintVoucher("Після --voucher", voucher);
  Voucher before_decrement = voucher--;
  PrintVoucher("Результат voucher-- (старе значення)", before_decrement);
  PrintVoucher("Сама путівка після voucher--", voucher);

  Voucher one_day_trip("Польща", 1, 3000.0, false, "10.07");
  try {
    --one_day_trip;
  } catch (const std::logic_error& error) {
    PrintError(error);
  }
}

void DemoBinaryOperators() {
  PrintSection("Бінарні оператори + та - (Voucher)");
  Voucher italy("Італія", 7, 20000.0, true, "01.06 - 08.06");
  Voucher greece("Греція", 5, 15000.0, true, "08.06 - 13.06");

  Voucher combined = italy + greece;
  PrintVoucher("italy + greece", combined);
  std::cout << "Дати комбінованої путівки: " << combined.travel_dates()
            << "\n";

  Voucher discounted = italy - 2500.0;
  PrintVoucher("italy - 2500", discounted);

  try {
    PrintVoucher("italy - 50000", italy - 50000.0);
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }
}

void DemoOtherOperators(ServiceCatalog& catalog) {
  PrintSection("Оператори *, =, +=, -=, *= (Voucher)");
  Voucher spain("Іспанія", 10, 25000.0, true, "15.08 - 25.08");

  Voucher family = spain * 3;
  PrintVoucher("spain * 3 (путівка на трьох)", family);

  Voucher copy;
  copy = spain;
  PrintVoucher("copy = spain", copy);

  copy += Voucher("Португалія", 4, 9000.0, true, "25.08 - 29.08");
  PrintVoucher("copy += Португалія", copy);

  copy -= 4000.0;
  PrintVoucher("copy -= 4000", copy);

  copy *= 1.1;
  PrintVoucher("copy *= 1.1", copy);

  try {
    copy *= 0;
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }

  PrintSection("Оператор [] (ServiceCatalog)");
  std::cout << "catalog[0]:\n";
  catalog[0].DisplayInfo();
  std::cout << "catalog[2]:\n";
  catalog[2].DisplayInfo();

  try {
    catalog[100].DisplayInfo();
  } catch (const std::out_of_range& error) {
    PrintError(error);
  }
}

void DemoTemplateFunction(const ServiceCatalog& catalog) {
  PrintSection("Шаблонна функція ServiceCatalog::CountOfType<T>()");
  std::cout << "Усі послуги (TravelService): "
            << catalog.CountOfType<TravelService>() << "\n"
            << "Страхування (InsuranceService): "
            << catalog.CountOfType<InsuranceService>() << "\n"
            << "Візові послуги (VisaService): "
            << catalog.CountOfType<VisaService>() << "\n"
            << "Трансфери (TransferService): "
            << catalog.CountOfType<TransferService>() << "\n"
            << "Повні пакети (FullPackageService): "
            << catalog.CountOfType<FullPackageService>() << "\n"
            << "Повний пакет рахується і як страхування, і як віза, бо "
               "наслідує обидва класи\n";
}

void DemoClassTemplate() {
  PrintSection("Шаблон класу Collection<int>");
  Collection<int> durations("Тривалості турів, днів", 2);
  durations.Add(7);
  durations.Add(10);
  durations.Add(14);
  durations.Print();
  std::cout << "Сума днів (Total): " << durations.Total() << "\n";
  std::cout << "Чи є тур на 10 днів (Contains): "
            << (durations.Contains(10) ? "так" : "ні") << "\n";
  durations[0] = 8;
  durations.RemoveAt(1);
  std::cout << "Змінено [0] на 8 та видалено [1], видалене значення: "
            << durations.LastRemoved() << "\n";
  durations.Print();

  PrintSection("Шаблон класу Collection<double>");
  Collection<double> prices("Ціни турів, грн", 3);
  prices.Add(20000.5);
  prices.Add(15000.0);
  prices.Add(9999.5);
  prices.Print();
  std::cout << "Сума цін (Total): " << prices.Total() << "\n";

  PrintSection("Шаблон класу Collection<std::string>");
  Collection<std::string> countries("Країни", 3);
  countries.Add("Італія");
  countries.Add("Греція");
  countries.Add("Іспанія");
  countries.Print();
  std::cout << "Чи є Греція (Contains): "
            << (countries.Contains("Греція") ? "так" : "ні") << "\n";

  PrintSection("Шаблон класу з користувацьким типом Collection<Excursion>");
  Collection<Excursion> excursions("Екскурсії", 2);
  excursions.Add(Excursion("Колізей", "Рим", 450.0, 3.0));
  excursions.Add(Excursion("Ватикан", "Рим", 600.0, 4.0));
  excursions.Add(Excursion("Помпеї", "Неаполь", 800.0, 6.0));
  excursions.Print();
  std::cout << "Загальна екскурсія (Total): " << excursions.Total() << "\n";
  std::cout << "Чи є екскурсія до Ватикану (Contains): "
            << (excursions.Contains(Excursion("Ватикан", "Рим", 600.0, 4.0))
                    ? "так"
                    : "ні")
            << "\n";
  excursions[0] = Excursion("Колізей і Форум", "Рим", 550.0, 4.0);
  excursions.RemoveAt(1);
  std::cout << "Видалена екскурсія (LastRemoved): "
            << excursions.LastRemoved() << "\n";
  excursions.Print();

  PrintSection("Виключні ситуації шаблону Collection<T>");
  try {
    Collection<int> wrong("Неправильна колекція", 0);
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }

  try {
    Collection<double> empty("Порожні ціни", 1);
    std::cout << empty.Total() << "\n";
  } catch (const std::runtime_error& error) {
    PrintError(error);
  }

  try {
    std::cout << excursions[10] << "\n";
  } catch (const std::out_of_range& error) {
    PrintError(error);
  }

  try {
    std::cout << countries.LastRemoved() << "\n";
  } catch (const std::logic_error& error) {
    PrintError(error);
  }

  try {
    excursions.Add(Excursion("Неправильна", "Київ", -100.0, 2.0));
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }
}

void DemoServiceMethods(ServiceCatalog& catalog) {
  PrintSection("Service_Static та Service_Dinamic");
  catalog.ShowAll();

  const double kMaxPrice = 1500.0;
  std::cout << "\nВидаляємо послуги, дорожчі за " << kMaxPrice << ":\n";
  int removed_static = catalog.Service_Static(kMaxPrice);
  int removed_dynamic = catalog.Service_Dinamic(kMaxPrice);
  std::cout << "Прибрано статичних: " << removed_static
            << ", видалено динамічних: " << removed_dynamic << "\n\n";
  catalog.ShowAll();

  PrintSection("Виключні ситуації: Service_Static та Service_Dinamic");
  try {
    catalog.Service_Dinamic(-100.0);
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }

  try {
    catalog.RemoveDynamic(42);
  } catch (const std::out_of_range& error) {
    PrintError(error);
  }

  try {
    ServiceCatalog empty_catalog(1);
    empty_catalog.Service_Static(1000.0);
  } catch (const std::runtime_error& error) {
    PrintError(error);
  }
}

std::string GetFileName(int argc, char* argv[]) {
  if (argc < 2) {
    throw std::invalid_argument(
        "не вказано ім'я файлу в командному рядку");
  }
  return argv[1];
}

void CheckFileName(const std::string& file_name) {
  if (file_name.empty()) {
    throw std::invalid_argument("ім'я файлу порожнє");
  }
  const std::string kExtension = ".txt";
  if (file_name.size() <= kExtension.size() ||
      file_name.compare(file_name.size() - kExtension.size(),
                        kExtension.size(), kExtension) != 0) {
    throw std::invalid_argument("файл \"" + file_name +
                                "\" повинен мати розширення .txt");
  }
}

void SaveService(const TravelService& service, const std::string& file_name) {
  CheckFileName(file_name);
  std::ofstream out(file_name);
  if (!out.is_open()) {
    throw std::runtime_error("не вдалося створити файл \"" + file_name +
                             "\"");
  }
  service.Write(out);
}

void LoadService(TravelService& service, const std::string& file_name) {
  CheckFileName(file_name);
  std::ifstream in(file_name);
  if (!in.is_open()) {
    throw std::runtime_error("не вдалося відкрити файл \"" + file_name +
                             "\"");
  }
  service.Read(in);
}

void Service(TravelService& service, const std::string& file_name) {
  PrintSection("Service: запис у файл та читання з файлу");
  SaveService(service, file_name);
  std::cout << "Послугу \"" << service.name() << "\" записано у "
            << file_name << "\n";
  LoadService(service, file_name);
  std::cout << "Послугу зчитано з файлу:\n";
  service.DisplayInfo();
}

void CreateTextFile(const std::string& file_name, const std::string& text) {
  std::ofstream out(file_name);
  out << text;
}

void DemoFileErrors(TransferService& transfer, const std::string& file_name) {
  PrintSection("Виключні ситуації: робота з файлами");

  try {
    SaveService(transfer, "");
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }

  try {
    SaveService(transfer, "services.doc");
  } catch (const std::invalid_argument& error) {
    PrintError(error);
  }

  try {
    SaveService(transfer, "Z:/немає/такої/папки/services.txt");
  } catch (const std::runtime_error& error) {
    PrintError(error);
  }

  try {
    LoadService(transfer, "missing_file.txt");
  } catch (const std::runtime_error& error) {
    PrintError(error);
  }

  try {
    CreateTextFile("empty_file.txt", "");
    LoadService(transfer, "empty_file.txt");
  } catch (const std::runtime_error& error) {
    PrintError(error);
  }

  try {
    CreateTextFile("broken_file.txt", "Трансфер\nЗламаний\nне число\n");
    LoadService(transfer, "broken_file.txt");
  } catch (const std::runtime_error& error) {
    PrintError(error);
  }

  try {
    LoadService(transfer, file_name);
  } catch (const std::logic_error& error) {
    PrintError(error);
  }
}

std::string ReadLine(const std::string& prompt) {
  std::cout << prompt;
  std::string line;
  if (!std::getline(std::cin, line)) {
    throw std::runtime_error("введення завершено");
  }
  return line;
}

double ReadNumber(const std::string& prompt) {
  std::string line = ReadLine(prompt);
  try {
    return std::stod(line);
  } catch (const std::exception&) {
    throw std::invalid_argument("\"" + line + "\" не є числом");
  }
}

TravelService* CreateService(int type) {
  std::string name = ReadLine("Назва послуги: ");
  double base_price = ReadNumber("Базова ціна: ");
  if (base_price < 0) {
    throw std::invalid_argument("ціна не може бути від'ємною");
  }
  switch (type) {
    case 1:
      return new InsuranceService(name, base_price, 30000.0, 2);
    case 2:
      return new VisaService(name, base_price, "Італія", false);
    case 3:
      return new TransferService(name, base_price, "Аеропорт - готель", 30);
    default:
      return new FullPackageService(name, base_price, 30000.0, 2, "Італія",
                                    false, 10.0);
  }
}

void PrintMenu() {
  std::cout << "\n----- Меню -----\n"
            << "1 - Створити страхування\n"
            << "2 - Створити візову послугу\n"
            << "3 - Створити трансфер\n"
            << "4 - Створити повний пакет\n"
            << "5 - Переглянути всі послуги\n"
            << "6 - Видалити послугу за номером\n"
            << "7 - Видалити послуги, дорожчі за ціну\n"
            << "0 - Вихід\n";
}

void RunMenu(ServiceCatalog& catalog) {
  PrintSection("Меню керування послугами");
  while (true) {
    PrintMenu();
    try {
      int choice = static_cast<int>(ReadNumber("Ваш вибір: "));
      switch (choice) {
        case 0:
          return;
        case 1:
        case 2:
        case 3:
        case 4:
          catalog.AddDynamic(CreateService(choice));
          break;
        case 5:
          catalog.ShowAll();
          std::cout << "Усього об'єктів послуг: "
                    << TravelService::AliveCount() << "\n";
          break;
        case 6:
          catalog.RemoveDynamic(
              static_cast<int>(ReadNumber("Номер послуги: ")) - 1);
          break;
        case 7: {
          double max_price = ReadNumber("Максимальна ціна: ");
          int removed = catalog.Service_Dinamic(max_price);
          std::cout << "Видалено послуг: " << removed << "\n";
          break;
        }
        default:
          std::cout << "Немає такого пункту меню\n";
      }
    } catch (const std::runtime_error& error) {
      PrintError(error);
      if (!std::cin) {
        return;
      }
    } catch (const std::exception& error) {
      PrintError(error);
    }
  }
}

int main(int argc, char* argv[]) {
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);

  DemoVirtualDestructors();

  PrintSection("Статичні об'єкти");
  InsuranceService insurance("Медичне страхування", 400.0, 50000.0, 2);
  VisaService visa("Шенгенська віза", 800.0, "Італія", true);
  TransferService transfer("Трансфер в аеропорт", 200.0, "Київ - Бориспіль",
                           40.0);
  FullPackageService package("Все включено", 1000.0, 30000.0, 1, "Іспанія",
                             false, 10.0);
  TransferService city_transfer("Міський трансфер", 100.0, "Готель - центр",
                                5.0);
  TravelService* static_services[] = {&insurance, &visa, &transfer, &package,
                                      &city_transfer};
  const int kStaticCount = 5;

  PrintSection("Динамічні об'єкти");
  ServiceCatalog catalog(5);
  catalog.AddDynamic(new InsuranceService("Страхування багажу", 150.0,
                                          10000.0, 1));
  catalog.AddDynamic(new VisaService("Віза до Японії", 1200.0, "Японія",
                                     false));
  catalog.AddDynamic(new TransferService("Трансфер Рим - Неаполь", 500.0,
                                         "Рим - Неаполь", 230.0));
  catalog.AddDynamic(new FullPackageService("Пакет Греція", 900.0, 20000.0,
                                            2, "Греція", true, 15.0));
  catalog.AddDynamic(new TransferService("Трансфер до пляжу", 80.0,
                                         "Готель - пляж", 3.0));
  for (TravelService* service : static_services) {
    catalog.AddStatic(service);
  }

  DemoPolymorphism(static_services, kStaticCount);
  DemoBinding(transfer);
  DemoVirtualBypass(package);
  DemoOwnVirtualFunctions(insurance, visa, transfer, package);
  DemoMemoryErrors(catalog);
  DemoUnaryOperators();
  DemoBinaryOperators();
  DemoOtherOperators(catalog);
  DemoTemplateFunction(catalog);
  DemoClassTemplate();
  DemoContainers(static_services, kStaticCount);
  DemoIterators();
  DemoAlgorithms();
  DemoFunctors();
  DemoServiceMethods(catalog);

  try {
    std::string file_name = GetFileName(argc, argv);
    Service(insurance, file_name);
    DemoFileErrors(transfer, file_name);
  } catch (const std::exception& error) {
    PrintError(error);
  }

  RunMenu(catalog);

  PrintSection("Кінець програми");
  return 0;
}
