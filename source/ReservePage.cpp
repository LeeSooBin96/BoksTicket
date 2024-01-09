#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

#include "ReservePage.h"

using std::cout;
using std::cin;
using std::endl;

short ReservePage::SelecSection(void)
{
    sleep(1);
    system("clear");
    //좌석 구역 선택
    cout<<"                 < 구역 선택 > \n"
        "1]         MVIP            가격: 250,000원 \n"
        "\n"
        "2]         VIP             가격: 200,000원 \n"
        "\n"
        "3]         GOLD            가격: 120,000원 \n"
        "\n"
        "4]         SILVER          가격: 80,000원 \n"
        "\n"
        "------------------------------------------------------ \n";
    cout<<"관람하실 구역을 선택해주세요 (이전으로 0)>";
    cin>>section;
    if(!cin)
    {
        cin.clear(); //에러 플래그 초기화
        cout<<"잘못된 입력입니다. \n";
        while(cin.get()!='\n'); //버퍼 비우기
        return SelecSection();
    }
    switch(section)
    {
        case 0:
            Ticket.clear();
            return -1;
        case 1:
            Ticket.append("MVIP,");
            price+=250000;
            break;
        case 2:
            Ticket.append("VIP,");
            price+=200000;
            break;
        case 3:
            Ticket.append("GOLD,");
            price+=120000;
            break;
        case 4:
            Ticket.append("SILVER,");
            price+=80000;
            break;
        default:
            cout<<"잘못된 입력입니다.\n";
            return SelecSection();
            break;
    }
    return 0;
}
short ReservePage::SelecSeat(void)
{
    sleep(1);
    system("clear");
    //상세 자리 선택
    for(int i=0;i<4;i++)
    {
        index[i]=0; //인덱스 초기화
    }
    cout<<"\t\t\t\t< 좌석 배치도 > \n";
    for(int i=0;i<11;i++) //좌석 배치도 출력
    {
        for(int j=0;j<21;j++)
        {
            switch(seat[i][j])
            {
                case 0:
                    cout<<"〓  ";
                    break;
                case 1: 
                    if(section==4&&!dayseat[day-1].silver[index[section-1]]) //좌석이 비어있으면
                    {
                        if(index[section-1]<10)
                        {
                            cout<<index[section-1]<<"  |";
                        }
                        else
                        {
                            cout<<index[section-1]<<" |";
                        }
                        index[section-1]++;
                    }
                    else if(section==4)
                    {
                        index[section-1]++;
                        cout<<"■   ";
                    }
                    else
                    {
                        cout<<"■   ";
                    }
                    break;
                case 2:
                    if(section==3&&!dayseat[day-1].gold[index[section-1]]) //좌석이 비어있으면
                    {
                        if(index[section-1]<10)
                        {
                            cout<<index[section-1]<<"  |";
                        }
                        else
                        {
                            cout<<index[section-1]<<" |";
                        }
                        index[section-1]++;
                    }
                    else if(section==3)
                    {
                        index[section-1]++;
                        cout<<"■   ";
                    }
                    else
                    {
                        cout<<"■   ";
                    }
                    break;
                case 3:
                    if(section==2&&!dayseat[day-1].vip[index[section-1]]) //좌석이 비어있으면
                    {
                        if(index[section-1]<10)
                        {
                            cout<<index[section-1]<<"  |";
                        }
                        else
                        {
                            cout<<index[section-1]<<" |";
                        }
                        index[section-1]++;
                    }
                    else if(section==2)
                    {
                        index[section-1]++;
                        cout<<"■   ";
                    }
                    else
                    {
                        cout<<"■   ";
                    }
                    break;
                case 4:
                    if(section==1&&!dayseat[day-1].mvip[index[section-1]]) //좌석이 비어있으면
                    {
                        if(index[section-1]<10)
                        {
                            cout<<index[section-1]<<"  |";
                        }
                        else
                        {
                            cout<<index[section-1]<<" |";
                        }
                        index[section-1]++;
                    }
                    else if(section==1)
                    {
                        index[section-1]++;
                        cout<<"■   ";
                    }
                    else
                    {
                        cout<<"■   ";
                    }
                    break;
                default:
                    break;
            }
        }
        cout<<endl;
    }
    cout<<"좌석 번호를 선택해주세요(돌아가기는 -1)>";
    cin>>seatNum;
    if(!cin)
    {
        cin.clear(); //에러 플래그 초기화
        cout<<"잘못된 입력입니다. 일정 선택창으로 돌아갑니다. \n";
        while(cin.get()!='\n'); //버퍼 비우기
        return -1;
    }
    if(seatNum==-1)
    {
        cout<<"일정 선택창으로 돌아갑니다. \n";
        return -1;
    }
    switch(section)
    {
        case 1: 
            if(seatNum<10&&!dayseat[day-1].mvip[seatNum]) //올바른 입력
            {
                dayseat[day-1].mvip[seatNum]=true; //예매 상태로
                cout<<seatNum<<"번 좌석을 선택하셨습니다. \n";
            }
            else if(seatNum<10)
            {
                cout<<"이미 선택된 좌석입니다. \n";
                return SelecSeat();
            }
            else
            {
                cout<<"비정상적인 입력입니다. 일정 선택 창으로 돌아갑니다. \n";
                return -1;
            }
            break;
        case 2:
            if(seatNum<28&&!dayseat[day-1].vip[seatNum]) //올바른 입력
            {
                dayseat[day-1].vip[seatNum]=true; //예매 상태로
                cout<<seatNum<<"번 좌석을 선택하셨습니다. \n";
            }
            else if(seatNum<28)
            {
                cout<<"이미 선택된 좌석입니다. \n";
                return SelecSeat();
            }
            else
            {
                cout<<"비정상적인 입력입니다. 일정 선택 창으로 돌아갑니다. \n";
                return -1;
            }
            break;
        case 3:
            if(seatNum<52&&!dayseat[day-1].gold[seatNum]) //올바른 입력
            {
                dayseat[day-1].gold[seatNum]=true; //예매 상태로
                cout<<seatNum<<"번 좌석을 선택하셨습니다. \n";
            }
            else if(seatNum<52)
            {
                cout<<"이미 선택된 좌석입니다. \n";
                return SelecSeat();
            }
            else
            {
                cout<<"비정상적인 입력입니다. 일정 선택 창으로 돌아갑니다. \n";
                return -1;
            }
            break;
        case 4:
            if(seatNum<54&&dayseat[day-1].silver[seatNum]) //올바른 입력
            {
                dayseat[day-1].silver[seatNum]=true; //예매 상태로
                cout<<seatNum<<"번 좌석을 선택하셨습니다. \n";
            }
            else if(seatNum<54)
            {
                cout<<"이미 선택된 좌석입니다. \n";
                return SelecSeat();
            }
            else
            {
                cout<<"비정상적인 입력입니다. 일정 선택 창으로 돌아갑니다. \n";
                return -1;
            }
            break;
        default:
            break;
    }
    return 0;
}
short ReservePage::ProgressRS(void)
{
    short flag;
    char answer;
    std::string Tlist;

    sleep(1);
    system("clear");
    //경기 일정 선택
    cout<<"                < 대한민국 경기 일정 > \n"
        "1] 1/15 20:30 대한민국   vs 바레인      개최지: DOHA\n"
        "\n"
        "2] 1/20 20:30 요르단     vs 대한민국    개최지: DOHA\n"
        "\n"
        "3] 1/25 20:3O 대한민국   vs 말레이시아  개최지: AL WAKRAH\n"
        "\n"
        "------------------------------------------------------ \n";
    cout<<"관람하실 경기 일정을 선택해주세요 (메인으로 0)>";
    cin>>day;
    if(!cin)
    {
        cin.clear(); //에러 플래그 초기화
        cout<<"잘못된 입력입니다. 메인창으로 돌아갑니다.\n";
        while(cin.get()!='\n'); //버퍼 비우기
        return 0;
    }
    switch(day)
    {
        case 0:
            cout<<"메인으로 돌아갑니다. \n";
            return 0;
        case 1:
            Ticket.append("1/15,");
            break;
        case 2:
            Ticket.append("1/20,");
            break;
        case 3:
            Ticket.append("1/25,");
            break;
        default:
            cout<<"잘못된 입력입니다. 메인창으로 돌아갑니다.\n";
            return 0;
    }

    flag=SelecSection(); //구역 선택
    if(flag==-1) //비정상적 종료
    {
        Ticket.clear();
        return ProgressRS(); //다시 실행
    }

    flag=SelecSeat(); //좌석 선택
    if(flag==-1) //비정상적 종료
    {
        Ticket.clear();
        price=0;
        return ProgressRS(); //다시 실행
    }
    if(count[day-1]==2)
    {
        cout<<"예매할 수 있는 좌석 수를 초과하셨습니다. \n";
        Ticket.clear();
        return ProgressRS();
    }
    //좌석 정보 확인
    cout<<"선택한 좌석> \n";
    cout<<Ticket<<seatNum<<"번,"<<price<<"원"<<endl;
    cout<<"계속해서 좌석을 선택하시겠습니까? (Y/N)";
    cin.get(); //버퍼에 남아있는 개행 지우기
    cin>>answer;
    while(cin.get()!='\n');
    while(answer!='y'&&answer!='Y'&&answer!='n'&&answer!='N')
    {
        cout<<"다시 입력해주세요 > ";
        answer = cin.get();
        while(cin.get()!='\n');
    } 
    Tlist=Ticket;
    Tlist.append(std::to_string(seatNum));
    Tlist.append(",");
    Tlist.append(std::to_string(price));
    Tlist.append(",");
    std::ofstream writeFile;
    writeFile.open("temp.txt",std::ios::app); //임시 저장 파일
    writeFile<<Tlist<<endl;
    writeFile.close();
    if(answer=='y'||answer=='Y') //선택된 정보 저장하고 좌석 계속 선택
    {
        cout<<"좌석 선택을 계속합니다. \n";
        Ticket.clear();
        Tlist.clear();
        price = 0;
        return ProgressRS();
    }
    else //결제 진행
    {
        cout<<"결제를 진행합니다. \n";
        //선택한 좌석 출력
        sleep(1);
        system("clear");
        cout<<"선택된 좌석 > \n";
        std::ifstream readFile;
        readFile.open("temp.txt"); //좌석 정보 저장되어있는 임시 파일
        std::string line;
        Tlist.clear();
        while(true)
        {
            readFile>>line;
            if(readFile.eof()) break;
            Tlist.append(line);
            Tlist.append("\n");
        } //임시파일에서 선택 좌석 정보 읽어와 Tlist에 저장
        cout<<Tlist;
        //결제 여부
        cout<<"계속해서 결제하시겠습니까? (Y/N)";
        cin>>answer;
        while(cin.get()!='\n');
        while(answer!='y'&&answer!='Y'&&answer!='n'&&answer!='N')
        {
            cout<<"다시 입력해주세요 > ";
            answer = cin.get();
            while(cin.get()!='\n');
        } 
        //ok면 결제 return 1
        if(answer=='y'||answer=='Y')
        {
            std::ofstream initFile;
            initFile.open("temp.txt"); //임시파일 비우기
            initFile.close();
            //유저 데이터에 저장해야함
            return 1;
        }
        //no면 메인 return 0
        else
        {
            cout<<"결제를 취소하고 메인으로 돌아갑니다. \n";
            return 0;
        }
    }
    return 0;             
}