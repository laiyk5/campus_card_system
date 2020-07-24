#include "system_functions.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <climits>
#include "data_types.h"

using std::iostream;
using std::cout;
using std::endl;   
using std::cin;
using std::string;
using std::vector;
using std::fstream;
using std::ios;


//It's already defined in menu.cpp
 int GetInt(int min, int max, string que, string w_que);
//{
//     int ret;
//     cout << que;
//     cin >> ret;

//     char ch;
//     while((ch = getchar()) != '\n' ){
//             continue;
//     }

//     while(ret < min || ret > max){
//         while((ch = getchar()) != '\n' ){
//             continue;
//         }
//         cout << w_que;
//         cin.clear();
//         cin >> ret;
//     }
//     return ret;    
// }






//***************************************************************************************
//Student Operations
//****************************************************************************************



void AddStudent::DoTask(){
    cout << "---------------------Add Student---------------------(-1 to quit)" << endl;
    //create a new student;
    cout << "Please enter information as followed: \n";
    int student_id;
    std::string name, sex, school, major;
    cout << "-----------------------------------\n";
    cout << "student id\tname\tsex\tschool\tmajor\n";
    cout << "-----------------------------------" << endl;
    cin >> student_id;
    if(student_id == -1) {return; }     //-1 to quit

    cin >> name >> sex >> school >> major;
    
    Student* student_ptr = new Student(student_id, name, sex, school, major);

    //check if it's duplicated
    if(system_manage.SearchStudent(student_id) != nullptr){
        cout << "Student has already exist.\n";
        return;
    }

    //create new card;
    int campus_card_id = system_manage.GetNewCampusCardId();
    CampusCard* CampusCard_ptr = new CampusCard(campus_card_id, 0, 0, false);
    CampusCard_ptr->SetStudentId(student_id);
    //bind new card to the student.
    student_ptr->SetCampusCardId(campus_card_id);

    //add student and campus card to the list.
    system_manage.AddStudent(student_ptr);
    system_manage.AddCampusCard(CampusCard_ptr);

    system_manage.WriteData();

    cout << "New Student: " << student_id << endl;
    cout << "New Campus card id: " << campus_card_id << endl;
}




void DeleteStudent::DoTask(){
    //get Student;
    cout << "----------------DeleteStudent-----------------(-1 to quit)" << endl;
    int student_id = GetInt(-1, INT16_MAX, "==> student ID: ", "==> Invalid ID. Please try again: ");

    if(student_id == -1) {return; }      //-1 to quit;

    Student* student_ptr = system_manage.SearchStudent(student_id);
    //check
    if(student_ptr == nullptr){
        cout << "Student does not exit!" << endl;
        return;
    }

    //get CampusCard Id
    int campus_card_id = student_ptr->GetCampusCardId();
    CampusCard* campus_card_ptr = system_manage.SearchCampusCard(campus_card_id);
    //check
    if(campus_card_ptr == nullptr){
        cout << "Campus card does not exit!" << endl;
    }

    //delete student and his/her campus card;
    system_manage.DeleteStudent(student_ptr);
    system_manage.DeleteCampusCard(campus_card_ptr);

    system_manage.WriteData();

    cout << "Deleted Student: " << student_id << endl;
    cout << "Deleted Campus card id: " << campus_card_id << endl;
}




void BindNewCard::DoTask(){
    cout << "-----------------------Bind New Card--------------------(-1 to quit)" << endl;
    //get student;
    int student_id = GetInt(-1, INT16_MAX, "==> student ID: ", "==> Invalid ID. Please try again: ");
    if(student_id == -1) {return; }           //-1 to quit

    Student* student_ptr = system_manage.SearchStudent(student_id);
    
    //check student
    if(student_ptr == nullptr) {
	    cout << "Student does not exist!"<< endl;
		return; 
	}
    //get old card
    CampusCard* old_campus_card_ptr = system_manage.SearchCampusCard(student_ptr->GetCampusCardId());
    
    //create and add new card;
    CampusCard* campus_card_ptr = new CampusCard(*old_campus_card_ptr);
    campus_card_ptr->SetState(false);
    campus_card_ptr->SetPasswd(0);
    
    campus_card_ptr->SetCampusCardId(system_manage.GetNewCampusCardId());    
    campus_card_ptr->SetStudentId(student_id);
    system_manage.AddCampusCard(campus_card_ptr);

    //bind
    student_ptr->SetCampusCardId(campus_card_ptr->GetCampusCardId());
    
    //delete old card;
    if(old_campus_card_ptr != nullptr){
        system_manage.DeleteCampusCard(old_campus_card_ptr);
    }

    system_manage.WriteData();

    cout << "New Card: " << campus_card_ptr->GetCampusCardId() << " belongs to Student " << student_id << endl;
}





void ShowStudent::DoTask(){
    //getStudent
    cout << "(-1 to quit)" << endl;
    int student_id = GetInt(-1, INT16_MAX, "==> student ID: ", "==> Invalid ID. Please try again: ");
    if(student_id == -1) {return; }
    
    Student* student_ptr = system_manage.SearchStudent(student_id);

    //check
    if(student_ptr == nullptr){
        cout << "Students does not exit!" << endl;
        return;
    }
    //print
    student_ptr->Show();
}






//***************************************************************************************
//Student Operations
//****************************************************************************************





