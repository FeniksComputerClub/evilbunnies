#include "Bunny.h"
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

bool Bunny::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  // Stroke 10 pixels wide.
  cr->set_line_width(10.0);
  cr->set_line_cap(Cairo::LINE_CAP_ROUND);

  // Red circle.
  cr->set_source_rgb(1.0, 0.0, 0.0);
  cr->arc(m_x, m_y, radius, 0.0, 2 * M_PI);
  cr->stroke();
}
