#include "sys.h"
#include "debug.h"
#include "MyArea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
#ifdef DEBUGGLOBAL
  GlobalObjectManager::main_entered();
#endif
  Debug(NAMESPACE_DEBUG::init());

  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Gtk::Window win;
  win.set_title("BUNNIES!");

  // Make window as large as our drawing area.
  win.set_size_request(MyArea::width, MyArea::height);
  win.set_resizable(false);

  MyArea area;
  
  for(int i=1;i<=3;++i)
  {
    boost::intrusive_ptr<Bunny> bunny = new Bunny;
    area.add_bunny(bunny);
  }

  win.add(area);
  area.show();

  return app->run(win);
}
