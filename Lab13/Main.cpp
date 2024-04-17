#include <fstream>
#include <sstream>
#include <algorithm>
#include "SStudData.h"

std::vector<SMark> GetMarks(std::string);

int main() {
	std::ifstream ifs("Data.txt");
	if (!ifs.good()) { std::cerr << "falure of opening Data.txt"; return 1; }
	std::string s;
	std::vector<SStudData> v;
	while (std::getline(ifs, s))
	{
		std::stringstream ss(s);
		std::string Name, Id, Marks;
		char bin;
		std::getline(ss, Name, ';');
		ss >> bin;
		std::getline(ss, Id, ';');
		ss >> bin;
		std::cout << Id;
		std::getline(ss, Marks);
		v.push_back(Name, stoi(Id), GetMarks(Marks));
	}
	auto av(v);
	auto zv(v);
	auto iv(v);
	std::sort(av.begin(), av.end(), [](const SStudData& lhs, const SStudData& rhs) {return lhs.GetName() < rhs.GetName(); });

}