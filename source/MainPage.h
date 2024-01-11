#ifndef MAIN_PAGE_H_
#define MAIN_PAGE_H_

class MainPage
{
    private:
        unsigned short  menu; //선택된 메뉴 번호를 저장
    public:
        //메뉴 출력
        void ShowMenu(bool,unsigned short);
        //로그인시 메뉴 - 커서 위치 입력 받음
        void LoginMenu(unsigned short);
        //비로그인시 메뉴 - 커서 위치 입력 받음
        void UnLoginMenu(unsigned short);
        //메인 페이지(메뉴 번호 입력 받아 반환) - 매개변수:로그인상태값
        unsigned short Home(bool);
};
#endif