#include <pistache/http.h>
#include <pistache/description.h>
#include <pistache/endpoint.h>

#include <pistache/serializer/rapidjson.h>

#include "view/ServiceManager.h"
#include "model/MySQLLink.h"

using namespace std;
using namespace Pistache;


int main(int argc, char *argv[]) {
    Port port(9080);
    ConMySQL * msql = new ConMySQL(); 
    int thr = 2;

    if (argc >= 2) {
        port = std::stol(argv[1]);

        if (argc == 3)
            thr = std::stol(argv[2]);
    }

    Address addr(Ipv4::any(), port);

    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << thr << " threads" << endl;

    ServiceManager manager(addr, msql);

    manager.init(thr);
    manager.start();

    auto c = getchar();

    manager.shutdown();
}
