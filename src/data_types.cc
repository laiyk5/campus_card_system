#include "data_types.hh"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//class student 
std::ostream& operator<<(std::ostream& os , const Student& student){
    os  << student.student_id_ << " "
        << student.name_    << " "
        << student.sex_     << " "
        << student.school_  << " "
        << student.major_   << " "
        << student.campus_card_id_;
    return os;
}

void Student::Show(){
    cout << "\n----------------STUDNET INFO----------------\n";
    cout    << "student_id_\t"
            << "name_\t"
            << "sex_\t"
            << "school_\t"
            << "major_\t"
            << "campus card id\n";
    cout    << student_id_  << "\t\t"
            << name_    << "\t"
            << sex_     << "\t"
            << school_  << "\t"
            << major_   << "\t"
            << campus_card_id_;
    
    cout << "\n---------------------------------------------\n\n";
}


//class CampusCard
std::ostream& operator<<(std::ostream& os, const CampusCard& campus_card)
{   
    os << campus_card.campus_card_id_ << " "
       << campus_card.passwd_   << " "
       << campus_card.balance_  << " "
       << campus_card.state_    << " "
       << campus_card.student_id_;

    return os;
}

void CampusCard::Show(){
    cout << "\n---------------CAMPUSCARD INFO---------------\n";
    std::cout   << "campus_card_id\t" << "passwd\t" << "balance\t" << "state\t" << "student_id\n";
    std::cout   << campus_card_id_ << "\t\t"
                << passwd_         << "\t"
                << balance_        << "\t"
                << state_          << "\t"
                << student_id_     << "\n";
    cout << "\n---------------------------------------------\n\n";
}