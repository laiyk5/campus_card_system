#include "system_functions.hh"

#include <iostream>
#include <string>
#include <climits>
#include "data_types.hh"

using std::cout;
using std::endl;   
using std::cin;
using std::string;

template<typename Callable>
void MysqlxSimpleErrorHandling(Callable f) {
    try {
        f();
    } catch (mysqlx::Error e) {
        std::cout << e.what() << std::endl;
    }
}

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
//Administrator's Operations
//****************************************************************************************



void AdminAddStudent::DoTask(mysqlx::Session &session) {
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
    //create a new student;
    cout << "Please enter information as followed: \n";
    int quit;
    std::string name, sex, school, major;
    cout << "-----------------------------------\n";
    cout << "quit?\tname\tsex\tschool\tmajor\n";
    cout << "-----------------------------------" << endl;
    cin >> quit;
    if(quit == -1) {return; }     //-1 to quit

    cin >> name >> sex >> school >> major;

    MysqlxSimpleErrorHandling(
        [&session, name, sex, school, major](){
            auto schema = session.getSchema("campus");
            mysqlx::Result res;
            res = schema.getTable("student").insert(
                    "name", "sex", "school", "major"
                ).values(
                    name, sex, school, major  
                    ).execute();
            auto student_id = res.getAutoIncrementValue();
            res = schema.getTable("card").insert("student_id").values(student_id).execute();
            auto card_id = res.getAutoIncrementValue();
            cout << "New Student: " << student_id << endl;
            cout << "New Campus card id: " << card_id << endl;
        }
    );
}




void AdminDeleteStudent::DoTask(mysqlx::Session &session) {
    //get Student;
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
    int student_id = GetInt(-1, INT16_MAX, "==> student ID: ", "==> Invalid ID. Please try again: ");

    if(student_id == -1) {return; }      //-1 to quit;

    try {
        session.getSchema("campus")
               .getTable("student")
               .remove()
               .where("id=:sid")
               .bind("sid",student_id)
               .execute();
        std::cout << "OK, student " << student_id << " deleted" << std::endl;
    } catch (mysqlx::Error e) {
        std::cout << e.what() << std::endl;
    }
}


void AdminBindNewCard::DoTask(mysqlx::Session &session){
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
    //get student;
    int student_id = GetInt(-1, INT16_MAX, "==> student ID: ", "==> Invalid ID. Please try again: ");
    if(student_id == -1) {return; }           //-1 to quit

    MysqlxSimpleErrorHandling(
        [&session, student_id](){
            auto schema = session.getSchema("campus");
            auto table = schema.getTable("card");
            table.remove().where("student_id = :s_id").bind("s_id", student_id).execute();
            auto res = table.insert("student_id").values(student_id).execute();

            cout << "Bind New Card " << res.getAutoIncrementValue() << " to Student " << student_id << " now" << endl;
        }
    );

}

static inline void ShowCampusCardHelper(mysqlx::Session &session, int card_id) {
    MysqlxSimpleErrorHandling(
        [&session, card_id](){
            auto card = session.getSchema("campus").getTable("card");
            auto res = card.select("id", "student_id", "balance").where("id = :c_id").bind("c_id", card_id).execute();
            auto row = res.fetchOne();
            if (row) {
                CampusCard(row[0], row[1], row[2]).Show();

            } else {
                std::cerr << "Card " << card_id << " Not Found." << std::endl;
            }
        }
    );
}

void AdminShowCampusCard::DoTask(mysqlx::Session &session){
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
  //get target campus card
    int card_id = GetInt(-1, INT16_MAX, "==> campus card id: ", "==> Invalid ID, please try again.");
    if(-1 == card_id ) {return; }
    
    ShowCampusCardHelper(session, card_id);
}

static inline void ShowStudentHelper(mysqlx::Session &session, int student_id) {
    MysqlxSimpleErrorHandling(
        [&session, student_id](){
            auto table = session.getSchema("campus").getTable("student");
            auto res = table.select("id", "name", "sex", "school", "major").where("id = :s_id").bind("s_id", student_id).execute();
            auto row = res.fetchOne();
            if (row) {
                int student_id(row[0]);
                std::string name(row[1]), sex(row[2]), school(row[3]), major(row[4]);
                row = session.getSchema("campus").getTable("card").select("id").where("student_id = :s_id").bind("s_id", student_id).execute().fetchOne();
                if (row) {
                    int card_id(row[0]);
                    Student(student_id, name, sex, school, major, card_id).Show();
                } else {
                    std::cerr << "Card with student_id " << student_id << " Not Found." << std::endl;
                    return;
                }
            } else {
                std::cerr << "Student " << student_id << " Not Found." << std::endl;
                return;
            }
        }
    );
}

