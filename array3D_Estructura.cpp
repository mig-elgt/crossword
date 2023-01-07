/*

Facultad de Ingenieria
Ing. En Informatica
Galicia Torrez Miguel Angel
Estructuras de Datos A y Algoritmos

Tema: Arreglos Tridimensionales en forma Grafica
Fecha: 07 de Marzo del 2010
Programa: 
          Crucigrama
*/

#include <graphics.h>
#include <winbgim.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define A 19
#define P 6
#define ANC 25
#define H 25
#define TAM 26

typedef struct
{
  int puntos;
  char name[20];
  char crucigrama[20];
  
}Records;

typedef struct
{
  int x,y;  
  char letra[1];
}Teclado;

typedef struct
{
   int x, y, color, exsistencia;
   char letra[1];
}Cubo;

int nJugadores();
char **crearArray(int );
void inicializaArray( char ** , int, Records , int *);
void liberaMemoriaArray( char ** );
void dibujaCubo(int , int , int );
Cubo ***creaContenedor(int , int , int );
void liberaMemoria(Cubo ***,int , int , int );
void inicializaContenedor(Cubo *** , int , int , int , int , char **);
void dibujaContenedor(Cubo *** , int , int , int  );
void moverDerecha( Cubo *** , int , int , int , int );
void moverIzquierda( Cubo *** , int , int , int , int );
void moverArriba( Cubo *** , int , int , int , int );
void moverAbajo(Cubo *** , int , int , int , int );
void moverAdelante( Cubo *** , int , int , int , int);
void moverAtras( Cubo *** , int , int , int , int );
void inicializaTeclado( Teclado * );
void leerLetras( char * );
void dibujaCuadro( int, int,  int );
void dibujaTeclado( Teclado *);
char vinculaLetra( char * , Cubo *** , Teclado *, char **, int, int * , Records * );
void insertaLetra( char , Cubo ***, char **, int, int *, Records * );
void comparaCrucigrama( Cubo ***, int , int , char ** , int , int * , Records *);
void retraso(int );
void juega(Records *, char *, int );
void mensaje( Records , int );
void dibuja(int , int, int );
void menu( Records * );
void imprimePuntos( Records  );
void imprimeTiempo( time_t , int * , time_t, int *);
void leerNombre( Records * );
int leerCrucigramaTime( Records * , int *);
void leerArchivoText( char *, int , int , int);
void lee_texto(int x,int y, char cadena[]);
void guardaRecords( Records );
void leerRecords();
void ordenaBurbuja( Records *, int );
void imprimeRecords( Records * , int );
void regresaMenu( int , int , int , int );
int determinaCrucigrama( int , int , int , int , int , Records *);
void leerTiempo( int * );
int nProposiciones( char * );
void inicializaLista( char **, char *);
void imprimeLista( char **, int );

int main() 
{ 
  initwindow(1000,650);
  
  Records records;
  
  //Inicializacion de records
  strcpy( records.name , "" );
  strcpy( records.crucigrama , "" );
  
  menu( &records);
  
 // printf( " Name: %s ", records.name );
 
  closegraph();
}

void menu(Records *rec)
{ 
  int x1, corX, corY, x2, y1, y2, z, tiempo, opcion,bandera = -1;
  char letra;
  
  //Coordenadas del primer cuadro
  x1 = 250;
  y1 = 120;
  x2 = 325;
  y2 = y1 + 96;
  z = 10;
  
  do
  {
     setcolor( YELLOW );
     
     setlinestyle( SOLID_LINE, 0 , 2);
     line(200, 100 , 800, 100 );
     rectangle( 200, 30,800, 610 + z );
     
     setcolor( WHITE );
     
     rectangle( x1, y1 + z,x2, y2 - z );
     rectangle( x1, y2 + z, x2 , y2 + 96 - z );
     rectangle( x1, y2 + z + 96, x2, (y2 + 2*96) - z );
     rectangle( x1, (y2 + 2*96) + z, x2, (y2 + 3*96)- z  );
     rectangle( x1, ( y2 + 3*96 ) + z, x2, ( y2 + 4*96 )- z );
     
     setcolor( WHITE );
     
     settextstyle( 1 , 0 , 0 );
    
     outtextxy( 265 , 50 , " MENU PRINCIPAL " );
     outtextxy( x1 + 150 , y1 + 30 , "JUGAR " );
     outtextxy( x1 + 140 , y1 + 125 , " RECORDS " );
     outtextxy( x1 + 140 , y1 + 225, " AYUDA " );
     outtextxy( x1 + 140 , y1 + 320, " ACERCA DE " );
     outtextxy( x1 + 140 , y1 + 417, " SALIR " );
     
     corX = mousex();
     corY = mousey();
     
     setlinestyle( SOLID_LINE, 0 , 6);
    
     // OPCION DE JUGAR    
     if( corX > x1 && corX < x2 && corY > y1 && corY < y2 - z  ) 
     {   
        dibuja( x1 + 50 , y1 + 50 , BLUE );
        setcolor( BLUE );
        line( x1 + 150 , y1 + 65, x1 + 320, y1 + 65 );
       
        if( ismouseclick( WM_LBUTTONDBLCLK ) )
        { 
           leerNombre( rec );
           opcion =  leerCrucigramaTime( rec , &tiempo);
           
           switch( opcion )
           {
              case 1: juega( rec , "lista1.txt" , tiempo);
                      break;
              case 2: juega( rec , "lista2.txt", tiempo );
                      break;
              case 3: juega( rec , "lista3.txt", tiempo );
                      break;
           }          
          guardaRecords( *rec );
        }
     }else
          {   
           dibuja( x1 + 50 , y1 + 50 , BLACK ); 
           setcolor( BLACK );
           line( x1 + 150 , y1 + 65, x1 + 320, y1 + 65 );
           
           // OPCION RECORDS
           if( corX > x1 && corX < x2 && corY > y2 +  z && corY < y2 + 96 - z  )
           {
               dibuja( x1 + 50, y2 + z + 50 , BLUE );
               
               setcolor( BLUE );
               line( x1 + 152 , y1 + 160, x1 + 392, y1 + 160 );
           
               if( ismouseclick(WM_LBUTTONDBLCLK)  )
                   leerRecords();
        }else
           {
             dibuja( x1 + 50, y2 + z + 50 , BLACK );
             setcolor( BLACK );
             line( x1 + 152 , y1 + 160, x1 + 392, y1 + 160 );
             
            //OPCION AYUDA
             if( corX > x1 && corX < x2 && corY > y2 + z + 96 && corY < ( y2 + 2*96) - z )
             {
                  dibuja( x1 + 50, ( y2 + z + 96) + 50, BLUE );
                  setcolor( BLUE );
                  line( x1 + 150 , y1 + 259, x1 + 345, y1 + 259 );
                 
                  if( ismouseclick( WM_LBUTTONDBLCLK ) ) 
                       leerArchivoText( "ayuda.txt", 250, 140 , 1);
            }else
                 {
                   dibuja( x1 + 50, ( y2 + z + 96) + 50, BLACK );
                   setcolor( BLACK );
                   line( x1 + 150 , y1 + 259, x1 + 345, y1 + 259 );
        
                   //ACERCA DE
                   if( corX > x1 && corX < x2 && corY > (y2 + 2*96) + z && corY < (y2 + 3*96)- z )
                   {
                        dibuja( x1 + 50, (y2 + 2*96) + z +50 , BLUE );
                        setcolor( BLUE );
                        line( x1 + 153 , y1 + 355 , x1 + 450, y1 + 355 );
                      
                        if( ismouseclick(WM_LBUTTONDBLCLK)  )
                                leerArchivoText( "acercaDe.txt", 250, 130 , 2 );
                   }else
                       {
                           dibuja( x1 + 50, (y2 + 2*96) + z +50 , BLACK );
                           setcolor( BLACK );
                           line( x1 + 153 , y1 + 355,  x1  + 450, y1 + 355 );
                           
                           //OPCION DE SALIR
                           if( corX > x1 && corX < x2 && corY > ( y2 + 3 * 96 ) + z && corY < ( y2 + 4*96 )- z )
                           {
                              dibuja( x1 + 50, ( y2 + 3 * 96 ) + z +50, BLUE );
                              setcolor( BLUE );
                              line( x1 + 153 , y1 + 450 , x1 + 305, y1 + 450 );
                           
                              if( ismouseclick(WM_LBUTTONDBLCLK)  ) 
                                   bandera = 1;   
                        }else
                            {
                              dibuja( x1 + 50, ( y2 + 3 * 96 ) + z +50, BLACK );
                              setcolor( BLACK );
                              line( x1 + 153 , y1 + 450 , x1 + 305, y1 + 450 );
                              
                            }   
                        }
                  }  
            }
     }
     clearmouseclick(WM_LBUTTONDBLCLK);   
    
    }while ( bandera != 1);   
}

