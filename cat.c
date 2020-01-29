/*
 * Linux terminalindeki cat komutunun işlevini gerçekleştiren program.
 * cat.c
 * */

#include <stdio.h>
#include <string.h>

/*Opsiyonsuz okuma*/
void readwithoutoption(int argc, char **argv){
	FILE *f;					
	for(int i = 1; i < argc; i++){
		f = fopen(argv[i],"r");	
		if(f == NULL){
			fprintf(stderr, "%s", "dosya bulunamadi\n");	
			return;
		}
		char c;     
		while((c = fgetc(f)) != EOF){        
			printf("%c", c);	
		}
		printf("\n");			
		fclose(f);
	}
}

/*Opsiyonsuz yazma ve kopyalama*/
void writewithoutoption(int argc, char **argv){
	FILE *f1, *f2;						
	char s[10001];						/*kullanıcıdan alınacak dosya içeriğini tutar*/
	f1 = fopen(argv[argc-1],"w");		
	if(f1 == NULL){
		fprintf(stderr, "%s", "dosya bulunamadi\n");	
		return;
	}
	if(argc == 3){
		/*> işaretinden önce bir dosya ismi girilmediyse*/
		puts("Lutfen dosyanin icine yazmak istediklerinizi giriniz:");
		scanf("%[^/]10000s", s);		
		fprintf(f1, "%.10000s", s);	
	}
	else{
		for(int i = 1; i < argc-2; i++){
			f2 = fopen(argv[i],"r");	
			if(f2 == NULL){
				fprintf(stderr, "%s", "dosya bulunamadi\n");	
				return;
			}    
			while (fgets (s, 10000, f2) != NULL){  
				fputs(s, f1);			
			}
			fputs("\n", f1);		
			fclose(f2);
		}
	}
	fclose(f1);
}

/*Opsiyonlu okuma*/
void readwithoption(int argc, char **argv){
	FILE *f;									
	for(int i = 2; i < argc; i++){
		f = fopen(argv[i],"r");					
		if(f == NULL){
			fprintf(stderr, "%s", "dosya bulunamadi\n");	
			return;
		}
		char s[10000];							/*f dosyasının içeriğine tutan dizi*/
		int a = 1;								
		while((fgets(s, 10000, f)) != NULL){	
			if(!(strcmp(argv[1], "-b"))){	
				/*boşluk olmayan her satır numaranlandırılır*/
				if(!(strcmp(s, "\n"))){
					printf("%s", s);
				}
				else{
					printf("%d. ", a);
					printf("%s", s);
					a++;
				}
			}
			else if(!(strcmp(argv[1], "-n"))){	
				/*her satır başı numaralandırılır*/
				printf("%d. ", a);
				printf("%s", s);
				a++;
			}
		}
		printf("\n");						
		fclose(f);
	}
}

/*Opsiyonlu yazma ve kopyalama*/
void writewithoption(int argc, char **argv){
	FILE *f1, *f2;					
	char s[10001];					
	int a = 1;						
	f1 = fopen(argv[argc-1],"w");	
	if(f1 == NULL){
		fprintf(stderr, "%s", "dosya bulunamadi\n");	
		return;
	}
	if(argc == 4){
		/*> işaretinden önce bir dosya ismi girilmediyse*/
		puts("Lutfen dosyanin icine yazmak istediklerinizi giriniz:");
		while((fgets(s, 10000, stdin)) != NULL){
			if(!(strcmp(argv[1], "-b"))){	
				/*boşluk olmayan her satır numaranlandırılır*/
				if(!(strcmp(s, "\n"))){
					fprintf(f1, "%s", s);
				}
				else{
					fprintf(f1,"%d. ", a);						
					fprintf(f1,"%s", s);
					a++;
				}
			}
			else if(!(strcmp(argv[1], "-n"))){
				/*her satır başı numaranlandırılır*/
				fprintf(f1, "%d. ", a);
				fprintf(f1, "%s", s);
				a++;
			}
		}
	}
	else{
		for(int i = 2; i < argc-2; i++){
			f2 = fopen(argv[i],"r");				
			if(f2 == NULL){
				fprintf(stderr, "%s", "dosya bulunamadi\n");	
				return;
			}    
			while (fgets (s, 10000, f2) != NULL){
				if(!(strcmp(argv[1], "-b"))){		
					/*boşluk olmayan her satır numaranlandırılır*/
					if(!(strcmp(s, "\n"))){
						fprintf(f1, "%s", s);
					}
					else{
						fprintf(f1,"%d. ", a);
						fprintf(f1,"%s", s);
						a++;
					}
				}
				else if(!(strcmp(argv[1], "-n"))){	
					/*her satır başı numaranlandırılır*/
					fprintf(f1, "%d. ", a);
					fprintf(f1, "%s", s);
					a++;
				}
			}
			fputs("\n", f1);	
			fclose(f2);
		}
	}
	fclose(f1);
}

int main(int argc, char **argv){
	
	if((!(strcmp(argv[1], "-b"))) || (!(strcmp(argv[1], "-n")))){
		/*-n veya -b girilirse*/
		if(!(strcmp(argv[argc-2], ">"))){
			/*> işareti girilip ardından da bir dosya adı girildiyse*/
			writewithoption(argc, argv);
		}
		else if((argc >= 4) && (!(strcmp(argv[argc-1], ">")))){
			/*> işaretinden sonra bir dosya adı girilmediyse*/
			printf("!!!ERROR!!!\n");
			printf("> isaretinden sonra da bir dosya ismi girmeniz gerekmektedir.\n");
		}
		else{
			/*sadece dosya ismi yazıldıysa*/
			readwithoption(argc, argv);
		}
	}
	else if(!(strcmp(argv[1], "-h"))){		/*-h girilirse*/
		printf("Bu progam kullaniciya iki farkli secenek sunar.\n");
		printf("Ilk secenek opsiyonsuz okuma:\n");
		printf("\tcat file1.txt: Program file1.txt isimli dosyanin icerigini okur.\n");
		printf("\tcat file1.txt > file2.txt: Bu file1.txt nin icerigini file2.txt ye kopyalar.\n");
		printf("\tcat file1.txt file2.txt >: Once hata mesaji verir, sonra catin dogru kullanimini gosterir ve programdan cikar.\n");
		printf("\tcat > file1.txt: Once yeni bir satira gecer, sonra kullanici girisini file1.txt dosyasina yazar.\n");
		printf("Ikinci secenek ise opsiyonlu okuma:\n");
		printf("\tcat -b: Bos olmayan satirlari numaralandirir.\n");
		printf("\tcat -n: Tum satirlari numaralandirir.\n");
		printf("\tcat -h: Programin nasil kullanildigini anlatir.\n");
	}
	else if(!(strcmp(argv[argc-2], ">"))){
		/*> işareti girilip ardından da bir dosya adı girildiyse*/
		writewithoutoption(argc, argv);
	}
	else if((argc >= 3) && (!(strcmp(argv[argc-1], ">")))){
		/*> işaretinden sonra bir dosya adı girilmediyse*/
		printf("!!!ERROR!!!\n");
		printf("> isaretinden sonra da bir dosya ismi girmeniz gerekmektedir.\n");
	}
	else{
		readwithoutoption(argc, argv);
	}
	return 0;
}

