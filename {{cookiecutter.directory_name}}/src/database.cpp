#include <iostream>
#include <cstdlib>

#include "database.h"

bool Database::ExecuteSQL(const std::string& sql)
{
    if (PQstatus(m_connection.get()) != CONNECTION_OK)
    {
        std::cerr << "Connection to database failed: "
                  << PQerrorMessage(m_connection.get()) << std::endl;
        return false;
    }
    else
    {
        std::cerr << "Connection to database has been established" << std::endl;
    }

    auto result = PQexec(m_connection.get(), sql.c_str());
    if(PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cerr << "Error occurred" << std::endl;
        return false;
    }
    return true;
}

Database::Database()
{
    LoadEnvVariables();
    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), std::to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
        throw std::runtime_error( PQerrorMessage( m_connection.get() ) );
    }

}

void Database::LoadEnvVariables()
{
    m_dbhost = getenv("DATABASE_HOST");
    m_dbport = atoi(getenv("DATABASE_PORT"));
    m_dbname = getenv("DATABASE_NAME");
    m_dbuser = getenv("DATABASE_USER");
    m_dbpass = getenv("DATABASE_PASSWORD");
}


std::shared_ptr<PGconn> Database::GetConnection() const
{
    return m_connection;
}