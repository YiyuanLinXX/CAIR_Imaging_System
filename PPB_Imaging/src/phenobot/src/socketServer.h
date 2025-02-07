//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <deque>
#include <boost/asio.hpp>

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

using boost::asio::ip::tcp;

typedef std::deque<std::string> msg_queue;

class session
  : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket, boost::shared_ptr<msg_queue> msgs_recv, boost::shared_ptr<msg_queue> msgs_send)
        : socket_(std::move(socket)),
            msgs_recv_(msgs_recv),
            msgs_send_(msgs_send)
    {
    }

    ~session(){
        writter_running_ = false;
    }

    void start()
    {
        auto self(shared_from_this());
        do_read_header();
        // start a thread to keep writing
        writter_running_ = true;
        do_write();
        //writter_thread_ = boost::thread(boost::bind(&session::do_write, self));
    }

private:
    void do_read_header()
    {
        auto self(shared_from_this());
        std::cout<<"wait reading"<<std::endl;
        socket_.async_read_some(boost::asio::buffer(data_, header_length),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    char header[header_length + 1] = "";
                    strncat(header, data_, header_length);
                    body_length_ = atoi(header);
                    //std::cout<<"read header, body length: "<<body_length_<<std::endl;
                    if (body_length_ > max_length)
                    {
                        body_length_ = 0;
                    }
                    do_read_body();
                }
                else{
                    std::cout<<"read header err/ disconnected:"<<std::endl;
                    writter_running_ = false;
                    return;
                }
            });
    }

    void do_read_body()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, body_length_),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    //std::cout<<"received body: "<<std::string(data_, body_length_)<<std::endl;
                    mutex_.lock();
                    msgs_recv_->push_back(std::string(data_, body_length_));
                    mutex_.unlock();
                    do_read_header();
                }
                else{
                    std::cout<<"read body err code:"<<ec<<std::endl;
                    writter_running_ = false;
                    return;
                }
            });
    }

    void do_write()
    {
        // Loop to wait for writting
        while(msgs_send_->size()==0 && writter_running_)
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if(!writter_running_){
            std::cout<<"writter thread stoped"<<std::endl;
            return;
        }

        auto self(shared_from_this());
        std::cout<<"wait writting"<<std::endl;

        

        std::string msg = msgs_send_->front();
        msgs_send_->pop_front();
        std::cout<<"Send message size:"<<msg.length()<<std::endl;
        boost::asio::async_write(socket_, boost::asio::buffer(msg.data(), msg.length()),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
            {
                if (!ec)
                {
                    do_write();
                }
            });
    }

    tcp::socket socket_;
    enum { max_length = 2048, header_length = 8 };
    int body_length_ = 0;
    char data_[max_length];

    // shared queues. Will be monitored in other processing threads
    boost::shared_ptr<msg_queue> msgs_recv_;    // The msgs_received
    boost::shared_ptr<msg_queue> msgs_send_;       // The msgs to send

    bool writter_running_ = false;
    //boost::thread writter_thread_;
    boost::mutex mutex_;
};

class server
{
public:
    server(boost::asio::io_service& io_service, short port)
        : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        socket_(io_service),
        io_service_(io_service)
    {}

    ~server(){stop();}

    // Main entry, set the shared msg queue, and start accepting connection
    void run(msg_queue& msgRecv, msg_queue& msgSend)
    {
        std::cout<<"TCP server start"<<std::endl;
        working_ = true;
        ptr_msgs_recv_.reset(&msgRecv);
        ptr_msgs_send_.reset(&msgSend);
        
        do_accept();
        worker_thread1_ = boost::thread(boost::bind(&boost::asio::io_service::run, &io_service_));
        worker_thread2_ = boost::thread(boost::bind(&boost::asio::io_service::run, &io_service_));
        //while(1)
        //{
        //    boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
        //}
    }

    // Stop operations
    void stop()
    {
        std::cout<<"Stopping server threads"<<std::endl;
        if(working_){
            working_ = false;
            io_service_.stop();
            worker_thread1_.join();
            std::cout<<"server thread 1 stopped"<<std::endl;
            worker_thread2_.join();
            std::cout<<"server thread 2 stopped"<<std::endl;
        }
        std::cout<<"server thread stopped"<<std::endl;
    }

    bool isWorking(){return working_;}

private:
    // Start accepting connections. If connection established, run a section, and wait for new connections
    void do_accept()
    {
        acceptor_.async_accept(socket_,
            [this](boost::system::error_code ec)
            {
                std::cout<<"new accept:"<<boost::lexical_cast<std::string>(socket_.remote_endpoint())<<std::endl;
                if (!ec)
                {
                    std::make_shared<session>(std::move(socket_), ptr_msgs_recv_, ptr_msgs_send_)->start();
                }
                if(working_)
                    do_accept();
            });
    }

    // Two threads ensure two handles can be executed concurretly
    boost::thread worker_thread1_;
    boost::thread worker_thread2_;

    tcp::acceptor acceptor_;
    tcp::socket socket_;

    // shared queues. Will be monitored in other processing threads
    boost::shared_ptr<msg_queue> ptr_msgs_recv_;
    boost::shared_ptr<msg_queue> ptr_msgs_send_;

    
    boost::asio::io_service& io_service_;

    bool working_ = false;
};

