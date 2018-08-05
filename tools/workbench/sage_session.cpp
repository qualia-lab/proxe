#include "sage_session.h"

#include "utils/logger.h"

namespace ipme {
namespace wb {
namespace websocket = boost::beast::websocket;

void fail(boost::system::error_code ec, char const* what)
{
    ERROR() << what << ": " << ec.message();
}

void Sage_session::run(const std::string& host, const std::string& port,
                       const std::string& text)
{
    host_ = host;
    text_ = text;

    resolver_.async_resolve(host.c_str(), port.c_str(),
                            std::bind(&Sage_session::on_resolve,
                                      shared_from_this(), std::placeholders::_1,
                                      std::placeholders::_2));
}

std::string Sage_session::read()
{
    ws_.async_read(buffer_,
                   std::bind(&Sage_session::on_read, shared_from_this(),
                             std::placeholders::_1, std::placeholders::_2));

    std::stringstream ss;
    ss << boost::beast::buffers(buffer_.data());
    return ss.str();
}

void Sage_session::write(const std::string& text)
{
    ws_.async_write(boost::asio::buffer(text_),
                    std::bind(&Sage_session::on_write, shared_from_this(),
                              std::placeholders::_1, std::placeholders::_2));
}

void Sage_session::close()
{
    ws_.async_close(websocket::close_code::normal,
                    std::bind(&Sage_session::on_close, shared_from_this(),
                              std::placeholders::_1));
}

void Sage_session::on_resolve(boost::system::error_code ec,
                              tcp::resolver::results_type results)
{
    if(ec) {
        return fail(ec, "resolve");
    }

    boost::asio::async_connect(ws_.next_layer(), results.begin(), results.end(),
                               std::bind(&Sage_session::on_connect,
                                         shared_from_this(),
                                         std::placeholders::_1));
}

void Sage_session::on_connect(boost::system::error_code ec)
{
    if(ec) {
        return fail(ec, "connect");
    }

    ws_.async_handshake(host_, "/",
                        std::bind(&Sage_session::on_handshake,
                                  shared_from_this(), std::placeholders::_1));
}

void Sage_session::on_handshake(boost::system::error_code ec)
{
    if(ec) {
        return fail(ec, "handshake");
    }

    DEBUG() << "handshake successful";
}

void Sage_session::on_write(boost::system::error_code ec,
                            std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec) {
        return fail(ec, "write");
    }

    DEBUG() << "Wrote " << bytes_transferred << " bytes";
}

void Sage_session::on_read(boost::system::error_code ec,
                           std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if(ec) {
        return fail(ec, "read");
    }

    DEBUG() << "Read " << bytes_transferred << " bytes";
}

void Sage_session::on_close(boost::system::error_code ec)
{
    if(ec) {
        return fail(ec, "close");
    }

    INFO() << "SAGE2 async connection closed";
    // INFO() << boost::beast::buffers(buffer_.data());
}

} // namespace wb
} // namespace ipme