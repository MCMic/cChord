
#include "TextHandler.hh"
#include <iostream>
#include <stdexcept>

using namespace std;

string intToString(int p) {
    stringstream ss;
    ss << p;
    return ss.str();
}

int stringToInt(string s) {
    stringstream ss(s);
    int i;
    ss >> i;
    return i;
}

//~ TextHandler::TextHandler(string ip,int port) : ChordNode(ip,port,ip,"/tmp/"),chord(NULL) {
TextHandler::TextHandler(string ip,int port) : ChordNode(ip,port,ip+intToString(port),"/tmp/"),chord(NULL),lastModifId(0) {
    cout << "constructor called" << endl;
}

void TextHandler::connect(string ip,int port) {
    cout << "connect called" << endl;
    chord = new Node(ip, port);
    join(chord);
    
    Request *request = new Request(this->getIdentifier(), GET);
    request->addArg("key", "0"); // 0 equals last modif
    // Send the Get request
    saveData("",serialize(sendRequest(request, successor)));
}

void TextHandler::eraseText(int pos, int len) { // erase len characters at pos position
	cout << "eraseText called" << endl;
	Modification m(time(NULL),content.substr(pos, len),pos,0,lastModifId, true);
    stringstream ss;
    ss << m;
    put("",ss.str());
}
	
void TextHandler::insertText(int pos, string str, bool e) {
    cout << "insertText called" << endl;
    Modification m(time(NULL),str,pos,0,lastModifId, e);
    stringstream ss;
    ss << m;
    put("",ss.str());
}

/* IOverlay Pure METHODS */
void TextHandler::put(string key, string value) {
    cout << "put called" << endl;
    if(key == getIdentifier()) {
        return;
    } else if(key.empty()) {
        key = getIdentifier();
    }
    
    saveData(key, serialize(value));
    
	Request *request = new Request(this->getIdentifier(), PUT);
	request->addArg("key", key);
	request->addArg("value", serialize(value));
	// Send the Put request
	sendRequest(request, successor);
}

/* DHT Get */
string TextHandler::get(string key) {
	// Convert the key in a hash integer
	int iKey = stringToInt(key);
    if(iKey==0) {
        if(lastModifId!=0) {
            iKey = lastModifId;
        } else {
            return "";
        }
    }
	if (modifTree.find(iKey)!=modifTree.end()) {
        cout << "returning modif" << endl;
		// I have this modif
        stringstream ss;
        ss << modifTree[iKey];
		return ss.str();
	} else {
        cout << "sending request to successor" << endl;
		// Create a get request.
		Request *request = new Request(this->getIdentifier(), GET);
		request->addArg("key", key);
		// Send the get request
		return sendRequest(request, successor);
	}
}


/* data CRUD */
void TextHandler::saveData(string, string value) {
    cout << "saveData called with " << unserialize(value) << endl;
    try {
        value = unserialize(value);
        stringstream ss(value);
        Modification m;
        ss >> m;
        //~ int pos;
        //~ ss >> pos;
        //~ value.erase(0,value.find(" ")+1);
        //~ content.insert(pos,value);
        if(m.getPrevId()==lastModifId) {
            modifTree[m.getId()] = m;
            lastModifId = m.getId();
            m.applyTo(content);
        } else {
            int id = lastModifId;
            while(id!=0 && modifTree[id].getPrevId()!=m.getPrevId()) {
                id = modifTree[id].getPrevId();
            }
            if(id!=0) { // The modif was found
                if(id != m.getId()) { // we have an other modif at the same place
                    if (m.getTime() < modifTree[id].getTime()) { // we got the bad one
                        id = lastModifId;
                        while(modifTree[id].getPrevId()!=m.getPrevId()) { // cancel bad modifications
                            int prevId = modifTree[id].getPrevId();
                            modifTree[id].cancelOn(content);
                            modifTree.erase(id);
                            id = prevId;
                        }
                        modifTree[id].cancelOn(content);
                        modifTree.erase(id);
                        
                        modifTree[id] = m;
                        lastModifId = m.getId();
                    }
                }
            } else { // The modif was not found
                cout << "searching for " << m.getPrevId() << endl;
                stringstream ss;
                ss << m.getPrevId();
                saveData("",serialize(get(ss.str())));
                saveData("",value);
            }
        }
    } catch(std::out_of_range e) {
        cout << "out of range" << endl;
    }
}

string TextHandler::printStatus() {
    stringstream ss;
    ss << ChordNode::printStatus();
    ss << "Content : " << content << endl;
    ss << "Modif Tree : " << endl;
    for(std::map<int,Modification>::iterator it = modifTree.begin(); it != modifTree.end();++it) {
        ss << it->first << " : " << it->second << endl;
    }
    return ss.str();
}

//~ void updateNeeded() {
    //~ 
//~ }
