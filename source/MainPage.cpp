//MainPage.cpp -- 메인 페이지 소스파일
#include <iostream>
#include <fstream>

#include "MainPage.h"
#include "GetCh.h"

using std::cout;
using std::cin;


void MainPage::UnLoginMenu(unsigned short pos)
{
    switch (pos)
    {
    case 0:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "1. 아시안컵 상세 정보 \n"
                "\x1b[30m2. 경기 예매 \n"
                "3. 로그인 \n"
                "4. 회원 가입 \n"
                "5. 종료 \x1b[m\n"
                "---------------------- \n";
        break;
    case 1:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "\x1b[30m1. 아시안컵 상세 정보 \x1b[m\n"
                "2. 경기 예매 \n"
                "\x1b[30m3. 로그인 \n"
                "4. 회원 가입 \n"
                "5. 종료 \x1b[m\n"
                "---------------------- \n";
        break;
    case 2:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "\x1b[30m1. 아시안컵 상세 정보 \n"
                "2. 경기 예매 \x1b[m\n"
                "3. 로그인 \n"
                "\x1b[30m4. 회원 가입 \n"
                "5. 종료 \x1b[m\n"
                "---------------------- \n";
        break;
    case 3:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "\x1b[30m1. 아시안컵 상세 정보 \n"
                "2. 경기 예매 \n"
                "3. 로그인 \x1b[m\n"
                "4. 회원 가입 \n"
                "\x1b[30m5. 종료 \x1b[m\n"
                "---------------------- \n";
        break;
    case 4:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "\x1b[30m1. 아시안컵 상세 정보 \n"
                "2. 경기 예매 \n"
                "3. 로그인 \n"
                "4. 회원 가입 \x1b[m\n"
                "5. 종료 \n"
                "---------------------- \n";
        break;
    default:
        break;
    }
}

void MainPage::LoginMenu(unsigned short pos)
{
    switch (pos)
    {
    case 0:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "1. 아시안컵 상세 정보 \n"
                "\x1b[30m2. 경기 예매 \n"
                "3. 예매내역 \n"
                "4. 로그아웃 \n"
                "5. 종료 \x1b[m\n"
                "---------------------- \n";
        break;
    case 1:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "\x1b[30m1. 아시안컵 상세 정보 \x1b[m\n"
                "2. 경기 예매 \n"
                "\x1b[30m3. 예매내역 \n"
                "4. 로그아웃 \n"
                "5. 종료 \x1b[m\n"
                "---------------------- \n";
        break;
    case 2:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "\x1b[30m1. 아시안컵 상세 정보 \n"
                "2. 경기 예매 \x1b[m\n"
                "3. 예매내역 \n"
                "\x1b[30m4. 로그아웃 \n"
                "5. 종료 \x1b[m\n"
                "---------------------- \n";
        break;
    case 3:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "\x1b[30m1. 아시안컵 상세 정보 \n"
                "2. 경기 예매 \n"
                "3. 예매내역 \x1b[m\n"
                "4. 로그아웃 \n"
                "\x1b[30m5. 종료 \x1b[m\n"
                "---------------------- \n";
        break;
    case 4:
        cout<<"\x1b[1;106m-----Bok's Ticket-----\x1b[m \n"
                "\x1b[30m1. 아시안컵 상세 정보 \n"
                "2. 경기 예매 \n"
                "3. 예매내역 \n"
                "4. 로그아웃 \x1b[m\n"
                "5. 종료 \n"
                "---------------------- \n";
        break;
    default:
        break;
    }
}

//메뉴 출력
void MainPage::ShowMenu(bool login,unsigned short pos)
{
    if(!login) //로그인이 안되어 있을때
    {
        UnLoginMenu(pos);
    }
    else //로그인 상태일때
    {
        LoginMenu(pos);
    }
}
//메인 페이지 진행(로그인 상태값 전달 받음)
unsigned short MainPage::Home(bool login)
{
    bool quit = false; //while문 탈출 코드
    int input; //입력 인자
    unsigned short pos=0;
    system("clear");
    ShowMenu(login,pos);
    //메뉴 번호 입력
    cout<<"(상:w,↑/하:s,↓) (선택: 엔터) \n";
    while(!quit)
    {
        input=getch(); //방향키 입력(상:27,91,65) 하(27,91,66) 엔터(10)
        switch (input)
        {
        case 65: //방향키 상
        case 'w':
            if(pos!=0) pos--;
            system("clear");
            ShowMenu(login,pos);
            cout<<"(상:w,↑/하:s,↓) (선택: 엔터) \n";
            break;
        case 66:
        case 's':
            if(pos!=4) pos++;
            system("clear");
            ShowMenu(login,pos);
            cout<<"(상:w,↑/하:s,↓) (선택: 엔터) \n";
            break;
        case 10:
            menu=pos+1;
            quit=true;
            break;
        default:
            break;
        }
    }
    return menu;
}