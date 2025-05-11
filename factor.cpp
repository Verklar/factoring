#include "factor.h"

void factor::out(vector<BI> a)
{
    for (int i = 0; i < a.size(); i++) cout << a[i] << " ";
}


vector<BI> factor::TrialDivisionOpt(BI n)
{
    vector<BI> factor;
    while (n % 2 == 0)
    {
        factor.push_back(2);
        n /= 2;
    }
    for (BI d = 3; d * d <= n; d += 2)
    {
        while (n % d == 0)
        {
            factor.push_back(d);
            n /= d;
        }
    }
    if (n > 1) factor.push_back(n);
    return factor;
}

void factor::Trial(BI n)
{
    trial_factors = TrialDivisionOpt(n);
}

bool factor::issquare(BI n)
{
    BI temp = BI(sqrt(BF(n)));

    if (temp * temp == n) return true;
    return false;
}

void factor::FermatHelper(BI n)
{
    if (n < 2) return;
    while (n % 2 == 0) { n /= 2; fermat_factors.push_back(2); }
    Fermat(n);
}

void factor::Fermat(BI n)
{
    BI x = BI(ceil(sqrt(BF(n)))), k = -1, a, b;
    BI temp = 2;
    while (!issquare(temp))
    {
        k++;
        temp = pow(x + k, 2) - n;
    }
    a = x + k + BI(sqrt(BF(temp)));
    b = x + k - BI(sqrt(BF(temp)));

    if (b != 1)
    {
        Fermat(a);
        Fermat(b);
    }
    else
    {
        fermat_factors.push_back(a);
    }
}

BI factor::f(BI x, BI n)
{
    return (x * x + 1) % n;
}

void factor::PollardRho(BI n)
{
    if (n < 2) return;
    BI x = rand() % (n - 2), y = x, g = 1;
    while (g == 1 || g == 0)
    {
        if (g == 0) { x = rand() % (n - 2); y = x; }//может получиться, что было выбранное неудачное изначальное значение
        x = f(x, n);
        y = f(f(y, n), n);
        g = gcd(abs(x - y), n);
    }
    if (g != n)
    {
        PollardRho(n / g);
        PollardRho(g);
    }
    else
    {
        pollard_factors.push_back(g);
    }
}

vector<BI> factor::getP(BI n)
{
    BF l = exp(sqrt(log(BF(n)) * log(log(BF(n)))));
    BI B = BI(sqrt(l));
    vector<BI>P;
    for (long long i = 0; primes[i] <= B; i++)
    {
        P.push_back(primes[i]);
    }
    return P;
}

bool factor::isB_smooth(BI n, BI div, vector<BI> P)
{
    vector<BI> num = { div };
    num.resize(P.size() + 1);//задаём длину массиву
    BI i = div * div % n;

    for (long long j = 0; j < P.size(); j++)//проходим по списку простых чисел, проверяем гладкость числа
    {
        while (i % P[j] == 0)
        {
            i /= P[j];
            num[j + 1]++;//записываем степени простых делителей
        }
    }
    if (i == 1)
    {
        B_numbers.push_back(num);//если число в-гладкое, добавляем в список
        return true;
    }
    else return false;
}

bool factor::areNiceVec(vector<BI> a, vector<BI> b)
{
    if (a[0] == b[0]) return 0;//одинаковые числа
    for (long long i = 1; i < a.size(); i++)
    {
        if ((a[i] + b[i]) % 2 == 1) return false;//если сумма степеней соотв. чисел нечётная, то векторы не подходят
    }
    return true;
}

void factor::findB_smooth(BI n, vector<BI>P)
{
    B_numbers.clear();
    BI size = P.size();
    BI k = BI(ceil(sqrt(BF(n)))) - 2;
    if (n < 1000) k = 1;
    for (BI i = k; i < n; i++)
    {
        if (isB_smooth(n, i, P))
        {
            long long bsize = B_numbers.size() - 1;//запоминаем индекс нового числа
            for (long long j = 0; j < bsize - 1; j++)//проходим по всем предыдущим числам и проверяем их на совместимость с новым
            {
                if (areNiceVec(B_numbers[j], B_numbers[bsize]))
                {
                    BI first = (B_numbers[bsize][0] * B_numbers[j][0]) % n;
                    BI second = Mult(B_numbers[bsize], B_numbers[j], P);
                    BI div = 1;
                    if (first + second == n || first == second) continue;//если числа +- сравнимы по модулю, ищем дальше
                    else
                    {
                        div = gcd(first - second, n);
                        Dixon(div);//делитель может быть составным
                        Dixon(n / div);
                        return;
                    }
                }
            }
        }
        if (B_numbers.size() >= 10 * size + 3) break;//если прошли много (или все) чисел и не нашли подходящих, число простое
    }
    dixon_factors.push_back(n);
}

BI factor::Mult(vector<BI> a, vector<BI> b, vector<BI> P)
{
    BI num = 1;
    for (long long i = 0; i < P.size(); i++)
    {
        long long k = long long((a[i + 1] + b[i + 1]) / 2);
        num = num * pow(P.at(i), k);
    }
    return num;
}

void factor::Dixon(BI n)
{
    if (n < 2) return;
    if (n < 50)//для малых чисел работает некорректно
    {
        vector<BI> temp = TrialDivisionOpt(n);
        dixon_factors.insert(dixon_factors.begin(), temp.begin(), temp.end());
        return;
    }
    vector<BI> P = getP(n);
    findB_smooth(n, P);//функция для поиска В-гладких чисел и делителей числа
}