/*
 Esta funcion  evalua el puntaje acumulado del jugador para poder determinar
 si fua ganador o perdedor, recibe como parametros la estructura records y el numero e letras
 del crucigrama*/

void mensaje( Records rec, int nLetras )
{
  cleardevice();
  
  char cad[20], tecla;
  rectangle( 190 , 80 , 810 , 570 );
  
  do
  {
    setcolor( YELLOW );             
    settextstyle( 4, 0 , 5 );
  
    if( nLetras > rec.puntos/10 )
        outtextxy( 205, 110 , " P E R D I S T E ! ! !" );
     else
        outtextxy( 220, 110 , " G A N A S T E ! ! ! " );
        
        setcolor( WHITE );
        settextstyle( 4, 0 , 2 );
    
        outtextxy( 280, 260 , " Alias : " );
        outtextxy( 510, 260 , rec.name);
        
        outtextxy( 280, 300 , " Crucigrama : " );
        strcpy( cad , rec.crucigrama );
        cad[ strlen( cad ) - 4] = 0 ;
        
        outtextxy(510, 300 , cad );
        
        sprintf( cad , " Puntos :              %d ", rec.puntos );
        outtextxy( 280, 340 , cad );
        
        settextstyle( 0, 0 , 0 );
        outtextxy( 260, 500 , " Presione  Esc para ir a menu.... " );
        
        tecla = getch();
        
   }while( /*( tecla != 13) &&*/ (tecla != 27 )  );
  
  cleardevice();       
}

/*
  La funcion leerNombre recibe por referencia el paramero r, para leer el nombre del jugador */
void leerNombre( Records *r )
{
  cleardevice();
  
  char cadena[50];
  int x , y, x1, y1, x2, y2;
  int corX, corY, bandera = -1;
  
  x = 240;
  y = 150;
  
  x1 = 490;
  y1 = 500;
  x2 = 540;
  y2 = 550;
  
  setcolor ( YELLOW );
  setlinestyle( SOLID_LINE, 0 , 2);
  
  rectangle( 190, 100 ,810, 590 );
  setcolor( WHITE );
  settextstyle( 1 , 0 , 0 );
  
  strcpy(cadena," INTRODUZCA ");
  outtextxy( x, y , cadena );
  strcpy(cadena," SU ALIAS ");
  outtextxy( x, y + 50 , cadena );
  
  settextstyle( 4, 0 , 4 );
  lee_texto( x + 20 ,y + 170, cadena );
  strcpy( r -> name , cadena ); 
  
  settextstyle( 4, 0 , 2 );
  outtextxy(  x1 + 60, y1 + 10 , "CONTINUAR" );
  rectangle( x1, y1 , x2, y2 );
  
  /* El ciclo do - while , analizan las coordenadas del mouse para dar efecto al rectangulo dibujado
     simulando la seleccion de el */
  do
  {
     corX = mousex();
     corY = mousey();
     
     setlinestyle( SOLID_LINE, 0 , 6);
     
     if( corX > x1  && corX < x2  && corY > y1 && corY < y2 ){   
            
            dibuja( x1 + 5, y1 + 5 , BLUE );
            setcolor( BLUE );
            line( x1 + 65 , y1 + 35 , x1 + 240 , y1 + 35 );
            
            if( ismouseclick(WM_LBUTTONDBLCLK)  )
                 bandera = 1;
    }else
        { 
            dibuja( x1 + 5, y1 + 5 , YELLOW );
            setcolor( BLACK );
            line( x1 + 60 , y1 + 35 , x1 + 240 , y1 + 35 );
        }     
  
       clearmouseclick(WM_LBUTTONDBLCLK);   
    
    }while ( bandera != 1);   
    
    cleardevice();
}

/* Esta funcion recibe una variable rec de tipo Records por refecencia, ya que se capturara el tipo de 
   crucigrama y posteriormente lo regresara con un valor entero */

int leerCrucigramaTime( Records *rec, int *tiempo )
{
  cleardevice();// Se limpia la pantalla
     
  int x1, x2, y1, y2, z,tiempoAux, opcion, bandera = -1;
  char cad[5], letra;
  
  x1 = 300;
  y1 = 120;
  x2 = 350;
  y2 = y1 + 96;
  z = 10;
  
  setcolor( WHITE );
 
  int corX, corY;
  
  setcolor( YELLOW );
  setlinestyle( SOLID_LINE, 0 , 2);
  rectangle( 200, 30,800, 610 + z );
  
  setcolor( WHITE );
  rectangle( x1, y1 + z, x2, y2 - z );
  rectangle( x1, y2 + z, x2 , y2 + 96 - z );
  rectangle( x1, y2 + z + 96, x2, (y2 + 2*96) - z );
  
  setcolor( LIGHTGREEN );
  settextstyle( 0 , 0 , 3 );
  outtextxy( 245 , 50 , "SELECCIONE UNO DE LOS" );
  outtextxy( 330 , 75 , " CRUCIGRAMAS " );
  
  setcolor( WHITE );
  
  outtextxy( x1 + 70 , y1 + 30 , " 1.- BASICO " );
  outtextxy( x1 + 70 , y1 + 130 , " 2.- INTERMEDIO " );
  outtextxy( x1 + 70 , y1 + 225, " 3.- AVANZADO " );
  
  /* Se determina que tipo de crucigrama fue elegido pasandoloe las cordenadas
     del primer cuadrado y la variable rec*/ 
  opcion = determinaCrucigrama( x1 , y1, x2, y2, z, rec );
  
  settextstyle( 0 , 0 , 3 );
   
  setcolor( LIGHTGREEN );
  outtextxy( 245 , y1 + 320, "ESTABLESCA SU TIEMPO " );
  outtextxy( 245 , y1 + 345, "PARA LA SOLUCION" );
  outtextxy( 245 , y1 + 365, "( max 30 min )" );
  outtextxy( 245 , y1 + 420, "TIME:" );
  
  leerTiempo( tiempo );
  
  setcolor( WHITE );
  setlinestyle( SOLID_LINE, 0 , 2);
  rectangle( x1 + 320, y1 + 450 , x2 + 300, 590 );
  settextstyle( 0 , 0 , 0 );
  outtextxy(  x1 + 365, y1 + 450 , "IR A JUEGO" ); 
  
  /* Se evaluan las coordenadas del mouse en el cuadrado, para la opcion de ir a juego 
     el ciclo termina una ves dando doble click en el cuadrado*/
  do
    {
 
     corX = mousex();
     corY = mousey();
      
     if( corX > x1 + 320  && corX < x2 + 300  && corY > y1 + 450 && corY < 590 ){   
              
              dibuja( x1 + 345, y1 + 455, BLUE );
              setcolor( BLUE );
              line( x1 + 368 , y1 + 470 , x1 + 463 , y1 + 470 );
              
               if( ismouseclick( WM_LBUTTONDBLCLK) ) 
                    bandera = 1;    
      
      }else
          { 
             dibuja( x1 + 345, y1 + 455, YELLOW );
             setcolor( BLACK );
             line( x1 + 368 , y1 + 470 , x1 + 463 , y1 + 470 );
          }     
             clearmouseclick(WM_LBUTTONDBLCLK);// Elimina la continuidad del mouse en pantalla   
      
    }while ( bandera != 1 );   
   
   cleardevice();
   
   return( opcion );
}

