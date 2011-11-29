
#include "TextHandler.hh"
#include <iostream>

using namespace std;

//~ TextHandler::TextHandler(string ip,int port) : ChordNode(ip,port,ip,"/tmp/"),chord(NULL) {
TextHandler::TextHandler(string ip,int port) : ChordNode(ip,port,"chordTestBed","/tmp/"),chord(NULL) {
    cout << "constructor called" << endl;
}

void TextHandler::connect(string ip,int port) {
    cout << "connect called" << endl;
    chord = new Node(ip, port);
    join(chord);
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

/* data CRUD */
void TextHandler::saveData(string filename, string value) {
    cout << "saveData called" << endl;
    value = unserialize(value);
    stringstream ss(value);
    int pos;
    ss >> pos;
    value.erase(0,value.find(" ")+1);
    content.insert(pos,value);
}

void updateNeeded() {
    
}