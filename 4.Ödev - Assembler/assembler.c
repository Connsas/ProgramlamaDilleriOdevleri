#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int* kelime_satiri;
int* hatalar;
uint8_t *AX, *BX, *CX, *DX; //8 bit registerlar
uint8_t* RAM[2048];	//8 bit 2KB ram

char* readFromTxt(char*);
char** tokenizer(char*);
int sayi(char**,int);
void assembler(char**);
void HRK(uint8_t*, uint8_t*, uint8_t, int);
void TOP(uint8_t*, uint8_t*, uint8_t, int);
void CRP(uint8_t*, uint8_t*, uint8_t, int);
void CIK(uint8_t*, uint8_t*, uint8_t, int);
void BOL(uint8_t*, uint8_t*, uint8_t, int);
void VE(uint8_t*, uint8_t*, uint8_t, int);
void VEYA(uint8_t*, uint8_t*, uint8_t, int);
void DEG(uint8_t*);

//ÝSMAÝL ÖNER 02200201041
int main(){
	char *txtIsmi;
	char *txtIcerigi;
	char **kelime_adresi;
	int i = 0;
	int j;
	int ic = 0;
	int dis = 0;
	int d = 0;
	int sayici = 0;
	int kontrol = 0;
	
	if(!(hatalar = malloc(201*sizeof(int)))){
		printf("Bellek ayrilirken hata olustu.");
	}
	for(i = 0; i < 201; i++){
		hatalar[i] = 0;
	}
	i = 0;
	if(!(txtIsmi = malloc(100*sizeof(char)))){
		printf("Bellek Ayrilamadi");
	}
	
	printf("Lutfen txt dosyasinin adini veya yolunu giriniz. (Dosya Yolunda Turkce Karakter Kullanmayiniz) = ");
	scanf("%s", txtIsmi);
	
	txtIcerigi = readFromTxt(txtIsmi);
	printf("-----KAYNAK KOD-----");
	printf("\n");
	printf("\n");
	while(txtIcerigi[i] != '\0'){
		printf("%c",txtIcerigi[i]);
		i++;	
	}
	kelime_adresi = tokenizer(txtIcerigi);
	i = 0;
	printf("\n");
	printf("\n");
	
	printf("-----KELIMELER-----");
	printf("\n");
	printf("\n");
	printf("{");
	while(kelime_adresi[dis][0] != '\0'){
		ic = 0;
		while(kelime_adresi[dis][ic] != '\0'){
			printf("%c",kelime_adresi[dis][ic]);
			ic++;
		}
		dis++;
		if(kelime_adresi[dis][0] != '\0'){
			printf(",");
		}
	}
	printf("}");
	printf("\n");
	printf("\n");
	
	assembler(kelime_adresi);
	printf("\n");
	printf("\n");
	printf("-----REGISTER ICERIKLERI-----");
	printf("\n");
	printf("\n");
	
	printf("AX Register :%d\n",AX);
	printf("BX Register :%d\n",BX);
	printf("CX Register :%d\n",CX);
	printf("DX Register :%d\n",DX);
	
	system("pause");
	return 0;
}

char* readFromTxt(char* txtIsmi){
	FILE *filePointer;
	char *okunan;
	char tmp;
	int i = 0;
	
	filePointer = fopen(txtIsmi, "r");
	fseek(filePointer, 0, SEEK_END);
	int size = ftell(filePointer);
	if(!(okunan = malloc(size*sizeof(char)))){
		printf("Bellek ayrilamadi veya txt ismi yanlis");
		exit(0);
	}
	fclose(filePointer);
	
	filePointer = fopen(txtIsmi, "r");
	
	if (filePointer == NULL){
        printf("Dosya mevcut degil. \n");
    }else{
    	
    	while ((tmp = fgetc(filePointer)) != EOF)
        {
            okunan[i] = tmp;
            i++;
        }
		okunan[i] = '\0';
	}
		
	fclose(filePointer);
	return okunan;
}

