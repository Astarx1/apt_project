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
    ServiceManager(Address addr, ConMySQL * msql);
    ~ServiceManager();

    void init(size_t thr = 2);
    void start();

    void shutdown();

private:
    void setupRoutes();
    void post_new_player(const Rest::Request& request, Http::ResponseWriter response);
    void get_all_players(const Rest::Request& request, Http::ResponseWriter response);

    typedef std::mutex Lock;
    typedef std::lock_guard<Lock> Guard;

    PlayerControler * player_controler;
    ConMySQL * msql;

    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;

};