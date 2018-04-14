#include "view/Service/ServicesManager.hpp"
#include "view/Service/VersionService.hpp"
#include "view/User/UserService.hpp"

#include <iostream>
#include <sstream>
#include <microhttpd.h>
#include <string.h>

using namespace std;

class Request {
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request();
};

// Fonction pour gérer les données imporantes en upload (non implanté ici)
int post_iterator(void *cls,
                enum MHD_ValueKind kind,
                const char *key,
                const char *filename,
                const char *content_type,
                const char *transfer_encoding,
                const char *data, uint64_t off, size_t size);

// Détruit les données d'une requête
void request_completed (void *cls, struct MHD_Connection *connection, 
                        void **con_cls, enum MHD_RequestTerminationCode toe);

// Gestionnaire principal
int main_handler (  void *cls,      
                    struct MHD_Connection *connection,
                    const char *url, // 
                    const char *method,
                    const char *version,
                    const char *upload_data, size_t *upload_data_size, void **ptr);
