#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define tahun 2006
#define bulan 8
#define hari 20
#define jam 12

#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif

void refreshterminal(){
  printf("\x1b[2J\x1b[1;1H");

  fflush(stdout);
}


int main(){
  refreshterminal();

  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  while(1){
    double birthyear = tahun + bulan/12 + hari/365 + jam/8760;

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    struct tm *t = localtime(&ts.tv_sec);
    double ms_sekarang = ts.tv_nsec / 1e6;

    double saatini = (t->tm_year + 1900) 
                    + (t->tm_mon + 1)   /12.0 
                    + t->tm_mday        /365.0 
                    + t->tm_hour        /8760.0 
                    + t->tm_min         /525600.0 
                    + ms_sekarang       /31556952000.0;

    double umur = saatini - birthyear;

    printf("%.20f\n", umur);
    ms_sekarang++;

    sleep_ms(1);
    refreshterminal();
  }

}