void ActivateCampusCard::DoTask(int campus_card_id){
	cout << "------------------- Activate campus card -------------------(-1 to quit)" << endl;
    //Get pointer of the target CampusCard 
    CampusCard* CampusCard_ptr = system_manage.SearchCampusCard(campus_card_id) ;
    
    //Activate it
    CampusCard_ptr->SetState(true);
    //modify the passwd

    int passwd = GetInt(-1, INT16_MAX, "Please enter your new passwd: ", "Invalid passwd. Please try again: ");
    if(passwd == -1) {return; }
    
    while(passwd == 0 || passwd == CampusCard_ptr->GetPasswd()){
        passwd = GetInt(0, INT16_MAX, "Invalid passwd. Please try again: ",  "Invalid passwd. Please try again: ");
    }

    CampusCard_ptr->SetPasswd(passwd);

    cout << "Passwd of your Campus Card has been reset.\n";
    cout << "Card Activated" << endl;
    return;

    system_manage.WriteData();
}





void Consume::DoTask(int campus_card_id){
    cout << "-----------------------Consume---------------------(-1 to quit)" << endl;
	//get target campus card
    CampusCard* campus_card_ptr = system_manage.SearchCampusCard(campus_card_id);
    
    //check if it's activated
    if(!campus_card_ptr->GetState()){
        cout << "\nPlease activate the campus card first.\n" << endl;
        return;
    }
    
    int amount;
    //get amount and Consume
    while(true){
        amount = GetInt(-1, 500, "==>Amount: ","==>No more than $500 and no less than $0. Please try again: ");
        if(amount == -1) {return; }
        
        if(amount > campus_card_ptr->GetBalance()){
            cout << "Your balance is not enough. " << endl;
            return;
        }else{
            break;
        }
    }

    
    int new_balance = campus_card_ptr->GetBalance() - amount;
    campus_card_ptr->SetBalance(new_balance);
    
    system_manage.Record("consume_records.dat", campus_card_id,  amount);


    system_manage.WriteData();

}





void Inpour::DoTask(){
	cout << "-----------------------Inpour------------------------(-1 to quit)" << endl;
    //get target campus card
    int campus_card_id = GetInt(0, INT16_MAX, "==> campus card ID: ", "==> Invalid ID. Please try again: ");
    CampusCard* campus_card_ptr = system_manage.SearchCampusCard(campus_card_id);
    
    //check
    if(campus_card_ptr == nullptr){
        cout << "This card is not exist!" << endl;
        return;
    }

    //get amount and inpour
    int amount = GetInt(-1, 500, "==>Amount: ","==>No more than $500 and no less than $0. Please try again: ");
    if(amount == -1) {return; }
    
    int new_balance = campus_card_ptr->GetBalance() + amount;
    campus_card_ptr->SetBalance(new_balance);

    system_manage.Record("inpour_records.dat", campus_card_id, amount);

    cout << "Added balance: " << amount << endl;
    cout << "current balance: " << new_balance << endl;

    system_manage.WriteData();
}





void ReportLoss::DoTask(int campus_card_id){

    CampusCard* campus_card_ptr = system_manage.SearchCampusCard(campus_card_id);
    
    campus_card_ptr->SetState(false);
    cout << "Your card has already to be set as \"LOSS\". But you can activate it again. \n\n";

    system_manage.WriteData();
}




void ShowCampusCard::DoTask(){
  //get target campus card
    cout << "(-1 to quit)" << endl;
    int campus_card_id = GetInt(0, INT16_MAX, "==> campus card id: ", "==> Invalid ID, please try again.");
    if(-1 == campus_card_id ) {return; }
    
    DoTask(campus_card_id);       
}


void ShowCampusCard::DoTask(int campus_card_id){
    //get target campus card;
    CampusCard* campus_card_ptr = system_manage.SearchCampusCard(campus_card_id);
    if(campus_card_ptr == nullptr){
        cout << "Card does not exit!" << endl;
        return;
    }
    //show campus_card_ptr;
    campus_card_ptr->Show();
}





void ShowConsumeRecords::DoTask(int campus_card_id){
    fstream inFile;
    inFile.open("consume_records.dat", ios::in);
    int id, amount;
    string day, month, date, time, year;
    cout << "CardId" << "\t" << "amount" << "\t" << "time" << endl;
    while(!inFile.eof()){
        inFile >> id >> amount >> day >> month >> date >> time >> year;
        if(!inFile.eof()){
        	break;
		}
        if(id == campus_card_id){
            cout << id << "\t" << amount << "\t" 
                << day << " " << month << " " << date << " "
                << time<< " " << year << " " << endl;
        }
    }   
}



void ShowInpourRecords::DoTask(int campus_card_id){
    fstream inFile;
    inFile.open("inpour_records.dat", ios::in);
    int id, amount;
    string day, month, date, time, year;
    cout << "CardId" << "\t" << "amount" << "\t" << "time" << endl;
    while(!inFile.eof()){ 
        inFile >> id >> amount >> day >> month >> date >> time >> year;
        if(!inFile.eof()){
        	break;
		}
        if(id == campus_card_id){
            cout << id << "\t" << amount << "\t" 
                << day << " " << month << " " << date << " "
                << time<< " " << year << " " << endl;
        }
    }    
}




void ShowStudentInfo::DoTask(int campus_card_id_){
    CampusCard* campus_card_ptr = system_manage.SearchCampusCard(campus_card_id_);
    int student_id = campus_card_ptr->GetStudentId();
    Student* student_ptr = system_manage.SearchStudent(student_id);

    student_ptr->Show();

}
