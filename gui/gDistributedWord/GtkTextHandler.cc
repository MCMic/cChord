#include "GtkTextHandler.hh"
	
std::size_t diff_bytes(const Gtk::TextIter& begin,
                       const Gtk::TextIter& end)
{
    std::size_t bytes = 0;
    Gtk::TextIter iter = begin;

    while(iter != end)
    {
        std::size_t line_bytes;
        if(iter.get_line() == end.get_line() )
        {
            line_bytes =
                end.get_line_index() -
                iter.get_line_index();

            iter = end;
        }
        else
        {
            line_bytes =
                iter.get_bytes_in_line() -
                iter.get_line_index();

            iter.forward_line();
        }

        bytes += line_bytes;
    }

    return bytes;
}
    
GtkTextHandler::GtkTextHandler(string ip, int port) : TextHandler(ip,port),m_buffer(gtk_text_buffer_new(NULL)),
    m_editing(false)
{
    Glib::RefPtr<Gtk::TextBuffer> cpp_buffer = Glib::wrap(GTK_TEXT_BUFFER(m_buffer), TRUE);
	
    cpp_buffer->signal_insert().connect(
		sigc::hide(sigc::mem_fun(*this, &GtkTextHandler::on_insert_before)),
		false
	);

	cpp_buffer->signal_insert().connect(
		sigc::hide(sigc::mem_fun(*this, &GtkTextHandler::on_insert_after)),
		true
	);
}

GtkTextBuffer* GtkTextHandler::get_buffer() const {
    return m_buffer;
}

void GtkTextHandler::on_insert_before(const Gtk::TextIter& iter,
                                       const Glib::ustring& text)
{
	// Only local edits that are not done via insert
	if(m_editing) return;
	//~ editor edit(m_editing);
    m_editing = true;

	Glib::RefPtr<Gtk::TextBuffer> cpp_buffer = Glib::wrap(GTK_TEXT_BUFFER(m_buffer), true);
	//~ m_signal_local_insert.emit(diff_bytes(cpp_buffer->begin(), iter), text);
    int pos = diff_bytes(cpp_buffer->begin(), iter);
	cout << pos << "," <<  text << endl;
    insertText(pos,text);
    m_editing = false;
}

void GtkTextHandler::on_insert_after(const Gtk::TextIter& iter,
                                      const Glib::ustring& text)
{
	if(m_editing) return;
	//~ editor edit(m_editing);
    m_editing = true;
	
	mark =  *gtk_text_buffer_get_mark(m_buffer, "insert");
	
	//~ Gtk::TextIter begin = iter;
	//~ begin.backward_chars(text.length() );
    gtk_text_buffer_set_text(m_buffer,content.c_str(),-1); // modifie le buffer, donc lance un signal, qu'on catch , …
    gtk_text_buffer_get_iter_at_mark(m_buffer, m_iter.gobj(), &mark);
    gtk_text_buffer_place_cursor(m_buffer, m_iter.gobj());
	//~ tag_text(begin, iter, &m_self)
	//gtk_text_iter_backward_cursor_positions(m_iter.gobj(), 1);
    m_editing = false;
}

void GtkTextHandler::saveData(string s, string value) {
    TextHandler::saveData(s, value);
    
    m_editing = true;
    gtk_text_buffer_set_text(m_buffer,content.c_str(),-1); // modifie le buffer, donc lance un signal, qu'on catch , …
    m_editing = false;
}
