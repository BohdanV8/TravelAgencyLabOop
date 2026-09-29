// main.cpp
//
// Демонстраційна програма для лабораторної роботи №2, третій рівень,
// варіант 8 "Туристична агенція".
// Кожен блок коду супроводжується коментарем з номером відповідного
// пункту завдання (п.11 третього рівня).

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "TravelAgency.h"
#include <Windows.h>
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // --- п.6: 5 об'єктів Tourist у статичній пам'яті ---
    Tourist static_tourists[5] = {
        Tourist("Іваненко Іван", 25, "AB123456"),
        Tourist("Петренко Петро", 62, "AB234567"),
        Tourist("Сидоренко Оксана", 34, "AB345678"),
        Tourist("Коваль Марія", 45, "AB456789"),
        Tourist("Гончар Andрій", 19, "AB567890"),
    };

    // --- п.6: 5 об'єктів Voucher у динамічній пам'яті ---
    Voucher* dynamic_vouchers[5];
    dynamic_vouchers[0] = new Voucher("Італія", 7, 15000.0, true, "01.06-08.06");
    dynamic_vouchers[1] = new Voucher("Туреччина", 10, 12000.0, false,
        "10.07-20.07");
    dynamic_vouchers[2] = new Voucher("Іспанія", 14, 25000.0, true,
        "01.08-15.08");
    dynamic_vouchers[3] = new Voucher("Єгипет", 5, 9000.0, false,
        "05.09-10.09");
    dynamic_vouchers[4] = new Voucher("Греція", 9, 18000.0, true,
        "12.09-21.09");

    // --- п.7: 2 масиви об'єктів у основній програмі ---
    // Масив 1: static_tourists (вище, статична пам'ять).
    // Масив 2: dynamic_vouchers (вище, динамічна пам'ять) - реалізований
    // як масив покажчиків на динамічно виділені об'єкти Voucher.

    // --- п.8: робота з об'єктами, розміщеними у масивах ---
    std::cout << "== Масив туристів (статична пам'ять) ==\n";
    for (int i = 0; i < 5; ++i) {
        static_tourists[i].set_phone_number("+380-00-000-00-0" +
            std::to_string(i));
        static_tourists[i].set_email("tourist" + std::to_string(i) +
            "@mail.com");
    }

    std::cout << "== Масив путівок (динамічна пам'ять) ==\n";
    for (int i = 0; i < 5; ++i) {
        dynamic_vouchers[i]->DisplayInfo();
    }

    // --- п.10 / сценарій взаємодії: турист купує путівку ---
    // Метод BookVoucher() приймає об'єкт Voucher як параметр (п.4),
    // а метод ApplyDiscountForTourist() приймає об'єкт Tourist (п.4).
    for (int i = 0; i < 5; ++i) {
        dynamic_vouchers[i]->ApplyDiscountForTourist(static_tourists[i]);
        static_tourists[i].BookVoucher(*dynamic_vouchers[i]);
    }

    // --- п.9: усі методи класів ---
    std::cout << "\n== Повна інформація про туристів після покупки ==\n";
    for (int i = 0; i < 5; ++i) {
        static_tourists[i].DisplayInfo();
        std::cout << "Вартість без знижки: "
            << static_tourists[i].CalculateTotalCost() << "\n";
        std::cout << "Вартість зі знижкою 10%: "
            << static_tourists[i].CalculateTotalCost(10.0) << "\n";
        static_tourists[i].ApplyForVisa();
    }

    // Метод, що повертає тип класу (Tourist) - UpgradeTourist().
    Tourist upgraded = static_tourists[0].UpgradeTourist("CD999999");
    std::cout << "\nОновлений паспорт туриста: " << upgraded.passport_number
        << "\n";

    // Метод, що повертає тип класу (Voucher) - CombineWith().
    Voucher combined = dynamic_vouchers[0]->CombineWith(*dynamic_vouchers[1]);
    std::cout << "Об'єднана путівка: " << combined.duration_days
        << " днів, ціна " << combined.base_price << "\n";

    // AddInsurance() - додаткова обробка даних.
    dynamic_vouchers[2]->AddInsurance(500.0);
    std::cout << "Ціна путівки #2 зі страхуванням: "
        << dynamic_vouchers[2]->GetFinalPrice() << "\n";
    std::cout << "Ціна путівки #2 з додатковим збором 100: "
        << dynamic_vouchers[2]->GetFinalPrice(100.0) << "\n";

    // --- п.11: покажчик на екземпляр класу ---
    Tourist* tourist_ptr = &static_tourists[3];
    std::cout << "\nЗвернення через покажчик: " << tourist_ptr->full_name
        << ", вік " << tourist_ptr->age << "\n";

    // --- п.12: додатковий метод - виділення динамічної пам'яті
    // випадкового розміру та сортування цілочисельних значень ---
    std::cout << "\n== Демонстрація динамічної пам'яті та сортування ==\n";
    static_tourists[0].GenerateAndSortRandomIds();
    dynamic_vouchers[0]->GenerateAndSortRandomDurations();

    // --- п.5: запис у файл та читання з файлу ---
    std::ofstream out_file("tourists_data.txt");
    if (out_file.is_open()) {
        for (int i = 0; i < 5; ++i) {
            static_tourists[i].SaveToFile(out_file);
        }
        out_file.close();
        std::cout << "\nДані туристів збережено у tourists_data.txt\n";
    }

    std::ifstream in_file("tourists_data.txt");
    if (in_file.is_open()) {
        Tourist loaded_tourist;
        loaded_tourist.LoadFromFile(in_file);
        in_file.close();
        std::cout << "\nЗчитаний з файлу турист:\n";
        loaded_tourist.DisplayInfo();
    }

    // --- звільнення динамічної пам'яті ---
    for (int i = 0; i < 5; ++i) {
        delete dynamic_vouchers[i];
    }

    return 0;
}