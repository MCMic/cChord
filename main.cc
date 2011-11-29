using namespace std;

#include "lib/TextHandler.hh"
#include <stdlib.h>
#include <myMed/ProtocolSingleton.h>

// This application receives args, "ip", "port" [, "ip2", "port2"]
int main(int argc, char * const argv[]) {
    if(argc<3) {
        cout << "usage : " << argv[0] << " myIp myPort [otherIp otherPort]" << endl;
        return EXIT_SUCCESS;
    }
        
    TextHandler *th = new TextHandler(argv[1], atoi(argv[2]));
    P_SINGLETON->setProtocolNode(th);
    if(argc>4) {
        cout << "connecting to " << argv[3] << ":" << argv[4] << endl;
        th->connect(argv[3], atoi(argv[4]));
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
                cout << th->printStatus();
                break;
            case 1:
                cout << "Pos = ";
                cin >> pos;
                cout << "Value = ";
                cin >> value;
                th->insertText(pos, value);
                break;
            case 2:
                cout << th->getText() << endl;
                break;
            //~ case 3:
                //~ cout << "Key = ";
                //~ cin >> key;
                //~ node->removekey(key);
                //~ break;
            case 4:
                th->shutDown();
                quit = true;
            default:
            break;
        }       
    }
    delete th;
}
