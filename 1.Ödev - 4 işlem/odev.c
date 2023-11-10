#include <stdio.h>

int topla (char[], int, char[], int, int, int);
int cikar (char[], int, char[], int, int, int);
int carp (char[], int, char[], int, int, int);
int duzenle (char*);

//ÝSMAÝL ÖNER 02200201041

int main(){
	char sayi1[100];
	char sayi2[100];
	int secilen, boyut1, boyut2 , max_boyut, min_boyut, i, tmp1, tmp2;

	printf("1. Sayiyi Giriniz : ");
	scanf("%s", sayi1);
	boyut1 = duzenle(sayi1);

	printf("2. Sayiyi Giriniz : ");
	scanf("%s", sayi2);
	boyut2 = duzenle(sayi2);

	if(boyut1 < boyut2){
		max_boyut = boyut2;
		min_boyut = boyut1;
	}else{
		max_boyut = boyut1;
		min_boyut = boyut2;
	}
		
	printf("\n1-Toplama\n2-Cikarma\n3-Carpma\n");
	printf("Yapmak Istediginiz Islemi Seciniz : ");
	scanf("%d",&secilen);
	printf("\n");
		
	if(secilen == 1){		//iþlem seçimi ve seçilen iþleme göre çýktýlarýn düzenlenmesinin yapýlmasý.
		
		if(boyut1 == boyut2 && (((int)(sayi1[max_boyut - 1] - '0')) + ((int)(sayi2[max_boyut - 1] - '0'))) >= 10){
			printf("  ");
		}
	
		for(i = max_boyut - 1; i >= 0; i--){
			if(boyut1 == min_boyut && (max_boyut - i) < (max_boyut - min_boyut)){
				printf("  ");
			}else{
				printf("%c ",sayi1[i]);	
			}
		
		}
	
		printf("\n");
	
		if(boyut1 == boyut2 && (((int)(sayi1[max_boyut - 1] - '0')) + ((int)(sayi2[max_boyut - 1] - '0'))) >= 10){
			printf("  ");
		}
	
		for(i = max_boyut - 1; i >= 0; i--){
			if(boyut2 == min_boyut && (max_boyut - i) < (max_boyut - min_boyut)){
				printf("  ");
			}else{
				printf("%c ",sayi2[i]);
			}

		}
		printf(" +\n");
		for(i = 0; i <= max_boyut; i++){
			printf("--");
		}
	
		printf("\n");
		
		topla(sayi1, boyut1, sayi2, boyut2, max_boyut, min_boyut);
		
	}else if(secilen == 2){
		tmp1 =(int)(sayi1[boyut1 -1] - '0');
		tmp2 =(int)(sayi2[boyut2 -1] - '0');
		
		if((tmp1 < tmp2 && boyut1 == boyut2) || boyut2 > boyut1){
			printf("  ");
		}
	
		for(i = max_boyut - 1; i >= 0; i--){
			if(boyut1 == min_boyut && (max_boyut - i) < (max_boyut - min_boyut)){
				printf("  ");
			}else{
				printf("%c ",sayi1[i]);	
			}
		
		}
	
		printf("\n");
	
		if((tmp1 < tmp2 && boyut1 == boyut2) || boyut2 > boyut1 ){
			printf("  ");
		}
	
		for(i = max_boyut - 1; i >= 0; i--){
			if(boyut2 == min_boyut && (max_boyut - i) < (max_boyut - min_boyut)){
				printf("  ");
			}else{
				printf("%c ",sayi2[i]);
			}

		}
		printf(" -\n");
		for(i = 0; i <= max_boyut; i++){
			printf("--");
		}
		printf("\n");
		cikar(sayi1, boyut1, sayi2, boyut2, max_boyut, min_boyut);
	}else if(secilen == 3){
		
		if((int)((sayi1[boyut1 - 1] - '0') * (sayi2[boyut2 - 1] - '0')) >= 10){
			printf("  ");
		}
		
		for(i = 0; i < boyut2 - 1; i++){
			if(boyut1 != 1 && boyut2 != 1){
				printf("  ");	
			} else if((boyut1 == 1 && boyut2 == 1) && (int)((sayi1[boyut1 - 1] - '0') * (sayi2[boyut2 - 1] - '0')) >= 10){
				printf("  ");
			}
		}
		for(i = boyut1 - 1; i >= 0; i--){
			printf("%c ",sayi1[i]);
		}
		printf("\n");
		if((int)((sayi1[boyut1 - 1] - '0') * (sayi2[boyut2 - 1] - '0')) >= 10){
			printf("  ");
		}
		for(i = 0; i < boyut1 - 1; i++){
			printf("  ");
		}
		for(i = boyut2 - 1; i >= 0; i--){
			printf("%c ",sayi2[i]);
		}
		printf(" x\n");
		for(i = 0; i < boyut1 + boyut2; i++){
			printf("--");
		}
		printf("\n");
		carp(sayi1, boyut1, sayi2, boyut2, max_boyut, min_boyut);
	}else{
		printf("Yanlis Tuslama Yaptiniz");
	}
	
	return 1;
}

