#include <immintrin.h>
#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <malloc.h>

char repeat = 0;

void avxAdd(void * noOneCares) {
    // Initialize the two argument vectors
    __m256 evens = _mm256_set_ps(2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0);
    __m256 odds = _mm256_set_ps(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    // Infinitely subtract the 2 numbers
    while (1) {
        __m256 result = _mm256_sub_ps(evens, odds);
    }
}

void fillMemory(void * noOneCares) {
    // Infinitely loop
    while (1) {
        // Check how much memory is left
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof (statex);
        GlobalMemoryStatusEx (&statex);
        // Run as long as there is free memory so that memory is always above 95% and page filing is not used as memory
        while (statex.dwMemoryLoad <= 95 && statex.ullTotalVirtual-statex.ullTotalPhys < statex.ullAvailVirtual) {
            unsigned long * a = malloc(sizeof(*a));  // allocating
            unsigned long * b = malloc(sizeof(*b));  // allocating
            unsigned long * c = malloc(sizeof(*c));  // allocating
            unsigned long * d = malloc(sizeof(*d));  // allocating
            // Update the amount of memory left
            GlobalMemoryStatusEx (&statex);
        
        }
        // Enable avx2 once memory is full
        if (statex.dwMemoryLoad >= 95){
            repeat = 1;
        }
    }
}

int main() {

    // Set process priority - Above Normal
    SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

    // Get number of cpu threads
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    // Multiply cpu processors by 2 to account for hyperthreaded CPUs
    int numThreads = 2 * sysinfo.dwNumberOfProcessors;

    for(int i = 0; i < numThreads; i++){
        // Fill the memory
        _beginthread(fillMemory, i, NULL);
    }

    if (repeat == 1){
        printf("%d", repeat);
        printf("Avx 2 has begun");
        for(int i = 0; i < numThreads; i++){
            // Run AVX2 on all cores
            _beginthread(avxAdd, i, NULL);
        }
    }

    // Make it impossible to leave the code as many times as you click enter
    scanf(" ");

}