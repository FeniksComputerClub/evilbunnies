#include "MyArea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

   Gtk::Window win;
   win.set_title("DrawingArea");
   win.set_size(800, 800);
   MyArea area;
   win.add(area);
   win.set_resizable(false); 
   area.show();

   return app->run(win);
}
