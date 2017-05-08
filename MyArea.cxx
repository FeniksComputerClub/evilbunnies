#include "MyArea.h"
#include <cairomm/context.h>

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();

  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  cr->set_line_width(10.0);
  cr->set_line_cap(Cairo::LINE_CAP_ROUND);

  cr->move_to(xc, yc);
  cr->line_to(xc, yc);
  cr->stroke();

  return true;
}
