#include "Bunny.h"
#include <thread>
#include <chrono>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

bool Bunny::on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& time)
{
  static double color = 0.0;
  for (int i = 0; i < 10; ++i)
  {
    // Red circle.
    cr->set_source_rgb(1.0, color, color);
    cr->arc(m_x + i * 0.04, m_y, radius, 0.0, 2 * M_PI);
    cr->fill_preserve();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  color += 1.0;
  return true;
}
