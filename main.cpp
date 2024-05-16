#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <random>
#include <fstream>
#include <ctime>
#include <numeric>

using namespace std;

struct InfoStudent
{
    string name;
    string surname;

    int ComputerScience;
    int Mathematics;
    int Physics;
    int ProbabilityTheory;
};

void task1();
int sumDigits(int num);

void task2();
void task3();
void task4();

void task5();
void getRandomScore(InfoStudent &student);
int sumBall(InfoStudent &student);

std::ostream &operator<<(std::ostream &os, const InfoStudent &student)
{
    os << "Имя: " << student.name << ", Фамилия: " << student.surname << std::endl;
    os << "Информатика: " << student.ComputerScience << std::endl;
    os << "Математика: " << student.Mathematics << std::endl;
    os << "Физика: " << student.Physics << std::endl;
    os << "Теория вероятностей: " << student.ProbabilityTheory << std::endl;
    return os;
}

void task6();

void task7();
bool findWords(const vector<vector<char>> &grid, const string &word);
bool checkHorizontal(const vector<vector<char>> &grid, vector<vector<char>>::const_iterator rowIt, vector<char>::const_iterator colIt, const string &word);

void task8();
void task9();
void task10();

int main()
{
    srand(time(nullptr));

    int choice;
    std::cout << "Выберите задачу (1-10): ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        task1();
        break;
    case 2:
        task2();
        break;
    case 3:
        task3();
        break;
    case 4:
        task4();
        break;
    case 5:
        task5();
        break;
    case 6:
        task6();
        break;
    case 7:
        task7();
        break;
    case 8:
        task8();
        break;
    case 9:
        task9();
        break;
    case 10:
        task10();
        break;
    default:
        std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
        break;
    }

    return 0;
}

// Функция, вычисляющая сумму цифр числа
int sumDigits(int num)
{
    int sum = 0;
    while (num)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

void task1()
{
    vector<int> numbers{213, 123, 1243, 423, 2134, 54, 3, 235, 13};

    cout << "original: ";
    for (auto i : numbers)
    {
        cout << i << " ";
    }
    cout << endl;

    std::sort(numbers.begin(), numbers.end(), [](int a, int b)
              { return sumDigits(a) > sumDigits(b); });
    cout << "sort: ";
    for (auto i : numbers)
    {
        cout << i << " ";
    }
    cout << endl;
}

void task2()
{
    vector<std::string> words = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon",
        "mango", "orange", "peach", "quince", "raspberry",
        "strawberry", "apple", "banana", "cherry", "date"};

    for (auto i : words)
    {
        cout << i << " ";
    }
    cout << endl;

    auto mostFrequentWord = max_element(words.begin(), words.end(), [&](const string &a, const string &b)
                                        { return count(words.begin(), words.end(), a) < count(words.begin(), words.end(), b); });

    cout << "most common word:" << *mostFrequentWord << endl;
}

void task3()
{
    vector<string> fruits = {"apple", "apple", "banana", "grape", "apricot", "apricot", "honeydew", "kiwi", "avocado", "lemon",
                             "mango", "orange", "avocado", "avocado", "quince", "raspberry", "apricot",
                             "apple"};

    cout << "original: ";
    for (const auto &fruit : fruits)
    {
        cout << fruit << " ";
    }
    cout << endl;

    for (auto it = fruits.begin(); it != fruits.end();)
    {
        string word = *it;

        if (word[0] == 'a')
        {
            // Считаем, сколько раз встречается этот фрукт
            int countWord = count(fruits.begin(), fruits.end(), word);

            // Если это единственный экземпляр, переходим к следующему
            if (countWord == 1)
            {
                ++it;
            }
            // Если есть дубликаты, меняем их на "-"
            else
            {

                auto nIt = find(it + 1, fruits.end(), word);
                while (nIt != fruits.end() && *nIt == word)
                {
                    *nIt = "";
                    nIt = find(it + 1, fruits.end(), word);
                }
            }
        }
        else
        {
            ++it;
        }
    }

    // auto rIt = partition(fruits.begin(), fruits.end(), [&](string word)
    //                      { return word == "-"; });
    cout << "modified: ";
    for (const auto &fruit : fruits)
    {
        cout << fruit << " ";
    }
    cout << endl;
}

