#pragma once
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

//There's two data function defined in this file: Student and CampusCard
//They have only get(), set(), and show(), operator<< and constructors.

//we manage them by another class: SystemManage.

class Student
{   
    friend std::ostream& operator<<(std::ostream&, const Student&);

    public:
    // Constructor;
        Student(int student_id,
                std::string name , std::string sex, 
                std::string school, std::string major,
                int campus_card_id = -1)
            : student_id_(student_id), campus_card_id_(campus_card_id),
              name_(name), sex_(sex), school_(school), major_(major)
        {
            //
        }
    //print functions
        void Show();

        int GetStudentId()  { return student_id_;        }
        int GetCampusCardId(){ return campus_card_id_;  }
        void SetCampusCardId(int campus_card_id){   campus_card_id_ = campus_card_id;  }      
    //As a list node;
        Student* next_ = nullptr;
    //private datas
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
    friend std::ostream& operator<<(std::ostream& os, const CampusCard& ); 
    
    public:
    //Constructor
        CampusCard(int campus_card_id, int passwd, int balance, bool state)
            :campus_card_id_(campus_card_id), passwd_(passwd), balance_(balance), state_(state)
        {
            //
        }
    //print functions
        void Show();
    //as a list node;
        CampusCard* next_ = nullptr;
    //Get and Set
        int GetCampusCardId()   { return campus_card_id_;   }
        int GetPasswd()        { return passwd_;    }
        int GetBalance()       { return balance_;   }
        bool GetState()         { return state_;     }
        int GetStudentId()      { return student_id_; }

        void SetCampusCardId(int id) {campus_card_id_ = id; }
        void SetBalance(int balance){ balance_ = balance; }
        void SetPasswd(int passwd)  { passwd_ = passwd; }
        void SetState(bool state)  { state_ = state;   }
        void SetStudentId(int student_id)     { student_id_ = student_id; }
    private:
        int campus_card_id_ = 0;
        int passwd_ = 0;
        int balance_ = 0;
        bool state_ = false;
        int student_id_ = 0;
};
