# Документация за проект Градски транспорт

## Увод
Програма, която по зададена начална спирка, крайна спирка и време на тръгване от начална сприка дава най-краткия път (като време), заедно с автобусите,
на които се прикачваме, за да се придвижим.

## Имплементация 
Проектът е описан от съвкупност от класове, които описват:
* Автобусна спирка
* Автобус
* Разписание на автобусите

Други класове:
* Програма
* Команда
* Работа с файл
* Граф

Класът, който описва една автобусна спирка е BusStop.
Обектите от тип BusStop съдържат следните член - данни:

* string name - Име на сприката
* vector<Bus*> Buses - списък от автобуси, които минават през нея

Класът, който описва един автобус е Bus.

Обектите от тип Bus съдържат следните член - данни:

* unsigned ID - Индентификационен номер на автобус
* BusRoute route - маршрут на автобус(спирките през, които минава)
typedef vector<BusStop*> BusRoute;

Класът, който описва разписание на автобусите е Schedule.
Обектите от тип Schedule съдържат следните член - данни:
* unordered_map<int, stopSchedule> schedule - Хеш таблица, чрез която за всяко ID на автобус и име на спирка -> разписание
typedef  unordered_map<string, vector<unsigned>> stopSchedule;

Класът, който пази всичката информация е Program.
Обектите от тип Program съдържат следните член - данни:
* vector<BusStop*> BusStopsContainer - контейнер за всички спирки
* vector<Bus*> BusesContainer - контейнер за всички автобуси
* Schedule* schedule - разписание

Класът, с който можем да модифицираме контейнерите (да добавяме и премахваме елементи) е Command.
Обектите от тип Command съдържат следните член - данни:
*	Program* containers - указател към контейнтерите

Класът, с който обработвме информация от файл и записваме такава във файл е FileInputOutput.
Обектите от тип FileInputOutput съдържат следните член - данни:
* ifstream reading_file - за четене на информация от файл
* ofstream writing_file - за писане на информация във файл

Класът, чрез който е реализирана основната задача на програмата е Graph.
Обектите от тип Graph съдържат следните член - данни:
* vecttor<Node> - списък с върхове
Обектите от тип Node съдържат следните член - данни:
* BusStop* stop - спирка
* vector<Edge> adj - списък с автобуси, които отиват до следващ връх(спирка)
* Node* pred - указател към предишен връх(спирка)
* int timeFromStart - време
* int busID - номер на автобус
Обектите от тип Edge съдържат следните член - данни:
* Bus* bus - автобус
* Node* to - указател към следващ връх(спирка)

## Алгоритъм на Дейкстра (намиране на най - къс път от един връх до друг).
# Описание на алгоритъма
1. Вземаме възелът, чието име на спирка отговаря на зададеното начално - този връх приемаме за начален
2. Инициализираме графът, върху, който ще приложим алгоритъма.
3. Докато не обходим всички върхове:
  3.1 ако върхът има вече добавено време за достигане и не е в множеството И вече зададеното време за достигане на този връх е по - малко от новото време за достигане,
    то вземи върхът, който дава по - малкото време
   3.2 за всяко ребро на взетия връх обнови информацията по следният начин:
      - намери всички автобуси, които отиват от взетия връх до друг връх през съответното ребро(съседните спирки) и ги запази
      - за всеки един автобус намираме най - краткото време за достигане на върхът(спирката) през съответното ребро и избираме най - краткото от всички най - кратки времена
      - ако намерените резултати са по - добри от старите -> актуализираме реброто
4. Извеждаме пътят на на пътуването на екрана по следният начин: 
  - от вече достигната спирка се движим по *pred указателят и добавяме всеки връх в стек
  - докато стекът не е празен извеждаме имената спирките и номерът на автобуса, с който сме пътували
5. Извеждаме най - доброто време за пътуване, което е времето за достигане на финалната ни спирка

