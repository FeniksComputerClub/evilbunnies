﻿#include "sys.h"
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
  
  size_t handled = 0;
  std::vector<Pos> locations;
  for (boost::intrusive_ptr<Bunny> bunny_to_draw : m_bunnies)
  {
    handled += bunny_to_draw->on_draw(cr, clock_type::now());
    locations.push_back(bunny_to_draw->get_pos());
    bunny_to_draw->signal(1);
  }
  Dout(dc::notice, "Drawn " << handled << " bunnies.");

  cr->begin_new_path();
  cr->set_line_width(0.001);
  cr->set_dash(std::vector<double>(1, 0.004), 0.008);
  std::vector<Pos>::iterator pos1;
  std::vector<Pos>::iterator pos2;
  for (pos1 = locations.begin(); pos1 != locations.end() - 1; pos1++)
  {
    for (pos2 = locations.begin() + 1; pos2 != locations.end(); pos2++)
    {
      if (pos1 >= pos2)
        continue;
      cr->move_to(pos1->getx(), pos1->gety());
      cr->line_to(pos2->getx(), pos2->gety());
    }
  }
  cr->stroke();

  // Restore context.
  cr->restore();

  return handled == m_bunnies.size();
}

int constexpr MyArea::width;
int constexpr MyArea::height;
