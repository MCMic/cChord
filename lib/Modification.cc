#include "Modification.hh"
#include "crypto/sha1.h"

using namespace std;

int Modification::nbModif = 0;

Modification::Modification(time_t t, std::string m, int pos, int oID, int bMI) {
    time = t;
    modification = m;
    position = pos;
    ownedID = oID;
    beforeModificationI = bMI;
    //~ afterModificationsI = aMI;
    //~ beforeModificationP = bMP;
    //~ afterModificationsP = aMP;
    identificateur = 0;
    stringstream ss;
    ss << *this;
    identificateur = getIntSHA1(ss.str());
}

void Modification::applyTo(string &s) {
    if(position >= s.size()) {
        s.append(modification);
    } else {
        s.insert(position, modification);
    }
}

void Modification::cancelOn(string& s) {
    s.erase(position,modification.size());
}
        
ostream& Modification::operator>>(ostream& flux) {
    flux << time << " ";
    flux << modification.size() << " ";
    flux << modification << " ";
    flux << position << " ";
    flux << identificateur << " ";
    flux << ownedID << " " << beforeModificationI;
    return flux;
}

istream& Modification::operator<<(istream& flux) {
    int taille;
    char* s;
    flux >> time;
    flux >> taille;
    s =  new char[taille];
    flux.get(); // ignore space
    flux.read(s, taille);
    modification = s;
    flux >> position;
    flux >> identificateur;
    flux >> ownedID;
    flux >> beforeModificationI;
    return flux;
}
