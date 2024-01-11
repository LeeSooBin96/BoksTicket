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
        unsigned short count[3]= { 0 }; //일자별 매수 계산

    public:
        //메뉴 출력 - 커서 위치 입력 받음
        void ShowMenu(unsigned short);
        //로그인 정보 초기화
        void ClearUserInfo(void);
        //로그인 진행(로그인 상태변수 참조)
        void ProgressLogin(bool &);
        //티켓 저장
        void SaveTicket(string & Tlist);
        //보유 티켓 갯수
        unsigned short* CountTicet(void);
        //보유 티켓 출력
        unsigned short ShowTicket(void);
        //티켓 상세 정보 출력
        void ShowTDetail(unsigned short);
};
#endif