/*********************************************************************
* File  : MultilayerPerceptron.cpp
* Date  : 2020
*********************************************************************/

#include "MultilayerPerceptron.h"

//#include "util.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <limits>
#include <math.h>


using namespace imc;
using namespace std;
//using namespace util;

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()
{
	layers = NULL;
	nOfLayers = 3;
	
	eta = 0.1;          
	mu  = 0.9;             
	validationRatio = 1;
	decrementFactor = 0;
}

// ------------------------------
// Allocate memory for the data structuresa
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[]) {

	if(nl>2){ //Si hay más de 3 capas
		nOfLayers = nl; //NUMERO DE CAPAS
		layers = new Layer[nl]; 
		std::cout << "Initialize -> nOfLayers: " << nOfLayers << std::endl;
		
		for(int i=0; i<nOfLayers; i++){
			layers[i].nOfNeurons = npl[i]; //NUMERO DE NEURONAS DE CADA CAPA
			std::cout << "Initialize -> layers[i].nOfNeurons: " << layers[i].nOfNeurons << std::endl;
			layers[i].neurons = new Neuron[npl[i]];	//RESERVA DE MEMORIA DE CADA NEURONA
			
			for(int j=0; j<npl[i]; j++){
				Neuron *nuevaNeurona= new Neuron; 
				layers[i].neurons[j] = *nuevaNeurona;
				
				if(i>0){
					layers[i].neurons[j].w = new double[layers[i-1].nOfNeurons+1]; //VECTOR PESOS ENTRADA
					layers[i].neurons[j].wCopy = new double[layers[i-1].nOfNeurons+1]; //COPIA PESOS ENTRADA
					layers[i].neurons[j].deltaW = new double[layers[i-1].nOfNeurons+1]; //CAMBIO A APLICAR A CADA PESO
					layers[i].neurons[j].lastDeltaW = new double[layers[i-1].nOfNeurons+1]; //ULTIMO CAMBIO
				}
			}
		}
		return 0;
	}
	return 1; //INICIALIZA FALLIDO, MENOS DE 3 CAPAS
}


// ------------------------------
// DESTRUCTOR: free memory
MultilayerPerceptron::~MultilayerPerceptron() {
	//freeMemory();
}


// ------------------------------
// Free memory for the data structures
void MultilayerPerceptron::freeMemory() {
	
	for(int i=0; i<nOfLayers; i++){
	
		for(int j=0; j<layers[i].nOfNeurons; j++){
			if(i!=0){
				delete layers[i].neurons[j].w;
				delete layers[i].neurons[j].deltaW;
				delete layers[i].neurons[j].lastDeltaW;
				delete layers[i].neurons[j].wCopy;
			}
		}
		delete layers[i].neurons;
	}
	delete layers;
}

