#ifndef _FILESTACK_H_
#define _FILESTACK_H_

#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>


#ifdef DEBUG
#define DBG(x) (std::cerr << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << x << std::endl)
#else
#define DBG(x)
#endif


class FileStack {
    public:
        FileStack();
        FileStack(const std::string & file_name);
        FileStack(const std::string & file_name, int maximum_line_length);
        ~FileStack();

        size_t size();

        int pop(int & i);
        int pop(std::string & buf);
        int pop(std::string & buf, size_t & size_after_pop);

        int top(int & i);
        int top(std::string & buf);

        int push(int i);
        int push(std::string buf);
        int push(std::string buf, size_t & size_after_push);

        int get_max_line_length();
        int set_max_line_length(int n);

        int clear();

        int lock();
        int unlock();

        bool poll_query(const std::string & query, const double sleep_s=0.5, const size_t max_iter=7200);
        bool poll_size(const size_t size, const double sleep_s=0.5, const size_t max_iter=7200);

    private:
        int fd;
        bool locked;
        struct flock lck;
        std::string file_name;
        off_t max_line_length;

        int pop(std::string &, const bool, size_t &);
};

#endif
