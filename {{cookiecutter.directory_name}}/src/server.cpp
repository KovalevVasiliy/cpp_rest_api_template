#include <iostream>
#include <string>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/StringTokenizer.h>
#include <Poco/URI.h>

#include "server.h"

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;

class TemplateServerAppHandler : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
    {
        URI uri(req.getURI());
        string method = req.getMethod();

        cerr << "URI: " << uri.toString() << endl;
        cerr << "Method: " << req.getMethod() << endl;

        StringTokenizer tokenizer(uri.getPath(), "/", StringTokenizer::TOK_TRIM);
        HTMLForm form(req,req.stream());

        if(!method.compare("POST"))
        {
            cerr << "POST" << endl;
        }
        else if(!method.compare("PUT"))
        {
            cerr << "PUT" << endl;
        }
        else if(!method.compare("DELETE"))
        {
            cerr << "DELETE" << endl;
        }

        resp.setStatus(HTTPResponse::HTTP_OK);
        resp.setContentType("application/json");
        ostream& out = resp.send();

        out << "{hello:heh}" << endl;

        out.flush();
    }
};

class TemplateRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
    virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest & request)
    {
        return new TemplateServerAppHandler;
    }
};

int TemplateServerApp::main(const vector<string> &)
{
    HTTPServerParams* pParams = new HTTPServerParams;

    pParams->setMaxQueued(100);
    pParams->setMaxThreads(16);

    HTTPServer s(new TemplateRequestHandlerFactory, ServerSocket(8000), pParams);

    s.start();
    cerr << "Server started" << endl;

    waitForTerminationRequest();  // wait for CTRL-C or kill

    cerr << "Shutting down..." << endl;
    s.stop();

    return Application::EXIT_OK;
}