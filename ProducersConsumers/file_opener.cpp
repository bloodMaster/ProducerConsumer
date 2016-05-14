//
//

// user define
#include "file_opener.hpp"

// standard
#include <exception>

namespace  antel
{
    void file_opener::open()
    {
        assert( !m_filename.empty() );
        m_file.open(m_filename, std::fstream::trunc | std::fstream::out);
        if ( !m_file.is_open() ) {
            static const std::string msg("Impossible to open " + m_filename + " file! ");
            throw  std::ios_base::failure(msg);
        }
        assert( m_file.is_open() );
    }

    std::fstream &file_opener::get_file_handler()
    {
        assert(m_file.is_open());
        return m_file;
    }

}; // end antel namespace
