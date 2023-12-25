#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

int main() {
    const char* library_path = "/usr/lib/liblist.so";

    void* handle = dlopen(library_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Не удалось загрузить библиотеку: %s\n", dlerror());
        return 1;
    }

    pid_t pid = getpid();

    char maps_file_path[256];
    sprintf(maps_file_path, "/proc/%d/maps", pid);

    FILE* maps_file = fopen(maps_file_path, "r");
    if (!maps_file) {
        perror("Не удалось открыть файл maps");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), maps_file)) {
        printf("%s", buffer);
    }

    fclose(maps_file);

    dlclose(handle);

    return 0;
}
