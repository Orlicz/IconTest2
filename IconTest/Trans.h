#pragma once

#pragma comment(lib,"ws2_32.lib")
#include<bits/stdc++.h>
#include<winsock2.h>
#include <string>
#include <locale>
#include <codecvt>

// convert string to wstring
inline std::wstring to_wide_string(const std::string& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}
// convert wstring to string 
inline std::string to_byte_string(const std::wstring& input)
{
    //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(input);
}
template<char* buf>
class HttpConnect {
public:
    std::string State;
    HttpConnect() {
        //此处一定要初始化一下，否则gethostbyname返回一直为空
        WSADATA wsa = { 0 };
        WSAStartup(MAKEWORD(2, 2), &wsa);
    };
    ~HttpConnect() {};
    const char* socketHttp(std::string host, std::string request) {
        int sockfd;
        struct sockaddr_in address;
        struct hostent* server;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_port = htons(80);
        server = gethostbyname(host.c_str());
        memcpy((char*)&address.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
        if (-1 == connect(sockfd, (struct sockaddr*)&address, sizeof(address))) {
            State = "connection error!";
            return "connection error!";
        }
        State = request;
        send(sockfd, request.c_str(), request.size(), 0);
        int offset = 0;
        int rc;
        while (rc = recv(sockfd, buf + offset, 1024, 0))
            offset += rc;
        closesocket(sockfd);
        buf[offset] = 0;
        return buf;
    }
    const char* postData(std::string host, std::string path, std::string post_content) {
        //POST请求方式
        std::stringstream stream;
        stream << "POST " << path;
        stream << " HTTP/1.0\r\n";
        stream << "Host: " << host << "\r\n";
        stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
        stream << "Content-Type:application/x-www-form-urlencoded\r\n";
        stream << "Content-Length:" << post_content.length() << "\r\n";
        stream << "Connection:close\r\n\r\n";
        stream << post_content.c_str();
        return socketHttp(host, stream.str());
    };
    const char* getData(std::string host, std::string path, std::string get_content) {
        //GET请求方式
        std::stringstream stream;
        stream << "GET " << path << "?" << get_content;
        stream << " HTTP/1.0\r\n";
        stream << "Host: " << host << "\r\n";
        stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
        stream << "Connection:close\r\n\r\n";
        return socketHttp(host, stream.str());
    }
};


std::vector<std::string> stringSplit(const std::string& str, std::string delim) {
    std::string s;
    s+=delim;
    std::regex reg(s);
    std::vector<std::string> elems(std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
        std::sregex_token_iterator());
    return elems;
}


std::string& replace_all(std::string& src, const std::string& old_value, const std::string& new_value) {
    // 每次重新定位起始位置，防止上轮替换后的字符串形成新的old_value
    for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length()) {
        if ((pos = src.find(old_value, pos)) != std::string::npos) {
            src.replace(pos, old_value.length(), new_value);
        }
        else break;
    }
    return src;
}
