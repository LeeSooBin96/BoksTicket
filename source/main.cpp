//main.cpp -- 메인 소스 파일
#include <iostream>
#include <unistd.h>

#include "MainPage.h" //메인 페이지
#include "SportPage.h" //스포츠 정보 게시판
#include "JoinPage.h" //회원가입 페이지
#include "LoginPage.h" //로그인 페이지
#include "ReservePage.h" //예매 페이지

using namespace std;

int main(void)
{
    srand(time(NULL));
    bool quit = false; //종료 트리거
    bool login = false; //로그인 상태
    unsigned short menuNum;

    MainPage main;
    LoginPage loginP;
    ReservePage reserve;
    while(!quit)
    {
        menuNum = main.Home(login);
        switch(menuNum)
        {
            case 1:
            {
                cout<<"스포츠 정보 게시판으로 넘어갑니다. \n";
                SportPage sport;
                sport.HomeBoard();
                break;
            }
            case 2:
            {
                if(!login) //로그인 확인
                {
                    cout<<"로그인이 되어있지 않습니다. 로그인을 진행합니다. \n";
                    loginP.ProgressLogin(login);
                    break;
                }
                cout<<"경기 예매를 진행합니다. \n";
                reserve.ProgressRS();
                break;
            }
            case 3:
            {
                if(!login) //로그인이 안되어있을 때만 반응
                {
                    cout<<"로그인을 진행합니다. \n";
                    loginP.ProgressLogin(login);
                }
                else //로그아웃
                {
                    cout<<"로그아웃 중입니다. \n";
                    loginP.ClearUserInfo();
                    login = false;
                }
                break;
            }
            case 4:
            {
                if(!login) //비로그인 시에만
                { 
                    cout<<"회원 가입을 진행합니다. \n";
                    JoinPage join;
                    join.ProgressJoin();
                    break;
                }
                //로그인 시 4번이 종료. 아래 레이블로 넘어가서 실행된다.
            }
            case 5:
            {
                cout<<"종료됩니다. \n";
                quit=true;
                break;
            }
        }
        sleep(1);
        system("clear");
    }
    return 0;
}