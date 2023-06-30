#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sun Oct 25 12:37:04 2020

IMC: lab assignment 3

@author: pagutierrez
"""
import math
import pickle
import os
import warnings
import click
import pandas as pd
import numpy as np
import scipy
import sklearn
import sklearn.cluster
import sklearn.metrics
import sklearn.preprocessing
import scipy.spatial.distance
import sklearn.linear_model
from sklearn.model_selection import train_test_split

warnings.filterwarnings('ignore')

@click.command()
@click.option('--train_file', '-t', default=None, required=True,
              help=u'Name of the file with training data.')
@click.option('--test_file', '-T', default=None, required=False,
              help=u'Name of the file with test data')

@click.option('--classification', '-c', is_flag=True, default=False, required=False,
              help=u'Booleano que indica si el problema es de clasificacion o no, si no se especifica es regresión')

@click.option('--ratio_rbf', '-r', default=0.1, required=False,
              help=u'Indica la razón de neuronas RBF con respecto al total de patrones. Por defecto 0.1 capa oculta')

@click.option('--l2', '-l', is_flag=True, default=False, required=False,
              help=u'Booleano que indica si utilizaremos regularización de L2 en lugar de regularización L1. Por defecto L1')

@click.option('--eta', '-e', default=0.01, required=False,
              help=u'Indica el valor del paramétro eta')

@click.option('--outputs', '-o', default=1, required=False, show_default=True,
              help=u'Numero de columnas de salida que tiene el conjunto de datos. Por defecto 1')

@click.option('--pred', '-p', is_flag=True, default=False, show_default=True, required=False,
              help=u'Use the prediction mode.') # KAGGLE
@click.option('--model', '-m', default="", show_default=False,
              help=u'Directory name to save the models (or name of the file to load the model, if the prediction mode is active).') # KAGGLE

def train_rbf_total(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, model, pred):
    """ 5 executions of RBFNN training
    
        RBF neural network based on hybrid supervised/unsupervised training.
        We run 5 executions with different seeds.
    """

    if not pred:    #Modo predicción desactivado

        if train_file is None:
            print("You have not specified the training file (-t)")
            return

        train_mses = np.empty(5)
        train_ccrs = np.empty(5)
        test_mses = np.empty(5)
        test_ccrs = np.empty(5)

        for s in range(1,6,1):   
            print("-----------")
            print("Seed: %d" % s)
            print("-----------")     
            np.random.seed(s)   # Inicializan las semillas de forma aleatoria
            train_mses[s-1], test_mses[s-1], train_ccrs[s-1], test_ccrs[s-1] = \
                train_rbf(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, \
                             model and "{}/{}.pickle".format(model, s) or "")
            print("Training MSE: %f" % train_mses[s-1])
            print("Test MSE: %f" % test_mses[s-1])
            print("Training CCR: %.2f%%" % train_ccrs[s-1])
            print("Test CCR: %.2f%%" % test_ccrs[s-1])
        
        print("******************")
        print("Summary of results")
        print("******************")
        print("Training MSE: %f +- %f" % (np.mean(train_mses), np.std(train_mses)))
        print("Test MSE: %f +- %f" % (np.mean(test_mses), np.std(test_mses)))
        print("Training CCR: %.2f%% +- %.2f%%" % (np.mean(train_ccrs), np.std(train_ccrs)))
        print("Test CCR: %.2f%% +- %.2f%%" % (np.mean(test_ccrs), np.std(test_ccrs)))
            
    else:   #Modo prediccion activado
        # KAGGLE
        if model is None:
            print("You have not specified the file with the model (-m).")
            return

        # Obtain the predictions for the test set
        predictions = predict(test_file, model)

        # Print the predictions in csv format
        print("Id,Category")
        for prediction, index in zip(predictions, range(len(predictions))):
            s = ""            
            s += str(index)
            
            if isinstance(prediction, np.ndarray):
                for output in prediction:
                    s += ",{}".format(output)
            else:
                s += ",{}".format(int(prediction))
                
            print(s)
            


def train_rbf(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, model_file=""):
    """ One execution of RBFNN training
    
        RBF neural network based on hybrid supervised/unsupervised training.
        We run 1 executions.

        Parameters
        ----------
        train_file: string
            Name of the training file
        test_file: string
            Name of the test file
        classification: bool
            True if it is a classification problem
        ratio_rbf: float
            Ratio (as a fraction of 1) indicating the number of RBFs
            with respect to the total number of patterns
        l2: bool
            True if we want to use L2 regularization for logistic regression 
            False if we want to use L1 regularization for logistic regression
        eta: float
            Value of the regularization factor for logistic regression
        outputs: int
            Number of variables that will be used as outputs (all at the end
            of the matrix)
        model_file: string
            Name of the file where the model will be written

        Returns
        -------
        train_mse: float
            Mean Squared Error for training data 
            For classification, we will use the MSE of the predicted probabilities
            with respect to the target ones (1-of-J coding)
        test_mse: float 
            Mean Squared Error for test data 
            For classification, we will use the MSE of the predicted probabilities
            with respect to the target ones (1-of-J coding)
        train_ccr: float
            Training accuracy (CCR) of the model 
            For regression, we will return a 0
        test_ccr: float
            Training accuracy (CCR) of the model 
            For regression, we will return a 0
    """
    train_inputs, train_outputs, test_inputs, test_outputs = read_data(train_file, test_file, outputs)

    #TODO: Obtain num_rbf from ratio_rbf
    num_rbf = round(ratio_rbf * len(train_inputs))

    print("Number of RBFs used: %d" %(num_rbf))
    kmeans, distances, centers = clustering(classification, train_inputs, 
                                              train_outputs, num_rbf)
    
    radii = calculate_radii(centers, num_rbf)
    
    r_matrix = calculate_r_matrix(distances, radii)

    if not classification:
        coefficients = invert_matrix_regression(r_matrix, train_outputs)
        train_predictions = np.matmul(r_matrix, coefficients)
        train_mse = sklearn.metrics.mean_squared_error(train_predictions, train_outputs)
        #Para el último apartado
        train_ccr = 100 * sklearn.metrics.accuracy_score(train_outputs, np.around(train_predictions))
        #train_ccr = 0
    else:
        logreg = logreg_classification(r_matrix, train_outputs, l2, eta)
        predictions = logreg.predict_proba(r_matrix)
        #OneHotEncode: Crea una columna binaria para cada categoria y devuelve una matriz dispersa
        salidas_train = sklearn.preprocessing.OneHotEncoder(categories='auto').fit_transform(train_outputs).toarray()
        train_mse = sklearn.metrics.mean_squared_error(predictions, salidas_train)
        train_ccr = 100 * logreg.score(r_matrix, train_outputs)

    """
    TODO: Obtain the distances from the centroids to the test patterns
          and obtain the R matrix for the test set
    """
    distancias_test = kmeans.transform(test_inputs)
    matriz_r_test = calculate_r_matrix(distancias_test, radii)

    # # # # KAGGLE # # # #
    if model_file != "":
        save_obj = {
            'classification' : classification,
            'radii' : radii,
            'kmeans' : kmeans
        }
        if not classification:
            save_obj['coefficients'] = coefficients
        else:
            save_obj['logreg'] = logreg

        dir = os.path.dirname(model_file)
        if not os.path.isdir(dir):
            os.makedirs(dir)

        with open(model_file, 'wb') as f:
            pickle.dump(save_obj, f)

    # # # # # # # # # # #

    if not classification:
        """
        TODO: Obtain the predictions for training and test and calculate
              the MSE
        """
        test_predictions = np.matmul(matriz_r_test, coefficients)
        test_mse = sklearn.metrics.mean_squared_error(test_predictions, test_outputs)
        # Para el último apartado
        test_ccr = 100 * sklearn.metrics.accuracy_score(test_outputs, np.around(test_predictions))
        #test_ccr=0

    else:
        """
        TODO: Obtain the predictions for training and test and calculate
              the CCR. Obtain also the MSE, but comparing the obtained
              probabilities and the target probabilities
        """
        test_predictions = logreg.predict(matriz_r_test)
        predictions = logreg.predict_proba(matriz_r_test)
        salidas_test = sklearn.preprocessing.OneHotEncoder(categories='auto').fit_transform(test_outputs).toarray()

        test_mse = sklearn.metrics.mean_squared_error(predictions, salidas_test)
        test_ccr = 100 * logreg.score(matriz_r_test, test_outputs)
        print("Matriz de confusión del Test")
        print(sklearn.metrics.confusion_matrix(test_outputs, test_predictions))

    return train_mse, test_mse, train_ccr, test_ccr

def read_data(train_file, test_file, outputs):
    """ Read the input data
        It receives the name of the input data file names (training and test)
        and returns the corresponding matrices

        Parameters
        ----------
        train_file: string
            Name of the training file
        test_file: string
            Name of the test file
        outputs: int
            Number of variables to be used as outputs
            (all at the end of the matrix).
              
        Returns
        -------
        train_inputs: array, shape (n_train_patterns,n_inputs)
            Matrix containing the inputs for the training patterns
        train_outputs: array, shape (n_train_patterns,n_outputs)
            Matrix containing the outputs for the training patterns
        test_inputs: array, shape (n_test_patterns,n_inputs)
            Matrix containing the inputs for the test patterns
        test_outputs: array, shape (n_test_patterns,n_outputs)
            Matrix containing the outputs for the test patterns
    """

    train = pd.read_csv(train_file, header=None)
    train = np.array(train)
    train = train.astype(np.float64)
    train_inputs = train[:, :-outputs]
    train_outputs = train[:, -outputs:]

    test = pd.read_csv(test_file, header=None)
    test = np.array(test)
    test = test.astype(np.float64)
    test_inputs = test[:, :-outputs]
    test_outputs = test[:, -outputs:]

    #TODO: Complete the code of the function
    return train_inputs, train_outputs, test_inputs, test_outputs

def init_centroids_classification(train_inputs, train_outputs, num_rbf):
    """ Initialize the centroids for the case of classification
        This method selects, approximately, num_rbf/num_clases
        patterns for each class.

        Parameters
        ----------
        train_inputs: array, shape (n_patterns,n_inputs)
            Matrix with all the input variables
        train_outputs: array, shape (n_patterns,n_outputs)
            Matrix with the outputs of the dataset
        num_rbf: int
            Number of RBFs to be used in the network
            
        Returns
        -------
        centroids: array, shape (num_rbf,n_inputs)
            Matrix with all the centroids already selected
    """
    
    #TODO: Complete the code of the function
    centroids = train_test_split(train_inputs, train_outputs, stratify=train_outputs, test_size=num_rbf / len(train_inputs))

    return centroids

def clustering(classification, train_inputs, train_outputs, num_rbf):
    """ It applies the clustering process
        A clustering process is applied to set the centers of the RBFs.
        In the case of classification, the initial centroids are set
        using the method init_centroids_classification(). 
        In the case of regression, the centroids have to be set randomly.

        Parameters
        ----------
        classification: bool
            True if it is a classification problem
        train_inputs: array, shape (n_patterns,n_inputs)
            Matrix with all the input variables
        train_outputs: array, shape (n_patterns,n_outputs)
            Matrix with the outputs of the dataset
        num_rbf: int
            Number of RBFs to be used in the network
            
        Returns
        -------
        kmeans: sklearn.cluster.KMeans
            KMeans object after the clustering
        distances: array, shape (n_patterns,num_rbf)
            Matrix with the distance from each pattern to each RBF center
        centers: array, shape (num_rbf,n_inputs)
            Centers after the clustering
    """

    #TODO: Complete the code of the function
    if(classification):
        centroids = init_centroids_classification(train_inputs, train_outputs, num_rbf)
        #kmeans = sklearn.cluster.KMeans(len(centroids), centroids, 1, 500).fit(train_inputs, train_outputs)
        # Para el apartado k-means++
        kmeans = sklearn.cluster.KMeans(num_rbf, init='k-means++', n_init=1, max_iter=500).fit(train_inputs, train_outputs)
    else:
        #kmeans = sklearn.cluster.KMeans(num_rbf, init='random', n_init=1, max_iter=500).fit(train_inputs, train_outputs)
        #Para el apartado k-means++
        kmeans = sklearn.cluster.KMeans(num_rbf, init='k-means++', n_init=1, max_iter=500).fit(train_inputs, train_outputs)

    centers = kmeans.cluster_centers_
    distances = kmeans.transform(train_inputs)
    return kmeans, distances, centers

def calculate_radii(centers, num_rbf):
    """ It obtains the value of the radii after clustering
        This methods is used to heuristically obtain the radii of the RBFs
        based on the centers

        Parameters
        ----------
        centers: array, shape (num_rbf,n_inputs)
            Centers from which obtain the radii
        num_rbf: int
            Number of RBFs to be used in the network
            
        Returns
        -------
        radii: array, shape (num_rbf,)
            Array with the radius of each RBF
    """

    #TODO: Complete the code of the function
    dist = scipy.spatial.distance.squareform(scipy.spatial.distance.pdist(centers))
    radii = np.array([], dtype=np.float64)

    for x in range(0, num_rbf):
        sumdist = sum(dist[x])
        sumdist = sumdist / (2 * (num_rbf - 1))
        radii = np.append(radii, sumdist)

    return radii

def calculate_r_matrix(distances, radii):
    """ It obtains the R matrix
        This method obtains the R matrix (as explained in the slides),
        which contains the activation of each RBF for each pattern, including
        a final column with ones, to simulate bias
        
        Parameters
        ----------
        distances: array, shape (n_patterns,num_rbf)
            Matrix with the distance from each pattern to each RBF center
        radii: array, shape (num_rbf,)
            Array with the radius of each RBF
            
        Returns
        -------
        r_matrix: array, shape (n_patterns,num_rbf+1)
            Matrix with the activation of every RBF for every pattern. Moreover
            we include a last column with ones, which is going to act as bias
    """

    #TODO: Complete the code of the function
    r_matrix = np.empty([len(distances), len(radii) +1]) #Matriz vacia
    r_matrix.astype(np.float64)

    for i in range(0, len(distances)):
        for j in range(0, len(radii)):
            #Gausiana
            r_matrix[i][j] = math.exp(distances[i,j] * distances[i,j] / (-2 * radii[j] * radii[j]))

    r_matrix[:, -1] = 1

    return r_matrix

def invert_matrix_regression(r_matrix, train_outputs):
    """ Inversion of the matrix for regression case
        This method obtains the pseudoinverse of the r matrix and multiplies
        it by the targets to obtain the coefficients in the case of linear
        regression
        
        Parameters
        ----------
        r_matrix: array, shape (n_patterns,num_rbf+1)
            Matrix with the activation of every RBF for every pattern. Moreover
            we include a last column with ones, which is going to act as bias
        train_outputs: array, shape (n_patterns,n_outputs)
            Matrix with the outputs of the dataset
              
        Returns
        -------
        coefficients: array, shape (n_outputs,num_rbf+1)
            For every output, values of the coefficients for each RBF and value 
            of the bias 
    """

    #TODO: Complete the code of the function
    if len(r_matrix) == len(r_matrix[0]):
        coefficients = np.matmul(np.linalg.inv(r_matrix), train_outputs)
    else:
        coefficients = np.matmul(np.matmul(np.linalg.pinv(np.matmul(r_matrix.T, r_matrix)), r_matrix.T), train_outputs)

    return coefficients

def logreg_classification(r_matrix, train_outputs, l2, eta):
    """ Performs logistic regression training for the classification case
        It trains a logistic regression object to perform classification based
        on the R matrix (activations of the RBFs together with the bias)
        
        Parameters
        ----------
        r_matrix: array, shape (n_patterns,num_rbf+1)
            Matrix with the activation of every RBF for every pattern. Moreover
            we include a last column with ones, which is going to act as bias
        train_outputs: array, shape (n_patterns,n_outputs)
            Matrix with the outputs of the dataset
        l2: bool
            True if we want to use L2 regularization for logistic regression 
            False if we want to use L1 regularization for logistic regression
        eta: float
            Value of the regularization factor for logistic regression
              
        Returns
        -------
        logreg: sklearn.linear_model.LogisticRegression
            Scikit-learn logistic regression model already trained
    """

    #TODO: Complete the code of the function
    if l2:
        logreg = sklearn.linear_model.LogisticRegression(penalty='l2', C=1/eta, solver='liblinear', multi_class='auto', max_iter=600)
    else:
        logreg = sklearn.linear_model.LogisticRegression(penalty='l1', C=1/eta, solver='liblinear', multi_class='auto', max_iter=600)

    logreg.fit(r_matrix, train_outputs.ravel())
    return logreg


def predict(test_file, model_file):
    """ Performs a prediction with RBFNN model
        It obtains the predictions of a RBFNN model for a test file, using two files, one
        with the test data and one with the model

        Parameters
        ----------
        test_file: string
            Name of the test file
        model_file: string
            Name of the file containing the model data

        Returns
        -------
        test_predictions: array, shape (n_test_patterns,n_outputs)
            Predictions obtained with the model and the test file inputs
    """
    test_df = pd.read_csv(test_file, header=None)
    test_inputs = test_df.values[:, :]
    
    with open(model_file, 'rb') as f:
        saved_data = pickle.load(f)
    
    radii = saved_data['radii']
    classification = saved_data['classification']
    kmeans = saved_data['kmeans']
    
    test_distancias = kmeans.transform(test_inputs)    
    test_r = calculate_r_matrix(test_distancias, radii)    
    
    if classification:
        logreg = saved_data['logreg']
        test_predictions = logreg.predict(test_r)
    else:
        coeficientes = saved_data['coefficients']
        test_predictions = np.dot(test_r, coeficientes)
        
    return test_predictions
    
if __name__ == "__main__":
    train_rbf_total()
