#ifndef MENU_H
#define MENU_H

#include <vector>
#include "system_functions.hh"

//Menu is a class that show choices, get choices, and exicute choices.

class Menu{
    public:
        virtual void Run() = 0;	//Menus' core function: show choices, get choices, and exicute them.
};

class ManagerMenu:Menu{
    public:
        ManagerMenu();		//The default Constructor is used to construct and initialize the system_functions. 

        void Run();

    private:
        bool Verification();		
        void Show();				//show choices
        std::vector<SystemFunction*> system_function_list_;	//the functionlist is used to store the functions defined as classes in system_functions.hh
        bool is_administer_ = false;
};


class StudentMenu:Menu{
    public:
        StudentMenu();
        void Run();
    private:
        void Show();
        bool Verification();
        std::vector<SystemFunction*> system_function_list_;
        int campus_card_id_;
};


//MainMenu
class MainMenu:Menu{
    public:
        void Run(); // UI: choose which submenu to enter. 
    private:
        void show();
        StudentMenu student_menu_;
        ManagerMenu manager_menu_;
};
#endif
