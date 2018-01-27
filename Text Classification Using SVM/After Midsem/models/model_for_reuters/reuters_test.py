import shelve
shelfFile = shelve.open('trainingData')
svm = shelfFile['svm']
trainingTime = shelfFile['trainingTime']
X_test = shelfFile['X_test']
y_test = shelfFile['y_test']
print("Training Time  = ", trainingTime)
y_pred = svm.predict(X_test)  #Predicted values
y_pred = list(y_pred)
listlen = len(y_pred)
diff = [(y_test[i],y_pred[i])  for i in range(listlen) if(y_test[i] != y_pred[i])]
print(svm.score(X_test, y_test))  #Accuracy