import pandas as pd

'''Inputting the training Dataset'''
categories = ['Politics','Sports','Television','Uplifting_news','Worldnews']
dataset = pd.DataFrame()
for i in categories :
    mydataset = pd.read_csv(i + '.tsv', delimiter = '\t', quoting = 3)
    mydataset.dropna(subset=['Article'], inplace=True)
    mydataset = mydataset.reset_index(drop=True)
    dataset = dataset.append(mydataset,ignore_index = True, verify_integrity = False)

"""Inputting test data set"""

testDataset = pd.read_csv('Custom.tsv', delimiter = '\t', quoting = 3)
#testDataset.dropna(subset=['Article'], inplace=True)
#testDataset = testDataset.reset_index(drop=True)

'''Preparing & Cleaning the training Dataset'''
import re
from nltk.corpus import stopwords
from nltk.stem.porter import PorterStemmer
corpus = []
testCorpus = []
"test data processing"
for i in range(3) :
	article = re.sub('[^a-zA-Z ]', '', str(testDataset['Article'][i]))
	article = article.lower()
	article = article.split()
	ps = PorterStemmer()
	article = [word for word in article if not word in set(stopwords.words('english'))]
	article = [ps.stem(word) for word in article]
	article = ' '.join(article)
	testCorpus.append(article)
    
"train data processing"
for i in range(5977) :
	article = re.sub('[^a-zA-Z ]', '', str(dataset['Article'][i]))
	article = article.lower()
	article = article.split()
	ps = PorterStemmer()
	article = [word for word in article if not word in set(stopwords.words('english'))]
	article = [ps.stem(word) for word in article]
	article = ' '.join(article)
	corpus.append(article)

'''Vectorization for test dataset'''
from sklearn.feature_extraction.text import CountVectorizer
cv = CountVectorizer()
X_test = cv.fit_transform(testCorpus).toarray()
y_test = testDataset.iloc[:, 1].values
testFeatures_list_original = cv.get_feature_names()
testFeatures_cv = []
for i in range(3):
    testFeatures_cv.append([testFeatures_list_original[j] for j in range(19) if (X_test[i][j] != 0)])        


'''Vectorization for training dataset'''

cv = CountVectorizer()
X = cv.fit_transform(corpus).toarray()
y = dataset.iloc[:, 1].values
features_list_original = cv.get_feature_names()
features_cv = []
#features 5803
for i in range(5977):
    features_cv.append([features_list_original[j] for j in range(5700) if (X[i][j] != 0)])        

'''TF-IDF for test dataset'''
from sklearn.feature_extraction.text import TfidfTransformer
transformer = TfidfTransformer()
tfidf = transformer.fit_transform(X_test)
tfidf = tfidf.toarray()

'''SVD for test dataset'''
from sklearn.decomposition import TruncatedSVD
svd = TruncatedSVD(n_components = 3)
svdMatrix_test = svd.fit_transform(tfidf)

features_svd_test = svd.components_

'''TF-IDF for training dataset'''

transformer = TfidfTransformer()
tfidf = transformer.fit_transform(X)
tfidf = tfidf.toarray()

'''SVD for training dataset'''

svd = TruncatedSVD(n_components = 3)
svdMatrix = svd.fit_transform(tfidf)

features_svd = svd.components_


'''SVM Classification'''
"""from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(svdMatrix, y, test_size=0.2, random_state=80)

y_test = [word for word in y_test]"""

''' y_test and y_train'''
y_test = [word for word in y_test]
y_train  = [word for word in y]

#from timeit import default_timer as timer
from sklearn.svm import SVC

svm = SVC(C=10, gamma=5, kernel='rbf')
svm.fit(svdMatrix, y_train)
y_pred = svm.predict(svdMatrix_test)  #Predicted values
print(svm.score(svdMatrix_test, y_test))  #Accuracy