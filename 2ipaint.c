/*
8==D mark of the man 168504
*/
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

//#define X 80
//#define Y 24

void clear(){printf("\033c");}
void help(){
  printf("\
\e[1;44;36m▌\e[1;32;44mWSAD \e[1;31;44m& \e[1;32;44mHJKL\e[0;44;36m to move cursor, \e[1;32;44mP \e[1;31;44m& \e[1;32;44mR\e[0;44;36m to toggle drawing.      \e[1;31;47m+\e[0;41;37m to toggle help.\e[1;44;36m ▐\e[0m\n\
\e[1;44;36m▌\e[1;32;44mX \e[1;31;44m& \e[1;32;40m,\e[0;44;36m to select draw char, \e[1;32;44mV \e[1;31;44m& \e[1;32;44mN\e[0;44;36m to select FG color. \e[0m\e[1;44mColors|");
for(int i=0;i<8;++i)printf("\e[48;5;%dm%2d",i,i);
printf("\e[1;44;36m▐\e[0m\e[1;34m\n\e[1;36m▀\e[1;32;44mC\e[1;31;44m&\e[1;32;44mM\e[0;44;36m to select BG color, \e[1;32mE\e[0;44;36m to export \e[0;33;40mANSI\e[0;44;36m. \e[1;32mG\e[0;44;36m for TypeMode.  \e[0m\e[1;44m|");
for(int i=0;i<8;++i)printf("\e[48;5;%dm%2d",i+8,i+8);
printf("\e[0m\e[1;36m▀\e[0m ");
}
int main(int argc,char* argv[]){
  struct termios bezentertermios,zwyklytermios;
 // struct winsize svenska;
  tcgetattr(STDIN_FILENO,&zwyklytermios);bezentertermios=zwyklytermios;
  bezentertermios.c_lflag&=~(ICANON);
  tcsetattr(STDIN_FILENO,TCSANOW,&bezentertermios);
 // ioctl(STDIN_FILENO,TIOCGWINSZ,&svenska);

 int Y=atoi(argv[1]),//svenska.ws_row-7,
     X=atoi(argv[2]),//svenska.ws_col-3,
     bgrid[Y*2][X],
     fgrid[Y*2][X],
     curx=X/2,
     cury=Y/2,
     bgbrush=15,
     fgbrush=0,
     drawing=0,
     helpT=1,
     typemode=0,
     toggleclear=0;
 char tgrid[Y*2][X],
      chbrush='#',
      input;
 for(int y=0;y<Y*2;++y)
  for(int x=0;x<X;++x){tgrid[y][x]=' ';fgrid[y][x]=7;bgrid[y][x]=0;}
 clear();
 while(1){
  if(toggleclear==1){
   clear();
   toggleclear=0;
  }
  if(drawing==1){
   bgrid[cury][curx]=bgbrush;
   fgrid[cury][curx]=fgbrush;
   tgrid[cury][curx]=chbrush;
  }

  printf(\
 "\033[0;0H\e[0;34m▄\e[1;44;36m ─═2iPaint by \
\e[0;31;43mХальцён-СФТ under DiSC-8\e[1;32;44m 2022\e[1;33;44m<N>\e[1;36;44m");
  for(int i=0;i<X-69+2;++i)printf("═");
 printf("\e[1;33;40mx=%2d y=%2d\e[1;36;44m══",
	curx,
	cury);
 printf("Brush:\e[0m[\e[38;5;%dm\e[48;5;%dm%c\e[0m]\e[1;44;36m ▄\e[0m\n",
        fgbrush,bgbrush,chbrush);
printf("\e[0;44;36m╒");
 for(int i=0;i<X;++i)
  if(i==curx) printf("\e[0;42;30m╥");
  else printf("\e[1;44;36m═");
 printf("\e[0;106;34m╖\n");
  for(int y=0;y<Y;++y){ 
    if(y==cury)printf("\e[0;42;30m╞");else printf("\e[0;44;36m║");
   for(int x=0;x<X;++x){
   if(y==cury&&x==curx)
    printf("\e[38;5;%dm\e[48;5;%dm",bgrid[y][x],
				      fgrid[y][x]);else
    printf("\e[38;5;%dm\e[48;5;%dm",fgrid[y][x],
				      bgrid[y][x]);
	printf("%c",tgrid[y][x]);
   }
  if(y==cury)printf("\e[0;42;30m╡");else printf("\e[0;106;34m║\e[0m");
  
   printf("\n");
  }
printf("\e[1;44;36m▄\e[1;106;34m");
for(int i=0;i<X;++i)
  if(i==curx) printf("\e[0;42;30m╨");
  else printf("\e[1;106;34m═");
 printf("\e[0;106;34m╛\n");

  printf("\e[1;106;34m  ─══════\e[0;35;107mxmidget3mj4lnryldmv5t7uik3p26egkgkg3t7mlcloottrxwnrrn5yd.onion\e[1;34;106m═════─ \e[0m\e[1;36m▀\e[0m\n");
if(!typemode){  
  if(helpT)help();

  scanf("%c",&input);
  switch(input){
   case '+':if(helpT){toggleclear=1;helpT=0;}else helpT=1;break;
   case 'g':typemode=1;toggleclear=1;break;
   case 'w':case 'k':if(cury!=0)cury--;break;
   case 's':case 'j':if(cury!=Y-1)cury++;break;
   case 'a':case 'h':if(curx!=0)curx--;break;
   case 'd':case 'l':if(curx!=X-1)curx++;break;
   case 'p':case 'r':if(drawing==0)drawing=1;else drawing=0;break;
   case 'e':clear();

 for(int y=0;y<Y*2;++y){
  for(int x=0;x<X;++x){
 
  if(bgrid[y][x]!=bgrid[y][x-1]){
   if(fgrid[y][x]==7 && bgrid[y][x]==0)printf("\\033[0m");
   printf("\\033[48;5;%dm",bgrid[y][x]);
   }
  if(fgrid[y][x]!=fgrid[y][x-1])
   printf("\\033[38;5;%dm",fgrid[y][x]);
 
  printf("%c",tgrid[y][x]);
 }
  printf("\\n");
}
  printf("\033[0;47;31mPress any key to return.");getchar();toggleclear=1;break;
  /* case 'e':clear();export(bgrid,fgrid,tgrid,1);
  printf("\033[0;47;31mPress any key to return.");getchar();toggleclear=1;break;
*/   case 'c':case 'm':
   toggleclear=1;
    printf("\n\033[1;31mSelect Background Color\033[0;32m.> ");
   tcsetattr(STDIN_FILENO,TCSANOW,&zwyklytermios);
    scanf("%d",&bgbrush);
   tcsetattr(STDIN_FILENO,TCSANOW,&bezentertermios);break;
   case 'v':case 'n':
   toggleclear=1;
    printf("\n\033[1;31mSelect Foreground Color\033[0;32m.> ");
   tcsetattr(STDIN_FILENO,TCSANOW,&zwyklytermios);
    scanf("%d",&fgbrush);
   tcsetattr(STDIN_FILENO,TCSANOW,&bezentertermios);break;
   case 'x':case ',':
   toggleclear=1;
    printf("\n\033[1;31mSelect Brush Character\033[0;32m.> ");
   scanf("%c",&chbrush);break;
  }
 }else{
  printf("\e[1;31;47m`\e[1;37;41m to quit TypeMode.");
  drawing=1;
  scanf("%c",&chbrush);
  if(chbrush=='`'){
   typemode=0;
   toggleclear=1;
   drawing=0;};
  if(curx!=X-1)curx++;else{if(cury!=Y-1)cury++;curx=0;}
 }
}
 tcsetattr(STDIN_FILENO,TCSANOW,&zwyklytermios);
}