// Esta funcion recibe una apuntador a entero, para guardar el tiempo establecido
void leerTiempo( int *time )
{  
   char cad[5];
   int bandera = 0;
   
   do
    {    
         lee_texto( 370 , 540 , cad ); 
         
         /* Todo las lecturas en el interface del juego son de tipo cadena
            para ello, se necesita convertir la cadena tiempo en entero */
             
         *time = atoi( cad );
         
         /* Se evalua el tiempo, si esta en los rangos correspondientes, si es asi la funcion 
            termina */
         if( *time < 0 || *time >  30 )
          {
              settextstyle( 4 , 0 , 3 );
              setcolor( RED );
              outtextxy( 270, 580 , "ERROR!! intente de nuevo" );
              retraso( 1400);
              outtextxy( 270 , 580 ,"                                              " );
              //settextstyle( 4 , 0 , 3 );
          }else
                return;
     
     }while(  bandera == 0);  
}

/*
  Esta funcion recibe 5 parametros de tipo entero, que indican las coordenas del primer cuadrado
  dibujado en la pantalla de la funcion leerCrucigramaTime, y una variable de tipo estructura rec
  por referencia, ya que se guardara el tipo de crucigrama a eleguir en la estructura records.
  La funcion retornara un valor de tipo entero, que indica el tipo de crucigrama seleccionado 
*/
int determinaCrucigrama( int x1, int y1, int x2, int y2, int z, Records *rec)
{
  int corX, corY, opcAux, bandera = 0;
  
  /* 
    Este do - while controla las coordenadas del mouse, verificando se se realizan doble ciclk en
    las opciones , se copia una cadena con el nombre del crucigrama a la estrutura rec */
    
  do
  { 
    corX = mousex();
    corY = mousey();
    
    setlinestyle( SOLID_LINE, 0 , 4);
    // Crucigrama  Basico
    if( corX > x1 && corX < x2 && corY > y1 && corY < y2 - z  ) {   
          
          dibuja( x1 + 15 , y1 + 15 , BLUE );
          setcolor( BLUE );
          line( x1 + 195 , y1 + 58, x1 + 333, y1 + 58 );

          if( ismouseclick(WM_LBUTTONDBLCLK)  ){ 
             
             strcpy( rec -> crucigrama , "cruBasico.txt" ); 
             opcAux = 1;
             bandera = 1;
        }
   }else
    {   
         dibuja( x1 + 15 , y1 + 15 , BLACK );
         setcolor( BLACK );
         line( x1 + 195 , y1 + 58, x1 + 333, y1 + 58 );
         
         // Crucigrama  Intermedio
         if( corX > x1 && corX < x2 && corY > y2 + z && corY < y2 + 96 - z ) {   
                
                  dibuja( x1 + 15 , y2 + z + 15, BLUE );
                  setcolor( BLUE );
                  line( x1 + 195 , y1 + 158, x1 + 429, y1 + 158 );
                  
                  if( ismouseclick(WM_LBUTTONDBLCLK)  ){ 
                    strcpy( rec -> crucigrama , "cruIntermedio.txt" ); 
                    opcAux = 2;
                    bandera = 1;
                  }
        }else
            {   
                 dibuja( x1 + 15 , y2 + z + 15, BLACK );
                 setcolor( BLACK );
                 line( x1 + 195 , y1 + 158, x1 + 429, y1 + 158 );
    
                // Crucigrama Avanzado
                 if( corX > x1 && corX < x2 && corY > y2 + z + 96 && corY < ( y2 + 2* 96) - z  ) {   
                        
                        dibuja( x1 + 15 ,  y2 + z + 96 + 15, BLUE );
                        setcolor( BLUE );
                        line( x1 + 190 , y1 + 252, x1 + 380, y1 + 252 );
                        
                        if( ismouseclick(WM_LBUTTONDBLCLK)  ){ 
                           strcpy( rec -> crucigrama , "cruAvanzado.txt" ); 
                           opcAux = 3;
                           bandera = 1;
                        }
                }else
                    {   
                       dibuja( x1 + 15 ,  y2 + z + 96 + 15, BLACK );
                       setcolor( BLACK );
                       line( x1 + 190 , y1 + 252, x1 + 380, y1 + 252 );
                    }
              }  
       }
      clearmouseclick(WM_LBUTTONDBLCLK);   
   
   }while ( bandera != 1 );   
  
  return( opcAux );   

}

/* Esta funcion hace lectura de dos archivos ya sea ayuda.txt o acercaDe.txt.
   Recibe como parametro una cadena de caracteres que representa el nombre del archivo
   a leer , dos valores de tipo entero, que indican las coordenadas en donde se empezara a 
   imprimir lo del archivo , y una variable num de tipo entero que indica, que tipo 
   de archivo se va a leer ( 1: Ayuda 2: Acerca de  ) esta funcion es reutilizable
*/
void leerArchivoText( char *name, int x, int y , int num)
{
  cleardevice();
  
  FILE *ptrA;
  char cadena[900];
  int x1, y1, x2, y2 ;
  
  x1 = 250;
  y1 = 570;
  x2 = 300;
  y2 = 600;
  
  setcolor(WHITE ); 
       
  if( num == 1 )
      outtextxy( 390 , 50 , " AYUDA " );
  else
      outtextxy( 335 , 50 , " ACERCA DE " );
      
  setlinestyle( SOLID_LINE,0, 1);
  
  setcolor( YELLOW );
  line(200, 100 , 800, 100 );
  rectangle( 200, 30,800, 620 );
  
  setcolor( WHITE );
  rectangle( x1 , y1 , x2 , y2 );
  
  ptrA = fopen(  name , "r" );
  
  if( ptrA != NULL )
  {
     while( !feof( ptrA ) )
     {
        fgets( cadena, 900 , ptrA );
        
        cadena[ strlen( cadena )  ] = '\0' ;
        setcolor( WHITE );
     
        settextstyle( 11 , 0 , 1 );
        outtextxy( x , y , cadena );
        y += 16;
            
     }
     fclose( ptrA );
  }else
       outtextxy( 10, 20, "Error" );
  
  settextstyle( 0 , 0 , 0 );
  outtextxy( x2 + 15 ,  y1 + 7 , " IR A MENU " );
  
  regresaMenu( x1, y1 , x2 , y2 );
  
  cleardevice();
}

