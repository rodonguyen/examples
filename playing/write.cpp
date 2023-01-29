
#include <thread>
#include <sys/resource.h>     // For memory measurement
#include <fstream>            // For file write/read
#include <chrono>             // For time measurement
#include <sstream>            // For string formatting
// #include <format>             // For string formatting



using namespace std;

long get_mem_usage() {
  struct rusage myusage;
  getrusage(RUSAGE_SELF, &myusage);
  return myusage.ru_maxrss;
}

void addRecord(string line) {
   // Create and open a text file
   ofstream myrecord("record.csv", std::ios_base::app);

   // Write to the file
   myrecord << line;

   // Close the file
   myrecord.close();
}

void addRecord(std::chrono::_V2::system_clock::time_point timeStart, std::chrono::_V2::system_clock::time_point timeNow, long memory, string description) {
   // Create and open a text file
   ofstream myrecord("record.csv", std::ios_base::app);

   stringstream line;
   line << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(timeNow-timeStart).count()) << ", " << to_string(memory) << ", " << description << "\n";

   // Write to the file
   myrecord << line.str();

   // Close the file
   myrecord.close();
}


int main() {
   addRecord("time(s), memory(kB), description\n");
   auto time_00 = std::chrono::high_resolution_clock::now();
   long mem_usage_00 = get_mem_usage();
   stringstream line;

   std::this_thread::sleep_for(std::chrono::milliseconds(500));

   long mem_usage_01 = get_mem_usage();
   auto time_01 = std::chrono::high_resolution_clock::now();
   addRecord(time_00, time_01, mem_usage_01-mem_usage_00, "desp01");


   long mem_usage_02 = get_mem_usage();
   auto time_02 = std::chrono::high_resolution_clock::now();
   addRecord(time_00, time_02, mem_usage_02-mem_usage_00, "desp02");


   long mem_usage_03 = get_mem_usage();
   auto time_03 = std::chrono::high_resolution_clock::now();
   addRecord(time_00, time_03, mem_usage_03-mem_usage_00, "desp03");

   // line << "time01, " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(time_01-time_00).count()) << "ms\n";
   // addRecord(line.str());
   // printf( "time01: %ld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(time_01-time_00).count() );
   // printf( "time02: %ld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(time_02-time_00).count() );
   // printf( "time03: %ld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(time_03-time_00).count() );

   addRecord("\n\n");
} 