#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>
#include <nlohmann/json.hpp>
#include<string>
#include<fstream>
using json = nlohmann::json;
typedef std::vector<char> char_array;



std::string getresponse;
bool authenticated = false;



char_array charset()
{
    return char_array(
        { '0','1','2','3','4',
        '5','6','7','8','9',
        'A','B','C','D','E','F',
        'G','H','I','J','K',
        'L','M','N','O','P',
        'Q','R','S','T','U',
        'V','W','X','Y','Z',
        'a','b','c','d','e','f',
        'g','h','i','j','k',
        'l','m','n','o','p',
        'q','r','s','t','u',
        'v','w','x','y','z'
        });
};



std::string random_string(size_t length, std::function<char(void)> rand_char)
{
    std::string str(length, 0);
    std::generate_n(str.begin(), length, rand_char);
    return str;
}



size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* s)
{
    s->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}



int get(std::string url)
{
    getresponse = "";
    CURL* curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &getresponse);
        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }
    return 0;
}



void gen_random(int length) {
    const std::string urlstart = "https://api.anonfiles.com/v2/file/";
    std::string urlcustom;
    std::string jsonstring;
    const std::string urlend = "/info";
    const auto ch_set = charset();
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, ch_set.size() - 1);
    auto randchar = [ch_set, &dist, &rng]() {return ch_set[dist(rng)];};
    urlcustom = random_string(length, randchar);
    std::string totalurl = urlstart + urlcustom + urlend;
    get(totalurl);
    auto jsoncontent = json::parse(getresponse);
    if (jsoncontent["status"] == false)
    {
        std::cout << "[Invalid] https://anonfiles.com/" << urlcustom << "/" << "\n";
    }
    if (jsoncontent["status"] == true)
    {
        std::cout << "[Valid] https://anonfiles.com/" << urlcustom << "/" << "\n";
        std::ofstream fout;
        std::ifstream fin;
        fin.open("valid.txt");
        fout.open("valid.txt", std::ios::app);
        if (fin.is_open())
            fout << "https://anonfiles.com/" << urlcustom << "/" << "\n";
        fin.close();
        fout.close();
    }

}



void authenticate() {
    std::string authurl = "ENTER AUTHENTICATION URL HERE";
    /* Removed authentication as this is not required.

    while (!(authenticated == true))
    {
      
            system("CLS");
            std::string hashurl, totalurl, authkey, hash, jsoncontent, status, username;
            std::cout << "Enter Your Auth Key: ";
            std::cin >> authkey;
            hashurl += "https://api.hashify.net/hash/md5/hex?value=";
            hashurl += authkey;
            get(hashurl);
            system("CLS");
            nlohmann::json json;
            json = json::parse(getresponse,nullptr,false);
            hash == json["Digest"];
            totalurl += authurl;
            totalurl += hash;
            totalurl += "/getToken/";
            get(totalurl);
            json = json::parse(getresponse,nullptr,false);
    	try {
            status == json["token"];
          //  username = json["username"];
            authenticated = true;
        }
    	catch(...){}
        }

        */
}



int main(void)
{
    SetConsoleTitle("AnonBrute | Created By Adamn (https://github.com/Adamn1111)");
    authenticate();
    std::string data,choice;
    std::string temp;
    int urlnumber;
    do {
        system("CLS");
        std::cout << "AnonBrute | Created By Adamn (https://github.com/Adamn1111)\n\n";
        try {
                std::cout << "Enter number of URLs to check:  ";
                std::cin >> urlnumber;

                for (auto i = 0; i <= urlnumber - 1; i++)
                {
                    gen_random(10);
                }
        }
        catch (...) {

        }
        
    } while (true);
}


