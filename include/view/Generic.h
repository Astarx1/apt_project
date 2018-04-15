#include <pistache/http.h>
#include <pistache/description.h>
#include <pistache/endpoint.h>

using namespace Pistache;

namespace Generic {
void handleReady(const Rest::Request&, Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "1");
}
}