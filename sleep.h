#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(x) Sleep(x)
#else
    #ifdef __linux__
        #include <unistd.h>
        #define SLEEP(x) usleep(1000 * x)
    #endif // __linux__
#endif
