#include <stdio.h>
#include <stdlib.h>

int* kelime_satiri;
int* hatalar;

char* readFromTxt(char*);
char** tokenizer(char*);
int if_parser(char**,int*,int);
int else_if_parser(char**,int*,int);
int else_cumle(char**,int*,int);
int sart(char**,int*,int);
int cumle(char**,int*,int);
int sayi(char**,int*,int);
int harf(char**,int*,int);
int harf_sayi(char**,int*,int);
int lojik_opertor_mu(char**,int);
int aritmetik_opertor_mu(char**,int);
int harf_mi(char**,int);
int sayi_mi(char**,int);

//ÝSMAÝL ÖNER 02200201041

int main(){
	char *txtIsmi;
	char *txtIcerigi;
	char **kelime_adresi;
	int i = 0;
	int j;
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
	printf("\n");
	kelime_adresi = tokenizer(txtIcerigi);
	i = 0;
	if_parser(kelime_adresi, hatalar, 0);
	while(hatalar[i] != 1 && hatalar[i] != 2){
		i++;
	}
	while(hatalar[d] != 2){
		if(hatalar[d] == 1){
			kontrol = 1;
		}
		d++;
	}
	while(kelime_satiri[sayici] != kelime_satiri[i]){
		sayici++;
	}
	if(kontrol == 0){
		printf("Kaynak Kod Dogru.");
	}else{
		printf("Kaynak Kod Hatali.\n");
		printf("%d. satir %d. kelime hatali luften kontrol ediniz.", kelime_satiri[i], i-sayici+1);
	}
	
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
	kelime_satiri = malloc(200*sizeof(int));
	char **kelimeler = malloc(200*sizeof(char*));
	for(i = 0; i < 200; i++){
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

int if_parser (char** kelimeler, int* hatalar, int i){
	
	if(!(kelimeler[i][0] == 'i' && kelimeler[i][1] == 'f')){
		hatalar[i] = 1;
	}
	i++;
	if(kelimeler[i][0] != '('){
		hatalar[i] = 1;
	}
	i++;
	i = sart(kelimeler, hatalar, i);
	if(kelimeler[i][0] != ')'){
		hatalar[i] = 1;
	}
	i++;
	if(kelimeler[i][0] != '{'){
		hatalar[i] = 1;
	}
	i++;
	i = cumle(kelimeler, hatalar, i);
	if(kelimeler[i][0] != '}'){
		hatalar[i] = 1;
	}
	i++;
	while(kelimeler[i][0] == 'e' && kelimeler[i][1] == 'l' && kelimeler[i][2] == 's' && kelimeler[i][3] == 'e' && kelimeler[i+1][0] == 'i' && kelimeler[i+1][1] == 'f'){
		i = else_if_parser(kelimeler, hatalar, i);
	}
	if(kelimeler[i][0] == 'e' && kelimeler[i][1] == 'l' && kelimeler[i][2] == 's' && kelimeler[i][3] == 'e'){
		i = else_cumle(kelimeler, hatalar, i);
	}
	if(kelimeler[i][0] != '\0'){
		hatalar[i] = 1;	
	}
	return i;
}

int else_if_parser (char** kelimeler, int* hatalar, int i){
	if(!(kelimeler[i][0] == 'e' && kelimeler[i][1] == 'l' && kelimeler[i][2] == 's' && kelimeler[i][3] == 'e')){
		hatalar[i] = 1;
	}
	i++;
	if(!(kelimeler[i][0] == 'i' && kelimeler[i][1] == 'f')){
		hatalar[i] = 1;
	}
	i++;
	if(kelimeler[i][0] != '('){
		hatalar[i] = 1;
	}
	i++;
	i = sart(kelimeler, hatalar, i);
	if(kelimeler[i][0] != ')'){
		hatalar[i] = 1;
	}
	i++;
	if(kelimeler[i][0] != '{'){
		hatalar[i] = 1;
	}
	i++;
	i = cumle(kelimeler, hatalar, i);
	if(kelimeler[i][0] != '}'){
		hatalar[i] = 1;
	}
	i++;
	
	return i;
}
int else_cumle(char** kelimeler, int* hatalar, int i){
	if(!(kelimeler[i][0] == 'e' && kelimeler[i][1] == 'l' && kelimeler[i][2] == 's' && kelimeler[i][3] == 'e')){
		hatalar[i] = 1;
	}
	i++;
	if(kelimeler[i][0] != '{'){
		hatalar[i] = 1;
	}
	i++;
	i = cumle(kelimeler, hatalar, i);
	if(kelimeler[i][0] != '}'){
		hatalar[i] = 1;
	}
	i++;
	
	return i;
}

int sart(char** kelimeler, int* hatalar, int i){
	
	if(harf_mi(kelimeler, i) == 0 && sayi_mi(kelimeler, i) == 0){
		hatalar[i] = 1;		
	}
	i++;
	if(lojik_opertor_mu(kelimeler, i) == 0){
		hatalar[i] = 1;
	}
	i++;
	if(harf_mi(kelimeler, i) == 0 && sayi_mi(kelimeler, i) == 0){
		hatalar[i] = 1;
	}
	i++;
	return i;
}

int cumle(char** kelimeler, int* hatalar, int i){
	
	i = harf_sayi(kelimeler, hatalar, i);
	if(kelimeler[i][0] != '='){
		hatalar[i] = 1;
	}
	i++;
	i = harf_sayi(kelimeler, hatalar, i);
	if(kelimeler[i][0] != '}'){
		if(aritmetik_operator_mu(kelimeler, i) == 0){
			hatalar[i] = 1;
		}
		i++;
		i = harf_sayi(kelimeler, hatalar, i);
	}
	return i;
}

int sayi(char** kelimeler, int* hatalar, int i){
	
	int j = 0;
	
	while(kelimeler[i][j] != '\0'){
		if(sayi_mi(kelimeler, i) == 0){
			hatalar[i] = 1;
		}
		j++;
	}
	i++;
	return i;	
}

int harf(char** kelimeler, int* hatalar, int i){
	
	if(harf_mi(kelimeler, i) == 0){
		hatalar[i] = 1;
	}
	i++;
	
	return i;
}

int harf_sayi(char** kelimeler, int* hatalar, int i){ //Hem sayýnýn hemde harfin ayný anda gelebileceði yerler için kontrol.
	if(harf_mi(kelimeler, i) == 1){
		i++;
	}else if(sayi_mi(kelimeler, i) == 1){			
		i = sayi(kelimeler, hatalar, i);
	}else{
		hatalar[i] = 1;
		i++;
	}
	return i;
}

int harf_mi(char** kelimeler, int i){
	if((kelimeler[i][0] == 'a' || kelimeler[i][0] == 'b' || kelimeler[i][0] == 'c' || kelimeler[i][0] == 'd' || kelimeler[i][0] == 'e' || kelimeler[i][0] == 'f') && kelimeler[i][1] == '\0'){
		return 1;
	}else{
		return 0;
	}
}

int sayi_mi(char** kelimeler, int i){
	if(kelimeler[i][0] == '0' || kelimeler[i][0] == '1' || kelimeler[i][0] == '2' || kelimeler[i][0] == '3' || kelimeler[i][0] == '4' || kelimeler[i][0] == '5' || kelimeler[i][0] == '6' || kelimeler[i][0] == '7' || kelimeler[i][0] == '8' || kelimeler[i][0] == '9'){
		return 1;
	}else{
		return 0;
	}
}

int aritmetik_operator_mu(char** kelimeler, int i){
	if((kelimeler[i][0] == '+' || kelimeler[i][0] == '-' || kelimeler[i][0] == '*' || kelimeler[i][0] == '/') && kelimeler[i][1] == '\0'){
		return 1;
	}else{
		return 0;
	}
}

int lojik_opertor_mu(char** kelimeler, int i){
	if((kelimeler[i][0] == '<' && kelimeler[i][1] == '\0') || (kelimeler[i][0] == '>' && kelimeler[i][1] == '\0') || (kelimeler[i][0] == '<' && kelimeler[i][1] == '=' && kelimeler[i][2] == '\0') || (kelimeler[i][0] == '>' && kelimeler[i][1] == '=' && kelimeler[i][2] == '\0') || (kelimeler[i][0] == '=' && kelimeler[i][1] == '=' && kelimeler[i][2] == '\0')){
		return 1;
	}else{
		return 0;
	}
}


