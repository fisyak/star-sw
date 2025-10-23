#ifndef FIELDMAP_H
#define FIELDMAP_H

namespace Heed {

class vec;
class point;

/// Retrieve electric and magnetic field.
class fieldmap {
 public:
  fieldmap() = default;
  virtual ~fieldmap() = default;
  fieldmap(const fieldmap&) = delete;
  fieldmap(fieldmap&&) = delete;
  fieldmap& operator=(fieldmap&&) = default;
  fieldmap& operator=(const fieldmap&) = delete;
  virtual void evaluate(const point& /*pt*/, vec& efield, vec& bfield,
                        double& mrange) const = 0;
  virtual bool inside(const point& /*pt*/) const = 0;
};

}  // namespace Heed
#endif
