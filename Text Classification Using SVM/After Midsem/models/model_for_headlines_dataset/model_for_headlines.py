import pandas as pd

'''Inputting the Dataset'''
categories = ['Politics','Sports','Television','Uplifting_news','Worldnews']
dataset = pd.DataFrame()
for i in categories :
    mydataset = pd.read_csv(i + '.tsv', delimiter = '\t', quoting = 3)
    mydataset.dropna(subset=['Article'], inplace=True)
    mydataset = mydataset.reset_index(drop=True)
    dataset = dataset.append(mydataset,ignore_index = True, verify_integrity = False)


'''Preparing & Cleaning the Dataset'''
import re
from nltk.corpus import stopwords
from nltk.stem.porter import PorterStemmer
corpus = []
noOfArticles = (dataset['Article'].size)
for i in range(noOfArticles) :
	article = re.sub('[^a-zA-Z ]', '', str(dataset['Article'][i]))
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

features_svd = svd.components_


'''SVM Classification'''
from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(svdMatrix, y, test_size=0.2, random_state=67)

y_test = [word for word in y_test]

#from timeit import default_timer as timer
from sklearn.svm import SVC

svm = SVC(C=10,gamma = 5,kernel='rbf')
svm.fit(X_train, y_train)
y_pred = svm.predict(X_test)  #Predicted values
print(svm.score(X_test, y_test))  #Accuracy