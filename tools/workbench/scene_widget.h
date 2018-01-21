#ifndef IPME_WB_SCENE_WIDGET_H
#define IPME_WB_SCENE_WIDGET_H

#include <vector>

#include <QOpenGLWidget>

#include "color.h"
#include "scene_object.h"

namespace ipme::wb {
class Scene_widget : public QOpenGLWidget {
public:
    Scene_widget(QWidget* widget);

    virtual void paintGL() override;

    inline void set_objects(const std::vector<Scene_object>& objects)
    {
        objects_ = objects;
    }

    void clear_objects();

    inline void set_colors(const std::vector<Color>& colors)
    {
        colors_ = colors;
    }

    inline void set_show_centerline(bool show)
    {
        show_centerline_ = show;
    }

    inline void set_show_tsegment(bool show)
    {
        show_tsegment_ = show;
    }

private:
    bool show_centerline_ = true;
    bool show_tsegment_ = false;

    std::vector<Scene_object> objects_;
    std::vector<Color> colors_{Color{.0f, .0f, .0f}};
};
} // namespace ipme::wb

#endif // IPME_WB_SCENE_WIDGET_H