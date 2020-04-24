#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 


int main(int argc, char *argv[]){

	float E_serie[12]={0.1, 0.12, 0.15, 0.18, 0.22, 0.27, 0.33, 0.39, 0.47, 0.56, 0.68, 0.82};

	int e_resistance(float orig_resistance, float *res_array){
		int count = 0;
		float resistans = orig_resistance;
		float counter=10000000000.0;
		float *Pek = E_serie;
		int i = 0;
		while(counter > 0.1){
			counter = counter*0.1;
			for (i=11; i>-1; i--){
				if(resistans >= Pek[i]*counter){
					res_array[0] = Pek[i]*counter;
					break;
				}
			}
			if(res_array[0] == Pek[i]*counter){
				break;
			}
		
		}
		if(res_array[0] == orig_resistance){
			return 1;
		}
		else{
			counter = 10000000000.0;
			resistans = orig_resistance - res_array[0];
			while(counter > 0.1){
				counter = counter*0.1;
				for (i=11; i>-1; i--){
					if(resistans >= Pek[i]*counter){
						res_array[1] = Pek[i]*counter;
						break;
					}
				}
				if(res_array[1] == Pek[i]*counter){
					break;
				}
			}
			count = 2;
		}
		if(res_array[0]+res_array[1] == orig_resistance){
			return 2;
		}
		else{
			counter = 10000000000.0;
			resistans = resistans - res_array[1];
			while(counter > 0.1){
				counter = counter*0.1;
				for (i=11; i>-1; i--){
					if(resistans >= Pek[i]*counter){
						res_array[2] = Pek[i]*counter;
						break;
					}
				}
				if(res_array[2] == Pek[i]*counter){
					break;
				}
			}
			count = 3;
		}
	return count;
	}

	float calc_power_r(float volt, float resistance) {
		return volt * volt / resistance;
	}

	float calc_power_i(float volt, float current) {
		return volt * current;
	}

	float calc_resistance(int count, char conn, float *array){
		float sumOhm = 0, tempOhm = 0, divideOhm = 0;

		if(array != NULL){
			if(conn != 'S' && conn != 'P'){
						return -1;
				}
			if(conn == 'S'){
				for(int i = 0; i < count; i++){
					sumOhm += array[i];
				}
				return sumOhm;
			}
			else if(conn == 'P'){
				for(int i = 0; i < count; i++){
					if(array[i]!=0)
						tempOhm += (1 / array[i]);
					else
						return -1;
				}
				divideOhm = 1 / tempOhm;
				sumOhm = divideOhm;
				return sumOhm;
			}

			divideOhm = 1 / tempOhm;
			sumOhm = divideOhm;
			return sumOhm;
		}
		return -1;
	}	













	//Variables for libresistance
	int count;
	float *array;
	char conn;

	//Variables for e_resistance
	float arrayE[3] = {1.0, 1.0, 1.0};
	float *arraypek = arrayE;
	int raknare = 0;

	float resistance;

	//Variables for libpower
	int voltage;
	float power;

	printf("Ange spänningskälla i V: ");
	scanf("%d", &voltage);
	printf("Ange koppling[S | P]: ");
	scanf(" %c", &conn);
	printf("Antal komponenter: ");
	scanf("%d", &count);
	array = (float *)malloc(sizeof(count));
	for(int i = 0; i < count; i++){
		printf("komponent %d i ohm: ", i + 1);
		scanf("%f", &array[i]);
	}
	resistance = calc_resistance(count, conn, array);
	printf("Ersättningsresistans: \n%.1f ohm\n", resistance);
	free(array);

	//printf("%0.2f",calc_resistance(count, conn, array));
	/*	
	for(int i = 0; i < count; i++){
                printf("%0.2f", array[i]);
        }
	*/
	
	//Functioncall and printouts for libpower.
	power = calc_power_r(voltage, resistance);
	printf("Effekt:\n%.2f W\n", power);

	//Funktioncall and printouts of e_resistance.
	
	count = e_resistance(resistance, arraypek);
	printf("Ersättningsresistanser i E12-serien kopplade i serie:\n");
	while(raknare<count){
		printf("%.0f\n", arrayE[raknare]);
		raknare++;
	}
	raknare = 0;

	return 0;
}	
