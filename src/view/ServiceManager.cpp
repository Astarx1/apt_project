#include "view/ServiceManager.h"

ServiceManager::ServiceManager(Address addr, ConMySQL * msql)
    : httpEndpoint(std::make_shared<Http::Endpoint>(addr)), msql(msql), player_controler(new PlayerControler(msql))
{ }

ServiceManager::~ServiceManager(){
    delete player_controler;
}

void ServiceManager::init(size_t thr) {
    auto opts = Http::Endpoint::options()
        .threads(thr)
        .flags(Tcp::Options::InstallSignalHandler | Tcp::Options::ReuseAddr);
    httpEndpoint->init(opts);
    setupRoutes();
}

void ServiceManager::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serveThreaded();
}

void ServiceManager::shutdown() {
    httpEndpoint->shutdown();
}

void ServiceManager::setupRoutes() {
    using namespace Rest;

    Routes::Post(router, "/player", Routes::bind(&ServiceManager::post_new_player, this));
    Routes::Get(router, "/players", Routes::bind(&ServiceManager::get_all_players, this));
}

void ServiceManager::post_new_player(const Rest::Request& request, Http::ResponseWriter response) {
    Player ret = player_controler->create();
    std::string out = ret.to_json_string();
    response.send(Http::Code::Ok, out);       
}

void ServiceManager::get_all_players(const Rest::Request& request, Http::ResponseWriter response) {
    std::vector<Player> ret = player_controler->get();
    response.send(Http::Code::Ok, "Ok");       
}