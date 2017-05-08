#include "MyArea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

   Gtk::Window win;
   win.set_title("BUNNIES!");

   // Make window as large as our drawing area.
   win.set_size_request(MyArea::width, MyArea::height);
   win.set_resizable(false); 

   MyArea area;

   win.add(area);
   area.show();

   return app->run(win);
}
