#include<regex>
#include<iostream>
#include<fstream>
#include<string>
#include<exception>
//6. Напишите программу, обнаруживающую даты в текстовом файле.
//Выведите на печать каждую строку, содержащую хотя бы одну дату, в
//формате номер строки : текст.Начните с регулярного выражения для
//простого формата, например 20.02.2004, и протестируйте на нем программу.Затем добавьте новые форматы.
//
//7. Напишите программу(аналогичную предыдущей), которая находит в
//файле номера кредитных карточек.Разберитесь в том, какие форматы
//используются для записи номеров кредитных карточек, и реализуйте
//их проверку в вашей программе.
void load_from_file(const std::string path,const std::regex reg)
{
	std::ifstream in;
	in.open(path);
	int linelo = 0;
	for (std::string line; getline(in, line);)
	{
		++linelo;
		std::smatch matches;
		if (regex_search(line, matches, reg))
		{
			std::cout << linelo << ":" << matches[0] << std::endl;
			if (1 < matches.size() && matches[1].matched)
			{
				std::cout << "\t    " << matches[1] << std::endl;
			}
		}
	}
	in.close();
}
int main()
{
	std::string path1 = "file.txt";
	std::string path2 = "file1.txt";
	std::regex pat1{ R"(\d{4}.\d{2}.\d{2}(\s*-\s*\d{2}::\d{2})?)" };
	std::regex pat2{ R"(\d{4} \d{4} \d{4} \d{4} \d{2}/\d{2}(\s*\w*\s*\w*)?)" };
	try
	{
		load_from_file(path1, pat1);
		std::cout << "==================================" << std::endl;
		load_from_file(path2, pat2);
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what() << std::endl;
		std::cerr << "File open error" << std::endl;
	}
	return 0;
}