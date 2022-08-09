#pragma once

#ifndef UTIL_HPP_NEROSHOP
#define UTIL_HPP_NEROSHOP

#ifdef _WIN32
#include <windows.h>
#include <Lmcons.h> // UNLEN
#endif

#ifdef __gnu_linux__
#include <unistd.h> // getcwd, getwd, get_current_dir_name, getpwnam, getpwnam_r, getpwuid, getpwuid_r
#include <sys/types.h> // ??
#include <dirent.h> // opendir, fdopendir, closedir
#include <pwd.h> // getpwnam, getpwnam_r, getpwuid, getpwuid_r
#include <sys/stat.h> // mkdir
#include <string.h> // strdup
#endif

#include <iostream>
#include <sstream> // std::ostringstream
#include <vector>
#include <algorithm> // std::transform

namespace neroshop {

namespace string {
	static std::string lower(const std::string& str) 
	{
		std::string temp_str = str;
		std::transform(temp_str.begin(), temp_str.end(), temp_str.begin(), [](unsigned char c){ return std::tolower(c); });	
		return temp_str;
	}
	
	static std::string upper(const std::string& str)
	{
		std::string temp_str = str;
		std::transform(temp_str.begin(), temp_str.end(), temp_str.begin(), [](unsigned char c){ return std::toupper(c); });	
		return temp_str;		
	}    
	
    template <typename T>
    static std::string precision(const T value, const int n)
    {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << value;
        return out.str();
    } 		
    
	static std::vector<std::string> split(const std::string& str, const std::string& delimiter)
	{
		std::vector<std::string> output;
        char * dup = strdup(str.c_str());
        char * token = strtok(dup, delimiter.c_str());
        while(token != nullptr)
		{
            output.push_back(std::string(token));
            token = strtok(nullptr, delimiter.c_str());
        }
        free(dup);	
        return output;		
	}	
}
//-------------------------
namespace filesystem {
    static bool is_file(const std::string& filename) { // checks if file exists
        return std::filesystem::is_regular_file(filename);
    }
    
    static bool is_directory(const std::string& path) {
        #if defined(__cplusplus) && (__cplusplus >= 201703L)
        return std::filesystem::is_directory(path);
        #endif
        #ifdef _WIN32
	    DWORD dwAttrib = GetFileAttributes(path.c_str());
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
        #endif
        #ifdef __gnu_linux__
        DIR * dir = opendir(path.c_str());
        if(dir) {
            closedir(dir);
	        return true;
        }		
        #endif
        return false;
    }
    
    static bool make_directory(const std::string& path) {
        if(is_directory(path)) {
            std::cout << "\033[1;93mDirectory \"" << path << "\" already exists\033[0m" << std::endl;
            return false;
        }
        #if defined(__cplusplus) && (__cplusplus >= 201703L)
        return std::filesystem::create_directories(path.c_str());
        #endif
        #ifdef _WIN32
	    return (CreateDirectory(path.c_str(), nullptr) != 0);
        #endif
        #ifdef __gnu_linux__
	    return (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0);
        #endif	
        return false;
    }
    
    static std::string current_directory() {    
        #if defined(__cplusplus) && (__cplusplus >= 201703L)
        return std::filesystem::current_path();
        #endif
        #ifdef _WIN32
        #endif
        #ifdef __gnu_linux__
	    char buffer[1024];
        if(getcwd(buffer, sizeof(buffer)) != nullptr)
		    return std::string(buffer);
        #endif            
        return "";
    }
    //static std::vector<std::string> get_directory() { // return a list of filenames in a directory
    //static dialog() {
    // filename string manipulation
    /*static std::string get_file_extension(const std::string& filename) {
	    std::string extension = filename.substr(filename.find_last_of(".") + 1);
	    return extension;    
    }*/
}
//-------------------------
namespace device {
    static std::string get_user() {
	    #ifdef _WIN32
	    char username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        if(GetUserName(username, &username_len) == 0) 
            return "";
		return std::string(username);
	    #endif    
	    #ifdef __gnu_linux__ // works!
	    uid_t uid = geteuid();
		struct passwd * pw = getpwuid(uid);
        if(!pw) return "";
        return std::string(pw->pw_name);
	    #endif    
	    return "";
	}
}

}

#endif