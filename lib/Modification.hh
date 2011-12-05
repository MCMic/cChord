#ifndef MODIFICATION_H_INCLUDED
#define MODIFICATION_H_INCLUDED

#include <string>
#include <vector>


class Modification {
    private:
        static int nbModif;
        time_t time;
        std::string modification;
        int position;
        int identificateur;
        int ownedID;
        int beforeModificationI;
        //~ Modification* beforeModificationP;
        //~ std::vector<int> afterModificationsI;
        //~ std::vector<Modification*> afterModificationsP;

    public:
        Modification(time_t t, std::string m, int pos, int oID, int bMI=0);

        //~ void addModification(Modification* m) {
            //~ if(afterModificationsI.size() > 0) {
                //~ if(m->getTime() >= afterModificationsP[0]->getTime()) {
                    //~ afterModificationsP[0]->addModification(m);
                //~ } else {
                    //~ Modification* after = afterModificationsP[0];
                    //~ Modification* before = afterModificationsP[0]->getPreviousP();
                    //~ removeModification(after, false);
                    //~ after->setAfterModificationI(*(new std::vector<int>));
                    //~ after->setAfterModificationP(*(new std::vector<Modification*>));
                    //~ after->setBeforeModificationI(0);
                    //~ after->setBeforeModificationP(NULL);
                    //~ before->addModification(m);
                    //~ m->addModification(after);
//~ 
                //~ }
            //~ }
            //~ else {
                //~ afterModificationsI.push_back(m->getIdentificateur());
                //~ afterModificationsP.push_back(m);
                //~ m->setBeforeModificationI(identificateur);
                //~ m->setBeforeModificationP(this);
            //~ }
        //~ }
//~ 
        //~ void removeModification(Modification* m, bool sup) {
            //~ m->getPreviousP()->setAfterModificationI(m->getNextI());
            //~ m->getPreviousP()->setAfterModificationP(m->getNextP());
            //~ for(int i = 0; i < m->getNextP().size(); i++) {
                //~ m->getNextP()[i]->setBeforeModificationI(m->getPreviousP()->getIdentificateur());
                //~ m->getNextP()[i]->setBeforeModificationP(m->getPreviousP());
            //~ }
            //~ if(sup) delete m;
        //~ }

        int getId() {
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

        int getPrevId() {
            return beforeModificationI;
        }
        
        void setBeforeModificationI(int i) {
            beforeModificationI = i;
        }

        //~ void setBeforeModificationP(Modification* m) {
            //~ beforeModificationP = m;
        //~ }
//~ 
        //~ void setAfterModificationI(std::vector<int> v) {
            //~ afterModificationsI = v;
        //~ }
//~ 
        //~ void setAfterModificationP(std::vector<Modification*> v) {
            //~ afterModificationsP = v;
        //~ }

        //~ Modification* getPreviousP() {
            //~ return beforeModificationP;
        //~ }
//~ 
        //~ std::vector<Modification*> getNextP() {
            //~ return afterModificationsP;
        //~ }
//~ 
        //~ std::vector<int> getNextI() {
            //~ return afterModificationsI;
        //~ }

        //~ std::string toString() {
            //~ std::string s = modification;
            //~ if(afterModificationsI.size() > 0) {
                //~ afterModificationsP[0]->toString(&s);
            //~ }
            //~ return s;
        //~ }
//~ 
        void applyTo(std::string&);
        
        void cancelOn(std::string&);
};

#endif // MODIFICATION_H_INCLUDED
