#include <iostream>
#include "measurements.hpp"
#include <string>
#include <sstream>

namespace json_benchmarks {
    
class json_parsing_report_generator
{
private:
    const size_t max_text_length = 30;
    std::string title_;
    std::vector<result_code_info> result_code_info_;
    std::vector<library_info> library_info_;
    std::ostream* os_ptr_;
    std::vector<std::tuple<std::string,std::string,std::function<void(json_parsing_report_generator&)>>> generators_;
    size_t counter_;
public:

    json_parsing_report_generator(const std::string& title,
                                  const std::vector<result_code_info>& result_code_info,
                                  const std::vector<library_info>& library_info,
                                  std::ostream& os)
        : title_(title),
          result_code_info_(result_code_info), 
          library_info_(library_info),
          os_ptr_(std::addressof(os)),
          counter_(0)
    {
    }

    ~json_parsing_report_generator()
    {
    }

void insert_generator(const std::string& heading, std::function<void(json_parsing_report_generator&)> generator)
{
    std::ostringstream os;
    os << "a" << counter_;
    generators_.push_back(std::make_tuple(heading, os.str(),generator));
    ++counter_;
}

void generate()
{
    begin_report();
    for (auto& pr : generators_)
    {
(*os_ptr_) << "<div id=\"";
(*os_ptr_) << std::get<1>(pr);
(*os_ptr_) << "\">\n";

(*os_ptr_) << "<h2>";
(*os_ptr_) << std::get<0>(pr);
(*os_ptr_) << "</h2>" << std::endl;
        std::get<2>(pr)(*this);
(*os_ptr_) << "</div>\n";
    }
    end_report();
}

void insert_results(std::vector<test_suite_file>& pathnames,
                    const std::vector<std::vector<test_suite_result>>& results)
{
(*os_ptr_) << R"(
    <table>
    <tr>
      <th></th>
)";
for (const auto& lib : library_info_)
{
    (*os_ptr_) << "<th class=\"rotate\"><div><span>";
    (*os_ptr_) << lib.name << "-" << lib.version;
    (*os_ptr_) << "</span></div></th>\n"; 
}
(*os_ptr_) << R"(
    </tr>
)";

for (size_t i = 0; i < result_code_info_.size(); ++i)
{
    (*os_ptr_) << "<tr><td bgcolor=\"";
    (*os_ptr_) << result_code_info_[i].color << "\">";
    (*os_ptr_) << "<font color=\"white\">";
    (*os_ptr_) << result_code_info_[i].description << "</font></td>";
    for (size_t j = 0; j < results.size(); ++j)
    {
        size_t count = count_results(results[j],result_code_info_[i].code);
        (*os_ptr_) << "<td>" << count << "</td>\n";
    }
    (*os_ptr_) << "</tr>\n";
}

(*os_ptr_) << R"(
    </table>
)";
(*os_ptr_) << R"(
    </table>
    <table style="width:100%">
    <tr>
      <th></th>
)";
for (const auto& lib : library_info_)
{
    (*os_ptr_) << "<th class=\"rotate\"><div><span>";
    (*os_ptr_) << lib.name;
    (*os_ptr_) << "</span></div></th>\n"; 
}
(*os_ptr_) << R"(
      <th></th>
    </tr>
)";

for (size_t i = 0; i < pathnames.size(); ++i)
{
(*os_ptr_) << "<tr>\n";
(*os_ptr_) << "<td>";
(*os_ptr_) << pathnames[i].path.filename().string().c_str();
(*os_ptr_) << "</td>";
    for (size_t j = 0; j < results.size(); ++j)
    {
        result_code rc = results[j][i].result;
        auto it = std::find_if(result_code_info_.begin(),
                            result_code_info_.end(),
                  [rc](const result_code_info& a){return a.code == rc;});
        if (it != result_code_info_.end())
        {
            (*os_ptr_) << "<td bgcolor=\"";
            (*os_ptr_) << (*it).color;
            (*os_ptr_) << "\"></td>\n";
        }
    }
    size_t max_length = pathnames[i].text.length();
    if (max_length > max_text_length)
    {
        max_length = max_text_length;
    }
(*os_ptr_) << "<td>";
(*os_ptr_) << pathnames[i].text.substr(0,max_length);
if (max_length < pathnames[i].text.length())
{
    (*os_ptr_) << " ...";
}
(*os_ptr_) << "</td>\n";
(*os_ptr_) << "</tr>\n";
}

(*os_ptr_) << R"(
    </table>
)";

}

private:

void begin_report()
{
(*os_ptr_) << R"(
<!DOCTYPE html>
<html>
)";
(*os_ptr_) << R"(
    <head>
      <title>Parsing Tests</title>
      <style>
          th.rotate {
            height: 140px;
            white-space: nowrap;
          }

          th.rotate > div {
            transform: 
              translate(25px, 51px)
              rotate(315deg);
            width: 30px;
          }
          th.rotate > div > span {
            border-bottom: 1px solid #ccc;
            padding: 5px 10px;
      }
      </style>
          <script>
  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','https://www.google-analytics.com/analytics.js','ga');

  ga('create', 'UA-42023908-2', 'auto');
  ga('send', 'pageview');

</script>
    </head>
)";

(*os_ptr_) << R"(
    <body>
)";
(*os_ptr_) << "<h1>";
(*os_ptr_) << title_;
(*os_ptr_) << "</h1>" << std::endl;

    for (auto& pr : generators_)
    {
(*os_ptr_) << "<p><a href=\"#";
(*os_ptr_) << std::get<1>(pr);
(*os_ptr_) << "\">";
(*os_ptr_) << std::get<0>(pr);
(*os_ptr_) << "</a></p>\n";
    }
}

void end_report()
{
(*os_ptr_) << R"(
    </body>
</html>
)";
os_ptr_->flush();
}

};

}
