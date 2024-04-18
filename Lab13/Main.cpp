#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "SStudData.h"

using ISP = std::pair<int, SStudData>;

std::vector<SMark> GetMarks(std::string);
template <typename T, typename Q>
std::vector<T> GetVector(const std::map<Q, T>&);
int sum(const std::vector<SMark>&);
template <typename T, typename Q>
void printMap(const std::map<T, Q>);
template <typename T>
void printMap(const std::map<int, SStudData>, const T& endIter);
double GetMid(const std::vector<SMark>&);
template <typename T>
void PrintVector(const std::vector<T>&);
template <typename T, typename Q>
void printVector(const std::vector<T>&, const Q& endIter);

template <typename T>
void func(T) = delete;

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
		// ss >> bin;
		std::getline(ss, Id, ';');
		// ss >> bin;
		std::getline(ss, Marks);
		// std::cout << Id;
		v.push_back(SStudData(Name, stoi(Id), GetMarks(Marks)));
	}
	auto av(v);
	std::sort(av.begin(), av.end(), [](const SStudData& lhs, const SStudData& rhs) {return lhs.GetName() == rhs.GetName() ? lhs.GetID() < rhs.GetID() : lhs.GetName() > rhs.GetName(); });
	std::map <int, SStudData> m;
	for (auto i : v) { /*m[i.GetID()] = i;*/ m.insert({i.GetID(), i}); }
	// task 4
	{
		SStudData q(v[0]);
		for (auto i : m) {
			if (sum(q.GetMarks()) < sum(i.second.GetMarks())) { q = i.second; }
		}
		std::cout << "Max sum of marks: " << q;
	}
	std::cout << '\n';
	// task 5
	{
		std::map<int, SStudData> q;
		for (auto i : m) {
			auto e = i.second.GetMarks();
			bool t = std::any_of(e.begin(), e.end(), [](const SMark& w) { return w.Mark <= 2; });
			if (t) {
				q.insert(i);
			}
		}
		std::cout << "Students with mark <= 2:\n";
		printMap(q);
	}
	std::cout << '\n';
	// task 6
	{
		for (auto i : m) {
			std::cout << "mid of " << i.second.GetName() << " is: " << GetMid(i.second.GetMarks()) << '\n';
		}
	}
	std::cout << '\n';
	// task 7
	{
		auto av(GetVector(m));
		std::sort(av.begin(), av.end(), [](const SStudData& lhs, const SStudData& rhs) {
			return lhs.GetName() == rhs.GetName() ? 
				GetMid(lhs.GetMarks()) > GetMid(rhs.GetMarks()) : 
				lhs.GetName() < rhs.GetName(); 
		});
		for (auto i : av) {
			std::cout << i.GetName() << ' ' << GetMid(i.GetMarks()) << ' ' << i.GetID() << '\n';
		}
	}
	std::cout << '\n';
	// task 8
	{
		auto av(GetVector(m));
		double min = 2, max = 3;
		auto end = std::remove_if(av.begin(), av.end(), [min, max](const SStudData& obj) {
			auto p = GetMid(obj.GetMarks());
			return !(p >= min && p <= max);
		});
		std::sort(av.begin(), end, [](const SStudData& lhs, const SStudData& rhs) {return GetMid(lhs.GetMarks()) > GetMid(rhs.GetMarks()); });
		printVector(av, end);
	}
	std::cout << '\n';
	// task 9
	{
		auto av(GetVector(m));
		std::string sub = "Math";
		auto end = std::remove_if(av.begin(), av.end(), [sub](const SStudData& obj) {
			auto q = obj.GetMarks();
			return !(std::any_of(q.begin(), q.end(), [sub](const SMark& o) { return o.Subject == sub; }));
		});
		printVector(av, end);
	}
	std::cout << '\n';
	// task 10
	{
		std::map<std::string, size_t> am;
		for (auto i : m) {
			for (auto j : i.second.GetMarks()) {
				am[j.Subject]++;
			}
		}
		for (auto i : am) {
			std::cout << i.first << " " << i.second << '\n';
		}
	}
}

std::vector<SMark> GetMarks(std::string s) {
	std::vector<SMark> v;
	std::stringstream ss(s);
	char bin;
	std::string sub;
	std::string mark;
	while (ss >> sub && std::getline(ss, mark, ',')) {
		v.push_back(SMark(sub, stoi(mark)));
		// ss >> bin;
	}
	return v;
}

int sum(const std::vector<SMark>& v) {
	int s = 0;
	for (auto i : v) { s += i.Mark; }
	return s;
}

template <typename T, typename Q>
void printMap(const std::map<T, Q> m) {
	for (auto i : m) {
		std::cout << i.second << '\n';
	}
}

template <typename T>
void printMap(const std::map<int, SStudData> m, const T& endIter) {
	for (auto i = m.begin(); i != endIter; i++) {
		std::cout << i->second << '\n';
	}
}

template <typename T, typename Q>
std::vector<T> GetVector(const std::map<Q, T>& m) {
	std::vector<T> v;
	for (auto i : m) { v.push_back(i.second); }
	return v;
}

double GetMid(const std::vector<SMark>& v) {
	double s = 0;
	for (auto i : v) { s += i.Mark; }
	return s / v.size();
}

template <typename T>
void PrintVector(const std::vector<T>& v) {
	for (auto i : v) {
		std::cout << i << '\n';
	}
}

template <typename T, typename Q>
void printVector(const std::vector<T>& v, const Q& endIter) {
	for (auto i = v.begin(); i != endIter; i++) {
		std::cout << *i << '\n';
	}
}