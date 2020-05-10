#include "test.h"
#include "database.h"

void Test::TestDB()
{
    Database db;
    db.ExecuteSQL("create table if not exists users(id int, name text);");
}