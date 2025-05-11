#pragma once
#include <iostream>
#include <numeric>
#include <../boost/multiprecision/cpp_int.hpp>
#include <../boost/multiprecision/cpp_bin_float.hpp>
#include <../boost/multiprecision/cpp_dec_float.hpp>
#include <../boost/multiprecision/number.hpp>
#include <cmath>
#include<fstream>
using namespace std;
using namespace boost::multiprecision;

using BF = boost::multiprecision::cpp_bin_float_100;
using BI = boost::multiprecision::cpp_int;

class factor
{
public:

	vector<BI> trial_factors, fermat_factors, pollard_factors, dixon_factors;//поля для записи найденных делителей

	void out(vector<BI> a);//функция для вывода найденных делителей в консоль

	vector<BI> TrialDivisionOpt(BI n);//функция, которая находит делители числа 
	void Trial(BI n);//функция, которая записывает найденные числа в вектор trial_factors

	bool issquare(BI n);//проверка на то, является ли число полным квадратом
	void Fermat(BI n);//функция, которая рекурсивно находит делители числа
	void FermatHelper(BI n);

	BI f(BI x, BI n);//функция, f(x) - для построения последовательности
	void PollardRho(BI n);//функция, которая рекурсивно находит делители числа

	vector<BI> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409 };//список простых чисел для функции getP

	vector<BI> getP(BI n);//функция для поиска простых чисел до границы В
	vector<vector<BI>> B_numbers;//список В-гладких чисел и степеней их простых делителей
	bool isB_smooth(BI n, BI div, vector<BI> P);//проверка числа на гладкость по В
	bool areNiceVec(vector<BI> a, vector<BI> b);//проверяет, чётна ли сумма соответствующих степеней простых множителей гладкого числа
	void findB_smooth(BI n, vector<BI>P);//функция для поиски гладких чисел
	BI Mult(vector<BI> a, vector<BI> b, vector<BI> P);//функция, которая подсчитывает левую часть сравнения
	void Dixon(BI n);//функция, которая рекурсивно находит делители числа
};

