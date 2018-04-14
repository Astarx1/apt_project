#include "view/Service/ServicesManager.hpp"
#include "view/Service/VersionService.hpp"
#include "view/User/UserService.hpp"
#include "view/Request.h"

#include <iostream>
#include <sstream>
#include <microhttpd.h>
#include <string.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(int argc, char *const *argv)
{ 
    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        driver = get_driver_instance();
        
        ServicesManager servicesManager;
//        servicesManager.registerService(make_unique<VersionService>());
        servicesManager.registerService (make_unique<VersionService>());

        servicesManager.registerService(make_unique<UserService>());

        struct MHD_Daemon *d;
        if (argc != 2) {
            printf("%s PORT\n", argv[0]);
            return 1;
        }
        d = MHD_start_daemon(// MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
                MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
                // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
                atoi(argv[1]),
                NULL, NULL, 
                &main_handler, (void*) &servicesManager,
                MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                MHD_OPTION_END);
        if (d == NULL)
            return 1;
        cout << "Pressez <entrée> pour arrêter le serveur" << endl;
        (void) getc(stdin);
        MHD_stop_daemon(d);
    }
    catch(exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}