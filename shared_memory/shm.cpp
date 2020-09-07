#include <boost/interprocess/shared_memory_object.hpp>

int main() {

using namespace boost::interprocess;
shared_memory_object shm_obj
   (create_only                  //only create
   ,"shared_memory"              //name
   ,read_write                   //read-write mode
   );

}
