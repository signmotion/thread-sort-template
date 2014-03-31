#include <vector>
#include <boost/assign.hpp>
#include <boost/thread.hpp>




typedef std::vector< std::pair< int, int > >  container_t;


template< class F > 
inline void performTest(
    size_t*  current,
    size_t   numTests,
    void( *func )( typename F, typename F ),
    container_t*  result
) {
    std::cout << "invoked thread function" << std::endl;
}



namespace Sort {
    template< class RandomAccessIterator >
    void quick( RandomAccessIterator begin, RandomAccessIterator end ) {
        std::cout << "invoked sort function" << std::endl;
    }

} // Sort




/**
* Пример использования шаблонов для передачи в потоки.
*
* @source http://stackoverflow.com/questions/4064852/boostthread-and-template-functions
*/
int main( int argc, char** argv ) {

    setlocale( LC_ALL, "Russian" );
    setlocale( LC_NUMERIC, "C" );


    const size_t count =
        (argc > 1) ? std::atoi( argv[ 1 ] ) : 10;

    std::cout <<
        "Демонстарция работы потоков с шаблонами."
        "\n\nКоманда для запуска\t"
        "\n    thread-sort-template [count]"
        "\nгде"
        "\n    count     количество потоков"
        "\n"
        "\nЗапущено потоков\t" << count <<
        std::endl << std::endl;


    container_t  result = boost::assign::map_list_of
        ( 1, 2 )
        ( 3, 4 )
        ( 5, 6 )
        ( 7, 8 )
        ( 9, 10 )
    ;
    size_t current = 0;
    const size_t numTests = 30;

    boost::thread  th(
        &performTest< container_t::iterator >,
        &current,
        numTests,
        Sort::quick< container_t::iterator >,
        &result
    );
    th.join();
 


    std::cout << "\n^\n";
    std::cin.ignore();
}
