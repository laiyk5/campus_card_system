#include <iostream>
#include "system_manage.h"
#include <fstream>
#include <ctime> 
#include <string>
using std::fstream;
using std::cout;
using std::cin;
using std::string;
using std::ios;
using std::fstream;
using std::time;

SystemManage system_manage;
SystemManage::SystemManage(){
    ReadData();
}

SystemManage::~SystemManage(){
    WriteData();
    if(student_count_ == 0){
        delete student_head_;
        delete campus_card_current_;
    }else{
        while(student_head_){
            Student* temp = student_head_;
            student_head_ = student_head_->next_;
            delete temp;
        }
    }

    if(campus_card_count_ == 0){
        delete campus_card_head_;
        delete campus_card_current_;
    }else{
        while(campus_card_head_){
            CampusCard* temp = campus_card_head_;
            campus_card_head_ = campus_card_head_->next_;
            delete temp;
        }
    }
}





//*************************************************************************************
//Students Management
//*************************************************************************************





void SystemManage::AddStudent(Student* student_ptr){
    if (student_count_ == 0) {
        student_head_ = student_current_ = student_ptr;
    }
    else {
        student_current_->next_ = student_ptr;
        student_current_ = student_current_->next_;
    }

    student_current_->next_ = nullptr;
    ++student_count_;
    return;     
}






void SystemManage::DeleteStudent(Student* student_ptr){ 
    if(student_head_ == student_ptr){               //if delete the head        
        //make new link
        Student* temp_head = student_head_;
        student_head_ = student_head_->next_;

        //set pointer current
        if(student_current_ == student_ptr){
            student_current_ = nullptr;
        }

        delete temp_head;
        student_ptr = nullptr;
    }else{                                          //if delete the body
        Student* student_before = student_head_;    
        while(student_before->next_ != student_ptr){
            student_before = student_before->next_;
            continue;
        }
        student_before->next_ = student_ptr->next_;
        //set pointer current
        if(student_current_ == student_ptr){
            student_current_ = student_before;
        }

        delete student_ptr;
        student_ptr = nullptr;

    }
    --student_count_;
    return;
}






Student* SystemManage::SearchStudent(int student_id){
    //search
    Student* student_ptr = student_head_;
    while(student_ptr != nullptr){
        if(student_ptr->GetStudentId() == student_id){
            return student_ptr;
        }
        student_ptr = student_ptr->next_;
        continue;
    }

    //if not found
    return nullptr;

}






//**********************
//CampusCard Management
//**********************





void SystemManage::AddCampusCard(CampusCard* campus_card_ptr){
    if(campus_card_count_ == 0){
        campus_card_head_ = campus_card_current_ = campus_card_ptr;
    }else{
        campus_card_current_->next_ = campus_card_ptr;
        campus_card_current_ = campus_card_current_->next_;
    }

    campus_card_current_->next_ = nullptr;
    ++campus_card_count_;
    return;    
}





void SystemManage::DeleteCampusCard(CampusCard* campus_card_ptr){
    if(campus_card_head_ == campus_card_ptr){
        CampusCard* temp_head = campus_card_head_;
        campus_card_head_ = campus_card_head_->next_;
        delete temp_head;
    }else{
        CampusCard* campus_card_before = campus_card_head_;    
        while(campus_card_before->next_ != campus_card_ptr){
            campus_card_before = campus_card_before->next_;
            continue;
        }
        campus_card_before->next_ = campus_card_ptr->next_;
        delete campus_card_ptr;
    }
    --campus_card_count_;
    return;
}





CampusCard* SystemManage::SearchCampusCard(int campus_card_id){
    //search
    CampusCard* campus_card_ptr = campus_card_head_;
    while(campus_card_ptr != nullptr){
        if(campus_card_ptr->GetCampusCardId() == campus_card_id){
            return campus_card_ptr;
        }
        campus_card_ptr = campus_card_ptr->next_;
        continue;
    }

    //if not found
    return nullptr;

}





int SystemManage::GetNewCampusCardId(){
    if(campus_card_count_ == 0){
        return 0;
    }else{
        return campus_card_current_->GetCampusCardId() + 1;
    }
}





//*************************************************************************************
//file operations
//*************************************************************************************





void SystemManage::ReadData(){
    //studnet
    fstream inFile;
    inFile.open("student_datas.dat", ios::in);
    if(!inFile){
        std::cerr << "Fail to open student_datas.dat!";
        exit(1);
    }
    while(!inFile.eof()){
        if(inFile.peek() == EOF){
            inFile.close();
            break;
        }else{
            //read data
            int student_id, campus_card_id;
            string name, sex, school, major;
            inFile >> student_id >> name >> sex >> school >> major >> campus_card_id;

            //construct a Student
            Student* newStudent_ptr = new Student(student_id, name, sex, school, major);
            newStudent_ptr->SetCampusCardId(campus_card_id);

            //store in the list
            AddStudent(newStudent_ptr);
        }
    }
    inFile.close();


    //campus card
    inFile.open("campus_card_datas.dat", ios::in);
    if(!inFile){
        std::cerr << "Fail to open campus_card_datas.dat!";
        exit(1);
    }
    while(!inFile.eof()){
        if(inFile.peek() == EOF){
            inFile.close();
            break;
        }else{
            //read Datas
            int campus_card_id, passwd, balance, student_id;
            bool state;
            inFile >> campus_card_id >> passwd >> balance >> state >> student_id;
            
            //construct a campus_card
            CampusCard* new_card_ptr = new CampusCard(campus_card_id, passwd, balance, state); 
            new_card_ptr->SetStudentId(student_id);

            //store in the list.
            AddCampusCard(new_card_ptr);
        }
    }
    inFile.close();
}





void SystemManage::WriteData(){
    fstream outFile;
    outFile.open("student_datas.dat", ios::out | ios::trunc);
    if(!outFile){
        std::cerr << "Faile to open student_datas.dat!\n";
        exit(1);
    }

    Student* student_head_ptr = student_head_;
    while(student_head_ptr != nullptr){
        outFile << endl << *student_head_ptr;
        student_head_ptr = student_head_ptr->next_;
    }
    outFile.close();


    outFile.open("campus_card_datas.dat", ios::out | ios::trunc);
    if(!outFile){
        std::cerr << "Faile to open campus_card_datas.dat!\n";
        exit(1);
    }

    CampusCard* campus_card_head_ptr = campus_card_head_;
    while(campus_card_head_ptr != nullptr){
        outFile << endl << *campus_card_head_ptr;
        campus_card_head_ptr = campus_card_head_ptr->next_;
    }
    outFile.close();
}





//*************************************************************************************
//Private Functions
//*************************************************************************************





void SystemManage::Record(string filename, int id, int amount){
    fstream outFile;
    outFile.open(filename,ios::out|ios::app);

    time_t ti = time(0);
    outFile << endl << id << " " << amount << " " << ctime(&ti);
    outFile.close();
}
