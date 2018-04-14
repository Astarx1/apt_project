#include "view/Service/AbstractService.hpp"

AbstractService::AbstractService (const string& pattern) {
    setPattern(pattern);
}

AbstractService::~AbstractService() {
    
}

const string& AbstractService::getPattern () const {
    return pattern;
}

void AbstractService::setPattern (const std::string& pattern) {
    this->pattern = pattern;
}

HttpStatus AbstractService::get (Json::Value& out, const std::vector<std::string>& params) const {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
}

HttpStatus AbstractService::post (const Json::Value& in, const std::vector<std::string>& params) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
}

HttpStatus AbstractService::put (Json::Value& out, const Json::Value& in) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
}

HttpStatus AbstractService::remove (const std::vector<std::string>& params) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
}
