/*
# Copyright (c) 2018 Yixi. All rights reserved.
*/

#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

#include "front_engine.pb.h"
#include <iostream>
#include <map>
#include <mutex>

namespace walletfront {
class CallBackManager;
class RequestManager
{
    public:
        RequestManager();
        ~RequestManager();

    public:
        void Run();
        void RequestManagerInit();

    private:
        void OnRequest(const int &socket, const char *message);
        void HeartBeatHandler();

    private:
        void SendManage(const char *message);
        void CheckAppId(const int &socket, FrontEngine::RequestMessage &req_message);
        void RequestHeartBeat(const int &socket, FrontEngine::RequestMessage &req_message);
        void RequestCreatAccount(const int &socket, FrontEngine::RequestMessage &req_message);
        void RequestQueryBalance(const int &socket, FrontEngine::RequestMessage &req_message);
        void QueryFeeRequest(const int &socket, FrontEngine::RequestMessage &req_message);
        void RequestQueryOrder(const int &socket, FrontEngine::RequestMessage &req_message);
        void RequestQueryOrders(const int &socket, FrontEngine::RequestMessage &req_message);
        void RequestSendCoin(const int &socket, FrontEngine::RequestMessage &req_message);
        void RequestRecieveCoin(const int &socket, FrontEngine::RequestMessage &req_message);
        bool CheckClientId(const int &socket, const FrontEngine::RequestMessage &req_message);
        // for tests IF start
        void CreatAccountCallBack(FrontEngine::RequestMessage &message);
        void QueryBalanceCallBack(FrontEngine::RequestMessage &message);
        void QueryFeeCallBack(FrontEngine::RequestMessage &cb_message);
        void QueryOrderCallBack(FrontEngine::RequestMessage &message);
        void QueryOrdersCallBack(FrontEngine::RequestMessage &message);
        void TradedCallBack(FrontEngine::RequestMessage &message);
        // for tests IF end
        bool CheckMd5(char *message);
        bool SetHeartBeatCount(const std::string &sdk_id);
        bool RemoveSdkId(const std::string &sdk_id);
        std::string MakeSdkId(const std::string &sdk_id, const int &socket);

        RequestManager(const RequestManager&);
        RequestManager& operator=(const RequestManager&);

    private:
        std::map<std::string, int> m_heat_count;
        CallBackManager*            m_pCallBack;

        std::mutex m_heat_mtux;
};

}
#endif //REQUEST_MANAGER_H