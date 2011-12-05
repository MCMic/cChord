#ifndef MODIFICATION_H_INCLUDED
#define MODIFICATION_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>


class Modification {
    private:
        static int nbModif;
        time_t time;
        std::string modification;
        unsigned position;
        bool erase;
        int identificateur;
        int ownedID;
        int beforeModificationI;

    public:
        Modification(time_t t=0, std::string m="", int pos=0, int oID=0, int bMI=0, bool e=false);

		int getE() {
			return erase;
		}

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

        void applyTo(std::string&);
        
        void cancelOn(std::string&);
        
        friend std::ostream& operator<<(std::ostream& flux, Modification& m) {
            return (m >> flux);
        }

        std::ostream& operator>>(std::ostream& flux);

        friend std::istream& operator>>(std::istream& flux, Modification& m) {
            return (m << flux);
        }

        std::istream& operator<<(std::istream& flux);
};

#endif // MODIFICATION_H_INCLUDED
