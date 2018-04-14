#include "view/Request.h"

Request::~Request() {
    if (pp) MHD_destroy_post_processor (pp);
}

// Fonction pour gérer les données imporantes en upload (non implanté ici)
int post_iterator(void *cls,
        enum MHD_ValueKind kind,
        const char *key,
        const char *filename,
        const char *content_type,
        const char *transfer_encoding,
        const char *data, uint64_t off, size_t size) {
    std::cout << "Request.cpp - post_iterator" << std::endl;
    if (0 == strcmp ("DONE", key)) {
      std::cout << "Session done" << std::endl;
      return MHD_YES;
    }
    if (0 == strcmp ("v1", key)) {
        std::cout << "V1" << std::endl;
        return MHD_YES;
    }
    if (0 == strcmp ("v2", key)) {
        std::cout << "V1" << std::endl;
        return MHD_YES;
    }
    std::cout << "Unsupported form value " << key << std::endl;
    return MHD_YES;
}

// Détruit les données d'une requête
void
request_completed (void *cls, struct MHD_Connection *connection,
                   void **con_cls, enum MHD_RequestTerminationCode toe)
{
  Request *request = (Request*)*con_cls;
  if (request) {
      delete request;
      *con_cls = nullptr;
  }
}

// Gestionnaire principal
int
main_handler (void *cls,      
          struct MHD_Connection *connection,
          const char *url, // 
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr) 
{
    Request *request = (Request*)*ptr;
    std::cout << "Request.cpp - beginning handler (data size : " << *upload_data_size << ")" << std::endl;
    if (!request) { 
        std::cout << "Request.cpp - New Request : " << url << " - " << method << std::endl;   
        request = new Request();
        if (!request) {
            return MHD_NO;
        }
        *ptr = request;
        
        return MHD_YES;
    }    

    if ((*upload_data_size) > 0) {
        std::cout << "Request.cpp - Data :" << upload_data << std::endl;
        request->data += std::string(upload_data); 
    }

    HttpStatus status;
    string response = "ok";
    try {
        std::cout << "Request.cpp - Finding parameters" << std::endl;
        std::vector<std::string> params;
        
        const char * qs = MHD_lookup_connection_value (connection, MHD_GET_ARGUMENT_KIND, "name");
        if (qs != NULL)
            params.push_back(std::string(qs));
        else
            params.push_back(std::string(""));

        qs = MHD_lookup_connection_value (connection, MHD_GET_ARGUMENT_KIND, "name");
        if (qs != NULL)
            params.push_back(std::string(qs));
        else
            params.push_back(std::string(""));

        std::cout << "Request.cpp - Calling Service Manager" << std::endl;
        ServicesManager *manager = (ServicesManager*) cls;
        status = manager->queryService(response, request->data, url, method, params);
        std::cout << "Request.cpp - Service ended" << std::endl;
    }
    catch(ServiceException& e) {
        std::cout << "Request.cpp - Service Error" << std::endl;
        status = e.status();
        response = e.what();
        response += "\n";
    }
    catch(exception& e) {
        std::cout << "Request.cpp - Server Error" << std::endl;
        status = HttpStatus::SERVER_ERROR;
        response = e.what();
        response += "\n";
    }
    catch(...) {
        std::cout << "Request.cpp - Unknown Server Error" << std::endl;
        status = HttpStatus::SERVER_ERROR;
        response = "Unknown exception\n";
    }

    struct MHD_Response *mhd_response;
    
    if (method == "GET") {
        std::cout << "Request.cpp - Creating response : " << response.c_str() << " (" << response.size() << ")" << std::endl;
        mhd_response = MHD_create_response_from_buffer(response.size(),(void *)response.c_str(),MHD_RESPMEM_MUST_COPY);
        MHD_add_response_header(mhd_response,"Content-Type","application/json; charset=utf-8");
    }
    else {
         mhd_response = MHD_create_response_from_data(0,NULL,0,0);
    }       
    
    std::cout << connection << std::endl;       
    std::cout << status << std::endl;       
    std::cout << mhd_response << std::endl;
    int ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);

    std::cout << "Request.cpp - Response status : " << ret << " - " << MHD_NO << std::endl;
    std::cout << "Request.cpp - Sending response\n\n" << std::endl;

    return ret;
}
