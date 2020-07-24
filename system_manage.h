#ifndef SYSTEM_MANAGE_H
#define SYSTEM_MANAGE_H

#include "system_functions.h"
#include "data_types.h"
#include <string>

//this is a class for file and data management
// it has only one instance.
//it mamange 4 files: student_data.dat, campus_card_data.dat, 
//						inpour_record.dat and consume_record.dat. 
class SystemManage{
    public:
        //Constructor and Destructor
        SystemManage();
        ~SystemManage();
        //Student
        void AddStudent(Student* student);
        void DeleteStudent(Student* student);

        Student* SearchStudent(int student_id);

        //CampusCard
        void AddCampusCard(CampusCard* CampusCard);
        void DeleteCampusCard(CampusCard* campusCard);
        CampusCard* SearchCampusCard(int student_id);
        int GetNewCampusCardId();

        //file management
        void WriteData();
        void ReadData();
        void Record(std::string filename, int id, int amount);
    private:
        int campus_card_count_ = 0;
        int student_count_ = 0;
        
        CampusCard* campus_card_head_;		//Manage it as a list in the memory
        CampusCard* campus_card_current_;
        
        Student* student_head_;
        Student* student_current_;
};

extern SystemManage system_manage;	//only one instance of SystemManage to avoid disoder.

#endif
