#pragma once
#include<string>
#include<windows.h>
std::string utf8_to_ansi(std::string strUTF8) {
    UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, NULL, NULL);
    WCHAR* wszBuffer = new WCHAR[nLen + 1];
    nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, wszBuffer, nLen);
    wszBuffer[nLen] = 0;
    nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
    CHAR* szBuffer = new CHAR[nLen + 1];
    nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
    szBuffer[nLen] = 0;
    strUTF8 = szBuffer;
    delete[]szBuffer;
    delete[]wszBuffer;
    return strUTF8;
}
std::string ansi_to_utf8(std::string strAnsi) {
    UINT nLen = MultiByteToWideChar(936, NULL, strAnsi.c_str(), -1, NULL, NULL);
    WCHAR* wszBuffer = new WCHAR[nLen + 1];
    nLen = MultiByteToWideChar(936, NULL, strAnsi.c_str(), -1, wszBuffer, nLen);
    wszBuffer[nLen] = 0;
    nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
    CHAR* szBuffer = new CHAR[nLen + 1];
    nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
    szBuffer[nLen] = 0;
    strAnsi = szBuffer;
    delete[]wszBuffer;
    delete[]szBuffer;
    return strAnsi;
}
char* utf8_to_ansi(char* strUTF8A) {
    std::string strUTF8 = strUTF8A;
    UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, NULL, NULL);
    WCHAR* wszBuffer = new WCHAR[nLen + 1];
    nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, wszBuffer, nLen);
    wszBuffer[nLen] = 0;
    nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
    CHAR* szBuffer = new CHAR[nLen + 1];
    nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
    szBuffer[nLen] = 0;
    strUTF8 = szBuffer;
    delete[]szBuffer;
    delete[]wszBuffer;
    char* p = (char*)strUTF8.data();
    return p;
}
char* ansi_to_utf8(char* strAnsiA) {
    std::string strAnsi = strAnsiA;
    UINT nLen = MultiByteToWideChar(936, NULL, strAnsi.c_str(), -1, NULL, NULL);
    WCHAR* wszBuffer = new WCHAR[nLen + 1];
    nLen = MultiByteToWideChar(936, NULL, strAnsi.c_str(), -1, wszBuffer, nLen);
    wszBuffer[nLen] = 0;
    nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
    CHAR* szBuffer = new CHAR[nLen + 1];
    nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
    szBuffer[nLen] = 0;
    strAnsi = szBuffer;
    delete[]wszBuffer;
    delete[]szBuffer;
    char* p = (char*)strAnsi.data();
    return p;
}