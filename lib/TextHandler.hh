
#include "protocols/chord/ChordNode.h"
#include "lib/Modification.hh"

class TextHandler : public ChordNode {
    private:
        Node *chord;
        std::string myIp;
        
    protected:
        std::string content;
        
        std::map<int,Modification> modifTree;
        int lastModifId;
        //~ void updateNeeded();
        
        /* IOverlay Pure METHODS */
        void   put(string key, string value);
        string get(string);
        /* data CRUD */
        void saveData(string filename, string value);
    public:
        TextHandler(std::string,int);
        void eraseText(int, int);
        void insertText(int pos, std::string text, bool e = false);
        void connect(std::string,int);
        std::string getText() {return content;}
        string printStatus();
};
