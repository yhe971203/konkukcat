#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#define INTERVAL_LEVEL  20
//#define INTERVAL_GAGE	3

pthread_mutex_t mutex_lock;
static int level=1;
static int cleangage = 50;
static int foodgage = 50;
static int sleepgage = 50;
static int joygage = 50;
static int menunum;



void time_level(int signo)
{
	level=level+1;
	
	printf("\n\n*************************************\n");
	printf("**************level%d*****************\n", level);
	printf("*************************************");
	alarm(INTERVAL_LEVEL);
	
}


void *t_function(void *data)
{


	static struct sigaction act;
        act.sa_handler = time_level;
       	sigfillset(&act.sa_mask);
       if( sigaction(SIGALRM, &act, 0)== -1)
       {
       	perror("sigaction");
	exit(0);
       }
	alarm(INTERVAL_LEVEL);

}




 void * rand_minus(void *data)
        {
            int rand_num;

            while(1)
        {
                srand((unsigned)time(NULL));
                rand_num = rand()%4 +1;

                switch(rand_num)
                {
            case 1:
                foodgage = foodgage -5;
                 break;
            case 2:
                sleepgage = sleepgage -5;
                break;
            case 3:
                joygage = joygage -5;
                break;
            case 4:
                cleangage = cleangage -5;
                break;
            }
if(foodgage<=0|sleepgage<=0|joygage<=0|cleangage<=0) break;


            pthread_mutex_unlock(&mutex_lock);

	    
            sleep(9-level);
        }  // while문 끝 
            printf("*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.\n\n              GAME OVER!\n        Now one gage is zero\n\n*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.*:.\n");
            exit(0);
    }

void menu(void){
        while(1){ // level이 10이 되거나 게이지가 0이되면 종료해야함
	menunum=6;
		if(level>=10) exit(0);
		if(menunum !=5){
                printf("\n\n\n 배부름\t%d\n 잠\t%d\n 즐거움\t%d\n 깔끔함\t%d\n",foodgage,sleepgage,joygage,cleangage);
                printf("0: eat/ 1: sleep/ 2: play/ 3:clean/ 4:exit\n");
		}
		scanf("%d",&menunum);
                switch(menunum){
                case 0:
                        select_food();
			menunum = 5;
                        break;

                case 1:
                        select_sleep();
			menunum = 5;
                        break;

                case 2:
                        select_minigame();
			menunum = 5;
                        break;

                case 3: 
                        select_clean();
			menunum = 5;
                        break;

                case 4:
 			 exit(0);
                }
        }
}


       



     // 음식 선택지 주고 그에 따라 게이지 변경
         void select_food()
        {
            int num;
            if (foodgage > 90) {
            printf("건냥 is already full ^-^* \n");    // 최대게이지 100 넘는 것을 방지
            return;
            }

       while(1){

        printf("**** Select the food's number ****\n ex)1 \n\n1. 말린 황태    2. 연어    3. 삼계탕\n\n");
   	scanf("%d", &num);
	printf("%d\n",num);

		if(num==1){	
		foodgage = foodgage + 5;
            		break;}
                if(num==2){
			foodgage = foodgage + 8;
            		break;}
                if(num==3){
			foodgage = foodgage + 10;
            		break;
		}
            }
       
            printf("food_gage: %d\n", foodgage);

            if (50 <= foodgage && foodgage < 70)
        	showcat_food(50);
	  
	    else if (70 <= foodgage && foodgage <= 100)
		showcat_food(70);

	   // return;
        }

// 화면에 이미지 출력
        void showcat_food(int n)
        {
	  
            FILE *fp;
            int c=0;

	    switch(n){
		case 50 :
			fp = fopen("food50.txt", "r");
			break;
		case 70 :
			fp = fopen("food70.txt", "r");
			break; 
	    }

            while ((c = fgetc(fp))!= -1) {
            putchar(c);
	    }

        fclose(fp);

        sleep(2);
        
	}


	void select_sleep(void){

		if(sleepgage>90) printf("건냥 is already deep sleep\n\n"); //최대 게이지 100넘는 것 방지
		else{
        		sleepgage = sleepgage + 10;
		}
		showcat_sleep();
		return 0;
	}	

	void showcat_sleep(void){
        	FILE * fp;
        	int c;

       		fp = fopen("sleep.txt", "r");

    		while ((c = fgetc(fp))!= EOF){
      	 		putchar(c);
       		}
		fclose(fp);

       		sleep(2);
   	  	return 0;
	}

void select_clean(void){
        if(cleangage>90) printf("건냥 is already clean\n\n"); //최대 게이지 100넘는 것 방지
        else{ //clean이미지 출력 & 게이지 10증가
                cleangage = cleangage + 10;
                printf("clean: %d\n",cleangage);
                showcat_clean();
        }
	return 0;
}

