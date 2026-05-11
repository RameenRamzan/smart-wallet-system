#ifndef REPORT_H
#define REPORT_H

#include <string>
#include "User.h"
using namespace std;

class Report {
public:
    static void generateUserReport(User* users, int userCount);
    static void generateTransactionReport(User* users, int userCount, 
                                         string startDate = "", string endDate = "");
    static void generateFinancialSummary(User* users, int userCount);
    static void generateUserActivityReport(User* users, int userCount);
    
    static int getActiveUserCount(User* users, int userCount);
    static double getTotalSystemBalance(User* users, int userCount);
};

#endif