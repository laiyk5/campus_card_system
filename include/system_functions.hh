#ifndef SYSTEM_FUNCTION_H
#define SYSTEM_FUNCTION_H
#include <string>
#include <mysql-cppconn-8/mysqlx/xdevapi.h>
// This is a class to execute the functions in the student menu and managerMenu.

//base class
class SystemFunction{
    public:
        SystemFunction(std::string function_name): function_name_(function_name){ }
        std::string GetFunctionName(){
            return function_name_;   
        }
    private:
        
        std::string function_name_;
};

class AdminFunction: public SystemFunction {
public:
    AdminFunction(std::string function_name): SystemFunction(function_name) {}
    virtual void DoTask(mysqlx::Session & session) {};
};

class UserFunction: public SystemFunction {
public:
    UserFunction(std::string function_name): SystemFunction(function_name) {}
    virtual void DoTask(mysqlx::Session & session, int student_id) {};
};


//***************************************************************************************
//manager_functions
//***************************************************************************************




class AdminAddStudent: public AdminFunction{
    public:
        AdminAddStudent()
            :AdminFunction("Add Student"){ }
        void DoTask(mysqlx::Session &session) override;
};

class AdminDeleteStudent: public AdminFunction{
    public:
        AdminDeleteStudent()
            :AdminFunction("Delete Student"){ }
        void DoTask(mysqlx::Session &session) override;
};

class AdminBindNewCard: public AdminFunction{
    public:
        AdminBindNewCard()
            :AdminFunction("Recreate a card for a student"){
            //
        }
        void DoTask(mysqlx::Session &session) override;
};

class AdminShowStudent: public AdminFunction{
    public:
        AdminShowStudent()
            :AdminFunction("Show student"){
            //
        }
        void DoTask(mysqlx::Session &session) override;
};

class AdminShowCampusCard: public AdminFunction{
    public:
        AdminShowCampusCard()
            :AdminFunction("Show campus card info"){
            //
        }
        void DoTask(mysqlx::Session &session) override;
};

class AdminInpour: public AdminFunction{
    public:
        AdminInpour()
            :AdminFunction("Inpour"){ }
        void DoTask(mysqlx::Session &session) override;
};


//***************************************************************************************
//student_functions
//***************************************************************************************

class UserConsume: public UserFunction{
    public:
        UserConsume()
            :UserFunction("Consume"){
            //
        }
        void DoTask(mysqlx::Session &session, int student_id) override;
};


class UserShowCampusCard: public UserFunction{
    public:
        UserShowCampusCard()
            :UserFunction("Show campus card info"){
            //
        }
        void DoTask(mysqlx::Session &session, int student_id) override;
};


class UserShowStudent: public UserFunction{
    public:
        UserShowStudent()
            :UserFunction("Show student info"){
            //
        }
        void DoTask(mysqlx::Session &session, int student_id) override;
};

class UserUpdatePasswd: public UserFunction{
    public:
        UserUpdatePasswd()
            :UserFunction("Update Passwd") {
            //
        }
        void DoTask(mysqlx::Session &session, int student_id) override;
};

#endif 