char** tokenizer(char *txtIcerigi){
	int i = 0;
	int satir = 1;
	int size;
	int j = 0;
	int k = 0;
	kelime_satiri = malloc(1000*sizeof(int));
	char **kelimeler = malloc(1000*sizeof(char*));
	for(i = 0; i < 1000; i++){
		kelimeler[i] = malloc(50*sizeof(char));
	}
	
	if(kelimeler == NULL){
		printf("Bellek Ayrilamadi");
		exit(0);
	}
	
	i = 0;
	
	while(txtIcerigi[i] != '\0'){
		kelime_satiri[j] = satir;
		if((txtIcerigi[i] > 96 && txtIcerigi[i] < 123) || (txtIcerigi[i] > 64 && txtIcerigi[i] < 91) || (txtIcerigi[i] > 47 && txtIcerigi[i] < 58) || txtIcerigi[i] == 95 || txtIcerigi[i] == 46){
			kelimeler[j][k] = txtIcerigi[i];		
			k++;
			i++;
			if((txtIcerigi[i] < 48 && txtIcerigi[i] != 46) || (txtIcerigi[i] > 57 && txtIcerigi[i] < 65) || (txtIcerigi[i] > 90 && txtIcerigi[i] < 97) && (txtIcerigi[i] != 95) || txtIcerigi[i] > 122){
				kelimeler[j][k] = '\0';
				j++;
				k = 0;
			}
		}else if(txtIcerigi[i] == 10 || txtIcerigi[i] == 9 || txtIcerigi[i] == 32){
			if(txtIcerigi[i] == 10){
				satir++;
			}
			i++;
		}else{					
			if(txtIcerigi[i] == 61 || txtIcerigi[i] == 60 || txtIcerigi[i] == 62 || txtIcerigi[i] == 33 || txtIcerigi[i] == 42 || txtIcerigi[i] == 43 || txtIcerigi[i] == 45 || txtIcerigi[i] == 37 || txtIcerigi[i] == 47){
				if(txtIcerigi[i+1] == 61){
					kelimeler[j][k] = txtIcerigi[i];
					i++;
					k++;
					kelimeler[j][k] = txtIcerigi[i];
					kelimeler[j][k+1] = '\0';
					i++;
					j++;
					k = 0;	
				}else{
					if(txtIcerigi[i] == 60 || txtIcerigi[i] == 62 || txtIcerigi[i] == 33){
						kelimeler[j][k] = txtIcerigi[i];
						kelimeler[j][k+1] = '\0';
						j++;
						i++;
						k = 0;
					}else if(txtIcerigi[i] == 61){
						kelimeler[j][k] = txtIcerigi[i];
						kelimeler[j][k+1] = '\0';
						j++;
						i++;
						k = 0;
					}	
				}		
			}else if(txtIcerigi[i] == 40 || txtIcerigi[i] == 41 || txtIcerigi[i] == 91 || txtIcerigi[i] == 93 || txtIcerigi[i] == 123 || txtIcerigi[i] == 125 || txtIcerigi[i] == 59 || txtIcerigi[i] == 44){
				kelimeler[j][k] = txtIcerigi[i];
				kelimeler[j][k+1] = '\0';
				j++;
				k = 0;
				i++;
			}else if(txtIcerigi[i] == 34 || txtIcerigi[i] == 39){
				if(txtIcerigi[i] == 34){
					kelimeler[j][k] = txtIcerigi[i];
					k++;
					i++;
					while(txtIcerigi[i] != 34){
						kelimeler[j][k] = txtIcerigi[i];
						k++;
						i++;
					}
					kelimeler[j][k] = txtIcerigi[i];
					i++;
					j++;
					k = 0;
				}else{
					kelimeler[j][k] = txtIcerigi[i];
					k++;
					i++;
					while(txtIcerigi[i] != 39){
						kelimeler[j][k] = txtIcerigi[i];
						k++;
						i++;
					}
					kelimeler[j][k] = txtIcerigi[i];
					i++;
					j++;
					k = 0;
				}
				
			}else if(txtIcerigi[i] == 124 || txtIcerigi[i] == 38){
				if(txtIcerigi[i] == 124){
					if(txtIcerigi[i+1] == 124){
						kelimeler[j][k] = txtIcerigi[i];
						i++;
						k++;
						kelimeler[j][k] = txtIcerigi[i];
						kelimeler[j][k+1] = '\0';
						i++;
						j++;
						k = 0;
					}
				}else{
					if(txtIcerigi[i+1] == 38){
						kelimeler[j][k] = txtIcerigi[i];
						i++;
						k++;
						kelimeler[j][k] = txtIcerigi[i];
						kelimeler[j][k+1] = '\0';
						i++;
						j++;
						k = 0;
					}else{
						kelimeler[j][k] = txtIcerigi[i];
						i++;
						k++;
					}
				}
			}else{
				kelimeler[j][k] = txtIcerigi[i];
				kelimeler[j][k+1] = '\0';
				i++;
				j++;
				k = 0;
			}
			if(txtIcerigi[i] == 43 || txtIcerigi[i] == 45 || txtIcerigi[i] == 37 || txtIcerigi[i] == 42 || txtIcerigi[i] == 47){
				if(txtIcerigi[i] == 43){
					if(txtIcerigi[i+1] == 43){
						kelimeler[j][k] = txtIcerigi[i];
						i++;
						k++;
						kelimeler[j][k] = txtIcerigi[i];
						kelimeler[j][k+1] = '\0';
						i++;
						j++;
						k = 0;
					}else{
						kelimeler[j][k] = txtIcerigi[i];
						kelimeler[j][k+1] = '\0';
						i++;
						j++;
						k = 0;
					}
				}else if(txtIcerigi[i] == 45){
					if(txtIcerigi[i+1] == 45){
						kelimeler[j][k] = txtIcerigi[i];
						i++;
						k++;
						kelimeler[j][k] = txtIcerigi[i];
						kelimeler[j][k+1] = '\0';
						i++;
						j++;
						k = 0;
					}else{
						kelimeler[j][k] = txtIcerigi[i];
						kelimeler[j][k+1] = '\0';
						i++;
						j++;
						k = 0;
					}
				}else{
					kelimeler[j][k] = txtIcerigi[i];
					kelimeler[j][k+1] = '\0';
					i++;
					j++;
					k = 0;
				}
			}
		}		
	}
	size = j;
	kelimeler[j][0] = '\0';
	hatalar[j] = 2;
	kelime_satiri[j+1] = -1;
	return kelimeler;
}

