import pandas as pd
import matplotlib.pyplot as plt

'''Inputting the Dataset'''
dataset = pd.read_csv('dataset_proper.tsv', delimiter = '\t', quoting = 3)

dataset.dropna(subset=['Article'], inplace=True)
dataset = dataset.reset_index(drop=True)

'''Preparing & Cleaning the Dataset'''
import re
from nltk.corpus import stopwords
from nltk.stem.porter import PorterStemmer
corpus = []
features_cv = []
features_tfidf = []

for i in range(10377):
	article = re.sub('[^a-zA-Z ]', '', dataset['Article'][i])
	article = article.lower()
	article = article.split()
	ps = PorterStemmer()
	article = [word for word in article if not word in set(stopwords.words('english'))]
	article = [ps.stem(word) for word in article]
	article = ' '.join(article)
	corpus.append(article)

'''Vectorization'''
from sklearn.feature_extraction.text import CountVectorizer
cv = CountVectorizer(max_features = 21500) #Original = 21911 words
X = cv.fit_transform(corpus).toarray()
y = dataset.iloc[:, 1].values
features_list_original = cv.get_feature_names()

for i in range(10377):
    features_cv.append([features_list_original[j] for j in range(21500) if (X[i][j] != 0)])        

'''TF-IDF'''
from sklearn.feature_extraction.text import TfidfTransformer
transformer = TfidfTransformer()
tfidf = transformer.fit_transform(X)
tfidf = tfidf.toarray()

'''SVD'''
from sklearn.decomposition import TruncatedSVD
svd = TruncatedSVD(n_components = 100)
svdMatrix = svd.fit_transform(tfidf)

features_svd = svd.components_
U = svdMatrix
Sigma = svd.explained_variance_ratio_
Vt = features_svd

'''SVM Classification'''
from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(svdMatrix, y, test_size=0.2, random_state=42)

y_test = [word for word in y_test]

from timeit import default_timer as timer
from sklearn.svm import SVC

C = []
x = 1
for i in range(7):
    C.append(x)
    x *= 10

gamma = [float(i) for i in range(0, 15, 5)]

accuracy_rbf = [[] for i in range(3)]
time_rbf = [[] for i in range(3)]
accuracy_linear = []
time_linear = []
x = 0
for i in gamma:
    for j in C:
        start = timer()
        svm = SVC(C=j, gamma=i, kernel='rbf')
        svm.fit(X_train, y_train)
        y_pred = svm.predict(X_test)
        end = timer()
        time_rbf[x].append(end - start)
        accuracy_rbf[x].append(svm.score(X_test, y_test))
    x += 1
  
C.pop()
x = 0
for j in C:
    start = timer()
    svm = SVC(C=j, gamma='auto', kernel='linear')
    svm.fit(X_train, y_train)
    y_pred = svm.predict(X_test)
    end = timer()
    time_linear.append(end - start)
    accuracy_linear.append(svm.score(X_test, y_test))
x += 1

import heapq

random_states = []
for i in range(10, 60, 10):
    random_states.append(i)
    
'''Top 5 best accuracy data for 'rbf' kernel and their performance on different random_state value'''
tuples_rbf = []
c1 = 0.0
for i in accuracy_rbf:
    c2 = 1
    for j in i:
        tuples_rbf.append([j, c2, c1])
        c2 *= 10
    c1 += 5.0
    
largest_tuples_rbf = []
largest_tuples_rbf = heapq.nlargest(5, tuples_rbf, key=lambda e: e[0])

largest_rbf = [[] for i in range(5)]
for t in largest_tuples_rbf:
    for state in random_states:
        X_train, X_test, y_train, y_test = train_test_split(svdMatrix, y, test_size=0.2, random_state=state)
        start = timer()
        svm = SVC(C=t[1], gamma=t[2], kernel='rbf')
        svm.fit(X_train, y_train)
        y_pred = svm.predict(X_test)
        end = timer()
        largest_rbf[int((state/10) - 1)].append([svm.score(X_test, y_test), (end - start)])
    
'''Top 5 best accuracy data for 'linear' kernel and their performance on different random_state value'''
tuples_linear = []
c = 1
for i in accuracy_linear:
    tuples_linear.append([i, c])
    c *= 10
        
largest_tuples_linear = []
largest_tuples_linear = heapq.nlargest(5, tuples_linear, key=lambda e: e[0])
        
