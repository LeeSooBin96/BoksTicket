#include <iostream>

#include "LoginPage.h"

#ifndef PAY_PAGE_H_
#define PAY_PAGE_H_

class PayPage
{
    private:
        std::string Tlist;
    public:
        bool ProgressPay(LoginPage & login);
};
#endif