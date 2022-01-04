#include "Mysql.hpp"

Mysql::Mysql(string host, string login, string pwd, string dbName)
{
	try
	{
	    con = get_driver_instance()->connect(host.c_str(), login.c_str(), pwd.c_str());

	    setDataBase(dbName);

	    stmt = con->createStatement();
	} catch (SQLException &e) {
		throw string("An error occurred while trying to connect to the database");
	}
}

Mysql::~Mysql()
{
    delete res;
	delete stmt;
	delete con;
	delete pstmt;

}

//---------------------------
// Change data base 
//--------------------------- 
void Mysql::setDataBase(string dbName)
{
	try
	{
		con->setSchema(dbName.c_str());
	} catch (SQLException &e) {
		throw string("An error occurred while trying to connect to the database");
	}
}


//---------------------------
// get result
//--------------------------- 
string Mysql::getColumn(string columnName)
{
	string s;

	try
	{
		s = res->getString(columnName.c_str());
	} catch (SQLException &e) {
		throw string("An error occurred while trying to get the column " + columnName);
	}
	
	return s;
}

string Mysql::getColumn(int columnIndex)
{
	string s;

	try
	{
		s = res->getString(columnIndex);
	} catch (SQLException &e) {
		throw string("An error occurred while trying to get the column index " + columnIndex);
	}
	
	return s;
}

bool Mysql::isEmpty(string columnName)
{
	return res->isNull(columnName);
}

bool Mysql::isEmpty(int columnIndex)
{
	return res->isNull(columnIndex);
}

//---------------------------
// next line of result 
//--------------------------- 
bool Mysql::next()
{
	bool exist = false;

	try
	{
		if(res->next())
			exist = true;
	} catch (SQLException &e) {
		throw string("An error occurred while trying to seek next results");
	}

	return exist;
} 

//---------------------------
// query
//--------------------------- 
bool Mysql::query(string queryInstruction, bool prepare)
{
	bool isOk = false;
	waitReturn = queryInstruction.find("SELECT") == 0 || queryInstruction.find("select") == 0;

	try
	{
		if(prepare)
		{
			if(pstmt != NULL)
				delete(pstmt);
			pstmt = con->prepareStatement((queryInstruction + ";").c_str());
		} else {

			if(waitReturn)
			{
				res = stmt->executeQuery((queryInstruction + ";").c_str());
				isOk = !res;
			} else {
				isOk = stmt->execute((queryInstruction + ";").c_str());
			}
		}
	} catch (SQLException &e) {
		throw string("An error occurred while trying to fetch the query");
	}

	return isOk || prepare;
}


//---------------------------
// prepare query
//--------------------------- 

void Mysql::set(int index, string var)
{
	try
	{
		pstmt->setString(index, var.c_str());
	} catch (SQLException &e) {
		throw string("An error occurred while trying to send data");
	}
}

void Mysql::set(int index, int var)
{
	try
	{
		pstmt->setInt(index, var);
	} catch (SQLException &e) {
		throw string("An error occurred while trying to send data");
	}
}

void Mysql::set(int index, double var)
{
	try
	{
		pstmt->setDouble(index, var);
	} catch (SQLException &e) {
		throw string("An error occurred while trying to send data");
	}
	
}

void Mysql::set(int index, bool var)
{
	try
	{
		pstmt->setBoolean(index, var);
	} catch (SQLException &e) {
		throw string("An error occurred while trying to send data");
	}
}

void Mysql::execute()
{
	try
	{
	    if(waitReturn)
	    	res = pstmt->executeQuery();
	    else
	    	pstmt->execute();
	} catch (SQLException &e) {
		throw string("An error occurred while trying to execute the query");
	}
}

//---------------------------
//method
//---------------------------

int Mysql::getNbRows()
{
	int i;

	try
	{
		i = res->rowsCount();
	} catch (SQLException &e) {
		throw string("An error occurred while trying to get the rows count");
	}

	return i;
}