void task4()
{
    vector<string> phoneNumbersCallers = {
        "123456785", "987654321", "123456785", "123456789", "456789123",
        "987654325", "456789125", "987654325", "4236234325", "789123456",
        "789123456", "88805553535", "456789125", "123456785"};

    cout << "phoneNumbersCallers: ";
    for (const auto &phone : phoneNumbersCallers)
    {
        cout << phone << " ";
    }
    cout << endl;

    unordered_set<string> uniqueFiveEndingCallersChecker;
    vector<string> uniqueFiveEndingCallers;

    for (const auto &number : phoneNumbersCallers)
    {
        if (number.back() == '5' && uniqueFiveEndingCallersChecker.find(number) == uniqueFiveEndingCallersChecker.end())
        {
            uniqueFiveEndingCallers.push_back(number);
            uniqueFiveEndingCallersChecker.insert(number);
        }
    }

    if (uniqueFiveEndingCallers.size() >= 5)
    {
        auto fifthUniqueNumber = next(uniqueFiveEndingCallers.begin(), 4);
        cout << "Пятый уникальный звонивший, чей номер оканчивается на 5: " << *fifthUniqueNumber << endl;
    }
    else
    {
        cout << "Пятый уникальный звонивший, чей номер оканчивается на 5 не существует" << endl;
    }
}

void task5()
{
    vector<InfoStudent> students;
    const int numStudents = 7; // Количество студентов
    const int minBall = 210;

    for (size_t i = 0; i < numStudents; i++)
    {
        InfoStudent student;

        getRandomScore(student);
        students.push_back(student);
    }

    for (auto i : students)
    {
        cout << i << endl;
    }

    cout << "----------------------" << endl;

    auto it = partition(students.begin(), students.end(), [&](InfoStudent stud)
                        { return sumBall(stud) < minBall; });

    int numberOfExpelled = 0;

    for (auto i = students.begin(); i < it; i++)
    {
        InfoStudent studentExpelled = *i;
        cout << studentExpelled.name << "" << studentExpelled.surname << endl;
        numberOfExpelled++;
    }

    cout << numberOfExpelled << endl;
}

int sumBall(InfoStudent &student)
{

    return student.ComputerScience + student.Mathematics + student.Physics + student.ProbabilityTheory;
}

void getRandomScore(InfoStudent &student)
{

    vector<string> nameList = {"Александр", "Дмитрий", "Анна", "Мария", "Сергей", "Екатерина", "Иван", "Ольга", "Максим", "Елена"};
    vector<string> surnameList = {"Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов", "Попов", "Соколов", "Лебедев", "Козлов", "Новиков"};

    student.name = nameList[rand() % nameList.size()];
    student.surname = surnameList[rand() % surnameList.size()];
    student.ComputerScience = 10 + rand() % 99 - 10;
    student.Mathematics = 10 + rand() % 99 - 10;
    student.Physics = 10 + rand() % 99 - 10;
    student.ProbabilityTheory = 10 + rand() % 99 - 10;
}