/* Dada las coordenas x , y, rellena uno de los cuadros del menu de color BLUE hasta
   encotrar un borde de color WHITE*/
void dibuja(int x, int y, int color)
{
   setfillstyle(SOLID_FILL, color);
   floodfill( x ,y , WHITE);
}

/* La funcion lee_texto sirve para hacer lectura en la ventana grafica,
   recibe dos parametros de tipo entero, indicando en donde se empezara
   a escribir, recibe una cadena para almacenar el nombre 
*/
void lee_texto(int x,int y, char cadena[])
{
 char tecla, var;     
 int contador=0;
 cadena[0]='\0';
 
 do{
      //Si no se presiona una tecla, se imprimira un guion definidamente
      do{  //párpadeo
			 setcolor(15);
			 outtextxy(x+textwidth(cadena),y,"_       ");
			 retraso(50);
			 setcolor(0);
			 outtextxy(x+textwidth(cadena),y,"_       ");
			 retraso(50);
			 setcolor(15);
      }while(!kbhit());
     
      tecla = getch();
     
      if(tecla==0)  // si es código extendido
         tecla=getch();
        if(tecla==8 && contador > 0)  // se presion¢ <backspace>
			{
				 setcolor(BLACK);
				 outtextxy(x,y,cadena);  // se borra en la pantalla
				 cadena[--contador]='\0';  //se borr¢ £ltimo caracter del arreglo
				 setcolor( WHITE );
				 outtextxy(x,y,cadena);
			}
		 else
			{  
              if(tecla!=13)
              {  
				 cadena[contador++]=tecla;
				 cadena[contador]='\0';
				 outtextxy(x,y,cadena);
              }
            }    
  }while(tecla!=13); 
}

// Funcion principal del juego
void juega( Records *rec, char lista[], int tiempo)
{  
  cleardevice();
  
  Cubo *** contenedor;
  Teclado tec[TAM];
  
  char **array, **listaCru, tecla, cadLetras[ TAM ];
  int  nCap ,nCol, nRen ,nLetras, page , segundos, minutos, tamLista, color ,band,  bandera = -1; 
  time_t tSeg, tMin ;
 
  band  = -1;
  segundos = minutos = -1;  
  
  tamLista = nProposiciones(lista);// Se lee el numero de renglones de una lista del crucigrama
  rec -> puntos = 0;
  nCap = 8;
  nRen = 21;
  nCol = 20;
  page = 0;
  color = YELLOW;
  
  // Se inicializa arreglo de tipo char, para almacenar las letras del alfabeto
  leerLetras( cadLetras );
 
  array = crearArray( nRen );
  listaCru = crearArray( tamLista );
  
  inicializaArray( array, nCol, *rec, &nLetras );    
  inicializaLista( listaCru, lista );
  inicializaTeclado( tec );
 
  contenedor = creaContenedor( nCap , nRen , nCol );
  inicializaContenedor( contenedor , nCap , nRen , nCol , color, array);
  
  if ( page == 1 ) // cambia a otra página, que no es visible
       page = 0;
   else
       page = 1;
  
   setactivepage ( page ); // define la página no visible como lo activa
   cleardevice();
   setvisualpage( page ); //una vez que se termina de dibujar, la pagina no visible se pone como activa 
   
   tSeg = time( NULL );
   tMin = time( NULL );
   
   tSeg += 61;
   tMin += tiempo * 60;
   
   do// Este ciclo controla los movimientos del cubo
   {
      if ( page == 1 ) // cambia a otra página, que no es visible
            page = 0;
      else
            page = 1;

      setactivepage ( page ); // define la página no visible como lo activa
      cleardevice();
      
       imprimeLista( listaCru, tamLista );
      
      // Se establce el marco del juego  
       setcolor( YELLOW);
       setlinestyle( SOLID_LINE, 0 , 2);
       line( 300 , 15 , 300 ,635   );
       rectangle( 15, 15 , 985 , 635 );
       
       setcolor( WHITE );        
       imprimePuntos( *rec );
        
       setlinestyle( SOLID_LINE, 0 , 0);
       
       dibujaContenedor( contenedor , nCap , nRen , nCol ); // dibuja en la pantalla no visible 
       dibujaTeclado( tec );
       
       setvisualpage( page ); //una vez que se termina de dibujar, la pagina no visible se pone como activa 
       
      /* Este ciclo provoca el fin del juego, ya sea que el usario haya concluido el crucigrama
         antes del tiempo preestablecido o el el tiempo se le agoto*/
       do
       {    
           if( ( minutos == 0 && segundos == 1)|| ( rec -> puntos / 10) == nLetras ){
                    band = 1;
                    break;
           }else
                if( segundos == 0 )
                {
                     tSeg += 60;
                     imprimeTiempo(  tSeg, &segundos , tMin , &minutos);
                 }else
                      imprimeTiempo(  tSeg, &segundos , tMin , &minutos);
      }while( !kbhit ()  );
    
      if( band != 1 ) 
      {    
         do
            tecla = vinculaLetra( cadLetras , contenedor , tec, array , nRen, &bandera, rec);
         while( isalpha( tecla ) && bandera != 1 );
      
         switch( tecla ) 
         {
            case 54 : 
                     moverDerecha( contenedor , nCap , nRen , nCol , color );
                     break; 
         
            case 52 : 
                     moverIzquierda( contenedor , nCap , nRen , nCol , color );
                     break; 
          
            case 56 : 
                     moverArriba( contenedor , nCap , nRen , nCol , color );
                     break; 
         
            case 50 : 
                     moverAbajo( contenedor , nCap , nRen , nCol , color );
                     break;
         
            case 55: // 7 
                    moverAtras( contenedor , nCap , nRen , nCol , color );
                     break;
  
            case 57: // 9
                    moverAdelante( contenedor , nCap , nRen , nCol , color );
                    break;
          }
        }   
   }while( band != 1 );
   
   setcolor( YELLOW );
   settextstyle( 4 , 0 , 3 );
   outtextxy( 515, 570, " F I N   D E L   J U E G O  " );
   retraso( 6000 );
   
   mensaje( *rec , nLetras );
   
   liberaMemoriaArray( array );
   liberaMemoria( contenedor , nCap , nRen , nCol );

   cleardevice();
}

/*
 Se lee de un archivo de texto el numero de lineas de este, para ello recibe com
 parametro el nombre del archivo en la cadena nameLista */
int nProposiciones( char nameLista[] )
{
  FILE *ptrA;
  char cadena[900];
  int nRen = 0;
  
  ptrA = fopen(  nameLista , "r" );
  
  if( ptrA != NULL )
  {
     while( !feof( ptrA ) )
     {
        fgets( cadena, 900 , ptrA );
        nRen++;
     }
  }else
       printf( " Error no se pudo abrir la lista ");
  
  fclose( ptrA );
  
  return( nRen );
}

/* La funcion inicialisa lista, recibe dos arreglos uno de tipo apuntador a char y uno de tipo 
  char, la funcion lee de un archivo de texto la lista del crucigrama que fue elegido */
void inicializaLista( char **arrayLista, char *nameLista )
{
  char cad[100];
  FILE *ptrA;
  int i;
     
  ptrA = fopen( nameLista, "r" );
   
  if( ptrA != NULL )
  { 
     i = 0;
     
     while( !feof( ptrA ) )
     { 
         fgets( cad, 100, ptrA );
         cad[strlen( cad ) - 1] = '\0';
       
         //Se reserva espacio para cada apuntador del arreglo
         arrayLista[i] = ( char * ) malloc( strlen( cad - 1 ) );
         strcpy( arrayLista[i] , cad );
    
         i++;
     }
  }else 
       outtextxy( 200, 300, " Error No se puede leer lalista " );

    fclose( ptrA ); 
}