void assembler(char** kelimeler){
	
	int i = 0;
	int t = 0;
	int ek = 0;
	int kontrol = 0;
	int cont = 0;
	int control = 0;
	char x, y;
	uint8_t *operant_bir, *operant_iki;
	uint8_t operant_sayi_bir = 0;
	uint8_t operant_sayi_iki = 0;
	int sayi_bir_mi = 0;
	int sayi_iki_mi = 0;
	
	while(kelimeler[i][0] != '\0'){
		
		x = kelimeler[i][0];
		y = kelimeler[i][1];
		
		if(kelimeler[i+1][0] == 'A'){
			operant_bir = &AX;
		}else if(kelimeler[i+1][0] == 'B'){
			operant_bir = &BX;
		}else if(kelimeler[i+1][0] == 'C'){
			operant_bir = &CX;
		}else if(kelimeler[i+1][0] == 'D'){
			operant_bir = &DX;
		}else if(kelimeler[i+1][0] != '['){
			operant_sayi_bir = (uint8_t)(sayi(kelimeler, i+1));
			sayi_bir_mi = 1;
			cont++;
		}else{
			operant_bir = &RAM[sayi(kelimeler, i+2)];
			cont++;
			control++;
		}
		
		if(control == 1){
			ek = 2;
		}else{
			ek = 0;
		}
		
		if(kelimeler[i+3+ek][0] == 'A'){
			operant_iki = &AX;
		}else if(kelimeler[i+3+ek][0] == 'B'){
			operant_iki = &BX;
		}else if(kelimeler[i+3+ek][0] == 'C'){
			operant_iki = &CX;
		}else if(kelimeler[i+3+ek][0] == 'D'){
			operant_iki = &DX;
		}else if(kelimeler[i+3+ek][0] != '['){
			operant_sayi_iki = (uint8_t)(sayi(kelimeler, i+3+ek));
			sayi_iki_mi = 1;
			cont++;
		}else{
			operant_iki = &RAM[sayi(kelimeler, i+4+ek)];
			cont++;
			control++;
		}
		
		if(kelimeler[i][0] != 'H' && cont == 2){
			printf("En az bir kayitci olmali.");
			exit(2);
		}
		cont = 0;
		
		if(x == 'H'){
			HRK(operant_bir, operant_iki, operant_sayi_iki, sayi_iki_mi);
			kontrol = 0;
		}else if(x == 'T'){
			TOP(operant_bir, operant_iki, operant_sayi_iki, sayi_iki_mi);
			kontrol = 0;
		}else if(x == 'C' && y == 'R'){
			CRP(operant_bir, operant_iki, operant_sayi_iki, sayi_iki_mi);
			kontrol = 0;
		}else if(x == 'C' && y == 'I'){
			CIK(operant_bir, operant_iki, operant_sayi_iki, sayi_iki_mi);
			kontrol = 0;
		}else if(x == 'B'){
			BOL(operant_bir, operant_iki, operant_sayi_iki, sayi_iki_mi);
			kontrol = 0;
		}else if(x == 'V' && y == 'E' && kelimeler[i][2] == '\0'){
			VE(operant_bir, operant_iki, operant_sayi_iki, sayi_iki_mi);
			kontrol = 0;
		}else if(x == 'V' && y == 'E'){
			VEYA(operant_bir, operant_iki, operant_sayi_iki, sayi_iki_mi);
			kontrol = 0;
		}else if(x == 'D'){
			DEG(operant_bir);
			kontrol = 1;
		}
		
		if(kontrol == 0 && control == 0){
			i += 4;
		}else if(kontrol == 1 && control == 0){
			i += 2;
		}else if(kontrol == 1 && control == 1){
			i += 4;
		}else if(kontrol == 0 && control == 1){
			i += 6;
		}else if(kontrol == 0 && control == 2){
			i += 8;
		}
		control = 0;
		sayi_iki_mi = 0;
		sayi_bir_mi = 0;
	}
	
	
}

