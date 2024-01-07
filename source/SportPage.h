#ifndef SPORT_PAGE_H_
#define SPORT_PAGE_H_

class SportPage
{
    private:
        unsigned int menu; //선택된 메뉴 번호 저장
        bool quit_s=false; //while 루프 탈출 트리거
        char group; //조 선택 저장
        unsigned int nation; //참가국 선택 번호
};
#endif