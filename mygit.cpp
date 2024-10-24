#include <bits/stdc++.h>
#include <openssl/sha.h>
#include <filesystem>
#include <zstr.hpp>
using namespace std;

/*
    ./mygit init
    ./mygit hash-object [-w] <file>
    ./mygit cat-file <flag> <file-sha>
    ./mygit write-tree
    ./mygit ls-tree [--name-only] <tree-sha>
    ./mygit add . && ./mygit add <file1> <file2> ..
    ./mygit commit -m "Commit Message" && ./mygit commit
    ./mygit log
    ./mygit checkout <commit-sha>
*/
bool argumentCheckUtility(string cmd, int argc)
{
    if (cmd == "init" && argc != 2)
    {
        cout << "Usage: ./mygit init" << endl;
        return false;
    }
    else if (cmd == "hash-object" && argc != 3 && argc != 4)
    {
        cout << "Usage: ./mygit hash-object [-w] <file>" << endl;
        return false;
    }
    else if (cmd == "cat-file" && argc != 4)
    {
        cout << "Usage: ./mygit cat-file <flag> <file-sha>" << endl;
        return false;
    }
    else if (cmd == "write-tree" && argc != 2)
    {
        cout << "Usage: ./mygit write-tree" << endl;
        return false;
    }
    else if (cmd == "ls-tree" && argc != 3 && argc != 4)
    {
        cout << "Usage: ./mygit ls-tree [--name-only] <tree-sha>" << endl;
        return false;
    }
    else if (cmd == "commit" && argc != 4 && argc != 2)
    {
        cout << "Usage: ./mygit commit -m \"Commit Message\" OR ./mygit commit" << endl;
        return false;
    }
    else if (cmd == "log" && argc != 2)
    {
        cout << "Usage: ./mygit log" << endl;
        return false;
    }
    else if (cmd == "checkout" && argc != 3)
    {
        cout << "Usage: ./mygit checkout <commit-sha>" << endl;
        return false;
    }
    return true;
}
void repoInitializer()
{
    std::filesystem::create_directory(".git");
    std::filesystem::create_directory(".git/objects");
    std::filesystem::create_directory(".git/refs");
    std::filesystem::create_directories(".git/refs/heads");
    std::ofstream headFile(".git/HEAD");
    if (headFile.is_open())
    {
        headFile << "ref: refs/heads/main\n";
        headFile.close();
    }
    else
    {
        std::cerr << "Failed to create .git/HEAD file.\n";
        return;
    }
}
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "Usage: ./mygit [init][hash-object][cat-file][write-tree][ls-tree][add][commit][log][checkout]" << endl;
        return 0;
    }
    string cmd = argv[1];
    if (!argumentCheckUtility(cmd, argc))
        return 0;

    if (cmd == "init")
    {
        repoInitializer();
    }
    else if (cmd == "hash-object")
    {
        
    }
    else if (cmd == "cat-file")
    {
        const std::string flag = argv[2];
        const std::string SHA_VAL = argv[3];
        const std::string dir_name = SHA_VAL.substr(0, 2);
        const std::string blob_sha = SHA_VAL.substr(2);

        std::string path = ".git/objects/" + dir_name + "/" + blob_sha;
        zstr::ifstream input(path, std::ofstream::binary);
        if (!input.is_open())
        {
            std::cerr << "Failed to open object file?\n";
            return EXIT_FAILURE;
        }
        std::string object_str{std::istreambuf_iterator<char>(input),
                               std::istreambuf_iterator<char>()};
        input.close();
        const auto object_content = object_str.substr(object_str.find('\0') + 1);
        std::cout << object_content << std::flush;
    }
    else if (cmd == "write-tree")
    {
    }
    else if (cmd == "ls-tree")
    {
    }
    else if (cmd == "add")
    {
    }
    else if (cmd == "commit")
    {
    }
    else if (cmd == "log")
    {
    }
    else if (cmd == "checkout")
    {
    }
    else
    {
        cout << "Usage: ./mygit [init][hash-object][cat-file][write-tree][ls-tree][add][commit][log][checkout]" << endl;
    }
}
