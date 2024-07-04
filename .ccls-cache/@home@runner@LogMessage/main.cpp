#include <stdarg.h>
#include <stdio.h>

#define LOG_BUFFER_SIZE 500
void LogD(const char *message, ...) {
  va_list args;
  va_start(args, message);
  vprintf(message, args); // 실제 환경에 맞게 수정 가능
  va_end(args);
}
//

void logMessage(char *buffer, size_t *currentLengh, size_t bufferSize,
                const char *format, ...) {

  va_list args;

  // 시작 부분: 가변 인자 리스트 초기화
  va_start(args, format);
  // printf("%zu %zu\n", sizeof(buffer), bufferSize);
  if (*currentLengh < 200) {
    *currentLengh += vsnprintf(&buffer[*currentLengh],
                               bufferSize - *currentLengh, format, args);
  } else {
    *currentLengh += vsnprintf(&buffer[*currentLengh],
                               bufferSize - *currentLengh, format, args);
    // snprintf(&buffer[currentLength], bufferSize - currentLength, " <%zu>\n",
    // currentLength);
    LogD("%s", buffer);
    *currentLengh = 0;
  }

  // 끝 부분: 가변 인자 리스트 종료
  va_end(args);
}

void exampleUsage() {
  static char logSave1[LOG_BUFFER_SIZE];
  int detIdx, rangeIndx, angleIndx;
  size_t currentLengh = 0;
  float noise;
  logMessage(logSave1, &currentLengh, sizeof(logSave1), "hello\n");
  for (int i = 0; i < 100; ++i) {
    detIdx = i;
    rangeIndx = i * 10;
    angleIndx = i * 5;
    noise = i * 0.5f;

    logMessage(logSave1, &currentLengh, sizeof(logSave1),
               "[%d] r:%d a:%d np:%.1f ", detIdx, rangeIndx, angleIndx, noise);
    logMessage(logSave1, &currentLengh, sizeof(logSave1), "end\n");
  }
}

int main() {
  exampleUsage();
  printf("const char *__restrict format, ...");
  return 0;
}