// Guarda la estructura Records en un archivo de tipo binario
void guardaRecords( Records rec )
{
  FILE *ptrArch;
  
  ptrArch = fopen( "records.dat", "ab" );
  
  if( ptrArch != NULL )
      fwrite( &rec, sizeof( Records ), 1 , ptrArch );
  else
      printf(" Error no se pudo guardar eñ archivo" );
  
  fclose( ptrArch );

}

/*
  Para saber el numero de jugadores, se abre un archivo binario ( records.dat )
  y se retorna los N jugadores */
int nJugadores( )
{
   int nJugAux = 0;
   Records recAux;
   FILE *ptrArch;
   
   if(( ptrArch = fopen( "records.dat", "rb" ) ) != NULL  )
       while( !feof( ptrArch ))
       { 
          fread( &recAux, sizeof( Records ), 1, ptrArch );
          nJugAux++;
       }
   else
         printf( "Error no se puede leer el archivo " );
        
    fclose( ptrArch );
   
   return ( nJugAux );
   
}

/* Se hace lectura de un archivo binario donde se guardo la informacion del usuario 
   guardandola en un arreglo de tipo Records  y posteriormente ordenar el arreglo*/
void leerRecords()
{
  Records recAux;
  Records *arrayRec;
  int  nJug, i  = 0;
  FILE *ptrArch;
  
  nJug = nJugadores();// Se determina el numero de jugadores existentes en el archivo
  
  //Reservacion de espacio de memoria para el arreglo de tipo Records
  arrayRec = ( Records *)malloc( sizeof( Records ) * nJug -1 ); 
  
  ptrArch = fopen( "records.dat", "rb+" );
  
  // Se almacenan los datos del jugador en el arreglo de tipo Records arrayRec
  if( ptrArch != NULL )
      while( !feof( ptrArch ))
      {      
         fread( &recAux, sizeof( Records ), 1, ptrArch );
         
         strcpy( arrayRec[i].name , recAux.name );
         arrayRec[i].puntos = recAux.puntos;
         
         i++;
      }
  else
       printf( "Error no se puede leer el archivo " );
  
  fclose( ptrArch );
  
  ordenaBurbuja( arrayRec , nJug -1 );
  imprimeRecords( arrayRec , nJug -1 );
  
  free( arrayRec );// Liberacion de memoria
  arrayRec = NULL;
}

/* Recibe un arreglo de tipo Records y el numero de jugadores registrados
   en un archivo*/
void imprimeRecords( Records *a, int nJ )
{
  cleardevice();
  
  int x1,j, x2, y1, y2,x,y, corX,corY, bandera = -1;
  char cad[10];
  
  x = 250;
  y = 150;
  x1 = 250;
  y1 = 570;
  x2 = 300;
  y2 = 600;
   
  setcolor( WHITE );
  settextstyle( 1 , 0 , 0 ); 
  outtextxy( 360 , 50 , " RECORDS " );
  
  settextstyle( 4, 0 , 3 );
  outtextxy( x , y , " Nombre                Puntos" );
  
  // Imprime el nombre y los puntos de cada jugador
  for( j = 0; j < nJ ; j++, y += 30  )
  {
    settextstyle( 4, 0 , 2 );
    outtextxy( x + 30 , y + 70  , a[j].name);
    
    sprintf(cad, "%d", a[j].puntos );
    
    if( a[j].puntos < 100 && a[j].puntos > 0)
         outtextxy( x + 335 , y + 70  , cad);
    else
        if( a[j].puntos == 0 )
             outtextxy( x + 351 , y + 70  , cad);
        else
             outtextxy( x + 320 , y + 70  , cad);
   }
  
  setlinestyle( SOLID_LINE,0, 1);
  rectangle( x1 , y1 , x2 , y2 );
  
  settextstyle( 0, 0 , 0 );
  outtextxy( x2 + 15 ,  y1 + 7 , " IR A MENU " );
  
  setcolor( YELLOW );
  line(200, 100 , 800, 100 );
  line(500, 130 , 500, 530 );
  line(230, 190 , 770, 190 );
  rectangle( 200, 30,800, 620 );
  
  regresaMenu( x1 ,y1 , x2, y2 );
  
  cleardevice();
}

/*
  La funcion regresaMenu recibe como parametros las coordenadas de algun rectangulo
  y posteriormeente analiza las coordenadas del mause()con las del rectangulo y poder vincularse 
  al menu pricipal */
void regresaMenu( int x1, int y1, int x2, int y2 )
{
   int corX, corY, bandera = 0;
   
   do
   {  
      setlinestyle( 0, 0 , 4 ); 
      
      corX = mousex();
      corY = mousey();
     
       if( corX > x1 && corX < x2 && corY > y1 && corY < y2 )
       {
          dibuja( x1 + 30 , y1 + 10, BLUE );
          setcolor( BLUE );
          line( x2 +  25 , y1 + 25 , x2 + 115 , y1 + 25 );
        
            if( ismouseclick(WM_LBUTTONDBLCLK)  ) 
                bandera = 1;
      }else
          { 
             dibuja( x1 + 30 , y1 + 10, YELLOW );
             setcolor( BLACK );
             line( x2 +  25 , y1 + 25 , x2 + 115 , y1 + 25 );
          }     
      
      clearmouseclick(WM_LBUTTONDBLCLK);   
  
    }while ( bandera != 1);   
}

/*
 Se hace uso de uno de los metodos de ordenacion menos eficientes 
 para porder reagrupar el puntaje de los jugadores en forma drecreciente,
 recibe como parametro la estructura Records y el numero de jugadores */
 
void ordenaBurbuja( Records *a , int nJ )
{
  int i , pas, bandera = 1;
  Records aux;

  for( pas = 1; pas < nJ  && bandera == 1  ; pas ++ )
  { 
     bandera  = 0; 
      
    for( i = nJ -1; i > 0 ; i-- )
         if( a[ i ].puntos > a[ i - 1 ].puntos )
         { 
           aux.puntos  = a[ i ].puntos;
           a[ i ].puntos = a[ i - 1 ].puntos;
           a[ i - 1 ].puntos = aux.puntos;
           
           strcpy( aux.name ,  a[ i ].name );
           strcpy( a[ i ].name ,  a[ i - 1].name );
           strcpy( a[ i - 1].name ,  aux.name );
           
           bandera = 1;
         } 
  }
}

/*
  La funcion imprimePuntos escribe el puntaje actual del jugador durante el juego
  recibe como parametro una variable e tipo Record */
void imprimePuntos( Records r )
{  
   char cad[10];
   
   rectangle( 315 , 30 , 510 , 80 );
   
   setcolor( YELLOW );   
   settextstyle( 9 , 0 , 1 );
   outtextxy( 330, 45 , " PUNTOS : " );
   
   setcolor( WHITE );
   sprintf( cad , "%d", r.puntos  );
   outtextxy( 455, 45 , cad );
   settextstyle( 0 , 0 , 0);
}


