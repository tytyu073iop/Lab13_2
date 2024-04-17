#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include "SStudData.h"

using ISP = std::pair<int, SStudData>;

std::vector<SMark> GetMarks(std::string);
int sum(const std::vector<SMark>&);
template <typename T, typename Q>
void printMap(const std::map<T, Q>);
template <typename T>
void printMap(const std::map<int, SStudData>, const T& endIter);
double GetMid(const std::vector<SMark>&);

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
	std::sort(av.begin(), av.end(), [](const SStudData& lhs, const SStudData& rhs) {return lhs.GetName() == rhs.GetName() ? lhs.GetID() < rhs.GetID() : lhs.GetName() > rhs.GetName(); });
	std::map <int, SStudData> m;
	for (auto i : v) { m[i.GetID()] = i; }
	// task 4
	{
		SStudData q(v[0]);
		for (auto i : m) {
			if (sum(q.GetMarks()) < sum(i.second.GetMarks())) { q = i.second; }
		}
		std::cout << "Max sum of marks:" << q;
	}
	// task 5
	{
		auto q(m);
		for (auto i : m) {
			auto e = i.second.GetMarks();
			bool t = std::any_of(e.begin(), e.end(), [](int w) { return w <= 2; });
			if (t) {
				q.insert(i);
			}
		}	
	}
	// task 6
	{
		for (auto i : m) {
			std::cout << "mid of " << i.second.GetName() << " is: " << GetMid(i.second.GetMarks()) << '\n';
		}
	}
	// task 7
	{
		auto av(m);
		std::sort(av.begin(), av.end(), [](const ISP& lhs, const ISP& rhs) {
			return lhs.second.GetName() == rhs.second.GetName() ? 
				GetMid(lhs.second.GetMarks()) > GetMid(rhs.second.GetMarks()) : 
				lhs.second.GetName() < rhs.second.GetName(); 
		});
		printMap(av);
	}
	// task 8
	{
		auto av(m);
		double min = 2, max = 3;
		auto end = std::remove_if(av.begin(), av.end(), [min, max](const ISP& obj) {
			auto p = GetMid(obj.second.GetMarks());
			return !(p >= min && p <= max);
		});
		std::sort(av.begin(), end, [](const ISP& lhs, const ISP& rhs) {return GetMid(lhs.second.GetMarks()) < GetMid(rhs.second.GetMarks()); });
		printMap(av, end);
	}
	// task 9
	{
		auto av(m);
		std::string sub = "Math";
		auto end = std::remove_if(av.begin(), av.end(), [sub](const ISP& obj) {
			auto q = obj.second.GetMarks();
			return !(std::any_of(q.begin(), q.end(), [sub](const SMark& o) {o.Subject == sub; }));
		});
		printMap(av, end);
	}
	// task 10
	{
		std::map<std::string, size_t> am;
		for (auto i : m) {
			for (auto j : i.second.GetMarks()) {
				am[j.Subject]++;
			}
		}
		printMap(am);
	}
}