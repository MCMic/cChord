using namespace std;

#include "lib/TextHandler.hh"
#include <stdlib.h>

// This application receives args, "ip", "port", "overlay identifier (unique string)", "root directory)"
int main(int argc, char * const argv[]) {
    TextHandler th(string(argv[1]), atoi(argv[2]));
    if(argc>3) {
        th.connect(string(argv[3]), atoi(argv[4]));
    }
    
    int chx;
    bool quit = false;
    int pos;
    string value;
    
    while (!quit) { // sleep...
        cout << "0) Print status" << endl
            << "1) Insert Text" << endl
            << "2) Display Text" << endl
            << "4) Exit" << endl;
        cout << "---> ";
        cin >> chx;

        switch (chx) {
            case 0:
                cout << th.printStatus();
                break;
            case 1:
                cout << "Pos = ";
                cin >> pos;
                cout << "Value = ";
                cin >> value;
                th.insertText(pos, value);
                break;
            case 2:
                cout << th.getText() << endl;
                break;
            //~ case 3:
                //~ cout << "Key = ";
                //~ cin >> key;
                //~ node->removekey(key);
                //~ break;
            case 4:
                th.shutDown();
                quit = true;
            default:
            break;
        }       
    }
}
