#ifndef BOX_H
#define BOX_H
#include "wcpplib/geometry/surface.h"
#include "wcpplib/geometry/volume.h"
/*
Copyright (c) 2000 Igor B. Smirnov

The file can be used, copied, modified, and distributed
according to the terms of GNU Lesser General Public License version 2.1
as published by the Free Software Foundation,
and provided that the above copyright notice, this permission notice,
and notices about any modifications of the original text
appear in all copies and in supporting documentation.
The file is provided "as is" without express or implied warranty.
*/

namespace Heed {

/// Box (three-dimensional rectangle/rectangular parallelogram).
/// The box is centred with respect to the centre of the coordinate system.

class box : public absvol {
 public:
  double m_dx, m_dy, m_dz;     ///< Lengths of sides
  double m_dxh, m_dyh, m_dzh;  ///< Half-lengths of sides
  ulsvolume m_ulsv;

 public:
  /// Default constructor.
  box();
  // Constructor, compute precision from mean of dimensions.
  box(double fdx, double fdy, double fdz);
  box(box& fb);
  box(const box& fb);
  /// Destructor
  virtual ~box() {}

  void init_prec();
  void init_planes();

  int check_point_inside(const point& fpt, const vec& dir) const override;

  /// Range till exit from given volume or to entry only.
  int range_ext(trajestep& fts, int s_ext) const override;
  void income(gparticle* gp) override;

 protected:
  absref_transmit get_components() override;
};

}  // namespace Heed
#endif