int topla(char dizi1[], int boyut1, char dizi2[], int boyut2, int max_boyut, int min_boyut){		//toplama iþlemi.
	int sonuc[max_boyut + 1];
	int i, a, b, kalan;
	int tmp = 0;
	int integer_sayi1[max_boyut];
	int integer_sayi2[max_boyut];
	
	for(i = boyut1; i < max_boyut; i++){
		integer_sayi1[i] = 0;
	}
	
	for(i = boyut2; i < max_boyut; i++){
		integer_sayi2[i] = 0;
	}
	
	for(i = 0; i < max_boyut + 1; i++){
		sonuc[i] = 0;
	}
	
	for(i = 0; i < boyut1; i++){
		integer_sayi1[i] = dizi1[i] - '0';
	}
	
	for(i = 0; i < boyut2; i++){
		integer_sayi2[i] = dizi2[i] - '0';
	}
	
	for(i = 0; i < max_boyut; i++){
		
		a = integer_sayi1[i];
		b = integer_sayi2[i];
		kalan = (a + b) % 10;
	
		if(a + b >= 10){
			if(boyut1 > boyut2){
				integer_sayi1[i + 1]++;
			}else{
				integer_sayi2[i + 1]++;
			}	
		}
		
		sonuc[i] = kalan;
		
	}
	
	if(min_boyut == max_boyut && integer_sayi1[i-1] + integer_sayi2[i-1] >= 10){
		sonuc[i] = 1;
	}
	
	if(sonuc[max_boyut] == 0){
		i = max_boyut - 1;
	}else{
		i = max_boyut;
	}
	
	while(i >= 0){
		printf("%d ", sonuc[i]);
		i--;
	}
	
	return 1;
}

