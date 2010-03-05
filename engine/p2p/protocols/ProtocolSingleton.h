/*
 *  ProtocolSingleton.h
 *  P2P_Engine
 *
 *  Created by Nicolas Goles on 2/9/10.
 *  Copyright 2010 INRIA Lognet. All rights reserved.
 *
 */

#define P_SINGLETON ProtocolSingleton::getInstance()

#ifndef PROTOCOL_SINGLETON_H
#define PROTOCOL_SINGLETON_H

#include "ChordNode.h"
#include <string>

class ProtocolSingleton
{
public:
	//To obtain the singleton instance.
	static ProtocolSingleton* getInstance();
	
	//Destructor.
	~ProtocolSingleton();

	//Action methods.
	void		initChordNode(const string &ip, int port, const string &networkName);
	void		initChordNode(const string &ip, int port, const string &s, unsigned int nid);
	void		stopChord();
	
	//Getters & setters.
	void		setProtocolNode(ChordNode *n) { myNode = n ;}
	ChordNode*	getChordNode() { return myNode; }
	
protected:
	ProtocolSingleton();
	
private:
	ChordNode *myNode;					//This could be more generic ( ChordNode* is hard coded. )
	static ProtocolSingleton *instance;	//The singleton instance of the protocol container.
};

#endif