#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Mon Nov 23 10:14:36 2017

@author: pedroa
"""
import time
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from sklearn import svm
from sklearn import model_selection
from sklearn import preprocessing
from sklearn.model_selection import GridSearchCV

data = pd.read_csv('datasetsLA4IMC/Datasets/csv/train_spam.csv',header=None)
X = data.iloc[:,:-1].values
Y = data.iloc[:,-1].values
data = pd.read_csv('datasetsLA4IMC/Datasets/csv/test_spam.csv',header=None)
X_test = data.iloc[:,:-1].values
Y_test = data.iloc[:,-1].values

# Train the SVM model
svm_model = svm.SVC(kernel='linear', C=10)
svm_model.fit(X,Y)

print(svm_model.score(X_test, Y_test))

