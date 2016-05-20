#include <iostream>
#include <memory>
#include <rapidjson/document.h>
#include <fstream>

void runTestcase(rapidjson::Value& testcase);

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " <config-file>" << std::endl;
    return -1;
  }

  std::ifstream fs(argv[1]);
  std::string str((std::istreambuf_iterator<char>(fs)),
	          std::istreambuf_iterator<char>());

  rapidjson::Document doc;
  rapidjson::ParseResult check = doc.Parse<0>(str.c_str());

  if (check)
  {
    rapidjson::Value& testcases = doc["testcases"];
    for (rapidjson::SizeType i = 0; i < testcases.Size(); i++)
    {
      rapidjson::Value& testcase = testcases[i];
      runTestcase(testcase);
    }
  }
  else
  {
    std::cout << "Error parsing file!" << std::endl;
    getchar();
    return -1;
  }

  return 0;
}
