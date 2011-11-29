
#include "TextHandler.hh"

using namespace std;

TextHandler::TextHandler(string ip,int port) : ChordNode(ip,port,ip,"/tmp/"),chord(NULL) {
}

void TextHandler::connect(string ip,int port) {
    chord = new Node(ip, port);
    join(chord);
}

void TextHandler::insertText(int pos, string str) {
    stringstream ss;
    ss << pos << " " << str;
    put("",ss.str());
}

/* IOverlay Pure METHODS */
void TextHandler::put(string key, string value) {
    if(key == getIdentifier())
        return;
    
    saveData(key, value);
    
	Request *request = new Request(this->getIdentifier(), PUT);
	request->addArg("key", key);
	request->addArg("value", value);
	// Send the Put request
	sendRequest(request, successor);
}

/* data CRUD */
void TextHandler::saveData(string filename, string value) {
    stringstream ss(value);
    int pos;
    ss >> pos;
    content.insert(pos,ss.str());
}

void updateNeeded() {
    
}
