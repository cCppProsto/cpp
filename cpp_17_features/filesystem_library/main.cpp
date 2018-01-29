#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>

using namespace std;

namespace fs = experimental::filesystem;

namespace  example_a
{
  void example()
  {
    auto cur_p = fs::current_path();
    cout << "current path - " << cur_p << endl;
    cout << endl;

    auto root_p = fs::path("/");
    auto space = fs::space(root_p);
    /* capacity  - total size of the filesystem, in bytes
       free      - free space on the filesystem, in bytes
       available - free space available to a non-privileged process
                   (may be equal or less than free) */
    cout << "Total     : " << space.capacity/1024/1024/1024 << "GB" << endl;
    cout << "Free      : " << space.free/1024/1024/1024 << "GB" << endl;
    cout << "Available : " << space.available/1024/1024/1024 << "GB" << endl;
    cout << endl;
  }
}

namespace  example_b
{
  void example()
  {
    fs::path aPath {"./path/to/file.txt"};

    cout << "Path to file: " << aPath << endl;
    cout << "Parent path : " << aPath.parent_path() << endl;
    cout << "Filename    : " << aPath.filename() << endl;
    cout << "Extension   : " << aPath.extension() << endl;
    cout << endl;

    cout << "Separator in my OS "  << fs::path::preferred_separator << endl;
    cout << endl;

    fs::path root{"/"};
    fs::path  dir{"dev/db"};
    fs::path   db{"database.db"};

    fs::path pathToDB = root / dir / db;
    cout << pathToDB << endl;
    cout << endl;
  }
}

namespace  example_c
{
  void example()
  {
    auto cur_p = fs::current_path();
    fs::create_directory("tmp");
    fs::create_directories(cur_p / "tmp/" / "a/");
    fs::create_directories(cur_p / "tmp/b");
    fs::create_directories(cur_p / "tmp/b" / "bb" / "bbb");
  }
}

namespace  example_d
{
  void example()
  {
    auto cur_p = fs::current_path();
    fs::remove(cur_p / "tmp/b" / "bb" / "bbb");
    fs::remove_all(cur_p / "tmp");
  }
}

namespace  example_e
{
  vector<string> getDirectoryFiles(const fs::path & dir, const vector<string> & ext)
  {
    vector<string> files;
    for(auto & p: fs::recursive_directory_iterator(dir))
    {
      if(fs::is_regular_file(p))
      {
        if (ext.empty()
            ||
            find(ext.begin(), ext.end(), p.path().extension().string()) != ext.end() )
          files.push_back(p.path().string());
      }
    }
    return files;
  }

  void example()
  {
    auto res_dir = fs::current_path();

    res_dir = res_dir / "res" / "pics";
    fs::create_directories(res_dir);

    vector<string> res_files =
    {
      "./res/pics/file.png",
      "./res/pics/file.jpg",
      "./res/pics/file.info"
    };

    for (auto &f: res_files)
      ofstream(f) << "data";

    auto print_files = [](const auto &aVector)
    {
      for (auto &f: aVector)
        cout << f << endl;
      cout << endl;
    };

    cout << "JPG filter" << endl;
    auto files = getDirectoryFiles(res_dir, {".jpg"});
    print_files(files);

    cout << "INFO filter" << endl;
    files = getDirectoryFiles(res_dir, {".info", ".jpg"});
    print_files(files);

    cout << "without filter" << endl;
    files = getDirectoryFiles(res_dir, {});
    print_files(files);
  }
}

namespace  example_f
{
  void example()
  {
    auto permission = [](fs::perms aPerm)
    {
      cout << ((aPerm & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
           << ((aPerm & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
           << ((aPerm & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
           << ((aPerm & fs::perms::group_read) != fs::perms::none ? "r" : "-")
           << ((aPerm & fs::perms::group_write) != fs::perms::none ? "w" : "-")
           << ((aPerm & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
           << ((aPerm & fs::perms::others_read) != fs::perms::none ? "r" : "-")
           << ((aPerm & fs::perms::others_write) != fs::perms::none ? "w" : "-")
           << ((aPerm & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
           << endl;
    };

    ofstream("file_test");

    cout << "Initial file permissions for a file: ";
    permission(fs::status("file_test").permissions());

    fs::permissions("file_test",
                      fs::perms::add_perms
                    | fs::perms::owner_all
                    | fs::perms::group_all);

    cout << "Adding all bits to owner and group:  ";
    permission(fs::status("file_test").permissions());

    fs::permissions("file_test",
                     fs::perms::remove_perms
                   | fs::perms::owner_write
                   | fs::perms::group_write
                   | fs::perms::others_write);

    cout << "Removing the write bits for all:     ";
    permission(fs::status("file_test").permissions());

    fs::remove("file_test");
  }
}

int main()
{
  example_a::example();
  example_b::example();
  example_c::example();
  example_d::example();
  example_e::example();
  example_f::example();

  return 0;
}