// Se imprime el tiempo transcurrido durante el juego
void imprimeTiempo( time_t tS, int *seg , time_t tM, int *min)
{
   time_t t2 ;
   char  cad[5];
      
   t2 = time( NULL );
   
   setlinestyle( SOLID_LINE, 0 , 2);
   
   setcolor( WHITE );
   rectangle( 315, 575, 510, 620 );
   
   setcolor( YELLOW );
   outtextxy( 320, 590 , " TIEMPO " );
   
   sprintf( cad, " %d:%d ", ( tM - t2)/60 , ((tS - t2) - 1) );
   setcolor( WHITE );
   outtextxy( 410, 590 , cad );
   
   *seg = tS - t2 ;
   *min = ( tM - t2)/60;
   
}

void moverDerecha( Cubo *** a, int p, int r, int c, int color) 
{
  int i , j , k ;

  for( k = 0; k < p; k++)
    for( i = 0; i < r; i++)
      for( j = 0; j < c; j++){
        if( (j == c-1 ) && ( a[k][i][j].color == color) ) { 
             a[k][i][j].color = a[k][i][(j-c) + 1].color;
             a[k][i][(j-c)+1].color = color;
        }else
             if(  j == c -2 && a[k][i][j].color == color ) { 
                 a[k][i][j].color = a[k][i][ c - 3 ].color ;
                 a[k][i][j += 1].color = color;     
             }else
                if(  j == 0 && a[k][i][j].color == color ) { 
                   a[k][i][j].color = WHITE;
                   a[k][i][j += 1].color = color;     
                }else    
                     if( a[k][i][j].color == color ) { 
                        a[k][i][j].color = a[k][i][j += 1].color;
                        a[k][i][j++].color = color;
              }
    }    
}

void moverIzquierda( Cubo ***a, int p, int r, int c, int color )
{
  int i , j , k;
  
  for( k = 0; k < p; k++ )
    for( i = 0; i < r; i++ )
         if( a[k][i][0].color == color ) {   
            a[k][i][0].color = a[k][i][c-1].color;
            a[k][i][c-1].color = color;
         }else
            for( j = 1; j < c; j++)
               if( j == c -1 && a[k][i][j].color == color ){
                  a[k][i][j].color = WHITE;
                  a[k][i][j-1].color = color;
               }else
                  if( j == 1 && a[k][i][j].color == color ){
                      a[k][i][j].color =a[k][i][j+1].color;
                      a[k][i][0].color = color;
                 }else
                     if( a[k][i][j].color == color ) {   
                        a[k][i][j].color = a[k][i][j-1].color;
                        a[k][i][j-1].color = color;
                      }
    
} 

void moverArriba( Cubo *** a, int p, int r, int c, int color )
{
  int i ,j , k;
  
  for( k = 0; k < p; k++)
    for( i = 0; i < r; i++)
      for( j = 0; j < c; j++) {
         if( (i == ( r-1) ) && ( a[k][i][j].color == color ) ) {
              a[k][i][j].color = a[k][i - ( r-1) ][j].color;
              a[k][i-(r-1)][j].color = color;
         }else
               if( a[k][i][j].color == color){ 
                  a[k][i][j].color = a[k][i+1][j].color;
                  a[k][++i][j].color = color;
               }
       }    
}

void moverAbajo( Cubo ***a, int p, int r, int c, int color )
{ 
  int i , j , k;

  for( k = 0 ; k < p ; k++)
    for( j = 0; j < c; j++)
        if( a[k][0][j].color == color ) {
            a[k][0][j].color = a[k][r-1][j].color ;
            a[k][r-1][j].color = color;
          }else
             for( i = 1 ; i < r ; i++) 
                  if( a[k][i][j].color == color ){  
                       a[k][i][j].color = a[k][i -1][j].color;
                       a[k][i-1][j].color = color;
                    }
}

void moverAtras( Cubo ***a, int p, int r, int c, int color)
{
  int i , j , k;
  
  for( i = 0 ; i < r ; i++) 
     for( j = 0 ; j < c ; j++) 
             for( k = p-3; k >= 0 ; k-- )
                  if( k == p-2 && a[k][i][j].color == color ){
                       a[k][i][j].color =  a[k-1][i][j].color;
                       a[k + 1 ][i][j].color = color;
                  }else
                    if( k == 0 && a[k][i][j].color == color ){    
                        a[k][i][j].color = a[p-1][i][j].color;
                        a[k + 1][i][j].color = color;
                    }else    
                        if(a[k][i][j].color == color ) {  
                          a[k][i][j].color =  a[k+1][i][j].color;
                          a[k+1][i][j].color = color;
                         }
}

void moverAdelante( Cubo ***a, int p, int r, int c, int color )
{
  int i , j , k;
  
  for( i = 0; i < r; i++ ) 
      for( j = 0; j < c; j++ )
             for( k = 1; k < p; k++ )
                 if( k == 1 && a[k][i][j].color == color ){ 
                     a[k][i][j].color = a[k + 1][i][j].color;
                     a[0][i][j].color = color;
                 }else
                     if( k == p-1 && a[k][i][j].color == color ){ 
                         a[k][i][j].color = WHITE;
                         a[p-2][i][j].color = color;
                     }else
                          if(a[k][i][j].color == color ){
                               a[k][i][j].color = a[k - 1][i][j].color;
                               a[k-1][i][j].color = color;
                          }
}

// Se reserva espacio de memoria para un arreglo de tipo apuntador a char
char **crearArray( int nR )
{
   char **arrayAux;
   
   arrayAux = ( char ** )malloc( sizeof( char * ) * nR );
   
   return( arrayAux );
}

/* Esta funcion recibe 4 parametros, un arreglo ( a )de tipo apuntador, una varible ( nC )de tipo entero
   una instancia ( rec ) de tipo Records y una varible (*nL) de tipo entero por referencia.
   La funcion se encarga de abrir y leer de un archivo de texto el crucigrama que se haya 
   escogido durante el juego, almacenado este en la estrutura Records y asi poder inicialiazar
   cada apuntador del arreglo de tipo puntero, se hace una contabilizacion de el numero 
   de caracteres que tiene el crucigrama para una funcionalidad en la impresion de ello*/
   
void inicializaArray( char **a , int nC, Records rec, int *nL)
{
   char cad[100], cadAux[1];
   FILE *ptrA;
   int x,y ,i, j;
    
    x = 20;
    y = 35;
   *nL = 0;
     
   ptrA = fopen( rec.crucigrama, "r" );
   
   if( ptrA != NULL )
   { 
     i = 0;
      
      while( !feof( ptrA ) )
      { 
       
       fgets( cad, 100, ptrA );
       cad[strlen( cad ) - 1] = '\0';
       
       //Se reserva espacio para cada apuntador del arreglo
       a[i] = ( char * ) malloc( nC  * sizeof( char ) );
       strcpy( a[i] , cad );
       
       for( j = 0; j < strlen( a[i] ); j++ )
            if( isalpha( a[i][j] ) )
                *nL += 1; 
       i++;
       }
       
       a[i] = ( char * ) malloc( nC  * sizeof( char ) );
       strcpy( a[i] , "" );
      
     }else 
     outtextxy( 200, 300, " Error de lectura " );

    fclose( ptrA ); 
}     

/* La incializacion del contenedor implica, determinar que cubos seran vistos durante el juego
   para mostrar el crucigrama en una de las capas del contenedor, se pasa como parametro el arreglo 
   de tipo apuntador que contiene el crucigrama*/
