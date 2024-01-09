#include <fstream>
#include <unistd.h>

#include "LoginPage.h"
#include "JoinPage.h"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

void LoginPage::ClearUserInfo(void)
{
    userID.clear();
    userPW.clear();
}
void LoginPage::ProgressLogin(bool & login)
{
    sleep(1);
    system("clear");
    cout<<"1. 아이디 / 비밀번호 입력하기 \n"
        "2. 아이디 찾기 \n"
        "3. 비밀번호 찾기 \n"
        "4. 회원가입 \n"
        "5. 메인으로 \n"
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
    while(menu>5)
    {
        cout<<"잘못된 입력입니다. 다시 입력하세요. \n";
        cin>>menu;
    }
    switch(menu)
    {
        case 1: //로그인 진행
        {
            sleep(1);
            system("clear");
            cout<<" 아이디 > ";
            cin>>userID;
            cout<<" 비밀번호 > ";
            cin>>userPW;
            //아이디, 비밀번호 일치 검사
            ifstream readFile;
            readFile.open("data.csv");
            if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
            {
                ofstream tempFile;
                tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                if(!tempFile.is_open())
                {
                    cout<<"존재하지 않는 아이디 또는 비밀번호입니다. \n";
                    ClearUserInfo();
                    tempFile.close();
                    return;
                }
                tempFile.close();
                readFile.clear();
            }
            string temp;
            while(!readFile.eof())
            {
                getline(readFile,temp,','); //회원번호 건너뛰기
                getline(readFile,temp,','); //아이디 가져오기
                if(!temp.compare(userID)) //아이디 일치
                {
                    getline(readFile,temp,','); //비밀번호 가져오기
                    if(!temp.compare(userPW)) //비밀번호 일치
                    {
                        login = true;//로그인 성공
                        cout<<"로그인에 성공했습니다. \n";
                        break;
                    }
                    else //비밀번호 불일치
                    {
                        cout<<"아이디 또는 비밀번호가 일치하지 않습니다. \n";
                        ClearUserInfo();
                        ProgressLogin(login);
                        break;
                    }
                }
                else
                {
                    for(int i=0;i<3;i++)
                    {
                        getline(readFile,temp,','); //비밀번호,이메일,휴대폰 건너뛰기
                    }
                }
            }
            if(readFile.eof())
            {
                cout<<"존재하지 않는 아이디 또는 비밀번호입니다. \n";
                ClearUserInfo();
                ProgressLogin(login);   
            }
            readFile.close();
            usleep(500000);
            break;
        }
        case 2: //아이디 찾기
        {
            sleep(1);
            system("clear");
            cout<<"이메일 혹은 휴대폰 번호를 입력해주십시오 > ";
            cin>>input;
            //입력받은 값으로 아이디 찾기 진행
            ifstream readFile;
            readFile.open("data.csv");
            if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
            {
                ofstream tempFile;
                tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                if(!tempFile.is_open())
                {
                    cout<<"존재하지 않은 계정 정보입니다. \n";
                    break;
                }
                tempFile.close();
                readFile.clear();
            }
            string temp;
            while(!readFile.eof())
            {
                getline(readFile,temp,','); //회원번호 건너뛰기
                getline(readFile,searchID,','); //아이디 가져오기 - 아이디 변수에 저장
                getline(readFile,temp,','); //비밀번호 건너뛰기
                getline(readFile,temp,','); //이메일 가져오기
                if(!temp.compare(input)) //이메일 일치 검사
                {
                    cout<<"검색된 아이디는 다음과 같습니다. \n";
                    cout<<" 아이디 : "<<searchID<<endl;
                    break;
                }
                else
                {
                    getline(readFile,temp,','); //휴대폰 번호 가져오기
                    if(!temp.compare(input)) //휴대폰 번호 일치 검사
                    {
                        cout<<"검색된 아이디는 다음과 같습니다. \n";
                        cout<<" 아이디 : "<<searchID<<endl;
                        break;
                    }
                }
            }
            if(readFile.eof())
            {
                cout<<"존재하지 않은 계정 정보입니다. \n";
            }
            readFile.close();
            cout<<"\n엔터키를 누르면 메인으로 돌아갑니다) \n";
            cin.get();
            cin.get();
            break;
        }
        case 3: //비밀번호 찾기
        {
            sleep(1);
            system("clear");
            cout<<"아이디 > ";
            cin>>searchID;
            cout<<"이메일 혹은 휴대폰 번호 > ";
            cin>>input;
            //입력받은 값으로 비밀번호 찾기 진행
            ifstream readFile;
            readFile.open("data.csv");
            if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
            {
                ofstream tempFile;
                tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                if(!tempFile.is_open())
                {
                    cout<<"존재하지 않은 계정 정보입니다. \n";
                    break;
                }
                tempFile.close();
                readFile.clear();
            }
            string temp;
            while(!readFile.eof())
            {
                getline(readFile,temp,','); //회원번호 건너뛰기
                getline(readFile,temp,','); //아이디 가져오기
                if(!temp.compare(searchID)) //아이디 일치
                {
                    getline(readFile,searchPW,','); //비밀번호 가져오기 - 비밀번호 저장 
                    getline(readFile,temp,','); //이메일 가져오기
                    if(!temp.compare(input)) //이메일 일치 검사
                    {
                        cout<<"검색된 비밀번호는 다음과 같습니다. \n";
                        cout<<" 비밀번호 : "<<searchPW<<endl;
                        break;
                    }
                    else
                    {
                        getline(readFile,temp,','); //휴대폰 번호 가져오기
                        if(!temp.compare(input)) //휴대폰 번호 일치 검사
                        {
                            cout<<"검색된 비밀번호는 다음과 같습니다. \n";
                            cout<<" 비밀번호 : "<<searchPW<<endl;
                            break;
                        }
                    }
                }
                else
                {
                    for(int i=0;i<3;i++)
                    {
                        getline(readFile,temp,','); //비밀번호,이메일,휴대폰 번호 건너뜀
                    }
                }
                
            }
            if(readFile.eof())
            {
                cout<<"존재하지 않은 계정 정보입니다. \n";
            }
            readFile.close();
            cout<<"\n엔터키를 누르면 메인으로 돌아갑니다) \n";
            cin.get();
            cin.get();
            break;
        }
        case 4:
        {
            cout<<"회원 가입을 진행합니다. \n";
            JoinPage join;
            join.ProgressJoin();
            break;
        }
        case 5: //메인으로
            break;
    }
}