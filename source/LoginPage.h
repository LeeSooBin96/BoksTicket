#ifndef LOGIN_PAGE_H_
#define LOGIN_PAGE_H_

#include <iostream>

using std::string;

class LoginPage
{
    private:
        //로그인 페이지
        string userID; //아이디 저장
        string userPW; //비밀번호 저장
        string searchID; //아이디 찾을 때 사용 - 찾은 아이디 저장 혹은 비밀번호 찾기 시 아이디 저장
        string searchPW; //비밀번호 찾을 때 사용 - 찾은 비밀번호 저장
        string input; //아이디/비밀번호 찾기 시 입력받은 정보 저장
        unsigned short menu; //선택된 메뉴 번호 저장
    public:
        //로그인 정보 초기화
        void ClearUserInfo(void);
        //로그인 진행(로그인 상태변수 참조)
        void ProgressLogin(bool &);
};
#endif