void inicializaContenedor( Cubo ***a, int p, int r, int c, int color, char **arrayCad )
{
  int i , j , k , l, x;
  
  l = 65;
  x = r - 1;
  
  for( k = 0; k < p; k++ )
    for( i = 0; i < r ; i++, x-- )
      for( j = 0; j < c; j++) 
       { 
        
        if( i == 0 || k == 0)
            a[k][i][j].exsistencia  = 1 ;
         else
             a[k][i][j].exsistencia  = 0 ;
       
       if( k == p-1 && i == 0 )
           a[k][i][j].exsistencia  = 0 ;
       
       // Coordenadas de cada cubo
        a[k][i][j].x = ( 200 + A * j - k * A /  2 ) + 380;
        a[k][i][j].y = ( 200 - A * i + k * P ) + 216;
        
        strcpy(a[k][i][j].letra, "" );
           
        if( ( k < p-1 && k > 0  ) && ( j < c-1  && j > 0 ) )            
             a[k][i][j].color =  RED;
        else
           a[k][i][j].color = WHITE;
        
        // Se analiza cada componente del la matriz que contiene el crucigrama
        if( k == 0 )
            if( isalpha( arrayCad[x][j] )  )
               a[k][i][j].exsistencia = 1;
            else
               a[k][i][j].exsistencia = 0;
        
      }
       a[p-2][1][10].color  = color ;

}
/*
  Esta funcion dibuja aquellos cubos que esten en existencia, uitlizando las coordenadas
  y su campo color */
void dibujaContenedor( Cubo ***a, int p, int r, int c )
{
   int i , j , k ;
   
   for( k = 0; k < p; k++)
     for( i = 0; i < r; i++)
       for( j = 0; j < c; j++)
       {
           if( a[k][i][j].exsistencia == 1 )
               dibujaCubo( a[k][i][j].x , a[k][i][j].y , a[k][i][j].color );
           
           if(  a[k][i][j].color == YELLOW  ){   
              //  a[k][i][j].exsistencia == 1;
               dibujaCubo( a[k][i][j].x , a[k][i][j].y , a[k][i][j].color );
           }
          
           if( k == 0){
               setbkcolor( WHITE );
               setcolor( RED );
                  
               outtextxy( a[k][i][j].x + 5, a[k][i][j].y + 1, a[k][i][j].letra ); 
               setbkcolor( BLACK );
            }
        }
}

void dibujaCubo( int x, int y, int color)
{
     int poly[8];
     
     setcolor( BLACK);
     
     poly[0] = x;              // x1
	 poly[1] = y;             // y1
	 poly[2] = x + A / 2;         // x2
	 poly[3] = y - P;           // y2
	 poly[4] = x + A + A / 2;       // x3
	 poly[5] = y - P;           // y3
	 poly[6] = x + A;           // x4
	 poly[7] = y;             // y4
	 
	 //Se establece el patron para el relleno
     setfillstyle( 1, color);
 	 // Dibuja un poligono, cuyas coordenas son alamacenadas en un arreglo de tipo entero
     fillpoly( 4, poly);
	 
     bar( x, y, x + A, y + A );
	 rectangle( x, y, x + A, y + A );
     
     poly[0] = x + A;             // x1
	 poly[1] = y;             // y1
	 poly[2] = x + A;         // x2
	 poly[3] = y + A;           // y2
	 poly[4] = x + A * 3 / 2;       // x3
	 poly[5] = y + A - P;           // y3
	 poly[6] = x + A * 3 / 2;           // x4
	 poly[7] = y - P;             // y4
 	 
     setfillstyle( 1, color);
	 fillpoly( 4 , poly );
}	

// Se reserva espacio para el arreglo tridimensional de tipo Cubo
Cubo ***creaContenedor(int nCapas, int nRenglones, int nColumnas)
{
   Cubo ***ptr;
   int capas,renglon;

   ptr = (Cubo ***)malloc( nCapas * sizeof( Cubo ** ));
   
   for ( capas = 0; capas < nCapas; capas++ )
   {
     ptr[capas] = (Cubo**) malloc(nRenglones * sizeof(Cubo *));
     
     for ( renglon = 0; renglon < nRenglones; renglon++)
          ptr[capas][renglon] = (Cubo *) malloc(nColumnas * sizeof(Cubo));  
   }  
  
   return (ptr);  
}     

/* Imprime las listas correspondientes al crucigrama por resolve
   recibe como parametro un arreglo de tipo apuntador a char, 
   y el numero de renglones de la lista */
void imprimeLista( char **arrayLista, int nRen )
{
  int i, x, y;
  
  x = 25;
  y = 30;
  
  for( i = 0; i < nRen; i++ )
     if(strcmp( arrayLista[i] , "Vertical:" ) == 0 || strcmp( arrayLista[i] , "Horizontal:" ) == 0  )
        { 
          setcolor( YELLOW );
          settextstyle( 9 , 0 , 1 );
          outtextxy( x , y , arrayLista[i] );
          y+=5;
        }else
             {  
               setcolor( WHITE );
               settextstyle( 11 , 0 , 1 );
               outtextxy( x , y ,arrayLista[i] );
               y += 16;
              }
}
/* La funcion inicializaTeclado resibe como parametro un arreglo de tipo Teclado
   este arreglo contiene los campos, letra, color y cordenadas.
   Se detemina la coordenada para una las de teclas que representan una estrutura de tipo teclado,
   asi como la incializacion para el campo letra, tomando las letras mayusculas
   del codigo ASCII */

void inicializaTeclado( Teclado t[])
{ 
   char car, cad[1];
   int l , j , x ;

   x = 540;
   j = 540;
   l = 65;
   
   // Este ciclo determina las corrdenadas de cada tecla
   for( int i = 0; i < 26; i++, l++ ) 
   { 
       if( i >= 13 )
       {
        t[i].x = j - 15;
        t[i].y = 540;
        j += 30;
       }
       else{
             t[i].x = x;
             t[i].y = 510;
             x += 30 ;
           }
       
       car = l;
       cad[0] = l;
       cad[1] = '\0';
       strcpy(t[i].letra, cad );
       }
}

/*
  La funcion dibuja teclado, imprimira todas las letras que del arreglo accediendo al acampo
  letra */
void dibujaTeclado( Teclado tec[])
{
    for( int i = 0; i < 26; i++ )
   { 
     dibujaCuadro( tec[i].x, tec[i].y, WHITE );
     
     settextstyle( 0 , 0 , 0);
     setbkcolor( WHITE );
     setcolor( RED );
     
     outtextxy( tec[i].x + 6, tec[i].y - 20, tec[i].letra );  
     setbkcolor( BLACK );
   }
}

/*
  Esta funcion se encarga de dibujar un poligo de cuatro lados( cuadrado )
  recibe como parametro, el color del relleno, y las coordenas en donde se
  dara inicio al dibujo de piligonos*/
void dibujaCuadro(int x, int y, int color )
{
   int poly[8];
   
   setcolor( WHITE );
   
   poly[0] = x;              // x1
   poly[1] = y ;             // y1
   poly[2] = x;              //x + A / 2;         // x2
   poly[3] = y - H;           // y2
   poly[4] = x + ANC;       // x3
   poly[5] = y - H;           // y3
   poly[6] = x  + ANC;           // x4
   poly[7] = y;             // y4
   
   setfillstyle( 1, color);
   fillpoly( 4 , poly ); 
}

/* La funcion leerLetras resibe una arreglo tipo caracter, para inicializarlo con
   las letras mayusculas del alfabeto */
void leerLetras( char l[] )
{
  int i, car = 65;
  
  for( i = 0; i <26; i++, car++)
        l[i] = car;
}

