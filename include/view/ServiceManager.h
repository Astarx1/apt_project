#include "controler/Player/PlayerControler.h"
#include "model/MySQLLink.h"

#include "view/Generic.h"
#include "ignored/infos.h"

#include <algorithm>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

using namespace std;
using namespace Pistache;


class ServiceManager {
public:
    ServiceManager(Address addr, ConMySQL * msql)
        : httpEndpoint(std::make_shared<Http::Endpoint>(addr)), msql(msql), player_controler(new PlayerControler(msql))
    { }

    ~ServiceManager(){
        delete player_controler;
    }

    void init(size_t thr = 2) {
        auto opts = Http::Endpoint::options()
            .threads(thr)
            .flags(Tcp::Options::InstallSignalHandler | Tcp::Options::ReuseAddr);
        httpEndpoint->init(opts);
        setupRoutes();
    }

    void start() {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serveThreaded();
    }

    void shutdown() {
        httpEndpoint->shutdown();
    }

private:
    void setupRoutes() {
        using namespace Rest;

        Routes::Post(router, "/player", Routes::bind(&ServiceManager::post_new_player, this));
    }

    void post_new_player(const Rest::Request& request, Http::ResponseWriter response) {
        Player ret = player_controler->create();
        std::string out = ret.to_json_string();
        response.send(Http::Code::Ok, out);       
    }

    typedef std::mutex Lock;
    typedef std::lock_guard<Lock> Guard;

    PlayerControler * player_controler;
    ConMySQL * msql;

    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;

};