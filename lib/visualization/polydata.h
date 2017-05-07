#ifndef LIB_VISUALIZATION_POLYDATA_H
#define LIB_VISUALIZATION_POLYDATA_H

#include <boost/filesystem.hpp>
#include <memory>

#include <vtkPoints.h>

#include "data/point3d.h"

namespace cdi {
namespace visualization {
template <typename TPoint>
class Polydata {
  public:
    /**
     * @brief Polydata Constructor
     */
    Polydata();

    /**
     * @brief add_point inline function to add point
     * @param point to be added
     */
    inline void add_point(const TPoint& point)
    {
        points_->InsertNextPoint(point.x, point.y, point.z);
    }

    /**
     * @brief write_file function to output file
     * @param output_filename file name to write to
     */
    void write_file(const boost::filesystem::path& output_filename);

  private:
    vtkSmartPointer<vtkPoints> points_;
};
} // namespace visualization
} // namespace cdi

#include "polydata.ipp"

#endif // LIB_VISUALIZATION_POLYDATA_H
