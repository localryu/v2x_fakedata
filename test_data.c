#include <lcm/lcm.h>
#include <stdio.h>

#include "eurecar_INTER_t.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

int RED = 30;
int GREEN = 50;
int YELLOW = 10;


int i = 1, h = 0;
int j = 0, k = 30, l = 80;
int red[3] = {0,};
int green[3] = {0,};
int yellow[3] = {0,};
int inter_1st_state = 0,  inter_1st_time = 0, inter_2nd_state = 0 , inter_2nd_time = 0 , inter_3rd_state = 0, inter_3rd_time = 0;
int ds1,ds2,ds3,dt1,dt2,dt3;

void send_inter(){
	
	lcm_t *lcm = lcm_create(NULL);
	if (!lcm)
		return;

	eurecar_INTER_t intersection;
	i = (rand() % 100);

	if(h == 0){	
		for(int x = 0; x < 3; x++){
			red[x] = RED * 10 + 10;
			green[x] = GREEN * 10 + 10;
			yellow[x] = YELLOW * 10 + 10;
		}
		h++;
	}

	if(red[0] < 0)
		red[0] = RED * 10;
	if(red[1] < 0)
		red[1] = RED * 10;
	if(red[2] < 0)
		red[2] = RED * 10;
	if(green[0] < 0)
		green[0] = GREEN * 10;
	if(green[1] < 0)
		green[1] = GREEN * 10;
	if(green[2] < 0)
		green[2] = GREEN * 10;
	if(yellow[0] < 0)
		yellow[0] = YELLOW * 10;
	if(yellow[1] < 0)
		yellow[1] = YELLOW * 10;
	if(yellow[2] < 0)
		yellow[2] = YELLOW * 10;


	intersection.timestamp = 0;

	if(j < RED){
		inter_1st_state = 3;
		red[0] = red[0] - 10;
		inter_1st_time = red[0];
	}else if(j >= RED && j < RED + GREEN){
		inter_1st_state = 5;
		green[0] = green[0] - 10;
		inter_1st_time = green[0];
	}else if(j > RED + GREEN + YELLOW){
		j = 0;
	}else{
		inter_1st_state = 7;
		yellow[0] = yellow[0] - 10;
		inter_1st_time = yellow[0];
	}
	
	if(k < RED){
		inter_2nd_state = 3;
		red[1] = red[1] - 10;
		inter_2nd_time = red[1];
	}else if(k >= RED && k < RED + GREEN){
		inter_2nd_state = 5;
		green[1] = green[1] - 10;
		inter_2nd_time = green[1];
	}else if(k > RED + GREEN + YELLOW){
		k = 0;
	}else{
		inter_2nd_state = 7;
		yellow[1] = yellow[1] - 10;
		inter_2nd_time = yellow[1];
	}

	if(l < RED){
		inter_3rd_state = 3;
		red[2] = red[2] - 10;
		inter_3rd_time = red[2];
	}else if(l >= RED && l < RED + GREEN){
		inter_3rd_state = 5;
		green[2] = green[2] - 10;
		inter_3rd_time = green[2];
	}else if(l > RED + GREEN + YELLOW){
		l = 0;
	}else{
		inter_3rd_state = 7;
		yellow[2] = yellow[2] - 10;
		inter_3rd_time = yellow[2];
	}

	if(i % 7 == 1){
		fprintf(stdout, "loop : %d, j : %3d, k : %3d\n", i%7, j, k);
		ds1 = inter_1st_state;
		dt1 = inter_1st_time;
	}else if(i % 7 == 2){
		fprintf(stdout, "loop : %d, j : %3d, k : %3d\n", i%7, j, k);
		ds2 = inter_2nd_state;
		dt2 = inter_2nd_time;
	}else if(i % 7 == 3){
		fprintf(stdout, "loop : %d, j : %3d, k : %3d\n", i%7, j, k);
		ds3 = inter_3rd_state;
		dt3 = inter_3rd_time;	
	}else if(i % 7 == 4){
		fprintf(stdout, "loop : %d, j : %3d, k : %3d\n", i%7, j, k);
		ds1 = inter_1st_state;
		dt1 = inter_1st_time;
		ds2 = inter_2nd_state;
		dt2 = inter_2nd_time;
	}else if(i % 7 == 5){
		fprintf(stdout, "loop : %d, j : %3d, k : %3d\n", i%7, j, k);
		ds1 = inter_1st_state;
		dt1 = inter_1st_time;
		ds3 = inter_3rd_state;
		dt3 = inter_3rd_time;
	}else if(i % 7 == 6){
		fprintf(stdout, "loop : %d, j : %3d, k : %3d\n", i%7, j, k);
		ds2 = inter_2nd_state;
		dt2 = inter_2nd_time;
		ds3 = inter_3rd_state;
		dt3 = inter_3rd_time;
	}else{
		fprintf(stdout, "loop : %d, j : %3d, k : %3d\n", i%7, j, k);
		ds1 = inter_1st_state;
		dt1 = inter_1st_time;
		ds2 = inter_2nd_state;
		dt2 = inter_2nd_time;
		ds3 = inter_3rd_state;
		dt3 = inter_3rd_time;
	}
	
	intersection.inter_1st_state = ds1;
	intersection.inter_1st_time = dt1;
	intersection.inter_2nd_state = ds2;
	intersection.inter_2nd_time = dt2;
	intersection.inter_3rd_state = ds3;
	intersection.inter_3rd_time = dt3;

	j++;
	k++;
	l++;

	fprintf(stdout, "state : %d, time : %4d\n", intersection.inter_1st_state, intersection.inter_1st_time);
	fprintf(stdout, "state : %d, time : %4d\n", intersection.inter_2nd_state, intersection.inter_2nd_time);
	fprintf(stdout, "state : %d, time : %4d\n", intersection.inter_3rd_state, intersection.inter_3rd_time);
	fprintf(stdout, "------------------------------------\n");
	eurecar_INTER_t_publish(lcm, "INTER", &intersection);

	lcm_destroy(lcm);

}


int main( )
{
	while(1){
		send_inter();
		sleep(1);
	}
	return 1;
}
