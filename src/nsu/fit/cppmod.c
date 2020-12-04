#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <polyglot.h>

typedef struct CpuInfo {
    char cpu_model[256];
    int cpu_cores;
} CpuInfo;

POLYGLOT_DECLARE_TYPE(CpuInfo)

void* cpuModel() {
    FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
    char *arg = 0;
    size_t size = 0;

    int cpu_cores;
    static char cpu_model[256];

    while(getdelim(&arg, &size, '\n', cpuinfo) != -1) {
        if (strstr(arg, "model name") == arg) {
            strncpy(cpu_model, strchr(arg, ':') + 1, 256);
        }
    }
    fclose(cpuinfo);

    return polyglot_from_string(cpu_model, "ascii");
}

void* cpuInfo() {

    FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
    char *arg = 0;
    size_t size = 0;

    int cpu_cores;
    static char cpu_model[256];

    while(getdelim(&arg, &size, '\n', cpuinfo) != -1) {
        if (strstr(arg, "cpu family") == arg) {
            cpu_cores = atoi(strchr(arg, ':') + 1);
        }
        if (strstr(arg, "model name") == arg) {
            strncpy(cpu_model, strchr(arg, ':') + 1, 256);
        }
    }
    fclose(cpuinfo);


    static CpuInfo info;
    memcpy(info.cpu_model, cpu_model, 256);
    info.cpu_cores = cpu_cores;

    return polyglot_from_CpuInfo(&info);
}

//int main() {
//    CpuInfo info = cpuInfo();
//    printf("cpu_cores: %d\n", info.cpu_cores);
//    printf("cpu_model: %s\n", info.cpu_model);
//    return 0;
//}