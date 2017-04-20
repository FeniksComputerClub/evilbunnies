#include "MyArea.h"
#include <cairomm/context.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  // Coordinates for the center of the window.
  double const xc = 0.5 * width;
  double const yc = 0.5 * height;

  // Save context.
  cr->save();

  double const line_width = 10.0;
  double const radius1 = (std::min(width, height) - line_width) / 2;
  double const radius2 = radius1 / 2;

  // Move coordinate system to the center of the window.
  cr->translate(xc, yc);

  // Stroke 10 pixels wide.
  cr->set_line_width(10.0);

  // Red circle.
  cr->set_source_rgb(1.0, 0.0, 0.0);
  cr->arc(0.0, 0.0, radius1, 0.0, 2 * M_PI);
  cr->stroke();

  // Blue circle.
  cr->set_source_rgb(0.0, 0.0, 1.0);
  cr->arc(radius2 - radius1, radius1 - radius2, radius2, 0.0, 2 * M_PI);
  cr->stroke();

  // Restore context.
  cr->restore();
  return true;
}

int const MyArea::width;
int const MyArea::height;
