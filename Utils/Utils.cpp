#include "Utils.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

char * Genesis::Utils::ResolvePath(const char *path) {
#ifdef __APPLE__
    CFStringRef pathCFString = CFStringCreateWithCString(kCFAllocatorDefault, path, kCFStringEncodingUTF8);
    CFURLRef resourceURL = CFBundleCopyResourceURL(CFBundleGetMainBundle(), pathCFString, NULL, NULL);
    CFStringRef resourcePath = CFURLCopyPath(resourceURL);

    char *result = strdup(CFStringGetCStringPtr(resourcePath, kCFStringEncodingUTF8));

    CFRelease(resourcePath);
    CFRelease(resourceURL);

    return result;
#else
    return strdup(path);
#endif
}

std::filesystem::path Genesis::Utils::ResolvePath(const std::filesystem::path& path) {
#ifdef __APPLE__
    std::string pathString = path.string();
    CFStringRef pathCFString = CFStringCreateWithCString(kCFAllocatorDefault, pathString.c_str(), kCFStringEncodingUTF8);

    CFURLRef resourceURL = CFBundleCopyResourceURL(CFBundleGetMainBundle(), pathCFString, NULL, NULL);
    CFStringRef resourcePath = CFURLCopyPath(resourceURL);

    std::filesystem::path result = CFStringGetCStringPtr(resourcePath, kCFStringEncodingUTF8);

    CFRelease(resourcePath);
    CFRelease(resourceURL);
    CFRelease(pathCFString);

    return result;
#else
    return path
#endif
}
