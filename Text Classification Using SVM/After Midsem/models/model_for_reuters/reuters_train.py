import pandas as pd

'''Inputting the Dataset'''
dataset = pd.read_csv('reuters.tsv', delimiter = '\t', quoting = 3)

dataset.dropna(subset=['Article'], inplace=True)
dataset = dataset.reset_index(drop=True)

'''Preparing & Cleaning the Dataset'''
import re
from nltk.corpus import stopwords
from nltk.stem.porter import PorterStemmer
corpus = []
noOfArticles = (dataset['Article'].size)
for i in range(noOfArticles):
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
cv = CountVectorizer()
#cv = CountVectorizer(max_features = 21500) #Original = 21911 words
X = cv.fit_transform(corpus).toarray()
y = dataset.iloc[:, 1].values

'''TF-IDF'''
from sklearn.feature_extraction.text import TfidfTransformer
transformer = TfidfTransformer()
tfidf = transformer.fit_transform(X)
tfidf = tfidf.toarray()

'''SVD'''
from sklearn.decomposition import TruncatedSVD
svd = TruncatedSVD(n_components = 100)
svdMatrix = svd.fit_transform(tfidf)


'''SVM Classification'''
from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(svdMatrix, y, test_size=0.2, random_state=42)

y_test = [word for word in y_test]
from timeit import default_timer as timer
from sklearn.svm import SVC
start = timer()
svm = SVC(C=10000, gamma=5, kernel='rbf')
svm.fit(X_train, y_train)
end = timer()
''' offline training data '''
import shelve
shelfFile = shelve.open('trainingData')
shelfFile['X_train'] = X_train
shelfFile['X_test'] = X_test
shelfFile['y_train'] = y_train
shelfFile['y_test'] = y_test
shelfFile['svm'] = svm
shelfFile['trainingTime'] = end - start