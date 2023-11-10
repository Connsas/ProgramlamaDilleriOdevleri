#include <stdio.h>
#include <stdlib.h>

char* readFromTxt(char*);
void tokenizer(char*);

//ÝSMAÝL ÖNER 02200201041
int main(){
	char *txtIsmi;
	char *txtIcerigi;
	int i = 0;
	int j;
	
	if(!(txtIsmi = malloc(100*sizeof(char)))){
		printf("Bellek Ayrilamadi");
	}
	
	printf("Lutfen txt dosyasinin adini veya yolunu giriniz. (Dosya Yolunda Turkce Karakter Kullanmayiniz) = ");
	scanf("%s", txtIsmi);
	
	txtIcerigi = readFromTxt(txtIsmi);
	printf("-----TXT ICERIGI-----");
	printf("\n");
	printf("\n");
	while(txtIcerigi[i] != '\0'){
		printf("%c",txtIcerigi[i]);
		i++;
	}
	printf("\n");
	printf("\n");
	printf("-----KELIMELER-----");
	printf("\n");
	printf("\n");
	tokenizer(txtIcerigi);
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
	
	if (filePointer == NULL)
    {
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

void tokenizer(char *txtIcerigi){
	int i = 0;
	int size;
	int j = 0;
	int k = 0;
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
	printf("{");
	for(i = 0; i < size; i++){
		j = 0;
		while(kelimeler[i][j] != '\0'){
			printf("%c",kelimeler[i][j]);
			j++;
		}
		if(i != size-1){
			printf(",");
		}	
	}
	printf("}");
}
