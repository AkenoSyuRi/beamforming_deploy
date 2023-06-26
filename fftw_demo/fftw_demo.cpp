   #include <stdio.h>
   #include <unistd.h>
   #include <string.h>
   #include <stdlib.h>
   #include <fftw3.h>
    /* python　np.rfft的结果
[ 900.          +0.j          -75.52811087+135.48370223j
  -89.26960212 -36.89088019j -141.76211763 +52.35641639j
  144.53910524 -47.87005769j  -18.87933361+144.12556982j
  -37.07400191 +56.05170075j  -63.94721021+121.1031161j
   14.         -46.j          -31.86080989 +67.67386715j
  -31.16863878 +12.15220581j  -10.16093173 -15.92191832j
   -2.53910524  -5.87005769j  -87.62402389 +45.36275212j
   29.51224281 -12.79037513j   -2.23746216 +59.10827716j
  -92.          +0.j        ]
*/
  
  //采用的double对齐的接口
  int main(int args, char *argv[]) {
      int window = 32;
  
      int ret = 0;
      int index = 0;     
      short int16_t_buf[32] = {
          0, 1, 10, 20, 31, 21, 29, 30,
          32, 41, 12, 13, 15, 15, 14, 12,
          54, 65, 43, 32, 12, 43, 12, 43,
          54, 64, 43, 31, 11, 21, 32, 44
      };
  
      double* din  = (double *)fftw_malloc(sizeof(double)*(32));
      fftw_complex* dout = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*(17));
      fftw_plan p = fftw_plan_dft_r2c_1d(window, din, dout, FFTW_ESTIMATE);
	  fftw_plan b = fftw_plan_dft_c2r_1d(window, dout, din, FFTW_ESTIMATE);
      for (index = 0; index < window; index++) {
          din[index] = (double)int16_t_buf[index];
      }
    

    fftw_execute(p);

      printf ("\nreal\n");
      for (index = 0; index < window/2+1; index++) {
          if (index % 8 == 0) printf("\n");
          printf ("%5.5lf ", dout[index][0]);
      }
      //打印虚部
      printf ("\nimag\n");
      for (index = 0; index < window/2+1; index++) {
          if (index % 8 == 0) printf("\n");
          printf ("%5.5lf ", dout[index][1]);
      }
      printf ("\n");
     
      //对rfft输出数据进行irfft逆变
      fftw_execute(b);
  
      for (index = 0; index < window; index++) {
          if (index % 8 == 0) printf("\n");
          printf ("%.10lf ", din[index]/window);
      }
      printf ("\n");

	//.......
  }

