#include "SStudData.h"


SStudData::SStudData(std::string Name, int ID, std::vector<SMark>&& Marks) : Name(Name), ID(ID), Marks(Marks) {
    
}

SStudData& SStudData::operator=(const SStudData& rhs) {
    if (this != &rhs) {
        Name = rhs.Name;
        ID = rhs.ID;
        Marks = rhs.Marks;
    }
    return *this;
}

std::string SStudData::GetName() const {
    return Name;
}

int SStudData::GetID() const {
    return ID;
}

const std::vector<SMark>& SStudData::GetMarks() const {
    return Marks;
}

void SStudData::AddMark(const SMark& mark) {
    Marks.push_back(mark);
}

std::ostream& operator<<(std::ostream& os, const SStudData& rhs) {
    os << rhs.Name << ";" << rhs.ID << ";";
    for (const auto& mark : rhs.Marks) {
        os << mark.Subject << " " << mark.Mark << ",";
    }
    return os;
}