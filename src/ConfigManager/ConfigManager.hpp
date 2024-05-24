 /*
 * Projet 2014 infosv
 * Laurent Kilchoer
 * David Laroche
 */
 
#include <map>
#include <string>
#include <iostream>

#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP
 
 
class ConfigManager
{
public:
	//methodes
	int getInt(std::string const& key) const;
	void setInt(std::string const& key, int value);
	double getDouble(std::string const& key) const;
	void setDouble(std::string const& key, double value);
	std::string getString(std::string const& key) const;
	void setString(std::string const& key, std::string value);
	bool getBool(std::string const& key) const;
	void setBool(std::string const& key, bool value);
	bool load(std::string const& filename, bool clear=false);
	
private:
	std::map<std::string,int> entiers; //bibliotheque des int
	std::map<std::string,double> rationels; //bibliotheque des double
	std::map<std::string,std::string> chaines; //bibliotheque des string
	std::map<std::string,bool> booleens; //bibliotheque des bool
};
#endif

