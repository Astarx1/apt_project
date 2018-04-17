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
        std::cout << "ServiceManager.cpp - Error when processing the JSON : " << reader.getFormattedErrorMessages() << std::endl; 

        Json::FastWriter fast;
        try {
            /*std::cout << "get member names" << std::endl;
            auto g = input.getMemberNames();
            std::cout << "get member names" << std::endl;
            for (auto a : g) {
                std::cout << a << std::endl;
            }*/ 
                    std::cout << "test idp1" << std::endl;
        Json::Value val = input;
        switch (input.type()) {
            case Json::nullValue: cout << "null\n"; break;
            case Json::intValue: cout << "int " << val.asLargestInt() << "\n"; break;
            case Json::uintValue: cout << "uint " << val.asLargestUInt() << "\n"; break;
            case Json::realValue: cout << "real " << val.asDouble() << "\n"; break;
            case Json::stringValue: cout << "string " << val.asString() << "\n"; break;
            /*
            -or-
            case Json::stringValue: {
                const char *begin;
                const char *end;
                val.getString(&begin, &end);
                cout << "string of length " << end - begin << "\n";
            }
            break;
            */
            case Json::booleanValue: cout << "boolean " << val.asBool() << "\n"; break;
            case Json::arrayValue: cout << "array of length " << val.size() << "\n"; break;
            case Json::objectValue: cout << "object of length " << val.size() << "\n"; break;
            default: cout << "wrong type\n"; break;
        }
        }
        catch(exception& e) {
            std::cout << e.what() << std::endl;
        }


        std::cout << "ServiceManager.cpp - JSON created, parsing values, starting by player 1 ..." << std::endl; 
        auto idp1 = input["id_player_1"].asInt();
        std::cout << "ServiceManager.cpp - player 2 ..." << std::endl; 
        int idp2 = input["id_player_2"].asInt();
        std::cout << "ServiceManager.cpp - moves ..." << std::endl; 
        std::string m =  fast.write(input["moves"]);

        std::cout << "ServiceManager.cpp - JSON values parsed, calling controler..." << std::endl; 
        Game ret = game_controler->create(idp1, idp2, m);
        std::string out = ret.to_json_string();

        std::cout << "ServiceManager.cpp - Sending answer for creating new game" << std::endl; 
        response.send(Http::Code::Ok, out);       
        std::cout << "ServiceManager.cpp - Answer sent for creating new game\n" << std::endl;
    }
    catch(...) {
        std::cout << "ServiceManager.cpp - exception occured in the view in post_new_game" << std::endl;
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