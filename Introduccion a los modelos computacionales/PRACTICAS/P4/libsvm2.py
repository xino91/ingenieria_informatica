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

data = pd.read_csv('datasetsLA4IMC/Datasets/csv/train_nomnist.csv',header=None)
X = data.iloc[:,:-1].values
y = data.iloc[:,-1].values

scaler = preprocessing.StandardScaler ()  #Estandarización
X = scaler.fit_transform (X , y )
x_train , x_test , y_train, y_test = model_selection.train_test_split(X , y , stratify =y , test_size =0.25 , random_state =5)

# Train the SVM model
svm_model = svm.SVC(kernel='rbf')
#svm_model.fit(X, y)
#print("CCR: " ,svm_model.score(X,y))

start_time = time.time()
Cs = np.logspace(-3, 3, num=7, base=10)
Gs = np.logspace(-3, 3, num=7, base=10)
optimo = GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs,gamma=Gs),n_jobs=-1,cv=3)
optimo.fit(x_train,y_train)
end = time.time()

print(optimo.score(x_test, y_test))
print(end - start_time)
