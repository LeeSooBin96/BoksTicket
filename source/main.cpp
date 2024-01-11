//main.cpp -- 메인 소스 파일
#include <iostream>
#include <unistd.h>

#include "MainPage.h" //메인 페이지
#include "SportPage.h" //스포츠 정보 게시판
#include "JoinPage.h" //회원가입 페이지
#include "LoginPage.h" //로그인 페이지
#include "ReservePage.h" //예매 페이지 --결제 페이지 포함
#include "BookingDetail.h" //예매 내역 페이지

using namespace std;

int main(void)
{
    srand(time(NULL));
    bool quit = false; //종료 트리거
    bool login = false; //로그인 상태
    bool pay; //결제 트리거
    unsigned short menuNum;
    char answer;

    MainPage main;
    LoginPage loginP;
    ReservePage reserve;
    reserve.SetSeat();
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
                else
                {
                    cout<<"경기 예매를 진행합니다. \n";
                    pay=reserve.ProgressRS(loginP);
                    if(pay)
                    {
                        cout<<"결제가 완료되었습니다. \n"; //결제 완료
                        cout<<"예매 내역을 보시겠습니까? (Y/N)";
                        cin>>answer;
                        while(cin.get()!='\n');
                        while(answer!='y'&&answer!='Y'&&answer!='n'&&answer!='N')
                        {
                            cout<<"다시 입력해주세요 > ";
                            answer = cin.get();
                            while(cin.get()!='\n');
                        } 
                        if(answer=='y'||answer=='Y')
                        {
                            BookingDetail booking;
                            booking.ShowBookingL(loginP);
                            cin.get();
                        }
                        else
                        {
                            cout<<"메인으로 돌아갑니다. \n";
                        }
                    }
                }
                break;
            }
            case 3:
            {
                if(!login) //로그인이 안되어있을 때만 반응
                {
                    cout<<"로그인을 진행합니다. \n";
                    loginP.ProgressLogin(login);
                }
                else
                {
                    BookingDetail booking;
                    booking.ShowBookingL(loginP);
                    cin.get();
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
                    cin.get();
                }
                else //로그인 시 로그아웃 
                {
                    cout<<"로그아웃 중입니다. \n";
                    loginP.ClearUserInfo();
                    login = false;
                }
                break;
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