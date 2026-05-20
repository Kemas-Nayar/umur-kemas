#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

  double tahun = 2006;
  double bulan = 8;
  double hari = 20;
  double jam = 12;
  double menit = 30;

  double ms_sekarang = 0;



  while(1){
    double birthyear = tahun + bulan/12 + hari/365 + jam/8760 + menit/525600;

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