// ------------------------------
// Feel all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	
	for(int i=1; i<nOfLayers; i++){
	
		for(int j=0; j<layers[i].nOfNeurons; j++){
			
			for(int k=0; k<layers[i-1].nOfNeurons+1; k++){
			
				double w = ((double)rand()/RAND_MAX)* pow(-1,rand());/******************************************************************************/
				//cout << "Pesos aleatorios w= "<<w<<"\tCapa: "<<i<<"\tNeurona: "<<j<<"\tPeso: "<< k <<endl;
				layers[i].neurons[j].w[k] = w; 
			}
		}
	}

}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {
	
	for(int i=0; i<layers[0].nOfNeurons; i++){
	
		layers[0].neurons[i].out = input[i];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output)
{

	for(int i=0; i<layers[nOfLayers-1].nOfNeurons; i++){
	
		output[i] = layers[nOfLayers-1].neurons[i].out;
	}	
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {
	
	for(int i=1; i<nOfLayers; i++){
	
		for(int j=0; j<layers[i].nOfNeurons; j++){
			
			for(int k=0; k<layers[i-1].nOfNeurons+1; k++){
			
				layers[i].neurons[j].wCopy[k] = layers[i].neurons[j].w[k]; 
			}
		}
	}
	
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {

	for(int i=1; i<nOfLayers; i++){
	
		for(int j=0; j<layers[i].nOfNeurons; j++){
			
			for(int k=0; k<layers[i-1].nOfNeurons+1; k++){
			
				layers[i].neurons[j].w[k] = layers[i].neurons[j].wCopy[k]; 
			}
		}
	}
	
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {

	double sumSigmoide = 0.0;

	for(int i=1; i<nOfLayers; i++){
	
		for(int j=0; j<layers[i].nOfNeurons; j++){
		
			sumSigmoide = layers[i].neurons[j].w[0]; //sesgo
			
			for(int k=0; k<layers[i-1].nOfNeurons+1; k++){
			
				sumSigmoide += layers[i].neurons[j].w[k+1] * layers[i-1].neurons[k].out;
			}
			
			layers[i].neurons[j].out = 1/ (1 + exp (-1*sumSigmoide));
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
double MultilayerPerceptron::obtainError(double* target) {
	
	double mse = 0.0; //ERROR CUADRATICO MEDIO
	
	for(int i=0; i<layers[nOfLayers-1].nOfNeurons; i++){
	
		mse += pow(target[i] - layers[nOfLayers-1].neurons[i].out,2);
	}
	mse = mse / (double)layers[nOfLayers-1].nOfNeurons;
	return mse;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
void MultilayerPerceptron::backpropagateError(double* target) {

	for(int i=0; i<layers[nOfLayers-1].nOfNeurons; i++){
    
    		double out = layers[nOfLayers-1].neurons[i].out;
    		layers[nOfLayers-1].neurons[i].delta = -1*(target[i] - out) * (1 - out) * out; //DERIVADA DE LA ENTRADA PARA CADA NEURONA DE CAPA SALIDA 
     }
     for(int j=nOfLayers-2; j>=1; j--){
     
	    	for(int k=0; k<layers[j].nOfNeurons; k++){
	    		double sum=0.0;
	    		for(int l=0; l<layers[j+1].nOfNeurons; l++){
	    			sum += layers[j+1].neurons[l].delta * layers[j+1].neurons[l].w[k+1];
	    		}
	    		double out = layers[j].neurons[k].out;
	    		layers[j].neurons[k].delta = sum * out*(1-out);
	    	}
     }
}


// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {

	for(int i=1; i<nOfLayers; i++){
	
		for(int j=0; j<layers[i].nOfNeurons; j++){
			
			for(int k=1; k<layers[i-1].nOfNeurons+1; k++){
			
				layers[i].neurons[j].lastDeltaW[k] = layers[i].neurons[j].deltaW[k];
				layers[i].neurons[j].deltaW[k] += layers[i].neurons[j].delta * layers[i-1].neurons[k-1].out;
			}
			
			layers[i].neurons[j].lastDeltaW[0] = layers[i].neurons[j].deltaW[0];
			layers[i].neurons[j].deltaW[0] += layers[i].neurons[j].delta;
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {

	double eeta = this->eta;

	for(int i=1; i<nOfLayers; i++){
	
		for(int j=0; j<layers[i].nOfNeurons; j++){
			
			for(int k=1; k<layers[i-1].nOfNeurons+1; k++){
			
				layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k] - eeta * layers[i].neurons[j].deltaW[k] - mu * (eeta * layers[i].neurons[j].lastDeltaW[k]);
			}
			
			layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0] - eeta * layers[i].neurons[j].deltaW[0] - mu * (eeta * layers[i].neurons[j].lastDeltaW[0]);
		}
		
		eeta = pow(decrementFactor, -(nOfLayers-i)) * eeta;
	}
}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {

	for(int i=1; i<nOfLayers; i++){
		std::cout << "Capa " << i << std::endl << "______" << std::endl;
		
		for(int j=0; j<layers[i].nOfNeurons; j++){
		
			for(int k=0; k<layers[i-1].nOfNeurons+1; k++){
			
				std::cout << layers[i].neurons[j].w[k] << "\t";
			}
			std::cout << std::endl;
		}
	}
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
void MultilayerPerceptron::performEpochOnline(double* input, double* target) {

	for(int i=1; i<nOfLayers; i++){
		
		for(int j=0; j<layers[i].nOfNeurons; j++){
		
			for(int k=0; k<layers[i-1].nOfNeurons+1; k++){
			
				layers[i].neurons[j].deltaW[k] = 0.0;
			}
		}
	}
	
	feedInputs(input);
	forwardPropagate();
	backpropagateError(target);
	accumulateChange();
	weightAdjustment();
}

// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {
	
	  std::ifstream fichero(fileName,std::ifstream::in);	
	  Dataset *dataset = new Dataset;
	  
	  if(fichero.is_open()){
	  
		  fichero >> dataset->nOfInputs >> dataset->nOfOutputs >> dataset->nOfPatterns;

		  dataset -> inputs = new double*[ dataset -> nOfPatterns];
		  
		  for(int i=0; i< dataset -> nOfPatterns; i++)
			  dataset -> inputs[i] = new double[dataset->nOfInputs];
			  
		  dataset -> outputs = new double*[dataset->nOfPatterns];
		  
		  for(int i=0; i < dataset->nOfPatterns; i++)
			  dataset -> outputs[i] = new double[dataset->nOfOutputs];

		  for(int i=0; i< dataset->nOfPatterns; i++){
			  for(int j=0; j< dataset->nOfInputs; j++){
				  fichero >> dataset -> inputs[i][j];
			  }
			  for(int k=0; k< dataset->nOfOutputs; k++){
				  fichero >> dataset -> outputs[i][k];
			  }
		  }
		  return dataset;	
	}
	else{
		std::cout << "Error al abrir el fichero" << std::endl << std::endl;
	}
	return NULL;
}

// ------------------------------
// Perform an online training for a specific trainDataset
void MultilayerPerceptron::trainOnline(Dataset* trainDataset) {
	int i;
	for(i=0; i<trainDataset->nOfPatterns; i++){
		performEpochOnline(trainDataset->inputs[i], trainDataset->outputs[i]);
	}
}

// ------------------------------
// Test the network with a dataset and return the MSE
double MultilayerPerceptron::test(Dataset* testDataset) {

	double mse = 0.0; 	
	
	for(int i=0; i< testDataset -> nOfPatterns; i++){
		feedInputs( testDataset->inputs[i]);
		forwardPropagate();
		mse += obtainError(testDataset->outputs[i]);
	}
	
	return mse / testDataset->nOfPatterns;
}


// Optional - KAGGLE
// Test the network with a dataset and return the MSE
// Your have to use the format from Kaggle: two columns (Id y predictied)
void MultilayerPerceptron::predict(Dataset* pDatosTest)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * obtained = new double[numSalidas];
	
	cout << "Id,Predicted" << endl;
	
	for (i=0; i<pDatosTest->nOfPatterns; i++){

		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(obtained);
		
		cout << i;

		for (j = 0; j < numSalidas; j++)
			cout << "," << obtained[j];
		cout << endl;

	}
}

// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
void MultilayerPerceptron::runOnlineBackPropagation(Dataset * trainDataset, Dataset * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;

	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0;
	int iterWithoutImproving;
	double testError = 0;

	double validationError = 1;
	
	// Generate validation data
	if(validationRatio > 0 && validationRatio < 1){
		// .......
	}


	// Learning
	do {

		trainOnline(trainDataset);
		double trainError = test(trainDataset);
		if(countTrain==0 || trainError < minTrainError){
			minTrainError = trainError;
			copyWeights();
			iterWithoutImproving = 0;
		}
		else if( (trainError-minTrainError) < 0.00001)
			iterWithoutImproving = 0;
		else
			iterWithoutImproving++;

		if(iterWithoutImproving==50){ //Salida porque no hay mejora
			cout << "We exit because the training is not improving!!" << endl;
			restoreWeights();
			countTrain = maxiter;
		}


		countTrain++;

		// Check validation stopping condition and force it
		// BE CAREFUL: in this case, we have to save the last validation error, not the minimum one
		// Apart from this, the way the stopping condition is checked is the same than that
		// applied for the training set

		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;

	} while ( countTrain<maxiter );

	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;
	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nOfPatterns; i++){
		double* prediction = new double[pDatosTest->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<pDatosTest->nOfOutputs; j++)
			cout << pDatosTest->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}

	testError = test(pDatosTest);
	*errorTest=testError;
	*errorTrain=minTrainError;

}

// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * archivo)
{
	// Object for writing the file
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
		f << " " << layers[i].nOfNeurons;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * archivo)
{
	// Object for reading a file
	ifstream f(archivo);

	if(!f.is_open())
		return false;

	// Number of layers and number of neurons in every layer
	int nl;
	int *npl;

	// Read number of layers
	f >> nl;

	npl = new int[nl];

	// Read number of neurons in every layer
	for(int i = 0; i < nl; i++)
		f >> npl[i];

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
