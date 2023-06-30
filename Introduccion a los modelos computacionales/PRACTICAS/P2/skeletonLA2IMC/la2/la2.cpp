//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
// Author      : Pedro A. Gutiérrez
// Version     :
// Copyright   : Universidad de Córdoba
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // To obtain current time time()
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <string.h>
#include <math.h>
#include <float.h> // For DBL_MAX

#include "imc/MultilayerPerceptron.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
	int c;
	
	//Estructura a utilizar por getopt_long
	static struct option long_option[]=
	{
	
		{"filetrain",	 	required_argument, 0, 't'},
		{"filetest",  		required_argument, 0, 'T'},
		{"iterations", 	required_argument, 0, 'i'},
		{"hiddenlayers", 	required_argument, 0, 'l'},
		{"neuronshidden",	required_argument, 0, 'h'},
		{"eta", 			required_argument, 0, 'e'},
		{"mu", 			required_argument, 0, 'm'},
		{"validationpatterns",  required_argument, 0, 'v'},
		{"decrementFactor",		required_argument, 0, 'd'},
		{"versionalgorithm",		required_argument, 0, 'o'},
		{"errorfunction",		required_argument, 0, 'f'},
		{"softmaxfunction",		required_argument, 0, 's'},
		{"filemodel",			required_argument, 0, 'w'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};
	
	/* Estas variables servirán para almacenar el resultado de procesar la línea de comandos */
	bool tflag=false, Tflag=false, iflag=false, lflag=false, hflag=false, eflag=false, mflag=false, vflag=false, dflag=false, pflag=false; oflag=false, fflag=false, sflag=false, wflag=false; 
	char *tvalue = NULL, *Tvalue = NULL, *ivalue = NULL, *lvalue = NULL, *hvalue = NULL, *evalue = NULL, *mvalue = NULL, *vvalue = NULL, *dvalue = NULL, *ovalue = NULL, *fvalue = NULL, *svalue = NULL, *wvalue = NULL;
	
	/* getopt_long guardará el índice de la opción en esta variable. */
	int option_index = 0;
	
	/* Deshabilitar la impresión de errores por defecto */
	/* opterr=0; */
	while ((c = getopt_long (argc, argv, "t:T:i:l:h:e:m:v:d:o:f:s:w:", long_option, &option_index))!=-1)
	{
		/* El usuario ha terminado de introducir opciones */
		if (c == -1)
			break;
		switch (c)
		{
			case 't':			//Nombre fichero que contiene los datos de entrenamiento, sin este no funciona el programa
				printf("Opción -t con valor '%s' \n", optarg);
				tflag=true;
				tvalue = optarg;
				break;

			case 'T':			//Nombre fichero que contiene los datos de test. Si no se especifica utiliza los datos de entrenamiento como test
				printf("Opción -T con valor '%s'\n", optarg);
				Tflag=true;
				Tvalue = optarg;
				break;

			case 'i':			//Numero Iteraciones del bucle externo. Si no se especifica = 1000 iteraciones
				printf("Opción -i con valor '%s'\n", optarg);
				iflag=true;
				ivalue = optarg;
				break;

			case 'l':			//Numero de capas ocultas. Si no se especifica utilizar 1
				printf("Opción -l con valor '%s'\n", optarg);
				lflag=true;
				lvalue = optarg;
				break;

			case 'h':			//Numero de neuronas en cada una de las capas ocultas. Si no se especifica utilizar 4
				printf("Opción -h con valor '%s'\n", optarg);
				hflag=true;
				hvalue = optarg;
				break;
				
			case 'e':			//Indica el valor del parametro eta. Por defecto utilizar 0.7
				printf("Opción -e con valor '%s'\n", optarg);
				eflag=true;
				evalue = optarg;
				break;
			
			case 'm':			//Indica el valor del parametro mu. Por defecto utilizar 1
				printf("Opción -m con valor '%s'\n", optarg);
				mflag=true;
				mvalue = optarg;
				break;
			
			case 'v':			//Indica el ratio de patrones de entrenamiento a utilizar como validacion
				printf("Opción -v con valor '%s'\n", optarg);
				vflag=true;
				vvalue = optarg;
				break;
			
			case 'd':			//Indica el valor del Factor de decremento F. Por defecto utilizar F = 1
				printf("Opción -d con valor '%s'\n", optarg);
				dflag=true;
				dvalue = optarg;
				break;
				
			case 'o':			//Booleano que indica si se va a utilizar la version on-line. Si no se especifica utilizar off-line.
				printf("Opción -o con valor '%s'\n", optarg);
				oflag=true;
				ovalue = optarg;
				break;
				
			case 'f':			//Funcion de error que se va a utilizar. 0 Para función MSE y 1 para entropía cruzada. Por defecto usa MSE
				printf("Opcion -f con valor '%s'\n", optarg);
				fflag=true;
				fvalue = optarg;
				break;
			
			case 's':			//Booleano que indica si se utiliza la función softmax en capa de salida. Si no se especifica usa sigmoide.
				printf("Opcion -s con valor '%s'\n", optarg);
				sflag=true;
				svalue = optarg;
				break;
				
			case 'w':			//Indica el nombre del fichero en el que se almacenaran la configuracion y el valor de los pesos del modelo entrenado
				printf("Opción -w con valor '%s'\n", optarg);
				wflag=true;
				wvalue = optarg;
				break;
			
			case '?':
				/* getopt_long ya imprime su mensaje de error, no es necesario hacer nada */
				/* Si queremos imprimir nuestros propios errores, debemos poner opterr=0,
				 y hacer algo como lo que se expone a continuacion.
				if (optopt == 'c')
					fprintf (stderr, "La opción %c requiere un argumento.\n", optopt);*/
				//Nosotros solo mostraremos una ayuda 
				std::cout << std::endl;
				cout << "PARAMETROS Y BANDERAS VÁLIDAS" << endl;
				cout << "-t: Fichero con los datos de entrenamiento \t Obligatorio" << endl;
				cout << "-T: Fichero con los datos de test \t Si no se introduce utilizara entrenamiento como test" << endl;
				cout << "-i: Número de iteraciones \t Por defecto=1000" << endl;
				cout << "-l: Número de capas ocultas \t Por defecto=1" << endl;
				cout << "-h: Número de neuronas en capa oculta \t Por defecto=5" << endl;
				cout << "-e: Valor del parámetro eta \t Por defecto=0.7" << endl;
				cout << "-m: Valor del parámetro mu\t Por defecto=1" << endl;
				break;

			default:
				abort ();
		}
	}

	/* Imprimir el resto de argumentos de la línea de comandos que no son opciones con "-" */
	if (optind < argc)
	{
		printf("Argumentos ARGV que no son opciones: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		putchar ('\n');
	}
	
		
	if(tflag == false){
		std::cout << "Parametro -t es obligatorio" << std::endl;
		return EXIT_FAILURE;
	}


    if (!pflag) {
        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

        // Multilayer perceptron object
    	MultilayerPerceptron mlp;

        // Parameters of the mlp. For example, mlp.eta = value
        int iterations, neuronas, hiddenlayers;
		
		if(Tflag == false){	//iteraciones
			Tvalue = tvalue;
		}
		
		if(iflag == false){	//iteraciones
			iterations = 1000;
		}
		else{
			iterations = atoi(ivalue);
		}
		
		if(lflag == false){	//capas ocultas
			hiddenlayers = 1;
		}
		else{
			hiddenlayers = atoi(lvalue);
		}
		
		if(hflag == false){	//Neuronas
			neuronas = 4;
		}
		else{
			neuronas = atoi(hvalue);
		}
		
		if(eflag == false){	//eta
			mlp.eta = 0.7;
		}
		else{
			mlp.eta = atof(evalue);
		}
		
		if(mflag == false){	//mu
			mlp.mu = 1;
		}
		else{
			mlp.mu = atof(mvalue);
		}
		
		if(vflag == false){	//validationRatio
			mlp.validationRatio = 0.0;
		}
		else{
			mlp.validationRatio = atof(vvalue);
		}
		
		if(dflag == false){	//DecrementFactor
			mlp.decrementFactor= 1;
		}
		else{
			mlp.decrementFactor= atof(dvalue);
		}
		

    	// Type of error considered
    	int error=0; // This should be completed
    	if(fflag == true){
		error = atof(fvalue);	
	}

    	// Maximum number of iterations
    	int maxIter=1000; // This should be completed

        // Read training and test data: call to mlp.readData(...)
    	Dataset * trainDataset = mlp.readData(tvalue);
    	Dataset * testDataset = mlp.readData(Tvalue);

        // Initialize topology vector
        //int *topology = new int[layers+2];
        //topology[0] = trainDataset->nOfInputs;
        //for(int i=1; i<(layers+2-1); i++)
        //    topology[i] = neurons;
        //topology[layers+2-1] = trainDataset->nOfOutputs;
        //mlp.initialize(layers+2,topology);

		// Seed for random numbers
		int seeds[] = {1,2,3,4,5};
		double *trainErrors = new double[5];
		double *testErrors = new double[5];
		double *trainCCRs = new double[5];
		double *testCCRs = new double[5];
		double bestTestError = DBL_MAX;
		for(int i=0; i<5; i++){
			cout << "**********" << endl;
			cout << "SEED " << seeds[i] << endl;
			cout << "**********" << endl;
			srand(seeds[i]);
			mlp.runBackPropagation(trainDataset,testDataset,maxIter,&(trainErrors[i]),&(testErrors[i]),&(trainCCRs[i]),&(testCCRs[i]),error);
			cout << "We end!! => Final test CCR: " << testCCRs[i] << endl;

			// We save the weights every time we find a better model
			if(wflag && testErrors[i] <= bestTestError)
			{
				mlp.saveWeights(wvalue);
				bestTestError = testErrors[i];
			}
		}


		double trainAverageError = 0, trainStdError = 0;
		double testAverageError = 0, testStdError = 0;
		double trainAverageCCR = 0, trainStdCCR = 0;
		double testAverageCCR = 0, testStdCCR = 0;

        // Obtain training and test averages and standard deviations

		cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

		cout << "FINAL REPORT" << endl;
		cout << "*************" << endl;
	    cout << "Train error (Mean +- SD): " << trainAverageError << " +- " << trainStdError << endl;
	    cout << "Test error (Mean +- SD): " << testAverageError << " +- " << testStdError << endl;
	    cout << "Train CCR (Mean +- SD): " << trainAverageCCR << " +- " << trainStdCCR << endl;
	    cout << "Test CCR (Mean +- SD): " << testAverageCCR << " +- " << testStdCCR << endl;
		return EXIT_SUCCESS;
    } else {

        //////////////////////////////
        // PREDICTION MODE (KAGGLE) //
        //////////////////////////////

        // You do not have to modify anything from here.
        
        // Multilayer perceptron object
        MultilayerPerceptron mlp;

        // Initializing the network with the topology vector
        if(!wflag || !mlp.readWeights(wvalue))
        {
            cerr << "Error while reading weights, we can not continue" << endl;
            exit(-1);
        }

        // Reading training and test data: call to mlp.readData(...)
        Dataset *testDataset;
        testDataset = mlp.readData(Tvalue);
        if(testDataset == NULL)
        {
            cerr << "The test file is not valid, we can not continue" << endl;
            exit(-1);
        }

        mlp.predict(testDataset);

        return EXIT_SUCCESS;

	}
}

