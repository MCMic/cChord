/*
 *  Request.cpp
 *  P2P_Engine
 *
 *  Created by LogNet team 2010 - INRIA
 *  Mediteranee - Sophia Antipolis - France
 *
 */

#include "Request.h"
#include "ChordTransportCode.h"

//Constructor.
Request::Request(string overlayID, int code){
	this->overlayID = overlayID;
	this->code		= code;
}

//Adds an arument to the Request arguments Map.
void Request::addArg(string key, string value)
{
	arguments.insert(arg(key, value));
}

//Request an argument to the request arguments Map.
string Request::getArg(string key)
{
	argMap::iterator it = arguments.find(key);
	
	if(it != arguments.end())
	{
		return(it->second);
	}
	
	return "";
}

//Serialize the whole request into a callback string. "/callback?var1=a&var2=b....&var1000=bar"
string Request::serialize()
{
	argMap::iterator it;
	
	ostringstream ss;
	string *callback;
	
	switch (this->getCode()) {
		case GETPRED:
			callback = new string("/getpred");
			break;
			
		case FINDSUCC:			
			callback = new string("/findsucc");
			break;
			
		case NOTIF:
			callback = new string("/notif");
			break;
			
		case JOIN:
			callback = new string("/join");
			break;
			
		case PUT:
			callback = new string("/put");
			break;
			
		case GET:
			callback = new string("/get");
			break;
			
		case SETSUCC:
			callback = new string("/setsucc");
			break;
			
		case SETPRED:
			callback = new string("/setpred");
			break;
			
		default:
			cout << " UNHANDLED CHORD TRANSPORT CODE! ... ASSERTING" << endl;
			assert(this->getCode());
			break;
	}
	
	ss << (*callback);
	int mapSize = 0; 
	
	if((mapSize = arguments.size()) > 0)
	{
		ss << "?";
		int i = 0;
		
		for (it = arguments.begin(); it != arguments.end(); ++it)
		{
			ss << (*it).first << "=" << (*it).second;
			
			if (i < mapSize - 1)
			{
				ss << "&";
				i++;
			}		
		}
	}
	return 	ss.str();
}

















