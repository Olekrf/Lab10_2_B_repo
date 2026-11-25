#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum Specialty { CS, INFORMATICS, MATH_ECON, PHYS_INFORM, LABOR };

string specialtyStr[] = { "Комп. науки", "Інформатика", "Матем. та екон.",
                          "Фіз. та інформ.", "Труд. навчання" };

struct Student
{
    string    prizv;
    int       kurs;
    Specialty spec;
    int       physics;
    int       math;
    union
    {
        int programming;
        int numerical_methods;
        int pedagogy;
    };
};

void   Create(Student* p, const int N);
void   Print(Student* p, const int N);
int    ThirdGrade(const Student& s);
double StudentAverage(const Student& s);
int    BinSearch(Student* p, const int N, const string prizv, const int thirdGrade, const double avg);

int main()
{
    int N;
    cout << "Введіть кількість студентів N: "; cin >> N;

    Student* p = new Student[N];

    string prizv;
    double avg;
    int    thirdGrade;
    int    found;
    int    menuItem;

    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - бінарний пошук студента" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            cout << "Введіть ключі пошуку:" << endl;
            cout << " оцінка з третього предмету: "; cin >> thirdGrade;
            cout << " середній бал: ";               cin >> avg;
            cout << " прізвище: ";                   cin >> prizv;
            cout << endl;

            found = BinSearch(p, N, prizv, thirdGrade, avg);
            if (found != -1)
                cout << "Знайдено студента під номером: " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                 << "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    delete[] p;

    return 0;
}

void Create(Student* p, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cout << "     прізвище: ";   cin >> p[i].prizv;
        cout << "     курс: ";       cin >> p[i].kurs;
        cout << "     спеціальність (0 - Комп. науки, 1 - Інформатика, 2 - Матем. та екон.," << endl
             << "                    3 - Фіз. та інформ., 4 - Труд. навчання): ";
        cin >> spec;
        p[i].spec = (Specialty)spec;
        cout << "     оцінка з фізики: ";      cin >> p[i].physics;
        cout << "     оцінка з математики: ";  cin >> p[i].math;
        switch (p[i].spec)
        {
        case CS:
            cout << "     оцінка з програмування: "; cin >> p[i].programming;
            break;
        case INFORMATICS:
            cout << "     оцінка з чисельних методів: "; cin >> p[i].numerical_methods;
            break;
        case MATH_ECON:
        case PHYS_INFORM:
        case LABOR:
            cout << "     оцінка з педагогіки: "; cin >> p[i].pedagogy;
            break;
        }
        cout << endl;
    }
}

void Print(Student* p, const int N)
{
    cout << "Студенти групи" << endl;
    cout << "=================================================================================================="
         << endl;
    cout << "|  №  | Прізвище    | Курс | Спеціальність   | Фізика | Матем. | Програм. | Числ.мет. | Педагог. |"
         << endl;
    cout << "--------------------------------------------------------------------------------------------------"
         << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(11) << left << p[i].prizv << " "
             << "| " << setw(4) << right << p[i].kurs << " "
             << "| " << setw(15) << left << specialtyStr[p[i].spec] << " "
             << "| " << setw(6) << right << p[i].physics << " "
             << "| " << setw(6) << right << p[i].math << " ";
        switch (p[i].spec)
        {
        case CS:
            cout << "| " << setw(8) << right << p[i].programming << " |"
                 << setw(12) << right << "|" << setw(11) << right << "|" << endl;
            break;
        case INFORMATICS:
            cout << "|" << setw(11) << right << "|"
                 << " " << setw(9) << right << p[i].numerical_methods << " |"
                 << setw(11) << right << "|" << endl;
            break;
        case MATH_ECON:
        case PHYS_INFORM:
        case LABOR:
            cout << "|" << setw(11) << right << "|"
                 << setw(12) << right << "|"
                 << " " << setw(8) << right << p[i].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "=================================================================================================="
         << endl;
    cout << endl;
}

int ThirdGrade(const Student& s)
{
    switch (s.spec)
    {
    case CS:
        return s.programming;
    case INFORMATICS:
        return s.numerical_methods;
    default:
        return s.pedagogy;
    }
}

double StudentAverage(const Student& s)
{
    return (s.physics + s.math + ThirdGrade(s)) / 3.0;
}

int BinSearch(Student* p, const int N, const string prizv, const int thirdGrade, const double avg)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (ThirdGrade(p[m]) == thirdGrade &&
            StudentAverage(p[m]) == avg &&
            p[m].prizv == prizv)
            return m;

        if ((ThirdGrade(p[m]) < thirdGrade)
            ||
            (ThirdGrade(p[m]) == thirdGrade &&
             StudentAverage(p[m]) < avg)
            ||
            (ThirdGrade(p[m]) == thirdGrade &&
             StudentAverage(p[m]) == avg &&
             p[m].prizv < prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}