#include <winsock2.h>
#include <iostream>
#include<ctime>
#include <thread>
#include <chrono>
using namespace std;
int main()
{
    WSADATA WsaData;
    int err = WSAStartup(MAKEWORD(2,2), &WsaData);
    if (err == SOCKET_ERROR)
    {
        printf("WSAStartup() failed: %ld\n", GetLastError());
        system("PAUSE");
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(228);
    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    err = bind(s, (LPSOCKADDR)&sin, sizeof(sin));

    if (err == SOCKET_ERROR)
    {
        printf("bind() failed: %ld\n", GetLastError());
        system("PAUSE");
        return 1;
    }

    err = listen(s, SOMAXCONN);

    if (err == SOCKET_ERROR)
    {
        printf("listen() failed: %ld\n", GetLastError());
        system("PAUSE");
        return 1;
    }

    SOCKET acceptS;

    SOCKADDR_IN from;
    int fromlen = sizeof(from);

    acceptS = accept(s, (struct sockaddr*)&from, &fromlen);
    char recvbuf[32] = "";
    //interval
    int bytesRecv = SOCKET_ERROR;
    while( bytesRecv == SOCKET_ERROR ) {
        bytesRecv = recv( acceptS, recvbuf, 32, 0 );
        if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET ) {
          printf( "Connection Closed.\n");
          break;
        }
        if(bytesRecv == SOCKET_ERROR){
            printf("%d\n", WSAGetLastError());
       }
        printf( "Bytes Recv: %ld\n", bytesRecv );
      }
      int interval = 0;
        for (int i = 0; recvbuf[i]!='\0'; i++)
        {
            interval*=10;
            interval+=int (recvbuf[i])-48;
        }
        //alarm1
        char recvbuf1[32] = "";
    bytesRecv = SOCKET_ERROR;
    while( bytesRecv == SOCKET_ERROR ) {
        bytesRecv = recv( acceptS, recvbuf1, 32, 0 );
        if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET ) {
          printf( "Connection Closed.\n");
          break;
        }
        if(bytesRecv == SOCKET_ERROR){
            printf("%d\n", WSAGetLastError());
       }
        printf( "Bytes Recv: %ld\n", bytesRecv );
      }
      int alarm1 = 0;
        for (int i = 0; recvbuf1[i]!='\0'; i++)
        {
            alarm1*=10;
            alarm1+=int (recvbuf1[i])-48;
        }
        //alarm2
        char recvbuf2[32] = "";
        bytesRecv = SOCKET_ERROR;
    while( bytesRecv == SOCKET_ERROR ) {
        bytesRecv = recv( acceptS, recvbuf2, 32, 0 );
        if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET ) {
          printf( "Connection Closed.\n");
          break;
        }
        if(bytesRecv == SOCKET_ERROR){
            printf("%d\n", WSAGetLastError());
       }
        printf( "Bytes Recv: %ld\n", bytesRecv );
      }
      int alarm2 = 0;
        for (int i = 0; recvbuf2[i]!='\0'; i++)
        {
            alarm2*=10;
            alarm2+=int (recvbuf2[i])-48;
        }
        //alarm3
        char recvbuf3[32] = "";
        bytesRecv = SOCKET_ERROR;
        while( bytesRecv == SOCKET_ERROR ) {
        bytesRecv = recv( acceptS, recvbuf3, 32, 0 );
        if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET ) {
          printf( "Connection Closed.\n");
          break;
        }
        if(bytesRecv == SOCKET_ERROR){
            printf("%d\n", WSAGetLastError());
       }
        //printf( "Bytes Recv: %ld\n", bytesRecv );
      }
      int alarm3 = 0;
        for (int i = 0; recvbuf3[i]!='\0'; i++)
        {
            alarm3*=10;
            alarm3+=int (recvbuf3[i])-48;
        }
        bool a1 = true, a2 = true, a3 = true;
        if (alarm1 == 0) a1 = false;
        if (alarm2 == 0) a2 = false;
        if (alarm3 == 0) a3 = false;
        std::string sendbuf = "";
        while (1)
        {
            for (int i = 0; i < 32; i++)
                cout<<"-";
            cout<<'\n';
            time_t seconds = time(NULL);
            tm* timeinfo = localtime(&seconds);
            sendbuf = asctime(timeinfo);
            int bytesSent = send(acceptS, sendbuf.c_str(), 32, 0);
            printf( "Bytes Sent: %ld\n", bytesSent);
            if (alarm1 > 0 ) {
                sendbuf.clear();
                sendbuf = std::to_string(alarm1);
                sendbuf+=" sec left at Alarm 1.\n";
                bytesSent = send(acceptS, sendbuf.c_str(), 32, 0);
                printf( "Bytes Sent: %ld\n", bytesSent);
                alarm1 -= interval;
            }
            else if (alarm1 <= 0 && a1)
            {
                sendbuf.clear();
                sendbuf = "ALARM # 1!\n";
                bytesSent = send(acceptS, sendbuf.c_str(), 32, 0);
                printf( "Bytes Sent: %ld\n", bytesSent);
                a1 = false;
            }
            if (alarm2 > 0) {
                sendbuf.clear();
                sendbuf = std::to_string(alarm2);
                sendbuf+=" sec left at Alarm 2.\n";
                bytesSent = send(acceptS, sendbuf.c_str(), 32, 0);
                printf( "Bytes Sent: %ld\n", bytesSent);
                alarm2 -= interval;
            }
            else if (alarm2 <= 0 && a2)
            {
                sendbuf.clear();
                sendbuf = "ALARM # 2!\n";
                bytesSent = send(acceptS, sendbuf.c_str(), 32, 0);
                printf("Bytes Sent: %ld\n", bytesSent);
                a2 = false;
            }
            if (alarm3 > 0) {
                sendbuf.clear();
                sendbuf = std::to_string(alarm3);
                sendbuf+=" sec left at Alarm 3.\n";
                bytesSent = send(acceptS, sendbuf.c_str(), 32, 0);
                printf( "Bytes Sent: %ld\n", bytesSent);
                alarm3 -= interval;
            }
            else if (alarm3 <= 0 && a3)
            {
                sendbuf.clear();
                sendbuf = "ALARM # 3!\n";
                bytesSent = send(acceptS, sendbuf.c_str(), 32, 0);
                printf( "Bytes Sent: %ld\n", bytesSent);
                a3 = false;
            }
            std::this_thread::sleep_for( std::chrono::seconds(interval));
        }

    WSACleanup();
    closesocket(s);
    closesocket(acceptS);
    system("PAUSE");
    return 0;
}

/*int receve()
{
    int bytesRecv = SOCKET_ERROR;
    while( bytesRecv == SOCKET_ERROR ) {
        bytesRecv = recv( acceptS, recvbuf, 32, 0 );
        if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET ) {
          printf( "Connection Closed.\n");
          break;
        }
        if(bytesRecv == SOCKET_ERROR){
            printf("%d\n", WSAGetLastError());
       }
        printf( "Bytes Recv: %ld\n", bytesRecv );
      }
      int value = 0;
        for (int i = 0; recvbuf[i]!='\0'; i++)
        {
            interval*=10;
            interval+=int (recvbuf[i])-48;
        }
    return value;
}
*/
