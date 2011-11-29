
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
    stringstream ss;
    ss << pos << " " << str;
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
	return content;
}


/* data CRUD */
void TextHandler::saveData(string filename, string value) {
    cout << "saveData called" << endl;
    try {
        value = unserialize(value);
        stringstream ss(value);
        int pos;
        ss >> pos;
        value.erase(0,value.find(" ")+1);
        content.insert(pos,value);
    } catch(std::out_of_range e) {
        cout << "out of range" << endl;
    }
}

void updateNeeded() {
    
}
