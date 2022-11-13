#pragma once
#include <iostream>

class Student
{   
    public:
        Student(int student_id,
                std::string name , std::string sex, 
                std::string school, std::string major,
                int campus_card_id)
            : student_id_(student_id),
              name_(name), sex_(sex), school_(school), major_(major),
              campus_card_id_(campus_card_id)
        {
            //
        }
        void Show() {
            std::cout << "\n----------------STUDNET INFO----------------\n";
            std::cout << "student_id_\t"
                 << "name_\t"
                 << "sex_\t"
                 << "school_\t"
                 << "major_\t"
                 << "campus card id\n";
            std::cout << student_id_  << "\t\t"
                 << name_    << "\t"
                 << sex_     << "\t"
                 << school_  << "\t"
                 << major_   << "\t"
                 << campus_card_id_;
            std::cout << "\n---------------------------------------------\n\n" << std::flush;
        }
    private:
        int student_id_;
        
        std::string name_;
        std::string sex_;
        std::string school_;
        std::string major_;

        int campus_card_id_;
};





class CampusCard
{   
    public:
        CampusCard(int campus_card_id, int student_id, int balance)
            :campus_card_id_(campus_card_id), student_id_(student_id), balance_(balance)
        {
            //
        }
    void Show() {
            std::cout << "\n---------------CAMPUSCARD INFO---------------\n";
            std::cout << "campus_card_id\t" << "balance\t" << "student_id\n";
            std::cout << campus_card_id_ << "\t\t"
                      << balance_        << "\t"
                      << student_id_     << "\n";
            std::cout << "\n---------------------------------------------\n\n" << std::flush;
        }
    private:
        int campus_card_id_ = 0;
        int balance_ = 0;
        int student_id_ = 0;
};
