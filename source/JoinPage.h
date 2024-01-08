#include <iostream>
#include <string>

#ifndef JOIN_PAGE_H_
#define JOIN_PAGE_H_

using std::string;

class JoinPage
{
    private:
        char acctID[9]; //회원 번호
        string id; //아이디
        string password; //비밀번호
        string email; //이메일
        string phoneNum; //전화번호
        bool unpass; //입력값 검사값
        const long long CID = 10000000; //회원번호 베이스

    public:
        //회원가입 메인 진행
        void ProgressJoin(void);
        //아이디 검사
        bool CheckID(void);
        //비밀번호 검사
        bool CheckPW(void);
        //이메일 검사
        bool CheckEmail(void);
};
#endif