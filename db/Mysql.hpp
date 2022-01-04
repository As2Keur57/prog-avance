#ifndef MYSQL
#define MYSQL

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdarg.h>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>

using namespace sql;
using namespace std;

/**
 * \mainpage Mysql documentation
 * You must install : 
 * apt-get install libmysqlcppconn-dev
 * apt-get install libboost-dev libboost1.67-dev
 *
 * To compile, use  : g++ ... -lmysqlcppconn
 *
 * Git connect cpp : https://github.com/anhstudios/mysql-connector-cpp
 */

/**
 * \author Limbach Thibaud
 * \version 1.0
 * \file Mysql.h
 */

/**
 * \class Mysql
 * \brief Overlay that ease the use of a database
 */

class Mysql
{
    public:
        /**
         * Allows you to connect to a mysql server and choose a database
         * \param const string host 
         * \param const string login
         * \param const string pwd
         * \param string dbName;
         */
        Mysql(const string host, const string login, const string pwd, string dbName);

        /**
         * Delete a mysql instance 
         */
        virtual ~Mysql();

        //methods

        /**
         * Allows to change your current database
         * \param string name : name of the new database 
         */
        void setDataBase(string name);

        /**
         * Allows you to send any query to a database serveur
         * \param string queryInstruction : in sql language
         * \param bool prepare : true if the queryInstruction is a prepareInstruction 
         * \return bool : false if there is any problem while sending the query
         */
        bool query(string queryInstruction, bool prepare = false);

        /**
         * Fetch the desired result 
         * \param string columnName
         * \return string : result
         */
        string getColumn(string columnName);

        /**
         * Fetch the desired result
         * \param int columnIdex 
         * \return string : result
         */
        string getColumn(int columnIndex);

        /**
         * Seek if the current column name is null
         * \param string columnIdex 
         * \return bool : result
         */
        bool isEmpty(string columnName);

        /**
         * Seek if the current column index is null
         * \param int columnIdex 
         * \return bool : result
         */
        bool isEmpty(int columnIndex);

         /**
         * Allows you to insert parameter(s) in the prepare query
         * \param int index : index of the parameter, it begins at 1
         * \param string var
         */
        void set(int index, string var);

        /**
         * Allows to insert paramte(s) in the prepare query
         * \param int index : index of the parameter, it begins at 1
         * \param int var
         */
        void set(int index, int var);

        /**
         * Allows to insert paramte(s) in the prepare query
         * \param int index : index of the parameter, it begins at 1
         * \param double var
         */
        void set(int index, double var);

        /**
         * Allows to insert paramte(s) in the prepare query
         * \param int index : index of the parameter, it begins at 1
         * \param bool var
         */
        void set(int index, bool var);

        /**
         * Execute the prepare query
         */
        void execute();

        /**
         * Initialize the first line of the result or go to the next line
         */
        bool next();

        /**
         * Get the result number line
         */
        int getNbRows();


    protected:

    private:
	  	Connection *con;
	    Statement *stmt;
        PreparedStatement *pstmt;
	    ResultSet *res;
        bool waitReturn;
};

#endif //MYSQL_OVERLAY
