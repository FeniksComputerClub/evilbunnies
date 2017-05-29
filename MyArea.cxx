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

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  // Save context.
  cr->save();

  // Move coordinate system to the center of the window.
  cr->scale(width, -height);
  cr->translate(0.0, -1.0);

  bool handled = m_bunny.on_draw(cr, clock_type::now());

  // Restore context.
  cr->restore();

  queue_draw();

  return handled;
}

int constexpr MyArea::width;
int constexpr MyArea::height;