/* 
  La funcion vincula letra, espera a que se realize un tecleo, analizando si correspode al teclado si es asi
  resaltara en el teclado virtual dicha letra  y procedera a imprimirla en el contenedor llamando a la funcion
  insertaLetra() que intrega al crucigrama, retornando la tecla presionada ya sea un digito o una legtra, recibe 
  como parametros un arreglo de tipo cadena que contiene el abecedario, el contenedor, un arreglo de tipo estructura, 
  el numero de renglones, La estrutura Records por referencia y una variable bandera de tipo entero por referencia */

char vinculaLetra( char cadAux[], Cubo ***cuboAux , Teclado t[], char **mat, int nR ,int * bandera, Records *r)
{ 
  char letraAux;
  int i ,x ;
  i = 0;
  static int contador = 0;
  
  letraAux = getch();
  
  if( isdigit( letraAux ) )
         return ( letraAux );
  else
      if( isupper( letraAux ) )
      {
          while( i < 26 &&  cadAux[i] != letraAux )
                  i ++;
          
          if( i < 26 )
          { 
          //printf( " \n%d ", ++contador );
          dibujaCuadro( t[i].x -2, t[i].y -2, YELLOW );
          setbkcolor(  YELLOW );
          setcolor( RED );
          outtextxy( t[i].x + 4, t[i].y - 20 , t[i].letra );  
         
          insertaLetra( letraAux , cuboAux , mat , nR, bandera, r);  
          }
     }
      else
         {
             setcolor( YELLOW );
             outtextxy( 590, 570, " ACTIVE BLOQ MAYUS ! !" ); 
             retraso( 1600 );
             outtextxy( 530, 570, "                                        " ); 
         }
    
    if( i < 26 ) 
    { 
        retraso( 300 );
        
        dibujaCuadro( t[i].x -2, t[i].y -2, WHITE);
        setbkcolor(  WHITE);
        setcolor( RED );
        outtextxy( t[i].x + 4, t[i].y - 20 , t[i].letra );   
        setbkcolor(  BLACK );
    
    }
    return ( letraAux );
}

/*
  Este funcion, se encarga de hacer una copia de la letra que se halla
  presionado en el teclado virtual, para ello, se necesita como parametros, el contenedor, 
  el arreglo de tipo apuntador que representa el crucigrama, el numero de renglos, una bandera
  la estructura Records y por ende la letra a insertar, antes de dibujajarla en el
  contenedor, se analiza la posicion del cubo en donde sera escrita la letra, estos , si el cubo esta 
  en la posicion correspondientes ,si es asi, entonces se hara el llamado de compaCrucigrama()
  para verificar si la letra introducida es igual a una de las letras del crucigrama y asignarla 
  al contenedor*/

void insertaLetra( char  car, Cubo ***c, char **mat, int nR, int *band, Records *r)
{
   int i , j , bandera = -1; 
   char cadAux[1];

   cadAux[0] = car;
   cadAux[1] = '\0';
   
   for( i = 0; ( i < 21 && bandera != 1 ) ; i++)
      for( j = 0; ( j < 20 && bandera != 1 ); j++)
      {   
          // Se verifica si el cubo esta en la capa del crucigrama
          if( c[0][i][j].color == YELLOW && c[0][i][j].exsistencia == 1 )
             if ( strcmp( c[0][i][j].letra , "" ) == 0 )
                {
                  strcpy( c[0][i][j].letra, cadAux );
                  setbkcolor( YELLOW );
                  setcolor( RED );
          
                  outtextxy(  c[0][i][j].x + 4 , c[0][i][j].y + 1 , c[0][i][j].letra  );  
                  setbkcolor( BLACK );
              
                  comparaCrucigrama( c , i , j , mat , nR, band , r );
              
                  bandera = 1;
                 }            
        }
}

/*
  Para efectuar la comparacion, la funcion recibe como parametro, el contenedor, las coordenadas
  actuales del cubo en donde fue isertada la letra, la matriz del crucigrama, el numero de renglones, una 
  variable de tipo  entero pasada por referencia y la estructura records.
  Si la comparacion se lleva con exito, el cubo se movera a la siguiente posicion del contenedor, ya sea 
  este horizontal o verticalmente, si no es asi, se retornara el cubo en la posico del juego y 
  se dara po menifiesto un mensaje adecuado para el usuario*/
  
void comparaCrucigrama( Cubo ***cubo, int i, int j, char **mat, int nR, int *bandera , Records *r)
{
 
   srand( time( NULL ) );
   
   // Analiza la letra inserta en el cubo con la matriz que contiene el crucigrama
   if( cubo[0][i][j].letra[0] == mat[ ( nR - 1 ) - i ][ j ] )
   {   
      r -> puntos += 10;
      
      if(  cubo[0][i][j+1].exsistencia && j < 19 )
      {
           cubo[0][i][j].color = WHITE;
           cubo[0][i][j+1].color  = YELLOW ;
           *bandera = 1;
      }else
            if(  cubo[0][i-1][j].exsistencia )
            {
                 cubo[0][i][j].color = WHITE;
                 cubo[0][i-1][j].color  = YELLOW ;
                 *bandera = 1;
            }
   }else
         {
    
           strcpy( cubo[0][i][j].letra, "" );
           setcolor( WHITE );
         
           switch( 1 + rand() % 9 )
           {
            case 1:  setcolor( YELLOW );      
                     outtextxy( 650, 570, " ESTUVISTE CERCA " ); 
                     break; 
            case 2:  setcolor( YELLOW );      
                     outtextxy( 650, 570, " FRIO " ); 
                     break;
            case 3:  setcolor( YELLOW );      
                     outtextxy( 650, 570, " CALIENTE " ); 
                     break;
            case 4:  setcolor( YELLOW );      
                     outtextxy( 650, 570, " TU PUEDES " ); 
                     break;
            case 5:  setcolor( YELLOW );      
                     outtextxy( 650, 570, " ANIMO " ); 
                     break;
            case 6:  setcolor( YELLOW );      
                     outtextxy( 650, 570, " MUY MAL" ); 
                     break;
            case 7:  setcolor( YELLOW );      
                     outtextxy( 650, 570, "HIBAS BIEN" ); 
                     break;
            case 8:  setcolor( YELLOW );      
                     outtextxy( 650, 570, " NO TE DISTRAIGAS " ); 
                     break;
            case 9:  setcolor( YELLOW );      
                     outtextxy( 650, 570, " CONCENTRATE " ); 
                     break;
           }
       
         *bandera = 1;
         
         cubo[0][i][j].color = WHITE;
         cubo[6][1][ 0 + rand() % 19].color  = YELLOW ;
       
         retraso( 500 );
    }     
} 

void retraso(int ms)
{
  clock_t i,j;
 
  i=clock();
 
  do
  {
    j=clock();
  }while((j-i) < ms);  
}

void liberaMemoriaArray( char **a )
{
  int i;
  
  for( i = 0; i < 21; i++ )
     free( *(a + i) );
  
  free( a );
  
  a = NULL;
}

void liberaMemoria( Cubo ***ptr, int nCapas, int nRenglones, int nColumnas)
{
  int capas,renglon;
  
  for( capas = 0; capas < nCapas; capas++ )
  {   
    for ( renglon = 0; renglon < nRenglones; renglon++ )
        free(ptr[capas][renglon]);  /* libera columnas */
    
    free(ptr[capas]);             /* libera renglones */
  }
  
  free(ptr);                      /* libera capas */

} 
