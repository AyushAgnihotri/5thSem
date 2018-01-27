import shelve
shelfFile = shelve.open('trainingData')
svm = shelfFile['svm']
X_test = shelfFile['X_test']
y_test = shelfFile['y_test']
y_pred = svm.predict(X_test)  #Predicted values
y_pred = [i for i in y_pred ]
print(svm.score(X_test, y_test))  #Accuracy