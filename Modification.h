#ifndef MODIFICATION_H_INCLUDED
#define MODIFICATION_H_INCLUDED

#include <string>
#include <vector>

int nbModif = 0;

class Modification {
    private:
        time_t time;
        std::string modification;
        int position;
        int identificateur;
        int ownedID;
        int beforeModificationI;
        Modification* beforeModificationP;
        std::vector<int> afterModificationsI;
        std::vector<Modification*> afterModificationsP;

    public:
        Modification(time_t t, std::string m, int pos, int oID, int bMI, std::vector<int> aMI, Modification* bMP, std::vector<Modification*> aMP) {
            time = t;
            modification = m;
            position = pos;
            ownedID = oID;
            beforeModificationI = bMI;
            afterModificationsI = aMI;
            beforeModificationP = bMP;
            afterModificationsP = aMP;
            identificateur = ++nbModif;
        }

        Modification(time_t t, std::string s, int p, int id) {
            time = t;
            modification = s;
            position = p;
            ownedID = id;
            beforeModificationI = 0;
            afterModificationsI = *(new std::vector<int>);
            beforeModificationP = NULL;
            afterModificationsP = *(new std::vector<Modification *>);
            identificateur = ++nbModif;
        }

        void addModification(Modification* m) {
            if(afterModificationsI.size() > 0) {
                if(m->getTime() >= afterModificationsP[0]->getTime()) {
                    afterModificationsP[0]->addModification(m);
                } else {
                    Modification* after = afterModificationsP[0];
                    Modification* before = afterModificationsP[0]->getPreviousP();
                    removeModification(after, false);
                    after->setAfterModificationI(*(new std::vector<int>));
                    after->setAfterModificationP(*(new std::vector<Modification*>));
                    after->setBeforeModificationI(0);
                    after->setBeforeModificationP(NULL);
                    before->addModification(m);
                    m->addModification(after);

                }
            }
            else {
                afterModificationsI.push_back(m->getIdentificateur());
                afterModificationsP.push_back(m);
                m->setBeforeModificationI(identificateur);
                m->setBeforeModificationP(this);
            }
        }

        void removeModification(Modification* m, bool sup) {
            m->getPreviousP()->setAfterModificationI(m->getNextI());
            m->getPreviousP()->setAfterModificationP(m->getNextP());
            for(int i = 0; i < m->getNextP().size(); i++) {
                m->getNextP()[i]->setBeforeModificationI(m->getPreviousP()->getIdentificateur());
                m->getNextP()[i]->setBeforeModificationP(m->getPreviousP());
            }
            if(sup) delete m;
        }

        int getIdentificateur() {
            return identificateur;
        }

        int getPos() {
            return position;
        }

        int getSize() {
            return modification.size();
        }

        time_t getTime() {
            return time;
        }

        void setBeforeModificationI(int i) {
            beforeModificationI = i;
        }

        void setBeforeModificationP(Modification* m) {
            beforeModificationP = m;
        }

        void setAfterModificationI(std::vector<int> v) {
            afterModificationsI = v;
        }

        void setAfterModificationP(std::vector<Modification*> v) {
            afterModificationsP = v;
        }

        Modification* getPreviousP() {
            return beforeModificationP;
        }

        std::vector<Modification*> getNextP() {
            return afterModificationsP;
        }

        std::vector<int> getNextI() {
            return afterModificationsI;
        }

        std::string toString() {
            std::string s = modification;
            if(afterModificationsI.size() > 0) {
                afterModificationsP[0]->toString(&s);
            }
            return s;
        }

        void toString(std::string *s) {
            if(position >= s->size()) {
                s->append(modification);
            } else {
                s->insert(position, modification);
            }
            if(afterModificationsI.size() > 0) {
                afterModificationsP[0]->toString(s);
            }
        }

        /*std::string serialize() {
            std::string s;
            s += "[" + identificateur + "]";
            s += "time = " + time;
            s += "modification = " + modification;
            s += "position = " + position;
            s += "identificateur = " + identificateur;
            s += "ownerID = " + ownedID;
            s += "beforeModification = " + beforeModificationI;
            return s;
        }*/
        friend std::ostream& operator<<(std::ostream& flux, Modification& m) {
            m >> flux;
            return flux;
        }

        std::ostream& operator>>(std::ostream& flux) {
            flux << time << " " << modification.size() << " " << modification << " " << position << " " << identificateur << " " << ownedID << " " << beforeModificationI;
            return flux;
        }

        friend std::istream& operator>>(std::istream& flux, Modification& m) {
            return (m << flux);
        }

        std::istream& operator<<(std::istream& flux) {
            int taille;
            char* s;
            flux >> time;
            flux >> taille;
            s =  new char[taille];
            flux.read(s, taille);
            modification = s;
            flux >> position;
            flux >> identificateur;
            flux >> ownedID;
            flux >> beforeModificationI;
            return flux;
        }
};

#endif // MODIFICATION_H_INCLUDED
