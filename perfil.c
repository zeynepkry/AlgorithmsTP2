#include <stdio.h>
#include "perfil.h"

  char cine;
  int maldades;
  int mascotas ;
  int zodiaco;
  int tipo_elemento;
  char caracter;
  int nu_mal;
  int nu_mas;
  int intensidad;

     void ingresar_signo_del_zodiaco(int* zodiaco, int* tipo_elemento){

      		printf("ingresa un numero que corresponde tu signo del zodiaco\n" );
      		scanf(" %i",zodiaco);
	      	while ((*zodiaco < 1) || (*zodiaco > 12)){

    	        printf("ingresa un numero que corresponde tu signo del zodiaco\n");
    	        scanf("%i",&*zodiaco);
    	    }
    	    if (((*zodiaco)==1) || ((*zodiaco)==5) || ((*zodiaco)==9)){
    	        (*tipo_elemento) = 1;
    	  		 printf("TU TIPO SIGNO ES FUEGO\n");
    	  		
    	  	}else if (((*zodiaco)==2) || ((*zodiaco)==6) || ((*zodiaco)==10)){
        	    (*tipo_elemento) = 2;
      			 printf("TU TIPO SIGNO ES TIERRA\n");
	      	
	      	}else if (((*zodiaco)==3) || ((*zodiaco)==7) || ((*zodiaco)==11)){
    	         (*tipo_elemento) = 3;
    	  		 printf("TU TIPO SIGNO ES AIRE\n");
      		 
    	  	}else if (((*zodiaco)==4 )|| ((*zodiaco)==8) || ((*zodiaco)==12)){
        	     (*tipo_elemento) = 4;
      			 printf("TU TIPO SIGNO ES AGUA\n");
     
    	  	}else if (((*zodiaco) < 1 )|| ((*zodiaco) > 12)){

       		 	printf("valor invalido ingresa un valor valido\n");
        		scanf(" %i", zodiaco);

        	}
        	
     }

     void ingreasa_genero_de_cine_preferido (char* cine){

    	  	printf("ingresa genero de cine preferido \n");
      		scanf(" %c",cine);

	      	while (*cine !='A'&& *cine != 'C' && *cine != 'D' && *cine != 'T'){
    	        printf(" ingresa genero de cine de nuevo \n " );
    	        scanf(" %c", cine );
    	    }
	        switch(*cine){
    		    case 'A': 
    		    printf("accion\n");
    	    	break;

	            case 'C': 
    		    printf("comedia\n");
        	    break;

	            case 'D': 
    		    printf("drama\n");
    		    break;

	            case 'T': 
    		    printf("terror\n");
    		    break;
        
	            default:
    	        printf("ingresa un letra A,C,D,T\n");
        	}
     }   
     void ingreasa_cantidad_de_maldades_en_el_ultimo_mes (int * maldades){
	     	printf(" ingresa cantidad de maldades en el ultimo mes\n");
    	    scanf(" %i",maldades);

	      while (((*maldades) < 0 ) || ((*maldades )> 99)){
                printf(" valor invalido!ingresa cantidad_de_maldades_en_el_ultimo_mes\n");
	            scanf(" %i",maldades);
    	  }
     } 
     void ingresa_cantidad_de_mascotas (int* mascotas){
	     	printf(" ingresa cantidad de mascotas\n");
    	    scanf(" %i",&*mascotas);
	        while((*mascotas)>5){
	       	  	printf(" valor invalido!ingresa cantidad de mascotas\n");
	            scanf(" %i",&*mascotas);
	        }

     }
     void determinar_lado_de_guerra ( int* zodiaco,int* tipo_elemento,char* cine,int* maldades,int* mascotas,char* caracter ){
	     	if ((((*tipo_elemento) == 1)|| ((*tipo_elemento) == 3) ) && (((*cine) == 'C') || ((*cine )=='T')) && ((*maldades) >=50)){
			   (*caracter)='O';
	   
	    	}else if ((((*tipo_elemento) == 2) || ((*tipo_elemento) == 4)) && (((*cine) == 'A') || ((*cine) =='D')) && ((*maldades) < 50) ){
      	     
	            (*caracter)='D';
	      	}else{
    	        while (((*caracter)!= 'O') && ((*caracter)!= 'D')){
        	  	    printf(" ya no estas en ningun lado,ingresa todos los datos de nuevo \n ");
	                ingresar_signo_del_zodiaco(zodiaco,tipo_elemento);
	                ingreasa_genero_de_cine_preferido(cine);
	                ingreasa_cantidad_de_maldades_en_el_ultimo_mes(maldades);
	                ingresa_cantidad_de_mascotas(mascotas);
	                determinar_lado_de_guerra( zodiaco,tipo_elemento,cine,maldades,mascotas,caracter );
	            }
	        } 
     }
     void determinar_intensidad( int* maldades,int*mascotas,int* nu_mal,int* nu_mas,int* intensidad,char* caracter){

	     	if (((*maldades)>=0) && ((*maldades) <=9)){
    	  	  (*nu_mal) = 1;
	        }else if (((*maldades)>=10) && ((*maldades) <=19)){
	      	  (*nu_mal) = 2;
	        }else if (((*maldades)>=20) && ((*maldades) <=29)){
	      	  (*nu_mal) = 3;
	        }else if (((*maldades)>=30) && ((*maldades) <=39)){
	      	  (*nu_mal) = 4;
	        }else if (((*maldades)>=40) && ((*maldades) <=49)){
	      	  (*nu_mal) = 5;
	      	}else  if(((*maldades)>=50) && ((*maldades) <=59)){
	      	  (*nu_mal) = 1;
   	        }else if (((*maldades)>=60) && ((*maldades) <=69)){
	   	   	  (*nu_mal) = 2;
	        }else if (((*maldades)>=70) && ((*maldades) <=79)){
	      	  (*nu_mal) = 3;
	        }else if (((*maldades)>=80) && ((*maldades) <=89)){
	      	  (*nu_mal) = 4;
	        }else if (((*maldades)>=90) && ((*maldades) <=99)){
	      	  (*nu_mal) = 5;
    	  	}

	        if ((*mascotas)== 0){
    	  	  (*nu_mas) = 0;
	        }else if ((*mascotas) == 1){
	      	  (*nu_mas) = 1;
	      	}else if ((*mascotas)== 2){
	      	  (*nu_mas) = 2;
	        }else if ((*mascotas) == 3){
	      	  (*nu_mas) = 3;
	      	}else if ((*mascotas)== 4){
	      	  (*nu_mas) = 4;
	        }else if ((*mascotas) == 5){
	      	  (*nu_mas) = 5;
	      	}
	         (*intensidad) = (*nu_mal) + (*nu_mas);

	        if((*caracter)=='O'){
	     	printf("estas en lado ofensivo con intensidad %i \n", (*intensidad));
	        }else if ((*caracter)=='D'){
	     	printf("estas en lado defensivo con intensidad %i \n", (*intensidad));
	        }
     }
    	void perfil(char * tipo , int * intensidad ){
			int zodiaco;
			int tipo_elemento;
	    	ingresar_signo_del_zodiaco( &zodiaco,&tipo_elemento);
			char cine;
			ingreasa_genero_de_cine_preferido( &cine);
			int maldades;
			ingreasa_cantidad_de_maldades_en_el_ultimo_mes( &maldades);
			int mascotas;
			ingresa_cantidad_de_mascotas( &mascotas);
			
	    	determinar_lado_de_guerra( &zodiaco,&tipo_elemento,&cine,&maldades,&mascotas,tipo);
	    	int nu_mal;
	    	int nu_mas;
	    	
	    	determinar_intensidad(&maldades,&mascotas,&nu_mal,&nu_mas,intensidad,tipo);
     		
	    }
   
