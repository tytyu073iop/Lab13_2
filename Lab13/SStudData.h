#pragma once
#include <vector>
#include <iostream>
#include "SMark.h"

class SStudData {
	std::string Name;
	int ID;
	std::vector<SMark> Marks;
public:
	SStudData(std::string Name, int ID, std::vector<SMark>&& Marks);
	SStudData& operator=(const SStudData& rhs);
	friend std::ostream& operator<<(std::ostream& os, const SStudData& rhs);
	std::string GetName() const;
	int GetID() const;
	const std::vector<SMark>& GetMarks() const;
	void AddMark(const SMark& mark);
};