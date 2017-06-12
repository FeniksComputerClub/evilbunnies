#include "sys.h"
#include "MyArea.h"
#include "clock.h"
#include <iostream>
#include <cairomm/context.h>

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

void MyArea::add_bunny(boost::intrusive_ptr<Bunny>& bunny_to_add)
{
  m_bunnies.push_back(bunny_to_add);
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  // Save context.
  cr->save();

  // Move coordinate system to the center of the window.
  cr->scale(width, -height);
  cr->translate(0.0, -1.0);
  
  std::size_t handled = 0;
  for(boost::intrusive_ptr<Bunny> bunny_to_draw : m_bunnies)
  {
    handled += bunny_to_draw->on_draw(cr, clock_type::now());
  }
  std::cout << "drawn " << handled << " bunnies" << std::endl;
  // Restore context.
  cr->restore();

  return (handled == m_bunnies.size());
}

int constexpr MyArea::width;
int constexpr MyArea::height;
