#ifndef CAMPUS_CARD_SYSTEM_H
#define CAMPUS_CARD_SYSTEM_H

#include "menu.hh"
//The system has a menu call main_menu.
class CampusCardSystem
{
    public:
        void Run(){
            main_menu.Run();
        }
    private:
        MainMenu main_menu;
};

#endif
