//MainPage.cpp -- 메인 페이지 소스파일
#include <iostream>
#include <fstream>

#include "MainPage.h"
using std::cout;
using std::cin;

//메뉴 출력
void MainPage::ShowMenu(bool login)
{
    if(!login) //로그인이 안되어 있을때
    {
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "1. 아시안컵 상세 정보 \n"
                "2. 경기 예매 \n"
                "3. 로그인 \n"
                "4. 회원 가입 \n"
                "5. 종료 \n"
                "---------------------- \n";
    }
    else //로그인 상태일때
    {
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
            "1. 아시안컵 상세 정보 \n"
            "2. 경기 예매 \n"
            "3. 예매 내역 \n"
            "4. 로그아웃 \n"
            "5. 종료 \n"
            "---------------------- \n";
    }
}
//메인 페이지 진행(로그인 상태값 전달 받음)
unsigned short MainPage::Home(bool login)
{
    MainPage::ShowMenu(login);
    //메뉴 번호 입력
    cout<<"선택 >";
    cin>>menu;
    //잘못된 입력(숫자 이외)
    while(!cin)
    {
        cin.clear(); //에러 플래그 초기화
        cout<<"잘못된 입력입니다. 다시 입력하세요. \n";
        while(cin.get()!='\n'); //버퍼 비우기
        cin>>menu;
    }
    //잘못된 입력(숫자)
    while(menu>5)
    {
        cout<<"잘못된 입력입니다. 다시 입력하세요. \n";
        cin>>menu;
    }
    return menu;
}