largest_linear = [[] for i in range(5)]
for t in largest_tuples_linear:
    for state in random_states:
        X_train, X_test, y_train, y_test = train_test_split(svdMatrix, y, test_size=0.2, random_state=state)
        start = timer()
        svm = SVC(C=t[1], gamma='auto', kernel='linear')
        svm.fit(X_train, y_train)
        y_pred = svm.predict(X_test)
        end = timer()
        largest_linear[int((state/10) - 1)].append([svm.score(X_test, y_test), (end - start)])              
   
        
from statistics import mean
'''mean_accuracies, mean_times, min_accuracies and max_accuracies for 'rbf' kernel'''
mean_accuracy_rbf = []
mean_time_rbf = []
min_accuracy_rbf = []
max_accuracy_rbf = []
for i in largest_rbf:
    mean_accuracy_rbf.append(mean([x[0] for x in i]))
    mean_time_rbf.append(mean([x[1] for x in i]))
    min_accuracy_rbf.append(min([x[0] for x in i]))
    max_accuracy_rbf.append(max([x[0] for x in i]))
    
'''mean_accuracies, mean_times, min_accuracies and max_accuracies for 'linear' kernel'''
mean_accuracy_linear = []
mean_time_linear = []
min_accuracy_linear = []
max_accuracy_linear = []
for i in largest_linear:
    mean_accuracy_linear.append(mean([x[0] for x in i]))
    mean_time_linear.append(mean([x[1] for x in i]))
    min_accuracy_linear.append(min([x[0] for x in i]))
    max_accuracy_linear.append(max([x[0] for x in i]))   

'''Graphs for rbf kernel'''
C.append(1000000)
i = gamma[0]
plt.title('Kernel = \'rbf\'')
plt.scatter(C, [x*100 for x in accuracy_rbf[int(int(i)/5)]], color = 'red')
plt.plot(C, [x*100 for x in accuracy_rbf[int(int(i)/5)]], color = 'red', label="gamma = 0.0")

i = gamma[1]
plt.scatter(C, [x*100 for x in accuracy_rbf[int(int(i)/5)]], color = 'green')
plt.plot(C, [x*100 for x in accuracy_rbf[int(int(i)/5)]], color = 'green', label="gamma = 5.0")

i = gamma[2]
plt.scatter(C, [x*100 for x in accuracy_rbf[int(int(i)/5)]], color = 'blue')
plt.plot(C, [x*100 for x in accuracy_rbf[int(int(i)/5)]], color = 'blue', label="gamma = 10.0")

plt.xlabel('Penalty Parameter(C)')
plt.ylabel('Accuracy (in % age)')
plt.xscale('log')
plt.legend(bbox_to_anchor=(0.65, 0.2), loc=2, borderaxespad=0.0)
plt.show()

'''Graphs for linear kernel'''
C.pop()

plt.title('Kernel = \'linear\'')
plt.scatter(C, [x*100 for x in accuracy_linear], color = 'red')
plt.plot(C, [x*100 for x in accuracy_linear], color = 'red')
plt.xlabel('Penalty Parameter(C)')
plt.ylabel('Accuracy (in % age)')
plt.xscale('log')
plt.show()

'''Graphs for 'rbf' kernel with different random_states'''
plt.title('Kernel = \'rbf\' with each gamma = 5.0')
plt.scatter([x[1] for x in largest_tuples_rbf], [x*100 for x in mean_accuracy_rbf], color = 'red')
plt.plot([x[1] for x in largest_tuples_rbf], [x*100 for x in mean_accuracy_rbf], color = 'red')
plt.xlabel('Penalty Parameter(C)')
plt.ylabel('Average Accuracy (in % age)')
plt.xscale('log')
plt.show()

'''Graphs for 'linear' kernel with different random_states'''
plt.title('Kernel = \'linear\'')
plt.scatter([x[1] for x in largest_tuples_linear], [x*100 for x in mean_accuracy_linear], color = 'red')
plt.plot([x[1] for x in largest_tuples_linear], [x*100 for x in mean_accuracy_linear], color = 'red')
plt.xlabel('Penalty Parameter(C)')
plt.ylabel('Average Accuracy (in % age)')
plt.xscale('log')
plt.show()

y_pred = [word for word in y_pred]