int cikar(char dizi1[], int boyut1, char dizi2[], int boyut2, int max_boyut, int min_boyut){		//cikarma iþlemi.
	int i, buyuk, kucuk, kalan, j, eksi;
	int integer_sayi1[max_boyut];
	int integer_sayi2[max_boyut];
	int sonuc[max_boyut];
	int sayi1;
	int sayi2;
	
	for(i = boyut1; i < max_boyut; i++){
		integer_sayi1[i] = 0;
	}
	
	for(i = boyut2; i < max_boyut; i++){
		integer_sayi2[i] = 0;
	}
	
	for(i = 0; i < max_boyut + 1; i++){
		sonuc[i] = 0;
	}
	
	for(i = 0; i < boyut1; i++){
		integer_sayi1[i] = dizi1[i] - '0';
	}
	
	for(i = 0; i < boyut2; i++){
		integer_sayi2[i] = dizi2[i] - '0';
	}
	
	sayi1 = integer_sayi1[boyut1 - 1];
	sayi2 = integer_sayi2[boyut2 - 1];
	
	for(i = 0; i < min_boyut; i++){
		if(boyut1 > boyut2){
			buyuk = integer_sayi1[i];
			kucuk = integer_sayi2[i];
			eksi = 0;
		}else if(boyut1 == boyut2 && sayi1 > sayi2){
			buyuk = integer_sayi1[i];
			kucuk = integer_sayi2[i];
			eksi = 0;
		}else if(boyut1 == boyut2 && sayi1 < sayi2){
			kucuk = integer_sayi1[i];
			buyuk = integer_sayi2[i];
			eksi = 1;
		}else{
			kucuk = integer_sayi1[i];
			buyuk = integer_sayi2[i];
			eksi = 1;
			
			if(sayi1 == sayi2){
				eksi = 0;
			}
		}
		
		if(buyuk - kucuk >= 0){
			kalan = buyuk - kucuk;
			sonuc[i] = kalan;
		}else{
			if(buyuk == integer_sayi1[i]){
				for(j = i + 1; j < max_boyut; j++){
					if(integer_sayi1[j] != 0){
						integer_sayi1[j]--;
						j = max_boyut;
					}else if(integer_sayi1[j] == 0){
						integer_sayi1[j] = 9;
					}
				}
			}else{
				for(j = i + 1; j < max_boyut; j++){
					if(integer_sayi2[j] != 0){
						integer_sayi2[j]--;
						j = max_boyut;
					}else if(integer_sayi2[j] == 0){
						integer_sayi2[j] = 9;
					}
				}
			}
			buyuk += 10;
			kalan = buyuk - kucuk;
			sonuc[i] = kalan;
		}
		
	}
	
	for(i = min_boyut; i < max_boyut; i++){
		if(max_boyut == boyut1){
			sonuc[i] = integer_sayi1[i];
		}else{
			sonuc[i] = integer_sayi2[i];
		}
	}
	
		if(sonuc[max_boyut] == 0){
		i = max_boyut - 1;
	}else{
		i = max_boyut;
	}
	
	if(eksi == 1){
		printf("- ");
	}
	while(i >= 0){
		printf("%d ",sonuc[i]);
		i--;
	}
	
	return 1;
}

int carp(char dizi1[], int boyut1, char dizi2[], int boyut2, int max_boyut, int min_boyut){		//çarpma iþlemi.
	int integer_sayi1[boyut1];
	int integer_sayi2[boyut2];
	int sonuc[boyut1 + boyut2];
	int i, j;
	
	for(i = 0; i < boyut1; i++){
		integer_sayi1[i] = dizi1[i] - '0';
	}
	
	for(i = 0; i < boyut2; i++){
		integer_sayi2[i] = dizi2[i] - '0';
	}
	
	for(i = 0; i < (boyut1 + boyut2); i++){
		sonuc[i] = 0;
	}
		
	for(i = 0; i < boyut1; i++){
		for(j = 0; j < boyut2; j++){
			sonuc[i + j] += integer_sayi1[i] * integer_sayi2[j];
		}
	}
	
	for(i = 0; i < (boyut1 + boyut2); i++){
		if(sonuc[i] >= 10){
			sonuc[i + 1] += sonuc[i] / 10;
			sonuc[i] = sonuc[i] % 10;			
		}
	}
	
	if(sonuc[boyut1 + boyut2 - 1] == 0){
		i = boyut1 + boyut2 - 2;
	}else{
		i = boyut1 + boyut2 -1;
	}
	
	while(i >= 0){
		printf("%d ",sonuc[i]);
		i--;
	}
	
	return 1;
}

int duzenle(char* dizi){	//alýnan stringlerin iþleme uygun hale getirlmesini saðlayan fonksiyon.
	char tmp[100];
	int i;
	int boyut = 0;
	int a = 0;
	int j = 0;

	while(dizi[j] != '\0'){
		boyut++;
		j++;
	}

	for (i = 0; i < 99; i++){
		tmp[i] = dizi[i];
	}
	
	for (i = boyut - 1; i >= 0; i--){
		dizi[i] = tmp[a++];
	}
	
	return boyut;
}
