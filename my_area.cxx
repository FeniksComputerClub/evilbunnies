#include "sys.h"
#include "debug.h"
#include "MyArea.h"
#include "statefultask/AIEngine.h"
#include "statefultask/AIAuxiliaryThread.h"
#include <gtkmm.h>

bool on_idle()
{
  std::cout << "Calling gMainThreadEngine.mainloop()" << std::endl;
  gMainThreadEngine.mainloop();
  return true;
}

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

  AIAuxiliaryThread::start();

  MyArea area;
  for(int i=1;i<=3;++i)
  {
    boost::intrusive_ptr<Bunny> bunny = new Bunny(area);
    area.add_bunny(bunny);
    bunny->run();
  }

  win.add(area);
  area.show();
  
  //run statefultask's mainloop whenever idle
  Glib::signal_idle().connect( sigc::ptr_fun(&on_idle) );

  return app->run(win);
}
