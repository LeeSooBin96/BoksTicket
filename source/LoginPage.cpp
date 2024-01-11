#include <fstream>
#include <unistd.h>

#include "LoginPage.h"
#include "JoinPage.h"
#include "GetCh.h"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;


//티켓 저장
void LoginPage::SaveTicket(string & Tlist)
{
    string line;
    int count=1;

    ofstream writeFile;
    writeFile.open("BookingL.csv",std::ios_base::in);
    ifstream readFile;
    readFile.open("BookingL.csv");
    
    while(true)
    {
        getline(readFile,line,','); //해당하는 아이디 찾기
        if(readFile.eof()&&count==1) //첫줄 부터 없으면 개행 없이
        {
            writeFile<<userID<<","<<Tlist; //아이디,티켓 정보 연달아 입력될것
            break;
        }
        else if(readFile.eof()) //아이디 없을때
        {
            writeFile.seekp(0,std::ios::end);
            writeFile<<"\n"<<userID<<","<<Tlist; //아이디,티켓 정보 연달아 입력될것
            break;
        }
        else if(line.compare(userID)==0) //일치하는 아이디 찾으면
        {
            getline(readFile,line); //줄 끝으로
            if(readFile.eof()) //맨 끝줄이면 추가
            {
                writeFile<<","<<Tlist;
            }
            else //아니면 새줄에 저장
            {
                writeFile.seekp(0,std::ios::end);
                writeFile<<"\n"<<userID<<","<<Tlist;
            }
            break;
        }
        else //다음줄로 넘어가기
        {
            count+=line.size();
            getline(readFile,line);
            count+=line.size();
        }
    }
    readFile.close();
    writeFile.close();
}
//보유 티켓 갯수 갱신
unsigned short* LoginPage::CountTicet(void)
{
    for(int i=0;i<3;i++) count[i]=0;
    std::string line;
    std::ifstream readFile;
    readFile.open("BookingL.csv");
    if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
    {
        std::ofstream tempFile;
        tempFile.open("BookingL.csv"); //없으면 데이터 파일 생성해주기
        tempFile.close();
        readFile.close(); 
        return count; //셀 것이 없으므로 종료
    }
    while (true)
    {
        getline(readFile,line,','); //아이디 가져오기
        if(readFile.eof()) //일치하는 아이디가 없으면
        {
            break;
        }
        else if(!line.compare(userID)) //아이디 일치(예매 내역 있음)
        {
            while(true)
            {
                getline(readFile,line,','); //경기 일정
                if(readFile.eof()) break;
                if(!line.compare("1/15"))
                {
                    count[0]++;
                }
                else if(!line.compare("1/20"))
                {
                    count[1]++;
                }
                else if(!line.compare("1/25"))
                {
                    count[2]++;
                }
                else if(!line.compare("\n"+userID)) //다음줄로 넘어감
                {
                    continue;
                }
                else break;
                for(int i=0;i<3;i++)
                {
                    getline(readFile,line,','); //좌석 구역,번호,가격 건너뜀
                }
            }
        }
        // else //아이디 불일치
        // {
        getline(readFile,line); //남은 줄 읽어들이기
        // }
    }
    readFile.close();
    return count;
}
//보유 티켓 출력
unsigned short LoginPage::ShowTicket(void)
{
    unsigned short listNum=0; //목록 번호
    CountTicet();
    if(count[0]==0&&count[1]==0&&count[2]==0)
    {
        cout<<"예매내역이 없습니다. \n";
        return listNum;
    }
    if(count[0]!=0)
    {
        listNum++;
        cout<<listNum<<"] "<<"1/15 "<<count[0]<<"매 \n";
    }
    if(count[1]!=0)
    {
        listNum++;
        cout<<listNum<<"] "<<"1/20 "<<count[1]<<"매 \n";
    }
    if(count[2]!=0)
    {
        listNum++;
        cout<<listNum<<"] "<<"1/25 "<<count[2]<<"매 \n";
    }
    return listNum;
}
//티켓 상세 정보 출력
void LoginPage::ShowTDetail(unsigned short listNum)
{
    string line;

    ifstream readFile;
    readFile.open("BookingL.csv");
    
    while(true)
    {
        getline(readFile,line,','); //해당하는 아이디 찾기
        if(readFile.eof()) //데이터 없음
        {
            break;
        }
        else if(!line.compare(userID)) //일치하는 아이디 찾으면
        {
            while(true)
            {
                getline(readFile,line,','); //경기 일자
                if(readFile.eof()) break;
                if(!line.compare("1/15")) 
                {
                    if(count[0]!=0&&listNum==1)
                    {
                        cout<<line<<" 20:30 대한민국 vs 바레인 (개최지:DOHA) \n";
                        getline(readFile,line,','); //좌석 구역
                        cout<<line<<"구역 ";
                        getline(readFile,line,','); //좌석 번호
                        cout<<line<<"번 좌석 가격: ";
                        getline(readFile,line,','); //가격
                        cout<<line<<"원 \n";
                        continue;
                    }
                }
                else if(!line.compare("1/20"))
                {
                    if(count[0]==0&&listNum==1)
                    {
                        cout<<line<<" 20:30 요르단 vs 대한민국 (개최지:DOHA) \n";
                        getline(readFile,line,','); //좌석 구역
                        cout<<line<<"구역 ";
                        getline(readFile,line,','); //좌석 번호
                        cout<<line<<"번 좌석 가격: ";
                        getline(readFile,line,','); //가격
                        cout<<line<<"원 \n";
                        continue;
                    }
                    else if(count[0]!=0&&listNum==2)
                    {
                        cout<<line<<" 20:30 요르단 vs 대한민국 (개최지:DOHA) \n";
                        getline(readFile,line,','); //좌석 구역
                        cout<<line<<"구역 ";
                        getline(readFile,line,','); //좌석 번호
                        cout<<line<<"번 좌석 가격: ";
                        getline(readFile,line,','); //가격
                        cout<<line<<"원 \n";
                        continue;
                    }
                }
                else if(!line.compare("1/25"))
                {
                    if(count[0]==0&&count[1]==0&&listNum==1)
                    {
                        cout<<line<<" 20:30 대한민국 vs 말레이시아 (개최지:AL WAKRAH) \n";
                        getline(readFile,line,','); //좌석 구역
                        cout<<line<<"구역 ";
                        getline(readFile,line,','); //좌석 번호
                        cout<<line<<"번 좌석 가격: ";
                        getline(readFile,line,','); //가격
                        cout<<line<<"원 \n";
                        continue;
                    }
                    else if(count[0]==0&&listNum==2)
                    {
                        cout<<line<<" 20:30 대한민국 vs 말레이시아 (개최지:AL WAKRAH) \n";
                        getline(readFile,line,','); //좌석 구역
                        cout<<line<<"구역 ";
                        getline(readFile,line,','); //좌석 번호
                        cout<<line<<"번 좌석 가격: ";
                        getline(readFile,line,','); //가격
                        cout<<line<<"원 \n";
                        continue;
                    }
                    else if(listNum==3)
                    {
                        cout<<line<<" 20:30 대한민국 vs 말레이시아 (개최지:AL WAKRAH) \n";
                        getline(readFile,line,','); //좌석 구역
                        cout<<line<<"구역 ";
                        getline(readFile,line,','); //좌석 번호
                        cout<<line<<"번 좌석 가격: ";
                        getline(readFile,line,','); //가격
                        cout<<line<<"원 \n";
                        continue;
                    }
                }
                else if(!line.compare("\n"+userID)) //다음줄로 넘어갔는데 같은 아이디
                {
                    continue;
                }
                else break; //다른아이디 나오면
                for(int i=0;i<3;i++)
                {
                    getline(readFile,line,','); //좌석 구역,번호,가격 건너뜀
                }
            }
            
        }
        // else //다음줄로 넘어가기
        // {
            getline(readFile,line);
        // }
    }
    readFile.close();
}
void LoginPage::ClearUserInfo(void)
{
    userID.clear();
    userPW.clear();
    for(int i=0;i<3;i++) count[i]=0;
}
void LoginPage::ShowMenu(unsigned short pos)
{
    switch (pos)
    {
    case 0:
        cout<<"1. 아이디 / 비밀번호 입력하기 \n"
            "\x1b[30m2. 아이디 찾기 \n"
            "3. 비밀번호 찾기 \n"
            "4. 회원가입 \n"
            "5. 메인으로 \x1b[m\n";
        break;
    case 1:
        cout<<"\x1b[30m1. 아이디 / 비밀번호 입력하기 \x1b[m\n"
            "2. 아이디 찾기 \n"
            "\x1b[30m3. 비밀번호 찾기 \n"
            "4. 회원가입 \n"
            "5. 메인으로 \x1b[m\n";
        break;
    case 2:
        cout<<"\x1b[30m1. 아이디 / 비밀번호 입력하기 \n"
            "2. 아이디 찾기 \x1b[m\n"
            "3. 비밀번호 찾기 \n"
            "\x1b[30m4. 회원가입 \n"
            "5. 메인으로 \x1b[m\n";
        break;
    case 3:
        cout<<"\x1b[30m1. 아이디 / 비밀번호 입력하기 \n"
            "2. 아이디 찾기 \n"
            "3. 비밀번호 찾기 \x1b[m\n"
            "4. 회원가입 \n"
            "\x1b[30m5. 메인으로 \x1b[m\n";
        break;
    case 4:
        cout<<"\x1b[30m1. 아이디 / 비밀번호 입력하기 \n"
            "2. 아이디 찾기 \n"
            "3. 비밀번호 찾기 \n"
            "4. 회원가입 \x1b[m\n"
            "5. 메인으로 \n";
        break;
    default:
        break;
    }
}
void LoginPage::ProgressLogin(bool & login)
{
    unsigned short pos=0;
    bool quit = false;
    int in_key;
    sleep(1);
    
    system("clear");
    cout<<"\x1b[1;106m-----------|L||o||g||i||n||P||a||g||e|-----------\x1b[m\n";
    ShowMenu(pos);
    cout<<"-------------------------------------------------\n";
    cout<<"(상:w,↑/하:s,↓) (선택: 엔터) \n";
    while(!quit)
    {
        in_key=getch(); //방향키 입력(상:27,91,65) 하(27,91,66) 엔터(10)
        switch (in_key)
        {
        case 65: //방향키 상
        case 'w':
            if(pos!=0) pos--;
            system("clear");
            cout<<"\x1b[1;106m-----------|L||o||g||i||n||P||a||g||e|-----------\x1b[m\n";
            ShowMenu(pos);
            cout<<"-------------------------------------------------\n";
            cout<<"(상:w,↑/하:s,↓) (선택: 엔터) \n";
            break;
        case 66:
        case 's':
            if(pos!=4) pos++;
            system("clear");
            cout<<"\x1b[1;106m-----------|L||o||g||i||n||P||a||g||e|-----------\x1b[m\n";
            ShowMenu(pos);
            cout<<"-------------------------------------------------\n";
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
    switch(menu)
    {
        case 1: //로그인 진행
        {
            int input;
            system("clear");
            cout<<"\x1b[1;106m-----------|L||o||g||i||n||P||a||g||e|-----------\x1b[m\n";
            cout<<" 아이디 > ";
            cin>>userID;
            cin.get();
            cout<<" 비밀번호 > ";
            // cin>>userPW;
            unsigned short count=0;//백스페이스 제한
            while(1)
            {
                input=getch();
                if(input=='\n') break;
                else if(count!=0&&input==127) //지우기일때
                {
                    cout<<"\b \b";
                    userPW.pop_back();
                    count--;
                }
                else if(input!=127)
                {
                    cout<<"*";
                    userPW.push_back(input);
                    count++;
                }
            }
            cout<<"\n-------------------------------------------------\n";
            
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
            system("clear");
            cout<<"\x1b[1;106m-----------|L||o||g||i||n||P||a||g||e|-----------\x1b[m\n";
            cout<<"이메일 혹은 휴대폰 번호를 입력해주십시오 > ";
            cin>>input;
            cout<<"\n-------------------------------------------------\n";
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
            system("clear");
            cout<<"\x1b[1;106m-----------|L||o||g||i||n||P||a||g||e|-----------\x1b[m\n";
            cout<<"아이디 > ";
            cin>>searchID;
            cout<<"이메일 혹은 휴대폰 번호 > ";
            cin>>input;
            cout<<"\n-------------------------------------------------\n";
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
            cin.get();
            break;
        }
        case 5: //메인으로
            break;
    }
}
