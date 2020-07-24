#ifndef SYSTEM_FUNCTION_H
#define SYSTEM_FUNCTION_H
#include "system_manage.h"
#include <string>
// This is a class to execute the functions in the student menu and managerMenu.

//base class
class SystemFunction{
    public:
        SystemFunction(std::string function_name): function_name_(function_name){ }
        virtual void DoTask(){};
        virtual void DoTask(int campus_card_id){};
        std::string GetFunctionName(){
            return function_name_;   
        }
    private:
        
        std::string function_name_;
};




//***************************************************************************************
//manager_functions
//***************************************************************************************




class AddStudent: public SystemFunction{
    public:
        AddStudent()
            :SystemFunction("Add Student"){ }
        void DoTask() override;
};

class DeleteStudent: public SystemFunction{
    public:
        DeleteStudent()
            :SystemFunction("Delete Student"){ }
        void DoTask() override;
};

class BindNewCard: public SystemFunction{
    public:
        BindNewCard()
            :SystemFunction("Recreate a card for a student"){
            //
        }
        void DoTask() override;
};

class ShowStudent: public SystemFunction{
    public:
        ShowStudent()
            :SystemFunction("Show student"){
            //
        }
        void DoTask() override;
};





//***************************************************************************************
//student_functions
//***************************************************************************************






class ActivateCampusCard: public SystemFunction{
    public:
        ActivateCampusCard()
            :SystemFunction("Activate Campus Card"){ }
        void DoTask(int campus_card_id) override;
};


class Consume: public SystemFunction{
    public:
        Consume()
            :SystemFunction("Consume"){
            //
        }
        void DoTask(int campus_card_id) override;
};

class Inpour: public SystemFunction{
    public:
        Inpour()
            :SystemFunction("Inpour"){ }
        void DoTask() override;
};



class ReportLoss: public SystemFunction{
    public:
        ReportLoss()
            :SystemFunction("Report campus card loss"){ }
        void DoTask(int campus_card_id) override;
};



//student and manager common functions
class ShowCampusCard: public SystemFunction{
    public:
        ShowCampusCard()
            :SystemFunction("Show campus card info"){
            //
        }
        void DoTask(int campus_card_id_) override;
        void DoTask() override;
};




class ShowConsumeRecords: public SystemFunction{
    public:
        ShowConsumeRecords()
            :SystemFunction("Show consume records"){
            //
        }
        void DoTask(int campus_card_id_) override;
};

class ShowInpourRecords: public SystemFunction{
    public:
        ShowInpourRecords()
            :SystemFunction("Show inpour records"){
            //
        }
        void DoTask(int campus_card_id_) override;
};



class ShowStudentInfo: public SystemFunction{
    public:
        ShowStudentInfo()
            :SystemFunction("Show student info"){
            //
        }
        void DoTask(int campus_card_id_) override;
};


#endif 
