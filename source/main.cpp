//main.cpp -- 메인 소스 파일
#include <iostream>
#include <unistd.h>

#include "MainPage.h" //메인 페이지
#include "SportPage.h" //스포츠 정보 게시판
#include "JoinPage.h" //회원가입 페이지

using namespace std;

int main(void)
{
    srand(time(NULL));
    bool quit = false; //종료 트리거
    bool login = false; //로그인 상태
    
    //로그인 페이지
    string userID; //아이디 저장
    string userPW; //비밀번호 저장
    unsigned short menu; //선택된 메뉴 번호 저장

    MainPage main;
    while(!quit)
    {
        unsigned int menuNum = main.Home(login);
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
                    break;
                }
                cout<<"경기 예매를 진행합니다. \n";
                break;
            }
            case 3:
            {
                if(!login) //로그인이 안되어있을 때만 반응
                {
                    cout<<"로그인을 진행합니다. \n";
                    sleep(1);
                    system("clear");
                    cout<<"1. 아이디 / 비밀번호 입력하기 \n"
                        "2. 아이디 찾기 \n"
                        "3. 비밀번호 찾기 \n"
                        "4. 회원가입 \n"
                        "--------------------------------------------------------\n";
                    cout<<"선택 > ";
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
                    while(menu>4)
                    {
                        cout<<"잘못된 입력입니다. 다시 입력하세요. \n";
                        cin>>menu;
                    }
                    sleep(1);
                    system("clear");
                    switch(menu)
                    {
                        case 1: //로그인 진행
                            cout<<" 아이디 > ";
                            cin>>userID;
                            cout<<" 비밀번호 > ";
                            cin>>userPW;
                            //아이디, 비밀번호 일치 검사
                            
                            login = true;
                            break;
                        case 2: //아이디 찾기
                            cout<<"이메일 혹은 휴대폰 번호를 입력해주십시오 >\n";
                            break;
                        case 3: //비밀번호 찾기
                            cout<<"아이디 > ";
                            cout<<"이메일 혹은 휴대폰 번호 > ";
                            break;
                        case 4:
                            cout<<"회원 가입을 진행합니다. \n";
                            JoinPage join;
                            join.ProgressJoin();
                            break;
                    }
                }
                else //로그아웃
                {
                    cout<<"로그아웃 중입니다. \n";
                    userID.clear();
                    userPW.clear();
                    login = false;
                    sleep(1);
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