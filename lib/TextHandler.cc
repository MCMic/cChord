
#include "TextHandler.hh"
#include <iostream>
#include <stdexcept>

using namespace std;

string intToString(int p) {
    stringstream ss;
    ss << p;
    return ss.str();
}

//~ TextHandler::TextHandler(string ip,int port) : ChordNode(ip,port,ip,"/tmp/"),chord(NULL) {
TextHandler::TextHandler(string ip,int port) : ChordNode(ip,port,ip+intToString(port),"/tmp/"),chord(NULL) {
    cout << "constructor called" << endl;
}

void TextHandler::connect(string ip,int port) {
    cout << "connect called" << endl;
    chord = new Node(ip, port);
    join(chord);
    
    Request *request = new Request(this->getIdentifier(), GET);
    request->addArg("key", "dummy_key");
    // Send the Put request
    content = sendRequest(request, successor);
}

void TextHandler::insertText(int pos, string str) {
    cout << "insertText called" << endl;
    Modification m(time(NULL),str,pos,0,lastModifId);
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
    
    saveData(key, value);
    
	Request *request = new Request(this->getIdentifier(), PUT);
	request->addArg("key", key);
	request->addArg("value", serialize(value));
	// Send the Put request
	sendRequest(request, successor);
}

/* DHT Get */
string TextHandler::get(string) {
	// Convert the key in a hash integer
	int iKey = intToString(key);
	if (modifTree.find(iKey)!=modifTree.end()) {
		// I have this modif
		return modifTree[iKey];
	} else {
		// Create a get request.
		Request *request = new Request(this->getIdentifier(), GET);
		request->addArg("key", key);
		// Send the get request
		return sendRequest(request, successor);
	}
}


/* data CRUD */
void TextHandler::saveData(string filename, string value) {
    cout << "saveData called" << endl;
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
            modifTree[m.getPrevId] = m;
            lastModifId = m.getId();
            m.applyTo(content);
        } else {
            int id = lastModifId;
            while(modifTree[id]!=m.getPrevId()) {
                id = modifTree[id].getPrevId();
                //FIXME : find what to do here
            }
        }
    } catch(std::out_of_range e) {
        cout << "out of range" << endl;
    }
}

//~ void updateNeeded() {
    //~ 
//~ }
