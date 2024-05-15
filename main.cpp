#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <random>
#include <ctime>
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

int main()
{
    srand(time(nullptr));

    // task1();
    // task2();
    task3();
    // task4();
    // task5();

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

    auto mostFrequentWord = max_element(words.begin(), words.end(), [&](const string &a, const string &b)
                                        { return count(words.begin(), words.end(), a) < count(words.begin(), words.end(), b); });

    cout << *mostFrequentWord << endl;
}

void task3()
{
    vector<string> fruits = {"apple", "apple", "banana", "grape", "apricot", "apricot", "honeydew", "kiwi", "avocado", "lemon",
                             "mango", "orange", "avocado", "avocado", "quince", "raspberry", "apricot",
                             "apple"};

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
