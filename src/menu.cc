#include "menu.hh"

#include <iostream>
#include <string>
#include <climits>
using std::cin;
using std::cout;
using std::endl;
using std::string;


//modifiable IO function. It make the program more readable and IO more tidy. 
int GetInt(int min, int max, string que, string w_que){
    int ret;
    cout << que;
    cin >> ret;
    

    while(!cin.good() || ret < min || ret > max){
        char ch;
        while((ch = getchar()) != '\n' ){
            continue;
        }
        cout << w_que;
        cin.clear();
        cin >> ret;
    }
    
    char ch;
    while((ch = getchar()) != '\n' ){
            continue;
    }
    return ret;    
}








//*****************************************************
// Main Menu
//************************************************************








void MainMenu::Run(){
    while(true){
        this->show();

        int choice = GetInt(-1, 2, "==> Please enter your choice: ", "==> Invalid coice. Please try again: ");

        if(choice == -1){
            break;
        }else if(choice == 1){
            manager_menu_.Run();
        }else if(choice == 2){
            student_menu_.Run();
        }else {
            break;
        }
    }
}





void MainMenu::show(){
    cout << "\n====================校园卡管理系统====================\n" << endl;
    cout << "\t-1. System Exit" << endl;
    cout << "\t 1. Enter Manager Menu" << endl;
    cout << "\t 2. Enter Student Menu" << endl;
    cout << "\n=======================================================\n" << endl;
}







//*****************************
//manager_menu
//******************************










//public members
ManagerMenu::ManagerMenu(){
    system_function_list_.push_back(new AddStudent);
    system_function_list_.push_back(new DeleteStudent);
    system_function_list_.push_back(new BindNewCard);
    system_function_list_.push_back(new ShowStudent);
    system_function_list_.push_back(new ShowCampusCard);
    system_function_list_.push_back(new Inpour);
}




void ManagerMenu::Run(){
    if(!this->Verification()){
        return;
    }
    this->Show();    
    while(true){
        int choice = GetInt(-1, system_function_list_.size(),
             "==> Please enter your choice(0 to show): ", "==> Invalid choice. Please try again(0 to show): ");
        
        if(choice == -1){
            break;
        }else if(choice == 0){
            this->Show();
        }else if (choice <= system_function_list_.size()){
            system_function_list_[choice-1]->DoTask();
        }
    }
}



bool ManagerMenu::Verification(){
    cout << "\n---------------Login---------------(-1 to quit)\n" << endl;
    int id = GetInt(-1, INT16_MAX, "==> Manager ID: ", "==> Invalid ID. Please try again: ");
    if(id == -1) {return false; }

    int passwd = GetInt(-1, INT16_MAX, "==> passwd: ", "==> Invalid passwd. Please try again: ");
    if(passwd == -1) {return false; }

    cout << "\n-----------------------------------\n" << endl;
    
    if(id == 0 && passwd == 628){
        is_administer_ = true;
        return true;
    }else{
        cout << "Wrong ID or wrong passwd.\n" << endl;
        return false;
    }

}



void ManagerMenu::Show(){
    cout << "\n================MANAGER MENU=================\n" << endl;
    int i = -1;
    cout << "\t" << i++ << "-" << "Exit" << endl;
    cout << "\t " << i++ << "-" << "Show" << endl;
    for(auto system_function : system_function_list_){
        cout << "\t " << i++ << "-" << system_function->GetFunctionName()<< endl;
    }
    cout << "\n==============================================\n" << endl;
}






//***************************
//student menu
//***************************






StudentMenu::StudentMenu(){
    system_function_list_.push_back(new ActivateCampusCard);
    system_function_list_.push_back(new Consume);
    system_function_list_.push_back(new ReportLoss);
    system_function_list_.push_back(new ShowCampusCard);
    system_function_list_.push_back(new ShowConsumeRecords);
    system_function_list_.push_back(new ShowInpourRecords);
    system_function_list_.push_back(new ShowStudentInfo);
}
//
void StudentMenu::Run(){
    if(!this->Verification()){
        return;
    }
    
    this->Show();

    while(true){
        //get choice
        int choice = GetInt(-1, system_function_list_.size(),
             "==> Please enter your choice(0 to show): ", "==> Invalid choice. Please try again:(0 to show) ");

        //do tasks
        if(choice == -1){
            break;
        }else if(choice == 0){
            this->Show();
        }else if(choice <= system_function_list_.size()){
            system_function_list_[choice-1]->DoTask(campus_card_id_);
        }
    }

}





bool StudentMenu::Verification(){
    //get Student's id and passwd
    cout << "\n\n---------------Login---------------(-1 to quit)\n";
    int student_id = GetInt(-1, INT16_MAX, "==> Student ID: ", "==> Invalid Student ID. Please try again: ");
    if(student_id == -1) {return false; }

    int passwd = GetInt(-1, INT16_MAX, "==> Campus Card passwd: ", "==> Invalid passwd, Please try again: ");
    if(passwd == -1) {return false; }

    cout << "-----------------------------------\n\n";

    //check student
    Student* student_ptr = system_manage.SearchStudent(student_id);
    if(student_ptr == nullptr){
        cout << "\nstudent doesn't exist.\n" << endl;
        return false;
    }

    //get bounded campus card
    int campus_card_id = student_ptr->GetCampusCardId();
    CampusCard* campus_card_ptr = system_manage.SearchCampusCard(campus_card_id);

    //verify
    if(campus_card_ptr->GetPasswd() == passwd){
        campus_card_id_ = campus_card_id;
        return true;
    }else{ 
        cout << "Campus card under your name and its passwd does't match.\n" << endl;
        return false;
    }
}






void StudentMenu::Show(){
    cout << "\n================= STUDENT MENU =================\n" << endl;
    int i = -1;
    cout << "\t" << i++ << "-" << "Exit" << endl;
    cout << "\t " << i++ << "-" << "Show" << endl;
    for(auto system_function : system_function_list_){
        cout << "\t " << i++ << "-" << system_function->GetFunctionName()<< endl;
    }
    cout << "\n=================================================\n" << endl;
}


