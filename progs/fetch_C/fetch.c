//
//  main.c
//  fetch
//
//  Created by aswer on 04.04.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <getopt.h>

// Версия программы
#define VERSION "1.1"

#ifdef __APPLE__
#include <sys/sysctl.h>
#elif __linux__
#include <sys/sysinfo.h>
#endif

// Цвета для текста (ANSI-коды)
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_WHITE   "\033[1;37m"
#define COLOR_RESET   "\033[0m"

// ASCII-арт для Linux (Tux)
const char *LINUX_ART =
    COLOR_WHITE "░█████╗░████████╗░█████╗░░██████╗\n"
    COLOR_WHITE "██╔══██╗╚══██╔══╝██╔══██╗██╔════╝\n"
    COLOR_WHITE "██║░░╚═╝░░░██║░░░██║░░██║╚█████╗░\n"
    COLOR_WHITE "██║░░██╗░░░██║░░░██║░░██║░╚═══██╗\n"
    COLOR_WHITE "╚█████╔╝░░░██║░░░╚█████╔╝██████╔╝\n"
    COLOR_WHITE "░╚════╝░░░░╚═╝░░░░╚════╝░╚═════╝░\n";

// ASCII-арт для macOS (Apple logo)
const char *MACOS_ART =
    COLOR_GREEN "       .:.\n"
    COLOR_GREEN "    .:;;;;:..\n"
    COLOR_GREEN "   //;;;;;;;;\\\\\n"
    COLOR_GREEN "   \\\\;;;;;;;;//\n"
    COLOR_GREEN "    `':;;;;;'`\n"
    COLOR_GREEN "       .:;:.\n";

// Функция для вывода версии
void print_version() {
    printf("Version: %s\n", VERSION);
}

void print_help(const char *program_name) {
    printf("Using: %s [OPTION]\n", program_name);
    printf("Options:\n");
    printf("  -n, --no-art       Show system information without ASCII art\n");
    printf("  -v, --version      Display the program version\n");
    printf("  -h, --help         Show this helpу\n");
}

// Вывод ASCII-арта в зависимости от ОС
void print_art() {
#if defined(__linux__)
    printf("%s", LINUX_ART);
#elif defined(__APPLE__)
    printf("%s", MACOS_ART);
#endif
}

// Получаем uptime системы
void get_uptime() {
    double uptime_seconds = 0;

#if defined(__linux__)
    FILE *uptime_file = fopen("/proc/uptime", "r");
    if (!uptime_file) {
        perror("Failed to open /proc/uptime");
        return;
    }
    fscanf(uptime_file, "%lf", &uptime_seconds);
    fclose(uptime_file);
#elif defined(__APPLE__)
    struct timeval boottime;
    size_t len = sizeof(boottime);
    int mib[2] = { CTL_KERN, KERN_BOOTTIME };
    if (sysctl(mib, 2, &boottime, &len, NULL, 0) == -1) {
        perror("Error getting boot time");
        return;
    }
    time_t now;
    time(&now);
    uptime_seconds = difftime(now, boottime.tv_sec);
#endif

    int days = (int)uptime_seconds / 86400;
    int hours = ((int)uptime_seconds % 86400) / 3600;
    int minutes = ((int)uptime_seconds % 3600) / 60;

    printf(COLOR_CYAN "Uptime:" COLOR_RESET " %d days, %d hours, %d minutes\n", days, hours, minutes);
}

// Получаем версию macOS
#ifdef __APPLE__
void get_macos_version() {
    char version[256];
    size_t len = sizeof(version);
    if (sysctlbyname("kern.osproductversion", version, &len, NULL, 0) == -1) {
        perror("Error getting macOS version");
        return;
    }
    printf(COLOR_BLUE "OS Version:" COLOR_RESET " macOS %s\n", version);
}
#endif

