#include "StlDemos.h"

#include <algorithm>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <type_traits>
#include <vector>

#include "Excursion.h"
#include "Functors.h"
#include "Services.h"

namespace {

void PrintTitle(const std::string& title) {
  std::cout << "\n========== " << title << " ==========\n";
}

std::vector<Excursion> SampleExcursions() {
  return {
      Excursion("Колізей", "Рим", 450.0, 3.0),
      Excursion("Ватикан", "Рим", 600.0, 4.0),
      Excursion("Помпеї", "Неаполь", 800.0, 6.0),
      Excursion("Уффіці", "Флоренція", 550.0, 3.0),
      Excursion("Гондоли", "Венеція", 900.0, 1.0),
  };
}

template <typename Container>
void PrintAll(const std::string& label, const Container& items) {
  std::cout << label << " (" << items.size() << "):\n";
  for (const auto& item : items) {
    std::cout << "  " << item << "\n";
  }
}

void PrintService(const TravelService* service) {
  std::cout << "  " << service->name() << " (" << service->Category()
            << "), " << service->CalculatePrice() << " грн\n";
}

void PrintNumbers(const std::string& label, const std::vector<double>& values) {
  std::cout << label << ": ";
  std::copy(values.begin(), values.end(),
            std::ostream_iterator<double>(std::cout, " "));
  std::cout << "\n";
}

void PrintFlags(const std::string& label, const std::vector<bool>& flags) {
  std::cout << label << ": ";
  for (bool flag : flags) {
    std::cout << (flag ? "так " : "ні ");
  }
  std::cout << "\n";
}

template <typename Iterator>
std::string CategoryName() {
  using Category = typename std::iterator_traits<Iterator>::iterator_category;
  if constexpr (std::is_same_v<Category, std::input_iterator_tag>) {
    return "input";
  } else if constexpr (std::is_same_v<Category, std::output_iterator_tag>) {
    return "output";
  } else if constexpr (std::is_same_v<Category, std::forward_iterator_tag>) {
    return "forward";
  } else if constexpr (std::is_same_v<Category,
                                      std::bidirectional_iterator_tag>) {
    return "bidirectional";
  } else {
    return "random access";
  }
}

void DemoVector() {
  PrintTitle("vector<Excursion>: push_back, insert, erase");
  std::vector<Excursion> excursions;
  excursions.push_back(Excursion("Колізей", "Рим", 450.0, 3.0));
  excursions.push_back(Excursion("Помпеї", "Неаполь", 800.0, 6.0));
  excursions.insert(excursions.begin() + 1,
                    Excursion("Ватикан", "Рим", 600.0, 4.0));
  PrintAll("Після push_back та insert", excursions);
  excursions.erase(excursions.begin());
  PrintAll("Після erase першого елемента", excursions);
}

void DemoList() {
  PrintTitle("list<Excursion>: push_front, sort, remove_if");
  std::vector<Excursion> samples = SampleExcursions();
  std::list<Excursion> route(samples.begin(), samples.end());
  route.push_front(Excursion("Дуомо", "Мілан", 350.0, 2.0));
  route.sort();
  PrintAll("Після push_front та sort (за ціною)", route);
  route.remove_if(PriceAtMost(500.0));
  PrintAll("Після remove_if(PriceAtMost(500))", route);
}

void DemoDeque() {
  PrintTitle("deque<Excursion>: push_back, push_front, pop_front/pop_back");
  std::deque<Excursion> schedule;
  schedule.push_back(Excursion("Уффіці", "Флоренція", 550.0, 3.0));
  schedule.push_back(Excursion("Гондоли", "Венеція", 900.0, 1.0));
  schedule.push_front(Excursion("Колізей", "Рим", 450.0, 3.0));
  PrintAll("Після push_back, push_back, push_front", schedule);
  schedule.pop_front();
  schedule.pop_back();
  PrintAll("Після pop_front та pop_back", schedule);
}

void DemoSet() {
  PrintTitle("set<Excursion>: insert, find, erase");
  std::vector<Excursion> samples = SampleExcursions();
  std::set<Excursion> unique_excursions(samples.begin(), samples.end());
  auto result =
      unique_excursions.insert(Excursion("Колізей", "Рим", 450.0, 3.0));
  std::cout << "insert дубліката \"Колізей\": "
            << (result.second ? "додано" : "відхилено, такий елемент вже є")
            << "\n";
  PrintAll("set, відсортований за ціною", unique_excursions);
  auto found =
      unique_excursions.find(Excursion("Помпеї", "Неаполь", 800.0, 6.0));
  if (found != unique_excursions.end()) {
    std::cout << "find: " << *found << "\n";
    unique_excursions.erase(found);
  }
  PrintAll("Після erase знайденого елемента", unique_excursions);
}

void DemoMultiset() {
  PrintTitle("multiset<Excursion>: insert, count, erase");
  Excursion colosseum("Колізей", "Рим", 450.0, 3.0);
  std::multiset<Excursion> bookings;
  bookings.insert(colosseum);
  bookings.insert(Excursion("Ватикан", "Рим", 600.0, 4.0));
  bookings.insert(colosseum);
  bookings.insert(colosseum);
  PrintAll("Замовлення екскурсій", bookings);
  std::cout << "count(Колізей): " << bookings.count(colosseum) << "\n";
  bookings.erase(bookings.find(colosseum));
  std::cout << "Після erase(find(Колізей)) лишилось: "
            << bookings.count(colosseum) << "\n";
}

void DemoMap() {
  PrintTitle("map<string, Excursion>: insert, operator[], find, erase");
  std::map<std::string, Excursion> by_title;
  for (const Excursion& excursion : SampleExcursions()) {
    by_title.insert({excursion.title(), excursion});
  }
  by_title["Пантеон"] = Excursion("Пантеон", "Рим", 300.0, 1.5);
  auto found = by_title.find("Ватикан");
  if (found != by_title.end()) {
    std::cout << "find(\"Ватикан\"): " << found->second << "\n";
  }
  by_title.erase("Гондоли");
  std::cout << "Після erase(\"Гондоли\"), ключі впорядковані за алфавітом:\n";
  for (const auto& [title, excursion] : by_title) {
    std::cout << "  " << title << " -> " << excursion << "\n";
  }
}

void DemoMultimap(TravelService* services[], int count) {
  PrintTitle("multimap<string, TravelService*>: insert, count, equal_range");
  std::multimap<std::string, TravelService*> by_category;
  for (int i = 0; i < count; ++i) {
    by_category.insert({services[i]->Category(), services[i]});
  }
  for (const auto& [category, service] : by_category) {
    std::cout << "  " << category << " -> " << service->name() << "\n";
  }
  std::cout << "count(\"Трансфер\"): " << by_category.count("Трансфер")
            << "\n";
  std::cout << "equal_range(\"Трансфер\"):\n";
  auto range = by_category.equal_range("Трансфер");
  for (auto it = range.first; it != range.second; ++it) {
    PrintService(it->second);
  }
}

void DemoStack() {
  PrintTitle("stack<Excursion>: push, top, pop");
  std::stack<Excursion> visited;
  for (const Excursion& excursion : SampleExcursions()) {
    visited.push(excursion);
  }
  std::cout << "top(): " << visited.top() << "\n";
  std::cout << "Повертаємося маршрутом у зворотному порядку:\n";
  while (!visited.empty()) {
    std::cout << "  " << visited.top() << "\n";
    visited.pop();
  }
}

void DemoQueue() {
  PrintTitle("queue<Excursion>: push, front, pop");
  std::queue<Excursion> waiting;
  for (const Excursion& excursion : SampleExcursions()) {
    waiting.push(excursion);
  }
  std::cout << "front(): " << waiting.front()
            << "\nback(): " << waiting.back() << "\n";
  std::cout << "Проводимо екскурсії в порядку черги:\n";
  while (!waiting.empty()) {
    std::cout << "  " << waiting.front() << "\n";
    waiting.pop();
  }
}

void DemoPriorityQueue(TravelService* services[], int count) {
  PrintTitle("priority_queue<TravelService*>: push, top, pop");
  std::priority_queue<TravelService*, std::vector<TravelService*>,
                      ByServicePrice>
      by_price;
  for (int i = 0; i < count; ++i) {
    by_price.push(services[i]);
  }
  std::cout << "top() - найдорожча послуга:\n";
  PrintService(by_price.top());
  std::cout << "Обробка послуг за пріоритетом ціни:\n";
  while (!by_price.empty()) {
    PrintService(by_price.top());
    by_price.pop();
  }
}

void DemoArithmeticFunctors() {
  PrintTitle("Функтори plus, minus, multiplies, divides, modulus, negate");
  std::vector<double> prices = {450.0, 600.0, 800.0};
  std::vector<double> discounts = {50.0, 100.0, 150.0};
  std::vector<double> hours = {3.0, 4.0, 6.0};
  std::vector<double> result(prices.size());
  PrintNumbers("Ціни", prices);

  double total =
      std::accumulate(prices.begin(), prices.end(), 0.0, std::plus<double>());
  std::cout << "plus (сума цін): " << total << "\n";

  std::transform(prices.begin(), prices.end(), discounts.begin(),
                 result.begin(), std::minus<double>());
  PrintNumbers("minus (ціна - знижка)", result);

  std::multiplies<double> multiply;
  std::transform(prices.begin(), prices.end(), result.begin(),
                 [&multiply](double price) { return multiply(price, 2.0); });
  PrintNumbers("multiplies (ціна для двох осіб)", result);

  std::transform(prices.begin(), prices.end(), hours.begin(), result.begin(),
                 std::divides<double>());
  PrintNumbers("divides (ціна за годину)", result);

  std::vector<int> days = {7, 10, 15};
  std::vector<int> extra_days(days.size());
  std::modulus<int> modulus;
  std::transform(days.begin(), days.end(), extra_days.begin(),
                 [&modulus](int day) { return modulus(day, 7); });
  std::cout << "modulus (днів понад повні тижні для 7, 10, 15): ";
  std::copy(extra_days.begin(), extra_days.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::transform(discounts.begin(), discounts.end(), result.begin(),
                 std::negate<double>());
  PrintNumbers("negate (знижки як списання з балансу)", result);
}

void DemoComparisonFunctors() {
  PrintTitle(
      "Функтори equal_to, not_equal_to, greater, less, greater_equal, "
      "less_equal");
  std::vector<double> prices = {450.0, 600.0, 800.0, 550.0, 900.0, 600.0};
  PrintNumbers("Ціни", prices);

  std::equal_to<double> equal;
  std::not_equal_to<double> not_equal;
  std::greater_equal<double> greater_equal;
  std::less_equal<double> less_equal;
  std::cout << "equal_to 600: "
            << std::count_if(prices.begin(), prices.end(),
                             [&equal](double p) { return equal(p, 600.0); })
            << "\n";
  std::cout << "not_equal_to 600: "
            << std::count_if(
                   prices.begin(), prices.end(),
                   [&not_equal](double p) { return not_equal(p, 600.0); })
            << "\n";
  std::cout << "greater_equal 600: "
            << std::count_if(prices.begin(), prices.end(),
                             [&greater_equal](double p) {
                               return greater_equal(p, 600.0);
                             })
            << "\n";
  std::cout << "less_equal 550: "
            << std::count_if(
                   prices.begin(), prices.end(),
                   [&less_equal](double p) { return less_equal(p, 550.0); })
            << "\n";

  std::sort(prices.begin(), prices.end(), std::greater<double>());
  PrintNumbers("sort з greater (за спаданням)", prices);
  std::sort(prices.begin(), prices.end(), std::less<double>());
  PrintNumbers("sort з less (за зростанням)", prices);
}

void DemoLogicalFunctors() {
  PrintTitle("Функтори logical_and, logical_or, logical_not");
  std::vector<bool> needs_visa = {true, false, true, false};
  std::vector<bool> has_insurance = {true, true, false, false};
  std::vector<bool> result(needs_visa.size());
  PrintFlags("Потрібна віза      ", needs_visa);
  PrintFlags("Є страховка        ", has_insurance);

  std::transform(needs_visa.begin(), needs_visa.end(), has_insurance.begin(),
                 result.begin(), std::logical_and<bool>());
  PrintFlags("logical_and (віза і страховка)", result);
  std::transform(needs_visa.begin(), needs_visa.end(), has_insurance.begin(),
                 result.begin(), std::logical_or<bool>());
  PrintFlags("logical_or (віза або страховка)", result);
  std::transform(needs_visa.begin(), needs_visa.end(), result.begin(),
                 std::logical_not<bool>());
  PrintFlags("logical_not (віза не потрібна)", result);
}

void DemoCustomFunctors() {
  PrintTitle("Власні функтори PriceAtMost, InCity, ExcursionPrinter");
  Excursion pompeii("Помпеї", "Неаполь", 800.0, 6.0);
  PriceAtMost cheap(500.0);
  InCity in_rome("Рим");
  std::cout << "PriceAtMost(500) для " << pompeii << ": "
            << (cheap(pompeii) ? "так" : "ні") << "\n";
  std::cout << "InCity(\"Рим\") для " << pompeii << ": "
            << (in_rome(pompeii) ? "так" : "ні") << "\n";
  std::vector<Excursion> excursions = SampleExcursions();
  std::cout << "Екскурсій у Римі: "
            << std::count_if(excursions.begin(), excursions.end(), in_rome)
            << "\n";
}

}  // namespace

void DemoContainers(TravelService* services[], int count) {
  DemoVector();
  DemoList();
  DemoDeque();
  DemoSet();
  DemoMultiset();
  DemoMap();
  DemoMultimap(services, count);
  DemoStack();
  DemoQueue();
  DemoPriorityQueue(services, count);
}

void DemoIterators() {
  PrintTitle("Вхідний ітератор: istream_iterator");
  std::istringstream input("7 10 14 5 21");
  std::istream_iterator<int> first_number(input);
  std::istream_iterator<int> end_of_input;
  std::vector<int> durations(first_number, end_of_input);
  std::cout << "Категорія: "
            << CategoryName<std::istream_iterator<int>>() << "\n"
            << "Зчитано тривалостей турів з потоку: " << durations.size()
            << "\n";

  PrintTitle("Вихідний ітератор: ostream_iterator, back_inserter");
  std::cout << "Категорія: "
            << CategoryName<std::ostream_iterator<int>>() << "\n"
            << "Тривалості: ";
  std::copy(durations.begin(), durations.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  std::vector<int> long_trips;
  std::copy_if(durations.begin(), durations.end(),
               std::back_inserter(long_trips),
               [](int days) { return days >= 10; });
  std::cout << "Тури від 10 днів (back_inserter): ";
  std::copy(long_trips.begin(), long_trips.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::vector<Excursion> samples = SampleExcursions();

  PrintTitle("Односпрямований ітератор: forward_list");
  std::forward_list<Excursion> wishlist(samples.begin(), samples.end());
  std::cout << "Категорія: "
            << CategoryName<std::forward_list<Excursion>::iterator>() << "\n";
  for (auto it = wishlist.begin(); it != wishlist.end(); ++it) {
    std::cout << "  " << *it << "\n";
  }
  std::cout << "std::distance: "
            << std::distance(wishlist.begin(), wishlist.end()) << "\n";

  PrintTitle("Двонаправлений ітератор: list");
  std::list<Excursion> route(samples.begin(), samples.end());
  std::cout << "Категорія: "
            << CategoryName<std::list<Excursion>::iterator>() << "\n"
            << "Маршрут з кінця (--it):\n";
  auto it = route.end();
  while (it != route.begin()) {
    --it;
    std::cout << "  " << *it << "\n";
  }

  PrintTitle("Ітератор довільного доступу: vector");
  std::cout << "Категорія: "
            << CategoryName<std::vector<Excursion>::iterator>() << "\n";
  auto first = samples.begin();
  auto last = samples.end() - 1;
  std::cout << "first[2]: " << first[2] << "\n"
            << "*(first + 4): " << *(first + 4) << "\n"
            << "last - first: " << (last - first) << "\n"
            << "first < last: " << (first < last ? "так" : "ні") << "\n";
}

void DemoAlgorithms() {
  PrintTitle("Алгоритми STL");
  std::vector<Excursion> excursions = SampleExcursions();

  std::cout << "for_each з функтором ExcursionPrinter:\n";
  ExcursionPrinter printer =
      std::for_each(excursions.begin(), excursions.end(), ExcursionPrinter());
  std::cout << "Функтор надрукував елементів: " << printer.printed() << "\n";

  std::sort(excursions.begin(), excursions.end(),
            [](const Excursion& left, const Excursion& right) {
              return left.hours() < right.hours();
            });
  std::cout << "sort за тривалістю:\n";
  std::for_each(excursions.begin(), excursions.end(), ExcursionPrinter());

  auto in_naples =
      std::find_if(excursions.begin(), excursions.end(), InCity("Неаполь"));
  if (in_naples != excursions.end()) {
    std::cout << "find_if(InCity(\"Неаполь\")): " << *in_naples << "\n";
  }

  std::cout << "count_if(PriceAtMost(600)): "
            << std::count_if(excursions.begin(), excursions.end(),
                             PriceAtMost(600.0))
            << "\n";

  auto most_expensive = std::max_element(excursions.begin(), excursions.end());
  auto cheapest = std::min_element(excursions.begin(), excursions.end());
  std::cout << "max_element: " << *most_expensive << "\n"
            << "min_element: " << *cheapest << "\n";

  double total_hours = std::accumulate(
      excursions.begin(), excursions.end(), 0.0,
      [](double sum, const Excursion& excursion) {
        return sum + excursion.hours();
      });
  std::cout << "accumulate (загальна тривалість): " << total_hours
            << " год\n";

  std::vector<std::string> titles(excursions.size());
  std::transform(excursions.begin(), excursions.end(), titles.begin(),
                 [](const Excursion& excursion) { return excursion.title(); });
  std::reverse(titles.begin(), titles.end());
  std::cout << "transform у назви + reverse: ";
  std::copy(titles.begin(), titles.end(),
            std::ostream_iterator<std::string>(std::cout, "; "));
  std::cout << "\n";
}

void DemoFunctors() {
  DemoArithmeticFunctors();
  DemoComparisonFunctors();
  DemoLogicalFunctors();
  DemoCustomFunctors();
}
