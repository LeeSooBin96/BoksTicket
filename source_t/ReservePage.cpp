#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

#include "ReservePage.h"
#include "LoginPage.h"
#include "PayPage.h"

using std::cout;
using std::cin;
using std::endl;

void ReservePage::SetSeat(void)
{
    string line;
    unsigned short dayIndex; //일자 인덱스
    unsigned short sectIndex; //구역 인덱스
    unsigned short seatIndex; //좌석 인덱스

    std::ifstream readFile;
    readFile.open("BookingL.csv");
    if(!readFile.is_open()) //파일 열렸는지 확인(파일이 없으면 안열린다)
    {
        std::ofstream tempFile;
        tempFile.open("BookingL.csv"); //없으면 데이터 파일 생성해주기
        tempFile.close();
        readFile.close(); 
        return; //볼것이 없다.
    }
    
    getline(readFile,line,','); //아이디 건너뛰기
    while(true)
    {
        getline(readFile,line,','); //경기 일자 가져오기
        if(readFile.eof()) break;
        if(!line.compare("1/15")) dayIndex = 0;
        else if(!line.compare("1/20")) dayIndex = 1;
        else if(!line.compare("1/25")) dayIndex = 2;
        else //아이디 일때 다시 읽기
            continue;

        getline(readFile,line,','); //구역 가져오기
        if(!line.compare("MVIP")) sectIndex=0;
        else if(!line.compare("VIP")) sectIndex=1;
        else if(!line.compare("GOLD")) sectIndex=2;
        else if(!line.compare("SILVER")) sectIndex=3;

        getline(readFile,line,','); //좌석 번호 가져오기
        seatIndex=stoi(line);
        //예약 좌석 정보 적용
        switch(sectIndex)
        {
            case 0:
                dayseat[dayIndex].mvip[seatIndex]=true;
                break;
            case 1:
                dayseat[dayIndex].vip[seatIndex]=true;
                break;
            case 2:
                dayseat[dayIndex].gold[seatIndex]=true;
                break;
            case 3:
                dayseat[dayIndex].silver[seatIndex]=true;
                break;
        }
        getline(readFile,line,','); //가격 건너뛰기
    }
    
    return;
}
short ReservePage::SelecSection(void)
{
    sleep(1);
    system("clear");
    //좌석 구역 선택
    cout<<"\x1b[1;106m--------------|B||o||o||k||i||n||g||S||Y||S|--------------\x1b[m\n"
        "                 < 구역 선택 > \n"
        "1]         MVIP            가격: 250,000원 \n"
        "\n"
        "2]         VIP             가격: 200,000원 \n"
        "\n"
        "3]         GOLD            가격: 120,000원 \n"
        "\n"
        "4]         SILVER          가격: 80,000원 \n"
        "\n"
        "---------------------------------------------------------- \n";
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
    cout<<"\x1b[1;106m--------------------------|B||o||o||k||i||n||g||S||Y||S|--------------------------\x1b[m\n"
        "\t\t\t\t< 좌석 배치도 > \n";
    for(int i=0;i<11;i++) //좌석 배치도 출력
    {
        for(int j=0;j<21;j++)
        {
            switch(seat[i][j])
            {
                case 0:
                    if(i==0||i==10||j==0||j==20)
                    {
                        cout<<"〓  ";
                    }
                    else
                    {
                        cout<<"🟩  ";
                    }
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
short ReservePage::ProgressRS(LoginPage & login)
{
    short flag;
    char answer;
    std::string Tlist;

    sleep(1);
    system("clear");
    //경기 일정 선택
    cout<<"\x1b[1;106m--------------|B||o||o||k||i||n||g||S||Y||S|--------------\x1b[m\n"
        "                < 대한민국 경기 일정 > \n"
        "1] 1/15 20:30 대한민국   vs 바레인      개최지: DOHA\n"
        "\n"
        "2] 1/20 20:30 요르단     vs 대한민국    개최지: DOHA\n"
        "\n"
        "3] 1/25 20:3O 대한민국   vs 말레이시아  개최지: AL WAKRAH\n"
        "\n"
        "---------------------------------------------------------- \n";
    cout<<"관람하실 경기 일정을 선택해주세요 (메인으로 0)>";
    cin>>day;
    if(!cin)
    {
        cin.clear(); //에러 플래그 초기화
        cout<<"잘못된 입력입니다. 메인창으로 돌아갑니다.\n";
        while(cin.get()!='\n'); //버퍼 비우기
        return 0;
    }
    count=login.CountTicet();
    switch(day)
    {
        case 0:
            cout<<"메인으로 돌아갑니다. \n";
            return 0;
        case 1:
            Ticket.append("1/15,");
            count[0]++;
            break;
        case 2:
            Ticket.append("1/20,");
            count[1]++;
            break;
        case 3:
            Ticket.append("1/25,");
            count[2]++;
            break;
        default:
            cout<<"잘못된 입력입니다. 메인창으로 돌아갑니다.\n";
            return 0;
    }

    flag=SelecSection(); //구역 선택
    if(flag==-1) //비정상적 종료
    {
        Ticket.clear();
        return ProgressRS(login); //다시 실행
    }

    flag=SelecSeat(); //좌석 선택
    if(flag==-1) //비정상적 종료
    {
        Ticket.clear();
        price=0;
        return ProgressRS(login); //다시 실행
    }
    if(count[day-1]>2)
    {
        cout<<"예매할 수 있는 좌석 수를 초과하셨습니다. (1일 2매 가능)\n";
        Ticket.clear();
        sleep(1);
        return ProgressRS(login);
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
        if(!ProgressRS(login)) //비정상적인 종료
        {
            std::ofstream truncFile;
            truncFile.open("temp.txt");
            truncFile.close();
            return 0;
        }
        else return 1;
    }
    else //결제 진행
    {
        cout<<"결제를 진행합니다. \n";
        Ticket.clear();
        Tlist.clear();
        price = 0;
        PayPage pay;
        return pay.ProgressPay(login);
    }
    return 0;             
}