void showcat_clean(void){ //저장된 고양이 이미지 출력


        FILE *fp;
        int c;

        fp = fopen("clean.txt","r");

        while((c = fgetc(fp)) != EOF){
        putchar(c);
        }

        fclose(fp);

        sleep(1);
        return 0;
}


void gameover_atexit(void){ //게임종료되면 현재 레벨 출력하며 종료
        printf("*****************game finish***************\n");
	printf("*******************레벨 %d*****************\n",level);
	printf("*******************************************\n");
}

void savecatimage(){ //고양이 이미지 저장
        FILE *fp1 = fopen("food50.txt","wt");
            fputs("\n     ♡:.    ∧  ,, ∧\n       *. (= ' ω ' =)  *:.\n           {          }/  .♡:.\n Meow~ \n(mean: Thank u!)\n", fp1);
            fclose(fp1);

        FILE *fp2 = fopen("food70.txt","wt");
            fputs("      *♡.\n    ♡:.    ∧  ,, ∧  ♡:.\n     *.  (= > ω < =)  .:*\n          {          }/  ♡:.\n Meow~ Meow~\n(mean: Thank u so much! Now I'm full)\n", fp2);
            fclose(fp2);
        FILE *fp3 = fopen("sleep.txt","wt");
                fputs(" ∧,,∧ Good night\n(-ω-)Z Z Z Z Z\n/　|\nＵＵ　　",fp3);
                fclose(fp3);

        FILE *fp4 = fopen("clean.txt","wt");
                fputs(" ∧,,∧ clean~\n(oω<)\n/　つ----:☆:。\nＵＵ　　　 ..。\n　　　　　 .☆:.\n　　　　　　　′ .:☆:。\n　　　　　　  　＊:☆＊\n",fp4);
                fclose(fp4);



FILE *fp10 = fopen("minigame1.txt", "wt");

    fputs("\n[ M I N I G A M E ! ]\n\n       ^ ,,^\n Mya! (='ω'=)  oO{?}\n       ∪   ∪\n(mean: Guess the number I think!(1~100))\n\n", fp10);

    fclose(fp10);



    FILE *fp20 = fopen("same.txt", "wt");

    fputs("\n[ C O R R E C T ! ]\n\n       ^ ,,^\n Mya~ (=^ω^=)  <{♡}\n       ∪   ∪\n\n", fp20);

    fclose(fp20);



    FILE *fp30 = fopen("greaterthan.txt", "wt");

    fputs("\n        ^ ,, ^\n Meow (=∨ㅅ∨=)  <{↑}\n       ∪    ∪\n(mean: greater than that number)\n\n", fp30);

    fclose(fp30);



    FILE *fp40 = fopen("lessthan.txt", "wt");

    fputs("\n        ^ ,, ^\n Meow (=∨ㅅ∨=)  <{↓}\n       ∪    ∪\n(mean: less than that number)\n\n", fp40);

    fclose(fp40);



    FILE *fp50 = fopen("best.txt", "wt");

    fputs("\n[ Joyful + 10 ]\n\n  ^ ,,^\n (=>ω<=) Myamya!\n  ∪   ∪\n(mean: It was so fun!)\n\n", fp50);

    fclose(fp50);



    FILE *fp60 = fopen("good.txt", "wt");

    fputs("\n[ Joyful + 7 ]\n\n  ^ ,,^\n (='ω'=) Mya\n  ∪   ∪\n(mean: It was fun)\n\n", fp60);

    fclose(fp60);



    FILE *fp70 = fopen("soso.txt", "wt");

    fputs("\n[ Joyful + 3 ]\n\n  ^ ,, ^\n (='ㅅ'=) Hmm..\n  ∪    ∪\n(mean: I'm still boring..)\n\n", fp70);

    fclose(fp70);



    FILE *fp80 = fopen("draw.txt", "wt");

    fputs("\n  [Joyful +3]\n      /\\_/\\\n      ( ._. ) {ONE MORE TIME!!}\n     (mean: It was boring)\n\n", fp80);

    fclose(fp80);



    FILE *fp90 = fopen("win.txt", "wt");

    fputs("\n  [Joyful +7]\n          /\\_/\\\n         (= >_< )// \n  (mean: I W~I~N~ It's funny)\n\n", fp90);

    fclose(fp90);



    FILE *fp100 = fopen("lose.txt", "wt");

    fputs("\n  [joyful +1]\n    (=^-w-^=)../\n    u___u\n  (meam: I L O S E.. I am so sad)\n\n", fp100);

    fclose(fp100);


return 0;
}

void showcat_minigame(int n) //이미지 출력

