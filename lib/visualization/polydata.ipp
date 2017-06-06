#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkVersion.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataWriter.h>

#include <iostream>

namespace ipme {
namespace visualization {
template <typename TPoint>
Polydata<TPoint>::Polydata()
    : points_{vtkSmartPointer<vtkPoints>::New()},
      point_powers_{vtkSmartPointer<vtkDoubleArray>::New()},
      point_rasters_{vtkSmartPointer<vtkIntArray>::New()},
      indices_{vtkSmartPointer<vtkIntArray>::New()}
{
    if(data::Has_power<TPoint>::value) {
        point_powers_->SetNumberOfComponents(1);
        point_powers_->SetName("Power");
    }

    if(data::Has_raster<TPoint>::value) {
        point_rasters_->SetNumberOfComponents(1);
        point_rasters_->SetName("Raster");
    }

    indices_->SetNumberOfComponents(1);
    indices_->SetName("Index");
}

template <typename TPoint>
void Polydata<TPoint>::write_file(
    const boost::filesystem::path& output_filename)
{
    auto polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points_);

    auto filter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
    filter->AddInputData(polydata);
    filter->Update();
    polydata = filter->GetOutput();

    polydata->GetPointData()->AddArray(point_powers_);
    polydata->GetPointData()->AddArray(point_rasters_);
    polydata->GetPointData()->AddArray(indices_);

    auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName(output_filename.string().c_str());
    writer->SetInputData(polydata);

    writer->Write();
}

template <typename TPoint>
void Polydata<TPoint>::add_point(const TPoint& point)
{
    points_->InsertNextPoint(point.x, point.y, point.z);
    indices_->InsertNextValue(index_++);

    //    if(data::Has_raster<TPoint>::value) {
    //        // point_rasters_->InsertNextValue(point.raster);
    //    }

    //    if(data::Has_power<TPoint>::value) {
    //        // point_powers_->InsertNextValue(point.power);
    //    }

    //    if(data::Has_sourceid<TPoint>::value) {
    //        // point_sourceids_-InsertNextValue(point.power);
    //    }
}

} // namespace visualizaton
} // namespace ipme
