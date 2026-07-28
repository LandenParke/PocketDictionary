#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <locale.h>


typedef struct {
    int x[4];
    int y[4];
    double confidence;
    const char* text;
} OCRResult;



void process_results(OCRResult* results, int count) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");


    for (int i = 0; i < count; i++) {
        printf("Text: %s | Confidence: %.4f | BBox: (%d,%d)-(%d,%d)-(%d,%d)-(%d,%d)\n",
               results[i].text, results[i].confidence,
               results[i].x[0], results[i].y[0],
               results[i].x[1], results[i].y[1],
               results[i].x[2], results[i].y[2],
               results[i].x[3], results[i].y[3]);
    }
}

