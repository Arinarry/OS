#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")

#include <cstdlib>
#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <bitset>
#include <fstream>

#define SIO_RCVALL         0x98000001  
using namespace std;


typedef struct IPHeader
{
    unsigned char  ip_header_len : 4;
    unsigned char  ip_version : 4;
    unsigned char  ip_tos;
    unsigned short ip_total_length;
    unsigned short ip_id;
    unsigned char  ip_frag_offset : 5;
    unsigned char  ip_more_fragment : 1;
    unsigned char  ip_dont_fragment : 1;
    unsigned char  ip_reserved_zero : 1;

    unsigned char  ip_frag_offset1;
    unsigned char  ip_ttl;
    unsigned char  ip_protocol;
    unsigned short ip_checksum;
    unsigned int   ip_srcaddr;
    unsigned int   ip_destaddr;
};


int main(int argc, char* argv[])
{
    WSAData WSData;
    WSAStartup(0x202, &WSData);
    WSADATA     wsadata;
    SOCKET      soket;
    char        name[128];
    HOSTENT* phe;
    SOCKADDR_IN sokadr;
    IN_ADDR sa1;
    unsigned long flag = 1;

    soket = socket(AF_INET, SOCK_RAW, IPPROTO_IP);

    gethostname(name, sizeof(name));
    phe = gethostbyname(name);
    ZeroMemory(&sokadr, sizeof(sokadr));
    sokadr.sin_family = AF_INET;
    sokadr.sin_addr.s_addr = ((struct in_addr*)phe->h_addr_list[0])->s_addr;

    bind(soket, (SOCKADDR*)&sokadr, sizeof(SOCKADDR));

    ioctlsocket(soket, SIO_RCVALL, &flag);
    ofstream outputFile("packet_info.txt", ios::app);
    while (1)
    {
        int s = 0;
        char Buffer[1024];
        s = recv(soket, Buffer, sizeof(Buffer), 0);
        if (s >= sizeof(IPHeader))
        {
            cout << "\tPackage information: " << endl;
            IPHeader* hdr = (IPHeader*)Buffer;
            sa1.s_addr = hdr->ip_srcaddr;
            cout << "\tSource = ";
            printf(inet_ntoa(sa1));
            cout << endl;
            cout << "\tDestination = ";
            sa1.s_addr = hdr->ip_destaddr;
            printf(inet_ntoa(sa1));
            cout << endl;
            if (hdr->ip_protocol == IPPROTO_TCP) printf("\tProtocol: TCP \n");
            if (hdr->ip_protocol == IPPROTO_UDP) printf("\tProtocol: UDP \n");
            cout << "\tVersion =  " << static_cast<int>(hdr->ip_version) << endl;
            cout << "\tHeader length: " << static_cast<int>(hdr->ip_header_len & 15) << endl;
            cout << "\tType of Service: " << bitset<8>(hdr->ip_tos) << " (" << static_cast<int>(hdr->ip_tos) << ")" << endl;
            cout << "\tTotal length: " << ntohs(hdr->ip_total_length) << endl;
            cout << "\tId: " << hdr->ip_id << endl;
            //cout << "\tFlags: 0x" << hex << (hdr->ip_frag_offset >> 13) << dec << endl;
            //cout << "\tOffset: " << (hdr->ip_frag_offset & 8191) << endl;
            cout << "\tTTL = " << static_cast<int>(hdr->ip_ttl) << " ms" << endl;
            cout << "---------------------------------------";

            sa1.s_addr = hdr->ip_srcaddr;
            outputFile << "\tSource = " << inet_ntoa(sa1) << endl;
            sa1.s_addr = hdr->ip_destaddr;
            outputFile << "\tDestination = " << inet_ntoa(sa1) << endl;
            if (hdr->ip_protocol == IPPROTO_TCP) outputFile << "\tProtocol: TCP \n";
            if (hdr->ip_protocol == IPPROTO_UDP) outputFile << "\tProtocol: UDP \n";
            outputFile << "\tVersion =  " << static_cast<int>(hdr->ip_version) << endl;
            outputFile << "\tHeader length: " << static_cast<int>(hdr->ip_header_len & 15) << endl;
            outputFile << "\tType of Service: " << bitset<8>(hdr->ip_tos) << " (" << static_cast<int>(hdr->ip_tos) << ")" << endl;
            outputFile << "\tTotal length: " << ntohs(hdr->ip_total_length) << endl;
            outputFile << "\tId: " << hdr->ip_id << endl;
            //outputFile << "\tFlags: " << bitset<3>(hdr->ip_frag_offset >> 13) << endl;
            //outputFile << "\tOffset: " << bitset<13>(hdr->ip_frag_offset & 8191) << endl;
            outputFile << "\tTTL = " << static_cast<int>(hdr->ip_ttl) << " ms" << endl;
            outputFile << "---------------------------------------" << endl;
        }
        cout << endl;
        Sleep(1000);
    }
    outputFile.close();
    WSACleanup();
    system("PAUSE");
    return EXIT_SUCCESS;
}