{

    FILE *fp;

	int c;

    switch(n)

    {

        case 10:

            fp = fopen("minigame1.txt", "r");
            break;

        case 20:

            fp = fopen("same.txt", "r");
            break;

        case 30:

            fp = fopen("greaterthan.txt", "r");
            break;

        case 40:

            fp = fopen("lessthan.txt", "r");
            break;

        case 50:

            fp = fopen("best.txt", "r");
            break;

        case 60:

            fp = fopen("good.txt", "r");
            break;

        case 70:

            fp = fopen("soso.txt", "r");
            break;

        case 80:

            fp = fopen("draw.txt", "r");
            break;

        case 90:

            fp = fopen("win.txt", "r");
            break;

        case 100:

            fp = fopen("lose.txt", "r");
            break;

      
    }

 while((c = fgetc(fp)) != EOF){
        putchar(c);
        }
	fclose(fp);

	return 0;
}






void play_minigame1(void) //랜덤 숫자 맞추기 게임

{
        printf("game1");
    int rand_num=0;

    int count=0;

    int guess=0;

    char q=NULL;

    char buf[200];


    srand((unsigned)time(0));


    rand_num = rand()%100;


        showcat_minigame(10);
                                          

   while(1){
printf("숫자를 입력하세요");

        scanf("%d", &guess);

        if(0<=guess<=100)
        {
            if(guess==rand_num)
            {
                showcat_minigame(20);
                break;
            }

            else if(guess<rand_num)
                showcat_minigame(30);

            else if(guess>rand_num)

                showcat_minigame(40);

            count++;
        }

        else

        {
            printf("\n* only 1~100 number *\n");
            break;
        }
    }

        if(count<=5)

        {
            showcat_minigame(50);
            joygage += 10;
        }

        else if(5<count<=15)
        {
   showcat_minigame(60);
            joygage += 7;
        }
        else if(count>15)

        {

            showcat_minigame(70);

            joygage += 3;

        }





 buf[0] = '\0';


}



void play_minigame2(void)

{

    int a;

    int t;

    char q=NULL;

    char buf[200];

    

    srand(time(NULL)); //time(NULL):1초 단위로 시간 변경

    a=rand()%3+1; //0~3까지 렌덤하게 숫자 발생



    do

    {

        printf("\n가위바위보게임을 시작합니다 \n1.가위, 2.바위 3.보 0.게임나가기\n");

        scanf("%d", &t);



        if(t==0)

        {

            printf("\n게임나가기\n");

            return 0;

        }



        else if(t<0||t>3)

        {

            printf("\n잘못된 입력했습니다.\n");

            return 0;

        }



        else if(t==a)

        {

            printf("\n비겼습니다\n");

            showcat_minigame(80);

            joygage+=3;

        }



        else if((t==1&&a==3)||(t==2&&a==1)||(t==3&&a==2))

        {

            printf("\n이겼습니다\n");

            showcat_minigame(90);

            joygage+=7;

        }



        else if((t==1&&a==2)||(t==2&&a==3)||(t==3&&a==1))

        {

            printf("\n졌습니다\n");

            showcat_minigame(100);

            joygage+=1;

        }



        buf[0] = '\0';


        printf("\n게임을 계속하시겠습니까?(y/n)\n"); //사용자가 게임 진행여부를 선택할 수 있다.

        scanf("%s", &q);
    }while(q=='y');
	return 0;
}



void select_minigame()

{

    int mg;


    while(1){
    printf("\n게임을 선택해 주세요!\n1. 랜덤 숫자 맞추기   2. 가위바위보   0. 메인 화면으로 돌아가기\n");

    scanf("%d", &mg);



    if(mg==1){

        play_minigame1();
	break;}

    else if(mg==2){

        play_minigame2();
	break;}

    else if(mg==0){

        return;
	break;}
    }


}



int main(void){

 pthread_t p_thread1, p_thread2;
 int thr_id1, thr_id2;
 int status;
 int a = 1;



    pthread_mutex_init(&mutex_lock,NULL);

    pthread_create(&p_thread1,NULL,t_function,(void*)&a);
    pthread_create(&p_thread2,NULL,rand_minus,(void*)&a);

   if(thr_id1< 0 | thr_id2 < 0)
   {
        perror("thread create error!");
        exit(0);
   }
        savecatimage();
        atexit(gameover_atexit);

 printf("~!~!건냥이 키우기~!~!\n건냥이의 만족도가 하나라도 0이 되면 건냥이 키우기 실패!\nlevel 10이 되면 건냥이 키우기 성공!\n만족도를 유지시켜 건냥이를 무사히 키워주세요(=oωo=)");
                printf("\n  |￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣|\n　|!!!!게임이  시작되었습니다!!!!|            　  \n　|＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿|\n　　　 ∧∧  ||\n　　 ( ○?○)||\n　　　/　つΦ\n");

                printf("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");


	menu();
        exit(0);


}


