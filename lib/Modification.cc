#include "Modification.hh"
#include "crypto/sha1.h"
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

int Modification::nbModif = 0;

Modification::Modification(time_t t, std::string m, int pos, int oID, int bMI, bool e) {
    time = t;
    modification = m;
    position = pos;
    ownedID = oID;
    beforeModificationI = bMI;
    erase = e;
    
    //~ afterModificationsI = aMI;
    //~ beforeModificationP = bMP;
    //~ afterModificationsP = aMP;
    stringstream ss;
    ss << pos << m << oID << bMI << t << e;
    
    string str = ss.str();
	SHA1 *sha1 = new SHA1();
	sha1->addBytes( str.c_str(), strlen( str.c_str() ));
	unsigned char* digest = sha1->getDigest();
	unsigned int res = sha1->shaToInteger(digest, 20, pow(2, 9));
	delete sha1;
	free( digest );
    
	identificateur = res;
}

void Modification::applyTo(string &s) {
	if(erase) {
		s.erase(position, modification.size());
	} else {
		if(position >= s.size()) {
			s.append(modification);
		} else {
			s.insert(position, modification);
		}
	}
}

void Modification::cancelOn(string& s) {
	if(erase) {
		if(position >= s.size()) {
			s.append(modification);
		} else {
			s.insert(position, modification);
		}
	} else {
		s.erase(position,modification.size());
	}
    
}
        
ostream& Modification::operator>>(ostream& flux) {
    flux << time << " ";
    flux << modification.size() << " ";
    flux << modification << " ";
    flux << position << " ";
    flux << identificateur << " ";
    flux << ownedID << " " << beforeModificationI << " ";
    flux << erase;
    return flux;
}

istream& Modification::operator<<(istream& flux) {
    int taille;
    char* s;
    flux >> time;
    flux >> taille;
    s = new char[taille+1];
    s[taille] = '\0';
    flux.get(); // ignore space
    flux.read(s, taille);
    modification = s;
    delete[] s;
    flux >> position;
    flux >> identificateur;
    flux >> ownedID;
    flux >> beforeModificationI;
    flux >> erase;
    return flux;
}
