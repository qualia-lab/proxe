#include "sage_element_container.h"

namespace ipme::wb::sage {
void Sage_element_container::add_element(const ipme::utils::Json& message)
{
    auto id = message.get("d.id");
    auto left = message.get<double>("d.left");
    auto top = message.get<double>("d.top");
    auto width = message.get<double>("d.width");
    auto height = message.get<double>("d.height");

    elements_.emplace(id, Sage_element{id, left, top, width, height});
}

void Sage_element_container::update_element(const std::string& id, double left,
                                            double top, double width,
                                            double height)
{
    auto itr = elements_.find(id.data());
    if(itr != std::end(elements_)) {
        itr->second.update(left, top, width, height);
    }
}

void Sage_element_container::delete_element(const std::string& id)
{
    auto itr = elements_.find(id);
    if(itr != std::end(elements_)) {
        elements_.erase(itr);
        std::cout << "[DELETE] " << id << "\n";
    }
}
} // namespace ipme::wb::sage
