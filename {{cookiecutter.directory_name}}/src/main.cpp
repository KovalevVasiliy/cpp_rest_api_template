#include "server.h"
#include "database.h"
#include "test.h"

int main(int argc, char** argv)
{
    //
    //Test::TestDB();
    //
    TemplateServerApp app;

    return app.run(argc, argv);
}