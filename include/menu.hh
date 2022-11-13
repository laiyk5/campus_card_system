#ifndef MENU_H
#define MENU_H

#include <vector>
#include "system_functions.hh"
#include <mysql-cppconn-8/mysqlx/xdevapi.h>

//Menu is a class that show choices, get choices, and exicute choices.

class Menu{
    public:
        Menu(mysqlx::Session &&session): session(std::move(session)) {
            ;
        }
        virtual void Run() = 0;	//Menus' core function: show choices, get choices, and exicute them.
    protected:
        mysqlx::Session session;
};

class ManagerMenu: public Menu{
    public:
        ManagerMenu(mysqlx::Session &&session);		//The default Constructor is used to construct and initialize the system_functions. 

        void Run();

    private:
        void Show();				//show choices
        std::vector<std::unique_ptr<AdminFunction>> system_function_list_;	//the functionlist is used to store the functions defined as classes in system_functions.hh
};


class StudentMenu: public Menu{
    public:
        StudentMenu(mysqlx::Session &&session, int card_id);		//The default Constructor is used to construct and initialize the system_functions. 
        void Run();
    private:
        void Show();
        int card_id_;
        std::vector<std::unique_ptr<UserFunction>> system_function_list_;	//the functionlist is used to store the functions defined as classes in system_functions.hh
};

#endif
