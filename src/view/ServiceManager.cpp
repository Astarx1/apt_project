#include "view/ServiceManager.h"

ServiceManager::ServiceManager(Address addr, ConMySQL * msql) : 
    httpEndpoint(std::make_shared<Http::Endpoint>(addr)), 
    msql(msql), 
    player_controler(new PlayerControler(msql)), 
    game_controler(new GameControler(msql))
{ }

ServiceManager::~ServiceManager(){
    delete player_controler;
    delete game_controler;
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

    Routes::Get(router, "/player/:id", Routes::bind(&ServiceManager::get_player_from_id, this));
    Routes::Delete(router, "/player/:id", Routes::bind(&ServiceManager::delete_player_from_id, this));

    Routes::Post(router, "/player", Routes::bind(&ServiceManager::post_new_player, this));
    
    Routes::Get(router, "/players", Routes::bind(&ServiceManager::get_all_players, this));

    Routes::Post(router, "/game", Routes::bind(&ServiceManager::post_new_game, this));
}

void ServiceManager::post_new_game(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        std::cout << "ServiceManager.cpp - Analysing request for creating new game, getting body..." << std::endl; 

        std::string r = request.body();

        std::cout << "ServiceManager.cpp - body got, creating adequate Json reader...\n" << r << std::endl;

        Json::Value input;   
        Json::Reader reader;
        bool parsingresult = reader.parse(r, input);
        if (!parsingresult) {
            std::cout  << "ServiceManager.cpp - Failed to parse json" << reader.getFormattedErrorMessages() << "\n" << std::endl;
            response.send(Http::Code::Bad_Request, std::string("Request badly formatted : ") + r);
            return;       
        }
        parsingresult = reader.parse(input.asString(), input);
        if (!parsingresult) {
            std::cout  << "ServiceManager.cpp - Failed to parse json" << reader.getFormattedErrorMessages() << "\n" << std::endl;
            response.send(Http::Code::Bad_Request, std::string("Request badly formatted : ") + r);
            return;       
        }
        std::cout << "ServiceManager.cpp - Error (?) when processing the JSON : " << reader.getFormattedErrorMessages() << std::endl; 

        Json::FastWriter fast;
        auto idp1 = input["id_player_1"].asInt();
        int idp2 = input["id_player_2"].asInt();
        std::string m =  fast.write(input["moves"]);

        Game ret;
        std::cout << "ServiceManager.cpp - JSON values parsed, calling controler..." << std::endl; 
        if (input.isMember("winner"))
            ret = game_controler->create(idp1, idp2, m, input["winner"].asInt());
        else
            ret = game_controler->create(idp1, idp2, m);
        std::string out = ret.to_json_string();

        std::cout << "ServiceManager.cpp - Sending answer for creating new game" << std::endl; 
        response.send(Http::Code::Ok, out);       
        std::cout << "ServiceManager.cpp - Answer sent for creating new game\n" << std::endl;
    }
    catch(...) {
        std::cout << "ServiceManager.cpp - exception occured in the view in post_new_game" << std::endl;
    }
}

void ServiceManager::get_all_games(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        std::cout << "ServiceManager.cpp - Analysing request for getting all games" << std::endl; 
        
        std::vector<Game> ret = game_controler->get();
        
        Json::Value val;
        for (int i=0; i < ret.size(); i++) {
            val.append(ret[i].to_json());
        }
        std::string r = val.toStyledString();

        std::cout << "ServiceManager.cpp - Sending answer for getting all games" << std::endl; 
        response.send(Http::Code::Ok, r);       
        std::cout << "ServiceManager.cpp - Answer sent for getting all games\n" << std::endl;
    }
    catch(...) {
        std::cout << "ServiceManager.cpp - exception occured in the view in get_all_players" << std::endl;
    }
}

void ServiceManager::post_new_player(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        std::cout << "ServiceManager.cpp - Analysing request for creating new player" << std::endl; 

        Player ret = player_controler->create();
        std::string out = ret.to_json_string();

        std::cout << "ServiceManager.cpp - Sending answer for creating new player" << std::endl; 
        response.send(Http::Code::Ok, out);       
        std::cout << "ServiceManager.cpp - Answer sent for creating new player\n" << std::endl;
    }
    catch(...) {
        std::cout << "ServiceManager.cpp - exception occured in the view in post_new_player" << std::endl;
    }
}

void ServiceManager::get_all_players(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        std::cout << "ServiceManager.cpp - Analysing request for getting all players" << std::endl; 
        
        std::vector<Player> ret = player_controler->get();
        
        Json::Value val;
        for (int i=0; i < ret.size(); i++) {
            val.append(ret[i].to_json());
        }
        std::string r = val.toStyledString();

        std::cout << "ServiceManager.cpp - Sending answer for getting all players" << std::endl; 
        response.send(Http::Code::Ok, r);       
       std::cout << "ServiceManager.cpp - Answer sent for getting all player\n" << std::endl;
    }
    catch(...) {
        std::cout << "ServiceManager.cpp - exception occured in the view in get_all_players" << std::endl;
    }
}

void ServiceManager::get_player_from_id(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        std::cout << "ServiceManager.cpp - Analysing request for getting player from id" << std::endl; 
        
        auto id = request.param(":id").as<int>();
        
        Player ret = player_controler->read_from_id(id);
        std::string out = ret.to_json_string();

        std::cout << "ServiceManager.cpp - Sending answer for getting player from id" << std::endl; 
        response.send(Http::Code::Ok, out);  
        
        std::cout << "ServiceManager.cpp - Answer sent for getting player from id\n" << std::endl; 
    }
    catch(...) {
        std::cout << "ServiceManager.cpp - exception occured in the view in get_player_from_id" << std::endl;
    }
}

void ServiceManager::delete_player_from_id(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        std::cout << "ServiceManager.cpp - Analysing request for getting player from id" << std::endl; 

        auto id = request.param(":id").as<int>();
        
        Player ret = player_controler->delete_from_id(id);
        
        std::cout << "ServiceManager.cpp - Sending answer for deleting player from id" << std::endl; 
        response.send(Http::Code::Ok, ret.to_json_string());  
        
        std::cout << "ServiceManager.cpp - Answer sent for deleting player from id\n" << std::endl; 
    }
    catch(...) {
        std::cout << "ServiceManager.cpp - exception occured in the view in get_player_from_id" << std::endl;
    }
}