#ifndef IPME_WB_CONFIG_H
#define IPME_WB_CONFIG_H

#include <filesystem>
#include <string>
#include <unordered_map>

#include "protobuf/scene.pb.h"
#include "utils/json.h"

namespace ipme::wb {
class Config {
public:
    struct Sage_config {
        std::string id;
        std::string host;
        unsigned short port;
        std::string session_token;
        ipme::scene::Position offset;
        ipme::scene::Size_2d dimensions;
        ipme::scene::Vector_3d normal_vector;

        static Sage_config create(const boost::property_tree::ptree& sage_node);
    };

    const std::vector<Sage_config>& sage_configs() const
    {
        return sage_config_;
    }

    inline Config(const std::filesystem::path& path)
    {
        parse_config(path);
    }

    inline std::string vrpn_host() const
    {
        return vrpn_host_;
    }

    inline short vrpn_port() const
    {
        return vrpn_port_;
    }

    inline short vrpn_data_port() const
    {
        return vrpn_data_port_;
    }

    //    inline std::string sage_host() const
    //    {
    //        return sage_host_;
    //    }

    //    inline short sage_port() const
    //    {
    //        return sage_port_;
    //    }

    //    inline std::string sage_session_token() const
    //    {
    //        return sage_session_token_;
    //    }

    inline int video_device_index() const
    {
        return video_device_index_;
    }

    inline bool vrpn_on() const
    {
        return vrpn_on_;
    }

    inline bool sage_on() const
    {
        return sage_on_;
    }

    inline bool video_on() const
    {
        return video_on_;
    }

    const scene::Scene_config& scene_config() const
    {
        return scene_config_;
    }

    //    inline double offset_x(uint32_t id) const
    //    {
    //        return display_map_.at(id).offset().x();
    //    }

    //    inline double offset_y(uint32_t id) const
    //    {
    //        return display_map_.at(id).offset().y();
    //    }

    //    inline double offset_z(uint32_t id) const
    //    {
    //        return display_map_.at(id).offset().z();
    //    }

    //    void set_screen_offset(double x, double y, double z);

    void set_vrpn_host(const std::string& host);
    void set_vrpn_port(unsigned short port);
    void set_vrpn_data_port(unsigned short port);

    void set_sage_host(const std::string& host);
    void set_sage_port(unsigned short port);
    void set_sage_session_token(std::string_view token);

    void set_video_device_index(int index);

    std::string to_string() const;

private:
    void parse_config(const std::filesystem::path& path);

    void create_default_config();

    scene::Scene_config scene_config_;
    utils::Json json_;

    std::string vrpn_host_ = "thor.evl.uic.edu";
    unsigned short vrpn_port_ = 28000;
    unsigned short vrpn_data_port_ = 7000;

    std::string sage_host_ = "localhost";
    unsigned short sage_port_ = 9292;
    std::string sage_session_token_ = "";

    int video_device_index_ = 0;

    bool vrpn_on_ = true;
    bool sage_on_ = true;
    bool video_on_ = true;

    std::unordered_map<uint32_t, ipme::scene::Display> display_map_;

    std::vector<Sage_config> sage_config_;
};

} // namespace ipme::wb
#endif // IPME_WB_CONFIG_H
