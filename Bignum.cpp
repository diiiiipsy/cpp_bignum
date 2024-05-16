#include "Bignum.h"

void Bignum::set_num(const string& data)
{
	flag = 1;
	abs_num = "";
	int n = data.length();
	int state = 0;
	for (int i = 0; i < n; i++)
	{
		switch (state)
		{
		case 0:
			if (data[i] == '+')
				state = 1;
			else if (data[i] == '-')
			{
				state = 1;
				flag = 0;
			}
			else if (data[i] == '0')
				state = 3;
			else if (data[i] >= '1' && data[i] <= '9')
			{
				state = 2;
				abs_num += data[i];
			}
			break;
		case 1:
			if (data[i] == '-')
				flag = !flag;
			else if (data[i] == '0')
				state = 3;
			else if (data[i] >= '1' && data[i] <= '9')
			{
				state = 2;
				abs_num += data[i];
			}
			break;
		case 2:
			if (data[i] >= '0' && data[i] <= '9')
				abs_num += data[i];
			break;
		case 3:
			if (data[i] >= '1' && data[i] <= '9')
			{
				state = 2;
				abs_num += data[i];
			}
			break;
		}
	}
}

void Bignum::print()const
{
	if (!abs_num.length())
		cout << '0' << endl;
	else
	{
		if (!flag)
			cout << '-';
		cout << abs_num << endl;
	}
}

Bignum operator +(Bignum& a, Bignum& b)
{
	Bignum answer;
	if (a.flag == b.flag)
	{
		string ans="";
		string a_data = a.abs_num;
		string b_data = b.abs_num;
		if (a_data.length() < b_data.length() || (a_data.length()==b_data.length()&&a_data<b_data))
			a_data.swap(b_data);
		int length = a_data.length()+1;
		string tmp1(length, '0'), tmp2(length, '0');
		for (int i = 0; i < a_data.length(); i++)
			tmp1[i] = a_data[a_data.length() - 1 - i];
		for (int i = 0; i < b_data.length(); i++)
			tmp2[i] = b_data[b_data.length() - 1 - i];
		int* to_int_tmp1 = new int[length];
		int* to_int_tmp2 = new int[length];
		for (int i = 0; i < length; i++)
		{
			to_int_tmp1[i] = tmp1[i] - '0';
			to_int_tmp2[i] = tmp2[i] - '0';
		}//倒序准备


		for (int i = 0; i < length; i++)
		{
			to_int_tmp1[i] += to_int_tmp2[i];
			
			if (to_int_tmp1[i] >= 10)
			{
				to_int_tmp1[i] -= 10;
				to_int_tmp1[i + 1]++;
				tmp1[i] = '0' + to_int_tmp1[i];
			}
			else
				tmp1[i] = '0' + to_int_tmp1[i];
		}
		if (tmp1[length - 1])
			ans += tmp1[length - 1];
		for (int i = 0; i < length - 1; i++)
		{
			ans += tmp1[length - 2 - i];
		}
		answer.set_num(ans);
		answer.flag = a.flag;
		return answer;
	}
	else
	{
		string ans = "";
		string a_data = a.abs_num;
		string b_data = b.abs_num;
		if (a_data.length() < b_data.length() || (a_data.length() == b_data.length() && a_data < b_data))
			a_data.swap(b_data);
		int length = a_data.length() + 1;
		string tmp1(length, '0'), tmp2(length, '0');
		for (int i = 0; i < a_data.length(); i++)
			tmp1[i] = a_data[a_data.length() - 1 - i];
		for (int i = 0; i < b_data.length(); i++)
			tmp2[i] = b_data[b_data.length() - 1 - i];
		int* to_int_tmp1 = new int[length];
		int* to_int_tmp2 = new int[length];
		for (int i = 0; i < length; i++)
		{
			to_int_tmp1[i] = tmp1[i] - '0';
			to_int_tmp2[i] = tmp2[i] - '0';
		}//倒序准备


		for (int i = 0; i < length; i++)
		{
			to_int_tmp1[i] -= to_int_tmp2[i];

			if (to_int_tmp1[i] < 0)
			{
				to_int_tmp1[i] += 10;
				to_int_tmp1[i + 1]--;
				tmp1[i] = '0' + to_int_tmp1[i];
			}
			else
				tmp1[i] = '0' + to_int_tmp1[i];
		}
		if (tmp1[length - 1])
			ans += tmp1[length - 1];
		for (int i = 0; i < length - 1; i++)
		{
			ans += tmp1[length - 2 - i];
		}
		answer.set_num(ans);
		if ( a.abs_num.length() < b.abs_num.length() || (a.abs_num.length() == b.abs_num.length() && a.abs_num < b.abs_num))
			answer.flag = b.flag;
		else
			answer.flag = a.flag;
		return answer;
	}
}
Bignum operator -(Bignum& a, Bignum& b)
{
	Bignum tmp = b;
	tmp.flag = !b.flag;
	return a+tmp;
}

Bignum operator *(Bignum& a, Bignum& b)
{
	Bignum one,tmp1,tmp2;
	one.set_num("1");
	tmp2 = b;
	tmp1.flag = 1;
	tmp2.flag = 1;
	while (tmp2.flag)
	{
		tmp1 = tmp1 + a;
		tmp2 = tmp2 - one;
	}
	if (a.flag != b.flag)
		tmp1.flag = 0;
	return tmp1;
}
Bignum operator /(Bignum& a, Bignum& b)
{
	Bignum one, cnt, tmp1, tmp2;
	one.set_num("1");
	tmp1 = a;
	tmp2 = b;
	tmp1.flag = 1;
	tmp2.flag = 1;
	while (tmp1.flag)
	{
		tmp1 = tmp1 - tmp2;
		cnt = cnt + one;
	}
	cnt = cnt - one;
	return cnt;
}