#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <locale>

using boost::asio::ip::tcp;

int main() {
    setlocale(LC_ALL, "");

    try {
        boost::asio::io_context io;

        tcp::resolver reshaatel(io);
        tcp::socket klient_socket(io);

        auto konechnaya_tochka = reshaatel.resolve("127.0.0.1", "12347");
        boost::asio::connect(klient_socket, konechnaya_tochka);

        std::cout << "[Клиент] Соединение установлено с сервером.\n";

        std::string zapros = "status\n";
        boost::asio::write(klient_socket, boost::asio::buffer(zapros));
        std::cout << "[Клиент] Отправлено: " << zapros;

        boost::asio::streambuf otvet_buf;
        boost::asio::read_until(klient_socket, otvet_buf, '\n');

        std::istream otvet_stream(&otvet_buf);
        std::string otvet;
        std::getline(otvet_stream, otvet);

        std::cout << "[Клиент] Ответ от сервера: " << otvet << std::endl;
    }
    catch (std::exception& ex) {
        std::cerr << "[Клиент] Ошибка: " << ex.what() << std::endl;
    }

    return 0;
}