void AdminShowStudent::DoTask(mysqlx::Session &session){
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
    int student_id = GetInt(-1, INT16_MAX, "==> student ID: ", "==> Invalid ID. Please try again: ");
    if(student_id == -1) {return; }
    
    ShowStudentHelper(session, student_id);
}



void AdminInpour::DoTask(mysqlx::Session &session) {
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
    //get target campus card
    int campus_card_id = -1;
    std::cout << "==> campus card ID: " << std::flush;
    std::cin >> campus_card_id;
    if (campus_card_id == -1) {
        return;
    }
    
    int old_balance = -1;
    MysqlxSimpleErrorHandling(
        [& session, campus_card_id, &old_balance](){
            auto table = session.getSchema("campus").getTable("card");
            auto res = table.select("balance").where("id = :c_id").bind("c_id", campus_card_id).execute();
            auto row = res.fetchOne();
            if (!row.isNull()) {
                old_balance = row[0];
            } else {
                std::cerr << "Card " << campus_card_id << " Not found." << std::endl;
            }
        }
    );
    if (old_balance == -1) {
        return;
    }
    
    if (old_balance == -1) {
        return;
    }
    
    MysqlxSimpleErrorHandling(
        [& session, old_balance](){
            auto table = session.getSchema("campus").getTable("card");
            int amount = GetInt(-1000, 500, "==> Amount: ","==> No more than $500 and no less than $0. Please try again: ");
            if(amount == -1) {return; }
            auto res = table.update().set("balance", old_balance + amount).execute();
            std::cout << "Success. Balance updated from " << old_balance << " to " << old_balance + amount << std::endl;
        }
    );
}




// //***************************************************************************************
// //Student Operations
// //****************************************************************************************


void UserConsume::DoTask(mysqlx::Session &session, int card_id){
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;	
    
    MysqlxSimpleErrorHandling(
        [&session, card_id](){
            auto table = session.getSchema("campus")
                                .getTable("card");
            auto row = table.select("balance")
                            .where("id = :cid")
                            .bind("cid", card_id)
                            .execute()
                            .fetchOne();
            if (!row) {
                std::cerr << "The card id " << card_id << " is invalid." << std::endl;
                return;
            }
            int old_balance = row[0];
            int amount = GetInt(-1, 500, "==> Amount: ","==> No more than $500 and no less than $0. Please try again: ");
            if (amount == -1) {
                return;
            }
            int new_balance = old_balance - amount;
            if (new_balance < 0) {
                std::cerr << "Not Enough Balance in the Account" << std::endl;
                return;
            }
            table.update()
                 .set("balance", new_balance)
                 .where("id = :cid")
                 .bind("cid", card_id)
                 .execute();
        }
    );
}


void UserShowCampusCard::DoTask(mysqlx::Session &session, int card_id){
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
    ShowCampusCardHelper(session, card_id);
}


void UserShowStudent::DoTask(mysqlx::Session &session, int card_id){
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
    MysqlxSimpleErrorHandling(
        [&session, card_id](){
            auto row = session.getSchema("campus")
                              .getTable("card")
                              .select("student_id")
                              .where("id=:cid")
                              .bind("cid", card_id)
                              .execute()
                              .fetchOne();
            if (!row) {
                std::cout << "Card ID " << card_id << " invalid." << std::endl;
                return;
            }
            ShowStudentHelper(session, row[0]);
        }
    );
}


void UserUpdatePasswd::DoTask(mysqlx::Session &session, int card_id){
    std::cout << std::string(20, '-') << this->GetFunctionName() << std::string(20, '-') << std::endl;
    MysqlxSimpleErrorHandling(
        [&session, card_id](){
            std::string newpasswd;
            auto row = session.getSchema("campus")
                              .getTable("card")
                              .select("student_id")
                              .where("id=:cid")
                              .bind("cid", card_id)
                              .execute()
                              .fetchOne();
            if (!row) {
                std::cout << "Card ID " << card_id << " invalid." << std::endl;
                return;
            }

            int student_id = row[0];
            
            std::cout << "==> New Passwd: " << std::endl;
            std::cin >> newpasswd;

            session.getSchema("campus")
                   .getTable("student")
                   .update()
                   .set("passwd", newpasswd)
                   .where("id=:sid")
                   .bind("sid", student_id)
                   .execute();

            std::cout << "OK, passwd updated." << std::endl;
        }
    );
}