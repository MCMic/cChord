#include <iostream>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include "GtkTextHandler.hh"
#include <myMed/ProtocolSingleton.h>

using namespace std;

int main(int argc, char* argv[]) try
{
    if(argc<3) {
        cout << "usage : " << argv[0] << " myIp myPort [otherIp otherPort]" << endl;
        return EXIT_SUCCESS;
    }
    
	g_thread_init(NULL);
//	if(!Glib::thread_supported())
//		Glib::thread_init();

	// I would rather like to have Gtk::Main on the stack, but I see
	// no other chance to catch exceptions from the command line option
	// parsing. armin.
	Gtk::Main* kit;

	try
	{
		kit = new Gtk::Main(argc, argv);
	}
	catch(Glib::Exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
    
    GtkWidget* wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(wnd),800,600);
    gtk_window_set_title(GTK_WINDOW(wnd),"DistributedWord");
    GtkTextView *gtw = GTK_TEXT_VIEW(gtk_text_view_new());
    //~ wnd.add(GTK_WIDGET(gtw));
    
    
    GtkTextHandler* gth = new GtkTextHandler(argv[1], atoi(argv[2]));
    P_SINGLETON->setProtocolNode(gth);
    if(argc>4) {
        cout << "connecting to " << argv[3] << ":" << argv[4] << endl;
        gth->connect(argv[3], atoi(argv[4]));
        cout << gth->printStatus() << endl;
    }
    GtkTextBuffer* buffer = gth->get_buffer();
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(gtw), GTK_TEXT_BUFFER(buffer));
    
	gtk_container_add(GTK_CONTAINER(wnd), GTK_WIDGET(gtw));
    gtk_widget_show_all(wnd);
    g_signal_connect(wnd, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);

    
    kit->run();
    
	return 0;
}
catch(Glib::Exception& e)
{
	//~ handle_exception(e.what() );
    cout << "Exception 1 : " << e.what() << endl;
}
catch(std::exception& e)
{
	//~ handle_exception(e.what() );
    cout << "Exception 2 : " << e.what() << endl;
}