void HRK(uint8_t* operant_bir, uint8_t* operant_iki,uint8_t operant_sayi_iki, int sayi_iki_mi){
	uint8_t x = *operant_iki;
	if(sayi_iki_mi == 1){
		x = operant_sayi_iki;
	}
	*operant_bir = x;
}

void TOP(uint8_t* operant_bir, uint8_t* operant_iki,uint8_t operant_sayi_iki, int sayi_iki_mi){
	uint8_t x = *operant_bir;
	uint8_t y = *operant_iki;
	if(sayi_iki_mi == 1){
		y = operant_sayi_iki;
	}
	*operant_bir = x + y;
}

void CRP(uint8_t* operant_bir, uint8_t* operant_iki,uint8_t operant_sayi_iki, int sayi_iki_mi){
	uint8_t x = *operant_bir;
	uint8_t y = *operant_iki;
	if(sayi_iki_mi == 1){
		y = operant_sayi_iki;
	}
	*operant_bir = x * y;
}

void CIK(uint8_t* operant_bir, uint8_t* operant_iki,uint8_t operant_sayi_iki, int sayi_iki_mi){
	uint8_t x = *operant_bir;
	uint8_t y = *operant_iki;
	if(sayi_iki_mi == 1){
		y = operant_sayi_iki;
	}
	*operant_bir = x - y;
}

void BOL(uint8_t* operant_bir, uint8_t* operant_iki,uint8_t operant_sayi_iki, int sayi_iki_mi){
	uint8_t x = *operant_bir;
	uint8_t y = *operant_iki;
	if(sayi_iki_mi == 1){
		y = operant_sayi_iki;
	}
	*operant_bir = x / y;
	DX = x % y;
}

void VE(uint8_t* operant_bir, uint8_t* operant_iki,uint8_t operant_sayi_iki, int sayi_iki_mi){
	uint8_t x = *operant_bir;
	uint8_t y = *operant_iki;
	if(sayi_iki_mi == 1){
		y = operant_sayi_iki;
	}
	*operant_bir = x & y;
}

void VEYA(uint8_t* operant_bir, uint8_t* operant_iki,uint8_t operant_sayi_iki, int sayi_iki_mi){
	uint8_t x = *operant_bir;
	uint8_t y = *operant_iki;
	if(sayi_iki_mi == 1){
		y = operant_sayi_iki;
	}
	*operant_bir = x | y;
}

void DEG(uint8_t* operant_bir){
	uint8_t x = *operant_bir;
	*operant_bir = ~ x;
}

int sayi(char** kelimeler, int i){
	
	int basamak_sayisi = 0;
	int j = 0;
	int sonuc = 0;
	
	while(kelimeler[i][basamak_sayisi] != '\0'){
		basamak_sayisi++;
	}
	basamak_sayisi--;
	
	while(kelimeler[i][j] != '\0'){
		sonuc += (pow(10, basamak_sayisi)*(kelimeler[i][j] - '0'));
		j++;
		basamak_sayisi--;
	}
	
	return sonuc;
}




