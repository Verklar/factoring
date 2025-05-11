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

	vector<BI> trial_factors, fermat_factors, pollard_factors, dixon_factors;//���� ��� ������ ��������� ���������

	void out(vector<BI> a);//������� ��� ������ ��������� ��������� � �������

	vector<BI> TrialDivisionOpt(BI n);//�������, ������� ������� �������� ����� 
	void Trial(BI n);//�������, ������� ���������� ��������� ����� � ������ trial_factors

	bool issquare(BI n);//�������� �� ��, �������� �� ����� ������ ���������
	void Fermat(BI n);//�������, ������� ���������� ������� �������� �����
	void FermatHelper(BI n);

	BI f(BI x, BI n);//�������, f(x) - ��� ���������� ������������������
	void PollardRho(BI n);//�������, ������� ���������� ������� �������� �����

	vector<BI> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409 };//������ ������� ����� ��� ������� getP

	vector<BI> getP(BI n);//������� ��� ������ ������� ����� �� ������� �
	vector<vector<BI>> B_numbers;//������ �-������� ����� � �������� �� ������� ���������
	bool isB_smooth(BI n, BI div, vector<BI> P);//�������� ����� �� ��������� �� �
	bool areNiceVec(vector<BI> a, vector<BI> b);//���������, ����� �� ����� ��������������� �������� ������� ���������� �������� �����
	void findB_smooth(BI n, vector<BI>P);//������� ��� ������ ������� �����
	BI Mult(vector<BI> a, vector<BI> b, vector<BI> P);//�������, ������� ������������ ����� ����� ���������
	void Dixon(BI n);//�������, ������� ���������� ������� �������� �����
};

