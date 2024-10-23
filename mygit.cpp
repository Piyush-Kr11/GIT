#include <bits/stdc++.h>
#include <openssl/sha.h>
#include <zlib.h>
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

        std::ifstream input(path, std::ofstream::binary);
        if (!input.is_open())
        {
            std::cerr << "Failed to open object file?\n";
            return EXIT_FAILURE;
        }
        std::string compressed_data{std::istreambuf_iterator<char>(input),
                                    std::istreambuf_iterator<char>()};
        input.close();
        const size_t buffer_size = 1024; // Size of the buffer for decompression
        std::vector<char> decompressed_data(buffer_size);

        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = static_cast<uInt>(compressed_data.size());
        strm.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(compressed_data.data()));

        // Initialize the zlib stream
        if (inflateInit(&strm) != Z_OK)
        {
            std::cerr << "inflateInit failed\n";
            return EXIT_FAILURE;
        }

        std::ostringstream oss;
        int ret;
        do
        {
            strm.avail_out = static_cast<uInt>(buffer_size);
            strm.next_out = reinterpret_cast<Bytef *>(decompressed_data.data());

            ret = inflate(&strm, Z_NO_FLUSH);

            if (oss.good())
            {
                oss.write(decompressed_data.data(), buffer_size - strm.avail_out);
            }
        } while (ret == Z_OK);

        if (ret != Z_STREAM_END)
        {
            std::cerr << "inflate failed: " << ret << "\n";
            inflateEnd(&strm);
            return EXIT_FAILURE;
        }

        // Clean up
        inflateEnd(&strm);

        // Get the decompressed content and handle null terminator
        std::string object_content = oss.str();
        const auto null_pos = object_content.find('\0');
        if (null_pos != std::string::npos)
        {
            object_content = object_content.substr(null_pos + 1);
        }

        std::cout << object_content << std::flush;
        return EXIT_SUCCESS;
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
