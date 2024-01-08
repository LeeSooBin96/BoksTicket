#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <unistd.h>

#include "JoinPage.h"

using namespace std;

void JoinPage::ProgressJoin(void)
{
    sleep(1);
        system("clear");
        cout<<"[ 메인으로 돌아가려면 x를 입력해주세요 ] \n";
        //아이디 입력
        cout<<" 아이디 ______\b\b\b\b\b\b";
        cin>>id;
        if(!id.compare("x"))
        {
            return;
        }
        //문자수 부족 혹은 초과이거나 영문자가 아닌 문자로 시작
        unpass = (id.size()<6||id.size()>20)||(!isalpha(id.front())); 
        if(!unpass) //위 조건 통과
        {
            for(int i=0;i<id.size();i++) //영문자,숫자 제외한 문자 있는지 검사
            {
                if(!islower(id[i])&&!isdigit(id[i])) 
                {
                    unpass=true;
                }
            }
        }
        if(!unpass) //위 조건 모두 통과
        {
            //데이터 파일 열기
            ifstream readFile;
            readFile.open("data.csv");
            if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
            {
                ofstream tempFile;
                tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                if(!tempFile.is_open())
                {
                    cout<<"아이디 중복 검사에 실패했습니다. \n";
                    exit(1);
                }
                tempFile.close();
            }
            //중복 검사 실시
            string temp;
            while(!readFile.eof())
            {
                getline(readFile,temp,','); //회원번호 건너뛰기
                getline(readFile,temp,','); //아이디 가져오기
                if(!temp.compare(id)) //아이디가 중복이면
                {
                    cout<<"중복된 아이디입니다. \n";
                    unpass = true;
                    break;
                }
                for(int i=0;i<3;i++)
                {
                    getline(readFile,temp,','); //비밀번호,이메일,휴대폰 건너뛰기
                }
            }
            readFile.close();
        }
        while(unpass) //아이디 부적합 판정일때 재입력 요구
        {
            id.clear();
            cout<<"영문으로 시작하는 6~20자 영문(소문자),숫자만 사용해주세요. \n";
            cout<<"--------------------------------------------------------\n";
            cout<<" 아이디 ______\b\b\b\b\b\b";
            cin>>id;
            if(!id.compare("x")) break;
            //문자수 부족 혹은 초과이거나 영문자가 아닌 문자로 시작
            unpass = (id.size()<6||id.size()>20)||(!isalpha(id.front())); 
            if(!unpass) //위 조건 통과
            {
                for(int i=0;i<id.size();i++) //영문자,숫자 제외한 문자 있는지 검사
                {
                    if(!islower(id[i])&&!isdigit(id[i])) 
                    {
                        unpass=true;
                        break;
                    }
                }
            }
            if(!unpass) //위 조건 모두 통과
            {
                //데이터 파일 열기
                ifstream readFile;
                readFile.open("data.csv");
                if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
                {
                    ofstream tempFile;
                    tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                    if(!tempFile.is_open())
                    {
                        cout<<"아이디 중복 검사에 실패했습니다. \n";
                        exit(1);
                    }
                    tempFile.close();
                }
                //중복 검사 실시
                string temp;
                while(!readFile.eof())
                {
                    getline(readFile,temp,','); //회원번호 건너뛰기
                    getline(readFile,temp,','); //아이디 가져오기
                    if(!temp.compare(id)) //아이디가 중복이면
                    {
                        cout<<"중복된 아이디입니다. \n";
                        unpass = true;
                        break;
                    }
                    for(int i=0;i<3;i++)
                    {
                        getline(readFile,temp,','); //비밀번호,이메일,휴대폰 건너뛰기
                    }
                }
                readFile.close();
            }
        }
        if(!id.compare("x"))
        {
            return;
        }
        cout<<"--------------------------------------------------------\n";
        cout<<"사용 가능한 아이디입니다. \n\n";

        //비밀번호 입력
        cout<<" 비밀번호 __________\b\b\b\b\b\b\b\b\b\b";
        cin>>password;
        unpass = (password.size()<8||password.size()>12); //자리수 검사
        if(!unpass) //위 조건 통과
        {
            //영문자,숫자,특수문자 포함 확인 변수
            unsigned short alphaCNT = 0;
            unsigned short digitCNT = 0;
            unsigned short punctCNT = 0;
            for(int i=0;i<password.size();i++)
            {
                if(isalpha(password[i])) alphaCNT++;
                else if(isdigit(password[i])) digitCNT++;
                else if(ispunct(password[i])) punctCNT++;
            }
            unpass=(alphaCNT==0||digitCNT==0||punctCNT==0);
        }
        while(unpass)
        {
            password.clear();
            cout<<"8~12자 영문자,숫자,특수문자를 포함해야 합니다. \n";
            cout<<"--------------------------------------------------------\n";
            cout<<" 비밀번호 __________\b\b\b\b\b\b\b\b\b\b";
            cin>>password;
            unpass = (password.size()<8||password.size()>12); //자리수 검사
            if(!unpass)
            {
                //영문자,숫자,특수문자 포함 확인 변수
                unsigned short alphaCNT = 0;
                unsigned short digitCNT = 0;
                unsigned short punctCNT = 0;
                for(int i=0;i<password.size();i++)
                {
                    if(isalpha(password[i])) alphaCNT++;
                    else if(isdigit(password[i])) digitCNT++;
                    else if(ispunct(password[i])) punctCNT++;
                }
                unpass=(alphaCNT==0||digitCNT==0||punctCNT==0);
            }
        }
        cout<<"--------------------------------------------------------\n";
        cout<<"사용 가능한 비밀번호입니다. \n\n";

        //이메일 입력
        cout<<" 이메일 __________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        cin>>email;
        //이메일 입력값 검사
        unpass = (email.find("@")==string::npos)||(email.find(".")==string::npos);
        if(!unpass) //위 조건 통과
        {
            unpass=(email.find("@")>email.find("."));
        }
        if(!unpass) //위 조건 모두 통과
        {
            //데이터 파일 열기
            ifstream readFile;
            readFile.open("data.csv");
            if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
            {
                ofstream tempFile;
                tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                if(!tempFile.is_open())
                {
                    cout<<"이메일 중복 검사에 실패했습니다. \n";
                    exit(1);
                }
                tempFile.close();
            }
            //중복 검사 실시
            string temp;
            while(!readFile.eof())
            {
                for(int i=0;i<3;i++)
                {
                    getline(readFile,temp,','); //회원번호,아이디,비밀번호 건너뛰기
                }
                getline(readFile,temp,','); //이메일 가져오기
                if(!temp.compare(email)) //이메일이 중복이면
                {
                    cout<<"중복된 이메일입니다. \n";
                    unpass = true;
                    break;
                }
                getline(readFile,temp,','); //비밀번호,이메일,휴대폰 건너뛰기
            }
            readFile.close();
        }
        while(unpass)
        {
            cout<<"올바르지 않은 이메일입니다. \n";
            cout<<"--------------------------------------------------------\n";
            cout<<" 이메일 __________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
            cin>>email;
            //이메일 입력값 검사
            unpass = (email.find("@")==string::npos)||(email.find(".")==string::npos);
            if(!unpass)
            {
                unpass=(email.find("@")>email.find("."));
            }
            if(!unpass) //위 조건 모두 통과
            {
                //데이터 파일 열기
                ifstream readFile;
                readFile.open("data.csv");
                if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
                {
                    ofstream tempFile;
                    tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                    if(!tempFile.is_open())
                    {
                        cout<<"이메일 중복 검사에 실패했습니다. \n";
                        exit(1);
                    }
                    tempFile.close();
                }
                //중복 검사 실시
                string temp;
                while(!readFile.eof())
                {
                    for(int i=0;i<3;i++)
                    {
                        getline(readFile,temp,','); //회원번호,아이디,비밀번호 건너뛰기
                    }
                    getline(readFile,temp,','); //이메일 가져오기
                    if(!temp.compare(email)) //이메일이 중복이면
                    {
                        cout<<"중복된 이메일입니다. \n";
                        unpass = true;
                        break;
                    }
                    getline(readFile,temp,','); //비밀번호,이메일,휴대폰 건너뛰기
                }
                readFile.close();
            }
        }
        cout<<"--------------------------------------------------------\n";

        //휴대폰 번호 입력
        unpass = false; //초기화
        cout<<" 휴대폰 (- 제외)___________\b\b\b\b\b\b\b\b\b\b\b";
        cin>>phoneNum;
        {
            //데이터 파일 열기
            ifstream readFile;
            readFile.open("data.csv");
            if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
            {
                ofstream tempFile;
                tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                if(!tempFile.is_open())
                {
                    cout<<"휴대폰 번호 중복 검사에 실패했습니다. \n";
                    exit(1);
                }
                tempFile.close();
            }
            //중복 검사 실시
            string temp;
            while(!readFile.eof())
            {
                for(int i=0;i<4;i++)
                {
                    getline(readFile,temp,','); //회원번호,아이디,비밀번호,이메일 건너뛰기
                }
                getline(readFile,temp,','); //휴대폰 번호 가져오기
                if(!temp.compare(phoneNum)) //휴대폰 번호가 중복이면
                {
                    cout<<"중복된 휴대폰 번호입니다. \n";
                    unpass = true;
                    break;
                }
            }
            readFile.close();
        }
        while(unpass)
        {
            unpass = false; //초기화
            cout<<"--------------------------------------------------------\n";
            cout<<" 휴대폰 (- 제외)___________\b\b\b\b\b\b\b\b\b\b\b";
            cin>>phoneNum;
            {
                //데이터 파일 열기
                ifstream readFile;
                readFile.open("data.csv");
                if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
                {
                    ofstream tempFile;
                    tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
                    if(!tempFile.is_open())
                    {
                        cout<<"휴대폰 번호 중복 검사에 실패했습니다. \n";
                        exit(1);
                    }
                    tempFile.close();
                }
                //중복 검사 실시
                string temp;
                while(!readFile.eof())
                {
                    for(int i=0;i<4;i++)
                    {
                        getline(readFile,temp,','); //회원번호,아이디,비밀번호,이메일 건너뛰기
                    }
                    getline(readFile,temp,','); //휴대폰 번호 가져오기
                    if(!temp.compare(phoneNum)) //휴대폰 번호가 중복이면
                    {
                        cout<<"중복된 휴대폰 번호입니다. \n";
                        unpass = true;
                        break;
                    }
                }
                readFile.close();
            }
        }

        //회원번호 생성
        long long makeNum = CID + rand()%CID;
        sprintf(acctID,"%lld",makeNum);
        //회원번호 중복 검사
        ifstream readFile;
        readFile.open("data.csv");
        if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
        {
            ofstream tempFile;
            tempFile.open("data.csv"); //없으면 데이터 파일 생성해주기
            if(!tempFile.is_open())
            {
                cout<<"회원번호 생성에 실패했습니다. \n";
                exit(1);
            }
            tempFile.close();
        }

        string temp;
        while(!readFile.eof()) //회원번호 생성 및 중복 검사
        {
            getline(readFile,temp,',');
            if(!temp.find(acctID))
            {
                makeNum = CID + rand()%CID;
                sprintf(acctID,"%lld",makeNum);
            }
            for(int i=0;i<4;i++)
            {
                getline(readFile,temp,','); //아이디,비밀번호,이메일,휴대폰 건너뛰기
            }
        }
        readFile.close();

        cout<<"--------------------------------------------------------\n";
        cout<<"등록된 정보는 다음과 같습니다. \n";
        cout<<"회원 번호 : "<<acctID<<endl;
        cout<<"아이디 : "<<id<<endl;
        cout<<"비밀번호 : ";
        for(int i=0;i<password.size();i++)
        {
            cout<<"● ";
        }
        cout<<endl;
        cout<<"이메일 : "<<email<<endl;
        cout<<"휴대폰 : "<<phoneNum<<endl;
        
        
        //데이터 파일에 저장
        ofstream writeFile;
        writeFile.open("data.csv",ios_base::app);
        if(!writeFile.is_open()) //파일 열렸는지 확인
        {
            cout<<"회원 데이터 저장에 실패했습니다. \n";
            exit(1);
        }
        //파일에 입력
        writeFile<<acctID<<","<<id<<","<<password<<","<<email<<","<<phoneNum<<","<<endl;
        writeFile.close();

        sleep(1);
}