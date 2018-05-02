#include <pistache/http.h>
#include <pistache/description.h>
#include <pistache/endpoint.h>

#include <pistache/serializer/rapidjson.h>

#include "view/ServiceManager.h"
#include "model/MySQLLink.h"

using namespace std;
using namespace Pistache;


int main(int argc, char *argv[]) {
    std::string url;

    if (argc > 1) {
        url = argv[1];
        std::cout << "Using MySQL URL given in command line : " << url << std::endl;
    }
    else {
        url = "tcp://127.0.0.1:3306";
    }

    Port port(9080);
    ConMySQL * msql = new ConMySQL(url); 
    
    int thr = 2;

    Address addr(Ipv4::any(), port);

    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << thr << " threads" << endl;

    ServiceManager manager(addr, msql);

    manager.init(thr);
    manager.start();

    auto c = getchar();

    manager.shutdown();
}
