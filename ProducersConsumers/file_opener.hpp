//
//

#ifndef ANTEL_FILE_OPENER_HPP
#define ANTEL_FILE_OPENER_HPP

// user define

// standard
#include <fstream>
#include <cassert>

namespace  antel
{
    class file_opener;
};

namespace  antel {

    class file_opener
    {
    public:
        file_opener(const std::string &filename)
                : m_filename(filename)
        {
            assert(!filename.empty());
        }

        ~file_opener()
        {
            m_file.close();
        }

    public:
        /// @brief open empty file, or if
        /// already has data, remove content
        /// @exception may throw exception
        ///  in case of unsuccessfully file creation/open
        void open();

        /// @brief get file handler
        /// @return file handler
        /// @note need to change letter
        std::fstream &get_file_handler();

    private:
        std::string m_filename;
        std::fstream m_file;
    };

}// end namespace antel





#endif //ANTEL_FILE_OPENER_HPP
