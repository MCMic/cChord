#include "lib/TextHandler.hh"
#include <gtkmm/textbuffer.h>

class GtkTextHandler : public TextHandler {
public:
	typedef sigc::signal<void, unsigned, const std::string>
		signal_insert_type;

	GtkTextHandler(std::string,int);
	~GtkTextHandler();
    
	GtkTextBuffer* get_buffer() const;
protected:
    void saveData(string s, string value);
	
    void on_insert_before(const Gtk::TextIter& iter,
	                      const Glib::ustring& text);
	void on_insert_after(const Gtk::TextIter& iter,
	                     const Glib::ustring& text);
    void on_erase_before(const Gtk::TextIter& begin,
                         const Gtk::TextIter& end);
	GtkTextBuffer* m_buffer;
	Gtk::TextIter m_iter;
	GtkTextMark mark;
    
    bool m_editing;
};
