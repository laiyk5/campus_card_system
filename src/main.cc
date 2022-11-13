#include "menu.hh"
#include <mysql-cppconn-8/mysqlx/xdevapi.h>
#include <iostream>
#include <string>

int main()
{
    try {
        mysqlx::Session session("localhost", 33060, "root", "sql_laiyk");
        
        int sid;
        std::cout << "Student ID: " << std::flush;
        std::cin >> sid;

        if (sid == -1) {
            return 0;
        }
            
        auto row = session.getSchema("campus")
                          .getTable("student")
                          .select("passwd", "name")
                          .where("id = :sid")
                          .bind("sid", sid)
                          .execute()
                          .fetchOne();
        if (row) {
            std::string passwd;
            std::cout << "Passwd: " << std::flush;
            std::cin >> passwd;
            if (passwd != std::string(row[0])) {
                std::cerr << "Passwd Does Not Match." << std::endl;
                return -1;
            } else {
                std::cout << "Welcome, " << row[1] << std::endl;
            }
        } else {
            std::cerr << "Student With ID " << sid << " Does Not Exists." << std::endl;
            return -1;
        }


        if (sid == 1) { // Super Manager.
            ManagerMenu(std::move(session)).Run();   
        } else {
            auto row = session.getSchema("campus")
                              .getTable("card")
                              .select("id")
                              .where("student_id = :sid")
                              .bind("sid", sid)
                              .execute()
                              .fetchOne();
            if (!row) {
                std::cerr << "The student has no card." << std::endl;
                return -1;
            }
            StudentMenu(std::move(session), row[0]).Run();
        }
    } catch (mysqlx::Error e) {
        std::cout << e.what() << std::endl;
        return -1;
    }


    return 0;
}
