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

  // Save context.
  cr->save();

  // Move coordinate system to the center of the window.
  cr->scale(width, height);
  cr->translate(0.5, 0.5);

  bool handled = m_bunny.on_draw(cr);

  // Restore context.
  cr->restore();

  return handled;
}

int constexpr MyArea::width;
int constexpr MyArea::height;
