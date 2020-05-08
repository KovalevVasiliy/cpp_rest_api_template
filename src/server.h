#pragma once

#include <string>
#include <vector>
#include <Poco/Util/ServerApplication.h>

class TemplateServerApp : public Poco::Util::ServerApplication
{
    protected:
        int main(const std::vector<std::string> &);
};