// Получаем информацию о процессоре
void get_cpu_info() {
    char cpu_model[256] = "Unknown";

#if defined(__linux__)
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (!cpuinfo) {
        perror("Failed to open /proc/cpuinfo");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), cpuinfo)) {
        if (strstr(line, "model name")) {
            strcpy(cpu_model, strchr(line, ':') + 2);
            break;
        }
    }
    fclose(cpuinfo);
#elif defined(__APPLE__)
    size_t len = sizeof(cpu_model);
    if (sysctlbyname("machdep.cpu.brand_string", cpu_model, &len, NULL, 0) == -1) {
        perror("Error getting CPU model");
        return;
    }
#endif

    printf(COLOR_WHITE "CPU:" COLOR_RESET " %s", cpu_model);
}

// Получаем информацию о памяти
void get_memory_info() {
    unsigned long total_mem = 0;

#if defined(__linux__)
    struct sysinfo mem_info;
    if (sysinfo(&mem_info) == -1) {
        perror("Error getting memory information");
        return;
    }
    total_mem = mem_info.totalram * mem_info.mem_unit / (1024 * 1024); // в МБ
#elif defined(__APPLE__)
    size_t len = sizeof(total_mem);
    if (sysctlbyname("hw.memsize", &total_mem, &len, NULL, 0) == -1) {
        perror("Error getting memory information");
        return;
    }
    total_mem /= (1024 * 1024); // в МБ
#endif

    printf(COLOR_WHITE "Memory:" COLOR_RESET " %lu MB\n", total_mem);
}

int main(int argc, char *argv[]) {
    
    struct utsname sys_info;
    if (uname(&sys_info) == -1) {
        perror("Error getting system information");
        return 1;
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname))) {
        perror("Error getting host name");
        return 1;
    }
    
    if (argc == 1) {
        // Выводим ASCII-арт и информацию в две колонки
        printf("\n");
        print_art();
        printf("\n");

        printf(COLOR_GREEN "User:" COLOR_RESET " %s\n", getenv("USER"));
        printf(COLOR_YELLOW "Hostname:" COLOR_RESET " %s\n", hostname);

    #if defined(__linux__)
        printf(COLOR_BLUE "OS:" COLOR_RESET " %s\n", sys_info.sysname);
    #elif defined(__APPLE__)
        printf(COLOR_BLUE "OS:" COLOR_RESET " %s\n", "macOS");
        get_macos_version();
    #endif

        printf(COLOR_MAGENTA "Kernel:" COLOR_RESET " %s\n", sys_info.release);
        get_uptime();
        get_cpu_info();
        get_memory_info();

        printf("\n");
            return EXIT_SUCCESS;
        }
    
    int opt;

    // Длинные опции
    static struct option long_options[] = {
        {"version", no_argument,       0, 'v'},
        {"help",    no_argument,       0, 'h'},
        {"no-art",  no_argument,       0, 'n'},
        {0, 0, 0, 0}
    };
    
    while ((opt = getopt_long(argc, argv, "vhn", long_options, NULL)) != -1) {
        switch (opt) {
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);
            case 'h':
                print_help(argv[0]);
                exit(EXIT_SUCCESS);
            case 'n':
                printf(COLOR_GREEN "User:" COLOR_RESET " %s\n", getenv("USER"));
                printf(COLOR_YELLOW "Hostname:" COLOR_RESET " %s\n", hostname);

            #if defined(__linux__)
                printf(COLOR_BLUE "OS:" COLOR_RESET " %s\n", sys_info.sysname);
            #elif defined(__APPLE__)
                printf(COLOR_BLUE "OS:" COLOR_RESET " %s\n", "macOS");
                get_macos_version();
            #endif

                printf(COLOR_MAGENTA "Kernel:" COLOR_RESET " %s\n", sys_info.release);
                get_uptime();
                get_cpu_info();
                get_memory_info();

                printf("\n");
                exit(EXIT_SUCCESS);
            case '?':
                // Неизвестный параметр
                print_help(argv[0]);
                exit(EXIT_FAILURE);
            default:
                fprintf(stderr, "Error in parameters\n");
                exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}
