#ifndef SPORT_PAGE_H_
#define SPORT_PAGE_H_

class SportPage
{
    private:
        unsigned short menu; //선택된 메뉴 번호 저장
        bool quit_s=false; //while 루프 탈출 트리거
        unsigned int group; //조 선택 저장
        unsigned short nation; //참가국 선택 번호
    public:
        //아시안컵 기본정보 및 상세 정보 메뉴
        void ShowInfo(unsigned int); 
        //커서 이동 화면 - 커서 위치 전달 받음
        void ShowInfoCur(unsigned int);
        void ShowGroupCur(unsigned int);
        //조편성 정보
        void ShowGroup(unsigned int); 
        //조별 일정
        void ShowGroupSchedule(void);
        //참가국 정보 
        void ShowNationInfo(void);
        //스포츠 정보 게시판 
        void HomeBoard(void); 
};
#endif