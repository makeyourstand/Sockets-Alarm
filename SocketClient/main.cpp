#include <winsock2.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
void print();
int printInterval();
int printAlarm();
void process(int, int, int, int);
int alarmCount = 0;
int main()
{
    print();
    return 0;
}

void print()
{
    cout<<"Set time interval and 3 alarms\n";
    for (int i =0 ; i < 32; i++)
        cout<<"=";
    cout<<'\n';
    int interval = printInterval();
    int t1 = printAlarm(), t2 = printAlarm(), t3 = printAlarm();
    process(interval, t1, t2, t3);
}
int printInterval()
{
    int interval;
    cout<<"Input int interval\n";
    while (true)
    {
        if (!(cin>>interval))
            {
                cout<<"Input int interval\n";
                cin.clear();
                cin.get();
                continue;
            }
        break;
    }
    return interval;
}
int printAlarm()
{
    cout<<"You can set only 3 alarms.\nInput 0, if you wanna skip one.\nInput int count of seconds>0, if you wanna set an alarm\n";
    int t = -1;
    if (alarmCount < 3)
    {
        while (true)
        {
        if (!(cin>>t))
            {
                cout<<"Set time in seconds\n";
                cin.clear();
                cin.get();
                continue;
            }
        if (t>=0) break;
        }
        alarmCount++;
        cin.clear();
        return t;
    }
}
void process(int Interval, int Alarm1, int Alarm2, int Alarm3)
{
    WSADATA WsaData;
    int err = WSAStartup(MAKEWORD(2,2), &WsaData);
    if (err == SOCKET_ERROR)
    {
        printf("WSAStartup() failed: %ld\n", GetLastError());
        system("PAUSE");
        exit(1);
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN anADDR;
    anADDR.sin_family = AF_INET;
    anADDR.sin_port = htons(228);
    anADDR.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    err = connect(s, (struct sockaddr*)&anADDR, sizeof(struct sockaddr));

    if (err == SOCKET_ERROR)
    {
        printf("connect() failed: %ld\n", GetLastError());
        system("PAUSE");
        exit(1);
    }
    string interval = to_string(Interval);
    string alarm1 = to_string(Alarm1);
    string alarm2 = to_string(Alarm2);
    string alarm3 = to_string(Alarm3);
    // Declare and initialize variables.
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char sendbuf[32] = "";
    char recvbuf[32] = "";

  //----------------------
  // Send and receive data.
    bytesSent = send( s, interval.c_str(), interval.size(), 0 );
    printf( "Bytes Sent: %ld\n", bytesSent );
    bytesSent = send( s, alarm1.c_str(), alarm1.size(), 0 );
    printf( "Bytes Sent: %ld\n", bytesSent );
    bytesSent = send( s, alarm2.c_str(), alarm2.size(), 0 );
    printf( "Bytes Sent: %ld\n", bytesSent );
    bytesSent = send( s, alarm3.c_str(), alarm3.size(), 0 );
    printf( "Bytes Sent: %ld\n", bytesSent );
    for (int i = 0; i < 32; i++)
            cout<<"-";
        cout<<'\n';
    while (1)
    {
        bytesRecv = SOCKET_ERROR;
        while( bytesRecv == SOCKET_ERROR ) {
        bytesRecv = recv( s, recvbuf, 32, 0 );
        if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET ) {
          printf( "Connection Closed.\n");
          break;
        }
        if(bytesRecv == SOCKET_ERROR){
            printf("%d\n", WSAGetLastError());
       }
      }
        cout<<recvbuf;
        for (int i = 0; i < 32; i++)
            cout<<"-";
        cout<<'\n';
    }
    closesocket(s);
    WSACleanup();
    system("PAUSE");
}
