#include "Modification.hh"

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
    identificateur = ++nbModif;
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
