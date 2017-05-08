#include "MyArea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

   Gtk::Window win;
   win.set_title("BUNNIES!");
   win.set_size_request(MyArea::width, MyArea::height);
   MyArea area;
   //bunny(200,200,1,false);
   win.add(area);
   win.set_resizable(false); 
   area.show();

   return app->run(win);
}
