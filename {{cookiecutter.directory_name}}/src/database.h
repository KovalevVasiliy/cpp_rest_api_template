#pragma once

#include <memory>
#include <mutex>
#include <libpq-fe.h>

class Database
{
public:
    Database();
    std::shared_ptr<PGconn> GetConnection() const;
    bool ExecuteSQL(const std::string& sql);

private:
    void establish_connection();

    std::string m_dbhost = "postgres";
    int         m_dbport = 5432;
    std::string m_dbname = "template";
    std::string m_dbuser = "user";
    std::string m_dbpass = "password";

    std::shared_ptr<PGconn>  m_connection;
};