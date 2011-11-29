
#include "protocols/chord/ChordNode.h"

class TextHandler : public ChordNode {
    private:
        Node *chord;
        std::string myIp;
        
        std::string content;
        
    protected:
        void updateNeeded();
        
        /* IOverlay Pure METHODS */
        void   put(string key, string value);
        string get(string);
        /* data CRUD */
        void saveData(string filename, string value);
    public:
        TextHandler(std::string,int);
        void insertText(int pos, std::string text);
        void connect(std::string,int);
        std::string getText() {return content;}
};
