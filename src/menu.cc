#include "menu.hh"

#include <iostream>
#include <string>
#include <climits>

#include <mysql-cppconn-8/mysqlx/xdevapi.h>


//modifiable IO function. It make the program more readable and IO more tidy. 
int GetInt(int min, int max, std::string que, std::string w_que){
    int ret;
    std::cout << que;
    std::cin >> ret;
    

    while(!std::cin.good() || ret < min || ret > max){
        char ch;
        while((ch = getchar()) != '\n' ){
            continue;
        }
        std::cout << w_que;
        std::cin.clear();
        std::cin >> ret;
    }
    
    char ch;
    while((ch = getchar()) != '\n' ){
            continue;
    }
    return ret;    
}

//*****************************
//manager_menu
//******************************



//public members
ManagerMenu::ManagerMenu(mysqlx::Session &&session)
    : Menu(std::move(session))
{
    system_function_list_.push_back(std::unique_ptr<AdminFunction>(new AdminAddStudent()));
    system_function_list_.push_back(std::unique_ptr<AdminFunction>(new AdminDeleteStudent()));
    system_function_list_.push_back(std::unique_ptr<AdminFunction>(new AdminShowStudent()));
    system_function_list_.push_back(std::unique_ptr<AdminFunction>(new AdminBindNewCard()));
    system_function_list_.push_back(std::unique_ptr<AdminFunction>(new AdminShowCampusCard()));
    system_function_list_.push_back(std::unique_ptr<AdminFunction>(new AdminInpour()));
}




void ManagerMenu::Run(){
    this->Show();    
    while(true){
        int choice = GetInt(-1, system_function_list_.size(),
             "==> Please enter your choice(0 to show): ", "==> Invalid choice. Please try again(0 to show): ");
        
        if(choice == -1){
            break;
        }else if(choice == 0){
            this->Show();
        }else if (choice <= system_function_list_.size()){
            system_function_list_[choice-1]->DoTask(this->session);
        }
    }
}



void ManagerMenu::Show(){
    std::cout << "\n================MANAGER MENU=================\n" << std::endl;
    int i = -1;
    std::cout << "\t" << i++ << "-" << "Exit" << std::endl;
    std::cout << "\t " << i++ << "-" << "Show" << std::endl;
    for(auto && system_function : system_function_list_){
        std::cout << "\t " << i++ << "-" << system_function->GetFunctionName()<< std::endl;
    }
    std::cout << "\n==============================================\n" << std::endl;
}






//***************************
//student menu
//***************************






StudentMenu::StudentMenu(mysqlx::Session &&session, int card_id)
    : Menu(std::move(session))
      , card_id_(card_id)
{
    system_function_list_.push_back(std::unique_ptr<UserFunction>(new UserConsume()));
    system_function_list_.push_back(std::unique_ptr<UserFunction>(new UserUpdatePasswd()));
    system_function_list_.push_back(std::unique_ptr<UserFunction>(new UserShowCampusCard()));
    system_function_list_.push_back(std::unique_ptr<UserFunction>(new UserShowStudent()));
}
//
void StudentMenu::Run(){
    
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
            this->system_function_list_[choice-1]->DoTask(this->session, this->card_id_);
        }
    }

}


void StudentMenu::Show(){
    std::cout << "\n================= STUDENT MENU =================\n" << std::endl;
    int i = -1;
    std::cout << "\t" << i++ << "-" << "Exit" << std::endl;
    std::cout << "\t " << i++ << "-" << "Show" << std::endl;
    for(auto && system_function : system_function_list_){
        std::cout << "\t " << i++ << "-" << system_function->GetFunctionName()<< std::endl;
    }
    std::cout << "\n=================================================\n" << std::endl;
}


