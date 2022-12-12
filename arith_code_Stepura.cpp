#include <string>
#include <iostream>
#define symbol_break '\0'
#define _low_edge 0
#define _high_edge 65535
#define EOF_symbol '-'
using namespace std;

class arithmetic
{
private:
	// определение половины, четверти и 3/4 
	const int first_qtr = _high_edge / 4 + 1;
	const int half = 2 * first_qtr;
	const int third_qtr = 3 * first_qtr;
	// объекты для работы с текстом */
	string text;
	string abc;
	string encode;
	int* freq; // массив частот
protected:
	static bool debug_mode; //режим вывода дебаг - информации
public:
	void show_table(); // таблица частот и символов
	string get_encode(); // закодированная строка
	void input_string(string input); // string text
	void get_abc(); // алфавит
	void get_frequency(); // массив частот
	void get_next_symbol(int i, int* current); // получение индекса следующего символа
	string write_bits(bool bit, int bits_to_foll); // записать биты
	void encode_text(); // метод кодирования текста
};

bool arithmetic::debug_mode = false;

void arithmetic::show_table()
{
	cout << endl << text << endl;
	cout << abc << endl;
	for (int i = 0; i < abc.size(); i++)
	{
		cout << abc[i] << " - " << freq[i] << endl;
	}
	cout << endl;
}

string arithmetic::get_encode()
{
	return encode;
}

void arithmetic::input_string(string input)
{
	text = input;
	text.push_back(symbol_break);
}

void arithmetic::get_abc()
{
	bool exit_flag = 0; // добавить символ - в начало
	abc.push_back(EOF_symbol);
	for (int i = 0; i < text.size(); i++)
	{
		exit_flag = 0;
		for (int j = 0; j < abc.size(); j++)
		{
			if (abc[j] == text[i])			//если в алфавите уже есть такая буква
			{
				exit_flag = 1;				//выходим, если нашли такую букву
				break;
			}
		}
		if (exit_flag == 1)					//если мы находили букву ранее
		{
			continue;						//переход на следующую итерацию для след. буквы
		}
		else								//если буква найдена не была
		{
			abc.push_back(text[i]);
			continue;
		}
	}
}

void arithmetic::get_frequency()
{
	freq = new int[abc.size()];
	for (int i = 0; i < abc.size(); i++)
	{
		freq[i] = 0;
	}
	for (int j = 0; j < abc.size(); j++)
	{
		for (int i = 0; i < text.size(); i++)
		{
			if (abc[j] == text[i])
			{
				freq[j]++;
			}
		}
		if (j > 0)
		{
			freq[j] += freq[j - 1];
		}
	}
}

void arithmetic::get_next_symbol(int i, int* current)
{
	// индекс символа из текста в алфавите
	bool exit = false;
	for (i; i < text.size() && !exit; i++)
	{
		char temp_text = text[i];
		for (int j = 0; j < abc.size(); j++)
		{
			char temp_abc = abc[j];
			if (temp_text == temp_abc)
			{
				*current = j;
				exit = true;
				break;
			}
		}
	}
}

string arithmetic::write_bits(bool bit, int bits_to_foll)
{
	string temp;
	temp += to_string(bit);
	while (bits_to_foll > 0)
	{
		temp += to_string(!bit);
		bits_to_foll -= 1;
	}
	return temp;
}

void arithmetic::encode_text()
{
	int mass_size = text.length();
	unsigned short int* _low = new unsigned short int[mass_size];
	unsigned short int* _high = new unsigned short int[mass_size];
	_low[0] = _low_edge;
	_high[0] = _high_edge;
	int current = 1;	// какой элемент берём 
	int i = 0;			// где находимся 
	unsigned int range = 0;
	int del = freq[abc.size() - 1]; // del - последняя накопленная частота
	int bits_to_foll = 0;
	string code = "";
	while (i < text.length())
	{
		get_next_symbol(i, &current);
		i += 1;

		range = _high[i - 1] - _low[i - 1] + 1;
		_low[i] = _low[i - 1] + (range * freq[current - 1]) / del;
		_high[i] = _low[i - 1] + (range * freq[current]) / del - 1;
		if (debug_mode)
		{
			cout << "[" << _low[i] << "; " << _high[i] << ")" << endl;
		}

		for (;;)
		{
			if (_high[i] < half)
			{
				code += write_bits(0, bits_to_foll);
				bits_to_foll = 0;
			}
			else if (_low[i] >= half)
			{
				code += write_bits(1, bits_to_foll);
				bits_to_foll = 0;
				_low[i] -= half;
				_high[i] -= half;
			}
			else if (_low[i] >= first_qtr && _high[i] < third_qtr)
			{
				bits_to_foll += 1;
				_low[i] -= first_qtr;
				_high[i] -= first_qtr;
			}
			else break;
			_low[i] = 2 * _low[i];
			_high[i] = 2 * _high[i] + 1;
		}
	}
	/*if (debug_mode)
	{
		cout << endl << code << endl;
	}*/
	encode = code;
}

string arith_cod(string in)
{
	arithmetic coding;
	coding.input_string(in);
	coding.get_abc();
	coding.get_frequency();
	coding.encode_text();
	return coding.get_encode();
}
int main()
{
	string a;
	a = "абобушка";
	cout << "encode: " << arith_cod(a) << endl;
	return 0;
}