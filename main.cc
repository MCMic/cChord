using namespace std;

#include "lib/TextHandler.hh"
#include "lib/Modification.hh"
#include <stdlib.h>
#include <protocols/ProtocolSingleton.h>

// This application receives args, "ip", "port" [, "ip2", "port2"]
int main(int argc, char * const argv[]) {
    Modification m(time(NULL),"coucou",0,1);
    string s;
    m.applyTo(s);
    cout << "s : '" << s << "'" << endl;
    m.cancelOn(s);
    cout << "s : '" << s << "'" << endl;
    
    cout << m << endl;
    stringstream ss;
    ss << m;
    Modification m2;
    m2 << ss;
    cout << m2 << endl;
    
    
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
            << "3) Erase Test" << endl
            << "4) Exit" << endl
            /*<< "5) Cancel" << endl*/;
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
            case 3:
                cout << "pos = ";
                cin >> pos;
                cin >> value;
                th->insertText(pos, value, true);
                break;
            case 4:
                th->shutDown();
                quit = true;
                break;
            //case 5:
			//	th->;
			//	break;
            default:
            break;
        }       
    }
    delete th;
}
