#include <iostream>

#ifndef RESERVE_PAGE_H_
#define RESERVE_PAGE_H_

//좌석 상태 배열 -- 일정별로 저장되게 ---
struct DaySeat
{
    bool mvip[10] = { false };
    bool vip[28] = { false };
    bool gold[52] = { false };
    bool silver[54] = { false };
};
class ReservePage
{
    private:
        //예매 페이지
        short count[3]={ 0 }; //일정마다 카운트 - 1일 1인 2매

        unsigned short day;
        unsigned short section; //1 MVIP|2 VIP|3 GOLD|4 SILVER
        short seatNum;
        //예매 정보 저장
        std::string Ticket;
        int price = 0;
        DaySeat dayseat[3];
        //좌석 인덱스
        unsigned short index[4]={ 0 }; //MVIP, VIP, GOLD, SILVER 순
        //좌석 배치도
        short seat[11][21]={ //mvip=4,vip=3,gold=2,silver=1
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,
            0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,
            0,1,1,1,3,3,3,3,4,4,4,4,4,3,3,3,3,1,1,1,0,
            0,1,1,1,3,3,0,0,0,0,0,0,0,0,0,3,3,1,1,1,0,
            0,1,1,1,3,3,0,0,0,0,0,0,0,0,0,3,3,1,1,1,0,
            0,1,1,1,3,3,0,0,0,0,0,0,0,0,0,3,3,1,1,1,0,
            0,1,1,1,3,3,3,3,4,4,4,4,4,3,3,3,3,1,1,1,0,
            0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,
            0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        };

    public:
        //예매 진행
        void ProgressRS(void);
        //구역 선택 - 상태 플래그 반환
        short SelecSection(void);
        //자리 선택 - 상태 플래그 반환
        short SelecSeat(void);

};
#endif