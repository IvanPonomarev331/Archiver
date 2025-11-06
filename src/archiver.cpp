#include "include.h"
#include "encoder.h"
#include "decoder.h"
#include "writer.h"

std::unordered_map<std::string, std::vector<std::string> > CheckValid(const std::vector<std::string> &args) {
    if (args.empty()) {
        exit(EXIT_CODE);
    }
    if (args[0] != "-d" && args[0] != "-c" && args[0] != "-h") {
        exit(EXIT_CODE);
    }
    if (args[0] == "-h" && args.size() != 1) {
        exit(EXIT_CODE);
    }
    if (args[0] == "-c" && args.size() < 3) {
        exit(EXIT_CODE);
    }
    if (args[0] == "-d" && args.size() < 2) {
        exit(EXIT_CODE);
    }

    std::unordered_map<std::string, std::vector<std::string> > command;
    command["type"].push_back(args[0]);
    if (command["type"].front() == "-d") {
        command["archive_name"].push_back(args[1]);
    } else if (command["type"].front() == "-c") {
        command["archive_name"].push_back(args[1]);
        for (int i = 2; i < args.size(); ++i) {
            command["files"].push_back(args[i]);
        }
    }
    return command;
}

int main(int argc, char **argv) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        args.push_back(arg);
    }

    std::unordered_map<std::string, std::vector<std::string> > command = CheckValid(args);

    if (command["type"].front() == "-c") {
        std::ofstream out(command["archive_name"].front().c_str());
        Writer writer(out);
        for (std::string &filename : command["files"]) {
            std::string file = "" + filename;
            std::ifstream in(file.c_str());
            std::unordered_map<int, int> cnt = GetStatistics(in, filename);
            std::vector<std::pair<int, std::string> > code = Encode(in, cnt, filename);
            WriteFile(writer, filename, code, (filename == command["files"].back()));
        }
        writer.ClearBuffer();
        return 0;
    }

    if (command["type"].front() == "-d") {
        std::ifstream in(command["archive_name"].front().c_str());
        Decode(in);
        return 0;
    }

    if (command["type"].front() == "-h") {
        std::cout << "-c archive_name file1 [file2, file3 ... , fileN]\n";
        std::cout << "-d archive_name";
    }
    return 0;
}