void task6()
{
    string inputFile = "text.txt";
    string outputFile = "output.txt";
    string wordToReplace = "2023";
    string newWord = "2012";

    // Чтение текста из входного файла
    ifstream input(inputFile);
    if (!input.is_open())
    {
        cout << "Не удалось открыть файл " << inputFile << endl;
        return;
    }

    string line;
    vector<std::string> lines;
    while (getline(input, line))
    {
        lines.push_back(line);
    }
    input.close();

    // Замена слова
    for (string &l : lines)
    {
        size_t pos = l.find(wordToReplace);
        while (pos != string::npos)
        {
            l.replace(pos, wordToReplace.length(), newWord);
            pos = l.find(wordToReplace, pos + newWord.length());
        }
    }

    // Запись результата в выходной файл
    ofstream output(outputFile);
    if (!output.is_open())
    {
        cerr << "Не удалось открыть файл " << outputFile << std::endl;
        return;
    }

    for (const std::string &l : lines)
    {
        output << l << std::endl;
    }
    output.close();

    std::cout << "Готово! Результат записан в файл " << outputFile << std::endl;
}

void task7()
{
    vector<vector<char>> grid = {
        {'O', 'A', 'A', 'N'},
        {'E', 'A', 'T', 'E'},
        {'I', 'H', 'K', 'R'},
        {'I', 'E', 'A', 'T'},
        {'Q', 'F', 'U', 'D'}};

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    vector<string> words = {"OATH", "PEA", "EAT", "RAIN", "TE"};
    vector<string> result;

    for (const auto &word : words)
    {
        if (findWords(grid, word))
        {
            result.push_back(word);
        }
    }

    cout << "слова которые можно найти в сетке: ";
    for (const string &word : result)
    {
        cout << word << " ";
    }
    cout << endl;
}

bool findWords(const vector<vector<char>> &grid, const string &word)
{
    for (auto rowIt = grid.begin(); rowIt != grid.end(); ++rowIt)
    {
        auto colIt = find(rowIt->begin(), rowIt->end(), word[0]);
        while (colIt != rowIt->end())
        {
            if (checkHorizontal(grid, rowIt, colIt, word))
            {
                return true;
            }
            colIt = find(next(colIt), rowIt->end(), word[0]);
        }
    }

    return false;
}

bool checkHorizontal(const vector<vector<char>> &grid, vector<vector<char>>::const_iterator rowIt, vector<char>::const_iterator colIt, const string &word)
{
    if (distance(colIt, rowIt->end()) >= word.size())
    {
        return equal(word.begin(), word.end(), colIt);
    }
    return false;
}

void task8()
{
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};

    cout << "vector: ";
    for (auto num : numbers)
    {
        cout << num << " ";
    }

    cout << endl;

    // Находим максимальный и минимальный элементы
    auto max_it = std::max_element(numbers.begin(), numbers.end());
    auto min_it = std::min_element(numbers.begin(), numbers.end());

    // Вычисляем сумму максимального и минимального элементов
    int sum = *max_it + *min_it;

    cout << "Максимальный элемент: " << *max_it << std::endl;
    cout << "Минимальный элемент: " << *min_it << std::endl;
    cout << "Сумма максимального и минимального элементов: " << sum << std::endl;
}

void task9()
{
    vector<int> numbers = {-2, 5, -3, 8, -1, 4};
    cout << "vector: ";
    for (auto num : numbers)
    {
        cout << num << " ";
    }

    cout << endl;

    // Находим сумму всех отрицательных элементов
    int sum_negative = accumulate(numbers.begin(), numbers.end(), 0, [](int acc, int x)
                                  { return x < 0 ? acc + x : acc; });
    int abs_sum_negative = abs(sum_negative);

    // Заменяем отрицательные элементы на модуль суммы всех отрицательных
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [&](int x)
                   { return x < 0 ? abs_sum_negative : x; });

    // Вывод результата
    cout << "modified vector: ";
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    cout << endl;
}

void task10()
{
    std::vector<int> numbers = {-2, 5, -3, 8, -1, 4, 0, 1, -4, 6};

    cout << "vector: ";
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    cout << endl;

    // Подсчет чисел больше 0 с использованием std::count_if
    int count = std::count_if(numbers.begin(), numbers.end(), [](int x)
                              { return x > 0; });

    cout << "Количество чисел больше 0: " << count << endl;
}
