#include <iostream>
#include <fstream>
#include <unistd.h>

#include "PayPage.h"
#include "LoginPage.h"

bool PayPage::ProgressPay(LoginPage & login,unsigned int & Tprice)
{
    char answer;
    //선택한 좌석 출력
    sleep(1);
    system("clear");
    std::cout<<"\x1b[1;106m-------------|P||a||y||m||e||n||t|-------------\x1b[m\n"
                "선택된 좌석 > \n";
    std::ifstream readFile;
    readFile.open("temp.txt"); //좌석 정보 저장되어있는 임시 파일
    std::string line;
    while(true)
    {
        getline(readFile,line);
        if(readFile.eof()) break;
        std::cout<<line<<std::endl; //예매내역 출력
        Tlist.append(line);
    } //임시파일에서 선택 좌석 정보 읽어와 Tlist에 저장
    //결제 여부
    std::cout<<"계속해서 결제하시겠습니까? (Y/N)";
    std::cin>>answer;
    while(std::cin.get()!='\n');
    while(answer!='y'&&answer!='Y'&&answer!='n'&&answer!='N')
    {
        std::cout<<"다시 입력해주세요 > ";
        answer = std::cin.get();
        while(std::cin.get()!='\n');
    } 
    
    //ok면 결제 return 1
    if(answer=='y'||answer=='Y')
    {
        std::cout<<Tprice<<"원이 결제됩니다. \n";
        //유저 데이터에 저장해야함
        login.SaveTicket(Tlist);
        Tprice =0;
        return true;
    }
    //no면 메인 return 0
    else
    {
        std::cout<<"결제를 취소하고 메인으로 돌아갑니다. \n";
        Tprice = 0;
        return false;
    }
}
