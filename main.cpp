#include <cpr/cpr.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
long long tries = 0;
long long counter = 0;
const std::string GOOGLE_ABUSE_EXEMPTION =
    "ID=cc893ad4a4ca091f:TM=1650900117:C=r:IP=2402:800:6384:1748:9fc5:a5b:9fec:"
    "ca8c-:S=g4OchLCJFiJ1re2wTRXSzR8";

std::string cookie = "";
void sub() {
  const auto thread_id = std::this_thread::get_id();
  auto myid = thread_id;
  std::stringstream ss;
  ss << myid;
  std::string str_thread_id = ss.str();
  const std::string INFO_PREFIX = "[INFO:" + str_thread_id + "] ";
  const std::string WARN_PREFIX = "[WARN:" + str_thread_id + "] ";
  cpr::Response r = cpr::Post(
      cpr::Url{"https://docs.google.com/forms/d/e/"
               "1FAIpQLScpkNZWZUUTZVpo11HqBQvXjt6KLtVBffAfJRGxDh0C3ovcsQ/"
               "formResponse"},
      cpr::Header{
          {"Content-Type", "application/x-www-form-urlencoded"},
          {"User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:100.0) "
                         "Gecko/20100101 Firefox/100"},
          {"Cookie", cookie},
      },

      cpr::Payload{{
                       "entry.1452884723",
                       "#storyofTDNer",
                   },
                   {"entry.2087055325", "."}});
  // std::cout << r.h] << std::endl;
  // for (auto &i : r.header) {
  // std::cout << i.first << ": " << i.second << std::endl;
  //}
  // std::cout << r.text << std::endl;
  std::cout << "\n";
  std::string text = r.text;
  // Write text to index.html
  std::ofstream myfile;
  myfile.open("index.html", std::ios::trunc);
  myfile << text;
  myfile.close();

  // tries++;
  if (text.find("Gửi phản hồi khác") != std::string::npos) {
    counter++;
    std::cout << INFO_PREFIX << "Successfully submitted form\n"
              << INFO_PREFIX << "Response: " << r.status_code << "\n"
              << INFO_PREFIX << "Count: " << counter << "\n";
  } else {
    std::cout << WARN_PREFIX << "Failed to submit form\n"
              << WARN_PREFIX << "Response: " << r.status_code << "\n"
              << INFO_PREFIX << "Count: " << counter << "\n";
  }
}
void loopedForm() {
  while (true) {
    sub();
    // Wait for 1 second
    // std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
int main(int argc, char *argv[]) {

  // THe first argument is the cookie string to use
  if (argc > 1) {
    cookie = argv[1];
  }
  sub();
  const int THREADS = 10;
  std::vector<std::thread> threads;
  for (int i = 0; i < THREADS; i++) {
    threads.emplace_back(loopedForm);
  }
  for (auto &t : threads) {
    t.join();
  }

  return 0;
}
