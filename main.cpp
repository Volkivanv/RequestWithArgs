#include <iostream>
#include <cpr/cpr.h>
#include <vector>


std::string requestMaking(std::vector<std::pair<std::string,std::string>> &inReq){
    std::string buf = "?";
    for(int i = 0; i < inReq.size();i++){
        if(i!=0) {
            buf+="&";
        }
        buf+=inReq[i].first+"="+inReq[i].second;
    }
    return buf;
}

int main() {
    std::vector<std::pair<std::string,std::string>> req;






    std::string arg = "", value = "";

    while((arg!="get")&&(arg!="post")){
        std::cout<<"input argument and its value"<<std::endl;
        std::cin >> arg;
        if((arg!="get")&&(arg!="post")){
            std::cin >> value;
            req.push_back(std::pair(arg,value));


        }else if(arg == "get"){

            std::cout << requestMaking(req)<<std::endl;
            cpr::Response r = cpr::Get(cpr::Url("http://httpbin.org/get"+ requestMaking(req)));
            std::cout << r.text << std::endl;
        }else if(arg == "post"){

           std::vector<cpr::Pair> initReq;




          for(int i = 0; i < req.size(); i++){
              cpr::Pair somePair =  cpr::Pair(req[i].first.c_str(), req[i].second.c_str());
              initReq.push_back(somePair);
            }




            cpr::Response r = cpr::Post(cpr::Url("http://httpbin.org/post"),
                          cpr::Payload(initReq.begin(),initReq.end()));
            std::cout << r.text << std::endl;



        }


    }




    return 0;
}
