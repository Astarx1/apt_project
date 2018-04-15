#include "pistache/endpoint.h"

class HelloHandler : public Pistache::Http::Handler {
public:
    HTTP_PROTOTYPE(HelloHandler);
    ~HelloHandler() {}
    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response);
};