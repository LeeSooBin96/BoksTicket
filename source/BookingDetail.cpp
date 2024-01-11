#include <iostream>
#include <unistd.h>

#include "LoginPage.h"

#include "BookingDetail.h"

void BookingDetail::ShowBookingL(LoginPage& login)
{
    system("clear");
    unsigned short count;
    unsigned short input;
    std::cout<<"\x1b[1;106m-------------|B||o||o||k||i||n||g||D||T|-------------\x1b[m\n"
                "    < 예매 내역 > \n";
    count = login.ShowTicket();
    std::cout<<"----------------------------------------------------- \n";
    std::cout<<"목록 번호를 입력하시면 상세 내역을 볼 수 있습니다.\n"
               "(메인으로 돌아가기는 0)";
    std::cin>>input;
    while(!std::cin||input>count)
    {
        std::cin.clear();
        std::cout<<"잘못된 입력입니다. 다시 입력하세요 >";
        std::cin>>input;
    }
    if(input==0)
    {
        std::cout<<"메인으로 돌아갑니다. \n";
        return;
    }
    else
    {
        //상세 내역 보여주기
        std::cout<<"상세 정보>> \n";
        login.ShowTDetail(input);
        std::cout<<"엔터키를 누르면 이전으로 돌아갑니다. \n";
        std::cin.get();
        std::cin.get();
        ShowBookingL(login);
    }
}
